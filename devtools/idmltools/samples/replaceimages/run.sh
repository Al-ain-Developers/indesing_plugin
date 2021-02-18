#!/bin/sh

sh replaceimages.sh -et ReplaceImages.idml export.xml
sh replaceimages.sh -it export.xml ReplaceImages.idml ReplaceImages_FromXmlImport.idml
sh replaceimages.sh
