//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/DynamicDocumentsUIUtils.h $
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
#pragma once
#ifndef __DynamicDocumentsUIUtils__
#define __DynamicDocumentsUIUtils__

#include "DynamicDocumentsUIID.h"
#include "AnimationTypes.h"
#include "IDynamicEventTimingMgr.h"
#include "NodeID.h"

#include "DVAForwardDeclarations.h"

class IPageRange;
class IDocument;
class IPanelControlData;
class IControlView;
class IViewPort;
class IDynamicEventTimingSuite;
class IAnimationAttributeSuite;
class PMReal;

namespace ddui_utils
{
	/** Initialize the page range edit box with the string stored in the IPageRange interface.
		If the range is not valid for the document, the edit box will be initialized with 
		a range that includes all the pages in the document.

		@return bool16 kTrue if the passed in page range was valid, kFalse otherwise
	*/
	bool16 InitializeRangeEdit(IPageRange* iPageRange, IDocument* iDocument, IPanelControlData* iPanelControlData);

	/** Enable or disable a widget control.
	*/
	void SetWidgetState(IPanelControlData* iPanelData, const WidgetID& wid, bool bEnable);

	/** Calculate the width and height, based on the source width and height, and the 
		target width and height. Returns values in destWidth and destHeight parameters.
	*/
	void CalculateWidthAndHeight(		PMReal const &sourceWidth, PMReal const &sourceHeight,
										uint32 targetWidth, uint32 targetHeight,
										uint32 &destWidth, uint32 &destHeight );

	/** Calculate the width based on the given target height and on the source width and height. 
		Returns value in the destWidth parameter.
	*/
	void CalculateWidthFromHeight(		PMReal const &sourceWidth, PMReal const &sourceHeight,
										uint32 targetHeight,
										uint32 &destWidth );

	/** Calculate the height based on the given target width and on the source width and height. 
		Returns value in the destHeight parameter.
	*/
	void CalculateHeightFromWidth(		PMReal const &sourceWidth, PMReal const &sourceHeight,
										uint32 targetWidth,
										uint32 &destHeight );


	/** Calculate the width and height, based on the source width and height, and the 
		given scale amount. Returns values in destWidth and destHeight parameters.
	*/
	void CalculateWidthAndHeightScale(	PMReal const &sourceWidth, PMReal const &sourceHeight,
										PMReal const &scaleAmount,
										uint32 &destWidth, uint32 &destHeight );

	/** TODO::This function is the similiar to PagePanelUtils::GetTargetedNonMasterSpreadsOnly(IPMUnknown* targetWidget, UIDList& spreadUIDList);
		We should put the function in some public place.
	*/
	void GetSelectedNonMasterSpreadsInPagesPanel(IPMUnknown* targetWidget, UIDList& spreadUIDList);

	/** Get the trigger event currently shown in timing panel's drop down event widget.
	*/
	EventTriggerType GetCurrentEventTypeInTimingPanel();

	ErrorCode UngroupTimingItems(IDynamicEventTimingMgr::DynamicTargetList const &itemList);

	ErrorCode GroupTimingItems(IDynamicEventTimingMgr::DynamicTargetList const &itemList);

	void GetSelectedTimingItems(IDataBase* db, IDynamicEventTimingMgr::DynamicTargetList &itemList);
	PMReal GetSelectedTimingItemsDelay (IDynamicEventTimingSuite* iTimingSuite, const EventTriggerType& trigger, const NodeIDList& nodes, bool& mixed);
	uint32 GetSelectedTimingItemsGroupPlays (IDynamicEventTimingSuite* iTimingSuite, const EventTriggerType& trigger, const NodeIDList& nodes, uint32& groupIndex);
	PMReal GetTimingPanelEditControlValue (IPanelControlData* iTimingPanelData, const WidgetID& editWidgetID, bool& hasValue, PMString& errorString);
	WidgetID UpdateTimingItemsIfNecessary (IPMUnknown* iRelatedWidget, const NodeIDList& nodes);
	void DisplayErrorAndSetTimingPanelEditBoxFocus (IPanelControlData* iTimingPanelData, const WidgetID& editWidgetID, const PMString& errorString);
	void UpdateTimingPanelEditBoxFocus (IPMUnknown* iRelatedWiget, const WidgetID& editWidgetID);

	uint32 GetDirectionFromSelectionIndex(ClassID const &transitionClassID, int32 const &selectIndex);
	uint32 GetSpeedFromSelectionIndex(int32 const &speedSelectedIndex);

	void DrawGroupWidgetLines(PMPoint const &startPoint, PMReal const &width, PMReal const &height, dvaui::drawbot::Drawbot *drawbotP, 
		                      bool const isHilite, bool16 const bIsFirstItemInGroup, bool16 const bIsLastItemInGroup);

	bool AllItemsInSameTimingGroup(IDynamicEventTimingMgr::DynamicTargetList const &itemList, uint32& groupIndex);
	bool AllItemsInTimingGroups(IDynamicEventTimingMgr::DynamicTargetList const &itemList, std::map<int32, IDynamicEventTimingMgr::DynamicTargetList>& groupTargetList);

	int16 MapAnimationPanelDetailLevel (bool showPreview, bool showSubProperty);
	void UpdateAnimationPanelSize (IControlView* iAnimationPanelView, bool showPreview, bool showSubProperty);
	void UpdateAnimationItemName (IAnimationAttributeSuite* iAttrSuite, IPMUnknown* iRelatedWidget);
	void UpdateAnimationPreviewProxy(const IPanelControlData* iAnimatilnPanelData, IAnimationAttributeSuite* iAnimationAttrSuite = nil);

	enum ContainingDirectoryBehavior { kDoNotDeleteContainingDirectory, kDeleteContainingDirectory };
	bool DeleteTempExportDirectory(IDFile const &tempExportDirectory);
}

#endif //!def __DynamicDocumentsUIUtils__
