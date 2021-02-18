//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/gotolasttextedit/GTTxtEdtControlStripSuite.cpp $
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

// ----- Interfaces -----

#include "IControlStripPrefs.h"
#include "IControlStripWidgetSuite.h"
#include "ILayoutUIUtils.h"
#include "IDocument.h"
#include "IGTTxtEdtSnapshotInterface.h"

// ----- Includes -----

#include "GTTxtEdtResDefs.h"
#include "ControlStripWidgetInfo.h"
#include "K2Vector.tpp"
#include "LocaleSetting.h"

// ----- Utility files -----

// ----- ID.h files -----

#include "GTTxtEdtID.h"

/**
This suite allows us to participate in the control strip. It provides our UI on demand to the application.

@ingroup gotolasttextedit
*/
class GTTxtEdtControlStripSuite: public CPMUnknown<IControlStripWidgetSuite>
{
public:
	/**
	Constructor
	*/
	GTTxtEdtControlStripSuite(IPMUnknown* boss);

	/**
	Provide the widgets to the application.
	*/
	virtual void GetEnabledWidgets(K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID) const;
	/**
	Provide the widgets to the application.
	*/
	virtual void GetEnabledTrackingWidgets(K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID, const ITracker* tracker) const;
};

/*
*/
CREATE_PMINTERFACE(GTTxtEdtControlStripSuite, kGTTxtEdtControlStripSuiteImpl)

/*
*/
GTTxtEdtControlStripSuite::GTTxtEdtControlStripSuite(IPMUnknown* boss):
CPMUnknown<IControlStripWidgetSuite>(boss)
{
}

/*
This suite provides the goto text widget and is used in document default and layout suites
*/
void GTTxtEdtControlStripSuite::GetEnabledWidgets(K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID) const
{
	do {
		IDocument* iDocument = Utils<ILayoutUIUtils>()->GetFrontDocument ();
		if (iDocument == nil){
			ASSERT_FAIL("GTTxtEdtControlStripSuite::GetEnabledWidgets - no document when enabling widgets?");
			break;
		}

		InterfacePtr<IGTTxtEdtSnapshotInterface> iGTTxtEdtSnapshotInterface(iDocument,UseDefaultIID());
		if (iGTTxtEdtSnapshotInterface == nil || !iGTTxtEdtSnapshotInterface->StoryValid()){
			break;
		}

		// if we get here, there is a valid "last edit" story identified.
		infoList.push_back(kGTTxtEditControlStripSet);
	} while (kFalse);
}

/*
*/
void GTTxtEdtControlStripSuite::GetEnabledTrackingWidgets(K2Vector<ControlStripWidgetInfo>& infoList, const PMIID& suiteIID, const ITracker* tracker) const
{
}
