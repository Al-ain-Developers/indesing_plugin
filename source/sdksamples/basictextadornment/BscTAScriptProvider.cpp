//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basictextadornment/BscTAScriptProvider.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IScriptRequestData.h"
#include "IDocument.h"
#include "IScriptUtils.h"
#include "ITextAttributeSuite.h"
#include "ITextAttrBoolean.h"
// General includes:
#include "CScriptProvider.h"
#include "TextAttrScriptUtility.h"

#include "Utils.h"
#include "GenericID.h"

// Project includes:
#include "BscTAID.h"
#include "BscTAScriptingDefs.h"


/** From SDK sample; Handles scripting of the BasicTextAdornment's text attribute property
	(p_BscTAShade). See the Provider
	statement for kBscTAScriptProviderBoss in BscTA.fr for the list of scripting objects
	on which the p_BscTAShade property is available.

	@ingroup basictextadornment
 */
class BscTAScriptProvider : public CScriptProvider
{
public:
	/**	Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
	BscTAScriptProvider(IPMUnknown* boss): CScriptProvider(boss), tasu(nil) {}

	/**	Destructor.
	 */
	~BscTAScriptProvider() {}

	/** Called if a provider can handle a method/event.
		@param methodID identifies the ID of the method/event to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);    

	/** PreAccessProperty is called before AccessPropery.  This method in this class resets tasu 
		with a pointer to a new instnace of TextAttributeScriptUtility.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode  PreAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script );

	/** Called if a provider can handle a property.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

	/** PostAccessProperty is called after AccessPropery.  This method in this class calls ApplyScriptCmd on tasu, if it's a put,
		and resets tasu to nil.
		@param propID identifies the ID of the property to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode  PostAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script );

private:
	
	/** Text attribute script providers need to use the TextAttrScriptUtility 
	class to access and modify text attributes.  This provider demonstrates
	how to use this utility.  Third party text attribute script providers should
	follow this same pattern.
	*/
	scoped_ptr<TextAttrScriptUtility>	tasu ;
};

/*	Make the implementation available to the application.
*/
CREATE_PMINTERFACE(BscTAScriptProvider, kBscTAScriptProviderImpl)

/*
*/
ErrorCode BscTAScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	// No events.
	return CScriptProvider::HandleMethod(methodID, data, script);
}


/* Restet tasu to a new instance of TextAttrScriptUtility.
*/
ErrorCode BscTAScriptProvider::PreAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	tasu.reset( new TextAttrScriptUtility( script, data->GetRequestContext() ) ) ;
	return kSuccess ;
}

/* Access the p_BscTAShade property via TextAttrScriptUtility.
*/
ErrorCode BscTAScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	ASSERT( tasu != nil ) ;
	switch (propID.Get())
	{
		case p_BscTAShade:
			return tasu->AccessBoolAttribute(data, propID, kBscTAAttrBoss);
		default:
			ASSERT_FAIL( "Unexpected property ID" ) ;
	}

	return kFailure ;
}

/* Call ApplyScriptCmd if it's  a put, and reset tasu to nil.
*/
ErrorCode BscTAScriptProvider::PostAccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	ASSERT( tasu != nil ) ;
	ErrorCode err = kSuccess ;
	if ( data->IsPropertyPut() )
		err = tasu->ApplyScriptCmd() ;
	tasu.reset() ;
	return err ;
}

// BscTAScriptProvider.cpp
