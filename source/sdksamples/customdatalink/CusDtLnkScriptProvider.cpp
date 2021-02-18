//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkScriptProvider.cpp $
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
#include "IWorkspace.h"
#include "ICusDtLnkFacade.h"
#include "ILinksManager.h"
#include "IDocument.h"
#include "IAddLinkCmdData.h"
#include "ILink.h"
#include "ILinkState.h"
#include "IDatalink.h"
#include "IDatalink.h"
#include "ILinkResource.h"
#include "ILinkManager.h"
#include "ILinkObject.h"
#include "ILinkObjectReference.h"
#include "ILinkUtils.h"
#include "ILinkFacade.h"
#include "IRestoreLinkCmdData.h"
#include "IUpdateLink.h"
#include "IScriptUtils.h"
#include "LinkQuery.h"

// General includes:
#include "Utils.h"
#include "FileUtils.h"
#include "FileTypeInfo.h"
#include "IDTime.h"
#include "ErrorUtils.h"
#include "NAMEINFO.H"
#include "CAlert.h"
#include "CScriptProvider.h" // RepresentSc...
#include "UIDList.h"
// Project includes:
#include "CusDtLnkScriptingDefs.h"
#include "CusDtLnkID.h"



/** Implements IScriptProvider, to support INX/Snippet roundtripping, e.g. to 
	let custom datalinked page items roundtrip through asset libraries or
	through INDS (Snippet) files or INX.

    @ingroup customdatalink
*/
class CusDtLnkScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkScriptProvider(IPMUnknown* boss) : RepresentScriptProvider(boss) {};

	/** Destructor
	*/
	~CusDtLnkScriptProvider() {}

	/** @see IScriptProvider::HandleMethod	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent);

	/** @see IScriptProvider::AccessProperty
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

	/** @see RepresentScriptProvider::GetNumObjects */
	virtual int32  GetNumObjects( const IScriptRequestData* data, IScript* parent ) ;

	/** @see RepresentScriptProvider::AppendNthObject */
	virtual ErrorCode  AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList ) ;
 
	/** @see RepresentScriptProvider::AppendAllObjects */
	virtual ErrorCode AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList ) ;

private:

	ErrorCode doUpdate(IScriptRequestData* data, IScript* script);

	ErrorCode doCreate(IScriptRequestData* data, IScript* parent);

	ErrorCode accessLinkInfo(IScriptRequestData* data, IScript* parent, ScriptID propID);

//	ErrorCode accessUniqueKey(IScriptRequestData* data, IScript* parent, ScriptID propID);

	/** Get list of links from parent, which could be either a 
		document or a page item, and returns a count of the links
	*/
	int32 getLinkList( IScript* script, const IScriptRequestData* data, UIDList& outLinkList );
	int32 GetScriptStatusEnum( ILinkResource::ResourceState resourceState, ILinkResource::ResourceStoreState storeState );
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(CusDtLnkScriptProvider, kCusDtLnkScriptProviderImpl)


/*  
*/
ErrorCode CusDtLnkScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, 
											  IScript* script)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkScriptProvider::HandleMethod() +\n");
	ErrorCode status = kFailure;
	do {
		switch (methodID.Get())
		{
			case e_Create:
				status = this->doCreate(data, script);
				break;

			case e_Update:
				status = this->doUpdate(data, script);
				break;	
		
			default:
			{
				status = RepresentScriptProvider::HandleMethod(methodID, data, script);
			}
			break;
		}	
	} while(kFalse);

    return status;
}


/* 
*/
ErrorCode CusDtLnkScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, 
												 IScript* script)
{
	ErrorCode status = kFailure;
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkScriptProvider::AccessProperty() +\n");
	do {
		switch (propID.Get())
		{
			case p_CusDtLnkLinkInfo:
				status=  this->accessLinkInfo(data, script, propID);
			break;

			default:
			{
				
				status = RepresentScriptProvider::AccessProperty(propID, data, script);
			}
			break;
		}
	} while(kFalse);

    return status;
}

/*
*/
int32  CusDtLnkScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	ASSERT(parent);
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkScriptProvider::GetNumObjects() +\n");
	UIDList linkList(parent->GetDataBase( data->GetRequestContext() )) ;
	return this->getLinkList( parent, data, linkList ) ;
}

/*
*/
ErrorCode CusDtLnkScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	ASSERT(parent);
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkScriptProvider::AppendNthObject() +\n");
	UIDList linkList(parent->GetDataBase( data->GetRequestContext() ));
	this->getLinkList(parent, data, linkList);
	InterfacePtr<IScript> linkScript(linkList.GetRef(n), UseDefaultIID()) ;
	if(linkScript) {
		objectList.push_back(linkScript);
	}
	return kSuccess ;
}

/*
*/
ErrorCode CusDtLnkScriptProvider::AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList )
{
	ASSERT(parent);
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkScriptProvider::AppendAllObjects() +\n");
	UIDList linkList(parent->GetDataBase( data->GetRequestContext() )) ;
	int32 count = this->getLinkList(parent, data, linkList) ;
	for (int32 i = 0 ; i < count ; ++i ) {
		InterfacePtr<IScript> linkScript( linkList.GetRef( i ), UseDefaultIID() ) ;
		if (linkScript) {
			objectList.push_back( linkScript ) ;
		}
	}
	return kSuccess ;
}

/*
*/
int32 CusDtLnkScriptProvider::getLinkList( IScript* script, const IScriptRequestData* data, UIDList& outLinkList )
{
	UIDList allLinksList(outLinkList.GetDataBase());
	do {
		InterfacePtr<IDocument> document(script, UseDefaultIID());
		
		// See if this looks like a document
		if (document)
		{
			InterfacePtr<ILinkManager> iLinkManager(script, UseDefaultIID());
			if ( iLinkManager )
			{
				// an empty query matches all links
				LinkQuery emptyQuery;
				iLinkManager->QueryLinks(emptyQuery, kIDLinkClientID, allLinksList);
			}
		}
		else //assume it's a page item (or text story)
		{
			IDataBase *db = ::GetDataBase(script);
			InterfacePtr<ILinkManager> iLinkManager(db, db->GetRootUID(), UseDefaultIID());

			if ( iLinkManager )
			{
				ILinkManager::QueryResult result;
				if ( iLinkManager->QueryLinksByObjectUID(::GetUID(script), result) )
				{
					const RequestContext context = data->GetRequestContext();
					UIDList childList(db);

					for ( ILinkManager::QueryResult::const_iterator iter = result.begin(); iter != result.end(); ++iter )
					{
						InterfacePtr<ILink> iLink(db, *iter, UseDefaultIID());
						if ( iLink )
						{
							allLinksList.push_back(*iter);
							// we could be doing this step more efficiently by adding the children directly to
							// allLinksList, but pre-Basil, all child links were appended to the very end of the list.
							// therefore, I'm attempting to preserve that behavior by accumulating a list of all children
							// and then appending the list to the bigger list as a final step.  Also, I do not want
							// to assume that the call to GetLinkChildren will append the result to the uidlist that is
							// passed to the function.  It could clear the list if there are no children.  Therefore,
							// I'm creating a local list which I'll append to the childList.
							UIDList children(db);
							iLink->GetChildren(children);

							childList.Append(children);
						}
					}

					// append any child links
					if ( !childList.IsEmpty() )
					{
						allLinksList.Append(childList);
					}
				}
			}
		}

		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}

		// Now filter the all-links-list for only our custom datalinks
		for(int32 i=0; i < allLinksList.Length(); i++) {
			UIDRef nextUIDRef = allLinksList.GetRef(i);
			// Only add if it's a custom datalink
			if(facade->IsOurCustomDataLink(nextUIDRef)) {
				outLinkList.Append(nextUIDRef.GetUID()) ;
			}
		}
	} while(kFalse);

	

	return outLinkList.Length() ;
}


/*
*/
ErrorCode CusDtLnkScriptProvider::doCreate(IScriptRequestData* data, 
											   IScript* parentScript)
{
	ErrorCode retval = kFailure;
	do 
	{
		ErrorCode err = kSuccess;
		IDataBase* db = parentScript->GetDataBase( data->GetRequestContext() ) ;

		// assume alias-database-1.csv is loaded already, we are going to create a link for asset record ID 1000592
		// this is on par with the CS3 implementation, although not good enough
		URI uri;
		uri.SetComponent(URI::kScheme, WideString(kCusDtLnkScheme));
		InterfacePtr<IWorkspace> appWorkspace(GetExecutionContextSession()->QueryWorkspace());
		PMString dbName("alias-database-1.csv");
		Utils<ICusDtLnkFacade> facade;
		PMString dbPath = facade->GetAssetDataBasePath(appWorkspace, dbName);
		uri.SetComponent(URI::kPath, WideString(dbPath));
		uri.SetComponent(URI::kQuery, WideString("1000592"));

		UID newResourceUID(kInvalidUID);
		Utils<Facade::ILinkFacade> iFacade;
		retval = iFacade->CreateResource(db, uri, kIDLinkClientID, PMString(), newResourceUID);
		ASSERT(newResourceUID != kInvalidUID);
		UID linkUID = kInvalidUID;
		retval = iFacade->CreateLink(db, ILink::kImport, kIDLinkClientID, ::GetUID(parentScript), newResourceUID, false, linkUID);
		ASSERT(linkUID != kInvalidUID);

		InterfacePtr<IScript> linkScript(db, linkUID, UseDefaultIID());
		data->AppendReturnData( parentScript, e_Create, ScriptData( linkScript ) ) ;
	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode CusDtLnkScriptProvider::doUpdate(IScriptRequestData* data, IScript* script)
{
	ErrorCode retval = kFailure;
	do {
		ASSERT(script);
		if(!script) {
			break;
		}
		ASSERT(data);
		if(!data) {
			break;
		}

		IDataBase* db = script->GetDataBase( data->GetRequestContext() ) ;

		UID newObjectUID;

		InterfacePtr<ILink> iLink(script, UseDefaultIID());
		if (!iLink) { 
			break;
		}
		
		// If the link is missing, 
		// the update cannot  work.
		InterfacePtr<ILinkState> linkState(db, iLink->GetObject(), IID_ILINKSTATE);

		InterfacePtr<IUpdateLink> update((IUpdateLink *)::CreateObject(kImportLinkBoss, IID_IUPDATELINK));
		if ( !update) 
			return kFailure;

		InterfacePtr<ILinkResource> linkResource(db, iLink->GetResource(), UseDefaultIID());
		if (!linkResource || linkResource->GetState() == ILinkResource::kMissing)
			return kLinkMissingError;

		UIFlags uiFlags = kSuppressUI;

		ErrorCode result = update->DoUpdateLink(linkState->GetProviderClass(), iLink, newObjectUID, uiFlags);

		switch ( result )
		{
			case IUpdateLink::kSuccess :
			{
				ErrorCode err = kLinkMissingError ;


				//return the new link
				if ( newObjectUID != kInvalidUID )
				{
					InterfacePtr<ILinkManager> iLinkManager(db, db->GetRootUID(), UseDefaultIID());
					ILinkManager::QueryResult queryResult;
					iLinkManager->QueryLinksByObjectUID(newObjectUID, queryResult);
					InterfacePtr<IScript> newLink(db, *queryResult.begin(), UseDefaultIID());

					data->AppendReturnData( script, e_Update, ScriptData( newLink ) ) ;
					err = kSuccess ;
				}


				ASSERT_MSG( err == kSuccess, "Updated link not found" ) ;
				return err ;
			}
			case IUpdateLink::kOutOfMemory :
				return kMemoryFullError ;
			case IUpdateLink::kInvalidParameter :
				return kInvalidParameterErr ;
			case IUpdateLink::kNoAssociatedPageItem :
				return kNoAssociatedPageItemError ;
			default :
				// Don't assert here. There are various other legitimate errors
				// (like file system errors. Than can happen.
				// -- Steve Pellegrin 2/12/2003
				//		ASSERT_FAIL( "Unrecognized return code from DoUpdateLink" ) ;
				return kFailure ;
		}

	} while(kFalse);
	return retval;
}

/*
*/
ErrorCode CusDtLnkScriptProvider::accessLinkInfo(IScriptRequestData* data, IScript* script, ScriptID propID)
{

	InterfacePtr<ILink> iLink(script, UseDefaultIID());
	InterfacePtr<ILinkResource> iLinkResource(::GetDataBase(script), iLink->GetResource(), UseDefaultIID());
	InterfacePtr<ILinkObject> iLinkObject(::GetDataBase(script), iLink->GetObject(), UseDefaultIID());

	ErrorCode err = kFailure;
	IDataBase* db = script->GetDataBase(data->GetRequestContext());
	UID itemUID = iLink->GetObject();
    InterfacePtr<ILinkState> linkState((ILinkState*)iLinkObject->QueryLinkedObject(IID_ILINKSTATE));

	ClassID theClass = ::GetClass(iLink);

	if (!linkState)
	{
		ASSERT_FAIL("CusDtLnkScriptProvider::AccessLinkInfo can't find ILinkState -- this IScript still using IDataLink?");
		return kFailure;
	}

	ScriptData scriptData;
	NameInfo ni;
	PMString formatName;
	uint32 fileType = 0;
	uint64 size = 0;
	uint64 timestamp = 0;
	IDataLink::StateType state = IDataLink::kLinkNormal;
	bool16 isNeeded;
	bool16 hasChanged;

	if (data->IsPropertyGet())
	{
		isNeeded = linkState->IsLinkNeeded();
		hasChanged = linkState->HasChanged();

		ILinkResource::ResourceState resourceState = iLinkResource->GetState();
		ILinkResource::ResourceStoreState resourceStoreState = iLinkResource->GetStoreState();
		int32 statusEnum = GetScriptStatusEnum(resourceState, resourceStoreState);
		switch (statusEnum) {
			case en_LinkNormal:
				state = IDataLink::kLinkNormal;
				break;
			case en_LinkEmbedded:
				state = IDataLink::kEmbedded;
				break;
			case en_LinkOutOfDate:
				state = IDataLink::kLinkOutOfDate;
				break;
			case en_LinkMissing:
			default:
				state = IDataLink::kLinkMissing;
				break;
		}

		PMString tempFullName("");
		PMString shortName("");
		PMString volume("");
		uint32 dirID = 0L;

		if (iLinkResource)
		{
			// If there's a valid UID being pointed to for the linked item, dig up the file info
			WideString wShortName = iLinkResource->GetShortName(true);
			wShortName.GetSystemString(&shortName);	// can we do this without copying?
			shortName.SetTranslatable(kFalse);

			IDFile file;
			Utils<ICusDtLnkFacade>()->URIToIDFile(iLinkResource->GetURI(), file);

#if BASIL_SCRIPTING_DOM
			WideString longName = iLinkResource->GetLongName(false);
			longName.GetSystemString(&tempFullName);
			tempFullName.SetTranslatable(kFalse);
#else
			// For pre-basil scripting DOMs, we need to return system paths.  Perhaps,
			// we can use UNIX style paths in Basil/Chive.  However, we
			// first need the AutoFindFileUtils to work with UNIX paths.
			FileUtils::IDFileToPMString(file, tempFullName);
			tempFullName.SetTranslatable(kFalse);
#endif

#ifdef MACINTOSH
			FileUtils::GetVolumeName(&file, &volume);
			dirID = file.GetParId();
#endif
			formatName = iLinkResource->GetFormatType();
			FileTypeInfo fileTypeInfo = iLinkResource->GetDataType();
#ifdef MACINTOSH
			SysOSType osFileType = fileTypeInfo.GetFileType();
			fileType = osFileType;
#endif
			size = iLinkResource->GetSize();
			timestamp = iLinkResource->GetModTime().GetTime();
		}

		ScriptListData listData;

//		PMString *s = ni.GetFilename();
		ScriptData tempData(shortName.empty() ? "" : shortName);
		listData.push_back(tempData);
		
//		s = ni.GetVolume();
		tempData.SetPMString(volume.empty() ? "" : volume);
		listData.push_back(tempData);

		tempData.SetInt32(dirID);
		listData.push_back(tempData);
		
		tempData.SetInt32((int32&)(theClass.Get()));
		listData.push_back(tempData);
		
		tempData.SetPMString(formatName);
		listData.push_back(tempData);
		
		tempData.SetInt32((int32)fileType);
		listData.push_back(tempData);

		tempData.SetPMString(tempFullName);
		listData.push_back(tempData);

		tempData.SetInt64((int64)size);
		listData.push_back(tempData);
		
		tempData.SetDate(timestamp);
		listData.push_back(tempData);
		
		tempData.SetInt32((int32)state);
		listData.push_back(tempData);
		
		tempData.SetBoolean(isNeeded);
		listData.push_back(tempData);
		
		tempData.SetBoolean(hasChanged);
		listData.push_back(tempData);
		
		scriptData.SetList(listData);
		data->AppendReturnData( script, propID, scriptData ) ;
		err = kSuccess;
	}
	else if (data->IsPropertyPut())
	{
		err = data->ExtractRequestData( p_LinkInfo, scriptData ) ;	
		if (err != kSuccess) return err;
		
		ScriptListData listData;
		err = scriptData.GetList( listData ) ;
		if (err != kSuccess) return kFailure;
		
		int32 listIndex = 0;
		PMString newFileName;
		listData[listIndex++].GetPMString(newFileName);
		
		PMString newVolume;
		listData[listIndex++].GetPMString(newVolume);
		
		int32 newDirID;
		listData[listIndex++].GetInt32(&newDirID);

		int32 newClassID;
		listData[listIndex++].GetInt32(&newClassID);

		listData[listIndex++].GetPMString(formatName);
		listData[listIndex++].GetInt32((int32 *)&fileType);

		PMString fullName;
		listData[listIndex++].GetPMString(fullName);

		listData[listIndex++].GetInt64((int64 *)&size);
		
		listData[listIndex++].GetDate(&timestamp);
		
		int32 tempState;
		listData[listIndex++].GetInt32(&tempState);
		state = (IDataLink::StateType)tempState;
		
		listData[listIndex++].GetBoolean(&isNeeded);
		listData[listIndex++].GetBoolean(&hasChanged);

		// Set up the ILink and IResource and ILinkObject
		IDFile file(FileUtils::PMStringToSysFile(fullName.empty() ? newFileName : fullName));
		URI linkURI;
		bool succeeded = Utils<ILinkUtils>()->IDFileToResourceId(file, linkURI);
		if (!succeeded)
		{
			if ( fullName.empty() )
				linkURI.SetURI(newFileName.GetUTF8String().c_str());
			else
				linkURI.SetURI(fullName.GetUTF8String().c_str());
			
			linkURI.SetComponent(URI::kScheme, WideString("file"));
		}
		
		// Update resource and link
		err = Utils<Facade::ILinkFacade>()->ReinitResource(UIDRef(db, iLink->GetResource()), linkURI);

		// Set the format type --- IS THIS STEP REALLY NEEDED? WILL kLinkResourceStateUpdateCmdBoss
		// SET THE FORMAT TYPE FOR US ALREADY? -- Not if the link resource is missing.  If we do not
		// set the format, then we fail to recognize such things as "IsInCopyStory."
        InterfacePtr<ILinkResource> iLinkResource2(db, iLink->GetResource(),UseDefaultIID());
		db->BeginTransaction();
        iLinkResource2->SetFormatType(formatName);
		if ( size )
			iLinkResource2->SetSize(size);
		db->EndTransaction();

		if (err != kSuccess )	 // error adding the links.
		{
			ErrorUtils::PMSetGlobalErrorCode(err);
			return err;
		}


		if (err == kSuccess)
		{
			if (linkState != nil)
			{
				linkState->SetIsLinkNeeded(isNeeded);
				linkState->SetHasChanged(hasChanged);
			}
		}
	
	}

	return err ;
}




/*
*/
#if 0
ErrorCode CusDtLnkScriptProvider::accessUniqueKey(IScriptRequestData* data, IScript* script, ScriptID propID)
{
	ErrorCode retval = kFailure;
	
	do {
		InterfacePtr<IDataLink> dl(script, UseDefaultIID() ) ;
		ASSERT(dl);
		if(!dl) {
			break;
		}
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		ASSERT(facade->IsOurCustomDataLink(::GetClass(dl)));
		PMString value = facade->RetrieveUniqueKey(dl);
		if (data->IsPropertyGet())
		{
			ScriptData outputData;
			outputData.SetPMString(value);
			data->AppendReturnData( script,&outputData);
			retval = kSuccess;
		}
		else if (data->IsPropertyPut())
		{
			PMString value;
			ScriptData inputdata;
			retval = data->ExtractRequestData(propID, inputdata);	
			if(retval == kSuccess) {
				retval	= inputdata.GetPMString(value);
			}
		}
	} while(kFalse);

	return retval ;

}
#endif

int32 CusDtLnkScriptProvider::GetScriptStatusEnum( ILinkResource::ResourceState resourceState, ILinkResource::ResourceStoreState storeState )
{
	switch( resourceState )
	{
		// storeState can be kNormal, kCached, kEmbedded
		case ILinkResource::kAvailable :
			// Probably should change last state -- available and cached probably doesn't equal normal
			return storeState == ILinkResource::kNormal ? en_LinkNormal : storeState == ILinkResource::kEmbedded ? en_LinkEmbedded : en_LinkNormal;

		case ILinkResource::kMissing :
			return  en_LinkMissing;

		case ILinkResource::kInaccessible :
			return  en_LinkInaccessible;

		case ILinkResource::kPending :
			return en_LinkOutOfDate ;
		
		case ILinkResource::kUnknown :
			return en_LinkMissing ;
			
		default :
			ASSERT_FAIL( "Unrecognized link status" ) ;
			return 0 ;
	}
}

//  Code generated by DollyXs code generator
