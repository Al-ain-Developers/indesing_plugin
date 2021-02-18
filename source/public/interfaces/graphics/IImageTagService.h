//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageTagService.h $
//  
//  Owner: frits
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
#ifndef __IImageTagService__
#define __IImageTagService__

#include "IPMUnknown.h"

/**
 Interface that defines a mechanism for importing and exporting image tags.
 
 Note: This interface is for internal use only. The code that uses this 
 interface looks for a specific implementation and so does not provide a way
 for third-party developers to provide their own implementations. In addition, 
 the data provided by the one existing implementation is for internal use only
 and is intentionally undocumented.
 */
class IImageTagService : public IPMUnknown
{
public:
	/**
	 Imports data for the specified tag.
	 
	 Note: The implementation can assume the incoming tagData holds data 
	 corresponding to the tagID. It is free to do whatever it needs to with 
	 this data, but must not delete it.
	 
	 @param tagID		IN The selector for the tag being imported
	 @param item		IN The page item to import to
	 @param tagData		IN The data for the tag
	 @param dataSize	IN The size of the data
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool8 ImportTagData(int16 tagID, const UIDRef &item, void *tagData, uint32 dataSize) = 0;
	
	/**
	 Exports data for the specified tag.
	 
	 Note: The implementation should take the item and extract the data
	 corresponding to the tagID. It should then pass back a pointer to newly 
	 created data. The caller owns the returned data and is responsible for 
	 cleaning it up.
	 
	 @param tagID		IN The selector for the tag being exported
	 @param item		IN The page item to export from
	 @param tagData		OUT Receives a pointer to the data for the tag
	 @return kTrue if the method succeeds, else kFalse
	 */
	virtual bool8 ExportTagData(int16 tagID, const UIDRef& item, void **tagData) = 0;
};

#endif // __IImageTagService__
