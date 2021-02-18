//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPixelBenderData.h $
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
//  ADOBE CONFIDENTIAL
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

#include "DynamicDocumentsID.h"

#include "BravoForwardDecl.h"

class IPixelBenderData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPIXELBENDERDATA };
	
	virtual void Set(uint8 const *data, size_t count) = 0;
	virtual uint8 const *Get(size_t &count) const = 0;
	
	virtual BIBSharedBuffer *GetBuffer() const = 0;
	
	// Needs work, obviously.
	virtual void ClearParameters() = 0;
	virtual void SetParameter(PMString const &name, uint32 count, PMReal const *value) = 0;
	virtual void GetParameters(K2Vector<PMString> &params) const = 0;
	virtual bool GetParameterCount(PMString const &name, uint32 &count) const = 0;
	virtual bool GetParameter(PMString const &name, PMReal *value) const = 0;
	
	virtual bool IsValid() const = 0;
};
