# Define the URL and the target folder
$url = "https://broth.itch.ovh/butler/windows-amd64/LATEST/archive/default"
$zipFile = "butler.zip"
$targetFolder = "D:\a\DOGEngine\DOGEngine\butler"

# Download the file
Invoke-WebRequest -Uri $url -OutFile $zipFile

# Unzip the file
Expand-Archive -LiteralPath $zipFile -DestinationPath $targetFolder -Force

# Remove the ZIP file if no longer needed
Remove-Item -Path $zipFile

# Add the butler folder to the PATH environment variable for the current session
$env:Path += ";$PWD\$targetFolder"

[System.Environment]::SetEnvironmentVariable("Path", $env:Path, [System.EnvironmentVariableTarget]::Machine)
