<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'facade-impl-file']">
Generating <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="facade-impl"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="facade-impl" match="facade-impl">
// Interface includes:
#include "IPMUnknown.h"
#include "I<xsl:value-of select="$sname"/>Facade.h"

// General includes:

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

/**  A facade provides a level of APIs that sits on top of commands.  If your plug-in implements
	commands or calls a collection of InDesign commands for which a facade is not provided
	you should process those commands from within a facade.  You then can then call the same
	code in several contexts.  For example if you implement scripting and a UI
*/
class <xsl:value-of select="$sname"/>Facade : public CPMUnknown&lt;I<xsl:value-of select="$sname"/>Facade&gt;
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	<xsl:value-of select="$sname"/>Facade(IPMUnknown* boss) : CPMUnknown&lt;I<xsl:value-of select="/code/@short-name"/>Facade&gt;(boss) {};

	/** Destructor. Does nothing.
	*/
	~<xsl:value-of select="$sname"/>Facade() {}

	virtual bool16 CanDoX(const UIDList&amp; items) const;
	virtual ErrorCode DoX(const UIDList&amp; items) ;

	virtual bool16 CanDoY(const UIDList&amp; items) const ;
	virtual ErrorCode DoY(const UIDList&amp; items) ;

	virtual void GetZ( const UIDList&amp; items, K2Vector&lt;int32&gt; &amp; vector) ;
	virtual ErrorCode SetZ( const UIDList&amp; items, int32 z ) ;
};


CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)

/* 
*/
bool16 <xsl:value-of select="@impl-name"/>::CanDoX(const UIDList&amp; items) const
{
	return kTrue;
}

/* 
*/
ErrorCode <xsl:value-of select="@impl-name"/>::DoX(const UIDList&amp; items)
{
	return kFailure;
}

/* 
*/
bool16 <xsl:value-of select="@impl-name"/>::CanDoY(const UIDList&amp; items) const
{
	return kTrue;
}

/*
*/
ErrorCode <xsl:value-of select="@impl-name"/>::DoY(const UIDList&amp; items)
{
	return kFailure;
}

/* 
*/
void <xsl:value-of select="@impl-name"/>::GetZ( const UIDList&amp; items, K2Vector&lt;int32&gt; &amp; vector)
{
	vector.push_back(1);
}

/* 
*/
ErrorCode <xsl:value-of select="@impl-name"/>::SetZ( const UIDList&amp; items, int32 z )
{
	return kFailure;
}

</xsl:template>
</xsl:stylesheet>