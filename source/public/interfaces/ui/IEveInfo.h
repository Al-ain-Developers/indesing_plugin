//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IEveInfo.h $
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
#ifndef __IEveInfo_h__
#define __IEveInfo_h__

#include "IPMUnknown.h"
#include "DialogLayoutID.h"

/** Interface for providing the information EVE needs about a widget to properly lay it out in a dialog.
*/

class IEveInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IEVEINFO };

	/** Get the height in pixels of the widget
		@return height in pixels of this widget. For container widgets(i.e. panels) this is treated by EVE as a minimum height
	*/
	virtual uint32 GetHeight() const = 0;

	/** Get the width in pixels of the widget. This is typically a measured value for widgets which have a string(i.e. static text, radio buttons, etc)
		@return width in pixels of this widget. For container widgets(i.e. panels) this is treated by EVE as a minimum width
	*/
	virtual uint32 GetWidth() const = 0;
	
	/** Append an EVE express view string describing this widget(& any child widgets)
		@param dialogDesc specifies the string to append to
	*/
	virtual void AppendEveDescriptionForControl(PMString* dialogDesc) const = 0;
	
	/** Apply the changes suggested by EVE to this widget. Usually consists of moving to the new location and resizing to the new size
		@param newTopLeft new top left point to move to (parent relative)
		@param newWidth new width for this widget
		@param newHeight new height for this widget
	*/
	virtual void ApplyEVELayoutToWidget(const PMPoint& newTopLeft, const PMReal& newWidth, const PMReal& newHeight) = 0;
	
	/** report the child arrangement for this widget - only valid for panels
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetChildArrangement() const = 0;
	
	/** Change the child arrangement for this widget - only valid for panels
		@param newArrangement a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual void SetChildArrangement(uint32 newArrangement) = 0;
	
	/** report the child alignment for this widget - only valid for panels
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetChildAlignment() const = 0;
	
	/** report if this panel or this widget has to participate in alignment for first column of labels in dialog
		@return true if Panel needs to be included for alignment with sibing groups or panels
	*/
	virtual bool16 GetIncludeForFirstColumnAlignment() const = 0;

	/** report if this widget specifies not to participate in alignment for column of labels in dialog
		@return true if static text widget is not to be included for alignment across groups.
	*/
	virtual bool16 GetDoNotIncludeForAlignmentOfLables() const = 0;

	/** report the child space after for this widget - only valid for panels
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetChildSpaceAfter() const = 0;
	
	/** report the margin for this widget - only valid for panels
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetMargin() const = 0;

	/** Set the margin for this widget 
		@param a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual void SetMargin(uint32) = 0;

	/** report the space after for this widget 
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetSpaceAfter() const = 0;

	/** Set the space after for this widget 
		@param a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual void SetSpaceAfter(uint32 newSpaceAfter) = 0;

	/** report the alignment for this widget
		@return a constant from EVEInfo.fh indicating the value for this widget
	*/
	virtual uint32 GetAlignment() const = 0;

	/** Report if this widget has EveInfo filled out.
		@return true if this widget has EVE info.
	*/
	virtual bool16 HasEVEInfo() const = 0;

	/** Append an EVE express view string describing this widget(& any child widgets)
	@param dialogDesc specifies the string to append to
	*/
	virtual void AppendEveDescriptionForControlToStdString(std::stringstream &dialogDesc) const = 0;

};

#endif // __IEveInfo_h__

