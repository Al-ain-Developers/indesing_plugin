//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionmenus/StandardActionMenus.cpp $
//  
//  Owner: Tim Wright
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

#include "CPMUnknown.h"
#include "IBehaviorEvent.h"
#include "IActionMenuService.h"
#include "IActionMenuManager.h"

// ----- Implementation Includes -----

#include "BehaviorID.h"
#include "CServiceProvider.h"	
#include "ActionMenuPositions.h"	

//========================================================================================
// CLASS StandardActionMenus
//========================================================================================

class StandardActionMenus : public CPMUnknown<IActionMenuService>
{
public:
	StandardActionMenus(IPMUnknown *boss);

	void AddEventMenuItems(IActionMenuManager* inBehaviorMenuMgr);
	void AddBehaviorMenuItems(IActionMenuManager* inBehaviorMenuMgr);
};

//========================================================================================
// METHODS StandardActionMenus
//========================================================================================

CREATE_PMINTERFACE(StandardActionMenus, kStandardActionMenusImpl)

//----------------------------------------------------------------------------------------

StandardActionMenus::StandardActionMenus(IPMUnknown *boss) :
	CPMUnknown<IActionMenuService>(boss) 
{
}

//----------------------------------------------------------------------------------------

void StandardActionMenus::AddEventMenuItems(IActionMenuManager* inActionMenuManager)
{
	inActionMenuManager->AddEventMenuItem(kMouseUpEvt, "", kMouseUpEvtPosition);
	inActionMenuManager->AddEventMenuItem(kMouseDownEvt, "", kMouseDownEvtPosition);
	inActionMenuManager->AddEventMenuItem(kMouseEnterEvt, "", kMouseEnterEvtPosition);
	inActionMenuManager->AddEventMenuItem(kMouseExitEvt, "", kMouseExitEvtPosition);
	
	inActionMenuManager->AddEventSeparatorItem(kOnFocusEvt, kFocusEvtSepPosition);
	inActionMenuManager->AddEventMenuItem(kOnFocusEvt, "", kOnFocusEvtPosition);
	inActionMenuManager->AddEventMenuItem(kOnBlurEvt, "", kOnBlurEvtPosition);

	inActionMenuManager->AddEventSeparatorItem(kPageOpenEvt, kPageEvtSepPosition);
	inActionMenuManager->AddEventMenuItem(kPageOpenEvt, "", kPageOpenEvtPosition);
	inActionMenuManager->AddEventMenuItem(kPageCloseEvt, "", kPageCloseEvtPosition);

	inActionMenuManager->AddEventSeparatorItem(kFormatEvt, kFormatEvtSepPosition);
	inActionMenuManager->AddEventMenuItem(kFormatEvt, "", kFormatEvtPosition);
	inActionMenuManager->AddEventMenuItem(kKeystrokeEvt, "", kKeystrokeEvtPosition);
	inActionMenuManager->AddEventMenuItem(kValidateEvt, "", kValidateEvtPosition);
	inActionMenuManager->AddEventMenuItem(kCalculateEvt, "", kCalculateEvtPosition);

	inActionMenuManager->AddEventSeparatorItem(kSignedEvt, kSignedEvtPosition);
	inActionMenuManager->AddEventMenuItem(kSignedEvt, "", kSignedEvtSepPosition);

	inActionMenuManager->AddEventSeparatorItem(kSelectionChangedEvt, kSelectionChangedSepEvtPosition);
	inActionMenuManager->AddEventMenuItem(kSelectionChangedEvt, "", kSelectionChangedEvtPosition);
}


//----------------------------------------------------------------------------------------

void StandardActionMenus::AddBehaviorMenuItems(IActionMenuManager* inActionMenuManager)
{
	//This is where we will add the behavior menu ordering...
}
