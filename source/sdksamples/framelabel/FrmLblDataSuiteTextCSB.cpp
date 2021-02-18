//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblDataSuiteTextCSB.cpp $
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

// General includes:
#include "Utils.h"
#include "UIDList.h"

// Project includes:
#include "FrmLblID.h"
#include "IFrmLblDataFacade.h"
#include "IFrmLblDataSuite.h"
#include "FrmLblType.h"


/** FrmLblDataSuiteTextCSB is the text specific implementation of FrmLblDataSuiteCSB.

    
    @ingroup framelabel
*/
class FrmLblDataSuiteTextCSB : public CPMUnknown<IFrmLblDataSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	FrmLblDataSuiteTextCSB(IPMUnknown* boss) : CPMUnknown<IFrmLblDataSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~FrmLblDataSuiteTextCSB() {}

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
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(FrmLblDataSuiteTextCSB, kFrmLblDataSuiteTextCSBImpl)

//
// Add any text specific implementations here
//

ErrorCode FrmLblDataSuiteTextCSB::GetFrameLabelProperties(FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<ITextTarget> iTextTarget(this, UseDefaultIID());
		if (iTextTarget == nil)
		{
			ASSERT_FAIL("ITextTarget invalid");
			break;
		}
		UIDList splineItems(iTextTarget->GetTextModel().GetDataBase());
		
		//Get spline items that the text target was placed in.
		Utils<ITextUtils>()->GetSelectedTextItemsFromTextTarget(iTextTarget, nil, nil, &splineItems);
		error = Utils<IFrmLblDataFacade>()->GetFrameLabelProperties(splineItems, labelInfo);

	} while (false);

	return error;
}

ErrorCode FrmLblDataSuiteTextCSB::UpdateFrameLabelProperties(const FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<ITextTarget> iTextTarget(this, UseDefaultIID());
		if (iTextTarget == nil)
		{
			ASSERT_FAIL("ITextTarget invalid");
			break;
		}
		UIDList splineItems(iTextTarget->GetTextModel().GetDataBase());

		//Get spline items that the text target was placed in.
		Utils<ITextUtils>()->GetSelectedTextItemsFromTextTarget(iTextTarget, nil, nil, &splineItems);
		error = Utils<IFrmLblDataFacade>()->UpdateFrameLabelProperties(splineItems, labelInfo);
	} while (false);

	return error;
}

