<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
xmlns:fo="http://www.w3.org/1999/XSL/Format"
xmlns:aid="http://ns.adobe.com/AdobeInDesign/4.0/"
>


<xsl:output 
        omit-xml-declaration="no" method="xml" 
      doctype-system= "sdocbook.dtd" 
        indent="no" encoding="UTF-8"/> 
        
<!-- 

XSLT Spec: http://www.w3.org/TR/1999/REC-xslt-19991116

Adding namespace xmlns:aid isn't quite as easy as you'd like. The AXE parser seemed a bit unhappy with
	the version that worked for MSXML parser, so this is why I've added the dummy aid:role to the article
	
	The recipe to do this partly came from
		http://www.biglist.com/lists/xsl-list/archives/200212/msg00980.html
		http://www.dpawson.co.uk/xsl/sect2/N8367.html
		
-->

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

<xsl:template match="article/title">
     <xsl:copy>
      <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_article</xsl:attribute>
                 <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>


<xsl:template match="article/section/section/title">
     <xsl:copy>
                <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_sub</xsl:attribute>
                  <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>

<xsl:template match="article/section/section/section/title">
     <xsl:copy>
                 <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_sub_sub</xsl:attribute>
                <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>

<xsl:template match="article/section/section/section/section/title">
     <xsl:copy>
                 <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_sub_sub_sub</xsl:attribute>
                 <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>


<xsl:template match="itemizedlist/listitem/para">
     <xsl:copy>
    	            <xsl:variable name="p">aid</xsl:variable>
    		<xsl:attribute name="{concat($p,':pstyle')}"
				namespace="http://ns.adobe.com/AdobeInDesign/4.0/">para_itemizedlist</xsl:attribute>
              <xsl:apply-templates select="@* | node()"/>
     </xsl:copy>
</xsl:template>

<!--  Template -->
		<xsl:template match="itemizedlist/listitem/para">
		<xsl:copy>
			<xsl:variable name="p">aid</xsl:variable>
			<xsl:attribute name="{concat($p,':pstyle')}" namespace="http://ns.adobe.com/AdobeInDesign/4.0/">para_itemizedlist</xsl:attribute>
			<xsl:apply-templates select="@* | node()"/>
		</xsl:copy>
	</xsl:template>
		<!--  Template -->
		<xsl:template match="orderedlist/listitem/para">
		<xsl:copy>
			<xsl:variable name="p">aid</xsl:variable>
			<xsl:attribute name="{concat($p,':pstyle')}" namespace="http://ns.adobe.com/AdobeInDesign/4.0/">para_orderedlist</xsl:attribute>
			<xsl:apply-templates select="@* | node()"/>
		</xsl:copy>
		</xsl:template>

<!--  Template -->	
	<xsl:template match="caption/para">
		<xsl:copy>
			<xsl:variable name="p">aid</xsl:variable>
			<xsl:attribute name="{concat($p,':pstyle')}" namespace="http://ns.adobe.com/AdobeInDesign/4.0/">para_caption</xsl:attribute>
			<xsl:apply-templates select="@* | node()"/>
		</xsl:copy>
	</xsl:template>
		<!--  Template -->	
	<xsl:template match="abstract/para">
		<xsl:copy>
			<xsl:variable name="p">aid</xsl:variable>
			<xsl:attribute name="{concat($p,':pstyle')}" namespace="http://ns.adobe.com/AdobeInDesign/4.0/">para_abstract</xsl:attribute>
			<xsl:apply-templates select="@* | node()"/>
		</xsl:copy>
	</xsl:template>
		<!--  Template -->
		<xsl:template match="table/title | example/title | figure/title">
		<xsl:copy>
			<xsl:variable name="p">aid</xsl:variable>
			<xsl:attribute name="{concat($p,':pstyle')}" namespace="http://ns.adobe.com/AdobeInDesign/4.0/">title_examplefiguretable</xsl:attribute>
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
