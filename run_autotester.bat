@echo off
setlocal enabledelayedexpansion
echo Autotester Runner
echo ==================
set failures=0
for /d %%d in (%CEDEV%\examples\*\*) do (for %%f in (%%d\*.json) do (
	echo Launching autotester on %%f
	autotester "%%f"
	set /a failures+=!errorlevel!
))
exit /b %failures%
