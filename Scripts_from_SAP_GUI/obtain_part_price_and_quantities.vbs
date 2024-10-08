'
' This chunk of code is a template for setting up the argue inputs at the moment of executing the program via the terminal
'
'To parse and save in memory input named arguments
Set input_args = WScript.Arguments.Named
article_id = input_args.Item("article_id") ' Expected entry: "/article_id:_VALUE_"

'
'
'

If Not IsObject(application) Then
   Set SapGuiAuto  = GetObject("SAPGUI")
   Set application = SapGuiAuto.GetScriptingEngine
End If
If Not IsObject(connection) Then
   Set connection = application.Children(0)
End If
If Not IsObject(session) Then
   Set session    = connection.Children(0)
End If
If IsObject(WScript) Then
   WScript.ConnectObject session,     "on"
   WScript.ConnectObject application, "on"
End If
session.findById("wnd[0]").maximize
session.findById("wnd[0]/tbar[0]/okcd").text = "ZC29"
session.findById("wnd[0]/tbar[0]/btn[0]").press
session.findById("wnd[0]/usr/ctxtS_MATNR-LOW").text = article_id
session.findById("wnd[0]").sendVKey 4
session.findById("wnd[1]/usr/sub/1[0,0]/sub/1/2[0,0]/sub/1/2/14[0,14]/lbl[57,14]").setFocus
session.findById("wnd[1]/usr/sub/1[0,0]/sub/1/2[0,0]/sub/1/2/14[0,14]/lbl[57,14]").caretPosition = 5
session.findById("wnd[1]").sendVKey 2
session.findById("wnd[0]/tbar[1]/btn[8]").press
session.findById("wnd[0]/usr/subSUB_AREA_D2:SAPLZMMC01_ZC29:0106/txtZMMC_ZC29_SCREEN-STPRS").setFocus
session.findById("wnd[0]/usr/subSUB_AREA_D2:SAPLZMMC01_ZC29:0106/txtZMMC_ZC29_SCREEN-STPRS").caretPosition = 0

' String to output:
Wscript.Echo session.findById("wnd[0]/usr/subSUB_AREA_MD:SAPLZMMC01_ZC29:0101/txtZMMC_ZC29_SCREEN-MAKTX").text
Wscript.Echo session.findById("wnd[0]/usr/subSUB_AREA_D2:SAPLZMMC01_ZC29:0106/txtZMMC_ZC29_SCREEN-STPRS").text
'
session.findById("wnd[0]/tbar[0]/btn[15]").press