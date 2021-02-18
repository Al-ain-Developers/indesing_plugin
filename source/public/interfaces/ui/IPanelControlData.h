//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelControlData.h $
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
#ifndef __IPanelControlData__
#define __IPanelControlData__

#include "PMTypes.h"
#include "widgetid.h"
#include "IControlView.h"

/** Interface that container widgets implement
*/
class INTERFACE_DECL IPanelControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPANELCONTROLDATA };

	// -----------------------
	/**@name Maintenance */
	//@{

	/** Add a child widget at position 'at'. If 'at' is -1 the widget is added
		at the end of the of the child widget list.
	*/
	virtual void			AddWidget(IControlView *w, int32 at = -1, bool16 invalidate = kTrue) = 0;
								 
	/** Remove widget 'w'.
	*/
	virtual void			RemoveWidget(IControlView *w, bool16 invalidate = kTrue, bool16 deleteUID = kFalse) = 0;
								
	/** Move the widget 'w' to a new position in the child widget list. Does not change parent or reattach observers.
	    0 would move to start of list, 1 to next position, etc. -1 can be used to move widget to the end of the list.
	*/
	virtual void			MoveWidget(IControlView *w, int32 at, bool16 invalidate = kTrue) = 0;

	/** Remove widget at position 'index'.
	*/ 
	virtual void			RemoveWidget(int32 index, bool16 invalidate = kTrue, bool16 deleteUID = kFalse) = 0;
								
	/** Release all widgets.
	*/
	virtual void			ReleaseAll(bool16 deleteUID = kTrue) = 0;
								 
	//@}							
	
	// -----------------------
	/**@name Inquisition */
	//@{

	/** Return the widget whose position in the widget list is 'index'.
	*/
	virtual IControlView*	GetWidget(int32 index) const = 0;
	
	enum {
		kSearchLevel_Invalid = 0,
		kSearchLevel_Self = 1,
		kSearchLevel_SelfAndChildren = 2,
		kSearchLevel_SelfChildrenAndGrandchildren = 3,
		kSearchLevel_SelfChildrenGrandchildrenAndGreatgrandchildren = 4,
		
		kSearchLevel_AllDescendants = 9999,
	};
	
								
	/** Recursively find the widget whose widget id is 'widgetId'. Only search
		'searchLevels' deep.
	*/
	virtual IControlView*	FindWidget(const WidgetID& widgetId, int16 searchLevels = kSearchLevel_AllDescendants) const = 0;
							
	/** Recursively find the widget that windowPt falls within. Only search
		'searchLevels' deep.
	*/
	virtual IControlView*	FindWidget(const SysPoint& windowPt, int16 searchLevels = kSearchLevel_AllDescendants) const = 0;
								
	/** Returns the widgets visible state flag.
	*/
	virtual bool16			GetWidgetVisibleState(int32 index) const = 0;
								
	/** Returns true if the widget is currently instantiated.
	*/
	virtual bool16			IsWidgetInstantiated(int32 index) const = 0;
								
	/** Get the position of widget 'w'.
	*/
	virtual int32			GetIndex(const IControlView *w) const = 0;
								 
	/** Return the number of child widgets.
	*/
	virtual int32			Length() const = 0;
	//@}
	

	// -----------------------
	/**@name Notification */
	//@{

	/** Called by child widget when one of its attributes changes. Only a small
		set of 'interesting' attrubutes are defined. See WidgetID.h.
	*/
	virtual void			WidgetAttributeChanged(IControlView* view, const WidgetAttributeID& id) = 0;
	//@}							
								
	// -----------------------
	/**@name Keyboard Focus */
	//@{

	/** Sets the keyboard focus to the specified widget
	*/
	virtual void			SetKeyboardFocus(const WidgetID& widgetId) = 0;
	//@}							

	// -----------------------
	/**@name Keyboard Focus */
	//@{

	/** Sets the keyboard focus to the specified widget.
		controlView, passed must be one of its children.
	*/
	virtual void			SetKeyboardFocus(const IControlView* widget) = 0;
	//@}							

};

#endif
