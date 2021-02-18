//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpSelectShape.cpp $
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
#include "ILayoutTarget.h"
#include "IPathGeometry.h"
#include "IDocument.h"
#include "ISpread.h"
#include "IPathUtils.h"
#include "IControlView.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionManager.h"

// General includes:
#include "Utils.h"
#include "ILayoutUIUtils.h"
#include "Trace.h"
#include "SplineID.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"


/** 
	\li how to iterate a spread, examining page items
	\li how to identify page item types
	\li how to extend the current selection
	\li how to refresh the current view.

	This snippet identifies the PMPageItemType of the current
	page item selection, then searches the spread containing the
	selection for all other page items of the same type.

	@ingroup sdk_snippet
	@ingroup sdk_layout

 */
class SnpSelectShape 
{
public:
	/** Constructor.
	 */
	SnpSelectShape() {}

	/** Destructor.
	 */
	virtual ~SnpSelectShape() {}

	/** Report selected object shape type to sniplog.
		@param pathType (in) Specifies enum of shape types.
		@return kSuccess on identify, kFailure otherwise.
	 */
	ErrorCode ReportObjectType(PMPageItemType pathType);

	/** Find all page items of the same PMPageItemType.
		@param pathType (in) Specifies enum of shape types.
		@param uids (in/out) Specifies list to hold similar page items.
		@param spread (in) Specifies pointer to spread containing selection.
		@see IPathUtils
	 */
	void FindSimilarObjectTypes(PMPageItemType pathType, 
								UIDList& uids, 
								ISpread* spread);

	/**	Select the given page items.
		@param selectionManager in which items are to be selected.
		@param itemList UIDs of items to be selected. 
	 */
	void Select(ISelectionManager* selectionManager, 
				const UIDList& itemList);


};


/* ReportObjectType
*/
ErrorCode SnpSelectShape::ReportObjectType(PMPageItemType pathType)
{
	ErrorCode result = kSuccess;
	do
	{
		switch (pathType)
		{
		case kIsPoint:
			SNIPLOG("Shape is a point.");
			break;
		case kIsLine:
			SNIPLOG("Shape is line.");
			break;
		case kIsRectangle:
			SNIPLOG("Shape is rectangle.");
			break;
		case kIsSquare:
			SNIPLOG("Shape is square.");
			break;
		case kIsCircle:
			SNIPLOG("Shape is circle.");
			break;
		case kIsOval:
			SNIPLOG("Shape is oval.");
			break;
		case kIsPoly:
			SNIPLOG("Shape is a polygon.");
			break;
		case kIsPath:
			SNIPLOG("Shape is a path.");
			break;
		case kIsCompoundPath:
			SNIPLOG("Shape is a compound path.");
			break;
		default:
			SNIPLOG("Unknown shape.");
			result = kFailure;
			break;
		}
	} while (false);
	return result;
}


/* FindSimilarObjectTypes
*/
void SnpSelectShape::FindSimilarObjectTypes(PMPageItemType pathType, 
											UIDList& uids, 
											ISpread* spread)
{
	for (int32 i = 0; i < spread->GetNumPages(); i++)
	{
		UIDList tempList(uids.GetDataBase());

		spread->GetItemsOnPage(i, &tempList, kFalse, kFalse);

		// Iterate the list of page items we just got...
		for (int32 j = 0; j < tempList.Length(); j++)
		{
			// ...and if you find a spline item...
			if (tempList.GetDataBase()->GetClass(tempList[j]) == kSplineItemBoss)
			{
				InterfacePtr<IPathGeometry> pathGeo(tempList.GetRef(j), UseDefaultIID());
				ASSERT(pathGeo);
				// ...check whether it is of the kind we are looking for...
				if (Utils<IPathUtils>()->WhichKindOfPageItem(pathGeo) == pathType)
				{
					// ...and if so, save it in our passed-in list
					uids.Append(tempList.GetRef(j));
				}
			}
		}
	}
}


/* Select
*/
void SnpSelectShape::Select(ISelectionManager* selectionManager, 
							const UIDList& itemList)
{
	do
	{
		InterfacePtr<ILayoutSelectionSuite> 
			layoutSelectionSuite(selectionManager, UseDefaultIID());
		if (!layoutSelectionSuite)
		{
			break;
		}
		selectionManager->DeselectAll(nil);
		layoutSelectionSuite->SelectPageItems(itemList, Selection::kReplace,  Selection::kDontScrollLayoutSelection);
	} while (false);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerSelectShape : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerSelectShape();

	/** Destructor.
	 */
	virtual ~_SnpRunnerSelectShape();

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}
};

/* Constructor.
*/
_SnpRunnerSelectShape::_SnpRunnerSelectShape() : SnpRunnable("SelectShape")
{
	// Describe what your snippet does.
	this->SetDescription("Identifies type of shape selected and selects all other shapes of the same type.");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Document containing single spline selection");

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor.
*/
_SnpRunnerSelectShape::~_SnpRunnerSelectShape()	
{
}

/* Check whether your preconditions are met.
*/
bool16 _SnpRunnerSelectShape::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ILayoutTarget> 
			layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget != nil)
		{
			result = kTrue;
		}
	} while (false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerSelectShape::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do
	{
		SnpSelectShape instance;
		InterfacePtr<ILayoutTarget> 
			layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget == nil)
		{
			ASSERT(layoutTarget);
			break;
		}
		UIDList uids = layoutTarget->GetUIDList(kStripStandoffs);
		UIDRef primaryObject = uids.GetRef(0);

		InterfacePtr<IPathGeometry> 
			pathGeometry(primaryObject, UseDefaultIID());
		if (pathGeometry == nil)
		{
			ASSERT(pathGeometry);
			break;
		}

		PMPageItemType pathType = 
			Utils<IPathUtils>()->WhichKindOfPageItem(pathGeometry);

		// Report the PMPageItemType in sniplog.
		status = instance.ReportObjectType(pathType);
		if (status == kFailure)
		{
			break;
		}

		InterfacePtr<ILayoutControlData> 
			iLCData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (iLCData == nil)
		{
			ASSERT(iLCData);
			break;
		}

		// Find the spread containing our selected page item.
		InterfacePtr<ISpread> spread(iLCData->GetSpreadRef(), UseDefaultIID());
		if (spread == nil)
		{
			ASSERT(spread);
			break;
		}

		// Find all page items of the same PMPageItemType
		// and put any matches in the passed-in UIDList.
		instance.FindSimilarObjectTypes(pathType, uids, spread);

		// Clear current selection(s).
		layoutTarget->Clear();

		ISelectionManager* selectionManager = 
			runnableContext->GetActiveContext()->GetContextSelection(); 

		// Reselect all similar items.
		instance.Select(selectionManager, uids);

	} while (false);
	return(status);
}

/* Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerSelectShape instance_SnpRunnerSelectShape;
DEFINE_SNIPPET(_SnpRunnerSelectShape) 	

// End, SnpSelectShape.cpp

