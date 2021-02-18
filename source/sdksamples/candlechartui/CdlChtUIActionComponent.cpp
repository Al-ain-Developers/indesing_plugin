//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechartui/CdlChtUIActionComponent.cpp $
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
#include "IActiveContext.h"
#include "IControlView.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayoutUtils.h"

// General includes:
#include "CActionComponent.h"
#include "CAlert.h"
#include "IActionStateList.h"
#include "LocaleSetting.h"
#include "TransformUtils.h"
#include "ErrorUtils.h"

// Project includes:
#include "CdlChtUIID.h"
#include "ChartUIBrowseCSVFile.H"
#include "ICdlChartFacade.h"

/** Implements IActionComponent; performs the actions that are executed when the plug-in's
	menu items are selected.

	@ingroup candlechartui

*/
class CdlChtUIActionComponent : public CActionComponent
{
public:
/**
 Constructor.
 @param boss interface ptr from boss object on which this interface is aggregated.
 */
		CdlChtUIActionComponent(IPMUnknown* boss);

		/** The action component should perform the requested action.
			This is where the menu item's action is taken.
			When a menu item is selected, the Menu Manager determines
			which plug-in is responsible for it, and calls its DoAction
			with the ID for the menu item chosen.

			@param actionID identifies the menu item that was selected.
			@param ac active context
			@param mousePoint contains the global mouse location at time of event causing action (e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget contains the widget that invoked this action. May be nil. 
			*/
		virtual void DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget);

		/** Called when the action component is asked to update a list of actions to the proper state.
			@param ac IN The current active context.
			@param listToUpdate IN contains the items that client code should update the state for.
			@param mousePoint IN contains the global mouse location at time of event causing action 
	  			(e.g. context menus). kInvalidMousePoint if not relevant.
			@param widget IN contains the widget that invoked this action. May be nil. 
	  		@see CActionComponent::UpdateActionStates
		*/
		virtual void UpdateActionStates(IActiveContext* ac, 
										IActionStateList* listToUpdate, 
										GSysPoint mousePoint, 
										IPMUnknown* widget);

	private:
		/** Encapsulates functionality for the about menu item. */
		void DoAbout();
		
		/** Encapsulates functionality for the "New Candle Chart" menu item. */
		void DoCandleChart(IActiveContext* ac);

		/** Test to see if a candle chart can be created.
		 * 	@param ac IN active context from DoAction
		 * 	@return kTrue if a chart can be created, kFalse otherwise.
		 */
		bool16 CanCreateUICandleChart(IActiveContext* ac);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CdlChtUIActionComponent, kCdlChtUIActionComponentImpl)

/* CdlChtUIActionComponent Constructor
*/
CdlChtUIActionComponent::CdlChtUIActionComponent(IPMUnknown* boss)
: CActionComponent(boss)
{
}

/* DoAction
*/
void CdlChtUIActionComponent::DoAction(IActiveContext* ac, ActionID actionID, GSysPoint mousePoint, IPMUnknown* widget)
{
	switch (actionID.Get())
	{

		case kCdlChtUIPopupAboutThisActionID:
		case kCdlChtUIAboutActionID:
		{
			this->DoAbout();
			break;
		}
					
		case kCdlChtUINewCandleChartActionID:
			{
				this->DoCandleChart(ac);
				break;
			}


		default:
		{
			break;
		}
	}
}


/* UpdateActionStates
*/
void CdlChtUIActionComponent::UpdateActionStates(IActiveContext* ac, 
												 IActionStateList* listToUpdate, 
												 GSysPoint mousePoint, 
												 IPMUnknown* widget)
{
	do
	{
		if (listToUpdate == nil)
		{
			ASSERT(listToUpdate);
			break;
		}
		int32 numActions = listToUpdate->Length();
		for (int32 i = 0 ; i < numActions ; i++)
		{
			ActionID actionID = listToUpdate->GetNthAction(i);
			if (actionID != kCdlChtUINewCandleChartActionID)
			{
				// we don't really need to do anything with ActionIDs
				// other than kCdlChtUINewCandleChartActionID
				continue;
			}
			
			// If we can't create the candle chart, make sure the action is disabled.
			// If we can create the candle chart, make sure the action is enabled.
			int16 newState = (this->CanCreateUICandleChart(ac) == kTrue) ? 
				kEnabledAction : kDisabled_Unselected;
			
			// Update state only if needed
			if (listToUpdate->GetNthActionState(i) != newState)
			{
				listToUpdate->SetNthActionState(i, newState);
			}
		}
	} while (false);
}



/* DoAbout
*/
void CdlChtUIActionComponent::DoAbout()
{
	CAlert::ModalAlert
	(
		kCdlChtUIAboutBoxStringKey,				// Alert string
		kOKString, 						// OK button
		kNullString, 						// No second button
		kNullString, 						// No third button
		1,							// Set OK button to default
		CAlert::eInformationIcon				// Information icon.
	);
}





/* DoCandleChart
*/
void CdlChtUIActionComponent::DoCandleChart(IActiveContext* ac)
{
    do
	{
		// first check if a candle chart can be created on the current context.
		if (this->CanCreateUICandleChart(ac) == kFalse)
		{
			// Alert the user that the proper preconditions are needed.
			PMString alertMsg(kCdlChtUIErrorNoLayoutStringKey, PMString::kTranslateDuringCall);
			CAlert::InformationAlert(alertMsg);
			break;
		}

		IDFile thefile;
		// Let user to choose a CSV file of stock chart data
		if (!ChartUIBrowseCSVFile::BrowseFile(thefile))
		{
			break;
		}
		
		// query the layout control data from the context
        IControlView* view = ac->GetContextView();
		if (!view) 
		{
			// no need to assert here 
			// CanCreateCandleChart() wouldn't have let us come this far
			break;
		}
		InterfacePtr<ILayoutControlData> layout(
			(ILayoutControlData*)view->QueryInterface(ILayoutControlData::kDefaultIID));

		// Obtain active layer for later use
		// NOTE: If you are doing this in a faceless document, layerHier might be nil,
		// so you will need to obtain the layer by descending the hierarchy.
		InterfacePtr<IHierarchy> layerHier(layout->QueryActiveLayer());
		if (layerHier == nil)
		{
			ASSERT_FAIL("IHierarchy pointer nil - could this be a faceless document?");
			break;
		}

		// Get the UIDRef of the layer:
		UIDRef layerRef(::GetUIDRef(layerHier));

		// Get the bounding box for the current page
		IDataBase* db = layerRef.GetDataBase();
		UIDRef pageUIDRef = UIDRef(db,layout->GetPage());

		// Get geometry to calculate where to place the new page item
		InterfacePtr<IGeometry> pageGeometry(pageUIDRef, UseDefaultIID());
		if (pageGeometry == nil)
		{
			ASSERT_FAIL("IGeometry pointer nil");
			break;
		}

		// page item coordinates (hardcoded)
		PMPoint startPoint(0,0);	// Upper Left in Page Coords
		PMPoint endPoint(300,150);	// Size of rectangle
		endPoint += startPoint;		// calculate bottom left corner

		// Convert them to pasteboard coords now
		::TransformInnerPointToPasteboard(pageGeometry,&startPoint);
		::TransformInnerPointToPasteboard(pageGeometry,&endPoint);


		// create the candle chart
		Utils<ICdlChartFacade> facade;
		if(!facade) {
			ErrorUtils::PMSetGlobalErrorCode(kFailure);
			break;
		}
		ErrorCode status = facade->CreateCandleChart(layerRef, thefile, startPoint, endPoint);

	} while (kFalse);
}

/* CanCreateCandleChart
 */
bool16 CdlChtUIActionComponent::CanCreateUICandleChart(IActiveContext* ac)
{
	bool16 canCreate = kFalse;
	do
	{
		if (ac == nil)
		{
			break;
		}
		IControlView* view = ac->GetContextView();
		if (view == nil) 
		{
			break;
		}
		InterfacePtr<ILayoutControlData> layout((ILayoutControlData*)view->QueryInterface(ILayoutControlData::kDefaultIID));
		if (layout == nil)
		{
			break;
		}

		// Check if this is running in InCopy.
		// NOTE: We don't want to be able to add the CandleChart, since 
		// InCopy doesn't have a selection tool to help the user
		// select and move the page item.
		// Without being able to select the page item, you won't see the
		// CdlChartSelection observer in action either.
		// However, this plug-in provides the model support for the 
		// candle chart page item, so it is able to load under InCopy.
		bool16 inInCopy = LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS);
		if (inInCopy)
		{
			break;
		}

		// if we got this far, we can create a candle chart on the layout.
		canCreate = kTrue;

	} while (false);
	return canCreate;
}
