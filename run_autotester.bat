@echo off
echo Autotester Runner
echo ==================
set RESULT=0
for /d %%d in (%cd%\examples\*) do (for %%f in (%%d\*.json) do (
	echo Launching autotester on %%f
	autotester "%%f"
	set /a "RESULT=%RESULT% + %errorlevel%"
))
exit /b %RESULT%