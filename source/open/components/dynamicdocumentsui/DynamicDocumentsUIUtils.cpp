//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/DynamicDocumentsUIUtils.cpp $
//  
//  Owner: DBerggren
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
#include "DynamicDocumentsUIUtils.h"

#include "IActiveContext.h"
#include "CoreFileUtils.h"
#include "IApplication.h"
#include "IKeyBoard.h" 
#include "IKeyFocusHandler.h"
#include "IDocument.h"
#include "IDropDownListController.h"
#include "IIntData.h"
#include "IPageList.h"
#include "IPageRange.h"
#include "IPanelControlData.h"
#include "IStringListControlData.h"
#include "ITextControlData.h"
#include "ITextUIDListValue.h"
#include "ITextValue.h"
#include "ITextDataValidation.h"
#include "IEditBoxAttributes.h"
#include "IEventHandler.h"
#include "IUIDData.h"
#include "IAnimationAttributeSuite.h"
#include "IDynamicEventTimingSuite.h"
#include "IDynamicEventTimingFacade.h"
#include "UIDList.h"
#include "IDynDocsPublicUtils.h"
#include "ISelectionUtils.h"
#include "IPalettePanelUtils.h"
#include "Utils.h"
#include "ITreeViewController.h"
#include "ISysFileData.h"
#include "ISubject.h"
#include "ITriStateControlData.h"
#include "ILayoutUIUtils.h"
#include "iuicolorutils.h"
#include "IViewPort.h"
#include "IGraphicsPort.h"
#include "ITreeViewHierarchyAdapter.h"
#include "IMotionPresetMgr.h"
#include "IMotionPresetUtils.h"
#include "IAnimationUtils.h"
#include "IPageTransition.h"
#include "IInterfaceColors.h"

#include "AutoGSave.h"
#include "TimingPanelTreeNodeID.h"
#include "NodeID.h"
#include "K2Vector.tpp"
#include "DynamicDocumentsUIDefs.h"

// Those heads are for GetSelectedNonMasterSpreadsInPagesPanel
#include "IApplication.h"
#include "IHierarchy.h"
#include "IMasterSpread.h"
#include "IPanelMgr.h"
#include "ISpread.h"
#include "IUIDListControlData.h"
#include "IWidgetParent.h"
#include "IWidgetUtils.h"
#include "PagesPanelID.h"

#include "FileUtils.h"
#include "FileUtility.h"
#include "PaletteRefUtils.h"
#include "PlatformFolderTraverser.h"
#include "CAlert.h"
#include "InterfaceColorDefines.h"

#include "DVPublicUtilities.h"
#include "DVGIFPlayerView.h"

//
// ** Helper functions **
//

static char const * const kPreviewDirectoryName = "InDesign_SWFPreview";
static char const * const kExportSWFFileBaseName = "IDSWFPreview";
static char const * const kSWFFileExtension = ".swf";
static char const * const kExportSWFDefaultName = "IDSWFPreview.swf";

static bool GetPreviewDirectory(IDFile &directory, const char* dirName);

//========================================================================================
// InitializeRangeEditBox
//========================================================================================
bool16 ddui_utils::InitializeRangeEdit(IPageRange* iPageRange, IDocument* iDocument, IPanelControlData* iPanelControlData)
{
	IControlView* iControlView = iPanelControlData->FindWidget(kPagesPageRangeEditWID);
	ASSERT_MSG(iControlView != nil, "cannot find range edit widget");

	PMString pageRangeText(iPageRange->GetPageRange());

	UIDList pageRangeUIDList(::GetDataBase(iDocument));
	InterfacePtr<IPageList> iPageList(iDocument, UseDefaultIID());
	ASSERT_MSG(iPageList != nil, "cannot get IPageList from document");
	iPageList->PageRangeStringToUIDList(pageRangeText, &pageRangeUIDList);

	bool16 pageRangeValid = (pageRangeUIDList.Length() > 0);
	if (!pageRangeValid) 
	{
		// Get the page range from the document page UIDs
		int32 docPageCount = iPageList->GetPageCount();
		UID pageUID;

		for (int32 pageIndex = 0; pageIndex < docPageCount; ++pageIndex) 
		{
			pageUID = iPageList->GetNthPageUID(pageIndex);
			if (pageUID != kInvalidUID) 
			{
				pageRangeUIDList.Append(pageUID);
			}
		}
	}

	// Set the page range edit widget's UID list
	InterfacePtr<ITextUIDListValue> iTextUIDListValue(iControlView, IID_ITEXTUIDLISTVALUE);
	iTextUIDListValue->SetTextFromValue(pageRangeUIDList, kTrue, kFalse);

	if (!pageRangeValid) 
	{
		// Now get the page range UID list back from the widget and reverify
		// since IPageList will sometimes return an ambiguous string
		pageRangeUIDList.Clear();
		ITextDataValidation::RangeError rangeErr;
		iTextUIDListValue->GetTextAsValue(pageRangeUIDList, &rangeErr);

		if (rangeErr == ITextDataValidation::kNoError) 
		{
			InterfacePtr<ITextControlData> iTextControlData(iControlView, UseDefaultIID());
			pageRangeText.Clear();
			pageRangeText = iTextControlData->GetString();
		}
		else 
		{
			// The page range is still invalid and most likely ambiguous, so
			// set the page range from the number of pages in the document
			InterfacePtr<IIntData>  pageNameStyleData(iControlView, IID_IPAGENAMESTYLEDATA);
			if (pageNameStyleData) {
				pageRangeText = PMString("kAllPagesString", PMString::kTranslateDuringCall);    // "All Pages" string 
			}
			else {
				int32 docPageCount = iPageList->GetPageCount();
				PMString dash("kDash");
				dash.Translate();
				pageRangeText.Clear();
				pageRangeText.Append(kTextChar_PlusSign);
				pageRangeText.AppendNumber(1);
				pageRangeText.Append(dash);
				pageRangeText.Append(kTextChar_PlusSign);
				pageRangeText.AppendNumber(docPageCount);
			}
			pageRangeText.SetTranslatable(kFalse);

			InterfacePtr<ITextControlData> iTextControlData(iControlView, UseDefaultIID());
			iTextControlData->SetString(pageRangeText, kTrue /*kDoInvalidate*/, kFalse /*kDontNotify*/);
		}
	}

	return pageRangeValid;
}

//========================================================================================
// SetWidgetState - enable/disable control
//========================================================================================
void ddui_utils::SetWidgetState(IPanelControlData* iPanelData, const WidgetID& wid, bool bEnable)
{
	if (!iPanelData) return;
	IControlView *iControlView = iPanelData->FindWidget (wid);
	if (!iControlView) return;
	iControlView->Enable(bEnable);
}

//========================================================================================
// CalculateWidthAndHeight
//========================================================================================
void ddui_utils::CalculateWidthAndHeight(
	PMReal const &sourceWidth, PMReal const &sourceHeight,
	uint32 targetWidth, uint32 targetHeight,
	uint32 &destWidth, uint32 &destHeight
)
{
	PMReal scale = std::min(targetWidth / sourceWidth, targetHeight / sourceHeight);

	destWidth = std::min(::ToUInt32(::Ceiling(sourceWidth * scale)), targetWidth);
	destHeight = std::min(::ToUInt32(::Ceiling(sourceHeight * scale)), targetHeight);
}

//========================================================================================
// CalculateWidthFromHeight
//========================================================================================
void ddui_utils::CalculateWidthFromHeight(
	PMReal const &sourceWidth, PMReal const &sourceHeight,
	uint32 targetHeight,
	uint32 &destWidth
)
{
	PMReal scale = targetHeight / sourceHeight;

	destWidth = ::ToUInt32(::Ceiling(sourceWidth * scale));
}

//========================================================================================
// CalculateHeightFromWidth
//========================================================================================
void ddui_utils::CalculateHeightFromWidth(
	PMReal const &sourceWidth, PMReal const &sourceHeight,
	uint32 targetWidth,
	uint32 &destHeight
)
{
	PMReal scale = targetWidth / sourceWidth;

	destHeight = ::ToUInt32(::Ceiling(sourceHeight * scale));
}

//========================================================================================
// CalculateWidthAndHeightScale
//========================================================================================
void ddui_utils::CalculateWidthAndHeightScale(
	PMReal const &sourceWidth, PMReal const &sourceHeight,
	PMReal const &scaleAmount,
	uint32 &destWidth, uint32 &destHeight
)
{
	destWidth = ::ToUInt32(::Ceiling(sourceWidth));
	destHeight = ::ToUInt32(::Ceiling(sourceHeight));

	if (scaleAmount != 100.0)
	{
		PMReal scale = scaleAmount / 100.0;
		
		destWidth = ::ToUInt32(::Ceiling(sourceWidth * scale));
		destHeight = ::ToUInt32(::Ceiling(sourceHeight * scale));
	}
}

// TODO::We should refactor the code so that it can be reused.
// This function is the same as PagePanelUtils::GetTargetedNonMasterSpreadsOnly(IPMUnknown* targetWidget, UIDList& spreadUIDList);
void ddui_utils::GetSelectedNonMasterSpreadsInPagesPanel(IPMUnknown* targetWidget, UIDList& spreadUIDList)
{
	if (targetWidget == nil)
	{
		InterfacePtr<IApplication>  iApplication(GetExecutionContextSession()->QueryApplication ());
		InterfacePtr<IPanelMgr> iPanelMgr(iApplication->QueryPanelManager ());
		targetWidget = iPanelMgr->GetVisiblePanel(kPagesPanelWidgetID);
	}

	spreadUIDList.Clear();
	
	// If no db provided, no document is probably open, don't fill out list.
	if (spreadUIDList.GetDataBase() == nil)
		return;

	InterfacePtr<IWidgetParent> parent(targetWidget, IID_IWIDGETPARENT);
	if (parent)
	{
		InterfacePtr<IUIDListControlData> selectedUIDs((IUIDListControlData *)Utils<IWidgetUtils>()->QueryRelatedWidget(targetWidget, kPagesPanelWidgetID, IID_IUIDLISTCONTROLDATA));
		if (!selectedUIDs)
			return;

		if ( spreadUIDList.GetDataBase() != selectedUIDs->GetDataBase___() )
			return;
		selectedUIDs->Sort___();

		int32 numItems = selectedUIDs->Length___();
		for (int32 j = 0; j < numItems; j++)
		{
			UID jthUID = selectedUIDs->GetUID___(j);
			IDataBase* uidListDB = selectedUIDs->GetDataBase___();

			// kInvalidUID is the None Master, need to allow it here.
			bool16 bNotDeleted = ((jthUID == kInvalidUID) || uidListDB->IsValidUID(jthUID));
			if (bNotDeleted)	// but what if it is deleted???
			{
				InterfacePtr<ISpread> nestedSpread(uidListDB, jthUID, UseDefaultIID());
				if (nestedSpread)
				{
					// spread selected.. add it if not a master
					InterfacePtr<IMasterSpread> iMaster(nestedSpread, UseDefaultIID());
					if (iMaster == nil) 
						spreadUIDList.Append(jthUID);
				}
				else
				{
					// page selected.. add parent spread if not a master
					InterfacePtr<IHierarchy> iHier(uidListDB, jthUID, UseDefaultIID());
					if (!iHier) continue;
					UID spreadUID = iHier->GetRootUID();
					
					// need to be sure it's not already in the list, since there could
					// be more than one page selected on the same spread..
					InterfacePtr<IMasterSpread> iMaster(uidListDB, spreadUID, IID_IMASTERSPREAD);
					if (iMaster == nil && spreadUIDList.Location(spreadUID) < 0) 
						spreadUIDList.Append(spreadUID);
				}
			}
		}
	}
}

bool GetPreviewDirectory(IDFile &directory, const char* dirName)
{
	FileUtility fileUtility(dirName);

	fileUtility.SetTemporaryFile(IFileUtility::kUserDomainMac | IFileUtility::kPreferencesFolderTypeMac);
	directory = fileUtility.GetSysFile();
	
	if (directory.Exists())
	{
		if (directory.GetAttribute(AFile::kDirectory))
		{
			return true;	
		}

		if(!directory.Delete())
		{
			// Already there but not a directory and can't delete, punt
			ASSERT_FAIL("SWF preview file directory isn't a directory and can't be deleted!");
			
			return false;
		}
	}
	
	if (!directory.MakeDirectory())
	{
		ASSERT_FAIL("SWF preview file directory can't be created!");
		
		return false;
	}
	
	return true;
}

uint32 ddui_utils::GetDirectionFromSelectionIndex(ClassID const &transitionClassID, int32 const &selectIndex)
{
	switch (transitionClassID.Get())
	{
		case kBlindsPageTransitionBoss:
		case kCombPageTransitionBoss:
			{
				return (selectIndex + IPageTransition::kHorizontal);
			}
		case kBoxPageTransitionBoss:
			{
				return (selectIndex + IPageTransition::kIn);
			}
		case kCoverPageTransitionBoss:
		case kPushPageTransitionBoss:
		case kUncoverPageTransitionBoss:
		case kWipePageTransitionBoss:
		case kZoomInPageTransitionBoss:
		case kZoomOutPageTransitionBoss:
			{
				return (selectIndex + IPageTransition::kDown);
			}

		case kDissolvePageTransitionBoss:
		case kFadePageTransitionBoss:
		case kPageTurnPageTransitionBoss:	
			{
				return IPageTransition::kNA;
			}

		case kSplitPageTransitionBoss:
			{
				return (selectIndex + IPageTransition::kHorizontalIn);
			}
		default:
			ASSERT("Unknown page transition type!");
	}

	return IPageTransition::kNA;
}

uint32 ddui_utils::GetSpeedFromSelectionIndex(int32 const &speedSelectedIndex)
{
	switch (speedSelectedIndex)
	{
		case 0:
			return IPageTransition::kPageTransitionsSlowSpeedTime;

		case 1:
			return IPageTransition::kPageTransitionsMediumSpeedTime;

		case 2:
			return IPageTransition::kPageTransitionsFastSpeedTime;
	}

	return IPageTransition::kDefaultDurationTime;
}

EventTriggerType ddui_utils::GetCurrentEventTypeInTimingPanel()
{		
	EventTriggerType eventType = kNoTriggerEvent;

	InterfacePtr<IPanelControlData> iPanelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kTimingPanelWidgetID)); 
    if( iPanelControlData ) 
    { 
        IControlView* eventDropDownView = iPanelControlData->FindWidget(kTimingPanelEventDropDownWidgetID); 
		InterfacePtr<IDropDownListController> iEventDDListController(eventDropDownView, UseDefaultIID()); 
		int32 indexSelected = iEventDDListController->GetSelected();

		if (indexSelected >= 0)
		{
			InterfacePtr<IStringListControlData> iEventDropDownStringData(iEventDDListController, UseDefaultIID());		
			PMString eventString = iEventDropDownStringData->GetString(indexSelected);

			eventType = Utils<IAnimationUtils>()->GetEventTriggerFromString(eventString);
		}
	}

	return eventType;
}

bool ddui_utils::AllItemsInSameTimingGroup(IDynamicEventTimingMgr::DynamicTargetList const &itemList, uint32& groupIndex)
{	
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	uint32 numGroups = iDynamicEventTimingSuite ? iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType) : 0;
	if (numGroups <= 0)
		return false;

	if (itemList.size() <= 0)
		return false;

	uint32 position = 0;
	groupIndex = iDynamicEventTimingSuite->FindTargetInEvent(eventType, itemList[0], position);

	IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList;
	if (iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, groupIndex, nthGroupItemList))
	{
		if (itemList.size() == nthGroupItemList.size())
		{
			for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = itemList.begin(); iter != itemList.end(); ++iter)
			{
				bool bFound = false;
				for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator nthGroupIter = nthGroupItemList.begin(); (!bFound && (nthGroupIter != nthGroupItemList.end())); ++nthGroupIter)
				{
					if (((*iter)->GetTargetUID() == (*nthGroupIter)->GetTargetUID()) && ((*iter)->GetRole() == (*nthGroupIter)->GetRole()) && ((*iter)->GetAction() == (*nthGroupIter)->GetAction()))
						bFound = true;
				}
				if (!bFound)
					return false;
			}

			return true;
		}
	}
	
	return false;
}

// Only when the selected items are all in groups, then we will return true
// For example, we have group1(a,b,c) and group2(d,e,f). 
// If the selected items have (a,b,c,d,e,f), then we will return true. 
// If the selected items have only (a,b,c,d) then we will return false.
// groupTargetList is a map contains the group index and the item list in the group index.
bool ddui_utils::AllItemsInTimingGroups(IDynamicEventTimingMgr::DynamicTargetList const &itemList, std::map<int32, IDynamicEventTimingMgr::DynamicTargetList>& groupTargetList)
{
	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	uint32 numGroups = iDynamicEventTimingSuite ? iDynamicEventTimingSuite->GetNumGroupsInEvent(eventType) : 0;
	if (numGroups <= 0)
		return false;

	if (itemList.size() <= 0)
		return false;

	// Get all the group index for the given item list
	std::vector<int32> groupIndexList;
	for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator itemIter = itemList.begin(); itemIter != itemList.end(); ++itemIter)
	{
		uint32 position = 0;
		int32 groupIndex = iDynamicEventTimingSuite->FindTargetInEvent(eventType, *itemIter, position);

		if (groupIndex >= 0 && std::find(groupIndexList.begin(), groupIndexList.end(), groupIndex) == groupIndexList.end())
			groupIndexList.push_back(groupIndex);
	}

	// sort group index
	std::sort(groupIndexList.begin(), groupIndexList.end());

	// build a map (group index, group items)
	for (std::vector<int32>::const_iterator indexIter = groupIndexList.begin(); indexIter != groupIndexList.end(); ++indexIter)
	{
		IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList;
		if (iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, *indexIter, nthGroupItemList))
			groupTargetList[*indexIter] = nthGroupItemList;
	}

	ASSERT(groupIndexList.size() > 0);

	for (std::vector<int32>::const_iterator groupIter = groupIndexList.begin(); groupIter != groupIndexList.end(); ++groupIter)
	{
		IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList;
		if (iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, *groupIter, nthGroupItemList))
		{	
			bool bFound = false;

			for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator nthGroupIter = nthGroupItemList.begin(); (!bFound && (nthGroupIter != nthGroupItemList.end())); ++nthGroupIter)
			{
				for (IDynamicEventTimingMgr::DynamicTargetList::const_iterator iter = itemList.begin(); (!bFound && (iter != itemList.end())); ++iter)
				{
					if (((*iter)->GetTargetUID() == (*nthGroupIter)->GetTargetUID()) && ((*iter)->GetRole() == (*nthGroupIter)->GetRole()) && ((*iter)->GetAction() == (*nthGroupIter)->GetAction()))
						bFound = true;
				}

				if (!bFound)
					return false;

				bFound = false;
			}
		}
	}

	return true;
}

ErrorCode ddui_utils::UngroupTimingItems(IDynamicEventTimingMgr::DynamicTargetList const &itemList)
{
	if (itemList.size() <= 0)
		return kSuccess;

	InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
	InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));
	
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	ASSERT(eventType != kNoTriggerEvent);

	//
	// Check if the items are within the same group or not.
	// If they are in the same group, then we will ungroup them all at once without changing the order.
	//
	ICommandSequence* iUnlinkCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
	ASSERT (iUnlinkCmdSequence != nil);

	uint32 groupIndex = 0;
	bool bSameGroup = AllItemsInSameTimingGroup(itemList, groupIndex);

	IDynamicEventTimingMgr::DynamicTargetList nthGroupItemList;
	if (bSameGroup)
		iDynamicEventTimingSuite->GetNthGroupInEvent(eventType, groupIndex, nthGroupItemList);

	if (bSameGroup)
	{
		// UnlinkNthGroupInEvent will unlink all the items and keep them in the same position.
		iDynamicEventTimingSuite->UnlinkNthGroupInEvent(eventType, groupIndex);
	}
	else
	{
		for (int32 i = 0; i < itemList.size(); ++i)
		{
			uint32 position = -1;
			int32 originalGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, itemList[i], position);	

			//(warn: unsigned >= 0) if (groupIndex >= 0)
			{
				iDynamicEventTimingSuite->UnlinkTargetInEvent(eventType, itemList[i], originalGroup);
			}
		}
	}

	ErrorCode result = (CmdUtils::EndCommandSequence(iUnlinkCmdSequence));
	return result;
}

ErrorCode ddui_utils::GroupTimingItems(IDynamicEventTimingMgr::DynamicTargetList const &itemList)
{		
	EventTriggerType eventType = ddui_utils::GetCurrentEventTypeInTimingPanel();
	ASSERT(eventType != kNoTriggerEvent);

	if ((itemList.size() > 0) && (eventType != kNoTriggerEvent))
	{
		ICommandSequence* iLinkCmdSequence = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		ASSERT (iLinkCmdSequence != nil);

		InterfacePtr<ISelectionManager> iSelectionMgr(Utils<ISelectionUtils>()->QueryActiveSelection ()); 
		InterfacePtr<IDynamicEventTimingSuite> iDynamicEventTimingSuite(static_cast<IDynamicEventTimingSuite*>(Utils<ISelectionUtils>()->QuerySuite(IID_IDYNAMICEVENTTIMINGSUITE, iSelectionMgr)));

		IDataBase* db = iSelectionMgr->GetDataBase();
		uint32 position = -1;
		int32 newGroup = iDynamicEventTimingSuite->FindTargetInEvent(eventType, itemList[0], position);

		iDynamicEventTimingSuite->GroupTargetsInEvent(eventType, itemList, newGroup);		
		ErrorCode result = (CmdUtils::EndCommandSequence(iLinkCmdSequence));

		return result;
	
	}

	return kSuccess;
}

void ddui_utils::GetSelectedTimingItems(IDataBase* db, IDynamicEventTimingMgr::DynamicTargetList &itemList)
{
	itemList.clear();

	InterfacePtr<IPanelControlData> iPanelControlData(Utils<IPalettePanelUtils>()->QueryPanelByWidgetID(kTimingPanelWidgetID));

	if (iPanelControlData)
	{
		IControlView* iTreeView = iPanelControlData->FindWidget(kTimingPanelTreeWidgetID); 
		InterfacePtr<ITreeViewController> iTreeViewController(iTreeView, UseDefaultIID());
		
	    InterfacePtr<ITreeViewHierarchyAdapter> iTreeViewHierarchyAdapter(iTreeView, UseDefaultIID()); 
		NodeID rootNode = iTreeViewHierarchyAdapter->GetRootNode(); 
		int32 numItems = iTreeViewHierarchyAdapter->GetNumChildren(rootNode);

		for (int32 i = 0; i < numItems; ++i)
		{
			NodeID nthNode = iTreeViewHierarchyAdapter->GetNthChild(rootNode, i);
			if (iTreeViewController->IsSelected(nthNode))
			{
				TreeNodePtr<TimingPanelTreeNodeID> itemNode(nthNode); 

				IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget = Utils<Facade::IDynamicEventTimingFacade>()->CreateDynamicTarget 
																		(UIDRef(db,itemNode->GetUID()), itemNode->GetRole(), itemNode->GetAction());

				itemList.push_back(dynamicTarget);
			}
		}
	}
}

PMReal ddui_utils::GetSelectedTimingItemsDelay (IDynamicEventTimingSuite* iTimingSuite, const EventTriggerType& trigger, const NodeIDList& nodes, bool& mixed)
{
	InterfacePtr<ISelectionManager> iSelectionMgr (iTimingSuite, UseDefaultIID ());
	IDataBase* db = iSelectionMgr->GetDataBase();
	uint32 position = 0;

	mixed = false;
	PMReal delay = 0;
	NodeIDList::const_iterator d = nodes.begin ();
	for (; d != nodes.end (); ++d)
	{
		TreeNodePtr<TimingPanelTreeNodeID> itemNode(*d);
		IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget (UIDRef (db, itemNode->GetUID()), itemNode->GetRole(), itemNode->GetAction()));
		
		//	We could get an invalid group index if we are in the middle of switching event.
		int32 group = iTimingSuite->FindTargetInEvent (trigger, dynamicTarget, position);
		if (group >= 0)
		{
			PMReal itemDelay = iTimingSuite->GetTargetDelayInEvent(trigger, dynamicTarget, group);
			if (d == nodes.begin ()) delay = itemDelay;
			else if (itemDelay != delay) mixed = true;
		}
	}

	return delay;
}

uint32 ddui_utils::GetSelectedTimingItemsGroupPlays (IDynamicEventTimingSuite* iTimingSuite, const EventTriggerType& trigger, const NodeIDList& nodes, uint32& groupIndex)
{
	InterfacePtr<ISelectionManager> iSelectionMgr (iTimingSuite, UseDefaultIID ());
	IDataBase* db = iSelectionMgr->GetDataBase();

	uint32 position = 0;
	NodeIDList::const_iterator d = nodes.begin ();
	TreeNodePtr<TimingPanelTreeNodeID> itemNode(*d);
	IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget (UIDRef (db, itemNode->GetUID()), itemNode->GetRole(), itemNode->GetAction()));
	groupIndex = iTimingSuite->FindTargetInEvent (trigger, dynamicTarget, position);
	ASSERT (groupIndex >= 0 && groupIndex != IDynamicEventTimingMgr::kInvalidTimingPosition);

	IDynamicEventTimingMgr::DynamicTargetList targetList;
	targetList.push_back (dynamicTarget);
	++d;

	for (; d != nodes.end (); ++d)
	{
		TreeNodePtr<TimingPanelTreeNodeID> targetNode(*d);
		IDynamicEventTimingMgr::DynamicTargetPtr targetPtr (Utils<Facade::IDynamicEventTimingFacade> ()->CreateDynamicTarget (UIDRef (db, targetNode->GetUID()), targetNode->GetRole(), targetNode->GetAction()));

#ifdef DEBUG
		int32 targetGroup = iTimingSuite->FindTargetInEvent (trigger, dynamicTarget, position);
		ASSERT (targetGroup >= 0);
#endif
		targetList.push_back (targetPtr);
	}
	
	uint32 numPlays = 0;
	if (targetList.size () <= 1 || !ddui_utils::AllItemsInSameTimingGroup(targetList, groupIndex))
	{
		groupIndex = IDynamicEventTimingMgr::kInvalidTimingPosition;
	}
	else
	{
		numPlays = iTimingSuite->GetNthGroupNumPlaysInEvent (trigger, groupIndex);
	}

	return numPlays;
}

PMReal ddui_utils::GetTimingPanelEditControlValue (IPanelControlData* iTimingPanelData, const WidgetID& editWidgetID, bool& hasValue, PMString& errorString)
{
	IControlView* iEditDataView = iTimingPanelData->FindWidget (editWidgetID);
	InterfacePtr<ITextValue> iEditData (nil); 
	InterfacePtr<IPanelControlData> iInlinePanelData (iEditDataView, UseDefaultIID());
	if (iInlinePanelData)
	{
		IControlView * iStaticTextView = iInlinePanelData->FindWidget (kInLineEditStaticTextWidgetID);
		iEditData = InterfacePtr<ITextValue> (iStaticTextView, UseDefaultIID());
	}
	else
	{
		iEditData = InterfacePtr<ITextValue> (iEditDataView, UseDefaultIID());
	}

	bool16 hasError = kFalse;
	bool16 blankEntry = kFalse;
	PMReal newValue = iEditData->GetTextAsValue (&hasError, &blankEntry);
	
	InterfacePtr<ITextDataValidation> iValidation (iEditData, UseDefaultIID ()); 
	if (iEditDataView->IsEnabled () && iValidation && !iValidation->IsEntryLegal ())
	{
		hasError = true;
		errorString = iValidation->GetErrorString ();
	}
	else
	{
		errorString.clear ();
	}

	hasValue = (!hasError && !blankEntry);

	return newValue;
}

void ddui_utils::DisplayErrorAndSetTimingPanelEditBoxFocus (IPanelControlData* iTimingPanelData, const WidgetID& editWidgetID, const PMString& errorString)
{
	if (!errorString.empty ())
	{
		ASSERT (errorString.HasTranslated ());
		CAlert::WarningAlert(errorString); 
	}

	IControlView* iEditDataView = iTimingPanelData->FindWidget (editWidgetID);
	InterfacePtr<ITextControlData> iEditData (nil); 
	InterfacePtr<IPanelControlData> iInlinePanelData (iEditDataView, UseDefaultIID());
	if (iInlinePanelData)
	{
		IControlView * iStaticTextView = iInlinePanelData->FindWidget (kInLineEditStaticTextWidgetID);
		iEditData = InterfacePtr<ITextControlData> (iStaticTextView, UseDefaultIID());
	}
	else
	{
		iEditData = InterfacePtr<ITextControlData> (iEditDataView, UseDefaultIID());
	}

	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication()); 
	InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD); 

	InterfacePtr<IEventHandler> iEditBoxEH (iEditData, UseDefaultIID ());
	InterfacePtr<ITextControlData> iLastGoodText(iEditBoxEH, IID_ILASTVALIDTEXTCONTROLDATA); 
	InterfacePtr<ITextControlData> iTextData(iEditBoxEH, UseDefaultIID ()); 
	if (iLastGoodText && iTextData)
	{
		iTextData->SetString (iLastGoodText->GetString (), kTrue, kFalse);
	}

	theKeyBoard->AcquireKeyFocus (iEditBoxEH); 
	InterfacePtr<IEditBoxAttributes> iEBAttrs (iEditBoxEH, UseDefaultIID ()); 
	if (iEBAttrs)
	{
		if (iTextData->GetString ().empty ())
			iEBAttrs->SelectRange(0, 0); 
		else
			iEBAttrs->SelectRange(0, kEndOfRange);

#if WINDOWS
		// Presumably, someone clicked on another control and that's triggering
		// this editbox to manually validate and re-focus if there's an error.
		// Unfortunately, Windows has probably already changed the focus to the other control.
		// Make sure we switch it back here.
		IEventHandler *currentFocus = theKeyBoard->GetKeyFocus();
		if (currentFocus != iEditBoxEH)
			theKeyBoard->AcquireKeyFocus(iEditBoxEH);
#endif
	}
}

void ddui_utils::UpdateTimingPanelEditBoxFocus (IPMUnknown* iRelatedWiget, const WidgetID& editWidgetID)
{
	InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication()); 
	InterfacePtr<IKeyBoard> theKeyBoard(theApp, IID_IKEYBOARD); 

	InterfacePtr<IPanelControlData> iTimingPanelData (static_cast<IPanelControlData*> (Utils<IWidgetUtils> ()->QueryRelatedWidget (iRelatedWiget, kTimingPanelWidgetID, IID_IPANELCONTROLDATA))); 

	IControlView* iEditDataView = iTimingPanelData->FindWidget (editWidgetID);
	InterfacePtr<ITextControlData> iEditData (nil); 
	InterfacePtr<IPanelControlData> iInlinePanelData (iEditDataView, UseDefaultIID());
	if (iInlinePanelData)
	{
		IControlView * iStaticTextView = iInlinePanelData->FindWidget (kInLineEditStaticTextWidgetID);
		iEditData = InterfacePtr<ITextControlData> (iStaticTextView, UseDefaultIID());
	}
	else
	{
		iEditData = InterfacePtr<ITextControlData> (iEditDataView, UseDefaultIID());
	}

	InterfacePtr<IEventHandler> iEditBoxEH (iEditData, UseDefaultIID ());

    InterfacePtr<IKeyFocusHandler> keyFocusHandler (QueryKeyFocusHandler(iEditBoxEH)); 
    ASSERT(keyFocusHandler != nil); 
    if (keyFocusHandler) 
        keyFocusHandler->SetCurrentTargetEventHandler(iEditBoxEH); 

	InterfacePtr<IEditBoxAttributes> iEBAttrs (iEditBoxEH, UseDefaultIID ()); 
	if (iEBAttrs)
	{
		if (iEditData->GetString ().empty ())
			iEBAttrs->SelectRange(0, 0); 
		else
			iEBAttrs->SelectRange(0, kEndOfRange); 

#ifdef WINDOWS
		// Presumably, someone clicked on another control and that's triggering
		// this editbox to manually validate and re-focus if there's an error.
		// Unfortunately, Windows has probably already changed the focus to the other control.
		// Make sure we switch it back here.
		IEventHandler *currentFocus = theKeyBoard->GetKeyFocus();
		if (currentFocus != iEditBoxEH)
			theKeyBoard->AcquireKeyFocus(iEditBoxEH);
#endif
	}
}

WidgetID ddui_utils::UpdateTimingItemsIfNecessary (IPMUnknown* iRelatedWidget, const NodeIDList& nodes)
{
	WidgetID invalidWidgetID = kDefaultWidgetId;
	if (!nodes.empty ())
	{
		InterfacePtr<IWidgetParent> iWidgetParent (iRelatedWidget, UseDefaultIID ());
		InterfacePtr<ITextControlData> iPanelMenuData ((ITextControlData*)iWidgetParent->QueryParentFor(IID_IPANELMENUDATA));
		InterfacePtr<IPanelControlData> iPanelData (iPanelMenuData, UseDefaultIID());

		bool hasDelayValue = true;
		bool hasPlayValue = true;
		PMString delayErrorString, playErrorString;
		PMReal newDelay = ddui_utils::GetTimingPanelEditControlValue (iPanelData, kTimingDelayILEWidgetID, hasDelayValue, delayErrorString);
		uint32 newNumPlays = ::ToInt32 (ddui_utils::GetTimingPanelEditControlValue (iPanelData, kTimingPanelPlayLinkedItemEditBoxWidgetID, hasPlayValue, playErrorString));
		if (hasDelayValue || hasPlayValue)
		{
			Utils<Facade::IDynamicEventTimingFacade> iTimingFacade;
			ISelectionManager* iActiveSelMgr = Utils<ISelectionUtils> ()->GetActiveSelection ();
			InterfacePtr<IDynamicEventTimingSuite> iTimingSuite (iActiveSelMgr, UseDefaultIID ());
			IDataBase* db = iActiveSelMgr->GetDataBase ();

			//	Check delay first
			bool mixedValue = false;
			EventTriggerType trigger = ddui_utils::GetCurrentEventTypeInTimingPanel();
			PMReal delay = ddui_utils::GetSelectedTimingItemsDelay (iTimingSuite, trigger, nodes, mixedValue);
			if (hasDelayValue && (newDelay != delay || mixedValue))
			{
				//	Update delay
				CmdUtils::SequencePtr seq;
				seq->SetName("kUpdateDynamicTargetDataCmd");
				NodeIDList::const_iterator d = nodes.begin ();
				for (; d != nodes.end (); ++d)
				{
					uint32 position = 0;
					TreeNodePtr<TimingPanelTreeNodeID> itemNode(*d);
					IDynamicEventTimingMgr::DynamicTargetPtr dynamicTarget (iTimingFacade->CreateDynamicTarget (UIDRef (db, itemNode->GetUID()), itemNode->GetRole(), itemNode->GetAction()));
					int32 whichGroup = iTimingSuite->FindTargetInEvent(trigger, dynamicTarget, position);
					iTimingSuite->SetTargetDelayInEvent(trigger, dynamicTarget, whichGroup, newDelay);
				}
			}
			else
			{
				//	Check number of group plays
				uint32 group = 0;
				uint32 numPlays = ddui_utils::GetSelectedTimingItemsGroupPlays (iTimingSuite, trigger, nodes, group);
				if (group != IDynamicEventTimingMgr::kInvalidTimingPosition)
				{
					if (hasPlayValue && numPlays > 0 && newNumPlays > 0 && numPlays != newNumPlays)
					{
						iTimingSuite->SetNthGroupNumPlaysInEvent(trigger, group, newNumPlays);
					}
				}
			}
		}

		//	Get key focus back to the edit box containing errors
		if (!hasDelayValue && !delayErrorString.empty ())
		{
			invalidWidgetID = kTimingDelayILEWidgetID;
			ddui_utils::DisplayErrorAndSetTimingPanelEditBoxFocus (iPanelData, kTimingDelayILEWidgetID, delayErrorString);
		}
		else if (!hasPlayValue && !playErrorString.empty ())
		{
			invalidWidgetID = kTimingPanelPlayLinkedItemEditBoxWidgetID;
			ddui_utils::DisplayErrorAndSetTimingPanelEditBoxFocus (iPanelData, kTimingPanelPlayLinkedItemEditBoxWidgetID, playErrorString);
		}
		return invalidWidgetID;
	}
	return invalidWidgetID;
}

void ddui_utils::DrawGroupWidgetLines(PMPoint const &startPoint, PMReal const &width, PMReal const &height, dvaui::drawbot::Drawbot *drawbotP, 
	bool const isHilite, bool16 const bIsFirstItemInGroup, bool16 const bIsLastItemInGroup)
{
	dv_utils::DVSaveAndRestoreStateStack(drawbotP, true); //FIXME_DV: See declaration: 2nd parameter is unused
	dv_utils::DVSetAntiAliasPolicy(drawbotP, dv_utils::kAntiAliasPolicy_None);

	RealAGMColor hiliteColor;
	InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
	colors->GetRealAGMColor(isHilite ? kInterfaceWhite : kInterfaceTextColor, hiliteColor);
	
	PMPointList pathPtsV;
	PMPointList pathPtsH;	
	if (bIsFirstItemInGroup)
	{
		// --- Draw vertical line 
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height/2)); //moveto
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height)); //lineto

		// --- Draw horizontal line 
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height/2));
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop+kGroupWidgetHorzizontalLineLength, startPoint.Y()+height/2));
	}
	else if (bIsLastItemInGroup)
	{
		// --- Draw vertical line 
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()));
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height/2));

		// --- Draw horizontal line 
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height/2));
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop+kGroupWidgetHorzizontalLineLength, startPoint.Y()+height/2));
	}
	else	// middle item in group
	{
		// --- Draw vertical line 
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()));
		pathPtsV.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height));

		// --- Draw horizontal line 
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop, startPoint.Y()+height/2));
		pathPtsH.push_back(PMPoint(startPoint.X()+width/2-kGroupWidgetHorzizontalLineSlop+kGroupWidgetHorzizontalLineLength, startPoint.Y()+height/2));		
	}

	dv_utils::DVStrokePath(drawbotP, hiliteColor, pathPtsV, dv_utils::kDefaultStrokeWidth);
	dv_utils::DVStrokePath(drawbotP, hiliteColor, pathPtsH, dv_utils::kDefaultStrokeWidth);
}

//	The animation panel has these different detail configurations:
//	0: preview, main property, sub property control, control strip (default)
//		==> showPreview = true, showSubProperty = false
//	1: preview, main property, sub property control, sub property, control strip
//		==> showPreview = true, showSubProperty = true
//	2: main property, sub property control
//		==> showPreview = false, showSubProperty = false
//	3: main property, sub property control, sub property, control strip
//		==> showPreview = false, showSubProperty = true
//	Additionally, in any of these three views, user can open/close the sub property control to reveal or hide the sub property
//	panel on demand.
//	The strategy assumes that the panel resource is setup so that the three distinct subpanels are wholely contained.
//	When rotating through different configurations, we simple show/hide these subpanels accordingly.
//	Since this panel is not resizable, we don't really have to set frame binding in the resource.
//	It is already set, so we will honor it. But bindings messed up the panel frame resize, we will
//	need to set to none before resize and reset to original values after resize.
//	NOTE: if we ever change the configuration enum in the detail controller impl, we need to also change it here.
//	(Or we could move the enum to the UI project _Defs.h or the _UIUtils.h, but I am too lazy a this point.)
int16 ddui_utils::MapAnimationPanelDetailLevel (bool showPreview, bool showSubProperty)
{
	int32 detailLevel = 0;
	if (showPreview)
	{
		if (showSubProperty) detailLevel = 1;
	}
	else
	{
		if (showSubProperty) detailLevel = 3;
		else detailLevel = 2;
	}
	return detailLevel;
}

void ddui_utils::UpdateAnimationPanelSize (IControlView* iAnimationPanelView, bool showPreview, bool showSubProperty) 
{ 			
	PMReal frameInset (0);
	PMRect panelFrame = iAnimationPanelView->GetFrame();
	PMReal frameLeft = frameInset;

	InterfacePtr<IPanelControlData> iPanelData (iAnimationPanelView, UseDefaultIID());

	//	Preview panel group
	IControlView* iPreviewPanelView = iPanelData->FindWidget (kAnimationUIPreviewGroupWID); 
	FrameBinding previewBinding = iPreviewPanelView->GetFrameBinding ();
	iPreviewPanelView->SetFrameBinding (kBindNone);

	if (showPreview)
	{
		iPreviewPanelView->ShowView ();
		ddui_utils::UpdateAnimationPreviewProxy (iPanelData);
	}
	else
	{
		iPreviewPanelView->HideView ();
	}
	
	PMReal previewFrameHeight = iPreviewPanelView->GetFrame().Height();
	if (previewFrameHeight != kAnimationUIPreviewPanelHeight)
	{
		iPreviewPanelView->Resize (PMPoint (iPreviewPanelView->GetFrame().Width(), kAnimationUIPreviewPanelHeight));
		previewFrameHeight = iPreviewPanelView->GetFrame().Height();
	}
	ASSERT (previewFrameHeight == kAnimationUIPreviewPanelHeight);
	PMReal frameBottom = (showPreview) ? kAnimationUIPreviewPanelHeight : frameInset;

	//	Main property panel group
	IControlView* iPropertyMainView = iPanelData->FindWidget( kAnimationUIMainPanelWID ); 
	FrameBinding mainPanelBinding = iPropertyMainView->GetFrameBinding ();
	iPropertyMainView->SetFrameBinding (kBindNone);
	PMReal propertyMainFrameHeight = iPropertyMainView->GetFrame().Height();
	ASSERT (propertyMainFrameHeight == kAnimationUIMainPanelHeight);

	//	Sub property panel group
	IControlView* iPropertySubPanelView = iPanelData->FindWidget (kAnimationUIPropertySubPanelGroupWID);
	FrameBinding propPanelBinding = iPropertySubPanelView->GetFrameBinding ();
	iPropertySubPanelView->SetFrameBinding (kBindNone);

	PMReal propertySubPanelHeight = iPropertySubPanelView->GetFrame().Height();
	ASSERT (propertySubPanelHeight == kAnimationUIPropertySubPanelHeight);

	//	Control strip panel group
	IControlView* iCcontrolStripView = iPanelData->FindWidget (kAnimationUIControlStripWID); 
	PMRect controlScriptFrame = iCcontrolStripView->GetFrame();
	PMReal controlStripPanelHeight = controlScriptFrame.Height();

	//	Expander icon
	IControlView* iExpanderIconView = iPanelData->FindWidget(kAnimationUIPropertyExpanderWidgetIconWID);
	
	IControlView* iPropertySubPanelControlView = iPanelData->FindWidget(kAnimationUIPropertyTitleGroupWID); 
	FrameBinding propPanelControlBinding = iPropertySubPanelControlView->GetFrameBinding ();
	iPropertySubPanelControlView->SetFrameBinding (kBindNone);

	PMReal propertySubPanelControlHeight = iPropertySubPanelControlView->GetFrame ().Height();
	ASSERT (propertySubPanelControlHeight == kAnimationUISubPanelControlHeight);

	//	At minimum, the panel should be at least the main property + expander + control strip
	PMReal panelHeight = propertyMainFrameHeight + propertySubPanelControlHeight + controlStripPanelHeight;

	if (showPreview) panelHeight += previewFrameHeight;
	if (showSubProperty)
	{
		panelHeight += propertySubPanelHeight;
		iPropertySubPanelView->ShowView();

		if (iExpanderIconView->GetRsrcID () != kTreeBranchExpandedRsrcID)
			iExpanderIconView->SetRsrcID (kTreeBranchExpandedRsrcID);
	}
	else
	{
		iPropertySubPanelView->HideView();

		if (iExpanderIconView->GetRsrcID () != kTreeBranchCollapsedRsrcID)
			iExpanderIconView->SetRsrcID (kTreeBranchCollapsedRsrcID);
	}


	PMPoint delta(0, panelHeight - panelFrame.Height());

	Utils<IPalettePanelUtils>()->ResizePalettePanel(iAnimationPanelView , delta);

	//	Move main panel
	iPropertyMainView->MoveTo (PMPoint (frameLeft, frameBottom), kTrue);
	iPropertyMainView->Invalidate ();

	//	Move property sub panel control group
	frameBottom += propertyMainFrameHeight;
	iPropertySubPanelControlView->MoveTo (PMPoint(frameLeft, frameBottom), kTrue/*invalidate*/);
	iPropertySubPanelControlView->Invalidate ();

	//	Move property sub panel group
	frameBottom += propertySubPanelControlHeight;
	if (iPropertySubPanelView->IsVisible())
	{
		iPropertySubPanelView->MoveTo(PMPoint(frameLeft, frameBottom), kTrue/*invalidate*/);
		iPropertySubPanelView->Invalidate ();

		frameBottom += kAnimationUIPropertySubPanelHeight;
	}

	iCcontrolStripView->MoveTo(PMPoint(frameLeft, frameBottom), kTrue/*invalidate*/);
	iCcontrolStripView->Invalidate ();


	//	Restore binding
	iPreviewPanelView->SetFrameBinding (previewBinding);
	iPropertyMainView->SetFrameBinding (mainPanelBinding);
	iPropertySubPanelControlView->SetFrameBinding (propPanelControlBinding);
	iPropertySubPanelView->SetFrameBinding (propPanelBinding);

}

void ddui_utils::UpdateAnimationItemName (IAnimationAttributeSuite* iAttrSuite, IPMUnknown* iRelatedWidget)
{
	if (iAttrSuite == nil)
	{
		iAttrSuite = InterfacePtr<IAnimationAttributeSuite> (Utils<ISelectionUtils> ()->GetActiveSelection (), UseDefaultIID ());
	}

	InterfacePtr<ITextControlData> iNameData(static_cast<ITextControlData*>(Utils<IWidgetUtils>()->QueryRelatedWidget(iRelatedWidget, kAnimationUINameEditBoxWID, IID_ITEXTCONTROLDATA)));	
	if (iAttrSuite && iNameData)
	{
		PMString currentName;
		PMString newName = iNameData->GetString ();
		if (iAttrSuite && iAttrSuite->GetName (currentName) && currentName != newName)
		{
			iAttrSuite->SetName (newName);
		}
	}
}
void ddui_utils::UpdateAnimationPreviewProxy(const IPanelControlData* iAnimatilnPanelData, IAnimationAttributeSuite* iAttrSuite)
{
	if (iAttrSuite == nil)
	{
		iAttrSuite = InterfacePtr<IAnimationAttributeSuite> (Utils<ISelectionUtils> ()->GetActiveSelection (), UseDefaultIID ());
	}

	IControlView* iPresetPreviewPanel = iAnimatilnPanelData->FindWidget(kAnimationUIPreviewGroupWID);
    IControlView* iPresetProxyWidget = iAnimatilnPanelData->FindWidget(kGIFPlayerWidgetID);
	IControlView* iNoSelectionPresetProxyWidget = iAnimatilnPanelData->FindWidget(kAnimationUINoSelectionPreviewProxyWID);
	if (!iPresetPreviewPanel->IsVisible () || iAttrSuite == nil )//|| iPlayer == nil)
		return;

	iPresetProxyWidget->HideView ();
	if (!iAttrSuite->CanApplyMotionPreset ())
	{
		iNoSelectionPresetProxyWidget->ShowView ();
		return;
	}
	else
	{
		iNoSelectionPresetProxyWidget->HideView ();
	}

	PMString presetName;
	bool unique = iAttrSuite->GetBaseMotionPresetNameApplied (presetName);
	if (!unique || iAttrSuite->HasCustomAnimationSettings ()) presetName.clear ();

	PMString subFolderName("kMotionPresetsFolderTextKey", PMString::kTranslateDuringCall);

	IDFile presetsFolder; 
	bool16 hasPresetFolder = FileUtils::GetPresetsFolder(&presetsFolder, subFolderName, PMLocaleId());
	IDFile defaultPresetsFolder(presetsFolder);

	if (!presetName.empty())
	{
		InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
		int32 presetIndex = iPresetMgr->FindPreset (presetName);
		
		if (presetIndex >= 0)
		{
			//	Do not translate file name. They are the same regardless of languages.
			PMString appliedPresetName(presetName);
			appliedPresetName.Append(PMString("kDynamicDocumentsUISWFFileExtention", PMString::kTranslateDuringCall));

			if (!iPresetMgr->IsDefaultPreset (presetIndex))
			{
				hasPresetFolder = FileUtils::GetAppRoamingDataFolder(&presetsFolder, subFolderName);
			}

			if (hasPresetFolder) FileUtils::AppendPath(&presetsFolder, appliedPresetName);	
		}
	}

	//
	// If requested swf does not exists, we use the default empty swf file. 
	//
	if (hasPresetFolder)
	{
		if (presetName.empty() || !FileUtils::DoesFileExist(presetsFolder))
		{
			PMString defaultPresetName("kDynamicDocumentsUIDefaultSWF", PMString::kTranslateDuringCall);
			FileUtils::AppendPath(&defaultPresetsFolder, defaultPresetName);
			presetsFolder = defaultPresetsFolder;
		}

		PMString localFile;
		FileUtils::IDFileToPMString(presetsFolder, localFile);
        
        DVGIFPlayerView* view = dynamic_cast<DVGIFPlayerView*>(iPresetProxyWidget);
        view->SetGIFPath(localFile);

		iPresetProxyWidget->ShowView ();
	}
}

static inline IDFile HTMLFileFromSWFFile(const IDFile& swfFile)
{
	return IDFile(swfFile.GetParentPath() + APath(swfFile.GetName().GetBase() + ".html"));
}

static inline IDFile ResourceDirectoryFromSWFFile(const IDFile& swfFile)
{
	return IDFile(swfFile.GetParentPath() + APath((Utils<IDynDocsPublicUtils>()->GetResourceDirectoryNameFromDDExportFile(swfFile))));
}

bool ddui_utils::DeleteTempExportDirectory(IDFile const &exportDirectory)
{	
	IDFile swfFile;
    return false;

}

