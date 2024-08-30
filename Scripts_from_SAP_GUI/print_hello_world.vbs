'To parse and save in memory input named arguments
Set input_args = WScript.Arguments.Named

first_arg = input_args.Item("first_arg")
second_arg = input_args.Item("second_arg")

text_file_path="..\SAP logs\example_print.txt"

WScript.Echo first_arg

Set objFSO=CreateObject("Scripting.FileSystemObject")

'~ Provide file path
outFile=text_file_path

'~ Setting up file to write
Set objFile = objFSO.CreateTextFile(outFile,True)

ObjFile.WriteLine first_arg
ObjFile.WriteLine second_arg
ObjFile.WriteLine "Ponete serio omeee"



objFile.Close