//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorOnOffButtonView.cpp $
//  
//  Owner: Michael Burbidge
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

// ----- Interface Includes -----

#include "ITriStateControlData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CIDIconSuiteButtonView.h"

#include "Trace.h"

//========================================================================================
// CLASS BehaviorOnOffButtonView
//========================================================================================

class BehaviorOnOffButtonView : public CIDIconSuiteButtonView
{
	typedef CIDIconSuiteButtonView inherited;
public:
	BehaviorOnOffButtonView(IPMUnknown *boss);
	virtual ~BehaviorOnOffButtonView();

protected :
	virtual void CommonInit();

	virtual void DrawUnknown(dvaui::drawbot::Drawbot* drawbotP);
	virtual void DrawHilited(dvaui::drawbot::Drawbot* drawbotP);
	virtual void DrawDisabled(dvaui::drawbot::Drawbot* drawbotP);

	virtual void PreDrawDoIconChange();
	
private :
	RsrcID	 fBaseRsrcID;
};

//========================================================================================
// METHODS BehaviorOnOffButtonView
//========================================================================================

CREATE_PERSIST_PMINTERFACE(BehaviorOnOffButtonView, kBehaviorOnOffButtonViewImpl)

//----------------------------------------------------------------------------------------
// BehaviorOnOffButtonView constructor 
//----------------------------------------------------------------------------------------

BehaviorOnOffButtonView::BehaviorOnOffButtonView(IPMUnknown *boss) :
	inherited(boss)
{
}

//----------------------------------------------------------------------------------------
// BehaviorOnOffButtonView::~BehaviorOnOffButtonView
//----------------------------------------------------------------------------------------

BehaviorOnOffButtonView::~BehaviorOnOffButtonView()
{
}

void BehaviorOnOffButtonView::CommonInit()
{
	inherited::CommonInit();
	fBaseRsrcID = GetRsrcID ();
}

void BehaviorOnOffButtonView::DrawUnknown(dvaui::drawbot::Drawbot* drawbotP)
{
	inherited::DrawUnselected (drawbotP);
}

void BehaviorOnOffButtonView::DrawHilited(dvaui::drawbot::Drawbot* drawbotP)
{
	InterfacePtr<ITriStateControlData> data(this, UseDefaultIID());
	if (data->IsSelected())
		DrawSelected(drawbotP);
	else if (data->IsUnknown())
		DrawUnknown(drawbotP);
	else
		DrawUnselected(drawbotP);
}

void BehaviorOnOffButtonView::DrawDisabled(dvaui::drawbot::Drawbot* drawbotP)
{
	InterfacePtr<ITriStateControlData> data(this, UseDefaultIID());
	if (data->IsSelected())
		DrawSelected(drawbotP);
	else if (data->IsUnknown())
		DrawUnknown(drawbotP);
	else
		DrawUnselected(drawbotP);
}

void BehaviorOnOffButtonView::PreDrawDoIconChange()
{
	// DV_Note: Moved the icon changes to here from DrawXXX methods
	InterfacePtr<ITriStateControlData> data(this, UseDefaultIID());
	if (data->IsSelected())
		SetRsrcID(fBaseRsrcID);
	else if (data->IsUnknown())
		SetRsrcID (fBaseRsrcID + 2);	
	else
		SetRsrcID (fBaseRsrcID + 1);	
}

