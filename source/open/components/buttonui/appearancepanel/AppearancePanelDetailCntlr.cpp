//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/AppearancePanelDetailCntlr.cpp $
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
//  
//  I needed to override the panel moving behavior of SetsPanelDetailController, hence this
//  file - twright 08/02/2001
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface Includes -----

#include "IAppearanceSuite.h"
#include "IControlView.h"
#include "IEVEUtils.h"
#include "IPanelControlData.h"

// ----- Implementation Includes -----

#include "SelectionUtils.h"
#include "setspaneldetailcontroller.h"

#include "Utils.h"

#include "FormFieldUIID.h"
#include "BehaviorUIID.h"

//----------------------------------------------------------------------------------------

class AppearancePanelDetailController : public SetsPanelDetailController
{
public:
	AppearancePanelDetailController(IPMUnknown *boss);
	virtual void	ShowDetailLevel(int16 nthLevel);
	virtual int16	GetDefaultDetailLevel() const { return 1; }
};

//========================================================================================
// METHODS AppearancePanelDetailController
//========================================================================================

CREATE_PERSIST_PMINTERFACE(AppearancePanelDetailController, kAppearancePanelDetailControllerImpl)

	//----------------------------------------------------------------------------------------
	// AppearancePanelDetailController::AppearancePanelDetailController
	//----------------------------------------------------------------------------------------

	AppearancePanelDetailController::AppearancePanelDetailController(IPMUnknown *boss) :
SetsPanelDetailController(boss)
{
}

//----------------------------------------------------------------------------------------
// AppearancePanelDetailController::ShowDetailLevel
//----------------------------------------------------------------------------------------

void AppearancePanelDetailController::ShowDetailLevel(int16 nthLevel)
{
	PreDirty ();

	InterfacePtr<IPanelControlData> panel(this, IID_IPANELCONTROLDATA);

	IControlView *listContainer = panel->FindWidget(kStateListBoxesContainerWidgetID);
	IControlView *smallList = panel->FindWidget(kStateListSmallWidgetID);
	IControlView *medList = panel->FindWidget(kStateListMediumWidgetID);
	IControlView *largeList = panel->FindWidget(kStateListLargeWidgetID);
	IControlView *hugeList = panel->FindWidget(kStateListExtraLargeWidgetID);
	IControlView *AppearanceTextWidget = panel->FindWidget(kToggleStatesTextWidgetID);

	// show the lists only if the selection has an appearance list..
	InterfacePtr<IAppearanceSuite> iAppearanceSuite( SelectionUtils::QuerySuite<IAppearanceSuite>() );
	bool ShowAppearanceDetail = iAppearanceSuite && iAppearanceSuite->NumStates();

	if(ShowAppearanceDetail)
	{
		//		First time through the loop hide panels not in the set (pass == 0),
		//		Second time through the loop show panels in the set (pass == 1).
		// 		This allows correct redraw when certain widgets overlap (listboxes).
		AppearanceTextWidget->ShowView();
		listContainer->ShowView();
		for ( int pass = 0; pass < 2; ++pass )
		{		
			if ( (nthLevel & 0xFF) == 0 )
			{
				if ( pass )
				{
					smallList->ShowView();
				}
				else
				{
					medList->HideView();
					largeList->HideView();
					hugeList->HideView();
				}
			}
			else if ( (nthLevel & 0xFF) == 1 )
			{
				if ( pass ) 
				{
					medList->ShowView();
				}
				else
				{
					smallList->HideView();
					largeList->HideView();
					hugeList->HideView();
				}
			}
			else if ( (nthLevel & 0xFF) == 2 )
			{
				if ( pass )
				{
					largeList->ShowView();
				}
				else
				{
					smallList->HideView();
					medList->HideView();
					hugeList->HideView();
				}
			}
			else if ( (nthLevel & 0xFF) == 3 )
			{
				if ( pass )
				{
					hugeList->ShowView();
				}
				else
				{
					smallList->HideView();
					medList->HideView();
					largeList->HideView();
				}
			}
		}
	}
	else
	{
		// hide all..
		smallList->HideView();
		medList->HideView();
		largeList->HideView();
		hugeList->HideView();
		AppearanceTextWidget->HideView();
		listContainer->HideView();
	}

	// ----- Resize the panel to fit around the visible subpanels.

	InterfacePtr<IControlView> panelView(this, IID_ICONTROLVIEW);


	// This panel is now uses EVE widgets, so instead of moving everything
	// around, let's let EVE "compose" the layout for us.
	Utils<IEVEUtils>()->ApplyEveLayout(panelView);
	panelView->Invalidate();
	fCurrentLevel = nthLevel;
}
