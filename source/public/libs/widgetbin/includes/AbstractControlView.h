//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/AbstractControlView.h $
//  
//  Owner: Dave Burnard
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __AbstractControlView__
#define __AbstractControlView__
	
#include "IControlView.h"


#ifdef WIDGET_BUILD
#pragma export on
#endif

/**	This class is a new base class used to implement IControlView for essentially all widgets. It's purpose is to isolate Drover-based widgets from
	some of the assumptions found in CControlView related to wrapping platform widgets. Implementations in AbstractControlView must be independent
	of how the ControlView is actually implemented - so it deals mostly with identification, notification, common data, etc.
	
	@see IControlView, CControlView, DVControlView
*/
class DV_WIDGET_DECL AbstractControlView : public IControlView
{
public:
	// ----- Initialization -----

	AbstractControlView(IPMUnknown *boss); 
	virtual ~AbstractControlView();
		
	virtual void					ReadWrite(IPMStream *s, ImplementationID prop);
	
	/**	Default implementation just stores off WidgetID, bbox, and RsrcID
	*/
	virtual void					Init(const WidgetID& widgetId = kDefaultWidgetId,
										 const PMRect& bbox = kZeroRect,
										 RsrcID rsrcID = 0);

	/** Default implementation resets transform and panorama. Subclasses sometimes override this to do some delayed initialization.
	*/
	virtual void					DoPostCreate();

	/** Returns stored value. Subclasses rarely override this method */
	virtual RsrcID					GetRsrcID() const;

	/** Sets stored value. Subclasses rarely override this method */
	virtual	void					SetRsrcID(const RsrcID &id);

	/** Returns stored value. Subclasses rarely override this method */
	virtual PluginID				GetRsrcPluginID() const;

	/** Sets stored value. Subclasses rarely override this method */
	virtual	void					SetRsrcPluginID(const PluginID &id);

	/** Returns stored value. Subclasses rarely override this method */
	virtual WidgetID				GetWidgetID() const;

	/** Sets stored value. Subclasses rarely override this method */
	virtual	void					SetWidgetID(const WidgetID &id);

	/** Moves and resizes the widget. Invals appropriately. */
	virtual void					SetFrame(const PMRect& newFrame, bool16 invalidate = kTrue) = 0;

	/** Returns Frame of widget. */
	virtual const PMRect&			GetFrame() const = 0;

	/** Resizes the widget. Invals appropriately. */
	virtual void					Resize(const PMPoint& newDimensions, bool16 invalidate = kTrue) = 0;

	/** Moves the widget. Invals appropriately. */
	virtual void  					MoveTo(const PMPoint& where, bool16 invalidate = kTrue) = 0;

	/** Sets stored value. Subclasses rarely override this method */
	virtual void					SetFrameBinding(const FrameBinding& binding);

	/** Returns stored value. Subclasses rarely override this method */
	virtual FrameBinding			GetFrameBinding() const;

	/** Resizes based on the current binding setting. Subclasses rarely override this method */
	virtual void					AdaptToParentsSize(const PMPoint& dimensions) = 0;

	/** Resizes based on the current binding setting of child. Subclasses rarely override this method */
	virtual void					AdaptToChildsGeometry(const PMPoint& delta, const FrameBinding& childsBinding, bool16 invalidate = kFalse) = 0;
	
	/** Default implementation just returns the dimensions passed in. If your widget has some limits on how it resizes(e.g. only want to 
		grow shrink in increments of a row height or something) you need to override this method.
	*/
	virtual PMPoint					ConstrainDimensions(const PMPoint& dimensions) const;
	
	/** Returns stored value, or calls CreateDrawRegion if it doesn't have one. Subclasses rarely override this method */	
	virtual SysRgn					GetDrawRegion() = 0;

	/** As a default, Child regions will be contained within their parent's draw region(returns kTrue), but this can be overridden by some views to indicate 
		that child regions are independant of their parent regions.
 	*/
	virtual bool16 					DrawRegionEncompassesChildRegions() const = 0;

	/** Returns value based on Frame and transform. */
	virtual SysRect					GetBBox() const;
	
	/** Default implementation returns cached transform, or uses bbox and panorama to calculate the current transform. Subclasses rarely override this method */
	virtual PMMatrix*				GetContentToWindowTransform() const;
	virtual void					ContentToWindowTransform( PMPoint * point) const;
	virtual void					ContentToWindowTransform( PMRect * rect) const;
	virtual void					ContentToWindowTransform( PMPolygon4 * poly) const;

	virtual void					WindowToContentTransform( PMPoint * point) const;
	virtual void					WindowToContentTransform( PMRect * rect) const;
	virtual void					WindowToContentTransform( PMPolygon4 * poly) const;

	virtual PMMatrix				GetContentToWindowMatrix() const;
	virtual PMMatrix				GetWindowToContentMatrix() const;
	virtual PMRect					GetContentBounds_() const;

	/** Default implementation throws away cached Transform. Next call to GetContentToWindowTransform will recalculate it. Subclasses rarely override this method */
	virtual void					InvalidateTransform();
	
	/** Default implementation throws away cached Draw Region. Next call to GetDrawRegion will recalculate it. Subclasses rarely override this method */
	virtual void					DeleteDrawRegion() = 0;
	
	/** Default implementation returns kTrue if the passed in point is within the bbox of the control view. Subclasses who want different hittest behavior must override this method. */
	virtual int32 					HitTest(const SysPoint& where) = 0;
	

	/** Draw the control. All subclasses must override. */
	virtual void 					Draw(IViewPort* viewPort, SysRgn updateRgn) = 0;
	
	/** Force the control to redraw, or just the invalid region passed in. */
	virtual void					ForceRedraw(SysRgn invalidRgn, bool16 forceRedraw) = 0;

	/** Inval the draw region of this control, or just the bbox passed in. */
	virtual void					Invalidate(PMRect *bbox = nil) = 0;

	/** Validate the draw region of this control, or just the bbox passed in. */
	virtual void					Validate(PMRect *bbox = nil) = 0;

	/** Sets stored value. */
	virtual void					Hilite(bool16 doHilite = kTrue) = 0;

	/** Sets stored value.  */
	virtual void					Unhilite() = 0;

	/** Returns stored value. */
	virtual bool16					IsHilited() const = 0;

	/** Returns stored value. */
	virtual bool16					IsRolledOver() const = 0;

	/** Sets visible flag. Causes inval. Does AutoAttach or AutoDetach of observer */
	virtual void					Show(bool16 doShow) = 0;
	
	/** Sets visible flag. Causes inval. Does AutoDetach of observer */
	virtual void					Hide() = 0;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					GetVisibleState() const = 0;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					IsVisible(bool16 requireVisibleWindow = kFalse) const = 0;
	
	/** Does AutoAttach or AutoDetach of observer */
	virtual void					ParentsVisibleStateChanged(bool16 visible);

	/** Sets enable flag. Optionally causes inval. */
	virtual void					Enable(bool16 doEnable, bool16 invalidate) = 0;

	/** Sets enable flag. Optionally causes inval. */
	virtual void 					Disable(bool16 invalidate) = 0;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					GetEnableState() const = 0;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16 					IsEnabled() const = 0;
	
	/** Default implementation just invals(if requested to) */
	virtual void					ParentsEnableStateChanged(bool16 enable, bool16 invalidate) = 0;

	/** Default implementation does nothing */
	virtual void					WindowActivated();

	/** Default implementation does nothing */
	virtual void					WindowDeactivated();

	/** Default implementation AutoAttaches observer */
	virtual void					WindowShown();

	/** Default implementation AutoDetaches observer */
	virtual void					WindowHidden();

	/** Default implementation Auto attaches/detaches observer, invalidates transform, destroys system control */
	virtual void					WindowChanged();

	/** Default implementation invalidates transform, destroys system control, deletes draw region */
	virtual void					WindowClosed();
	
	/** Default implementation invalidates transform, destroys system control, deletes draw region */
	virtual void					ParentPurged();

	/** Calls the AutoAttach method of the observer on the same boss with IID_IOBSERVER, plus attaches additional observers using the IControlViewObservers interface */
	virtual void					DoAutoAttach();

	/** Calls the AutoDetach method of the observer on the same boss with IID_IOBSERVER, plus detaches additional observers using the IControlViewObservers interface */
	virtual void					DoAutoDetach();

protected:

	/** Changes value of state flag, no side effects */
	virtual void					SetVisibleState(bool16 isVisible = kTrue) = 0;
	virtual void					SetEnableState(bool16 isVisible = kTrue) = 0;

	/** Checks if all parents of this widget are visible. Optionally check the window as well */
	virtual bool16					AncestorsAreVisible(bool16 requireVisibleWindow) const = 0;

	/** Checks if all parents of this widget are enabled. */
	virtual bool16					AncestorsAreEnabled() const;
	
	/** Convenience method to make it easier to get your window or your parent view. Continues querying up the widget hierarchy until a boss with the requested interface is found. */
	IPMUnknown*						QueryParentFor(const PMIID& interfaceID) const;
	
	/**  Notify parent of an attrubute change, such as kWidgetSize */
	void							NotifyParent(const WidgetAttributeID& id);
	
		
	/** Calculates new transform from current bbox and panorama. Subclasses usually don't need to override this method */
	virtual PMMatrix*				GetUpdatedContentToWindowTransform() = 0;

	/** 	Return a region that defines the drawing area of the control.  Default implementation creates a region from the control bbox.
		Overriding this allows you to create a different draw region. Some controls do this to draw a drop shadow outside the bounds 
		of the control. Your draw region should not extend beyond your parent's draw region, so your draw region should usually be
		an intersection of your adjusted bbox and your parent's draw region.
	*/
	virtual void					CreateDrawRegion(SysRgn& drawRgn) = 0;
	

	/** 	Allocates a new transform. Subclasses rarely need to override this method */
	virtual PMMatrix*				CreateTransform();
	
	/** 	Frees the content Transform. */ 
	void							DestroyContentTransform();

	/**	Destroy any platform controls wrapped by this control. Does nothing by default - see CControlView */
	virtual void					DestroyWrappedSystemControls();

	/**	Check if AutoAttach was called more recently than AutoDetach */
	virtual bool16					IsAutoAttached() const = 0;
	virtual void					SetIsAutoAttached(bool16 flag = kTrue) = 0;
	
	/** 	As control views are enabled, activated and shown we only want to call Attach once. These
		methods make sure that AutoAttach is only called once.
	*/
	virtual void					HandleAutoAttach();

	/** 	As control views are disabled, deactivated and hidden we only want to call Detach once. These
		methods make sure that AutoDetach is only called once.
	*/
	virtual void					HandleAutoDetach();


protected:


	WidgetID					fWidgetId;
	PMRsrcID					fRsrcId;
	FrameBinding				fFrameBinding;
	PMRect						fFrame;
	
	PMMatrix*					fContentTransform;

DECLARE_HELPER_METHODS()
};


#pragma export off

#endif

