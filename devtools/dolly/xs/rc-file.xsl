<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>

<xsl:output name="cppfile" method="text"/>
<xsl:template match="rc-file">Generating .RC file from template...
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{/code/@short-name}.rc" format="cppfile">
<xsl:call-template name="standard-adobe-header">
<xsl:with-param name="suppress-normal-include" select="1"/>
</xsl:call-template>
<xsl:call-template name="rc"/>
<xsl:call-template name="standard-footer"/>
</xsl:document>
</xsl:template>

<xsl:template match="rc" name="rc">
#include "WinRezFlags.h"
#include "BuildNumber.h"
#include "<xsl:value-of select="/code/@short-name"/>ID.h"

1 VERSIONINFO
 FILEVERSION kMajorVersionNumberForResource, kMinorVersionNumberForResource, 0, kBuildNumber
 PRODUCTVERSION kMajorVersionNumberForResource, kMinorVersionNumberForResource, 0, 0
 FILEFLAGSMASK 0x3fL
#ifdef _DEBUG
 FILEFLAGS 0x1L
#else
 FILEFLAGS 0x0L
#endif
 FILEOS 0x40004L
 FILETYPE 0x2L
 FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "CompanyName", "Adobe Systems Incorporated\0"
            VALUE "FileDescription", "Adobe InDesign SDK Plug-in\0"
            VALUE "FileVersion", "1.0", "\0"
            VALUE "InternalName", k<xsl:value-of select="/code/@short-name"/>PluginName, "\0"
            VALUE "LegalCopyright", kShortCopyRightStr, "\0"

            VALUE "OriginalFilename", k<xsl:value-of select="/code/@short-name"/>PluginName ".pln\0"
            VALUE "ProductName", "Adobe InDesign\0"
            VALUE "ProductVersion", kVersionNumberStr, "\0"
            VALUE "Copyright", kVersionCopyRightStr, "\0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x0409, 1200
    END
END

</xsl:template>
</xsl:stylesheet>

