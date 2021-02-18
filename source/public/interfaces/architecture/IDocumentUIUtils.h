//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocumentUIUtils.h $
//  
//  Owner: hhorton
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

#pragma once
#ifndef _H_IDocumentUIUtils
#define _H_IDocumentUIUtils

#include "IPMUnknown.h"
#include "IDocument.h"
#include "IDataBase.h"
#include "IErrorState.h"
#include "AppUIID.h"
#include <boost/function.hpp>
#include "IDocumentPresentation.h"
#include "Utils.h"
#include "CAlert.h"

class PaletteRef;

/** typedefs for the acceptance and ordering predicates used with FindPresentationForDocument/FindPresentationsForDocument

		A set of commonly used criteria are available (is_active, is_layout, is_floating, etc...)
		@see DocumentPresFindCriteria.h
*/
typedef unary_presentation_predicate FindPresentation_CriteriaFunc;
typedef unary_presentation_predicate* FindPresentation_Criteria;
typedef std::vector<FindPresentation_Criteria> FindPresentation_PreferCriteria;

/** typedefs for the acceptance and comparison predicates used with FindRelatedPresentations 
		A set of commonly used criteria are available.  (is_active, is_layout, is_same_kind, is_same_document, etc...)
		@see DocumentPresFindCriteria.h
*/
typedef binary_presentation_predicate FindRelatedPresentation_CriteriaFunc;
typedef binary_presentation_predicate* FindRelatedPresentation_Criteria;
typedef std::vector<FindRelatedPresentation_Criteria> FindRelatedPresentation_PreferCriteria;

typedef K2Vector<IDocumentPresentation*> PresentationSequence;

/**	Interface containing various utility methods for document presentations.
 */
class IDocumentUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDOCUMENTUIUTILS };

	/**	Get the active Document Presentation.
			Note: there is only one active document presentation in InDesign - based on GetExecutionContextSession()->GetActiveContext().
			 But there are times when the active context's view is pointing at a panel, so ONLY in that case do we rely on the OS activation.
		@return active presentation or nil if none are open
	*/
	virtual IDocumentPresentation* GetActiveDocumentPresentation() = 0; // FIXME_OWL2: remove or convert to inline call to GetDocumentPresentationFromActiveContext when we understand more subtle cases
	
	/**	Get the OS activated Document Presentation.
			Note: this is based on OS activation and event targeting. So why do we have both methods? 
				In "steady state" both methods will return the same value, but at certain times during an activation transition they may temporarily disagree. 
				We believe there are only a few rare instances where low level code may need to distinguish between the two.
				Clients should not call this method without thinking hard about why they cannot use GetDocumentPresentationFromActiveContext instead
				(One situation where it will matter is keyboard focus handling)
		@return active presentation or nil if none are open
	*/
	virtual IDocumentPresentation* GetOSActivatedDocumentPresentation() = 0; 

	/** Find a particular presentation for the specified document.
		@param db restricts the presentations to a partucular open document. Cannot be NIL.
		@param acceptCriteria a comparison or unary criteria applied to all candidates, candidate will be considered if the criteria evaluates to true.
		@param preferCriteria set of comparison or unary criteria applied to all candidates. successful candidates will be ordered if all criteria evaluates to true.
	*/
	virtual IDocumentPresentation* FindPresentationForDocument(IDataBase* db, const FindPresentation_Criteria&  acceptCriteria, const FindPresentation_PreferCriteria& preferCriteria) = 0;
	
	/** Find a set of presentation for a specified document, or all documents, that match an acceptance criteria, and which are ordered by a set of preference criteria.
		@param db restricts the presentations to a partucular open document. Can be NIL to consider presentations on all open documents.
		@param acceptCriteria a comparison or unary criteria applied to all candidates, candidate will be considered if the criteria evaluates to true.
		@param preferCriteria set of comparison or unary criteria applied to all candidates. successful candidates will be ordered if all criteria evaluates to true.
	*/
	virtual uint32 FindPresentationsForDocument(IDataBase* db, PresentationSequence&, const FindPresentation_Criteria& acceptCriteria, const FindPresentation_PreferCriteria& preferCriteria) = 0;
	
	/** Find the "frontmost" presentation for the specified document.
			If the Active presentation is viewing the specified document, then it will be returned, otherwise if any of the documents presentations are visible (i.e. frontmost in their tabgroup) 
			one of them will be returned (no attempt is made to return the frontmost one if several visible but non-active presentations are available)
	*/
	virtual IDocumentPresentation* GetFrontmostPresentationForDocument(IDataBase* db) = 0;

	/**	Given a particular presentation, find the set of document presentations that satisfy a set of requirements and are ordered by a set of preferences.
			By default, if the supplied presentation passes the requirements, it will appear in the list.
		@param db restricts the presentations to a partucular open document. Can be NIL. Could also be expressed as a requirement (is_samedocument or isnot_samedocument)
		@param me the presentation all other candidates are compared to.
		@param myRelatives provided to hold the resulting ordered set of successful candidates on return.
		@param acceptCriteria a comparison or unary criteria applied to all candidates, candidate will be included if the criteria evaluates to true.
		@param preferCriteria set of comparison or unary criteria applied to all candidates. successful candidates will be ordered if all criteria evaluates to true.
		@return includeMe include provided presentation as a potential candidate (default is to include it)
		@return count of presentations satisfying the requirement
	*/
	virtual uint32 FindRelatedPresentations(IDataBase* db, IDocumentPresentation* me, PresentationSequence& myRelatives, 
																					const FindRelatedPresentation_Criteria& acceptCriteria, const FindRelatedPresentation_PreferCriteria& preferCriteria,
																					bool16 includeMe = kTrue) = 0;
 
	/**	Cascade currently open document windows
		@param currentDocOnly If true, only do windows of current document, else do all document windows.
	*/
	virtual void CascadeFloatingDocumentWindows( bool16 currentDocOnly ) = 0;

	/**	Tile currently open document windows
	*/
	virtual void TileDocumentWindows() = 0;

	/** 	Sends the current frontmost document window to the back, thus revealing a new frontmost document window
	*/
	//virtual void	NextWindow() = 0;
	// Cycle through document tabs in the active pane
	virtual void	CycleNextPresentationToFront() = 0;
	// Cycle through top level document bearing windows (CS3 behavior)
	virtual void	CycleNextPresentationWindowToFront() = 0;

	/** 	Reorders document windows by bringing the currently backmost document window to the front.
	*/
	//virtual void	PreviousWindow() = 0;
	// Cycle through document tabs in the active pane
	virtual void	CycleLastPresentationToFront() = 0;
	// Cycle through top level document bearing windows (CS3 behavior)
	virtual void	CycleLastPresentationWindowToFront() = 0;

	/** Reposition/resize open document windows so they are accessible to the user.
			Optionally you can pass in the type of change that triggered this request.
			
			@see AdjustDocumentWindowBounds
	*/
	//virtual void AdjustDocumentWindowsBounds(ClassID theTriggeringChange = kInvalidClass) = 0;
	virtual void AdjustDocumentPresentationsBounds(ClassID theTriggeringChange = kInvalidClass) = 0;

	/** Reposition/resize a document window so it is accessible to the user
			Optionally you can pass in the type of change that triggered this request, which indicates the extent to which the document window will be modified.
			Supported changes are (in decreasing order of severity): kDisplayChangeMsg, kAppFrameRestoreMsg, kAppFrameResizeMsg, 
				kPaletteWorkspaceLoadedMsg, kDockedPaletteAreaChangedMsg, kDockedPaletteAreaChangedByUserMsg, kApplicationResumeMsg			
	*/
	//virtual void AdjustDocumentWindowBounds(IWindow* docWindow, ClassID theTriggeringChange = kInvalidClass) = 0;
	virtual void AdjustDocumentPresentationBounds(IDocumentPresentation* presentation, ClassID theTriggeringChange = kInvalidClass) = 0;

	// Refactored methods (from IDocumentUIUtils)
	
	/**	Close active document presentation. If the document is only open in 
	                this one presentation, also close the document.
		@param allowCancel Allow user to cancel close. 
		@return If front window closed without error. 
	 */
	virtual bool16 		CloseActivePresentation(bool16 allowCancel = kTrue) = 0;

	/**	Close active document
		@param allowCancel Allow user to cancel close.
        @param uiFlags A flag indicating whether or not ui is permitted
		@return If front document closed without error. 
	 */
	virtual bool16 		CloseActiveDocument(bool16 allowCancel = kTrue, UIFlags uiFlags = kFullUI) = 0;

	/**	Close specified document presentation
		@param allowCancel Allow user to cancel close.  
		@return If document closed without error. 
	 */
	//virtual bool16 		CloseDocWindow(IWindow* window, bool16 allowCancel = kTrue) = 0;
	virtual bool16 		CloseDocumentPresentation(IDocumentPresentation* presentation, bool16 allowCancel = kTrue) = 0;

	/**	Discard all changes and reopen the originally saved docunent
		@param allowCancel  Allow user to cancel revert. 
		@return if rever without error 
	 */
	virtual bool16 		RevertActiveDocument(bool16 allowCancel = kTrue) = 0;

	/**	Update titles used for all presentations of a document
		@param doc The document to update titles for. 
	 */
	virtual void 		UpdatePresentationLabels(IDocument *doc) = 0;

	/**	UpdateDocumentIsModifiedIndicators
		@param doc The document to update the is modified indicators for, or NULL for all documents. 
	 */
	virtual void 		UpdateDocumentIsModifiedIndicators(IDocument *doc = NULL) = 0;

	/**	INTERNAL USE ONLY - suspends consistency check between our view of the active document presentation and what OWL thinks is active
		@param suspend - true to suspend check.
	 */
	virtual void SuspendActivePresentationConsistencyCheck(bool16 suspend = kTrue) = 0;

	/**
		Dispatch a presentation-related service signal to all registered responders.
		@param document - is the document containing the presentation
		@param presentation - is the presentation
		@param serviceID - is the signal
		@return is kSuccess or an error
	*/
	virtual ErrorCode DispatchPresentationSignalToAllResponders( IDocument* document, IDocumentPresentation* presentation, ServiceID serviceID ) const = 0 ;

	/**	INTERNAL USE ONLY - Obtain the next presentation containing the layout, 
	  this should ignore the other presentations such as StoryPresentation etc.
	*/
	virtual IDocumentPresentation* GetLayoutPresentationNextToActive() = 0;

	/**	INTERNAL USE ONLY - Obtain the next presentation containing the layout for this sroty presentation
	*/
	virtual IDocumentPresentation* GetLayoutPresentationForStoryEditorPresentation(IDocumentPresentation* inStoryPresentation) = 0;

	/**
	 * Show Hide Document windows
	 */
	virtual void ShowHideDocumentWindows(bool16 show) = 0;

};

#endif	/* _H_IDocumentUIUtils */
