//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformNamedGrid.cpp $
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
#include "IWorkspace.h"
#include "IStyleNameTable.h"
#include "INamedGridInfo.h"
//#include "ICJKGridData.h" // included by "ICJKLayoutGridData.h"
//#include "ICJKFrameGridDefaults.h"  // included by "ICJKGridSuite.h"
#include "ICJKLayoutGridDefaults.h"
#include "INamedGridUID.h"
#include "ICJKGridUIUtils.h"
#include "ICJKGridSuite.h"
#include "ISelectionUtils.h"
#include "IStringData.h"
#include "IUIDData.h"

// General includes:
//#include "CJKGridID.h" // included by "INamedGridInfo.h"
#include "Utils.h"
#include "LocaleSetting.h"
#include "UIDList.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// TODO align with coding conventions
#define ASSERT_BREAK_IF_NIL(p) { ASSERT(p); if(p == nil){ break; } }

/** Text Alignment name table
	@see ICompositionStyle
 */
static const char* Snp_kTextAlignmentTable[8] = { 
	"kTextAlignLeft",
	"kTextAlignCenter",
	"kTextAlignRight",
	"kTextAlignJustifyFull",
	"kTextAlignJustifyLeft",		
	"kTextAlignJustifyCenter",	
	"kTextAlignJustifyRight",	
	"kTextAlignAuto"             // only warichu in 2.0
};

/** Grid Alignment name table
	@see CTextEnum.h
 */
static const char* Snp_kGridAlignmentMetric[8] = {
	"kGANone",
	"kGABaseline",
	"kGAEmTop",
	"kGAEmCenter",
	"kGAEmBottom",
	"kGAICFTop",
	"kGAICFBottom",
	"kGACapHeight"
};

/** Character Hang name table
	@see IDrawingStyle
 */
static const char* Snp_kCharacterHang[6] = {
	"kHangBaseline",
	"kHangEmCenter",
	"kHangEmBottom",
	"kHangEmTop",
	"kHangICFBottom",
	"kHangICFTop"
}; 

// TODO align with coding conventions
/** A structure that keeps named grid settings. 
	The fields have been modelled after methods in INamedGridInfo and ICJKGridData.
	@see INamedGridInfo
	@see ICJKGridData
*/
struct SnpNamedGridSettings
{

	/** The name of the named grid. 
		@see INamedGridInfo::GetName()
	*/
	PMString	fName;

	/** Grid FontUID
		@see ICJKGridData::GetFontUID()
	*/
	UID			fFontUID;
	
	/** Grid Font Style(variant)
		@see ICJKGridData::GetFontStyleName()
	*/
	PMString	fFontStyleName;
	
	/** Grid cell size in points.
		@see ICJKGridData::GetTextSize()
	*/
	PMReal		fTextSize;
	
	/** The square that a character is written, and the spacing of the next square. (em box end to next em box start)
		@see ICJKGridData::GetCharAki()
	*/
	PMReal		fCharacterAki;
	
	/** The space from the previous line to the next line. (em box end to next em box start)
		@see ICJKGridData::GetLineAki()
	*/
	PMReal		fLineAki;
	
	/** The horizontal scale of character.
		@see ICJKGridData::GetHScale()
	*/
	PMReal		fHScale;
	
	/** The vertical scale of character.
		@see ICJKGridData::GetVScale()
	*/
	PMReal		fVScale;
	
	/** Text Alignment
		@see ICJKGridData::GetTextAlignment()
	*/
	ICompositionStyle::TextAlignment	fTextAlignment;
	
	/** Grid Alignment
		@see ICJKGridData::GetGridAlignment()
	*/
	Text::GridAlignmentMetric			fGridAlignment;
	
	/** Character Hang.
		@see ICJKGridData::GetCharacterHang()
	*/
	IDrawingStyle::CharacterHang		fCharacterHang;

};

/** 
	\li Inspects a named grid,
	\li Creates a new named grid,
	\li Deletes an existing named grid.

  	@ingroup sdk_snippet
 	@ingroup sdk_cjk
  	@ingroup sdk_text
	@see ICJKGridData
	@see ICJKFrameGridDefaults
	@see ICJKLayoutGridDefaults
	@see ICJKGridSuite
	@see IFilteredCJKGridCmdData
	@see INamedGridInfo
	@see INamedGridUID
	@see IStyleNameTable
	@see IUIDData
	@see kCreateNamedGridCmdBoss
	@see kFilteredCJKGridDataBoss 
	@see kDeleteNamedGridCmdBoss
*/
class SnpPerformNamedGrid 
{
public:

	/** Constructor.
	*/
	SnpPerformNamedGrid() {}

	/** Destructor.
	*/
	virtual			~SnpPerformNamedGrid() {}

	/** Inspect a named grid.
		@param workspace IN The workspace that contains the named grid to be inspected.
		@param namedGridUID IN The UID for the named grid that is to be inspected.
		@param data OUT The named grid data for the given UID.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode InspectNamedGrid(IWorkspace* workspace, const UID& namedGridUID, SnpNamedGridSettings& data);
	
	/** Creates a new named grid based on default grid data.
		@param workspace IN The workspace that contains the named grid to be created.
		@param filteredGridData IN A part of ICJKGridData with the change of the selection frame.
		@param gridName IN/OUT The name for The new named grid. When there is no name, a name is given automatically, and NamedGrid is made.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode CreateNamedGrid(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, PMString& gridName);
	
	/** Initialize a grid data.
		The conditions of InDesign are investigated. Then, the grid data given to it are
		initialized corresponding to the conditions.
		@param workspace IN The workspace that contains the named grid to be created.
		@param filteredGridData IN A part of ICJKGridData with the change of the selection frame.
		@param gridData OUT The Grid data to initialize.
		@return kSuccess on success, other ErrorCode otherwise.

		*/
	ErrorCode InitializeNewCJKGridData(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, ICJKGridData* gridData);
	
	/** Delete a named grid.
		@param workspace IN The workspace that contains the named grid to be created.
		@param name IN The name for the named grid that is to be deleted.
		@return kSuccess on success, other ErrorCode otherwise.
		*/
	ErrorCode DeleteNamedGrid(IWorkspace* workspace, const PMString& name);
	

	/** Gets the name list of the named grids.
		@param styleNameTable IN The IStyleNameTable interface for named grid on a specific workspace. 
		@return A list of named grids.
		*/
	K2Vector<PMString> GetNamedGridList(IStyleNameTable* styleNameTable);
	
	/** Reports the named grid data to SNIPLOG.
		@param data IN The named grid settings to report.
		*/
	void ReportNamedGridData(const SnpNamedGridSettings& data);


};

/* InspectNamedGrid
*/
ErrorCode SnpPerformNamedGrid::InspectNamedGrid(IWorkspace* workspace, const UID& namedGridUID, SnpNamedGridSettings& data)
{
	ErrorCode result = kFailure;
	do{
		ASSERT_BREAK_IF_NIL(workspace);

		if(namedGridUID == kInvalidUID)
		{
			break;
		}
		
		IDataBase* db = ::GetDataBase(workspace);
		
		InterfacePtr<INamedGridInfo> namedGridInfo(db, namedGridUID, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(namedGridInfo);

		data.fName = namedGridInfo->GetName();
		
		InterfacePtr<ICJKGridData> namedGridData(db, namedGridUID, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(namedGridData);
		
		data.fFontUID = namedGridData->GetFontUID();
		data.fFontStyleName = namedGridData->GetFontStyleName();
		data.fTextSize = namedGridData->GetTextSize();
		data.fCharacterAki = namedGridData->GetCharAki();
		data.fLineAki = namedGridData->GetLineAki();
		data.fHScale = namedGridData->GetHScale();
		data.fVScale = namedGridData->GetVScale();
		data.fTextAlignment = namedGridData->GetTextAlignment();
		data.fGridAlignment = namedGridData->GetGridAlignment();
		data.fCharacterHang = namedGridData->GetCharacterHang();
		
		ReportNamedGridData(data);
		
		result = kSuccess;
	
	}while(false);
	
	
	return result;
}

/* CreateNamedGrid
*/
ErrorCode SnpPerformNamedGrid::CreateNamedGrid(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, PMString& gridName)
{
	ErrorCode result = kFailure;
	do {
		ASSERT_BREAK_IF_NIL(workspace);
		
		//PMString gridName(name);
		
		// When there is no designation of the name, A name is made 'NamedGrid '.
		if(gridName.empty())
		{
			gridName.SetKey("Named Grid ", PMString::kTranslateDuringCall);
		}		
					
		InterfacePtr<IStyleNameTable> styleNameTable(workspace, IID_INAMEDGRIDSNAMETABLE);
		ASSERT_BREAK_IF_NIL(styleNameTable);
		
		int32 numStyles = styleNameTable->GetNumStyles();
		
		UID styleUID =  styleNameTable->FindByName(gridName);

		// Make a unique name.
		if(styleUID != kInvalidUID)
		{
			PMString uniqueName;
			for(int32 i = 0; i < numStyles; i++)
			{
				uniqueName = gridName;
				uniqueName.AppendNumber(i+1);
				
				styleUID =  styleNameTable->FindByName(uniqueName);
				if(styleUID == kInvalidUID)
				{
					gridName = uniqueName;
					break;  // It break through the 'for' loop.
				}
			}
		}
					
		InterfacePtr<ICommand> createNamedGridCmd(CmdUtils::CreateCommand(kCreateNamedGridCmdBoss));
		ASSERT_BREAK_IF_NIL(createNamedGridCmd);
		
		InterfacePtr<INamedGridInfo> namedGridInfo(createNamedGridCmd, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(namedGridInfo);

		createNamedGridCmd->SetItemList(UIDList(workspace));
				
		namedGridInfo->SetName(gridName);
		namedGridInfo->SetKeyboardShortcut(0,0);
		
		InterfacePtr<ICJKGridData> cjkGridData(createNamedGridCmd, UseDefaultIID());
		result = this->InitializeNewCJKGridData(workspace, filteredGridData, cjkGridData);
		if(result == kSuccess)
		{
			result = CmdUtils::ProcessCommand(createNamedGridCmd);
		}

	} while(false);
	return result;
}

/* InitializeNewCJKGridData
*/
ErrorCode SnpPerformNamedGrid::InitializeNewCJKGridData(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, ICJKGridData* gridData)
{
	ErrorCode result = kFailure;

	do{
		ASSERT_BREAK_IF_NIL(workspace);
		ASSERT_BREAK_IF_NIL(gridData);

		InterfacePtr<ICJKFrameGridDefaults> defaultsFrameGrid(workspace, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(defaultsFrameGrid);
		
		// Set the gridData to defaults frame grid data.
		gridData->CopyFrom(defaultsFrameGrid);
			
		InterfacePtr<INamedGridUID> defaultsNamedGridUID(defaultsFrameGrid, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(defaultsNamedGridUID);

		InterfacePtr<IStyleNameTable> namedGridTable(defaultsFrameGrid, IID_INAMEDGRIDSNAMETABLE);
		ASSERT_BREAK_IF_NIL(namedGridTable);
	
		// If the root style are the defaults grid format then override
		// the defaults frame grid with selected page's layout grid or defaults layout grid.
		if(defaultsNamedGridUID->Get() == namedGridTable->GetRootStyleUID())
		{
			// 1056246- InterfacePtr<ICJKGridData> selectedLayoutGrid(Utils<ICJKGridUIUtils>()->QuerySelectedLayoutGrid());
			// 1056246+
			InterfacePtr<ICJKGridData> selectedLayoutGrid;
			Utils<ICJKGridUIUtils> cjkGridUIUtils;
			if (cjkGridUIUtils) {
				selectedLayoutGrid.reset(cjkGridUIUtils->QuerySelectedLayoutGrid());
			}
			else {
				// ICJKGridUIUtils is implemented by a plug-in that does not load under InCopy so it may not be available.
				// When its not available leave selectedLayoutGrid as a nil pointer which means the code below
				// just uses default grid settings rather than the grid settings for the viewed page.
			}
			// 1056246+
			
			if(selectedLayoutGrid) 
			{
				// The condition that route style is selected and a document is open.
				
				gridData->CopyFrom(selectedLayoutGrid);
				
				// These set up value by the default because it is not a part of the layout grit data.
				gridData->SetTextAlignment(defaultsFrameGrid->GetTextAlignment());
				gridData->SetGridAlignment(defaultsFrameGrid->GetGridAlignment());
				gridData->SetCharacterHang(defaultsFrameGrid->GetCharacterHang());
			}
			else 
			{
				// The condition that route style is selected and a document isn't open
				
				InterfacePtr<ICJKLayoutGridDefaults> defaultsLayoutGrid(workspace, UseDefaultIID());
				ASSERT_BREAK_IF_NIL(defaultsLayoutGrid);
				// Get the gridData too defaults layout grid data.
				gridData->CopyFrom(defaultsLayoutGrid);
			}
		}
		else if(defaultsNamedGridUID->Get() != kInvalidUID)
		{
			// Use named grid data.
			IDataBase* db = ::GetDataBase(defaultsFrameGrid);
			InterfacePtr<ICJKGridData> namedGridData(db, defaultsNamedGridUID->Get(), UseDefaultIID());
			ASSERT_BREAK_IF_NIL(namedGridData);
			
			gridData->CopyFrom(namedGridData);
		}
	
		// Try to setup of the gridData by using selection.
		// When a grid text frame is selected, data are made to reflect on the grid data.
		if(filteredGridData != nil)
		{
			gridData->CopyFrom(filteredGridData);
		}		

		result = kSuccess;
	} while(false);
	return result;
}

/* DeleteNamedGrid
*/
ErrorCode SnpPerformNamedGrid::DeleteNamedGrid(IWorkspace* workspace, const PMString& name)
{
	ErrorCode result = kFailure;

	do{
		ASSERT_BREAK_IF_NIL(workspace);
		
		if(name.empty())
		{
			break;
		}

		InterfacePtr<IStyleNameTable> styleNameTable(workspace, IID_INAMEDGRIDSNAMETABLE);
		ASSERT_BREAK_IF_NIL(styleNameTable);
					
		UID styleUID =  styleNameTable->FindByName(name);

		if(styleUID == kInvalidUID)
		{			
			break;
		}
		
		UID defaultStyleUID = styleNameTable->GetDefaultStyleUID();
		
		// this prevents the deletion of the root style
		if(styleUID == defaultStyleUID)
		{
			break;		
		}
		
		InterfacePtr<ICommand> deleteNamedGridCmd(CmdUtils::CreateCommand(kDeleteNamedGridCmdBoss));

		deleteNamedGridCmd->SetItemList(UIDList(workspace));
		
		InterfacePtr<IUIDData> uidData(deleteNamedGridCmd, UseDefaultIID());
		
		IDataBase* db = ::GetDataBase(workspace);

		uidData->Set(db, styleUID);
		
		result = CmdUtils::ProcessCommand(deleteNamedGridCmd);
		
	} while(false);
	return result;
}

/* GetStyleNameList
*/
K2Vector<PMString> SnpPerformNamedGrid::GetNamedGridList(IStyleNameTable* styleNameTable)
{

	K2Vector<PMString> nameList;
	nameList.clear();

	do{
		ASSERT_BREAK_IF_NIL(styleNameTable);
		
		IDataBase* db = ::GetDataBase(styleNameTable);
		ASSERT_BREAK_IF_NIL(db);
		
		int32 numStyles = styleNameTable->GetNumStyles();
		
		// iterate through each style name table in the list
		for (int32 i = 0 ; i < numStyles ; i++) 
		{
			UID styleUID = styleNameTable->GetNthStyle(i);
			InterfacePtr<INamedGridInfo> namedGridInfo(db, styleUID, UseDefaultIID());
			if(namedGridInfo != nil)
			{
				PMString styleName = namedGridInfo->GetName();
				nameList.push_back(styleName);
			}
			else
			{
				PMString badStyleName("<invalid Style ");
				badStyleName.AppendNumber(i);
				badStyleName.Append(">");
				nameList.push_back(badStyleName);
			}
		}
		
	}while(false);

	return nameList;
}

/* ReportNamedGridData
*/
void SnpPerformNamedGrid::ReportNamedGridData(const SnpNamedGridSettings& data)
{
	// unravel all of the named grid data
	SNIPLOG("=== Named grid data start ===");
	SNIPLOG("*Name: \"%s\"", data.fName.GetPlatformString().c_str());
	SNIPLOG("*Font UID: 0x%X", data.fFontUID.Get());
	SNIPLOG("*Font Style Name: \"%s\"", data.fFontStyleName.GetPlatformString().c_str());
	SNIPLOG("*Text size: %f pt", ::ToDouble(data.fTextSize));
	SNIPLOG("*Character Aki: %f", ::ToDouble(data.fCharacterAki));
	SNIPLOG("*Line Aki: %f", ::ToDouble(data.fLineAki));
	SNIPLOG("*H Scale: %f", ::ToDouble(data.fHScale));
	SNIPLOG("*V Scale: %f", ::ToDouble(data.fVScale));
	SNIPLOG("*Text Alignment: %s", Snp_kTextAlignmentTable[data.fTextAlignment]);
	SNIPLOG("*Grid Alignment: %s", Snp_kGridAlignmentMetric[data.fGridAlignment]);
	SNIPLOG("*Character Hang: %s", Snp_kCharacterHang[data.fCharacterHang]);
	SNIPLOG("=== Named grid data end ===");
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerPerformNamedGrid : public SnpRunnable
{
	public:
	
		/** Inspect a named grid.
			@param workspace IN The workspace that contains the named grid to be inspected.
			@param namedGridUID IN The UID for the named grid that is to be inspected.
			@param data OUT The named grid data for the given UID.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode InspectNamedGrid(IWorkspace* workspace, const UID& namedGridUID, SnpNamedGridSettings& data);
		
		/** Creates a new named grid based on default grid data.
			@param workspace IN The workspace that contains the named grid to be created.
			@param filteredGridData IN A part of ICJKGridData with the change of the selection frame.
			@param gridName IN/OUT The name for The new named grid. When there is no name, a name is given automatically, and NamedGrid is made.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode CreateNamedGrid(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, PMString& gridName);
		
		/** Initialize a grid data.
			The conditions of InDesign are investigated. Then, the grid data given to it are
			initialized corresponding to the conditions.
			@param workspace IN The workspace that contains the named grid to be created.
			@param filteredGridData IN A part of ICJKGridData with the change of the selection frame.
			@param gridData OUT The Grid data to initialize.
			@return kSuccess on success, other ErrorCode otherwise.

		 */
		ErrorCode InitializeNewCJKGridData(IWorkspace* workspace, IFilteredCJKGridCmdData* filteredGridData, ICJKGridData* gridData);
		
		/** Delete a named grid.
			@param workspace IN The workspace that contains the named grid to be created.
			@param name IN The name for the named grid that is to be deleted.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode DeleteNamedGrid(IWorkspace* workspace, const PMString& name);
		
	
		/** Gets the name list of the named grids.
			@param styleNameTable IN The IStyleNameTable interface for named grid on a specific workspace. 
			@return A list of named grids.
		 */
		K2Vector<PMString> GetNamedGridList(IStyleNameTable* styleNameTable);
		
		/** Reports the named grid data to SNIPLOG.
			@param data IN The named grid settings to report.
		 */
		void ReportNamedGridData(const SnpNamedGridSettings& data);

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerPerformNamedGrid();

		/** Destructor.
		 */
		virtual			~_SnpRunnerPerformNamedGrid();

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
			language feature set is Japanese and the product is InDesign.
			@return kTrue if the snippet can be loaded, kFalse otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunWorkspaceContext;}
};
/* Constructor.
*/
_SnpRunnerPerformNamedGrid::_SnpRunnerPerformNamedGrid() : SnpRunnable("PerformNamedGrid")
{
	this->SetDescription("Creates, Deletes, and Inspects a named grid");
	this->SetPreconditions("Active workspace, Japanese feature set ONLY");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformNamedGrid::~_SnpRunnerPerformNamedGrid()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformNamedGrid::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		ASSERT_BREAK_IF_NIL(runnableContext);

		// get the active workspace.
		IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();
		ASSERT_BREAK_IF_NIL(workspace);

		// get the style name table from the workspace. 
        InterfacePtr<IStyleNameTable> styleNameTable(workspace, IID_INAMEDGRIDSNAMETABLE);
		ASSERT_BREAK_IF_NIL(styleNameTable);

		// if we got here, we can run the snippet.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformNamedGrid::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpPerformNamedGrid instance;
		ASSERT_BREAK_IF_NIL(runnableContext);

		// get the active workspace.
		IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();
		ASSERT_BREAK_IF_NIL(workspace);

		// get the style name table from the workspace. 
        InterfacePtr<IStyleNameTable> styleNameTable(workspace, IID_INAMEDGRIDSNAMETABLE);
		ASSERT_BREAK_IF_NIL(styleNameTable);
		
		// get the IFilteredCJKGridCmdData of selection.
		InterfacePtr<ICJKGridSuite> cjkGridSuite(runnableContext, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(cjkGridSuite);
		InterfacePtr<IFilteredCJKGridCmdData> filteredGridData (::CreateObject2<IFilteredCJKGridCmdData>(kFilteredCJKGridDataBoss));
		ASSERT_BREAK_IF_NIL(filteredGridData);
		
		Utils<ISnipRunParameterUtils> parameterUtils;

		// what do you want to do?
		// inspect, create, delete
		enum { kInspect, kCreate, kDelete };
		K2Vector<PMString> operations;
		operations.clear();
		operations.push_back("inspect a named grid"); // kInspect (default)
		operations.push_back("create new named grid"); // kCreate
		operations.push_back("delete a named grid"); // kDelete
		int32 operation = parameterUtils->GetChoice("What operation do you want to perform?", operations, kInspect);
		if (parameterUtils->WasDialogCancelled()) 
		{
			// user cancelled! get out of do-while loop
			break;
		}
		
		// get the current list of Named Grid on the workspace
		K2Vector<PMString> namedGridList = instance.GetNamedGridList(styleNameTable);
		
		// get the number of "actual" Named Grid on the workspace.
		int32 numAvailableTables = namedGridList.size();
		
		// get the active database.
		IDataBase* db = ::GetDataBase(workspace);
		
		SnpNamedGridSettings data;

		switch (operation) 
		{
			case kInspect:
			{
				// get the choice of named grid to inspect 
				int32 choiceToInspect = parameterUtils->GetChoice("Which named grid do you want to inspect?", namedGridList, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
				UID choiceUID = styleNameTable->GetNthStyle(choiceToInspect);
				status = instance.InspectNamedGrid(workspace, choiceUID, data);
			}
			break;

			case kCreate:
			{
				PMString gridName = parameterUtils->GetPMString("Specify the name of the new named grid.", "MyNamedGrid"); 
				if (parameterUtils->WasDialogCancelled()) 
				{
					break;
				}
			
				status = instance.CreateNamedGrid(workspace, filteredGridData, gridName);
				
				if(status == kSuccess)
				{
					SNIPLOG("Named grid \"%s\" was created.", gridName.GetPlatformString().c_str());
				}
				else
				{
					SNIPLOG("Named grid \"%s\" couldn't be created.", gridName.GetPlatformString().c_str());
				}
			}
			break;
			
			case kDelete:
			{
				int32 choiceToInspect = parameterUtils->GetChoice("Which named grid do you want to delete?", namedGridList, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
				
				UID choiceUID = styleNameTable->GetNthStyle(choiceToInspect);
				
				InterfacePtr<INamedGridInfo> namedGridInfo(db, choiceUID, UseDefaultIID());
				ASSERT_BREAK_IF_NIL(namedGridInfo);
				
				PMString styleName = namedGridInfo->GetName();

				status = instance.DeleteNamedGrid(workspace, styleName);
				
				if(status == kSuccess)
				{
					SNIPLOG("Named grid \"%s\" was deleted.", styleName.GetPlatformString().c_str());
				}
				else
				{
					SNIPLOG("Named grid \"%s\" couldn't be deleted.", styleName.GetPlatformString().c_str());
				}
			}
			break;
		}	

	} while(false);
	return (status);
}

/* 
*/
bool16  _SnpRunnerPerformNamedGrid::CanLoad() const
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
static _SnpRunnerPerformNamedGrid instance_SnpRunnerPerformNamedGrid;
DEFINE_SNIPPET(_SnpRunnerPerformNamedGrid) 	

// End, SnpPerformNamedGrid.cpp

