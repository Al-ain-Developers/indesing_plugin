//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImageFormatAccess.h $
//  
//  Owner: jargast
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
#ifndef __IImageFormatAccess__
#define __IImageFormatAccess__

#include "IPMUnknown.h"
#include "ImageID.h"

/** Interface living off of an image boss which stores the format of the reader
	needed to read the image data.
*/
class IImageFormatAccess : public IPMUnknown
{
public:
	/** default IID for this interface 
	*/
	enum { kDefaultIID = IID_IIMAGEFORMATACCESS };

	/** We store the class ID of the image format plug-in that can
		read the image data.  In this way we can avoid finding the correct
		image format plug-in every time we render and/or export the image.
		@param classID - IN: ClassID of the read filter's plug-in.  Examples,
			kPSImageReadFormatBoss, kJPEGImageReadFormatBoss, kTIFFImageReadFormatBoss
	*/
	virtual void SetFormatClassID (ClassID classID) = 0;
	
	/** @return Retrieve the ClassID of the read filter
	*/
	virtual ClassID GetFormatClassID () const = 0;
	
	/** OBSOLETE
		This tells us which image in the file we are.  TIFF, for instance, allows
		for more than one image per file: a low res and a high res version in our
		case.  whichImage takes on either kPMHighResImage or kPMLowResImage (defined
		in ImageTypes.h)
		OBSOLETE: Some formats, such as TIFF, may have several images per file.  Hence,
		two constants are not enough to distinguish which image is in use.  Instead,
		the image resolution can be used as an identifier.  Each InDesign Class (boss)
		containing an IImageFormatAccess interface should also have an IImageAttributes
		interface which contain resolution tags.
	*/
	virtual void SetWhichImage (uint32 whichImage) = 0;
	
	/** OBSOLETE: See comments for SetWhichImage()
	*/
	virtual uint32 GetWhichImage () const = 0;

};


#endif
