//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ISelectionFilter.h $
//  
//  Owner: Stacy Molitor
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
#ifndef __ISELECTIONFILTER__
#define __ISELECTIONFILTER__

#include "IPMUnknown.h"
#include "ISelectionMessages.h"
#include "PathSelectionList.h"

class UIDList;
class IConcreteSelection;

/**  Defines the interface for a selection filter.  Used so plugins can put
	restrictions (filters) on what gets selected.

	Typical use case is inlines, where only one can be selected, or guides, which aren't selected
	at same time as regular page items.
	
	The selection filters are called whenever the selection changes (inside SelectUtils).
	Everyone should be using these selection utilities to do selection.

	@ingroup layout_select
	@ingroup arch_select
*/
class ISelectionFilter : public IPMUnknown
{
public:
/**
	Can change the list of items to select and whether to replace or add the list to 
	the existing selection.
	This filter is used on all selection types except for Marquee and select all
	@param itemsToSelect UIDList
	@param replaceOrAdd Selection action
	@param currentSelection current Selection
	@param concreteSelection is the selection boss.
*/
	virtual void FilterSelection(UIDList& itemsToSelect, Selection::Action &replaceOrAdd, UIDList& currentSelection, IConcreteSelection* concreteSelection) = 0;

/** This is the filter used from SelectUtils::DeselectPageItems().
	For example StandOffSelectionFilter deselects standoff pageitems if the main item gets deselected.
	@param itemsToSelect UIDList
	@param currentSelection current Selection
	@param concreteSelection is the selection boss.
*/
	virtual void FilterDeselect( UIDList& itemsToSelect, UIDList& currentSelection, IConcreteSelection* concreteSelection) = 0;
	
};

#endif