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
        <xsl:if test="@Self != $condition">
            <xsl:copy>
                <xsl:apply-templates
                    select="*|@*|comment()|processing-instruction()|text()"/>
            </xsl:copy>
        </xsl:if>
    </xsl:template>
</xsl:stylesheet>