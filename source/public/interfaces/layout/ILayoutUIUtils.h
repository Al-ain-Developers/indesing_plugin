//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutUIUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ILayoutUIUtils__
#define __ILayoutUIUtils__


#include "LayoutID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "PMRect.h"
#include "ILayoutControlData.h"
#include "ISnapTo.h"				// SnapType
#include "UIDRef.h"
#include "PMMatrix.h"
#include "UIDList.h"
#include "HitTestDragConstants.h"
#include "IDocumentPresentation.h"
#include "IInterfaceColors.h"

class IControlView;
class IDocument;
class ISpread;
class IWindow;
class IViewPort;
class IHierarchy;
class IMargins;
class IColumns;
class IMasterSpreadList;
class IStringListControlData;
class IRulerData;
class IGraphicsContext;
class IDataExchangeHandler;
class IPanorama;
class ISpreadList;
class ICommand;
class ILayoutData;
class ISnapTo;
class IWorkspace;
class IFrameList;
class IUIDListData;
class IHyperlinkDestination;
class IShape;

/** UI Layout-related utilities */
class ILayoutUIUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTUIUTILS };

	/** Options for the method FillListWithHyperlinkDestinations includeOptions parameter. */
	enum IncludeOptions {
		/** Include only visible destinations */
		includeVisibleOnly = 0, 
		/** Include only hidden destinations */
		includeHiddenOnly,		
		/** Include all destinations */
		includeBoth,
		/** Include only visible URL destinations */
		includeVisibleURLsOnly,
		/** Include only visible Email destinations */
		includeVisibleEmailsOnly,
		/** Include only visible File destinations */
		includeVisibleFilesOnly,
	};

	/** Return the view associated with the frontmost layout presentation.
		@return IControlView pointer for frontmost layout presentation.  Reference count is incremented; caller is
		responsible for calling Release();
	*/
	virtual IControlView* QueryFrontView() = 0;//SEIssue <sheridan>

	/** Return the document associated with the frontmost layout presentation.
		@return IDocument pointer associated with the frontmost layout presentation.
	*/
	virtual IDocument* GetFrontDocument() = 0;//SEIssue <sheridan>
	
	/** Create and return a new layout presentation for specified the document.
		@return IDocumentPresentation pointer to the new layout presentation. 
			Caller not responsible for releasing this pointer
	*/
	virtual IDocumentPresentation* CreateNewLayoutPresentation(IDataBase* whichDoc, IDocumentPresentation::CreationParentingPrefs parentPref = IDocumentPresentation::kDefaultParentingPref, const IDocumentPresentation *relative = NULL) = 0;

	/** Create and return a command to create a new layout presentation for the specified document.
		@return ICommand pointer to the new command. 
			Caller responsible for releasing this pointer
	*/
	virtual ICommand* CreateNewLayoutPresentationCmd(IDataBase* whichDoc = 0) = 0;

	/** Test to see if the given presentation contains ILayoutControlData.
		@return true if inPresentation contains a layout data part. 
	*/
	virtual bool IsLayoutPresentation(IDocumentPresentation *inPresentation) = 0;

	/** Return the layout widget data associated with the supplied presentation.
		@param inWindow [IN] Window to retrieve layout widget data from. Note: it doesn't have to be a window -
		if it isn't, it'll just query for a layoutdata anyway; this way you can pass a viewMaster).

		@return The first occurrence of a layout data part (ILayoutControlData*) of a widget. If you
		have more than one layout widget in the presentation, it won't return the others.  The reference 
		count is incremented; the caller is responsible for calling Release().
	*/
	virtual ILayoutControlData* QueryLayoutData(IPMUnknown *inPresentation) = 0;//SEIssue <sheridan>

	/** Return the layout widget data associated with the front most presentation.

		@return The first occurrence of a layout data part (ILayoutControlData*) of the front presentation. If you
		have more than one layout widget in the presentation, it won't return the others. Reference count is 
		incremented; the caller is responsible for calling Release();
	*/
	virtual ILayoutControlData* QueryFrontLayoutData() = 0;//SEIssue <sheridan>

	/*
	virtual IViewPort* QueryViewPort(IPMUnknown *vmBoss) = 0;
		// Query for the viewmaster, then query for the
		// requested viewport type.
	*/
	
	/** Tells whether the application has no document windows visible to the user.
		@return kTrue if there are no document windows visible to the user.  Headless
		documents are not counted for these purposes.
	*/
	virtual bool16 IsApplicationInNoPubWindowState() = 0;

	/** Returns a count of the number of UI document windows opened by the user.
		@return the count of the number of UI document windows opened by the user.  Headless
		documents are not counted.
	*/
	virtual bool16 GetUIDocumentWindowCount() = 0;//SEIssue <sheridan>


	/** Return the margins of the spread associated with the frontmost layout window, or the
		indicated spread if the optional argument is used.
		@param whichpage [IN] Optional zero-based page index for the desired page of the spread 
		(zero is the left page in left-to-right binding documents, the right page in right-to-left documents).
		@param currentSpread [IN] Optional ISpread pointer for the desired spread.
		@return IMargins pointer for the margins.  The reference count is incremented; the caller is responsible
		for calling Release();
	*/
//	virtual IMargins* QueryFrontMargins(int32 whichPage = 0, ISpread* currentSpread = nil) = 0;//SEIssue <sheridan>

	/** Return the columns of the spread associated with the frontmost layout window, or the
		indicated spread if the optional argument is used.
		@param whichpage [IN] Optional zero-based page index for the desired page of the spread 
		(zero is the left page in left-to-right binding documents, the right page in right-to-left documents).
		@param currentSpread [IN] Optional ISpread pointer for the desired spread.
		@return IColumns pointer for the columns.  The reference count is incremented; the caller is responsible
		for calling Release();
	*/
//	virtual IColumns* Query_FrontColumns(int32 whichPage = 0, ISpread* currentSpread = nil) = 0;//SEIssue <sheridan>
		// Return the columns of the spread associated with the frontmost layout window, or the
		// indicated spread if the optional argument is used.

	/** Populates pageUIDList with UIDs for the selected pages (or spreads) in the Pages Panel. Will return the "current page" when Pages Panel is not visible. 
		@param UIDList [IN/OUT] UIDs of pages selected in the pages panel. Note that depending on bPagesOnly parameter, this list could also contain spread UIDs.
		UIDList must be set up with proper database.
		@param bIncludeMasters [IN] kTrue to include master pages.
		@param bCurrentPageOnly [IN] kTrue to only include "current" page if pages panel is not shown; kFalse to use all pages from the current spread.
		@param bPagesOnly [IN] kTrue to return only page uids in list (appends each page UID from selected spread(s)), kFalse to return a mixture of page UIDs and/or spread UIDs 
	*/
	virtual void GetSelectedPages(UIDList& pageUIDList, bool16 bIncludeMasters = kTrue, bool16 bCurrentPageOnly = kFalse, bool16 bPagesOnly = kTrue) = 0;

	/** Given a control view for a kPageNumComboBoxWidgetBoss or kPageNavigateComboBoxWidgetBoss, return the UID for it.
	*/
	virtual UID GetPageUIDFromWidget(IControlView* view, IDocument* iDocument) = 0;
	
	/** Given a control view for a kPageNumComboBoxWidgetBoss or kPageNavigateComboBoxWidgetBoss, set the initially selected page UID for it.
	*/
	virtual void SetPageUIDForWidget(IControlView* view, const UIDRef& pageRef) = 0;

	/** Return the 'active' workspace.  This belongs either to the frontmost view, or, if there isn't any,
		to the session (i.e., app-wide).
		@return IWorkspace pointer for the active workspace.  The reference count is incremented; the caller is
		responsible for calling Release();
	*/
	virtual IWorkspace* QueryActiveWorkspace() = 0;

	/** Find the page that is currently being viewed in the referred to IControlView.
		@param layoutView [IN] IControlView pointer for the view.
		@param spreadGeometry [IN] If provided, constrains the search to this spread.
		Otherwise, the routine will look for visible page whose center is nearest the view's center (what the page navigation widget shows).
		@return UID of the page being viewed.
	*/
	virtual	UID GetVisiblePageUID(IControlView* layoutView, IGeometry* spreadGeometry = nil) = 0;

	/** Find the spread that is currently being viewed in a layout view 
		@param layoutView [IN] IControlView pointer for the view.
		@param spreadList [IN] ISpreadList pointer for the document.
		@return UID of the spread being viewed.
	*/
	virtual	UID GetVisibleSpreadUID(IControlView* layoutView, ISpreadList* spreadList) = 0;

	/** Find the master spread that is currently being viewed in a layout view 
		@param layoutView [IN] IControlView pointer for the view.
		@param masterList [IN] IMasterSpreadList pointer for the document.
		@return UID of the master spread being viewed.
	*/
	virtual	UID GetVisibleMasterSpreadUID(IControlView* layoutView, IMasterSpreadList* masterList) = 0;

	/** Enable each window of each document. */
	virtual void EnableUpdateAllDocumentViews() = 0;
	/** Disable each window of each document. */
	virtual void DisableUpdateAllDocumentViews() = 0;
	/** Invalidate the views of a document. 
		@param iDoc [IN] IDocument pointer for the document.
	*/
	virtual void InvalidateViews (IDocument* iDoc) = 0;

	/** Sets the global path selection mode. For internal use only. Use IPathSelectionSuite->ActivatePathSelection instead.
	@param isPathSelected [IN] kTrue means that of the pointer tool and direct select tool, that the
	direct select tool was most recently selected.
	*/
	virtual void SetPathSelectionMode(bool16 isPathSelected) = 0;

	/** Tells which of pointer tool or direct select tool was most recently selected 
		@return kTrue if the direct select tool was most recently selected.
	*/
	virtual bool16 GetPathSelectionMode() = 0;

	/** Helper function to create a scroll to point command for indicated spread. If the view percentage is one of the 
		"fit" settings, it will scroll to the center of the spread. Otherwise it will scroll to the same offset from
		center as was in the view before the scroll.
		Useful after a SetSpreadCmd since it no longer scrolls to a spread.
		@param controlView [IN] IControlView pointer for the scrolling operation.
		@param spreadGeometry [IN] IGeometry pointer for the spread. If spread is nil, scroll to center of current spread.
		@param bMakeVisibleSpreadActive [IN] kTrue to make the visible spread active.
		@return an ICommand pointer for the command.  
		@see ILayoutControlData, GetFit
	*/
	virtual ICommand* MakeScrollToSpreadCmd(IControlView *controlView, IGeometry* spreadGeometry = nil, bool16 bMakeVisibleSpreadActive = kTrue) = 0;

	/** Helper function to cycle through the zoom percentages for a particular view.
		@param controlView [IN] IControlView pointer for the zoom operation.
		@param zoomIn [IN] kTrue increases the zoom percentage, kFalse decreases the zoom percentage.
		@param adjustForMonitorPPI [IN] Factor in an additional scale to adjust for the resolution of the monitor that is displaying this view?
			For example, if the monitor is 96ppi, then factor in an additional scale of 96/72 = 1.33
		@return the next zoom percentage.
	*/
	virtual PMReal GetNextZoomFactor(IControlView* controlView, bool32 zoomIn, bool32 adjustForMonitorPPI = kTrue) = 0;

	/** Helper function to get the next zoom percentage. Used by GetNextZoomFactor.
		@param currentZoom [IN] Current zoom value from which to fetch the 'next' zoom level.
		@param zoomIn [IN] kTrue increases the zoom percentage, kFalse decreases the zoom percentage.
		@return the next zoom percentage.
	*/
	virtual PMReal GetNextZoomValue(PMReal currentZoom, bool32 zoomIn) = 0;

	/** Make a command to zoom in.
		@param controlView [IN] IControlView pointer for zoom operation.
		@param bJustZoomToPoint [IN] kTrue to zoom to center of view; kFalse to zoom to selection (as long as it is visible).
		@return ICommand pointer for zooming.
	*/
	virtual ICommand* MakeZoomInCmd(IControlView *controlView, bool16 bJustZoomToPoint = kTrue) = 0;

	/** Make a command to zoom out.
		@param controlView [IN] IControlView pointer for zoom operation.
		@param bJustZoomToPoint [IN] kTrue to zoom to center of view; kFalse to zoom to selection (as long as it is visible).
		@return ICommand pointer for zooming.
	*/
	virtual ICommand* MakeZoomOutCmd(IControlView *controlView, bool16 bJustZoomToPoint = kTrue) = 0;

	/** Make one of several zoom commands.
		Makes kFitInViewCmdBoss if fit == ILayoutControlData::kFitSpread, 
		kFitPageInViewCmdBoss if fit == ILayoutControlData::kFitPage, 
		kFullViewCmdBoss if fit == ILayoutControlData::kFitPasteBoard, and 
		kZoomToCmdBoss if fit == ILayoutControlData::kFitNone.

		@param controlView [IN] IControlView pointer for zoom operation.
		@param zoomPct [IN] Zoom percentage (fit must be set to ILayoutControlData::kFitNone).
		@param fit [IN] Use a fit-to setting instead of a zoom percentage.  Using value other than
			ILayoutControlData::kFitNone ignores the bJustZoomToPoint and pt parameters.
		@param bJustZoomToPoint [IN] kTrue to use pt parameter; kFalse to zoom to selection. 
		@param pt [IN] Center of zoom, if bJustZoomToPoint is kTrue.  Using kZeroPoint chooses center of view.
		@param bMakeVisibleSpreadActive [IN] If fit is not ILayoutControlData::kFitNone, tells whether to
			make the visible spread active before zooming.
		@return ICommand pointer for zooming.
	*/
	virtual ICommand* MakeZoomCmd(IControlView *controlView, PMReal zoomPct, 
									  ILayoutControlData::FitSetting fit = ILayoutControlData::kFitNone,
									  bool16 bJustZoomToPoint = kTrue, PMPoint pt = kZeroPoint, 
									  bool16 bMakeVisibleSpreadActive = kTrue) = 0;

	/** Find the ISnapTo interface appropriate to do snapping over a particular spread, and set it up for a drag operation.
		@param controlView [IN] IControlView pointer for the view.
		@param spread [IN] The spread for the snapping operation.
		@param itemList [IN] UIDList of items to snap.
		@param originalSpread [IN] UIDRef or originating spread.
		@param originalPoint [IN] Starting point for the drag, in pasteboard coordinates.
		@return ISnapTo interface for the operation.  The reference count is incremented; the caller is 
		responsible for calling Release().
	*/
	virtual ISnapTo* QueryAndPrepareSnapToForSpread(IControlView* controlView, ISpread* spread, const UIDList* itemList, 
																						const UIDRef& originalSpread, PBPMPoint originalPoint) = 0;
	// traverse up the hierarchy looking for one of the specified interfaces

	/** Traverse up the widget hierarchy looking for the specified interface. Queries starting at given level.
		@param pUnknown [IN] An interface from an object with an IWidgetParent (such as a IControlView.
		@param rIID [IN] The interface IID that you are looking for.
		@return IPMUnknown pointer. You must cast to your desired type. The reference count is incremented; the caller is responsible for 
		calling Release().
	*/
	virtual IPMUnknown* QueryWidgetParentFor( IPMUnknown *pUnknown, const PMIID &rIID ) = 0;

	/** Adjust a point in x, y direction when shift key is down during tracking.
		@param toHere [IN/OUT] The intended destination point, potentially modified by constraint logic.
		@param originalPoint [IN] The starting point.
		@param shiftDown [IN] kTrue means shift key is down; kFalse causes return with no change in toHere point.
		@param zoomPct [IN] The current zoom percentage to use.
		@return The appropriate snapping types (None, X, Y, XandY, etc.) to indicate direction(s) to snap		
	*/
	virtual SnapType ConstrainPointForSnapping(PMPoint& toHere, const PMPoint& originalPoint, bool16 shiftDown, const PMReal& zoomPct) = 0;

	/** Test if the selected pageitems are visible.
		@param controlView [IN] IControlView for the layout view.
		@return kTrue if the selected page items are at least partially visible.
	*/
	virtual bool16 AreSelectedPageItemsVisible(IControlView* controlView) = 0;

	/** Test if the current spread is completely visible.
		@param controlView [IN] IControlView for the layout view.
		@return kTrue if the current spread is completely visible.
	*/
	virtual bool16 IsCurrentSpreadVisible(IControlView* controlView) = 0;

	/** Return the horizontal ruler data of the layout widget passed in.
		@param layoutView [IN] An interface pointer for the layout view.
		@return IRulerData pointer for the horizontal ruler data interface.  The reference count is
		incremented; the caller is responsible for calling Release();
	*/
	virtual IRulerData* QueryHorzRulerData (IPMUnknown* layoutView) = 0;

	/** Return the vertical ruler data of the layout widget passed in.
		@param layoutView [IN] An interface pointer for the layout view.
		@return IRulerData pointer for the vertical ruler data interface.  The reference count is
		incremented; the caller is responsible for calling Release();
	*/
	virtual IRulerData* QueryVertRulerData (IPMUnknown* layoutView) = 0;

	/** Adjust a point so it snaps to exact ruler coordinates. It will return a pasteboard
		point that maps to a "nice" value in the current x or y unit of measure.
		So, instead of returning 12.14567 points, this function will return 12.1 points.
		The function takes the passed in pasteboard point, maps to a unit point, then rounds
		the units such the screen coordinate (the pixel) is still the same, but is a "nicer" value.
		As user zooms out, granularity is coarser, likewise as user zooms in, granularity is finer.
		@param pbPtIn [IN] The original point in pasteboard coordinates.
		@param iHorzRuler [IN] The horizontal ruler data. May be nil if x coordinate doesn't need adjusting.
		@param iVertRuler [IN] The vertical ruler data. May be nil if y coordinate doesn't need adjusting.
		@param pbtoview [IN] The pasteboard-to-view matrix.
		@return Adjusted point.
		@see ComputeRulerAdjustedRect.
	*/
	virtual PMPoint ComputeRulerAdjustedPoint 
		(
			const PMPoint& pbPtIn, 
			IRulerData* iHorzRuler, 
			IRulerData* iVertRuler,
			const PMMatrix& pbtoview
		) = 0;

	/** Adjust the position of a rectangle so its edges coincide with ruler tick marks.
		@param pbRectIn [IN] The original rectangle in pasteboard coordinates.
		@param iHorzRuler [IN] The horizontal ruler data. May be nil if x coordinate doesn't need adjusting.
		@param iVertRuler [IN] The vertical ruler data. May be nil if y coordinate doesn't need adjusting.
		@param pbtoview [IN] The pasteboard-to-view matrix.
		@return The adjusted rectangle.
		@see ComputeRulerAdjustedPoint.
	*/
	virtual PMRect ComputeRulerAdjustedRect 
		(
			const PMRect& pbRectIn, 
			IRulerData* iHorzRuler, 
			IRulerData* iVertRuler, 
			const PMMatrix& pbtoview
		) = 0;

	/** Convert a global point to pasteboard coordinates.
		This function encapsulates all the hueristics we use to guarantee 
		a given pixel value maps to a pasteboard value and then back to the same 
		pixel value.  The input is the coordinate in Global space and the result
		is in Pasteboard space.  This function does NOT ruler adjust the point.
		Call ComputeRulerAdjustedPoint on the result if you want that behaviour.
		@param inGlobalPoint [IN] The global point to convert.
		@param layoutView [IN] The IControlView interface for the view.
		@return Converted point in pasteboard coordinates.
		@see ComputeRulerAdjustedPoint
	*/
	virtual PMPoint ComputePasteboardPoint
		(
			const GSysPoint& inGlobalPoint,
			IControlView* layoutView 
		) = 0; 

	/** Transform a global point to pasteboard coordinates, using AGM rasterport. 
		NOTE: This method has side-effects: it sets up the transform in the views rasterport. Beware.
		@param controlView [IN] The IControlView interface for the view.
		@param thePoint [IN] The global point to transform.
		@return Transformed point in pasteboard coordinates.
	*/
	virtual PBPMPoint GlobalToPasteboard(IControlView* controlView, const GSysPoint& thePoint) = 0;


	/** Get the bounds (in pasteboard coordinates) of the spreads being viewed. If the 
	    current spread is a master spread then the bounds of that single master spread is 
		returned. Otherwise the union of the bounds of all the spreads in the viewed 
		document is returned including those that are scrolled/scaled out of view by the 
		panorama. In either case, an additional IPasteboardPrefs::kPasteboardSeperatorAmount 
		(in parent units, though) is included at the top and bottom of the returned bounds.
		@param layoutView [IN] An IControlView pointer for the view.
		@return A rect in pasteboard coordinates for the bounds of the spreads. 
	*/
	virtual PMRect GetViewedSpreadsBounds(IControlView* layoutView) = 0;

	/** Get a list of the spreads currently visible in the layout view.
		@param layoutView [IN] An IControlView pointer for the view.
		@return A UIDList of the visible spreads.
	*/
	virtual UIDList GetVisibleSpreads(IControlView* layoutView) = 0;

	/** Get a list of the spreads currently visible in a bounded portion of the layout view.
		@param layoutView [IN] An IControlView pointer for the view.
		@param viewBounds [IN] Only look within this portion of the view.
		@return A UIDList of the visible spreads.
	*/
	virtual UIDList GetVisibleSpreads(IControlView* layoutView, const PMRect& viewBounds) = 0;


	/** Determine whether the specified spread is visible in the specified layout vew.
		@param layout [IN] The layout view in question.
		@param spread [IN] The spread in question.
		@return kSpreadIsNotVisible if the spread is completely out of view, kSpreadIsCompletelyVisble if completely in view, kSpreadIsPartiallyVisible otherwise.
	*/
	enum SpreadVisibility { kSpreadIsNotVisible, kSpreadIsPartiallyVisible, kSpreadIsCompletelyVisble};
	virtual SpreadVisibility IsSpreadVisible( ILayoutControlData* layout, ISpread* spread) = 0;



	/** Fill a UIDList with the multi column text frames that are currently visible in a layout view. 
		@param layoutControlView [IN] An IControlView pointer for the view.
		If layoutControlView is nil and frameList is non-nil, then all open views for the document containing frameList are considered.
		@param frameList [IN] If non-nil, then multi column text frames with text frame columns not in frameList are removed from visibleMCTextFrames.  
		@param visibleMCTextFrames [IN/OUT] The list to fill.  This list must be set up with the database first.
		@return If frameList in nil or no multi column text frames with text frame columns in frameList are visible, kInvalidUID is returned. Otherwise the UID of the visible multi column text frame with text frame columns in frameList with the largest index are returned.  
	*/
	virtual UID   GetVisibleMCFrames(IControlView* layoutControlView, IFrameList* frameList, UIDList& visibleMCTextFrames) = 0;


	/** Set the spread occupying the center of the view to be active.
		If the active spread is already visible, nothing will happen.
		@param controlView [IN] An IControlView pointer for the view.
	*/
	virtual void MakeVisibleSpreadActive(IControlView* controlView) = 0;

	/** Draws the "floor" of the document, the gray area outside of the spread pasteboards.
		Used by the LayoutControlView and CSprite.
		@param gc [IN] IGraphicsContext pointer for drawing.
		@param thedocument [IN] IDocument poineter for the document.
		@param viewBounds [IN] The bounds of the view.
		@param visibleSpreads [IN] A UIDList of the visible spreads.
	*/
	virtual void DrawFloor(IGraphicsContext* gc, IDocument* theDocument, const PMRect& viewBounds, const UIDList& visibleSpreads) = 0;

	/** Tell whether the current selection would allow transforms.
		@return kTrue if the current selection would support rotating, skewing, or scaling.
	*/
	virtual bool16 CanDisplayTransformDialog() = 0;

	/** Tell whether the current selection would allow coordinate translations.
		@return kTrue if the current selection would support moving pageitems.
	*/
	virtual bool16 CanDisplayMoveDialog() = 0;
	
	/** If the frontmost dialog window has the key focus, close the dialog.
	*/
	virtual void CloseDialogWindow() = 0;

	/** Utility to fill out a StringListControlData with a list of Hyperlink Destinations.
		@param stringList [OUT] Will be filled with destination names (will not be cleared in this method)
		@param db [IN] A database to get destinations from.
		@param uids [IN] Will be filled with the destination uids to match the strings added to StringListControlData.
		@param bossList [IN] A list of bosses for which to add destinations.
		@param includeOptions [IN] Include visible dests, invisible dests, or both.
		@param bSorted [IN] kTrue to sort the list alphabetically on return.
	*/
	virtual void FillListWithHyperlinkDestinations(IStringListControlData *stringList, IDataBase *db, UIDList *uids, 
													   K2Vector<ClassID> *bossList, IncludeOptions includeOptions = includeVisibleOnly, 
													   bool16 bSorted = kFalse) = 0;

	

	/** Utility to calculate the scale factor when zooming to rect within the controlView.
		Used for zooming to page items.
		@param rect [IN] Intended final zoom rectangle.
		@param controlView [IN] IControlView pointer for the view.
		@return Scale factor needed to zoom to rect.
	*/
	virtual PMReal GetNewScaleFactor(const PMRect& rect, IControlView *controlView) = 0;

	/** Returns kTrue if this layout view has the preview mode set for it.
		@param layoutView [IN] Interface pointer for the view.
		@return kTrue if the preview mode for the view is not IPreviewPrefs::kPreviewOff.
		@see IPreviewPrefs.h for preview modes.
	*/
	virtual  bool16 IsPreviewOn(IPMUnknown* layoutView) = 0;

	/** Add a new page to the document.
		Same behavior as kAddNewPageActionID.
	*/
	virtual void AddNewPage() = 0;

	/** Force redraw the control view passed in.
		@param controlView [IN] IControlView pointer for the view.

		OBSOLETE in CC: use IControlView::ForceRedraw instead
		virtual void ForceRedrawControlView(IControlView* iControlView, bool16 flushBackBuffer = kFalse) = 0;
	*/

	/** Adjust a point position based the ruler preference for ruler location, etc.
		@param pointPos [IN/OUT] The point to adjust.
		@param currentSpread [IN] An ISpread pointer to the current spread.
	*/
//	virtual void AdjustPointPosition(PMPoint& pointPos, ISpread* currentSpread) = 0;
	// replace calls with:  pointPos -= Utils<ITransformUpdateUtils>()->PasteboardZeroPoint( currentSpread, pointPos);


	/** Get mouse position from a global point based on pasteboard coordinate system.
		@param globalLocation [IN] The global coordinate to convert.
		@param iCurrentView An IControlView pointer for the current view.
		@return Pasteboard coordinates for the globalLocation.
	*/
	virtual PMPoint GetMousePasteboardPosition(const SysPoint& globalLocation, IControlView* iCurrentView) = 0;

	/** Hit-test a point or a rectangle against a list of spreads in a view.
		Intended for internal use only.  Routines ILayoutControlViewHelper::QueryHitTestPageItemOnVisibleSpreadsNew
		and ILayoutControlViewHelper::QueryHitTestPageItemNew are higher level and more suitable for general use.
		@param owner [IN] Interface pointer from the owning view.
		@param pWherePt [IN] Pointer to a point to hit-test, if bUsePt == kTrue.
		@param pWhereRect [IN] Pointer to a rect to hit-test, if bUsePt == kFalse.
		@param handlerClass [IN] ClassID of handler boss for particular hit-test behavior desired.
		@param pTheSpreads [IN] UIDList of spreads to hit-test.
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance.
		@param bVisibleSpreads UNUSED
		@param bUsePt [IN] kTrue to use pWherePt, kFalse to use pWhereRect.
		@param bUseXform [IN] kTrue to transform the hit-test location to the view's transform before hit-testing.
		@param bFinishChildren [IN] kTrue to continue searching for sibling hits once a hit is found, kFalse to stop after one hit.
		@return IUIDListData pointer containing found items.

		@see GenericID.h and GenericClass.fr for various hit-test handler boss definitions.
	*/
	virtual IUIDListData *QueryHitTestResultsByUIDList(IPMUnknown *owner, const PBPMPoint *pWherePt, const PMRect *pWhereRect, const ClassID handlerClass, UIDList *pTheSpreads, int16 tolerance = kHitTestTolerance, bool16 bVisibleSpreads = kFalse, bool16 bUsePt = kTrue, bool16 bUseXform = kTrue, bool16 bFinishChildren = kFalse ) = 0;

	/** Hit-test a point or a rectangle against the current spread or all visible spreads in a view.
		Intended for internal use only.  Routines ILayoutControlViewHelper::QueryHitTestPageItemOnVisibleSpreadsNew
		and ILayoutControlViewHelper::QueryHitTestPageItemNew are higher level and more suitable for general use.
		@param owner [IN] Interface pointer from the owning view.
		@param pWherePt [IN] Pointer to a point to hit-test, if bUsePt == kTrue.
		@param pWhereRect [IN] Pointer to a rect to hit-test, if bUsePt == kFalse.
		@param handlerClass [IN] ClassID of handler boss for particular hit-test behavior desired.
		@param interfaceID [IN] Interface ID to query on hit item before returning.
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance.
		@param bVisibleSpreads [IN] kTrue to only search the visible spreads, kFalse to search the current spread.
		@param bUsePt [IN] kTrue to use pWherePt, kFalse to use pWhereRect.
		@return Interface pointer of type interfaceID on the first hit item.

		@see GenericID.h and GenericClass.fr for various hit-test handler boss definitions.
	*/
	virtual IPMUnknown *QueryInterfaceUsingHitTest(IPMUnknown *owner, const PBPMPoint *pWherePt, const PMRect *pWhereRect, const ClassID handlerClass, const PMIID& interfaceID, int16 tolerance = kHitTestTolerance, bool16 bVisibleSpreads = kFalse, bool16 bUsePt = kTrue ) = 0;


	/**	Return the class of the hit test handler to use given the set of hittesting flags.
		@param selectionMode a set of hittest flags from IShape.h. e.g. kSelect, kOverrideMasterPageItemNoSelect, etc.
		@return ClassID of the hittesting boss corresponding to the flags. See hittest handler bosses in LayoutUIID.h
		@see IShape.h
		@see LayoutUIID.h
	 */
	virtual ClassID GetHitTestFlagsToHandlerBoss(const int32 selectionMode) = 0;

	/** Tests to see if active window in full screen mode
		@return true if we are full screen
		*/
	virtual bool16 IsPresentationMode(IDocumentPresentation * documentPresentation = nil) = 0;

	/** runs an action
		@param actionID the id of the action to run
		*/
	virtual void HandleAction(ActionID actionID) = 0;

	/** Walks all the visible spreads and checks to see if the mouse is over an adornment of
		a locked item. It returns the first one it finds.
		@param view IControlView of the layout
		@param mouse Coordinates of the mouse location in view coordinates
		@param onlySelectedItems if true, only locks on items that are selected are considered.
	*/
	virtual UIDRef GetHitLockedItemAdornment(IControlView * layoutView, PMPoint mouse, bool16 onlySelectedItems=kFalse) = 0;

	/** Walks all the visible spreads and checks to see if the mouse is over an adornment of
		a linked item. It returns the first one it finds.
		@param view IControlView of the layout
		@param mouse Coordinates of the mouse location in view coordinates
	*/
	virtual UIDRef GetHitLinkedItemAdornment(IControlView * layoutView, PMPoint mouse) = 0;

	/** Walks all the visible spreads and checks to see if the mouse is over an adornment of
		a form field's missing font adornment. It returns the first one it finds.
		@param view IControlView of the layout
		@param mouse Coordinates of the mouse location in view coordinates
	*/
	virtual UIDRef GetHitMissingFontFormItemAdornment(IControlView * layoutView, PMPoint mouse) = 0;
	
    /** Toggles the Presentation Mode
		@param documentPresentation the document view that should be switched.
		*/
	virtual void TogglePresentationMode(IDocumentPresentation &documentPresentation) = 0;

	/** set the color of the background for Presentation Mode
		@param stockColor IUIColorUtils color. For example: IUIColorUtils::kStockUIWhite
		@param documentPresentation the document view to change the background color on
		*/
	virtual void SetPresentationBackgroundColor(int32 stockColor, IDocumentPresentation& documentPresentation) = 0;

	/** handle the hide cursor timer. Do not call this directly, it's called by the hide cursor timer
		*/
	virtual void HandlePresentationHideCursor() = 0;

	/** starts the timer that hides the presentation mode cursor after a period of inactivity
		*/
	virtual void StartCursorHideTimer() = 0;

	/** stops the timer that hides the presentation mode cursor after a period of inactivity
		*/
	virtual void StopCursorHideTimer() = 0;


	/** Show swf preview panel if it is not originally shown and generate swf file to preview
	    @param previewMode [IN]: different preview mode (preview document, preview spread, preview selection)
		*/
	//virtual void DoSWFPreview(ISWFPreviewPreferences::SWFPreviewType const previewMode) = 0;

#ifdef DEBUG	
	virtual void CmdUIObjectCheck( const PMString &offender ) = 0;
	virtual void	SetQueryUIObjectOK( bool16 bOK ) = 0;
	virtual bool16	IsQueryUIObjectOK() const = 0;
#endif	

	/** Invalidate the views of all the documents opened. 
	*
	*/
	virtual void InvalidateAllDocumentViews() = 0;

	typedef enum 
		{
			kMixed,
			kURL,
			kFile,
			kEmail,
			kBookmark,
			kPage,
			kShared,
			kParagraph,
			kUnknownDestinationType
	} DestinationSelectionType;

	/**	Returns what type of hyperlink it is. Email and File destinations are distinguised unlike IHyperlinkDestination::GetType.
		@param dest  hyperlink destination
		@param isExternal  is hyperlink an external destination (will return kShared for external URLs)
		@return type of destination
	 */
	virtual DestinationSelectionType GetDestinationSelectionTypeWithDest(IHyperlinkDestination * dest, bool16 isExternal) = 0;

	/** Finds the current visible page in the document. 
		@returns the currently visible page UID or kInvalidUID if none is found 
	*/
	virtual const UID GetCurrentVisiblePage() = 0;
	
	/** Invalidate the Shape Graphix Cache of all spreads of a document. 
		@param iDoc [IN] IDocument pointer for the document.
	*/
	virtual void InvalidateShapeGraphixCache(IDocument* iDoc) = 0;

	/** Invalidate the Shape Graphix Cache for shape. 
		@param iShape [IN] IShape pointer for the shape.
	*/
	virtual void InvalidateShapeGraphixCache(IShape* iShape) = 0;

	/** Add a new page to the current document after the page whose UID has been sent in the parameter.
	@param pageUID [IN] UID of the page on the document after which the new page should be created
	*/
	virtual void AddNewPageAfterSpecifiedPage(const UID pageUID) = 0;
    
    /** Tests to see if layout view is being rendered using hardware acceleration  in full screen mode
     @param layoutView [IN] Interface pointer for the view.
     @return true if layout view is hardware accelerated
     */
    virtual bool16 IsAcceleratedDrawing(IPMUnknown* layoutView) const = 0;

	/** Provides the color to be used on the border of the Pasteboard
	@param view [IN] is the IControlView of the Layout.
	@return RealAGMColor to be used as the border color
	*/
	virtual RealAGMColor GetPasteboardBorderColor(IControlView* view) const = 0;

	/** Provides the color to be used on the border of the Document
	@param view [IN] is the IControlView of the Layout.
	@return RealAGMColor to be used as the border color
	*/
	virtual RealAGMColor GetDocumentBorderColor(IControlView* view) const = 0;

};

#endif	// __ILayoutUIUtils__
