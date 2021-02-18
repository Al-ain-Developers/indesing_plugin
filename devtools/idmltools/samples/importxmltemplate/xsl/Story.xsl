<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" version="1.0">
      
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
    
    <!-- Starts the process of replacing the Content element with the content provided in the imported xml file.  -->
    <xsl:template match="//Story//XMLElement//Content">
         <xsl:variable name="xmlContent" select="ancestor::XMLElement/@XMLContent" />
         <xsl:call-template name="getIndex">
            <xsl:with-param name="xmlContent" select="$xmlContent" />
            <xsl:with-param name="markupTag" select="ancestor::XMLElement/@MarkupTag" />
            <xsl:with-param name="parentMarkupTag" select="$backingStory//XMLElement[@XMLContent=$xmlContent]/@MarkupTag" />
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
        <xsl:param name="parentMarkupTag" ></xsl:param>
        <xsl:for-each select="$backingStory//XMLElement[@MarkupTag=$parentMarkupTag]">
            <xsl:if test="current()/@XMLContent=$xmlContent">
                <xsl:call-template name="getContent">
                    <xsl:with-param name="index" select="position()" />
                     <xsl:with-param name="markupTag" select="$markupTag"/>
                     <xsl:with-param name="parentMarkupTag" select="$parentMarkupTag"/>
                </xsl:call-template>
            </xsl:if>
         </xsl:for-each>
    </xsl:template>
    
    <!--     Locates the content from the imported xml file to be placed in the story file.
               The location of the content depends on how the nesting works in the xml tag structure.
               The most paths are in order of most specific to most general.  The current example supports 
               content being in an element that is either a child or grandchild of the root.l    
    -->
    <xsl:template name="getContent">
        <xsl:param name="index" />        
        <xsl:param name="markupTag" />
        <xsl:param name="parentMarkupTag" />
        <xsl:variable name="parentName" select="$tags//XMLTag[@Self=$parentMarkupTag]/@Name" />
        <xsl:variable name="name" select="$tags//XMLTag[@Self=$markupTag]/@Name" />        
        <xsl:choose>
            <xsl:when test="count($import//*[name()=$parentName][$index]//*[name()=$name][1]/text()) = 1">
                <xsl:call-template  name="updateContent">
                      <xsl:with-param name="content" select="$import//*[name()=$parentName][$index]//*[name()=$name][1]/text()" />
                 </xsl:call-template>
            </xsl:when>
            <xsl:otherwise >
                <xsl:choose>
                     <xsl:when test="count($import//*[name()=$parentName][$index]) = 1">
                         <xsl:call-template  name="updateContent">
                              <xsl:with-param name="content" select="$import//*[name()=$parentName][$index]/text()" />
                         </xsl:call-template>
                     </xsl:when>
                    <xsl:otherwise>
                        
                    </xsl:otherwise>
                </xsl:choose>            
            </xsl:otherwise>
        </xsl:choose>
       
    </xsl:template>
    
    <xsl:template name="updateContent">
        <xsl:param name="content" />
         <Content><xsl:value-of select="$content"/></Content>
    </xsl:template>
    
</xsl:stylesheet>

       