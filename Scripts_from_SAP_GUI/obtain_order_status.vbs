'
' This chunk of code is a template for setting up the argue inputs at the moment of executing the program via the terminal
'
'To parse and save in memory input named arguments
Set input_args = WScript.Arguments.Named
OF_id = input_args.Item("OF_id") ' Expected entry: "/OF_id:_VALUE_"
sequence_id = input_args.Item("sequence_id") ' Expected entry: "/sequence_id:_VALUE_"

input_order = ""
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
session.findById("wnd[0]/tbar[0]/okcd").text = "ZSDS_PSTAT"
session.findById("wnd[0]/tbar[0]/btn[0]").press

If Not (StrComp(OF_id,"") = 0) Then
   input_order = OF_id
   session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/ctxtSO_AUFNR-LOW").text = input_order ' Input with OF number
ElseIf Not (StrComp(sequence_id,"") = 0) Then
   input_order = sequence_id
   session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/txtSO_SEQNR-LOW").text = input_order ' Input with sequence
Else
   Wscript.Echo "Something's wrong"
   WScript.Quit
End If

session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/ctxtSO_AUFNR-LOW").setFocus
session.findById("wnd[0]/usr/tabsTABSTRIP_MYTAB/tabpPUSH1/ssub%_SUBSCREEN_MYTAB:ZLE_PROD_STATUS:0100/ctxtSO_AUFNR-LOW").caretPosition = 9
session.findById("wnd[0]/tbar[1]/btn[8]").press
session.findById("wnd[0]/usr/cntlGRID1/shellcont/shell").currentCellColumn = "AUFNR"
session.findById("wnd[0]/usr/cntlGRID1/shellcont/shell").selectedRows = "0"
session.findById("wnd[0]/usr/cntlGRID1/shellcont/shell").doubleClickCurrentCell
session.findById("wnd[0]/usr/cntlGO_TREE1/shellcont/shell/shellcont[1]/shell[1]").selectedNode = "          2"
session.findById("wnd[0]/usr/cntlGO_TREE1/shellcont/shell/shellcont[1]/shell[1]").doubleClickNode "          2"

'
Wscript.Echo session.findById("wnd[0]/usr/txtCAUFVD-STTXT").text ' Extract string that contains the order status
'

session.findById("wnd[0]/tbar[0]/btn[12]").press
session.findById("wnd[0]/tbar[0]/btn[12]").press
session.findById("wnd[0]/tbar[0]/btn[12]").press
