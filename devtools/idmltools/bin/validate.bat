@echo off

if "%IDMLTOOLS_HOME%"=="" goto need_idml_home

java -classpath "%IDMLTOOLS_HOME%\jars\idmltools.jar;%IDMLTOOLS_HOME%\jing\bin\jing.jar;%IDMLTOOLS_HOME%\jing\bin\xercesImpl.jar;%IDMLTOOLS_HOME%\jing\bin\xml-apis.jar;%IDMLTOOLS_HOME%\jing\bin\saxon.jar;%IDMLTOOLS_HOME%\jing\bin\isorelax.jar" com.adobe.idml.Validator %*
goto exit

:need_idml_home
echo IDMLTOOLS_HOME is not set.  Please set IDMLTOOLS_HOME.


:exit
