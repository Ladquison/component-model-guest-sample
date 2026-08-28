@echo off
setlocal

call %~dp0setup_environment_guest.bat %1
if %errorlevel% neq 0 (
	exit /b
)

set WIT_BINDGEN_PATH=%TOOLS_PATH%\wit-bindgen
set OUTPUT_PATH=%GUEST_PATH%\wit
set WIT_FILE=%INTERFACE_PATH%\utility.wit

if not exist %OUTPUT_PATH% (
    mkdir %OUTPUT_PATH%
)

if "%~1"=="csharp" (
	echo C# uses wit-bindgen in build process
	copy %WIT_FILE% %OUTPUT_PATH%
	exit /b
) else if "%~1"=="python" (
	echo Python uses componentize-py
	rmdir /q /s %OUTPUT_PATH%
	mkdir %OUTPUT_PATH%
	copy %WIT_FILE% %OUTPUT_PATH%
	componentize-py --wit-path %INTERFACE_PATH% --world utility bindings %OUTPUT_PATH%
	exit /b
) else if "%~1"=="rust" (
	echo Rust uses wit-bindgen internally in build process
	copy %WIT_FILE% %OUTPUT_PATH%
	exit /b
) else if "%~1"=="ts" (
	echo TypeScript uses jco in build process
	copy %WIT_FILE% %OUTPUT_PATH%
	exit /b
)

%WIT_BINDGEN_PATH%\wit-bindgen.exe %1 %WIT_FILE% --out-dir %OUTPUT_PATH%

endlocal
