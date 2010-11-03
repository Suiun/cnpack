{*******************************************************}
{                                                       }
{       Pascal Script Source File                       }
{       Run by RemObjects Pascal Script in CnWizards    }
{                                                       }
{       Generated by CnPack IDE Wizards                 }
{                                                       }
{*******************************************************}

program GetBreakPt;

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs;

var
  IDebuggerService: IOTADebuggerServices;
  ISourceBkpt: IOTASourceBreakpoint;
  I: Integer;
begin
  // BorlandIDEServices as IOTADebuggerServices NOT supported.
  IDebuggerService := IOTADebuggerServices(BorlandIDEServices);
  I := IDebuggerService.GetSourceBkptCount;
  Writeln('Breakpoints: ' + IntToStr(I));

  for I := 0 to IDebuggerService.GetSourceBkptCount - 1 do
  begin
    ISourceBkpt := IDebuggerService.GetSourceBkpt(I);
    if ISourceBkpt <> nil then
    begin
      Writeln(ISourceBkpt.GetFileName + ', ' + IntToStr(ISourceBkpt.GetLineNumber));
    end;
  end;
end.
