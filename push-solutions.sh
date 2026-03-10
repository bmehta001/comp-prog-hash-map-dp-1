#!/usr/bin/env bash
# ============================================================================
# push-solutions.sh -- Push solutions to all student assignment repos
#
# Pushes SOLUTIONS.md to each student's GitHub Classroom repo via:
#   1. A 'solutions' branch (students can checkout to see answers)
#   2. A pull request (shows up in their PR tab / feedback PR)
#
# Prerequisites:
#   - gh CLI installed and authenticated: gh auth login
#   - You must have push access to the student repos (Classroom owner/admin)
#
# Usage:
#   bash push-solutions.sh <ORG> <ASSIGNMENT_PREFIX> <SOLUTIONS_FILE> [--dry-run]
#
# Example:
#   bash push-solutions.sh MehtaPlusTutoring assignment1 solutions/SOLUTIONS.md
#   bash push-solutions.sh MehtaPlusTutoring assignment1 solutions/SOLUTIONS.md --dry-run
# ============================================================================

set -euo pipefail

# ── Parse arguments ──────────────────────────────────────────
if [ $# -lt 3 ]; then
    echo "Usage: $0 <ORG> <ASSIGNMENT_PREFIX> <SOLUTIONS_FILE> [--dry-run]"
    echo ""
    echo "  ORG               GitHub org where student repos live"
    echo "  ASSIGNMENT_PREFIX  Assignment name (repos are named {prefix}-{username})"
    echo "  SOLUTIONS_FILE    Path to the SOLUTIONS.md file to push"
    echo "  --dry-run         List repos without pushing (optional)"
    exit 1
fi

ORG="$1"
PREFIX="$2"
SOLUTIONS_FILE="$3"
DRY_RUN="${4:-}"
BRANCH_NAME="solutions"
PR_TITLE="Solution Key"
PR_BODY="Solutions have been posted. Check \`solutions/SOLUTIONS.md\` for the answer key.

> **Note**: These are the optimal O(N) array-based solutions. Compare them with
> your approach to understand the performance differences shown in the scaling tests."

# ── Validate ─────────────────────────────────────────────────
if [ ! -f "$SOLUTIONS_FILE" ]; then
    echo "ERROR: Solutions file not found: $SOLUTIONS_FILE"
    exit 1
fi

if ! command -v gh &> /dev/null; then
    echo "ERROR: gh CLI not found. Install from https://cli.github.com"
    exit 1
fi

if ! gh auth status &> /dev/null; then
    echo "ERROR: Not authenticated. Run: gh auth login"
    exit 1
fi

# ── List student repos ───────────────────────────────────────
echo "Fetching repos matching '$PREFIX-*' in org '$ORG'..."
REPOS=$(gh api --paginate "/orgs/$ORG/repos?per_page=100" \
    -q ".[] | select(.name | startswith(\"$PREFIX-\")) | .name" 2>&1)

if [ -z "$REPOS" ]; then
    echo "No repos found matching '$PREFIX-*' in org '$ORG'."
    echo ""
    echo "Troubleshooting:"
    echo "  - Check that '$ORG' is the correct org (Classroom may use a different org)"
    echo "  - Check that '$PREFIX' matches the assignment name exactly"
    echo "  - Ensure you have admin/owner access to the org"
    exit 1
fi

REPO_COUNT=$(echo "$REPOS" | wc -l | tr -d ' ')
echo "Found $REPO_COUNT student repos:"
echo "$REPOS" | sed 's/^/  /'
echo ""

if [ "$DRY_RUN" = "--dry-run" ]; then
    echo "(dry run -- no changes made)"
    exit 0
fi

# ── Push solutions to each repo ──────────────────────────────
WORK_DIR=$(mktemp -d)
SOLUTIONS_ABS=$(realpath "$SOLUTIONS_FILE")
SUCCESS=0
FAILED=0

for REPO in $REPOS; do
    echo ""
    echo "── $ORG/$REPO ──"

    REPO_DIR="$WORK_DIR/$REPO"

    # Shallow clone
    if ! gh repo clone "$ORG/$REPO" "$REPO_DIR" -- --depth=1 -q 2>&1; then
        echo "  SKIP: Failed to clone"
        FAILED=$((FAILED + 1))
        continue
    fi

    cd "$REPO_DIR"

    # Create solutions branch from main
    git checkout -b "$BRANCH_NAME" 2>/dev/null || {
        # Branch might already exist remotely
        git fetch origin "$BRANCH_NAME" 2>/dev/null && \
        git checkout "$BRANCH_NAME" 2>/dev/null || \
        git checkout -b "$BRANCH_NAME" 2>/dev/null
    }

    # Copy solutions file
    mkdir -p solutions
    cp "$SOLUTIONS_ABS" solutions/SOLUTIONS.md

    # Commit and push
    git add -f solutions/SOLUTIONS.md
    if git diff --cached --quiet; then
        echo "  SKIP: Solutions already up to date"
    else
        git commit -m "Add solution key (posted after deadline)" \
            --author="Bhagirath Mehta <bhagirath.mehta.bmehta@gmail.com>" -q
        git push origin "$BRANCH_NAME" -q 2>&1
        echo "  DONE: Pushed '$BRANCH_NAME' branch"
    fi

    # Create PR if one doesn't exist
    EXISTING_PR=$(gh pr list --repo "$ORG/$REPO" --head "$BRANCH_NAME" --json number -q '.[0].number' 2>/dev/null || echo "")
    if [ -z "$EXISTING_PR" ]; then
        gh pr create --repo "$ORG/$REPO" \
            --head "$BRANCH_NAME" --base main \
            --title "$PR_TITLE" \
            --body "$PR_BODY" 2>&1 && \
            echo "  DONE: Created pull request" || \
            echo "  WARN: Could not create PR (may need different base branch)"
    else
        echo "  SKIP: PR #$EXISTING_PR already exists"
    fi

    SUCCESS=$((SUCCESS + 1))
    cd "$WORK_DIR"
done

# ── Cleanup ──────────────────────────────────────────────────
rm -rf "$WORK_DIR"

echo ""
echo "════════════════════════════════════════"
echo "  Done: $SUCCESS succeeded, $FAILED failed (out of $REPO_COUNT)"
echo "════════════════════════════════════════"
