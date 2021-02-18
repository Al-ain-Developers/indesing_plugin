//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IOpenManager.h $
//  
//  Owner: Zak Williamson
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
#ifndef __IOpenManager__
#define __IOpenManager__

#include "IPMUnknown.h"
#include "IImportProvider.h"

class IDataBase;
class SysFileList;

/**
 Interface used to open document files.
 */
class IOpenManager : public IPMUnknown
{
public:
	/**
	 Displays the open file dialog to the user.
	 @param openFiles			OUT List of files selected by the user from the dialog.
	 @param allowMultipleFiles	IN Denotes whether to allow the user to select multiple files.
	 @return kFalse if the user cancelled out of the dialog or there was an error, else kTrue.
	 */
	virtual bool16 DoOpenDialog(SysFileList& openFiles, bool16 allowMultipleFiles) = 0;

	/**
	 Creates a UIDRef from the given document file.
	 @param openMe	IN File to open.
	 @param flags	IN UI flags denoting how to handle UI events. (see BaseType.h)
	 @return UIDRef of the document boss of the newly created document (database).
	 */
	virtual UIDRef OpenDocFromFile(IDFile * openMe, UIFlags flags) = 0;
};

#endif
