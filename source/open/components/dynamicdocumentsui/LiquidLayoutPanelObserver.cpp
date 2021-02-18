//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/LiquidLayoutPanelObserver.cpp $
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

#include "IActiveContext.h"
#include "IAutoLayoutPrefs.h"
#include "IAutoLayoutPrefsCmdData.h"
#include "IControlView.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IFrameContentSuite.h"
#include "ILayoutControlData.h"
#include "ILayoutObject.h"
#include "ILayoutPolicySuite.h"
#include "ILayoutUIUtils.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IReferencePointData.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "ISpreadFacade.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IWorkspace.h"

// ----- Includes -----

#include "IconRsrcDefs.h"
#include "SelectionObserver.h"
#include "UIDList.h"

// ----- Utility files -----

#include "DynamicDocumentsUIUtils.h"
#include "ErrorUtils.h"
#include "PreferenceUtils.h"
#include "SelectionUtils.h"
#include "StringUtils.h"

// ----- ID.h files -----

#include "DynamicDocumentsUIID.h"
#include "FormFieldID.h"
#include "GenericID.h"

//========================================================================================
// class LiquidLayoutPanelObserver
//========================================================================================
class LiquidLayoutPanelObserver : public ActiveSelectionObserver 
{
	typedef ActiveSelectionObserver inherited;


public:
	LiquidLayoutPanelObserver(IPMUnknown *boss);
	virtual ~LiquidLayoutPanelObserver();

	virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* );

	virtual void	AutoAttach();
	virtual void	AutoDetach();

	virtual void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);	
	virtual void    HandleSelectionChanged(const ISelectionMessage*); 
	virtual void	HandleSelectionAttributeChanged(const ISelectionMessage* m);
	
protected:
	
	void UpdateWidgets() const;
	
	ErrorCode SetLayoutPolicy( ILayoutObject::LayoutPolicy);
	
private:
	void		UpdateLayoutPolicyWidget() const;
	void		UpdateAutoFitWidget() const;
	void		UpdateConstraintWidgets() const;
	
	void		_AttachDetachWidget (WidgetID const &widgetID, PMIID const &protocol, bool const bAttach);
	bool16      ActiveDocChange(IActiveContext *context);
	void        AttachTo(IDocument* theDocument);
	void        DetachFrom(IDocument* theDocument);
	
	IDocument*		fCurrentDocument;
};

CREATE_PMINTERFACE(LiquidLayoutPanelObserver, kLiquidLayoutPanelObserverImpl)


//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::LiquidLayoutPanelObserver
//----------------------------------------------------------------------------------------

LiquidLayoutPanelObserver::LiquidLayoutPanelObserver(IPMUnknown *boss) :
	inherited (boss), 
	fCurrentDocument(nil)
{
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::~LiquidLayoutPanelObserver
//----------------------------------------------------------------------------------------

LiquidLayoutPanelObserver::~LiquidLayoutPanelObserver()
{
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::AutoAttach()
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::AutoAttach()
{
	inherited::AutoAttach();
	
	//
	// Attach to all the widgets on this panel
	//
	_AttachDetachWidget (kLiquidLayoutPanelPolicyDropdownListWidgetID, IID_ISTRINGLISTCONTROLDATA, true);
	_AttachDetachWidget (kFixedHeightConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kFixedWidthConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kPinTopConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kPinBottomConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kPinLeftConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kPinRightConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, true);
	_AttachDetachWidget (kLiquidLayoutAutoFitObserverWidgetId, IID_ITRISTATECONTROLDATA, true);

	InterfacePtr<IActiveContext> context(GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
	if (context)
	{
		// Attach to Active context so I know when documents are closed or opened		
		InterfacePtr<ISubject> contextSubject( context, UseDefaultIID());
		if(contextSubject && !contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT,fObserverIID)  )
			contextSubject->AttachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT,fObserverIID  );
		
		ActiveDocChange(context);
	}
}


//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::AutoDetach()
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::AutoDetach()
{	
	//
	// Detach all the widgets on this panel
	//
	_AttachDetachWidget (kLiquidLayoutPanelPolicyDropdownListWidgetID, IID_ISTRINGLISTCONTROLDATA, false);
	_AttachDetachWidget (kFixedHeightConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kFixedWidthConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kPinTopConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kPinBottomConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kPinLeftConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kPinRightConstraintCheckboxWidgetID, IID_ITRISTATECONTROLDATA, false);
	_AttachDetachWidget (kLiquidLayoutAutoFitObserverWidgetId, IID_ITRISTATECONTROLDATA, false);
	
	InterfacePtr<ISubject> contextSubject( GetExecutionContextSession()->GetActiveContext(), UseDefaultIID());
	if(contextSubject && contextSubject->IsAttached(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT,fObserverIID)  )
		contextSubject->DetachObserver(ISubject::kRegularAttachment, this, IID_IACTIVECONTEXT,fObserverIID  );

	if (fCurrentDocument)
	{
		DetachFrom(fCurrentDocument);

		fCurrentDocument = nil;
	}
	
	inherited::AutoDetach();
}

//___________________________________________________________________________________
//  DESCR:      Attatch this observer to the document associated with the Spread CSB.
//___________________________________________________________________________________
void LiquidLayoutPanelObserver::AttachTo(IDocument* theDocument)
{
	InterfacePtr<ISubject>      iDocSubject (theDocument, IID_ISUBJECT);
	
	//  Protocols used for page item model changes
	if ( !iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILAYOUTOBJECT, fObserverIID))
		iDocSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILAYOUTOBJECT, fObserverIID);

	if ( !iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ILAYOUTCONSTRAINTS_DOCUMENT, fObserverIID))
		iDocSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ILAYOUTCONSTRAINTS_DOCUMENT, fObserverIID);		

	if ( !iDocSubject->IsAttached(ISubject::kLazyAttachment,this, IID_ITRANSFORM_DOCUMENT, fObserverIID))
		iDocSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_ITRANSFORM_DOCUMENT, fObserverIID);

	InterfacePtr<IWorkspace> docWorkspace(theDocument->GetDocWorkSpace(), UseDefaultIID());
	InterfacePtr<ISubject> workspaceSubject(docWorkspace, UseDefaultIID());
	if ( workspaceSubject && !workspaceSubject->IsAttached(ISubject::kLazyAttachment,this, IID_IAUTOLAYOUTPREFERENCES, fObserverIID) )
		workspaceSubject->AttachObserver(ISubject::kLazyAttachment,this, IID_IAUTOLAYOUTPREFERENCES, fObserverIID);
}

//___________________________________________________________________________________
//  DESCR:      Detatch this observer from the document associated with the Layout
//              CSB.
//___________________________________________________________________________________
void LiquidLayoutPanelObserver::DetachFrom(IDocument* theDocument)
{
	if (theDocument)
	{
		InterfacePtr<ISubject> oldSubject(theDocument, UseDefaultIID());
		if (oldSubject)
		{
			oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILAYOUTOBJECT, fObserverIID);
			oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ILAYOUTCONSTRAINTS_DOCUMENT, fObserverIID);
			oldSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_ITRANSFORM_DOCUMENT, fObserverIID);
		}

		InterfacePtr<IWorkspace> docWorkspace(theDocument->GetDocWorkSpace(), UseDefaultIID());
		InterfacePtr<ISubject> workspaceSubject(docWorkspace, UseDefaultIID());
		if ( workspaceSubject )
			workspaceSubject->DetachObserver(ISubject::kLazyAttachment,this, IID_IAUTOLAYOUTPREFERENCES, fObserverIID);
	}
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::ActiveDocChange:
//----------------------------------------------------------------------------------------
bool16 LiquidLayoutPanelObserver::ActiveDocChange(IActiveContext* context)
{
    IDocument* theDocument = context->GetContextDocument();
    bool16 bReallyChanged = kFalse;
	
    if (theDocument != fCurrentDocument)
	{
        if (fCurrentDocument)
            this->DetachFrom(fCurrentDocument);
		
        if (theDocument)
            this->AttachTo(theDocument);
		
        fCurrentDocument = theDocument;
        bReallyChanged = kTrue;
	}
	
    return(bReallyChanged);
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::_AttachDetachWidget()
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::_AttachDetachWidget (WidgetID const &widgetID, PMIID const &protocol, bool const bAttach) 
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());	
	IControlView* iWidgetView = iPanelControlData->FindWidget(widgetID);
	
	InterfacePtr<ISubject> iWidgetSubject(iWidgetView, UseDefaultIID());
	if (iWidgetSubject)
	{	
		if (bAttach && !iWidgetSubject->IsAttached( this, protocol, IID_IOBSERVER))
			iWidgetSubject->AttachObserver(this, protocol, IID_IOBSERVER);
		else if (!bAttach && iWidgetSubject->IsAttached( this, protocol, IID_IOBSERVER))
			iWidgetSubject->DetachObserver(this, protocol, IID_IOBSERVER);
	}
}


//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::HandleSelectionChanged
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::HandleSelectionChanged(const ISelectionMessage* inSelMsg)
{	
	UpdateWidgets();
}

void LiquidLayoutPanelObserver::HandleSelectionAttributeChanged(const ISelectionMessage* msg)
{
	if ( msg && msg->WasSuiteAffected(IID_IKEYOBJECTCHANGED) )
	{
		HandleSelectionChanged(msg);
	}
	else 
	{
		bool wasGfxAttrChanged = msg && (msg->WasSuiteAffected (IID_IFRAMECONTENTSUITE) || msg->WasSuiteAffected (IID_IAPPEARANCESUITE));
		
		if (wasGfxAttrChanged)
			this->UpdateAutoFitWidget();		
	}
}



//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::Update
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	switch (protocol.Get())
	{	
		case IID_IACTIVECONTEXT:  //this protocol sends IID instead of cmdID
		{
			InterfacePtr<IActiveContext> context(theSubject, UseDefaultIID());
			const PMIID& id = *((const PMIID*)changedBy);
			if (id == IID_ICONTROLVIEW)	
			{
			}
			else if (id == IID_IDOCUMENT)
			{
				if (ActiveDocChange(context))
				{
					//UpdateWidgets();	// Handled via selection changes for this observer
				}
			}
			
			break;
		}

		case IID_ITRISTATECONTROLDATA:	// click the navigation buttons
		{
			{	
				InterfacePtr<IControlView> iButtonView(theSubject, UseDefaultIID());
				WidgetID widgetID = iButtonView->GetWidgetID();

				if ( widgetID == kLiquidLayoutAutoFitObserverWidgetId )
				{
					InterfacePtr<IFrameContentSuite>    iFrameContentSuite (SelectionUtils::QuerySuite<IFrameContentSuite>());
					InterfacePtr<ITriStateControlData> autoFitData(iButtonView, UseDefaultIID());
					if (autoFitData && iFrameContentSuite)
					{
						if (iFrameContentSuite->CanSetFittingOptions())
						{
							PMRect cropAmounts(kZeroRect); 
							IFrameContentSuite::PersistentFitOptions fitting(IFrameContentSuite::kNoFitting); 
							IReferencePointData::ReferencePointPosition refPoint(IReferencePointData::kCenterReferencePoint); 
							bool16 autoFit = kFalse; 
							
							iFrameContentSuite->GetFittingOptions( &refPoint, &cropAmounts, &fitting, &autoFit); 
							
							if ( refPoint == IReferencePointData::kUninitializedReferencePointPosition )
								refPoint = IReferencePointData::kCenterReferencePoint;
							
							if (autoFitData->IsUnknown())
							{
								//TODO: do we do something here?
							}
							else if (autoFitData->IsSelected())
							{
								autoFit = kTrue;
								iFrameContentSuite->SetFittingOptions( refPoint , cropAmounts, fitting, autoFit); 
							}
							else
							{
								autoFit = kFalse;
								iFrameContentSuite->SetFittingOptions( refPoint, cropAmounts, fitting, autoFit); 
							}
						}
					}
					
					break;
				}
				
				InterfacePtr<ILayoutPolicySuite> iLayoutPolicySuite(fCurrentSelection, UseDefaultIID());
				if ( !iLayoutPolicySuite )
					break;

				Flow::ConstraintIndex index = Flow::kLeftConstraint;
				Flow::Constraint onValue = Flow::kFixedDimension;
				Flow::Constraint offValue = Flow::kFlexibleDimension;
				switch (widgetID.Get())
				{
					case kFixedHeightConstraintCheckboxWidgetID:
						index  = Flow::kHeightConstraint;
						std::swap( onValue, offValue);
						break;
					case kFixedWidthConstraintCheckboxWidgetID:
						index  = Flow::kWidthConstraint;
						std::swap( onValue, offValue);
						break;
					case kPinTopConstraintCheckboxWidgetID:
						index  = Flow::kTopConstraint;
						break;
					case kPinBottomConstraintCheckboxWidgetID:
						index  = Flow::kBottomConstraint;
						break;
					case kPinLeftConstraintCheckboxWidgetID:
						index  = Flow::kLeftConstraint;
						break;
					case kPinRightConstraintCheckboxWidgetID:
						index  = Flow::kRightConstraint;
						break;
					default:
						break;
				}


				Flow::ConstraintList constraintList(Flow::kNumConstraints, Flow::kSkipDimension);
				InterfacePtr<ITriStateControlData> constraintSetting(iButtonView, UseDefaultIID());
				if( constraintSetting->IsSelected()){
					constraintList[index] = onValue;
				}else if(constraintSetting->IsDeselected()){
					constraintList[index] = offValue;
				}else{
					constraintList[index] = Flow::kSkipDimension;
				}

				iLayoutPolicySuite->SetConstraints(constraintList);

				UpdateWidgets();
			}

			break;
		}
		case IID_ISTRINGLISTCONTROLDATA:
		{
			InterfacePtr<IControlView> iView(theSubject, UseDefaultIID());
			if ( iView->GetWidgetID() == kLiquidLayoutPanelPolicyDropdownListWidgetID )
			{
				InterfacePtr<IDropDownListController> listController( theSubject, UseDefaultIID());
				InterfacePtr<IStringListControlData> controlData( theSubject, UseDefaultIID());
				
				int32 selectedIndex = listController->GetSelected();
				if( selectedIndex >= 0 && selectedIndex < controlData->Length())
				{
					PMString selectedString = controlData->GetString(selectedIndex);
					if( selectedString == "kLayoutPolicyMenuString_UseMaster"){
						SetLayoutPolicy( ILayoutObject::kUseMasterLayoutPolicy);
					}
					else if( selectedString == "kLayoutPolicyMenuString_Recenter"){
						SetLayoutPolicy( ILayoutObject::kRecenterLayoutPolicy);
					}
					else if( selectedString == "kLayoutPolicyMenuString_Reposition"){
						SetLayoutPolicy( ILayoutObject::kRepositionLayoutPolicy);
					}
					else if( selectedString == "kLayoutPolicyMenuString_Scale"){
						SetLayoutPolicy( ILayoutObject::kScaleLayoutPolicy);
					}
					else if( selectedString == "kLayoutPolicyMenuString_GuideSlice"){
						SetLayoutPolicy( ILayoutObject::kGuideSliceLayoutPolicy);
					}
					else if( selectedString == "kLayoutPolicyMenuString_Off"){
						SetLayoutPolicy( ILayoutObject::kNoLayoutPolicy);
					}
					
				}
				UpdateWidgets();
			}
			
		}
		default:
		{
			break;
		}
	}
	inherited::Update(theChange, theSubject, protocol, changedBy);
}

void LiquidLayoutPanelObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* )
{
	switch (protocol.Get())
	{
		case IID_ILAYOUTOBJECT:
		case IID_ILAYOUTCONSTRAINTS_DOCUMENT:
			UpdateWidgets();
			break;
		case IID_ITRANSFORM_DOCUMENT:
			UpdateConstraintWidgets();
			break;
		default:
			break;
	}
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::UpdateAutoFitWidget
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::UpdateAutoFitWidget() const
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* autoFitView = iPanelControlData->FindWidget(kLiquidLayoutAutoFitObserverWidgetId);
	InterfacePtr<ITriStateControlData> iAutoFitTriStateData(autoFitView, UseDefaultIID());

	// AUTO-FIT CHECKBOX
	if ( autoFitView )
	{
		bool16 canSetOptions = kFalse;
		
		InterfacePtr<IFrameContentSuite> iFrameContentSuite(SelectionUtils::QuerySuite<IFrameContentSuite>());
		if ( iFrameContentSuite )
		{
			canSetOptions = iFrameContentSuite->CanSetFittingOptions();
			
			PMRect cropAmounts(kZeroRect); 
			IFrameContentSuite::PersistentFitOptions fitting(IFrameContentSuite::kNoFitting); 
			IReferencePointData::ReferencePointPosition refPoint(IReferencePointData::kTopLeftReferencePoint); 
			bool16 autoFit = kFalse; 
			
			bool16 bCanGetFittingOptions = iFrameContentSuite->GetFittingOptions( &refPoint, &cropAmounts, &fitting, &autoFit); 
			
			if (bCanGetFittingOptions) 
			{ 			
				// Auto-Fit 
				if (autoFit == kMixedAutoFit) 
				{ 
					if (!iAutoFitTriStateData->IsUnknown())
						iAutoFitTriStateData->SetUnknown(kTrue, kFalse);
				} 
				else if (autoFit) 
				{ 
					if (!iAutoFitTriStateData->IsSelected())
						iAutoFitTriStateData->Select(kTrue, kFalse);
				} 
				else 
				{ 
					if (!iAutoFitTriStateData->IsDeselected())
						iAutoFitTriStateData->Deselect(kTrue, kFalse);
				} 
				
				autoFitView->Enable(canSetOptions);
			}
			else
			{
				canSetOptions = kFalse;
			}
		}
		autoFitView->Enable(canSetOptions);
	}
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::UpdateConstraintWidgets
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::UpdateConstraintWidgets() const
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	
	IControlView* constraintsSubPanel = iPanelControlData->FindWidget(kObjectConstraintsSubPanelGroupWID);
	IControlView* iFixedWidthView = iPanelControlData->FindWidget(kFixedWidthConstraintCheckboxWidgetID);
	IControlView* iFixedHeightView = iPanelControlData->FindWidget(kFixedHeightConstraintCheckboxWidgetID);
	IControlView* iPinTopView = iPanelControlData->FindWidget(kPinTopConstraintCheckboxWidgetID);
	IControlView* iPinLeftView = iPanelControlData->FindWidget(kPinLeftConstraintCheckboxWidgetID);
	IControlView* iPinRightView = iPanelControlData->FindWidget(kPinRightConstraintCheckboxWidgetID);
	IControlView* iPinBottomView = iPanelControlData->FindWidget(kPinBottomConstraintCheckboxWidgetID);
	
	InterfacePtr<ITriStateControlData> iFixedWidthData(iFixedWidthView, UseDefaultIID());
	InterfacePtr<ITriStateControlData> iFixedHeightData(iFixedHeightView, UseDefaultIID());
	InterfacePtr<ITriStateControlData> iPinTopData(iPinTopView, UseDefaultIID());
	InterfacePtr<ITriStateControlData> iPinLeftData(iPinLeftView, UseDefaultIID());
	InterfacePtr<ITriStateControlData> iPinRightData(iPinRightView, UseDefaultIID());
	InterfacePtr<ITriStateControlData> iPinBottomData(iPinBottomView, UseDefaultIID());
	
	// OBJECT CONSTRAINTS
	InterfacePtr<ILayoutPolicySuite> iLayoutPolicySuite(fCurrentSelection, UseDefaultIID());
	
	if ( iLayoutPolicySuite && iLayoutPolicySuite->CanApplyObjectConstraints() )
	{		
		Flow::ConstraintList constraints(Flow::kNumConstraints, Flow::kSkipDimension);
		
		bool bDoEnable = iLayoutPolicySuite->GetConstraints(constraints);
		
		if ( constraints[Flow::kLeftConstraint] == Flow::kFixedDimension )
			iPinLeftData->Select(true, false);
		else if ( constraints[Flow::kLeftConstraint] == Flow::kFlexibleDimension )
			iPinLeftData->Deselect(true, false);
		else
			iPinLeftData->SetUnknown(true, false);
		
		if ( constraints[Flow::kRightConstraint] == Flow::kFixedDimension )
			iPinRightData->Select(true, false);
		else if ( constraints[Flow::kRightConstraint] == Flow::kFlexibleDimension )
			iPinRightData->Deselect(true, false);
		else
			iPinRightData->SetUnknown(true, false);
		
		if ( constraints[Flow::kTopConstraint] == Flow::kFixedDimension )
			iPinTopData->Select(true, false);
		else if ( constraints[Flow::kTopConstraint] == Flow::kFlexibleDimension )
			iPinTopData->Deselect(true, false);
		else
			iPinTopData->SetUnknown(true, false);
		
		if ( constraints[Flow::kBottomConstraint] == Flow::kFixedDimension )
			iPinBottomData->Select(true, false);
		else if ( constraints[Flow::kBottomConstraint] == Flow::kFlexibleDimension )
			iPinBottomData->Deselect(true, false);
		else
			iPinBottomData->SetUnknown(true, false);
		
		if ( constraints[Flow::kWidthConstraint] == Flow::kFlexibleDimension )
			iFixedWidthData->Select(true, false);
		else if ( constraints[Flow::kWidthConstraint] == Flow::kFixedDimension )
			iFixedWidthData->Deselect(true, false);
		else
			iFixedWidthData->SetUnknown(true, false);
		
		if ( constraints[Flow::kHeightConstraint] == Flow::kFlexibleDimension )
			iFixedHeightData->Select(true, false);
		else if ( constraints[Flow::kHeightConstraint] == Flow::kFixedDimension )
			iFixedHeightData->Deselect(true, false);
		else
			iFixedHeightData->SetUnknown(true, false);
		
		constraintsSubPanel->Enable(bDoEnable, true);
	}
	else 
	{
		iPinRightData->Deselect(true, false);
		iPinLeftData->Deselect(true, false);
		iPinTopData->Deselect(true, false);
		iPinBottomData->Deselect(true, false);
		iFixedWidthData->Deselect(true, false);
		iFixedHeightData->Deselect(true, false);
		
		constraintsSubPanel->Enable(false, true);
		/*
		 iFixedWidthView->Enable(false, false);
		 iFixedHeightView->Enable(false, false);
		 iPinTopView->Enable(false, false);
		 iPinLeftView->Enable(false, false);
		 iPinRightView->Enable(false, false);
		 iPinBottomView->Enable(false, false);
		 */
	}
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::UpdateLayoutPolicyWidget
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::UpdateLayoutPolicyWidget() const
{
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	IControlView* layoutPolicyDropDownView = iPanelControlData->FindWidget(kLiquidLayoutPanelPolicyDropdownListWidgetID);
	
	// UPDATE LAYOUT POLICY DROPDOWN
	InterfacePtr<IDropDownListController> listController( layoutPolicyDropDownView, UseDefaultIID());
	if ( listController )
	{
		InterfacePtr<IStringListControlData> controlData( listController, UseDefaultIID());
		
		InterfacePtr<ILayoutPolicySuite> iLayoutPolicySuite(fCurrentSelection, UseDefaultIID());
		if ( iLayoutPolicySuite )
		{
			ILayoutObject::LayoutPolicy onePolicy = ILayoutObject::kNoLayoutPolicy;
			bool32 mixed = !iLayoutPolicySuite->GetLayoutPolicy(onePolicy);
			
			int32 index = IDropDownListController::kNoSelection;
			if (	!mixed)
			{
				switch(onePolicy)
				{
					case ILayoutObject::kNoLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_Off");
						break;
					case ILayoutObject::kRecenterLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_Recenter");
						break;
					case ILayoutObject::kRepositionLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_Reposition");
						break;
					case ILayoutObject::kScaleLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_Scale");
						break;
					case ILayoutObject::kGuideSliceLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_GuideSlice");
						break;
					case ILayoutObject::kUseMasterLayoutPolicy:
						index = controlData->GetIndex("kLayoutPolicyMenuString_UseMaster");
						break;
					default:
						ASSERT_FAIL("Bad policy value?");
						index = IDropDownListController::kNoSelection;
						break;
				}		
			}

			layoutPolicyDropDownView->Enable(kTrue, kFalse);
			listController->Select(index, kTrue, kFalse);
			
			// enable/disable the "Based On Master" layout policy as appropriate
			if ( onePolicy != ILayoutObject::kUseMasterLayoutPolicy )
				index = controlData->GetIndex("kLayoutPolicyMenuString_UseMaster");
			bool16 canApplyBasedOnMaster = ( iLayoutPolicySuite && iLayoutPolicySuite->CanApplyBasedOnMasterPolicy() );
			
			listController->Enable(index, canApplyBasedOnMaster, kTrue, kFalse);
		}
		else
		{
			listController->Deselect(kTrue, kFalse);
			layoutPolicyDropDownView->Disable(kFalse);
		}
	}
}
	


//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::UpdateWidgets
//----------------------------------------------------------------------------------------
void LiquidLayoutPanelObserver::UpdateWidgets() const
{	
	UpdateAutoFitWidget();
	UpdateLayoutPolicyWidget();
	UpdateConstraintWidgets();
		
	InterfacePtr<IPanelControlData> iPanelControlData(this, UseDefaultIID());
	if ( iPanelControlData )
	{
		IControlView* pageRangeView = iPanelControlData->FindWidget(kPageRangeWidgetID);
		InterfacePtr<ILayoutPolicySuite> iLayoutPolicySuite(fCurrentSelection, UseDefaultIID());
		
		PMString displayString("kLiquidLayoutPanelPageRange");
		displayString.Translate();
		
		PMString pageRange("");
		if ( iLayoutPolicySuite )
			iLayoutPolicySuite->GetPageRangeString(pageRange);
		
		if ( pageRange.empty() )
		{
			pageRange = PMString(" ");
			pageRange.SetTranslatable(kFalse);
		}
		
		StringUtils::ReplaceStringParameters(&displayString, pageRange);
		InterfacePtr<ITextControlData> data(pageRangeView, UseDefaultIID());
		if ( data )
			data->SetString(displayString);
	}
}

//----------------------------------------------------------------------------------------
// LiquidLayoutPanelObserver::SetLayoutPolicy
//----------------------------------------------------------------------------------------
ErrorCode LiquidLayoutPanelObserver::SetLayoutPolicy( ILayoutObject::LayoutPolicy policy)
{
	InterfacePtr<ILayoutPolicySuite> iLayoutPolicySuite(fCurrentSelection, UseDefaultIID());
	if ( iLayoutPolicySuite )
	{
		return iLayoutPolicySuite->SetLayoutPolicy(policy);
	}

	return kFailure;
}



//---------------------------------------------------------------------------------------- 
// Class LayoutAdjustmentWarningObserver 
//---------------------------------------------------------------------------------------- 

class LayoutAdjustmentWarningObserver : public CObserver 
{ 
    public: 
        LayoutAdjustmentWarningObserver(IPMUnknown *boss); 
        virtual ~LayoutAdjustmentWarningObserver(); 
         
        virtual void AutoAttach(); 
        virtual void AutoDetach(); 
        virtual void Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy); 
		virtual void LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* );
		
		bool16 ActiveDocChange(IActiveContext *context);
		void AttachTo(IDocument* theDocument);
		void DetachFrom(IDocument* theDocument);

	private:
		void UpdateLayoutAdjustmentWarning() const;
		void SetAutoLayoutOff();

		IDocument*		fCurrentDocument;
}; 


//---------------------------------------------------------------------------------------- 
// 
// Class implementation 
// 
//---------------------------------------------------------------------------------------- 


//======================================================================================== 
// CLASS LayoutAdjustmentWarningObserver 
//======================================================================================== 

CREATE_PMINTERFACE(LayoutAdjustmentWarningObserver, kLayoutAdjustmentWarningObserverImpl) 

//---------------------------------------------------------------------------------------- 
// LayoutAdjustmentWarningObserver constructor 
//---------------------------------------------------------------------------------------- 

LayoutAdjustmentWarningObserver::LayoutAdjustmentWarningObserver(IPMUnknown *boss) : 
    CObserver(boss),
	fCurrentDocument(nil)
{ 
} 


//---------------------------------------------------------------------------------------- 
// LayoutAdjustmentWarningObserver::~LayoutAdjustmentWarningObserver: 
//---------------------------------------------------------------------------------------- 

LayoutAdjustmentWarningObserver::~LayoutAdjustmentWarningObserver() 
{ 
} 


//---------------------------------------------------------------------------------------- 
// LayoutAdjustmentWarningObserver::AutoAttach: 
//---------------------------------------------------------------------------------------- 

void LayoutAdjustmentWarningObserver::AutoAttach() 
{ 
} 

//---------------------------------------------------------------------------------------- 
// BrowseButtonObserver::AutoDetach: 
//---------------------------------------------------------------------------------------- 

void LayoutAdjustmentWarningObserver::AutoDetach() 
{ 
} 

//---------------------------------------------------------------------------------------- 
// LayoutAdjustmentWarningObserver::Update: 
//---------------------------------------------------------------------------------------- 

void LayoutAdjustmentWarningObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy) 
{ 
} 

void LayoutAdjustmentWarningObserver::LazyUpdate(ISubject* theSubject, const PMIID &protocol, const LazyNotificationData* )
{
}

bool16 LayoutAdjustmentWarningObserver::ActiveDocChange(IActiveContext* context)
{
    bool16 bReallyChanged = kFalse;
    return(bReallyChanged);
}

void LayoutAdjustmentWarningObserver::AttachTo(IDocument* theDocument)
{
}

void LayoutAdjustmentWarningObserver::DetachFrom(IDocument* theDocument)
{
}

//----------------------------------------------------------------------------------------
// LayoutAdjustmentWarningObserver::UpdateLayoutAdjustmentWarning
//----------------------------------------------------------------------------------------
void LayoutAdjustmentWarningObserver::UpdateLayoutAdjustmentWarning() const
{	
}

//----------------------------------------------------------------------------------------
// SetAutoLayoutOff
//----------------------------------------------------------------------------------------
void LayoutAdjustmentWarningObserver::SetAutoLayoutOff()
{
}
