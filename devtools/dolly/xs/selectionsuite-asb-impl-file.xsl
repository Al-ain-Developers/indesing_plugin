<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'selectionsuite-asb-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="selectionsuite-asb"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="selectionsuite-asb" match="selectionsuite-asb">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>

// Interface includes:
#include "I<xsl:value-of select="/code/@short-name"/>Suite.h"

// General includes:
#include "SelectionASBTemplates.tpp"
#include "K2Vector.tpp"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"


/** Provides the ASB implementation for the plug-ins selection suite.

    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : public CPMUnknown&lt;I<xsl:value-of select="/code/@short-name"/>Suite&gt;
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : CPMUnknown&lt;I<xsl:value-of select="/code/@short-name"/>Suite&gt;(boss) {};

	/** Destructor. Does nothing.
	*/
	~<xsl:value-of select="@impl-name"/>() {}

	/** @return kTrue if operation X is supported by any CSBs.*/
	virtual bool16 CanDoX() const;

	/** Performs operation X on each enabled CSB returning an ErrorCode.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoX() ;

	/** @return kTrue if operation Y is supported all CSB.*/
	virtual bool16 CanDoY() const ;

	/** Performs operation Y on each enabled CSB returning an ErrorCode. 
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoY() const ;

	/** Gets some data from each enabled CSB.  Instead of returning a value,
	implementations will stuff data into the OUT variable.
	@param vector OUT Data Z for the current selection is inserted into vector.*/
	virtual void GetZ( K2Vector&lt;int32&gt; &amp; vector) ;

	/** Sets some data on each enabled CSB.
	@param z IN Data to set.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode SetZ( int32 z ) ;
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

// Returns kTrue if any of the CSBs CanDoX.
bool16 <xsl:value-of select="@impl-name"/>::CanDoX() const
{
	return( AnyCSBSupports(make_functor(&amp;I<xsl:value-of select="/code/@short-name"/>Suite::CanDoX),(this), IID_I<xsl:value-of select="$uppersname"/>SUITE));
}

//  Create a sequence and call each CSB to process it's commands.
ErrorCode <xsl:value-of select="@impl-name"/>::DoX()
{
	return( Process(make_functor(&amp;I<xsl:value-of select="$sname"/>Suite::DoX), this, IID_I<xsl:value-of select="$uppersname"/>SUITE));
}

// Returns kTrue if all of the CSBs CanDoY
bool16 <xsl:value-of select="@impl-name"/>::CanDoY() const
{
	return( AllCSBSupports(make_functor(&amp;I<xsl:value-of select="$sname"/>Suite::CanDoY),(this), IID_I<xsl:value-of select="$uppersname"/>SUITE));
}

// Create a sequence and call each CSB to process it's commands
ErrorCode <xsl:value-of select="@impl-name"/>::DoY() const
{
	return( Process(make_functor(&amp;I<xsl:value-of select="$sname"/>Suite::DoY), this, IID_I<xsl:value-of select="$uppersname"/>SUITE));	
}

// Call each enabled CSB with an out parameter.
void <xsl:value-of select="@impl-name"/>::GetZ( K2Vector&lt;int32&gt; &amp; vector)
{
	CallEach(make_functor(&amp;I<xsl:value-of select="$sname"/>Suite::GetZ, vector), this);
}

// Create a sequence and call each CSB with an in parameter.
ErrorCode <xsl:value-of select="@impl-name"/>::SetZ( int32 z )
{
	return( Process(make_functor(&amp;I<xsl:value-of select="$sname"/>Suite::SetZ, z), this, IID_I<xsl:value-of select="$uppersname"/>SUITE));
}

</xsl:template>
</xsl:stylesheet>