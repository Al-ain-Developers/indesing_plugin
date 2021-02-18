//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenCore.h $
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
#ifndef __IOpenCore__
#define __IOpenCore__

#include "IPMUnknown.h"
#include "IImportProvider.h"

class IOpenFileDialog;
class IDataBase;
class ICommand;
class IDataLink;

/**
 Interface used to open files.
 */
class IOpenCore : public IPMUnknown
{
public:
	/**
	 Returns the dialog used to open files.
	 @return Pointer to the open file dialog used to select files to open.
	 */
	virtual IOpenFileDialog * QueryOpenFileDialog() = 0;
	
	/**
	 Creates a UIDRef from the file referenced by the given DataLink.
	 @param linkAssetUID	IN link asset identifying the URI to import from.
	 @param flags			IN UI flags denoting how to handle UI events. (see BaseType.h)
	 @param pImportedItem	OUT When opening a document, the UIDRef of the document boss of
								the newly created document (database).
								When importing a file, the UIDRef of the imported file.
	 @param db				IN Database to import into. Ignored when opening a document.
	 */
	virtual void MakeUIDFromLinkAssetUID(UID linkAssetUID, UIFlags flags, UIDRef * pImportedItem, IDataBase * db = nil) = 0;
};

#endif
