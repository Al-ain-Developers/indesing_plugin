//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformKinsokuTable.cpp $
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
#include "IDataBase.h"
#include "IStyleNameTable.h"
#include "ICommand.h"
#include "IStringData.h"
#include "IUIDData.h"
#include "IKinsokuTable.h"
#include "IWorkspace.h"

// General includes:
#include "CJKID.h"
#include "CmdUtils.h"
#include "TextChar.h"
#include "PersistUtils.h"
#include "UIDList.h"
#include "Utils.h"
#include "WideString.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// TODO why struct with sideways copy of data on an interface, align with coding conventions

/** A structure that keeps kinsoku table settings. 
 * 	The fields have been modelled after methods in IKinsokuTable.
 * 	@see IKinsokuTable
 */
struct SnpKinsokuTableSettings
{
	/** The name of the kinsoku table. 
	 * 	@see IStringData */
	PMString fName;
	
	/** The list of characters that cannot be placed before the end of a line. 
	 * 	Also known as "Gyoumatsu kinshi moji".
	 * 	@see IKinsokuTable::GetKinsokuBefore() */
	WideString fKinsokuBefore;
    
	/** The list of characters that cannot be placed after the beginning of a line. 
	 * 	Also known as "Gyoutou kinshi moji" .
	 * 	@see IKinsokuTable::GetKinsokuAfter() */
	WideString fKinsokuAfter;
    
	/** The list of characters that cannot be hanging at the end of a line.
	 * 	Also known as "Burasagari kinshi moji".
	 * 	@see IKinsokuTable::GetKinsokuHanging() */
	WideString fKinsokuHanging;
	
	/** The list of characters that must not be separated at the end of a line.
	 * 	Also known as "Bunri kinshi moji".
	 * 	@see IKinsokuTable::GetKinsokuNotSeparate() */
	WideString fKinsokuNotSeparate;
	
	/**	Editability of this kinsoku table.
	 * 	@see IKinsokuTable::GetEditability()
	 *  @see IKinsokuTable::SetEditability() */
	bool16 fEditability;
	
	/* NOTE: IKinsokuTable has a few methods for adding and testing for 
		"kinsoku between" characters, however, they are not supported. */
};


/** \li Inspects a kinsoku table,,
 * 	\li Creates a new kinsoku table (either based on an existing one 
 * 		or from scratch), and 
 * 	\li Deletes an existing kinsoku table.
 * 
 *  (1) <B>Inspecting a kinsoku table</B>:
 * 	Select one of the existing kinsoku tables to inspect. The
 * 	data associated with the kinsoku table will be written to the SNIPLOG.
 * 
 *  (2) <B>Creating a kinsoku table</B>:
 * 	Enter the name of your new kinsoku table, and select which existing 
 * 	kinsoku table you want to base it on.  If you choose <none>, then a 
 * 	brand new kinsoku table will be made based on the root style. 
 * 	After creating a kinsoku table, you can apply the new kinsoku table 
 * 	on your	text selection by simply using the Paragraph Panel 
 *  If you want to do it programmatically, you can 
 * 	apply the kTAKinsokuTableBoss attribute on the text model.
 * 
 *  (3) <B>Deleting a kinsoku table</B>:
 * 	Select one of the existing kinsoku to delete. After deleting, 
 * 	go to the Paragraph Panel to verify that the kinsoku table is gone. 
 * 
 *  <B>About Kinsoku tables</B>:
 * 
 * 	"Kinsoku tables" are tables that contain a set of characters that
 * 	define line break rules for the Japanese text composers. 
 * 	There are 4 kinds of line break rule classifications:
 * 	\li The list of characters that cannot be placed before the end of a line.(Gyoumatsu kinshi moji)
 * 	\li The list of characters that cannot be placed after the beginning of a line. (Gyoutou kinshi moji)
 * 	\li The list of characters that cannot be hanging at the end of a line. (Burasagari kinshi moji)
 * 	\li The list of characters that must not be separated at the end of a line. (Bunri kinshi moji)
 * 
 * 	While you do not need the Japanese version of InDesign to run 
 * 	this snippet, you will need the Japanese version of InDesign to 
 * 	create a kinsoku table and apply to text, using the application 
 * 	user interface.
 * 	
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_cjk
 * 	@ingroup sdk_text
 */
class SnpPerformKinsokuTable 
{
public:
	/** Constructor.
	 */
	SnpPerformKinsokuTable() {}

	/** Destructor.
	 */
	virtual ~SnpPerformKinsokuTable() {}

	/** Creates a new kinsoku table.
	 * 
	 * 	If the name of the new kinsoku table already exists in the kinsoku 
	 * 	name table, then this method will point kinsokuTableUIDRef to the 
	 * 	existing entry, and the characters will NOT be modified.
	 * 
	 * 	The additional characters are hardcoded in this snippet - modify 
	 * 	them to suit your needs.
	 * 
	 * 	<B>Use Cases</B>:
	 * 	\li <B>Create a completely new kinsoku table from scratch</B>: 
	 * 		Specify 'kinsokuTableName'. Leave 'baseKinsokuTableUID' blank.
	 * 	\li <B>Create a new kinsoku table based on an existing kinsoku table, 
	 * 		but with additional characters.</B>: 
	 * 		The same as (1), but specify 'baseKinsokuTableUID'.
	 *  \li <B>Create a copy of an existing kinsoku table, with no additional 
	 * 		characters.</B>:
	 * 		Only specify 'kinsokuTableName' and 'baseKinsokuTableUID'.
	 * 
	 *	@param ws IN The workspace on which the new kinsoku table should be created. 
	 *	@param data IN The kinsoku table data settings for the new kinsoku table. 
	 * 		SnpKinsokuTableSettings is modelled after IKinsokuTable.
	 * 	@param baseKinsokuTableUID IN The UID of the kinsoku table to base the new one on.
	 * 		If you want to base the new kinsoku table on the Root style (empty), 
	 * 		set this to kInvalidUID.
	 * 	@param newKinsokuTableUID OUT The newly created kinsoku table UID.
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode CreateKinsokuTable(IWorkspace* ws, 
								 const SnpKinsokuTableSettings& data,
								 const UID& baseKinsokuTableUID,
								 UID& newKinsokuTableUID);

	/** Delete a kinsoku table.
	 *	@param ws IN The workspace that contains the kinsoku table to be deleted.
	 * 	@param kinsokuTableUIDToDelete IN The UID for the kinsoku table that should be deleted. 
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode DeleteKinsokuTable(IWorkspace* ws, 
								 const UID& kinsokuTableUIDToDelete);
	
	/** Inspect a kinsoku table.
	 *	@param ws IN The workspace that contains the kinsoku table to be inspected.
	 * 	@param kinsokuTableUIDToInspect IN The UID for the kinsoku table that is to be inspected.
	 * 	@param data OUT The kinsoku table settings for the given UID.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectKinsokuTable(IWorkspace* ws, 
								  const UID& kinsokuTableUIDToInspect,
								  SnpKinsokuTableSettings& data);

	/** Sets the kinsoku table data structure with sensible defaults. 
	 * 	Call this method before calling the CreateKinsokuTable() method. 
	 * 
	 * 	NOTE: You can modify the contents to suite your needs. 
	 * 	
	 * 	@param kinsokuTableName IN The name of the new kinsoku table.
	 * 	@param data OUT SnpKinsokuTableSettings struct. This method fills out the structure.
	 */
	void SetKinsokuTableSettings(const PMString& kinsokuTableName, 
								 SnpKinsokuTableSettings& data);

	/**	Filter out any duplicates in the settings before creating a new kinsoku table.
	 * 	
	 * 	If we are basing the new kinsoku table on an existing one, the WideStrings 
	 * 	in 'data' will simply be added on, but we are not supposed to have duplicates,
	 *  or the  Japanese text composer might get confused. This will remove duplicates.
	 * 
	 *	@param ws IN The workspace on which the new kinsoku table should be created. 
	 * 	@param baseKinsokuTableUID IN The UID of the kinsoku table to base the new one on.
	 * 		If you want to base the new kinsoku table on the Root style (empty), 
	 * 		set this to kInvalidUID.
	 *	@param data IN/OUT The kinsoku table data settings for the new kinsoku table. 
	 * 		Pass IN what you want to add to the existing kinsoku table (identified by
	 * 		basedOnUID), and what you get OUT is only what needs to be added.
	 */
	void FilterDuplicateSettings(IWorkspace* ws, 
								 const UID& basedOnUID, 
								 SnpKinsokuTableSettings& data);

	/** Removes duplicate characters from WideStrings, so that the addString
	 * 	is left only with characters that don't belong in the baseString. 
	 * 	@param baseString IN The original string. 
	 * 	@param addString IN/OUT The string with potentially duplicated characters.
	 * 		After this method is complete, addString should only contain 
	 * 		characters that don't belong in baseString. 
	 * 	@return Number of characters stripped from addString.
	 */
	int32 RemoveDuplicates(const WideString& baseString, WideString& addString);

	
	/** Determines if a kinsoku table is one that could be deleted.
	 *	@param ws IN The workspace that contains the kinsoku table to be deleted.
	 * 	@param kinsokuTableUIDToDelete IN The UID for the kinsoku table to be deleted. 
	 * 	@return kTrue if it can be deleted, kFalse otherwise.
	 */
	bool16 CanBeDeleted(IWorkspace* ws, 
						const UID& kinsokuTableUIDToDelete);


	/** Reports the kinsoku table data to SNIPLOG.
	 * 	@param data IN The kinsoku table settings to report.
	 */
	void ReportKinsokuTableData(const SnpKinsokuTableSettings& data);

	/** Reports characters in a WideString one by one to SNIPLOG.
	 * 	@param s IN The WideString to report.
	 */
	void ReportWideString(const WideString& s);

	/** Gets the names of the kinsoku tables.
	 * 	@param kinsokuNameTable IN The IStyleNameTable interface for 
	 * 		kinsoku tables on a specific workspace. 
	 * 	@return A list of kinsoku table names.
	 */
	K2Vector<PMString> GetKinsokuTableNames(IStyleNameTable* kinsokuNameTable);


};


/* CreateKinsokuTable
*/
ErrorCode SnpPerformKinsokuTable::CreateKinsokuTable(IWorkspace* ws, 
													 const SnpKinsokuTableSettings& data,
													 const UID& baseKinsokuTableUID,
													 UID& newKinsokuTableUID)
{
	ErrorCode status = kFailure;
	do
	{
		// check for preconditions
		if (ws == nil || 
			data.fName.empty())
		{ 
			ASSERT_FAIL("preconditions are not met (CreateKinsokuTable()) - exiting.");
			break; 
		}
		
		IDataBase* db = ::GetDataBase(ws);
		ASSERT(db);
		
		// find the kinsokd name table on the workspace
		InterfacePtr<IStyleNameTable> kinsokuNameTable(ws, IID_IKINSOKUNAMETABLE);
		if (kinsokuNameTable == nil) 
		{ 
			ASSERT(kinsokuNameTable); 
            break; 
		}
        
		// find if the new name is already in the table
		const UID newTableUID = kinsokuNameTable->FindByName(data.fName);
		if (newTableUID != kInvalidUID)
		{
			SNIPLOG("The kinsoku table '%s' already exists - therefore will not be created.", data.fName.GetPlatformString().c_str());
			newKinsokuTableUID = newTableUID;
			status = kSuccess;
			break;
		}

		// create the CreateKinsokuTable command
		InterfacePtr<ICommand> createKinsokuTableCmd(CmdUtils::CreateCommand(kCreateKinsokuTableCmdBoss));
		if (createKinsokuTableCmd == nil) 
		{ 
			ASSERT(createKinsokuTableCmd); 
			break; 
		}

		// set the workspace for the command
		createKinsokuTableCmd->SetItemList(UIDList(ws));

		// set the name of the new kinsoku table
		InterfacePtr<IStringData> kinsokuTableNameStringData(createKinsokuTableCmd, UseDefaultIID());
		if (kinsokuTableNameStringData == nil) 
		{ 
			ASSERT(kinsokuTableNameStringData); 
			break; 
		}
		kinsokuTableNameStringData->Set(data.fName);
		
		// set the database and base UID for the new kinsoku table
		InterfacePtr<IUIDData> baseUIDData(createKinsokuTableCmd, UseDefaultIID());
		if (baseUIDData == nil) 
		{ 
			ASSERT(baseUIDData); 
			break; 
		}
		baseUIDData->Set(db, baseKinsokuTableUID);

        // process the command
		status = CmdUtils::ProcessCommand(createKinsokuTableCmd);
		if (status != kSuccess) 
		{
			// something went wrong - don't continue
			break;
		}

		// go find the newly created kinsoku table
		// NOTE: this is returned via the parameter list
		UIDRef newKinsokuTableUIDRef = UIDRef(db, kinsokuNameTable->FindByName(data.fName));
		if (newKinsokuTableUIDRef.ExistsInDB() == kFalse) 
		{ 
			ASSERT_FAIL("New kinsoku table isn't found after the create command - was it really created?"); 
			status = kFailure;
			break;
		}
		
		// set the data for the newly created kinsoku table
		InterfacePtr<IKinsokuTable> newKinsokuTable(newKinsokuTableUIDRef, UseDefaultIID());
		if (newKinsokuTable == nil) 
		{ 
			ASSERT(newKinsokuTable); 
			status = kFailure;
			break; 
		}
		if (baseKinsokuTableUID == kInvalidUID) 
		{
			// if no base table, clear the current set.
			newKinsokuTable->Clear();
		}

		if (newKinsokuTable->GetEditability())
		{
			// add kinsoku characters
            // NOTE: this dirties the database! (Should really be a command for undoability)
			CmdUtils::AutoUndoSequencePtr seq(db);
			
			newKinsokuTable->AddKinsokuBefore(data.fKinsokuBefore);
			newKinsokuTable->AddKinsokuAfter(data.fKinsokuAfter);
			newKinsokuTable->AddKinsokuHanging(data.fKinsokuHanging);
			newKinsokuTable->AddKinsokuNotSeparate(data.fKinsokuNotSeparate);
			// note: this really doesn't do anything, as GetEditability will always return kTrue
			newKinsokuTable->SetEditability(data.fEditability);            
		}
		else
		{
			ASSERT_FAIL("Kinsoku table is not editable! ");
		}

		// everything went well, so return status=success 
		status = kSuccess;
		newKinsokuTableUID = newKinsokuTableUIDRef.GetUID();

	} while (false);

	// adjust the UID to return in case of an error.
	if (status != kSuccess) 
	{
		newKinsokuTableUID = kInvalidUID;
	}
	return status;
}

/* DeleteKinsokuTable
 */
ErrorCode SnpPerformKinsokuTable::DeleteKinsokuTable(IWorkspace* ws, 
													 const UID& kinsokuTableUIDToDelete)
{
	ErrorCode status = kFailure;
	do {
		if (ws == nil || 
			kinsokuTableUIDToDelete == kInvalidUID) 
		{
			ASSERT_FAIL("One or more input conditions are not met (DeleteKinsokuTable()) - exiting...");
			break;
		}
		// create the delete kinsoku table cmd
		InterfacePtr<ICommand> deleteKinsokuTableCmd(CmdUtils::CreateCommand(kDeleteKinsokuTableCmdBoss));
		if (deleteKinsokuTableCmd == nil) 
		{
			ASSERT(deleteKinsokuTableCmd); 
			break;
		}
		// set the item list (the workspace)
        deleteKinsokuTableCmd->SetItemList(UIDList(ws));

		// set the UID to delete
		InterfacePtr<IUIDData> uidData(deleteKinsokuTableCmd, UseDefaultIID());
		if (uidData == nil) 
		{
			ASSERT(uidData);
			break;
		}
		IDataBase* db = ::GetDataBase(ws);
		uidData->Set(db, kinsokuTableUIDToDelete);

		// process the command
        status = CmdUtils::ProcessCommand(deleteKinsokuTableCmd);
		ASSERT(status == kSuccess);

	} while (false);
	return status;
}

/* InspectKinsokuTable
*/
ErrorCode SnpPerformKinsokuTable::InspectKinsokuTable(IWorkspace* ws, 
													  const UID& kinsokuTableUIDToInspect,
													  SnpKinsokuTableSettings& data)
{
	ErrorCode status = kFailure;
	do 
	{
		// check preconditions
		if (ws == nil || 
			kinsokuTableUIDToInspect == kInvalidUID) 
		{
			ASSERT_FAIL("One or more input conditions are not met (InspectKinsokuTable()) - exiting...");
			break;
		}

		// get the kinsoku table from the workspace. 
		IDataBase* db = ::GetDataBase(ws);
		if (db == nil)
		{ 
			ASSERT(db);
			break;
		}

		// query the kinsoku table from the UID
		InterfacePtr<IKinsokuTable> kinsokuTable(db, kinsokuTableUIDToInspect, UseDefaultIID());
		if (kinsokuTable == nil) 
		{ 
			ASSERT(kinsokuTable); 
			break; 
		}

		// unravel all of the data in IKinsokuTable into the SnpKinsokuTableSettings struct.
		kinsokuTable->GetKinsokuAfter(data.fKinsokuAfter);
		kinsokuTable->GetKinsokuBefore(data.fKinsokuBefore);
		kinsokuTable->GetKinsokuHanging(data.fKinsokuHanging);
		kinsokuTable->GetKinsokuNotSeparate(data.fKinsokuNotSeparate);
		data.fEditability = kinsokuTable->GetEditability();

		InterfacePtr<IStringData> kinsokuTableNameStringData(kinsokuTable, UseDefaultIID());
		if (kinsokuTableNameStringData == nil) 
		{
			ASSERT(kinsokuTableNameStringData);
			break;
		}
		data.fName = kinsokuTableNameStringData->Get();


		// report the data.
		this->ReportKinsokuTableData(data);

		status = kSuccess;

	} while (false);
	return status;
}

/* SetKinsokuTableSettings
	NOTE: Modify this to suit your needs. 
*/
void SnpPerformKinsokuTable::SetKinsokuTableSettings(const PMString& kinsokuTableName, 
													 SnpKinsokuTableSettings& data)
{
	// always kTrue!
	data.fEditability = kTrue;

	// name of the kinsoku table
	data.fName = kinsokuTableName;

	// NOTE: These characters are based on a subset of the soft kinsoku character set.
	// 		Also, not all of the "added" characters may render in the specific UI font 
	// 		used on the	Kinsoku settings dialog.

	// (Gyoumatsu kinshi moji)
	PMString kinsokuBeforeString;
    kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_IdeographicComma));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_IdeographicFullStop));
    kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthComma));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthStop));
    kinsokuBeforeString.AppendW(UTF32TextChar(0x30FB)); // Katakana Middle Dot
    kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthColon));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthSemiColon));
    kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthQuestionMark));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthExclamationMark));
    kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_RightSingleQuotationMark));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_RightDoubleQuotationMark));
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_Dagger)); // added
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_DoubleDagger)); // added
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_Bullet)); // added
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_FullWidthCentSign)); // added
	kinsokuBeforeString.AppendW(UTF32TextChar(kTextChar_Integral)); // added
	data.fKinsokuBefore = WideString(kinsokuBeforeString);

	// (Gyoutou kinshi moji)
	PMString kinsokuAfterString;
    kinsokuAfterString.AppendW(UTF32TextChar(kTextChar_LeftSingleQuotationMark));
	kinsokuAfterString.AppendW(UTF32TextChar(kTextChar_LeftDoubleQuotationMark));
	kinsokuAfterString.AppendW(UTF32TextChar(kTextChar_DegreeCelsius)); // added
	kinsokuAfterString.AppendW(UTF32TextChar(kTextChar_DegreeFahrenheit)); // added
	kinsokuAfterString.AppendW(UTF32TextChar(kTextChar_TrademarkSign)); // added
    data.fKinsokuAfter = WideString(kinsokuAfterString);

	// (Burasagari kinshi moji)
	PMString kinsokuHangingString;
    kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_IdeographicComma));
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_IdeographicFullStop));
    kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_FullWidthStop));
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_FullWidthComma));
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_ApproxEqual)); // added
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_NotEqual));// added
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_LessEqual));// added
	kinsokuHangingString.AppendW(UTF32TextChar(kTextChar_GreaterEqual));// added
	data.fKinsokuHanging = WideString(kinsokuHangingString);

	// (Bunri kinshi moji)
	PMString kinsokuNotSeparateString;
    kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_EmDash));
	kinsokuNotSeparateString.AppendW(UTF32TextChar(0x2025));
    kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_Ellipse));
	kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_ApproxEqual)); // added
	kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_NotEqual));// added
	kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_LessEqual));// added
	kinsokuNotSeparateString.AppendW(UTF32TextChar(kTextChar_GreaterEqual));// added
	data.fKinsokuNotSeparate = WideString(kinsokuNotSeparateString);

}


/* FilterDuplicateSettings
*/
void SnpPerformKinsokuTable::FilterDuplicateSettings(IWorkspace* ws, 
													 const UID& basedOnUID, 
													 SnpKinsokuTableSettings& data)
{
	do {
		if (basedOnUID == kInvalidUID) 
		{
			// there is no need to filter anything out, as we are creating a new 
			// kinsoku table.
			break;
		}

		if (ws == nil) 
		{
			ASSERT_FAIL("IWorkspace is nil!");
			break;
		}
		IDataBase* db = ::GetDataBase(ws);
		if (db == nil) 
		{
			ASSERT_FAIL("DataBase is nil!");
			break;
		}

		// query the kinsoku table from the UID
		InterfacePtr<IKinsokuTable> kinsokuTable(db, basedOnUID, UseDefaultIID());
		if (kinsokuTable == nil) 
		{ 
			ASSERT(kinsokuTable); 
			break; 
		}

		// get each of the WideStrings locally, and strip them of duplicates
		// fEditability and fName are left untouched.
		SnpKinsokuTableSettings localData;
		
		kinsokuTable->GetKinsokuAfter(localData.fKinsokuAfter);
		int32 numStrippedAfter = this->RemoveDuplicates(localData.fKinsokuAfter, data.fKinsokuAfter);
		
		kinsokuTable->GetKinsokuBefore(localData.fKinsokuBefore);
		int32 numStrippedBefore = this->RemoveDuplicates(localData.fKinsokuBefore, data.fKinsokuBefore);
		
		kinsokuTable->GetKinsokuHanging(localData.fKinsokuHanging);
		int32 numStrippedHanging = this->RemoveDuplicates(localData.fKinsokuHanging, data.fKinsokuHanging);
		
		kinsokuTable->GetKinsokuNotSeparate(localData.fKinsokuNotSeparate);
		int32 numStrippedNotSeparate = this->RemoveDuplicates(localData.fKinsokuNotSeparate, data.fKinsokuNotSeparate);

	} while (false);
}

/* RemoveDuplicates
*/
int32 SnpPerformKinsokuTable::RemoveDuplicates(const WideString& baseString, WideString& addString)
{
	int32 numCharsStripped = 0;

	// visit all characters in baseString, and strip them out of addString
	WideString::const_iterator iter = baseString.begin();
	while (iter != baseString.end()) 
	{
		UTF32TextChar c = *iter;
		int32 newCharsStripped = addString.Strip(c);
		numCharsStripped += newCharsStripped;
		++iter;
	}
	return numCharsStripped; 
}

/* CanBeDeleted
*/
bool16 SnpPerformKinsokuTable::CanBeDeleted(IWorkspace* ws, 
											const UID& kinsokuTableUIDToDelete)
{
	bool16 retVal = kFalse;
	do {
		if (ws == nil ||
			kinsokuTableUIDToDelete == kInvalidUID) 
		{
			ASSERT_FAIL("One or more input conditions not met - exiting");
			break;
		}
		IDataBase* db = ::GetDataBase(ws);
		if (db == nil)
		{
			ASSERT_FAIL("Could not get the database - exiting");
			break;
		}
		InterfacePtr<IStyleNameTable> kinsokuNameTable(ws, IID_IKINSOKUNAMETABLE);
		if (kinsokuNameTable == nil)
		{
			ASSERT_FAIL("Could not get the kinsokuNameTable - exiting");
			break;
		}

		// get the kinsoku table
		InterfacePtr<IKinsokuTable> kinsokuTable(db, kinsokuTableUIDToDelete, UseDefaultIID()); 
		if (kinsokuTable == nil) 
		{
			ASSERT(kinsokuTable);
			break;
		}
		
		// get the name of the kinsoku table
		InterfacePtr<IStringData> kinsokuTableNameStringData(kinsokuTable, UseDefaultIID());
		if (kinsokuTableNameStringData == nil) 
		{
			ASSERT(kinsokuTableNameStringData);
			break;
		}
        PMString name = kinsokuTableNameStringData->Get();
		if (name.HasTranslated() == kFalse)
		{
			name.Translate();
		}
		SNIPLOG("---Checking if '%s' can be deleted...", name.GetPlatformString().c_str());
		
		// decision tree:
		// * if the table isn't editable, don't delete.
		// * otherwise, you can delete

        // see if the table is editable
		if (kinsokuTable->GetEditability() == kFalse) 
		{
			//   NOTE: The Kinsoku_Weak and Kinsoku_Strong tables will 
			//			return kFalse for GetEditability() and cannot
			//			be deleted.  Other kinsoku tables that you create 
			//			with kCreateKinsokuTableCmdBoss can always be deleted. 
			
			// no, you can't delete this.
			retVal = kFalse;
			SNIPLOG("---'%s' can NOT be deleted\n", name.GetPlatformString().c_str());
			break;
		}

		// if we got here, we can delete
		retVal = kTrue;
		SNIPLOG("---'%s' can be deleted\n", name.GetPlatformString().c_str());

	} while (false);

	return retVal;
}


/* ReportKinsokuTableData
*/
void SnpPerformKinsokuTable::ReportKinsokuTableData(const SnpKinsokuTableSettings& data)
{
	// unravel all of the kinsoku table data
	SNIPLOG("=== Kinsoku table data ===");
	SNIPLOG(" name: \"%s\"", data.fName.GetPlatformString().c_str());
	SNIPLOG(" editabilty: \"%s\"", (data.fEditability ? "TRUE" : "FALSE"));

	SNIPLOG(" KinsokuBefore (Gyoumatsu kinsoku):");
	this->ReportWideString(data.fKinsokuBefore);
	SNIPLOG(" KinsokuAfter (Gyoutou kinsoku):");
	this->ReportWideString(data.fKinsokuAfter);
	SNIPLOG(" KinsokuHanging (Burasagari kinshi):");
	this->ReportWideString(data.fKinsokuHanging);
	SNIPLOG(" fKinsokuNotSeparate (Bunri kinshi):");
	this->ReportWideString(data.fKinsokuNotSeparate);
}

/* ReportWideString
*/
void SnpPerformKinsokuTable::ReportWideString(const WideString& s)
{
	if (s.empty()) 
	{
		SNIPLOG("  (Empty string)");
	}
	else
	{
		SNIPLOG("  CharCount: %d", s.CharCount());
		WideStringConstUTF32Iter iter = s.begin();
		int32 i = 0;
		while (iter != s.end()) 
		{
			// extract the next UTF32TextChar
			UTF32TextChar c = *iter;
			// make a PMString for display
			PMString onechar;
			onechar.AppendW(c);
			SNIPLOG("  [%d]: '%s' (0x%X)", i, onechar.GetPlatformString().c_str(), c.GetValue());
			iter++;
			i++;
		}
	}
}

/* GetKinsokuTableNames
*/
K2Vector<PMString> SnpPerformKinsokuTable::GetKinsokuTableNames(IStyleNameTable* kinsokuNameTable)
{
	K2Vector<PMString> kinsokuTableNames;
	kinsokuTableNames.clear();
	do 
	{
		if (kinsokuNameTable == nil) 
		{
			ASSERT_FAIL("kinsokuNameTable is nil!  I can't get the table names.");
			break;
		}
		IDataBase* db = ::GetDataBase(kinsokuNameTable);
		if (db == nil) 
		{
			ASSERT_FAIL("db is nil!");
			break;
		}
		int32 numStyles = kinsokuNameTable->GetNumStyles();
		
		// iterate through each kinsoku table in the list
		for (int32 i = 0 ; i < numStyles ; i++) 
		{
			UID kinsokuTableUID = kinsokuNameTable->GetNthStyle(i);
			InterfacePtr<IStringData> stringData(db, kinsokuTableUID, UseDefaultIID());
			if (stringData != nil) 
			{
				PMString kinsokuTableName = stringData->Get();
				kinsokuTableNames.push_back(kinsokuTableName);
			}
			else
			{
				PMString badKinsokuTable("<invalid kinsoku table ");
				badKinsokuTable.AppendNumber(i);
				badKinsokuTable.Append(">");
				kinsokuTableNames.push_back(badKinsokuTable);
			}
		}
					  
	} while (false);
	return kinsokuTableNames;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerPerformKinsokuTable : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerPerformKinsokuTable(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerPerformKinsokuTable(void);

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
		
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunWorkspaceContext;}
};

/* Constructor.
*/
_SnpRunnerPerformKinsokuTable::_SnpRunnerPerformKinsokuTable() : SnpRunnable("PerformKinsokuTable")
{
	this->SetDescription("Creates, Deletes, and Inspects a kinsoku table");
	this->SetPreconditions("Active workspace");
	this->SetCategories("sdk_snippet, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerPerformKinsokuTable::~_SnpRunnerPerformKinsokuTable(void)
{
	// do nothing.
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformKinsokuTable::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		if (runnableContext == nil) 
		{
			// this would be bad!
			break; 
		}
		// get the active workspace.
		IWorkspace* ws = runnableContext->GetActiveContext()->GetContextWorkspace();
		if (ws == nil) 
		{
			break;
		}
		// get the kinsoku table from the workspace. 
        InterfacePtr<IStyleNameTable> kinsokuNameTable(ws, IID_IKINSOKUNAMETABLE);
		if (kinsokuNameTable == nil) 
		{
			break;
		}

		// if we got here, we can run the snippet.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformKinsokuTable::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	static int32 tableNumber = 0;

	do {
		SnpPerformKinsokuTable instance;
		if (runnableContext == nil) 
		{
			// this would be bad!
			break; 
		}
		// get the active workspace.
		IWorkspace* ws = runnableContext->GetActiveContext()->GetContextWorkspace();
		if (ws == nil) 
		{
			ASSERT_FAIL("Can't get active workspace!");
			break;
		}
		// get the kinsoku table from the workspace. 
        InterfacePtr<IStyleNameTable> kinsokuNameTable(ws, IID_IKINSOKUNAMETABLE);
		if (kinsokuNameTable == nil) 
		{
			ASSERT_FAIL("Can't get kinsoku name table!");
			break;
		}

		// -------------------------------------------------------
		// get user choices
		// -------------------------------------------------------
		Utils<ISnipRunParameterUtils> parameterUtils;
		
		// what do you want to do?
		// inspect, create, delete
		enum { kKinsokuTableInspect, kKinsokuTableCreate, kKinsokuTableDelete };
		K2Vector<PMString> operations;
		operations.clear();
		operations.push_back("inspect a kinsoku table"); // kInspect (default)
		operations.push_back("create new kinsoku table"); // kCreate
		operations.push_back("delete a kinsoku table"); // kDelete
		int32 operation = parameterUtils->GetChoice("What operation do you want to perform?", operations, kKinsokuTableInspect);
		if (parameterUtils->WasDialogCancelled()) 
		{
			// user cancelled! get out of do-while loop
			break;
		}
		
		// get the current list of kinsoku tables on the workspace
		K2Vector<PMString> currentKinsokuTables = instance.GetKinsokuTableNames(kinsokuNameTable);
		// get the number of "actual" kinsoku tables on the workspace.
		int32 numAvailableTables = currentKinsokuTables.size();

		SnpKinsokuTableSettings data;

		switch (operation) 
		{
		default:
            {
				SNIPLOG("Invalid option - using default.");
				// no break, fall through.
			}
		case kKinsokuTableInspect:
			{
				if (currentKinsokuTables.size() > 0)
				{
					// get the choice of kinsoku table to inspect 
					int32 choiceToInspect = parameterUtils->GetChoice("Which kinsoku table do you want to inspect?", currentKinsokuTables, 0);
					if (parameterUtils->WasDialogCancelled()) 
					{
						// user cancelled! 
						break; // get out of switch
					}
					UID kinsokuTableToInspect = kinsokuNameTable->GetNthStyle(choiceToInspect);
					status = instance.InspectKinsokuTable(ws, kinsokuTableToInspect, data);					
				}
				else
				{
					SNIPLOG("There is no kinsoku table to inspect");
					status = kSuccess;
				}
			}
			break;
		case kKinsokuTableCreate:
			{
				PMString defaultKinsokuTable("MyNewKinsokuTable", PMString::kEncodingASCII);
				defaultKinsokuTable.AppendNumber(tableNumber++);
				PMString kinsokuTableName = parameterUtils->GetPMString("Specify the name of the new kinsoku table.", defaultKinsokuTable);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
	
				// set up the basis for the new composite font.
				// kInvalidUID will make a completely new one. 
				UID basedOnUID = kInvalidUID;
				// add a "<none>" at the end so that user can make a totally new one.
				currentKinsokuTables.push_back(PMString("<none>"));
				// get the choice of composite font to base 
				int32 choiceToCreate = parameterUtils->GetChoice("Which kinsoku table do you want to use as a basis?", currentKinsokuTables, numAvailableTables);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
				// user didn't choose "<none>", so get the actual composite font UID.
				if (choiceToCreate < numAvailableTables) 
				{
					basedOnUID = kinsokuNameTable->GetNthStyle(choiceToCreate);
				}
	
				// -------------------------------------------------------
				// now we are ready to create the composite font!!!
				// -------------------------------------------------------
				UID newKinsokuTableUID;
	
				// set various comppsite font settings
				instance.SetKinsokuTableSettings(kinsokuTableName, data);

				if (basedOnUID != kInvalidUID) 
				{
					// If we are basing the new kinsoku table on an old one,
					// the WideStrings in 'data' will simply be added on, but
					// we are not supposed to have duplicates, or the 
					// Japanese text composer might get confused. This will
					// remove duplicates.
					instance.FilterDuplicateSettings(ws, basedOnUID, data);
				}

				// call the commands to create the kinsoku tbale
				// the newly created UID is in 'newKinsokuTableUID'
				status = instance.CreateKinsokuTable(ws, data, basedOnUID, newKinsokuTableUID);
				if (status != kSuccess) 
				{
					ASSERT_FAIL("Error from CreateKinsokuTable!"); 
					break; // get out of switch
				}
	
				SNIPLOG("New kinsoku table %s (UID 0x%X) successfully created.", 
						kinsokuTableName.GetPlatformString().c_str(), newKinsokuTableUID.Get());
			}
			break;
		case kKinsokuTableDelete:
			{
				if (currentKinsokuTables.size() > 0)
				{
					// get the choice of kinsoku table to delete
					int32 choiceToDelete = parameterUtils->GetChoice("Which kinsoku table do you want to delete?", currentKinsokuTables, 0);
					if (parameterUtils->WasDialogCancelled()) 
					{
						// user cancelled! 
						break; // get out of switch
					}
					UID kinsokuTableToDelete = kinsokuNameTable->GetNthStyle(choiceToDelete);

					// check if this kinsoku table can be deleted
					if (instance.CanBeDeleted(ws, kinsokuTableToDelete) == kFalse) 
					{
						SNIPLOG("The selected kinsoku table should not be deleted. Cancelling.");
						break; // get out of switch
					}
					
					// go delete the kinsoku table
					status = instance.DeleteKinsokuTable(ws, kinsokuTableToDelete);
				}
				{
					SNIPLOG("There is no kinsoku table to delete");
					status = kSuccess;
				}
			}
			break;
		}

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformKinsokuTable instance_SnpRunnerPerformKinsokuTable;
DEFINE_SNIPPET(_SnpRunnerPerformKinsokuTable) 	

// End, SnpPerformKinsokuTable.cpp

