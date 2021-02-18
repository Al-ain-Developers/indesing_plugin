<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    
    <xsl:param name="conditionEscaped" /> 
    
    <xsl:template 
        match="*|@*|comment()|processing-instruction()|text()">
        <xsl:copy>
            <xsl:apply-templates
                select="*|@*|comment()|processing-instruction()|text()"/>
        </xsl:copy>
    </xsl:template>
    
    <xsl:template match="HiddenText">
        <xsl:choose>
            <xsl:when test="./CharacterStyleRange/@AppliedConditions = $conditionEscaped">
                <xsl:apply-templates
                    select="*|@*|comment()|processing-instruction()|text()"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:copy>
                    <xsl:apply-templates
                        select="*|@*|comment()|processing-instruction()|text()"/>
                </xsl:copy>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
    <xsl:template match="CharacterStyleRange">
        <xsl:choose>
            <xsl:when test="@AppliedConditions != $conditionEscaped and name(..) != 'HiddenText'">
                <xsl:element name="HiddenText">
                    <xsl:copy>
                        <xsl:apply-templates
                            select="*|@*|comment()|processing-instruction()|text()"/>
                    </xsl:copy>
                </xsl:element>
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