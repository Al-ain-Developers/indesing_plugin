//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnpRunnable.cpp $
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
#include "K2Vector.h"
#include "K2Assert.h"

// Project includes:
#include "SnpRunnable.h"
#include "SnipRunManager.h"
#include "SnipRunLog.h"

#include "ISnipRunSuite.h"
#include "ISnpRunnableContext.h"

#include "ILayoutUIUtils.h"
#include "ITextTarget.h"
#include "ILayoutTarget.h"
#include "ITableTarget.h"
#include "SDKLayoutHelper.h"
#include "ISelectUtils.h"
#include "ISelectionManager.h"
#include "IControlView.h"
#include "RangeData.h"
#include "ITextMiscellanySuite.h"
#include "ISelectionUtils.h"
#include "ISpreadList.h"
#include "ITextModel.h"
#include "ITableUtils.h"
#include "ITableModel.h"

constexpr ConstCString kEmptyCString = "";

/* Constructor register's snippet with the framework.
*/
SnpRunnable::SnpRunnable
(
	ConstCString name
)
:
	fName(name),
	fDescription(kEmptyCString),
	fPreconditions(kEmptyCString),
	fCategories(kEmptyCString)
{
	ASSERT(name != nil);
	if (name != nil) {
		SnipRunManager* snipRunnerManager = SnipRunManager::Instance();
		snipRunnerManager->AddSnippet(this);
	}
}

/* Destructor removes snippet from the framework.
*/
SnpRunnable::~SnpRunnable()
{
	SnipRunManager* snipRunnerManager = SnipRunManager::Instance();
//	Watson# 1315301: don't delete snippet here.  A SnpRunnable instance is static, in Xcode, it doesn't get deleted until InDesign Shutdown
//	RemoveSnippet relies on CoolTypeMain to do its job, since this will called after ID shutdown, CoolTypeMain will be
//	gone by then and results in crash.  Now call SnipRunManager::DeleteInstance() inside a shutdown responder, and DeletInstance
//	will remove all snippets there.  Leave the DeleteInstance here intact as an extra protection for memory leak, shouldn't 
//	get called.

//	snipRunnerManager->RemoveSnippet(this);	
	if (snipRunnerManager->GetNumberOfSnippets() <= 0)
	{
		snipRunnerManager->DeleteInstance();
	}
}

/* Unit Test.
*/
ErrorCode SnpRunnable::RunUnitTest(ISnpRunnableContext* runnableContext)
{
	return kSuccess;
}


/** 
	Set up the proper InDesign context for the snippert so that it
	can be run.
	@param runnableContext
	@return kSuccess on success, other ErrorCode otherwise
*/
ErrorCode SnpRunnable::SetupContext(ISnpRunnableContext* runnableContext)
{
	ISnipRunSuite::eSnpRunContextType contextType = this->GetContext();

	/* handle 'common' contexts */
	switch (contextType)	/* TODO: should we move this to a utility? */
	{
		case ISnipRunSuite::kSnpRunNoContext:
			{
				/* do nothing? */
			}
			break;
		case ISnipRunSuite::kSnpRunWorkspaceContext: 
			{
				/* make sure there is no other active context? */
			}
			break;
		case ISnipRunSuite::kSnpRunFrontDocContext: 
			{
				/* make sure there is a front document? */
				
				IDocument* doc = Utils<ILayoutUIUtils>()->GetFrontDocument();
				if (doc)
				{
					/* already have a front document */
				}
				else
				{
					SDKLayoutHelper layoutHelper;
					
					UIFlags uiFlags = K2::kSuppressUI;
					PMReal width = 612;
					PMReal height = 792;
					int32 pages = 1;
					int32 pagesPerSpread = 1;

					UIDRef docRef = layoutHelper.CreateDocument(uiFlags, width, height, pages, pagesPerSpread);
					ErrorCode ec = layoutHelper.OpenLayoutWindow(docRef);
				}
			}
			break;
		case ISnipRunSuite::kSnpRunLayoutTargetContext: 
			{
				/* make sure there is a front document, with a page item selected? */
				
				InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
				if (layoutTarget)
				{
					/* already have a layout target! */
				}
				else
				{
					SDKLayoutHelper layoutHelper;
					
					UIFlags uiFlags = K2::kSuppressUI;
					PMReal width = 612;
					PMReal height = 792;
					int32 pages = 1;
					int32 pagesPerSpread = 1;
					PMRect bounds(0, 0, 100, 100);

					UIDRef docRef = layoutHelper.CreateDocument(uiFlags, width, height, pages, pagesPerSpread);
					ErrorCode ec = layoutHelper.OpenLayoutWindow(docRef);
					InterfacePtr<ISpreadList> spreadList(docRef, UseDefaultIID());
					if(!spreadList) {
						break;
					}
					UIDRef spreadRef = UIDRef(docRef.GetDataBase(), spreadList->GetNthSpreadUID(0));
					UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
					UIDRef frameRef = layoutHelper.CreateRectangleFrame(spreadLayerRef, bounds);
				}
			}
			break;
		case ISnipRunSuite::kSnpRunTextTargetContext: 
		case ISnipRunSuite::kSnpRunTextSelectionTargetContext: 
			{
				/* make sure there is a front document, with text selected? */
				
				InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
				if (textTarget)
				{
					/* already have a text target! */
				}
				else
				{
					SDKLayoutHelper layoutHelper;
					
					UIFlags uiFlags = K2::kSuppressUI;
					PMReal width = 612;
					PMReal height = 792;
					int32 pages = 1;
					int32 pagesPerSpread = 1;
					PMRect bounds(0, 0, 100, 100);
					int32 numberOfColumns = 0;
  					bool16 verticalFrame = kFalse;
					UIDRef storyUIDRef;

					UIDRef docRef = layoutHelper.CreateDocument(uiFlags, width, height, pages, pagesPerSpread);
					ErrorCode ec = layoutHelper.OpenLayoutWindow(docRef);
					InterfacePtr<ISpreadList> spreadList(docRef, UseDefaultIID());
					if(!spreadList) {
						break;
					}
					UIDRef spreadRef = UIDRef(docRef.GetDataBase(), spreadList->GetNthSpreadUID(0));
					UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
					UIDRef frameRef = layoutHelper.CreateTextFrame(spreadLayerRef,
											bounds,
											numberOfColumns,
						  					verticalFrame,
											&storyUIDRef);

                    Utils<ISelectUtils>()->ProcessSelectText(
                              storyUIDRef, RangeData(0, 0, RangeData::kLeanForward),
                              Selection::kScrollIntoView, nil,
                              (ISelectionManager*)0, (IControlView*)0);

					if (contextType == ISnipRunSuite::kSnpRunTextSelectionTargetContext)
					{
						InterfacePtr<ISelectionManager> selectionManager(Utils<ISelectionUtils>()->QueryActiveSelection());
						InterfacePtr<ITextMiscellanySuite> textMiscSuite(static_cast<ITextMiscellanySuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_ITEXTMISCELLANYSUITE, selectionManager)));
						if (textMiscSuite)
							textMiscSuite->FillWithPlaceHolderText();
						
						InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
						int32 totalLength = textModel->TotalLength();
						if (totalLength > 1)
						{
							Utils<ISelectUtils>()->ProcessSelectText(
									  storyUIDRef, RangeData(0, totalLength-1, RangeData::kLeanForward),
									  Selection::kScrollIntoView, nil,
									  (ISelectionManager*)0, (IControlView*)0);
						}
					}
				}
			}
			break;
		case ISnipRunSuite::kSnpRunTableTargetContext: 
			{
				/* make sure there is a front document, with a table cell selected? */
				
				InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
				if (tableTarget)
				{
					/* already have a text target! */
				}
				else
				{
					SDKLayoutHelper layoutHelper;
					
					UIFlags uiFlags = K2::kSuppressUI;
					PMReal width = 612;
					PMReal height = 792;
					int32 pages = 1;
					int32 pagesPerSpread = 1;
					PMRect bounds(0, 0, 100, 100);
					int32 numberOfColumns = 0;
  					bool16 verticalFrame = kFalse;
					UIDRef storyUIDRef;

					UIDRef docRef = layoutHelper.CreateDocument(uiFlags, width, height, pages, pagesPerSpread);
					ErrorCode ec = layoutHelper.OpenLayoutWindow(docRef);
					InterfacePtr<ISpreadList> spreadList(docRef, UseDefaultIID());
					if(!spreadList) {
						break;
					}
					UIDRef spreadRef = UIDRef(docRef.GetDataBase(), spreadList->GetNthSpreadUID(0));
					UIDRef spreadLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadRef);
					UIDRef frameRef = layoutHelper.CreateTextFrame(spreadLayerRef,
											bounds,
											numberOfColumns,
						  					verticalFrame,
											&storyUIDRef);

                    Utils<ISelectUtils>()->ProcessSelectText(
                              storyUIDRef, RangeData(0, 0, RangeData::kLeanForward),
                              Selection::kScrollIntoView, nil,
                              (ISelectionManager*)0, (IControlView*)0);

					//create table
					InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
					ASSERT(textModel);
					if( textModel == nil)
						break;

					// Use the ITableUtils facade.
					Utils<ITableUtils> tableUtils;
					if (!tableUtils)
						break;

					const TextIndex at = 0;
					const int32 numRows = 4;
					const int32 numCols = 2;
					const PMReal rowHeight = 10;
					const PMReal colWidth = 40;
					const CellType cellType = kTextContentType;

					tableUtils->InsertTable (textModel, at, 0,
												 numRows, numCols,
												 rowHeight, colWidth,
												 cellType,
												 ITableUtils::eSetSelectionInFirstCell);

				}
			}
			break;
		case ISnipRunSuite::kSnpRunCustomContext:
			ASSERT_FAIL("ISnipRunSuite::kSnpRunCustomContext requires custom implementation of SetupContext(ISnpRunnableContext* runnableContext)");
			return kFailure;
		default:
			ASSERT_FAIL("Unknown context type");
			return kFailure;
	}

	return kSuccess;
}


// End, SnpRunnable.cpp

