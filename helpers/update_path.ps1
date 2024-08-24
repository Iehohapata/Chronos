param (
    [string]$appPath,
	[switch]$SystemWide
)

if ($SystemWide.IsPresent) {
    $scope = "Machine"
    Write-Host "Installing system-wide (Machine level)."
} else {
    $scope = "User"
    Write-Host "Installing for the current user (User level)."
}

$currentPath = [Environment]::GetEnvironmentVariable("Path", $scope)
if (-not ($currentPath -like "*$appPath*")) {
    [Environment]::SetEnvironmentVariable(
        "Path",
        $currentPath + ";" + $appPath,
        $scope
    )
    Write-Host "Path environment variable updated."
} else {
    Write-Host "Path environment variable seems to already contain the variable"
}

if ($scope -eq "User") {
    $env:Path = [Environment]::GetEnvironmentVariable("Path", "User")
}