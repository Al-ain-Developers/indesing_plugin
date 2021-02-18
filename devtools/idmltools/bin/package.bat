@echo off

if "%IDMLTOOLS_HOME%"=="" goto need_idml_home


java -classpath "%IDMLTOOLS_HOME%\jars\idmltools.jar" com.adobe.idml.Package %*

goto exit

:need_idml_home
echo IDMLTOOLS_HOME is not set.  Please set IDMLTOOLS_HOME.


:exit

