<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
<?aid style="50" type="document" readerVersion="6.0" featureSet="257" product="6.0(327)" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:idPkg="http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging" version="1.0">
        
    <xsl:output cdata-section-elements="Contents" />
        
    <!-- This value will be passed by the client application -->
    <xsl:param name="inputXmlFilePath" />  
    <xsl:param name="spreadID" />
   
    <!-- Document variables  -->
    <xsl:variable name="current" select="/" />
    <xsl:variable name="new" select="document($inputXmlFilePath)" />    
    
    <!-- Counts the category elements in the new document -->
    <xsl:variable name="newCategoryCount" select="count($new//Category)"></xsl:variable>
    
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
    
    <xsl:template match="/Document/@StoryList">
    </xsl:template>
    
    <!-- Determines when to add new idPkg:Story elements -->
    <xsl:template match="//idPkg:Story">
        <xsl:choose>
            <!-- If this is not the last idPkg:Story element, do not make any changes.  -->
            <xsl:when test="not (following-sibling::*[1][name()=local-name()])">
                <xsl:copy-of select="current()" />
            </xsl:when>
            <xsl:otherwise>
                <!-- If this is the last idPkg:Story element, add the new story elements.  -->
                <xsl:copy-of select="current()" />
                <xsl:call-template name="copyInputStories"></xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
    <!-- Add new idPkg:Story elements -->
    <xsl:template name="copyInputStories">
        <xsl:for-each select="$new//Category | $new//Item">
            <xsl:element name="idPkg:Story">
                <xsl:attribute name="src">Stories/Story_<xsl:value-of select="local-name()" /><xsl:value-of select="current()/@id"/>.xml</xsl:attribute>
            </xsl:element>        
        </xsl:for-each>
    </xsl:template>
    
    <!-- Determines when to add new idPkg:Spread elements -->
    <xsl:template match="//idPkg:Spread">
        <xsl:choose>
            <xsl:when test="not (following-sibling::*[1][name()=local-name()])">
                <xsl:copy-of select="current()" />
            </xsl:when>
            <xsl:otherwise>
                <xsl:copy-of select="current()" />
                <xsl:call-template name="addSpread"></xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
    <!-- Add new idPkg:Spread element -->
    <xsl:template name="addSpread">
        <xsl:element name="idPkg:Spread">
            <xsl:attribute name="src">Spreads/Spread_<xsl:value-of select="$spreadID"/>.xml</xsl:attribute>
        </xsl:element>        
    </xsl:template>
    
    <!-- Update the Length attribute in the Section tag with the correct value -->
    <xsl:template match="//Section/@Length">
        <xsl:attribute name="Length"><xsl:value-of select="number(current() + $newCategoryCount)" /></xsl:attribute>
    </xsl:template>
    
</xsl:stylesheet>