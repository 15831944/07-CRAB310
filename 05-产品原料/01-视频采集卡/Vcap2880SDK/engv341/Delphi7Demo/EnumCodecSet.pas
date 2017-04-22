unit EnumCodecSet;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,Menus,IniFiles,filectrl;

type
  TEnumCodecFrm = class(TForm)
    Button1: TButton;
    GroupBox1: TGroupBox;
    Label3: TLabel;
    Label2: TLabel;
    cbbVideoCodec: TComboBox;
    cbbAudioCodec: TComboBox;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    Label4: TLabel;
    TxtRecPath: TEdit;
    btnRecPath: TButton;
    TxtPicPath: TEdit;
    btPicPath: TButton;
    GroupBox3: TGroupBox;
    rbXvid: TRadioButton;
    rbDivx: TRadioButton;
    rbX264: TRadioButton;

    procedure FormShow(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure cbbVideoCodecChange(Sender: TObject);
    procedure cbbAudioCodecChange(Sender: TObject);
    procedure btnRecPathClick(Sender: TObject);
    procedure btPicPathClick(Sender: TObject);
    procedure rbX264Click(Sender: TObject);
    procedure rbDivxClick(Sender: TObject);
    procedure rbXvidClick(Sender: TObject);
  private

    { Private declarations }
  public
    { Public declarations }
  end;

var
  EnumCodecFrm: TEnumCodecFrm;
  VideoCurCodec:LongWord ;
  AudioCurCodec:LongWord ;
 
implementation
 uses GlobalVar,DxMediaApi,DxMediaFunction;

{$R *.dfm}


procedure TEnumCodecFrm.FormShow(Sender: TObject);
var
    VideoCodecNum:LongWord  ;
    AudioCodecNum:LongWord ;

    i:longword;

begin
       VideoCodecNum:=126;
       AudioCodecNum:=126;
       //ö������Ƶ�����㷨
       DXEnumVideoCodecs(VideoCodecInfo[0],VideoCodecNum);
       DXEnumAudioCodecs(AudioCodecInfo[0],AudioCodecNum);

       //��ö�ٵ�����Ƶ�����㷨��ӵ�combobox�ؼ��У�ָ��Ĭ�ϵ��㷨Ϊxvid
       for i:=0 to VideoCodecNum -1 do
       begin
             VideoCodecName[i]:=VideoCodecInfo[i].cfFaceName;
             cbbVideoCodec.Items.Add(VideoCodecName[i]);



       end;
        cbbVideoCodec.ItemIndex:=0;
       //  //��ö�ٵ�����Ƶ�����㷨��ӵ�combobox�ؼ��У�ָ��Ĭ�ϵ��㷨Ϊadpcm
        for i:=0 to AudioCodecNum -1 do
       begin
            AudioCodecName[i]:=AudioCodecInfo[i].cfFaceName ;
            cbbAudioCodec.Items.Add(AudioCodecName[i]);
            If (AudioCodecName[i] = 'Microsoft ADPCM') Then
              begin
                      AudioCurCodec:=i;
              end;
       end;
      cbbAudioCodec.ItemIndex :=AudioCurCodec;

end;

procedure TEnumCodecFrm.Button1Click(Sender: TObject);

begin






           if not DirectoryExists(TxtRecPath.Text) then   //�ж�Ŀ¼�Ƿ����

            begin
            CreateDir(TxtRecPath.Text);

            end;

           if not DirectoryExists(TxtPicPath.Text) then  //�ж�Ŀ¼�Ƿ����

            begin
            CreateDir(TxtPicPath.Text);

            end;

             RecSavePath:=TxtRecPath.Text+'\';
            PicSavePath:=TxtPicPath.Text+'\';

             SettingIni.WriteString('SystemSetting','VideoSavePath', TxtRecPath.Text);
             SettingIni.WriteString('SystemSetting','PictureSavePath', TxtPicPath.Text);


             if rbXvid.Checked =True then
             begin

                   DeviceInfo[CardNo].dwVideoCodecStr:='xvid Codec';
             end;

             if rbDivx.Checked =True then
             begin

                    DeviceInfo[CardNo].dwVideoCodecStr:='DivX? 5.1.1 Codec';

             end;
             if rbX264.Checked =True then
             begin

                  DeviceInfo[CardNo].dwVideoCodecStr:='x264 Codec';

             end;


               SettingIni.WriteString('SystemSetting','VideoCodec', DeviceInfo[CardNo].dwVideoCodecStr);


         EnumCodecFrm.Close ;
end;

procedure TEnumCodecFrm.cbbVideoCodecChange(Sender: TObject);
begin
       //��Ƶ��������ֵ
         VideoCurCodec:= cbbVideoCodec.ItemIndex ;

end;

procedure TEnumCodecFrm.cbbAudioCodecChange(Sender: TObject);
begin
       //��Ƶ��������ֵ
         AudioCurCodec:= cbbAudioCodec.ItemIndex ;
end;

procedure TEnumCodecFrm.btnRecPathClick(Sender: TObject);
begin
       //¼���ļ��洢Ŀ¼
        selectdirectory('��ѡ��洢Ŀ¼','',RecSavePath);
        TxtRecPath.Text := RecSavePath;
end;

procedure TEnumCodecFrm.btPicPathClick(Sender: TObject);
begin
        //����selectdirectory��USES "filectrl"(����ļ��к���)
       selectdirectory('��ѡ��洢Ŀ¼','',PicSavePath);
       TxtPicPath.Text := PicSavePath;
end;

procedure TEnumCodecFrm.rbX264Click(Sender: TObject);
begin
            if rbX264.Checked =True then
             begin

                  DeviceInfo[CardNo].dwVideoCodecStr:='x264 Codec';
                  SettingIni.WriteString('SystemSetting','VideoCodec', DeviceInfo[CardNo].dwVideoCodecStr);

             end;
end;

procedure TEnumCodecFrm.rbDivxClick(Sender: TObject);
begin
         if rbDivx.Checked =True then
             begin

                    DeviceInfo[CardNo].dwVideoCodecStr:='DivX? 5.1.1 Codec';
                    SettingIni.WriteString('SystemSetting','VideoCodec', DeviceInfo[CardNo].dwVideoCodecStr);

             end;
end;

procedure TEnumCodecFrm.rbXvidClick(Sender: TObject);
begin
         if rbXvid.Checked =True then
             begin

                   DeviceInfo[CardNo].dwVideoCodecStr:='Xvid MPEG-4 Codec';
                   SettingIni.WriteString('SystemSetting','VideoCodec', DeviceInfo[CardNo].dwVideoCodecStr);
             end;

end;

end.
