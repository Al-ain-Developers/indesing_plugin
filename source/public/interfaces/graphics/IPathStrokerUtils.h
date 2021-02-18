//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPathStrokerUtils.h $
//  
//  Owner: Greg St. Pierre
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPathStrokerUtils__
#define __IPathStrokerUtils__

#include "InstStrokeFillID.h"
#include "RequestContext.h"
#include "Utils.h"

class IDataBase;
class IDocument;
class IPathStroker;
class IPathStrokerList;
class IGraphicStyleDescriptor;
class IGraphicAttrClassID;
class IGraphicStyleAttributeBossList;
class ICommand;
class IPathStrokerMetadata;
class IDialog;
class IScript;
class IScriptRequestData;
class SortedUIDList;

class IPathStrokerUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPATHSTROKERUTILS };

	/**
	 Get number of path strokers for the specified document

	 @param document	The document to be checked
	 @return The number of path strokers in the document
	 */
	virtual uint32 GetPathStrokerCount(IDocument const *document) const = 0;

	/** 
	 Instantiates nth path stroker for the specified document
	
	 @param document	The document
	 @param index		Index of the path stroker to instantiate
	 @return AddRef'd pointer to nth stroker, or nil if failure
	 */
	virtual IPathStroker *QueryNthPathStroker(IDocument const *document, uint32 index) const = 0;

	/**
	 Queries for IPathStrokerList interface on given database

	 @param db			The database
	 @return AddRef'd pointer to path stroker list interface, or nil
	 */
	virtual IPathStrokerList *QueryPathStrokerList(IDataBase *db) const = 0;

	/** 
	 Queries for IPathStrokerList interface on given document

	 @param document	The database
	 @return AddRef'd pointer to path stroker list interface, or nil
	 */
	virtual IPathStrokerList *QueryPathStrokerList(IDocument const *document) const = 0;

	/** 
	 Queries active IPathStrokerList

	 @return AddRef'd pointer to path stroker list interface, or nil
	 */
	virtual IPathStrokerList *_QueryActivePathStrokerList() const = 0;

	/** 
	 Finds named path stroker in list, returning its index if found

	 @param strokerList			The list to be searched
	 @param name				Name of stroker to find
	 @param index				OUT param: index of found item if successful
	 @param useTranslatedNames	Whether to translate stroker names before compare (default is kTrue)
	 @return kTrue if specified stroker was found, else kFalse
	 */
	virtual bool16 FindNamedPathStroker(
		IPathStrokerList const *strokerList, 
		PMString const &name, 
		uint32 &index,
		bool16 useTranslatedNames = kTrue
	) const = 0;

	/**
	 Retrieves index of path stroker with given class ID and UID in the given list

	 @param strokerList		The list to be searched
	 @param classId			Class id of stroker
	 @param uid				UID of stroker
	 @param index			OUT param: index of found item if successful
	 @return kTrue if specified stroker was found, else kFalse
	 */
	virtual bool16 FindPathStroker(
		IPathStrokerList const *strokerList, 
		ClassID const &classId, 
		UID const &uid, 
		uint32 &index
	) const = 0;

	/**
	 Queries for a path stroker given its ClassID and UID

	 @param strokerList		The list
	 @param classId			Class id of stroker
	 @param uid				UID of stroker
	 @return AddRef'd pointer to stroker, or nil
	 */
	virtual IPathStroker *QueryPathStroker(
		IPathStrokerList const *strokerList, 
		ClassID const &classId, 
		UID const &uid
	) const = 0;

	/**
	 Queries for a path stroker based on a graphic style descriptor 

	 @param strokerList		Path stroker list
	 @param gsDesc			The style descriptor
	 @return AddRef'd pointer to stroker, or nil
	 */
	virtual IPathStroker *QueryPathStrokerFromGSDesc(
		IPathStrokerList const *strokerList,
		IGraphicStyleDescriptor *gsDesc
	) const = 0;

	/**
	 Returns kTrue if stroker is custom 

	 @param stroker			The stroker
	 @return kTrue if stroker is custom, else kFalse if it's built-in
	 */
	virtual bool16 IsCustomStroker(IPathStroker const *stroker) const = 0;

	/**
	 Returns kTrue if stroker is custom 

	 @param classId			Class id of stroker
	 @param uid				UID of stroker
	 @return kTrue if stroker is custom, else kFalse if it's built-in
	 */
	virtual bool16 IsCustomStroker(ClassID const &classId, UID const &uid) const = 0;

	/**
	 Returns name for the stroker. If path stroker is custom, returns the name
	 for the stroker instance; otherwise, returns the name for the stroker
	 class

	 @param stroker			The name of the path stroker
	 @param translateName	Whether to translate the name returned (default is kTrue)
	 @return its name
	 */
	virtual PMString GetPathStrokerName(IPathStroker const *stroker, bool16 translateName = kTrue) const = 0;

	/**
	 Returns a unique name based on given base. Uses same heuristic as is used
	 in the swatch panel (appends 'copy', then 'copy 2', 'copy 3', etc., as
	 necessary)

	 @param strokerList		The list
	 @param basename		Name used as the base for the calculated name
	 @return New name guaranteed to be unique in the specified list
	 */
	virtual PMString GetUniqueStrokerName(
		IPathStrokerList const *list, 
		PMString const &basename
	) const = 0;

	/**
	 Queries for path stroker's metadata, if it has one. Returns nil if not a 
	 custom stroker 

	 @param stroker			The path stroker
	 @return AddRef'd pointer to path stroker metadata interface, or nil
	 */
	virtual IPathStrokerMetadata *QueryPathStrokerMetadata(IPathStroker const *stroker) const = 0;

	/**
	 Queries for path stroker's metadata, if it has one. Returns nil if not a 
	 custom stroker 

	 @param strokerList		The list
	 @param classId			Class id of stroker
	 @param uid				UID of stroker
	 @return AddRef'd pointer to path stroker metadata interface, or nil
	 */
	virtual IPathStrokerMetadata *QueryPathStrokerMetadata(
		IPathStrokerList const *strokerList, 
		ClassID const &classId, 
		UID const &uid
	) const = 0;

	/**
	 Returns the number of path stroker metadata class known to the application.
	 This number is determined by counting available metadata services and is
	 consequently static

	 @return the number of available path stroker metadata classes 
	 */
	virtual uint32 GetMetadataCount() const = 0;

	/**
	 Queries for path stroker metadata interface by index

	 @param index			The index
	 @return AddRef'd pointer to path metadata interface, or nil
	  */
	virtual IPathStrokerMetadata *QueryNthMetadata(uint32 index) const = 0;

	/**
	 Queries for path stroker metadata by class id

	 @param metadataClass	The class id for the metadata
	 @return AddRef'd pointer to path metadata interface, or nil
	 */
	virtual IPathStrokerMetadata *QueryPathStrokerMetadataByClass(ClassID const &metadataClass) const = 0;

	/**
	 Queries for path stroker metadata by name

	 @param name	The name of the metadata
	 @return AddRef'd pointer to path metadata interface, or nil
	 */	
	virtual IPathStrokerMetadata *QueryPathStrokerMetadataByName(PMString const &name) const = 0;

	/**
	 Determines if specified path stroker can be duplicated

	 @param strokerList	The list
	 @param classId		The class id for the stroker
	 @param uid			The UID for the stroker
	 @return kTrue if the stroker can be duplicated, else kFalse
	 */
	virtual bool16 CanStrokerBeDuplicated(
		IPathStrokerList const *strokerList, 
		ClassID const &classId, 
		UID const &uid
	) const = 0;

	/**
	 Duplicates the given path stroker in the specified database. Does not set stroker's
	 name, nor does it add the stroker to the database's stroker list.

	 @param classId		The class id for the stroker
	 @param uid			The UID for the stroker
	 @param db			The database in which the stroker is duplicated
	 @param addToList	If kTrue, new stroker is added to database's list (its name is made unique)
	 @return The cloned path stroker
	 */
	virtual IPathStroker *DuplicatePathStroker(
		IPathStrokerList const *strokerList, 
		ClassID const &classId, 
		UID const &uid, 
		IDataBase *db, 
		bool16 addToList
	) const = 0;

	/**
	 Duplicates the given path stroker in the specified database. Does not set stroker's
	 name, nor does it add the stroker to the database's stroker list.

	 @param source		The path stroker to duplicate
	 @param db			The database in which the stroker is duplicated
	 @param addToList	If kTrue, new stroker is added to database's list (its name is made unique)
	 @return The cloned path stroker
	 */
	virtual IPathStroker *DuplicatePathStroker(
		IPathStroker const *source, 
		IDataBase *db, 
		bool16 addToList
	) const = 0;

	/**
	 Creates new instance of path stroker based on metadata

	 @param metadata	The path stroker metadata to use to create the new instance
	 @param db			The database in which the stroker is duplicated
	 @param addToList	If kTrue, new stroker is added to database's list (its name is made unique)
	 @return The new path stroker
	 */
	virtual IPathStroker *NewPathStroker(
		IPathStrokerMetadata const *metadata, 
		IDataBase *db, 
		bool16 addToList
	) const = 0;

	/**
	 Gets the line style UID from graphic style descriptor

	 @param uid			OUT param: The UID in the descriptor, if successful
	 @param styleDesc	The style descriptor
	 @return kSuccess if successful, else error code
	 */
	virtual ErrorCode GetLineStyleUID(UID &uid, IGraphicStyleDescriptor *styleDesc) const = 0;

	/**
	 Creates new line style attribute. Attribute is implicitly given a ClassID
	 of kCustomPathStrokerBoss.

	 @param uid			The UID for the style
	 @return AddRef'd pointer to the attribute
	 */
	virtual IGraphicAttrClassID *CreateLineStyleAttribute(UID const &styleUID) const = 0;

	/**
	 Adds style attribute to attribute list. Attribute is implicitly given a
	 ClassID of kCustomPathStrokerBoss

	 @param styleUID		The UID for the style
	 @param attributeList	The list
	 @return kSuccess if successful, else error code
	 */
	virtual ErrorCode AddLineStyleAttribute(
		UID const &styleUID, 
		IGraphicStyleAttributeBossList *attributeList
	) const = 0;

	/**
	 Creates command to install line style. Attribute is implicitly given a
	 ClassID of kCustomPathStrokerBoss

	 @param styleUID		The UID for the style
	 @param targetItemList	The target
	 @param doPrePost		kTrue if command should use pre/post actions
	 @param enableDoNotify	kTrue if command should notify
	 @return AddRef'd pointer to command interface, or nil
	 */
	virtual ICommand *CreateLineStyleCommand(
		UID const &styleUID,
		const UIDList *targetItemList,
		bool16 doPrePost,
		bool16 enableDoNotify
	) const = 0;

	/**
	 Replaces instances of path strokers with new instance

	 @param strokerList		UIDList of path strokers to replace
	 @param replaceClass	ClassID of path stroker to replace with
	 @param replaceUID		UID of path stroker to replace with
	 @return ErrorCode describing success/failure of function
	 */
	virtual ErrorCode ReplacePathStrokers(
		UIDList const &strokerList, 
		ClassID const &replaceClass,
		UID const &replaceUID
	) const = 0;

	/**
	 Retrieves list of referenced path strokers in the specified list

	 @param strokerList		The path stroker list to search
	 @param refdStrokers	The list of referenced strokers
	 */
	virtual void GetReferencedPathStrokers(
		IPathStrokerList const *strokerList, 
		SortedUIDList &refdStrokers
	) const = 0;

	/**
	 Sets the name of a path stroker

	 @param pathStroker		The path stroker
	 @param name			New name
	 @return kSuccess, or ErrorCode
	 */
	virtual ErrorCode SetPathStrokerName(IPathStroker *pathStroker, PMString const &name) const = 0;

	/**
	 Deletes and replaces path stroker

	 @param deleteList		List of strokers to delete
	 @param replaceClass	Class ID for replacement
	 @param replaceUID		UID for replacement
	 */
	virtual ErrorCode DeleteAndReplacePathStroker(
		UIDList const &deleteList, 
		ClassID const &replaceClass, 
		UID const &replaceUID
	) const = 0;

	enum StrokeStyleImportError
	{
		kErrorSuccess,
		kErrorFileDamaged,
		kFailedToCopyStroke,
		kErrorUnknown
	};

	/**
	 Imports line styles from a file

	 @param file			File to import styles from
	 @param destination		Document to import styles into
	 */
	virtual IPathStrokerUtils::StrokeStyleImportError ImportStyles(
		IDFile const &file, 
		IDataBase *destination
	) const = 0;

	/**
	 Exports line styles to a file

	 @param file			File to export styles to
	 @param destination		Document to export styles from
	 @param styles			List of styles to export
	 @param creator			Output file creator
	 @param fileType		Output file type
	 */
	virtual IPathStrokerUtils::StrokeStyleImportError ExportStyles(
		IDFile const &file, 
		IDataBase *source, 
		UIDList const &styles, 
		SysOSType const &creator, 
		SysOSType const &fileType
	) const = 0;

	/**	Built-in strokers aren't persistent, so need to create a proxy object for scripts
		@param context is the request context
		@param parent is the parent script object
		@param clsID is the stroker class
		@return IScript* is the proxy script object
	 */
	virtual IScript* CreateStrokeStyleScriptObject( const ScriptInfo::RequestContext& context, IScript* parent, const ClassID& clsID ) const  = 0 ;

	/**
		Set the stroke style for a script object into the return data for a get property request
		@param data is the script event data [in/out]
		@param db is the database of the script object [in]
		@param classID is the ClassID of the line type [in] (see @IGraphicAttrClassID)
		@param uid is the UID of custom line type [in]
		@param returnName if true, will return the name of the stroke style instead of the object
	*/
	virtual ErrorCode GetStrokeStyleForGetProperty( IScriptRequestData* data, IScript* script, const ScriptID& propID, IDataBase* db, const ClassID& classID, const UID& uid, bool16 returnName = kFalse ) const = 0 ;

	/**
		Get the stroke style specified by parameter data for a set property request
		@param data is the script event data [in]
		@param propID is the property id [in]
		@param db is the database of the script object (reset to the database of the stroke style object) [in/out]
		@param classID is the ClassID of the line type [out] (see @IGraphicAttrClassID)
		@param uid is the UID of custom line type [out]
		@param allowNone if true, will return kNonePathStrokerBoss if parameter is empty, nil, or Nothing
	*/
	virtual ErrorCode GetStrokeStyleForSetProperty( const IScriptRequestData* data, const ScriptID& propID, IDataBase*& db, ClassID& classID, UID& uid, bool16 allowNone = kFalse ) const = 0 ;
};

#endif //!def __IPathStrokerUtils__
