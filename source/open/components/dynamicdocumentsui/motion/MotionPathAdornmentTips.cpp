//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/motion/MotionPathAdornmentTips.cpp $
//  
//  Owner: Paul Sorrick
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

#include "AbstractTip.h"
#include "ITool.h"
#include "IToolToggleBehavior.h"

// ----- Includes -----

#include "KBSCModifierDefs.h"
#include "KeyStates.h"
#include "PMString.h"

// ----- Utils -----

#include "IToolBoxUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"


// Local helper function to determine if tips should be show for motion path adornment handle shape or not
bool16 IsMotionPathTipActive();
bool16 IsMotionPathTipActive()
{
	InterfacePtr<ITool> activeTool(Utils<IToolBoxUtils>()->QueryActiveTool());
	InterfacePtr<IToolToggleBehavior> toolToggleBehavior(activeTool, IID_ITOOLTOGGLEBEHAVIOR);
	ClassID activeToolID = (activeTool == nil ? kInvalidClass : ::GetClass(activeTool));
	int16 modifiers = ::GetKBSCModifierKeys();
	bool16 bDoPointerToolToggle = toolToggleBehavior && toolToggleBehavior->IsPointerToolToggleEnabled(modifiers);

	// Only show tips when using pointer or direct select tool, or using command/ctrl key to toggle to the tool.
	if (activeToolID == kPointerToolBoss || activeToolID == kDirectSelectToolBoss || (bDoPointerToolToggle && (modifiers & kControl)))
		return kTrue;

	return kFalse;
}

class MotionPathAdornmentTip : public AbstractTip
{
public:
    MotionPathAdornmentTip( IPMUnknown *boss );
	virtual ~MotionPathAdornmentTip() {}
    virtual PMString  GetTipText(const PMPoint& mouseLocation);

};

CREATE_PMINTERFACE( MotionPathAdornmentTip, kMotionPathAdornmentTipImpl )

MotionPathAdornmentTip::MotionPathAdornmentTip(IPMUnknown *boss) : 
	AbstractTip( boss )
{
}

PMString  MotionPathAdornmentTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString;
	
	if (IsMotionPathTipActive())
		tipString = PMString("kMotionPathTipStr");

    return tipString;
}

class EasingPathAdornmentTip : public AbstractTip
{
public:
    EasingPathAdornmentTip( IPMUnknown *boss );
	virtual ~EasingPathAdornmentTip() {}
    virtual PMString  GetTipText(const PMPoint& mouseLocation);

};

CREATE_PMINTERFACE( EasingPathAdornmentTip, kEasingPathAdornmentTipImpl )

EasingPathAdornmentTip::EasingPathAdornmentTip(IPMUnknown *boss) : 
	AbstractTip( boss )
{
}

PMString  EasingPathAdornmentTip::GetTipText(const PMPoint& mouseLocation)
{
	PMString tipString;
	if (IsMotionPathTipActive())
		tipString = PMString("kEasingPathTipStr");
    
	return tipString;
}


