@echo off
setlocal enableextensions enabledelayedexpansion
for /f "delims=" %%l in (%1) do (
  for /f "tokens=1,2,3,4" %%w in ("%%l") do (
    if NOT %%w+%%z == @+@ (
      echo %%l
    ) else (
      set i=
      for /f "delims=@ tokens=1,*" %%i in ("%%l") do if not x%%j == x set i=%%i
      pushd %%y
      for /r %%f in ("*.src") do echo !i!%%x "..\lib\%%y\%%~nxf"
      popd
    )
  )
)
