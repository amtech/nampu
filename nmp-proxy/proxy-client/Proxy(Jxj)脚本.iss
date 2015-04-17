; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "ProxyClient"
#define MyAppVersion "2.0.1.10"
#define MyFileVersion MyAppVersion
#define MyAppPublisher "�����м��Žݼ����ɷ����޹�˾"
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
OutputBaseFilename=ProxySetup(Jxj)
Compression=lzma
SolidCompression=yes
                

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
//Flags: unchecked; OnlyBelowVersion: 0,6.1
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}";
//Flags: unchecked

[Files]
Source: "output\ISTask.dll"; DestDir: "{sys}"; Flags: ignoreversion uninsnosharedfileprompt sharedfile; Attribs: hidden

Source: "output\ProxyClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "output\*.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "output\config.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "output\images\*"; DestDir: "{app}\images"; Flags: ignoreversion recursesubdirs createallsubdirs
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

//[Code]
//procedure InitializeWizard();
//begin
//  WizardForm.BorderIcons := [biHelp, biSystemMenu, biMinimize]; //��BorderStyle���ã��ᵼ�����Э���ҳ���RTF�ı�ʧЧ
//end;

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

//HasRun := FindWindowByWindowName('ProxyClient');
  strAppName := ExpandConstant('{#MyAppExeName}');
if RunTaskU(strAppName, false) then
begin
    MsgBox('ж�س����⵽���Ӧ�ó����������С�' #13#13 '�����˳����Ӧ�ó���Ȼ���ٽ���ж�أ�', mbError, MB_OK);
    Result := false;
end
else
    Result := true;
    UnloadDll(ExpandConstant('{sys}\ISTask.dll'));
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

[ISFormDesigner]
WizardForm=FF0A005457495A415244464F524D0030102F01000054504630F10B5457697A617264466F726D0A57697A617264466F726D0C436C69656E74486569676874034C010B436C69656E74576964746803F1010D4578706C69636974576964746803F9010E4578706C696369744865696768740367010D506978656C73506572496E636802600A54657874486569676874020C00F10C544E65774E6F7465626F6F6B0D4F757465724E6F7465626F6F6B00F110544E65774E6F7465626F6F6B5061676509496E6E65725061676500F10C544E65774E6F7465626F6F6B0D496E6E65724E6F7465626F6F6B00F110544E65774E6F7465626F6F6B506167651653656C65637450726F6772616D47726F75705061676500F10C544E6577436865636B426F780C4E6F49636F6E73436865636B0E506172656E7453686F7748696E740800000000000000


