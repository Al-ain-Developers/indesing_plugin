//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateSpreadsAndPages.cpp $
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
#include "INewSpreadCmdData.h"
#include "IApplyMasterCmdData.h"
#include "IDuplicateSpreadCmdData.h"
#include "IGeometry.h"
#include "IIntData.h"
#include "ISpread.h"
#include "IDocument.h"
#include "ILayoutCmdData.h"
#include "ISpreadList.h"
#include "IBoolData.h"
#include "IPageLayoutPrefs.h"
#include "IPageList.h"
#include "IUIDData.h"
#include "IPageSetupPrefs.h"
#include "IPageCmdData.h"
#include "IMovePageData.h"

// General includes:
#include "Utils.h"
#include "CmdUtils.h"
#include "PersistUtils.h"
#include "UIDList.h"
#include "PreferenceUtils.h"
#include "K2Vector.h"
#include "PMPageSize.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/** 
	\li	How to create spreads in a document.	
	\li	How to copy the contents of one spread onto another spread.
	\li How to create a new spread duplicated from an existing spread.
	\li How to delete an existing spread in the document.
	\li How to change the ordering of the spreads in a document.
	\li How to add new pages to an existing spread in the document.
	\li How to delete pages from an existing spread in the document.
	\li How to move a page to a different index within and across the spreads.
	\li How to clone pages (contents included) into new spreads int he document.
 
 	@ingroup sdk_snippet
 	@ingroup sdk_layout
*/
class SnpManipulateSpreadsAndPages 
{
public:
	/** Constructor.
	 */
	SnpManipulateSpreadsAndPages() {}

	/** Destructor.
	 */
	virtual	~SnpManipulateSpreadsAndPages() {}
	
private:
	// the in this section is the code that does the actual modfication of the model.
	/**
		Changes the actual model. Creates a spread (at position 0)with the defined parameters.
		@param docUIDRef IN the document the spread is to be added to.
		@param pageDimensions IN the dimensions for pages in the spread.
		@param numberOfPages IN the number of pages to be added to the spread.
		@param numberOfSpreads IN the number of spreads to be added.
		@return kSuccess if the if the model update is a success.
		@see INewSpreadCmdData
		@see kNewSpreadCmdBoss
	*/
	ErrorCode CreateSpreads(const UIDRef docUIDRef, const PMPageSize pageDimensions, const int32 numberOfPages, const int32 numberOfSpreads);

	/**
		Changes the actual model, copies from the source spread onto the destination spread. 
		@param sourceSpreadUIDRef IN the source spread.
		@param destSpreadUIDRef IN the destination spread.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode DuplicateSpreadContents(const UIDRef sourceSpreadUIDRef, const UIDRef destSpreadUIDRef);

	/**
		Does the work at the model level to copy a document spread (and all the contents). 
		@param iDocument IN the document to be modified
		@param sourceSpread IN the source spread to be copied.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode CreateSpreadFromSpread(const IDocument* iDocument,const UIDRef sourceSpread);

	/**
		Does the actual work of deleting the spread. 
		@param spreadUIDList IN the list of spreads to be deleted.
		@param allowShuffle IN defines whether re-shuffling of the pages to fit the format of the 
			document is allowed after the operation. For example, if you have two spreads, with facing pages,
			two pages per spread (one page in the first spread), deletion of a single page with page shuffling turned
			on will result in two spreads, with one page in each.
			Generally, you will want to reflect the document preference for this. However, if you have several operations
			to perform, you might want to optimise the shuffling to only occur after the last operation.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode DeleteSpread(const UIDList& spreadUIDList, const bool16 allowShuffle);

	/**
		Does the actual work of moving the spread. 
		@param spreadsToMoveUIDList IN the list of spreads to move.
		@param beforeThisSpread IN identifies the new position of the spreads. The spreads are moved to 
			be before this spread.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode MoveSpreads(const UIDList& spreadsToMoveUIDList, const UIDRef beforeThisSpread);

	/**
		Does the actual work of creating pages on the specified spread. 
		@param iDocument IN the document being manipulated
		@param spreadToAddTo IN spread that is the target for the page addition operation.
		@param numPagesToInsert IN the number of pages to add to the spread.
		@param pageToInsertAt IN the index of the page to insert the new pages to. If this is invalid (i.e. doesn't
			exist within the page list for the spread), the low level command will fail.
		@param pageSizeRect IN the page size of pages
		@param allowShuffle IN defines whether re-shuffling of the pages to fit the format of the 
			document is allowed after the operation. For example, if you have two spreads, with facing pages,
			two pages per spread (one page in the first spread), deletion of a single page with page shuffling turned
			on will result in two spreads, with one page in each.
			Generally, you will want to reflect the document preference for this. However, if you have several operations
			to perform, you might want to optimise the shuffling to only occur after the last operation.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode CreatePages(const IDocument* iDocument, const UIDRef spreadToAddTo, const int16 numPagesToInsert, const int16 pageToInsertAt, const PMPageSize& pageSizeRect, const bool16 allowShuffle);

	/**
		Does the actual work of deleting the pages from the document. 
		@param iDocument IN the document being manipulated
		@param numPagesToDelete IN number of pages to delete.
		@param allowShuffle IN defines whether re-shuffling of the pages to fit the format of the 
			document is allowed after the operation. For example, if you have two spreads, with facing pages,
			two pages per spread (one page in the first spread), deletion of a single page with page shuffling turned
			on will result in two spreads, with one page in each.
			Generally, you will want to reflect the document preference for this. However, if you have several operations
			to perform, you might want to optimise the shuffling to only occur after the last operation.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode DeletePages(const IDocument* iDocument,const int32 numPagesToDelete, const bool16 allowShuffle);
	
	/**
		Does the actual work of moving a page to the target spread in the index position specified. 
		@param pageToMove IN the page to be moved.
		@param spreadToMoveTo IN the spread that is the target of the move.
		@param indexToInsertInto IN the page index in the new spread to move the page to.
		@param allowShuffle IN defines whether re-shuffling of the pages to fit the format of the 
			document is allowed after the operation. For example, if you have two spreads, with facing pages,
			two pages per spread (one page in the first spread), deletion of a single page with page shuffling turned
			on will result in two spreads, with one page in each.
			Generally, you will want to reflect the document preference for this. However, if you have several operations
			to perform, you might want to optimise the shuffling to only occur after the last operation.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode MovePage(const UIDRef pageToMove, const UIDRef spreadToMoveTo, const int32 indexToInsertInto, const bool16 allowShuffle);

	/**
		Invokes the command required to clone the page list identified in the document.
		@param iDocument IN the document the pages are cloned in.
		@param pageUIDList IN the list of pages to be copied.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode CreatePagesFromPages(const IDocument* iDocument, const UIDList& pageUIDList);

public:
	// the code in this section drives the model UI code. It adapts from the snippetrunner framework to 
	// be environment neutral or model centric.
	/**
		The UI layer for this sub-snippet. Responsible for determining the parameters required to 
		drive the lower level call. 
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet completes normally.
	*/
	ErrorCode CreateSpreads(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Responsible for determining which spread should be duplicated and which 
		spread it should be duplicated to. 
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode DuplicateSpreadContents(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Responsible for determining which spread should be the source
		for the copy command. 
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet compleses successfully.
	*/
	ErrorCode CreateSpreadFromSpread(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Responsible for determining which spread is the target for the
		delete operation. 
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet compleses successfully.
	*/
	ErrorCode DeleteSpread(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Responsible for mapping the context to the spread list we wish to
		manipulate. This snippet moves the first spread to the end of the list (i.e. it becomes the last spread).
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet compleses successfully.
	*/
	ErrorCode MoveSpreads(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Gathers the parameters required to drive the operation.
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet compleses successfully.
	*/
	ErrorCode CreatePages(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Determines how many pages to delete and whether shuffling should 
		be performed.
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode DeletePages(ISnpRunnableContext* iSnpRunnableContext);

	/**
		The UI layer for this sub-snippet. Determines which page gets moved, the target spread and 
		the index in the target spread the page has to be moved to.
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode MovePage(ISnpRunnableContext* iSnpRunnableContext);

	/** 
		The UI layer for this sub-snippet. Determines how many pages to clone.
		@param iSnpRunnableContext IN the environment.
		@return kSuccess if the snippet completes successfully.
	*/
	ErrorCode CreatePagesFromPages(ISnpRunnableContext* iSnpRunnableContext);

private:
	// this section is for utility methods
	/** 
		Performs the tast of selecting a spread from the list of those available.
		@param selectedSpread OUT the spread chosen by the user.
		@param iDocument IN the document from which to select a spread.
		@param prompt IN text to prompt the user with.
		@return kFailure on error, or if the user cancels.
	*/
	ErrorCode SelectSpread(UIDRef& selectedSpread, int32& spreadIndex, const IDocument* iDocument, const char* prompt);

	/**
		provides the shuffling preference for the document passed in.
		@param shufflePref OUT set to the current value of the shuffle preference.
		@param iDocument IN the document whose shuffle preference we are after.
		@return kFailure on errror.
	*/
	ErrorCode  GetShufflePref(bool16& shufflePref, const IDocument* iDocument);

};

/*
*/
ErrorCode 
SnpManipulateSpreadsAndPages::GetShufflePref(bool16& shufflePref, const IDocument* iDocument){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IPageLayoutPrefs> iPageLayoutPrefs(static_cast<IPageLayoutPrefs *>(::QueryPreferences(IID_IPAGELAYOUTPREFERENCES, iDocument)));
		if (iPageLayoutPrefs == nil){
			ASSERT(iPageLayoutPrefs);
			break;
		}
		shufflePref = iPageLayoutPrefs->GetShuffle();
		status = kSuccess;
	} while(kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpManipulateSpreadsAndPages::SelectSpread(UIDRef& selectedSpread, int32& spreadIndex, const IDocument* iDocument, const char* prompt){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		InterfacePtr<ISpreadList> iSpreadList(iDocument,UseDefaultIID());
		if (iSpreadList == nil){
			ASSERT(iSpreadList);
			break;
		}
		int32 numOfSpreads = iSpreadList->GetSpreadCount();
		if (numOfSpreads == 0){
			ASSERT(numOfSpreads > 0);
			break;
		}

		K2Vector<PMString> choices;
		// build the list of source spreads
		for (int loop=0;loop<numOfSpreads;loop++){
			char buf[100];
			sprintf(buf,"Spread %d",loop);
			choices.push_back(PMString(buf));
		}

		spreadIndex = iSnipRunParameterUtils->GetChoice(prompt, choices);

		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		InterfacePtr<IGeometry> iSpreadGeometry(iSpreadList->QueryNthSpread(spreadIndex));
		if (iSpreadGeometry == nil){
			ASSERT(iSpreadGeometry);
			break;
		}
		selectedSpread = ::GetUIDRef(iSpreadGeometry);
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreatePagesFromPages(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		InterfacePtr<ISpreadList> iSpreadList(iDocument,UseDefaultIID());
		if (iSpreadList == nil){
			ASSERT(iSpreadList);
			break;
		}
		InterfacePtr<IPageList> iPageList(iDocument,UseDefaultIID());
		if (iPageList == nil){
			ASSERT(iPageList);
			break;
		}

		int32 totalNumOfPages = iPageList->GetPageCount();

		// Get number of pages we wish to clone
		int32 numOfPages = iSnipRunParameterUtils->GetInt32(PMString("Number of pages"), 1, 1, totalNumOfPages);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}
	
		K2Vector<PMString> pageOrder;
		pageOrder.push_back(PMString("First to last"));
		pageOrder.push_back(PMString("Last to first"));
		enum {kFirstToLast, kLastToFirst};
		int32 response = iSnipRunParameterUtils->GetChoice("What page ordering", pageOrder);

		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}
		bool16	FirstToLast = (response == kFirstToLast) ? kFalse : kTrue;

		IDataBase* iDataBase = ::GetUIDRef(iDocument).GetDataBase();
		if (iDataBase == nil){
			ASSERT(iDataBase);
			break;
		}

		UIDList pageUIDList(iDataBase);

		for (int32 loop = 0; loop <numOfPages; loop++){
			if (FirstToLast==kTrue){
				pageUIDList.Insert(iPageList->GetNthPageUID(loop));
			} else {
				pageUIDList.Append(iPageList->GetNthPageUID(loop));
			}
		}
		status = this->CreatePagesFromPages(iDocument,pageUIDList);
	}while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreatePagesFromPages(const IDocument* iDocument, const UIDList& pageUIDList){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iCreatePageFromPageCmd(CmdUtils::CreateCommand(kCreatePageFromPageCmdBoss));
		if (iCreatePageFromPageCmd == nil){
			ASSERT(iCreatePageFromPageCmd);
			break;
		}
		iCreatePageFromPageCmd->SetItemList(pageUIDList);
		InterfacePtr<ILayoutCmdData> iLayoutCmdData(iCreatePageFromPageCmd,UseDefaultIID());
		if (iLayoutCmdData == nil){
			ASSERT(iLayoutCmdData);
			break;
		}
		// it is valid to set the layout control data parameter to nil, there are times when there is no view.
		iLayoutCmdData->Set(::GetUIDRef(iDocument),nil);
		// process the command
		status = CmdUtils::ProcessCommand(iCreatePageFromPageCmd);
	}while(false);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::MovePage(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		IDataBase* iDataBase = ::GetUIDRef(iDocument).GetDataBase();
		if (iDataBase == nil){
			ASSERT(iDataBase);
			break;
		}

		// get the destination spread
		UIDRef destSpread;
		int32 spreadIndex;
		if (this->SelectSpread(destSpread,spreadIndex,iDocument,"Which spread to move page to?") == kFailure){
			break;
		}
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		InterfacePtr<ISpread> iSpread(destSpread,UseDefaultIID());
		if (iSpread == nil){
			ASSERT(iSpread);
			break;
		}
		// if the target and source spreads are the samne, and the spread only has a single
		// page, the move doesn't mean anything.
		if (spreadIndex == 0 && iSpread->GetNumPages()==1){
			SNIPLOG("Moving the page in a single page spread won't do anything");
			break;
		}
		// if the target spread is the same as the source, the index we can insert to is reduced by the page being moved.
		int32 numOfPagesInSpread = (spreadIndex == 0) ? iSpread->GetNumPages()-1 : iSpread->GetNumPages();
		// we can place the page to be moved in the numberOfPages in the spread + 1 (except when source spread == dest spread). 
		int32 placeNewPageIndex = iSnipRunParameterUtils->GetInt32(PMString("Index to place new page?"), 0, 0, numOfPagesInSpread);

		// we want to place page 0, get the pagelist from the document, that gives the pageUID.
		InterfacePtr<IPageList> iPageList(iDocument,UseDefaultIID());
		if (iPageList == nil){
			ASSERT(iPageList);
			break;
		}
		UID page0UID = iPageList->GetNthPageUID(0);

		bool16	allowShuffle;
		if (this->GetShufflePref(allowShuffle,iDocument)==kFailure){
			break;
		}

		status = this->MovePage(UIDRef(iDataBase,page0UID),destSpread,placeNewPageIndex,allowShuffle);
	}while (kFalse);
	return status;
}


ErrorCode
SnpManipulateSpreadsAndPages::MovePage(const UIDRef pageToMove, const UIDRef spreadToMoveTo, const int32 indexToInsertInto, const bool16 allowShuffle){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iMovePageCmd(CmdUtils::CreateCommand(kMovePageCmdBoss));
		if (iMovePageCmd == nil){
			ASSERT(iMovePageCmd);
			break;
		}
		iMovePageCmd->SetItemList(UIDList(pageToMove));

		InterfacePtr<IMovePageData> iMovePageData(iMovePageCmd,UseDefaultIID());
		if (iMovePageData == nil){
			ASSERT(iMovePageData);
			break;
		}
		iMovePageData->Set(spreadToMoveTo,indexToInsertInto /*, doNotify, kDefaultBinding*/);
		
		InterfacePtr<IBoolData> iBoolData(iMovePageData,UseDefaultIID());
		if (iBoolData == nil){
			ASSERT(iBoolData);
			break;
		}
		iBoolData->Set(allowShuffle);

		// process the command
		status = CmdUtils::ProcessCommand(iMovePageCmd);

	} while(false);
	return status;	
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::DeletePages(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		// Get number of pages
		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		InterfacePtr<IPageList> iPageList(iDocument,UseDefaultIID());
		if (iPageList == nil){
			ASSERT(iPageList);
			break;
		}

		int32 totalNumOfPages = iPageList->GetPageCount();
		if (totalNumOfPages == 1){
			SNIPLOG("Operation would leave document with no pages!");
			break;
		}
		// Get number of pages
		int32 numOfPages = iSnipRunParameterUtils->GetInt32(PMString("Number of pages to delete?"), 1, 1, totalNumOfPages-1);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}
        bool16	allowShuffle;
		if (this->GetShufflePref(allowShuffle,iDocument) == kFailure){
			break;
		}
		
		status = this->DeletePages(iDocument,numOfPages,allowShuffle);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::DeletePages(const IDocument* iDocument,const int32 numPagesToDelete, const bool16 allowShuffle){
	ErrorCode status = kFailure;
	do {
		IDataBase* iDataBase = ::GetUIDRef(iDocument).GetDataBase();
		if (iDataBase == nil){
			ASSERT(iDataBase);
			break;
		}

		UIDList pageUIDList(iDataBase);

		

		int32 SpreadCount = 0;
		InterfacePtr<IPageList> iPageList(iDocument,UseDefaultIID());
		if (iPageList == nil){
			ASSERT(iPageList);
			break;
		}
		for (int32 loop=0;loop<numPagesToDelete;loop++){
			pageUIDList.Insert(iPageList->GetNthPageUID(loop));
		}

		InterfacePtr<ICommand> iDeletePageCmd(CmdUtils::CreateCommand(kDeletePageCmdBoss));
		if (iDeletePageCmd == nil){
			ASSERT(iDeletePageCmd);
			break;
		}
		InterfacePtr<IBoolData> iBoolData(iDeletePageCmd,UseDefaultIID());
		if (iBoolData == nil){
			ASSERT(iBoolData);
			break;
		}
		iBoolData->Set(allowShuffle);
		iDeletePageCmd->SetItemList(pageUIDList);
		// process the command
		status = CmdUtils::ProcessCommand(iDeletePageCmd);

	} while(false);
	return status;	
}


/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreatePages(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}

		UIDRef targetSpread;
		int32 spreadIndex;
		if (this->SelectSpread(targetSpread,spreadIndex,iDocument,"Which spread to add page(s) to?") == kFailure){
			break;
		}

		int32 numPagesToInsert = iSnipRunParameterUtils->GetInt32("How many pages to insert?",1,1,10);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}
		int32 numOfPage = iSnipRunParameterUtils->GetInt32("What page position to insert to?",0,0,10);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}
		
		
		InterfacePtr<IPageSetupPrefs> iPageSetupPrefs(static_cast<IPageSetupPrefs *>(::QueryPreferences(IID_IPAGEPREFERENCES, iDocument)));
		if (iPageSetupPrefs == nil){
			ASSERT(iPageSetupPrefs);
			break;
		}
		PMPageSize dfltPMRectPageSize = iPageSetupPrefs->GetPageSizePref();	

		PMReal pageWidth = dfltPMRectPageSize.OutputWidth();
		pageWidth = iSnipRunParameterUtils->GetPMReal("Specify width of the page.", pageWidth, 5.0, 4000.0);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		PMReal pageHeight = dfltPMRectPageSize.OutputHeight();
		pageHeight = iSnipRunParameterUtils->GetPMReal("Specify height of the page.", pageHeight, 5.0, 4000.0);
		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		PMPageSize usrDefPMRectPageSize(pageWidth, pageHeight);

        bool16	allowShuffle;
		if (this->GetShufflePref(allowShuffle,iDocument) == kFailure){
			break;
		}

		status = this->CreatePages(iDocument, targetSpread, numPagesToInsert, numOfPage, usrDefPMRectPageSize, allowShuffle);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreatePages(const IDocument* iDocument, const UIDRef spreadToAddTo,const int16 numPagesToInsert, const int16 pageToInsertAt, const PMPageSize& pageSize, const bool16 allowShuffle){
	ErrorCode status = kFailure;
	PMRect pageRect(PMPoint(0,0),pageSize.OutputDimensions());
	do {

		InterfacePtr<ICommand> iNewPageCmd(CmdUtils::CreateCommand(kNewPageCmdBoss));
		if (iNewPageCmd == nil){
			ASSERT(iNewPageCmd);
			break;
		}
		InterfacePtr<IPageCmdData> iPageCmdData(iNewPageCmd,UseDefaultIID());
		if (iPageCmdData == nil){
			ASSERT(iPageCmdData);
			break;
		}

		K2Vector< PMRect> pageBoundingBoxes;
		for( int32 i = 0; i < numPagesToInsert; ++i){
			pageBoundingBoxes.push_back( pageRect);
		}
		iPageCmdData->SetNewPageCmdData( spreadToAddTo, numPagesToInsert, pageToInsertAt, &pageBoundingBoxes, nil);


		InterfacePtr<IBoolData> iBoolData(iNewPageCmd,UseDefaultIID());
		if (iBoolData == nil){
			ASSERT(iBoolData);
			break;
		}
		iBoolData->Set(allowShuffle);

		status = CmdUtils::ProcessCommand(iNewPageCmd);

	} while(false);
	return status;	
}


/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::MoveSpreads(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		InterfacePtr<ISpreadList> iSpreadList(iDocument,UseDefaultIID());
		if (iSpreadList == nil){
			ASSERT(iSpreadList);
			break;
		}

		int32 numOfSpreads = iSpreadList->GetSpreadCount();
		if (numOfSpreads == 1){
			SNIPLOG("Document has a single spread - no move possible.");		
			break;
		}

		IDataBase* iDataBase = ::GetUIDRef(iDocument).GetDataBase();
		if (iDataBase == nil){
			ASSERT(iDataBase);
			break;
		}

		UIDList spreadUIDList(iDataBase);

		// the command moves the spreads in the UIDList to precede the spread defined on 
		// the UIDList, if we wish to move the first spread to the end, to achieve this
		// we need to move all the other spreads to precede it.
		// build the list of all other spreads.
		ErrorCode innerStatus = kSuccess;
		for (int loop=1;loop<numOfSpreads;loop++){
			char buffer[100];
			sprintf(buffer,"Moving spread %d",loop);
			SNIPLOG(buffer);
			InterfacePtr<IGeometry> iSpreadGeometry(iSpreadList->QueryNthSpread(loop));
			if (iSpreadGeometry == nil){
				ASSERT(iSpreadGeometry);
				innerStatus = kFailure;
				break;
			}
			UID spreadUID = ::GetUIDRef(iSpreadGeometry).GetUID();
			spreadUIDList.Insert(spreadUID);
		}
		if (innerStatus == kFailure){
			break;
		}
		// we want all other spreads to precede spread 0, this moves the first spread to the end
		InterfacePtr<IGeometry> iSpread0Geometry(iSpreadList->QueryNthSpread(0));
		if (iSpread0Geometry == nil){
			ASSERT(iSpread0Geometry);
			break;
		}

		status = this->MoveSpreads(spreadUIDList, ::GetUIDRef(iSpread0Geometry));
	} while (kFalse);
	return status;
}

ErrorCode
SnpManipulateSpreadsAndPages::MoveSpreads(const UIDList& spreadsToMoveUIDList, const UIDRef beforeThisSpread){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iMoveSpreadCmd(CmdUtils::CreateCommand(kMoveSpreadCmdBoss));
		if (iMoveSpreadCmd == nil){
			ASSERT(iMoveSpreadCmd);
			break;
		}
		iMoveSpreadCmd->SetItemList(spreadsToMoveUIDList);

		InterfacePtr<IUIDData> iMoveSpreadCmdUIDData(iMoveSpreadCmd,UseDefaultIID()); 
		if (iMoveSpreadCmdUIDData == nil){
			ASSERT(iMoveSpreadCmdUIDData);
			break;
		}
		iMoveSpreadCmdUIDData->Set(beforeThisSpread);
		// process the command
		status = CmdUtils::ProcessCommand(iMoveSpreadCmd);
	} while(false);
	return status;	
}


/*
*/
ErrorCode 
SnpManipulateSpreadsAndPages::DeleteSpread(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnpRunParameterUtils;
		if (iSnpRunParameterUtils == nil){
			ASSERT(iSnpRunParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		InterfacePtr<ISpreadList> iSpreadList(iDocument,UseDefaultIID());
		if (iSpreadList == nil){
			ASSERT(iSpreadList);
			break;
		}

		if (iSpreadList->GetSpreadCount() == 1){
			SNIPLOG("Deleting a spread will leave the document with no spreads!");
			break;
		}
		UIDRef spreadToDelete;
		int32 chosenSpread;
		if (this->SelectSpread(spreadToDelete,chosenSpread,iDocument,"Which spread to delete?") == kFailure){
			break;
		}

		// Page shuffling should reflect the current document preference.
        bool16	allowShuffle;
		if (this->GetShufflePref(allowShuffle,iDocument) == kFailure){
			break;
		}

		status = this->DeleteSpread(UIDList(spreadToDelete), allowShuffle);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpManipulateSpreadsAndPages::DeleteSpread(const UIDList& spreadUIDList, const bool16 allowShuffle){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iDeleteSpreadCmd(CmdUtils::CreateCommand(kDeleteSpreadCmdBoss));
		if (iDeleteSpreadCmd == nil){
			ASSERT(iDeleteSpreadCmd);
			break;
		}

		InterfacePtr<IBoolData> iBoolData(iDeleteSpreadCmd,UseDefaultIID());
		if (iBoolData == nil){
			ASSERT(iBoolData);
			break;
		}

		iBoolData->Set(allowShuffle);
		iDeleteSpreadCmd->SetItemList(spreadUIDList);
		// process the command
		status = CmdUtils::ProcessCommand(iDeleteSpreadCmd);
	} while (kFalse);
	return status;
}

ErrorCode
SnpManipulateSpreadsAndPages::CreateSpreadFromSpread(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iParameterUtils;
		if (iParameterUtils == nil){
			ASSERT(iParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		UIDRef spreadToCopy;
		int32 spreadIndex;
		if (this->SelectSpread(spreadToCopy,spreadIndex,iDocument,"Which spread to copy?") == kFailure){
			break;
		}

		status = this->CreateSpreadFromSpread(iDocument,spreadToCopy);
	} while (kFalse);
	return status;
}


/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreateSpreadFromSpread(const IDocument* iDocument,const UIDRef sourceSpread){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iCreateSpreadFromSpreadCmd(CmdUtils::CreateCommand(kCreateSpreadFromSpreadCmdBoss));
		if (iCreateSpreadFromSpreadCmd == nil){
			ASSERT(iCreateSpreadFromSpreadCmd);
			break;
		}

		UIDList spreadUIDList(sourceSpread);

		InterfacePtr<ILayoutCmdData> iLayoutCmdData(iCreateSpreadFromSpreadCmd,UseDefaultIID());
		if (iLayoutCmdData == nil){
			ASSERT(iLayoutCmdData);
			break;
		}

		// setting the layoutcontroldata parameter to nil is valid, there will be cases where you do not have a window
		iLayoutCmdData->Set(::GetUIDRef(iDocument),nil);

		iCreateSpreadFromSpreadCmd->SetItemList(spreadUIDList);
		// process the command
		status = CmdUtils::ProcessCommand(iCreateSpreadFromSpreadCmd);

	} while(false);
	return status;	
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::DuplicateSpreadContents(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iParameterUtils;
		if (iParameterUtils == nil){
			ASSERT(iParameterUtils);
			break;
		}

		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		UIDRef sourceSpread,destSpread;
		int32 sourceIndex,destIndex;
		if (this->SelectSpread(sourceSpread,sourceIndex,iDocument,"Which spread to copy from?") == kFailure){
			break;
		}
		if (this->SelectSpread(destSpread,destIndex,iDocument,"Which spread to copy to?") == kFailure){
			break;
		}
		// the operation is only allowed between spreads with the same number of pages.
		InterfacePtr<ISpread> iFromSpread(sourceSpread, UseDefaultIID());
		if (iFromSpread == nil){
			ASSERT(iFromSpread);
			break;
		}
		InterfacePtr<ISpread> iToSpread(destSpread, UseDefaultIID());
		if (iToSpread == nil){
			ASSERT(iToSpread);
			break;
		}
		
		if (iFromSpread->GetNumPages() != iToSpread->GetNumPages()){
			SNIPLOG("The source and destination spreads need to have the same number of pages!");
			break;
		}

		status = this->DuplicateSpreadContents(sourceSpread,destSpread);

	} while(false);
	return status;	
}


/*
*/
ErrorCode SnpManipulateSpreadsAndPages::DuplicateSpreadContents(const UIDRef sourceSpreadUIDRef, const UIDRef destSpreadUIDRef){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iDuplicateSpreadCmd(CmdUtils::CreateCommand(kDuplicateSpreadCmdBoss));
		if (iDuplicateSpreadCmd == nil){
			ASSERT(iDuplicateSpreadCmd);
			break;
		}
		InterfacePtr<IDuplicateSpreadCmdData> iDuplicateSpreadCmdData(iDuplicateSpreadCmd,IID_IDUPLICATESPREADCMDDATA);
		if (iDuplicateSpreadCmdData == nil){
			ASSERT(iDuplicateSpreadCmdData);
			break;
		}

		iDuplicateSpreadCmdData->Set(sourceSpreadUIDRef,destSpreadUIDRef);
		// process the command
		status = CmdUtils::ProcessCommand(iDuplicateSpreadCmd);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreateSpreads(ISnpRunnableContext* iSnpRunnableContext){
	ErrorCode status = kFailure;
	do {
		Utils<ISnipRunParameterUtils> iSnpRunParameterUtils;
		if (iSnpRunParameterUtils == nil){
			ASSERT(iSnpRunParameterUtils);
			break;
		}
		
		// we get the document being operated on
		IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
		if (iDocument == nil){
			ASSERT(iDocument);
			break;
		}
		const UIDRef docUIDRef = ::GetUIDRef(iDocument);

		// page size should honour the current preferences for the document.
		InterfacePtr<IPageSetupPrefs> iPageSetupPrefs(static_cast<IPageSetupPrefs *>(::QueryPreferences(IID_IPAGEPREFERENCES, iDocument)));
		if (iPageSetupPrefs == nil){
			ASSERT(iPageSetupPrefs);
			break;
		}
		PMPageSize dfltPMRectPageSize = iPageSetupPrefs->GetPageSizePref();	

		// Get number of pages per spread.
		int32 pagesPerSpread = iSnpRunParameterUtils->GetInt32(PMString("Number of pages per spread"), 1, 1, 10);
		if (iSnpRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		// Get number of spreads
		int32 numOfSpreads = iSnpRunParameterUtils->GetInt32(PMString("Number of spreads"), 1, 1, 10);
		if (iSnpRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		// make the call to the model code
		status = this->CreateSpreads(docUIDRef, dfltPMRectPageSize,pagesPerSpread,numOfSpreads);

	} while(false);
	return status;	
}

/*
*/
ErrorCode
SnpManipulateSpreadsAndPages::CreateSpreads(const UIDRef docUIDRef, const PMPageSize pageSize, const int32 numberOfPages, const int32 numberOfSpreads){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<ICommand> iNewSpreadCmd(CmdUtils::CreateCommand(kNewSpreadCmdBoss));
		if (iNewSpreadCmd == nil){
			ASSERT(iNewSpreadCmd);
			break;
		}
		InterfacePtr<INewSpreadCmdData> iNewSpreadCmdData(iNewSpreadCmd,UseDefaultIID());
		if (iNewSpreadCmdData == nil){
			ASSERT(iNewSpreadCmdData);
			break;
		}
		InterfacePtr<IApplyMasterCmdData> iApplyMasterData(iNewSpreadCmd, IID_IAPPLYMASTERCMDDATA);
		if (iApplyMasterData == nil){
			ASSERT(iApplyMasterData);
			break;
		}

		// we place the new spread at the end of the document
		iNewSpreadCmdData->SetNewSpreadCmdData(docUIDRef, numberOfSpreads, ISpreadList::kAtTheEnd, INewSpreadCmdData::kPagesMayShuffleThroughNewSpread, numberOfPages, pageSize);
		iApplyMasterData->SetApplyMasterCmdData(kInvalidUIDRef, IApplyMasterCmdData::kKeepCurrentPageSize);

		InterfacePtr<IIntData> iBindingLocation(iNewSpreadCmd,IID_IBINDINGLOCATION);
		if (iBindingLocation == nil){
			ASSERT(iBindingLocation);
			break;
		}

		// choosing anything but default binding can lead to undesirable results.
		iBindingLocation->Set(ISpread::kDefaultBinding);

		// process the command
		status = CmdUtils::ProcessCommand(iNewSpreadCmd);
	} while (kFalse);
	return status;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpManipulateSpreadsAndPages available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateSpreadsAndPages : public SnpRunnable
{
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerManipulateSpreadsAndPages();

		/** Destructor.
		 */
		virtual				~_SnpRunnerManipulateSpreadsAndPages();

		/** Return kTrue if the snippet can run.
			@param iSnpRunnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16				CanRun(ISnpRunnableContext* iSnpRunnableContext);

		/** Run the snippet.
			@param iSnpRunnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode			Run(ISnpRunnableContext* iSnpRunnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};
/* Constructor
*/
_SnpRunnerManipulateSpreadsAndPages::_SnpRunnerManipulateSpreadsAndPages() : SnpRunnable("ManipulateSpreadsAndPages")
{
	this->SetDescription("Manipulate spreads and pages.");
	this->SetPreconditions("Valid document");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
_SnpRunnerManipulateSpreadsAndPages::~_SnpRunnerManipulateSpreadsAndPages()
{
}

/*
*/
bool16 _SnpRunnerManipulateSpreadsAndPages::CanRun(ISnpRunnableContext* iSnpRunnableContext)
{
	bool16 result = kTrue;
	// we get the document being operated on
	IDocument* iDocument = iSnpRunnableContext->GetActiveContext()->GetContextDocument();
	if (iDocument == nil){
		result = kFalse;
	}
	return result;
}


/*
*/
ErrorCode _SnpRunnerManipulateSpreadsAndPages::Run(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateSpreadsAndPages instance;

		K2Vector<PMString> choices;
		choices.push_back(PMString("Create Spread(s)"));
		choices.push_back(PMString("Duplicate Spread Contents"));
		choices.push_back(PMString("Create New Spread From Spread"));
		choices.push_back(PMString("Delete a Spread From the Document"));
		choices.push_back(PMString("Move the first spread to the end"));
		choices.push_back(PMString("Create pages and add to a spread"));
		choices.push_back(PMString("Delete pages"));
		choices.push_back(PMString("Move first page"));
		choices.push_back(PMString("Clone pages in the document"));
		enum
		{
			kCreateSpreads, kDuplicateSpreadContents, kCreateSpreadFromSpread, kDeleteSpread, kMoveSpreads,
			kCreateAddPages, kDeletePages, kMovePage, kCreatePagesFromPages
		};

		Utils<ISnipRunParameterUtils> iParameterUtils;
		int32 choiceScope = iParameterUtils->GetChoice("Which option?", choices);
		if (iParameterUtils->WasDialogCancelled())
		{
			break;
		}

		switch (choiceScope)
		{
		case kCreateSpreads:
		{
			status = instance.CreateSpreads(iSnpRunnableContext);
			break;
		}
		case kDuplicateSpreadContents:
		{
			status = instance.DuplicateSpreadContents(iSnpRunnableContext);
			break;
		}
		case kCreateSpreadFromSpread:
		{
			status = instance.CreateSpreadFromSpread(iSnpRunnableContext);
			break;
		}		
		case kDeleteSpread:
		{
			status = instance.DeleteSpread(iSnpRunnableContext);
			break;
		}		
		case kMoveSpreads:
		{
			status = instance.MoveSpreads(iSnpRunnableContext);
			break;
		}
		case kCreateAddPages:
		{
			status = instance.CreatePages(iSnpRunnableContext);
			break;
		}	
		case kDeletePages:
		{
			status = instance.DeletePages(iSnpRunnableContext);
			break;
		}	
		case kMovePage:
		{
			status = instance.MovePage(iSnpRunnableContext);
			break;
		}	
		case kCreatePagesFromPages:
		{
			status = instance.CreatePagesFromPages(iSnpRunnableContext);
			break;
		}	
		default: 
			ASSERT("Choice not covered");			
			break;
		}
	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateSpreadsAndPages instance_SnpRunnerManipulateSpreadsAndPages;
DEFINE_SNIPPET(_SnpRunnerManipulateSpreadsAndPages) 	

//End, SnpManipulateSpreadsAndPages.cpp
