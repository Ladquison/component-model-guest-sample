@echo off
setlocal

call %~dp0setup_environment_guest.bat %1
if %errorlevel% neq 0 (
	exit /b
)
set HOST_OUTPUT_PATH=%HOST_PATH%\wasm
set TARGET_NAME=Component_%GUEST_LANG%

pushd %GUEST_PATH%

if "%~1"=="cpp" (
	rmdir /q /s build
	mkdir build
	cd build
	cmake -S .. --preset=wasi -DHOST_OUTPUT_PATH=%HOST_OUTPUT_PATH% -DTARGET_NAME=%TARGET_NAME%
	cmake --build .
	cmake --install .
) else if "%~1"=="csharp" (
	dotnet build .
) else if "%~1"=="python" (
	call build_wasm.bat
) else if "%~1"=="rust" (
	cargo component build
	copy target\wasm32-wasip1\debug\Component.wasm %HOST_OUTPUT_PATH%\%TARGET_NAME%.wasm
) else if "%~1"=="ts" (
	npm run build
)

popd

endlocal