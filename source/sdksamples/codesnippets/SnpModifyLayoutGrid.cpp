//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpModifyLayoutGrid.cpp $
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
#include "IActiveContext.h"
#include "ICJKGridData.h"
#include "ICJKGridPrefs.h"
#include "ICJKGridUtils.h"
#include "ICJKLayoutGridData.h"
#include "ICJKLayoutGridDefaults.h"
#include "IColumnGutterCmdData.h"
#include "IColumnPrefs.h"
#include "IColumnPrefsCmdData.h"
#include "IColumns.h"
#include "ICommand.h"
#include "ICommandSequence.h"
#include "ICompositionStyle.h" // for TextAlignment enum
#include "IControlView.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDrawingStyle.h" // for CharacterHang enum
#include "IFilteredCJKGridCmdData.h"
#include "IFontFamily.h"
#include "IGeometry.h"
#include "ILayoutUIUtils.h"
#include "IMarginPrefs.h"
#include "IMarginPrefsCmdData.h"
#include "IMargins.h"
#include "IMasterPage.h"
#include "IMeasurementSystem.h"
#include "IPageColumnsCmdData.h"
#include "IPageList.h"
#include "IPageMarginsCmdData.h"
#include "IPageSetupPrefs.h"
#include "IPMFont.h"
#include "ITextAttrFont.h"
#include "ITextAttributes.h"
#include "ITextAttrUID.h"
#include "ITextOptions.h"
#include "IUnitOfMeasure.h"
#include "IWorkspace.h"
// General includes:
#include "CJKID.h"
#include "CJKLayoutID.h"
#include "CmdUtils.h"
#include "CTextEnum.h" // for GridAlignmentMetric enum
#include "LocaleSetting.h"
#include "PersistUtils.h"
#include "PreferenceUtils.h"
#include "SpreadID.h" // for various page/spread IIDs and page command IDs
#include "TextAttrID.h"

// Framework includes:
#include "SnipRunID.h"
#include "SnipRunLog.h"
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "ISnpRunnableContext.h"
#include "ErrorUtils.h"


// TODO align with coding conventions
#define ASSERT_BREAK_IF_NIL(p) if (p==nil) { ASSERT(p); break; }
#define ASSERT_BREAK_IF_UNSUCCESSFUL(p) if (p!=kSuccess) { ASSERT(p!=kSuccess); break; }

/** Keeps layout grid setup related parameters. 
*/
//struct 
class SnpModLayoutGridParameters
{
public:
	/** Constructor.  Sets defaults so we can tell if something was mutated.
	 */
	SnpModLayoutGridParameters(void):
		fStartingPoint(ICJKLayoutGridData::kTopOutside),
		fModifyMasterPage(kFalse),
		fVertical(kFalse),
		fNumCharsPerLine(-1),
		fNumLines(-1),
		fNumColumns(-1),
		fColumnGapWidth(-1.0),
		fMarginLeft(-1.0),
		fMarginTop(-1.0),
		fMarginRight(-1.0),
		fMarginBottom(-1.0),
		fFontUID(kInvalidUID),
		fFontStyle(""),
		fTextSize(-1.0),
		fCharAki(-1.0),
		fLineAki(-1.0),
		fCharOkuri(-1.0),
		fLineOkuri(-1.0),
		fHScale(-1.0),
		fVScale(-1.0),
		fAlignment(ICompositionStyle::kTextAlignLeft),
		fGridAlignment(Text::kGANone),
		fCharacterHang(IDrawingStyle::kHangBaseline)
    {
	}
	/** Destructor.  Does nothing.
	 */
	~SnpModLayoutGridParameters(void) 
	{}

	// member variables
	
	/* ICJKLayoutGridData settings */

	/** Starting point of grid.
	 * 	@see kSetCJKLayoutGridDataCmdBoss
	 * 	@see ICJKLayoutGridData
	 */
	ICJKLayoutGridData::GridStartingPoint fStartingPoint;

	/** Flag that indicates if you want to modify the master page.
	 * 	@see kSetCJKLayoutGridDataCmdBoss
	 * 	@see ICJKLayoutGridData
	 */
	bool16 fModifyMasterPage;

	/* layout related data */
	/** Layout grid orientation flag - kTrue if vertical.
	 * 	@see kSetPageColumnsCmdBoss
	 * 	@see IPageColumnsCmdData
	 */
	bool16 fVertical;

	/** Number of characters per line per column in the layout grid.
	 * 	This affects the column height if vertical, and column width if horizontal.
	 * 	@see kSetPageColumnsCmdBoss
	 * 	@see IPageColumnsCmdData
	 */
	int32 fNumCharsPerLine;

	/** Number of lines in a column in the layout grid. 
	 * 	This affects the column width if vertical, and column height if horizontal
	 * 	@see kSetPageMarginsCmdBoss
	 * 	@see IPageMarginsCmdData
	 */
	int32 fNumLines;

	/** Number of columns the layout grid.
	 * 	@see kSetPageColumnsCmdBoss
	 * 	@see IPageColumnsCmdData
	 */
	int32 fNumColumns;

	/** The distance in between columns.
	 * 	@see kSetColumnGutterCmdBoss
	 * 	@see IColumnGutterCmdData
	 */
	PMReal fColumnGapWidth;

	/** "Left" margin.  Inside if left page, outside if right page.
	 * 	@see kSetPageMarginsCmdBoss
	 * 	@see IPageMarginsCmdData
	 */
	PMReal fMarginLeft;
	
	/** Top margin.
	 * 	@see kSetPageMarginsCmdBoss
	 * 	@see IPageMarginsCmdData
	 */
	PMReal fMarginTop;
	
	/** "Right" margin.  Outside if left page, inside if right page.
	 * 	@see kSetPageMarginsCmdBoss
	 * 	@see IPageMarginsCmdData
	 */
	PMReal fMarginRight;
	
	/** Bottom margin.
	 * 	@see kSetPageMarginsCmdBoss
	 * 	@see IPageMarginsCmdData
	 */
	PMReal fMarginBottom;


	/* ICJKGridData settings - copy from workspace defaults if not set right */

	/** UID of default font family to use in the layout grid.
	 * 	Defaults to kInvalidUID.
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	UID fFontUID; 
	
	/** Name of default font style to use in the layout grid.
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMString fFontStyle; // ""
	
	/** Text size to use in the layout grid.
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fTextSize;  // -1.0 (points)

	/** Size of the character aki (spacing).
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fCharAki;	// -1.0(points)

	/** Size of the line aki (spacing) 
	 * 	(This is the distance from the bottom of one line to the top of the next line, and
	 * 	is NOT equivalent to leading.)
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fLineAki;	// -1.0(points)

	/** The distance between the top of two adjacent characters in a line.
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fCharOkuri; // -1.0 (points)

	/** Leading value (for Japanese text composition)
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fLineOkuri; // -1.0 (points)

	/** Horizontal character scale.
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fHScale;	// -1.0 (0..1)

	/** Vertical character scale. 
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	PMReal fVScale; 	// -1.0 (0..1)

	/** Specifies how characters are aligned with each other in a text run.
	 * 	@see TextAlignment
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
    ICompositionStyle::TextAlignment fAlignment; // (invalid)

	/** Specifies what part of the tile and grid should be aligned to each other.
	 * 	@see GridAlignmentMetric
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	Text::GridAlignmentMetric fGridAlignment; // (invalid)

	/** Specifies how the character hangs in a grid box.
	 * 	@see CharacterHang
	 * 	@see kSetCJKGridDataCmdBoss
	 * 	@see IFilteredCJKGridCmdData
	 * 	@see kSetCJKLayoutGridDefaultsCmdBoss
	 * 	@see ICJKLayoutGridDefaults
	 */
	IDrawingStyle::CharacterHang fCharacterHang; // (invalid)
};


/**	
 * 	\li How to modify the layout grid data for a page or the global workspace.
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_cjk
 * 	@ingroup sdk_layout
 */
class SnpModifyLayoutGrid 
{
public:
	/** Constructor.
	 */
	SnpModifyLayoutGrid() {}

	/** Destructor.
	 */
	virtual ~SnpModifyLayoutGrid() {}

	/**	The main method that modifies a layout grid, either on a page
	 * 	or a global workspace.  Note that layout grid data exists for both
	 * 	a page and a global workspace.  Also, a page may be using a layout
	 * 	grid from a master page (and that master page may be based on 
	 * 	another master page...)
	 * 
	 * 	@param targetPageOrWorkspace (in) UIDRef to a page or workspace. 
	 * 		A page has IMasterPage, IColumns, IMargins. If a page 
	 * 		is selected, the UIDRef will be that of a page (kPageBoss).
	 * 		A workspace has ICJKLayoutGridDefaults. If no document is
	 * 		open at the moment, the UIDRef should be that of a
	 * 		workspace (kWorkspaceBoss)
	 * 	@param parameters (in) A structure that contains all of the 
	 * 		layout grid parameters to use. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode ModifyLayoutGrid(UIDRef& targetPageOrWorkspace, 
							   const SnpModLayoutGridParameters& parameters);
	
	/** Modifies layout grid defaults on a page.
	 * 	@param targetPage (in) As long as this is a valid page, the view is not required.
	 * 	@param parameters (in) A structure that contains all of the 
	 * 		layout grid parameters to use. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 * 	@see ModifyLayoutGrid()
	 */
	ErrorCode ModifyLayoutGridPage(UIDRef& targetPage, 
								   const SnpModLayoutGridParameters& parameters);

	/** Modifies layout grid defaults on a workspace.
	 * 	Note that this method sets the defaults on the workspace. 
	 * 	To restore original defaults, delete your "InDesign Defaults" file.
	 * 	This method is verified to work on the global workspace, although
	 * 	you could probably use this on the document workspace as well.
	 * 	@param targetWorkspace (in) The workspace to target.
	 * 	@param parameters (in) A structure that contains all of the 
	 * 		layout grid parameters to use. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 * 	@see ModifyLayoutGrid() method.
	 */
	ErrorCode ModifyLayoutGridWorkspace(UIDRef& targetWorkspace, 
										const SnpModLayoutGridParameters& parameters);

	
	/** Gets the first visible and selected page, or if there are no pages selected, 
	 * 	returns the global workspace.
	 * 	@param activeContext (in) The current active context.
	 *	@return UIDRef of the first selected page or global workspace
	 */
	UIDRef GetFirstSelectedPageOrGlobalWorkspace(IActiveContext* activeContext);

	/**	Gets arguments and puts the values into a parameter structure.
	 * 	Also set hardcoded default values for other parameters that are 
	 * 	not specified as sniprun arguments.
	 *  NOTE: You can experiment by changing some of the hardcoded parameters 
	 * 		inside this method to see what happens!
	 * 	@param db (in) The database to get the preferences from.
	 * 	@param params (out) The parsed and preset parameters.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	const ErrorCode GetParameters(IDataBase* db, 
								  SnpModLayoutGridParameters& params);
	
	/** Convert millimeters into point. 
		@param val (in) Value in millimeters to be converted. */
	static PMReal ConvertMillimetersToPoint(const PMReal& val);

	/** Convert Q (kyu) into point.
		@param val Value in Q to be converted. */
	static PMReal ConvertQToPoint(const PMReal& val);

	/** Convert Ha into point.
		@param val Value in Ha to be converted. */
	static PMReal ConvertHaToPoint(const PMReal& val);

private:

	/** Sets up the CJK Grid data using IFilteredCJKGridCmdData for 
	 * 	kSetCJKGridDataCmdBoss.
	 * 	@param parameters (in) The layout grid parameters to use.
	 * 	@param sourceGridData (in) The grid data to use as a basis.
	 * 	@param destGridData (in/out) The destination grid data to set up.
	*/
	void SetupFilteredCJKGridData(const SnpModLayoutGridParameters& parameters,
								  ICJKGridData* sourceGridData,
								  IFilteredCJKGridCmdData* destGridData);

	/**	Sets up the default layout grid settings for 
	 * 	kSetCJKLayoutGridDefaultsCmdBoss.
	 * 	@param parameters (in) The layout grid parameters to use.
	 * 	@param sourceCJKLayoutGridDefaults (in) The layout grid default data 
	 * 		to use as a basis.
	 * 	@param destCJKLayoutGridDefaults (in/out) The destination layout 
	 * 		grid default data to set up.
	 */
	void SetupLayoutGridDefaults(const SnpModLayoutGridParameters& parameters, 
								 ICJKLayoutGridDefaults* sourceCJKLayoutGridDefaults,
								 ICJKLayoutGridDefaults* destCJKLayoutGridDefaults);
	
	/**	Calculates the column settings based on layout grid parameters.
	 * 	@param parameters (in) The layout grid parameters to use.
	 * 	@param pageRect (in) The dimensions of the page.
	 * 	@param pageCols (out) The calculated column settings.
	 * 	@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode CalculateColumns(const SnpModLayoutGridParameters& parameters, 
							   const PMPageSize& pageRect,
							   PMRealList& pageCols);

	/**	Calculates the margin settings based on layout grid parameters.
	 * 	@param parameters (in) The layout grid parameters to use.
	 * 	@param db (in) The target database (either document or 
	 * 		global workspace)
	 * 	@param pageRect (in) The dimensions of the page. 
	 * 	@param totalColumnSize (in) The column size calculated in 
	 * 		CalculateColumns().
	 * 	@param inside (out) The calculated inside margin settings.
	 * 	@param top (out) The calculated top margin settings.
	 * 	@param outside (out) The calculated outside margin settings.
	 * 	@param bottom (out) The calculated bottom margin settings.
	 * 	@param pageGeometry (in, optional) The IGeometry of the page 
	 * 		to set margins (needed only if db refers to a document)
	 * 	@return kSuccess on success, kFailure otherwise.
 	 */
	ErrorCode CalculateMargins(const SnpModLayoutGridParameters& parameters, 
							   IDataBase* db, const PMPageSize& pageRect,
							   const PMReal totalColumnSize,
							   PMReal& inside, PMReal& top, 
							   PMReal& outside, PMReal& bottom,
							   IGeometry* pageGeometry = nil);


};



/* ModifyLayoutGrid
*/
ErrorCode SnpModifyLayoutGrid::ModifyLayoutGrid(UIDRef& targetPageOrWorkspace,
												const SnpModLayoutGridParameters& parameters)
{
	ErrorCode status = kFailure;
	ICommandSequence* seq = nil;

	// We'll use a do-while to break out when we have a bad pointer:
	do
	{	
		bool16 isTargetAPage;

		// verify parameters
		if (targetPageOrWorkspace.GetDataBase() == nil ||
			targetPageOrWorkspace.GetUID() == kInvalidUID)
		{
			ASSERT_FAIL("Invalid targetPageOrWorkspace!");
			break;
		}
		
		// check the UIDRef to see what boss it refers to (page or workspace?), and set a flag
		InterfacePtr<IMargins> margins(targetPageOrWorkspace, IID_IMARGINS);
		InterfacePtr<IColumns> columns(targetPageOrWorkspace, IID_IMARGINS);
		InterfacePtr<IMasterPage> masterPage(targetPageOrWorkspace, IID_IMASTERPAGE);
		InterfacePtr<ICJKLayoutGridDefaults> cjkLayoutGridDefaults(targetPageOrWorkspace, 
																   IID_ICJKLAYOUTGRIDDEFAULTS);
		
		if (margins && columns && masterPage) 
		{
			// it has IMargins, IColumns, and IMasterPage - must be kPageBoss
			isTargetAPage = kTrue;
		}
		else if (cjkLayoutGridDefaults) 
		{
			// it has ICJKLayoutGridDefaults 
			// this means it's a workspace (doc or global - we don't care)
			isTargetAPage = kFalse; 
		}
		else
		{
			ASSERT_FAIL("The targetPageOrWorkspace parameter is neither a page or a workspace");
			break;
		}

		// start a command sequence
		seq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		ASSERT_BREAK_IF_NIL(seq)

		if (isTargetAPage == kTrue) 
		{
			// process the commands to set the layout grid for a page
			status = this->ModifyLayoutGridPage(targetPageOrWorkspace, 
												parameters);
		}
		else
		{
			// for the workspace, we just need to change the 
			// CJKLayoutGridDefaults on the workspace.
			status = this->ModifyLayoutGridWorkspace(targetPageOrWorkspace, 
													 parameters);
		}
	} while (false); // Only do once.

	// clean up the sequence based on status code
	if (seq) 
	{
		if (status == kSuccess) 
		{
			CmdUtils::EndCommandSequence(seq);
		}
		else
		{
			ErrorUtils::PMSetGlobalErrorCode(status);
			CmdUtils::EndCommandSequence(seq);
		}
		seq = nil;
	}
	return status;
} 

/* ModifyLayoutGridPage
	Modifies the layout grid for the given page.
	Step 1: kSetCJKGridPrefsCmdBoss on the kDocWorkspaceBoss (if necessary)
	Step 2: kSetCJKLayoutGridDataCmdBoss and kSetCJKGridDataCmdBoss on the page
	Step 3: kSetPageColumnsCmdBoss and kSetPageMarginsCmdBoss on the page
*/
ErrorCode SnpModifyLayoutGrid::ModifyLayoutGridPage(UIDRef& targetPage, 
													const SnpModLayoutGridParameters& parameters)
{
	ErrorCode status = kFailure;
	// the page (release this later)
	IGeometry* thePage = nil;

	do {
		if (targetPage.GetDataBase() == nil ||
			targetPage.GetUID() == kInvalidUID) 
		{
			// this would have been caught earlier...
			break;
		}

		// get the database
		IDataBase* db = targetPage.GetDataBase();

		// get the document
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		ASSERT_BREAK_IF_NIL(doc)

		// get the current page geometry
		InterfacePtr<IGeometry> selectedPage(targetPage, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(selectedPage)

		// get the actual page we want to modify
		if (parameters.fModifyMasterPage == kTrue)
		{
			// get the true master page 
			// (even if the master is based on a master is based...)
			thePage = (IGeometry*)Utils<ICJKGridUtils>()->QueryLayoutGrid(selectedPage, IGeometry::kDefaultIID);
		}
		else
		{
			// stay on the current page
			thePage = selectedPage.forget();
		}
		ASSERT_BREAK_IF_NIL(thePage)

		// create a UIDRef for this page
		UIDRef thePageRef(db, ::GetUID(thePage));
		// create a UIDList with this page
		UIDList thePageList(thePageRef);

		// OKAY! Now we are ready to process the 3 steps to set up the layout grid
		// ***************************************************
		// [Step 1: Show all layout grids if they are not on]
		InterfacePtr<ICJKGridPrefs> currentGridPrefs((ICJKGridPrefs*)::QueryPreferences(IID_ICJKGRIDPREFS, doc));
		ASSERT_BREAK_IF_NIL(currentGridPrefs)

		// decide if we need to show the layout grids
		bool16	showGrids = !currentGridPrefs->GetShowAllLayoutGrids(); 

		if (showGrids)
		{
			// create the SetCJKGridPrefsCmd
			InterfacePtr<ICommand> setCJKGridPrefsCmd(CmdUtils::CreateCommand(kSetCJKGridPrefsCmdBoss));
			ASSERT_BREAK_IF_NIL(setCJKGridPrefsCmd)

			// get the command data interface
			InterfacePtr<ICJKGridPrefs> myCJKGridPrefs(setCJKGridPrefsCmd, IID_ICJKGRIDPREFS);
			ASSERT_BREAK_IF_NIL(myCJKGridPrefs)

			// set up the data
			myCJKGridPrefs->CopyFrom(currentGridPrefs);
			myCJKGridPrefs->SetShowAllLayoutGrids(showGrids);

			// setup the item list (document workspace)
			setCJKGridPrefsCmd->SetItemList(UIDList(currentGridPrefs));

			// change the name of the command based on the flag
			/* NOTE: Translations for these strings are automatically 
				available only if the Layout Grid Dialog plugin is loaded */
			setCJKGridPrefsCmd->SetName(showGrids ? "Show Layout Grid" : "Hide Layout Grid");

			status = CmdUtils::ProcessCommand(setCJKGridPrefsCmd);
			ASSERT_BREAK_IF_UNSUCCESSFUL(status)
		}		

		// ***************************************************
		// [Step 2a: Set CJK Layout Grid Data]

		// create the SetCJKLayoutGridDataCmd 
		InterfacePtr<ICommand> setCJKLayoutGridDataCmd(CmdUtils::CreateCommand(kSetCJKLayoutGridDataCmdBoss));
		ASSERT_BREAK_IF_NIL(setCJKLayoutGridDataCmd)

		// set the cmd data
		InterfacePtr<ICJKLayoutGridData> cmdCJKLayoutGridData(setCJKLayoutGridDataCmd, IID_ICJKLAYOUTGRIDDATA);
		ASSERT_BREAK_IF_NIL(cmdCJKLayoutGridData)
		cmdCJKLayoutGridData->SetGridStartingPoint(parameters.fStartingPoint);
		cmdCJKLayoutGridData->SetUseMaster(parameters.fModifyMasterPage);

		// set up item list
		setCJKLayoutGridDataCmd->SetItemList(thePageList);

		// process the command
		status = CmdUtils::ProcessCommand(setCJKLayoutGridDataCmd);


		// [Step 2b: Set CJK Grid Data]
		// get the grid data from the page (master or actual page)
		InterfacePtr<ICJKGridData> pageGridData(thePage, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pageGridData)

		//Create kSetCJKGridDataCmdBoss command.
		InterfacePtr<ICommand> setCJKGridDataCmd(CmdUtils::CreateCommand(kSetCJKGridDataCmdBoss));
		ASSERT_BREAK_IF_NIL(setCJKGridDataCmd)

		// Get own IFilteredCJKGridCmdData interface.
		InterfacePtr<IFilteredCJKGridCmdData> myFilteredCJKGridData(setCJKGridDataCmd, IID_IFILTEREDCJKGRIDCMDDATA);
		ASSERT_BREAK_IF_NIL(myFilteredCJKGridData)

		// set up the filtered data
		this->SetupFilteredCJKGridData(parameters, pageGridData, myFilteredCJKGridData);

		// set up item list
		setCJKGridDataCmd->SetItemList(thePageList);

		// process the command
		status = CmdUtils::ProcessCommand(setCJKGridDataCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)


		// ***************************************************
		// [Step 3: Set Page related data (margin, column gutter, columns)]
		// get the page dimensions
		PMRect pageRect = thePage->GetStrokeBoundingBox();

		// calculate the columns based on parameters
		PMRealList pageCols;
		pageCols.clear();
		status = this->CalculateColumns(parameters, PMPageSize(pageRect), pageCols);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		// calculate the columns based on parameters
		PMReal totalColumnSize = pageCols[pageCols.size()-1];
		PMReal 	inside = 0.0, 
				top = 0.0, 
				outside = 0.0,
				bottom = 0.0;
		status = this->CalculateMargins(parameters, db, PMPageSize(pageRect), 
										totalColumnSize, 
										inside, top, 
										outside, bottom, 
										thePage);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		// [Step 3a: Set Page Margin Data]
		// create the SetPageMarginsCmd
		InterfacePtr<ICommand> setPageMarginsCmd(CmdUtils::CreateCommand(kSetPageMarginsCmdBoss));
		ASSERT_BREAK_IF_NIL(setPageMarginsCmd)

		// set the margin data
		InterfacePtr<IPageMarginsCmdData> pageMarginsCmdData(setPageMarginsCmd, IID_IPAGEMARGINSCMDDATA);
		ASSERT_BREAK_IF_NIL(pageMarginsCmdData)
		pageMarginsCmdData->Set(inside, top, outside, bottom, kTrue);

		// set the item list
		setPageMarginsCmd->SetItemList(thePageList);

		// process the command
		status = CmdUtils::ProcessCommand(setPageMarginsCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)


		// [Step 3b: Set Column Gap Data]
		InterfacePtr<ICommand> setColumnGutterCmd(CmdUtils::CreateCommand(kSetColumnGutterCmdBoss));
		ASSERT_BREAK_IF_NIL(setPageMarginsCmd)

		// set the gutter data
		InterfacePtr<IColumnGutterCmdData> columnGutterCmdData(setColumnGutterCmd, IID_ICOLUMNGUTTERCMDDATA);
		ASSERT_BREAK_IF_NIL(columnGutterCmdData)
		columnGutterCmdData->Set(parameters.fColumnGapWidth);

		// set the item list
		setColumnGutterCmd->SetItemList(thePageList);

		// process the command
		status = CmdUtils::ProcessCommand(setColumnGutterCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)


		// [Step 3c: Set Page Column Data]
		bool16 isCustom = kFalse;
		bool16 isVertical = parameters.fVertical;

		// create the SetPageColumnsCmd
		InterfacePtr<ICommand> setPageColumnsCmd(CmdUtils::CreateCommand(kSetPageColumnsCmdBoss));
		ASSERT_BREAK_IF_NIL(setPageColumnsCmd)

		// set the column data
		InterfacePtr<IPageColumnsCmdData> pageColumnsCmdData(setPageColumnsCmd, IID_IPAGECOLUMNSCMDDATA);
		ASSERT_BREAK_IF_NIL(pageColumnsCmdData)
		pageColumnsCmdData->SetPageColumnsCmdData_( pageCols, isVertical ? IColumns::kTraditionalCJKColumnOrientation : IColumns::kRomanColumnOrientation, kTrue, kFalse);

		// set the item list
		setPageColumnsCmd->SetItemList(thePageList);

		// process the command
		status = CmdUtils::ProcessCommand(setPageColumnsCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

	} while (false);
	
	// the page is no longer needed - cleanup
	if (thePage != nil) 
	{
		thePage->Release();
		thePage = nil;
	}
	return status;
}

/* ModifyLayoutGridWorkspace
	Modifies the layout grid for the given workspace.
	Step 1: kSetCJKGridPrefsCmdBoss on kWorkspaceBoss to show the grids 
	Step 2: kSetCJKLayoutGridDefaultsCmdBoss on kWorkspaceBoss 
	Step 3: kSetMarginPrefsCmdBoss and kSetColumnPrefsCmdBoss
*/
ErrorCode SnpModifyLayoutGrid::ModifyLayoutGridWorkspace(UIDRef& targetWorkspace, 
														 const SnpModLayoutGridParameters& parameters)
{
	ErrorCode status = kFailure;
	do {
		if (targetWorkspace.GetDataBase() == nil ||
			targetWorkspace.GetUID() == kInvalidUID) 
		{
			// this would have been caught earlier...
			break;
		}
		
		// get the workspace
		InterfacePtr<IWorkspace> workspace(targetWorkspace, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(workspace)

		// make a UIDList for the workspace
		UIDList workspaceList(targetWorkspace);
        
		// OKAY! Now we are ready to process the 3 steps to set up the layout grid defaults 

		// ***************************************************
		// [Step 1: Show all layout grids if they are not on]
		InterfacePtr<ICJKGridPrefs> workspaceGridPrefs(workspace, IID_ICJKGRIDPREFS);
		ASSERT_BREAK_IF_NIL(workspaceGridPrefs)

		// decide if we need to show the layout grids
		bool16	workspaceShowGrids = !workspaceGridPrefs->GetShowAllLayoutGrids(); 

		if (workspaceShowGrids)
		{
			// create the SetCJKGridPrefsCmd
			InterfacePtr<ICommand> setWSCJKGridPrefsCmd(CmdUtils::CreateCommand(kSetCJKGridPrefsCmdBoss));
			ASSERT_BREAK_IF_NIL(setWSCJKGridPrefsCmd)

			// get the command data interface
			InterfacePtr<ICJKGridPrefs> myWSCJKGridPrefs(setWSCJKGridPrefsCmd, IID_ICJKGRIDPREFS);
			ASSERT_BREAK_IF_NIL(myWSCJKGridPrefs)

			// set up the data
			myWSCJKGridPrefs->CopyFrom(workspaceGridPrefs);
			myWSCJKGridPrefs->SetShowAllLayoutGrids(workspaceShowGrids); 

			// setup the item list (global workspace)
			setWSCJKGridPrefsCmd->SetItemList(workspaceList);

			// change the name of the command based on the flag
			/* NOTE: Translations for these strings are automatically 
				available only if the Layout Grid Dialog plugin is loaded */
			setWSCJKGridPrefsCmd->SetName(workspaceShowGrids ? "Show Layout Grid" : "Hide Layout Grid"); 

			status = CmdUtils::ProcessCommand(setWSCJKGridPrefsCmd);
			ASSERT_BREAK_IF_UNSUCCESSFUL(status)
		}		

		// ***************************************************
		// [Step 2: Set Layout grid defaults]

		// get the grid data from the workspace
		InterfacePtr<ICJKLayoutGridDefaults> wsCJKLayoutGridDefaults(workspace, IID_ICJKLAYOUTGRIDDEFAULTS);
		ASSERT_BREAK_IF_NIL(wsCJKLayoutGridDefaults)

		//Create kSetCJKLayoutGridDefaultsCmdBoss command.
		InterfacePtr<ICommand> setCJKLayoutGridDefaultsCmd(CmdUtils::CreateCommand(kSetCJKLayoutGridDefaultsCmdBoss));
		ASSERT_BREAK_IF_NIL(setCJKLayoutGridDefaultsCmd)

		// Get own ICJKLayoutGridDefaults interface.
		InterfacePtr<ICJKLayoutGridDefaults> cjkLayoutGridDefaultsCmdData(setCJKLayoutGridDefaultsCmd, IID_ICJKLAYOUTGRIDDEFAULTS);
		ASSERT_BREAK_IF_NIL(cjkLayoutGridDefaultsCmdData)

		// set up the layout grid data
		this->SetupLayoutGridDefaults(parameters, wsCJKLayoutGridDefaults, cjkLayoutGridDefaultsCmdData);

		// set up item list
		setCJKLayoutGridDefaultsCmd->SetItemList(workspaceList);

		// process the command
		status = CmdUtils::ProcessCommand(setCJKLayoutGridDefaultsCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		
		// ***************************************************
		// [Step 3: Set Page related data Data (margin, column gutter, columns)]
		// get the page dimensions
		InterfacePtr<IPageSetupPrefs> pageSetupPrefs(workspace, IID_IPAGEPREFERENCES);
		ASSERT_BREAK_IF_NIL(pageSetupPrefs)
		PMPageSize pageRect = pageSetupPrefs->GetPageSizePref();

		// calculate the columns based on parameters
		PMRealList pageCols;
		pageCols.clear();
		status = this->CalculateColumns(parameters, pageRect, pageCols);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		// calculate the columns based on parameters
		PMReal totalColumnSize = pageCols[pageCols.size()-1];
		PMReal 	inside = 0.0, 
				top = 0.0, 
				outside = 0.0,
				bottom = 0.0;
		status = this->CalculateMargins(parameters, targetWorkspace.GetDataBase(), pageRect, totalColumnSize, inside, top, outside, bottom);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		// [Step 3a: Set workspace margin preferences data]
		// get the current margin prefs (for inspection)
		InterfacePtr<IMarginPrefs> marginPrefs(workspace, IID_IMARGINPREFERENCES);
		ASSERT_BREAK_IF_NIL(marginPrefs)
#ifdef DEBUG
		// examine margins (debug only)
		PMReal currInside, currTop, currOutside, currBottom;
		marginPrefs->GetMargins(&currInside, &currTop, &currOutside, &currBottom);
#endif
		// create the SetMarginPrefsCmd
		InterfacePtr<ICommand> setMarginPrefsCmd(CmdUtils::CreateCommand(kSetMarginPrefsCmdBoss));
		ASSERT_BREAK_IF_NIL(setMarginPrefsCmd)

		// set the margin prefs data
		InterfacePtr<IMarginPrefsCmdData> marginPrefsCmdData(setMarginPrefsCmd, IID_IMARGINPREFSCMDDATA);
		ASSERT_BREAK_IF_NIL(marginPrefsCmdData)
		marginPrefsCmdData->Set(UIDRef(nil, kInvalidUID), // for global workspace, leave empty
								inside, 
								top, 
								outside, 
								bottom);

		// process the command
		status = CmdUtils::ProcessCommand(setMarginPrefsCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)


		// [Step 3b: Set workspace column and gutter preferences data]
		// get the current column prefs (for inspection)
        InterfacePtr<IColumnPrefs> columnPrefs(workspace, IID_ICOLUMNPREFERENCES);
		ASSERT_BREAK_IF_NIL(columnPrefs)
#ifdef DEBUG
		// examine columns (debug only)
		const bool16 currDirection = columnPrefs->GetColumnOrientation_2() == IColumns::kTraditionalCJKColumnOrientation;
		const PMReal currGutter = columnPrefs->GetGutter();
		const int32 currNumColumns = columnPrefs->GetNumColumns();
#endif

		// create the SetColumnPrefsCmd
		InterfacePtr<ICommand> setColumnPrefsCmd(CmdUtils::CreateCommand(kSetColumnPrefsCmdBoss));
		ASSERT_BREAK_IF_NIL(setColumnPrefsCmd)

		// set the column prefs data
		InterfacePtr<IColumnPrefsCmdData> columnPrefsCmdData(setColumnPrefsCmd, IID_ICOLUMNPREFSCMDDATA);
        columnPrefsCmdData->SetColumnPrefsCmdData( UIDRef(nil, kInvalidUID), // for global workspace, leave empty
								parameters.fNumColumns, 
								parameters.fColumnGapWidth,
								parameters.fVertical ? IColumns::kTraditionalCJKColumnOrientation : IColumns::kRomanColumnOrientation); // kTrue = vertical

		// process the command
		status = CmdUtils::ProcessCommand(setColumnPrefsCmd);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

	} while (false);
	return status;
}

/* GetFirstSelectedPageOrGlobalWorkspace
*/
UIDRef SnpModifyLayoutGrid::GetFirstSelectedPageOrGlobalWorkspace(IActiveContext* activeContext)
{
	UIDRef selectedItem(nil, kInvalidUID);

	do {
		if (activeContext == nil)
		{
			break;
		}
		// get the current context view
		IControlView* view = activeContext->GetContextView();
		if (view == nil) 
		{
			// there's no front layout, so get the global workspace from the context
			IWorkspace* workspace = activeContext->GetContextWorkspace();
			ASSERT(workspace);
			selectedItem = UIDRef(::GetDataBase(workspace), ::GetUID(workspace));
			break; // out of do-while, we got what we needed
		}
		// get the current context document, so we can get the database
		IDocument* doc = activeContext->GetContextDocument();
		ASSERT(doc);
		if (doc == nil)
		{
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
		// that we didn't get any UIDRefs - this is a rare case and shouldn't happen, 
		// but even if it did, GetParameters() will catch it and report an error. 

	} while (false);

	ASSERT(selectedItem.ExistsInDB());
	return selectedItem;
}

/* GetParameters
	NOTE: Experiment by changing some of the hardcoded parameters and see what happens!
*/
const ErrorCode SnpModifyLayoutGrid::GetParameters(IDataBase* db, 
												   SnpModLayoutGridParameters& params)
{
	ErrorCode status = kCancel;
	do {
		// check input conditions
		ASSERT_BREAK_IF_NIL(db)
		
		// see if our database is a document, and pick which preferences you want
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<ITextAttributes> defaultTextAttributes(nil);
		if (doc != nil)
			defaultTextAttributes.reset((ITextAttributes*)::QueryPreferences(ITextAttributes::kDefaultIID, doc));
		else
			defaultTextAttributes.reset((ITextAttributes*)::QuerySessionPreferences(ITextAttributes::kDefaultIID));

	    /* set up the defaults
		*/
		
		/* ICJKLayoutGridData settings */
		params.fStartingPoint = ICJKLayoutGridData::kTopInside; // top outside (depends on binding direction)
		params.fModifyMasterPage = kTrue; // modifies the master page layout grid.
		
		/* layout related data */
        params.fVertical = kTrue; // default (TO BE SET FROM PARAMS)
		params.fNumCharsPerLine = 20; // per column // default (TO BE SET FROM PARAMS)
		params.fNumLines = 40; // default (TO BE SET FROM PARAMS)
		params.fNumColumns = 4; // default (TO BE SET FROM PARAMS)
		params.fColumnGapWidth = 12.0; // Points // default (TO BE SET FROM PARAMS)
		
		// the margins (will be overridden in CalculateMargins())
		params.fMarginLeft = 48.5; // Points 
		params.fMarginTop = 58.0; // Points
		params.fMarginRight = 48.5; // Points
		params.fMarginBottom = 58.0; // Points
		
        /* ICJKGridData settings - copy from workspace defaults if not set right */
		// font settings are copied from global workspace
        if (defaultTextAttributes == nil) 
		{
			ASSERT_FAIL("Could not get ITextAttributes from session!");
			break;
		}
		// get default font UID from workspace
        InterfacePtr<ITextAttrUID> textAttrUID((ITextAttrUID*)defaultTextAttributes->QueryByClassID(kTextAttrFontUIDBoss, ITextAttrUID::kDefaultIID));
		if (textAttrUID == nil) 
		{
			ASSERT_FAIL("Could not get ITextAttrUID from default text attributes!");
			break;
		}
		params.fFontUID = textAttrUID->Get();
		if (params.fFontUID == kInvalidUID)
		{
			ASSERT_FAIL("Could not get the UID for the font!");
			break;
		}
		// get default font style from workspace
		InterfacePtr<ITextAttrFont> textAttrFont((ITextAttrFont*)defaultTextAttributes->QueryByClassID(kTextAttrFontStyleBoss, ITextAttrFont::kDefaultIID));
		if (textAttrFont == nil) 
		{	
			ASSERT_FAIL("Could not get ITextAttrFont from default text attributes!");
			break;
		}
		params.fFontStyle = textAttrFont->GetFontName(); // font style 
		if (params.fFontStyle.empty())
		{
			// workspace ITextAttrFont not initialized - so get the style name from the IPMFont
			IDataBase* db = ::GetDataBase(defaultTextAttributes);
			InterfacePtr<IFontFamily> fontGroup(db, params.fFontUID, UseDefaultIID());
			ASSERT(fontGroup);
			InterfacePtr<IPMFont> font(fontGroup->QueryFace(""));
			ASSERT(font);
			font->AppendStyleName(params.fFontStyle);
		}
		if (params.fFontStyle.empty())
		{
			ASSERT_FAIL("Could not get the font style name!");
			break;
		}

		// other text parameters
		params.fTextSize = 8.0; // Points // default (TO BE SET FROM PARAMS)
		params.fCharAki = 0.0; // Points
		params.fLineAki = 5.0; // Points
		params.fHScale = 1.0;	// (0..1)
		params.fVScale = 1.0; 	// (0..1)
		params.fAlignment = ICompositionStyle::kTextAlignCenter;
		params.fGridAlignment = Text::kGAEmCenter;
		params.fCharacterHang = IDrawingStyle::kHangEmCenter;
	

		// Now, get the parameters from the SnipRunParameterUtils
		Utils<ISnipRunParameterUtils> parameterUtils;

		/* NOTE: 
		Parameters are in the following order:
		(0) numCharsPerLine	(1 - inf)
		(1) numLines (1 - inf) 
		(2) numColumns (1 - inf)
		(3) gutterWidth (mm, 0.0 - inf)
		(4) textSize (Q = 0.25mm, 1.0 - inf)
		(5) orientation (V or H)
		
		Some of the parameters are hardcoded here so that the user doesn't have to 
		set up all of the parameters. */
		
		// parameter 0: numCharsPerLine
		int32 numCharsPerLine = parameterUtils->GetInt32("How many characters per line?", 20, 1, kMaxInt32);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		params.fNumCharsPerLine = numCharsPerLine;
		

		// parameter 1: numLines
		int32 numLines = parameterUtils->GetInt32("How many lines?", 40, 1, kMaxInt32);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		params.fNumLines = numLines;


		// parameter 2: numColumns
		int32 numColumns = parameterUtils->GetInt32("How many columns?", 4, 1, kMaxInt32);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		params.fNumColumns = numColumns;

		// parameter 3: columnGapWidth
		PMReal columnGapWidth = parameterUtils->GetPMReal("Width of column gutter? (Units=mm)", 5.0, 0.0, 1000.0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		// in units of "mm", so we need to convert to points
		params.fColumnGapWidth = this->ConvertMillimetersToPoint(columnGapWidth);
		
		
		// parameter 4: textSize
		PMReal textSize = parameterUtils->GetPMReal("Size of text? (Units=Q)", 11.0, 1.0, 1000.0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		// in units of "Q", so we need to convert to points
		params.fTextSize = this->ConvertQToPoint(textSize);


		// parameter 5: orientation
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back("Horizontal"); // 0
		choices.push_back("Vertical"); // 1 (default)
		
		ITextOptions::WritingDirection orientation = 
			(ITextOptions::WritingDirection)parameterUtils->GetChoice("Layout grid orientation?", choices, ITextOptions::kVertical);
		if (parameterUtils->WasDialogCancelled()) 
		{
			status = kCancel;
			break;
		}
		params.fVertical = (orientation == ITextOptions::kVertical) ? kTrue : kFalse;
	
		// calculate okuri values
		if (params.fVertical == kTrue)
		{
			params.fCharOkuri = params.fTextSize * params.fVScale + params.fCharAki;
			params.fLineOkuri = params.fTextSize * params.fHScale + params.fLineAki;
		}
		else
		{
			params.fCharOkuri = params.fTextSize * params.fHScale + params.fCharAki;
			params.fLineOkuri = params.fTextSize * params.fVScale + params.fLineAki;
		}
		status = kSuccess;
	} while (false);
    return status;
}

/* ConvertMillimetersToPoint (static)
*/
PMReal SnpModifyLayoutGrid::ConvertMillimetersToPoint(const PMReal& val)
{
	InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IUnitOfMeasure> currentUnit(ms->QueryUnitOfMeasure(ms->Location(kMillimetersBoss)));
	
	return currentUnit->UnitsToPoints(val);
}

/* ConvertQToPoint (static)
*/
PMReal SnpModifyLayoutGrid::ConvertQToPoint(const PMReal& val)
{
	InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IUnitOfMeasure> currentUnit(ms->QueryUnitOfMeasure(ms->Location(kQBoss)));
	
	return currentUnit->UnitsToPoints(val);
}

/* ConvertHaToPoint (static)
*/
PMReal SnpModifyLayoutGrid::ConvertHaToPoint(const PMReal &val)
{
	InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IUnitOfMeasure> currentUnit(ms->QueryUnitOfMeasure(ms->Location(kHaBoss)));
	
	return currentUnit->UnitsToPoints(val);
}

/* SetupFilteredCJKGridData
*/
void SnpModifyLayoutGrid::SetupFilteredCJKGridData(const SnpModLayoutGridParameters& parameters, 
													ICJKGridData* sourceGridData,
													IFilteredCJKGridCmdData* destGridData)
{
	do {
		ASSERT_BREAK_IF_NIL(sourceGridData) 
		ASSERT_BREAK_IF_NIL(destGridData) 

#ifdef DEBUG
		// examine source grid data for debugging...
		const IDrawingStyle::CharacterHang sourceCharacterHang = sourceGridData->GetCharacterHang();
		const PMReal sourceCharAki = sourceGridData->GetCharAki();
		const PMReal sourceCharOkuri = sourceGridData->GetCharOkuri(parameters.fVertical);
		const PMString sourceFontStyleName = sourceGridData->GetFontStyleName();
		const UID sourceFontUID = sourceGridData->GetFontUID();
		const Text::GridAlignmentMetric sourceGridAlignment = sourceGridData->GetGridAlignment();
		const PMReal sourceHScale = sourceGridData->GetHScale();
		const PMReal sourceLineAki = sourceGridData->GetLineAki();
		const PMReal sourceLineOkuri = sourceGridData->GetLineOkuri(parameters.fVertical);
		const ICompositionStyle::TextAlignment sourceTextAlignment = sourceGridData->GetTextAlignment();
		const PMReal sourceTextSize = sourceGridData->GetTextSize();
		const PMReal sourceVScale = sourceGridData->GetVScale();
#endif

		// Copy from original CJKGridData to own CJKGridData as part of the command settings.
		destGridData->CopyFrom(sourceGridData);
		destGridData->SetCharAki(parameters.fCharAki);
		destGridData->SetCharacterHang(parameters.fCharacterHang);
		destGridData->SetFontStyleName(parameters.fFontStyle);
		destGridData->SetFontUID(parameters.fFontUID);
		destGridData->SetGridAlignment(parameters.fGridAlignment);
		destGridData->SetHScale(parameters.fHScale);
		destGridData->SetLineAki(parameters.fLineAki);
		destGridData->SetTextAlignment(parameters.fAlignment);
		destGridData->SetTextSize(parameters.fTextSize);
		destGridData->SetVScale(parameters.fVScale);
        
		// Since we are changing all fields, set them all to "valid" - which means that
		// the command will use these fields as valid command data.
		destGridData->SetFieldValid(IFilteredCJKGridCmdData::kAllValid, kTrue);
		
		// See enum IFilteredCJKGridCmdData::NamedGridFieldIDs for other field IDs.
		// 
		// Also, see CJKGridID.h for kMixedValue, which is a special grid data value 
		// used by fields that are not supposed to be set.
	} while (false);
}

/* SetupLayoutGridDefaults
*/
void SnpModifyLayoutGrid::SetupLayoutGridDefaults(const SnpModLayoutGridParameters& parameters, 
												   ICJKLayoutGridDefaults* sourceCJKLayoutGridDefaults, 
												   ICJKLayoutGridDefaults* destCJKLayoutGridDefaults)
{
	do {
		ASSERT_BREAK_IF_NIL(sourceCJKLayoutGridDefaults) 
		ASSERT_BREAK_IF_NIL(destCJKLayoutGridDefaults) 
#ifdef DEBUG
		// examine source layout grid defaults for debugging...
        const IDrawingStyle::CharacterHang sourceCharacterHang = sourceCJKLayoutGridDefaults->GetCharacterHang();
		const PMReal sourceCharAki = sourceCJKLayoutGridDefaults->GetCharAki();
		const PMReal sourceCharOkuri = sourceCJKLayoutGridDefaults->GetCharOkuri(parameters.fVertical);
		const PMString sourceFontStyleName = sourceCJKLayoutGridDefaults->GetFontStyleName();
		const UID sourceFontUID = sourceCJKLayoutGridDefaults->GetFontUID();
		const Text::GridAlignmentMetric sourceGridAlignment = sourceCJKLayoutGridDefaults->GetGridAlignment();
		const ICJKLayoutGridData::GridStartingPoint sourceGridStartingPoint = sourceCJKLayoutGridDefaults->GetGridStartingPoint();
		const PMReal sourceHScale = sourceCJKLayoutGridDefaults->GetHScale();
		const PMReal sourceLineAki = sourceCJKLayoutGridDefaults->GetLineAki();
		const PMReal sourceLineOkuri = sourceCJKLayoutGridDefaults->GetLineOkuri(parameters.fVertical);
		const ICompositionStyle::TextAlignment sourceTextAlignment = sourceCJKLayoutGridDefaults->GetTextAlignment();
		const PMReal sourceTextSize = sourceCJKLayoutGridDefaults->GetTextSize();
		const PMReal sourceVScale = sourceCJKLayoutGridDefaults->GetVScale();
#endif
		//  set values here
		destCJKLayoutGridDefaults->CopyFrom(sourceCJKLayoutGridDefaults, kFalse);
		destCJKLayoutGridDefaults->SetCharacterHang(parameters.fCharacterHang);
		destCJKLayoutGridDefaults->SetCharAki(parameters.fCharAki);
		destCJKLayoutGridDefaults->SetFontStyleName(parameters.fFontStyle);
		destCJKLayoutGridDefaults->SetFontUID(parameters.fFontUID);
		destCJKLayoutGridDefaults->SetGridAlignment(parameters.fGridAlignment);
		destCJKLayoutGridDefaults->SetGridStartingPoint(parameters.fStartingPoint);
		destCJKLayoutGridDefaults->SetHScale(parameters.fHScale);
		destCJKLayoutGridDefaults->SetLineAki(parameters.fLineAki);
		destCJKLayoutGridDefaults->SetTextAlignment(parameters.fAlignment);
		destCJKLayoutGridDefaults->SetTextSize(parameters.fTextSize);
		destCJKLayoutGridDefaults->SetVScale(parameters.fVScale);
	} while (false);
}


/* CalculateColumns
*/
ErrorCode SnpModifyLayoutGrid::CalculateColumns(const SnpModLayoutGridParameters& parameters, 
												 const PMPageSize& pageRect, 
												 PMRealList& pageCols)
{
	ErrorCode status = kFailure;
	do {
		// Get the column and the gutter value
		bool16	isCustom = kFalse; 
		bool16 	isVertical = parameters.fVertical;
		int32	numCols = parameters.fNumColumns;
		int32	numCharsPerLine = parameters.fNumCharsPerLine;
		PMReal	gutter = parameters.fColumnGapWidth;
		// these are calculated
		PMReal	columnStart, columnWidth;
	
		K2Vector<int32> charsPerLines;
		charsPerLines.clear();
		for (int32 col = 0; col < numCols; col++)
		{
			charsPerLines.push_back(numCharsPerLine);
		}
	
		// NOTE: Okuri values are calculated in GetParameters.
	
		// Column positions are relative to the top margin (CJK, direction), or left margin.
		pageCols.clear();
		columnStart = 0;	// The top or left edge. Start at zero
		pageCols.push_back(columnStart);
	
		// NOTE: Regardless of orientation, columns are always calculated with
		//  respect to char okuri values. 
		for (int32 j = 0; j < numCols - 1; j++)
		{
			columnWidth = (parameters.fCharOkuri * charsPerLines[j]) - parameters.fCharAki;
	
			columnStart += columnWidth;
			pageCols.push_back(columnStart);
			columnStart += gutter;
			pageCols.push_back(columnStart);
		}
		if (numCols > 0)	// The bottom or right edge.
		{
			columnWidth = (parameters.fCharOkuri * charsPerLines[numCols - 1]) - parameters.fCharAki;
	
			columnStart += columnWidth;
			pageCols.push_back(columnStart);
		}

		// if the calculations are correct, there should be numCols * 2 entries in the pageCols list.
		ASSERT(pageCols.size() == numCols * 2);

		// roughly verify that the column settings will work
		if ((parameters.fVertical == kTrue && columnStart < pageRect.DesignHeight()) ||
			(parameters.fVertical == kFalse && columnStart < pageRect.DesignWidth()))
		{
			status = kSuccess;
		}
		else
		{
			SNIPLOG("The column settings are too big for the page!");
		}
	} while (false);
	return status;
}

/* CalculateMargins
*/
ErrorCode SnpModifyLayoutGrid::CalculateMargins(const SnpModLayoutGridParameters& parameters, 
												 IDataBase* db, 
												 const PMPageSize& pageRect, 
												 const PMReal totalColumnSize,
                                                 PMReal& inside, 
												 PMReal& top, 
												 PMReal& outside, 
												 PMReal& bottom,
												 IGeometry* pageGeometry /*=nil*/)
{
	ErrorCode status = kFailure;

	/* based on text area and alignment, set the margins selectively just like the UI
	*/
	// NOTE: for margin settings, certain settings are calculated based on fGridStartingPoint
	do {
		ASSERT_BREAK_IF_NIL(db)
		
		// get page geometry PMRect.
		PMReal pageWidth = pageRect.DesignWidth();
		PMReal pageHeight = pageRect.DesignHeight();
		
		// get page binding direction
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		InterfacePtr<IPageSetupPrefs> pageSetupPrefs(nil);
		if (doc)
			pageSetupPrefs.reset((IPageSetupPrefs*)::QueryPreferences(IID_IPAGEPREFERENCES, doc));
		else
			pageSetupPrefs.reset((IPageSetupPrefs*)::QuerySessionPreferences(IID_IPAGEPREFERENCES));
			
		ASSERT_BREAK_IF_NIL(pageSetupPrefs)
		// for values, see ILayoutUtils.h -- enum DocPageBinding
		int32 pageBindingDirection = pageSetupPrefs->GetPageBindingPref();

		// figure out if this is a left page or not
		bool16 isLeftPage = kFalse;

		if (doc != nil) 
		{
			// get the page index of this page.
			int32 pageIndex = -1; 
			ASSERT(pageGeometry);
			UID pageUID = ::GetUID(pageGeometry);
			ASSERT(pageUID != kInvalidUID);
			
			InterfacePtr<IPageList> pageList(doc, UseDefaultIID());
			ASSERT_BREAK_IF_NIL(pageList)
			pageIndex = pageList->GetPageIndex(pageUID);
			if (pageIndex < 0) 
			{
				// couldn't find the page in the page list - this might be a master page
				InterfacePtr<IMasterPage> masterPage(pageGeometry, IID_IMASTERPAGE);
				ASSERT_BREAK_IF_NIL(masterPage)
				pageIndex = (int32)masterPage->GetMasterSpreadPageIndex();
			}
			ASSERT(pageIndex >= 0);
			
			
			// figure out if this page is a "right" or "left" page.
			// kLeftToRightBinding: even page indices=right page, odd page indices=left page
			// kRightToLeftBinding: even page indices=left page, odd page indices=right page
	
			if  (((pageIndex % 2 == 0) && (pageBindingDirection == kRightToLeftBinding)) || 
				 ((pageIndex % 2 == 1) && (pageBindingDirection == kLeftToRightBinding)))
			{
				// WARNING! this may not be fool-proof if there are more than 2 pages on a spread.
				isLeftPage = kTrue;
			}
		}
		else
		{
			// global workspaces don't have multiple page setups.
			// So choose left page only if binding is right-to-left.
			isLeftPage = (pageBindingDirection == kRightToLeftBinding);
		}

		    

        // determine the text area width and height...
        PMReal textAreaHeight = 0;
		PMReal textAreaWidth = 0;
		if (parameters.fVertical == kTrue) 
		{
			/* Vertical orientation means that the columns will be aligned like this:
			+--------+
			|        |
			+--------+
			+--------+
			|        |
			+--------+
			So the textAreaHeight equals "totalColumnSize, and 
			textAreaWidth is determined by the line okuri multiplied by the number of lines in 
			the column, less one line aki width. 
			*/
			textAreaHeight = totalColumnSize;
			textAreaWidth = parameters.fLineOkuri * (parameters.fNumLines) - parameters.fLineAki;
		}
		else
		{
			/* Horizontal orientation means that the columns will be aligned like this:
			+---++---+
			|   ||   |
			|   ||   |
			|   ||   |
			|   ||   |
			+---++---+
			So the textAreaWidth equals "totalColumnSize", and 
			textAreaHeight is determined by the line okuri multiplied by the number of lines in 
			the column, less one line aki width. 
			*/
			textAreaWidth = totalColumnSize;
			textAreaHeight = parameters.fLineOkuri * (parameters.fNumLines) - parameters.fLineAki;
		}

		// calculate the margins appropriately
		ICJKLayoutGridData::GridStartingPoint startingPoint = parameters.fStartingPoint;

		switch (startingPoint) 
		{
		case ICJKLayoutGridData::kBottomInside:
			// use bottom and inside, calculate top and outside.
			{
				bottom = parameters.fMarginBottom;
				top = pageHeight - textAreaHeight - bottom;
				if (isLeftPage == kTrue) 
				{
					inside = parameters.fMarginRight;
					outside = pageWidth - textAreaWidth - inside;
				}
				else
				{
					inside = parameters.fMarginLeft;
					outside = pageWidth - textAreaWidth - inside;
				}
			}
			break;
		
		case ICJKLayoutGridData::kBottomOutside:
			// use bottom and outside, calculate top and inside.
			{
				bottom = parameters.fMarginBottom;
				top = pageHeight - textAreaHeight - bottom;
				if (isLeftPage == kTrue) 
				{
					outside = parameters.fMarginLeft;
					inside = pageWidth - textAreaWidth - outside;
				}
				else
				{
					outside = parameters.fMarginRight;
					inside = pageWidth - textAreaWidth - outside;
				}
			}
			break;

		case ICJKLayoutGridData::kCenter:
			// calculate top, inside, bottom, and outside.
			{
				bottom = (pageHeight - textAreaHeight) / 2;
				top = bottom;
				outside = (pageWidth - textAreaWidth) / 2;
				inside = outside;
			}
			break;

		case ICJKLayoutGridData::kCenterHorizontal:
			// use top, calculate inside, bottom, and outside.
			{
				top = parameters.fMarginTop;
				bottom = pageHeight - textAreaHeight - top;
				outside = (pageWidth - textAreaWidth) / 2;
				inside = outside;
			}
			break;

		case ICJKLayoutGridData::kCenterVertical:
			// use outside, calculate top, bottom, and inside.
			{
				bottom = (pageHeight - textAreaHeight) / 2;
				top = bottom;
				if (isLeftPage == kTrue) 
				{
					outside = parameters.fMarginLeft;
					inside = pageWidth - textAreaWidth - outside;
				}
				else
				{
					outside = parameters.fMarginRight;
					inside = pageWidth - textAreaWidth - outside;
				}
			}
			break;

		case ICJKLayoutGridData::kTopInside:
			// use top and inside, calculate bottom and outside.
			{
				top = parameters.fMarginTop;
				bottom = pageHeight - textAreaHeight - top;
				if (isLeftPage == kTrue) 
				{
					inside = parameters.fMarginRight;
					outside = pageWidth - textAreaWidth - inside;
				}
				else
				{
					inside = parameters.fMarginLeft;
					outside = pageWidth - textAreaWidth - inside;
				}
			}
			break;

		default:
			ASSERT_FAIL("Benign: It seems like the starting point wasn't set up properly. Using TopOutside.");
			//fall through
		case ICJKLayoutGridData::kTopOutside:
			// use top and outside, calculate bottom and inside.
			{
				top = parameters.fMarginTop;
				bottom = pageHeight - textAreaHeight - top;
				if (isLeftPage == kTrue) 
				{
					outside = parameters.fMarginLeft;
					inside = pageWidth - textAreaWidth - outside;
				}
				else
				{
					outside = parameters.fMarginRight;
					inside = pageWidth - textAreaWidth - outside;
				}
			}
			break;
        }

		if(top > 0 && bottom > 0 && inside > 0 && outside > 0)
		{
            status = kSuccess;
		}
		else
		{
			SNIPLOG("You ended up with the margins {top, bottom, inside, outside} = (%f, %f, %f, %f). Adjust some parameters.",
					::ToDouble(top), ::ToDouble(bottom), ::ToDouble(inside), ::ToDouble(outside));
		}
	} while (false);
	return status;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerModifyLayoutGrid : public SnpRunnable
{

public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerModifyLayoutGrid(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerModifyLayoutGrid(void);

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
_SnpRunnerModifyLayoutGrid::_SnpRunnerModifyLayoutGrid(void) : SnpRunnable("ModifyLayoutGrid")
{
	// what this snippet does.
	this->SetDescription("Modifies the layout grid of a page or the layout grid defaults in the global workspace.");
	// NOTE: If the chosen parameters don't fit on a page, then you will see an error message on the SNIPLOG.

	// the preconditions required by the snippet
	this->SetPreconditions("Must be running the Japanese feature set.  Optionally, to modify layout grid on a page, that page must be open as the front layout.");

	// the categories for this snippet
	this->SetCategories("sdk_snippet, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerModifyLayoutGrid::~_SnpRunnerModifyLayoutGrid(void)
{
	// does nothing.
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerModifyLayoutGrid::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		if (runnableContext == nil) 
		{
			break;
		}
		
		// if we got here, we can run this snippet.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerModifyLayoutGrid::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do
	{
		SnpModifyLayoutGrid instance;

		// get the first selected page or global workspace
		IActiveContext* activeContext = runnableContext->GetActiveContext();
		UIDRef targetUIDRef = instance.GetFirstSelectedPageOrGlobalWorkspace(activeContext);
		if (targetUIDRef.ExistsInDB() == kFalse) 
		{
			SNIPLOG("Could not get a page or global workspace!");
			break;
		}
		
		// intrepret parameters into a structure
		SnpModLayoutGridParameters parameters;
		status = instance.GetParameters(targetUIDRef.GetDataBase(), parameters);
		ASSERT_BREAK_IF_UNSUCCESSFUL(status)

		// modify the layout grid on the page according to the given parameters
        status = instance.ModifyLayoutGrid(targetUIDRef, parameters);

	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerModifyLayoutGrid::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS) == kFalse) {
		// Only load under the Japanese language feature set.
		// NOTE: Layout grid calculations done in this code snippet require the Q and Ha measurement units, 
		// so that they are similar to what the user sets in the Layout Grid Settings dialogs.
		// The Q and Ha measurement units are available only on the Japanese feature set. 
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
static _SnpRunnerModifyLayoutGrid instance_SnpRunnerModifyLayoutGrid;
DEFINE_SNIPPET(_SnpRunnerModifyLayoutGrid) 	

//End, SnpModifyLayoutGrid.cpp

