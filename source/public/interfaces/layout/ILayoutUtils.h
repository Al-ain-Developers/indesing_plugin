//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutUtils.h $
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
#ifndef __ILayoutUtils__
#define __ILayoutUtils__



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
#include "TransformTypes.h"

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

/** Types of pages. */
enum PageType {
	/** Left-hand page */
	kLeftPage = 0,
	/** Single-sided page */
	kUnisexPage,
	/** Right-hand page */
	kRightPage };

/** Page binding types */
enum DocPageBinding {
	/** Default binding for locale */
	kDefaultBinding = -1,
	/** Left to right */
	kLeftToRightBinding,
	/** Right to left */
	kRightToLeftBinding };

/** Layout-related utilities on model side.
	@see kUtilsBoss
	@see ILayoutUIUtils for view-related methods

*/
class ILayoutUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTUTILS };

	/** Searches the document list for a particular document.
		@param docRef UIDRef identifying the document being sought
		@return kTrue if the document is in the document list
	*/
	virtual bool16 FindDocument(const UIDRef& docRef) = 0;//SEIssue <sheridan>

	/** Return the UID of the page on which a given page item falls.
		For page items that lie on multiple pages, this routine returns the
		page on which the majority of the page item area falls. If the page
		item does not fall on a page at all, the routine returns the UID of
		the spread.
		@param pageItemHier [IN] An IHierarchy pointer for the page item.
		@param enlargeForSlug [IN] kTrue to take into consideration the slug area around the page.
		@return UID of the page on which the page item falls, or the spread if the item does not
		fall on a page.
	*/
	virtual	UID GetOwnerPageUID(const IHierarchy* pageItemHier, bool16 enlargeForSlug = kFalse) = 0;

	/** Return the UID of the page on which a given page item is currently being drawn.
		This can be used to get the page UID of the layout page on which a
		master page item is being drawn--very useful for determining page number strings.
		For page items that lie on multiple pages, this routine returns the
		page on which the majority of the page item area falls. If the page
		item does not fall on a page at all, the routine returns the UID of
		the spread.
		@param pageItemHier [IN] An IHierarchy pointer for the page item.
		@return UID of the page on which the page item is drawn, or the spread if the item is not
		drawn on a page.
	*/
	virtual	UID GetDrawingPageUID(const IHierarchy* pageItemHier, bool16 enlargeForSlug = kFalse) = 0;

	/** Given a PMRect for a page and some info about the page, enlarge the rect to account
		for the slug area.

		Note: Special care must be paid to "middle" pages in a spread -- we don't allow the rect to
		enlarge in such a way that it would result in a rect that overlaps a neighboring page on
		the spread.  Thus, while all pages can grow vertically, only first and last pages of
		a spread can grow in both horizontal directions.  Special attention must also be paid to
		binding direction (meaning of 'first' and 'last' differs in RtoL cases).
		@param db [IN] IDataBase pointer for the document.
		@param pageRect [IN/OUT] Page's rectangle, potentially modified to account for slug area.
		@param spreadPageCount [IN] The number of pages in the spread.
		@param pageType [IN] What kind of page is represented by pageRect.
		@param bPrintingOrExporting [IN] Whether rect is being computed while printing or exporting. Obsolete, and unused.
		@param trueSpreadPageCount [IN] Used in situations where spreadPageCount "lies," like in cases where
		the master spread's pagecount is used instead of the layout spread.

		@see PageType for allowable page types.
	*/
	virtual void EnlargePagesRectBySlug(IDataBase *db, PMRect& pageRect, int32 pageIndex, int32 spreadPageCount, PageType pageType, bool16 bPrintingOrExporting = kFalse, int32 trueSpreadPageCount = 0) = 0;

	/** Given a PBPMRect and a UIDRef of a Spread, this helper function returns
		the UID of the page in the Spread on which the PBPMRect would fall.

		@param UIDRef [IN] UIDRef for the spread.
		@param itemBounds [IN] Rectangle in pasteboard or spread coordinates as specified by coordinateSpace.
		@param coordinateSpace [IN] The coordinate system in which itemBounds is specified.  The possible values are Transform::PasteboardCoordinates() and Transform::SpreadCoordinates().
		@return UID of page where itemBounds rect falls.
		For a rect that would fall on multiple pages, this routine returns the
		page on which the majority of the rect area falls. If the rect
		does not fall on a page at all, the routine returns the UID of
		the spread.
	*/
	virtual	UID GetIntersectingPageUID(const UIDRef& spreadRef, const PBPMRect& itemBounds, bool16 enlargeForSlug = kFalse, const Transform::CoordinateSpace &coordinateSpace = Transform::PasteboardCoordinates()) = 0;

	/** Give a ref for a page, return if it is a left, unisex (neither left nor right), or right page.
		Used for determining what type of page tab to draw in Pages Panel, and
		has margin implications. For pages that are left pages, their actual
		left margin will be an outside margin, and their right margin will
		be an inside margin.
		@param pageRef [IN] UIDRef for the page.
		@return PageType for the page.
	*/
	virtual	PageType GetPageType(const UIDRef& pageRef) = 0;


	/** Return the binding direction for the specified document
		@param docRef [IN] UIDRef of the document.
		@return DocPageBinding for the binding being used.  Note: One of
		kLeftToRightBinding or kRightToLeftBinding will be returned (default
		is kLeftToRightBinding; kDefaultBinding will not be returned).
	*/
	virtual	DocPageBinding GetDocumentPageBinding(const UIDRef& docRef) = 0;

	/** Traverse up the hierarchy looking for an item supporting the specified interface.
		@param pUnknown [IN] Interface pointer to the starting item.
		@param rIID [IN] Interface ID for the interface being sought.
		@return IPMUnknown pointer for item found, else nil.  If non-nil, the reference count is
		incremented; the caller is responsible for calling Release().
	*/
	virtual IPMUnknown *QueryParentFor(const IPMUnknown *pUnknown, const PMIID &rIID) = 0;

	/** Traverse up the hierarchy to the outermost frame looking for an item supporting the specified interface.
		@param pUnknown [IN] Interface pointer to the starting item.
		@param rIID [IN] Interface ID for the interface being sought.
		@return IPMUnknown pointer for item found, else nil.  If non-nil, the reference count is
		incremented; the caller is responsible for calling Release().
	*/
	virtual IPMUnknown *QueryOutermostParentFor(const IPMUnknown *pUnknown, const PMIID &rIID) = 0;

	/** Figure out how many pages a particular spread (or any spread, if theSpread == nil) can have.
		@param theSpread [IN] ISpread interface of spread to calculate.  If nil, calculate for all spreads.
		@param bFactorInIslandness [IN] Whether to take "island spread" capability into account.
		@param bFactorInFirstOddPage [IN] Whether to assume the first page is odd-numbered (and hence a right page).
		@param bFactorInPagesPerSpreadPref [IN] Whether to consider preference value for pages per spread.
		@return the calculated number of pages for the spread(s).
	*/
	virtual int32 GetMaxSpreadSize(const ISpread *theSpread = nil,
								bool16 bFactorInIslandness = kTrue,
								bool16 bFactorInFirstOddPage = kTrue,
								bool16 bFactorInPagesPerSpreadPref = kTrue) = 0;

	// For now, hard code the limits on spreads & pages. Eventually, these should
	// come from a resource. TODO : convert the tagged into real functions, initialized from
	// a resource
	//
	/** @name Page-related min/max values. */
	//@{
	/** Return the minimum number of pages in a document. */
	virtual int32	GetMinNumPages() = 0;
	/** Return the maximum number of pages in a document. */
	virtual int32	GetMaxNumPages() = 0;				/* CONVERT TO RESOURCE BASED */
	/** Return the minimum number of pages in a spread. */
	virtual int32	GetMinPagesPerSpread() = 0;
	/** Return the maximum number of pages in a spread. */
	virtual int32	GetMaxPagesPerSpread() = 0;			/* CONVERT TO RESOURCE BASED */
	/** Return the minimum page width in points. */
	virtual int32	GetMinPageWidth() = 0;				/* CONVERT TO RESOURCE BASED */
	/** Return the maximum page width in points. */
	virtual int32	GetMaxPageWidth() = 0;				/* 18 Feet. CONVERT TO RESOURCE BASED */
	/** Return the minimum page height in points. */
	virtual int32	GetMinPageLength() = 0;				/* CONVERT TO RESOURCE BASED */
	/** Return the maximum page height in points. */
	virtual int32	GetMaxPageLength() = 0;				/* 18 Feet. CONVERT TO RESOURCE BASED */
	//@}

	/** Helper function to create a shuffle pages command for all the pages in a document.
		Be careful to shuffle the correct spreads, or just default to the whole document.
		@param doc [IN] The document to use.  If nil, use the front document.
		@param firstSpread [IN] If specified, start with this spread.
		@param lastSpread [IN] If specified, end with this spread.
		@return an ICommand pointer for the command.
	*/

	/** Determine there is content on any page in a range of pages
		@param pageUIDList [IN] UIDList of pages to check.
		@return kTrue if any of the pages contain content.
	*/
	virtual  bool16 DoesPageHaveContent(const UIDList& pageUIDList) = 0;

	/** Return the margins of the given spread.
		@param whichpage [IN] Optional zero-based page index for the desired page of the spread
		(zero is the left page in left-to-right binding documents, the right page in right-to-left documents).
		@param currentSpread [IN] Optional ISpread pointer for the desired spread.
		@return IMargins pointer for the margins.  The reference count is incremented; the caller is responsible
		for calling Release();
	*/

	virtual IMargins* QueryMargins(int32 whichPage, const ISpread* currentSpread) = 0;

	/** Return the columns of the spread associated with the frontmost layout window, or the
		indicated spread if the optional argument is used.
		@param whichpage [IN] Optional zero-based page index for the desired page of the spread
		(zero is the left page in left-to-right binding documents, the right page in right-to-left documents).
		@param currentSpread [IN] Optional ISpread pointer for the desired spread.
		@return IColumns pointer for the columns.  The reference count is incremented; the caller is responsible
		for calling Release();
	*/
	virtual IColumns* Query_Columns(int32 whichPage, const ISpread* currentSpread) = 0;

	/** Helper function to create a shuffle pages command for all the pages in a document.
		Be careful to shuffle the correct spreads, or just default to the whole document.
		@param doc [IN] The document to use.  If nil, use the front document.
		@param firstSpread [IN] If specified, start with this spread.
		@param lastSpread [IN] If specified, end with this spread.
		@return an ICommand pointer for the command.
	*/
	virtual ICommand* MakeShuffleCmd(IDocument* doc,
									 const UIDRef& firstSpread =  UIDRef::gNull,
									 const UIDRef& lastSpread = UIDRef::gNull) = 0;

	/** Tell whether a page is a master page or a master spread.
		@param spreadOrPageUID [IN] UID of a page or a spread to check.
		@param db [IN] IDataBase pointer for the document.
		@return kTrue if the UID is a page in a master spread or is a master spread.
	*/
    virtual bool16	IsAMaster(UID spreadOrPageUID, IDataBase *db) = 0;

	/** If there are any views, invalidate them, otherwise do nothing. This calls
		into the UI plug-in Layout UI to actually do the invalidation if there
		is a UI present.
		@param document [IN] to invalidate views for.
	*/
    virtual void InvalidateViews(IDocument* document) = 0;

	/** UI independant Hit testing code.  If your hit testing can be done with the UI(not ID server), use the calls in ILayoutUIUtils to Hit test.
		Hit-test a point on the given spread
		@param mySpread [IN] the spread to hit-test
		@param where [IN] point to hit-test in pasteboard coordinates.
		@param handlerClass [IN] ClassID of handler boss for particular hit-test behavior desired.
		@param interfaceID [IN] the interfaceID of the hit page item you want returned
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance.
		@return item that was hit.  Interface returned is the one specified with interfaceID parameter
	*/
	virtual IPMUnknown* SpreadQueryHitTestPageItemNew(const ISpread* mySpread, const PBPMPoint& where, ClassID handlerClass, const PMIID& interfaceID, int16 tolerance = kHitTestTolerance) = 0;

#ifdef ID_DEPRECATED
	/**
	NOTE: WILL CHANGE

	A still private Messaging subsystem is new to CS4 which has the property of
	deferring some re-actions to changes until the command stack goes empty.
	TextWrap, TextInset, Inlines and MultiColumnTextFrame are among the most
	important users of this new subsytem.

	In some scenarios an observer or command sequence requires that something
	that the MultiColumnTextFrame will do, such as resizing itself or creating
	or adjusting text columns, must be done before the observer can proceed.

	This method will force all this deferred action to take place immediately
	and should only be called when it is known that changes to PageItems can
	take place without interfering with other internal processing.

	So, for example, if a command is busy fiddling with a PageItem and has not
	yet completed its task and an Observer calls this method then the command
	may become confused if the PageItem changes as a side effect.

	Please avoid calling this method unless absolutely necessary and if you do
	please drop us a line and tell us why. The application of the new messaging
	subsystem is evolving and we are still learning how to best apply it and
	we would appreciate more use cases.
	*/
	virtual void	M2MValidateAll(IDataBase* db) = 0;
#endif

};


#endif	// __ILayoutUtils__
