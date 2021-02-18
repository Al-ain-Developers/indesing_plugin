<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" version="1.0">
       
    <xsl:output cdata-section-elements="Contents" />
    
     <!-- These values will be passed by the client application -->
    <xsl:param name="backingStoryPath" select="'../before/XML/BackingStory.xml'" />
    <xsl:param name="tagsPath" select="'../before/XML/Tags.xml'" />
    <xsl:param name="importPath" select="'../Import.xml'" />
   
    <!-- Document variables  -->
    <xsl:variable name="currentStory" select="/" />
    <xsl:variable name="backingStory" select="document($backingStoryPath)" />
    <xsl:variable name="tags" select="document($tagsPath)" />
    <xsl:variable name="import" select="document($importPath)" />  
     
    <!-- Identity Transformation -->
    <xsl:template match="/ | @* | node()">
        <xsl:copy>
            <xsl:apply-templates select="@* | node()"/>
        </xsl:copy>
    </xsl:template>    
    
      <!-- Copy the CDATA section -->
    <xsl:template match="Contents"> 
        <xsl:copy> 
            <xsl:apply-templates/>
        </xsl:copy>
    </xsl:template>    
        
    <!-- Replace the LinkResourceURI attribute with the content provided where parent XMLElement has an XMLContent attribute equal to the ContentID provided.  -->
    <xsl:template match="//Image/Link/@LinkResourceURI">
        <xsl:variable name="xmlContent" select="ancestor::Image/@Self"></xsl:variable>
        <xsl:variable name="markupTag" select="$backingStory//XMLElement[@XMLContent=$xmlContent]/@MarkupTag" />                    
        <xsl:call-template name="getIndex">
            <xsl:with-param name="xmlContent" select="$xmlContent" />
            <xsl:with-param name="markupTag" select="$markupTag"/>    
        </xsl:call-template>
    </xsl:template>
    
    <xsl:template name="getIndex">
        <xsl:param name="xmlContent"></xsl:param>
        <xsl:param name="markupTag"></xsl:param>
        <xsl:for-each select="$backingStory//XMLElement[@MarkupTag=$markupTag]">
            <xsl:if test="current()/@XMLContent=$xmlContent">
                <xsl:call-template name="getContent">
                    <xsl:with-param name="index" select="position()" />
                     <xsl:with-param name="xmlContent" select="$xmlContent" />
                     <xsl:with-param name="markupTag" select="$markupTag"/>
                </xsl:call-template>
            </xsl:if>
         </xsl:for-each>
    </xsl:template>
    
     <xsl:template name="getContent">
        <xsl:param name="index" />
        <xsl:param name="xmlContent" />
        <xsl:param name="markupTag" />
         <xsl:variable name="name" select="$tags//XMLTag[@Self=$markupTag]/@Name" />
         <xsl:variable name="link" select="$import//*[name()=$name][$index]/@href" />
        <xsl:attribute name="LinkResourceURI"><xsl:value-of select="$link"/></xsl:attribute>
     </xsl:template>
    
</xsl:stylesheet>

       