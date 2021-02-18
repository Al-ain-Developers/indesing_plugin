<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
	<xsl:output method="xml" indent="yes"/>
	<xsl:template match="/package/container">
		<xsl:document href="{$workingdir}{$filesep}META-INF{$filesep}container.xml" method="xml" indent="yes">
			<container version="1.0" xmlns="urn:oasis:names:tc:opendocument:xmlns:container">
				<rootfiles>
					<rootfile full-path="designmap.xml" media-type="text/xml">
					</rootfile>
				</rootfiles>
			</container>
		</xsl:document>
	</xsl:template>
</xsl:stylesheet>