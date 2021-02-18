<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:output method="text"/>
    <xsl:template match="/package/mimetype">
        <xsl:document href="{$workingdir}{$filesep}mimetype" format="text">application/vnd.adobe.indesign-idml-package</xsl:document>
    </xsl:template>
</xsl:stylesheet>

