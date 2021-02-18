//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/AnimationUIAnimateOptionTip.cpp $
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

#include "IDropDownListController.h"
#include "IStringListControlData.h"
#include "AbstractTip.h"

// ----- Includes -----

#include "AnimationTypes.h"

// ----- Utils -----

#include "IMenuUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"

class AnimationUIAnimateOptionTip : public AbstractTip
{			
public:
	AnimationUIAnimateOptionTip( IPMUnknown *boss ) : AbstractTip( boss ) {}
	virtual ~AnimationUIAnimateOptionTip() {}

	virtual PMString  GetTipText (const PMPoint& mouseLocation)
	{
		PMString tipString("");
		
		InterfacePtr<IDropDownListController> iListController (this, UseDefaultIID());
		InterfacePtr<IStringListControlData> iListData (iListController, UseDefaultIID());

		int32 selectedIndex = iListController->GetSelected();
		PMString animateString = (selectedIndex >= 0 && iListData->Length() > 0) ? iListData->GetString(selectedIndex) : kNullString;

		if (animateString == "kAnimationUIFrom")
			tipString = PMString ("kAnimationUIFromTip");
		else if (animateString == "kAnimationUITo")
			tipString = PMString ("kAnimationUIToTip");
		else if (animateString == "kAnimationUIOffset")
			tipString = PMString ("kAnimationUIOffsetTip");
		else
			tipString = PMString ("kAnimationUIAnimationOptionTip");

		return tipString;
	} 
};

CREATE_PMINTERFACE(AnimationUIAnimateOptionTip, kAnimationUIAnimateOptionTipImpl)


