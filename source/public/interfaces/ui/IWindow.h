//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWindow.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __IWINDOW__
#define __IWINDOW__

#include "IPMUnknown.h"
#include "ShuksanID.h"

#include "PMReal.h"
#include "PMRect.h"
#include "WindowVisibleState.h"

class ICursorMgr;
class PMString;
class IEvent;
class IViewPort;
class InterfaceFontInfo;

// window property constants to get the data we want on the mac.
const uint32 kIWindowPtrProp     = 'IWin';	// data is the IWindow*

/** InDesign wrapper interface for platform windows.
*/
class INTERFACE_DECL IWindow :  public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_IWINDOW };

	/** possible window visibilities */
	enum VisibleState { kHide = SW_HIDE, kMaximize = SW_MAXIMIZE, kMinimize = SW_MINIMIZE,
						kRestore = SW_RESTORE, kShow = SW_SHOW, kShowNormal = SW_SHOWNORMAL,
						kShowNoActivate = SW_SHOWNA };
	
	/**	WindowSpec encapsulates 4 sets of window properties into one int32. Someday this combined bitfield will probably be replaced with several different enums or bitfields.
		The 4 things defined within this WindowSpec are:
		1. Window layer
		2. Window frame
		3. Window controls
		4. Window policies
	*/
	enum WindowSpec{ 
		/* The lowest 4 bits are for Window layer property. Each window must have exactly one window layer specified. This determines which windows float above
			which others. This property must be set. The following layer constants are sequenced in front to back order so that layers with a higher enum value overlap those with a lower enum value. 
			Note there are some holes for possible additional window layers in the future. The window layer for a window will determine the default window frame, controls, and other policies for the window
			kWindowLayerMask is the mask to use to get the window layer bits out of the window spec bitfield. 
		*/
		kWindowLayerMask = (0x0000000FUL),
		
		/** kAppRootWindowLayer MDI parent window - Windows only */
		kAppRootWindowLayer = 1,  
	  	/**  kDocumentWindowLayer - documents(and sheets), modeless dialogs */
	  	kDocumentWindowLayer = 2, 
	  	/** kToolbarWindowLayer - above documents, below palettes */
		kToolbarWindowLayer = 4, 
		/** kPaletteWindowLayer - palettes, floating modeless dialogs, perhaps popout subtools */
		kPaletteWindowLayer = 5, 
		/** alerts, modal dialogs */
		kAppModalWindowLayer = 7, 
		/** In the future, additional layers could be added here...*/
		/** kUtilityWindowLayer - system-wide floating TSM, AppleGuide */
		kUtilityWindowLayer = 11, 
		/** kMenuWindowLayer */
		kMenuWindowLayer = 13,
		/** kHelpWindowLayer - tips, coachmarks, perhaps popup sliders and popout subtools */
		kHelpWindowLayer = 14,	


		/** 4 bits for window frame. Defines the window border/titlebar. You can choose 0 or 1 of these. If you do not specify a window frame constant,
			you'll get the default one for your window layer. kWindowFrameMask is the mask to get the frame bits out of the whole bitfield. */
		kWindowFrameMask = (0x000000F0UL),
		/** Standard frame based on specified window layer. Internally mapped to one of the other window frame types, based on window layer. */
		kStandardWindowFrame = 0, 
		/** Window frame appropriate for a document window. Standard for kDocumentWindowLayer */
		kDocWindowFrame = (1UL << 4), 
		/** Window frame appropriate for a palette window. Standard for kPaletteWindowLayer */
		kPaletteWindowFrame = (2UL << 4), 
		/** Window frame appropriate for a modeless dialog window(like find/change dialog) */
		kModelessDialogWindowFrame = (3UL << 4),
		/** Window frame appropriate for a movable modal dialog window. Standard for kAppModalWindowLayer */
		kMovableModalDialogWindowFrame = (4UL << 4), 
		/** Window frame appropriate for a modal dialog window. */
		kModalDialogWindowFrame = (5UL << 4),
		/** Window frame appropriate for a movable alert window. */
		kMovableAlertWindowFrame = (6UL << 4),
		/** Window frame appropriate for an alert window. */
		kAlertWindowFrame = (7UL << 4),
		/** Window frame appropriate for an app frame window. */
		kAppRootWindowFrame = (8UL << 4),
		/** Window frame which is just a border. Win Only - specifies WS_BORDER and WS_EX_TOOLWINDOW    */
		kBorderOnlyWindowFrame = (9UL << 4),        
		/** Custom Window frame. Mac Only - window proc is specified by client code, rather than platform window */
		kCustomWindowFrame = (14UL << 4),  	         
		/** No Window frame. Standard for kHelpWindowLayer and kUtilityWindowLayer */
		kNoWindowFrame = (15UL << 4), 

		/** Window Controls. Most callers specify kStandardWindowControls. If you do not specify kStandardWindowControls, you must specify all controls that you want.
			8 bits for Type of window controls, such as titlebar, resize controls, zoom controls. Multiple values can be or'd together. kWindowControlsMask is the mask to get at just the window control bits */
		kWindowControlsMask = (0x0000FF00),
		/**  Standard controls based on specified frame and layer. Here's a list of what the standard controls are for various window frames:
				&bull; for windows with kNoWindowFrame, kStandardWindowControls ==> kNoWindowControls
				&bull; otherwise for kDocWindowFrame windows, kStandardWindowControls ==> kStandardDocWindowControls
				&bull; otherwise for kPaletteWindowFrame windows, kStandardWindowControls ==> kStandardPaletteWindowControls
				&bull; otherwise for kModelessDialogWindowFrame windows, kStandardWindowControls ==> kCloseWindowControl
				&bull; otherwise kStandardWindowControls ==> kNoWindowControls 
		*/
		kStandardWindowControls = 0, 
		/**  */
		kCloseWindowControl = (1UL << 8),
		/**  */
		kZoomWindowControl = (1UL << 9),
		/**  */
		kCollapseWindowControl = (1UL << 10),
		/**  */
		kResizeWindowControl = (1UL << 11),
		/**  */
		kToolbarWindowControl = (1UL << 12),
		/** Used to put the titlebar on the side of a paletteFrame window */
		kSideTitlebarControl = (1UL << 13), 	
		/**  Used to remove the titlebar of a paletteFrame window */
		kRemoveTitlebarControl = (1UL << 14), 
		/** e.g., to get all except the toolbar control:  kListAbsentWindowControls | kToolbarWindowControl */
		kListAbsentWindowControls = (1UL << 15), 
		/**  */
		kNoWindowControls = kWindowControlsMask,
		/**  */
		kAllWindowControls = kListAbsentWindowControls,
		/** Standard control attributes for doc window type. */		
		kStandardDocWindowControls = (kCloseWindowControl | kZoomWindowControl | kCollapseWindowControl | kResizeWindowControl),
		/** Standard control attributes for palette window type. */		
		kStandardPaletteWindowControls = (kCloseWindowControl | kZoomWindowControl),

		/** Window policy--presence of a bit overrides standard policy, so you only need spec the policies that are non-standard.
			Note that bits 16..31 come in mutually exclusive pairs--this is asserted in the code. (Hmm -- this wastes bits as there are some bit patterns that are illegal such as kHideInBackgroundWindowPolicy | kDontHideInBackgroundWindowPolicy)
			16 bits for window behavior. Use kWindowPolicyMask to get just these bits from the whole bitfield. */         
		kWindowPolicyMask = (0xFFFF0000UL),
		/** use all standard policies for the specified controls, frame, and layer */
		kStandardWindowPolicy = 0, 
		
		/** The window should hide when the app is not frontmost. Standard above kDocumentWindowLayer */
		kHideInBackgroundWindowPolicy = (1UL << 16), 
		/** The window should not hide when the app is not frontmost. Standard at and below kDocumentWindowLayer */
		kDontHideInBackgroundWindowPolicy = (1UL << 17), 
		
		/** The tab key should move focus from one widget to the next in this window. Standard above kDocumentWindowLayer */
		kTabCyclesKeyFocusWindowPolicy = (1UL << 18),
		/** The tab key should not move focus from one widget to the next in this window. Standard at and below kDocumentWindowLayer */
		kTabDoesntCycleKeyFocusWindowPolicy = (1UL << 19),
		
		/** Tells InDesign to remember the last widget in this window that has focus, so the user can restore focus to that editbox using a shortcut. Standard at kPaletteWindowLayer */
		kRememberLastEditboxKeyFocusWindowPolicy = (1UL << 20),
		/** Standard at other layers */
		kDontRememberLastEditboxKeyFocusWindowPolicy = (1UL << 21),
		
		/**  This attribute indicates there's a default button we should push when the window closes. It's assumed to be the cancel button. Standard for any of the dialog or alert window frames */
		kHasDefaultButtonWindowPolicy = (1UL << 22),
		/**  */
		kDoesntHaveDefaultButtonWindowPolicy = (1UL << 23),
		
		/** Window is movable. Standard except for windows with kNoWindowFrame or a kModalDialogWindowFrame */
		kMovableWindowPolicy = (1UL << 24), 
		/**  */
		kNonMovableWindowPolicy = (1UL << 25),
		
		/** When the user clicks on a treeview/listbox, this indicates it should take the keyboard focus. Standard for dialog window frames  */
		kListBoxGrabsKeyFocusWindowPolicy = (1UL << 26),  
		/**  */
		kListBoxDoesntGrabsKeyFocusWindowPolicy = (1UL << 27),
		
		/**  */
		kDoUnused1WindowPolicy = (1UL << 28),
		/**  */
		kDontUnused1WindowPolicy = (1UL << 29),
		
		/**  */
		kDoUnused2WindowPolicy = (1UL << 30),
		/**  */
		kDontUnused2WindowPolicy = (1UL << 31)
	};


public:
	/**	Initialize the window. Call this after constructing the window, but before opening it. This tells us what kind of window to create. @see IWindow::WindowSpec
		@param policyBits the WindowSpec policy bits defining the window layer, frame, controls, and policies.
	*/
	virtual	void		InitWindow( uint32 policyBits) = 0;

	/** This call actually creates the platform window, and gets it ready to use. Must be called after InitWindow. Also adds the window to the app window list.
	*/
	virtual void  			OpenWindow() = 0;

	/** This call destroys the platform window, and does some cleanup. Also removes the window from the app window list.
	*/
	virtual void  			CloseWindow() = 0;
	
	/** Notify the window that the platform window has been closed 
	*/
	virtual void			PlatformWindowClosed() = 0;

	/** Set the title of the window. Will be translated and displayed in the window titlebar if this window has one.
		@param newtitle the new title for the window
	*/
	virtual void				SetTitle(const PMString& newtitle) = 0; 

	/** Get the title of the window. 
		@return the last title set by calling SetTitle. Does not fetch the actual title from the window.
	*/
	virtual const PMString&		GetTitle() const = 0;
	
	/**	Return the font that should be used by all UI elements in this window. This is the mechanism which allows widgets in palettes to default to a smaller font than widgets in dialogs.
		@return default UI font to use for widgets in this window.
	*/
	virtual const InterfaceFontInfo& GetFont() const = 0;
	
	/**	Return the hilite font that should be used by all UI elements in this window. This is the mechanism which allows widgets in palettes to default to a smaller font than widgets in dialogs.
		@return default UI hilite font to use for widgets in this window.
	*/
	virtual const InterfaceFontInfo& GetHiliteFont() const = 0;

	/** 	Set the size of the window using its frame bounding box. The frame bounding box includes the title bar and any drop shadow. This includes the 'non-client' area.
		@param rt new window frame rect
	*/
	virtual void			SetFrameBBox(const GSysRect& rt) = 0;
	
	/** 	Get the size of the window's frame bounding box. The frame bounding box includes the title bar and any drop shadow. This includes the 'non-client' area.
		@return existing window frame rectangle
	*/
	virtual GSysRect		GetFrameBBox() const = 0;
			
	/** 	Get the size of the window's content bounding box. The content bounding box excludes the title bar and any drop shadow. This includes just the 'client' area.
		@return existing window content rectangle
	*/
	virtual GSysRect  GetContentBBox() const = 0;
	
	/** 	Set the size of the window using its content bounding box. The content bounding box excludes the title bar and any drop shadow. This includes just the 'client' area.
		@param rt new window content rect
	*/
	virtual void    	SetContentBBox(const GSysRect& bbox) = 0;
		
	/** 	Get the height of window's titlebar, in pixels.
	*/		
	virtual int32 GetTitlebarHeight() const = 0;
		
	/** 	Get the width of window's border(on one side) in pixels.
	*/
	virtual int32 GetBorderWidth() const = 0;
		
	/** 	Get the visible region bounding box for this window. If the window is not open, this returns an empty rect. Otherwise it returns the content bbox. This might be removed in a future version.
		@return bbox for visible window content bounds.
	*/
	virtual SysRect  GetVisRgnBBox() const = 0;

	/** 	Resize the content bbox to be this new size.
		@param newWidth the new width for the content bbox
		@param newHeight the new height for the content bbox
	*/
	virtual void    	Resize(SysCoord newWidth, SysCoord newHeight) = 0; 
			
	/**	Move window's frame bbox top left to (xPos, yPos), where the coordinates are global coordinates. If inFront is true, the window will be moved to the front of the 
		window list. Otherwise, the window retains its position in the window list.
		@param xPos new x position for the window's left side.
		@param yPos new y position for the window's top edge
		@param inFront whether or not to bring this window to the front of it's layer. @see BringToFront if that's all you want to do.
	*/
	virtual void    	SetPosition(GSysCoord xPos, GSysCoord yPos, bool16 inFront) = 0;
	
	/** Put the window in the middle of the screen the mouse is currently on.
	*/
	virtual void		CenterOnScreen() = 0;
		
	/**	Get the platform window we are wrapping.
		@return the platform window.
	*/
	virtual SysWindow GetSysWindow() const = 0;

#ifdef ID_DEPRECATED
	virtual void SetSysWindow(const SysWindow sysWindow) = 0;
#endif

	typedef enum { kZoomedOut, kZoomedIn, kResetZoomedOut} ZoomState;
	
	/**	Zoom the window in or out, or snapshot the current size as the new zoomed out size and set the window to zoomed out. If not, the window is zoomed to 
		whereever it was before it was last zoomed out. The new bounding box is returned in zoomRect, in global QuickDraw coordinates.
	*/
	virtual void Zoom(ZoomState zoomState, GSysRect *zoomRect) = 0;

	/** 	Return the current zoom state, either zoomIn or zoomOut.
	*/
	virtual ZoomState   GetZoomState() const = 0;
	/** Set the current zoom state without zooming the window.
	*/
	virtual void		SetZoomState(ZoomState zoomState) = 0;
	
	/**	Set the visibility. Call SetVisible(kHide) to make the windowinvisible, SetVisible(kShow) to make it visible again.
	*/
	virtual void  			SetVisible(VisibleState state, bool16 apply = kTrue) = 0;

	/**	Get the visibility. 
	*/
	virtual VisibleState	GetVisible() const = 0;

	/**	Check if the window is currently visible
	*/
	virtual bool16  			IsVisible() const = 0;

	/**	VisibleStateChanged is called when the visible state changes, to allow implementations of IWindow to do anything they need to.
	*/
	virtual void			VisibleStateChanged(VisibleState state) = 0;

	/** Bring this window to the front of it's window layer.
	*/
	virtual void    	BringToFront() = 0;

	/** Notify this window it's being activated.
	*/
	virtual void		Activate() = 0;

	/** Notify this window it's being deactivated. Window implementation might do things like dim selections, hide scroll bars, etc.		
	*/
	virtual void		Deactivate() = 0;
	
	/** Check if this window is active.
	*/
	virtual bool16		IsActive() const = 0;

	typedef enum{ kLimitMinimumWidth, kLimitMaximumWidth, kLimitMinimumHeight, kLimitMaximumHeight } LimitType;

	/** Get the current limits for this window for min/max width, height.
	*/
	virtual SysCoord GetLimits( const LimitType type ) const = 0;

	/** Set the current limits for this window for min/max width, height.
	*/
	virtual void SetLimits( const LimitType type,  const SysCoord newLimit) = 0;
	
	/** Draw the window contents. Paint is usually called by SystemPaint
	*/
	virtual void    	Paint(IViewPort* viewPort, SysRgn updateRgn) = 0;
	
	/** 	SystemPaint is called in response to an update event, and it sets the window up for Paint.
	*/
	virtual void    	SystemPaint() = 0;

	/**  Is the window rolled up and has this state changed since it was last checked
	*/
	virtual bool16 IsRolledUp(bool16& changed) const = 0;
	
	/** Returns true if this window is a floating window.
	*/
	virtual bool16 DoesFloat() const = 0;
		
	/**	Performs the hardware scroll
		Bitblt scrolling is a two step process. First, the bitblt is done using SystemScroll. SystemScroll returns the exposed region. The caller is
		responsible for disposing the region. The second step is to update the exposed region. This is done by calling ForceRedraw. This two step
		process makes it easier for cooperating panoramas to scroll sychronously, by making it possible for all panoramas to do the bitblt and then all
		panoramas update the exposed region. [amb]
	
		@param delta How much to scroll by.
		@param bDoInval A boolean indicating whether the OS should generate an inval message or not.
		@param bbox The part of the window to scroll. If this is nil, the content area is scrolled.
		@return a region for the newly exposed part of the window, i.e. the part that needs to be redrawn. Caller must dispose.
	*/
	virtual SysRgn SystemScroll(const SysPoint& delta, bool16 bDoInval = kTrue, SysRect *bbox = nil) = 0;
	
	/**	Redraws the invalid region directly. If 'forceRedraw' is true the redraw will happen immedeately otherwise it just invals the region. 
		@param invalidRgnToAdopt region of the window to draw. This region will NOT be disposed by ForceRedraw. If nil then entire window.
		@param forceRedraw kTrue if you'd like to draw now, kFalse to just inval.
	*/
	virtual void	ForceRedraw(SysRgn invalidRgnToAdopt, bool16 forceRedraw) = 0;

	/**	Returns kTrue if any portion of this window is visible on any monitor
	*/
	virtual bool16 IsOnScreen() const = 0;
	
	/**	Positions the window (if required) so that calling IsOnScreen returns kTrue
	*/
	virtual void   EnsureOnScreen() = 0;

	/** 	Get the WindowSpec bitfield for this window. Can be useful to test if certain bits are enabled.
		@return This window's WindowSpec bitfield.
	*/
	virtual uint32 GetWindowPolicy() const = 0;

	/**	Change the window attributes, Currently only can change kSideTitlebarControl for existing windows.
		@param policy New WindowSpec bitfiled for this window.
	*/
	virtual void SetWindowPolicy(uint32 policy) = 0;
	
	/* Set the drover theme on the top level window for Palette, Dialog or Document
	 *
	 */
	virtual void InitThemeForWindow() = 0;
};
				
DECLARE_BASE_TYPE(IWindow::WindowSpec);

#endif
