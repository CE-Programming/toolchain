 !include "MUI2.nsh"
 !include "EnvVarUpdate.nsh"
 !include "winmessages.nsh"
 !define env_hkcu 'HKCU "Environment"'
 
 !define MUI_ICON "icon.ico"
;--------------------------------

  Name "CE C SDK"
  BrandingText "CE C Software Development Kit"
  
;--------------------------------

  ;Name and file
  OutFile "CEdev.exe"
  
  ; Get system drive

  ;Default installation folder
  InstallDir "$INSTDIR"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  
;--------------------------------
;Pages

  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE "DirectoryLeave"
  
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "French"
  
;--------------------------------
;Installer Section

Section ""

  SetOutPath "$INSTDIR"
  
  ;Add released file
  File /r "C:\CEdev\*.*"
  
  ;Add to PATH
  ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "$INSTDIR\bin"

  ;Add CEDEV variable
  WriteRegExpandStr ${env_hkcu} "CEDEV" "$INSTDIR"
  
  ; make sure windows knows about the change
  SendMessage ${HWND_BROADCAST} ${WM_WININICHANGE} 0 "STR:Environment" /TIMEOUT=5000

SectionEnd

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

Function .onInit

  ReadEnvStr $R0 SYSTEMDRIVE
  StrCpy $INSTDIR "$R0\CEdev"
  
FunctionEnd
