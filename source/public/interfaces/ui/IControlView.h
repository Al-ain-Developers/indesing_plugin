//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IControlView.h $
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
#ifndef __IControlView__
#define __IControlView__

#include "PMTypes.h"
#include "widgetid.h"
#include "SystemUtils.h"
#include "PMRect.h"
#include "PMString.h"
#include "IControlViewDefs.h"

class IViewPort;
//class ITransform;
class PMRect;
class PMPolygon4;
//========================================================================================
// Types
//========================================================================================

typedef uint32 WidgetAttributeID;
typedef uint16 FrameBinding;

/** kDefaultWidgetId is seldom used. It has the same value as kInvalidWidgetID. Widgets should all be given unique WidgetIDs */
static const WidgetID kDefaultWidgetId = 0;

/** Interface responsible for determining the visual appearance of widgets. Handles drawing in
	various states. Also involved in hit testing and Auto attaching/detaching observers.
*/
class INTERFACE_DECL IControlView : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_ICONTROLVIEW };

	// -----------------------------------------------------------
	/**@name Initialization */
	//@{

	/** Initialize the control view.
		@param widgetId specifies WidgetID to associate with this widget
		@param fFrame bounding box for the control
		@param rsrcID identifies resource to associate with this widget
	*/
	virtual void					Init(const WidgetID& widgetId = kDefaultWidgetId,
										 const PMRect& fFrame = kZeroRect,
										 RsrcID rsrcID = 0) = 0;
	/** Called after the widget hierarchy is created. Can be
		overriden to do initialization that may need the hierarchy
		to perform.
	*/
	virtual void					DoPostCreate() = 0;
								
	//@}

	// -----------------------------------------------------------
	/**@name Attributes */
	//@{

	/**  Get the resource  ID for the widget.
	*/
	virtual RsrcID					GetRsrcID() const = 0;

	/** Set the resource ID for the widget.
		@param id resource ID to associate with this widget
	*/
	virtual	void					SetRsrcID(const RsrcID &id) = 0;
										
	/** Get the resources plugin id for the widget.
	*/
	virtual PluginID				GetRsrcPluginID() const = 0;

	/** Set the resources plugin id for the widget.
	*/
	virtual	void					SetRsrcPluginID(const PluginID &id) = 0;
										// Get and set the resources plugin id for the widget.
	/** Get the widget ID. The widget ID is used to uniquely
		identify a particular child widget within a panel.
		@return ID for this widget
	*/
	virtual WidgetID				GetWidgetID() const = 0;

	/** Set the widget ID.
	*/
	virtual	void					SetWidgetID(const WidgetID &id) = 0;

	/** 
		This flag will instruct view to clip it's children drawing
		within it's view
	*/
	virtual void	SetClipToSelfEnabled(bool16 clipChildren) const = 0;	
								
	//@}


	// -----------------------------------------------------------
	/**@name Geometry */

	//@{
	/** Set a frame for the widget within the parent's co-ordinate system.
		@param newFrame specifies frame for the widget
		@param invalidate if set to kTrue, indicates that the widget should be marked for redraw
	*/
	virtual void					SetFrame(const PMRect& newFrame, bool16 invalidate = kTrue) = 0;

	/** Get the frame  of the widget within the parent's co-ordinate system.
		@return reference to the frame enclosing the widget
	*/
	virtual const PMRect&			GetFrame() const = 0;
									
	/** Get the frame  of the widget within the widget's inner co-ordinate system.
	 @return PMRect contraining the frame enclosing the widget
	 */
	virtual const PMRect			GetLocalFrame() const = 0;

	/** Resize the widget.
	*/
	virtual	void					Resize(const PMPoint& newDimensions, bool16 invalidate = kTrue) = 0;

	/** Move the widget to a specific position within the parent's
		coordinate system.
		@param where new top-left location for widget frame in parent's co-ordinate system
		@param invalidate if set to kTrue, indicates that the widget should be marked for redraw
	*/
	virtual	void					MoveTo(const PMPoint& where, bool16 invalidate = kTrue) = 0;

	/** Set the frame binding. Each side of a widget's frame can be bound to the same side of its parent frame.
		Whenever the parent widget is moved/resized, child widgets which have binding other than kBindNone will
		adapt to their parent's new size/position.
		
		Binding choices are kBindNone, kBindLeft, kBindTop,
		kBindRight, kBindBottom, kBindAll. Bindings can be logically composed using the '|' operator.
		@param binding specifies the new binding
	*/
	virtual void					SetFrameBinding(const FrameBinding& binding) = 0;

	/** Get the frame binding. Each side of a widget's frame
		can be bound to the same side of its parent frame.
	*/
	virtual FrameBinding			GetFrameBinding() const = 0;

	/** The widget should adapt its geometry based on the parent's
		geometry. Called on changes in parent's size.
	*/
	virtual void					AdaptToParentsSize(const PMPoint& dimensions) = 0;

	/** The widget should adapt it geometry based on one of its children
		geometry changing. Only called when child changes and if propagate is set.
	*/
	virtual void					AdaptToChildsGeometry(const PMPoint& delta, const FrameBinding& childsBinding, bool16 invalidate = kFalse) = 0;
										 
	/** Before resizing a widget, the client can ask if the size makes sense by calling this method. Return size constraints.
	*/
	virtual PMPoint					ConstrainDimensions(const PMPoint& dimensions) const = 0;
									
	/** Return a region that represents the area that the view draws
		in. The graphics context clips drawing to this region. The returned
		region is in window coordinates.
	*/
	virtual SysRgn					GetDrawRegion() = 0;
										
	/** Returns kTrue if all potential children of this view should be contained within this views DrawRegion
		Returns kFalse if this is not the case.
		
		By default, the draw region for a widget is an intersection of it's bounding box and it's parent's draw region, since
		typically, the parent widget clips the child widgets drawing.  In some cases, a widget may not want to restrict it's children's drawing
		to it's bounds.  For these cases, DrawRegionEncompassesChildRegions() should return kFalse.
	*/
	virtual bool16 				DrawRegionEncompassesChildRegions() const = 0;

	/** Return the bounding box, in window coordinates, of the view. Its
		preferable to use GetFrame.

		Note:  Listbox controls(kStdListBoxWidgetNewBoss) on the Windows platform behave differently.  They will always return a bounding box in their own
		coordinates instead of the window coordinates.	They will always return a bounding box with an origin of 0,0.  Also, all children
		of listbox controls will return a bounding box relative to the listbox instead of the window.
	*/
	virtual SysRect 				GetBBox() const = 0;

	/** Returns a transform for mapping geometry in content coordinate
		space to window cooridinate space.

		Note:  Listbox controls(kStdListBoxWidgetNewBoss) on the Windows platform behave differently.  They do not include the transform from listbox to window
		All children of listbox controls will get a content to listbox transform.
	*/
	virtual PMMatrix*				GetContentToWindowTransform() const = 0;
	virtual void					ContentToWindowTransform( PMPoint * point) const = 0;
	virtual void					ContentToWindowTransform( PMRect * rect) const = 0;
	virtual void					ContentToWindowTransform( PMPolygon4 * poly) const = 0;
	virtual void					WindowToContentTransform( PMPoint * point) const = 0;
	virtual void					WindowToContentTransform( PMRect * rect) const = 0;
	virtual void					WindowToContentTransform( PMPolygon4 * poly) const = 0;
	virtual PMMatrix				GetContentToWindowMatrix() const = 0;
	virtual PMMatrix				GetWindowToContentMatrix() const = 0;
	virtual PMRect					GetContentBounds_() const = 0;
									
	/** Invalidates transforms, causing them to be recalculated next time
		they're asked for.
	*/
	virtual void					InvalidateTransform() = 0;
									
	/** Deletes cached DrawRegion, causing it to be recalculated next time
		they're asked for.
	*/
	virtual void					DeleteDrawRegion() = 0;

	/** Returns true if the point 'where' is within the bounds of the view. Note this method really returns a boolean. Not sure why the return type is an int32.
	*/
	virtual int32 					HitTest(const SysPoint& where) = 0;
	
	// Geometry methods replacing similar ones from IWindowPort that are no longer supported, as of CS6.
	//
	//	Note the unlike IWindowPort, these methods don't require an acquired and/or focused viewport to work.
	//
	//	Also note that IWindowPort converts between global and window coordinates, so the term "local" can be misleading.
	//	That why here we have two versions of, GlobalToLocal (and vice versa) one converting to window coords and one converting to view
	//	coords. To avoid confusion, neither of the new methods is named GlobalToLocal.
	//	Where the "window" is defined by the object above us in the hierarchy containing an IWindow interface.
	
	/**
	 Converts the specified rectangle/point from global (screen) coordinates to local coordinates.
	 */
	virtual PMRect		GlobalToView(const PMRect& convertRect) const = 0;
	virtual PMPoint		GlobalToView(const PMPoint& convertPoint) const = 0;
	virtual PMRect		GlobalToWindow(const PMRect& convertRect) const = 0;
	virtual PMPoint		GlobalToWindow(const PMPoint& convertPoint) const = 0;

	/**
	 Converts the specified rectangle from local coordinates to global (screen) coordinates.
	 */
	virtual PMRect		ViewToGlobal(const PMRect& convertRect) const = 0;
	virtual PMPoint		ViewToGlobal(const PMPoint& convertPoint) const = 0;
	virtual PMRect		WindowToGlobal(const PMRect& convertRect) const = 0;
	virtual PMPoint		WindowToGlobal(const PMPoint& convertPoint) const = 0;
	
	//@}

	// -----------------------------------------------------------
	/**@name Rendering */
	//@{

	/** Should be overridden to render the contents of the view.
	*/
	virtual void 					Draw(IViewPort* viewPort, SysRgn updateRgn = nil) = 0;
										
	/** Invalidate a portion of the control view. 
		@param invalidRect should be in content coordinates(i.e. GetFrame()).
		nil invalidates the whole control view.
	*/
	virtual void					Invalidate(PMRect *invalidRect = nil) = 0;
										
	/** Validate a portion of the control view.
		@param invalidRect should be in window coordinates(i.e. GetBBox()). 
		nil validates the whole control view.
	*/
	virtual void					Validate(PMRect *invalidRect = nil) = 0;
										
	
	/**	Redraws the invalid region directly. If 'forceRedraw' is true the redraw will happen immediately otherwise it just invals the region.
	 
		@param invalidRgn region of the window to draw. This region will NOT be disposed by ForceRedraw. If nil, then entire view (default)
		@param forceRedraw kTrue if you'd like to draw now (default), kFalse to just inval.
	*/
	virtual void					ForceRedraw(SysRgn invalidRgn = nil, bool16 forceRedraw = kTrue) = 0;

	/** Set hiliting on or off.
		@param doHilite can be set to kFalse to turn hilite off.
	*/
	virtual void					Hilite(bool16 doHilite = kTrue) = 0;

	/** Set hiliting off.
	*/
	virtual void					Unhilite() = 0;

	/** Inspect the current hilite state.
		@param return the current hilite state
	*/
	virtual bool16					IsHilited() const = 0;
	
	/** Returns true if mouse is in a rollover state, requires rolloverboss
		@param return the current hilite state
	*/									
	virtual bool16                    IsRolledOver() const = 0;
	//@}

	// -----------------------------------------------------------
	/**@name Show-Enable attributes */
	//@{
	void ShowView(bool16 doShow = kTrue)
	{
		Show( doShow);
	}
	void HideView()
	{
		Hide();
	}

private:
	/** 
	*/
	virtual void					Show(bool16 doShow = kTrue) = 0;

	/** 
	*/
	virtual void					Hide() = 0;
public:

	/** Return true if this view's visible flag is set.
	*/
	virtual bool16					GetVisibleState() const = 0;
										// 
	/** Return true if this view is visible. A view is visible if its
		visible flag is set and all of its ancestors are visible.
		@param requireVisibleWindow specifies what to do if this widget and all it's parent widgets are visible, but it's not in a visible window.
	*/
	virtual bool16					IsVisible(bool16 requireVisibleWindow = kFalse) const = 0;
										// 
	/** 
	*/
	virtual void					ParentsVisibleStateChanged(bool16 visible) = 0;
										// Called whenever the widget's parent's visible state changes.

	/** 
	*/
	virtual void					Enable(bool16 doEnable = kTrue, bool16 invalidate = kTrue) = 0;
	/** 
	*/
	virtual void 					Disable(bool16 invalidate = kTrue) = 0;
	/** Return true if this view's enabled flag is set.
	*/
	virtual bool16					GetEnableState() const = 0;
										
	/** Return true if this view is enabled. A view is enabled if its
	 enable flag is set and all of its ancestors are enabled.
	*/
	virtual bool16 					IsEnabled() const = 0;
										
	/** Called whenever the widget's parent's enable state changes.
	*/
	virtual void					ParentsEnableStateChanged(bool16 visible, bool16 invalidate = kTrue) = 0;
									
	//@}

	// -----------------------------------------------------------
	/**@name Window attributes */
	//@{

	/** Called when a window containing this widget is
		made active or inactive. Do things like dim
		selections, hide scroll bars, etc.		
	*/
	virtual void					WindowActivated() = 0;
	/** Called when a window containing this widget is
		made active or inactive. Do things like dim
		selections, hide scroll bars, etc.	
	*/
	virtual void					WindowDeactivated() = 0;
										
	
	/** Called when a window containing this widget is shown.	
	*/
	virtual void					WindowShown() = 0;

	/** Called when a window containing this widget is hidden.		
	*/
	virtual void					WindowHidden() = 0;
	
	/** Called when window containing this widget changes.
		i.e. This widget is moved from one window to another.
	*/
	virtual void					WindowChanged() = 0;
										

	/** Called when window containing this widget closes.
	*/
	virtual void					WindowClosed() = 0;
									

	//@}
	
	// -----------------------------------------------------------
	/**@name Notification */
	//@{
	/** Called when this widget's parent will be purged in
		the near future.
	*/
	virtual void					ParentPurged() = 0;
									
	//@}


	// -----------------------------------------------------------
	/**@name Auto attaching-detaching */
	//@{

	/** Call to automatically attach observers. Shouldn't
		generally be called. Called on making view visible.
	*/
	virtual void					DoAutoAttach() = 0;

	/** Call to automatically detach observers. Shouldn't
		generally be called. Called on making view invisible.
	*/
	virtual void					DoAutoDetach() = 0;		

	// -----------------------------------------------------------
	//@{
//
//public : 
//	//										
//	//@}
};

#endif
