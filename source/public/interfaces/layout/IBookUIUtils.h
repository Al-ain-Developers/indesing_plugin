//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookUIUtils.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IBOOKUIUTILS__
#define __IBOOKUIUTILS__

#include "IPMUnknown.h"
#include "IPanelControlData.h"

#include "K2Vector.h"
#include "UIDList.h"
#include "Utils.h"

#include "BookID.h"

/** This interface exposes some utility functions related to book UI.
	@ingroup layout_book
	@see kUtilsBoss
	@ingroup layout_util
 */
class IBookUIUtils : public IPMUnknown
{
	public:
		/** kDefaultIID */
		enum { kDefaultIID = IID_IBOOKUIUTILS };

		/** Get the total list items(documents) from the book panel.
			@param panelData describes the book panel control data.
			@return int32 indicating how many items(documents) in the book panel.
		*/
		// Comments: Get the total list items in this panel.
		virtual int32 GetListItems(IPanelControlData* panelData) = 0;

		/** Helper function to return the indices of selected items in this list and 
			their BookContent(Indd document) UIDs.
			@param selectedItems describe the indices of the selected items. This is an out parameter.
			@param selectedUIDList describe book content UIDs corresponding to the selected items. This is an out parameter.
			@param panelData describe the book panel control data and use widget parent interface of the panel to find the list box and then the selected items
			@return int32 as the number of selected items.
		*/
		virtual int32 GetSelectedBookContents
						(
							K2Vector<int32>& selectedItems,
							UIDList* &selectedUIDList,
							IPanelControlData* panelData
						) = 0;

		/** Get book file from book panel..
			@param bookFile describes the IDFile of the book. This is an out parameter.
			@param widget, IPMUnknown interface for widget in book panel. Typically comes from UpdateActionStates or DoAction from action manager.
			@return void.
		*/
		virtual void GetBookFileFromBookPanel(IDFile& bookFile, IPMUnknown* widget) = 0;

		/** Query the book panel data from the current active UI such as panel's popup menu,
		    panel's current selection, buttons on the panel etc.
			@param widget, IPMUnknown interface for widget in book panel. Typically comes from UpdateActionStates or DoAction from action manager.
			@return panel control data of the book.
		*/
		virtual IPanelControlData* QueryBookPanelData(IPMUnknown* widget) = 0;

		/** Query the book panel data for the active book (IBookManager::GetCurrentActiveBook)
			@param void.
			@return panel control data of the book.
		*/
		virtual IPanelControlData* QueryActiveBookPanel(void) = 0;

		/** INTERNAL USE ONLY private function, DO NOT USE.
			@param widget, IPMUnknown interface for from UpdateActionStates or DoAction from action manager.
			@return void.
		*/
		virtual void SetBookPanelWidget(IPMUnknown* widget) = 0;

		/** INTERNAL USE ONLY private function, DO NOT USE.
			@param void.
			@return widget, IPMUnknown interface from UpdateActionStates or DoAction from action manager.
		*/
		virtual IPMUnknown* GetBookPanelWidget(void) = 0;
};

#endif	// __IBOOKUIUTILS__
