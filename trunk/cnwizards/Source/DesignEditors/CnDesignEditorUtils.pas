{******************************************************************************}
{                       CnPack For Delphi/C++Builder                           }
{                     中国人自己的开放源码第三方开发包                         }
{                   (C)Copyright 2001-2009 CnPack 开发组                       }
{                   ------------------------------------                       }
{                                                                              }
{            本开发包是开源的自由软件，您可以遵照 CnPack 的发布协议来修        }
{        改和重新发布这一程序。                                                }
{                                                                              }
{            发布这一开发包的目的是希望它有用，但没有任何担保。甚至没有        }
{        适合特定目的而隐含的担保。更详细的情况请参阅 CnPack 发布协议。        }
{                                                                              }
{            您应该已经和开发包一起收到一份 CnPack 发布协议的副本。如果        }
{        还没有，可访问我们的网站：                                            }
{                                                                              }
{            网站地址：http://www.cnpack.org                                   }
{            电子邮件：master@cnpack.org                                       }
{                                                                              }
{******************************************************************************}

unit CnDesignEditorUtils;
{* |<PRE>
================================================================================
* 软件名称：开发包属性、组件编辑器库
* 单元名称：属性组件编辑器公共过程单元
* 单元作者：CnPack开发组
* 备    注：
* 开发平台：PWin2000 + Delphi 5.01
* 兼容测试：PWin9X/2000/XP + Delphi 5/6
* 本 地 化：该单元中的字符串均符合本地化处理方式
* 单元标识：$Id: CnDesignEditorUtils.pas,v 1.7 2009/01/02 08:36:28 liuxiao Exp $
* 修改记录：2003.03.14 V1.2
*               增加了DrawBoolCheckBox函数
*           2003.03.01 V1.0
*               创建单元
================================================================================
|</PRE>}

interface

{$I CnWizards.inc}

uses
  Windows, SysUtils, Classes, Graphics, IniFiles, Registry, TypInfo,
  {$IFDEF COMPILER6_UP}
  DesignIntf, DesignEditors,
  {$ELSE}
  DsgnIntf,
  {$ENDIF}
  CnCommon, CnConsts, CnDesignEditorConsts, CnWizOptions, CnWizUtils;

function CreateEditorIniFile(CompilerSection: Boolean = False): TCustomIniFile; overload;
{* 创建编辑器INI对象 }

function CreateEditorIniFile(PropEditor: TPropertyEditorClass;
  CompilerSection: Boolean = False): TCustomIniFile; overload;
{* 创建属性编辑器INI对象 }

function CreateEditorIniFile(CompEditor: TComponentEditorClass;
  CompilerSection: Boolean = False): TCustomIniFile; overload;
{* 创建组件编辑器INI对象 }

procedure DrawBoolCheckBox(Canvas: TCanvas; const Rect: TRect;
  Value: Boolean; const Text: string = '');
{* 在指定Canvas的Rect内画Checkbox }

function CheckBoxHeight: Integer;
{* CheckBox的Height }

function CheckBoxWidth: Integer;
{* CheckBox的Width }

implementation

var
  Checked: TBitmap;
  Unchecked: TBitmap;
  FCheckBoxWidth, FCheckBoxHeight: Integer;

function CreateEditorIniFile(CompilerSection: Boolean = False): TCustomIniFile; overload;
begin
  Result := WizOptions.CreateRegIniFile(WizOptions.PropEditorRegPath, CompilerSection);
end;

function CreateEditorIniFile(PropEditor: TPropertyEditorClass;
  CompilerSection: Boolean = False): TCustomIniFile;
var
  Path: string;
begin
  Path := MakePath(WizOptions.PropEditorRegPath) +
    RemoveClassPrefix(PropEditor.ClassName);
  Result := WizOptions.CreateRegIniFile(Path, CompilerSection);
end;

function CreateEditorIniFile(CompEditor: TComponentEditorClass;
  CompilerSection: Boolean = False): TCustomIniFile; overload;
var
  Path: string;
begin
  Path := MakePath(WizOptions.PropEditorRegPath) +
    RemoveClassPrefix(CompEditor.ClassName);
  Result := WizOptions.CreateRegIniFile(Path, CompilerSection);
end;

{-----------------------------------------------------------------------------
  Procedure: Initialize
  Author:    Chinbo(Chinbo)
  Date:      14-三月-2003
  Arguments: None
  Result:    None
-----------------------------------------------------------------------------}

procedure Initialize;
var
  Bitmap: TBitmap;
  Src, Dst: TRect;
begin
  Checked := TBitmap.Create;
  Unchecked := TBitmap.Create;

  Bitmap := TBitmap.Create;
  try
    Bitmap.Handle := LoadImage(0, PChar(Obm_CheckBoxes), Image_Bitmap, 0, 0,
      Lr_DefaultSize or Lr_CreateDibSection or Lr_Shared or Lr_LoadMap3DColors);
    if Bitmap.Handle = 0 then
   {$IFDEF COMPILER6_UP}
      RaiseLastOSError;
   {$ELSE}
      RaiseLastWin32Error;
   {$ENDIF COMPILER6_UP}
    Src.Left := 0;
    Src.Top := 0;
    Src.Right := Bitmap.Width div 4;
    Src.Bottom := Bitmap.Height div 3;
    Unchecked.Height := Src.Bottom - Src.Top - 1;
    Unchecked.Width := Src.Right - Src.Left - 1;
    Dst := Src;
    Unchecked.Canvas.CopyRect(Dst, Bitmap.Canvas, Src);

    Checked.Height := Unchecked.Height;
    Checked.Width := Unchecked.Width;
    FCheckBoxHeight := Checked.Height;
    FCheckBoxWidth := Checked.Width;
    Src.Left := Src.Right;
    Src.Right := Src.Left + Bitmap.Width div 4;
    Checked.Canvas.CopyRect(Dst, Bitmap.Canvas, Src);
  finally
    Bitmap.Free;
  end;
end;

{-----------------------------------------------------------------------------
  Procedure: CheckBoxHeight
  Author:    Chinbo(Chinbo)
  Date:      14-三月-2003
  Arguments: None
  Result:    Integer
-----------------------------------------------------------------------------}

function CheckBoxHeight: Integer;
begin
  Result := FCheckBoxHeight;
end;

{-----------------------------------------------------------------------------
  Procedure: CheckBoxWidth
  Author:    Chinbo(Chinbo)
  Date:      14-三月-2003
  Arguments: None
  Result:    Integer
-----------------------------------------------------------------------------}

function CheckBoxWidth: Integer;
begin
  Result := FCheckBoxWidth;
end;

{-----------------------------------------------------------------------------
  Procedure: DrawBoolCheckBox
  Author:    Chinbo(Chinbo)
  Date:      14-三月-2003
  Arguments: Canvas: TCanvas; const Rect: TRect; const Value: string
  Result:    None
-----------------------------------------------------------------------------}

procedure DrawBoolCheckBox(Canvas: TCanvas; const Rect: TRect;
  Value: Boolean; const Text: string);
var
  S: string;
begin
  Canvas.FillRect(Rect);
  if Text = '' then
    S := BooleanIdents[Value]
  else
    S := Text;
  Canvas.TextRect(Rect, Rect.Left + Checked.Width + 2, Rect.Top + 1, S);
  if Value then
    Canvas.Draw(Rect.Left + 1, Rect.Top + 1, Checked)
  else
    Canvas.Draw(Rect.Left + 1, Rect.Top + 1, UnChecked);
end;

initialization
  //装载checkbox图像
  Initialize;

finalization
  FreeAndNil(Checked);
  FreeAndNil(Unchecked);

end.

