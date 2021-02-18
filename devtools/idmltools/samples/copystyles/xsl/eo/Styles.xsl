<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <!-- This value will be passed by the client application -->
    <xsl:param name="srcXmlFilePath" />
    
    <!-- Document variables  -->
    <xsl:variable name="dest" select="/" />
    <xsl:variable name="src" select="document($srcXmlFilePath)" />
        
    <!-- These are the names of the object styles which not created by the user. -->
    <xsl:variable name="noObject" select="'$ObjectStyle/$ID/[None]'" />
    <xsl:variable name="normalGraphicsFrame" select="'$ID/[Normal Graphics Frame]'" />
    <xsl:variable name="normalTextFrame" select="'$ID/[Normal Text Frame]'" />
    <xsl:variable name="normalGrid" select="'$ID/[Normal Grid]'" />
    
    <!-- Identity Transformation -->
    <xsl:template match="/ | @* | node()">
        <xsl:copy>
            <xsl:apply-templates select="@* | node()"/>
        </xsl:copy>
    </xsl:template>
    
    <!-- This exclusion template will be matched once. -->
    <xsl:template match="//RootObjectStyleGroup">
        <RootObjectStyleGroup>
            <xsl:call-template name="retainObjectStyles"></xsl:call-template>
            <xsl:for-each select="$dest//ObjectStyle[@Name!=$noObject and @Name!=$normalGraphicsFrame and @Name!=$normalTextFrame and @Name!=$normalGrid]">
                <xsl:call-template name="copyUserObjectStyles">
                    <xsl:with-param name="destObjectStyleName" select="current()/@Name" />
                </xsl:call-template>
            </xsl:for-each>
        </RootObjectStyleGroup>
    </xsl:template>
    
    <!-- These Object Styles will be retained in the transformed document -->
    <xsl:template name="retainObjectStyles">
        <xsl:apply-templates select="//ObjectStyle[@Name=$noObject]" /> 
        <xsl:apply-templates select="//ObjectStyle[@Name=$normalGraphicsFrame]" />         
        <xsl:apply-templates select="//ObjectStyle[@Name=$normalGrid]" /> 
        <xsl:apply-templates select="//ObjectStyle[@Name=$normalTextFrame]" /> 
    </xsl:template>
    
    <!-- Copies the user created object styles from the source document -->
    <xsl:template name="copyUserObjectStyles">
        <xsl:param name="destObjectStyleName"></xsl:param>
        <xsl:choose>
            <!-- If the local object style can be found in the remote document, copy the remote style  -->
            <xsl:when test="count($src//ObjectStyle[@Name=$destObjectStyleName]) > 0">
                <xsl:apply-templates select="$src//ObjectStyle[@Name=$destObjectStyleName]"/> 
            </xsl:when>
            <!-- If the local object style cannot be found in the remote document, retain the local style -->
            <xsl:otherwise>
                <xsl:apply-templates select="$dest//ObjectStyle[@Name=$destObjectStyleName]"/> 
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
</xsl:stylesheet>