//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DVHostedWidgetView.h $
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
#ifndef __DVHostedWidgetView__
#define __DVHostedWidgetView__
	
#include "AbstractControlView.h"

#include "DVAForwardDeclarations.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	IControlView baseclass used for widgets in the Drover world.
*/

class DV_WIDGET_DECL DVHostedWidgetView : public AbstractControlView
{

	typedef AbstractControlView inherited;

public:

	DVHostedWidgetView(IPMUnknown *boss); 
	virtual ~DVHostedWidgetView();

	virtual void					DoPostCreate();
	virtual void					ReadWrite(IPMStream *s, ImplementationID prop);

	/** Moves and resizes the widget. Invals appropriately if requested (default). */
	virtual void					SetFrame(const PMRect& newFrame, bool16 invalidate = kTrue);

	/** Returns bounding content frame of the widget relative to the parent's coordinate system. */
	virtual const PMRect&			GetFrame() const;

	/** Returns bounding content frame of the widget in the widgets own inner (local) coordinate system with the top/left corner point at the origin (0,0) */
	virtual	const PMRect			GetLocalFrame() const;

	/** Returns bounding content frame of the widget in the widgets own inner (local) coordinate system with the top/left corner point at the origin (0,0) */
	virtual  PMRect					GetInnerContentFrame() const;

	/** Resizes the widget. Invals appropriately if requested (default). 
		It is preferable for side effects to occur in the BoundsChangedCallback rather than in a subclass reimplementation of Resize.
		Default implementation also handles frame bindings. */
	virtual void					Resize(const PMPoint& newDimensions, bool16 invalidate = kTrue);

	/** Moves the widget. Invals appropriately if requested (default).
		It is preferable for side effects to occur in the BoundsChangedCallback rather than in a subclass reimplementation of MoveTo
		Default implementation also handles frame bindings. */
	virtual void  					MoveTo(const PMPoint& where, bool16 invalidate = kTrue);

	/** Frame bindings, layout changes are cpplied in AdaptLayoutToFrameBindings, which is called during Resize/MoveTo. */
	virtual void					SetFrameBinding(const FrameBinding& binding);
	virtual FrameBinding			GetFrameBinding() const;

	/** Resizes based on the current binding setting. Subclasses rarely override this method */
	virtual void					AdaptToParentsSize(const PMPoint& dimensions);

	/** Resizes based on the current binding setting of child. Subclasses rarely override this method */
	virtual void					AdaptToChildsGeometry(const PMPoint& delta, const FrameBinding& childsBinding, bool16 invalidate = kFalse);

	/** Returns stored value, or calls CreateDrawRegion if it doesn't have one. Subclasses rarely override this method */	
	virtual SysRgn					GetDrawRegion();

	/** As a default, Child regions will be contained within their parent's draw region(returns kTrue), but this can be overridden by some views to indicate 
		that child regions are independant of their parent regions.
 	*/
	virtual bool16 					DrawRegionEncompassesChildRegions() const;

	/** Default implementation throws away cached Draw Region. Next call to GetDrawRegion will recalculate it. Subclasses rarely override this method */
	virtual void					DeleteDrawRegion();
	
	/** Default implementation returns kTrue if the passed in point is within the bbox of the control view. Subclasses who want different hittest behavior must override this method. */
	virtual int32 					HitTest(const SysPoint& where);

	/** Draw the control. Not used for drover-based widgets, see DV_Draw below. */
	virtual void 					Draw(IViewPort* viewPort, SysRgn updateRgn);
	
	/** Do any extra drawing for the control here. (or in the drover widget itself) */
	virtual void					DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const {};

	/** Force the control to redraw, or just the invalid region passed in.
	*/
	virtual void					ForceRedraw(SysRgn invalidRgn, bool16 forceRedraw);

	/** Inval the draw region of this control, or just the bbox passed in. */
	virtual void					Invalidate(PMRect *bbox = nil);

	/** Validate the draw region of this control, or just the bbox passed in. */
	virtual void					Validate(PMRect *bbox = nil);

	/** Sets stored value. */
	virtual void					Hilite(bool16 doHilite = kTrue);

	/** Sets stored value.  */
	virtual void					Unhilite();

	/** Returns stored value. */
	virtual bool16					IsHilited() const;

	/** Returns stored value. */
	virtual bool16					IsRolledOver() const;

	/** Sets visible flag. Causes inval. Does AutoAttach or AutoDetach of observer */
	virtual void					Show(bool16 doShow);
	
	/** Sets visible flag. Causes inval. Does AutoDetach of observer */
	virtual void					Hide();

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					GetVisibleState() const;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					IsVisible(bool16 requireVisibleWindow = kFalse) const;

	/** Sets enable flag. Optionally causes inval. */
	virtual void					Enable(bool16 doEnable, bool16 invalidate);

	/** Sets enable flag. Optionally causes inval. */
	virtual void 					Disable(bool16 invalidate);

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16					GetEnableState() const;

	/** Returns stored value. Subclasses rarely override this method */
	virtual bool16 					IsEnabled() const;
	
	/** Default implementation just invals(if requested to) */
	virtual void					ParentsEnableStateChanged(bool16 enable, bool16 invalidate);

	/** Sets the size of the drover widget accordingly */
	virtual void                    Init(const WidgetID& widgetId = kDefaultWidgetId, 
                                         const PMRect& bbox = kZeroRect, 
                                         RsrcID rsrcID = 0);

	virtual void					DoAutoDetach();
	
	// GlobalToLocal(window or view) transformations (replaces similar methods in IWindowPort)
	virtual PMRect		GlobalToView(const PMRect& convertRect) const;
	virtual PMPoint		GlobalToView(const PMPoint& convertPoint) const;
	virtual PMRect		GlobalToWindow(const PMRect& convertRect) const;
	virtual PMPoint		GlobalToWindow(const PMPoint& convertPoint) const;

	virtual PMRect		ViewToGlobal(const PMRect& convertRect) const;
	virtual PMPoint		ViewToGlobal(const PMPoint& convertPoint) const;
	virtual PMRect		WindowToGlobal(const PMRect& convertRect) const;
	virtual PMPoint		WindowToGlobal(const PMPoint& convertPoint) const;

	virtual void	SetClipToSelfEnabled(bool16 clipChildren) const;	

protected:
	/** Changes value of state flag, no side effects */
	virtual void					SetVisibleState(bool16 isVisible = kTrue);
	virtual void					SetEnableState(bool16 isVisible = kTrue);
	
	/** Checks if all parents of this widget are visible. Optionally check the window as well */
	virtual bool16					AncestorsAreVisible(bool16 requireVisibleWindow) const;

	/** Calculates new transform from current bbox and panorama. Subclasses usually don't need to override this method */
	virtual PMMatrix*				GetUpdatedContentToWindowTransform();

	/** 	Return a region that defines the drawing area of the control.  Default implementation creates a region from the control bbox.
		Overriding this allows you to create a different draw region. Some controls do this to draw a drop shadow outside the bounds 
		of the control. Your draw region should not extend beyond your parent's draw region, so your draw region should usually be
		an intersection of your adjusted bbox and your parent's draw region.
	*/
	virtual void					CreateDrawRegion(SysRgn& drawRgn);

	/**	Check if AutoAttach was called more recently than AutoDetach */
	virtual bool16					IsAutoAttached() const;
	virtual void					SetIsAutoAttached(bool16 flag = kTrue);
	
	void							Set_UI_Node(dvaui::ui::UI_Node* node);
	dvaui::ui::UI_Node*				Get_UI_Node() const;

	/** Called to release an existing UI_Node.
		When switching from one node to another, Call Release_UI_Node followed by Set_UI_Node(new_node) 
	*/
	void							Release_UI_Node();

	virtual void					BoundsChangedCallback();
	virtual void					ParentEnableStateChangedCallback();

	/** give subclass a chance to control resize behavior of its children */
	virtual void					ResizeChildren(const PMPoint& delta, bool16 invalidate);
	virtual void					AdaptLayoutToFrameBindings(const PMPoint& delta, bool16 invalidate = kTrue);
	
	/** INTERNAL USE ONLY: give subclasses a chance to do something after our low-level 
		KeyfocusChangeCallback is called.
		In CC so far there is only one client, so it may go away. */
	
	virtual void 					DoAfterKeyfocusChangedCallback() {}
	unsigned int					fGeometryBusy : 1;
	class AcquireGeometry;

private:
	/*	If this view can display multiple tips while moving on the same widget, depending on the context.
		Then following function should be called after setting the UI_Node in the view.
		Normally, drover asks for new tool tip when the ui_node/widget under the mouse point changes.
		In Indesign we have some widgets which are bigger controls that contain multiple sub-items which 
		are individual drawable entities but under the same widget.
		So, to enable that drover asks tool tip text for these kind of controls on a bit frequent basis,
		clients need to call this function to enable it.
		For example, layout view is a single view for drover and it asks for new tool tip text only on ui node changes
					 changes. So we call this function from DVLayoutControlView constructor.
					 This function is also used for grid of glyphs in bullets and numbering and glyphs panel
	*/
	void							UpdateToolTipOnMouseMove(); 

	void							CommonInit();

	/** If there is a cursor provider and a cursor region on the view's boss, hook them up. */ 
	void                            ConnectCursorProviderToRegion(); 

	// Non-persistent data
	bool16							fAutoAttached;
	bool16							fHilited;
	mutable SysRgn					fDrawRegion;

	// Private implementation class
	class PrivateImpl;
	PrivateImpl*			Impl() const {return fImpl;}
	PrivateImpl*			fImpl;

public:

	/** FOR INTERNAL USE ONLY. Get/Set the flag to check if this Widget's creation process is finished,
	i.e. DoPostCreate() (or any other such function to create the widget) has been called.
    */
	bool16	IsWidgetConstructionFinished() const;
	void	WidgetConstructionFinished(const bool16 bFlag);

	/** FOR INTERNAL USE ONLY. Set/Reset the flag to indicate that widget is disabled
	 by non-suppressed UI. This flag is needed to identify and separate out the 
	 Enable() and Disable() calls caused by SuppressedUI.
    */
	void MarkDisabledByNonSuppressedUIIfRequired(const bool16 bFlag);

	/** FOR INTERNAL USE ONLY. Set/Reset the flag to indicate that widget is hidden
	by non-suppressed UI. This flag is needed to identify and separate out the 
	Show() and Hide() calls caused by SuppressedUI.
    */
	void MarkHiddenByNonSuppressedUIIfRequired(const bool16 bFlag);

	/** FOR INTERNAL USE ONLY. Get/Set the flag to disable the widget due to 
	 Suppressed UI
    */
	bool16 IsDisabledBySuppressedUI() const;
	void DisableBySuppressedUI(const bool16 bFlag);

	/** FOR INTERNAL USE ONLY. Get/Set the flag to hide the widget due to 
	 Suppressed UI
    */
	bool16 IsHiddenBySuppressedUI() const;
	void HideBySuppressedUI(const bool16 bFlag);	

private:

	/** Get/Set the flag to call Enable() or Disable() function call from SuppressUI
    */
	bool16 IsEnableOrDisableFuncCalledFromSuppressedUI() const;
	void EnableOrDisableFuncCalledFromSuppressedUI(const bool16 bFlag);

	/** Get/Set the flag to disable the widget due to Non suppressed UI. 	
    */
	bool16 IsDisabledByNonSuppressedUI() const;
	void DisableByNonSuppressedUI(const bool16 bFlag);

	/** Check if this widget is marked disabled either by suppressed UI or by non-suppressed UI.
    */
	bool16 IsMarkedDisabled();

	/** Get/Set the flag to call Show() or Hide() function call from SuppressUI
    */
	bool16 IsShowOrHideFuncCalledFromSuppressedUI() const;
	void ShowOrHideFuncCalledFromSuppressedUI(const bool16 bFlag);

	/** Get/Set the flag to hide the widget due to non suppressed UI.
	*/
	bool16 IsHiddenByNonSuppressedUI() const;
	void HideByNonSuppressedUI(const bool16 bFlag);

	/** Get the flag to check if widget is marked hidden either by suppressed UI 
	 or by non-suppressed UI.
    */
	bool16 IsMarkedHidden();
};

//========================================================================================
// DVHostedWidgetView::AcquireGeometry
//========================================================================================
/**	Since we push geometry changes both up and down the hierarchy we need someway to avoid circular geometry changes.
 This class is used on the stack to acquire the right to change the geometry. [amb]
 */
class DVHostedWidgetView::AcquireGeometry
{
public:
	AcquireGeometry(DVHostedWidgetView* view);
	~AcquireGeometry();
private:
	DVHostedWidgetView* fView;
};

inline DVHostedWidgetView::AcquireGeometry::AcquireGeometry(DVHostedWidgetView* view) 
	:
	fView(view)
{ 
	ASSERT_MSG(fView->fGeometryBusy == 0,"AcquireGeometry - fGeometryBusy is already set, and it's a 1 bit bitfield. Not good.");
	fView->fGeometryBusy++;
}

inline DVHostedWidgetView::AcquireGeometry::~AcquireGeometry()
{
	ASSERT_MSG(fView->fGeometryBusy == 1,"~AcquireGeometry - fGeometryBusy is already unset, and it's a 1 bit bitfield. Not good.");
	fView->fGeometryBusy--;
}

#pragma export off

#endif

