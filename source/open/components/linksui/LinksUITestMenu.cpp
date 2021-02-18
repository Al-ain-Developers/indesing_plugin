//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/linksui/LinksUITestMenu.cpp $
//  
//  Owner: Steve Flenniken
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

#ifdef DEBUG

#include "LinksUIID.h"
#include "TestMenuComponent.h"
#include "IApplication.h"

#include "ILayoutUIUtils.h"
#include "ILink.h"
#include "ILinkFacade.h"
#include "ILinkItemSuite.h"
#include "ILinkObject.h"
#include "ILinkObjectReference.h"
#include "ISelectionManager.h"
#include "ISelectionUtils.h"
#include "IURIUtils.h"
#include "NAMEINFO.H"
#include "URI.h"
#include "IDatalink.h"


class LinksUITestMenu : public TestMenuComponent 
{
public:
	LinksUITestMenu(IPMUnknown *boss);
};


CREATE_PERSIST_PMINTERFACE(LinksUITestMenu, kLinksUITestMenuImpl)


//void TestAddNewLink(ILink::LinkType);
//void TestAddNewLink(ILink::LinkType whatKindOfLink)
//{//
////	ISelectionManager* selectionMgr = Utils<ISelectionUtils>()->GetActiveSelection();
//	IDataBase* db = selectionMgr->GetDataBase();
//	Utils<Facade::ILinkFacade> iLinkFacade;
//
//	InterfacePtr<ILinkItemSuite> iLinkItemSuite(selectionMgr, UseDefaultIID());
//	if (iLinkItemSuite) {
//		K2::scoped_ptr<UIDList> datalinks(iLinkItemSuite->CreateItemsDataLinkUIDList());
//
//		UIDList::const_iterator iterEnd(datalinks.get()->end());
//		for (UIDList::const_iterator iter(datalinks.get()->begin()); iter != iterEnd; ++iter) {
//			// validate the objects to make sure the interfaces we want are there
//			InterfacePtr<IDataLink> iDataLink(db, *iter, UseDefaultIID());
//			ASSERT_MSG(iDataLink, "TestAddNewLink - Can't instantiate IDataLink.");
//			if (!iDataLink) continue;
//
//			InterfacePtr<ILinkObjectReference> iLinkObjectRef(iDataLink, UseDefaultIID());
//			ASSERT_MSG(iLinkObjectRef, "TestAddNewLink - Can't instantiate ILinkObjectReference.");
//			if (!iLinkObjectRef) continue;
//
//			UID objectUID = iLinkObjectRef->GetUID();
//			InterfacePtr<ILinkObject> iLinkObject(db, objectUID, UseDefaultIID());
//			if (!iLinkObject) continue;
//
//			// get the path from the datalink and create a URI
//			NameInfo ni;
//			if (iDataLink->GetNameInfo(&ni, nil, nil) != 0 || !ni.GetFile()) {
//				ASSERT_FAIL("TestAddNewLink - Can't get NameInfo from datalink.");
//				continue;
//			}
//
//			URI linkURI;
//			if (!Utils<IURIUtils>()->IDFileToURI(*ni.GetFile(), linkURI)) {
//				ASSERT_FAIL("TestAddNewLink - IDFileToURI failed.");
//				continue;
//			}
//
//			// create the new link
//			UID linkUID = kInvalidUID;
//			ErrorCode err = iLinkFacade->CreateLink(whatKindOfLink, objectUID, linkURI, false, false, linkUID);
//			ASSERT_MSG(linkUID != kInvalidUID, "TestAddNewLink - Can't create link.");
//			if(err != kSuccess)
//				return;
//		}
//	}
//
//	return;
//}

void TestAddNewExportLink();
void TestAddNewExportLink()
{
//	TestAddNewLink(ILink::kExport);
}
void TestAddNewBiDirectionalLink();
void TestAddNewBiDirectionalLink()
{
//	TestAddNewLink(ILink::kBidirectional);
}

LinksUITestMenu::LinksUITestMenu(IPMUnknown *boss) :
	TestMenuComponent(boss)
{
	// Add the items in reverse order.
	AddTestMenu("New Links","Create Export Link from selection", TestAddNewExportLink,kDisableIfNoFrontLayoutView,kFalse);
	AddTestMenu("New Links","Create BiDirectional Link from selection", TestAddNewBiDirectionalLink,kDisableIfNoFrontLayoutView,kFalse);
}

#endif
