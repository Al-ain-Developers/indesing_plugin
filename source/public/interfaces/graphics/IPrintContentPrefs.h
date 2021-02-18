//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintContentPrefs.h $
//  
//  Owner: Heath Lynn
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
#ifndef __IPrintContentPrefs__
#define __IPrintContentPrefs__

#include "IPMUnknown.h"
#include "PrintID.h"

class IPrintData;

/**
 IPrintContentPrefs are used to allow users to control which content they would 
 like printed or omitted from printing. Such content includes text, page items,
 layout grids, and frame grids.

 These preferences are only considered when IViewPortAttributes::SetViewPortFilterContent 
 on the print port is set to true.

 The printing of baseline grids and ruler guides is controlled by a different
 interface, IPrintData->GetPrintWYSIWYGGridsGuides(), and has core access for Roman
 and J products in the Print dialog, General subdialog.

 @see IViewPortAttributes::SetViewPortFilterContent
 @see IPrintData::GetPrintWYSIWYGGridsGuides
 */
class IPrintContentPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRINTCONTENTPREFS };

	/** Enumeration governing how grids are to be printed */
	enum GridView
	{
		kInvalidView = -1,
		kPerFrameGridView = 0,
		kGridView = 1,
		kZNGridView = 2,
		kAlignmentGridView = 3
	};

	/** Unused */
	enum WhenGrid
	{
		kAlways = 0,
		kWhenEmpty = 1
	};

	/**
	 Sets preference for printing text
	 
	 @param printText		Flag: whether to print text
	 */
	virtual void	SetPrintText(bool16 printText) = 0;
	/**
	 Gets preference for printing text
	 
	 @return kTrue if printing text, else kFalse
	 */
	virtual bool16	GetPrintText() const = 0;
	
	/**
	 Sets preference for printing page items
	 
	 @param printPageItems		Flag: whether to print page items
	 */
	virtual void	SetPrintPageItems(bool16 printPageItems) = 0;
	/**
	 Gets preference for printing page items
	 
	 @return kTrue if printing page items, else kFalse
	 */
	virtual bool16	GetPrintPageItems() const  = 0;
	
	/**
	 Sets preference for printing layout grids
	 
	 @param printLayoutGrids	Flag: whether to print layout grids
	 */
	virtual void	SetPrintLayoutGrids(bool16 printLayoutGrids) = 0;
	/**
	 Gets preference for printing layout grids
	 
	 @return kTrue if printing layout grids, else kFalse
	 */
	virtual bool16	GetPrintLayoutGrids() const  = 0;
	
	/**
	 Sets preference for printing frame grids
	 
	 @param printFrameGrids		Flag: whether to print frame grids
	 */
	virtual void	SetPrintFrameGrids(bool16 printFrameGrids) = 0;
	/**
	 Gets preference for printing frame grids
	 
	 @return kTrue if printing frame grids, else kFalse
	 */
	virtual bool16	GetPrintFrameGrids() const  = 0;
	
	/**
	 Sets preference for printing frame grids when empty
	 
	 @param printWhenEmpty	Flag: whether to print frame grids when empty
	 */
	virtual void	SetOnlyPrintFrameGridWhenEmpty(bool16 printWhenEmpty) = 0;
	/**
	 Gets preference for printing frame grids when empty
	 
	 @return kTrue if printing frame grids when empty, else kFalse
	 */
	virtual bool16	GetOnlyPrintFrameGridWhenEmpty() const  = 0;
	
	/**
	 Sets preference for printing frame grid view
	 
	 @param viewNumber	The frame grid view to print
	 */
	virtual void	SetPrintFrameGridView(int32 viewNumber) = 0;
	/**
	 Gets preference for printing frame grid view
	 
	 @return The frame grid view to print
	 */
	virtual int32	GetPrintFrameGridView() const  = 0;

	/**
	 Sets preference for frame grid stroke weight
	 
	 @param points		The new frame grid stroke weight
	 */
	virtual void	SetFrameGridStrokeWeight( const PMReal & points ) = 0;
	/**
	 Gets preference for frame grid stroke weight
	 
	 @return The frame grid stroke weight
	 */
	virtual PMReal GetFrameGridStrokeWeight() const  = 0;

	/**
	 Sets preference for layout grid stroke weight
	 
	 @param points		The new layout grid stroke weight
	 */
	virtual void	SetLayoutGridStrokeWeight( const PMReal & points ) = 0;
	/**
	 Gets preference for layout grid stroke weight
	 
	 @return The layout grid stroke weight
	 */
	virtual PMReal GetLayoutGridStrokeWeight() const  = 0;

	/**
	 Sets preference for UI flags used during print
	 
	 @param nFlags		The new UI flags
	 */
	virtual void SetUIFlags( UIFlags nFlags ) = 0;
	/**
	 Gets preference for UI flags to use during print
	 
	 @return The UI flags to use during print
	 */
	virtual UIFlags GetUIFlags() const  = 0;

	/**
	 Copies preferences from an IPrintContentPrefs instance
	 
	 @param from		The prefs to copy
	 */
	virtual void CopyFrom(IPrintContentPrefs const* from) = 0;
	/**
	 Copies preferences from an IPrintData instance
	 
	 @param printData	The data to copy
	 */
	virtual void CopyFrom(IPrintData const* printData) = 0;
	/**
	 Copies preferences to an IPrintData instance
	 
	 @param printData	The data to copy to
	 */
	virtual void CopyTo(IPrintData * printData) const = 0;
};

#endif
