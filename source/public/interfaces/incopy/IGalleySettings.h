//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleySettings.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IGalleySettings__
#define __IGalleySettings__

#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "IPMUnknown.h"

class RealAGMColor;
class IPMFont;

/** Setters and Getters for the various Galley properties*/
class IGalleySettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGALLEYSETTINGS };

	/** The type of cursor that should be shown in the galley */
	enum CursorType{
		/** Use a normal thin straight line */
		kNormalCursor = 0, 
		/** Use a thick straight line */
		kThickCursor, 
		/** typical i-beam insertion point */
		kBarbellCursor, 
		/** Insertion point is a block that covers the current letter */
		kBlockCursor};
		

	/** Should the text be drawn antialiased
		@return - kTrue == Draw the text antialias
	*/
	virtual bool16 GetSmoothText() const = 0;

	/** Set whether or not the text shoudl be antialiased
		@param smoothText - kTrue will draw the text antialiased
	*/
	virtual void SetSmoothText(bool16 smoothText) = 0;			
	
	/** Should we show paragraph style names or not
		@return - kTrue == Show the style names
	*/
	virtual bool16 GetShowParagraphStyleNames() = 0;
	
	/** Set whether or not to show paragraph style names
		@param showStyleNames - kTrue will Show the style names
	*/
	virtual void SetShowParagraphStyleNames(bool16 showStyleNames) = 0;
	
	/** Should we show paragraph break marks or not
		@return - kTrue == Show the paragraph break marks
	*/
	virtual bool16 GetShowParagraphBreakMarks() = 0;
	
	/** Set whether or not to show paragraph break marks
		@param showBreakMarks - kTrue will Show the paragraph break marks
	*/
	virtual void SetShowParagraphBreakMarks(bool16 showBreakMarks) = 0;
	
	/** Get the paragraph indent multiplier
		@return - Value for the paragraph indent multiplier
		@see SetParagraphIndentMultiplier
	*/
	virtual PMReal GetParagraphIndentMultiplier() = 0;
	
	/** Allow control of the distance that paragraphs are indented. A value of 1.0 for the multiplier will give an indent of
		1X the width of the paragraph glyph (kTextChar_PilchrowSign) at the currently selected display font size. Using the
		font for show invisible characters ("AdobeSansMM"). 2.0 is 2X, 2.1 is 2.1X etc... Negative numbers while allowed
		are not tested.
		@param indentMultiplier - Value for the paragraph indent multiplier
	*/
	virtual void SetParagraphIndentMultiplier(const PMReal indentMultiplier) = 0;
	
	/** Should we show line numbers or not
		@return - kTrue == Show the line numbers
	*/
	virtual bool16 GetShowLineNumbers() = 0;
	
	/** Set whether or not to show line numbers
		@param showLineNumbers - kTrue will Show the line numbers
	*/
	virtual void SetShowLineNumbers(bool16 showLineNumbers) = 0;
	
	/** Is the galley ALE (accurate line endings) or ILE (inaccurate line ending)
		@return - kTrue == Using ALE
	*/
	virtual bool16 GetIsGalleyAle() = 0;
	
	/** Set whether galley is ALE (accurate line endings) or ILE (inaccurate line ending)
		@param isAle - kTrue will use ALE
	*/
	virtual void SetGalleyAle(bool16 isAle) = 0;
	
	/** Get the color to show the galley text in
		@return - The color to show the text in
	*/
	virtual RealAGMColor &GetTextColor() = 0;
	
	/** Set color to show the galley text in
		@param color - The text color to show the text in
	*/
	virtual void SetTextColor(RealAGMColor &color) = 0;
	
	// Galley background color
	
	/** Get the color for the galley background
		@return - The color to use for the galley background
	*/
	virtual RealAGMColor &GetBackgroundColor() = 0;
	
	/** Set the color for the galley background
		@param color - The background color to show in the galley
	*/
	virtual void SetBackgroundColor(RealAGMColor &color) = 0;
	
	/** Get the amount of leading to use for the text
		@return - Value to use for the leading
	*/
	virtual PMReal GetLeadingValue() const = 0;
	
	/** Set the amount of leading to use for the text
		@param leadingValue - Value to use for the leading
	*/
	virtual void SetLeadingValue(PMReal leadingValue) = 0;
	
	/** List of Font Overrides (font that display in their true type instead of
		as the galley display font)
	*/

	/** Get the override count 
		@return - Number of overrides
	*/
	virtual int32 GetOverrideCount() = 0;
	
	/**	Get the name of a particular font override
		@param n - The item in the list that you want the name of
		@return - The name of the selected font
	*/
	virtual const PMString &GetNthFontOverrideName(int32 n) = 0;

	/**	Set the name of a particular font override
		@param n - The item in the list that you want to set the name of
		@param &name - The name of the selected font
	*/
	virtual void SetNthFontOverrideName(int32 n, const PMString &name) = 0;

	/** Remove a font from the list of overrides
		@param n - The font to remove from the list
	*/
	virtual void DeleteNthFontOverrideName(int32 n) = 0;
	
	/** Add a font override to the list
		@param &name - The name to append
	*/
	virtual void AppendFontOverrideName(const PMString &name) = 0;
	
	/** Is a given font in the override list
		@param fontFamilyName - The family name of the font you are checking for
		@param *font - The font you are looking for
		@return - kTrue means that the font was in the list and is overridden
	*/
	virtual bool16 IsAnOverrideFont(PMString fontFamilyName, IPMFont *font = nil) = 0;
	
	/** Get the cursor type to use for this galley view
		@return - The type of the cursor to use
	*/
	virtual IGalleySettings::CursorType GetCursorType() = 0;

	/** Set the cursor type to use for this galley view
		@param type - The type of the cursor to use
	*/
	virtual void SetCursorType(CursorType type) = 0;
	
	/** Get the display font preference to use for this galley view
		@return - The display font to use
	*/
	virtual PMString GetDisplayFont() = 0;
	
	/** Set the display font preference to use for this galley view
		@param displayFont - The display font preference to use
	*/
	virtual void SetDisplayFont(PMString displayFont) = 0;

	/** Get whether text cursor should blink or not
		@return - whether text cursor should blink or not
	*/
	virtual bool16 GetBlinkCursor() = 0;
	
	/** Set whether text cursor should blink or not
		@param blinkOn - whether text cursor should blink or not
	*/
	virtual void SetBlinkCursor(bool16 blinkOn) = 0;
	
	/** Set whether the user font display font override setting will do anything in galley. Note that
		the hard coded overrides will always apply no matter what the setting.
		@param useUserOverride - Use the override or not
	*/
	virtual void SetUseUserFontOverride(bool16 useUserOverride) = 0;
	
	/** Get whether the user font display font override setting will do anything in galley. Note that
		the hard coded overrides will always apply no matter what the setting.
		@return - Use the override or not
	*/
	virtual bool16 GetUseUserFontOverride() = 0;
	
	/** Set the font size to use for this galley view
		@param &fontsize - The font size to use
	*/
	virtual void SetDisplayFontSize (const PMReal& fontSize) = 0;
	
	/** Get the font size to use for this galley view
		@return - The font size to use
	*/
	virtual PMReal GetDisplayFontSize () = 0;
	
	/** Set the whether or not to use the display font for this galley view.
		Not persistant right now but can be set on a session basis. This can be used to cause the story/galley
		views to use the actual text model font to display text rather than the display font. Currently,
		this is not part of the regular product (ie. we always display text in the display font except
		for exceptions stored in the override font list.
		@param useDisplayFont - The use the display font or not
	*/
	virtual void SetUseDisplayFont(bool16 useDisplayFont) = 0;

	/** Get the whether or not to use the display font for this galley view.
		@return - The use the display font or not
	*/
	virtual bool16 GetUseDisplayFont() = 0;

	/** Set the width preference for the info column
		@param width - The width preference for the info column
	*/
	virtual void SetInfoColumnWidth(PMReal width) = 0;
	
	/** Get the width preference for the info column
		@return - The width preference for the info column
	*/
	virtual PMReal GetInfoColumnWidth() = 0;

	/** Set the hidden state of the info column. Only used in InCopy.
		@param hidden - Is the info column hidden or visible
	*/
	virtual void SetInfoColumnHidden(bool16 hidden) = 0;
	
	/** Get the hidden state of the info column. Only used in InCopy.
		@return - Is the info column hidden or visible
	*/
	virtual bool16 GetInfoColumnHidden() = 0;
	
	
	enum OversetDisplayType {
		/** Overset text is display just like any other text in the story */
		kNone = 0, 
		/** A divider precedes the overset text and the text itself is displayed in a different color */
		kDividerColor, 
		/** A divider precedes the overset text and the text background is displayed in a different color */
		kDividerBackground, 
		/** No divider but the overset text is displayed in a different color */
		kColorOnly,
		/** No divider but the overset background is display in a different color */
		kBackgroundOnly,
		/** No divider a vertical bar is drawn on the side and a stair step line is draw though point where overset begins */
		kMarginIndicator
		};
		
	/** Allows control of the way overset text is display in the story view.
		@param oversetType see enum values.
	*/
	virtual void SetOversetDisplayType(OversetDisplayType oversetType) = 0;
	
	/** Get the value setting for the way overset text is display in story view.
		@param oversetType see enum values.
	*/	
	virtual OversetDisplayType GetOversetDisplayType() = 0;
	
	/** Set the color of the background for overset text.
		@param color value to display overset text background
	*/
	virtual void SetOversetBackgroundColor(const RealAGMColor &color) = 0;
	
	/** Get the background color of overset text.
		@param color value of background overset text.
	*/	
	virtual RealAGMColor GetOversetBackgroundColor() = 0;
	
	/** Set the show state of the depth ruler.
		@param hidden - kTrue the the ruler will be shown
		@return none
	*/
	virtual void SetShowDepthRuler(bool16 showRuler) = 0;
	
	/** Get the show state of the depth ruler.
		@return kTrue if the ruler is shown otherwise it's hidden
	*/
	virtual bool16 GetShowDepthRuler() = 0;
	
	/** Used to describe the style of view antialiasing to use in the story and galley views */
	enum TextAntiAliasType {
		/** Default type is grayddr same as layout */
		kStandardGrayDDR = 0,
		
		/** ColorDDR use shades of color rather than shades of grey to anti-alias */
		kColorDDR,
		
		/** use preview mode */
		kPreview
	};	

	/** Set style of text anti-aliasing to use for galley/story text.
		@param aliasType - type of anti-alias to use
		@return none
	*/
	virtual void SetTextAntiAliasStyle(TextAntiAliasType aliasType) = 0;
	
	/** Get style of text anti-aliasing used to render text.
		@return style of anti-aliasing being used
	*/
	virtual TextAntiAliasType GetTextAntiAliasStyle() = 0;
	
	/** Set the show state of footnotes in galley and story view.
		@param show - kTrue to show footnotes
	*/
	virtual void SetShowFootnotes(bool16 showFootnotes) = 0;

	/** Get the show state footnotes in galley and story view.
		@return kTrue if the ruler is shown otherwise it's hidden
	*/
	virtual bool16 GetShowFootnotes() = 0;
	
	/** Set the color to display the bookends for footnotes
		@param color - color to display the footnotes in
	*/
	virtual void SetFootnoteDisplayColor(const RealAGMColor &color) = 0;
	
	/** Get the color to display the bookends for footnotes
		@return color the footnote bookends are being displayed in.
	*/
	virtual RealAGMColor &GetFootnoteDisplayColor() = 0;

};

#endif // __IGalleySettings__