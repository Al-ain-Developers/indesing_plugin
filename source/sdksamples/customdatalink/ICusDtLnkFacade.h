//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/ICusDtLnkFacade.h $
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

#ifndef __ICusDtLnkFacade_H_DEFINED__
#define __ICusDtLnkFacade_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"
#include "URI.h"
#include <map>
// Project includes:
#include "CusDtLnkID.h"

// Forward declarations:
class IDocument;
class IDataLink;

/** From SDK sample; facade interface that is used by both this plug-in and it's associated
	UI, CustomDataLinkUI sample. Provides methods to access and store persistent data, including
	the database files used by this sample. Also provides methods to work with the adornments added
	to the containers for custom datalinked layout objects.

	@ingroup customdatalink
	@see CustomDataLinkUI
*/
class ICusDtLnkFacade : public IPMUnknown
{

public:

	/** Default interface identifier for UseDefaultIID 
		@see UseDefaultIID
	*/
	enum { kDefaultIID = IID_ICUSDTLNKFACADE };


	/**	Sets a persistent option on the session workspace (kWorkspaceBoss).	
		These are stored in interface(s) of type ICusDtLnkOptions, differentiated
		by PMIID. These are:
		\li IID_ICUSDTLNKOPTIONS for any options
		\li IID_ICUSDTLNKDATABASESASOPTIONS for the list of databases only

		@param key unique key to use when retrieving option
		@param val value to store
		@param iid identifies interface to use when storing value
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
		@see ICusDtLnkOptions
		@see kWorkspaceBoss
	 */
	virtual ErrorCode SetKeyValuePair(const IWorkspace *ws, const PMString& key, const PMString& val, const PMIID& iid)=0;


	/**	Retrieve an option stored in the session workspace (kWorkspaceBoss).

		@param key key to use when looking up the option (stored in a map)
		@param iid identifies the interface (on workspace) where we should look
		@return PMString representing the value of the option given the key, empty if not found
		@see kWorkspaceBoss and adds that we have defined in this plug-in
		@see ICusDtLnkOptions responsible for storing the key-value pairs persistently
	 */
	virtual PMString GetValueFromKey(const IWorkspace *ws, const PMString& key, const PMIID& iid) const=0;


	/**	Determine if given ClassID is a custom datalink of our own type. 
		In practice, we are looking to see if the class exposes an interface IBoolData
		with PMIID of IID_ICUSDTLNKDATALINKBOOLDATA. The rationale behind this was to
		allow multiple subclasses of our base type (kCusDtLnkBasicCustDataLinkBoss) to
		be identified through a marker interface, without explicitly examining ClassID.

		@param classID the ClassID of a datalink of interest
		@return bool16 kTrue if this is one of our custom datalink boss classes, kFalse otherwise
	 */
	virtual bool16 IsOurCustomDataLink(const ClassID& classID) const =0;
	
	/**	Determine if given UIDRef of an ILink is an our own type. 
		In practice, we are looking to see if the link resource associated with the ILink
		has an URL whose schema is of ours.

		@param linkUIDRef the link of interest
		@return bool16 kTrue if this is one of our link resource type, kFalse otherwise
	 */
	virtual bool16 IsOurCustomDataLink(const UIDRef& linkUIDRef) const =0;


	/**	Add our page item adornment to the list of layout objects
		@param itemList specifies layout objects to add adornment to
		@return ErrorCode kSuccess if we succeeded, another ErrorCode otherwise
	 */
	virtual ErrorCode AddAdornment(const UIDList& itemList)=0;



	/**	Remove the page item adornment from list of layout objects
		@param itemList specifies layout objects to remove our adornment from
		@return ErrorCode kSuccess if we succeeded, another ErrorCode otherwise
	 */
	virtual ErrorCode RemoveAdornment(const UIDList& itemList)=0;



	/**	Add a mapping from database name to where the database file is in the local
		filesystem, persisting this to the session workspace.

		@param dbName the database name, e.g. alias-database-1.csv
		@param fullPath where the database file is located in the local file system
		@return ErrorCode kSuccess if we succeeded, another ErrorCode otherwise
	 */
	virtual ErrorCode AddAssetDataBase(const IWorkspace *ws, const PMString& dbName, 
									const PMString& fullPath)=0;


	/**	Accessor for the nth database name
		@param index 
		@return PMString 
	 */
	virtual PMString GetNthAssetDataBase(const IWorkspace *ws, int32 index) const =0;


	/**	Determine how many databases are known about, that is, mapped through to
		database files in the local filesystem
		
		@return int32 giving number of databases for which we have done an AddAssetDataBase
			and where we know what the path is to the database file given its name
	 */
	virtual int32 GetAssetDataBaseCount(const IWorkspace *ws) const=0;


	/**	Given a name of a database, e.g. alias-database-1.csv, return a path 
		to the database file in local filesystem as PMString
		@param dbName identifies the database, found in the custom datalink as first part of 
			the unique asset key for a custom datalink
		@return PMString with path to the database file in local filesystem
	 */
	virtual PMString GetAssetDataBasePath(const IWorkspace *ws, const PMString& dbName) const=0;


	/**	Given a path of some kind, return the original with the
		last part of the path removed

		@param fullPath input path to process
		@param useAnySeparator if any path separator can be used
		@param useThisOne if !useAnySeparator, which path separator to use
		@return PMString with the input minus the last component
	 */
	virtual PMString TruncatePath(const PMString& fullPath, 
		bool16 useAnySeparator = kTrue, 
		const PlatformChar& useThisOne = kTextChar_Solidus) const = 0;


	/**	Given a document and a path in local file system to image, load
		the placegun, initializing a custom datalink with the uniqueKey supplied

		@param docUIDRef which document to target
		@param path refers to asset in local filesystem
		@param uniqueKey unique identifier for custom datalink to create pointing at asset
		@return UIDRef representing contents of the place gun
	 */
	virtual UIDRef ImportImageAndLoadPlaceGun(const UIDRef& docUIDRef, 
		const PMString& path, 
		const PMString& uniqueKey)=0;


	/**	Given a document and an URI to image, load the placegun.

		@param docUIDRef which document to target
		@param uri refers to asset uri
		@return UIDRef representing contents of the place gun
	 */
	virtual UIDRef ImportImageAndLoadPlaceGun(const UIDRef& docUIDRef, 
		const URI& uri)=0;


	/**	Used only by the UI. Might consider refactoring out.
		@return PMString 
	 */
	virtual PMString GetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws) const = 0;


	/**	Used only by the UI. Might consider refactoring out.
		@param newKey 
		@return ErrorCode 
	 */
	virtual ErrorCode SetCurrentlyChosenUniqueAssetKey(const IWorkspace *ws, const PMString& newKey) = 0;


	/**	Initializes one of our custom datalinks so that it will behave correctly.
		Means that we don't have to use IDataLinkHelper::InitializeDataLink,
		which doesn't initialize our custom type in the way that is required.

		@param dl datalink of interest, which should be one of our custom types
		@param file path to local replica of asset, if it exists
		@param formatName name of asset's format if known
		@param uniqueAssetKey unique key identifying asset in database
		@return ErrorCode kSuccess if we succeeded, other ErrorCode otherwise
		@precondition IsOurCustomDataLink(dl) == true

	 */
	virtual ErrorCode InitializeDataLink(const IWorkspace *ws, 
										IDataLink *dl, 
										const IDFile &file, const PMString &formatName,
										const PMString& uniqueAssetKey) = 0;

	/** See Convert an unique key to URI, this is mainly for phase 2 conversion: when we get an old kCusDtLnkAliasedDataLinkBoss
		during conversion, we will query its IDataLink and use it to get the unique key used in CS3 and earlier, then we need to
		convert this unique key into an URI, which is used to create the new link resource under the new CS4 link architecture
		@param uk the unique key that represent an asset for our custom data link, it has the format of "alias-database-1.csv/1000141"
		@param uri the URI for the link resource, it has the format of CusDtLnk://database_fulloath?recordID
		@return True if the conversion succeeds, else false. 
	*/
	virtual bool UniqueKeyToURI(const PMString& uk, URI& uri) const = 0;

	/**	
		 Converts an URI that represents our CSV based asset to an IDFile.
		 @param uri	 [IN] URI to convert.
		 @param file [OUT] Resulting IDFile.
		 @return True if the conversion succeeds, else false. 
	 */
	virtual bool URIToIDFile(const URI& uri, IDFile& file) const = 0;


	/**	Given a path, return the first part up to a directory separator (like forward or reverse slash
		or colon) ; so given something like xyz/abc, return xyz
		@param p path of interest
		@return PMString representing first component of path
	 */
	virtual PMString GetFirstPartOfPath(const PMString& p) const =0;


	/**	Determine the path in local filesystem to a "local replica" of asset given the unique identifier.
		Although we have no checkin/checkout protocol, we treat the path to the local replica
		as just another parameter from the database, rather than as a defining property of the link.
		
		@param uniqueAssetKey 
		@return IDFile 
	 */
	virtual IDFile GetLocalFileFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const = 0;


	/**	Given a database (a flatfile database with a single, unnamed table) and a record
		identifier, retrieve a value for the named column in row identified by the recordID
		@param databaseFile path to database file
		@param recordID identifies row within the file 
		@param fieldName specifies a column
		@return PMString value for the field specified, or empty if none exists with matching criteria
	 */
	virtual PMString GetAssetDataBaseRecordFieldValue(const IDFile& databaseFile, 
									const PMString& recordID, 
									const PMString& fieldName) const =0;

	/**	Determine size of asset given its unique identifier
		@param uniqueAssetKey 
		@return uint64 representing asset size
	 */
	virtual uint64 GetAssetSizeFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const = 0;

	/**	Determine the timestamp (includes date) of last modification
		for asset given its unique identifier
		@param uniqueAssetKey 
		@return uint64 encoding the date/time asset was last modified
		@see GlobalTime
	 */
	virtual uint64 GetAssetTimestampFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const = 0;

	/**	Determine the asset description given its unique identifier
		@param uniqueAssetKey 
		@return PMString 
	 */
	virtual PMString GetAssetDescriptionFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey) const = 0;
	virtual uint64 GetAssetTimestampFromURI(const URI& uri) const = 0;


	/**	Given a unique key, retrieve named field from associated record
		@param uniqueAssetKey 
		@param fieldName 
	 */
	virtual PMString GetFieldValueFromAssetIdentifier(const IWorkspace *ws, const PMString& uniqueAssetKey,
														const PMString& fieldName) const = 0;

	/**	Determine the asset description given its URI
		@param uri 
		@return PMString 
	 */
	virtual PMString GetAssetDescriptionFromURI(const URI& uri) const = 0;
	
	/**	Given a custom datalink, associate it with a unique key to identify an asset
		that it refers to.

		@param dataLink 
		@param uniqueAssetKey 
	 */
	virtual void StoreUniqueKey(IDataLink* dataLink, const PMString& uniqueAssetKey)=0;

	/**	Given a datalink, find the unique key associated with the asset it points to.
		For instance, this would be something like "alias-database-1.csv/1000141".
		This will only work for one of our own custom datalinks, with a normal datalink
		would just return an empty string.

		@param dataLink specifies the datalink object of interest
		@return PMString containing its unique key, identifying the asset by combination
			of database name and record identifier.
	 */
	virtual PMString RetrieveUniqueKey(IDataLink* dataLink) const=0;

	/**	Given a uri, retrieve named field from associated field key
		@param uri the uri that reprents a record in some database (CSV) file.
		@param whichField the field key defined in CusDtLnkID.h
		@return PMString field value in string
	 */
	PMString GetRecordFieldValueFromURI(const URI& uri, PMString& whichField) const;

	/**	Determine if the given layout object should have our page item adornment to signify it
		it has custom datalinked dependent
		@param pageItemUIDRef identifies layout object of interest
		@return bool16 kTrue if it should have the adornment, kFalse otherwise
	 */
	virtual bool16 NeedsOurAdornment(const UIDRef& pageItemUIDRef) const=0;

	/**	Determine if the given layout object already has our page item adornment to signify it
		has a custom datalinked dependent
		@param pageItemUIDRef identifies layout object of interest
		@return bool16 kTrue if it has the adornment, kFalse otherwise
	 */
	virtual bool16 HasOurAdornment(const UIDRef& pageItemUIDRef) const =0;
};

#endif // __ICusDtLnkFacade_H_DEFINED__

