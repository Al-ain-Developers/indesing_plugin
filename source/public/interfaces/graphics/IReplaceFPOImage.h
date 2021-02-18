//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IReplaceFPOImage.h $
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
#ifndef __IReplaceFPOImage__
#define __IReplaceFPOImage__

#include "ImageID.h"

class IPMStream;

class IReplaceFPOImage : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREPLACEFPOIMAGE };

	enum Mode
	{
		kReplaceIfInteract,		// Replace image only if interacts with XP
		kReplaceAlways,			// Replace image in all cases
		kNeverReplace,			// Never replace image
		kUnsupportedImage		// Image not supported by this implementation
	};

	/**
	 Asks implementation how given image should be treated. If the impl can
	 handle the specified image, it should return one of kReplaceIfInteract,
	 kReplaceAlways, or kNeverReplace to indicate how the image should be
	 handled. If it cannot handle the specified image, it should return
	 kUnsupportedImage to indicate that another service be given a chance to
	 replace the image

	 @param image		UIDRef for the image
	 @return a value from the Mode enum
	 */
	virtual Mode GetReplaceModeForImage(UIDRef const &image) const = 0;

	/**
	 Queries for the replacement IPMStream for the specified image. This will
	 be called if the impl previously indicated that it wanted to replace the
	 given image (by returning either kReplaceIfInteract or kReplaceAlways)
	 
	 If an error occurs, the impl should return a nil interface. This will abort 
	 the print/export operation.

	 @param fpoImage	UIDRef for the FPO image. The service should use this 
						to identify the image to be replaced.
	 @return an addref'd pointer to an IPMStream interface, or nil if an error
		occurs
	 */

	virtual IPMStream *ReplaceFPOImage(UIDRef const &fpoImage) = 0;
};

#endif //!def __IReplaceFPOImage__
