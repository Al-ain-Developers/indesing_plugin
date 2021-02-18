//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartSuiteCSB.cpp $
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
#include "ICommand.h"
#include "IDocumentBroadcastMsg.h"
#include "ISelectionExtension.h"

// General includes
#include "GenericID.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "SelectionExtTemplates.tpp"
#include "UIDList.h"

// Project includes
#include "CdlChartID.h"
#include "CdlChartSuiteCSB.h"
#include "ICdlChartData.h"

/* Constructor
*/
CdlChartSuiteCSB::CdlChartSuiteCSB(IPMUnknown* iBoss)
	: CPMUnknown<ICdlChartSuite>(iBoss)
{
}

/* Destructor
*/
CdlChartSuiteCSB::~CdlChartSuiteCSB(void)	
{
}

/* CanGetChartName
*/
bool16 CdlChartSuiteCSB::CanGetChartName(void)
{
	bool16 result = kFalse;
	do
	{
		UIDList target = this->GetTarget();
		if (target.Length() != 1)
		{
			break;
		}
		InterfacePtr<ICdlChartData> candleChartData(target.GetRef(0), UseDefaultIID());
		if (candleChartData == nil)
		{
			break;
		}
		result = kTrue;
	} while (false);
	return result;
}

/* GetChartName
*/
ErrorCode CdlChartSuiteCSB::GetChartName(WideString& outChartName)
{
	ErrorCode result = kFailure;
	do
	{
		UIDList target = this->GetTarget();
		if (target.Length() != 1)
		{
			break;
		}
		InterfacePtr<ICdlChartData> candleChartData(target.GetRef(0), UseDefaultIID());
		if (candleChartData == nil)
		{
			break;
		}
		candleChartData->GetName(outChartName);

	} while (false);
	return(result);
}


// End, CdlChartSuiteCSB.cpp