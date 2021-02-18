//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISVGImportPrefs.h $
//  
//  Owner: Gaurav T Kakkar
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose:
//  Stores the current SVG import preferences. These preferences should
//  be set using the kSetSVGPrefsCmdBoss command.	
//  
//========================================================================================

#pragma once
#ifndef __ISVGImportPrefs__
#define __ISVGImportPrefs__

#include "IPMUnknown.h"
#include "PMReal.h"
#include "EPSID.h"


/** SVG Import Preferences - settings used when the SVG was imported.
	Use the kSetSVGPrefsCmdBoss command to set SVG import preferences!
*/
class ISVGImportPrefs : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ISVGIMPORTPREFS };
	/** Used for SVG import settings
	*/
	enum 
	{
		kCropToBBox,
		kCropToArt,
		kCropToClippingPath
	};

	/**  Determine whether we show a preview in the import options dialog.
	*/
	virtual bool16 GetShowPreview() const= 0;
	virtual void SetShowPreview(bool16 b) = 0;

	
	/** Method to store the CropTo information.
		@param newCropTo
	*/
	virtual void SetCropTo(int32 newCropTo) = 0;

	/** Method to get the CropTo information.
		@return the CropTo number.
	*/
	virtual int32 GetCropTo() const = 0;

	/** Method to copy preferences from one interface to another.
		@param toCopy is from where preferences are copied
	*/
	virtual void CopyData(ISVGImportPrefs* toCopy) = 0;
	
};

#endif
