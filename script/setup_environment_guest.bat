@echo off

call %~dp0setup_environment_common.bat

if "%1"=="" (
	echo guest languange needs to be set.
	exit /b 1
)
set GUEST_LANG=%1
set GUEST_PATH=%SRC_PATH%\guest\%1
