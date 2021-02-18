//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateAssignment.cpp $
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
#include "IAssignmentSelectionSuite.h"
#include "IAssignment.h"
#include "IDocument.h"
#include "IAssignmentMgr.h"
#include "IAssignSetPropsCmdData.h"
#include "IBoolData.h"
#include "IAssignmentSelectionSuite.h"
#include "ISelectionManager.h"
#include "iuicolorutils.h"
#include "IAssignedStory.h"
#include "IStringData.h"
#include "ISaveFileDialog.h"

// General includes:
#include "LocaleSetting.h"
#include "FileTypeRegistry.h"
#include "FileUtils.h"
#include "UIDList.h"
#include "SDKFileHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"


/** 
	This snippet provides: 
    \li Create an assignemnt
	\li Add new content to existing assignment
	\li A snippet view of contents of an assignment
	\li delete assignment.

		<h2>Exercising</h2>

	<h3>New Assignment</h3>
		-# Open an existing document or Create a new document and save
		-# Run the Manipulate Assignment snippet
		-# Choose the option New Assignment.
		-# Choose a file name the assignment to save to in the save as dialog
		-# Choose various assignment options
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see a new assignment created in Assignment palette.
		-# Snippet runner log reports an assignment is created.
	<h3>Add to Assignment</h3>
		-# Open an existing document with assignment or continue from New Assignment above
		-# Select an image or story from the document window
		-# Run the Manipulate Assignment snippet
		-# Choose the option Add to Assignment
		-# Choose an assignment you want to add to
		-# There is an assert about fTransactionLevel is not 0 as of debug build 211, ingore it.
		-# You should see snippet runner log reports successful
		-# You should see a new assigned story is added to the assignment you choose in Assignment palette.
		-# Known issue: If your selection is not an image and story, you still can run, but nothing is added to the assignment.
	<h3>Inspect Assignment</h3>
		-# Open an existing document with assignment or continue from New Assignment above
		-# Add images or stories to assignment from Assignment palette or run above add to assingment snippet.
		-# Run the Manipulate Assignment snippet
		-# Choose the option Inspect Assignment
		-# Choose an assignment you want to inspect
		-# If all is well, there should be no asserts (if in debug build).
		-# Assignment information will be dumped to snippet runner log. Examine the result
	<h3>Delete Assignment </h3>
		-# Open an existing document with assignment or continue from New Assignment above
		-# Run the Manipulate Assignment snippet
		-# Choose the option Delete Assignment
		-# Choose an assignment you want to delete
		-# If all is well, there should be no asserts (if in debug build).
		-# You should see the assignment disappeared from Assignment palette.
		-# Snippet runner log will report assignment deleted.
    <h2> Running without InCopy plugins </h2>
	  If running in InDesign without AssignmentUI, InCopyBridge, InCopyBridgeUI, InCopyExport,
	  InCopyExportUI plugin (these are normally installed under ...\\plugins\\incopyworkflow\), the
	  following behavior change is expected:
	    -# Inspect Assignment, Delete assignment works as normal
        -# Add to assignment will fail becuase we can not export story without InCopyBridge. No item is added to assignment, but the SnippetRunner log will still report success (known issue)

	@ingroup sdk_snippet
	@ingroup sdk_assignment
 */
/**
  Manipulate assignment snippet.
  Create, inspect, delete an assignment, add the selected item (story/graphic) to assignment.
*/
class SnpManipulateAssignment
{
	public:
		/** Create new assignment file.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode NewAssignment(IActiveContext * ac);

		/** Add selection to assignment file.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode AddToAssignment(IActiveContext * ac, IAssignment * assignment);

		/** inspect assignment file.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode InspectAssignment(IAssignment * assignment);
		
		/** Add selection to assignment file.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode DeleteAssignment(IAssignment * assignment);
};

/*
*/
ErrorCode SnpManipulateAssignment::NewAssignment(IActiveContext * ac)
{
	ErrorCode result = kFailure;
	do {
		IDocument * doc = ac->GetContextDocument();
		IDataBase *db = ::GetDataBase(doc);

		//where the assignment saved to
		SDKFileSaveChooser fileChooser;
		// initialize the dialog title
		PMString title("New Assignment", PMString::kTranslateDuringCall);

		fileChooser.SetTitle(title);
		SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kAssignmentFileTypeInfoID);
		FileTypeInfo fti = FileTypeRegistry::GetCurrentFileTypeInfo(kAssignmentFileTypeInfoID);
		PMString defExt(fti.GetFileExtension());	// inca
		PMString pub("Assignment File", PMString::kTranslateDuringCall);
		fileChooser.AddFilter(macFileCreator, kTextType, defExt, pub);
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}	

		IDFile sysFile = fileChooser.GetIDFile();

		// check and delete if this file already exist
		if (sysFile.Exists() && sysFile.Delete())
		{
			//warning the user the file exist is done via Dialog, so not necessary here
		}

		PMString baseFileName;
		FileUtils::GetBaseFileName(sysFile, baseFileName);
	
		// save off the file we exported to
		PMString assignFile = FileUtils::SysFileToPMString(sysFile);

		// Get assignment options
		Utils<ISnipRunParameterUtils> parameterUtils;
		PMString user = parameterUtils->GetPMString("User:");
		PMString newAssName = parameterUtils->GetPMString("Assignment Name:",baseFileName );
		user.SetTranslatable(kFalse);			
		newAssName.SetTranslatable(kFalse);	

		K2Vector<PMString> options;
		options.push_back(PMString("Frames"));
		options.push_back(PMString("Assigned Spreads"));
		options.push_back(PMString("All Spreads"));
		int32 option = parameterUtils->GetChoice(PMString("Please choose export option:"), options);
		IAssignment::AssignmentExportOptions	assExpOption= IAssignment::kAssignmentExportFrames;
		if (!parameterUtils->WasDialogCancelled()) 
		{
			switch (option)
				{
				case 0:
					break;

				case 1:
					assExpOption =  IAssignment::kAssignmentExportSpreads;
					break;

				case 2:
					assExpOption =  IAssignment::kAssignmentExportAll;
					break;
			}
		}

		//Get Color
		Utils<IUIColorUtils> colorUtils;
		K2Vector<PMString> uicolors;
		int32 numColors = colorUtils->GetUIColorNum();
		for (int32 colorIndex = 0; colorIndex < numColors; colorIndex++)
			uicolors.push_back(colorUtils->GetUIColorName(colorIndex));
		int32 colorChoice = parameterUtils->GetChoice(PMString("Please choose a color:"), uicolors);
		UID color = kInvalidUID;
		if (!parameterUtils->WasDialogCancelled()) 
			color = colorUtils->GetUIColor(colorChoice, doc).GetUID();
		

		//make new assignment 
		InterfacePtr<ICommand> assignDocCmd(CmdUtils::CreateCommand(kAssignDocCmdBoss));
  		UIDRef docRef(db, db->GetRootUID());
		UIDList uidl(docRef);
		assignDocCmd->SetItemList(uidl);
		IAssignSetPropsCmdDataPtr data(assignDocCmd, UseDefaultIID());	
		bool16 dirty = kFalse;
		bool16 includeLinked = kTrue;
		data->Set(&newAssName, &assignFile, &user, &color, &assExpOption, &dirty, &includeLinked);
		ErrorCode err = CmdUtils::ProcessCommand(assignDocCmd);
		if (err != kSuccess)
			break;
		
		IAssignmentPtr assignment(assignDocCmd->GetItemList()->GetRef(0), UseDefaultIID());

		//save assignment
		InterfacePtr<IAssignmentMgr> assMgr(GetExecutionContextSession(), UseDefaultIID()); 
		assMgr->SaveAssignment(assignment);

		assMgr->NotifyPanel();

		SNIPLOG("New assignment created.");
		result = kSuccess;

	} while(false);
	return result;
}



/* Add to assignment snppet
*/
ErrorCode SnpManipulateAssignment::AddToAssignment(IActiveContext * ac, IAssignment * assignment)
{
	ErrorCode result = kFailure;
	do {

		if (!assignment)
		{
			SNIPLOG("No assignment available for add content");
			break;
		}
		InterfacePtr<IAssignmentSelectionSuite> sweet(ac->GetContextSelection(), UseDefaultIID());
		ASSERT(sweet);
		if (!sweet)
			break;

 		result = sweet->Assign(assignment);

		IAssignmentMgrPtr assMgr(GetExecutionContextSession(), UseDefaultIID());
		assMgr->NotifyPanel();		

		if (result == kSuccess)
			SNIPLOG("Selection added to assignment.");
		else
			SNIPLOG("Add selection to assignment failed.");

	} while(false);
	return result;
}




/* Inspect assignment snippet
*/
ErrorCode SnpManipulateAssignment::InspectAssignment(IAssignment * assignment)
{
	ErrorCode result = kFailure;
	do {
		if (!assignment)
		{
			SNIPLOG("No assignment available for inspect");
			break;
		}

		SNIPLOG("Assignment Information \n");
		PMString assPath = assignment->GetFile();
		SNIPLOG("Assignment Path: %s", assPath.GetPlatformString().c_str());
		PMString assName = assignment->GetName();
		SNIPLOG("Assignment Name: %s", assName.GetPlatformString().c_str());
		PMString assUser = assignment->GetUser();
		SNIPLOG("Assignment To: %s", assUser.GetPlatformString().c_str());

		PMString assColorName;
		UID	assColor = assignment->GetColor();
        IDataBase *db = ::GetDataBase(assignment);
		InterfacePtr<IDocument> doc(db, db->GetRootUID(), UseDefaultIID());
        int32 colorIndex = Utils<IUIColorUtils>()->GetUIColorIndex(assColor, doc);
        if (colorIndex != -1)
			assColorName = Utils<IUIColorUtils>()->GetUIColorName(colorIndex);
		SNIPLOG("Assignment Color: %s", assColorName.GetPlatformString().c_str());

		PMString assExpOption;
		IAssignment::AssignmentExportOptions	exportOption= assignment->GetExportOption();
		switch (exportOption)
			{
			case IAssignment::kAssignmentExportFrames:
				assExpOption = "Frames";
				break;

			case IAssignment::kAssignmentExportSpreads:
				assExpOption =  "Assigned Spreads";
				break;

			case IAssignment::kAssignmentExportAll:
				assExpOption =  "All Spreads";
				break;
		}
		assExpOption.Translate();
		SNIPLOG("Assignment Export Option: %s", assExpOption.GetPlatformString().c_str());


		SNIPLOG("Assigned story list in this assignment:");
		UIDList storyList= assignment->GetStories();
		for (int32 i = 0; i < storyList.size(); i++)
		{	
			InterfacePtr<IAssignedStory>	iAssignedStory (storyList.GetDataBase (), storyList[i], UseDefaultIID ());
			UIDRef storyRef = iAssignedStory->GetUIDRef();
			UID storyUID =    storyRef.GetUID();
			ClassID clsID = ::GetClass(iAssignedStory);
			if (clsID == kAssignedImageBoss)
				SNIPLOG("Story %d is an image", i);
			else if (clsID == kAssignedStoryBoss)
				SNIPLOG("Story %d is a text story", i);
			else
				SNIPLOG("Unknown story type");

			SNIPLOG("Story %d UID: %ld", i, storyUID.Get());
			PMString storyFile =    iAssignedStory->GetFile();
			SNIPLOG("Story %d File path %s",i, storyFile.GetPlatformString().c_str());
			PMString storyName =    iAssignedStory->GetName();
			SNIPLOG("Story %d Story name %s",i, storyName.GetPlatformString().c_str());
		}

		SNIPLOG("Assignment information displayed.");
		result = kSuccess;

	} while(false);
	return result;
}


/*4. Delete Assignment snippet
*/
ErrorCode SnpManipulateAssignment::DeleteAssignment(IAssignment * assignment)
{
	ErrorCode result = kFailure;
	do {
		
 		if (!assignment)
		{
			SNIPLOG("No assignment available for delete");
			break;
		}

		IDataBase *db = ::GetDataBase(assignment);
		PMString fromAssignPath	= assignment->GetFile();
		IAssignedDocumentPtr assignDoc(db, db->GetRootUID(), UseDefaultIID());

		// remove assignment from document
		InterfacePtr<ICommand> unassignDocCmd(CmdUtils::CreateCommand(kUnassignDocCmdBoss));
		UIDList uidl(::GetUIDRef(assignDoc));
		unassignDocCmd->SetItemList(uidl);
		InterfacePtr<IStringData> sd(unassignDocCmd, UseDefaultIID());
		sd->Set(fromAssignPath);
		result = CmdUtils::ProcessCommand(unassignDocCmd);
		if (result == kSuccess)
			SNIPLOG("Assignment deleted.");

		InterfacePtr<IAssignmentMgr> assMgr(GetExecutionContextSession(), UseDefaultIID());
		assMgr->NotifyPanel();

	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpManipulateAssignment available to the SnippetRunner framework.

  	@ingroup sdk_snippet

 */
class _SnpRunnerManipulateAssignment : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulateAssignment();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateAssignment();

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

		/** Don't present this snippet in the framework's UI if the
		product we are running under is InCopy.
		@return kFalse if the host product is InCopy, kTrue otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}

private:
		/** Choose an assignment. Put up an assignment list for user to choose from.
		*/
		IAssignment * GetAssignment(IActiveContext * ac);
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerManipulateAssignment::_SnpRunnerManipulateAssignment() : SnpRunnable("ManipulateAssignments")
{
	this->SetDescription("Manipulate assignment");

	this->SetPreconditions("1. Document open and saved");

	this->SetCategories("sdk_snippet, sdk_assignment");
}

/* Destructor.
*/
_SnpRunnerManipulateAssignment::~_SnpRunnerManipulateAssignment()
{
}

/* Manupute precondtion. requires document saved.
*/
bool16	_SnpRunnerManipulateAssignment::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;

	do {
		//can not run until the document is saved once
		IActiveContext * ac = runnableContext->GetActiveContext();
		IDocument* doc = ac->GetContextDocument();
		if (!doc)
			break;
		IDataBase* db = GetDataBase(doc);
		if (!db)
			break;
		const IDFile* sysFile = db->GetSysFile();
		if (sysFile == nil)
			break;

		result = kTrue;
	} while(false);

	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerManipulateAssignment::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	IActiveContext * ac = runnableContext->GetActiveContext();

	do {

		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> operations;
		operations.push_back(PMString("New Assignment"));
		operations.push_back(PMString("Add to Assignment"));
		operations.push_back(PMString("Inspect Assignment"));
		operations.push_back(PMString("Delete Assignment"));
		int32 action = parameterUtils->GetChoice(PMString("What action?"), operations);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		switch(action) {
			case 0: //New assignment
			{
				SnpManipulateAssignment instance;
				status = instance.NewAssignment(ac);
			}
			break;

			case 1: // Add to assignment
			{
				InterfacePtr<IAssignmentSelectionSuite> sweet(ac->GetContextSelection(), UseDefaultIID());
				if (!sweet)
				{
					SNIPLOG("Can not add to assignment, nothing selected.");
					break;
				}
				if (!sweet->CanAssign())
				{
					SNIPLOG("Can not add selection to assignment");
					break;
				}

				IAssignment* assignment = this->GetAssignment(ac);

				SnpManipulateAssignment instance;
				status = instance.AddToAssignment(ac, assignment);
		

			}
			break;

			case 2: // Inspect assignment
			{
				IAssignment* assignment = this->GetAssignment(ac);

				SnpManipulateAssignment instance;
				status = instance.InspectAssignment(assignment);
			}
			break;

			case 3: // Delete assignment
			{

				IAssignment* assignment = this->GetAssignment(ac);

				SnpManipulateAssignment instance;
				status = instance.DeleteAssignment(assignment);
			}
			break;

		}
		
	} while(false);
	return (status);
}

bool16  _SnpRunnerManipulateAssignment::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		result = kFalse;
	}
	return result;
}

/* Choose an assignment. Put up an assignment list for user to choose from.
*/
IAssignment * _SnpRunnerManipulateAssignment::GetAssignment(IActiveContext * ac)
{
	IAssignment* assignment = nil;
	do {
		
		Utils<ISnipRunParameterUtils> parameterUtils;
		IAssignedDocumentPtr assignDoc(ac->GetContextDocument(), UseDefaultIID());
		K2Vector<PMString> choices;
		int32 unAssignedIndex = 0;
		UIDList assignments = assignDoc->GetAssignments();
		for (int32 i = 0; i < assignments.size(); i++)
		{
			InterfacePtr<IAssignment>	iAssignment (assignments.GetDataBase (), assignments[i], UseDefaultIID ());
			assignment = iAssignment;
			if (!(assignment->GetFile().empty()))
				choices.push_back(assignment->GetName());
			else
				unAssignedIndex = i;
		}

		if (choices.size() == 0)
		{
			assignment = nil;
			break;   // No assignment available, but let caller of this method to choose error message
		}
		int32 choice = parameterUtils->GetChoice(PMString("Choose an Assignment"), choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		//Adjust index to exclude UnAssigned
		if (choice >= unAssignedIndex)
			choice++;

		InterfacePtr<IAssignment>	iAssignment (assignments.GetDataBase (), assignments[choice], UseDefaultIID ());
		assignment = iAssignment;

		
	} while(false);

	return assignment;
}



/*	Declare instances to register the snippet hook with the framework.
*/

static _SnpRunnerManipulateAssignment instance_SnpRunnerManipulateAssignment;
DEFINE_SNIPPET(_SnpRunnerManipulateAssignment) 	

// End, SnpAssignmentFile.cpp

