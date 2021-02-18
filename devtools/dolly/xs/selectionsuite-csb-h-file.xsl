<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>




<xsl:template match="selectionsuite-csb-h-file">Generating selection suite CSB base class header file...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}{/code/@short-name}SuiteCSB.h" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
<xsl:call-template name="selectionsuite-csb-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="selectionsuite-csb-h" name="selectionsuite-csb-h">
<xsl:variable name="sname" select="/code/@short-name"/>
#pragma once
#ifndef __<xsl:value-of select="$sname"/>SuiteCSB_h__
#define __<xsl:value-of select="$sname"/>SuiteCSB_h__

#include "IPMUnknown.h"
#include "I<xsl:value-of select="$sname"/>Suite.h"
#include "<xsl:value-of select="$sname"/>ID.h"

/**  This class can be used to implement code common to all I<xsl:value-of select="$sname"/>Suite CSBs.
       For example, you may be calling the same code in each CSB, you just find the UIDs to operate on differently.
*/
class <xsl:value-of select="$sname"/>SuiteCSB : public CPMUnknown&lt;I<xsl:value-of select="$sname"/>Suite&gt;
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	<xsl:value-of select="$sname"/>SuiteCSB(IPMUnknown* boss) : CPMUnknown&lt;I<xsl:value-of select="/code/@short-name"/>Suite&gt;(boss) {};

	/** Destructor. Does nothing.
	*/
	~<xsl:value-of select="$sname"/>SuiteCSB() {}

	/** @return kTrue if operation X is supported by this CSB.*/
	virtual bool16 CanDoX() const;

	/** Performs operation X returning an ErrorCode.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoX() ;

	/** @return kTrue if operation Y is supported by this CSB.*/
	virtual bool16 CanDoY() const ;

	/** Performs operation Y returning an ErrorCode. 
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoY() const ;

	/** Gets some data from the current selection.  Instead of returning a value,
	implementations will stuff data into the OUT variable.
	@param vector OUT Data Z for the current selection is inserted into vector.*/
	virtual void GetZ( K2Vector&lt;int32&gt; &amp; vector) ;

	/** Sets some data on the current selection.
	@param z IN Data to set.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode SetZ( int32 z ) ;
	

};
#endif // <xsl:value-of select="$sname"/>SuiteCSB_h__
</xsl:template>
</xsl:stylesheet>

