//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IOPIInfo.h $
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
//  Holds the information gathered from OPI (Open Prepress Interface) comments
//  embedded in EPS files. This interface hangs off the kEPSItemBoss. This 
//  information is used by the OPI print engine when printing a placed EPS.	
//  
//========================================================================================

#pragma once
#ifndef __IOPIInfo__
#define __IOPIInfo__

#include "IPMUnknown.h"
#include "IPMStream.h"
#include "PMString.h"
#include "PMRect.h"

class IOPIInfo : public IPMUnknown  
{ 
public:
	// Set methods
	
	virtual void SetEmpty(void) = 0; 
	virtual void SetOPI13(const bool16 isOPI13) = 0;
	virtual void SetFileName(const PMString fileName) = 0;
	virtual void SetHResolution(const uint32 res) = 0;
	virtual void SetVResolution(const uint32 res) = 0;
	virtual void SetPixelWidth(const PMReal width) = 0;
	virtual void SetPixelHeight(const PMReal height) = 0;
	virtual void SetCropRect(const double l, const double t, const double r, const double b) = 0;
	virtual void SetCropRect(const PMRect rect) = 0;
	virtual void SetNumChannel(const uint16 sample) = 0;
	virtual void SetBitsPerChannel(const uint16 bits) = 0;
	
	// Access methods
	
	virtual PMString ImageFileName(void) const = 0;
	virtual uint32 HResolution(void) const = 0;
	virtual uint32 VResolution(void) const = 0;
	virtual PMReal PixelWidth(void) const = 0;
	virtual PMReal PixelHeight(void) const = 0;
	virtual PMRect CropRect(void) const = 0;
	virtual uint16 NumChannel(void) const = 0;
	virtual uint16 BitsPerChannel(void) const = 0;
	virtual bool16 IsOPI13(void) const = 0;
	virtual bool16 IsEmpty(void) const = 0;

	// Copy method
	virtual void CopyOPIInfo (const IOPIInfo* otherInfo) = 0;
};


#endif