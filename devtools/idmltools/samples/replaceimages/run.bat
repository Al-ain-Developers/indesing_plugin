@echo off

cmd /C replaceimages.bat -et ReplaceImages.idml export.xml
cmd /C replaceimages.bat -it export.xml ReplaceImages.idml ReplaceImages_FromXmlImport.idml
cmd /C replaceimages.bat
