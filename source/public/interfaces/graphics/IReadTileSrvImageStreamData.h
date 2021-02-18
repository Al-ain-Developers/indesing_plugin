//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IReadTileSrvImageStreamData.h $
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
#ifndef __IReadTileSrvImageStreamData__
#define __IReadTileSrvImageStreamData__

#include "IPMUnknown.h"
#include "PDFID.h"
#include "BravoForwardDecl.h"

/** 
 Data interface for storing an AGMImage * for use by the virtual image reader 
 segment in the image stream manager. A misnomer in current InDesign, but kept
 for historical reasons.
 
 This interface is not generally useful for third party developers as it uses an 
 internal type.
 
 @see IImageStreamManager
 */
class IReadTileSrvImageStreamData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IREADTILESRVIMAGESTREAMDATA };

	/**
	 Sets the tiling server (an AGM image) to use when reading. Implicitly
	 bumps the reference count on the image.
	 
	 @param pAGMImage		The image to read
	 */
	virtual void SetTilingServer (AGMImage *pAGMImage) = 0;
	
	/**
	 Gets the tiling server (an AGM image) to read. Does not bump the
	 reference count on the returned image.
	 
	 @return the image to read
	 */
	virtual AGMImage *GetTilingServer () const = 0;
};

#endif
