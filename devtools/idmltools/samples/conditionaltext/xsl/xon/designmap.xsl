<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    
    <xsl:param name="condition" />  
    
    <xsl:template 
        match="*|@*|comment()|processing-instruction()|text()">
        <xsl:copy>
            <xsl:apply-templates
                select="*|@*|comment()|processing-instruction()|text()"/>
        </xsl:copy>
    </xsl:template>
    
    <xsl:template match="Condition">
        <xsl:choose>
            <xsl:when test="@Self != $condition and @Visible = 'true'">
                <xsl:copy>
                    <xsl:copy-of select="attribute::*[not(local-name()='Visible')]" />
                    <xsl:attribute name="Visible">false</xsl:attribute>
                    <xsl:copy-of select="not(attribute::*)"/>
                </xsl:copy>
            </xsl:when>
            <xsl:when test="@Self=$condition and @Visible = 'false'">
                <xsl:copy>
                    <xsl:copy-of select="attribute::*[not(local-name()='Visible')]" />
                    <xsl:attribute name="Visible">true</xsl:attribute>
                    <xsl:copy-of select="not(attribute::*)"/>
                </xsl:copy>
            </xsl:when>
            <xsl:otherwise>
                <xsl:copy>
                    <xsl:apply-templates
                        select="*|@*|comment()|processing-instruction()|text()"/>
                </xsl:copy>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
        
    
</xsl:stylesheet>