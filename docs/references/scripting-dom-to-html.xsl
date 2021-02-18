<!--
//========================================================================================
//
//  $File$
//
//  Owner: Adobe Developer Technologies
//
//  $Author$
//
//  $DateTime$
//
//  $Revision$
//
//  $Change$
//
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or
//  distribution of it requires the prior written permission of Adobe.
//
//========================================================================================

/**	XSLT stylesheet that creates a Scripting DOM Reference for C++ programmers by transforming an xml dump of the
		Scripting DOM created by the Diagnostics plug-in into html.

    Usage:

    [Saxon]

   Hint... Use the saxon.jar distributed with DollyXs @ <sdk>\devtools\sdktools\dollyxs\jars\saxon.jar

   For HTML output:
        java -jar <sdk>\devtools\sdktools\dollyxs\jars\saxon.jar -o scriptingDOM.html scripting-dom-inx-idr50.xml scripting-dom-to-html.xsl

    [MSXSL]
   For HTML output:
       msxsl scripting-dom-inx-idr50.xml scripting-dom-idname-table.xsl -xw > scriptingDOM.html
*/
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" encoding="utf-8" standalone="yes"/>

<xsl:template match="dom">  <!--dom rule-->
<!-- html begin-->
	<html>

<!-- head begin-->
	<head>
	<title><xsl:value-of select="@product"/><xsl:text> </xsl:text><xsl:value-of select="@name"/> Scripting DOM Reference for C++ Programmers</title>
	<style type="text/css">
	  th {text-align: left; padding-right: 0.5em;}
	  td {text-align: left; padding-right: 0.5em;}
	</style>
	</head>
<!-- head end-->

<!-- body begin-->
	<body>

<!-- introduction begin-->
	Adobe InDesign CS6 SDK<br/>
	<h1><xsl:value-of select="@product"/><xsl:text> </xsl:text><xsl:value-of select="@name"/> Scripting DOM Reference for C++ Programmers</h1>
	<b>Product</b> = <xsl:value-of select="@product"/>,
	<b>Build</b> = <xsl:value-of select="@build"/>,
	<b>Language</b> = <xsl:value-of select="@language"/>,
	<b>ScriptManager</b> = <xsl:value-of select="@scriptManager"/>,
	<b>ScriptVersion</b> = <xsl:value-of select="@scriptVersion"/>
	<p>This reference documents the script objects, properties, methods and enums provided for programmers to extend when making a plug-in scriptable. For example, when you define a new script object using an Object ODFRez statement you must base it on an existing script object, such as kUniqueIDBasedObjectScriptElement, kPageItemObjectScriptElement, etc. When you add a script object using a Provider ODFRez statement you must reference your script object's parent. The parent must be an object that already exists in the Scripting DOM. The IDs you will need to use when writing the ODFRez statements for your script elements are documented below. See the [Making Your Plug-in Scriptable] tech note for documentation on exposing your plug-in's functionality in the Scripting DOM.</p>
	<p>This is the reference for the Scripting DOM identified above. The Scripting DOM varies by product (InDesign, InCopy, etc.), feature set locale (Roman, Japanese, etc.), script manager (INX, AppleScript, JavaScript, Visual Basic), and Scripting DOM version (4.0, 5.0, etc.). If this reference is not for the Scripting DOM you want, refer to Diagnostics guide for instructions on creating a reference.</p>
<!-- introduction end-->

<!-- contents begin-->
	<hr/>
	<h2>Contents</h2>
	<a href="#objects">Objects</a><br/>
	<a href="#methods">Methods</a><br/>
	<a href="#properties">Properties</a><br/>
	<a href="#enums">Enums</a><br/>
	<a href="#suites">Suites</a><br/>
	<a href="#events">Events</a><br/>
<!-- contents end-->

<!-- objects begin-->
	<hr/>
	<a name="objects"/>
	<h2>Objects</h2>
	<xsl:variable name="objects" select="//object"/>
	<xsl:apply-templates select="$objects" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # objects=<xsl:value-of select="count($objects)"/>)
	<xsl:apply-templates select="$objects" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- objects end-->

<!-- methods begin-->
	<hr/>
	<a name="methods"/>
	<h2>Methods</h2>
	<xsl:variable name="methods" select="//method"/>
	<xsl:apply-templates select="$methods" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # methods=<xsl:value-of select="count($methods)"/>)
	<xsl:apply-templates select="$methods" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- methods end-->

<!-- properties begin-->
	<hr/>
	<a name="properties"/>
	<h2>Properties</h2>
	<xsl:variable name="properties" select="//property"/>
	<xsl:apply-templates select="$properties" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # properties=<xsl:value-of select="count($properties)"/>)
	<xsl:apply-templates select="$properties" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- properties end-->

<!-- enums begin-->
	<hr/>
	<a name="enums"/>
	<h2>Enums</h2>
	<xsl:variable name="enums" select="//enum"/>
	<xsl:apply-templates select="$enums" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # enums=<xsl:value-of select="count($enums)"/>)
	<xsl:apply-templates select="$enums" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- enums end-->

<!-- suites begin-->
	<hr/>
	<a name="suites"/>
	<h2>Suites</h2>
	<xsl:variable name="suites" select="//suite"/>
	<xsl:apply-templates select="$suites" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # suites=<xsl:value-of select="count($suites)"/>)
	<xsl:apply-templates select="$suites" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- suites end-->

<!-- events begin-->
	<hr/>
	<a name="events"/>
	<h2>Events</h2>
	<xsl:variable name="events" select="//event"/>
	<xsl:apply-templates select="$events" mode="index"><xsl:sort select="@formattedName"/></xsl:apply-templates> (Total # events=<xsl:value-of select="count($events)"/>)
	<xsl:apply-templates select="$events" mode="content"><xsl:sort select="@formattedName"/></xsl:apply-templates>
<!-- events end-->

<!-- copyright footer begin -->
	<br/>
	<hr></hr>
	<TABLE id="Table1" cellSpacing="0" cellPadding="0" width="745" border="0">
			<TR>
				<TD width="20"><xsl:text disable-output-escaping="yes">&amp;nbsp;</xsl:text></TD>
				<TD vAlign="top" width="725">
					<TABLE id="Table2" cellSpacing="0" cellPadding="0" border="0">
						<TR>
							<TD class="bio" vAlign="top" align="left" colSpan="13">Adobe Solutions Network.</TD>
						</TR>
						<TR height="3">
							<TD colSpan="13" height="3"><SPACER width="20" type="block" height="3"/></TD>
						</TR>
						<TR>
							<TD class="bio" vAlign="top" align="left" colSpan="13">Copyright <xsl:text disable-output-escaping="yes">&amp;copy;</xsl:text> 2010 Adobe
								Systems Incorporated. All rights reserved.</TD>
						</TR>
						<TR height="3">
							<TD colSpan="13" height="3"><SPACER width="20" type="block" height="3"/></TD>
						</TR>
						<TR>
							<TD vAlign="top"><A class="footerlink" href="http://www.adobe.com/misc/copyright.html">Terms
									of Use</A></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD width="1"><SPACER width="1" type="block" height="1"/></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD vAlign="top"><A class="footerlink" href="http://www.adobe.com/misc/privacy.html">Online
									Privacy Policy</A></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD width="1"><SPACER width="1" type="block" height="1"/></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD vAlign="top"><A class="footerlink" href="http://access.adobe.com">Adobe and
									accessibility</A></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD width="1"><SPACER width="1" type="block" height="1"/></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD vAlign="top"><A class="footerlink" href="http://www.adobe.com/aboutadobe/antipiracy/main.html">Avoid
									software piracy</A></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD width="1"><SPACER width="1" type="block" height="1"/></TD>
							<TD width="5"><SPACER width="5" type="block" height="10"/></TD>
							<TD vAlign="top"><A class="footerlink" href="http://www.adobe.com/misc/agreement.html">Permissions
									and Trademarks</A></TD>
						</TR>
						<TR height="40">
							<TD colSpan="12" height="40"><SPACER width="20" type="block" height="40"/></TD>
							<TD height="40"></TD>
						</TR>
					</TABLE>
				</TD>
			</TR>
		</TABLE>
<!-- copyright footer end -->

</body>
<!-- body end-->

</html>
<!-- html end-->

</xsl:template>   <!--dom rule-->

<xsl:template match="object|method|property|enum|suite|event" mode="index">
	<xsl:variable name="id" select="@scriptElementID"/>
	<a href="#{$id}"><xsl:value-of select="@formattedName"/></a>,
</xsl:template>

<xsl:template match="object" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-object)</h3>
	<b>ScriptID</b> = '<xsl:value-of select="@scriptID"/>',
	<b>Name</b> = "<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>BaseObject</b> = <a href="#{@baseObject}"><xsl:value-of select="@baseObject"/></a>,
	<b>Suite</b> = <a href="#{@suite}"><xsl:value-of select="@suite"/></a>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
	<xsl:variable name="collectionScriptID" select="@collectionScriptID"/>
	<xsl:if test="string-length($collectionScriptID)!=0">
		<br/>
		<b>CollectionScriptID</b> = '<xsl:value-of select="@collectionScriptID"/>',
		<b>CollectionName</b>="<xsl:value-of select="@collectionName"/>"
	</xsl:if>
	<br/>
	<xsl:variable name="parents" select=".//parent"/>
    <!--<xsl:comment>count($parents)=<xsl:value-of select="count($parents)"/></xsl:comment>-->
	<xsl:if test="count($parents)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Parent Object</th><th>Provider</th><th>Surrogate</th>
				</tr>
				<xsl:apply-templates select="$parents" mode="content"><xsl:sort select="@scriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
	<xsl:variable name="children" select=".//child"/>
    <!--<xsl:comment>count($children)=<xsl:value-of select="count($children)"/></xsl:comment>-->
	<xsl:if test="count($children)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Child Object</th><th>Provider</th><th>Surrogate</th>
				</tr>
				<xsl:apply-templates select="$children" mode="content"><xsl:sort select="@scriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
	<xsl:variable name="methodproviders" select=".//methodprovider"/>
    <!--<xsl:comment>count($methodproviders)=<xsl:value-of select="count($methodproviders)"/></xsl:comment>-->
	<xsl:if test="count($methodproviders)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Method</th><th>Provider</th>
				</tr>
				<xsl:apply-templates select="$methodproviders" mode="content"><xsl:sort select="@scriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
  <xsl:variable name="eventproviders" select=".//eventprovider"/>
  <!--<xsl:comment>count($eventproviders)=<xsl:value-of select="count($eventproviders)"/></xsl:comment>-->
	<xsl:if test="count($eventproviders)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Event</th><th>Provider</th>
				</tr>
				<xsl:apply-templates select="$eventproviders" mode="content"><xsl:sort select="@scriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
	<xsl:variable name="collectionmethodproviders" select=".//collectionmethodprovider"/>
    <!--<xsl:comment>count($collectionmethodproviders)=<xsl:value-of select="count($collectionmethodproviders)"/></xsl:comment>-->
	<xsl:if test="count($collectionmethodproviders)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Collection Method</th><th>Provider</th><th>Parent Object</th>
				</tr>
				<xsl:apply-templates select="$collectionmethodproviders" mode="content"><xsl:sort select="@scriptElementID"/><xsl:sort select="@parentScriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
	<xsl:variable name="propertyproviders" select=".//propertyprovider"/>
    <!--<xsl:comment>count($propertyproviders)=<xsl:value-of select="count($propertyproviders)"/></xsl:comment>-->
	<xsl:if test="count($propertyproviders)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Property</th><th>Provider</th><th>Access</th><th>Metadata</th>
				</tr>
		<xsl:apply-templates select="$propertyproviders" mode="content"><xsl:sort select="@scriptElementID"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
    <xsl:variable name="metadata" select=".//metadataelement"/>
    <!--<xsl:comment>count($metadata)=<xsl:value-of select="count($metadata)"/></xsl:comment>-->
    <xsl:if test="count($metadata) > 0">
        <br/>
        <table>
            <tbody>
                <tr>
                    <th>Metadata Key</th><th>Value</th>
                </tr>
        <xsl:apply-templates select="$metadata" mode="content"><xsl:sort select="@key"/></xsl:apply-templates>
            </tbody>
        </table>
    </xsl:if>
</xsl:template>

<xsl:template match="parent|child" mode="content">
	<tr>
		<td><a href="#{@scriptElementID}"><xsl:value-of select="@scriptElementID"/></a></td>
		<td><xsl:value-of select="@provider"/></td>
		<td><xsl:value-of select="@surrogate"/></td>
	</tr>
</xsl:template>

<xsl:template match="methodprovider" mode="content">
	<tr>
		<td><a href="#{@scriptElementID}"><xsl:value-of select="@scriptElementID"/></a></td>
		<td><xsl:value-of select="@provider"/></td>
	</tr>
</xsl:template>

<xsl:template match="eventprovider" mode="content">
	<tr>
		<td><a href="#{@scriptElementID}"><xsl:value-of select="@scriptElementID"/></a></td>
		<td><xsl:value-of select="@provider"/></td>
	</tr>
</xsl:template>

<xsl:template match="collectionmethodprovider" mode="content">
	<tr>
		<td><a href="#{@scriptElementID}"><xsl:value-of select="@scriptElementID"/></a></td>
		<td><xsl:value-of select="@provider"/></td>
		<td><a href="#{@parentScriptElementID}"><xsl:value-of select="@parentScriptElementID"/></a></td>
	</tr>
</xsl:template>

<xsl:template match="propertyprovider" mode="content">
	<tr>
		<td><a href="#{@scriptElementID}"><xsl:value-of select="@scriptElementID"/></a></td>
		<td><xsl:value-of select="@provider"/></td>
		<td><xsl:value-of select="@access"/></td>
        <td>
            <xsl:if test="count(@m_INXIgnoreDefaultValueCheck)>0">
                <xsl:value-of select="local-name(@m_INXIgnoreDefaultValueCheck)"/>=<xsl:value-of select="@m_INXIgnoreDefaultValueCheck"/>
            </xsl:if>
        </td>
	</tr>
</xsl:template>

<xsl:template match="metadataelement" mode="content">
	<tr>
		<td><xsl:value-of select="@key"/></td>
		<td>
            <xsl:if test="string-length(@value)>0">
                <xsl:value-of select="@value"/>
            </xsl:if>
        </td>
	</tr>
</xsl:template>

<xsl:template match="method" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-method)</h3>
	<b>ScriptID</b> = '<xsl:value-of select="@scriptID"/>',
	<b>Name</b> = "<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
	<br/>
	<b>Return Type</b> = <xsl:value-of select="@returnType"/>
	<xsl:variable name="parameters" select=".//parameter"/>
	<xsl:if test="count($parameters)>0">
		<br/>
		<br/>
		<table>
			<tbody>
				<tr>
					<th>ParameterScriptID</th><th>Name</th><th>Data Type</th><th>Optionality</th><th>Description</th>
				</tr>
				<xsl:apply-templates select="$parameters" mode="content"></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
</xsl:template>

<xsl:template match="parameter" mode="content">
	<tr>
		<td>'<xsl:value-of select="@scriptID"/>'</td>
		<td>"<xsl:value-of select="@name"/>"</td>
		<td><xsl:value-of select="@dataType"/></td>
		<td><xsl:value-of select="@optional"/></td>
		<td><xsl:value-of select="@description"/></td>
	</tr>
</xsl:template>

<xsl:template match="property" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-property)</h3>
	<b>ScriptID</b>='<xsl:value-of select="@scriptID"/>',
	<b>Name</b> = "<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
	<br/>
	<b>Data Type</b> = <xsl:value-of select="@dataType"/>
	<xsl:apply-templates select=".//attributeboss" mode="content"></xsl:apply-templates>
	<xsl:variable name="assignableTypes" select=".//assignableType"/>
	<xsl:if test="count($assignableTypes)>0">
		<br/>
		<table>
			<tbody>
				<tr>
					<th>Other Assignable Types</th>
				</tr>
				<xsl:apply-templates select="$assignableTypes" mode="content"><xsl:sort select="@dataType"/></xsl:apply-templates>
			</tbody>
		</table>
	</xsl:if>
</xsl:template>

<xsl:template match="assignableType" mode="content">
	<tr>
		<td><xsl:value-of select="@dataType"/></td>
	</tr>
</xsl:template>

<xsl:template match="attributeboss" mode="content">
	<br/>
	<b>Associated Attribute</b> = <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="enum" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-enum)</h3>
	<b>ScriptID</b> ='<xsl:value-of select="@scriptID"/>',
	<b>Name</b> ="<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
	<br/>
	<br/>
	<table>
		<tbody>
			<tr>
				<th>EnumeratorScriptID</th><th>Name</th><th>Description</th>
			</tr>
			<xsl:apply-templates select=".//enumerator" mode="content"></xsl:apply-templates>
		</tbody>
	</table>
</xsl:template>

<xsl:template match="enumerator" mode="content">
	<tr>
		<td>'<xsl:value-of select="@scriptID"/>'</td>
		<td>"<xsl:value-of select="@name"/>"</td>
		<td><xsl:value-of select="@description"/></td>
	</tr>
</xsl:template>

<xsl:template match="suite" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-suite)</h3>
	<b>ScriptID</b> = '<xsl:value-of select="@scriptID"/>',
	<b>Name</b> = "<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
</xsl:template>

<xsl:template match="event" mode="content">
	<xsl:variable name="id" select="@scriptElementID"/>
	<hr/>
	<a name="{$id}"/>
	<h3><xsl:value-of select="@formattedName"/> (<xsl:value-of select="$id"/>-event)</h3>
	<b>ScriptID</b> = '<xsl:value-of select="@scriptID"/>',
	<b>Name</b> = "<xsl:value-of select="@name"/>",
	<b>Description</b> = <xsl:value-of select="@description"/>,
	<b>Cancelable</b> = <xsl:value-of select="@cancelable"/>,
	<b>Bubble</b> = <xsl:value-of select="@bubble"/>,
	<b>Plugin</b> = <xsl:value-of select="@plugin"/>
</xsl:template>

</xsl:stylesheet>

