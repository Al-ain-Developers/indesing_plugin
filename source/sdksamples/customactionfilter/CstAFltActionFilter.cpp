//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customactionfilter/CstAFltActionFilter.cpp $
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
#include "IActionFilter.h"
#include "IEnvironment.h"

#include "DebugClassUtils.h"
#include "IApplication.h"
#include "IActionManager.h"
#include "IActionIDToUIDData.h"
#include "ActionMapper.h"

// General includes:
#include "ActionDefs.h" // for kCustomEnabling
#include "CPMUnknown.h"
//#include "UpdateManagerID.h" // for actionIDs and bossclasses

// Project includes:
#include "CstAFltID.h"
#include "CstAFltActionFilter.h"

#include "PDFID.h"

#include "Utils.h"
#include "ILayoutUIUtils.h"

#include "PMString.h"

#include "IDocument.h"

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CstAFltActionFilter, kCstAFltActionFilterImpl)


/* Constructor 
*/
CstAFltActionFilter::CstAFltActionFilter(IPMUnknown* boss)
	: CPMUnknown<IActionFilter>(boss) 
{
	// does nothing. 
}


/* FilterAction
*/
void CstAFltActionFilter::FilterAction(ClassID* componentClass, ActionID* actionID, 
									   PMString* actionName, PMString* actionArea, 
									   int16* actionType, uint32* enablingType, 
									   bool16* userEditable)
{

	IDocument* myDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
	// configure only when there is a document open needed...
	if (myDoc)
	{
		PMString test;
		myDoc->GetName(test);
		if (*actionID>=kFirstPDFStyleActionID && *actionID<= kLastPDFStyleActionID)
		{
			// heavyweight logic here, do you want the action filtered at all?
			if (test == "ross.indd") 
			{
				ActionMapper * actionMapperPtr = ActionMapper::ActionMapperFactory();
				// add action will only add the action if it is missing.
				actionMapperPtr->AddAction(*actionID,*componentClass);
				*componentClass = kCstAFltActionComponentBoss;
			}

		}
	}

}

// End, CstAFltActionFilter.cpp.
