@echo off
setlocal

call %~dp0setup_environment_common.bat

pushd %HOST_PATH%

rmdir /q /s build
mkdir build
cd build
cmake -S .. --preset=host -DTOOLS_PATH=%TOOLS_PATH%
cmake --build . --config Debug

popd

endlocal