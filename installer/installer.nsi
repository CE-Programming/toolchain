;--------------------------------
; Incldudes

  !include "MUI2.nsh"
  !include "EnvVarUpdate.nsh"
  !include "winmessages.nsh"
  
;--------------------------------
;Names

  Name "CE C SDK"
  BrandingText "CE C Software Development Kit"
  
;--------------------------------
;Input and output

  OutFile "CEdev.exe"
  InstallDir "$INSTDIR"
  RequestExecutionLevel admin

;--------------------------------
;Interface and defines

  !define env_hkcu 'HKCU "Environment"'
  !define MUI_ABORTWARNING
  !define MUI_ICON "icon.ico"
  
;--------------------------------
;Pages

  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE "DirectoryLeave"
  !insertmacro MUI_PAGE_DIRECTORY
  
  !insertmacro MUI_PAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  
;--------------------------------
;Installer Section

Section ""

  SetOutPath "$INSTDIR"
  
  File /r ${DIST_PATH}\*.*
  
  ReadRegStr $R1 ${env_hkcu} "CEDEV"
  ${EnvVarUpdate} $0 "PATH" "R" "HKLM" "$R1\bin"

  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\bin"

  WriteRegExpandStr ${env_hkcu} "CEDEV" "$INSTDIR"
  
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

SectionEnd

;--------------------------------
;Check for spaces

Function DirectoryLeave

  Push $INSTDIR
   Call CheckForSpaces
  Pop $R0
  StrCmp $R0 0 NoSpaces

  MessageBox MB_OK|MB_ICONEXCLAMATION "Error: The Installaton directory \
  contains a space character.$\nPlease ensure no spaces are in the path before installing."
  Abort

  NoSpaces:
  
FunctionEnd

Function CheckForSpaces

 Exch $R0
 Push $R1
 Push $R2
 Push $R3
 StrCpy $R1 -1
 StrCpy $R3 $R0
 StrCpy $R0 0
 loop:
   StrCpy $R2 $R3 1 $R1
   IntOp $R1 $R1 - 1
   StrCmp $R2 "" done
   StrCmp $R2 " " 0 loop
   IntOp $R0 $R0 + 1
 Goto loop
 done:
 Pop $R3
 Pop $R2
 Pop $R1
 Exch $R0
 
FunctionEnd

;--------------------------------
; Find system drive

Function .onInit

  ReadEnvStr $R0 SYSTEMDRIVE
  StrCpy $INSTDIR "$R0\CEdev"
  
FunctionEnd

;--------------------------------