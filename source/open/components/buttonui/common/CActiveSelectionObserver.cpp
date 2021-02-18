//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/common/CActiveSelectionObserver.cpp $
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

#include "IDocument.h"
#include "ISubject.h"
#include "ITextControlData.h"
#include "ITriStateControlData.h"
#include "IWidgetUtils.h"

// ----- Implementation Includes -----

#include "CActiveSelectionObserver.h"
#include "ISelectionUtils.h"
#include "Utils.h"

//========================================================================================
// METHODS CActiveSelectionObserver
//========================================================================================

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::CActiveSelectionObserver
//----------------------------------------------------------------------------------------
CActiveSelectionObserver::CActiveSelectionObserver(IPMUnknown *boss, const PMIID& observerIID) :
	ActiveSelectionObserver(boss, observerIID)
{
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::~CActiveSelectionObserver
//----------------------------------------------------------------------------------------
CActiveSelectionObserver::~CActiveSelectionObserver()
{
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::AttachToWidget
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::AttachToWidget(const WidgetID& widgetId,
									 	 const PMIID& interestedIn, const PMIID& asObserver,
										 IPMUnknown* widget)
{
	InterfacePtr<ISubject> subject((ISubject*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : this, widgetId, IID_ISUBJECT)); 
	subject->AttachObserver(this, interestedIn, asObserver);
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::DetachFromWidget
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::DetachFromWidget(const WidgetID& widgetId,
										   const PMIID& interestedIn, const PMIID& asObserver,
										   IPMUnknown* widget)
{
	InterfacePtr<ISubject> subject((ISubject*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : this, widgetId, IID_ISUBJECT)); 
	subject->DetachObserver(this, interestedIn, asObserver);
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::AttachToDocument
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::AttachToDocument(IDocument* document, const PMIID& iid)
{
	if (document != nil)
	{
		InterfacePtr<ISubject> subject(document, UseDefaultIID());
		subject->AttachObserver(this, iid);
	}
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::DetachFromDocument
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::DetachFromDocument(IDocument* document, const PMIID& iid)
{
	if (document != nil)
	{
		InterfacePtr<ISubject> subject(document, UseDefaultIID());
		subject->DetachObserver(this, iid);
	}
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::SetTextControlData
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::SetTextControlData(const WidgetID& widgetId, const PMString& text, IPMUnknown* widget, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<ITextControlData> textData((ITextControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : this, widgetId, IID_ITEXTCONTROLDATA)); 
	ASSERT(textData != nil);	
	textData->SetString(text, invalidate, notifyOfChange);
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::GetTextControlData
//----------------------------------------------------------------------------------------

PMString CActiveSelectionObserver::GetTextControlData(const WidgetID& widgetId, IPMUnknown* widget) const
{
	InterfacePtr<ITextControlData> textData((ITextControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : (CActiveSelectionObserver*) this, widgetId, IID_ITEXTCONTROLDATA)); 
	ASSERT(textData != nil);	
	return textData->GetString();
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::SetTristateControlData
//----------------------------------------------------------------------------------------

void CActiveSelectionObserver::SetTristateControlData(const WidgetID& widgetId, const ITriStateControlData::TriState& state, IPMUnknown* widget, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<ITriStateControlData> tristateData((ITriStateControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : this, widgetId, IID_ITRISTATECONTROLDATA)); 
	ASSERT(tristateData != nil);	
	tristateData->SetState(state, invalidate, notifyOfChange);
}

//----------------------------------------------------------------------------------------
// CActiveSelectionObserver::GetTristateControlData
//----------------------------------------------------------------------------------------

ITriStateControlData::TriState CActiveSelectionObserver::GetTristateControlData(const WidgetID& widgetId, IPMUnknown* widget) const
{
	InterfacePtr<ITriStateControlData> tristateData((ITriStateControlData*) Utils<IWidgetUtils>()->QueryRelatedWidget(widget ? widget : (CActiveSelectionObserver*) this, widgetId, IID_ITRISTATECONTROLDATA)); 
	ASSERT(tristateData != nil);	
	return tristateData->GetState();
}
