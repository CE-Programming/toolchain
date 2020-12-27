; -- CEdev installation script --

[Setup]
AppName=CE C Toolchain
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

[InstallDelete]
Type: filesandordirs; Name: "{app}"

[Code]
const SystemEnvironmentKey = 'SYSTEM\CurrentControlSet\Control\Session Manager\Environment';
const UserEnvironmentKey = 'Environment';
const CEDEVKey = 'CEDEV';

type
  TDependency = record
    Filename: String;
    Parameters: String;
    Title: String;
    URL: String;
    Checksum: String;
    ForceSuccess: Boolean;
    InstallClean: Boolean;
    RebootAfter: Boolean;
  end;
  InstallResult = (InstallSuccessful, InstallRebootRequired, InstallError);
var
  MemoInstallInfo: String;
  Dependencies: array of TDependency;
  DelayedReboot, ForceX86: Boolean;
  DownloadPage: TDownloadWizardPage;

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
    if not RegQueryStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths) then exit;

    P := Pos(';' + Uppercase(Path) + ';', ';' + Uppercase(Paths) + ';');
    if P = 0 then exit;

    Delete(Paths, P - 1, Length(Path) + 1);
    RegWriteStringValue(HKEY_LOCAL_MACHINE, SystemEnvironmentKey, 'Path', Paths);
end;

procedure EnvAddCEdev(CEdevNewPath: string);
var
    CEdevPath: string;
begin
  if RegQueryStringValue(HKEY_CURRENT_USER, UserEnvironmentKey, CEDEVKey, CEdevPath) then EnvRemovePath(CEdevPath + '\bin');

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

// https://github.com/DomGries/InnoDependencyInstaller
// code to download and install Microsoft Visual C++ Runtime as needed.
procedure AddDependency(const Filename, Parameters, Title, URL, Checksum: String; const ForceSuccess, InstallClean, RebootAfter: Boolean);
var
  Dependency: TDependency;
  I: Integer;
begin
  MemoInstallInfo := MemoInstallInfo + #13#10 + '%1' + Title;
  Dependency.Filename := Filename;
  Dependency.Parameters := Parameters;
  Dependency.Title := Title;
  if FileExists(ExpandConstant('{tmp}{\}') + Filename) then begin
    Dependency.URL := '';
  end else begin
    Dependency.URL := URL;
  end;
  Dependency.Checksum := Checksum;
  Dependency.ForceSuccess := ForceSuccess;
  Dependency.InstallClean := InstallClean;
  Dependency.RebootAfter := RebootAfter;
  I := GetArrayLength(Dependencies);
  SetArrayLength(Dependencies, I + 1);
  Dependencies[I] := Dependency;
end;
function IsPendingReboot: Boolean;
var
  Value: String;
begin
  Result := RegQueryMultiStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager', 'PendingFileRenameOperations', Value) or
    (RegQueryMultiStringValue(HKEY_LOCAL_MACHINE, 'SYSTEM\CurrentControlSet\Control\Session Manager', 'SetupExecute', Value) and (Value <> ''));
end;
function InstallProducts: InstallResult;
var
  ResultCode, I, ProductCount: Integer;
begin
  Result := InstallSuccessful;
  ProductCount := GetArrayLength(Dependencies);
  MemoInstallInfo := SetupMessage(msgReadyMemoTasks);
  if ProductCount > 0 then begin
    DownloadPage.Show;
    for I := 0 to ProductCount - 1 do begin
      if Dependencies[I].InstallClean and (DelayedReboot or IsPendingReboot) then begin
        Result := InstallRebootRequired;
        break;
      end;
      DownloadPage.SetText(Dependencies[I].Title, '');
      DownloadPage.SetProgress(I + 1, ProductCount);
      while True do begin
        ResultCode := 0;
        if ShellExec('', ExpandConstant('{tmp}{\}') + Dependencies[I].Filename, Dependencies[I].Parameters, '', SW_SHOWNORMAL, ewWaitUntilTerminated, ResultCode) then begin
          if Dependencies[I].RebootAfter then begin
            // delay reboot after install if we installed the last dependency anyways
            if I = ProductCount - 1 then begin
              DelayedReboot := True;
            end else begin
              Result := InstallRebootRequired;
              MemoInstallInfo := Dependencies[I].Title;
            end;
            break;
          end else if (ResultCode = 0) or Dependencies[I].ForceSuccess then begin
            break;
          end else if ResultCode = 3010 then begin
            // Windows Installer ResultCode 3010: ERROR_SUCCESS_REBOOT_REQUIRED
            DelayedReboot := True;
            break;
          end;
        end;
        case SuppressibleMsgBox(FmtMessage(SetupMessage(msgErrorFunctionFailed), [Dependencies[I].Title, IntToStr(ResultCode)]), mbError, MB_ABORTRETRYIGNORE, IDIGNORE) of
          IDABORT: begin
            Result := InstallError;
            MemoInstallInfo := MemoInstallInfo + #13#10 + '      ' + Dependencies[I].Title;
            break;
          end;
          IDIGNORE: begin
            MemoInstallInfo := MemoInstallInfo + #13#10 + '      ' + Dependencies[I].Title;
            break;
          end;
        end;
      end;
      if Result <> InstallSuccessful then begin
        break;
      end;
    end;
    DownloadPage.Hide;
  end;
end;
// Inno Setup event functions
procedure InitializeWizard;
begin
  DownloadPage := CreateDownloadPage(SetupMessage(msgWizardPreparing), SetupMessage(msgPreparingDesc), nil);
end;
function PrepareToInstall(var NeedsRestart: Boolean): String;
var
  I: Integer;
begin

  Result := '';

  if DirExists(ExpandConstant('{app}')) then
  begin
    if SuppressibleMsgBox('The installer will now delete the destination folder (' + ExpandConstant('{app}') + '). It is recommended to back up any files inside, as they will be replaced by the installer. Continue?', mbConfirmation, MB_YESNO, IDYES) = IDNO
    then
      Result := 'Installing aborted by user.';
  end;

  DelayedReboot := False;
  case InstallProducts of
    InstallError: begin
      Result := MemoInstallInfo;
    end;
    InstallRebootRequired: begin
      Result := MemoInstallInfo;
      NeedsRestart := True;
      // write into the registry that the installer needs to be executed again after restart
      RegWriteStringValue(HKEY_CURRENT_USER, 'SOFTWARE\Microsoft\Windows\CurrentVersion\RunOnce', 'InstallBootstrap', ExpandConstant('{srcexe}'));
    end;
  end;
end;
function NeedRestart: Boolean;
begin
  Result := DelayedReboot;
end;
function UpdateReadyMemo(const Space, NewLine, MemoUserInfoInfo, MemoDirInfo, MemoTypeInfo, MemoComponentsInfo, MemoGroupInfo, MemoTasksInfo: String): String;
begin
  Result := '';
  if MemoUserInfoInfo <> '' then begin
    Result := Result + MemoUserInfoInfo + Newline + NewLine;
  end;
  if MemoDirInfo <> '' then begin
    Result := Result + MemoDirInfo + Newline + NewLine;
  end;
  if MemoTypeInfo <> '' then begin
    Result := Result + MemoTypeInfo + Newline + NewLine;
  end;
  if MemoComponentsInfo <> '' then begin
    Result := Result + MemoComponentsInfo + Newline + NewLine;
  end;
  if MemoGroupInfo <> '' then begin
    Result := Result + MemoGroupInfo + Newline + NewLine;
  end;
  if MemoTasksInfo <> '' then begin
    Result := Result + MemoTasksInfo;
  end;
  if MemoInstallInfo <> '' then begin
    if MemoTasksInfo = '' then begin
      Result := Result + SetupMessage(msgReadyMemoTasks);
    end;
    Result := Result + FmtMessage(MemoInstallInfo, [Space]);
  end;
end;
function NextButtonClick(const CurPageID: Integer): Boolean;
var
  I, ProductCount: Integer;
  Retry: Boolean;
begin
  Result := True;
  if (CurPageID = wpReady) and (MemoInstallInfo <> '') then begin
    DownloadPage.Show;
    ProductCount := GetArrayLength(Dependencies);
    for I := 0 to ProductCount - 1 do begin
      if Dependencies[I].URL <> '' then begin
        DownloadPage.Clear;
        DownloadPage.Add(Dependencies[I].URL, Dependencies[I].Filename, Dependencies[I].Checksum);
        Retry := True;
        while Retry do begin
          Retry := False;
          try
            DownloadPage.Download;
          except
            if GetExceptionMessage = SetupMessage(msgErrorDownloadAborted) then begin
              Result := False;
              I := ProductCount;
            end else begin
              case SuppressibleMsgBox(AddPeriod(GetExceptionMessage), mbError, MB_ABORTRETRYIGNORE, IDIGNORE) of
                IDABORT: begin
                  Result := False;
                  I := ProductCount;
                end;
                IDRETRY: begin
                  Retry := True;
                end;
              end;
            end;
          end;
        end;
      end;
    end;
    DownloadPage.Hide;
  end;
end;
// architecture helper functions
function IsX64: Boolean;
begin
  Result := not ForceX86 and Is64BitInstallMode;
end;
function GetString(const x86, x64: String): String;
begin
  if IsX64 then begin
    Result := x64;
  end else begin
    Result := x86;
  end;
end;
function GetArchitectureSuffix: String;
begin
  Result := GetString('', '_x64');
end;
function GetArchitectureTitle: String;
begin
  Result := GetString(' (x86)', ' (x64)');
end;
function CompareVersion(const Version1, Version2: String): Integer;
var
  Position, Number1, Number2: Integer;
begin
  Result := 0;
  while (Version1 <> '') or (Version2 <> '') do begin
    Position := Pos('.', Version1);
    if Position > 0 then begin
      Number1 := StrToIntDef(Copy(Version1, 1, Position - 1), 0);
      Delete(Version1, 1, Position);
    end else if Version1 <> '' then begin
      Number1 := StrToIntDef(Version1, 0);
      Version1 := '';
    end else begin
      Number1 := 0;
    end;
    Position := Pos('.', Version2);
    if Position > 0 then begin
      Number2 := StrToIntDef(Copy(Version2, 1, Position - 1), 0);
      Delete(Version2, 1, Position);
    end else if Version2 <> '' then begin
      Number2 := StrToIntDef(Version2, 0);
      Version2 := '';
    end else begin
      Number2 := 0;
    end;
    if Number1 < Number2 then begin
      Result := -1;
      break;
    end else if Number1 > Number2 then begin
      Result := 1;
      break;
    end;
  end;
end;

function MsiEnumRelatedProducts(UpgradeCode: String; Reserved, Index: DWORD; ProductCode: String): Integer;
external 'MsiEnumRelatedProductsW@msi.dll stdcall';
function MsiGetProductInfo(ProductCode, PropertyName, Value: String; var ValueSize: DWORD): Integer;
external 'MsiGetProductInfoW@msi.dll stdcall';
function IsMsiProductInstalled(const UpgradeCode, MinVersion: String): Boolean;
var
  ProductCode, Version: String;
  ValueSize: DWORD;
begin
  SetLength(ProductCode, 39);
  Result := False;
  if MsiEnumRelatedProducts(UpgradeCode, 0, 0, ProductCode) = 0 then begin
    SetLength(Version, 39);
    ValueSize := Length(Version);
    if MsiGetProductInfo(ProductCode, 'VersionString', Version, ValueSize) = 0 then begin
      Result := CompareVersion(Version, MinVersion) >= 0;
    end;
  end;
end;

function InitializeSetup: Boolean;
var
  Version: String;
begin

  if not IsMsiProductInstalled(GetString('{65E5BD06-6392-3027-8C26-853107D3CF1A}', '{36F68A90-239C-34DF-B58C-64B30153CE35}'), '14.28.29325') then begin
      AddDependency('vcredist2019' + GetArchitectureSuffix + '.exe',
        '/install /quiet /norestart',
        'Visual C++ 2015-2019 Redistributable' + GetArchitectureTitle,
        GetString('https://aka.ms/vs/16/release/vc_redist.x86.exe', 'https://aka.ms/vs/16/release/vc_redist.x64.exe'),
        '', False, False, False);
  end;

  Result := True;
end;
