//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIPanelDetailController.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IPanelDetailController.h"
#include "IPanelControlData.h"
#include "IPMStream.h"
#include "IControlView.h"

// ----- Implementation Includes -----

#include "CPMUnknown.h"
#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsUIDefs.h"
#include "DynamicDocumentsUIUtils.h"
#include "IconRsrcDefs.h"

//______________________________________________________________________________
//	The animation panel has three different detail configurations:
//	0: preview, main property, sub property control, control strip (default)
//		==> showPreview = true, showSubProperty = false
//	1: preview, main property, sub property control, sub property, control strip
//		==> showPreview = true, showSubProperty = true
//	2: main property, sub property control
//		==> showPreview = false, showSubProperty = false
//	______________________________________________________
//	3: main property, sub property, sub property control, control strip
//		==> showPreview = false, showSubProperty = true
//______________________________________________________________________________

class AnimationUIPanelDetailController : public CPMUnknown<IPanelDetailController>
{
	enum {kPreviewPlusMainConfig = 0, kFullPanelConfig, kMainPropertyOnly, kNumPanelConfigs};
	enum {kMainAndSubProperty = kNumPanelConfigs};
	enum {kDefaultPanelConfig = kPreviewPlusMainConfig};
	int32 fCurrentConfig;

public:
	AnimationUIPanelDetailController(IPMUnknown *boss) : 
		CPMUnknown<IPanelDetailController>(boss), fCurrentConfig (kDefaultPanelConfig) {}
	virtual ~AnimationUIPanelDetailController() {}
	
	void ReadWrite(IPMStream *s, ImplementationID prop)
	{
		bool16 readingFromResource = kFalse;
		s->XferBool(readingFromResource);
		s->XferInt32 (fCurrentConfig);

	}

	virtual void RotateDetailLevel()
	{
		PreDirty ();
		int32 nextDetail = static_cast<int32>(std::fmod(static_cast<double>(++fCurrentConfig), static_cast<double>(kNumPanelConfigs)));
		fCurrentConfig = nextDetail;

		ShowPanelConfig (fCurrentConfig);
	}

	virtual void ShowDetailLevel(int16 nthLevel)
	{
		if (fCurrentConfig != nthLevel)
		{
			PreDirty ();
			fCurrentConfig = nthLevel;
		}
		ShowPanelConfig (fCurrentConfig);
	}

	virtual int16 GetDetailLevel() const
	{
		return fCurrentConfig;
	}

	//________________________________________________________________________________________
	// AnimationUIPanelDetailController::GetNumDetailLevels
	//________________________________________________________________________________________

	virtual int16 GetNumDetailLevels() const
	{
		return kNumPanelConfigs;
	}

	//________________________________________________________________________________________
	// AnimationUIPanelDetailController::GetDefaultDetailLevel
	//________________________________________________________________________________________

	virtual int16 GetDefaultDetailLevel() const
	{
		return kDefaultPanelConfig;
	}


private:
		
	void ShowPanelConfig (int32 detailLevel)
	{
		bool showPreview = false;
		bool showPropertySubPanel = false;

		if (detailLevel == kDefaultPanelConfig || detailLevel == kPreviewPlusMainConfig)
		{
			showPreview = true;
		}
		else if (fCurrentConfig == kFullPanelConfig)
		{
			showPreview = true;
			showPropertySubPanel = true;
		}
		else if (fCurrentConfig == kMainAndSubProperty)
		{
			showPropertySubPanel = true;
		}

		InterfacePtr<IControlView> iPanelView (this, UseDefaultIID ());
		ddui_utils::UpdateAnimationPanelSize (iPanelView, showPreview, showPropertySubPanel);
	}
};


CREATE_PERSIST_PMINTERFACE(AnimationUIPanelDetailController, kAnimationUIPanelDetailControllerImpl)

