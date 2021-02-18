//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDuplicatePrefs.h $
//  
//  Owner: Paul Sorrick
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

#ifndef __IDUPLICATEPREFS__
#define __IDUPLICATEPREFS__

#include "IPMUnknown.h"
#include "PageItemScrapID.h"

/**
	An interface off the kWorkspaceBoss, holds defaults for Step and Repeat and object duplication via keyboard shortcut.
 */
class IDuplicatePrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IDUPLICATEPREFS };

	/**	Function to set the session preferences for duplicating objects. Step and Repeat
		dialog sets these values, they are used when duplicating objects via keyboard shortcut.
		@param newOffset the x offset in pasteboard units for duplicating objects.
	 */
	virtual void SetXOffset(const PMReal newOffset) = 0;

	/**	Return the x offset vale.
		@param none
		@return PMReal the x offset value for duplicating objects. 
	 */
	virtual const PMReal GetXOffset() = 0;

	/**	Function to set the session preferences for duplicating objects. Step and Repeat
		dialog sets these values, they are used when duplicating objects via keyboard shortcut.
		@param newOffset the y offset in pasteboard units for duplicating objects.
	 */
	virtual void SetYOffset(const PMReal newOffset) = 0;

	/**	Return the y offset vale.
		@param none
		@return PMReal the y offset value for duplicating objects. 
	 */
	virtual const PMReal GetYOffset() = 0;

};

#endif
