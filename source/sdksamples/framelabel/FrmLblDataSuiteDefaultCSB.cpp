//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblDataSuiteDefaultCSB.cpp $
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

// General includes:
#include "Utils.h"

// Project includes:
#include "FrmLblID.h"
#include "IFrmLblDataSuite.h"
#include "IFrmLblData.h"
#include "IFrmLblDataFacade.h"


/** FrmLblDataSuiteDefaultsCSB is the defaults specific implementation of FrmLblDataSuiteCSB.

    
    @ingroup framelabel
*/
class FrmLblDataSuiteDefaultsCSB : public CPMUnknown<IFrmLblDataSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	FrmLblDataSuiteDefaultsCSB(IPMUnknown* boss) : CPMUnknown<IFrmLblDataSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~FrmLblDataSuiteDefaultsCSB() {}

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
CREATE_PMINTERFACE(FrmLblDataSuiteDefaultsCSB, kFrmLblDataSuiteDefaultsCSBImpl)

ErrorCode FrmLblDataSuiteDefaultsCSB::GetFrameLabelProperties(FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<IFrmLblData> frmLblData(this, UseDefaultIID());
		if(frmLblData == nil)
		{
			ASSERT_FAIL("Invalid IFrmLblData in document preference");
			break;
		}

		//Get default setting  of frame label from doc-workspace
		error = Utils<IFrmLblDataFacade>()->GetFrameLabelPreference(::GetUIDRef(this), labelInfo);
	} while (kFalse);

	return error;
}

ErrorCode FrmLblDataSuiteDefaultsCSB::UpdateFrameLabelProperties(const FrmLblInfo& labelInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<IFrmLblData> frmLblData(this, UseDefaultIID());
		if(frmLblData == nil)
		{
			ASSERT_FAIL("Invalid IFrmLblData in document preference");
			break;
		}

		//Update default setting  of frame label in doc-workspace
		error = Utils<IFrmLblDataFacade>()->SetFrameLabelPreference(::GetUIDRef(this), labelInfo);
	} while (kFalse);

	return error;
}
