//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpHitTestFrame.cpp $
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
#include "IControlView.h"
#include "ILayoutControlViewHelper.h"
#include "IGeometry.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "ILayoutSelectionSuite.h"
#include "ISelectionManager.h"

// General includes:
#include "UIDList.h"
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/** 
	\li How to use ILayoutControlViewHelper and kSolidHitTestHandlerBoss to hit test a point
	given in pasteboard co-ordinates,
	\li how to determine if a graphic frame was hit.

	Note: the coordinate system is pasteboard system, centered on pasteboard
	 center (default size 1224X792 in points). If you want hit (12pica,12pica), 
	 enter x = 12*12 = 144, y = 144-396=-252.

	ILayoutHitTestSuite provides methods that can hit test the selection. But if 
	you want to hit test a point for items that are not already selected this 
	snippet shows an approach you can use.
	
	There are many different kinds of hit tests, hit test to see if the path of 
	a page item was clicked, hit test the handles of a page item etc.
	Consequently the API provides boss classes that apply different hit test
	rules. To find hit test boss classes provided by the API examine the documentation
	for their signature interface IBaseHandler. 

  	@ingroup sdk_snippet
  	@ingroup sdk_layout
	
	@see ILayoutControlViewHelper
	@see kSolidHitTestHandlerBoss
	@see IBaseHandler
	@see ILayoutHitTestSuite
*/
class SnpHitTestFrame 
{
	public:

		/** Constructor.
		 */
		SnpHitTestFrame() {}

		/** Destructor.
		 */
		virtual				~SnpHitTestFrame() {}

		/** Uses kSolidHitTestHandlerBoss to hit test the given point and returns
			the graphic frame associated with the hit. If the point is anywhere within
			the bounding box of a page item a hit will be found. If the point is within the
			bounding box of more than one item the item frontmost in the page item z-order will
			be returned as the hit.
			@param layoutControlViewHelper with which the hit test should be done. 
			@param where the point to be hit tested in pasteboard co-ordinates
			@return IGraphicFraneData of the frame that was hit or nil if no hit detected.
		 */
		IGraphicFrameData*	QueryHitGraphicFrame(ILayoutControlViewHelper* layoutControlViewHelper, const PBPMPoint& where);

		/**	Select the given page items.
			@param selectionManager in which items are to be selected.
			@param itemList UIDs of items to be selected. 
		 */
		void				Select(ISelectionManager* selectionManager, const UIDList& itemList);

		/** Iterates up the hierarchy of the given item till
			a frame is found.
			@param item hitted item
			@return frame that contains the given page item.
		 */
		IGraphicFrameData*	QueryAssociatedGraphicFrame(IGeometry* item);
};

/*
*/
IGraphicFrameData* SnpHitTestFrame::QueryHitGraphicFrame(ILayoutControlViewHelper* layoutControlViewHelper, const PMPoint& where)	
{
	InterfacePtr<IGraphicFrameData> result(nil);
	do {
		ASSERT(layoutControlViewHelper != nil);
		if (layoutControlViewHelper == nil) {
			break;
		}

		// Do the hit test.
		// kSolidHitTestHandlerBoss will return a hit if you click within
		// the bounds of an item. Other hit test boss classes that apply
		// different rules are available (search for boss classes that
		// aggregate interface IBaseHandler). For example if you want 
		// similar hit testing to the pointer tool use kPtrHitTestHandlerBoss.

		/** Note: the coordinate system is pasteboard system, centered on pasteboard
		       center (default size 1224X792 in points). If you want hit (12pica,12pica), 
		       enter x = 12*12 = 144, y = 144-396=-252.
        */
		const ClassID hitTestHandlerClass = kSolidHitTestHandlerBoss;
		InterfacePtr<IGeometry> hitGeometry(static_cast<IGeometry*>(layoutControlViewHelper->QueryHitTestPageItemNew(where, hitTestHandlerClass, IGeometry::kDefaultIID)));
		SNIPLOG("where.x=%f, where.y=%f", ::ToDouble(where.X()), ::ToDouble(where.Y()));
		if (hitGeometry == nil) {
			SNIPLOG("no item hit");
			break;
		}

		ClassID classID = ::GetClass(hitGeometry);
		UID uid = ::GetUID(hitGeometry);
		SNIPLOG("hit item ClassID=0x%x, UID=0x%x", classID.Get(), uid.Get());

		// Determine the frame associated with the hit.
		InterfacePtr<IGraphicFrameData> graphicFrameData(this->QueryAssociatedGraphicFrame(hitGeometry));
		if (graphicFrameData == nil) {
			SNIPLOG("No associated frame");
		}
		result = graphicFrameData;

		classID = ::GetClass(graphicFrameData);
		uid = ::GetUID(graphicFrameData);
		SNIPLOG("hit frame ClassID=0x%x, UID=0x%x", classID.Get(), uid.Get());

	} while (false);

	return result.forget();

} 

/*
*/
void SnpHitTestFrame::Select(ISelectionManager* selectionManager, const UIDList& itemList)
{
	do {
		InterfacePtr<ILayoutSelectionSuite> layoutSelectionSuite(selectionManager, UseDefaultIID());
		if (!layoutSelectionSuite) {
			break;
		}
		selectionManager->DeselectAll(nil); // deselect every active CSB
		 
		layoutSelectionSuite->SelectPageItems(itemList, Selection::kReplace,  Selection::kDontScrollLayoutSelection);
	} while(false);
}

/*
*/
IGraphicFrameData* SnpHitTestFrame::QueryAssociatedGraphicFrame(IGeometry* item)
{
	InterfacePtr<IGraphicFrameData> result(nil);

	do {
		InterfacePtr<IGraphicFrameData> graphicFrameData(item, UseDefaultIID());
		if (graphicFrameData != nil) {
			result = graphicFrameData;
			break;
		}
		// Go up the hierarchy till we find a parent object
		// that aggregates IGraphicFrameData.
		InterfacePtr<IHierarchy> child(item, UseDefaultIID());
		if (child == nil) {
			break;
		}
		do {
			InterfacePtr<IHierarchy> parent(child->QueryParent());
			if (parent == nil) {
				break;
			}
			InterfacePtr<IGraphicFrameData> graphicFrameData(parent, UseDefaultIID());
			if (graphicFrameData != nil) {
				result = graphicFrameData;
				break;
			}
			child = parent;
		} while(child != nil);

	} while(false);

	return result.forget();

}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpHitTestFrame available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerHitTestFrame : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerHitTestFrame();

		/** Destructor.
		 */
		virtual				~_SnpRunnerHitTestFrame();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16				CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode			Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};
/* Constructor
*/
_SnpRunnerHitTestFrame::_SnpRunnerHitTestFrame() : SnpRunnable("HitTestFrame")
{
	this->SetDescription("Hit test for any frame at the given pasteboard point.");
	this->SetPreconditions("document view open");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
_SnpRunnerHitTestFrame::~_SnpRunnerHitTestFrame()
{
}

/*
*/
bool16 _SnpRunnerHitTestFrame::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// Require an open document view.
	InterfacePtr<ILayoutControlViewHelper> layoutControlViewHelper(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
	if (layoutControlViewHelper != nil) {
		result = kTrue;
	}
	return result;
}


/*
*/
ErrorCode _SnpRunnerHitTestFrame::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpHitTestFrame instance;
		// Hit test the point in the frontmost document view.
		InterfacePtr<ILayoutControlViewHelper> layoutControlViewHelper(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlViewHelper == nil) {
			SNIPLOG("Please open a document and try again");
			break;
		}

		// Ask for the pasteboard point.
		Utils<ISnipRunParameterUtils> parameterUtils;
		PMPoint where(0.0, 0.0);
		where.X() = parameterUtils->GetPMReal("Pasteboard x co-ordinate", where.X());
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		where.Y() = parameterUtils->GetPMReal("Pasteboard y co-ordinate", where.Y());
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Do the hit test.
		InterfacePtr<IGraphicFrameData> hitFrame(instance.QueryHitGraphicFrame(layoutControlViewHelper, where));
		if (!hitFrame) {
			break;
		}

		// Select the frame that was hit.
		UIDList itemList(::GetUIDRef(hitFrame));
		instance.Select(runnableContext->GetActiveContext()->GetContextSelection(), itemList);

		status = kSuccess;

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerHitTestFrame instance_SnpRunnerHitTestFrame;
DEFINE_SNIPPET(_SnpRunnerHitTestFrame) 	

//End, SnpHitTestFrame.cpp
