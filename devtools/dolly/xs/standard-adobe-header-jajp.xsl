<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:import href="global-variables.xsl"/>
<xsl:output name="cppfile" method="text"/>
	<xsl:template match="standard-adobe-header-jajp" name="standard-adobe-header-jajp"><xsl:param name="suppress-normal-include"/>//========================================================================================
//  
//  $File: $
//  
//  Owner: <xsl:value-of select="/code/@author"/>
//  
//  $Author: $
//  
//  $DateTime: $
//  
//  $Revision: $
//  
//  $Change: $
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
<xsl:if test="not($suppress-normal-include)">
#include "VCPlugInHeaders.h"
</xsl:if>
 </xsl:template>
</xsl:stylesheet>