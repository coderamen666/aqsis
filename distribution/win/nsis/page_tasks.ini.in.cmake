; Title: Aqsis 'Additional Tasks' Page for Win32/64 Installer (NSIS)
; Author: Aqsis Team (packages@aqsis.org)
; Info: Last tested with NSIS 2.21


[Settings]
NumFields=10
Title=@AQSIS_PROJECT_NAME@ @MAJOR@.@MINOR@.@BUILD@ Setup
CancelEnabled=1
CancelShow=1
BackEnabled=1

[Field 1]
Type=RadioButton
Text=For current user
Left=2
Right=283
Top=36
Bottom=46

[Field 2]
Type=RadioButton
Text=For all users
Left=2
Right=283
Top=48
Bottom=58
State=1

[Field 3]
Type=RadioButton
Text=None
Left=2
Right=283
Top=60
Bottom=70

[Field 4]
Type=Checkbox
Text=Create a desktop icon
Left=2
Right=283
Top=92
Bottom=102
State=1

[Field 5]
Type=Checkbox
Text=Create a Quick Launch icon
Left=2
Right=283
Top=104
Bottom=113

[Field 6]
Type=Checkbox
Text=Create AQSISHOME environment variable
Left=2
Right=283
Top=116
Bottom=126
State=1

[Field 7]
Type=Checkbox
Text=Associate Aqsis with the RIB, SL and SLX file extensions
Left=2
Right=283
Top=128
Bottom=138
State=1

[Field 8]
Type=Label
Text=Select the additional tasks you would like Setup to perform while installing @AQSIS_PROJECT_NAME@ @MAJOR@.@MINOR@.@BUILD@, then click Next.
Left=0
Right=283
Top=0
Bottom=20

[Field 9]
Type=Label
Text=Update PATH environment variable:
Left=0
Right=283
Top=24
Bottom=34

[Field 10]
Type=Label
Text=Additional tasks:
Left=0
Right=283
Top=80
Bottom=90
