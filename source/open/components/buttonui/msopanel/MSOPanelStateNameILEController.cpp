//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelStateNameILEController.cpp $
//  
//  Owner: Michele Stutzman
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
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

// ----- Interfaces -----

#include "IInLineEditWidgetAttributes.h"
#include "IPanelControlData.h"

// ----- Includes -----

#include "AGMGraphicsContext.h"
#include "InLineEditController.h"

// ----- Utility files -----

#include "IWidgetUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"
#include "SysControlIds.h"


class MSOPanelStateNameILEController : public InLineEditController
{
public:
	MSOPanelStateNameILEController(IPMUnknown *boss);
	~MSOPanelStateNameILEController();
	
protected:
	virtual	void CreateEditingWidget();
	virtual	void RemoveEditingWidget();
};


// =============================================================================
// *** MSOPanelStateNameILEEditingAttributes impl ***
// -----------------------------------------------------------------------------

CREATE_PMINTERFACE(MSOPanelStateNameILEController, kMSOPanelStateNameILEControllerImpl)

MSOPanelStateNameILEController::MSOPanelStateNameILEController(IPMUnknown *boss) :
	InLineEditController(boss)
{
} // end constructor

MSOPanelStateNameILEController::~MSOPanelStateNameILEController()
{
} // end destructor

// -----------------------------------------------------------------------------
//	Note: This is basically the same as the TextInLineEditController, except that it 
//	ensure the ile text edit widget is vertically centered.

void MSOPanelStateNameILEController::CreateEditingWidget()
{
	ClassID ewClass = kTextInLineEditChildEditBoxWidgetBoss;
	int32 ewRsrc = kSysEditBoxRsrcId;
	InterfacePtr<IInLineEditWidgetAttributes> ieAttr(this,UseDefaultIID());
	if(ieAttr)
	{
		ewClass = ieAttr->GetEditingWidgetClassID();
		ewRsrc = ieAttr->GetEditingWidgetResourceID();
	}

	InterfacePtr<IPanelControlData>	iPanelData(this, UseDefaultIID());
	IControlView * iStaticView = iPanelData->FindWidget(kInLineEditStaticTextWidgetID);
	NonMarkingAGMGraphicsContext gc(iStaticView);
	InterfaceFontInfo fontInfo = Utils<IWidgetUtils>()->GetAppropriateFontForWidget(iStaticView);
	int16 ascent, descent, leading;
	fontInfo.GetMetrics(&gc, ascent, descent, leading);
	
	// create editing widget
	InterfacePtr<IControlView>	iPanelView(this, UseDefaultIID());
	InterfacePtr<IControlView> iEditView((IControlView*)::CreateObject(ewClass,IID_ICONTROLVIEW));
	PMRect editingWidgetFrame(PMPoint(0.0, 0.0),PMPoint(iPanelView->GetFrame().Width(),ascent+descent+4));

	// vertically center the widget
	// NOTE that this is different from the base class.
	PMReal newTop = editingWidgetFrame.Top() + (iPanelView->GetFrame().Height() - editingWidgetFrame.Height())/2;
	editingWidgetFrame.MoveTo(editingWidgetFrame.Left(), newTop);

	iEditView->Init(kInLineEditEditingWidgetID,editingWidgetFrame,ewRsrc);
	iEditView->SetFrameBinding(kBindLeft|kBindRight);
	iPanelData->AddWidget(iEditView);
} // end CreateEditingWidget()

// -----------------------------------------------------------------------------

void MSOPanelStateNameILEController::RemoveEditingWidget()
{
	InterfacePtr<IPanelControlData>	iPanelData(this, UseDefaultIID());
	IControlView * iEditView = iPanelData->FindWidget(kInLineEditEditingWidgetID);
	iPanelData->RemoveWidget(iEditView);
} // end RemoveEditingWidget()
