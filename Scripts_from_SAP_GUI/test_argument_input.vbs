'Set objArgs = Wscript.Arguments

'To parse and save in memory input named arguments
Set input_args = WScript.Arguments.Named
article_id = input_args.Item("first_arg")


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
session.findById("wnd[0]/tbar[0]/okcd").text = "ZSDS_PSTAT"
session.findById("wnd[0]/tbar[0]/btn[0]").press
session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/ctxtSO_KDAUF-LOW").text = article_id  'input to enter
session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/ctxtSO_KDAUF-LOW").caretPosition = 9
'session.findById("wnd[0]/tbar[0]/btn[15]").press
'session.findById("wnd[0]/tbar[0]/btn[15]").press
