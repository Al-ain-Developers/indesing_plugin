//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIEventInfoTip.cpp $
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

#include "IIntData.h"
#include "AbstractTip.h"
#include "IIntList.h"
#include "IControlView.h"
#include "IAnimationAttributeSuite.h"
#include "ISpreadDynamicContentMgr.h"
#include "IAnimationUtils.h"
#include "ISelectionUtils.h"

// ----- Includes -----

#include "AnimationTypes.h"

// ----- Utils -----

#include "IMenuUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class AnimationUIEventInfoTip : public AbstractTip
{			
	public:
		AnimationUIEventInfoTip( IPMUnknown *boss );
		virtual ~AnimationUIEventInfoTip();

		virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE(AnimationUIEventInfoTip, kAnimationUIEventInfoTipImpl)

AnimationUIEventInfoTip::AnimationUIEventInfoTip(IPMUnknown *boss) :
	AbstractTip( boss )
{
}

AnimationUIEventInfoTip::~AnimationUIEventInfoTip()
{
}

PMString AnimationUIEventInfoTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString("");
	
	InterfacePtr<IIntData> iNumTriggers(this, IID_IANIMATIONTRIGGERTYPEDATA);
	InterfacePtr<IControlView> iInfoView (this, UseDefaultIID ());
	if (iNumTriggers)
	{
		int32 numTrigger = iNumTriggers->Get();
		if (numTrigger == 0)
		{
			if (iInfoView->IsEnabled ())
				tipString = PMString("kAnimationPanelEventMenuSelectorTip");
			else
				tipString = PMString("kAnimationPanelEventInfoDefaultTip");
		}
		else
		{
			tipString = PMString("kAnimationPanelEventInfoTip");

			ISelectionManager* iActiveSeltion = Utils<ISelectionUtils> ()->GetActiveSelection ();
			InterfacePtr<IAnimationAttributeSuite> iAttrSuite (iActiveSeltion, UseDefaultIID ());
			if (iAttrSuite != nil)
			{
				ISpreadDynamicContentMgr::DynamicContentType contentType = ISpreadDynamicContentMgr::kAnimationItemType;
				if (iAttrSuite->HasMSOAsTimingParent ()) contentType = ISpreadDynamicContentMgr::kMultiStateItemType;

				InterfacePtr<IIntList> iInfoData (this, UseDefaultIID ());
				if (iInfoData && iInfoView->IsEnabled ())
				{
					tipString.Translate ();
					tipString.Append (": ");
					for (int32 n = 0; n < iInfoData->Length (); n++)
					{
						PMString nthEventInfo = Utils<IAnimationUtils>()->GetStringFromEventTrigger (static_cast<EventTriggerType>(iInfoData->Get (n)), contentType);
						nthEventInfo.Translate();
						if (n > 0) tipString.Append (", ");
						tipString.Append (nthEventInfo);
					}
				}
			}
		}
	}

	return tipString;
} 

