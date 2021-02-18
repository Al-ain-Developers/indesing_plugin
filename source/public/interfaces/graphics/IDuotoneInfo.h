//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDuotoneInfo.h $
//  
//  Owner: David Berggren
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
//  Purpose:
//  Stores info about duotone inks read in from a placed graphic (i.e. PSD file)
//  
//========================================================================================

#pragma once
#ifndef __IDuotoneInfo__
#define __IDuotoneInfo__

#include "IPMUnknown.h"
#include "IColorData.h"
#include "ImageID.h"
#include "PMString.h"

/** 
	An interface for holding the duotone ink information for
	placed graphics such as Photoshop (PSD) files.
*/
class IDuotoneInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDUOTONEINFO };

	// ***********************
	// Add/Remove methods
	// ***********************

	/**	Append an ink into the interface. 
		@param inkName IN a PMString containing a ink name.
		@param colorSpace IN the color space of the ink, i.e. kPMCsCalCMYK
		@param colorData IN the color space's color data information
		@param clut IN a pointer to a 256 byte array containing the inks CLUT. The
		               information is copied out of the CLUT that is passed in.
	*/
	virtual void AppendDuotoneInk (	const PMString&					inkName, 
									int32							colorSpace,
									const ColorArray&				colorData,
									uint8*							clut
									) = 0;

	/**	Remove a ink from the interface.
		@param index IN the index (0 based) of the ink to remove.
	*/
	virtual void RemoveInk ( uint32 index ) = 0;

	/**	Clear all inks out of the interface.
	*/
	virtual void Clear() = 0;

	// ***********************
	// Set methods
	// ***********************

	/**	Set the ink name of a given ink index.
		@param index IN the index (0 based) of the ink to rename.
		@param newName IN the new name to be given to the ink
	*/
	virtual void SetInkName (uint32 index, const PMString& newName) = 0;

	/**	Set the ink color information of a given ink index.
		@param index IN the index (0 based) of the ink to change.
		@param colorSpace IN the new color space to be given to the ink, i.e. kPMCsCalCMYK 
		@param colorData IN the color space's color data information
	*/
	virtual void SetInkColor (uint32 index, int32 colorSpace, const ColorArray& colorData) = 0;

	/**	Set the ink CLUT information of a given ink index.
		@param index IN the index (0 based) of the ink to change.
		@param clut IN a pointer to an array of 256 entries ranging from 0x00 to 0xFF. The
		CLUT data is copied out of the array that is passed in.
	*/
	virtual void SetInkCLUT (uint32 index, uint8* clut) = 0;

	// ***********************
	// Get methods
	// ***********************

	/**	Get the number of inks currently stored in the interface. For use when iterating
		through the inks, setting or getting specific information. 1 ink == Monotone image,
		2 inks == Duotone image, 3 inks == Tritone image, 4 inks == Quadtone image.
		@return int32 of the number of inks. 
	*/
	virtual uint32 GetNumberInks () const = 0;

	/**	Get the ink name of a given ink index.
		@param index IN the index (0 based) of the ink to get.
		@return PMString of the ink name. 
	*/
	virtual PMString				GetNthInkName (uint32 index) const = 0;
	/**	Get the ink color space of a given ink index.
		@param index IN the index (0 based) of the ink to get.
		@return int32 of the ink color space, i.e. kPMCsCalCMYK 
	*/
	virtual int32					GetNthInkColorSpace (uint32 index) const = 0;
	/**	Get the ink color data of a given ink index.
		@param index IN the index (0 based) of the ink to get.
		@return ColorArray of the ink color data - see IColorData.h
	*/
	virtual ColorArray				GetNthInkColorData (uint32 index) const = 0;
	/**	Get the ink CLUT of a given ink index.
		@param index IN the index (0 based) of the ink to get.
		@param clut OUT a pointer to a 256 byte array to recieve CLUT values.
		@return ErrorCode - kSuccess if successful, kFailure otherwise 
	*/
	virtual ErrorCode				GetNthInkCLUT (uint32 index, uint8* clut) const = 0;

};

#endif
