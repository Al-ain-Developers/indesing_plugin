<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <!-- This value will be passed by the client application -->
    <xsl:param name="srcXmlFilePath" />
    
    <!-- Document variables  -->
    <xsl:variable name="dest" select="/" />
    <xsl:variable name="src" select="document($srcXmlFilePath)" />
    
    <!-- Identity Transformation -->
    <xsl:template match="/ | @* | node()">
        <xsl:copy>
            <xsl:apply-templates select="@* | node()"/>
        </xsl:copy>
    </xsl:template>
    
    <!-- This exclusion template will be matched once. -->
    <xsl:template match="//RootParagraphStyleGroup">
        <RootParagraphStyleGroup>
            <xsl:call-template name="retainParagraphStyles"></xsl:call-template>
            <xsl:for-each select="$src//ParagraphStyle">
                <xsl:call-template name="copyUserParagraphStyles">
                    <xsl:with-param name="srcParagraphStyleName" select="current()/@Name" />
                </xsl:call-template>
            </xsl:for-each>
        </RootParagraphStyleGroup>
    </xsl:template>
    
    <!-- These Paragraph Styles will be retained in the transformed document -->
    <xsl:template name="retainParagraphStyles">
        <xsl:for-each select="$dest//ParagraphStyle">
            <xsl:apply-templates select="current()" />
        </xsl:for-each>
    </xsl:template>
    
    <!-- Copies the user created paragraph styles from the source document -->
    <xsl:template name="copyUserParagraphStyles">
        <xsl:param name="srcParagraphStyleName"></xsl:param>
        <!-- If the source paragraph style is not found in the destination doc, add it.  -->
        <xsl:if test="count($dest//ParagraphStyle[@Name=$srcParagraphStyleName]) =0">
            <xsl:apply-templates select="$src//ParagraphStyle[@Name=$srcParagraphStyleName]"/> 
        </xsl:if>
    </xsl:template>
    
</xsl:stylesheet>
    

