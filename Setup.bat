@echo off
echo Running SetupVCPKG.bat from the .\Tools\Windows directory...
call .\Tools\Windows\SetupVCPKG.bat
if %errorlevel% neq 0 (
    echo Error: SetupVCPKG.bat failed with error code %errorlevel%.
    exit /b %errorlevel%
)
echo SetupVCPKG.bat completed successfully.
