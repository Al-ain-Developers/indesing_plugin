//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IImageShiftUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IImageShiftUtils__
#define __IImageShiftUtils__

#include "ImageID.h"
#include "IPMUnknown.h"
#include "Utils.h"

/**
	IImageShiftUtils is a utility class used to shift a row of image data a specified number
	of bits to the left or right.
	i.e. Utils<IImageShiftUtils>()->ShiftImageRowLeft( ... ) ;
	@ingroup layout_util
*/
class IImageShiftUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMAGESHIFTUTILS };

	/**
	 Shift the image row to the left shiftAmount bits.  Put the overflow in overflowByte 
	(up to 8 bits of overflow, the extra falls off the edge)

	 @param shiftAmount - IN: The number of bits by which to shift the entire row to the left.
	 @param bufLen - IN: The number of bytes in the inBuffer
	 @param inBuffer - IN/OUT: A pointer to the buffer containing the image data to shift.
	 @param overflowByte - OUT: pointer to a byte which will contain the overflow data.
	*/
	virtual void ShiftImageRowLeft (uint16 shiftAmount, uint32 bufLen, uint8* inBuffer, uint8* overflowByte) = 0;

	/**
	 Shift the image row to the right shiftAmount bits.  Put the overflow in overflowByte 
	 (up to 8 bits of overflow, the extra falls off the edge)

	 @param shiftAmount - IN: The number of bits by which to shift the entire row to the right.
	 @param bufLen - IN: The number of bytes in the inBuffer
	 @param inBuffer - IN/OUT: A pointer to the buffer containing the image data to shift.
	 @param overflowByte - OUT: pointer to a byte which will contain the overflow data.
	*/
	virtual void ShiftImageRowRight (uint16 shiftAmount, uint32 bufLen, uint8* inBuffer, uint8* overflowByte) = 0;

};


#endif	// __IImageShiftUtils__
