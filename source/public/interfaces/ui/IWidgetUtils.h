//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWidgetUtils.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IWidgetUtils__
#define __IWidgetUtils__

#include "widgetid.h"
#include "IPMUnknown.h"
#include "PMPoint.h"
#include "PMRect.h"
#include "InterfaceFontInfo.h"
#include "IEvent.h"
#include "Utils.h"
#include "IInterfaceColors.h"
#include "IDResourceShell.h"

class IControlView;
class IDialog;
class IDVPlatformOffscreen;
class IEventHandler;
class IGraphicsContext;
class IGraphicsPort;
class IPanelControlData;
class IPMfont;
class IUIColorSpec;
class IEventHandler;
class IKeyFocusHandler;
class IWindow;

#include "DVAForwardDeclarations.h"

class RoundedRectAppearance
{
public: 
	RoundedRectAppearance (const IControlView* controlView, PMReal radius, PMReal lineWidth, RealAGMColor strokeColor, 
							RealAGMColor fillColor, bool16 isRolledOverButton, RealAGMColor upperStrokeColor, 
							RealAGMColor lowerStrokeColor, PMReal inset = 1.0, bool16 isMoveReqd = kTrue) :
								fControlView(controlView),
								fRadius(radius),
								fLineWidth(lineWidth),
								fStrokeColor(strokeColor),
								fFillColor(fillColor),
								fIsRolledOverButton(isRolledOverButton),
								fUpperStrokeColor(upperStrokeColor),
								fLowerStrokeColor(lowerStrokeColor),
								fInset(inset),
								fIsMoveReqd(isMoveReqd)
	{
		ASSERT(controlView);
	}

	RoundedRectAppearance (const IControlView* controlView, PMReal radius, PMReal lineWidth, int32 strokeColorIndex, 
							int32 fillColorIndex, bool16 isRolledOverButton, int32 upperStrokeColorIndex, 
							int32 lowerStrokeColorIndex, PMReal inset = 1.0, bool16 isMoveReqd = kTrue) :
								fControlView(controlView),
								fRadius(radius),
								fLineWidth(lineWidth),
								fIsRolledOverButton(isRolledOverButton),
								fInset(inset),
								fIsMoveReqd(isMoveReqd)
	{
		ASSERT(controlView);

		RealAGMColor color;

		InterfacePtr<IInterfaceColors> colors(GetExecutionContextSession(), UseDefaultIID());

		colors->GetRealAGMColor(strokeColorIndex, fStrokeColor);
		colors->GetRealAGMColor(fillColorIndex, fFillColor);
		colors->GetRealAGMColor(lowerStrokeColorIndex, fLowerStrokeColor);
		colors->GetRealAGMColor(upperStrokeColorIndex, fUpperStrokeColor);
	}

	const IControlView*	fControlView;
	PMReal			fInset;
	PMReal			fRadius;
	PMReal			fLineWidth;
	RealAGMColor	fStrokeColor;
	RealAGMColor	fFillColor;
	bool16			fIsRolledOverButton;
	RealAGMColor	fUpperStrokeColor;
	RealAGMColor	fLowerStrokeColor;
	bool16			fIsMoveReqd;
};

/** Interface for some widget-related utility functions. 
     Use like so: Utils<IWidgetUtils>()->QueryRelatedWidget( view, kMyWidgetID,IID_ICONTROLVIEW )
*/

typedef enum {
    kCanDraw,
    kCanDrawLocaleText,
    kCannotDraw,
    kDrawWithStandardFont
} DrawStatus;

class IWidgetUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWIDGETUTILS };
	/** Convert a point in parent window coordinates to the window coordinates
	    of the destination view.
		@param mouseLocationInParentWindowCoords the mouse location in parent window coordinates
		@param destinationView view whose window coordinate system you want to use. 
	*/
	virtual SysPoint ConvertPointToLocalWindow(const PMPoint& mouseLocationInParentWindowCoords, IControlView* destinationView) = 0;

	/**  Given a widget, this method will find a related widget. i.e. child, parent, cousin, etc
		@param widget the widget to start with
		@param widgetId the WidgetID of the related widget that you want
		@param iid the IID of the related widget that you want returned - i.e. if you specify IID_ICONTROLVIEW you'll get back and IControlView*
		@return pointer to the requested interface on the requested widget, or nil.
	*/
	virtual IPMUnknown* QueryRelatedWidget(const IPMUnknown* widget, const WidgetID& widgetId, const PMIID& iid) = 0;

	/**  Given a widget, this method will find the correct fontInfo to use for it. It will query for IUIFontSpec, or go up to the window boss to get the
	      default font for the window.
		@param widget the widget you want the appropriate font for
		@return InterfaceFontInfo for the UI font to use.
	*/
	virtual const InterfaceFontInfo GetAppropriateFontForWidget(const IControlView* widget) = 0;

	/**  Given a widget, this method will find the correct IUIColorSpec to use for it. It will query up the hierarchy for a IUIColorSpec. It may return nil, if the widget and it's ancestors do not have a IUIColorSpec interface.
		@param widget the widget you want the appropriate colors for
		@return IUIColorSpec for the UI colors to use.
	*/
	virtual const IUIColorSpec* QueryColorSpecForWidget(const IPMUnknown* widget) = 0;
	
	/**  Use AGM transparency to "gray-out" an area of the UI
		@param gc the graphics port
		@param frame the frame you want to gray out
		@param transparency the transparency amount
	*/
	virtual void GrayOutFrameContents (IGraphicsPort *gc, PMRect frame, PMReal transparency) = 0;

	/** Fills the draw region of control view (or rect) with the correct palette background (Grey) using the offscreen Drawbot object. 
	 * Here the Drawbot object being passed as argument has been setup for offscreen, so the rectToFill
	 * area (in drawbot) has to be translated in client coordinates.
	 @param widget		: ControlView for drawing, the widget whose bounds you want to fill(if rectToFill is nil)
	 @param pDrawbot	: Offscreen Drawbot object, background rect will be drawn on its surface
	 @param rectToFill	: the rect you want to fill, if not the bounds of the widget
	 */
	virtual void DrawPaletteFill(const IControlView* widget, dvaui::drawbot::Drawbot * pDrawbot, const PMRect *rectToFill = nil) = 0;

	/**  Draws the background of control view using the Graphics Port passed as argument
	 @param widget		: ControlView for drawing, widget whose bounds you want to fill(if rectToFill is nil)
	 @param port		: GraphicsPort which will be used for Making AGM drawing calls, graphics port to draw into
	 @param rectToFill	: the rect you want to fill, if not the bounds of the widget
	 */
	virtual void DrawPaletteFill (const IControlView* widget,IGraphicsPort * port, const PMRect* rectToFill = nil) = 0;

	// moved from GridPanelUtils.h
	virtual void GridPanel_PositionWidgets(IPanelControlData* panel, int32 first, int32 last) = 0;
 
	virtual	void DeleteWidgetAndChildren(IControlView* widgetToDelete) = 0;

	/**   if the PMString appears to start with a number and have a user decimal(as defined by the OS setting) in it
	       it(commonly , or . or space) this will take out that character and replace it with plain old '.'
		@param string the string you want to have the user decimal replaced with '.'
	*/
	virtual void StripUserDecimal(PMString* string) = 0;
	
	/**   	if the PMString appears to start with a number, this will remove the '.' character and replace it with the OS setting for decimal
		which is commonly . or , or space.
		@param string the string you want to have the '.' character replaced with the user decimal
	*/
	virtual void FormatUserDecimal(PMString* string) = 0;

	/**   	Strips the Ampersands and any other extra characters corresponding to Accelerators, which do not need to be shown.
		@param rawString the string in which you want to have the characters corresponding to the accelerators be stripped.
	*/
	virtual void StripAccelerators(PMString &rawString) = 0;

	/**   	convert the value to PMString based on the current measurement system.
		@param value the number to be converted.
		@param bHorizontal the flag indicates if we need to use horizontal or vertical measurement system.
		@param string the output
	*/
	virtual void GetFormattedString(const PMReal& value, const bool16& bHorizontal, PMString& outString) = 0;

	/** Convert the value to a PMString representing the scale.
		e.g. Convert the number 0.85 to "85.0%" or "(85%)"
		@param value the number to be converted.
		@param outString the output
		@param bFormatWithParens, format the output with parens if kTrue, without if kFalse
	*/
	virtual void GetFormattedScalingString(const PMReal& value, PMString& outString, const bool16 bFormatWithParens) = 0;
	
#ifdef MACINTOSH
	virtual	void BringFinderToFront(void) = 0;
	virtual	void SynchDocumentProxyIcons(bool16 forceValidation = kFalse) = 0;
#endif

	virtual PMReal GetViewYPosition(IGraphicsContext* gc, const InterfaceFontInfo &fontInfo, const PMReal &height) = 0;

	/**   	Helper function to simulate a mouse click event.
			Uses the event handler's control view if present to fake location of mouse event.
		@param targetEH event handler to use for posting the event
	*/
	virtual void SimulateClick(IEventHandler* targetEH) = 0;

	/**	Accumulate a widget rect into a region. Useful for creating drag and drop regions of a group of widgets.
		@param widget the widget for which union its bbox into a region
		@param theRgn IN/OUT pass in a region which will be enlarged by the given widget
		@see IDragDropSource.h, DoMakeDragOutlineRegion
	 */
	virtual void CombineRegions(IControlView* widget, SysWireframe& theRgn) const = 0;

	/** Utility to draw selection/focus rect using direct drawing.
		@param view the control view to draw the focus rect for
		@param r rect defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
	 */
	virtual void DrawFocusRect(IControlView* view, const PMRect& r, bool16 flushDrawing) = 0;

	/** Utility to draw hilite/outline rect using direct drawing inset within the view bounds (used for DragDrop Target hiliting and more).
		@param view the control view to draw the hilite rect for
		@param r rect defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@param hiliteThickness thickness of the outline in user space (points)
		@return kTrue for success.
	 */
	#define kDefaultHiliteThickness 2.0
	virtual bool16 DrawHiliteRect(IControlView* view, const PMRect& r, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness) = 0;
	
	/** Utility to draw hilite/outline path using direct drawing inset within the view bounds (used for DragDrop Target hiliting and more).
		@param view the control view to draw the hilite path for
		@param pts path (having a single subpath) defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@param hiliteThickness thickness of the outline in user space (points). On the mac non-integer values can produce different results (0.5 produces a smaller line than 1.0)
		@return kTrue for success.
	 */
	virtual bool16 DrawHilitePath(IControlView* view, const PMPointList& pts, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness) = 0;

	/** Utility to draw hilite/outline path using direct drawing inset within the view bounds (used for DragDrop Target hiliting and more).
		@param view the control view to draw the hilite path for
		@param subPaths subpaths for the path defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@param hiliteThickness thickness of the outline in user space (points). On the mac non-integer values can produce different results (0.5 produces a smaller line than 1.0)
		@return kTrue for success.
	 */
	virtual bool16 DrawHilitePath(IControlView* view, const PMPointListCollection& subPaths, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness) = 0;
	
	/** Utility to draw selection/focus using direct drawing.
		@param view the control view to draw the focus for
		@param hilitePath defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@return kTrue for success.
	 */
	virtual bool16 DrawHilitePath(IControlView* view, SysWireframe hilitePath, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness) = 0;
	
	/** Utility to fill rect using direct drawing inset within the view bounds (used for block text carets).
		@param view the control view to draw the hilite rect for
		@param r rect defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@return kTrue for success.
	 */
	virtual bool16 FillHiliteRect(IControlView* view, const PMRect& r, bool16 flushDrawing = kTrue) = 0;
	
	/** Utility to draw fill path using direct drawing inset within the view bounds (used for text caret drawing).
		@param view the control view to draw the hilite path for
		@param subPaths subpaths for the path defined in view's content coordinate space
		@param flushDrawing whether to force flush the drawing
		@return kTrue for success.
	 */
	virtual bool16 FillHilitePath(IControlView* view, const PMPointListCollection& subPaths, bool16 flushDrawing = kTrue) = 0;


	/** Set the graphics port to the current system highlight color
		@param gPort the port to set the highlight color on.
		@param view the view selection will draw in.
	 */
	virtual void SetTextHighlightColor(IGraphicsPort *gPort, const IControlView *view) = 0;
	
	/**
		@param view of the control/widget
		@return true if the widget is in a palette
	*/
	virtual bool16 IsWidgetInPalette(const IControlView*  iWidget) = 0;

	/** Utility to copy bits from an offscreen to view using direct drawing.
		@param view the control view to copy the bits to
		@param dstBounds the area of the view to copy into
		@param srcOffscreen the source offscreen
		@param srcBounds the area of the offscreen to copy
		@param clip2destMatrix clip to destination space matrix
		@param clipRgn clipping to apply
	 */
	virtual bool16 CopyBitsToView(IControlView* view, const Int32Rect& dstBounds, IDVPlatformOffscreen* srcOffscreen, const Int32Rect& srcBounds,
								  const PMMatrix& clip2destMatrix = PMMatrix(), const SysRgn clipRgn = nil) = 0;

	/** Get the UI scale factor appropriate for drawing a view (designed to be called at Draw time)
		@param view the view.
		@return scale factor HiDPI
	 */
	virtual PMReal GetViewScaleFactorReal(const IControlView* view) = 0; 

    /**
     * Draw rectangles filled with given color and having rounded corners
	   @param drawbotP bot where to draw the rectangle
	   @param roundedRectAppearance instance of class RoundedRectAppearance stating appearance of the required rectangle
     */
    virtual void DrawRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance) = 0;

	/**
     * Draw rectangles filled with given color and having left rounded corners
	   @param drawbotP bot where to draw the rectangle
	   @param roundedRectAppearance instance of class RoundedRectAppearance stating appearance of the required rectangle
     */
    virtual void DrawLeftRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance) = 0;

	/**
     * Draw rectangles filled with given color and having right rounded corners
	   @param drawbotP bot where to draw the rectangle
	   @param roundedRectAppearance instance of class RoundedRectAppearance stating appearance of the required rectangle
     */
    virtual void DrawRightRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance) = 0;

	/**
     * Checks if the passed widget is controllable by cluster widget
	   @param widget input child widget view
	   @return isSelected returns whether the child view is selected or not
	   @param checkParentToBeCluster - pass kTrue to force this routine to check this child belongs to cluster.
	   @return kTrue if the the child is controllable by cluster widget.
     */
	virtual bool16 IsClusterControllableChildWidget(IControlView* widget, bool16& isSelected, bool16 checkParentToBeCluster = kFalse) = 0;

	/**
	  query the descendant widgets for interface id
	  @param widget input widget view
	  @param interfaceID the IID of the descendant widget that you want returned
	  @return pointer to the requested interface in the descendant widget, or nil.
	*/
	virtual IPMUnknown*	QueryDescendentWidgetOfType(IPMUnknown* widget, PMIID interfaceID) = 0;

	/**
	  opens up the context UI
	  @param rSpec						The resource spec for the dialog.
	  @param anchorRect					The rect around which the panel is to be opened in global coordinate space.
	  @param popupWindowClass			The pop up window class to use.
	  @param preferredtoBeDrawnOnLeft	Flag to state the preference to be drawn on left.
	  @param invokedFromPalette			Flag to specify whether the context UI is being invoked from the panel.
	  @param okToCacheDialog			Flag to specify whether or not to cache the context dialog ui.
      @param ensurePositionWrtDocLayout	Flag to specify whether popup window should be within document layout bounds or within screen bounds.
	  @param openImmediately			Flag to specify whether popup window should be immediately opened. Defaults to True. if False, user must call IDialog::Open on the returned pointer herself.
	  @return pointer to the requested interface in the descendant widget, or nil.
	*/
	virtual IDialog* CreateContextUI(const RsrcSpec& rSpec,
                                     const PMRect& globalAnchorRect,
                                     const ClassID& popupWindowClass = kPopupWindowBoss,
                                     bool16 preferredtoBeDrawnOnLeft = kFalse,
                                     bool16 invokedFromPalette = kFalse,
                                     bool16 okToCacheDialog = kFalse,
									 bool16 openImmediately = kTrue) = 0;

	/**
		opens up the context UI with a generic mechanism
		@param rSpec					The resource spec for the dialog.
		@param anchorRect				The rect around which the panel is to be opened in global coordinate space.
		@param popupWindowClass			The pop up window class to use.
		@param preferredtoBeDrawnOnLeft	Flag to state the preference to be drawn on left.
		@param invokedFromPalette		Flag to specify whether the context UI is being invoked from the panel.
 	  	@param okToCacheDialog			Flag to specify whether or not to cache the context dialog ui.
		@param openImmediately			Flag to specify whether popup window should be immediately opened. Defaults to True. if False, user must call IDialog::Open on the returned pointer herself.
		@return pointer to the requested interface in the descendant widget, or nil.
	*/
	virtual IDialog* CreateContextUI_Generic(const RsrcSpec& rSpec, const PMRect& globalAnchorRect, const ClassID& popupWindowClass = kPopupWindowBoss,
		bool16 preferredtoBeDrawnOnLeft = kFalse, bool16 invokedFromPalette = kFalse, bool16 okToCacheDialog = kFalse, bool16 openImmediately = kTrue) = 0;

    /**
     repositions the context UI popup
     @param popupWindow                 Popup window reference.
	 @param showWindow					Flag to specify whether to show window after repositioning it.
	 @param anchorRect                  Rect around which popup should be repositioned, in global coordinate space.
     @param ensurePositionWrtDocLayout	Flag to specify whether popup window should be within document layout bounds or within screen bounds.
     @return nothing.
     */
    virtual void RepositionAndShowContextUIPopup(IWindow* popupWindow,
												 bool16 showWindow = kTrue,
												 const PMRect& globalAnchorRect = kZeroRect) = 0;

	/*
	Gets the effective icon rsrcID after adding the appropriate offset if applicable
	@param uiScale				The scale factor in which to load the icon.
	@param baseRsrcID			The base icon rsrcID to which offset is added.
	@return						The effective rsrcID after adding the offset depending upon the scaleFactor.
	*/
	virtual RsrcID GetEffectiveIconRsrcID(float uiSCale, RsrcID baseRsrcID) = 0;

	/*
	Fallback logic which decides which icon is loaded based on various factors.
	@param pluginID					The plugin of the resource being considered.
	@param rsrcType					The type of the resource , whether it is kPNGArtRsrcType etc.
	@param rscID					The base rscID for the icon.
	@param iconRsrcID				The rsrcID for which the try is made to load the icon before invoking fallback logic.
	@param iconScale				The desired scaleFactor in which the icon is tried to be loaded.
	@param loadedIconScale			The actual scaleFactor for which the icon is loaded after executing the fallback logic.
	@return							The icon resource is returned.
	*/
	virtual IDResource SetIconDimensions(PluginID pluginID, RsrcType rsrcType, RsrcID rscID, RsrcID iconRsrcID, float iconScale, float* loadedIconScale) = 0;

	/**
	* Draw rectangles filled with given color and having top rounded corners
	@param drawbotP bot where to draw the rectangle
	@param roundedRectAppearance instance of class RoundedRectAppearance stating appearance of the required rectangle
	*/
	virtual void DrawTopRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance) = 0;
    
    /** Check if the font can draw the sample string passed.
     @param font - the IPMfont which is to be used to draw the sample string.
     @param stringToDraw - the string to draw.
     @param fontSize - fontSize to be used to draw the string.
     returns anyone of the four enums present in DrawStatus.
     */
    virtual DrawStatus CanDrawSampleText(IPMFont* font, PMString &stringToDraw, float fontSize) = 0;
    
    /** Check if the font can draw the sample string passed.
     @param font - the psFontName string which is to be used to draw the sample string.
     @param stringToDraw - the string to draw.
     @param fontSize - fontSize to be used to draw the string.
     returns anyone of the four enums present in DrawStatus.
     */
    virtual DrawStatus CanTQDrawSampleText(std::string fontName, PMString &stringToDraw, float fontSize) = 0;
};

#endif // __IWidgetUtils__
