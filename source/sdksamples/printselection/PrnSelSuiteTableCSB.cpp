//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteTableCSB.cpp $
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
#include "IHierarchy.h"
#include "ITableSuite.h"
#include "ITableTarget.h"
#include "ITextFrameColumn.h"
#include "ITextUtils.h"

// Implementation includes:
#include "K2Vector.h"
#include "UIDList.h"
#include "Utils.h"

// Project includes:
#include "IPrnSelData.h"
#include "PrnSelID.h"
#include "PrnSelSuiteCSB.h"

/** Implements the code necessary to identify and store page UIDs
	and page item UIDs that have a table cell selection.

	@ingroup printselection
*/
class PrnSelSuiteTableCSB : public PrnSelSuiteCSB
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	PrnSelSuiteTableCSB(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~PrnSelSuiteTableCSB(void);

private:
	/**	Returns the UIDs of text frames touched by the table selection.
		If the table selection spans multiple text frames the UID of each 
		frame(spline) is returned.
	*/
	virtual UIDList GetItemList(void) const;

	/** Find the graphic frame, the spline, that is associated with the given textFrameColumn.
		@param textFrameColumn 
		@return UID of the frame associated with the given textFrameColumn
	*/
	virtual UID FindAssociatedGraphicFrame(ITextFrameColumn* textFrameColumn) const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class to its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PrnSelSuiteTableCSB, kPrnSelSuiteTableCSBImpl)


/* Constructor
*/
PrnSelSuiteTableCSB::PrnSelSuiteTableCSB(IPMUnknown* boss) 
: PrnSelSuiteCSB(boss)
{
}

/* Detructor
*/
PrnSelSuiteTableCSB::~PrnSelSuiteTableCSB(void) 
{
}

/* GetItemList
*/
UIDList PrnSelSuiteTableCSB::GetItemList(void) const
{
	UIDList result;
	do
	{
		InterfacePtr<ITableTarget> tableTarget(this, UseDefaultIID());
		ASSERT(tableTarget);
		if (!tableTarget)
		{
			break;
		}
		InterfacePtr<ITableSuite> tableSuite(this, UseDefaultIID());
		ASSERT(tableSuite);
		if (!tableSuite)
		{
			break;
		}
		// Create a list of UIDs of the frames touched by the table selection.
		result = UIDList(tableTarget->GetModel().GetDataBase());
		K2::scoped_ptr< K2Vector<ITextFrameColumn*> > textFrameColumns(tableSuite->GetTextFramesSpannedBySelection());
		for (K2Vector<ITextFrameColumn*>::const_iterator iter = textFrameColumns->begin(); iter != textFrameColumns->end(); iter++)
		{
			ITextFrameColumn* textFrameColumn = *iter;
			UID graphicFrameUID =this->FindAssociatedGraphicFrame(textFrameColumn);
			if (graphicFrameUID != kInvalidUID)
			{
				result.Append(graphicFrameUID);
			}
			textFrameColumn->Release();
		}

	} while (false);

	return result;
}

/* FindAssociatedGraphicFrame
*/
UID PrnSelSuiteTableCSB::FindAssociatedGraphicFrame(ITextFrameColumn* textFrameColumn) const
{
	UID result = kInvalidUID;
	InterfacePtr<IHierarchy> hierarchy(Utils<ITextUtils>()->QuerySplineFromTextFrame(textFrameColumn));
	if (hierarchy)
	{
		result = ::GetUID(hierarchy);
	}
	return result;
}

// End,	PrnSelSuiteTableCSB.cpp.
