@echo off

if "%IDMLTOOLS_HOME%"=="" goto need_idml_home

set classpath="%IDMLTOOLS_HOME%\jars\idmltest.jar;%IDMLTOOLS_HOME%\jars\idmltools.jar;%IDMLTOOLS_HOME%\jing\bin\xercesImpl.jar;%IDMLTOOLS_HOME%\jing\bin\xml-apis.jar;%IDMLTOOLS_HOME%\jing\bin\saxon.jar;%IDMLTOOLS_HOME%\jing\bin\isorelax.jar"

java -classpath %classpath% com.adobe.idml.samples.ReplaceImages %*

goto exit

:need_idml_home
echo IDMLTOOLS_HOME is not set.  Please set IDMLTOOLS_HOME.


:exit
