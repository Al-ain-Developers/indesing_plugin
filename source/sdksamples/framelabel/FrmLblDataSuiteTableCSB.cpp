//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblDataSuiteTableCSB.cpp $
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

#include <algorithm>

// Interface includes:
#include "ITableTarget.h"
#include "ITableLayout.h"
#include "ITableFrame.h"
#include "ITextFrameColumn.h"
#include "IHierarchy.h"

// General includes:
#include "UIDList.h"
#include "Utils.h"

// Project includes:
#include "FrmLblID.h"
#include "IFrmLblDataFacade.h"
#include "IFrmLblDataSuite.h"
#include "FrmLblType.h"

/** FrmLblDataSuiteTableCSB is the layout specific implementation of FrmLblDataSuiteCSB.

    
    @ingroup framelabel
*/
class FrmLblDataSuiteTableCSB : public CPMUnknown<IFrmLblDataSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	FrmLblDataSuiteTableCSB(IPMUnknown* boss) : CPMUnknown<IFrmLblDataSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~FrmLblDataSuiteTableCSB() {}

	/**	Get properties of the frame label on the selected item(s).
	 * 	@param frmLblInfo OUT The properties of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelProperties(FrmLblInfo& labelInfo);

	/**	Set the frame label properties on the selected item(s).
	 * 	@param frmLblInfo IN The frame label properties.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode UpdateFrameLabelProperties(const FrmLblInfo& labelInfo);

private:

	/**	Get the spline items that the table target was placed in.
	 * 	@param frmLblInfo OUT The spline items.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	ErrorCode GetTableLayoutSplineItems(UIDList& selectedItems);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(FrmLblDataSuiteTableCSB, kFrmLblDataSuiteTableCSBImpl)

ErrorCode FrmLblDataSuiteTableCSB::GetFrameLabelProperties(FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<ITableTarget> iTableTarget(this, UseDefaultIID());
		if (iTableTarget == nil)
		{
			ASSERT_FAIL("ITableTarget is invalid");
			break;
		}

		UIDList selectedItems(iTableTarget->GetModel().GetDataBase());

		//Get the spline items that the table target was placed in.
		error = this->GetTableLayoutSplineItems(selectedItems);
		if(error != kSuccess)
		{
			break;
		}

		error = Utils<IFrmLblDataFacade>()->GetFrameLabelProperties(selectedItems, labelInfo);

	} while (false);

	return error;
}

ErrorCode FrmLblDataSuiteTableCSB::UpdateFrameLabelProperties(const FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<ITableTarget> iTableTarget(this, UseDefaultIID());
		if (iTableTarget == nil)
		{
			ASSERT_FAIL("ITableTarget is invalid");
			break;
		}

		UIDList selectedItems(iTableTarget->GetModel().GetDataBase());
		//Get the spline items that the table target was placed in.
		error = this->GetTableLayoutSplineItems(selectedItems);
		if(error != kSuccess)
		{
			break;
		}

		error = Utils<IFrmLblDataFacade>()->UpdateFrameLabelProperties(selectedItems, labelInfo);
	} while (false);

	return error;
}

ErrorCode FrmLblDataSuiteTableCSB::GetTableLayoutSplineItems(UIDList& selectedItems)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<ITableTarget> iTableTarget(this, UseDefaultIID());
		if (iTableTarget == nil)
		{
			ASSERT_FAIL("ITableTarget is invalid");
			break;
		}

		InterfacePtr<ITableLayout> iTableLayout(iTableTarget->GetModel(), UseDefaultIID());
		if(iTableLayout == nil)
		{
			ASSERT_FAIL("ITableLayout is invalid");
			break;
		}

		ITableLayout::frame_iterator frameIter = iTableLayout->begin_frame_iterator();
		ITableLayout::frame_iterator endFrameIter = iTableLayout->end_frame_iterator();
		for(; frameIter != endFrameIter; ++frameIter)
		{
			InterfacePtr<ITableFrame> tableFrame(frameIter->QueryFrame());
			if(tableFrame == nil)
			{
				ASSERT_FAIL("ITableFrame is invalid");
				break;
			}

			//tableFrame->IsValid() is kFalse if text overset
			if(tableFrame->IsValid() != kTrue)
			{
				break;
			}

			//Get the text frame that the table frame placed in
			InterfacePtr<ITextFrameColumn> textFrameColumn(tableFrame->QueryFrame());
			if(textFrameColumn == nil)
			{
				ASSERT_FAIL("ITextFrameColumn is invalid");
				break;
			}

			//The frmColHier is column item.
			InterfacePtr<IHierarchy> frmColHier(textFrameColumn, UseDefaultIID());
			ASSERT(frmColHier != nil);

			//The parentHier is interface of spline item.
			InterfacePtr<IHierarchy> parentHier(frmColHier->QueryParent());
			if(parentHier == nil)
			{
				ASSERT_FAIL("Column IHierarchy is invalid");
				break;
			}

			//May push repeated UIDs in selectedItems if this spline item has multiple text frames.
			selectedItems.push_back(parentHier->GetParentUID());
		}

		//Duplicate spline item's UIDs in selectedItems if spline item has multiple text frames in it.
		//So erases the repeated UIDs from selectedItems.
		UIDList::iterator newend = std::unique(selectedItems.begin(), selectedItems.end());
		selectedItems.erase(newend, selectedItems.end());
		error = kSuccess;

	} while (false);

	return error;

}
