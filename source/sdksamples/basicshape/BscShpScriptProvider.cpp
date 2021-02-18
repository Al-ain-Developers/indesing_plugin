//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicshape/BscShpScriptProvider.cpp $
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
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IPageItemScriptUtils.h"
#include "INewPageItemCmdData.h"
#include "IPathUtils.h"
#include "IPageItemTypeUtils.h"
#include "IMultiColumnTextFrame.h"
#include "ITextScriptUtils.h"
#include "ITextModel.h"
#include "ICommand.h"
#include "BscShpScriptingDefs.h"
#include "ITextModel.h"

// Implementation includes:
#include "CmdUtils.h"
#include "CScriptProvider.h"

// Project includes:
#include "BscShpID.h"
#include "BscShpUtils.h"

/** From SDK sample; shows how to implement a script provider for a custom page item,
	kBscShpPageItemBoss.

	See Scripting Resources defined in the plug-in's .fr file.
	
	@see kBscShpPageItemBoss - the scriptable boss
	@see kBasicShapeObjectScriptElement - the script object that exposes kBscShpPageItemBoss in the Scripting DOM
	@see BscShp.fr
	@see IPageItemScriptUtils
	@ingroup basicshape
*/
class BscShpScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor
		@param boss the boss object this interface is aggregated onto
	*/
	BscShpScriptProvider(IPMUnknown *boss);

	/** Destructor.
	*/
	virtual ~BscShpScriptProvider();

	/** Called if a provider can handle a method/event.
		@param methodID identifies the ID of the method/event to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode	HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** Called if a provider can access a property.
		@param propID identifies the property ID.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing.
	 */
	virtual ErrorCode	AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script);

protected:
	/**	Get the number of child objects in a collection on the given parent.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@return the number of child objects.
	 */
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent );

	/**	Append the nth child object from a collection on the given parent.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@param n IN the index (0-based) of the desired child object in the collection.
		@param objectList OUT the nth child gets added to this list
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );

	/**	Append all child objects in a collection on the given parent.
		n is a 0-based index.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@param objectList OUT the objects in the collection.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	virtual ErrorCode	AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList );

private:
	/** Callback that creates a kBscShpPageItemBoss, see IPageItemScriptUtils::DoCreatePageItem.
		@param data
		@param script
		@param parent
		@param bounds
		@param pageItem
		@param boundsSpace
	*/
	static ErrorCode CreateBasicShape(IScriptRequestData* data, IScript* script, IPMUnknown* parent, const PMPointList& bounds, UIDRef& pageItem, const Transform::CoordinateSpace& boundsSpace);
	ErrorCode AccessParentStory(IScriptRequestData*data, IScript*script);
	ErrorCode AccessTextBasicShape(IScriptRequestData*data, IScript*script);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(BscShpScriptProvider, kBscShpScriptProviderImpl)

/*
*/
BscShpScriptProvider::BscShpScriptProvider(IPMUnknown *boss):
RepresentScriptProvider(boss)
{
}

/*
*/
BscShpScriptProvider::~BscShpScriptProvider()
{
}

/*
*/
int32 BscShpScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	return Utils<IPageItemScriptUtils>()->CountPageItemChildren(parent, data) ;
}

/*
*/
ErrorCode BscShpScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	return Utils<IPageItemScriptUtils>()->GetNthPageItemChild( n, parent, data, objectList ) ;
}

/*
*/
ErrorCode BscShpScriptProvider::AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList )
{
	return Utils<IPageItemScriptUtils>()->GetEveryPageItemChild( parent, data, objectList ) ;
}

/*
*/
ErrorCode BscShpScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	switch (methodID.Get())
	{
		case e_Create:
			return Utils<IPageItemScriptUtils>()->DoCreatePageItem(data, script, &this->CreateBasicShape);
		default:
			return RepresentScriptProvider::HandleMethod(methodID, data, script);
	}
}

ErrorCode BscShpScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
	switch (propID.Get())
	{
		case p_TextBasicShape:
			return AccessTextBasicShape(data, script);
		case p_ParentStory:
			return AccessParentStory(data, script);
		default:
			return RepresentScriptProvider::AccessProperty(propID, data, script);
	}

}

/*
*/
ErrorCode BscShpScriptProvider::CreateBasicShape(IScriptRequestData* data, IScript* , IPMUnknown* parent, const PMPointList& bounds, UIDRef& pageItem, const Transform::CoordinateSpace& boundsSpace)
{
	UIDRef parentRef;
	ErrorCode result = Utils<IPageItemScriptUtils>()->PreparePageItemParent(data, parent, parentRef);
	ASSERT(result == kSuccess);
	if (result != kSuccess) {
		return kBscShpCreatePageItemErrorCode;
	}
	PMRect bbox = PMRect(bounds[0], bounds[1]);
	BscShpUtils bscShpUtils;
	pageItem = bscShpUtils.CreateBasicShape(parentRef, bbox);
	if (pageItem == UIDRef(nil, kInvalidUID)) {
		return kBscShpCreatePageItemErrorCode;
	}
	return kSuccess;
}

// Special attribute that indicates if the basic shape has text in it. During
// INX import, if the value is true, then convert it to text frame, 
// i.e. create a multicolumn frame inside basic shape.
ErrorCode BscShpScriptProvider::AccessTextBasicShape( IScriptRequestData* data, IScript* script )
{
    ScriptData scriptData;

    if (data->IsPropertyGet())
    {
		bool16 isTextFrame =  Utils<IPageItemTypeUtils>()->IsTextFrame( script );		
        scriptData.SetBoolean(isTextFrame);
        data->AppendReturnData( script, p_TextBasicShape, scriptData ) ;
        return kSuccess;
    }
    else if (data->IsPropertyPut())
    {
        ErrorCode err = data->ExtractRequestData( p_TextBasicShape, scriptData ) ;
		bool16 isTextFrame = kFalse;
        err = scriptData.GetBoolean(&isTextFrame);
        if (err != kSuccess) return err ;

		InterfacePtr<IMultiColumnTextFrame> multiTextFramePre ( (IMultiColumnTextFrame*) Utils<ITextScriptUtils>()->QueryChildMultiColFrame( script, IMultiColumnTextFrame::kDefaultIID ) );
		if (!multiTextFramePre && isTextFrame)
		{ // if the basicshape has text frame, then create one

			InterfacePtr<ICommand> convertCmd(CmdUtils::CreateCommand(kConvertItemToTextCmdBoss));
            convertCmd->SetItemList( ::GetUIDRef(script) );
            err = CmdUtils::ProcessCommand(convertCmd);
		}
        return err ;
    }

    return kSuccess;
}


ErrorCode BscShpScriptProvider::AccessParentStory(IScriptRequestData*data, IScript*script)
{
	if (data->IsPropertyGet())
	{
		bool16 isTextFrame =  Utils<IPageItemTypeUtils>()->IsTextFrame( script );		
		if (!isTextFrame)
		{
            data->AppendReturnData( script, p_ParentStory, ScriptData( (IScript*) nil ) ) ; //property not supported without text
			return kSuccess;
		}

		InterfacePtr<IMultiColumnTextFrame> multiTextFrame ( (IMultiColumnTextFrame*) Utils<ITextScriptUtils>()->QueryChildMultiColFrame( script, IMultiColumnTextFrame::kDefaultIID ) );
		if (!multiTextFrame) return kFailure;

		InterfacePtr<ITextModel> textModel(multiTextFrame->QueryTextModel());
		InterfacePtr<IScript> textModelScript(textModel, UseDefaultIID());
		if (!textModelScript) return kFailure;

		data->AppendReturnData( script, p_ParentStory, ScriptData( textModelScript ) ) ;
		return kSuccess;
	}
	else if (data->IsPropertyPut())
	{
		return Utils<IScriptErrorUtils>()->SetReadOnlyPropertyErrorData( data, p_ParentStory );
	}
	return kFailure;
}

// End, BscShpScriptProvider.cpp.
