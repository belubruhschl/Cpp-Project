@echo off
setlocal

:: 1. Check if g++ is installed and in the PATH
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] g++ compiler not found! 
    echo Please install MinGW or add it to your System PATH.
    pause
    exit /b 1
)

:: 2. Start Build Process
echo ========================================
echo [INFO] Starting Windows Unity Build...
echo [INFO] Compiling main.cpp...
echo ========================================

:: 3. Compile and capture the result
:: -Wall -Wextra turns on helpful warnings
g++ main.cpp -o app.exe -Wall -Wextra

:: 4. Check if the compilation was successful
if %errorlevel% equ 0 (
    echo.
    echo [SUCCESS] Build completed! Executable: app.exe
    echo.
    
    :: Optional: Ask to run it immediately
    set /p run="Run the app now? (Y/N): "
    if /I "%run%"=="Y" (
        echo --- Running app.exe ---
        app.exe
    )
) else (
    echo.
    echo [FATAL ERROR] Build failed. Check the compiler logs above.
    echo.
    pause
)