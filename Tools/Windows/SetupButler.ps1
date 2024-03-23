# Turn on debugging and verbose messages
$DebugPreference = 'Continue'
$VerbosePreference = 'Continue'

# Define the URL and the target folder
$url = "https://broth.itch.ovh/butler/windows-amd64/LATEST/archive/default"
$zipFile = "butler.zip"
$targetFolder = "butler"

# Write an informational message
Write-Host "Starting download of Butler from: $url"

# Download the file
Invoke-WebRequest -Uri $url -OutFile $zipFile -Verbose

# Check if the download was successful
if (Test-Path -Path $zipFile) {
    Write-Verbose "Downloaded the file successfully."
} else {
    Write-Error "Failed to download the file."
    exit
}

# Write an informational message
Write-Host "Unzipping the file: $zipFile"

# Unzip the file
Expand-Archive -LiteralPath $zipFile -DestinationPath $targetFolder -Force -Verbose

# Check if the extraction was successful
$butlerPath = Join-Path -Path $PWD -ChildPath $targetFolder
if (Test-Path -Path $butlerPath) {
    Write-Verbose "Extracted the archive successfully to $butlerPath"
} else {
    Write-Error "Failed to extract the archive."
    exit
}

# Validate if butler.exe exists
$butlerExePath = Join-Path -Path $butlerPath -ChildPath "butler.exe"
if (Test-Path -Path $butlerExePath) {
    Write-Verbose "Found butler.exe at $butlerExePath"
} else {
    Write-Error "butler.exe is missing in the $butlerPath directory."
    exit
}

# Write an informational message
Write-Host "Removing the ZIP file: $zipFile"

# Remove the ZIP file if no longer needed
Remove-Item -Path $zipFile -Verbose

# Add the butler folder to the PATH environment variable for the current session
$env:Path += ";$butlerPath"
Write-Verbose "Added Butler to the PATH for the current session."

# Set the PATH environment variable for the machine
[System.Environment]::SetEnvironmentVariable("Path", $env:Path, [System.EnvironmentVariableTarget]::Machine)

# Function to check if butler.exe is accessible from PATH
Function Test-CommandExists {
    Param (
        [string]$Command
    )
    $exists = Get-Command $Command -ErrorAction SilentlyContinue
    return -not ($null -eq $exists )
}

# Check if butler.exe is accessible via PATH
if (Test-CommandExists 'butler.exe') {
    Write-Host "butler.exe is accessible via PATH."
} else {
    Write-Host "butler.exe is NOT accessible via PATH. Please check your PATH settings."
}

Write-Host "Installation and configuration of Butler is complete."
