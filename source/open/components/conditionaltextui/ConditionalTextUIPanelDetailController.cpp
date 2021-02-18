//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionalTextUIPanelDetailController.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IPanelDetailController.h"
#include "IPanelControlData.h"
#include "IPMStream.h"
#include "IControlView.h"
#include "IPanelDetailController.h"

// ----- Includes -----

#include "CPMUnknown.h"

// ----- Utility files -----

#include "IEVEUtils.h"
#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "ConditionalTextUIID.h"


class ConditionalTextUIPanelDetailController : public CPMUnknown<IPanelDetailController>
{
public:
	ConditionalTextUIPanelDetailController(IPMUnknown *boss);
	virtual ~ConditionalTextUIPanelDetailController();
	
	virtual void	ReadWrite(IPMStream *s, ImplementationID prop);

	virtual void	RotateDetailLevel();
	virtual void	ShowDetailLevel(int16 nthLevel);
	
	virtual int16	GetDetailLevel() const;
	virtual int16	GetNumDetailLevels() const;
	virtual int16	GetDefaultDetailLevel() const;
	

private:
	bool16			AreOptionsShown() const;
	void			ShowHidePanelOptions( bool16 );

	bool16			fOptionsShown; 
		
};

// =============================================================================
// *** ConditionalTextUIPanelDetailController impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(ConditionalTextUIPanelDetailController, kConditionalTextUIPanelDetailControllerImpl)

ConditionalTextUIPanelDetailController::ConditionalTextUIPanelDetailController(IPMUnknown *boss) :
	CPMUnknown<IPanelDetailController>(boss), fOptionsShown(kFalse)
{
}

// -----------------------------------------------------------------------------

ConditionalTextUIPanelDetailController::~ConditionalTextUIPanelDetailController()
{
}

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelDetailController::ReadWrite(IPMStream *s, ImplementationID prop)
{
	bool16 readingFromResource = kFalse;
	s->XferBool(readingFromResource);
	 
	if (s->IsWriting() || !readingFromResource)
	{
		s->XferBool(fOptionsShown);
	}
}

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelDetailController::RotateDetailLevel()
{
	if (AreOptionsShown())
		ShowDetailLevel(0);
	else
		ShowDetailLevel(1);
}

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelDetailController::ShowDetailLevel(int16 nthLevel)
{
	ShowHidePanelOptions( nthLevel == 0 ? kFalse : kTrue );
	
}

// -----------------------------------------------------------------------------

int16 ConditionalTextUIPanelDetailController::GetDetailLevel() const
{
	return AreOptionsShown() ? 1 : 0;
}

// -----------------------------------------------------------------------------

int16 ConditionalTextUIPanelDetailController::GetNumDetailLevels() const
{
	return 2;
}

// -----------------------------------------------------------------------------

int16 ConditionalTextUIPanelDetailController::GetDefaultDetailLevel() const
{
	return 0;
}

// -----------------------------------------------------------------------------

bool16 ConditionalTextUIPanelDetailController::AreOptionsShown() const
{
	return fOptionsShown;
}

// -----------------------------------------------------------------------------

void ConditionalTextUIPanelDetailController::ShowHidePanelOptions(bool16 showOptions)
{
	//	Resize panel to show the appropriate options.
	//	When set to "Show Options", all controls in the panel are visible.
	//	When set to "Hide Options", the condition set controls are hidden.

	if (fOptionsShown != showOptions)
	{
		PreDirty ();
		fOptionsShown = showOptions;
	}

	InterfacePtr<IPanelControlData>	panelData (this, UseDefaultIID ());

	// Hide/show the sets area; this is currently our only option.
	IControlView* setsAreaView = panelData->FindWidget(kConditionalTextUIPanelSetsAreaWidgetId);
	if (showOptions)
	{
		if (setsAreaView)
			setsAreaView->ShowView();
	}
	else
	{
		if (setsAreaView)
			setsAreaView->HideView();
	}

	// Move the control strip to adjust for hide/show of the sets area.
	IControlView* controlStripView = panelData->FindWidget(kConditionalTextUIPanelControlStripWidgetId);
	if (controlStripView)
	{
		// Move the control strip.
		PMRect controlStripRect = controlStripView->GetFrame();
		PMReal controlStripAreaTop(showOptions ? setsAreaView->GetFrame().Bottom() + 1 : setsAreaView->GetFrame().Top());
		controlStripRect.MoveTo(0,controlStripAreaTop);
		controlStripView->SetFrame(controlStripRect);

		// Remove the bottom binding on tree before changing panel bottom so won't resize.
		IControlView* listPanelWidget = panelData->FindWidget(kConditionalTextUIPanelListWidgetId);
		if (listPanelWidget)
			listPanelWidget->SetFrameBinding(kBindLeft|kBindRight|kBindTop);

		// Resize panel to bottom of new control strip position.
		InterfacePtr<IControlView> panelView(panelData, UseDefaultIID());
		PMRect panelRect = panelView->GetFrame();
		panelRect.Bottom(controlStripView->GetFrame().Bottom());
		panelView->SetFrame(panelRect);	

		// Restore tree widget binding.
		if (listPanelWidget)
			listPanelWidget->SetFrameBinding(kBindAll);
	}
}

