<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="nostrip-file">Generating NoStrip.cpp file from template...
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}NoStrip.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
<xsl:call-template name="nostrip"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="nostrip" name="nostrip">
#include "InterfaceFactory.h"

extern bool16 gFalse;

/** References all implementations to stop the compiler dead stripping them from the executable image.
*/
void DontDeadStrip();

void DontDeadStrip()
{
	if (gFalse)
	{
#include "<xsl:value-of select="/code/@short-name"/>FactoryList.h"
	}
}
</xsl:template>
</xsl:stylesheet>

