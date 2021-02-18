@echo off

cmd /C conditionaltext.bat -off "Print Only" ConditionalText.idml ConditionalText-PrintOnlyOff.idml
cmd /C conditionaltext.bat -on "Print Only" ConditionalText.idml ConditionalText-PrintOnlyOn.idml

