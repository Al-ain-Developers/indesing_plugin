//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstDocObserver.cpp $
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

//===========================
//  Plug-in includes
//===========================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IDocument.h"
#include "IHierarchy.h"
#include "ISubject.h"

// API includes:
#include "CAlert.h"
#include "CmdUtils.h"
#include "CObserver.h"
#include "PageItemScrapID.h" // for kDeletePageItemCmdBoss
#include "StandOffID.h" // for kDeleteStandOffItemCmdBoss and kDeleteInsetPageItemCmdBoss
#include "UIDList.h"

// Project includes:
#include "IPstLstUIDList.h"
#include "PstLstID.h"


/** This observer observes the front document's IID_IHIERARCHY_DOCUMENT protocol, so when a page 
	item is deleted from the document, this observer will be notified.  This is needed because we want 
	to be notified _Before_ the page item is about to be deleted so this implementation can have a chance
	to delete the instances of persistent list items associated with the said page item, 
	otherwise if we wait until SelectionAttributeChanged of my CSB gets called, it's too late; 
  	The page item will have been deleted from the hierarchy, and all of instances of persistent list items
	will be left dangling somewhere in memory (= boss leaks)!  This observer gets attached
	with the ISubject of kDocBoss when a document is opened or created, through the use 
  	of a open/new document responder, and this observer is detached when a document is closed, through the
	use of a close document responder.
  
	@ingroup persistentlist
	@see PstLstDocResponder
*/
class PstLstDocObserver : public CObserver
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstDocObserver(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~PstLstDocObserver();

	/** Called by the application to allow the observer to attach to the 
	 * 	subjects to be observed (kDocBoss)
	*/
	void AutoAttach();

	/** Called by the application to allow the observer to detach from the 
	 * 	subjects being observed.
	*/
	void AutoDetach();

	/** Update is called for all registered observers, and is the method 
	 * 	through which changes are broadcast. 
	 * 	In this case, the only things we are interested in are if the drop 
	 * 	down list selection has changed and if a page item is deleted from 
	 * 	the document. 
	 * 
	 * 	@param theChange IN specifies the class ID of the change to the subject. 
	 * 		Frequently this is a command ID.
	 * 	@param theSubject IN points to the ISubject interface for the subject 
	 * 		that has changed.
	 * 	@param protocol IN specifies the ID of the changed interface on the 
	 * 		subject boss.
	 * 	@param changedBy IN points to additional data about the change. 
	 * 		Often this pointer indicates the class ID of the command 
	 * 		that has caused the change.
	*/
	virtual void Update(const ClassID& theChange, 
						ISubject* theSubject, 
						const PMIID& protocol, 
						void* changedBy);

protected:
	/**	Attaches this observer to a document.
	 * 	@param iDocument IN The document to which we want to attach.
	*/
	void AttachDocument(IDocument* iDocument);

	/**	Detaches this observer from a document.
	 * 	@param iDocument IN The document from which we want to detach.
	*/
	void DetachDocument(IDocument* iDocument);

	/**	The selected page items are about to be deleted, call IPstLstSuite's 
	 * 	function to delete its associated IPstLstData objects.  
	 * 	It is called when we get the pre-notification of deletion of 
	 * 	page items.
	 * 	@param changedBy IN points to additional data about the change. 
	 *	@see PstLstDocObserver::Update
	*/
	void HandlePageItemDeleted(void* changedBy);

};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PstLstDocObserver, kPstLstDocObserverImpl)

/* PstLstDocObserver Constructor
*/
PstLstDocObserver::PstLstDocObserver(IPMUnknown* boss) 
	: CObserver(boss, IID_IPSTLSTOBSERVER)
{
}

/* PstLstDocObserver Destructor
*/
PstLstDocObserver::~PstLstDocObserver()	
{
}


/*	PstLstDocObserver::AutoAttach
*/
void PstLstDocObserver::AutoAttach()
{
	CObserver::AutoAttach();

	InterfacePtr<IDocument> iDocument(this, UseDefaultIID());
	if (iDocument != nil)
		this->AttachDocument(iDocument);
}


/*	PstLstDocObserver::AutoDetach
*/
void PstLstDocObserver::AutoDetach()
{
	CObserver::AutoDetach();

	InterfacePtr<IDocument> iDocument(this, UseDefaultIID());
	if (iDocument != nil)
		this->DetachDocument(iDocument);
}

/*	PstLstDocObserver::Update
*/
void PstLstDocObserver::Update(const ClassID& theChange, 
							   ISubject* theSubject, 
							   const PMIID& protocol, 
							   void* changedBy)
{
	do
	{
		ICommand* iCommand = (ICommand*)changedBy;
		const UIDList itemList = iCommand->GetItemListReference();

		if (protocol == IID_IHIERARCHY_DOCUMENT)
		{
			if ((theChange == kDeletePageItemCmdBoss) ||
				(theChange == kDeleteStandOffItemCmdBoss) ||
				(theChange == kDeleteInsetPageItemCmdBoss))
			{
				if (itemList.Length() && 
					(iCommand->GetCommandState() == ICommand::kNotDone))
				{
					// We only do this when we are pre-notified that a page item is about to be deleted
					// so we need to tidy up any data this plug-in may have associated with it.
					HandlePageItemDeleted(changedBy);
				}
			}
		}

	} while (kFalse);
}

/*	PstLstDocObserver::HandlePageItemDeleted
*/
void PstLstDocObserver::HandlePageItemDeleted(void* changedBy)
{
	do
	{
		ICommand* cmd = (ICommand*)changedBy;
		const UIDList* selectUIDList = cmd->GetItemList();

		if (selectUIDList->Length() < 1)
		{
			ASSERT_FAIL("invalid page item");
			break;
		}

		int32 item = selectUIDList->Length();
		UIDList myUIDList = *selectUIDList;
		// remove those items that does not have IPstLstUIDList, IPstLstUIDList is only aggregated onto
		// kDrawablePageItemBoss
		while (item-- > 0)
		{
			InterfacePtr<IPstLstUIDList> iUIDList(myUIDList.GetRef(item), UseDefaultIID());
			if (iUIDList == nil)
			{
				myUIDList.Remove(item);
			}
		}
		// If there are no items left in the list, then leave.
		if (myUIDList.Length() == 0)
		{
			break;
		}

		// item list and settings information are ok, create the command.
		InterfacePtr<ICommand> iPstlstCommand(CmdUtils::CreateCommand(kPstLstDeletePageItemCmdBoss));
		if (iPstlstCommand == nil)
		{
			// For some reason we couldn't get our command pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("Delete Page Item PstLst Command invalid");
			break;
		}

		iPstlstCommand->SetItemList(myUIDList);

		// Finally, the command is processed:
		ErrorCode error = CmdUtils::ProcessCommand(iPstlstCommand);
		// Check for errors, issue warning if so:
		if (error != kSuccess)
		{
			CAlert::WarningAlert(kPstLstDeleteItemCmdFailedKey);
		}

	} while (false);
}

/*	PstLstDocObserver::AttachDocument
*/
void PstLstDocObserver::AttachDocument(IDocument* iDocument)
{
	do
	{
		if (iDocument == nil)
		{
			ASSERT_FAIL("no document to attach to");
			break;
		}

		InterfacePtr<ISubject> iDocSubject(iDocument, UseDefaultIID());
		if (iDocSubject == nil)
		{
			ASSERT_FAIL("no document subject to attach the observer");
			break;
		}

		//	Protocols used for page item model changes
		if (!iDocSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_IPSTLSTOBSERVER))
		{
			iDocSubject->AttachObserver(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_IPSTLSTOBSERVER);
		}
	} while (kFalse);
}


/*	PstLstDocObserver::DetachDocument
*/
void PstLstDocObserver::DetachDocument(IDocument* iDocument)
{
	do
	{
		if (iDocument == nil)
		{
			ASSERT_FAIL("no document to attach to");
			break;
		}

		InterfacePtr<ISubject>      iDocSubject(iDocument, UseDefaultIID());
		if (iDocSubject == nil)
		{
			ASSERT_FAIL("no document subject to attach the observer");
			break;
		}

		if (iDocSubject->IsAttached(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_IPSTLSTOBSERVER))
		{
			iDocSubject->DetachObserver(ISubject::kRegularAttachment,this, IID_IHIERARCHY_DOCUMENT, IID_IPSTLSTOBSERVER);
		}
	} while (kFalse);
}


// End, PstLstDocObserver.cpp.

