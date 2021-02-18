#!/bin/sh

if [ "$IDMLTOOLS_HOME" ]; then

	export classpath="$IDMLTOOLS_HOME/jars/idmltest.jar:$IDMLTOOLS_HOME/jars/idmltools.jar:$IDMLTOOLS_HOME/jing/bin/xercesImpl.jar:$IDMLTOOLS_HOME/jing/bin/xml-apis.jar:$IDMLTOOLS_HOME/jing/bin/saxon.jar:$IDMLTOOLS_HOME/jing/bin/isorelax.jar"

	java -classpath $classpath com.adobe.idml.samples.PageBuilder "$@"

else

	echo Please define the environment variable IDMLTOOLS_HOME.

fi