//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMotionTestUtils.h $
//
//  Owner: SusanCL
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
//  
//  Test Menu
//  
//========================================================================================
#pragma once
#ifndef __IMotionTestUtils__
#define __IMotionTestUtils__

#include "IPMUnknown.h"
#include "DynamicDocumentsID.h"
#include "Utils.h"

class IMotionTestUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IMOTIONTESTUTILS };
	
	//virtual bool ApplyMotionPreset (const UIDList& itemList, const IDFile& presetFile, PMString& restult) = 0;
	virtual bool ApplyMotionPreset (const UIDList& itemList, const UIDRef& presetRef, PMString& restult) = 0;

	virtual boost::shared_ptr<uint8> PeekPresetAsIDMotionXML (const UIDRef& pageItemRef, size_t& bufSize) = 0;

	virtual bool PeekPresetAsXML (const UIDRef& presetRef, PMString& result) = 0;

	virtual void ValidateMSOStateTimingMgr (const UIDRef& msoStateRef) = 0;
};

#endif