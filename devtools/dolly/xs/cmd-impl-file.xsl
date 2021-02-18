<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'cmd-impl-file']">
Generating cmd Implementation file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="cmdimpl"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>	
</xsl:template>


<xsl:template match="cmdimpl" name="cmdimpl">
<xsl:variable name="local-impl-name" select="@impl-name"/>
// Interface includes:

// General includes:
#include "Command.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/** <xsl:value-of select="@impl-name"/>

*/
class <xsl:value-of select="@impl-name"/> : public Command
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		<xsl:value-of select="@impl-name"/>(IPMUnknown* boss);
		virtual void Do();
		virtual void Undo();
		virtual void Redo();
		virtual void DoNotify();
		virtual PMString * CreateName();

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* <xsl:value-of select="@impl-name"/> Constructor
*/
<xsl:value-of select="@impl-name"/>::<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : Command(boss)
{
}

void <xsl:value-of select="@impl-name"/>::Do()
{

}

void <xsl:value-of select="@impl-name"/>::Undo()
{

}

void <xsl:value-of select="@impl-name"/>::Redo()
{

}

void <xsl:value-of select="@impl-name"/>::DoNotify()
{

}

PMString* <xsl:value-of select="@impl-name"/>::CreateName()
{
   PMString *str = new PMString("");
   return str;
}


</xsl:template>

</xsl:stylesheet>
