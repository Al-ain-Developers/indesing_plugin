//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutControlData.h $
//  
//  Owner: Frits Habermann
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
#ifndef __ILayoutControlData__
#define __ILayoutControlData__

#include "IPMUnknown.h"
#include "LayoutUIID.h"

class IGeometry;
class IDocumentLayer;
class IHierarchy;
class IDocumentLayer;
class IDocument;
class ISnapTo;
class UIDList;



/**
	Data interface for the Layout Widget. Provides access to the spread, document,
	and currently installed selection.
  Note: 
    those marked as SEIssue is obsolete, and 3rd party should not use.
 */
class ILayoutControlData : public IPMUnknown
{
	/** SEIssue this is temporary */
	friend class OpenLayoutWinCmd; 
	/** SEIssue this is temporary */
	friend class SetSpreadCmd; 
	/** SEIssue this is temporary */
	friend class NavLayoutWidgetObs; 
	/** SEIssue this is temporary */
	friend class CreatePrintLayoutViewCmd; 
	
public:
	enum { kDefaultIID = IID_ILAYOUTCONTROLDATA };

	/**
		kFitNone = 0,		Do no modifications to view pct;
		kFitSpread = 1,		Fit current spread in window;
		kFitPage = 2,		Fit current page in window;
		kFitPasteboard = 3	Fit all spreads in window;
	*/
	enum FitSetting
	{
		kFitNone = 0,		// Do no modifications to view pct
		kFitSpread = 1,		// Fit current spread in window
		kFitPage = 2,		// Fit current page in window
		kFitPasteboard = 3	// Fit all spreads in window
	};

	// ----- View stuff -----


	/**	  Set fit settting
		@param fit FitSetting enumerator defined above 
		@return  
	 */
	virtual void			SetFit(FitSetting fit) = 0;

	/**	  Get current fit setting
		@param none
		@return  current fit setting
	 */
	virtual FitSetting		GetFit() = 0;

	// ----- Spread stuff -----

	/**	  Internal use only.
		  Set current spread to newSpread. It will also set current document to this spread's document
		@param *newSpread  new spread 
		@param bDeselect  if true (kDeselect), deselect all layout selection. If kFalse (kDontDeselect), selection remains unchanged.
		@param bWithinSetPageCmd  if true, change has been made within a SetPageCmd 
		@return  
	 */
	virtual void			SetSpreadRef(const UIDRef& newSpread, bool16 bDeselect, bool16 bWithinSetPageCmd = kFalse) = 0;
public:

	// ----- Page stuff -----

	/**	  Get current page.Uses GetVisiblePageUID with current spread from GetSpreadRef.
		@param none
		@return  Return the "current" page on the current spread.   
	 */
	virtual UID				GetPage() const= 0;
								

	// ----- Layer stuff -----


	/**	   Set the UID of the active document layer.
		@param newActiveLayer the UID of a document layer want to set
		@return  
	 */
	virtual void			SetActiveDocLayerUID(UID newActiveLayer) = 0;
								

	/**	   Get the UID of the active document layer.
		@param none
		@return  the UID set by SetActiveDocLayerUID(UID newActiveLayer)
	 */
	virtual UID				GetActiveDocLayerUID() = 0;
								


	/**	  Get the UID of the active layer or spread layer specified by document layer of docLayerUID) . 		
		@param wantGuidesUID  
					  kFalse (By default) :return the spread layer UID for the regular spread
					  If kTrue, return the spread layer UID for the guides spread layer.
		@param docLayerUID  kInvalidUID (by default) return the active layer, 
						if docLayerUID is specified, return the spread layer corresponding to indicated document layer.
		@return  layer uid
	 */
	virtual UID			GetActiveLayerUID(bool16 wantGuidesUID = kFalse, UID docLayerUID = kInvalidUID) = 0;

	/**	  Query for  active document layer
		@param none
		@return  Active document layer
	 */
	virtual IDocumentLayer*	QueryActiveDocLayer() = 0;

	/**	  Query for the active layer hierarchy; Returns a spread layer or guide layer hierarchy.
		@param wantGuidesHierarchy  By default(kFalse)return the regular spread layer hierarchy.
								 If kTrue, return the corresponding spread guide layer hierarchy. 
		@return  
	 */
	virtual IHierarchy*		QueryActiveLayer(bool16 wantGuidesHierarchy = kFalse) = 0;

																
	// ----- Master page stuff -------

	/**	  Returns a list of all the spreads (including hierarchal masters) that appear as part of thisSpread.
					 NOTE (repeat), the result is not all spreads of the document, there are master spreads except itself
		@param spreadUID  The spread we want to collect applied masters 
		@param *spreadList  Resulting UID list of (master)spreads 
		@return  
	 */
	virtual void			GetAllSpreads(UID spreadUID, UIDList *spreadList) = 0;

	// ----- Document stuff -----

private: 
	/**	  This method is obselete, 3rd party should not use.
					 Set current document. But note SetSpreadRef() also sets document, it will
					asserts if it is called.
					
		@param *doc 
		@return  
	 */
	virtual void			SetDocument(IDocument *doc) = 0;
public:

	/**	  Get the document that this widget is currently viewing. SetDocument() is nolonger available for 3rd party

		@param none
		@return  current document
	 */
	virtual IDocument*		GetDocument() = 0;
								// Set and get the document that this widget is currently
								// viewing. SetDocument is called with nil when the layout window is closing.
								// Allows observers hooked up via layout actions to detach.


	// ----- Snap to stuff (used by cursor providers only, not trackers) -----

	/**	  Set cursor snap to value, used by cursor provider;
          ISnapTo could be obtained by IItemContext->QuerySnapTo();
		@param snapTo 
		@return  
	 */
	virtual void			SetCursorSnapTo(ISnapTo* snapTo) = 0;

	/**	  Get cursor snap to 
		@param none
		@return  
	 */
	virtual ISnapTo*		GetCursorSnapTo() = 0;
	

	/**	  The layout window is about to go away, release the items that are stored in the docuemnt database and detach observers;
		Called when the window is being closed.		
		@param void 
	 */
	virtual void			Shutdown (void) = 0;

	/**
	 These are only to be called by OpenLayoutWinCmd.  They are for initializing various
	 things for new layout windows. These used to be called by SetSpreadRef but that doesn't
	 really seem to make sense and actually caused problems in at least one case because
	 of ordering problems.
 
	*/

	/**	Attach document observers; These observers are for initializing various
	 things for new layout windows and watch for any changes that may affect the display of
	 layout widget. Include IID_ILAYOUTHIERARCHYOBSERVER, IID_ILAYOUTPAGEITEMOBSERVER and
	 IID_IREFERENCEPOINTSPREADOBSERVER, as well as kLayoutActionService providers.
		@param doc 
		@return  
	 */
	virtual void		AttachDocObservers(const IDocument* doc) = 0;

	/**	  Detach workspace observers.
		@param *doc 
		@return  
	 */
	virtual void		DetachWorkspaceObservers(const IDocument* doc) = 0;

	/**	Detach document observers.
		@param doc 
		@return  
	 */
	virtual void		DetachDocObservers(const IDocument* doc) = 0;

	/**	  Attach workspace observers, attach IID_ILAYOUTTEXTOPTIONSOBSERVER and IID_ILAYOUTINVALOBSERVER
		 to workspace to catch these changes to invalidate layout.
		@param *doc 
		@return  
	 */
	virtual void		AttachWorkspaceObservers(const IDocument* doc) = 0;

	/**	    Set default document layer. If a document layer is not set yet, set the first layer as default
		@param none
		@return  
	 */
	virtual void		SetDefaultDocLayer() = 0;


	/**	  Get current spread UIDRef, the spread this view is currently viewing
		@param none
		@return  current spread UIDRef. 
	 */
	virtual const UIDRef&		GetSpreadRef() const = 0;

	/**	  FOR Internal use only 
	 */
	virtual void		AttachSpreadObservers(const UIDRef& spreadRef) = 0;
	virtual	void		DetachSpreadObservers() = 0;
};

#endif
