//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIXFProxyEH.cpp $
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

#include "C9PointProxyEH.h"

#include "IControlView.h"
#include "IDVUINodeRef.h"
#include "IEvent.h"
#include "IWidgetParent.h"
#include "ISubject.h"
#include "IIntData.h"
#include "IProxyWidgetAttributes.h"

#include "DynamicDocumentsUIID.h"
#include "DynamicDocumentsUIUtils.h"

class AnimationUIXFProxyEH : public C9PointProxyEH
{
public:
	AnimationUIXFProxyEH(IPMUnknown* boss) : C9PointProxyEH(boss)
		{}

	virtual bool16 LButtonDn(IEvent* e)
	{
		ddui_utils::UpdateAnimationItemName (nil, this);

		return C9PointProxyEH::LButtonDn (e);
	}

	virtual bool16 CanHaveKeyFocus() const { return kTrue; }

protected:
	void ChangeReferencePosition(IReferencePointData::ReferencePointPosition newPosition)
	{
		InterfacePtr<IWidgetParent> iParent (this, UseDefaultIID());
		InterfacePtr<IControlView> iXFProxyView (this, UseDefaultIID());

		InterfacePtr<IProxyWidgetAttributes> iXFProxyAttr(this, UseDefaultIID());
		iXFProxyAttr->SetProxyPosition (newPosition);

		// Notify
		InterfacePtr<ISubject> iSubject (this, IID_ISUBJECT);
		if (iSubject)
		{
			iSubject->Change(kWidgetPositionChangedMessage, IID_IPROXYWIDGETATTRIBUTES, iXFProxyView);
		}
	}
};

CREATE_PMINTERFACE(AnimationUIXFProxyEH, kAnimationUIXFProxyEHImpl)


