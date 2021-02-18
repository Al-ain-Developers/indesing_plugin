//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVPublicUtilities.h $
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
//  Copyright 1997-2012 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __DVPublicUtilities__
#define __DVPublicUtilities__
	
#include "DVAForwardDeclarations.h"

#include "IDVUINodeRef.h"
#include "IControlView.h"
#include "IGraphicsPort.h"
#include "IInterfaceColors.h"


#if WINDOWS
#include "WInterfaceFontInfo.h"
#elif MACINTOSH
#include <Cocoa/Cocoa.h>
#include "MInterfaceFontInfo.h"
#endif

#include "boost/cast.hpp"
#include "boost/function.hpp"

class IWindow;

#pragma export on

/** namespace ID::os_utils
	Contains a number of platform utilities for HiDPI screens
 */

namespace ID {
namespace os_utils
{
	/**
	 * Does the current machine/OS support HiDPI displays.
	 *	yes or no 
	 */
	DV_WIDGET_DECL bool HasHiDPISupport();

	/**
	 * Does the machine currently have a HiDPI display (built in or external)
	 *	yes or no based on current configuration of monitor(s)
	 *  Note: Mac Retina screens are always in HiDPI mode, but with QuartzDebug installed, a 27" Apple monitor can switch HiDPI state on/off dynamically.
	 */
	DV_WIDGET_DECL bool HasHiDPIDisplay();
	
	/**
	 * Get the UI scale factor for the given control view (this should be called at draw time, but not cached between draw calls)
	 *  Note: in CC this returns 1, or on Mac only, 2 for HiDPI mode.
	 */
	DV_WIDGET_DECL float GetViewScaleFactorReal(const IControlView* view);

	/**
	* Gets the adjusted scale factor for the given control view (this should be called at draw time, but not cached between draw calls)
	*  Note: it either returns 1.0, 1.5, 2.0 or 3.0.
	*/
	DV_WIDGET_DECL float GetViewScaleFactorAdjusted(const IControlView* view);
};
};

namespace dv_utils
{

/**
 * The default size of the stroke pen
 */
const float kDefaultStrokeWidth = 1.0f;

//=====================================================================================================================
/** Font metrics */
DV_WIDGET_DECL bool FontInfoGetDVAFontMetrics(const InterfaceFontInfo & fontInfo,
							float* size = nil, float* ascent = nil, float* descent = nil, float* leading = nil);
	
/** Measuring strings */
DV_WIDGET_DECL float FontInfoDVAMeasureStringWidth(const InterfaceFontInfo & fontInfo, const PMString &str, int32 numChars = -1); // -1 means measure full string
DV_WIDGET_DECL float FontInfoDVAMeasureMultiLineStringHeight(const InterfaceFontInfo & fontInfo, const PMString &str, float stringWidth, int32 numChars = -1); // -1 means measure full string

DV_WIDGET_DECL PMPoint StringDimension( const InterfaceFontInfo & fontInfo, const PMString & str); //StringUtils::PMMeasureString calls this

//=====================================================================================================================

/** Drawing Utility Functions for drawbot
	These allow for simple drawing operations without exposure to the drawbot API. 
	Useful in simple drawing scenarios where the overhead of offscreen drawing via AGM is not desirable.
*/

/** Anti-alias policies */
typedef enum {
	kAntiAliasPolicy_None = 0,
	kAntiAliasPolicy_Med,
	kAntiAliasPolicy_High,
	
	kAntiAliasPolicy_Default = kAntiAliasPolicy_None
} AntiAliasPolicy;
	
/** Setting the anti-alias policy */
DV_WIDGET_DECL void DVSetAntiAliasPolicy(dvaui::drawbot::Drawbot* drawbotP, dv_utils::AntiAliasPolicy aaPolicy);
	
/** stack based object for saving and restoring the drawbot drawing state
	Similar to AutoGSave
 */
class DV_WIDGET_DECL DVSaveAndRestoreStateStack
{
public:
	DVSaveAndRestoreStateStack(dvaui::drawbot::Drawbot* drawbotP, bool dummy); // Workaround 2nd parameter seems necessary to disambiguate this from default copy constructor
	virtual ~DVSaveAndRestoreStateStack();
	
private:
	dvaui::drawbot::Drawbot* fDrawbotP;
	bool fDummy;
};

/** Drawing primitives - basic fill, bevel and stroke */
DV_WIDGET_DECL void DVFillRect(dvaui::drawbot::Drawbot* drawbotP, const RGBColor& color, const PMRect& fillRect);

DV_WIDGET_DECL void DVFillRect(dvaui::drawbot::Drawbot* drawbotP, const RealAGMColor& color, const PMRect& fillRect);

DV_WIDGET_DECL void DVBevelRect(dvaui::drawbot::Drawbot* drawbotP, const RGBColor& nwColor, const RGBColor& seColor, const PMRect& bevelRect, const float strokeWidth = kDefaultStrokeWidth);

DV_WIDGET_DECL void DVBevelRect(dvaui::drawbot::Drawbot* drawbotP, const RealAGMColor& nwColor, const RealAGMColor& seColor, const PMRect& bevelRect, const float strokeWidth = kDefaultStrokeWidth);

DV_WIDGET_DECL void DVStrokeRect(dvaui::drawbot::Drawbot* drawbotP, const RGBColor& color, const PMRect& strokeRect, const float strokeWidth = kDefaultStrokeWidth);

DV_WIDGET_DECL void DVStrokeRect(dvaui::drawbot::Drawbot* drawbotP, const RealAGMColor& color, const PMRect& strokeRect, const float strokeWidth = kDefaultStrokeWidth);
	
DV_WIDGET_DECL void DVStrokePath(dvaui::drawbot::Drawbot* drawbotP, const RGBColor& color, const PMPointList& pts, const float strokeWidth = kDefaultStrokeWidth);
	
DV_WIDGET_DECL void DVStrokePath(dvaui::drawbot::Drawbot* drawbotP, const RealAGMColor& color, const PMPointList& pts, const float strokeWidth = kDefaultStrokeWidth);

/** Drawing via a drawbot callback
	Used to trigger a DV_Draw call followed by a call to another function (useful for some target highlighting scenarios)
 */
typedef boost::function<bool (const dvaui::ui::UI_Node*, dvaui::drawbot::Drawbot*)> CustomDirectDrawCallbackFunction;
WIDGET_DECL void DirectDrawUsingDrawbot(IControlView* widget, SysRgn invalidRgn, CustomDirectDrawCallbackFunction fnPtr);

/** Direct Draw a PNG Image over Drawbot surface, this API should be called from DV_Draw() method
 *
 *  It is an API to directly draw the image on Drawbot surface, without using the off-screen drawing functionality
 *  This function provides capability to draw transparent PNG images appropriately over Drawbot surface
 *
 *  inDrawbotP	- Drawbot pointer, provide the surface to draw the PNG image directly
 *	inPluginID	- Plugin ID, to load the PNG image resource
 *  inRsrcID	- PNG image resource ID
 *  inDrawPoint	- The Left,Top draw point on Drawbot surface to draw the image
 *	inDrawDisabled - Default parameter, if true, will draw image at 50% opacity, else at 100% opacity
 */
DV_WIDGET_DECL void DrawImageUsingDrawbot(
	dvaui::drawbot::Drawbot*	inDrawbotP, 
	const PluginID				inPluginID, 
	const RsrcID				inRsrcID, 
	const PMPoint&				inDrawPoint,
	const bool16				inDrawDisabled = kFalse);

/** Direct Draw a PNG Image over Drawbot surface, this API should be called from DV_Draw() method
 *
 *  It is an API to directly draw the image on Drawbot surface, without using the off-screen drawing functionality
 *  This function provides capability to draw transparent PNG images appropriately over Drawbot surface
 *
 *  inDrawbotP	- Drawbot pointer, provide the surface to draw the PNG image directly
 *	inPluginID	- Plugin ID, to load the PNG image resource
 *  inRsrcID	- PNG image resource ID to be drawn
 *  inMatrix	- Matrix transformation  to be applied on Drawbot surface
 *	inAlpha		- Default parameter, transparency to draw the image, by default 100% opacity
 */

DV_WIDGET_DECL void DrawImageUsingDrawbot(
	dvaui::drawbot::Drawbot*	inDrawbotP, 
	const PluginID				inPluginID, 
	const RsrcID				inRsrcID,
	const PMPoint &				inDrawPoint,
	const PMMatrix &			inMatrix,
	const float					inAlpha = 1.0f);
	
//=====================================================================================================================	
	
/***********************************************************************/
// UI Theme related API (fonts, suzes, colors, etc.)
	
enum DroverThemeID
{
	kIDDialogTheme = 0,		// ID for obtaining theme for Dialog
	kIDPanelTheme,			// ID for obtaining theme for Palette	
	kIDDocumentTheme,		// ID for obtaining theme for Document	
	kIDTouchContainerTheme,	// ID for obtaining theme for Touch Container	
	kIDTouchPanelTheme,		// ID for obtaining theme for Touch Panel	
};

/* Initialize the theme cache
 *
 */
DV_WIDGET_DECL bool InitializeColorTheme();

/* Release the theme cache
 *
 */
DV_WIDGET_DECL void UninitializeColorTheme();


/* SetThemeForWindow sets the drover theme on the window, the theme is specified by theme ID
 *  This function should be called to set the appropriate theme on the Dialog / Palette / Document Window.
 *  The return value of SetThemeForWindow() will suggest whether call is successful or failure. 
 *  inWindow - IWindow pointer
 *	inThemeID - The ID for Dialog, Palette, or Document
 *  outFontStyle - the normal font of the theme
 *  outHiliteFontInfo - the highlight font of the theme
 */
DV_WIDGET_DECL bool16 SetThemeForWindow(
	const IWindow *					inWindow, 
	const DroverThemeID				inThemeID,
	InterfaceFontInfo &				outFontInfo, 
	InterfaceFontInfo &				outHiliteFontInfo);
	
/* SetThemeForView sets the drover theme for a sub hierarchy within a window, the theme is specified by theme ID
 */
DV_WIDGET_DECL bool16 SetThemeForView(
	const IControlView*				inView, 
	const DroverThemeID				inThemeID);

DV_WIDGET_DECL bool GetThemeFontForWidget(const IControlView* widget, InterfaceFontInfo& outFontInfo);
		
#if WINDOWS
	/* ShouldUseAlternateChineseWinXPUIFont has been moved from WInterfaceFonts.cpp
	 *
	 */
	DV_WIDGET_DECL bool ShouldUseAlternateChineseWinXPUIFont(const PMLocaleId& locale);
#endif
	
/***********************************************************************/
// UI Brightness related API
DV_WIDGET_DECL void SetBrightness(const float inBrightness);

DV_WIDGET_DECL float GetBrightness();

/*  IsUIInterfaceBright return FALSE if dark User Interface, and TRUE if bright User Interface
 *  For Dark UI, the brightness value is [0.0, threshhold] and
 *  for Bright UI, the brightness value is (threshhold, 1.0]
 *
 *	default threshhold is 0.5
 */
DV_WIDGET_DECL float GetUIBrightnessThreshhold();
DV_WIDGET_DECL bool IsUIInterfaceBright();

/***********************************************************************/

DV_WIDGET_DECL float GetScrollbarDefaultSize();

DV_WIDGET_DECL void DrawConditionalTextThumbnailBorder(dvaui::drawbot::Drawbot* drawbotP, const PMRect& strokeRect, const float strokeWidth, const IControlView* iView);

DV_WIDGET_DECL void DrawInfoThumbnailBorder(IGraphicsPort* gPort, const PMRect &thumbnailBorder, const IControlView* iView);

/***********************************************************************/
// Tool Tips related API

DV_WIDGET_DECL void UpdateToolTipOnMouseMoveUtility(const IControlView* view);

} //namespace dv_utils

#pragma export off

#endif // DVPublicUtilities
