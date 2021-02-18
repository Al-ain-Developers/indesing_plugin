<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">

    <xsl:param name="story-id"/>

    <xsl:template match="*|@*|comment()|processing-instruction()|text()">
        <xsl:copy>
            <xsl:apply-templates select="*|@*|comment()|processing-instruction()|text()"/>
        </xsl:copy>
    </xsl:template>

    <xsl:template match="Story">
        <xsl:copy>
            <xsl:copy-of select="attribute::*[not(local-name()='Self')]"/>
            <xsl:attribute name="Self">
                <xsl:value-of select="$story-id"/>
            </xsl:attribute>
            <xsl:copy-of select="*|comment()|processing-instruction()|text()"/>
            <xsl:copy-of select="not(attribute::*)"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
