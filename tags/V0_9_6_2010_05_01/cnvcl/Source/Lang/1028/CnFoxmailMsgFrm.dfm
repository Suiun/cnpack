object MsgForm: TMsgForm
  Left = 340
  Top = 206
  BorderStyle = bsNone
  Caption = '消息顯示窗體'
  ClientHeight = 136
  ClientWidth = 153
  Color = clWhite
  Font.Charset = CHINESEBIG5_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = '細明體'
  Font.Style = []
  OldCreateOrder = False
  OnClick = FormClick
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 12
  object lblMsg: TLabel
    Left = 8
    Top = 46
    Width = 137
    Height = 85
    AutoSize = False
    Transparent = True
    WordWrap = True
    OnClick = FormClick
  end
  object imgWarning: TImage
    Left = 8
    Top = 8
    Width = 32
    Height = 32
    AutoSize = True
    Picture.Data = {
      055449636F6E0000010001002020000001001800A80C00001600000028000000
      20000000400000000100180000000000000C0000000000000000000000000000
      00000000000000000000000000E4F2E8A0CCD295C1C3C7DBD7E4F2E800000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000F1FDF3C7ECEF4CB3D2007597005D7C00556D3275886F9DA59A
      BCBCD7E5DA000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000FBFFF697E9F600ACE30094C50079A2006483065B76065B7606
      5B7616617D44788778A3AD9ABCBCD9E6D7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000097E9F600D1FB00BDF5009CD40285B70079A2006F9602
      668A006483065B76015370115D7832758852859478A3AD78A3ADA4BEB6D4E1D0
      F9FBDE0000000000000000000000000000000000000000000000000000000000
      00000000000000000000C5FCF625F0FD00E4FF00BCFF00A4D60094C5028BBA02
      85B70079A2006F96006A8D02668A0F63840F638416617D16617D16617D528594
      6F9DA592B1AEBCCFC1DEE8D1F9FBDE0000000000000000000000000000000000
      00000000000000000000FBFFF661F7FA00E4FF00C4FF00ACE300A4D6009CD400
      9CD40693CC048EC0028BBA0C85B91581AB2D91B14096B64096B632819F1E6783
      0C5674034C69054B6744788776989CA4BEB6D1DEC8EAF3D8F9FBDE0000000000
      0000000000000000000000000078FBF900E4FF00CCFC00ACE300A4D6009DCE00
      9DCE009DCE009CD4009CD40693CC2184A94D6B7A76989C76989C67B8CF3A9BBA
      176F8E085C7D015370034C6900446200446216506A44788776989CC2D2BE0000
      00000000000000000000000000ADFEF600ECFF00D1FB00B5EE05A2DB009DCE00
      9DCE009DCE02A8E60285B7013F530A01002B2B2473666973666988AAB75EC5EA
      2494BB0C75A0006693025B8300557C004F75034C6900446200405E0C476384A4
      9E000000000000000000000000D6FEF515EFFE00DBFF00BDF505A2DB009DCE00
      9DCE009CD4009CD4006A8D0500000500000A01003714073714075B514A53A7C2
      2BB4E80C85B9007CAE0072A5006D9D006693025B8300557C034C6900405E0040
      5E000000000000000000000000E8FFF338FBFC00E4FF00C4FF00ACE3009CD400
      9CD400A4D60094C502668A001C260500000500000500000500001715131F7DA2
      17B5ED0888BA0285B7007DB2007DB2007DB20075AA006D9D025B83034C690044
      6200000000000000000000000000000078FBF900ECFF00CCFC00B5EE00A4D600
      9CD4009CD40094C50080AD006483062E3A05000000121F00121F004F750285B7
      0693CC0285B70285B7007DB2007CAE007CAE007CAE0072A5006693025B8384AC
      AB00000000000000000000000000000085FDF804F6FF00D1FB00B5EE05A2DB00
      9CD4009CD400ACE305A2DB019BDC0095D40072A50285B70285B7048EC0028BBA
      0188BD0285B70285B7007DB2007DB2007CAE0075AA0072A5006D9D89B8BAEAF3
      D8000000000000000000000000000000C5FCF604F6FF00DBFF00BDF505A2DB00
      A4D600ACE305A2DB0E9BCC2494BB2D91B132BAE927C4F927C4F913A6E0028BBA
      0188BD0188BD0285B70285B7007DB2007CAE0072A5006D9D89B8BA0000000000
      0000000000000000000000000000000000000038FBFC00E4FF00C4FF00ACE305
      A2DB00B6F3006F96062E3A36393473666978A3AD5EC5EA5EC5EA2BB4E80B94C5
      028BBA0188BD0188BD0285B7007CAE0072A50072A595C1C30000000000000000
      0000000000000000000000000000000000000054FEFB04F6FF00D1FB00B5EE00
      ACE300ACE30032410500001A00005B514A7C5F5178A3AD78A3AD44BAE3169BCB
      048EC0028BBA0188BD0285B7007CAE2184A995C1C30000000000000000000000
      0000000000000000000000000000000000000085FDF800FAFF00DBFF00BCFF00
      ABE9028BBA000A0D05000005000030281D4F210E52859452859432BAE9149FD4
      048EC0028BBA0285B7007CAE1581ABA7CFCA0000000000000000000000000000
      00000000000000000000000000000000000000ADFEF600FAFF00E4FF00C4FF00
      A1E8006A8D0500000500000A01002219113714073A9BBA3A9BBA27C4F90E9BCC
      048EC00188BD0285B72D91B1ADD4CD0000000000000000000000000000000000
      00000000000000000000000000000000000000ADFEF600FAFF00E4FF00C4FF00
      A1E8006A8D0500000500000A01002219113714073A9BBA3A9BBA27C4F90E9BCC
      048EC00188BD0285B72D91B1ADD4CD0000000000000000000000000000000000
      00000000000000000000000000000000000000F1FDF324FFFD04F6FF00D1FB01
      9BDC013F530500000500000A010022191137403D32BAE932BAE91DC5FF0B94C5
      028BBA0285B71E8DB3BEDED40000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000054FEFB00FAFF00E4FF04
      8EC0001C260500000500000500001A00002B5B6B27C4F927C4F914BEF8048EC0
      0285B72494BBAED6D10000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000078FBF900FAFF00E4FF00
      89B3002E40050000050000050000050000176F8E17B5ED17B5ED0CAAE2028BBA
      53A7C2BEDED40000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000097FFF60EFFFE00DBFF02
      8BBA005D7C001C26050000050000015370028BBA05A2DB05A2DB0693CC2E9FC0
      EAF3D80000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000D6FEF524FFFD00ECFF00
      B9ED0092BF00799D0064830064830080AD009CD40094C50094C546ADC7DCEFDF
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000061F7FA04F6FF00
      D1FB00B7FB00AFF000ACE300A4D60693CC0693CC46ADC746ADC7C8E6DC000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000085FDF800FAFF00
      E4FF00C4FF00B7FB00ABE905A2DB009DCE67B8CFDCF1E3DCF1E3000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000097FFF600FAFF04
      F6FF00CCFC00B5EE00A4D6009DCE67C3D7DCF1E3000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000ADFEF60EFFFE00
      FAFF00DBFF00B9ED00A4D667C3D7000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000F1FDF338FBFC00
      FAFF00E4FF00B9ED78CDE0000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000ADFEF638
      FBFC25F0FD84E0EEFDFFEB000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000E8FFF397
      FFF661F7FAC4F1ED000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000E0FFFFFF801FFFFF8001FFFFC00007FFC000007FC0000007E0000003
      E0000001E0000001E0000001F0000001F0000001F0000007F800000FF800001F
      F800003FF800007FF800007FF80000FFFC0001FFFC0003FFFC0007FFFC000FFF
      FE001FFFFE003FFFFE00FFFFFE03FFFFFE07FFFFFF07FFFFFF0FFFFFFFFFFFFF
      FFFFFFFF}
    Transparent = True
    Visible = False
    OnClick = FormClick
  end
  object lblIcon: TLabel
    Left = 48
    Top = 18
    Width = 6
    Height = 12
    Transparent = True
    OnClick = FormClick
  end
  object imgError: TImage
    Left = 8
    Top = 8
    Width = 32
    Height = 32
    AutoSize = True
    Picture.Data = {
      055449636F6E0000010001002020000001001800A80C00001600000028000000
      20000000400000000100180000000000000C0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EAEBDCD5D5CCBBBBBBADADAD9D9D9C9D9D9C9D9D9CA3A39FB4B4ABCBCCBD
      E5E5CD0000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000EAEBDCCE
      CECEB3B3B3ADADADA4A4A49D9D9C9D9D9C9D9D9C9D9D9C9393949393948D8C8D
      90908FB4B4ABDCDDC80000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FDFEECE2E3DCC4C5C5B3
      B3B3B3B3B3ADADAD9393948686867575757575757575757B7B7C8D8C8D939394
      8D8C8D8D8C8D939394C5C6B7F8F9DC0000000000000000000000000000000000
      00000000000000000000000000000000000000FDFEECE2E3DCCECECEC4C5C5BB
      BBBB8D8C8D6C6B6C545554403F3F3435353435353435354444435C5C5C757575
      8686868D8C8D8D8C8D8D8C8DBDBDB0F1F2D50000000000000000000000000000
      00000000000000000000000000000000FDFEF4EBEBE6D3D3D3D3D3D3A4A4A475
      75755C5C5C4B4C4C2C2C2B282D44232F61212B5B212B5B2A2E3F3C3C3C5C5C5C
      7575757B7B7C8D8C8D939394939394BDBDB0F8F9DC0000000000000000000000
      00000000000000000000000000000000F6F6EFE3E3E3E3E3E3A4A4A46464644B
      4C4C474A473C3C3C2536842443CB1F39AD1A31941A3194192F8F232F614B4C4C
      6C6B6C7575757B7B7C8D8C8D939394939394CBCCBD0000000000000000000000
      00000000000000000000000000FDFEF4F3F3F3EEEEEEBBBBBB64646444444344
      44433C3C3C3435352C52F52D53FD294CE62341C52341C51F39AD1D36A44B4C4C
      6464646C6B6C7575758686869393949D9D9CA4A4A4E5E5CD0000000000000000
      00000000000000000000000000FCFCFCFCFCFCF3F3F37B7B7C4444433C3C3C3C
      3C3C3C3C3C393D463B6EFF3B6EFF3462FF2D53FD2D53FD2749DE2443CB4E5059
      6464646C6B6C6C6B6C7876788686869D9D9C9D9D9CC5C6B70000000000000000
      00000000000000000000FDFEF4FCFCFCFCFCFCB3B3B34B4C4C343535302F2F34
      35353C3C3C3C3C3C3B5DB54077FF3C71FF3462FF3462FF2D53FD344BB25C5C5C
      6464646464646C6B6C7575757B7B7C939394A4A4A4ADADADEEEED10000000000
      00000000000000000000FCFCFCFCFCFCFCFCFC7B7B7C3C3C3C2C2C2B2C2C2B34
      35353435353C3C3C3C3C3C3E508B3859C33859C33859C33E508B5455545C5C5C
      61615E6464646C6B6C6C6B6C7575758D8C8DADADADADADADDADBC60000000000
      00000000000000000000FCFCFCFCFCFCE3E3E35C5C5C2F312F2C2C2B2C2C2B2C
      2C2B3435353435353435352C2C2B242324292727292727343535444443545554
      5C5C5C6464646464646C6B6C757575868686A4A4A4ADADADCBCCBD0000000000
      00000000000000000000FCFCFCFCFCFCBBBBBB4B4C4C3435352C2C2B2C2C2B2C
      2C2B302F2F2C2C2B1F1F1F2024382333772333772333772528372C2C2B4B4C4C
      5C5C5C5C5C5C6464646464646C6B6C7B7B7CA4A4A4B3B3B3C2C2BB0000000000
      00000000000000000000FCFCFCFCFCFCADADAD4444432C2C2B302F2F302F2F34
      35352F312F2423242536842646D5213EBC1D36A41D36A4192F8F212B5B3C3C3C
      5455545C5C5C6360636464646C6B6C7575759D9D9CBBBBBBBBBBBB0000000000
      00000000000000000000FCFCFCFCFCFCA4A4A444444334353534353534353534
      3535343535242324294CE62749DE2341C51D36A41D36A4192F8F192D85343535
      4B4C4C5C5C5C5C5C5C625F5F6464647575759D9D9CBBBBBBBBBBBB0000000000
      00000000000000000000FCFCFCFCFCFCB3B3B34B4C4C3435353435353435353C
      3C3C34353527315B2D53FD2C52F52749DE213EBC213EBC1D36A41A3194292F4A
      4B4C4C5455545C5C5C5C5C5C646464757575A4A4A4C4C5C5C4C5C50000000000
      00000000000000000000FCFCFCFCFCFCC4C5C55455544444433C3C3C3C3C3C3C
      3C3C3435352A355D325DFF325DFF2D53FD2647D92647D9213EBC1D36A4272F4A
      444443514E4E5455545C5C5C646464757575B3B3B3CECECED5D5CC0000000000
      00000000000000000000FCFCFCFCFCFCC4C5C55455544444433C3C3C3C3C3C3C
      3C3C3435352A355D325DFF325DFF2D53FD2647D92647D9213EBC1D36A4272F4A
      444443514E4E5455545C5C5C646464757575B3B3B3CECECED5D5CC0000000000
      00000000000000000000FCFCFCFCFCFCE3E3E36C6B6C4B4C4C3C3C3C4444433C
      3C3C3C3C3C2A355D3462FF325DFF325DFF2A4EEC2A4EEC2341C51F39AD272F4A
      4444434B4C4C514E515455546060637B7B7CCECECED3D3D3E2E2D50000000000
      00000000000000000000FCFCFCFCFCFCFCFCFC8D8C8D5455544B4C4C44444344
      44434444432C395F3462FF3462FF325DFF2A4EEC2A4EEC2443CB203BB429304C
      444443474A474B4C4C545554646464939394E3E3E3DADADAEAEBDC0000000000
      00000000000000000000FDFEF4FCFCFCFCFCFCBBBBBB6C6B6C5455544B4C4C47
      4A47444443313D623B6EFF3462FF325DFF2C52F52C52F52646D5213EBC2A3150
      4444434444434B4C4C5455546C6B6CB3B3B3E3E3E3E3E3E3F8F9DC0000000000
      00000000000000000000000000FCFCFCFCFCFCFCFCFC9393946464645455544B
      4C4C4B4C4C3744683C71FF3C71FF3B6EFF325DFF325DFF2A4EEC2646D5303758
      4444434B4C4C5455545E605E939394F3F3F3EEEEEEF2F2E40000000000000000
      00000000000000000000000000FDFEF4FCFCFCFCFCFCD3D3D38686866464645C
      5C5C54555443464F4077FF437DFF3C71FF3462FF3462FF2D53FD294CE6393D46
      4444435455545C5C5C7B7B7CD3D3D3FCFCFCF3F3F3FDFEE10000000000000000
      00000000000000000000000000000000FCFCFCFCFCFCFCFCFCCECECE8686866C
      6B6C5C5C5C545554456EC74785FF437DFF3B6EFF3B6EFF325DFF344BB24B4C4C
      5455545C5C5C7B7B7CC4C5C5FCFCFCFCFCFCFDFEEC0000000000000000000000
      00000000000000000000000000000000FDFEF4FCFCFCFCFCFCFCFCFCD3D3D393
      93947575756464645C5C5C4D6493456EC7456EC7456EC73E508B5455545C5C5C
      6C6B6C8D8C8DCECECEFCFCFCFCFCFCFDFEF4FDFEE10000000000000000000000
      00000000000000000000000000000000000000FDFEF4FCFCFCFCFCFCFCFCFCFC
      FCFCBBBBBB9393947B7B7C6C6B6C6464646464646464646464647575758D8C8D
      B3B3B3FCFCFCFCFCFCFCFCFCFDFEF4FDFEE10000000000000000000000000000
      00000000000000000000000000000000000000000000FDFEF4FDFEF4FCFCFCFC
      FCFCFCFCFCFCFCFCE3E3E3C4C5C5BBBBBBBBBBBBBBBBBBC4C5C5E3E3E3FCFCFC
      FCFCFCFCFCFCFCFCFCFDFEF4FDFEE10000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FDFEF4FC
      FCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFC
      FCFCFCFDFEF4FDFEEC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FDFEF4FDFEF4FCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFDFEF4FDFEF4
      FDFEEC0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FFFFFFFFFFFFFFFFFFC007FFFF0001FFFC00007FF800003FF000001F
      F000001FE000000FE000000FC0000007C0000007C0000007C0000007C0000007
      C0000007C0000007C0000007C0000007C0000007C0000007C0000007E000000F
      E000000FF000001FF000001FF800003FFC00007FFF0001FFFFC007FFFFFFFFFF
      FFFFFFFF}
    Transparent = True
    Visible = False
    OnClick = FormClick
  end
  object imgInfo: TImage
    Left = 8
    Top = 8
    Width = 32
    Height = 32
    AutoSize = True
    Picture.Data = {
      055449636F6E0000010001002020000001001800A80C00001600000028000000
      20000000400000000100180000000000000C0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000EAEBDCD5D5CCBBBBBBADADAD9D9D9C9D9D9C9D9D9CA3A39FB4B4ABCBCCBD
      E5E5CD000000FEFEE1FDFEDBF5F5D0EDEECBE3E4C4E3E4C4EDEECBF5F5D0FAFB
      D5FDFEDB000000000000000000000000000000000000000000000000EAEBDCCE
      CECEFDFEECFDFEECF1F2E4EBECDBE6E7D3E2E3CEE2E3CEE2E3CEE2E3CEE2E3CE
      E2E3CEEBECD1EBECD1DBDCC7C3C2AAB1B29CA7A892A7A892B1B29CC3C2AAE2E3
      C1F5F5D0000000000000000000000000000000000000FDFEECE2E3DCFDFEECF7
      F8EAEBECDBDBDCC7C6C7B9BABBAEAFB0A1A5A699A1A293A1A293A1A293A5A699
      AFB09DB9BAA3B9BAA3ABAC989697848C89738C89738F907D9D9E88B1B29CCFCE
      ADEDEECB000000000000000000000000000000FDFEECFDFEF1FDFEECEBECDBD6
      D6C8BABBAEA5A69995968A8C8D8187887B828377828377828377828377828377
      87887B8B8C7D8C8973887A56856E3A87692B8B6B2B998046B8A671CFCEADE3E4
      C4EFF0CC000000000000000000000000FDFEF4FDFEF1F7F8EAE3E4D8C6C7B9A5
      A699908B78887A56887346856E3A87692B85642385642385642383662B816936
      816E4283744D8169368564238564238564238A67228E6B24926D24BAA162EDE7
      BBFAFBD5000000000000000000000000FDFEF1F7F8EADFE0D4BABBAE99907791
      7C4D947431926D24926D248E6B248E6B248E6B248A67228A67228A6722856423
      8564238564238564238564238564238564238D7847AAA079D8D8B8EAEAC6EDE7
      BB000000000000000000000000FDFEF4FDFEECE3E4D8B9B7AA9D8A5F9D7A339B
      74279A73269A7326957025926D24926D24926D24926D24926D248E6B248E6B24
      8E6B248A67228A67228A6722856423856E3A84816C969784B9BAA3E3E4C4FAFB
      D5000000000000000000000000FDFEF1EDEEE3C3C2AAA58C56AD822BA27B2AA2
      7B2AA27B2A9A73269A73269A73269A73269A7326957025957025957025926D24
      926D248E6B248E6B248E6B248A67228A672285714384816C969784C3C2AAEDEE
      CBFAFBD5000000000000FDFEF4F7F8EAD6D6C8B1965EB2852CB2852CAD822BAA
      7F2AA27B2AA27B2AA27B2AA27B2AA27B2AA27B2A9B74279B74279A73269A7326
      9A7326957025926D248E6B248E6B248E6B248A6722857143828377A7A892D8D8
      B8F7F8D4000000000000FCFCFCF1F2E4C2AD7DBA8B2EBA8B2EB6892EB2852CB2
      852CAD822BAD822BAA7F2AAA7F2AA27B2AA27B2AA27B2AA27B2AA27B2AA27B2A
      9B74279A73269A7326957025926D248E6B248E6B248E6B2483744D969784C3C2
      AAF5F5D0000000000000FCFCFCE3DCC2C39A46C69532C69532BA8B2EBA8B2EBA
      8B2EB6892EB2852CB2852CAD822BAD822BAD822BAD822BAD822BAD822BAD822B
      A27B2AA27B2A9B74279A7326957025926D24926D248E6B248B6E308A8468B1B2
      9CEAEAC6000000000000FCFCFCDCC48FD29D34CE9A33CA9732C69532C69532C6
      9532BA8B2EBA8B2EBA8B2EB6892EB6892EB6892EB6892EB6892EB6892EB2852C
      B2852CAD822BA27B2AA27B2A9B74279A7326957025926D24926D248B7B4FA7A8
      92E3E4C4000000000000FCFCFCDBBA6DDAA336D6A136D29D34FFFFFFCE9A33CA
      9732C69532FFFFFFC69532FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBA8B2E
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA27B2A9A73269A73269A732691773CA2A3
      8BE2E3C1000000000000FCFCFCEAB74FE5AC39E5AC39DBA537FFFFFFDAA336D6
      A136D29D34FFFFFFCA9732C69532C69532C69532C69532C69532FFFFFFC69532
      FFFFFFBA8B2EBA8B2EB2852CFFFFFFAA7F2AA27B2AA27B2A9B74279D7A33A7A8
      92E3E4C4000000000000FCFCFCF2B53CF2B53CF2B53CEEB23BFFFFFFE5AC39FF
      FFFFDBA537FFFFFFD6A136FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCE9A33
      FFFFFFC69532FFFFFFFFFFFFFFFFFFB2852CAD822BA27B2AA27B2AA27B2AB1B2
      9CEAEAC6000000000000FCFCFCF2B53CF2B53CF2B53CEEB23BFFFFFFE5AC39FF
      FFFFDBA537FFFFFFD6A136FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCE9A33
      FFFFFFC69532FFFFFFFFFFFFFFFFFFB2852CAD822BA27B2AA27B2AA27B2AB1B2
      9CEAEAC6000000000000FCFCFCFDC654FFC341FFC341FBBC3FFFFFFFFFFFFFF2
      B53CFFFFFFFFFFFFE5AC39FFFFFFDAA336D6A136D6A136D6A136D29D34D29D34
      FFFFFFCA9732C69532C69532BA8B2EB6892EB2852CAD822BAA7F2AA58035C3C2
      AAF5F5D0000000000000FCFCFCFDD777FFCD44FFCD44FFCD44FFFFFFFFC341FF
      C341FBBC3FFFFFFFEEB23BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDAA336
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBA8B2EBA8B2EB6892EB2852CAC8D49D8D8
      B8F7F8D4000000000000FCFCFCFEEBA6FFD346FFD346FFD346FFD346FFD346FF
      CD44FFCD44FFC341FBBC3FF2B53CF2B53CEEB23BE9AF3AE9AF3AE9AF3AE5AC39
      E5AC39DAA336D6A136D29D34CE9A33C69532C69532BA8B2EBA8B2EB8A671EDEE
      CBFAFBD5000000000000FDFEF4FAFBD5FFE467FFDE4AFFDE4AFFDE4AFFDE4AFF
      DE4AFFD346FFCD44FFC341FFC341FBBC3FF7B93EF2B53CF2B53CF2B53CEEB23B
      E9AF3AE5AC39DAA336DAA336D29D34CE9A33C69532C69532BD9642DDD6ABFAFB
      D5000000000000000000000000FCFCFCFEEBA6FFE44CFFE44CFFE44CFFE44CFF
      E44CFFDE4AFFDE4AFFD346FFCD44FFC341FFC341FBBC3FFBBC3FFBBC3FF7B93E
      F2B53CEEB23BE5AC39E5AC39DAA336D29D34CE9A33CA9732D4BF82F7F8D4FDFE
      DB000000000000000000000000FDFEF4FDFEECFFF493FFEB4EFFEB4EFFEB4EFF
      EB4EFFE44CFFE44CFFDE4AFFD346FFD346FFCD44FFC341FFC341FFC341FFC341
      FBBC3FF2B53CEEB23BE5AC39E5AC39DAA336D6A136DBBA6DF5F5D0FDFEDB0000
      00000000000000000000000000000000FCFCFCFEFEE1FFF493FFEB4EFFEC4FFF
      EC4FFFEB4EFFEB4EFFE44CFFDE4AFFDE4AFFD346FFCD44FFCD44FFCD44FFC341
      FFC341FBBC3FF2B53CEEB23BE5AC39E5AC39E2C377F5F5D0FDFEDB0000000000
      00000000000000000000000000000000FDFEF4FCFCFCFDFEECFEF8A7FFF567FF
      F351FFF351FFEB4EFFEB4EFFE44CFFE44CFFDE4AFFD346FFD346FFD346FFCD44
      FFC341FFC341FBBC3FF2B53CEAB74FF4D78BFAFBD50000000000000000000000
      00000000000000000000000000000000000000FDFEF4FCFCFCFCFCFCFEFCCCFF
      F998FFF567FFF351FFEC4FFFEB4EFFE44CFFE44CFFDE4AFFDE4AFFDE4AFFD346
      FFCD44FFC341FDC654F4D78BFAEEBBFDFEE10000000000000000000000000000
      00000000000000000000000000000000000000000000FDFEF4FDFEF4FCFCFCFC
      FCFCFDFEDBFEFAB2FFF493FFF276FFE467FFE551FFE551FFE551FFDF5BFFE467
      FFE388FEEBA6FEF7CCFDFEF4FDFEE10000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FDFEF4FC
      FCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFC
      FCFCFCFDFEF4FDFEEC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FDFEF4FDFEF4FCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFCFDFEF4FDFEF4
      FDFEEC0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FFFFFFFFFFFFFFFFFFC00400FF000000FC000000F8000000F0000000
      F0000001E0000001E0000000C0000000C0000000C0000000C0000000C0000000
      C0000000C0000000C0000000C0000000C0000000C0000000C0000001E0000001
      E0000003F0000007F000001FF800003FFC00007FFF0001FFFFC007FFFFFFFFFF
      FFFFFFFF}
    Transparent = True
    Visible = False
    OnClick = FormClick
  end
end
