//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CImageReadFormat.h $
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
#ifndef __CIMAGEREADFORMAT__
#define __CIMAGEREADFORMAT__

#include "IImageReadFormat.h"
#include "IImageStream.h"

class IPMStream;
class IImageAttributes;
class IGraphicLayerInfo;

class CImageReadFormat : public IImageReadFormat
{
public:
	virtual bool16 Open(IPMStream* /* iPMStream */) { return kFalse; }

	virtual bool16 GetImageAttributes(IImageAttributes* /* iImageAttributes */) { return kFalse; }
	
	virtual bool16 GetGraphicLayerInfo(IGraphicLayerInfo* /* iLayerInfo */) { return kFalse; }
	
	virtual bool16 Close() { return kFalse; }

	virtual bool16 CanRead(IPMStream* /* iPMStream */) { return kFalse; }

	virtual bool16 SetFormatOption (uint32 /* formatOption*/ , uint32& /* formatData */) { return kFalse; }

	virtual bool16 ReadData(ImageStreamRecord& /* outRecord */) { return kFalse; }
};

#endif
