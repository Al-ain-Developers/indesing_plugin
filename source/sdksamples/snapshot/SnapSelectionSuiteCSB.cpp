//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapSelectionSuiteCSB.cpp $
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

// ----- Interfaces files
#include "ILayoutTarget.h"
#include "IWorkspace.h"
#include "IPageItemUtils.h"
#include "CAlert.h"
#include "GIFFilterID.h"
#include "TIFFFilterID.h"
#include "IGeometryFacade.h"

//#include "ILayoutUIUtils.h"
#include "SnapID.h"
#include "ISnapSelectionSuite.h"
#include "ISnapPrefsData.h"


/**
	Concrete selection class implementation  of ISnapSelectionSuite for layout selection.

	@ingroup snapshot
	
*/
class SnapSelectionSuiteCSB : public CPMUnknown<ISnapSelectionSuite>
{
	public:
		/** Constructor
		*/
		SnapSelectionSuiteCSB (IPMUnknown* boss);

		 /** Destructor */
		virtual ~SnapSelectionSuiteCSB (void);

		/**	See ISnapSelectionSuite::CreateSnapshot
		 */
		virtual SnapshotUtilsEx* CreateSnapshot(ISpread* spread);

		/**	See ISnapSelectionSuite::SelectionIsEmpty
		 */
		virtual bool16 SelectionIsEmpty();
		
	private:
	
		SnapshotUtilsEx* CreateSnapshotObject(
										ISpread* spread,
										const UIDList& itemList, 
										const PMRect& clippingBounds, 
										ISnapPrefsData* snapPrefsData, 
										bool16 addAlpha
										);

};

CREATE_PMINTERFACE (SnapSelectionSuiteCSB, kSnapSelectionSuiteCSBImpl)

SnapSelectionSuiteCSB::SnapSelectionSuiteCSB(IPMUnknown* boss) :
		CPMUnknown<ISnapSelectionSuite>(boss)
{
}

SnapSelectionSuiteCSB::~SnapSelectionSuiteCSB(void)
{
}

#pragma mark-

SnapshotUtilsEx* SnapSelectionSuiteCSB::CreateSnapshot(ISpread* spread)
{
	ASSERT(spread);
	SnapshotUtilsEx* snapshot = nil;

	do
	{
		// get selected items
		InterfacePtr<ILayoutTarget> iLayoutTarget (this, UseDefaultIID ());
		UIDList itemList(iLayoutTarget->GetUIDList (kStripStandoffs));

		// Bail if there are no items
		if (itemList.Length() <= 0)
			break;
		
		// Calculate the bounds surrounding the items to be drawn.	
		PMRect clippingBounds = Utils<Facade::IGeometryFacade>()->GetItemsBounds(itemList, Transform::SpreadCoordinates(), Geometry::OuterStrokeBounds());

		// Acquire Snapshot preferences
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}
		ISnapPrefsData*  snapPrefsData = (ISnapPrefsData*)workspace->QueryInterface(IID_ISNAPPREFSDATA);
		if (snapPrefsData == nil)
		{
			ASSERT_FAIL("snapPrefsData invalid");
			CAlert::ErrorAlert(kAlertSnapshotFailedKey);
			break;
		}		

		bool16 addAlpha = kFalse;

		if (snapPrefsData->GetFormatClassID() == kGIFImageWriteFormatBoss)
		{
			addAlpha = snapPrefsData->GetGIFTransparent();
		} 
		else if (snapPrefsData->GetFormatClassID() == kTIFFImageWriteFormatBoss)
		{
			addAlpha = snapPrefsData->GetTIFFTransparent();
		}
		
		snapshot = CreateSnapshotObject(spread, itemList, clippingBounds, snapPrefsData, addAlpha);
				
		// Release our preferences
		if (snapPrefsData != nil)
			snapPrefsData->Release();

	} while (false);	
	
	return snapshot;
}

SnapshotUtilsEx* SnapSelectionSuiteCSB::CreateSnapshotObject(
													ISpread* spread,
													const UIDList& itemList, 
													const PMRect& clippingBounds, 
													ISnapPrefsData* snapPrefsData, 
													bool16 addAlpha 
													)
{
	SnapshotUtilsEx::SSColorSpaceFamily colorSpace = snapPrefsData->GetDrawGray() ? 
													SnapshotUtilsEx::kCsGray :
													SnapshotUtilsEx::kCsRGB;

	SnapshotUtilsEx* snapshot = nil;
	if (snapPrefsData->GetDrawArea() == kTrue)
	{
		// Image everything withing the bounds of the selection.
		snapshot = new SnapshotUtilsEx
		(
			clippingBounds, PMMatrix(),
			::GetUIDRef(spread), 
			snapPrefsData->GetScale(),
			snapPrefsData->GetScale(),
			snapPrefsData->GetResolution(), 
			snapPrefsData->GetMinimumResolution(),
			snapPrefsData->GetBleed(),
			colorSpace,
			addAlpha
		);
	}
	else
	{
		// Image the selected items only.
		snapshot = new SnapshotUtilsEx
		(
			clippingBounds, PMMatrix(),
			itemList.GetDataBase(),
			snapPrefsData->GetScale(),
			snapPrefsData->GetScale(),
			snapPrefsData->GetResolution(),
			snapPrefsData->GetMinimumResolution(),	
			snapPrefsData->GetBleed(),
			colorSpace,
			addAlpha
		);
		
		for (int32 i = 0; i < itemList.Length(); i++)
			snapshot->Draw(
						itemList [i], 
						snapPrefsData->GetDrawingFlags(), 
						snapPrefsData->GetFullResolutionGraphics(),
						7.0,
						kTrue,
						SnapshotUtils::kXPHigh
						);
	}	
	
	return snapshot;
}

bool16 SnapSelectionSuiteCSB::SelectionIsEmpty()
{
	bool16	retVal = kFalse;
	InterfacePtr<ILayoutTarget> iLayoutTarget (this, UseDefaultIID ());
	UIDList itemList(iLayoutTarget->GetUIDList (kDontStripStandoffs));
	if (itemList.Length() == 0)
		retVal = kTrue;

	return retVal;
}

