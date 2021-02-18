<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    
    <!-- This value will be passed by the client application -->
    <xsl:param name="srcXmlFilePath" />
    
     <!-- Document variables  -->
    <xsl:variable name="dest" select="/" />
    <xsl:variable name="src" select="document($srcXmlFilePath)" />
        
     <!-- These are the names of the paragraph styles which not created by the user. -->
    <xsl:variable name="noParagraph" select="'ParagraphStyle/$ID/[No paragraph style]'" />
    <xsl:variable name="normalParagraph" select="'ParagraphStyle/$ID/NormalParagraphStyle'" />
    
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
            <xsl:call-template name="retainUniqueUserParagraphStyles"></xsl:call-template>
            <xsl:call-template name="copyUserParagraphStyles"></xsl:call-template>
        </RootParagraphStyleGroup>
    </xsl:template>
    
    <!-- These paragraph styles will be retained in the transformed document -->
    <xsl:template name="retainParagraphStyles">
        <xsl:apply-templates select="//ParagraphStyle[@Self=$normalParagraph]" /> 
        <xsl:apply-templates select="//ParagraphStyle[@Self=$noParagraph]" /> 
    </xsl:template>
    
     <!-- Retains user paragraph styles unique ot the destination document -->
    <xsl:template name="retainUniqueUserParagraphStyles">
        <xsl:for-each select="$dest//ParagraphStyle">       
             <!-- If the destination paragraph style is not found in the source document, add it.  -->
            <xsl:if test="count($src//ParagraphStyle[@Name=current()/@Name]) =0">
                <xsl:apply-templates select="current()" />
            </xsl:if>
        </xsl:for-each>
    </xsl:template>
    
    <!-- Copies the user created paragraph styles from the source document -->
    <xsl:template name="copyUserParagraphStyles">
        <xsl:for-each select="$src//ParagraphStyle[@Self!=$noParagraph and @Self!=$normalParagraph]">
            <xsl:copy>
                <xsl:apply-templates select="@*"/> 
                <xsl:copy-of select="*|text()"/>
            </xsl:copy>
        </xsl:for-each>        
    </xsl:template>
        
</xsl:stylesheet>