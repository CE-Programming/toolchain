; -- CEdev installation script --

[Setup]
AppName=TI-84+CE C SDK
AppVersion={#APP_VERSION}
DefaultDirName={sd}\CEdev
DefaultGroupName=CEdev
Compression=lzma2
SolidCompression=yes
Uninstallable=no
OutputDir=.
OutputBaseFilename=CEdev
ChangesEnvironment=yes
SetupIconFile=icon.ico
AllowNoIcons=yes
DisableWelcomePage=yes

[Files]
Source: {#DIST_PATH}\*; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Code]
const SystemEnvironmentKey = 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment';
const UserEnvironmentKey = 'Environment';
const CEDEVKey = 'CEDEV';

procedure EnvAddPath(Path: string);
var
    Paths: string;
begin
    if not RegQueryStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths)
    then Paths := '';

    if Pos(';' + Uppercase(Path) + ';', ';' + Uppercase(Paths) + ';') > 0 then exit;

    Paths :=  Path + ';' + Paths
    RegWriteStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths);
end;

procedure EnvRemovePath(Path: string);
var
    Paths: string;
    P: Integer;
begin
    if not RegQueryStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths) then
        exit;

    P := Pos(';' + Uppercase(Path) + ';', ';' + Uppercase(Paths) + ';');
    if P = 0 then exit;

    Delete(Paths, P - 1, Length(Path) + 1);
    RegWriteStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths);
end;

procedure EnvAddCEdev(CEdevNewPath: string);
var
    CEdevPath: string;
begin
  if RegQueryStringValue(HKEY_CURRENT_USER, UserEnvironmentKey, CEDEVKey, CEdevPath) then
    EnvRemovePath(CEdevPath + '\bin');

  RegWriteStringValue(HKEY_CURRENT_USER, UserEnvironmentKey, CEDEVKey, CEdevNewPath);
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
    if CurStep = ssPostInstall 
     then begin
       EnvAddCEdev(GetShortName(ExpandConstant('{app}')));
       EnvAddPath(GetShortName(ExpandConstant('{app}') + '\bin'));
     end;
end;




