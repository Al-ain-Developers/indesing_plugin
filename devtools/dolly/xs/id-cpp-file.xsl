<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="id-cpp-file">
Generating ID.cpp file from template...
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}ID.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
<xsl:call-template name="id-cpp"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="id-cpp" name="id-cpp">

// General includes:
#include "ShuksanID.h"
#include "IDFactory_cpp.h"

#pragma export on
	#include "<xsl:value-of select="/code/@short-name"/>ID.h"
#pragma export off

</xsl:template>

</xsl:stylesheet>
