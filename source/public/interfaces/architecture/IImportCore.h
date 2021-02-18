//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportCore.h $
//  
//  Owner: Lonnie Millett
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

#pragma once
#ifndef __IImportCore__
#define __IImportCore__

#include "IPMUnknown.h"
#include "IImportProvider.h"

class IOpenFileDialog;
class IDataBase;
class ICommand;
class FileTypeInfo;

typedef void AddTypeRoutine(void *data, SysOSType type);
typedef void AddExtensionRoutine(void *data, const PMString *family, const PMString *newExtension);

/**
 Interface used to import files.
 */
class IImportCore : public IPMUnknown
{
public:
	/**
	 Returns the default (API supplied) dialog used to import files.
	 @return Pointer to the place dialog used to select files to import.
	 */
	virtual IOpenFileDialog * QueryPlaceFileDialog() = 0;
	
	/**
	 Creates a UIDRef from the file referenced by the given DataLink.
	 @param linkAssetUID	IN link asset identifying the URI to import from.
	 @param flags			IN UI flags denoting how to handle UI events. (see BaseType.h)
	 @param pImportedItem	OUT When opening a document, the UIDRef of the document boss of
								the newly created document (database).
								When importing a file, the UIDRef of the imported file.
	 @param db				IN Database to import into. Ignored when opening a document.
	 @param uidPreview		IN UID of the pre-existing preview image.
	 */
	virtual void MakeUIDFromLinkAssetUID(UID linkAssetUID, UIFlags flags, UIDRef * pImportedItem, IDataBase * db = nil, UID uidPreview = kInvalidUID) = 0;

	/**
	 Calls the given AddTypeRoutine and AddExtensionRoutine functions with the
	 supported file types and extensions.
	 @param data			IN Pointer to user defined data passed to the AddTypeRoutine and
							   AddExtensionRoutine functions.
	 @param addType			IN Pointer to the AddTypeRoutine function which is called once for
							   each supported file type.
	 @param addExtension	IN Pointer to the AddExtensionRoutine function which is called once
							   for each supported extension.
	 */
	virtual void AddTypesAndExtensions(void *data, AddTypeRoutine *addType, AddExtensionRoutine *addExtension) = 0;
};

#endif
