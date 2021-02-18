<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>

<xsl:template match="selectionsuite-h-file">Generating selection suite interface file...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}I{/code/@short-name}Suite.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="selectionsuite-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="selectionsuite-h" name="selectionsuite-h">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
#pragma once
#ifndef __I<xsl:value-of select="$sname"/>Suite_h__
#define __I<xsl:value-of select="$sname"/>Suite_h__

#include "IPMUnknown.h"
#include "<xsl:value-of select="$sname"/>ID.h"

/** I<xsl:value-of select="$sname"/>Suite defines the interface for this plug-ins selection suite.

    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class I<xsl:value-of select="$sname"/>Suite : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_I<xsl:value-of select="$uppersname"/>SUITE };

	/** Selection suites will have methods that return whether or not the current selection supports an operation.  The
	actual ASB and CSB implementations may answer this question differently, so we demonstrate two different types. 
	The first will return kTrue when any CSBs support this operation.  The later will return kTrue when all CSBs support
	this operation.  This is actually an ASB detail, but it's explained here for demonstration purposes.
	@return kTrue if operation X is supported on the current selection.*/
	virtual bool16 CanDoX() const = 0;

	/** Performs operation X returning an ErrorCode.
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoX() = 0;

	/** Is operation Y supported by the current selection.  In this case, the ASB
	will dictate that all CSBs must support the selection.
	@return kTrue if operation Y is supported on the current selection.*/
	virtual bool16 CanDoY() const = 0;

	/** Performs operation Y returning an ErrorCode. 
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoY() const = 0;

	/** Gets some data from the current selection.  Instead of returning a value,
	implementations will stuff data into the OUT variable.
	@param vector OUT Data Z for the current selection is inserted into vector.*/
	virtual void GetZ( K2Vector&lt;int32&gt; &amp; vector) = 0;

	/** Sets some data on the current selection.
	@param z IN Data to set.
	@return kSuccess on success, or an appropriate ErrorCode on failure.  */
	virtual ErrorCode SetZ( int32 z ) = 0;

};
#endif // __I<xsl:value-of select="$sname"/>Suite_h__
</xsl:template>
</xsl:stylesheet>

