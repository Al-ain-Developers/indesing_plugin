//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectLayoutGrid.cpp $
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
#include "ICJKGridData.h"
#include "ICJKGridManager.h"
#include "ICJKGridUtils.h"
#include "ICJKLayoutGridData.h"
#include "ICompositionStyle.h"
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDrawingStyle.h"
#include "IFontFamily.h"
#include "IHierarchy.h"
//#include "ILayoutControlData.h"
#include "ILayoutUIUtils.h"
#include "IPageList.h"
#include "IPMFont.h"

// General includes:
#include "CJKGridID.h"
#include "K2Vector.h"
#include "K2TypeTraits.h"
#include "Utils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

typedef K2Vector<PMRect> SnpPMRectList;
DECLARE_OBJECT_TYPE(PMRect);

// TODO align with coding conventions
/** Storage class for layout grid information
*/
struct SnpLayoutGridInfo
{
	/** constructor - just to set defaults
	*/
	SnpLayoutGridInfo(void):
		fPageString(PMString("", PMString::kUnknownEncoding)), 
		fHasLayoutGrid(kFalse),
		fMasterPageString(PMString("", PMString::kUnknownEncoding)),

		// from ICJKLayoutGridData
		fIsUsingMaster(kFalse), fStartingPoint(ICJKLayoutGridData::kTopOutside), 

		// from ICJKGridManager
		fIsGridVertical(kFalse), fGridBounds(PMRect(-1.0, -1.0, -1.0, -1.0)),
		fCharsPerLine(Int32List()), fNumOfLines(-1),
		fRectCount(-1), 
		fEmBoxRects(SnpPMRectList()), fICFBoxRects(SnpPMRectList()),
		fHCellSize(-1.0), fVCellSize(-1.0), 
		fICFAdjustmentsX(-1.0), fICFAdjustmentsY(-1.0),

		// from ICJKGridData
		fFontUID(kInvalidUID),
		fFontStyleName(PMString("", PMString::kUnknownEncoding)), 
		fFontFullNativeName(PMString("", PMString::kUnknownEncoding)), 
		fTextSize(-1.0), fCharAki(-1.0), fLineAki(-1.0), 
		fCharOkuri(-1.0), fLineOkuri(-1.0),
		fHScale(-1.0), fVScale(-1.0), 
		fTextAlignment(ICompositionStyle::kTextAlignLeft),
		fGridAlignment(Text::kGANone), 
		fCharacterHang(IDrawingStyle::kHangBaseline) 
	{
	}

	/** destructor - does nothing.
	*/
	~SnpLayoutGridInfo(void)
	{
	}

	// member variables

	/** String for the page under inspection. */
	PMString fPageString;
	/** Flag indicating if this page has a layout grid */
	bool16 fHasLayoutGrid;

	/* ICJKLayoutGridData settings */

	/** Starting point of grid.
	 * 	@see ICJKLayoutGridData
	 */
	ICJKLayoutGridData::GridStartingPoint fStartingPoint;

	/** Flag indicating if the master page is to be used.
	 * 	@see ICJKLayoutGridData
	 */
	bool16 fIsUsingMaster;

	/** Stores master page as a string. */
	PMString fMasterPageString;

	/* ICJKGridManager settings */

	/** Flag indicating if the grid is vertical
	 * 	@see ICJKGridManager 
	 */
	bool16 fIsGridVertical;

	/** Grid bounds  (in points)
	 * 	@see ICJKGridManager 
	 */
	PMRect fGridBounds;

	/** List of characters per line in the grid.
	 * 	@see ICJKGridManager 
	 */
	Int32List fCharsPerLine;

	/** Number of text lines in the grid
	 * 	@see ICJKGridManager 
	 */
	int32 fNumOfLines;

	/** Number of cells (one per character) in the grid.
	 * 	@see ICJKGridManager 
	*/
	int32 fRectCount;

	/** Embox of each cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	SnpPMRectList fEmBoxRects;

	/** ICF box of each cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	SnpPMRectList fICFBoxRects;

	/** Horizontal size of a cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	PMReal fHCellSize;

	/** Vertical size of a cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	PMReal fVCellSize;

	/** Horizontal ICF adjustments for each cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	PMReal fICFAdjustmentsX;
	/** Vertical ICF adjustments for each cell in the grid. (in points)
	 * 	@see ICJKGridManager 
	*/
	PMReal fICFAdjustmentsY;

	/* ICJKGridData settings */

	/** Default font used in the grid.
	 *	@see ICJKGridData
	 */
	UID fFontUID;
	/** Style name of the default font used in the grid
	 *	@see ICJKGridData
	 */
	PMString fFontStyleName;
	/** Native name of the default font used in the grid
	 *	@see ICJKGridData
	 */
	PMString fFontFullNativeName;
	/** Default text size used in the grid (in points)
	 *	@see ICJKGridData
	 */
	PMReal fTextSize;
	/** Space between characters in the grid (in points)
	 *	@see ICJKGridData
	 */
	PMReal fCharAki;
	/** Space between lines in the grid (in points)
	 *	@see ICJKGridData
	 */
	PMReal fLineAki;
	/** Space between the top of two consecutive characters in the grid (in points)
	 * 	Sum of char aki + text size * scale. 
	 * 	The scale depends on grid direction. If vertical, use vertical scale.
	 *	@see ICJKGridData
	*/
	PMReal fCharOkuri;
	/** Space between the "top" of two consecutive lines in the grid (in points)
	 * 	Sum of line aki + text size * scale. 
	 * 	The scale depends on grid direction. If vertical, use horizontal scale.
	 *	@see ICJKGridData
	*/
	PMReal fLineOkuri;
	/** Horizontal scale of characters in the grid. (0.0 - 1.0)
	 * 	@see ICJKGridData
	 */
	PMReal fHScale;
	/** Vertical scale of characters in the grid. (0.0 - 1.0)
	 * 	@see ICJKGridData
	 */
	PMReal fVScale; 
	/** Text alignment of the body text in the grid. 
	 * 	@see ICJKGridData
	*/
	ICompositionStyle::TextAlignment fTextAlignment;
	/** Grid alignment.
	 * 	@see ICJKGridData
	 */
	Text::GridAlignmentMetric fGridAlignment;
	/** Character hang option for the grid.
	 *	@see ICJKGridData
	 */
	IDrawingStyle::CharacterHang fCharacterHang;
};

/** \li Inspect layout grid information for selected pages.

	@see ICJKGridData
	@see ICJKGridManager
	@see ICJKGridUtils
	@see ICJKLayoutGridData
	@see SnpModifyLayoutGrid

	@ingroup sdk_snippet
	@ingroup sdk_layout
	@ingroup sdk_cjk

*/
class SnpInspectLayoutGrid 
{
public:
	/**
	*/
	SnpInspectLayoutGrid() {}

	/** Destructor.
	 */
	virtual         ~SnpInspectLayoutGrid() {}

	/**	Shows how to inspect pages in a document
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode InspectPages(const UIDList& pages);

	/** Shows how to inspect all information related to a layout grid on a given page.
		@param thePage UIDRef of the page to inspect.
		@param info (return) Information structure with layout grid info.
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode InspectLayoutGrid(const UIDRef& thePage, SnpLayoutGridInfo& info);

	/** Report layout grid info to SNIPLOG.
		@param info Information structure returned from InspectLayoutGrid().
		@param pageIndex Index from the list of pages. In the snip log, the index of the page
			in the page list passed into InspectPages will be displayed.
			-1 means don't care, and a different title gets displayed in the SNIPLOG.
	*/
	void ReportLayoutGridInfo(const SnpLayoutGridInfo& info, const int32 pageIndex = -1);

	/** Gets the first visible and selected page.
	 * 	@param activeContext IN The current active context.
	 *	@return UIDRef of the first selected page
	 */
	UIDRef GetFirstSelectedPage(IActiveContext* activeContext);



};

/* InspectPages
*/
ErrorCode SnpInspectLayoutGrid::InspectPages(const UIDList& pages)
{
	// assume success 
	ErrorCode status = kSuccess;
	do
	{
		int32 i = 0;
		int32 numPages = pages.Length();
		while ((i < numPages) && 
			   (status == kSuccess))
		{
			SnpLayoutGridInfo info;

			// inspect each page for layout grid info.
			status = this->InspectLayoutGrid(pages.GetRef(i), info);

			if (status != kFailure)
			{
				// dump to sniplog.
				this->ReportLayoutGridInfo(info, i);
			}
			else
			{
				SNIPLOG("Page index[%d]:\nERROR while inspecting layout grid!", i);
			}
			++i;
		}
	} while (false);

	return status;
} 

/* InspectLayoutGrid
*/
ErrorCode SnpInspectLayoutGrid::InspectLayoutGrid(const UIDRef& thePage, SnpLayoutGridInfo& info)
{
	ErrorCode status = kFailure;
	do 
	{
		// be sure the page is not invalid
		if (thePage.ExistsInDB() == kFalse)
		{
			ASSERT_FAIL("the UIDRef for the page is invalid!");
			break;
		}
		// get the hierarchy for the page (needed in ICJKGridUtils::QueryLayoutGrid())
		InterfacePtr<IHierarchy> pageHier(thePage, UseDefaultIID());
		if (pageHier == nil)
		{
			ASSERT_FAIL("This persistent object doesn't have a hierarchy - is it really a page?");
			break;
		}

		// (1) get information about the page passed in, via the document page list.
		IDataBase* db = thePage.GetDataBase();
		if (db == nil)
		{
			ASSERT(db);
			break;
		}

		InterfacePtr<IDocument> doc ((IDocument*)db->QueryInstance(db->GetRootUID(), IDocument::kDefaultIID));
		if (doc == nil)
		{
			ASSERT_FAIL("Could not get document from the page hierarchy!");
			break;
		}
		InterfacePtr<IPageList> pageList(doc, UseDefaultIID());
		if (pageList == nil)
		{
			ASSERT_FAIL("Could not get page list from document!");
			break;
		}
		pageList->GetPageString(thePage.GetUID(), &(info.fPageString));


		// (2) check to see if the layout grid is from the master page (which could have another master page...)
		InterfacePtr<ICJKLayoutGridData> layoutGridDataForPage(thePage, UseDefaultIID());
		if (layoutGridDataForPage == nil)
		{
			// if we get here, there is no layout grid data to report... 
			// so we break out of the while-loop.
			// the kCancel tells the caller that we don't have any layout grid data.
			// (The default for info.fHasLayoutGrid is kFalse.)
			status = kCancel;
			break;
		}
		else
		{
			info.fHasLayoutGrid = kTrue;
			if (layoutGridDataForPage->GetUseMaster())
			{
				info.fIsUsingMaster = kTrue;
			}
		}

		// (3) query the layout grid information
		// ICJKGridUtils::QueryLayoutGrid() will get the ACTUAL ICJKGridData interface, 
		// even if it is on a masterpage of a masterpage of a...
		// See NOTE below above 2nd InterfacePtr<ICJKLayoutGridData> instance within this method. 
		// Also see documentation for ICJKGridUtils::QueryLayoutGrid for details.
		InterfacePtr<ICJKGridData> gridData
			((ICJKGridData*)Utils<ICJKGridUtils>()->QueryLayoutGrid(pageHier, ICJKGridData::kDefaultIID));
		if (gridData == nil)
		{
			ASSERT(gridData);
			break;
		}
		// (3a) get the page string of the master
		pageList->GetPageString(::GetUID(gridData), &(info.fMasterPageString));

		// (3b) get information from ICJKGridManager
		InterfacePtr<ICJKGridManager> actualGridMgr(gridData, UseDefaultIID());
		if (actualGridMgr == nil)
		{
			ASSERT(actualGridMgr);
			break;
		}
		info.fIsGridVertical = actualGridMgr->IsGridVertical();
		actualGridMgr->GetGridBounds(info.fGridBounds);
		info.fCharsPerLine = actualGridMgr->GetCharsPerLine();
		info.fNumOfLines = actualGridMgr->GetNumOfLines();
		info.fRectCount = actualGridMgr->GetRectCount();
		info.fEmBoxRects.clear();
		info.fICFBoxRects.clear();
		for (int32 cellNumber = 0 ; cellNumber < info.fRectCount ; ++cellNumber)
		{
			PMRect rect;
			rect = actualGridMgr->GetNthEmBoxRect(cellNumber);
			info.fEmBoxRects.push_back(rect);
			rect = actualGridMgr->GetNthICFBoxRect(cellNumber);
			info.fICFBoxRects.push_back(rect);
		}
		info.fHCellSize = actualGridMgr->GetHCellSize();
		info.fVCellSize = actualGridMgr->GetVCellSize();
		actualGridMgr->GetICFAdjustments(info.fICFAdjustmentsX, info.fICFAdjustmentsY);

		// (3c) get information from ICJKLayoutGridData (starting point)
		/* NOTE: We query for ICJKLayoutGridData here again in the same method because
			the actual layout grid data may not be on the kPageBoss that corresponds 
			to the page we are inspecting, but a master page (also kPageBoss)...
			Or, it may be on the same kPageBoss that we are inspecting (if the user
			decided to override the layout grid data for a specific page). 
			The call to ICJKGridUtils::QueryLayoutGrid() above gives us an interface 
			on the true source of the layout grid data. That is why we are making sure
			we have the ICJKLayoutGridData from the boss that has the action 
			layout grid data.
		*/
		InterfacePtr<ICJKLayoutGridData> actualLayoutGridData(gridData, UseDefaultIID());
		if (actualLayoutGridData == nil)
		{
			ASSERT(actualLayoutGridData);
			break;
		}
		{
			info.fStartingPoint = actualLayoutGridData->GetGridStartingPoint();
		}


		// (3d) get all of the layout grid data from ICJKGridData
		// get font info
		info.fFontUID = gridData->GetFontUID();
		info.fFontStyleName = gridData->GetFontStyleName();

		// get font name - get IFontFamily via UID
		InterfacePtr<IFontFamily> fontFamily(db, info.fFontUID.Get(), UseDefaultIID());
		if (fontFamily == nil)
		{
			ASSERT_FAIL("Must be an invalid font UID");
			break;
		}
		InterfacePtr<IPMFont> font(fontFamily->QueryFace(info.fFontStyleName));    
		if (font == nil)
		{
			ASSERT_FAIL(FORMAT_ARGS("Cannot find font with style '%s'", info.fFontStyleName.GetUTF8String().c_str()));
			break;
		}
		// see IPMFont for other Append*Name() methods...
		font->AppendFullNameNative(info.fFontFullNativeName);

		info.fTextSize = gridData->GetTextSize();
		info.fCharAki = gridData->GetCharAki(); 
		info.fLineAki = gridData->GetLineAki(); 
		info.fCharOkuri = gridData->GetCharOkuri(info.fIsGridVertical);
		info.fLineOkuri = gridData->GetLineOkuri(info.fIsGridVertical);
		info.fHScale = gridData->GetHScale();
		info.fVScale = gridData->GetVScale();
		info.fTextAlignment = gridData->GetTextAlignment();
		info.fGridAlignment = gridData->GetGridAlignment();
		info.fCharacterHang = gridData->GetCharacterHang();

		// if we got here, we have succeeded!
		status = kSuccess;

	} while (false);

	return status;  
}


/* ReportLayoutGridInfo
*/
void SnpInspectLayoutGrid::ReportLayoutGridInfo(const SnpLayoutGridInfo& info, 
												const int32 pageIndex)
{
	// declare reusable variables
	PMString s("", PMString::kUnknownEncoding);
	int32 i = 0;
	const PMRect* r = nil;

	SNIPLOG("=========================================");
	if (pageIndex >= 0)
	{
		SNIPLOG("LayoutGrid info for page index [%d]:", pageIndex);
	}
	else
	{
		SNIPLOG("LayoutGrid info for selected page");
	}
	SNIPLOG("=========================================");
	SNIPLOG("Page: %s", info.fPageString.GetPlatformString().c_str());

	if (info.fHasLayoutGrid == kFalse)
	{
		SNIPLOG("LayoutGrid?: NO");
	}
	else
	{
		SNIPLOG("LayoutGrid?: YES");
		if (info.fIsUsingMaster)
		{
			SNIPLOG("From Master?: YES, MasterPage=(%s)", info.fMasterPageString.GetPlatformString().c_str());
		}
		else
		{
			SNIPLOG("From Master?: NO");
		}
		SNIPLOG("---<ICJKLayoutGridData>---");
		switch (info.fStartingPoint)
		{
		case ICJKLayoutGridData::kTopOutside: 
			s="kTopOutside"; break;
		case ICJKLayoutGridData::kTopInside: 
			s="kTopInside"; break;
		case ICJKLayoutGridData::kBottomOutside: 
			s="kBottomOutside"; break;
		case ICJKLayoutGridData::kBottomInside: 
			s="kBottomInside"; break;
		case ICJKLayoutGridData::kCenterVertical: 
			s="kCenterVertical"; break;
		case ICJKLayoutGridData::kCenterHorizontal: 
			s="kCenterHorizontal"; break;
		case ICJKLayoutGridData::kCenter: 
			s="kCenter"; break;
		default: 
			s="(unknown)"; break;
		}
		SNIPLOG("GridStartingPoint: %s", s.GetPlatformString().c_str());

		SNIPLOG("---<ICJKGridManager>---");

		SNIPLOG("Grid orientation: %s", (info.fIsGridVertical ? "VERT" : "HORIZ"));

		r = &(info.fGridBounds);
		SNIPLOG("Grid bounds: (L,T,R,B)=(%f,%f,%f,%f) pt", ::ToDouble(r->Left()), ::ToDouble(r->Top()), ::ToDouble(r->Right()), ::ToDouble(r->Bottom()));

		SNIPLOG("NumOfLines: %d", info.fNumOfLines);
		/*
		// This could result in an enormous amount of text for the SNIPLOG. 
		// which would slow down the snippet runner.
		// If you want to look at this, put a break point within the loop.
		*/
		for (i = 0; i < info.fCharsPerLine.size() ; ++i)
		{
			int32 charsPerLine = info.fCharsPerLine[i];
			//SNIPLOG("  Chars per line[%d]: %d", i, charsPerLine);
		}

		SNIPLOG("NumOfGridBoxes: %d", info.fRectCount);

		/*
		// This results in an enormous amount of text for the SNIPLOG,
		// which would slow down the snippet runner.
		// If you want to look at this, put a break point within the loop.
		for (i = 0 ; i < info.fRectCount ; ++i)
		{
			r = &(info.fEmBoxRects[i]);
			SNIPLOG("  EmBoxRect[%d]: (L,T,R,B)pt=(%f,%f,%f,%f)", i, r->Left(), r->Top(), r->Right(), r->Bottom());
			r = &(info.fICFBoxRects[i]);
			SNIPLOG("  ICFBoxRect[%d]: (L,T,R,B)pt=(%f,%f,%f,%f)",i, r->Left(), r->Top(), r->Right(), r->Bottom());
		}
		*/

		SNIPLOG("HCellSize: %f pt", ::ToDouble(info.fHCellSize));
		SNIPLOG("VCellSize: %f pt", ::ToDouble(info.fVCellSize));
		SNIPLOG("ICFAdjustments: (X,Y)=(%f, %f) pt", ::ToDouble(info.fICFAdjustmentsX), ::ToDouble(info.fICFAdjustmentsY));


		SNIPLOG("---<ICJKGridData>---");
		SNIPLOG("Font: %s, Size=%f pt", info.fFontFullNativeName.GetPlatformString().c_str(), ::ToDouble(info.fTextSize));
		SNIPLOG("CharAki: %f pt", ::ToDouble(info.fCharAki));
		SNIPLOG("LineAki: %f pt", ::ToDouble(info.fLineAki));
		SNIPLOG("CharOkuri: %f pt", ::ToDouble(info.fCharOkuri));
		SNIPLOG("LineOkuri: %f pt", ::ToDouble(info.fLineOkuri));
		SNIPLOG("HScale: %f%%", ::ToDouble(info.fHScale * 100.0));
		SNIPLOG("VScale: %f%%", ::ToDouble(info.fVScale * 100.0));

		switch (info.fTextAlignment)
		{
		case ICompositionStyle::kTextAlignLeft:
			s="kTextAlignLeft"; break;
		case ICompositionStyle::kTextAlignCenter:
			s="kTextAlignCenter"; break;
		case ICompositionStyle::kTextAlignRight:
			s="kTextAlignRight"; break;
		case ICompositionStyle::kTextAlignJustifyFull:
			s="kTextAlignJustifyFull"; break;
		case ICompositionStyle::kTextAlignJustifyLeft:
			s="kTextAlignJustifyLeft"; break;
		case ICompositionStyle::kTextAlignJustifyCenter:
			s="kTextAlignJustifyCenter"; break;
		case ICompositionStyle::kTextAlignJustifyRight:
			s="kTextAlignJustifyRight"; break;
		case ICompositionStyle::kTextAlignAuto:
			s="kTextAlignAuto"; break;
		default: s="(unknown)"; break;
		}
		SNIPLOG("TextAlignment: %s", s.GetPlatformString().c_str());


		switch (info.fGridAlignment)
		{
		case Text::kGANone:
			s="kGANone"; break;
		case Text::kGABaseline:
			s="kGABaseline"; break;
		case Text::kGAEmTop:
			s="kGAEmTop"; break;
		case Text::kGAEmCenter:
			s="kGAEmCenter"; break;
		case Text::kGAEmBottom:
			s="kGAEmBottom"; break;
		case Text::kGAICFTop:
			s="kGAICFTop"; break;
		case Text::kGAICFBottom:
			s="kGAICFBottom"; break;
		case Text::kGACapHeight:
			s="kGACapHeight"; break;
		default:
			s="(unknown)"; break;
		}
		SNIPLOG("GridAlignment: %s", s.GetPlatformString().c_str());

		switch (info.fCharacterHang)
		{
		case IDrawingStyle::kHangBaseline:
			s="kHangBaseline"; break;
		case IDrawingStyle::kHangEmCenter:
			s="kHangEmCenter"; break;
		case IDrawingStyle::kHangEmBottom:
			s="kHangEmBottom"; break;
		case IDrawingStyle::kHangEmTop:
			s="kHangEmTop"; break;
		case IDrawingStyle::kHangICFBottom:
			s="kHangICFBottom"; break;
		case IDrawingStyle::kHangICFTop:
			s="kHangICFTop"; break;
		default:
			s="(unknown)"; break;
		}
		SNIPLOG("CharacterHang: %s", s.GetPlatformString().c_str());
	}
} 

/* GetFirstSelectedPage
*/
UIDRef SnpInspectLayoutGrid::GetFirstSelectedPage(IActiveContext* activeContext)
{
	UIDRef selectedItem(nil, kInvalidUID);

	do
	{
		if (activeContext == nil)
		{
			break; // out of do-while
		}
		// get the current context document, so we can get the database
		IDocument* doc = activeContext->GetContextDocument();
		if (doc == nil)
		{
			// don't throw an assert here, as this method is called from CanRun.
			// just return an invalid UIDRef.
			break;
		}
		IDataBase* db = ::GetDataBase(doc);
		UIDList selectedPages(db);
		Utils<ILayoutUIUtils>()->GetSelectedPages(selectedPages);

		// check if we got anything
		if (selectedPages.Length() > 0)
		{
			// get the first item (kPageBoss) in the UIDList (arbitrary)
			selectedItem = selectedPages.GetRef(0);
		}
		// else we want to return the empty UIDRef to the caller, indicating 
		// that we didn't get any UIDRefs - this is a rare case and shouldn't happen.

	} while (false);

	return selectedItem;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpInspectLayoutGrid available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerInspectLayoutGrid : public SnpRunnable
{

public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerInspectLayoutGrid(void);

	/** Destructor.
	 */
	virtual         ~_SnpRunnerInspectLayoutGrid(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16          CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode       Run(ISnpRunnableContext* runnableContext);

	/** Only present this snippet in the framework's UI if the
		language feature set is Japanese and the product is InDesign.
		@return kTrue if the snippet can be loaded, kFalse otherwise.
	*/
	bool16 CanLoad() const;
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}

};
/* Constructor.
*/
_SnpRunnerInspectLayoutGrid::_SnpRunnerInspectLayoutGrid(void) : SnpRunnable("InspectLayoutGrid")
{
	this->SetDescription("Inspect layout grid data on a selected page");
	this->SetPreconditions("document must be open");
	this->SetCategories("sdk_snippet, sdk_layout, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerInspectLayoutGrid::~_SnpRunnerInspectLayoutGrid(void)   
{
	// do nothing.
}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerInspectLayoutGrid::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		if (runnableContext == nil)
		{
			break;
		}

		// get the first selected page
		IActiveContext* activeContext = runnableContext->GetActiveContext();
		SnpInspectLayoutGrid instance;
		UIDRef targetUIDRef = instance.GetFirstSelectedPage(activeContext);
		if (targetUIDRef.ExistsInDB() == kFalse)
		{
			break;
		}

		// if we got here, we are ready to run
		result = kTrue;
	} while (false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInspectLayoutGrid::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do
	{
		SnpInspectLayoutGrid instance;
		if (runnableContext == nil)
		{
			SNIPLOG("No runnable context!");
			break;
		}
		// get the first selected page
		IActiveContext* activeContext = runnableContext->GetActiveContext();
		UIDRef targetUIDRef = instance.GetFirstSelectedPage(activeContext);
		if (targetUIDRef.ExistsInDB() == kFalse)
		{
			SNIPLOG("Could not get any selected pages!");
			break;
		}

		UIDList selectedPagesList(targetUIDRef);
		status = instance.InspectPages(selectedPagesList);

	} while (false);
	return status;
}

/* 
*/
bool16  _SnpRunnerInspectLayoutGrid::CanLoad() const
{
	bool16 result = kTrue;
	// Adopt the same load logic as the sister snippet SnpModifyLayoutGrid.
	if (LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS) == kFalse) {
		// Only load under the Japanese language feature set.
		result = kFalse;
	}
	if (LocaleSetting::GetLocale().IsProductFS(kInDesignProductFS) == kFalse) {
		// Only load under InDesign.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectLayoutGrid instance_SnpRunnerInspectLayoutGrid;
DEFINE_SNIPPET(_SnpRunnerInspectLayoutGrid) 	

// End, SnpInspectLayoutGrid.cpp


