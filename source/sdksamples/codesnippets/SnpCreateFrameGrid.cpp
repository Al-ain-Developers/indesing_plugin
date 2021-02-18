//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateFrameGrid.cpp $
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

// General Includes
#include "CJKGridID.h"
#include "CmdUtils.h"
#include "LocaleSetting.h"
#include "PersistUtils.h"
#include "PreferenceUtils.h"
#include "SplineID.h"
#include "TextID.h"
#include "TransformUtils.h"
#include "Utils.h"

// Interface includes
#include "IBoolData.h"
#include "ICJKGridData.h"
#include "ICJKGridUtils.h"
#include "ICommand.h"
#include "ICommandSequence.h"
#include "IControlView.h"
#include "ICreateMCFrameData.h"
#include "IDocument.h"
#include "IFilteredCJKGridCmdData.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "ILayoutControlData.h"
#include "ILayoutUtils.h"
#include "IMultiColumnItemData.h"
#include "INewPageItemCmdData.h"
#include "IRangeData.h"
#include "IStoryOptions.h"
#include "ITextModel.h"
#include "ITextModelCmds.h" // *** for InsertCmd() *** New in 3.0
#include "ITextOptions.h"
#include "IBaselineFrameGridData.h"
#include "ITextFrameFacade.h"
#include "ITextColumnData.h"

// General includes:
#include "Utils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	How to create a frame grid (Japanese feature set required).

	TODO: please use SequencePtr instead of ICommandSequence* 

	@ingroup sdk_snippet
	@see kCreateMultiColumnItemCmdBoss
	@see kActivateCJKGridCmdBoss
	@see kApplyCJKGridFormatCmdBoss
	@see ICJKGridData
 */
class SnpCreateFrameGrid 
{

public:
	/** Constructor.
	*/
	SnpCreateFrameGrid() {}

	/** Destructor.
		*/
	virtual			~SnpCreateFrameGrid() {}

	/**	Shows how to create a frame grid. 
	* 	The actual size of the frame will be determined by:
	* 	(1) the number of characters per line
	* 	(2) the number of lines
	* 	(3) the number of columns
	* 	(4) the space in between columns (in points)
	* 	(5) the settings of the layout grid of the page.
	* 	
	* 	@param outFrameUIDRef (out) The UIDRef of the created frame grid. 
	* 	@param left (in) The left coordinate of the frame grid to be created.
	* 	@param top (in) The top coordinate of the frame grid to be created.
	* 	@param numCharsPerLine (in) The number of characters per line in each
	* 			column of the frame grid.
	* 	@param numLines (in) The number of lines in each column of the frame grid.
	* 	@param numColumns (in) The number of columns in the frame grid.
	* 	@param columnGutterWidth (in) The gap between columns (in Points).
	* 			If there is only 1 column, this value is ignored.
	* 	@param verticalFrame (in) Set to kTrue to make the frame grid vertical, 
	* 			kFalse to make it horizontal.
	* 	@param textToInsert (in) Specify the ptr to the WideString to insert.
	* 			Set to nil if no text 
	* 			needs to be inserted.
	*	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode CreateFrameGrid(ILayoutControlData* layoutControlData,
						UIDRef& outFrameUIDRef,
							const PMReal left,
							const PMReal top,
							const int32 numCharsPerLine, 
							const int32 numLines, 
							const int32 numColumns,
							const PMReal columnGutterWidth,
							const bool16 verticalFrame = kTrue,
							WideString* textToInsert = nil);

	private:
	/** Internal version of CreateFrameGrid.
	* 	@see SnpCreateFrameGrid::CreateFrameGrid()
	*/
	ErrorCode PrivateCreateFrameGrid(ILayoutControlData* layoutControlData,
								UIDRef& outFrameUIDRef,
									const PMReal left,
									const PMReal top,
									const int32 numCharsPerLine, 
									const int32 numLines, 
									const int32 numColumns,
									const PMReal columnGutterWidth,
									const bool16 verticalFrame = kTrue,
									WideString* textToInsert = nil);

	/** Calculates the frame grid size given grid data and story orientation.
	* 	@param gridData (in) ICJKGridData from the appropriate workspace.
	* 		The grid data items from this interface are used to calculate dimensions.
	* 	@param textOptions (in) ITextOtions from the appropriate workspace.
	* 		The inset values are examined to adjust the width and height.
	* 	@param verticalFrame (in) Set to kTrue if the frame orientation is vertical, 
	* 		kFalse otherwise. 
	* 	@param numCharsPerLine (in) The number of characters per line in each
	* 			column of the frame grid.
	* 	@param numLines (in) The number of lines in each column of the frame grid.
	* 	@param numColumns (in) The number of columns in the frame grid.
	* 	@param columnGutterWidth (in) The gap between columns (in Points).
	* 			If there is only 1 column, this value is ignored.
	* 	@param width (out) The calculated width of the frame to create.
	* 		If an error occurs inside, this will return -1.0.
	* 	@param height (out) The calculated height of the frame to create.
	* 		If an error occurs inside, this will return -1.0.
	*/
	void CalculateFrameGridSize(ICJKGridData* gridData, 
							ITextOptions* textOptions,
							const bool16 verticalFrame, 
							const int32 numCharsPerLine, 
							const int32 numLines,
							const int32 numColumns,
							const PMReal columnGutterWidth,
							PMReal& width, 
							PMReal& height);
		
};






/* CreateFrameGrid - with UIDRef
*/
ErrorCode SnpCreateFrameGrid::CreateFrameGrid(ILayoutControlData* layoutControlData,
											   UIDRef& outFrameUIDRef,
											   const PMReal left,
											   const PMReal top,
											   const int32 numCharsPerLine, 
											   const int32 numLines, 
											   const int32 numColumns,
											   const PMReal columnGutterWidth,
											   const bool16 verticalFrame /*= kTrue*/, 
											   WideString* textToInsert /*= nil*/)
{
	return this->PrivateCreateFrameGrid(layoutControlData, outFrameUIDRef, left, top,
										numCharsPerLine, numLines, numColumns,
										columnGutterWidth, verticalFrame,
										textToInsert);
}


/* PrivateCreateFrameGrid
*/
ErrorCode SnpCreateFrameGrid::PrivateCreateFrameGrid(ILayoutControlData* layout,
													  UIDRef& outFrameUIDRef,
													  const PMReal left,
													  const PMReal top,
													  const int32 numCharsPerLine, 
													  const int32 numLines, 
													  const int32 numColumns,
													  const PMReal columnGutterWidth,
													  const bool16 verticalFrame /* = kTrue */,
													  WideString* textToInsert /*= nil*/)	
{
	ErrorCode status = kFailure;
	ICommandSequence* seq = nil;
	
	do {
		// check to make sure we have a front layout
		ASSERT(layout);
		if (layout == nil) 
		{
			SNIPLOG("There is no front layout - please open a document first.");
			break;
		}

		// find the active layer
		InterfacePtr<IHierarchy> layerHier(layout->QueryActiveLayer());
		ASSERT(layerHier);
		if (layerHier == nil) break;
		
		// Get the UIDRef of the layer
		UIDRef layerRef(::GetUIDRef(layerHier));

		// Get the bounding box for the current page
		IDataBase* db = layerRef.GetDataBase();
		ASSERT(db);
		
		// Get the document
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
		ASSERT(doc);

		// Get the text options on the document workspace
		InterfacePtr<ITextOptions> textOptPrefs((ITextOptions*)::QueryPreferences(ITextOptions::kDefaultIID, doc));
		ASSERT(textOptPrefs);
		if (textOptPrefs == nil) break;
		
		// Get the page and page geometry
		UIDRef pageUIDRef(db,layout->GetPage());
		InterfacePtr<IGeometry> pageGeometry(pageUIDRef, UseDefaultIID());
		ASSERT(pageGeometry);
		if (pageGeometry == nil) break;
		
		// get the layout grid data from the page
		InterfacePtr<ICJKGridData> layoutGridData((ICJKGridData*)Utils<ICJKGridUtils>()->QueryLayoutGrid(pageGeometry, ICJKGridData::kDefaultIID));
		ASSERT(layoutGridData);
		if (layoutGridData == nil) break;


		// start a command sequence and set its name so we can undo all of this.
		seq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		ASSERT(seq);
		if (seq == nil) break;
		seq->SetName(PMString("CreateFrameGrid", PMString::kEncodingASCII));
		
		// calculate the frame grid size based on criterion.
		PMReal width = 0.0;
		PMReal height = 0.0;
		// NOTE: This takes into account any text inset.
		this->CalculateFrameGridSize(layoutGridData, 
									 textOptPrefs,
									 verticalFrame, 
									 numCharsPerLine, numLines,
									 numColumns, columnGutterWidth, 
									 width, height);
		if (width <= 0.0 || height <= 0.0) break;
		SNIPLOG("Calculated {w,h} = {%f, %f}", ::ToDouble(width), ::ToDouble(height));
		
		PMReal right = left + width;
		PMReal bottom = top + height;
		SNIPLOG("Calculated inner coordinates {l,t,r,b} = {%f, %f, %f, %f}", 
				::ToDouble(left), ::ToDouble(top), ::ToDouble(right), ::ToDouble(bottom));

		// Here are the coordinates for our frame to be created at. 
		PMPoint startPoint(left, top);	// left, top
		PMPoint endPoint(right, bottom);	// right, bottom	
		// convert them to pasteboard coordinates
		::TransformInnerPointToPasteboard(pageGeometry, &startPoint);
		::TransformInnerPointToPasteboard(pageGeometry, &endPoint);
		SNIPLOG("Calculated pasteboard coordinates {l,t,r,b} = {%f, %f, %f, %f}", 
				::ToDouble(startPoint.X()), ::ToDouble(startPoint.Y()), ::ToDouble(endPoint.X()), ::ToDouble(endPoint.Y()));

		// Create new multi-column text frame
		status = Utils<Facade::ITextFrameFacade>()->CreateTextFrame(layerRef, outFrameUIDRef, PMRect(startPoint, endPoint), kTrue/*noGraphicAttr*/, !verticalFrame, kTrue/*isFrameGrid*/, kTrue/*isLeftToRight*/);
		ASSERT(outFrameUIDRef.GetDataBase() && outFrameUIDRef.GetUID() != kInvalidUID);
		if (outFrameUIDRef.GetDataBase() == nil ||
			outFrameUIDRef.GetUID() == kInvalidUID) break;

		// specify column data for the frame.
		InterfacePtr<ICommand> pifChangeCmd(CmdUtils::CreateCommand(kChangeNumberOfColumnsCmdBoss));
		InterfacePtr<ITextColumnData> cmdColumnData(pifChangeCmd, UseDefaultIID());
		cmdColumnData->SetNumberOfColumns(numColumns);
		cmdColumnData->UseFixedColumnSizing(kFalse);
		cmdColumnData->SetGutterWidth(columnGutterWidth);
		pifChangeCmd->SetItemList(UIDList(outFrameUIDRef));
		status = CmdUtils::ProcessCommand(pifChangeCmd);
		
		// get the story from the newly created text frame
		InterfacePtr<IMultiColumnTextFrame> mcFrame(outFrameUIDRef, UseDefaultIID());
		UIDRef newStoryUIDRef(::GetDataBase(mcFrame), mcFrame->GetTextModelUID());
		ASSERT(newStoryUIDRef.GetUID() != kInvalidUID);
		// Get frame grid activate state from prefs.
		InterfacePtr<IStoryOptions> storyOptPrefs((IStoryOptions*)::QueryPreferences(IStoryOptions::kDefaultIID, doc));
		ASSERT(storyOptPrefs);
		if (storyOptPrefs == nil) break;
		
		// obtain the text model
		InterfacePtr<ITextModel> textModel(newStoryUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if (textModel == nil) break;
		
        // Insert text to story only if we have specified text in the textToInsert parameter
		if (textToInsert != nil) 
		{
			// use ITextModelCmds to create a command *** New in 3.0 ***
			InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
			ASSERT(textModelCmds);
			boost::shared_ptr<WideString> string(new WideString (*textToInsert));
            InterfacePtr<ICommand> insertTextCmd(textModelCmds->InsertCmd(0, string));
			ASSERT(insertTextCmd);
			if (insertTextCmd == nil) break;

			status = CmdUtils::ProcessCommand(insertTextCmd);
			if (status != kSuccess) break;
		}

		// Apply grid format to story
		InterfacePtr<ICommand> applyCJKGridFormatCmd(CmdUtils::CreateCommand(kApplyCJKGridFormatCmdBoss));
		ASSERT(applyCJKGridFormatCmd);
		if (applyCJKGridFormatCmd == nil) break;		

		applyCJKGridFormatCmd->SetItemList(UIDList(textModel));
		InterfacePtr<IRangeData> rangeData(applyCJKGridFormatCmd, UseDefaultIID());
		ASSERT(rangeData);
		if (rangeData == nil) break;
		
		int32 length = textModel->TotalLength();
		rangeData->Set(0, length);

		status = CmdUtils::ProcessCommand(applyCJKGridFormatCmd);
		if (status != kSuccess) break;
		
	} while (false);

	// check on the command sequence
	if (seq != nil)
	{
		if (status != kSuccess)
		{
			ErrorUtils::PMSetGlobalErrorCode(status);
			CmdUtils::EndCommandSequence(seq);
		}
		else
			CmdUtils::EndCommandSequence(seq);
		
		// reset the sequence
		seq = nil;
	}

	return status;
} 

/* CalculateFrameGridSize
*/
void SnpCreateFrameGrid::CalculateFrameGridSize(ICJKGridData* gridData, 
												 ITextOptions* textOptions,
												 const bool16 verticalFrame, 
												 const int32 numCharsPerLine, 
												 const int32 numLines,
												 const int32 numColumns,
												 const PMReal columnGutterWidth,
												 PMReal& width, 
												 PMReal& height)
{
	do {
		if (gridData == nil) 
		{
			width = -1.0;
			height = -1.0;
			break;
		}
		
		PMReal columnWidth = 0.0;
		PMReal columnHeight = 0.0;
		
		PMReal charAki = gridData->GetCharAki();
        PMReal charOkuri = gridData->GetCharOkuri(verticalFrame); 
        PMReal lineAki = gridData->GetLineAki();
		PMReal lineOkuri = gridData->GetLineOkuri(verticalFrame);
		// optional - for reference only
		PMReal textSize = gridData->GetTextSize();
		PMReal vScale = gridData->GetVScale(); // doesn't depend on orientation
		PMReal hScale = gridData->GetHScale(); // doesn't depend on orientation

		/* NOTE: Okuri already takes into account the orientation, 
			h/v scales, text size, and aki, like this:
		if (verticalFrame)
		{
			charOkuri = textSize * vScale + charAki;
			lineOkuri = textSize * hScale + lineAki;
		}
		else
		{
			charOkuri = textSize * hScale + charAki;
			lineOkuri = textSize * vScale + lineAki;
		}
		*/
		
		// calculate the frame grid size based on criterion.
		if (verticalFrame) 
		{
			/* +-------------------+
			 * |                   |
			 * |                   |
			 * +-------------------+
			 * +-------------------+
			 * |                   |
 			 * |                   |
			 * +-------------------+
			 * +-------------------+
			 * |                   |
			 * |                   |
			 * +-------------------+
			 */
			// subtract the *aki since the last line/char doesn't have extra space after it.
			columnWidth = numLines * lineOkuri - lineAki;
			columnHeight = numCharsPerLine * charOkuri - charAki;
			
			// column width is the width of the frame
			width = columnWidth;
			// subtract one gutter since # of gutters = numColumns - 1
			height = columnHeight * numColumns + columnGutterWidth * (numColumns - 1);
		}
		else
		{
			/* +------++------++------+
			 * |      ||      ||      |
			 * |      ||      ||      |
			 * |      ||      ||      |
			 * |      ||      ||      |
			 * |      ||      ||      |
			 * +------++------++------+
			 */
			// subtract the *aki since the last line/char doesn't have extra space after it.
			columnWidth = numCharsPerLine * charOkuri - charAki;
			columnHeight = numLines * lineOkuri - lineAki;
			
			// subtract one gutter since # of gutters = numColumns - 1
			width = columnWidth * numColumns + columnGutterWidth * (numColumns - 1);
			// column height is the height of the frame
			height = columnHeight;
		}

		// add insets to calcuated width and height
		PMReal 	insetLeft = 0.0,
				insetTop = 0.0,
				insetRight = 0.0,
				insetBottom = 0.0;
		textOptions->GetFrameInsets(insetLeft, insetTop, insetRight, insetBottom);
		width += (insetLeft + insetRight);
		height += (insetTop + insetBottom);

	} while (false);
	ASSERT(width > 0.0 && height > 0.0);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------



/** Makes the snippet SnpCreateFrameGrid available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerCreateFrameGrid : public SnpRunnable
{

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerCreateFrameGrid();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateFrameGrid();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		/** Only present this snippet in the framework's UI if the
			language feature set is Japanese and the product is not
			InCopy.
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
_SnpRunnerCreateFrameGrid::_SnpRunnerCreateFrameGrid() : SnpRunnable("CreateFrameGrid")
{
	this->SetDescription("creates a frame grid");
	this->SetPreconditions("front document + Japanese feature set");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerCreateFrameGrid::~_SnpRunnerCreateFrameGrid()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerCreateFrameGrid::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// Require ILayoutControlData.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlData == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerCreateFrameGrid::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpCreateFrameGrid instance;

		// Require ILayoutControlData.
		InterfacePtr<ILayoutControlData> layoutControlData(runnableContext->GetActiveContext()->GetContextView(), UseDefaultIID());
		if (layoutControlData == nil) {
			break;
		}
		
		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		Utils<ISnipRunParameterUtils> parameterUtils;
		PMReal left = parameterUtils->GetPMReal("Left");
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		PMReal top = parameterUtils->GetPMReal("Top");
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		int32 numCharsPerLine = parameterUtils->GetInt32("numCharsPerLine", 10, 1, 100);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		int32 numLines = parameterUtils->GetInt32("numLines", 15, 1, 50);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		int32 numColumns = parameterUtils->GetInt32("numColumns", 2, 1, 10);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		PMReal columnGutterWidth = parameterUtils->GetPMReal("columnGutterWidth",  10, 10, 50);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		K2Vector<PMString> orientationChoices;
		orientationChoices.push_back(PMString("vertical"));
		orientationChoices.push_back(PMString("horizontal"));
		int32 orientation  = parameterUtils->GetChoice("Frame orientation?", orientationChoices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		bool16 verticalFrame = kTrue;
		if (orientation == 1) {
			verticalFrame = kFalse;
		}
		

		UIDRef outFrameUIDRef;

		// this is the end of the message in our scrolling about box...
		PMString aNiceMessage("ScrollingAboutboxTextTrailer", PMString::kTranslateDuringCall);
		WideString* textToInsert = new WideString(aNiceMessage);
		ASSERT(textToInsert);
		if (textToInsert == nil) {
			break;
		}
		
		status = instance.CreateFrameGrid(layoutControlData, outFrameUIDRef, left, top,
										  numCharsPerLine, numLines, numColumns,
										  columnGutterWidth, verticalFrame, textToInsert);
		// 1037710+ fix memory leak, CreateFrameGrid does not take ownership of the textToInsert buffer.
		delete textToInsert; 
		if (status == kSuccess) {
			SNIPLOG("Successfully created %s frame grid with UID=0x%X",
					(verticalFrame ? "vertical" : "horizontal"), 
					outFrameUIDRef.GetUID().Get());
		}
		
	} while(false);
	return (status);
}

/* 
*/
bool16  _SnpRunnerCreateFrameGrid::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS) == kFalse) {
		// Only load under the Japanese language feature set.
		result = kFalse;
	}
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS) == kTrue) {
		// Don't load under InCopy product.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerCreateFrameGrid instance_SnpRunnerCreateFrameGrid;
DEFINE_SNIPPET(_SnpRunnerCreateFrameGrid) 	
// End, SnpCreateFrameGrid.cpp


