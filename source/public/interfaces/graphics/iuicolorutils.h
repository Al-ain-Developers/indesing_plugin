//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/iuicolorutils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IUIColorUtils__
#define __IUIColorUtils__

#include "AppFrameworkID.h"
#include "IPMUnknown.h"
#include "Utils.h"

#include "IColorData.h"

#include "PMString.h"

class IScript;
class IScriptRequestData;
class IStringListControlData;
class IDocument;

// Constant used to adjust ui colors for handle shape drawing.
// Used in AdjustUIColorValue.
const PMReal kDefaultUIColorAdjust = 0.5;

/**
 Utility interface for dealing with UI colors.
 
 Note: This interface should be accessed through the Utils boss, eg., 
 Utils<IUIColorUtils>()->CopyObjects( ... )
 
 @see Utils
 */
class IUIColorUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUICOLORUTILS };

	/** For doc UI colors
	*/
	enum {
		/** The following 27 layer colors are all colors in the IID_IUICOLORLIST. This list can be added to,
		but these are the default colors for items in the Preferences dialogs for these items.
		*/
		kStockUILightBlue,
		kFirstUIColor = kStockUILightBlue,
		kStockUIRed,
		kStockUIGreen,
		kStockUIBlue,
		kStockUIYellow,
		kStockUIMagenta,
		kStockUICyan,
		kStockUIGray,
		kStockUIBlack,
		kStockUIOrange,
		kStockUIDarkGreen,
		kStockUITeal,
		kStockUITan,
		kStockUIBrown,
		kStockUIViolet,
		kStockUIGold,
		kStockUIDarkBlue,
		kStockUIPink,
		kStockUILavender,
		kStockUIBrickRed,
		kStockUIOlive,
		kStockUIPeach,
		kStockUIBurgundy,
		kStockUIGrassGreen,
		kStockUIOchre,
		kStockUIPurple,
		kStockUILightGray,

		kLastRomanUIColor = kStockUILightGray,

		/** The following are CJK specific colors --- (as of InDesign 2, these colors are in both feature sets).
		*/
		kStockUICharcoal,
		kFirstJUIColor = kStockUICharcoal,
		kStockUIGridBlue,
		kStockUIGridOrange,
		kStockUIFiesta,
		kStockUILightOlive,
		kStockUILipstick,
		kStockUICuteTeal,
		kStockUISulfur,
		kStockUIGridGreen,
		kStockUIWhite,
				
		kLastJUIColor = kStockUIWhite,
		kLastUIColor = kStockUIWhite,
		
		/** These colors are surrogates for special ui colors defined above
		*/
		kStockBaselineGrid = kStockUILightBlue,
		kStockMarginGuide = kStockUIMagenta,
		kStockRulerGuide = kStockUICyan,
		kStockColumnGuide = kStockUIViolet,
		kStockDocumentGrid = kStockUILightGray,
		kStockFloor = kStockUILightGray,
		kStockDynamicSpell = kStockUIRed,
		kStockDynamicSpellGrammar = kStockUIGreen,
		kStockJBaselineGrid = kStockUILightBlue,
		kStockJMarginGuide = kStockUILipstick,
		kStockJColumnGuide = kStockUILavender,
		kStockLayoutGrid = kStockUIGridGreen,
		kStockReferencePoint = kStockUITeal,
		kStockPasteboard = kStockUIWhite,
		kStockXMLTag = kStockUIGray,
		kStockPreviewBackground = kStockUILightGray

		};
	
	/** For the operations of dropdown list and color widgets
	*/
	enum {
		kNumUIColors = kLastUIColor - kFirstUIColor + 1
	};
	
		
	enum
	{
		kRed = 0,
		kGreen,
		kBlue
	};


	/**
	 Fills in the string list data with the UI color names. Will optionally 
	 add "Other" at the end.
	 
	 @param stringData		OUT The string list control data to populate
	 @param bAddOther		IN If kTrue, the method will add an entry for "Other" at the end
	 */
	virtual void BuildUIColorNameList(IStringListControlData *stringData, bool16 bAddOther = kTrue) = 0;
	
	/**
	 Returns the number of available UI Colors.
	 
	 @return The number of UI colors
	 */
	virtual int32 GetUIColorNum( ) = 0;

	/**
	 Returns the name of the UI color at the given index.
	 
	 @return The name of the UI color at index
	 */
	virtual PMString GetUIColorName(int32 index) = 0;

	/**
	 Gets the stock color from the given document's UI color list (which 
	 resides in the document's workspace). If the document is nil, will default
	 to the app UI color list.
	 
	 @param stockColor		IN The index of the stock color to return
	 @param doc				IN The document in which to find the color
	 @return UIDRef for the UI color (a swatch)
	 @see IColorData
	 */
	virtual UIDRef GetUIColor(int32 stockColor, IDocument* doc) = 0;
	
	/**
	 Gets the index of the specified stock color from a document's UI color list
	 (which resides in the document's workspace). If the document is nil, will 
	 default to the app UI color list.
	 
	 @param stockColorUID	IN The stock color's UID
	 @param doc				IN The document in which to find the color
	 @return The index of the specified stock color, or -1 if it cannot be found
	 */
	virtual int32 GetUIColorIndex(UID stockColorUID, IDocument* doc) = 0;
	
	/**
	 Gets the RGB value for a global UI color (from the application workspace).
	 
	 @param stockColor		IN The index of the stock color in the global color list
	 @return The RGB value for the specified UI color
	 */
	virtual ColorArray GetStockUIColorRGBValue( int32 stockColor ) = 0;
	
	/**
	 Gets the RGB value for a UI color from the given database. The color 
	 definition must already be in RGB color space. Otherwise, it will return 
	 the RGB value for Black.
	 
	 Use this when drawing document UI related colors such as guides, layer, etc.
	 
	 DO NOT use this to render any document color from the color list.
	 
	 @param db				IN The database for the UI color
	 @param colorUID		IN The UID for the UI color
	 @return The RGB value for the specified UI color, or the RGB value for black if the requested color is not already RGB
	 */
	virtual ColorArray GetRGBColorValue( IDataBase* db, UID colorUID ) = 0;

	/**
	 Gets a UI color adjusted by moving its RGB values closer to white (1.0). 
	 Used for standoff handle shape color, frame thread lines, and document 
	 grid subgridlines.
	 
	 Note: adjustFactor must be a percent value from 0.0 (0%) to 1.0 (100%)
	 
	 @param color			IN The color to adjust (RGB)
	 @param adjustFactor	IN The percentage by which RGB values are adjusted
	 @return The adjusted RGB color values
	 */
	virtual ColorArray GetAdjustedUIColorValue(ColorArray& color, PMReal adjustFactor) = 0;

	//FOR SCRIPTING -----------------------------------------------------------------------

	/**	Gets the UI color for scripting.
		GetUIColor needs both the uid of the ui color as well as its index.
		However, the caller need only supply one or the other.
		A valid UID and an index of -1 or a kInvalidUI and a valid index.
		@param data is the script event data from which the data is retrieved.
		@param script is the script object.
		@param propID is the property ID of the script object.
		@param colorUID is the color UID of the object.
		@param colorIndex is the color index of the object.
	*/
	virtual int32 GetUIColor( IScriptRequestData* data, IScript* script, const ScriptID& propID, UID colorUID = kInvalidUID, int32 colorIndex = -1 ) = 0 ;
	/**	Sets a UI color for scripting.
		@param data is the script event data from which the data is retrieved.
		@param script is the script object.
		@param propID is the property ID of the script object.
		@param colorUID is the new color UID to set.
	*/
	virtual int32 SetUIColor( IScriptRequestData* data, IScript* script, const ScriptID& propID, UID* colorUID ) = 0 ;
};


#endif	// __IUIColorUtils__
