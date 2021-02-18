//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkFacade.cpp $
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

// Interface Includes
#include "IClassIDData.h"
#include "IClassInfo.h"
#include "ICusDtLnkDelimTextReader.h"
#include "ICusDtLnkFacade.h"
#include "ICusDtLnkOptions.h"
#include "IDataLinkHelper.h"
#include "IDataLinkReference.h"
#include "IDocument.h"
#include "IHierarchy.h"
#include "IImageReadFormatInfo.h"
#include "IImportExportFacade.h"
#include "IImportResourceCmdData.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IObjectModel.h"
#include "IPageItemAdornmentList.h"
#include "IPlaceGun.h"
#include "IPMStream.h"
#include "IStringData.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "ILinkUtils.h"
#include "ILinkResource.h"
#include "ILinkManager.h"

// Other API includes
#include "GlobalTime.h"
#include "ImageID.h" // kImage...
#include "K2SmartPtr.h"
#include "NAMEINFO.H"
#include "SDKFileHelper.h"
#include "StreamUtil.h"
#include "TextChar.h"
#include "UIDList.h"
#include "ErrorUtils.h"
#include "Utils.h"
#include "URI.h"

#ifdef DEBUG
#include "DebugClassUtils.h"
#endif
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>

/** CusDtLnkFacade is an implementation of the command facade interface ICusDtLnkFacade.
	@ingroup customdatalink
*/
class CusDtLnkFacade : public CPMUnknown<ICusDtLnkFacade>
{
public:

	/** Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CusDtLnkFacade(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~CusDtLnkFacade() {}

	/** See ICusDtLnkFacade::SetKeyValuePair
	*/
	virtual ErrorCode SetKeyValuePair(const IWorkspace *ws, const PMString& key, const PMString& val, const PMIID& iid=IID_ICUSDTLNKOPTIONS);

	/** See ICusDtLnkFacade::GetValueFromKey */
	virtual PMString GetValueFromKey(const IWorkspace *ws, const PMString& key, const PMIID& iid=IID_ICUSDTLNKOPTIONS) const;

	/** See ICusDtLnkFacade::IsOurCustomDataLink */
	virtual bool16 IsOurCustomDataLink(const ClassID& classID) const;
	virtual bool16 IsOurCustomDataLink(const UIDRef& linkUIDRef) const;

	/** See ICusDtLnkFacade::AddAdornment */
	virtual ErrorCode AddAdornment(const UIDList& itemList);

	/** See ICusDtLnkFacade::RemoveAdornment */
	virtual ErrorCode RemoveAdornment(const UIDList& itemList);

	/** See ICusDtLnkFacade::AddAssetDataBase */
	virtual ErrorCode AddAssetDataBase(const IWorkspace *ws, const PMString& dbName,
									const PMString& fullPath);

	/** See ICusDtLnkFacade::GetNthAssetDataBase */
	virtual PMString GetNthAssetDataBase(const IWorkspace *ws, int32 index) const;

	/** See ICusDtLnkFacade::GetAssetDataBaseCount */
	virtual int32 GetAssetDataBaseCount(const IWorkspace *ws) const;

	/** See ICusDtLnkFacade::GetAssetDataBasePath */
	virtual PMString GetAssetDataBasePath(const IWorkspace *ws, const PMString& dbName) const;

	/** See ICusDtLnkFacade::TruncatePath */
	virtual PMString TruncatePath(const PMString& fullPath,
		bool16 useAnySeparator, const PlatformChar& separator
		) const;

	/** See ICusDtLnkFacade::ImportImageAndLoadPlaceGun */
	virtual UIDRef ImportImageAndLoadPlaceGun(const UIDRef& docUIDRef, 
		const URI& uri);
	virtual UIDRef ImportImageAndLoadPlaceGun(const UIDRef& docUIDRef, 
		const PMString& path, 
		const PMString& uniqueKey);

	/** See ICusDtLnkFacade::GetCurrentlyChosenUniqueAssetKey */
	virtual PMString GetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws) const;

	/** See ICusDtLnkFacade::SetCurrentlyChosenUniqueAssetKey */
	virtual ErrorCode SetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws, const PMString& k);

	/** See ICusDtLnkFacade::InitializeDataLink */
	virtual ErrorCode InitializeDataLink(const IWorkspace *ws, IDataLink *dl,
		const IDFile &file,
		const PMString &formatName,
		const PMString& uniqueAssetKey);
	
	/** See ICusDtLnkFacade::UniqueKeyToURI*/
	virtual bool UniqueKeyToURI(const PMString& uk, URI& uri) const;

	/** See ICusDtLnkFacade::URIToIDFile */
	virtual bool URIToIDFile(const URI& uri, IDFile& file) const;

	/** See ICusDtLnkFacade::GetFirstPartOfPath */
	virtual PMString GetFirstPartOfPath(const PMString& p) const;

	/** See ICusDtLnkFacade::GetLocalFileFromAssetIdentifier */
	virtual IDFile GetLocalFileFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const;

	/** See ICusDtLnkFacade::GetAssetDataBaseRecordFieldValue */
	virtual PMString GetAssetDataBaseRecordFieldValue(const IDFile& databaseFile, const PMString& recordID, const PMString& fieldName) const;

	/** See ICusDtLnkFacade::GetAssetSizeFromAssetIdentifier */
	virtual uint64 GetAssetSizeFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const;

	/** See ICusDtLnkFacade::GetAssetTimestampFromAssetIdentifier */
	virtual uint64 GetAssetTimestampFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const;
	
	/** See ICusDtLnkFacade::GetAssetTimestampFromURI */
	virtual uint64 GetAssetTimestampFromURI(const URI& uri) const;

	/** See ICusDtLnkFacade::GetAssetDescriptionFromAssetIdentifier */
	virtual PMString GetAssetDescriptionFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const;
	
	/** See ICusDtLnkFacade::GetAssetDescriptionFromURI */
	virtual PMString GetAssetDescriptionFromURI(const URI& uri) const;

	/** See ICusDtLnkFacade::GetFieldValueFromAssetIdentifier */
	virtual PMString GetFieldValueFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey,
														  const PMString& fieldName) const;

	/** See ICusDtLnkFacade::StoreUniqueKey */
	virtual void StoreUniqueKey(IDataLink* dataLink, const PMString& uniqueAssetKey);

	/** See ICusDtLnkFacade::RetrieveUniqueKey */
	virtual PMString RetrieveUniqueKey(IDataLink* dataLink) const;
	
	/** See ICusDtLnkFacade::GetRecordFieldValueFromURI */
	PMString GetRecordFieldValueFromURI(const URI& uri, PMString& whichField) const;

	/** See ICusDtLnkFacade::NeedsOurAdornment */
	virtual bool16 NeedsOurAdornment(const UIDRef& pageItemUIDRef) const;

	/** See ICusDtLnkFacade::HasOurAdornment */
	virtual bool16 HasOurAdornment(const UIDRef& pageItemUIDRef) const;

private:
	int32 getOptionsCount(const IWorkspace *ws, const PMIID& pmiid=IID_ICUSDTLNKOPTIONS) const;
	PMString getNthKey(const IWorkspace *ws, int32 index, const PMIID& pmiid=IID_ICUSDTLNKOPTIONS) const;
	void getIntegerTokens(const PMString& inputPmstr,
					const textchar* separatorChar,	  
					K2Vector<int32>& outIntTokens) const;

	uint32 fCreatorID;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CusDtLnkFacade, kCusDtLnkFacadeImpl)



/*
*/
CusDtLnkFacade::CusDtLnkFacade(IPMUnknown* boss) : CPMUnknown<ICusDtLnkFacade>(boss)
, fCreatorID(0)
{
}

/*
*/
ErrorCode CusDtLnkFacade::SetKeyValuePair(const IWorkspace *ws, const PMString& key, const PMString& val,
									const PMIID& pmiid)
{
	ErrorCode retval = kFailure;
	do
	{
		ASSERT(ws);
		if (!ws) {
			break;
		}

		InterfacePtr<ICommand> modOptionsCmd(CmdUtils::CreateCommand(kCusDtLnkChangeOptionsCmdBoss));
		ASSERT(modOptionsCmd);
		if (!modOptionsCmd) {
			break;
		}
		modOptionsCmd->SetCreatorID(fCreatorID++);
		modOptionsCmd->SetItemList(UIDList(ws));
		InterfacePtr<ICusDtLnkOptions> cmdData(modOptionsCmd, UseDefaultIID());
		ASSERT(cmdData);
		if (!cmdData) {
			break;
		}
		cmdData->AddKeyValuePair(WideString(key), WideString(val));
		InterfacePtr<IIntData> pmiidIntData(modOptionsCmd, IID_ICUSDTLNKPMIIDINTDATA);
		ASSERT(pmiidIntData);
		if(!pmiidIntData) {
			break;
		}
		pmiidIntData->Set(pmiid.Get());
		retval = CmdUtils::ProcessCommand(modOptionsCmd);
		ASSERT(retval == kSuccess);

	} while (kFalse);

	return retval;
}


/*
*/
PMString CusDtLnkFacade::GetValueFromKey(const IWorkspace *ws, const PMString& key, const PMIID& pmiid) const
{
	PMString retval;
	do
	{
		ASSERT(ws);
		if (!ws) {
			break;
		}
		InterfacePtr<ICusDtLnkOptions> options(ws, pmiid);
		ASSERT(options);
		if(!options) {
			break;
		}
		retval = options->GetValueFromKey(WideString(key));

	} while (kFalse);

	return retval;
}


/*
*/
static const WideString k_IsOurCustomDataLink_MyScheme(kCusDtLnkScheme);
bool16 CusDtLnkFacade::IsOurCustomDataLink(const UIDRef& linkUIDRef) const 
{
	bool16 retval = kFalse;
	do 
	{
		InterfacePtr<ILink> iLink(linkUIDRef, UseDefaultIID());
		if ( iLink )
		{
			IDataBase *db = linkUIDRef.GetDataBase();
			InterfacePtr<ILinkManager> iLinkManager(db, db->GetRootUID(), UseDefaultIID());
			InterfacePtr<ILinkResource> resource(iLinkManager->QueryResourceByUID(iLink->GetResource()));
			URI uri = resource->GetURI();
			WideString scheme = uri.GetComponent(URI::kScheme);
			if (scheme == k_IsOurCustomDataLink_MyScheme)
				retval = kTrue;
		}
	} while(kFalse);
	return retval;
}


/*
*/
ErrorCode CusDtLnkFacade::AddAdornment(const UIDList& itemList)
{
	ErrorCode status = kFailure;
	do
	{
		// Build a list of items that don't have the adornment.
		UIDList unadornedItemList(itemList.GetDataBase());
		for (int32 i = 0; i < itemList.Length(); i++) {
			InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(itemList.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
			if (pageItemAdornmentList->HasAdornment(kCusDtLnkAdornmentBoss) == kFalse) {
				unadornedItemList.Append(itemList [i]);
			}
		}
		if (unadornedItemList.Length() == 0) {
			// Perhaps all items have our adornment,
			// which counts as a success
			status = kSuccess;
			break;
		}

		// Add the adornment.
		InterfacePtr<ICommand>  addPageItemAdornmentCmd(CmdUtils::CreateCommand(kAddPageItemAdornmentCmdBoss));
		ASSERT(addPageItemAdornmentCmd);
		if (!addPageItemAdornmentCmd) {
			break;
		}
		InterfacePtr<IClassIDData>  classIDData(addPageItemAdornmentCmd, UseDefaultIID());
		ASSERT(classIDData);
		if (!classIDData) {
			break;
		}
		classIDData->Set(kCusDtLnkAdornmentBoss);
		addPageItemAdornmentCmd->SetItemList(unadornedItemList);
		status = CmdUtils::ProcessCommand(addPageItemAdornmentCmd);

	} while (false);
	return status;
}

/*
*/
ErrorCode CusDtLnkFacade::RemoveAdornment(const UIDList& itemList)
{
	ErrorCode status = kFailure;
	do
	{
		// Build a list of items that have the adornment.
		UIDList adorneditemList(itemList.GetDataBase());
		for (int32 i = 0; i < itemList.Length(); i++) {
			InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(itemList.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
			if (pageItemAdornmentList->HasAdornment(kCusDtLnkAdornmentBoss) == kTrue) {
				adorneditemList.Append(itemList [i]);
			}
		}
		if (adorneditemList.Length() == 0) {
			status = kSuccess;
			break;
		}


		// Remove the adornment.
		InterfacePtr<ICommand>  removePageItemAdornmentCmd(CmdUtils::CreateCommand(kRemovePageItemAdornmentCmdBoss));
		ASSERT(removePageItemAdornmentCmd);
		if (!removePageItemAdornmentCmd) {
			break;
		}
		InterfacePtr<IClassIDData>  classIDData(removePageItemAdornmentCmd, UseDefaultIID());
		ASSERT(classIDData);
		if (!classIDData) {
			break;
		}
		classIDData->Set(kCusDtLnkAdornmentBoss);
		removePageItemAdornmentCmd->SetItemList(adorneditemList);
		status = CmdUtils::ProcessCommand(removePageItemAdornmentCmd);


	} while (false);

	return status;
}

/*
*/
ErrorCode CusDtLnkFacade::AddAssetDataBase(const IWorkspace *ws, const PMString& dbName,
									const PMString& fullPath)
{
	return this->SetKeyValuePair(ws, dbName, fullPath, IID_ICUSDTLNKDATABASESASOPTIONS);
}

/*
*/
PMString CusDtLnkFacade::GetNthAssetDataBase(const IWorkspace *ws, int32 index) const
{
	return this->getNthKey(ws, index, IID_ICUSDTLNKDATABASESASOPTIONS);
}

/*
*/
PMString CusDtLnkFacade::getNthKey(const IWorkspace *ws, int32 index, const PMIID& pmiid) const
{
	PMString retval;
	do {
		ASSERT(ws);
		if (!ws) {
			break;
		}
		InterfacePtr<ICusDtLnkOptions> options(ws, pmiid);
		ASSERT(options);
		if(!options) {
			break;
		}
		retval = options->GetNthKey(index);

	} while(kFalse);
	return retval;
}



/*
*/
int32 CusDtLnkFacade::GetAssetDataBaseCount(const IWorkspace *ws) const
{
	return this->getOptionsCount(ws, IID_ICUSDTLNKDATABASESASOPTIONS);
}


/*
*/
int32 CusDtLnkFacade::getOptionsCount(const IWorkspace *ws, const PMIID& pmiid) const
{
	int32 retval = 0;
	do {
		ASSERT(ws);
		if (!ws) {
			break;
		}
		InterfacePtr<ICusDtLnkOptions> options(ws, pmiid);
		ASSERT(options);
		if(!options) {
			break;
		}
		retval = options->GetKeyValuePairCount();
	} while(kFalse);
	return retval;
}

/*
*/
PMString CusDtLnkFacade::GetAssetDataBasePath(const IWorkspace *ws, const PMString& dbName) const
{
	PMString retval;
	if(!dbName.empty()) {
		retval = this->GetValueFromKey(ws, dbName, IID_ICUSDTLNKDATABASESASOPTIONS);
	}
	return retval;
}




/*
*/
PMString CusDtLnkFacade::TruncatePath(const PMString& fromthis,
									  bool16 useAnySeparator,
									  const PlatformChar& useThisOne) const
{
	if(fromthis.empty() == kTrue) return PMString("Empty!");

	PMString retval = fromthis;
	int32 lastpos = (-1);
	for (int32 i = 0 ; i < fromthis.CharCount();i++)
	{
		PlatformChar currentChar = fromthis[i];

		bool16 anyMatched = ((currentChar == kTextChar_ReverseSolidus) ||
				(currentChar == kTextChar_Colon) ||
				(currentChar == kTextChar_Solidus));
		bool16 oneMatched = (currentChar == useThisOne);

		bool16 predicate = (anyMatched && useAnySeparator) ||
								(oneMatched && (!useAnySeparator));

		if (predicate) {
			lastpos = i;
		}
	}

	if(lastpos >= 0)
	{
		// Suppose we have ../X/Y.gif
		// Then, lastpos would be 4, and we'd want 5 chars from 5 onwards
		int32 countChars = fromthis.CharCount() - (lastpos+1);
		int32 startIndex = lastpos+1;
		int32 endIndex = (startIndex + countChars);
		if((endIndex > startIndex) && (endIndex <= fromthis.CharCount()))
		{
			K2::scoped_ptr<PMString> ptrRightStr(fromthis.Substring(startIndex, countChars));
			if(ptrRightStr)
			{
				retval = *ptrRightStr;
			}
		}
	}
	return retval;
}


/*
*/
ErrorCode CusDtLnkFacade::InitializeDataLink(const IWorkspace *ws, 
											 IDataLink *dataLink, 
											 const IDFile &file, 
											 const PMString &formatName,
											const PMString& uniqueAssetKey)
{
	ErrorCode retval = kFailure;
	do {
		ASSERT(dataLink);
		if(!dataLink) {
			break;
		}
		ClassID dataLinkClassID = kCusDtLnkAliasedDataLinkBoss;
			
		//Set the workspace ref of the datalink
		InterfacePtr<IUIDData> iWorkspaceRef(dataLink, IID_IUIDDATA);
		iWorkspaceRef->Set(::GetUIDRef(ws));
									
		uint64 computedSize = this->GetAssetSizeFromAssetIdentifier(ws, uniqueAssetKey);
		uint64 computedTime = this->GetAssetTimestampFromAssetIdentifier(ws, uniqueAssetKey);

		// Is this a real idFile?
		SDKFileHelper fileHelper(file);
		if(fileHelper.IsExisting()) {
			PMString realFilePath = fileHelper.GetPath();
			// Then populate the NameInfo ourselves,
			// but put the path in the NameInfo filename slot
			uint32 filetype=0;
			NameInfo nameInfo;
			nameInfo.Initialize (&realFilePath, nil, 0, dataLinkClassID);

			if (dataLink->SetNameInfo(&nameInfo, (PMString *)&formatName, filetype)) {
				break; // unable to set the name
			}
			dataLink->SetStoredState(&computedSize, &computedTime, IDataLink::kLinkNormal);
			this->StoreUniqueKey(dataLink, uniqueAssetKey);
			retval = kSuccess;
		} else 
		if(uniqueAssetKey.CharCount()>0) {

			// Then populate the NameInfo ourselves
			// and put the unique asset key in the NameInfo slot (for now)
			uint32 filetype=0;
			NameInfo nameInfo;
			PMString pretendyFilename(uniqueAssetKey);
			nameInfo.Initialize (&pretendyFilename, nil, 0, dataLinkClassID);

			if (dataLink->SetNameInfo(&nameInfo, (PMString *)&formatName, filetype)) {
				break; // unable to set the name
			}
			dataLink->SetStoredState(&computedSize, &computedTime, IDataLink::kLinkNormal);

			
			this->StoreUniqueKey(dataLink, uniqueAssetKey);
			retval = kSuccess;
		}

		else {
			// Create a kDataLinkHelperBoss utility.
			InterfacePtr<IDataLinkHelper> dataLinkHelper(::CreateObject2<IDataLinkHelper>(kDataLinkHelperBoss));
			ASSERT(dataLinkHelper);
			if(!dataLinkHelper) {
				break;
			}
			// Total fallback
			PMString localFormatName(formatName);
			// Fallback: no asset key, just a reg file-based link
			retval  = dataLinkHelper->InitializeDataLink(dataLink, 
				file, 
				&localFormatName );
		}
	} while(kFalse);
	return retval;
}

/*
*/
UIDRef CusDtLnkFacade::ImportImageAndLoadPlaceGun(
	const UIDRef& docUIDRef, const PMString& fromPath, const PMString& uniqueKey)
{
	// Precondition: active document
	// Precondition: file exists
	//
	UIDRef retval = UIDRef::gNull;
	do
	{
		SDKFileHelper fileHelper(fromPath);
		bool16 fileExists = fileHelper.IsExisting();
		if(!fileExists) {
			break;
		}
		InterfacePtr<IDocument>
			iDocument(docUIDRef, UseDefaultIID());
		ASSERT(iDocument);
		if(!iDocument)
		{
			break;
		}

		// Wrap the import in a command sequence.
		PMString seqName("Import");
		CmdUtils::SequenceContext seq(&seqName);

		// If the place gun is already loaded abort it so we can re-load it.
		InterfacePtr<IPlaceGun> placeGun(iDocument, UseDefaultIID());
		ASSERT(placeGun);
		if (!placeGun)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		if (Utils<Facade::IImportExportFacade>()->AbortPlaceGun( placeGun, Facade::IImportExportFacade::kAllItems ) != kSuccess)
		{
			ASSERT_FAIL("AbortPlaceGun failed");
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}

		// Now import the selected file and load it's UID into the place gun.
		IDataBase* db = docUIDRef.GetDataBase();
		ASSERT(db);
		if(!db)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		Utils<ICusDtLnkFacade> facade;
		if(!facade) {
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		InterfacePtr<IDataLink> tempDataLink(
				::CreateObject2<IDataLink>(kCusDtLnkAliasedDataLinkBoss) );
		if (!tempDataLink) {
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		PMString formatName;

		InterfacePtr<IWorkspace> ws(iDocument->GetDocWorkSpace(),IID_IWORKSPACE);
		ErrorCode err = facade->InitializeDataLink(ws, tempDataLink,
												fileHelper.GetIDFile(),
												formatName,
												uniqueKey);
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}

		UID linkResourceUID = kInvalidUID ; //TODO (#2354741): ConvertToLinkResource( tempDataLink ) ;
		const bool16 retainFormat = kFalse ;
		const bool16 convertQuotes = kFalse ;
		const bool16 applyCJKGrid = kFalse ;
		bool16 useClippingFrame, skipPlace ;
		err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, linkResourceUID, kMinimalUI, 
			retainFormat, convertQuotes, applyCJKGrid, useClippingFrame, skipPlace ) ;
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}
		// Get the contents of the place gun as our return value
		UIDRef placedItem(db, placeGun->GetFirstPlaceGunItemUID());
		retval = placedItem;
	} while(kFalse);

	return retval;
}

/*
*/
PMString CusDtLnkFacade::GetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws) const
{
	return this->GetValueFromKey(ws, kCusDtLnkCurrentlyChosenUniqueKeyOption);
}

/*
*/
ErrorCode CusDtLnkFacade::SetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws, const PMString& k)
{
	TRACEFLOW(kCusDtLnkPluginName,
		"CusDtLnkFacade::SetCurrentlyChosenUniqueAssetKey with <%s>\n", k.GetPlatformString().c_str());
	ASSERT(k.IndexOfWChar(kTextChar_Colon) < 0);
	ErrorCode ret =  this->SetKeyValuePair(ws, kCusDtLnkCurrentlyChosenUniqueKeyOption, k);
	return ret;

}

/* 
*/
bool CusDtLnkFacade::UniqueKeyToURI(const PMString& uk, URI& uri) const
{	
	InterfacePtr<IWorkspace> appWorkspace(GetExecutionContextSession()->QueryWorkspace());
	// The database name is the first part
	PMString databaseName = this->GetFirstPartOfPath(uk);
	// The record ID is the last part
	PMString recordID = this->TruncatePath(uk, kTrue, kTextChar_Solidus); // last arg irrelv here
	PMString fullPathToAssetDataBase = this->GetAssetDataBasePath(appWorkspace, databaseName);
	if(fullPathToAssetDataBase.empty() || recordID.empty())
		return false;

	uri.SetComponent(URI::kScheme, WideString(kCusDtLnkScheme));
	uri.SetComponent(URI::kPath, WideString(fullPathToAssetDataBase));
	uri.SetComponent(URI::kQuery, WideString(recordID));
	return true;
}

/* 
*/
static const WideString k_URIToIDFile_MyScheme(kCusDtLnkScheme);
bool CusDtLnkFacade::URIToIDFile(const URI& uri, IDFile& file) const
{
	WideString scheme = uri.GetComponent(URI::kScheme);
	if (scheme != k_URIToIDFile_MyScheme) {
		return false;
	}
	// our uri has the following format:
	// CusDtLnk://database_fulloath?recordID
	// first get the database path from the uri, create a file helper from the path
	WideString dbPath = uri.GetComponent(URI::kPath);
	PMString path(dbPath);
	SDKFileHelper dbFileHelper(path);
	if (!dbFileHelper.IsExisting())
		return false;
	// then get the record id from the uri
	WideString recordID = uri.GetComponent(URI::kQuery);
	PMString assetFieldName(kCusDtLnkAssetDataBaseAssetPathFieldNameKey, PMString::kTranslateDuringCall);
	// get the asset name from the database based on the unique record id
	PMString assetName = GetAssetDataBaseRecordFieldValue(dbFileHelper.GetIDFile(), PMString(recordID), assetFieldName);

//	PMString assetFieldName(kCusDtLnkAssetDataBaseAssetPathFieldNameKey, PMString::kTranslateDuringCall);
//	PMString assetName = this->GetRecordFieldValueFromURI(uri, assetFieldName);
	if (assetName.empty())
		return false;
	// asset is located in the same directory as the database
	file = dbFileHelper.GetAbsoluteFromRelative(assetName);
	bool bFileExists(file.Exists());
	
	return bFileExists;
}

/* 
*/
static const WideString k_GetRecordFieldValueFromURI_MyScheme(kCusDtLnkScheme);
PMString CusDtLnkFacade::GetRecordFieldValueFromURI(const URI& uri, PMString& whichField) const
{
	PMString	retStr("");

	WideString scheme = uri.GetComponent(URI::kScheme);
	if (scheme != k_GetRecordFieldValueFromURI_MyScheme) {
		return retStr;
	}
	// our uri has the following format:
	// CusDtLnk://database_fulloath?recordID
	// first get the database path from the uri, create a file helper from the path
	WideString dbPath = uri.GetComponent(URI::kPath);
	PMString path(dbPath);
	SDKFileHelper dbFileHelper(path);
	ASSERT(dbFileHelper.IsExisting());
	if (!dbFileHelper.IsExisting())
		return retStr;
	// then get the record id from the uri
	WideString recordID = uri.GetComponent(URI::kQuery);
	// get the asset name from the database based on the unique record id
	PMString fieldValue = GetAssetDataBaseRecordFieldValue(dbFileHelper.GetIDFile(), PMString(recordID), whichField);
	
	return fieldValue;
}

/*
*/
PMString CusDtLnkFacade::GetFirstPartOfPath(const PMString& fromthis) const
{
	if(fromthis.empty()) {
		return PMString("Empty!");
	}

	PMString retval = fromthis;

	CharCounter p1 = fromthis.IndexOfCharacter(kTextChar_ReverseSolidus);
	CharCounter p2 = fromthis.IndexOfCharacter(kTextChar_Colon);
	CharCounter p3 = fromthis.IndexOfCharacter(kTextChar_Solidus);

	// Get non-zero if any pos
	CharCounter sepPos = (p1 >= 0) ? p1 : (p2 >= 0 ? p2 : p3);
	// Has to be > 0 to take -1
	if(sepPos > 0)
	{
		// If you have e.g. abc/def, then the separator
		// would be at index = 3, and you'd want first 3 chars,
		// i.e. substring from 0 and take sepPos chars
		K2::scoped_ptr<PMString> ptrLeftStr(
			fromthis.Substring(0, sepPos));
		if(ptrLeftStr) {
			retval = *ptrLeftStr;
		}
	}

	return retval;
}

/*
*/
PMString CusDtLnkFacade::GetAssetDataBaseRecordFieldValue(const IDFile& databaseFile,
														  const PMString& recordID,
														  const PMString& fieldName) const
{
	PMString retval;
	do {
		// Preconditions
		SDKFileHelper fileHelper(databaseFile);
		bool16 preconditions = fileHelper.IsExisting() &&
									(!recordID.empty()) &&
										(!fieldName.empty());
		ASSERT(preconditions);
		if(!preconditions) {
			break;
		}

		// Load the database
		InterfacePtr<ICusDtLnkDelimTextReader> reader(CreateObject2<ICusDtLnkDelimTextReader>(kCusDtLnkDelimTextReaderBoss));
		ASSERT(reader);
		if(!reader) {
			break;
		}

		// Open stream onto database path


		InterfacePtr<IPMStream> stream( StreamUtil::CreateFileStreamRead(databaseFile));
		ASSERT(stream);
		if(!stream) {
			break;
		}
		if(!reader->CanRead(stream)) {
			stream->Close();
			break;
		}
		K2Vector<PMString> names;
		bool16 couldReadNames = reader->ReadRecord(stream, names);
		ASSERT(couldReadNames);
		if(!couldReadNames) {
			stream->Close();
			break;
		}
		ASSERT(names.size()>0);

		if(names.size() == 0) {
			stream->Close();
			break;
		}


		while (stream->GetStreamState() == kStreamStateGood) {
			K2Vector<PMString> fields;
			bool16 couldReadRec = reader->ReadRecord(stream, fields);
			bool16 foundDataOnThisRow = (couldReadRec && fields.size()>1);
			if(!foundDataOnThisRow) {
				continue;
			}
			PMString currentRecordID;

			K2Vector<PMString>::const_iterator iterNames = names.begin();
			K2Vector<PMString>::const_iterator iterVals = fields.begin();
			std::map<PMString, PMString> fieldValueMap;
			for( ; iterNames != names.end() && iterVals != fields.end();
								iterNames++, iterVals++) {
				PMString name = *iterNames;
				PMString val = *iterVals;
				fieldValueMap.insert(std::pair<PMString,PMString>(name,val));
			} // Store vals in map for quick perusal

			PMString recordIdentifierFieldName(kCusDtLnkAssetDataBaseRecordIDFieldNameKey, PMString::kTranslateDuringCall);


			std::map<PMString, PMString>::const_iterator
					findRecIDInMapResult =
						fieldValueMap.find(recordIdentifierFieldName);
			ASSERT(findRecIDInMapResult != fieldValueMap.end());
			if( findRecIDInMapResult == fieldValueMap.end()) {
				break;
			}
			PMString currentRecordIDValue = findRecIDInMapResult->second;
			if( recordID.Compare(kFalse, currentRecordIDValue) == 0) {
				// Then we found matching
				// So look for the fieldName we're after and get val
				std::map<PMString, PMString>::const_iterator
					findChosenFieldInMapResult =
						fieldValueMap.find(fieldName);
				ASSERT(findChosenFieldInMapResult != fieldValueMap.end());
				if(findChosenFieldInMapResult == fieldValueMap.end()) {
					break;
				}
				// break out of while look, we found what we're after
				retval = findChosenFieldInMapResult->second;
				break;
			}

		} // while we could read the stream

		// Tidy up stream
		stream->Close();

	} while(kFalse);
	return retval;
}

/*
*/
PMString CusDtLnkFacade::GetAssetDescriptionFromURI(const URI& uri) const
{

	PMString descFieldName(kCusDtLnkAssetDataBaseDescriptionFieldNameKey, PMString::kTranslateDuringCall);

	return this->GetRecordFieldValueFromURI(uri, descFieldName);
	
}

/*
*/
uint64 CusDtLnkFacade::GetAssetTimestampFromURI(const URI& uri) const
{
	PMString dateFieldName(kCusDtLnkAssetDataBaseDateFieldNameKey, PMString::kTranslateDuringCall);

	PMString timeFieldName(kCusDtLnkAssetDataBaseTimeFieldNameKey, PMString::kTranslateDuringCall);

	PMString strDate = this->GetRecordFieldValueFromURI(uri, dateFieldName);
	PMString strTime = this->GetRecordFieldValueFromURI(uri, timeFieldName);

	// Assume time is represented:
	// yyyy-mm-dd hh:mm:ss, like the JDBC timestamp escape format
	// See http://java.sun.com/j2se/1.5.0/docs/api/java/sql/Timestamp.html#valueOf(java.lang.String)
	K2Vector<int32> dateTokens;
	K2Vector<int32> timeTokens;
	textchar dateSeparator[2] = {'-', kTextChar_Null};
	textchar timeSeparator[2] = {':', kTextChar_Null};
	this->getIntegerTokens(strDate, dateSeparator, dateTokens);
	this->getIntegerTokens(strTime, timeSeparator, timeTokens);
	GlobalTime localGlobalTime;
	if(dateTokens.size() > 2 &&  timeTokens.size() > 2) {
		localGlobalTime.SetTime(dateTokens[0], dateTokens[1], dateTokens[2],
								timeTokens[0], timeTokens[1], timeTokens[2]);
	} else {
		// January 1, 1970, 00:00:00 
		localGlobalTime.SetTime(1970,1,1,0,0,0);
	}
	return localGlobalTime.GetTime();
}

/*
*/
void CusDtLnkFacade::getIntegerTokens(const PMString& inputPmstr,
							   const textchar* separatorChar, 
							   K2Vector<int32>& outIntTokens) const
{
	/** Defines type that a boost::tokenizer can act on */
	typedef std::basic_string<UTF16TextChar, std::char_traits<UTF16TextChar>, std::allocator<UTF16TextChar> > mystring16;
	/** Define specific type to tokenize something close to WideString */
	typedef boost::tokenizer<boost::char_separator<UTF16TextChar>, mystring16::const_iterator, mystring16> mytokenizer;
	boost::char_separator<UTF16TextChar> sep(separatorChar);
	mystring16 instr(inputPmstr.GrabUTF16Buffer(nil));
	mytokenizer tokens(instr, sep);

	for (mytokenizer::iterator tok_iter = tokens.begin();
		tok_iter != tokens.end(); ++tok_iter) {
			mystring16 stok(*tok_iter);
			PMString pms;
			pms.SetXString(stok.c_str(), static_cast<int32>(stok.length()));
			PMString::ConversionError convError;
			TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkFacade::getIntegerTokens val = %s\n", pms.GetPlatformString().c_str());
			int32 convertedVal = pms.GetAsNumber(&convError);
			if (convError == PMString::kNoError) {
				outIntTokens.push_back(convertedVal);
			} else {
				outIntTokens.clear();
				// malformed... not integer tokens
				return; 
			}
	  }
}

/*
*/
static const WideString k_NeedsOurAdornment_MyScheme(kCusDtLnkScheme);
bool16 CusDtLnkFacade::NeedsOurAdornment(const UIDRef& pageItemUIDRef) const
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkFacade::NeedsOurAdornment\n");
	bool16 retval = kFalse;
	do {
		UID linkUID = Utils<ILinkUtils>()->FindLink(pageItemUIDRef);
		if (linkUID != kInvalidUID)
		{
			UID resourceUID = Utils<ILinkUtils>()->FindLinkResource(pageItemUIDRef);
			InterfacePtr<ILinkResource> iLnkRsrc(pageItemUIDRef.GetDataBase(), resourceUID, UseDefaultIID());
			URI uri = iLnkRsrc->GetURI();
			WideString scheme = uri.GetComponent(URI::kScheme);
			if (scheme == k_NeedsOurAdornment_MyScheme)
				retval = kTrue;
		}
	} while(kFalse);
	return retval;
}

bool16 CusDtLnkFacade::HasOurAdornment(const UIDRef& pageItemUIDRef) const
{
	bool16 retval = kFalse;
	do
	{
		InterfacePtr<IPageItemAdornmentList> pageItemAdornmentList(pageItemUIDRef, IID_IPAGEITEMADORNMENTLIST);
		if(!pageItemAdornmentList) {
			break;
		}
		retval =  (pageItemAdornmentList->HasAdornment(kCusDtLnkAdornmentBoss) == kTrue) ;

	} while (kFalse);

	return retval;

}


/*
*/
bool16 CusDtLnkFacade::IsOurCustomDataLink(const ClassID& classID) const 
{
	bool16 retval = kFalse;
	do {

		InterfacePtr <IObjectModel> objectModel(GetExecutionContextSession(), UseDefaultIID());//IID_IOBJECTMODEL);
		ASSERT(objectModel);
		if(!objectModel) {
			break;
		}
		InterfacePtr<IClassInfo> classInfo(objectModel->QueryClassInfo(classID));
		ASSERT(classInfo);
		if(!classInfo) {
			break;
		}
		// Criterion: it should support our 'marker' bool data interface, which
		// we added just to indicate it's one of ours
		retval = ((classInfo->GetImplementation(IID_ICUSDTLNKDATALINKBOOLDATA)) != kInvalidImpl);
	} while(kFalse);
	return retval;
}


/*
*/
UIDRef CusDtLnkFacade::ImportImageAndLoadPlaceGun(
	const UIDRef& docUIDRef, const URI& uri)
{
	// Precondition: active document
	// Precondition: file exists
	// 
	UIDRef retval = UIDRef::gNull;
	do
	{
		InterfacePtr<IDocument> 
			iDocument(docUIDRef, UseDefaultIID());
		ASSERT(iDocument);
		if(!iDocument)
		{
			break;
		}

		// Wrap the import in a command sequence.
		PMString seqName("Import");
		CmdUtils::SequenceContext seq(&seqName);

		// If the place gun is already loaded abort it so we can re-load it. 
		InterfacePtr<IPlaceGun> placeGun(iDocument, UseDefaultIID());
		ASSERT(placeGun);
		if (!placeGun) 
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		if (Utils<Facade::IImportExportFacade>()->AbortPlaceGun( placeGun, Facade::IImportExportFacade::kAllItems ) != kSuccess) 
		{
			ASSERT_FAIL("AbortPlaceGun failed");
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}

		// Now import the selected file and load it's UID into the place gun.
		IDataBase* db = docUIDRef.GetDataBase();
		ASSERT(db);
		if(!db)
		{
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}

		const bool16 retainFormat = kFalse ;
		const bool16 convertQuotes = kFalse ;
		const bool16 applyCJKGrid = kFalse ;
		bool16 useClippingFrame, skipPlace ;
		ErrorCode err = Utils<Facade::IImportExportFacade>()->ImportAndLoadPlaceGun(db, uri, kMinimalUI, 
			retainFormat, convertQuotes, applyCJKGrid, useClippingFrame, skipPlace ) ;
		ASSERT(err == kSuccess);
		if(err != kSuccess) {
			break;
		}	
		// Get the contents of the place gun as our return value
		UIDRef placedItem(db, placeGun->GetFirstPlaceGunItemUID());
		retval = placedItem; 
	} while(kFalse);

	return retval;
}


/*
*/
IDFile CusDtLnkFacade::GetLocalFileFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const
{
	TRACEFLOW(kCusDtLnkPluginName, 
		"CusDtLnkFacade::GetLocalFileFromAssetIdentifier:: %s\n",
			uniqueAssetKey.GetPlatformString().c_str()); 
	
	IDFile retval;
	do {
		// "asset-path"
		PMString assetFieldName(kCusDtLnkAssetDataBaseAssetPathFieldNameKey, PMString::kTranslateDuringCall);
		PMString assetVal  = this->GetFieldValueFromAssetIdentifier(ws, uniqueAssetKey, assetFieldName);
		if(assetVal.empty()) {
			break;
		}
		// Now to find the asset, it is a relative path from the database
		// The database name is the first part
		PMString databaseName = this->GetFirstPartOfPath(uniqueAssetKey);
		PMString fullPathToAssetDataBase = this->GetAssetDataBasePath(ws, databaseName);
		SDKFileHelper dbFileHelper(fullPathToAssetDataBase);
		//ASSERT(dbFileHelper.IsExisting());
		if(!dbFileHelper.IsExisting()) {
			// Can't find DB
			break;
		}

		retval = dbFileHelper.GetAbsoluteFromRelative(assetVal);

	} while(kFalse);

	return retval;

}


/*
*/
uint64 CusDtLnkFacade::GetAssetSizeFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const
{
	uint64 retval = 65536;
	// Perhaps this would be in a field in the database, I'm
	// not considering it for this example
	return retval;
}

/*
*/
PMString CusDtLnkFacade::GetAssetDescriptionFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const
{

	PMString descFieldName(kCusDtLnkAssetDataBaseDescriptionFieldNameKey, PMString::kTranslateDuringCall);

	return this->GetFieldValueFromAssetIdentifier(ws, uniqueAssetKey, descFieldName);

}

/*
*/
uint64 CusDtLnkFacade::GetAssetTimestampFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const
{
	PMString dateFieldName(kCusDtLnkAssetDataBaseDateFieldNameKey, PMString::kTranslateDuringCall);

	PMString timeFieldName(kCusDtLnkAssetDataBaseTimeFieldNameKey, PMString::kTranslateDuringCall);

	PMString strDate = this->GetFieldValueFromAssetIdentifier(ws, uniqueAssetKey, dateFieldName);
	PMString strTime = this->GetFieldValueFromAssetIdentifier(ws, uniqueAssetKey, timeFieldName);

	// Assume time is represented:
	// yyyy-mm-dd hh:mm:ss, like the JDBC timestamp escape format
	// See http://java.sun.com/j2se/1.5.0/docs/api/java/sql/Timestamp.html#valueOf(java.lang.String)
	K2Vector<int32> dateTokens;
	K2Vector<int32> timeTokens;

	textchar dateSeparator[2] = {'-', kTextChar_Null};
	textchar timeSeparator[2] = {':', kTextChar_Null};
	this->getIntegerTokens(strDate, dateSeparator, dateTokens);
	this->getIntegerTokens(strTime, timeSeparator, timeTokens);	
	GlobalTime localGlobalTime;
	if(dateTokens.size() > 2 &&  timeTokens.size() > 2) {
		localGlobalTime.SetTime(dateTokens[0], dateTokens[1], dateTokens[2],
								timeTokens[0], timeTokens[1], timeTokens[2]);
	} else {
		// January 1, 1970, 00:00:00
		localGlobalTime.SetTime(1970,1,1,0,0,0);
	}
	return localGlobalTime.GetTime();
}

/*
*/
PMString CusDtLnkFacade::GetFieldValueFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey,
														  const PMString& fieldName) const
{
	TRACEFLOW(kCusDtLnkPluginName,
		"CusDtLnkFacade::GetFieldValueFromAssetIdentifier:: %s, field %s\n",
			uniqueAssetKey.GetPlatformString().c_str(), fieldName.GetPlatformString().c_str());

	PMString retval;
	do {

		// The database name is the first part
		PMString databaseName = this->GetFirstPartOfPath(uniqueAssetKey);
		// The record ID is the last part
		PMString recordID = this->TruncatePath(uniqueAssetKey,
												kTrue,
												kTextChar_Solidus); // last arg irrelv here
		PMString fullPathToAssetDataBase = this->GetAssetDataBasePath(ws, databaseName);
		if(fullPathToAssetDataBase.empty()) {
			break;
		}
		SDKFileHelper dbFileHelper(fullPathToAssetDataBase);
		//ASSERT(dbFileHelper.IsExisting());
		if(!dbFileHelper.IsExisting()) {
			// Can't find DB, though we found some path
			break;
		}
		retval = this->GetAssetDataBaseRecordFieldValue(dbFileHelper.GetIDFile(),
														recordID,
														fieldName);

	} while(kFalse);

	return retval;

}


/*
*/
void CusDtLnkFacade::StoreUniqueKey(IDataLink* dataLink, const PMString& uniqueAssetKey)
{
	do {
		bool16 ourType = this->IsOurCustomDataLink(::GetClass(dataLink));
		ASSERT(ourType);
		if(!ourType) {
			break;
		}


		InterfacePtr<IStringData> uniqueKeyStringData(dataLink, IID_ICUSDTLNKUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStringData);
		if(!uniqueKeyStringData) {
			break;
		}

		TRACEFLOW(kCusDtLnkPluginName,
			"CusDtLnkFacade::StoreUniqueKey(),state is <%s>.\n",
			this->RetrieveUniqueKey(dataLink).GetPlatformString().c_str());
		TRACEFLOW(kCusDtLnkPluginName,
			"CusDtLnkFacade::StoreUniqueKey(),is storing <%s>.\n",
			uniqueAssetKey.GetPlatformString().c_str());

		uniqueKeyStringData->Set(uniqueAssetKey);
	} while(kFalse);
}


/*
*/
PMString CusDtLnkFacade::RetrieveUniqueKey(IDataLink* dataLink) const
{
	PMString retval;
	do {
		bool16 ourType = this->IsOurCustomDataLink(::GetClass(dataLink));
		ASSERT(ourType);
		if(!ourType) {
			break;
		}

		InterfacePtr<IStringData> uniqueKeyStringData(dataLink, IID_ICUSDTLNKUNIQUEKEYSTRINGDATA);
		ASSERT(uniqueKeyStringData);
		if(!uniqueKeyStringData) {
			break;
		}
		retval = uniqueKeyStringData->GetString();
	} while(kFalse);
	return retval;
}

// End, CusDtLnkFacade.cpp.
