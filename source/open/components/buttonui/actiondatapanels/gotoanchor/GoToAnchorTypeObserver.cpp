//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/GoToAnchorTypeObserver.cpp $
//  
//  Owner: Mark VerMurlen
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

#include "IApplication.h"
#include "IBehaviorSuite.h"
#include "IControlView.h"
#include "IDialogMgr.h"
#include "IDialog.h"
#include "IDocument.h"
#include "IDocumentList.h"
#include "IDropDownListController.h"
#include "IHyperlinkTable.h"
#include "IHyperlinkDestination.h"
#include "IIntData.h"
#include "ISession.h"
#include "IStringListControlData.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "IUIDData.h"
#include "IWidgetUtils.h"
#include "IWindow.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "widgetid.h"
#include "BehaviorUIDefs.h"
#include "CActiveSelectionObserver.h"
#include "RsrcSpec.h"
#include "LocaleSetting.h"
#include "CoreResTypes.h"
#include "ISelectionUtils.h"

#include "IAnchorTypeListData.h"
#include "IGotoAnchorBehaviorData.h"
//========================================================================================
// CLASS GoToAnchorTypeObserver
//========================================================================================

class GoToAnchorTypeObserver : public CActiveSelectionObserver
{
public:
	GoToAnchorTypeObserver(IPMUnknown *boss);
	virtual ~GoToAnchorTypeObserver();
	
	virtual void 	AutoAttach();
	virtual void 	AutoDetach();
	virtual void 	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
	
protected:
	virtual void	SetAnchorType();

};

//========================================================================================
// METHODS GoToAnchorTypeObserver
//========================================================================================

CREATE_PMINTERFACE(GoToAnchorTypeObserver, kAnchorTypeDDLObserverImpl)

//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver constructor 
//----------------------------------------------------------------------------------------

GoToAnchorTypeObserver::GoToAnchorTypeObserver(IPMUnknown *boss) :
	CActiveSelectionObserver(boss)
{
}


//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver::~GoToAnchorTypeObserver
//----------------------------------------------------------------------------------------

GoToAnchorTypeObserver::~GoToAnchorTypeObserver()
{
}

//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver::AutoAttach
//----------------------------------------------------------------------------------------

void GoToAnchorTypeObserver::AutoAttach()
{
	CActiveSelectionObserver::AutoAttach();

        // Make to sure to attach to yourself
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject)
        subject->AttachObserver(this, IID_ISTRINGLISTCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver::AutoDetach
//----------------------------------------------------------------------------------------

void GoToAnchorTypeObserver::AutoDetach()
{
	CActiveSelectionObserver::AutoDetach();

		// Make to sure to detach from yourself
    InterfacePtr<ISubject> subject(this, IID_ISUBJECT);
    if (subject)
        subject->DetachObserver(this, IID_ISTRINGLISTCONTROLDATA);
}

//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver::Update
//----------------------------------------------------------------------------------------

void GoToAnchorTypeObserver::Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy)
{
	if ( theChange == kPopupChangeStateMessage )
	{
		SetAnchorType();
	}
	else
		CActiveSelectionObserver::Update(theChange, theSubject, protocol, changedBy);
}

//----------------------------------------------------------------------------------------
// GoToAnchorTypeObserver::SetAnchorType
//----------------------------------------------------------------------------------------

void GoToAnchorTypeObserver::SetAnchorType()
{
		// Get access to this drop down list
	InterfacePtr<IDropDownListController> anchorChoice((IDropDownListController *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorChoicesWidgetID, IID_IDROPDOWNLISTCONTROLLER));

		// Get the associated data list for the anchor choices drop down list
	InterfacePtr<IAnchorTypeListData> anchorTypeData(anchorChoice, IID_IANCHORTYPEDATA);
	K2Vector<IAnchorTypeListData::AnchorTypeData> theAnchorTypeList = anchorTypeData->GetAnchorTypeData();

	InterfacePtr<ITextControlData> anchorType((ITextControlData *) Utils<IWidgetUtils>()->QueryRelatedWidget(this, kAnchorTypeWidgetID, IID_ITEXTCONTROLDATA));
	
	PMString anchorTypeString("");
	int32 selection = anchorChoice->GetSelected();
	if ( selection >= 0 && selection < theAnchorTypeList.size() )
		anchorTypeString = theAnchorTypeList[selection].GetAnchorType();
	
	anchorType->SetString( anchorTypeString );
}
