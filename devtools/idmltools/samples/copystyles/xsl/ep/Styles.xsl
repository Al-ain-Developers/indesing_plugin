<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <!-- This value will be passed by the client application -->
    <xsl:param name="srcXmlFilePath" />
    
    <!-- Document variables  -->
    <xsl:variable name="dest" select="/" />
    <xsl:variable name="src" select="document($srcXmlFilePath)" />
        
    <!-- These are the names of the paragraph styles which not created by the user. -->
    <xsl:variable name="noParagraph" select="'$ID/[No paragraph style]'" />
    <xsl:variable name="normalParagraph" select="'$ID/NormalParagraphStyle'" />
    
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
            <xsl:for-each select="$dest//ParagraphStyle[@Name!=$noParagraph and @Name!=$normalParagraph]">
                <xsl:call-template name="copyUserParagraphStyles">
                    <xsl:with-param name="destParagraphStyleName" select="current()/@Name" />
                </xsl:call-template>
            </xsl:for-each>
        </RootParagraphStyleGroup>
    </xsl:template>
    
    <!-- These Paragraph Styles will be retained in the transformed document -->
    <xsl:template name="retainParagraphStyles">
        <xsl:apply-templates select="//ParagraphStyle[@Name=$normalParagraph]" /> 
        <xsl:apply-templates select="//ParagraphStyle[@Name=$noParagraph]" /> 
    </xsl:template>
    
    <!-- Copies the user created paragraph styles from the source document -->
    <xsl:template name="copyUserParagraphStyles">
        <xsl:param name="destParagraphStyleName"></xsl:param>
        <xsl:choose>
            <!-- If the local paragraph style can be found in the remote document, copy the remote style  -->
            <xsl:when test="count($src//ParagraphStyle[@Name=$destParagraphStyleName]) > 0">
                <xsl:apply-templates select="$src//ParagraphStyle[@Name=$destParagraphStyleName]"/> 
            </xsl:when>
            <!-- If the local paragraph style cannot be found in the remote document, retain the local style -->
            <xsl:otherwise>
                <xsl:apply-templates select="$dest//ParagraphStyle[@Name=$destParagraphStyleName]"/> 
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
</xsl:stylesheet>