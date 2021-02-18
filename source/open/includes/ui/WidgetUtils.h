//=======================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/WidgetUtils.h $
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
#ifndef __WidgetUtils__
#define __WidgetUtils__

#include "IWidgetUtils.h" // see IWidgetUtils for comments explaining usage.
#include "CPMUnknown.h"

class UIDList;

// BP 04/26/01: Please use the WidgetUtils via the UtilsBoss, see Utils.h:
//		Utils<IWidgetUtils>()->IsTextLeftToRight( myControlView );

class WidgetUtils : public CPMUnknown<IWidgetUtils>
{
public:
	enum { kDefaultIID = IID_IWIDGETUTILS };

			WidgetUtils( IPMUnknown *boss );

	virtual SysPoint ConvertPointToLocalWindow(const PMPoint& mouseLocationInParentWindowCoords, IControlView* destinationView);

	virtual IPMUnknown* QueryRelatedWidget(const IPMUnknown* widget, const WidgetID& widgetId, const PMIID& iid);
	
	virtual void GrayOutFrameContents (IGraphicsPort *gc, PMRect frame, PMReal transparency);

	/** Fills the draw region of control view (or rect) with the correct palette background (Grey) using the offscreen Drawbot object. 
	 * Here the Drawbot object being passed as argument has been setup for offscreen, so the rectToFill
	 * area (in drawbot) has to be translated in client coordinates.
	 @param widget		: ControlView for drawing, the widget whose bounds you want to fill(if rectToFill is nil)
	 @param pDrawbot	: Offscreen Drawbot object, background rect will be drawn on its surface
	 @param rectToFill	: the rect you want to fill, if not the bounds of the widget
	 */
	virtual void DrawPaletteFill (const IControlView* widget, dvaui::drawbot::Drawbot * pDrawbot, const PMRect *rectToFill = nil);
	
	/**  Draws the background of control view using the Graphics Port passed as argument
	 @param widget		: ControlView for drawing, widget whose bounds you want to fill(if rectToFill is nil)
	 @param port		: GraphicsPort which will be used for Making AGM drawing calls, graphics port to draw into
	 @param rectToFill	: the rect you want to fill, if not the bounds of the widget
	 */
	virtual void DrawPaletteFill (const IControlView* widget,IGraphicsPort * port, const PMRect* rectToFill = nil);

	virtual void GridPanel_PositionWidgets(IPanelControlData* panel, int32 first, int32 last);
	virtual const InterfaceFontInfo GetAppropriateFontForWidget(const IControlView* widget);

	virtual	void DeleteWidgetAndChildren(IControlView* widgetToDelete);
	
#ifdef MACINTOSH
	virtual	void BringFinderToFront(void);
	virtual	void SynchDocumentProxyIcons(bool16 forceValidation = kFalse);
#endif

	virtual PMReal GetViewYPosition(IGraphicsContext* gc, const InterfaceFontInfo &fontInfo, const PMReal &height);

	virtual void SimulateClick(IEventHandler* targetEH);

	virtual void CombineRegions(IControlView* widget, SysWireframe& theRgn) const;
	
	virtual void DrawFocusRect(IControlView* view, const PMRect& r, bool16 flushDrawing);
	virtual bool16 DrawHiliteRect(IControlView* view, const PMRect& r, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness);
	virtual bool16 DrawHilitePath(IControlView* view, const PMPointList& pts, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness);
	virtual bool16 DrawHilitePath(IControlView* view, const PMPointListCollection& subPaths, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness);
	virtual bool16 DrawHilitePath(IControlView* view, SysWireframe hilitePath, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness);
	
	virtual bool16 FillHiliteRect(IControlView* view, const PMRect& r, bool16 flushDrawing = kTrue);
	virtual bool16 FillHilitePath(IControlView* view, const PMPointListCollection& subPaths, bool16 flushDrawing = kTrue);

	virtual void SetTextHighlightColor(IGraphicsPort *gPort, const IControlView *view);

	virtual const IUIColorSpec* QueryColorSpecForWidget(const IPMUnknown* widget);
	virtual void StripUserDecimal(PMString* string);
	virtual void FormatUserDecimal(PMString* string);
	virtual void StripAccelerators(PMString &rawString);
	virtual void GetFormattedString(const PMReal& value, const bool16& bHorizontal, PMString& outString);
	virtual void GetFormattedScalingString(const PMReal& value, PMString& outString, const bool16 bFormatWithParens);

	virtual PMReal GetViewScaleFactorReal(const IControlView* view); 

	virtual bool16 IsWidgetInPalette(const IControlView*  iWidget);

	virtual bool16 CopyBitsToView(IControlView* view, const Int32Rect& dstBounds, IDVPlatformOffscreen* srcOffscreen, const Int32Rect& srcBounds,
								  const PMMatrix& clip2destMatrix = PMMatrix(), const SysRgn clipRgn = nil);

    virtual void DrawRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance);

    virtual void DrawLeftRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance);

    virtual void DrawRightRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance);

	virtual bool16 IsClusterControllableChildWidget(IControlView* widget, bool16& isSelected, bool16 checkParentToBeCluster);

	virtual IPMUnknown*	QueryDescendentWidgetOfType(IPMUnknown* widget, PMIID interfaceID);

    virtual IDialog* CreateContextUI(const RsrcSpec& rSpec,
                                     const PMRect& anchorRect,
                                     const ClassID& popupWindowClass = kPopupWindowBoss,
                                     bool16 preferredtoBeDrawnOnLeft = kFalse,
                                     bool16 invokedFromPalette = kFalse,
                                     bool16 okToCacheDialog = kFalse,
									 bool16 openImmediately = kTrue);

	virtual IDialog* CreateContextUI_Generic(const RsrcSpec& rSpec, 
											 const PMRect& anchorRect, 
											 const ClassID& popupWindowClass = kPopupWindowBoss,
											 bool16 preferredtoBeDrawnOnLeft = kFalse, 
											 bool16 invokedFromPalette = kFalse, 
											 bool16 okToCacheDialog = kFalse,
											 bool16 openImmediately = kTrue);

    virtual void RepositionAndShowContextUIPopup(IWindow* popupWindow,
												 bool16 showWindow = kTrue,
                                                 const PMRect& anchorRect = kZeroRect);

	/*
	Gets the effective icon rsrcID after adding the appropriate offset if applicable
	@param uiScale				The scale factor in which to load the icon.
	@param baseRsrcID			The base icon rsrcID to which offset is added.
	@return						The effective rsrcID after adding the offset depending upon the scaleFactor.
	*/
	virtual RsrcID GetEffectiveIconRsrcID(float uiSCale, RsrcID baseRsrcID);
	
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
	virtual IDResource SetIconDimensions(PluginID pluginID, RsrcType rsrcType, RsrcID rscID, RsrcID iconRsrcID, float iconScale, float* loadedIconScale);

	virtual void DrawTopRoundedRect(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance);
    
    /** Check if the font can draw the sample string passed.
     @param font - the IPMfont which is to be used to draw the sample string.
     @param stringToDraw - the string to draw.
     @param fontSize - fontSize to be used to draw the string.
     returns anyone of the four enums present in DrawStatus.
     */
    virtual DrawStatus CanDrawSampleText(IPMFont* font, PMString &stringToDraw, float fontSize);
    
    /** Check if the font can draw the sample string passed.
     @param font - the psFontName string which is to be used to draw the sample string.
     @param stringToDraw - the string to draw.
     @param fontSize - fontSize to be used to draw the string.
     returns anyone of the four enums present in DrawStatus.
     */
    virtual DrawStatus CanTQDrawSampleText(std::string fontName, PMString &stringToDraw, float fontSize);
    
protected:
	void	GatherUIDsFromChildren( IControlView* parentWidget, UIDList*	uidList);
	
private:
	enum DrawType { kStroke, kFill };
	bool16	PrivateDrawHiliteRect(IControlView* view, const PMRect& r, DrawType drawType, bool16 flushDrawing = kTrue, PMReal hiliteThickness = kDefaultHiliteThickness);
	bool16	PrivateDrawHilitePath(IControlView* view, const PMPointListCollection& subPaths, DrawType drawType, bool16 flushDrawing, PMReal hiliteThickness = kDefaultHiliteThickness);

	void	PlaceRoundedRectPathInPort(dvaui::drawbot::PathP &pathP, const RoundedRectAppearance& roundedRectAppearance);
	void	StrokeBevelRoundedRectPath(dvaui::drawbot::Drawbot *drawBotP, const RoundedRectAppearance& roundedRectAppearance);
	void	PlaceLeftRoundedRectPathInPort(dvaui::drawbot::PathP &pathP, const RoundedRectAppearance& roundedRectAppearance);
	void	PlaceRightRoundedRectPathInPort(dvaui::drawbot::PathP &pathP, const RoundedRectAppearance& roundedRectAppearance);
	void	PlaceTopRoundedRectPathInPort(dvaui::drawbot::PathP &pathP, const RoundedRectAppearance& roundedRectAppearance);

};

#endif // __WidgetUtils__
