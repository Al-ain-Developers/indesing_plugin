//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IMediaInfo.h $
//  
//  Owner: wtislar
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
#ifndef __IMediaInfo__
#define __IMediaInfo__

#include "ICommand.h"
#include "IPMUnknown.h"

#include "CursorSpec.h"
#include "MediaID.h"
#include "PMPoint.h"
#include "PMString.h"




/**
	This is a call-back interface that is used by the Media plugin to get information
	it needs to create 	media page items. When adding a new kind of media page item,
	you need to add this interface to your PlaceProvider boss, and to your page item
	boss that is based on the kMediaPageItemBoss.
*/
class IMediaInfo : public IPMUnknown
{
public:


	enum { kDefaultIID = IID_IMEDIAINFO };

	enum { kMinPageItemHeight = 10,
		   kMinPageItemWidth  = kMinPageItemHeight };
	
	/** DEPRECATED
		Retrieves an ICommand instance that applies IMediaFilterAttributes to the
		media page item. An example of such a command would be one that applies
		attributes taken from a movie file to a movie page item.
		@return a valid pointer to an ICommand object, or nil if there are
		no attributes to apply to the media page item.
	*/
	virtual ICommand * GetApplyFilterAttributesCmd() const = 0;

	/** Retrieves the default value for the EmbedOnPDFExport option.
		@return kTrue if the default is to embed content when exported to PDF; kFalse otherwise.
	*/
	virtual bool16 GetEmbedOnPDFExportDefault() const = 0;

	/**	Retrieves the ClassID (boss ID) of a media page item that is based on the
		kMediaPageItemBoss.
		@return a valid ClassID for a media page item.
	*/
	virtual ClassID GetMediaPageItemClassID() const = 0;

	/**	Retrieves the id of the type of media handled by this interface.
		@return a media type identifier, based on the MediaType enum.
	*/
	virtual MediaType GetMediaType() const = 0;

	/** Retrieves the cursor used for placing the media page item into another page item.
		@see IPlaceBehavior.
		@return the CursorSpec object for the place into cursor.
	*/
	virtual CursorSpec	GetPlaceIntoCursor() const = 0;

	/** Retrieves the cursor used for placing the media page item onto the spread.
		@see IPlaceBehavior.
		@return the CursorSpec object for the place cursor.
	*/
	virtual CursorSpec	GetPlaceCursor() const = 0;

	/** DEPRECATED. Use IMediaReadFormatInfo::GetStandardPosterFileName() instead.
		Retrieves the standard poster name for a specific type of media, if it exists.
		@return a PMString object containing the absolute path to the standard poster
		file. Returns the null string (PMString("")) if there is no standard poster for
		the media page item.
	*/
	virtual const PMString GetStandardPosterFileName() const = 0;

	/** Tests if the media page item is currently selected.
		@return kTrue if selected; kFalse if not selected.
	*/
	virtual bool16 IsSelected() const = 0;

}; // end IMediaInfo interface

#endif // __IMediaInfo__