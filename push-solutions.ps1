# ============================================================================
# push-solutions.ps1 -- Push solutions to all student assignment repos
#
# Pushes SOLUTIONS.md to each student's GitHub Classroom repo via:
#   1. A 'solutions' branch (students can checkout to see answers)
#   2. A pull request (shows up in their PR tab)
#
# Prerequisites:
#   - gh CLI installed and authenticated: gh auth login
#   - You must have push access to the student repos (Classroom owner/admin)
#
# Usage:
#   .\push-solutions.ps1 -Org <ORG> -Prefix <ASSIGNMENT_PREFIX> -SolutionsFile <PATH> [-DryRun]
#
# Example:
#   .\push-solutions.ps1 -Org MehtaPlusTutoring -Prefix assignment1 -SolutionsFile solutions\SOLUTIONS.md
#   .\push-solutions.ps1 -Org MehtaPlusTutoring -Prefix assignment1 -SolutionsFile solutions\SOLUTIONS.md -DryRun
# ============================================================================

param(
    [Parameter(Mandatory=$true)]
    [string]$Org,

    [Parameter(Mandatory=$true)]
    [string]$Prefix,

    [Parameter(Mandatory=$true)]
    [string]$SolutionsFile,

    [switch]$DryRun
)

$ErrorActionPreference = "Stop"
$BranchName = "solutions"
$PrTitle = "Solution Key"
$PrBody = @"
Solutions have been posted. Check ``solutions/SOLUTIONS.md`` for the answer key.

> **Note**: These are the optimal O(N) array-based solutions. Compare them with
> your approach to understand the performance differences shown in the scaling tests.
"@

# ── Validate ─────────────────────────────────────────────────
if (-not (Test-Path $SolutionsFile)) {
    Write-Error "Solutions file not found: $SolutionsFile"
    exit 1
}
$SolutionsAbs = (Resolve-Path $SolutionsFile).Path

if (-not (Get-Command gh -ErrorAction SilentlyContinue)) {
    Write-Error "gh CLI not found. Install from https://cli.github.com"
    exit 1
}

$authCheck = gh auth status 2>&1
if ($LASTEXITCODE -ne 0) {
    Write-Error "Not authenticated. Run: gh auth login"
    exit 1
}

# ── List student repos ───────────────────────────────────────
Write-Host "Fetching repos matching '$Prefix-*' in org '$Org'..."
$reposJson = gh api --paginate "/orgs/$Org/repos?per_page=100" 2>&1
$repos = ($reposJson | ConvertFrom-Json) | Where-Object { $_.name -like "$Prefix-*" } | Select-Object -ExpandProperty name

if (-not $repos -or $repos.Count -eq 0) {
    Write-Host "No repos found matching '$Prefix-*' in org '$Org'." -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Troubleshooting:"
    Write-Host "  - Check that '$Org' is the correct org (Classroom may use a different org)"
    Write-Host "  - Check that '$Prefix' matches the assignment name exactly"
    Write-Host "  - Ensure you have admin/owner access to the org"
    exit 1
}

# Handle single repo (PowerShell wraps single items differently)
if ($repos -is [string]) { $repos = @($repos) }

Write-Host "Found $($repos.Count) student repos:"
$repos | ForEach-Object { Write-Host "  $_" }
Write-Host ""

if ($DryRun) {
    Write-Host "(dry run -- no changes made)" -ForegroundColor Cyan
    exit 0
}

# ── Push solutions to each repo ──────────────────────────────
$workDir = Join-Path $env:TEMP "push-solutions-$(Get-Random)"
New-Item -ItemType Directory -Path $workDir -Force | Out-Null
$success = 0
$failed = 0

foreach ($repo in $repos) {
    Write-Host ""
    Write-Host "-- $Org/$repo --" -ForegroundColor Cyan

    $repoDir = Join-Path $workDir $repo

    # Shallow clone
    $cloneOutput = gh repo clone "$Org/$repo" $repoDir -- --depth=1 -q 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  SKIP: Failed to clone" -ForegroundColor Yellow
        $failed++
        continue
    }

    Push-Location $repoDir

    # Create solutions branch
    git checkout -b $BranchName 2>$null
    if ($LASTEXITCODE -ne 0) {
        git fetch origin $BranchName 2>$null
        git checkout $BranchName 2>$null
        if ($LASTEXITCODE -ne 0) {
            git checkout -b $BranchName 2>$null
        }
    }

    # Copy solutions file
    New-Item -ItemType Directory -Path "solutions" -Force | Out-Null
    Copy-Item $SolutionsAbs "solutions\SOLUTIONS.md" -Force

    # Commit and push
    git add -f solutions/SOLUTIONS.md 2>$null
    $diffCheck = git diff --cached --quiet 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "  SKIP: Solutions already up to date" -ForegroundColor Gray
    } else {
        git commit -m "Add solution key (posted after deadline)" `
            --author="Bhagirath Mehta <bhagirath.mehta.bmehta@gmail.com>" -q 2>$null
        git push origin $BranchName -q 2>&1 | Out-Null
        Write-Host "  DONE: Pushed '$BranchName' branch" -ForegroundColor Green
    }

    # Create PR if one doesn't exist
    $existingPr = gh pr list --repo "$Org/$repo" --head $BranchName --json number -q ".[0].number" 2>$null
    if (-not $existingPr) {
        $prOutput = gh pr create --repo "$Org/$repo" `
            --head $BranchName --base main `
            --title $PrTitle `
            --body $PrBody 2>&1
        if ($LASTEXITCODE -eq 0) {
            Write-Host "  DONE: Created pull request" -ForegroundColor Green
        } else {
            Write-Host "  WARN: Could not create PR (may need different base branch)" -ForegroundColor Yellow
        }
    } else {
        Write-Host "  SKIP: PR #$existingPr already exists" -ForegroundColor Gray
    }

    $success++
    Pop-Location
}

# ── Cleanup ──────────────────────────────────────────────────
Remove-Item $workDir -Recurse -Force -ErrorAction SilentlyContinue

Write-Host ""
Write-Host ("=" * 40)
Write-Host "  Done: $success succeeded, $failed failed (out of $($repos.Count))"
Write-Host ("=" * 40)
