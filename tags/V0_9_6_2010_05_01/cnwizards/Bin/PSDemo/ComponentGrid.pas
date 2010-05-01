{*******************************************************}
{                                                       }
{       Pascal Script Source File                       }
{       Run by RemObjects Pascal Script in CnWizards    }
{                                                       }
{       Generated by CnPack IDE Wizards                 }
{                                                       }
{*******************************************************}

program ComponentGrid;

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  CnWizUtils;

// Liu Xiao: This Script is similar to "Component Grid" function in GExperts.

// Please Add this Script to Script Library, and Run it from the Corresponding
// item of the Dropdown Menu under "Run" ToolButton in Script Window.

const
  EDIT_WIDTH = 95;

var
  DesignContainer, Comp: TComponent;
  Control: TControl;
  WinControl: TWinControl;
  Form: TForm;
  Box: TScrollBox;
  I, J, TmpInt, CompCount, ProcessTagCount, ProcessHCCount: Integer;
  Edit: TEdit;
  Lbl: TLabel;
  Btn: TButton;

function CreateButton(Parent: TWinControl; Name: string; Left, Top: Integer;
  Caption: string): TButton;
begin
  Result := TButton.Create(Parent);
  Result.Name := Name;
  Result.Parent := Parent;
  Result.Left := Left;
  Result.Top := Top;
  Result.Caption := Caption;
end;

function CreateEdit(Parent: TWinControl; Name: string; Left, Top: Integer;
  Text: string; Enabled: Boolean): TEdit;
begin
  Result := TEdit.Create(Parent);
  Result.Name := Name;
  Result.Parent := Parent;
  Result.Left := Left;
  Result.Top := Top;
  Result.Text := Text;
  Result.Enabled := Enabled;
end;

function CreateLabel(Parent: TWinControl; Name: string; Left, Top: Integer;
  Caption: string): TLabel;
begin
  Result := TLabel.Create(Parent);
  Result.Name := Name;
  Result.Parent := Parent;
  Result.Left := Left;
  Result.Top := Top;
  Result.Caption := Caption;
end;

procedure btnOkClick(Sender: TObject);
begin
  Form.ModalResult := mrOk;
end;

procedure btnCancelClick(Sender: TObject);
begin
  Form.ModalResult := mrCancel;
end;

begin
  DesignContainer := IdeGetDesignedForm(nil);
  if DesignContainer = nil then
  begin
    ErrorDlg('NO Designer Found.');
    Exit;
  end;
  if DesignContainer.ComponentCount = 0 then
  begin
    ErrorDlg('NO Component to Process.');
    Exit;
  end;

  Form := TForm.Create(nil);
  try
    Form.BorderStyle := bsDialog;
    Form.SetBounds(100, 100, 450, 550);
    Form.Position := poScreenCenter;
    Form.Caption := 'Component Grid';

    Box := TScrollBox.Create(Form);
    Box.Parent := Form;
    Box.SetBounds(8, 8, Form.Width - 24, Form.Height - 8 * 4 - 21 - 30);

    CompCount := DesignContainer.ComponentCount;
    for J := 1 to 4 do
    begin
      Lbl := CreateLabel(Box, Format('lbl_%d', [J]), 8 + (J - 1) * EDIT_WIDTH + 2, 8, '');
      case J of
        1: Lbl.Caption := 'Component';
        2: Lbl.Caption := 'Parent';
        3: Lbl.Caption := 'Tag';
        4: Lbl.Caption := 'HelpContext';
      end;
    end;

    for I := 1 to CompCount do
    begin
      for J := 1 to 4 do
      begin
        Edit := CreateEdit(Box, Format('edt_%d_%d', [I, J]),
          8 + (J - 1) * EDIT_WIDTH + 2, 28 + (I - 1) * 21, '', J > 2);
        Edit.Width := EDIT_WIDTH;
        if J <= 2 then
          Edit.Color := clBtnface;

        Edit.Tag := _Pointer(DesignContainer.Components[I - 1]);
        
        case J of
          1: Edit.Text := DesignContainer.Components[I - 1].Name;
          2:
            begin
              if DesignContainer.Components[I - 1] is TControl then
              begin
                Control := TControl(DesignContainer.Components[I - 1]);
                if Control.Parent <> nil then
                  Edit.Text := Control.Parent.Name
                else
                  Edit.Text := '<None>';
              end
              else
              begin
                Edit.Text := '<N.A.>';
              end;
            end;
          3: Edit.Text := IntToStr(DesignContainer.Components[I - 1].Tag);
          4:
            begin
              if DesignContainer.Components[I - 1] is TWinControl then
              begin
                WinControl := TWinControl(DesignContainer.Components[I - 1]);
                Edit.Text := IntToStr(WinControl.HelpContext);
              end
              else
              begin
                Edit.Text := '<N.A.>';
                Edit.Enabled := False;
                Edit.Color := clBtnFace;
              end;
            end;
        end;
      end;
    end;

    Btn := CreateButton(Form, 'btnOk', Form.Width - 75 * 2 - 16 * 2, Form.Height - 8 - 21 - 30, '&OK');
    Btn.OnClick := @btnOkClick;
    Btn.Default := True;

    Btn := CreateButton(Form, 'btnCancel', Form.Width - 75 - 16, Form.Height - 8 - 21 - 30, '&Cancel');
    Btn.OnClick := @btnCancelClick;
    Btn.Cancel := True;
      
    TButton(Form.FindComponent('btnOk')).Height := 21;
    TButton(Form.FindComponent('btnCancel')).Height := 21;

    if Form.ShowModal = mrOK then
    begin
      ProcessTagCount := 0;
      ProcessHCCount := 0;
      for I := 1 to CompCount do
      begin
        // Tag
        Edit := TEdit(Box.FindComponent(Format('edt_%d_%d', [I, 3])));
        if Edit.Tag <> 0 then
        begin
          Comp := TComponent(CnIntToObject(Edit.Tag));
          try
            TmpInt := StrToInt(Edit.Text);
            if TmpInt <> Comp.Tag then
            begin
              Comp.Tag := TmpInt;
              ProcessTagCount := ProcessTagCount + 1;
            end;
          except
            ;
          end;
        end;

        // HelpContext
        Edit := TEdit(Box.FindComponent(Format('edt_%d_%d', [I, 4])));
        if Edit.Tag <> 0 then
        begin
          Comp := TComponent(CnIntToObject(Edit.Tag));
          if Comp is TWinControl then
          begin
            WinControl := TWinControl(Comp);
            try
              TmpInt := StrToInt(Edit.Text);
              if TmpInt <> WinControl.HelpContext then
              begin
                WinControl.HelpContext := TmpInt;
                ProcessHCCount := ProcessHCCount + 1;
              end;
            except
              ;
            end;
          end;
        end;
      end;

      InfoDlg(Format('Change Tags: %d.%sChange HelpContexts: %d.', [ProcessTagCount,
        #13#10, ProcessHCCount]));
    end;
  finally
    Form.Free;
  end;
end.

