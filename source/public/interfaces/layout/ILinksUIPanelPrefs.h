//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinksUIPanelPrefs.h $
//  
//  Owner: lance bushore
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
#ifndef __ILinksUIPanelPrefs
#define __ILinksUIPanelPrefs

#include "IPMUnknown.h"
#include "LinksUIID.h"

class ILinkInfoProvider;

/** This interface provides access to the settings for the Links UI panel. */
class ILinksUIPanelPrefs : public IPMUnknown
{
public:	
	/** Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_ILINKSUIPANELPREFS };

	/** Get the current document DB that the Links panel is showing */
	virtual IDataBase* GetCurrentDocDB() const = 0;

	/** Set the current document DB that the Links panel is showing */
	virtual void SetCurrentDocDB(IDataBase* newDocDB) = 0;

	/** Get the current row height for rows in the links panel treeview */
	virtual int32 GetCurrentRowHeight() const = 0;

	/** Set the current row height for rows in the links panel treeview */
	virtual void SetCurrentRowHeight(int32 newHeight) = 0;
	
	/** Get the total number of registered ILinkInfoProviders */
	virtual int32 GetNumInfoProviders() const = 0;
	
	/** Get the nth registered ILinkInfoProvider */
	virtual ILinkInfoProvider* QueryNthInfoProvider(int32 nth) const = 0;
	
	/** Get the number of columns showing in the links panel. Each column is associated with one ILinkInfoProvider */
	virtual int32 GetNumShowingInfoColumns() const = 0;
	
	/** Gets an addref'd pointer to the nth ILinkInfoProvider which is currently showing as a column in the links panel */
	virtual ILinkInfoProvider* QueryNthShowingInfoColumn(int32 nth) const = 0;
	
	/** Sets which ILinkInfoProviders should be shown as columns in the links panel. ILinksUIPanelPrefs does not take ownership of any refs on the pointers. Caller is expected to release any owned refs.*/
	virtual void SetShowingInfoColumns(const K2Vector<ILinkInfoProvider*> columnProviders) = 0;
	
	/** Get the width of the nth Column in the links panel */
	virtual int32 GetNthColumnWidth(int32 nth) const =0;
	
	/** Set the widths for all the columns */
	virtual void SetColumnWidths(const K2Vector<int32>& columnWidths) =0;
	
	/** Get the widths for all the columns */	
	virtual void GetColumnWidths(K2Vector<int32>& columnWidths) const =0;
	
	/** Get how many ILinkInfoProviders are currently showing in the links panel 'More info' section. */
	virtual int32 GetNumMoreInfoProviders() const = 0;
	
	/** Get an addref'd pointer to the nth ILinkInfoProvider showing in the 'more info' section */
	virtual ILinkInfoProvider* QueryNthMoreInfoProvider(int32 nth) const = 0;
	
	/** Set which ILinkInfoProviders should be used in the more info section.  ILinksUIPanelPrefs does not take ownership of any refs on the pointers. Caller is expected to release any owned refs. */
	virtual void SetMoreInfoProviders(const K2Vector<ILinkInfoProvider*> infoProviders) = 0;

	/** Get the ILinkInfoProvider being used as the primary sort in the links panel. Can return nil if not currently sorted. */
	virtual const ILinkInfoProvider* GetSortInfoProvider() const = 0;

	/** Get the ILinkInfoProvider being used as the secondary sort in the links panel. Can return nil if not currently sorted. */
	virtual const ILinkInfoProvider* GetSecondarySortInfoProvider() const = 0;
	
	/** Set the ILinkInfoProvider being used as the primary sort in the links panel. The old primary sort will become the secondary sort. */
	virtual void SetSortInfoProvider(const ILinkInfoProvider* newSorter) = 0;
	
	/** Set the flag to sort ascending or descending. */
	virtual void SetSortLinksAscending(bool16 ascend) = 0;

	/** Get the flag to sort ascending or descending. */
	virtual bool16 GetSortLinksAscending() const = 0;
	
	/** Set the pref to show the thumbnail in the name column of the links panel tree view. */
	virtual void SetShowLinkThumbnail(bool16 showThumbnail) = 0;

	/** Get the pref to show the thumbnail in the name column of the links panel tree view. */
	virtual bool16 GetShowLinkThumbnail() const = 0;

	/** Set the pref to show the thumbnail in the info section of the links panel. */
	virtual void SetShowLinkInfoThumbnail(bool16 showThumbnail) = 0;

	/** Get the pref to show the thumbnail in the info section of the links panel. */
	virtual bool16 GetShowLinkInfoThumbnail() const = 0;
				
	/** Set the pref to collapse multiple links to same resource */
	virtual void SetCollapseMultipleLinksToSameResource(bool16 collapse) = 0;

	/** Get the pref to collapse multiple links to same resource */
	virtual bool16 GetCollapseMultipleLinksToSameResource() const = 0;
				
};

#endif
