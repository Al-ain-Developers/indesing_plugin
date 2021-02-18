<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'selectionsuite-defaultscsb-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="selectionsuite-defaultscsb"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="selectionsuite-defaultscsb" match="selectionsuite-defaultscsb">
// Interface includes:

// General includes:
#include "<xsl:value-of select="/code/@short-name"/>SuiteCSB.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"


/** <xsl:value-of select="@impl-name"/> is the defaults specific implementation of <xsl:value-of select="/code/@short-name"/>SuiteCSB.

    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : public <xsl:value-of select="/code/@short-name"/>SuiteCSB
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : <xsl:value-of select="/code/@short-name"/>SuiteCSB(boss) {};

	/** Destructor. Does nothing.
	*/
	~<xsl:value-of select="@impl-name"/>() {}

	//
	// Add any defaults specific implementations here
	//
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

//
// Add any defaults specific implementations here
//
</xsl:template>
</xsl:stylesheet>