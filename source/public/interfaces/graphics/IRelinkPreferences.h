//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRelinkPreferences.h $
//  
//  Owner: Dave Stephens
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
#ifndef __IRelinkPreferences__
#define __IRelinkPreferences__

#include "IPMUnknown.h"
#include "ImageID.h"

/** IRelinkPreferences
	Preferences for the behavior of relink when relinking graphics.
*/
class IRelinkPreferences : public IPMUnknown
{
public:
	/** default IID for this interface */
	enum { kDefaultIID = IID_IRELINKPREFERENCES };

	/** When relinking images, set whether or not to preserve
		the bounds of the image that is being replaced.
		@param doPreserveBounds [IN]: kTrue to preserve bounds
	*/
	virtual void SetPreserveBoundsOnRelink(bool16 doPreserveBounds) = 0;

	/** Get whether or not to preserve image bounds when relinking images.
		@return kTrue if preserving bounds.
	*/
	virtual bool16 GetPreserveBoundsOnRelink() const = 0;

	/**
	 Identifiers which denote which folder to initially target in the relink file dialog.
	 */
	enum DefaultRelinkFolder {
		/** Target the most recently used relink folder. */
		kMostRecentFolder = 0,
		/** Target the link's original folder. */
		kOriginalFolder
	};
	
	/** Set the "Default Relink Folder" preference. */
	virtual void SetDefaultRelinkFolder(DefaultRelinkFolder defaultRelinkFolder) = 0;
	/** Get the "Default Relink Folder" preference. */
	virtual DefaultRelinkFolder GetDefaultRelinkFolder() const = 0;

	/** Set the value for the 'Search for Missing Files in this Folder after relinking' preference */
	virtual void SetSearchForMissing(bool16 search) = 0;
	/** Get the value for the 'Search for Missing Files in this Folder after relinking' preference */
	virtual bool16 GetSearchForMissing() const = 0;
};

#endif
