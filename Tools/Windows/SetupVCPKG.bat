@echo off
SET VCPKG_ROOT=%CD%\vcpkg



:: Bootstrap vcpkg
echo Bootstrapping vcpkg...
call %VCPKG_ROOT%\bootstrap-vcpkg.bat
if errorlevel 1 (
    echo Failed to bootstrap vcpkg.
    exit /b %errorlevel%
)

:: Integrate vcpkg with Visual Studio
:: Integrate vcpkg with Visual Studio and check if already integrated
echo Checking vcpkg integration with Visual Studio...
FOR /F "tokens=*" %%i IN ('%VCPKG_ROOT%\vcpkg integrate install') DO SET INTEGRATION_RESULT=%%i
echo %INTEGRATION_RESULT%
IF "%INTEGRATION_RESULT%"=="Applied user-wide integration for this vcpkg root." (
    echo vcpkg is already integrated with Visual Studio.
) ELSE IF "%INTEGRATION_RESULT%"=="All installed packages are currently up to date." (
    echo No new packages to integrate.
) ELSE (
    echo Integration command executed.
)

set PATH=%VCPKG_ROOT%;%PATH%

echo Setup complete!
