//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectPathInfo.cpp $
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
#include "IPathGeometry.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "IImageDataAccess.h"
#include "ITextTarget.h"
#include "ICreateOutlinesUtils.h"
#include "IStandOffData.h"
#include "ISplineUtils.h"
#include "IBoolData.h"
#include "ISelectionUtils.h"
#include "IPageItemTypeUtils.h"

#include "InstStrokeFillID.h"
#include "PageItemScrapID.h"

// General includes:
#include "RangeData.h"
#include "UIDList.h"
#include "Utils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpGraphicHelper.h"

/**	
    This code snippet provide samples for access information of various paths.
	Specifically, the following area are covered:
	\li How to create and get paths from text outline,
	\li How to get clipping path,
	\li How to text wrap path,
	\li How to path of the graphic frame.
	
	Note:
	(1) To get path information of a text outline, a text selection is required, others all require layout selection
	(2) All the methods are hard-coded to only display path information of first item (or first child of group item when text outline is a group)

  	@ingroup sdk_snippet
  	@ingroup sdk_graphic
	

*/
class SnpInspectPathInfo
{

	public:
	
		/** Constructor.
		*/
		SnpInspectPathInfo() {}

		/** Destructor
		*/
		virtual ~SnpInspectPathInfo() {}

	/** Report outline of selected text
			@param iTextTarget text selection target.
			@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectTextOutline(ITextTarget* iTextTarget);

	/** Report clipping path of an graphic item
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectClippingPath(UIDList itemList);

	/** Report textwrap path of an graphic item
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectTextWrapPath(UIDList itemList);

	/** Report path of an graphic frame
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode InspectFramePath(UIDList itemList);

		

private:

	/** Report information about a path
		@param pathName Name of a path type.
		@param pathGeo Path geometry of the path.
		*/
	void ReportPathInfo(const char* pathName, IPathGeometry *pathGeo);


};


/**
Report path information of a specific type
*/
void SnpInspectPathInfo::ReportPathInfo(const char* pathName, IPathGeometry *pathGeo)
{
	SNIPLOG("Begin path info of %s ",pathName);
	if (pathGeo)
	{
		int32 numPaths = pathGeo->GetNumPaths();
		SNIPLOG("   %s has %d paths:",pathName, numPaths);
		int32 index = 0;
		for (index = 0; index < numPaths; index++)
		{	// only display number of segment and points here, you may add additonal information such as each points.
			SNIPLOG(      "Path %d has %d segments, %d points. ",index, pathGeo->GetNumSegments(index), pathGeo->GetNumPoints(index));
		}
	}
	else
		SNIPLOG("Error, path geometry is nil");
	SNIPLOG("End path info of %s \n",pathName);
}



ErrorCode SnpInspectPathInfo::InspectTextOutline(ITextTarget* iTextTarget)
{
	ErrorCode status = kFailure;
	do
	{
		if (!iTextTarget)
		{
			break;
		}
		
		// Check to see if there is text selected
		RangeData r = iTextTarget->GetRange();
		TextIndex startOfRange = r.Start(nil);;
		TextIndex endOfRange = r.End();

		// Create and process kCreateOutlinesTextCmdBoss to create
		// the outline, and report Path info.
		// You may also use ICreateOutlinesSuite to create and selected created item
		InterfacePtr<ICommand> iCreateOutlineCmd( Utils<ICreateOutlinesUtils>()->CreateCOTextCmd( iTextTarget->GetTextModel(),
													startOfRange, endOfRange, kFalse /*do not delete original text*/ ) ) ;

		if (! iCreateOutlineCmd)
			break;

		status = CmdUtils::ProcessCommand( iCreateOutlineCmd ) ;
		if ( status == kSuccess )
		{
			UIDList itemList(iCreateOutlineCmd->GetItemListReference());
			UIDRef firstItem = itemList.GetRef(0);
			if (Utils<IPageItemTypeUtils>()->IsGroup(firstItem))
			{
				// When there is more than one line of text is selected,
				// the result is grouped into one group item
				InterfacePtr<IHierarchy> groupHier(firstItem, UseDefaultIID());
				IDataBase *db = firstItem.GetDataBase();
				UIDList tempList(db);
				groupHier->GetDescendents( &tempList, IID_IPATHGEOMETRY );

				// Just want to report the first item.
				int32 numGroupItems = tempList.Length();
				firstItem = tempList.GetRef(0);
				SNIPLOG("The outline is a group with %d items! Only first item in the group will be reported", numGroupItems);						
			}

			InterfacePtr<IPathGeometry> pathGeo(firstItem, UseDefaultIID());
			this->ReportPathInfo("text outline", pathGeo);
				
			// Then we delete the text outline(a compound path) we just created
			InterfacePtr<ICommand> deleteOutlineCmd( CmdUtils::CreateCommand(kDeleteCmdBoss) );
			deleteOutlineCmd->SetItemList( itemList );
			CmdUtils::ProcessCommand(deleteOutlineCmd);

		}
		else
		{
			//Can not create a text outline, report error
			SNIPLOG("Can not create a text outline.");
		}

	} while (false);

	return status;
}

ErrorCode SnpInspectPathInfo::InspectClippingPath(UIDList itemList)
{
	ErrorCode status = kFailure;
	do {
		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Clipping path requires layout selection");
			break;
		}				
		if (itemList.Length()> 1 ) 
		{
			SNIPLOG("You have multiple item selected. We will only report clipping path on first item");
		}

		//Query image object. The code is hard coded for only one item
		UIDRef imageRef = itemList.GetRef(0);
		SnpGraphicHelper graphicHelper(imageRef);
		InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
		if (imageAccess)
		{
			InterfacePtr<IPathGeometry> pathGeo(imageAccess, UseDefaultIID());
			this->ReportPathInfo("clipping path", pathGeo);
			status = kSuccess;
		}
		else
		{
			SNIPLOG("No clipping path. The item is not a graphic frame or item");
			status = kFailure;
		}

	} while (false);

	return status;
}

/**
Inspect text wrap path.
*/
ErrorCode SnpInspectPathInfo::InspectTextWrapPath(UIDList itemList)
{
	ErrorCode status = kFailure;
	do {
		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Text wrap requires layout selection");
			break;
		}

		if (itemList.Length()> 1 ) 
		{
			SNIPLOG("You have multiple item selected. We will only report text wrap on first item");
		}

		//The code is hard coded work for only one item
		UIDRef itemRef = itemList.GetRef(0);
		SnpGraphicHelper graphicHelper(itemRef);
		InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
		if (imageAccess) //If these is an image, use the one on the image
			itemRef = ::GetUIDRef(imageAccess);

		InterfacePtr<IStandOffData> standoff(itemRef, UseDefaultIID());
		if (!standoff )
			break;

		UID standoffID = standoff->GetStandOffUID();
		if (standoffID != kInvalidUID)
		{
			InterfacePtr<IPathGeometry> pathGeo(itemRef.GetDataBase(), standoffID, UseDefaultIID());
			this->ReportPathInfo("text wrap path", pathGeo);
			status = kSuccess;
		}
		else
		{
			SNIPLOG("No text wrap path was created for this item.");
			status = kFailure;
		}

	} while (false);

	return status;

}

ErrorCode SnpInspectPathInfo::InspectFramePath(UIDList itemList)
{
	ErrorCode status = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("No layout selection");
			break;
		}

		if (itemList.Length() > 1 ) 
		{
			SNIPLOG("Only path information of first item is reported");
		}

		// Now we want to show the path on the frame, even if 
		// the selection is a graphic item. The reverse of clipping path case
		SnpGraphicHelper graphicHelper(itemList.GetRef(0));
		UIDRef frame = graphicHelper.GetGraphicFrame();
		InterfacePtr<IPathGeometry> pathGeo(frame, UseDefaultIID());
		this->ReportPathInfo("spline frame path", pathGeo);
		status = kSuccess;
	} while (false);

	return status;
}

	
// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpInspectPathInfo available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerInspectPathInfo : public SnpRunnable
{
	public:
		// For SnippetRunner framework.

		/** Constructor.
		*/
		_SnpRunnerInspectPathInfo();

		/** Destructor
		*/
		virtual ~_SnpRunnerInspectPathInfo();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if a document is open, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);	

		/** Don't present this snippet in the framework's UI if the
			product we are running under is InCopy. 
			@return kFalse if the host product is InCopy, kTrue otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}

private:
		/** If there is selected text?
		@param iTextTarget text selection target.
		@return kTrue if text selection is not empty, otherwise kFalse.
		*/
		bool16 HasTextSelected(ITextTarget* iTextTarget);


};

/* Constructor
*/
_SnpRunnerInspectPathInfo::_SnpRunnerInspectPathInfo() : SnpRunnable("InspectPathInfo")
{
	this->SetDescription("Examine path information of text outline, clipping path, text wrap and frame path");
	this->SetPreconditions("Either page item selected or text selected");
	this->SetCategories("sdk_snippet, sdk_graphic");
}

/* Destructor
*/
_SnpRunnerInspectPathInfo::~_SnpRunnerInspectPathInfo()
{
}

/*
*/
bool16 _SnpRunnerInspectPathInfo::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 canRun = kFalse;

	do {
		// If we have text selection, we will have to make sure the text is selected.
		InterfacePtr<ITextTarget> iTextTarget( runnableContext, UseDefaultIID() ) ;
		if (iTextTarget)
		{
			RangeData r = iTextTarget->GetRange();
			TextIndex startOfRange = r.Start(nil);
			TextIndex endOfRange = r.End();

			if ( startOfRange < endOfRange)
				canRun = kTrue;
		}
		
		if (!canRun)
		{ 
			// If no text selection, see if it's a layout selection.
			InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
			if (layoutTarget == nil) 
			{
				break;
			}
			UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
			if (itemList.Length() > 0)
				canRun = kTrue;
		}

	} while (false);

	return canRun;
}

/* 
*/
ErrorCode _SnpRunnerInspectPathInfo::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do 
	{

		SnpInspectPathInfo instance;

		// Ask for the type of path to get.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		
		InterfacePtr<ITextTarget> iTextTarget( runnableContext, UseDefaultIID() ) ;
		bool16 textSelected = this->HasTextSelected(iTextTarget);
		if (textSelected)
		{	// Inspect text outline only
			choices.push_back(PMString("Text outline"));
			int32 choice  = parameterUtils->GetChoice("Choose path type.", choices);
			if (parameterUtils->WasDialogCancelled()) {
				break;
			}
			// Since this is the only choice, we just call inspect outline
			status = instance.InspectTextOutline(iTextTarget);
		}
		else
		{
			// Require a layout selection to be able to run.
			InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
			if (layoutTarget == nil) 
			{
				SNIPLOG("Path information requires layout selection");
				break;
			}
			UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);

			choices.push_back(PMString("Clipping path"));
			choices.push_back(PMString("Text wrap path"));
			choices.push_back(PMString("Spline frame path"));
			int32 choice  = parameterUtils->GetChoice("Choose path type.", choices);
			if (parameterUtils->WasDialogCancelled()) {
				break;
			}

			enum {kClippingPath, kTextWrapPath, kSplineFramePath};

			switch (choice) 
			{
			case kClippingPath:
				{
					status = instance.InspectClippingPath(itemList);
					break;
				}
			case kTextWrapPath:
				{
					status = instance.InspectTextWrapPath(itemList);
					break;
				}
			case kSplineFramePath:
				{
					status = instance.InspectFramePath(itemList);
					break;
				}
			}
		}

	} while(false);

	return status;
}

/* 
*/
bool16  _SnpRunnerInspectPathInfo::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		result = kFalse;
	}
	return result;
}

bool16 _SnpRunnerInspectPathInfo::HasTextSelected(ITextTarget* iTextTarget)
{
	// Check to see if there is text selected
	TextIndex					startOfRange = -1;
	TextIndex					endOfRange = -1;
	if (iTextTarget)
	{
		RangeData r = iTextTarget->GetRange();
		startOfRange = r.Start(nil);
		endOfRange = r.End();
	}

	return (startOfRange < endOfRange);

}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerInspectPathInfo instance_SnpRunnerInspectPathInfo;
DEFINE_SNIPPET(_SnpRunnerInspectPathInfo) 	
//End, SnpInspectPathInfo.cpp
