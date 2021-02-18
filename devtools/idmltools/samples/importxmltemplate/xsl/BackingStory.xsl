<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" version="1.0">
       
    <!-- These values will be passed by the client application -->
    <xsl:param name="tagsPath" select="'../before/XML/Tags.xml'" />
    <xsl:param name="importPath" select="'../Import.xml'" />
   
    <!-- Document variables  -->
    <xsl:variable name="tags" select="document($tagsPath)" />
    <xsl:variable name="import" select="document($importPath)" />  
 
    <!-- Identity Transformation -->
    <xsl:template match="/ | @* | node()">
        <xsl:copy>
            <xsl:apply-templates select="@* | node()"/>
        </xsl:copy>
    </xsl:template>
   
    <!-- Starts the process of replacing value attribute with the content provided in the imported xml file.  -->
    <xsl:template match="//XMLAttribute/@Value">        
        <xsl:call-template name="getIndex">
            <xsl:with-param name="markupTag" select="ancestor::XMLElement/@MarkupTag" />    
            <xsl:with-param name="xmlContent" select="ancestor::XMLElement/@XMLContent" />     
        </xsl:call-template>
    </xsl:template>
    
    <!-- The index is the position of the element relative to other siblings in the BackingStory.xml file.
            This value is needed to identify the correct value from the imported xml file.
            Variables created in a for loop cannot be read outside the loop.  For this reason another template
            is called.
    -->
     <xsl:template name="getIndex">
        <xsl:param name="xmlContent" />
        <xsl:param name="markupTag" />
        <xsl:for-each select="//XMLElement/XMLElement[@MarkupTag=$markupTag]">
            <xsl:if test="current()/@XMLContent=$xmlContent">
                <xsl:call-template name="updateContent">
                    <xsl:with-param name="index" select="position()" />
                    <xsl:with-param name="markupTag" select="$markupTag"/>
                </xsl:call-template>
            </xsl:if>
         </xsl:for-each>
     </xsl:template>
    
     <!--    Updates the value attributes with content from the import file.
              The tags.xml file is used lookup the correct information in the import xml file.
      -->
     <xsl:template name="updateContent">
        <xsl:param name="markupTag" />
        <xsl:param name="index" />
        <xsl:variable name="name" select="$tags//XMLTag[@Self=$markupTag]/@Name" />
        <xsl:variable name="link" select="$import//*[name()=$name][$index]/@href" />
        <xsl:attribute name="Value"><xsl:value-of select="$link"/></xsl:attribute> 
     </xsl:template>                   
    
   </xsl:stylesheet>
