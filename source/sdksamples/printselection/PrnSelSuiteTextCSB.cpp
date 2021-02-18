//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteTextCSB.cpp $
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

// Interface includes:
#include "ITextTarget.h"
#include "ITextUtils.h"

// Implementation includes:
#include "UIDList.h"
#include "Utils.h"

// Project includes:
#include "IPrnSelData.h"
#include "PrnSelID.h"
#include "PrnSelSuiteCSB.h"


/** Implements the code necessary to identify and store page UIDs
	and page item UIDs that have a text selection.
	
	@ingroup printselection
*/
class PrnSelSuiteTextCSB : public PrnSelSuiteCSB
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on 
	  	which this interface is aggregated.
	*/
	PrnSelSuiteTextCSB(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~PrnSelSuiteTextCSB(void);

private:
	/**	Return the UIDs of text frames touched by the text selection.
		If the text selection spans multiple text frames the UID of each frame(spline) 
		touched is returned.
	*/
	virtual UIDList GetItemList(void) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelSuiteTextCSB, kPrnSelSuiteTextCSBImpl)


/* Constructor
*/
PrnSelSuiteTextCSB::PrnSelSuiteTextCSB(IPMUnknown* boss) 
: PrnSelSuiteCSB(boss)
{
}

/* Destructor
*/
PrnSelSuiteTextCSB::~PrnSelSuiteTextCSB(void)
{
}


/* GetItemList
*/
UIDList PrnSelSuiteTextCSB::GetItemList(void) const
{
	UIDList result;
	do
	{
		// Gather the list of frames associated with the text selection.
		InterfacePtr<ITextTarget> textTarget(this, UseDefaultIID());
		if (textTarget == nil)
		{
			break;
		}
		result = UIDList(textTarget->GetTextModel().GetDataBase());
		Utils<ITextUtils>()->GetSelectedTextItemsFromTextTarget(textTarget, nil, nil, &result);
	} while (false);
	return result;
}

// End, PrnSelSuiteTextCSB.cpp.
