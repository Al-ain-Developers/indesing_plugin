<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

    <xsl:output cdata-section-elements="Contents" />
    
    <!-- This value will be passed by the client application -->
    <xsl:param name="linkID" />
    <xsl:param name="linkURI" />

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
    
     <!-- Update the Length attribute in the Section tag with the correct value -->
    <xsl:template match="//Link">                       
               <xsl:element name="Link">
                   <xsl:apply-templates select="@* | node()"/>
                   <xsl:if test="current()/@Self=$linkID">
                       <xsl:attribute name="LinkResourceURI">
                            <xsl:value-of select="$linkURI" />
                        </xsl:attribute>      
                   </xsl:if>   
                   <!--  If Image is embedded --> 
                   <xsl:if test="current()/@StoredState='Embedded'">
                       <xsl:attribute name="StoredState">
                            <xsl:value-of select="'Normal'" />
                        </xsl:attribute>      
                     </xsl:if>  
               </xsl:element>            
    </xsl:template>
    
    <xsl:template match="//Image/Properties/Contents">
        <xsl:if test="not(ancestor::Image/Link/@Self=$linkID)" >
            <xsl:copy-of select="current()" />
        </xsl:if>                            
    </xsl:template>

    
</xsl:stylesheet>
