//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IShowPageItemUtils.h $
//  
//  Owner: Steve Flenniken
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
//  IShowPageItemUtils.h
//  
//========================================================================================

#pragma once
#ifndef __IShowPageItemUtils__
#define __IShowPageItemUtils__

#include "LinksID.h"

// IID_IShowPageItemUtils interface

/** This class is a helper class that will allow clients to show a given
	page item by passing in the database and UID of the item. The item 
	when shown will be centered on the page and zoomed in on.
*/
class IShowPageItemUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISHOWPAGEITEMUTILS };

	/** The return values for Show */
	enum // Show return values
	{
		/** Everything worked */
		kSuccess = 0,
		/** Ran out of memory */
		kOutOfMemory = kOutOfMemoryError,
		/** Invalid parameter passed in */
		kInvalidParameter = kInvalidParameterErr,
		/** Object was hidden (probably on a hidden layer) */
		kHiddenPageItem = kHiddenPageItemError,
		/** Object was in overset text and could not be shown */
		kOverSetGraphic = kOverSetGraphicError,
		/** The form field was in a hidden state */
		kHiddenFormFieldState = kHiddenFormFieldStateError,
		/** Object was in a deleted text track change and could not be shown */
		kDeletedTextGraphic = kDeletedTextGraphicError,
		/** Object was in XML backing store and could not be shown */
		kXMLNotInLayoutGraphic = kXMLNotInLayoutGraphicError,
		/** Object was in hidden conditional text and could not be shown */
		kHiddenTextGraphic = kHiddenTextGraphicError,
		/** Object was in an inactive state of a multiple-state object and could not be shown */
		kHiddenMSOState = kHiddenMSOStateError,
	};

	/** Show a page item
		@param db - The DataBase the page item is in
		@param pageItemUID - The UID of the page item
		@return - an error state indicating whether the item could be shown.
	*/
	virtual ErrorCode Show(IDataBase *db, UID pageItemUID) = 0;
};

#endif // __IShowPageItemUtils__
