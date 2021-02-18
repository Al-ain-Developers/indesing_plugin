<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>


<xsl:template match="impl-item[@impl-file = 'simple-impl-file']">
Generating Simple Implementation file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="simpleimpl"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>	
</xsl:template>

<xsl:template match="simpleimpl" name="simpleimpl">
<xsl:variable name="local-impl-name" select="@impl-name"/>
// Interface includes:
#include "IPMUnknown.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/** <xsl:value-of select="@impl-name"/>

	<xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
	@ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> :  <![CDATA[public CPMUnknown<IPMUnknown>]]>
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		<xsl:value-of select="@impl-name"/>(IPMUnknown* boss);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* <xsl:value-of select="@impl-name"/> Constructor
*/
<xsl:value-of select="@impl-name"/>::<xsl:value-of select="@impl-name"/>(IPMUnknown* boss)  : <![CDATA[CPMUnknown<IPMUnknown>(boss)]]>
{

}


</xsl:template>

</xsl:stylesheet>
