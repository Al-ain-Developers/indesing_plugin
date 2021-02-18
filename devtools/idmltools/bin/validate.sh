#!/bin/sh

if [ "$IDMLTOOLS_HOME" ]; then

	java -classpath "$IDMLTOOLS_HOME/jars/idmltools.jar:$IDMLTOOLS_HOME/jing/bin/jing.jar:$IDMLTOOLS_HOME/jing/bin/xercesImpl.jar:$IDMLTOOLS_HOME/jing/bin/xml-apis.jar:$IDMLTOOLS_HOME/jing/bin/saxon.jar:$IDMLTOOLS_HOME/jing/bin/isorelax.jar" com.adobe.idml.Validator "$@"

else

	echo Please define the environment variable IDMLTOOLS_HOME.

fi