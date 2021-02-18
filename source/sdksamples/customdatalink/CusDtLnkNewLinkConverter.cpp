//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkNewLinkConverter.cpp $
//  
//  Owner: SusanCL
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

// ----- Interfaces -----
#include "IAutoFindFileUtils.h"
#include "ICoreFilename.h"
#include "IDatalink.h"
#include "IDataLinkReference.h"
#include "IDataLinkListReference.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "ILinkManager.h"
#include "ILinkObject.h"
#include "ILinkObjectReference.h"
#include "ILinksManager.h"
#include "ILinkUtils.h"
#include "INewLinkConverter.h"
#include "IPersistUIDData.h"
//#include "IPrivateLinkUtils.h"
#include "IScript.h"
#include "IStoreInternal.h"
#include "ICusDtLnkFacade.h"

// ----- Includes -----
#include "GlobalTime.h"
#include "K2Vector.tpp"
#include "NAMEINFO.H"
#include "PMString.h"
#include "UIDList.h"
#include "WideString.h"
#include "CPMUnknown.h"
#include "CusDtLnkLinkAssetConverter.h"
#include "CusDtLnkImportLinkConverter.h"

// ----- Utility files -----
#include "CmdUtils.h"
#include "FileUtils.h"
#include "StreamUtil.h"
#include "Utils.h"

// ----- ID.h files -----
#include "CusDtLnkID.h"

/**
	This is for converting pre CS3 data link stuff to the new CS4 architecture, called by the phase 2 converter.
 
	@ingroup customdatalink
 */
class CusDtLnkNewLinkConverter : public CPMUnknown<INewLinkConverter>
{
public:
	CusDtLnkNewLinkConverter (IPMUnknown* boss) : 
	  CPMUnknown<INewLinkConverter> (boss), fDataBase (nil), fLinkManager (nil) {}

		~CusDtLnkNewLinkConverter () {}

	/**	Can override. Do all the basic conversion. */
	virtual ErrorCode DoConvert (const UIDRef& oldLinkRef);

protected:
	/**	Can override. Default is to assume direct reference to the link object from data link. */
	virtual UID CreateNewLinkObject (const UIDRef& oldLinkRef);

	/**	Should override. Default is to do nothing. */
	virtual ErrorCode DoCustomConversion (const UIDRef& oldLinkRef);

	InterfacePtr<ILinkManager>	fLinkManager;
	IDataBase*					fDataBase;

private:
	/** actual conversion */
	UID			_DoConvert(const UIDRef& oldLinkRef, bool bChild);
	/** Convert DataLink to LinkResource */
	ErrorCode	ConvertToLinkAssetData (IDataLink* iDataLink, const URI& uri);
	/** CusDtLnkImportLinkConverter using CusDtLnkImportLinkConverter that's aggregated on the old data link boss from this plug-in */
	ErrorCode	ConvertToImportLinkData (IDataLink* iDataLink);
	ErrorCode	DeleteOldStoredObject (IDataLink* iDataLink);
};

CREATE_PMINTERFACE(CusDtLnkNewLinkConverter, kCusDtLnkNewLinkConverterImpl)


//_____________________________________________________________________________________
//	Do conversion
//_____________________________________________________________________________________
ErrorCode CusDtLnkNewLinkConverter::DoConvert
	(
	const UIDRef&	oldLinkRef
	)
{
	if (fDataBase == nil)
	{
		fDataBase = oldLinkRef.GetDataBase ();
	}

	if (fLinkManager == nil)
	{
		fLinkManager = InterfacePtr<ILinkManager> (fDataBase, fDataBase->GetRootUID (), UseDefaultIID ()); 
	}

	ErrorCode	errorCode = kSuccess;

    // Get the associated page item.
	bool bChild(false);
    InterfacePtr<const ILinkObjectReference> pageItemReference(oldLinkRef, UseDefaultIID());
    if (pageItemReference)
    {
        InterfacePtr<const IDataLinkReference> iDataLinkReference(fDataBase, pageItemReference->GetUID(), UseDefaultIID());
        if ( iDataLinkReference && iDataLinkReference->GetUID() != oldLinkRef.GetUID() )
            bChild = true;
   }

	if ( !bChild )
	{
		UID linkUID = _DoConvert(oldLinkRef, false);

		if ( linkUID != kInvalidUID && pageItemReference )
		{
			// convert child links
			InterfacePtr<IDataLinkListReference> iDataLinkListReference(fDataBase, pageItemReference->GetUID(), IID_DATALINKLISTREFERENCE);
			if ( iDataLinkListReference )
			{
				UIDList oldChildList(iDataLinkListReference->GetList());
				UIDList newChildList(fDataBase);
				
				for ( UIDList::reverse_iterator iter = oldChildList.rbegin(); iter != oldChildList.rend(); ++iter )
				{
					UID childUID = _DoConvert(UIDRef(fDataBase, *iter), true);
					if ( childUID != kInvalidUID )
						newChildList.push_back(childUID);

					iDataLinkListReference->RemoveUID(*iter);
				}

				if ( !newChildList.IsEmpty() )
				{
					InterfacePtr<ILink> parentLink(fDataBase, linkUID, UseDefaultIID());
					if ( parentLink )
						parentLink->AddChildren(newChildList);
				}
			}
		} 
	}

    if (pageItemReference)
    {
        InterfacePtr<IDataLinkReference> iDataLinkReference(fDataBase, pageItemReference->GetUID(), UseDefaultIID());
		if ( iDataLinkReference )
			iDataLinkReference->SetUID(kInvalidUID);
	}

	return (errorCode);
}

//_____________________________________________________________________________________
//	Do conversion
//_____________________________________________________________________________________
UID CusDtLnkNewLinkConverter::_DoConvert
	(
	const UIDRef&	oldLinkRef, bool bChild
	)
{
	// if this is not our old data link boss, don't try to convert
	ClassID oldLinkClassID = oldLinkRef.GetDataBase()->GetClass(oldLinkRef.GetUID());
	if ( oldLinkClassID != kCusDtLnkAliasedDataLinkBoss )
		return kInvalidUID;

	ErrorCode	errorCode = kSuccess;

	//	Do all common data conversion first
	InterfacePtr<IDataLink>	iDataLink (oldLinkRef, UseDefaultIID ());
	if ( !iDataLink )
		return kInvalidUID;

	Utils<ICusDtLnkFacade> facade;
	ASSERT(facade);
	if(!facade) {
		return kInvalidUID;
	}
	PMString uniqueKey = facade->RetrieveUniqueKey(iDataLink);
	URI			uri;
	bool bHaveURI = facade->UniqueKeyToURI(uniqueKey, uri);

	if ( !bHaveURI )
		return kInvalidUID;
	

	//	Create link resource
	bool		kDontUseExisting = kFalse;

	UID			linkResourceUID = fLinkManager->CreateResource(uri, kIDLinkClientID, kDontUseExisting);
	ASSERT (linkResourceUID != kInvalidUID);

	//	Create Link object UID
	UID			linkObjectUID = bChild ? kInvalidUID : CreateNewLinkObject (oldLinkRef);
	//ASSERT (bChild || linkObjectUID != kInvalidUID);

	//	Create Link UID
	UID linkUID(kInvalidUID);
	ClassID linkClassID = kImportLinkBoss;
	if ( bChild )
		linkClassID = kChildLinkBoss;

	IDataBase* dataBase(oldLinkRef.GetDataBase());
	errorCode = Utils<Facade::ILinkFacade>()->CreateLink(dataBase, linkClassID, kIDLinkClientID, linkObjectUID, linkResourceUID, true, linkUID);
	ASSERT (linkUID != kInvalidUID);

	//	Convert data
	if (linkUID != kInvalidUID)
	{
		errorCode = ConvertToLinkAssetData (iDataLink, uri);
		if (errorCode == kSuccess)
		{
			InterfacePtr<ILinkResource>	iNewLinkResource (fDataBase, linkResourceUID, UseDefaultIID ());
			errorCode = iNewLinkResource->CopyAttributes (oldLinkRef);

			if (errorCode == kSuccess)
			{
				errorCode = ConvertToImportLinkData (iDataLink);

				InterfacePtr<ILink>	iNewImportLink (fDataBase, linkUID, UseDefaultIID ());
				errorCode = iNewImportLink->CopyAttributes (oldLinkRef);
			}
		}
	}

	// Copy Script Tags/labels
	if ( errorCode == kSuccess )
	{
		InterfacePtr<IScript> oldScript(iDataLink, UseDefaultIID());
		if ( oldScript )
		{
			IScriptLabel::ScriptLabelKeyValueList tags = oldScript->GetTags();
			if ( !tags.empty() )
			{
				InterfacePtr<IScript> newScript(fDataBase, linkUID, UseDefaultIID());
				if ( newScript )
					newScript->SetTags(tags);
			}
		}
	}
		
	//	Next do Custom conversion
	if (errorCode == kSuccess)
	{
		errorCode = DoCustomConversion (oldLinkRef);
		ASSERT_MSG (errorCode == kSuccess, FORMAT_ARGS ("NewLinkConverter::DoConvert, custom conversion failed with error code = %x", errorCode));
	}

	if (errorCode == kSuccess && linkObjectUID != kInvalidUID)
	{
		//	Delete stored UID from private link resource.
		//	CopyAttributes will copy stored UID by creating a new one in the new persist LinkResource.
		errorCode = DeleteOldStoredObject (iDataLink);
	}

	return (linkUID);
}

//_____________________________________________________________________________________
//	Create a link object
//_____________________________________________________________________________________
UID CusDtLnkNewLinkConverter::CreateNewLinkObject
	(
	const UIDRef&	oldLinkRef
	)
{
	InterfacePtr<ILinkObjectReference>	iOldObjectRef (oldLinkRef, UseDefaultIID ());
	if (iOldObjectRef /* && iOldObjectRef->IsDirectReference () */)
	{
		UID			linkObjectUID = iOldObjectRef->GetUID ();
		if (linkObjectUID != kInvalidUID )
		{
			InterfacePtr<ILinkObject> iLinkObject(oldLinkRef.GetDataBase(), linkObjectUID, UseDefaultIID());
			if ( iLinkObject )
			{
				return linkObjectUID;
			}
		}
	}

	return kInvalidUID;
}

//_____________________________________________________________________________________
//	Do custom conversion
//_____________________________________________________________________________________
ErrorCode CusDtLnkNewLinkConverter::DoCustomConversion
	(
	const UIDRef&	oldLinkRef
	)
{
	return kSuccess;
}

//_____________________________________________________________________________________
//	Convert DataLink to LinkResource
//_____________________________________________________________________________________
ErrorCode CusDtLnkNewLinkConverter::ConvertToLinkAssetData
(
	IDataLink*	iDataLink,
	const URI& uri
)
{
	ErrorCode	errorCode = kFailure;

	//	Need cast explicit to the implementation we want!
	InterfacePtr<CusDtLnkLinkAssetConverter>	iCusDtLnkLinkAsset (iDataLink, IID_ILINKRESOURCE);
	ASSERT_MSG (iCusDtLnkLinkAsset != nil, "CusDtLnkNewLinkConverter::ConvertToLinkAssetData, Expecting an ILinkResource for conversion, but not found.");

	if (iCusDtLnkLinkAsset != nil)
	{
		errorCode = iCusDtLnkLinkAsset->Init (iDataLink, uri);
	}


	return (errorCode);

}

//_____________________________________________________________________________________
//	Convert DataLink to ImportLink
//_____________________________________________________________________________________
ErrorCode CusDtLnkNewLinkConverter::ConvertToImportLinkData
(
	IDataLink*	iDataLink
)
{
	ErrorCode	errorCode = kFailure;
	InterfacePtr<CusDtLnkImportLinkConverter>	iCusDtLnkImportLink (iDataLink, IID_ILINK);
	ASSERT_MSG (iCusDtLnkImportLink != nil, "CusDtLnkNewLinkConverter::ConvertToLinkAssetData, Expecting a private ILinkResource for conversion, but not found.");

	if (iCusDtLnkImportLink != nil)
	{
		errorCode = iCusDtLnkImportLink->Init (iDataLink);
	}

	return (errorCode);
}


ErrorCode CusDtLnkNewLinkConverter::DeleteOldStoredObject 
	(
	IDataLink*	iDataLink
	)
{

	InterfacePtr<ILinkObjectReference>	iOldObjectRef (iDataLink, UseDefaultIID ());
	if (iOldObjectRef != nil && iOldObjectRef->GetUID () != kInvalidUID)
	{
		InterfacePtr<IStoreInternal>	iStoreInternal (fDataBase, iOldObjectRef->GetUID (), IID_ISTOREINTERNAL);
		
		//	Delete old stored data
		if ( iStoreInternal )
		{
			UID		storedUID = iStoreInternal->GetStoredUID ();
			if (storedUID != kInvalidUID && fDataBase->IsValidUID (storedUID))
			{
				fDataBase->DeleteUID (storedUID);
				iStoreInternal->SetStoredUID (kInvalidUID);

				//	TODO:	Remove IStoreInternal implementation ID. This removal must be a complete removal.
				//			Need a IPhase2Conversion interfacePtr.
			}
		}
	}

	return kSuccess;
}
