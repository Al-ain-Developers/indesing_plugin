//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/conditionaltextui/ConditionStaticTextView.cpp $
//  
//  Owner: Kevin Van Wiel
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
#include "IPMStream.h"
#include "IObserver.h"

// ----- Includes -----
#include "CIDStaticTextView.h"

// ----- Utility files -----

// ----- ID.h files -----
#include "ConditionalTextUIID.h"


/******************************************************************************
 * class ConditionStaticTextView
 ******************************************************************************/
class ConditionStaticTextView : public CIDStaticTextView
{
	typedef CIDStaticTextView inherited;
public:
	ConditionStaticTextView(IPMUnknown *boss);
	~ConditionStaticTextView();

	virtual void		DoAutoAttach();
	virtual void		DoAutoDetach();

};

CREATE_PERSIST_PMINTERFACE(ConditionStaticTextView, kConditionStaticTextViewImpl)

/******************************************************************************
 * ConditionStaticTextView ::ConditionStaticTextView
 ******************************************************************************/
ConditionStaticTextView::ConditionStaticTextView(IPMUnknown *boss) :
	inherited(boss)
{
}

/******************************************************************************
 * ConditionStaticTextView ::~ConditionStaticTextView
 ******************************************************************************/
ConditionStaticTextView::~ConditionStaticTextView()
{
}

/******************************************************************************
 * ConditionStaticTextView::DoAutoAttach
 ******************************************************************************/
void ConditionStaticTextView::DoAutoAttach()
{
	inherited::DoAutoAttach();

	InterfacePtr<IObserver> theSelectionObserver(this, IID_ISELECTIONOBSERVER);
	if (theSelectionObserver)
		theSelectionObserver->AutoAttach();

}

/******************************************************************************
 * ConditionStaticTextView ::DoAutoDetach
 ******************************************************************************/
void ConditionStaticTextView::DoAutoDetach()
{	
	InterfacePtr<IObserver> theSelectionObserver(this, IID_ISELECTIONOBSERVER);
	if (theSelectionObserver)
		theSelectionObserver->AutoDetach();
		
	inherited::DoAutoDetach();
}
