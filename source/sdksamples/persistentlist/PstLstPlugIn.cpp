//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstPlugIn.cpp $
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

// API includes
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IUIDIterator.h"

// General includes:
#include "CmdUtils.h"
#include "PersistUtils.h"
#include "PlugIn.h"
#include "UIDList.h"

// Project includes:
#include "IPstLstData.h"
#include "IPstLstUIDList.h"
#include "PstLstID.h"

// DEBUG ONLY:
#ifdef DEBUG
#include "IDocumentUtils.h"
#include "ProgressBar.h" // for TaskProgressBar
#include "Utils.h"
#endif


/** This is the entry point for the plug-in that specialises FixUpData
 *	to clear up stale data created when a document containing this
 *	plug-in's data is edited while this plug-in is missing.
 * 	
 *	@ingroup persistentlist
 *	
*/
class PstLstPlugIn : public PlugIn
{
public:
	/** Called when a document with persistent data from 
	 *	this plug-in was edited without the 
	 *	presence of this plug-in. Gives this plug-in
	 * the chance to fix any stale data it might
	 * have in the document.
	 * 
	 * 	@param doc IN The document currently being opened.
	 */
	virtual void FixUpData(IDocument* doc);

};

/* Create a static instance so that this class
	available during the lifetime of the plug-in.
*/
static PstLstPlugIn gPlugIn;

/* This is the main entry point from the application to the plug-in. The application calls
	this function when the plug-in is installed or loaded. This function is called by name,
	so it must be called GetPlugIn, and defined as C linkage.
*/
IPlugIn* GetPlugIn()
{
	return &gPlugIn;
}

/*
*/
void PstLstPlugIn::FixUpData(IDocument* doc)
{	
	TRACEFLOW(kPstLstPluginName, "PstLstPlugIn::FixUpData()-->In\n");
	do
	{
		if (doc == nil)
		{
			ASSERT(doc);
			break;
		}
		IDataBase* db = ::GetDataBase(doc);
		if (db == nil)
		{
			ASSERT(db);
			break;
		}

		// Check that each of the kPstLstDataBoss object
		// in the document is owned. Objects that are not
		// owned are added to a list of orphans that this
		// method deletes from the document. Orphaned objects
		// can be created by missing plug-in workflows like this:
		// 1) Create a document with a frame and associated a
		// kPstLstDataBoss object with it using this plug-in.
		// 2) Save and close the document.
		// 3) Quit InDesign and restart without this plug-in.
		// 4) Open the document and dismiss the Missing Plugin
		// dialog using the OK button, don't strip missing plug-in
		// data.
		// 5) Delete the frame, this orphans the kPstLstDataBoss object
		// because this plug-in isn't around to clean it up.
		// 6) Quit InDesign and restart with this plug-in.
		// 7) Open the document and this method (FixUpData) will
		// be called to fix up any data that might have gone stale
		// since the document was edited while this plug-in was missing.

		// A list of all the UIDs whose ClassID is kPstLstDataBoss.
		K2Vector<UID> dataBossUIDs;
		// A list of all the UIDs of kPstLstDataBoss objects that are owned by another boss object.
		// The ownership association is stored in interface IPstLstUIDList. 
		K2Vector<UID> ownedDataBossUIDs;
		// Iterate over all the UIDs in the database to create the lists described above.
		IUIDIterator* uidIter = db->NewUIDIterator();
		for (UID uid = uidIter->First(); uid != kInvalidUID; uid = uidIter->Next())
		{
			if (db->GetClass(uid) == kPstLstDataBoss) 
			{
				dataBossUIDs.push_back(uid);
			}
			InterfacePtr<IPstLstUIDList> pstLstUIDList(db, uid, UseDefaultIID());
			if (pstLstUIDList) 
			{
				const UIDList* list = pstLstUIDList->GetUIDList();
				for (int32 i = 0 ; i < list->Length(); i++)
				{
					ownedDataBossUIDs.push_back((*list)[i]);
				}
			}
		}
		db->DeleteUIDIterator(&uidIter);

		// Now build a list containing the UID's of orphaned kPstLstDataBoss 
		// objects. For example, if the user deletes a frame that owns
		// some kPstLstDataBoss objects while the PersistentList
		// plug-in is missing, the kPstLstDataBoss objects will be orphaned because 
		// the plug-in wasn't around to clean them up. Take the opportunity
		// to detect and clean them up now.
		UIDList orphanedDataBossUIDs(db);		
		for (K2Vector<UID>::iterator iter = dataBossUIDs.begin(); iter < dataBossUIDs.end(); iter++)
		{
			K2Vector<UID>::iterator result = std::find(ownedDataBossUIDs.begin(), ownedDataBossUIDs.end(), *iter);
			if (result == ownedDataBossUIDs.end()) 
			{
				TRACEFLOW(kPstLstPluginName, "Orphaned kPstLstDataBoss object UID 0x%x deleted\n", (*iter).Get());
				orphanedDataBossUIDs.Append(*iter);
			}
		}
		if (orphanedDataBossUIDs.Length() == 0)
		{
			// No orphans, we're done.
			break;
		}
		
		// Delete orphaned kPstLstDataBoss objects from the document.
		InterfacePtr<ICommand> deleteUIDsCmd(CmdUtils::CreateCommand(kDeleteUIDsCmdBoss));
		ASSERT(deleteUIDsCmd);
		if (!deleteUIDsCmd)
		{
			break;
		}
		// Don't show the command in undo/redo menu.
		deleteUIDsCmd->SetUndoability(ICommand::kAutoUndo);
	    deleteUIDsCmd->SetItemList(orphanedDataBossUIDs);
		ErrorCode status = CmdUtils::ProcessCommand(deleteUIDsCmd);
		ASSERT_MSG(status == kSuccess, "kDeleteUIDsCmdBoss failed to delete orphaned kPstLstDataBoss objects");
		
#ifdef DEBUG
		// Just to be extra safe, we want to make sure that we don't 
		// have any UID leaks in this document by means of doing this check.
		{
			PMString debugProgressString("Check for UID Leaks (Debug only)");
			debugProgressString.SetTranslatable(kFalse);
			TaskProgressBar progress(debugProgressString, 1);
			progress.DoTask();
			bool8 leakcheckStatus = Utils<IDocumentUtils>()->CheckForLeaks(db);
			ASSERT(leakcheckStatus == kTrue);
		}
#endif
	} while (false);
	TRACEFLOW(kPstLstPluginName, "PstLstPlugIn::FixUpData()-->Out\n");
}

// End, PstLstPlugIn.cpp.
