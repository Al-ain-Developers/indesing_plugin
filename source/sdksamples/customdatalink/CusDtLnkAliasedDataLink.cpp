//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkAliasedDataLink.cpp $
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
#include "ICoreFilename.h"
#include "ICusDtLnkFacade.h"
#include "IDatalink.h"
#include "IPMStream.h"
#include "IWorkspace.h"
#include "IUIDData.h"

// Imp includes
#include "CPMUnknown.h"
#include "NAMEINFO.H"
#include "SDKFileHelper.h"
#include "StreamUtil.h"
#include "Utils.h"


// Project includes
#include "CusDtLnkID.h"

//#define CUSDTLNK_DUMP_GETS
#define CUSTDTLNK_IS_VERBOSE

/** Implements IDataLink, but with a twist. Instead of storing a path to a file
	in the local filesystem, what we are working is a unique identifier, consisting
	of a database name plus a record ID within that database.

	The database is a symbolic name rather than a path. Other machinery is used to
	resolve a symbolic name to a "connection" to let you read the data.

	The identifier would look something like this:
	"alias-database-1.csv/1000141"
	
	In practice, we store it in an IStringData interface with an 
	exotic identifier of IID_ICUSDTLNKUNIQUEKEYSTRINGDATA.

	@see CusDtLnkFacade::StoreUniqueKey
	@ingroup customdatalink

*/
class CusDtLnkAliasedDataLink : public CPMUnknown<IDataLink>
{
public:
	/** Constructor */
	CusDtLnkAliasedDataLink(IPMUnknown*);
	/** Destructor */
	virtual ~CusDtLnkAliasedDataLink();


	/** @see IDataLink::Combine
	*/
	virtual int32 Combine(NameInfo *dirname, NameInfo *newname);

	/** @see IDataLink::CompareBaseName */
	virtual bool16 CompareBaseName(NameInfo *ni);

	/** @see IDataLink::CompareDirectory */
	virtual bool16 CompareDirectory(NameInfo *ni);

	/** @see IDataLink::Copy */
	virtual int32 Copy(NameInfo *dirname, ProgressParam *pp);

	/** @see IDataLink::CreateTestFile */
	virtual IDataLink *CreateTestFile(NameInfo *ni, PMString *formatName, uint32 filetype);

	/** @see IDataLink::DeleteTestFile */
	virtual void DeleteTestFile(NameInfo *ni);
	
	/** @see IDataLink::FindRelative */
	virtual bool16 FindRelative(NameInfo *dirname, NameInfo *newname, ProgressParam *pp);


	/** @see IDataLink::GetBaseName */
	virtual PMString *GetBaseName();

	/** @see IDataLink::GetCurrentState */
	virtual StateType GetCurrentState(NameInfo *ni, uint64 *size, uint64 *time, uint32 *filetype, ProgressParam *pp);

	/** @see IDataLink::GetFullName */
	virtual PMString *GetFullName();
	
	/** @see IDataLink::GetNameInfo */
	virtual int32 GetNameInfo(NameInfo *ni, PMString *formatName, uint32 *filetype);

	/** @see IDataLink::GetStoredState */
	virtual StateType GetStoredState(uint64 *size, uint64 *time);

	/** @see IDataLink::GetTestName */
	virtual int32 GetTestName(PMString *dirname, PMString *basename, NameInfo *pni);


	/** @see IDataLink::SetNameInfo */
	virtual int32 SetNameInfo(NameInfo *ni, PMString *formatName, uint32 filetype, const PMString *fullPath = nil);

	/** @see IDataLink::SetStoredState */
	virtual int32 SetStoredState(uint64 *size, uint64 *time, StateType state);

	/** Persistence-related method */ 
	void ReadWrite(IPMStream *s, ImplementationID prop);

protected:
	/** Debug helper to dump state when required, only creates trace when
		CUSTDTLNK_IS_VERBOSE is defined
	*/
	void dumpStateOfThis();


	/**	Method to compare two timestamps. If the supplied one (currentTimeStamp)
		is more recent than storedTimeStamp, then we return 'kFalse', which means
		that we need to update this link

		@param storedTimeStamp what we're storing here
		@param currentTimeStamp what we're comparing against
		@return bool16 kTrue if the timestamps are identical, and kFalse if the
			one we store is out of date relative to supplied one
	 */
	bool16 compareTimeStamps(uint64 storedTimeStamp, 
		uint64 currentTimeStamp);

	/**	Helper to write/read a 64-bit int to stream
		@param s stream to write to/ read from
		@param value the 64-bit integer to write or read
		@return uint64 giving the value written/read
	 */
	uint64 localXferInt64(IPMStream *s, uint64 &value);
	
private:
	
	/** Size of the asset as far as database is concerned */
	uint64 fSize;		
	/** Timestamp (inc date) as far as database is concerned */
	uint64 fTime;		
	/** State of the link last time it was checked. If OK, kLinkNormal */
	IDataLink::StateType fState; 

	/** Name of format for asset */
	PMString fFormatName;

	/** File type for the asset */
	uint32 fFileType;

	/** Path to replica in the local file system */
	PMString fLongLocReplicaFilename;
	// End persistent instance vars

	/** Short name for the linked asset (not persisted) */
	PMString fShortNameForAsset; 
	/** Longer description that appears in the Links Information dialog (not persisted) */
	PMString fFullDescriptor; 
};


CREATE_PERSIST_PMINTERFACE(CusDtLnkAliasedDataLink, kCusDtLnkAliasedDataLinkImpl)


/* Constructor
*/
CusDtLnkAliasedDataLink::CusDtLnkAliasedDataLink(IPMUnknown *boss) :
	CPMUnknown<IDataLink>(boss)
{
	fSize=0;
	fTime=0;
	fFileType = 'TEXT';
}

/*
*/
CusDtLnkAliasedDataLink::~CusDtLnkAliasedDataLink()
{
}

/*
*/
int32 CusDtLnkAliasedDataLink::Combine(NameInfo *dirname, NameInfo *newname)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::Combine() +\n");
	this->dumpStateOfThis();

	// "Creates new name information for a link by combining the 
	// current link's basename with the directory specified by the dirname parameter. 
	// Combine is used by the find missing command to look for missing links 
	// in other directories."
	do {
		bool16 preconditions = ((dirname != nil) && (newname != nil));
		ASSERT(preconditions);
		if(!preconditions) {
			break;
		}
		ASSERT(dirname->GetFilename());
		if(!(dirname->GetFilename())) {
			break;
		}
		PMString firstAssetID = *(dirname->GetFilename());
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		PMString secondAssetID = facade->RetrieveUniqueKey(this);
		
		PMString firstDB = facade->GetFirstPartOfPath(firstAssetID);
		PMString secondRec= facade->TruncatePath(secondAssetID);
		// For our custom implementation, we make a new unique key
		// by combining database name 1 with the recordID of name 2
		// This may not make sense in our simple implementation but it
		// reflects the semantics for this method
		PMString newAssetID(firstDB);
		newAssetID.Append(kTextChar_Solidus);
		newAssetID += secondRec;
		ClassID dataLinkClassID = ::GetClass(this);
		newname->Initialize (&newAssetID, nil, 0, dataLinkClassID);
		return 0; // 0=success
	} while(kFalse);

	return 1; // failure;
}



/*
*/
int32 CusDtLnkAliasedDataLink::Copy(NameInfo *dirname, ProgressParam *pp)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::Copy() +\n");
	this->dumpStateOfThis();
	int32 retval = 1; //failure
	do {
		// There is a bug that prevents this being called e.g. on Links Panel > Copy
		// when you expect (Watson #1172988)
		bool16 preconditions = (dirname != nil);
		ASSERT(preconditions);
		if(!preconditions) {
			break;
		}
		// Copy local replica to specified place
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}

		UIDRef  wsRef;
		IDataBase* db = ::GetDataBase(this);
		//The database may be NIL if the datalink is temporary created)
		if (db)
		{
			InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
			wsRef = doc->GetDocWorkSpace();
		}
		else
		{
			InterfacePtr<IUIDData> iWorkspaceRef(this, IID_IUIDDATA);
			wsRef = iWorkspaceRef->GetRef();
		}

		InterfacePtr<IWorkspace> ws(wsRef , UseDefaultIID());

		IDFile replicaFile = 
			facade->GetLocalFileFromAssetIdentifier(ws, facade->RetrieveUniqueKey(this));
		SDKFileHelper repHelper(replicaFile);
		if(!repHelper.IsExisting()) {
			break;
		}
		// Cheap implementation is to reuse the ICoreFilename 
		// implementation to perform the copy, as this is purely a platform
		// thing and all we can do is copy the local replica
		InterfacePtr<ICoreFilename> thisCoreFilename(CreateObject2<ICoreFilename>(kCoreFilenameBoss));
		ASSERT(thisCoreFilename);
		if(!thisCoreFilename) {
			break;
		}
		
		int32 initSucc = thisCoreFilename->Initialize(&replicaFile);
		if(initSucc != 0) {
			// couldn't init
			break;
		}
		
		InterfacePtr<ICoreFilename> folderCoreFilename(CreateObject2<ICoreFilename>(kCoreFilenameBoss));
		ASSERT(folderCoreFilename);
		if(!folderCoreFilename) {
			break;
		}
		initSucc = folderCoreFilename->Initialize(dirname);
		if(initSucc != 0) {
			// couldn't init
			break;
		}
		int32 copySuccess =  thisCoreFilename->Copy(folderCoreFilename, pp);
		retval = copySuccess;
	} while(kFalse);
	return retval; // failure;
}

/*
*/
bool16 CusDtLnkAliasedDataLink::CompareBaseName(NameInfo *ni)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::CompareBaseName() +\n");
	this->dumpStateOfThis();

	// "Determines whether the given name information has the same basename as the current link."
	do {
		if(ni && ni->GetFilename()) {
			Utils<ICusDtLnkFacade> facade;
			ASSERT(facade);
			if(!facade) {
				break;
			}
			PMString firstAssetID = *(ni->GetFilename());
			PMString secondAssetID = facade->RetrieveUniqueKey(this);
			
			PMString firstRec = facade->TruncatePath(firstAssetID);
			PMString secondRec= facade->TruncatePath(secondAssetID);

			return 0 == firstRec.Compare(kFalse, secondRec);
		}
	} while(kFalse);
	return kFalse;
}

/*
*/
bool16 CusDtLnkAliasedDataLink::CompareDirectory(NameInfo *ni)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::CompareDirectory() +\n");
	this->dumpStateOfThis();
	do {
		// "Determines whether the given directory is the same the the current link"
		// This sounds a lot like CompareBaseName
		//
		bool16 preconditions = (ni != nil);
		ASSERT(preconditions);
		if(!preconditions) {
			break;
		}
		ASSERT(ni->GetFilename());
		if(!(ni->GetFilename())) {
			break;
		}
			
			Utils<ICusDtLnkFacade> facade;
			ASSERT(facade);
			if(!facade) {
				break;
			}

			// We can define a comparison if the "database" for each
			// is unique
			// We want the first part of each ID
			PMString firstAssetID = *(ni->GetFilename());
			PMString secondAssetID = facade->RetrieveUniqueKey(this);
			if(secondAssetID.empty()) {
				break;
			}

			PMString firstDB = facade->GetFirstPartOfPath(firstAssetID);
			PMString secondDB = facade->GetFirstPartOfPath(secondAssetID);
			
			return 0 == firstDB.Compare(kFalse, secondDB);
		
	} while(kFalse);
	return kFalse;
}

/*
*/
IDataLink *CusDtLnkAliasedDataLink::CreateTestFile(NameInfo *ni, PMString *formatName, uint32 filetype)
{
	// Don't play
	return nil;
}

/*
*/
PMString *CusDtLnkAliasedDataLink::GetBaseName()
{

	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::GetBaseName() +\n");
#ifdef CUSDTLNK_DUMP_GETS
	this->dumpStateOfThis();
#endif
	do {
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}

		UIDRef  wsRef;
		IDataBase* db = ::GetDataBase(this);
		//The database may be NIL if the datalink is temporary created)
		if (db)
		{
			InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
			wsRef = doc->GetDocWorkSpace();
		}
		else
		{
			InterfacePtr<IUIDData> iWorkspaceRef(this, IID_IUIDDATA);
			wsRef = iWorkspaceRef->GetRef();
		}

		InterfacePtr<IWorkspace> ws(wsRef , UseDefaultIID());

		PMString uk = facade->RetrieveUniqueKey(this);
		this->fShortNameForAsset = facade->TruncatePath(uk);
		// Now add the description
		this->fShortNameForAsset += " (";
		this->fShortNameForAsset += 
			facade->GetAssetDescriptionFromAssetIdentifier(ws, uk);
		this->fShortNameForAsset += ")";
	} while(kFalse);
	return &(fShortNameForAsset);
}

/*
*/
PMString* CusDtLnkAliasedDataLink::GetFullName()
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::GetFullName() +\n");
#ifdef CUSDTLNK_DUMP_GETS
	this->dumpStateOfThis();
#endif

	UIDRef  wsRef;
	IDataBase* db = ::GetDataBase(this);
	//The database may be NIL if the datalink is temporary created)
	if (db)
	{
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		wsRef = doc->GetDocWorkSpace();
	}
	else
	{
		InterfacePtr<IUIDData> iWorkspaceRef(this, IID_IUIDDATA);
		wsRef = iWorkspaceRef->GetRef();
	}

	InterfacePtr<IWorkspace> ws(wsRef , UseDefaultIID());

	// What we return here is what appears in the Links Information Dialog in
	// bottom text widget
	PMString uniqueKey = Utils<ICusDtLnkFacade>()->RetrieveUniqueKey(this);
	this->fFullDescriptor = uniqueKey;
	this->fFullDescriptor += " [";
	this->fFullDescriptor += Utils<ICusDtLnkFacade>()->GetAssetDescriptionFromAssetIdentifier(ws, uniqueKey);
	this->fFullDescriptor += "]";

	return &(this->fFullDescriptor);
}

/*
*/
int32 CusDtLnkAliasedDataLink::GetNameInfo(NameInfo *ni, PMString *formatName, uint32 *filetype)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::GetNameInfo() +\n");
#ifdef CUSDTLNK_DUMP_GETS
	this->dumpStateOfThis();
#endif
	// We may be called with any of these params = nil
	if(ni) {
		NameInfo nameInfo;
		ClassID classID = ::GetClass(this);
		PMString uk = Utils<ICusDtLnkFacade>()->RetrieveUniqueKey(this);
		ni->Initialize (&uk, nil, 0, classID);	
	}

	if(formatName) {
		*formatName = this->fFormatName;
	}
	if(filetype) {
		*filetype = this->fFileType;
	}	
	
	return 0; // success
}

/*
*/
IDataLink::StateType CusDtLnkAliasedDataLink::GetStoredState(uint64 *size, uint64 *time)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::GetStoredState() +\n");
#ifdef CUSDTLNK_DUMP_GETS
	this->dumpStateOfThis();
#endif
	if (size != nil) {
		*size = fSize;
	}

	if (time != nil) {
		*time = fTime;
	}

	return fState;
}



/*
*/
IDataLink::StateType CusDtLnkAliasedDataLink::GetCurrentState(NameInfo *ni, uint64 *size, uint64 *time, uint32 *filetype, ProgressParam *pp)
{
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::GetCurrentState() +\n");
#ifdef CUSDTLNK_DUMP_GETS
	this->dumpStateOfThis();
#endif
	// Get the current state of the link.  size and time are not valid when
	// the state is kLinkMissing.

	IDataLink::StateType state = kLinkMissing;
	// here's the interesting bit:
	// How this particular datalink implementation defines the semantics of
	// missing and out of date
	// 1 if we have no notion where the database we refer to is, we are plain "missing"
	// 2 if there is not a record in the database for the asset, it is missing too
	// 3 if there is not a localfile for the asset, then it is missing
	// 4 if the timestamp in the database is more recent than the stored one we are out of date
	// 5 We don't pay attention to the local file timestamp
	do {
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		PMString uk = facade->RetrieveUniqueKey(this);
		// The database name is the first part
		PMString databaseName = facade->GetFirstPartOfPath(uk);
		// The record ID is the last part
		PMString recordID = facade->TruncatePath(uk);
	
		UIDRef  wsRef;
		IDataBase* db = ::GetDataBase(this);
		//The database may be NIL if the datalink is temporary created)
		if (db)
		{
			InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
			wsRef = doc->GetDocWorkSpace();
		}
		else
		{
			InterfacePtr<IUIDData> iWorkspaceRef(this, IID_IUIDDATA);
			wsRef = iWorkspaceRef->GetRef();
		}

		InterfacePtr<IWorkspace> ws(wsRef , UseDefaultIID());

		PMString fullDatabasePath = facade->GetAssetDataBasePath(ws, databaseName);
		if(databaseName.empty()) {
			// Oh-oh, missing
			state = kLinkMissing;
			break;
		}
		SDKFileHelper dbFileHelper(fullDatabasePath);
		if(!dbFileHelper.IsExisting()) {
			// Can't find DB in local FS
			state = kLinkMissing;
			break;
		}

		// if there is no record in the database, then this is LINK MISSING
		// We look at the "asset-path" field
		PMString assetFieldName(kCusDtLnkAssetDataBaseAssetPathFieldNameKey, PMString::kTranslateDuringCall);
		PMString assetVal  = 
			facade->GetFieldValueFromAssetIdentifier(ws,uk, assetFieldName);
		if(assetVal.empty()) {
			state = kLinkMissing;
			break;
		}

		// If the local file is missing, then this is a missing link
		IDFile replicaFile = 
			facade->GetLocalFileFromAssetIdentifier(ws, uk);
		SDKFileHelper repHelper(replicaFile);
		// If you assert here, you don't have the assets, or there's something wrong
		// with our logic
		if(!repHelper.IsExisting()) {
			state = kLinkMissing;
			break;
		}
	
		uint64 computedSize = 
			facade->GetAssetSizeFromAssetIdentifier(ws, uk);
		
		uint64 computedTime = 
			facade->GetAssetTimestampFromAssetIdentifier(ws, uk);


		if (!this->compareTimeStamps(this->fTime, computedTime)) {
			state = kLinkOutOfDate;
		} 
		else {
			// TODO TODO ipaterso: what about embedded poss?
			state = kLinkNormal;
		}
	
		if (size)
			*size = computedSize;

		if (time)
			*time = computedTime;

	} while(kFalse);

	

	

	return state;
}


/*
*/
int32 CusDtLnkAliasedDataLink::GetTestName(PMString *dirname, PMString *basename, NameInfo *ni)
{
	// don't play
	return 1; // failure
}

/*
*/
uint64 CusDtLnkAliasedDataLink::localXferInt64(IPMStream *s, uint64 &value)
{	
	uint32 hiBits = ((uint32)(value >> 32));
	uint32 outH = s->XferInt32((int32 &)hiBits);
	uint32 loBits = ((uint32)(value & 0xffffffff));
	uint32 outL = s->XferInt32((int32 &)loBits);
	return ((uint64)outH << 32) + outL;
}

/*
*/
void CusDtLnkAliasedDataLink::ReadWrite(IPMStream *s, ImplementationID prop)
{
	
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::ReadWrite() +\n");
	fSize = localXferInt64(s, (uint64 &)fSize);
	fTime = localXferInt64(s, (uint64 &)fTime);
	
	s->XferInt32((int32 &)fState);
	fFormatName.ReadWrite(s);
	s->XferInt32((int32 &) fFileType);
	
	this->fLongLocReplicaFilename.ReadWrite(s);
}

/*
*/
int32 CusDtLnkAliasedDataLink::SetStoredState(uint64 *size, uint64 *time, IDataLink::StateType state)
{
	PreDirty (kCusDtLnkAliasedDataLinkImpl,kFalse);
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::SetStoredState() +\n");
	this->dumpStateOfThis();
	if (size) {
		fSize = *size;
	}

	if (time) {
		fTime = *time;
	}

	fState = state;
	// ipaterso: We've changed state on persistent interface, so expect to mark document as PreDirty
	// + From Datalink.cpp: 
	// Do not dirty the pub.  This method is used in an pub action open
	// command and it is not allowed to dirty the pub.
	
	return 0; // success
}

/*
*/
int32 CusDtLnkAliasedDataLink::SetNameInfo(NameInfo *ni, 
										   PMString *formatName, 
										   uint32 filetype, 
										   const PMString *fullPath)
{ 
	TRACEFLOW(kCusDtLnkPluginName, "CusDtLnkAliasedDataLink::SetNameInfo() +\n");
	// We're going to change state on persistent interface, so mark document as PreDirty
	PreDirty();
	
	this->dumpStateOfThis();
	do {
		// We can be called with nil params here, so don't worry
		Utils<ICusDtLnkFacade> facade;
		ASSERT(facade);
		if(!facade) {
			break;
		}
		if(!(ni && (ni->GetFilename()))) {
			break;
		}

		// The filename slot of NameInfo we're using for our asset key
		PMString someKey = *(ni->GetFilename());
		TRACEFLOW(kCusDtLnkPluginName, "-- called SetNameInfo()  with %s\n", 
			someKey.GetPlatformString().c_str());

		bool16 validKey = kTrue;
		SDKFileHelper fileHelper(someKey);
		if(fileHelper.IsExisting()) {
			validKey = kFalse;
			// The filename in the slot of this datalnk exists locally
			TRACEFLOW(kCusDtLnkPluginName, 
					"CusDtLnkAliasedDataLink::SetNameInfo(): custom datalink, but filesystem path passed \n");
		}
		// We get called back with a 'real' filename by the Links core
		// during Restore (re-link) operation,
		// we don't want to store that in the wrong place, so some fancy footwork required here

		// The unique asset key shouldn't have a : separator in it...
		if(validKey) {
			facade->StoreUniqueKey(this, someKey);
		} else {
			// We are using our custom datalink as if it WERE a standard datalink,
			// e.g. to drive an import, and we have some stored state that represents
			// the unique key created elsewhere (see CusDtLnkFacade::InitializeDataLink)
			this->fLongLocReplicaFilename = someKey;

		}

	} while(kFalse);

	if(formatName) {
		fFormatName = *formatName;
	}
	fFileType = filetype;

	return 0; // success
}

/*
*/
void CusDtLnkAliasedDataLink::DeleteTestFile(NameInfo *ni)
{
	// Do nothing as we're not participating in this testing 
}	

/*
*/
bool16 CusDtLnkAliasedDataLink::FindRelative(NameInfo *dirname, NameInfo *newname, ProgressParam *pp)
{
	// No attempt to find relative
	return kFalse;
}

/*
*/
bool16 CusDtLnkAliasedDataLink::compareTimeStamps(uint64 storedTimeStamp, 
													 uint64 currentTimeStamp)
{
	GlobalTime storedGlobTime(storedTimeStamp);
	GlobalTime currGlobTime(currentTimeStamp);

	int32 storedyear, storedmonth, storedday, storedhour, storedminute, storedsecond;
	int32 curryear, currmonth, currday, currhour, currminute, currsecond;

	storedGlobTime.GetTime(&storedyear, &storedmonth, &storedday, &storedhour, &storedminute, &storedsecond);
	currGlobTime.GetTime(&curryear, &currmonth, &currday, &currhour, &currminute, &currsecond);
	// Return false unless the timestamp we store is within 'secondsThreshold' of the one in the
	// database
	bool16 retval = kFalse;
	do {

		if(storedyear < curryear) {
			break;
		}
		if(storedmonth < currmonth) {
			break;
		}
		if(storedday < currday) {
			break;
		}

		if(storedhour < currhour) {
			break;
		}
		if(storedminute < currminute) {
			break;
		}

		if(storedsecond < currsecond) {
			break;
		}

		retval = kTrue;

	} while(kFalse);

	return retval;
}

/*
*/
void CusDtLnkAliasedDataLink::dumpStateOfThis()
{
#ifdef CUSTDTLNK_IS_VERBOSE

	TRACEFLOW(kCusDtLnkPluginName, "START CusDtLnkAliasedDataLink::dumpState() +\n");
	TRACEFLOW(kCusDtLnkPluginName, "\t\tfTime-><%d>\n", this->fTime);
	TRACEFLOW(kCusDtLnkPluginName, "\t\tfFileType-><%d>\n", this->fFileType);
	TRACEFLOW(kCusDtLnkPluginName, "\t\tfLongFilename-><%s>\n", this->fLongLocReplicaFilename.GetPlatformString().c_str());
	TRACEFLOW(kCusDtLnkPluginName, "\t\tfFormatName-><%s>\n", this->fFormatName.GetPlatformString().c_str());
	TRACEFLOW(kCusDtLnkPluginName, "\t\t\tSTORED UNIQUE KEY-><%s>\n", 
		Utils<ICusDtLnkFacade>()->RetrieveUniqueKey(this).GetPlatformString().c_str());

	TRACEFLOW(kCusDtLnkPluginName, "END CusDtLnkAliasedDataLink::dumpState() +\n");
#endif

}

//  Code generated by DollyXS code generator
