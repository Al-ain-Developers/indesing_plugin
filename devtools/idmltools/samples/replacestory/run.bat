@echo off

cmd /C replacestory.bat -ea ReplaceStory2.idml temp
cmd /C replacestory.bat -r ReplaceStory.idml uf3 temp\Story_ud4.xml ReplaceStory3.idml

