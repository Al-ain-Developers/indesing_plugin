//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IListBoxAttributes.h $
//  
//  Owner: Frits Habermann
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
#ifndef __IListBoxAttributes__
#define __IListBoxAttributes__

#ifdef ID_DEPRECATED  // listboxes will disappear from a future version of InDesign. Please use TreeViews instead.

#include "PMPoint.h"
#include "widgetid.h"

/** Interface representing list box properties.
*/
class IListBoxAttributes : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ILISTBOXATTRIBUTES };

	/**@name Initialization */
	//@{

	/** Initialize this interface procedurally.
		@param listDimensions see GetListDimensions()
		@param cellHeight see GetCellHeight()
		@param borderWidth see GetBorderWidth()
		@param hasVerticalScrollBar see HasVerticalScrollBar()
		@param hasHorizontalScrollBar see HasHorizontalScrollBar()
	*/
	virtual void	Init(const PMPoint& listDimensions,	const PMReal& cellHeight, const PMReal& borderWidth,
						 const bool16& hasVerticalScrollBar, const bool16& hasHorizontalScrollBar) = 0;
						 
	//@}					 

	/**@name RsrcID for items in the listbox */
	//@{

	/** Get the current resource ID to use for each widget item in listbox.
		@return current resource ID for items in list
	*/
	virtual RsrcID	GetItemWidgetRsrcID() const = 0;
					 

	/** Set the current resource ID to use for each widget item in listbox.
		@param rsrcID specifies resource ID to use
	*/
	virtual void	SetItemWidgetRsrcID(const RsrcID& rsrcID) = 0;
					 
	//@}

	/**@name Geometry */
	//@{
	
	/** Return the dimensions of the list. i.e. how many cells in each
		dimension?
		@return number of cells in each dimension, held in a PMPoint. So pt.X() would give the cells across, and
			pt.Y() the cells down.
	*/
	virtual PMPoint GetListDimensions() const = 0;
						 
	/** Return the dimensions of a cell.
		@return height of a cell
	*/
	virtual PMReal	GetCellHeight() const = 0;
						 
	/** Return the width of the border between cells.
		@return border-width between cells
	*/
	virtual PMReal	GetBorderWidth() const = 0;
						
	//@}
	
	/**@name Scrollbar-related */
	//@{
	
	/** Determine if this list has vertical scrollbar.
		@return kTrue if the list has vertical scrollbar
	*/
	virtual bool16	HasVerticalScrollBar() const = 0;
	
	/** Return the width of vertical scrollbar.
		@return the width of vertical scrollbar
	*/
	virtual int32	GetVerticalScrollBarWidth() const = 0;

	/** Determine if the list has horizontal scrollbar.
		@return kTrue if the list has horizontal scrollbar
	*/
	virtual bool16	HasHorizontalScrollBar() const = 0;
	
	/** Return the height of horizontal scrollbar.
		@return the height of horizontal scrollbar
	*/
	virtual int32	GetHorizontalScrollBarHeight() const = 0;
					
	
	/** Turn on and off drawing. This can help cut down on flicker when
		you are adding a list of elements to the list.
		@param Mute specify whether to turn drawing on or off
	*/
	virtual void	MuteDrawing(bool16 Mute) = 0;
						 
	/** Returns true if drawing is currently muted.
		@return kTrue if drawing muted, kFalse otherwise
	*/
	virtual bool16	IsDrawingMuted() const = 0;
						 
	//@}
	
	/**@name Selection */
	//@{

	/** SetMultiSelection will allow for multiple cells to be selected at a time.
		@param OnOrOff specify whether multiple selection should be enabled
	*/
	virtual void	SetMultiSelection(bool16 OnOrOff) = 0;
						
	/** Determine if multiple selection enabled.
		@return kTrue if multiple selection is on, kFalse for single selection
	*/
	virtual bool16	GetMultiSelection() const = 0;
						
						
 
	/** SetAlwaysSelected will force the list to always have an item selected.  In
		other words, a user cannot deselect every item.
		@param OnOrOff specifies whether the list is to always have an item selected or not
	*/
	virtual void	SetAlwaysSelected(bool16 OnOrOff) = 0;
						 
	/** Returns a bool16 specifying whether at least one item always has to be selected.
		@return kTrue if at least one item always has to be selected
	*/
	virtual bool16	GetAlwaysSelected() const = 0;
						 
	
	/** If notify is true then notification will be sent out if the user selects
		the currently selected item.
		@param notify if kTrue, a reselection will trigger a broadcast to registered observers
	*/
	virtual void	SetNotifyOnReselect(bool16 notify) = 0;
						
	/** Returns a bool16 specifying whether notify on reselect is on.
		@return kTrue if notify on reselect is enabled, kFalse otherwise
	*/
	virtual bool16	GetNotifyOnReselect() const = 0;
						 
	//@}
					

	/**@name Draggin'n'Droppin */
	//@{
	
	/** SetReorderable will allow the user to drag list items and reorder them in the list.
		If multiple selection is on (actually, if single selection is off), the user can
		reorder multiple items in a single drag.
		@param OnOrOff specify whether list can be reordered by user
	*/
	virtual void	SetReorderable(bool16 OnOrOff) = 0;
						 
	/** Returns a bool16 specifying whether the user can reorder list items or not.
		@return kTrue if can be reordered by user, kFalse otherwise
	*/
	virtual bool16	GetReorderable() const = 0;
						 
	

	/** SetDraggable will allow the user to drag item(s) to the "new" and "delete" buttons.
		@param OnOrOff specify whether user should be able to drag to new/delete buttons
	*/
	virtual void	SetDraggable(bool16 OnOrOff) = 0;
						 
	/** Returns a bool16 specifying whether the user can drag items to the new and delete buttons or not.
		@return kTrue if user can drag items to new/delete buttons, kFalse otherwise
	*/
	virtual bool16	GetDraggable() const = 0;
						 
	

	/** SetDragDroppable will allow the user to drag items out of the list and drop them
		@param OnOrOff specify if the user should be able to drag items out of list or not
	*/
	virtual void	SetDragDroppable(bool16 OnOrOff) = 0;
						 
	/** Returns a bool16 specifying whether the user can drag items out of the list.
		@return kTrue if user can drag items out, kFalse otherwise
	*/
	virtual bool16	GetDragDroppable() const = 0;
						
	//@}

	/**@name Geometry */
	//@{
	
	/** Set the dimensions of a cell.
		@param cellHeight specifies new height
	*/
	virtual void	SetCellHeight(const PMReal& cellHeight) = 0;
						
	//@}

};

#endif

#endif
