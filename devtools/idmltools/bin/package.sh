#!/bin/sh

if [ "$IDMLTOOLS_HOME" ]; then

	java -classpath "$IDMLTOOLS_HOME/jars/idmltools.jar" com.adobe.idml.Package "$@"

else

	echo Please define the environment variable IDMLTOOLS_HOME.

fi



