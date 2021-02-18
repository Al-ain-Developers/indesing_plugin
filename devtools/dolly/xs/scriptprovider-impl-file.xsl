<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
<xsl:import href="global-variables.xsl"/>
<xsl:import href="standard-adobe-header.xsl"/>
<xsl:import href="standard-footer.xsl"/>
<xsl:output name="cppfile" method="text"/>

<xsl:template match="impl-item[@impl-file = 'scriptprovider-impl-file']">
Generating ScriptProvider Implementation file for <xsl:value-of select="@impl-name"/>
<xsl:document href="{/code/@source-dir-absolute}{$filesep}{@impl-name}.cpp" format="cppfile">
<xsl:call-template name="standard-adobe-header"/>
  <xsl:call-template name="scriptprovider"/>
  <xsl:call-template name="standard-footer"/>
 </xsl:document>
</xsl:template>

<xsl:template name="scriptprovider" match="scriptprovider">
// Interface includes:
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IWorkspace.h"

// General includes:
#include "CAlert.h"
#include "CScriptProvider.h"

// Project includes:
#include "<xsl:value-of select="/code/@short-name"/>ScriptingDefs.h"
#include "<xsl:value-of select="/code/@short-name"/>ID.h"


/** Demonstrates extending the Application script object, adding both an method and a property.

    To see the interaction between a script and this plug-in, copy the following code 
    into a file you create named sayhello.js, then place this JavaScript file into 
    a InDesign CSx/Presets/Scripts folder.

    var said = "hello";
    app.speak(said);
    var yourresponse = app.response;
    app.speak(yourresponse);
    
    From the application main menu, choose Window|Automation|Scripts if the 
    Scripts palette is not already visible. Double-click on sayhello.js to start the script. 
    In the debug build, you can set a breakpoint in HandleMethod() to step through the 
    interaction between the script and this plug-in.

    <xsl:variable name="groupname" select="translate(/code/@long-name, 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', 'abcdefghijklmnopqrstuvwxyz')"/>
    @ingroup <xsl:value-of select="$groupname"/>
*/
class <xsl:value-of select="@impl-name"/> : public CScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	<xsl:value-of select="@impl-name"/>(IPMUnknown* boss) : CScriptProvider(boss) {};

	/** Destructor. Does nothing.
	*/
	~<xsl:value-of select="@impl-name"/>() {}

	/** This method is called if a provider can handle an method.
	@param methodID identifies the ID of the method to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent);

	/** This method is called if a provider can handle a property.
	@param propID identifies the ID of the property to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

private:
	/** This method delegated to handle the e_Speak method, which extracts the p_Said property and displays its string content in a dialog. 
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode Speak(IScriptRequestData* data, IScript* parent);

	/** This method delegated to handle the p_Response property. 
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessResponse(ScriptID propID, IScriptRequestData* data, IScript* parent);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(<xsl:value-of select="@impl-name"/>, <xsl:value-of select="@impl-id"/>)


/* HandleMethod */
ErrorCode <xsl:value-of select="@impl-name"/>::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (methodID.Get())
	{
	case e_Speak:
		status = Speak(data, parent);
		break;

	default:
		status = CScriptProvider::HandleMethod(methodID, data, parent);
	}

    return status;
}


/* AccessProperty
*/
ErrorCode <xsl:value-of select="@impl-name"/>::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
	case p_Response:
		status = AccessResponse(propID, data, parent);
		break;

    default:
		status = CScriptProvider::AccessProperty(propID, data, parent);
    }

    return status;
}


/* Speak
*/
ErrorCode <xsl:value-of select="@impl-name"/>::Speak(
	IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	ScriptData scriptData;
	status = data->ExtractRequestData(p_Said, scriptData);
	if (status == kSuccess)
	{
		PMString said;
		status = scriptData.GetPMString(said);
		said.SetTranslatable(kFalse);
		CAlert::InformationAlert(said);
	}

	return status;
}


/* AccessResponse
*/
ErrorCode <xsl:value-of select="@impl-name"/>::AccessResponse(
	ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	if (data->IsPropertyGet())
	{
		PMString response("Hello back to you");

		ScriptData scriptData;
		scriptData.SetPMString(response);
		response.SetTranslatable(kFalse);
		data->AppendReturnData( parent, propID, scriptData ) ;
		status = kSuccess;
	}

	return status;
}
</xsl:template>
</xsl:stylesheet>