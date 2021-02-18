<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'selectionsuite-csb-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="selectionsuite-csb"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="selectionsuite-csb" match="selectionsuite-csb">
// Interface includes:

// General includes:
#include "<xsl:value-of select="/code/@short-name"/>SuiteCSB.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/* A shared implemenation for CanDoX() would go here
*/
bool16 <xsl:value-of select="@impl-name"/>::CanDoX() const
{
	return kTrue;
}

/* A shared implemenation for DoX() would go here
*/
ErrorCode <xsl:value-of select="@impl-name"/>::DoX()
{
	return kFailure;
}

/* A shared implemenation for CanDoY() would go here
*/
bool16 <xsl:value-of select="@impl-name"/>::CanDoY() const
{
	return kTrue;
}

/* A shared implemenation for DoY() would go here
*/
ErrorCode <xsl:value-of select="@impl-name"/>::DoY() const
{
	return kFailure;
}

/* A shared implemenation for GetZ() would go here
*/
void <xsl:value-of select="@impl-name"/>::GetZ( K2Vector&lt;int32&gt; &amp; vector)
{
	vector.push_back(1);
}

/* A shared implemenation for SetZ() would go here
*/
ErrorCode <xsl:value-of select="@impl-name"/>::SetZ( int32 z )
{
	return kFailure;
}

</xsl:template>
</xsl:stylesheet>