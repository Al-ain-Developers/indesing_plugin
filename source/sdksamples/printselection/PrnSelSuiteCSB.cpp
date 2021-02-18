//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/printselection/PrnSelSuiteCSB.cpp $
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
#include "ICallback.h"
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDrawMgr.h"
#include "IHierarchy.h"
#include "ILayoutUtils.h"
#include "IMasterPage.h"
#include "IPrintCmdData.h"
#include "ISelectionUtils.h"
#include "IShape.h" // for kDefaultIID

// General includes:
#include "CmdUtils.h"
#include "CPMUnknown.h"
#include "LocaleSetting.h"
#include "PrintID.h" // for print command IDs
#include "UIDList.h"

// Project includes:
#include "IPrnSelData.h"
#include "IPrnSelUtils.h"
#include "IPrnSelSuite.h"
#include "PrnSelID.h"
#include "PrnSelSuiteCSB.h"

/** Callback class used to in conjunction with IDrawMgr to
gather all contained page items from a list of selected
top level page items.  Instead of walking the document hierarchy
and dealing wiht any special cases such as inlines we use
the Draw Manager to iterate the exact children.

@ingroup printselection

*/
class PageItemCollector : public ICallback
{
public:

	/** Constructor
		@param data IN The IPrnSelData interface we are populating.
		@param drawMgr IN The IDrawMgr that is calling back into this class.
	*/
	PageItemCollector (IPrnSelData * data, IDrawMgr *drawMgr) : fData(data), fDrawMgr(drawMgr)
	{ }

	/** The actual callback method.
		@param xform IN The current transform.
		@param thing IN The current object in the draw order.
		@param flags IN The draw flags.
	*/
    virtual void ExecuteCallback(const PMMatrix *, IPMUnknown *thing, int32 flags);

	/** @return The IDrawMgr instance for this callback.
	*/
	virtual IDrawMgr *GetCallbackDrawManager()
	{ 
		return fDrawMgr;
	}

private:

	/* We keep the IDrawMgr and stuff the data into IPrnselData interface.
	*/
	IPrnSelData * fData;
	IDrawMgr *fDrawMgr;
};



/* Constructor
*/
PrnSelSuiteCSB::PrnSelSuiteCSB(IPMUnknown* boss)
:	CPMUnknown<IPrnSelSuite>(boss)
{
	// do nothing
}

/* Destructor. 
 */
PrnSelSuiteCSB::~PrnSelSuiteCSB(void)
{
	// do nothing
}

/* StoreSelectionData
*/
void PrnSelSuiteCSB::StoreSelectionData(void)
{
	do
	{
		// Get list of selected page items.
		UIDList itemList = this->GetItemList();

		// check the item list
		if (itemList.Length() == 0 ||
			itemList.GetDataBase() == nil)
		{
			ASSERT_FAIL("The itemList is empty or is not associated with a database");
			break;
		}
		// Get our data interface to store selected items.
		InterfacePtr<IDocument> doc(itemList.GetDataBase(), itemList.GetDataBase()->GetRootUID(), UseDefaultIID());
		InterfacePtr<IPrnSelData> psData(doc, UseDefaultIID());
		if (psData == nil)
		{
			ASSERT_FAIL("psData is nil");
			break;
		}

		// Save off the UIDs of the page items in the selection.
		for (int32 k = 0 ; k < itemList.Length() ; k++)
		{
			// We use the IDrawMgr to accurately iterate through the
			// the selected page item and its children.  Doing it this way instead of walking
			// the hierarchy ourselves will pick up more complex page items such
			// as inlines and any other page items that for some creative reason
			// are not in the hierarchy.
			InterfacePtr<IDrawMgr> drawMgr ((IDrawMgr *)::CreateObject (kDrawMgrBoss, IID_IDRAWMGR));
			PageItemCollector	pageItemCollector (psData, drawMgr);
			const int32		drwMgrFlags = IShape::kSkipHiddenLayers + IShape::kSkipGuideLayers;

			// Call IterateDrawOrder.  The Matrix is not important to us here.  It is important
			// that we call IterateDrawOrder with the selected page item and that we pass
			// it the address of our call back object.  In this case the drwMgrFlags are also not 
			// significant in that our callback doesn't check them.
			drawMgr->IterateDrawOrder( itemList.GetRef(k), &pageItemCollector, drwMgrFlags);
		}

		// Save off the UIDs of the pages that contain the selected page items.
		IDataBase* db = itemList.GetDataBase();
		for (int32 i=0; i<itemList.Length(); i++)
		{
			InterfacePtr<IHierarchy> hierarchy(db, itemList[i], UseDefaultIID());
			ASSERT(hierarchy);
			UID ownerUID = Utils<ILayoutUtils>()->GetOwnerPageUID(hierarchy);
			// Test ownerUID for interface IMasterPage, the signature interface for a page.
			// The selected page items may not lie on a page (i.e. they may lie on the pasteboard),
			// in which case ILayoutUtilsUtils<ILayoutUtils>()->GetOwnerPageUID will return the UID of a spread.
			InterfacePtr<IMasterPage> masterPage(db, ownerUID, UseDefaultIID());
			if (masterPage && psData->GetPageUIDHadSelection(ownerUID) == kFalse)
			{
				psData->LoadPageUID(ownerUID);
			}
		}
	} while (false);
}


/* CanGetPrintSelectionFlag
*/
bool16 PrnSelSuiteCSB::CanGetPrintSelectionFlag(void)
{
	UIDList itemList(this->GetItemList());
	return Utils<IPrnSelUtils>()->_CanGetPrintSelectionFlag(itemList);
}

/* GetPrintSelectionFlag
*/
bool16 PrnSelSuiteCSB::GetPrintSelectionFlag(void)
{
	UIDList itemList(this->GetItemList());
	IDataBase* db = itemList.GetDataBase();
	return Utils<IPrnSelUtils>()->_GetPrintSelectionFlag(db);

}

/* CanSetPrintSelectionFlag
*/
bool16 PrnSelSuiteCSB::CanSetPrintSelectionFlag(void)
{
	UIDList itemList(this->GetItemList());
	return Utils<IPrnSelUtils>()->_CanSetPrintSelectionFlag(itemList);
}

/* SetPrintSelectionFlag
*/
ErrorCode PrnSelSuiteCSB::SetPrintSelectionFlag(const bool16 printSelection)
{
	UIDList itemList(this->GetItemList());
	IDataBase* db = itemList.GetDataBase();
	return Utils<IPrnSelUtils>()->_SetPrintSelectionFlag(db, printSelection);
}

/* This method is called from the IDrawMgr and internally we simply save the 
	inform the IPrnSelData of every contained page item we encounter.
*/
void PageItemCollector::ExecuteCallback(const PMMatrix *, IPMUnknown *thing, int32 flags)
{
	UID uid = ::GetUID(thing);
	if (!fData->GetPageItemUIDHadSelection(uid))
	{
		fData->LoadPageItemUID(uid);
	}
}

// End, PrnSelSuiteCSB.cpp.
