; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "ProxyClient"
#define MyAppVersion "2.0.1.10"
#define MyFileVersion MyAppVersion
#define MyAppPublisher ""
#define MyAppExeName "ProxyClient.exe"
#define MyAppGroupName "�ۺ���Ƶ����ƽ̨\ProxyClient"

[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{AC8A81F1-D887-41C5-A4FC-EF7B3D81D21B}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
VersionInfoVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppGroupName}
AllowNoIcons=yes
OutputDir=./
OutputBaseFilename=ProxySetup(Neutral)
Compression=lzma
SolidCompression=yes
                

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "output\ISTask.dll"; DestDir: "{sys}"; Flags: ignoreversion uninsnosharedfileprompt sharedfile; Attribs: hidden
Source: "output\ProxyClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "output\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "output\config.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "output\images\*"; DestDir: "{app}\images"; Flags: ignoreversion

; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
procedure RedesignWizardForm;
begin
  with WizardForm.SelectProgramGroupPage do
  begin
    ParentShowHint := False;
  end;
end;

procedure InitializeWizard();
begin
  RedesignWizardForm;
  RedesignWizardForm;
  WizardForm.BorderIcons := [biHelp, biSystemMenu]; //��BorderStyle���ã��ᵼ�����Э���ҳ���RTF�ı�ʧЧ
end;

var
HasRun:HWND;
KeynotExist:boolean;
ResultCode: Integer;
uicmd: String;
function InitializeSetup():Boolean;
begin
begin
  HasRun := 1;
  while HasRun<>0 do
  begin
  KeynotExist:= true;
  if RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\{AC8A81F1-D887-41C5-A4FC-EF7B3D81D21B}_is1', 'UninstallString', uicmd) then
  begin
    if MsgBox('��װ�����⵽�ó����Ѿ���װ��' #13#13 '����ɾ�����Ӧ�ó���Ȼ�󵥻�"��"������װ, ��"��"�˳���', mbConfirmation, MB_YESNO) = idNO then
    begin
      HasRun := 0;
      KeynotExist := false;
    end
    else
    begin
      KeynotExist:= false;
      Exec(RemoveQuotes(uicmd), '', '', SW_SHOW, ewWaitUntilTerminated, ResultCode);   // ��
    end;
  end
  else
  begin
    HasRun := 0;
  end;
  Result:= KeynotExist
  end;
end;

end;

//ж�س�ʼ��
function RunTaskU(FileName: string; bFullpath: Boolean): Boolean;
  external 'RunTask@{sys}\ISTask.dll stdcall delayload uninstallonly';
function KillTaskU(ExeFileName: string): Integer;
  external 'KillTask@{sys}\ISTask.dll stdcall delayload uninstallonly';
  
function InitializeUninstall(): Boolean;
var strAppName: String;
begin
 strAppName := ExpandConstant('{#MyAppExeName}');
if RunTaskU(strAppName, false) then
begin
    MsgBox('ж�س����⵽���Ӧ�ó����������С�' #13#13 '�����˳����Ӧ�ó���Ȼ���ٽ���ж�أ�', mbError, MB_OK);
    Result := false;
    UnloadDll(ExpandConstant('{sys}\ISTask.dll'));
end
else
    Result := true;
end;

procedure CurUninstallStepChanged (CurUninstallStep: TUninstallStep );
var ResultCode: Integer;
begin
  if CurUninstallStep = usUninstall then begin

  end;
  if CurUninstallStep = usPostUninstall then begin
      DelTree(ExpandConstant('{app}'),True, True, True);
  end;
end;