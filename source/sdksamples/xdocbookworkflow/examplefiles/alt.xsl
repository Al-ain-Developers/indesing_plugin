<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:fo="http://www.w3.org/1999/XSL/Format"
xmlns:aid="http://ns.adobe.com/AdobeInDesign/4.0/"
>


<xsl:output 
        omit-xml-declaration="no" method="xml" 
      doctype-system= "sdocbook.dtd" 
        indent="no" encoding="UTF-8"/> 
        
<xsl:template match="@* | node()">

     <xsl:copy>
          <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>

<!--
<xsl:template match="@*">
     <xsl:copy>
     </xsl:copy>
</xsl:template>
-->

<xsl:template match="article/title | article/section/section/title | article/section/section/section/title | article/section/section/section/section/title">
     <xsl:copy>
      <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">keyword</xsl:attribute>
                 <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>


<xsl:template match="para">
     <xsl:copy>
    	            <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_sub_sub</xsl:attribute>
              <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>

<xsl:template match="listitem/para">
     <xsl:copy>
    	            <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_sub</xsl:attribute>
              <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>


<xsl:template match="article">
     <xsl:copy>
      <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute
				name="{concat($p,':role')}"
					namespace="http://ns.adobe.com/AdobeInDesign/4.0/">force-namespace</xsl:attribute>
    	         <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>


</xsl:stylesheet>
