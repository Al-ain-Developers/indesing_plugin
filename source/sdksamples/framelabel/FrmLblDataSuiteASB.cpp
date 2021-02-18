//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblDataSuiteASB.cpp $
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
#include "IFrmLblDataSuite.h"

// General includes:
#include "SelectionASBTemplates.tpp"
#include "K2Vector.tpp"

// Project includes:
#include "FrmLblID.h"


/** Provides the ASB implementation for the plug-ins selection suite.

    
    @ingroup framelabel
*/
class FrmLblDataSuiteASB : public CPMUnknown<IFrmLblDataSuite>
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	FrmLblDataSuiteASB(IPMUnknown* boss) : CPMUnknown<IFrmLblDataSuite>(boss) {};

	/** Destructor. Does nothing.
	*/
	~FrmLblDataSuiteASB() {}

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
CREATE_PMINTERFACE(FrmLblDataSuiteASB, kFrmLblDataSuiteASBImpl)

ErrorCode FrmLblDataSuiteASB::GetFrameLabelProperties(FrmLblInfo& labelInfo)
{
	return Process(make_functor(&IFrmLblDataSuite::GetFrameLabelProperties, labelInfo), this, IID_IFRMLBLDATASUITE);
}

ErrorCode FrmLblDataSuiteASB::UpdateFrameLabelProperties(const FrmLblInfo& labelInfo)
{
	return Process(make_functor(&IFrmLblDataSuite::UpdateFrameLabelProperties, labelInfo), this, IID_IFRMLBLDATASUITE);
}

