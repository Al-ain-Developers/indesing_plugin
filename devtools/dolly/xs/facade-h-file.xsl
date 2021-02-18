<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>

<xsl:template match="facade-h-file">Generating facade interface file...
 <xsl:document href="{/code/@id-header-dir-absolute}{$filesep}I{/code/@short-name}Facade.h" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="facade-h"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="facade-h" name="facade-h">
<xsl:variable name="sname" select="/code/@short-name"/>
<xsl:variable name="uppersname" select="translate($sname, 'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/>
#pragma once
#ifndef __I<xsl:value-of select="$sname"/>Facade_h__
#define __I<xsl:value-of select="$sname"/>Facade_h__

#include "IPMUnknown.h"
#include "<xsl:value-of select="$sname"/>ID.h"

/** I<xsl:value-of select="$sname"/>Facade defines the interface for this plug-ins facade.
	A Facade is a functional API layer that sits on top of commands and other complicated model operatoins.  Script providers and 
	selection suites often have to do the same thing.  Putting command and other model specific code into a facade provides
	code reuse.

    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class I<xsl:value-of select="$sname"/>Facade : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_I<xsl:value-of select="$uppersname"/>FACADE };

	/** Can we  perform operation X on the passed in items?
	@param items IN The target items  
	@return kTrue if operation X is supported by these items.*/
	virtual bool16 CanDoX(const UIDList&amp; items) const = 0;
	
	/** Performs operation X on the passed in items returning an ErrorCode.
	@param items IN The target items  
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoX(const UIDList&amp; items) = 0;

	/** Can we perform operation Y on the passed in items?
	@param items IN The target items  
	@return kTrue if operation Y is supported by these items.*/
	virtual bool16 CanDoY(const UIDList&amp; items) const = 0;

	/** Performs operation Y on the passed in items returning an ErrorCode.
	@param items IN The target items  
	@return kSuccess on success, or an appropriate ErrorCode on failure. */
	virtual ErrorCode DoY(const UIDList&amp; items) = 0;

	/** Gets some data from the specified items.  Instead of returning a value,
	implementations will stuff data into the OUT variable.
	@param items IN The target items  
	@param vector OUT Data Z for the current selection is inserted into vector.*/
	virtual void GetZ( const UIDList&amp; items, K2Vector&lt;int32&gt; &amp; vector) = 0;

	/** Sets some data on the specified items.
	@param items IN The target items  
	@param z IN Data to set.
	@return kSuccess on success, or an appropriate ErrorCode on failure.  */
	virtual ErrorCode SetZ( const UIDList&amp; items, int32 z ) = 0;

};
#endif // __I<xsl:value-of select="$sname"/>Facade_h__
</xsl:template>
</xsl:stylesheet>

