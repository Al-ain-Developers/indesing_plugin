//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUIButtonTips.cpp $
//  
//  Owner: lance bushore
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
#include "IControlView.h"
#include "AbstractTip.h"
#include "IApplication.h"
#include "IActionManager.h"
#include "PMString.h"

#include "CPMUnknown.h"
#include "LinksUIID.h"
#include "ActionStateList.h"

class LinksUIButtonTips : public AbstractTip
{			
public:
	LinksUIButtonTips( IPMUnknown *boss );
	virtual ~LinksUIButtonTips();

	virtual PMString  GetTipText(const PMPoint& mouseLocation);
};

CREATE_PMINTERFACE( LinksUIButtonTips, kLinksUIButtonTipsImpl )


LinksUIButtonTips::LinksUIButtonTips(IPMUnknown *boss) :
	AbstractTip( boss )
{
} 



LinksUIButtonTips::~LinksUIButtonTips()
{
} 


PMString LinksUIButtonTips::GetTipText(const PMPoint& mouseLocation)
{
#pragma unused(mouseLocation)

	ActionID menuActionForButton = kInvalidActionID;
	InterfacePtr<const IControlView> myView(this,UseDefaultIID());
	WidgetID myWidgetID = myView->GetWidgetID();
	switch(myWidgetID.Get())
	{
		case kRelinkButtonWidgetID:
			menuActionForButton = kLinksUIRelinkActionID;
			break;
		case kCCRelinkButtonWidgetID:
			menuActionForButton = kLinksUIRelinkToCloudAssetActionID;
			break;
        case kAALRelinkButtonWidgetID:
            menuActionForButton = kLinksUIRelinkToAALAssetActionID;
            break;
		case kUpdateLinkButtonWidgetID:
			menuActionForButton = kLinksUIUpdateLinkActionID;
			break;
		case kEditOriginalButtonWidgetID:
			return "#EditOriginalButtonTip";
			break;
		case kGotoLinkButtonWidgetID:
			return "#GotoLinkButtonTip";
			break;
		
	}
	if(menuActionForButton != kInvalidActionID)
	{
		// update the menu item, and get the string for the action to use as the tip.
		InterfacePtr<const IApplication> app(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IActionManager> actionMgr(app->QueryActionManager());
		
		ActionStateList updateList;
		updateList.AddActionID(menuActionForButton);
		actionMgr->UpdateActionStates(GetExecutionContextSession()->GetActiveContext(), &updateList);
		
		InterfacePtr<IControlView> view(this,UseDefaultIID());
		PMString tipString = updateList.GetNthActionName(0);
		if(myWidgetID == kUpdateLinkButtonWidgetID)
		{
			tipString.Translate();
#ifdef MACINTOSH
			PMString additionalTipStr("#appendedUpdateButtonTipMac");
#else
			PMString additionalTipStr("#appendedUpdateButtonTipWin");
#endif			
			additionalTipStr.Translate();
			tipString.Append(additionalTipStr);
		}
		else if(myWidgetID == kRelinkButtonWidgetID)
		{
			tipString.Translate();
#ifdef MACINTOSH
			PMString additionalTipStr("#appendedRelinkButtonTipMac");
#else
			PMString additionalTipStr("#appendedRelinkButtonTipWin");
#endif			
			additionalTipStr.Translate();
			tipString.Append(additionalTipStr);
		}
		else if (myWidgetID == kCCRelinkButtonWidgetID || myWidgetID == kAALRelinkButtonWidgetID )
		{
			tipString.Translate();
		}
		return tipString;
		
	}		
	return "";
} 
