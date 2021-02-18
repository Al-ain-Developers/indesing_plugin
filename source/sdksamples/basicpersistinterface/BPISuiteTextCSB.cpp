//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPISuiteTextCSB.cpp $
//  
//  Owner: Adobe Developer Technologies
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

// Interface includes
#include "ITextTarget.h"
#include "ITextModel.h"
#include "ITextFocus.h"
#include "ITextParcelList.h"
#include "IParcelList.h"
#include "ITextFrameColumn.h"
#include "IFrameList.h"	
								
// General includes
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"
#include "GenericID.h"

// Project includes
#include "BPIID.h"
#include "IBPISuite.h"		// Superclass declaration
#include "BPISuiteCSB.h"
#include "BPIHelper.h"

/** IBPISuite implementation for the text CSB that gets used when a text
	selection exists; it examines ITextTarget and determine the text
	frames touched by the range of text that is selected (IBPIData is associated
	with page items rather than a story).

	The rest of the implementation is provided by BPISuiteCSB.
	 
	@ingroup basicpersistinterface
	
	@see Selection fundamentals chapter in Programming Guide
*/
class BPISuiteTextCSB : public BPISuiteCSB
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BPISuiteTextCSB (IPMUnknown* boss);
	
	/** Destructor. 
	 */
	virtual					~BPISuiteTextCSB (void);

protected:
	/**	@return the UIDs of text frames touched by the text selection specified in ITextTarget.
		If the text selection spans multiple text frames the UID of each frame(spline) 
		touched is returned.
	*/
	virtual UIDList GetTarget(void);			
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID making the C++ code callable by the application.
*/
CREATE_PMINTERFACE (BPISuiteTextCSB, kBPISuiteTextCSBImpl)

/*
	Binds the suite onto its selection extension making the 
	selection extension member functions in the suite
	callable by the selection subsystem.
	The parameter to the template is the suite implementation class.
*/
template class SelectionExt<BPISuiteTextCSB>;
CREATE_PMINTERFACE (SelectionExt<BPISuiteTextCSB>, kBPISuiteTextSelectionExtImpl)

/* Constructor
*/
BPISuiteTextCSB::BPISuiteTextCSB(IPMUnknown* iBoss) :
	BPISuiteCSB(iBoss)
{
}

/* Destructor
*/
BPISuiteTextCSB::~BPISuiteTextCSB(void)
{
}

/*
*/
UIDList BPISuiteTextCSB::GetTarget(void)
{
	UIDList result;
	do {
#if 0
		// Gather the list of pageItems (splines) in the selection.
		InterfacePtr<ITextTarget> theTarget(this, UseDefaultIID());
		InterfacePtr<ITextModel> textModel(theTarget->QueryTextModel());
		UIDList splineList(::GetDataBase(textModel));
		Utils<ITextUtils>()->GetSelectedTextItemsFromTextTarget(theTarget, nil, nil, &splineList);
		result = splineList;
		// If a text selection lies in a table cell the above code
		// does not detect the text frames. So we roll our own solution
		// below so that our CSB suite works for text selections in
		// table cells.
#endif

		// Find the text model and range of text selected from
		// the text target.
		InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		result = UIDList(textTarget->GetTextModel().GetDataBase());
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel ());
		if (textModel == nil) {
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) {
			break;
		}

		// Find the index of the parcel that contains the first character
		// in the range of text selected.
		TextIndex startTextIndex = textFocus->GetStart(nil);
		if (startTextIndex == kInvalidTextIndex) {
			break;
		}
		InterfacePtr<ITextParcelList> textParcelList(textModel->QueryTextParcelList(startTextIndex));
		if (textParcelList == nil) {
			break;
		}
		InterfacePtr<IParcelList> parcelList(textParcelList, UseDefaultIID());
		if (parcelList == nil) {
			break;
		}
		ParcelKey startParcel = textParcelList->GetParcelContaining(startTextIndex);
		if (!startParcel.IsValid()) {
			break;
		}

		// Find the index of the parcel that contains the last character
		// in the range of text selected.
		TextIndex endTextIndex = textFocus->GetEnd();
		ParcelKey endParcel;
		if (endTextIndex != kInvalidTextIndex) {
			endParcel = textParcelList->GetParcelContaining(endTextIndex);
		}
		else {
			endParcel = parcelList->GetLastParcelKey();
		}
		if (!endParcel.IsValid()) {
			break;
		}
		
		// Find each frame(spline) touched by the text selection.
		BPIHelper bpiHelper;
		IParcelList::const_iterator iter = parcelList->begin(startParcel);
		IParcelList::const_iterator end = parcelList->end(endParcel);
		for (; iter != end; ++iter) {
			InterfacePtr<ITextFrameColumn> textFrameColumn(parcelList->QueryParcelFrame(*iter));
			UID graphicFrameUID = bpiHelper.FindAssociatedGraphicFrame(textFrameColumn);
			if (graphicFrameUID != kInvalidUID) {
				result.Append(graphicFrameUID);
			}
		}
	
	} while(false);
	return result;
}


