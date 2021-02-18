//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IControlledPageItems.h $
//  
//  Owner: Brendan O'Shea
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
//  
//  An interface for a pageitem which keeps a list of dependent page items (i.e.
//  ones that refer back to this item for something). 
//  
//========================================================================================

#pragma once
#ifndef __IControlledPageItems__
#define __IControlledPageItems__

#include "IPMUnknown.h"
#include "MasterPageID.h"

/** This is a persistent interface, added into drawable page items and guides that keeps track
	of what page items elsewhere in the document are overridden from this page item. Used primarily 
	to maintain connections between master page items and their overrides. @see IControllingPageItem
*/
class IControlledPageItems : public IPMUnknown
{
public:	
		/** @return count of page items overridden from this one */
	virtual int32	ControlledCount() = 0;

		/** add a UID to this items list of controlled items
			@param  controlledPageItemUID IN item controlled by this item
			@param controlledPageItemsPageUID IN page which contains the controlled item
		*/
	virtual void	AddPageItem(UID controlledPageItemUID, UID controlledPageItemsPageUID = kInvalidUID) = 0;

		/** remove a controlled item's UID from this items list. 
			@param piUID IN UID of page item to remove
			@param pageUID IN UID of page that the page item being removed was on
		*/
	virtual void	RemovePageItem(UID piUID, UID pageUID = kInvalidUID) = 0;

		/** replace one controlled page item with another
			@param piUID IN page item currently in this items list of controlled items
			@param pageUID IN page containing the page item being replaced
			@param newPIUID IN page item to replace the existing controlled item with
			@param newPageUID IN page containing the replacement page item
		*/
	virtual void	ReplacePageItem(UID piUID, UID pageUID, UID newPIUID, UID newPageUID) = 0;

		/** clear this page items list of controlled page items  */
	virtual void	RemoveAll() = 0;

		/** Index through all of this page items controlled items 
			@param index IN index of controlled page item
			@param pageUID OUT page which contains the 'index' controlled page item
			@return UID of 'index' controlled page item
		*/
	virtual UID	GetControlledPageItem(int32 index, UID *pageUID = nil) = 0;
};

#endif
