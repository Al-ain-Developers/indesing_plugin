//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIManagePresetItemListBoxCtrl.cpp $
//  
//  Owner: Yeming Liu
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

#include "VCPlugInHeaders.h"

// ----- Interfaces -----

#include "IApplication.h"
#include "IMotionPresetMgr.h"

// ----- Includes -----

#include "CTreeBasedListBoxController.h"

// ----- Utility files -----

#include "IMotionPresetUtils.h"
#include "Utils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class AnimationUIManagePresetItemListBoxCtrl : public CTreeBasedListBoxController
{
	public:
		AnimationUIManagePresetItemListBoxCtrl(IPMUnknown *boss) : CTreeBasedListBoxController(boss) {}
		virtual PMString GetNthItemString(int32 itemIndex) const;
};

CREATE_PMINTERFACE(AnimationUIManagePresetItemListBoxCtrl, kAnimationUIManagePresetItemListBoxCtrlImpl)

PMString AnimationUIManagePresetItemListBoxCtrl::GetNthItemString(int32 itemIndex) const
{		
	PMString presetName(kNullString);

	InterfacePtr<IMotionPresetMgr> iAppPresetMgr (Utils<IMotionPresetUtils>()->QueryMotionPresetManager ()); 

	int32 numPresets = iAppPresetMgr->GetNumPresets();
	if (itemIndex >= 0 && itemIndex < numPresets)
	{
		ErrorCode result = iAppPresetMgr->GetNthPresetName(itemIndex, presetName);
		if (result == kSuccess)
			return presetName;
	}

	return presetName;
}
