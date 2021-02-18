<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">

    <xsl:param name="conditionEscaped"/>

    <xsl:template match="*|@*|comment()|processing-instruction()|text()">
        <xsl:copy>
            <xsl:apply-templates select="*|@*|comment()|processing-instruction()|text()"/>
        </xsl:copy>
    </xsl:template>

    <xsl:template match="CharacterStyleRange">
        <xsl:choose>
            <xsl:when test="@AppliedConditions = $conditionEscaped">
            </xsl:when>
            <xsl:when test="contains(@AppliedConditions, $conditionEscaped)">
                <xsl:copy>
                    <xsl:variable name="strBefore" select="normalize-space(substring-before(@AppliedConditions, $conditionEscaped))"/>
                    <xsl:variable name="strAfter" select="normalize-space(substring-after(@AppliedConditions, $conditionEscaped))"/>
                    <xsl:copy-of select="attribute::*[not(local-name()='AppliedConditions')]" />
                    <xsl:attribute name="AppliedConditions"><xsl:value-of select="concat($strBefore, ' ', $strAfter)"/></xsl:attribute>
                    <xsl:copy-of select="*|comment()|processing-instruction()|text()"/>
                    <xsl:copy-of select="not(attribute::*)"/>
                </xsl:copy>
            </xsl:when>
            <xsl:otherwise>
                <xsl:copy>
                    <xsl:apply-templates select="*|@*|comment()|processing-instruction()|text()"/>
                </xsl:copy>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
</xsl:stylesheet>
