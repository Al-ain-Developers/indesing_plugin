//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVStaticTextView.h $
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
#ifndef __DVDVStaticTextView__
#define __DVDVStaticTextView__

#include "DVAbstractControlView.h"
#include "InterfaceFontInfo.h"
#include "IInterfaceColors.h" 

#include "WidgetDefs.h" // ellipsize constants are define here

#include "DVAForwardDeclarations.h"

/** Static Text View class overview:

	  I decided to keep DVStaticTextView based on UI_StaticText (keeping simple things simple), but have added OwnerDraw variants to allow a client more control over background fill, 
	font settings, text placement, etc. There is a common abstract baseclass now for all static text views, and the hierarchy looks like this:

	DVAbstractStaticTextView
		DVStaticTextView
			DVStaticMultiLineTextView == StaticMultiLineTextView
		AbstractOwnerDrawnStaticTextView
			DVOwnerDrawStaticTextView
			AGMOwnerDrawStaticTextView
			AGMOwnerDrawStaticMultiLineTextView

	DVAbstractStaticTextView:
		defines a common API and contains the shared code that came from refactoring the cloned and tweaked versions of Draw() in the clients.

	DVStaticTextView:
		implements that API onto a drover UI_StaticText, pretty much as it did before, but with the above bottleneck methods for text, font, color, ellipsizing, ampersand_to_underline, etc.
		DVStaticTextView draws with the font and size from the relevant theme. Color and font style can be changed.

	AbstractOwnerDrawnStaticTextView:
		implements that API onto a drover UI_ControlView, using local storage for the text, font, color etc so that it's subclasses can easily separate drawing from 
		decisions about where the text is located or where to find the appropriate font/color etc.

	AGMOwnerDrawStaticTextView:
		is based on the code from the old fully customizeable drawing code from CStaticTextView, but refactored to match the new API. 
		When converting, I used AGMOwnerDrawStaticTextView as the baseclass for complex clients that couldn't be easily converted to DVStaticTextView. 
		I still tried to factor out common code whenever possible but I had to leave the worst of the old "lets do everything in the Draw method" code alone.

	DVOwnerDrawStaticTextView:
		is just a skeleton at this point (with no clients). 
		My idea was to just droverize the code from AGMOwnerDrawStaticTextView, but I'm interested in Deepak's idea of trying to reuse the drawing code from UI_StaticText.

	DVStaticMultiLineTextView:
		continues to derive from DVStaticTextView. 
	
	AGMOwnerDrawStaticMultiLineTextView:
		is based on the code from the old fully customizeable drawing code from StaticMultiLineTextView, but refactored a little to match the inherited API. 
		I ran into a couple of cases where an OwnerDraw version would be required (one, in order to mix font styles within the text) 

*/

#pragma mark -
#pragma mark class DVAbstractStaticTextView
/**
	DVAbstractStaticTextView:
	Common base class for our StaticTextView variants.
	Common code has been refactored into a set of common text value getters and setters. Standard implementations are provided, but can be overridden.
*/
class DV_WIDGET_DECL DVAbstractStaticTextView : public DVAbstractControlView
{
	typedef DVAbstractControlView inherited;
public:
	DVAbstractStaticTextView(IPMUnknown *boss); // subclass constructors create underlying drover widget
	virtual ~DVAbstractStaticTextView();

	virtual void				ReadWrite(IPMStream *s, ImplementationID prop);
	
	// Override if the text is not being updated by some other interface, and/or if other text parameters can change at Draw time.
	//	If overridden, collect necessary information and call SetTextValue(s) or UpdateAllTextValues.
	virtual void				PreDrawGetText() = 0 ; // collects values from the text value methods below in preparation for drawing.

	//Sets the mnemonic location for drawing accelerator keys, this is required to be called
	//whenever we want to draw the text string corresponding to this static text widget.
	virtual void				SetMnemonic(PMString& textString) const;

	// Applies the ShouldEllipsize and StripMenuAccelerators settings to the raw string from GetText()
	virtual	void				ProcessRawTextString(PMString& rawString) const;
	
	// We override Hilite to recompute font when hilite state changes (old CStaticTextView did this on every draw call)
	virtual void				Hilite(bool16 doHilite = kTrue); 

	virtual void				GetText(PMString& stringToDraw) const;						// defaults to local ITextControlData, override if elsewhere.

	friend class				DVTextControlData; //DVTextControlData calls SetTextValue on string changes (rather than exposing implementation details here)

	void UpdateColorsOnBrightnessChange();
	
protected:
	// Clients can override these text value methods to customize text drawing attributes
	virtual void 				GetTextColors(RealAGMColor& enabledTextColor, RealAGMColor& disabledTextColor) const;	// defaults to theme colors (based on enabled and hilited states) 
	virtual void				GetAdjustedTextFrame(PMRect& adjustedTextFrame) const;		// defaults to widget frame moved to (0,0)
	virtual void				GetFont(InterfaceFontInfo& fontInfo) const;					// defaults to theme font (based on  hilited state)
	virtual bool16				GetShouldStripMenuAccelerators() const;						// defaults to local IStaticTextAttributes setting
	virtual EllipsizeStyle		GetShouldEllipsize() const;									// defaults to local IStaticTextAttributes setting
	// Do we also need:			GetAlignment and GetUnderline? 
	//	Use of IStaticTextAttributes is so prevalent now that we just use these values (there are a few exceptions, noted in clients)

	// Sets local string, font and color values into underlying static text
	virtual void				SetTextValues(const PMString& textToDraw, const RealAGMColor& enabledTextColor, const RealAGMColor& disabledTextColor, const InterfaceFontInfo& fontInfo);
	virtual void				SetTextValue(const PMString& textToDraw);
	virtual void				SetTextValue(const RealAGMColor& enabledTextColor, const RealAGMColor& disabledTextColor);
	virtual void				SetTextValue(const InterfaceFontInfo& fontInfo);

	virtual void				TextValues_CommonInit();

	//If you override PreDrawGetText, you can call this convenience method to refetch the text/font/color data.		
	//	Is it really necessary to refetch everything? It depends on if your static text widget can be hilighted.
	//	Since hilite state typically affects font (plain vs bold) and color and font changes can affect how a string is ellipsized, yes. 
	//	In performance sensitive areas, it ought be possible to only trigger the refetch on hilite state changes, rather than on every Draw call.
	virtual void				UpdateAllTextValues();	 
	
	virtual dvaui::controls::UI_StaticText* Get_UI_StaticText() = 0;

	// Current brightness, if the brightness changes, need to update the color values
	float						fCurrBrightness;
private:
};


#pragma mark -
#pragma mark class DVStaticTextView
/**
	DVStaticTextView:
	Generic static text view widget, derived from drover's UI_StaticText

	VERY IMPORTANT: DVStaticTextView does not call the pre-CC viewPort based Draw method (since DVStaticTextView is based on the drover static text widget).

	DVStaticTextView also does not support custom background drawing, try to get your parent to draw it if possible. First determine if the background 
	is really still necessary, and if so the widget will need to derive from an OwnerDraw StaticTextView and override DrawBackground.

	If a StaticText-like widget needs to draw with AGM, or draw it's own text via PMDrawString, it should be based on qn OwnerDrawn StaticTextView.
	
	DVStaticTextView also does not support dynamic resizing at Draw time, there are a number of reasons for this. Widgets can resize in response
	to a variety of other valid triggers, DoPostCreate, ParentsVisibleStateChanged, AdaptToParentsSize, etc. (DoAutoAttach?)

	Note that a lot our old StaticTextViews used to "micro manage" the position of the text within their frame. This led to widespread copying of the Draw code
	in order to tweak the text location by a pixel or two. DVStaticTextView (via UI_StaticText) does not allow this, so the only alternatives at present are
	either: 1) repositioning the widget so that the standard location works, or 2) derive instead from one of the OwnerDraw variants below.
	So although you can override GetAdjustedTextFrame in DVStaticTextView, it only applies to the width used when ellipsizing the text.
	If demand necessitates we support text positioning we would have to add such support to drover's UI_StaticText. It might also be possible
	to achieve some positioning by applying a transform to the UI_StaticText while it is being drawn?

	You can draw (post text drawing) adornments in an override of DV_Draw.

	SHORTCOMINGS: DVStaticTextView/UI_StaticText doesnt do everything we need it to:
	
		1) Drover's UI_StaticText does ellipsizing, but the algorithm and options do not match the ones we uses ourselves.
				We are currently using drover ellipsizing code with mismatched options. 
				Longer term, I recommend adding the options we need to drawbot, it shouldn't be very difficult. 
				Drover's PathEllipsis is broken (saves first 8 chars - useless on a Mac) and sometimes their EndEllipsis will replace a single character like an M with an ellipsis!
			
		2) Drover's UI_StaticText does not have an equivalent for IStaticTextAttributes::GetConvertAmpersandsToUnderline.
				Drover widgets aparently have some mnemonic support, but we have not tried to use it here (would it apply to UI_StaticText, or only buttons, checkboxes, etc). 
				We are currently preprocessing the string to honor IStaticTextAttributes::GetConvertAmpersandsToUnderline before passing it to DVStaticTextView.
			
		3) DVStaticTextView does not honor IStaticTextAttributes::GetDrawUnderline.
				Drover's UI_StaticText does not support underlining, Drawbot has a utility - but we'll have to do it ourselves in a DV_Draw that augments UI_StaticText::UI_Draw.
				Several client widgets do use DV_Draw to draw a solid underline, but it's just a line, not an integral part of the text drawing. 
				I could do a similar thing here based on IStaticTextAttributes::GetDrawUnderline(), but have not.
			
		4) DVStaticTextView does not allow for a background fill color.
				Drover's UI_StaticText does not support setting a background color, we would have to subclass UI_StaticText to add this (as it needs to draw before UI_StaticText draws).
				Drover instead relyies on a parent widget to draw the background (usually at the window level), and this is working reasonably well at this point. 
				I'd like to avoid adding a background fill here.
					From what I can tell, background fill color for StaticTextView was used in list (and menu?) cells (but not tree nodes) to paint differents backgrounds for 
					selected(hilited) vs uncelected(unhilited) cells, as in:
						colors->GetRealAGMColor(bIsHilited ? kInterfaceHighLight : kInterfaceWhite, background);
					With all lists being converted to tree-based-lists, the tree node selection code seems to be working fine and the selected nodes are drawing the custom background, and
					DVStaticTextView just draws the text on top of that background without having to know about it. 
				
				The OwnerDraw variants can still draw a background (even this may not be necessary).
				If you think you need to draw a background in DVStaticTextView, please don't just hack one in, contact the UI_Arch team for guidance.
*/

class DV_WIDGET_DECL DVStaticTextView : public DVAbstractStaticTextView
{
	typedef DVAbstractStaticTextView inherited;
public:
	DVStaticTextView(IPMUnknown *boss);
	virtual ~DVStaticTextView();

	// Text is passed to the underlying UI_StaticText by the accompanying DVTextControlData implementation.
	//	and Font and color information is set at DoPostCreate/ParentsVisibleStateChanged (ui themes are likely to have been set properly by then)
	virtual void				DoPostCreate();
	virtual void				ParentsVisibleStateChanged(bool16 visible);
	
	// Default says true. Override it to say false, so that widget doesn't ask for text while creation.
	virtual bool16				IsTextAvailableWhileCreate();

	// Override to draw something *after* the underlying static text draws
	virtual void				DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;			 

	// Override if the text is not being updated by some other interface, and/or if other text parameters can change at Draw time.
	//	This PreDrawGetText does nothing. If overridden, collect necessary information and call SetTextValue(s)
	virtual void				PreDrawGetText();

protected:	
	virtual void				TextValues_CommonInit();

	virtual dvaui::controls::UI_StaticText* Get_UI_StaticText();
					
private:
  #if DEBUG
	// Making the old Draw method private here will cause an error in subclasses who call inherited::Draw. 
	void						Draw(IViewPort* viewPort, SysRgn updateRgn) {}
  #endif
	
};


#pragma mark -
#pragma mark class AbstractOwnerDrawnStaticTextView
/**
	AbstractOwnerDrawnStaticTextView:
	Common baseclass for owner drawn static text views - common code for AGM and Drawbot drawn
*/
class DV_WIDGET_DECL AbstractOwnerDrawnStaticTextView : public DVAbstractStaticTextView
{
	typedef DVAbstractStaticTextView inherited;
public:
	AbstractOwnerDrawnStaticTextView(IPMUnknown *boss);
	virtual ~AbstractOwnerDrawnStaticTextView();

	//Sets the mnemonic location and calls inherited::DV_Draw()
	virtual void				DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const;

	virtual void				PreDrawGetText(); // Updates all of the text values.

protected:
	virtual void 				GetBackgroundColor(RealAGMColor& backgroundColor) const;

	// Set local string, font, draw rect and color cache (called from PreDrawGetText)
	virtual void				SetTextValue(const PMString& textToDraw); // (called by DVTextControlData)
	virtual void				SetTextValue(const RealAGMColor& enabledTextColor, const RealAGMColor& disabledTextColor);
	virtual void				SetTextValue(const InterfaceFontInfo& fontInfo);

	virtual void				UpdateAllTextValues();	//if you override PreDrawGetText, you can call this convenience method to refetch the text/font/color/frame data. 

	virtual dvaui::controls::UI_StaticText* Get_UI_StaticText() {return nil;} //Owner drawn
	
protected:
	const PMString&				TextToDraw() const {return fTextToDraw;}
	const RealAGMColor&			TextColor() const {return IsEnabled() ? fEnabledTextColor : fDisabledTextColor;}
	const InterfaceFontInfo&	TextFontInfo() const {return fTextFontInfo;}
	const PMRect&				TextAdjustedFrame() const {return fTextAdjustedFrame;}
	void						SetTextAdjustedFrame(const PMRect& adjTextFrame) {fTextAdjustedFrame = adjTextFrame;}
	
private:
	// Local string, font, and color cache (set by PreDrawGetText, used in DV_DrawText)
	PMString			fTextToDraw;
	RealAGMColor		fEnabledTextColor;
	RealAGMColor		fDisabledTextColor;
	InterfaceFontInfo	fTextFontInfo;
	PMRect				fTextAdjustedFrame;
	
protected:
	// TextSettings
	//	From CStaticTextView - except they were just protected data members there
	void	DetermineBackgroundColorIDs();
	bool16	HasDeterminedBackgroundColorIDs() const {return fBGColorIDsLoaded;}
	void	SetHasDeterminedBackgroundColorIDs() {fBGColorIDsLoaded = kTrue;}
	
	void	SetBackgroundColorID(int32 bgColorID)  {fBGColorID = bgColorID;}
	int32	GetBackgroundColorID() const {return fBGColorID;}

	void	SetHiliteBGColorID(int32 hiliteBGColorID) {fHiliteBGColorID = hiliteBGColorID;}
	int32	GetHiliteBGColorID() const {return fHiliteBGColorID;}

private:
	bool16				fBGColorIDsLoaded;	
	int32				fBGColorID;
	int32				fHiliteBGColorID;
};

#pragma mark -
#pragma mark class DVOwnerDrawnStaticTextView
/**
	DVOwnerDrawnStaticTextView:
	Client subclass is responsible for drawing background (if any), text and post text adornments (if any)
*/
class DV_WIDGET_DECL DVOwnerDrawnStaticTextView : public AbstractOwnerDrawnStaticTextView
{
	typedef AbstractOwnerDrawnStaticTextView inherited;
public:
	DVOwnerDrawnStaticTextView(IPMUnknown *boss);
	virtual ~DVOwnerDrawnStaticTextView();

	virtual void				DV_Draw(dvaui::drawbot::Drawbot *drawbotP) const; // calls PreDrawGetText and drawing methods below

	virtual	void				ProcessRawTextString(PMString& rawString) const; //applies ShouldEllipsize and StripMenuAccelerators settings to raw string
				 
protected:
	// OwnerDraw methods:
	virtual void				DV_DrawBackground(dvaui::drawbot::Drawbot *drawbotP) const;			 
	virtual void				DV_PreDrawText(dvaui::drawbot::Drawbot *drawbotP) const;			 
	virtual void				DV_DrawText(dvaui::drawbot::Drawbot *drawbotP) const;			 
	virtual void				DV_PostDrawText(dvaui::drawbot::Drawbot *drawbotP) const;			 
};

#pragma mark -
#pragma mark class AGMOwnerDrawnStaticTextView
/**
	AGMOwnerDrawnStaticTextView:
	Client subclass is responsible for drawing background (if any), text and post text adornments (if any)
*/
class DV_WIDGET_DECL AGMOwnerDrawnStaticTextView : public AbstractOwnerDrawnStaticTextView
{
	typedef AbstractOwnerDrawnStaticTextView inherited;
public:
	AGMOwnerDrawnStaticTextView(IPMUnknown *boss);
	virtual ~AGMOwnerDrawnStaticTextView();

	// AGM based Drawing methods derived from the pre CC CStaticTextView
	virtual void				Draw(IViewPort* viewPort, SysRgn updateRgn);

protected:
	virtual void				GetAdjustedTextFrame(PMRect& adjustedTextFrame) const;

	// OwnerDraw methods:
	virtual void				DrawBackgroundFill(IViewPort* viewPort, SysRgn updateRgn);					  // called first, before text is drawn
	virtual void				PreDrawText(IViewPort* viewPort, SysRgn updateRgn);  // called before text is drawn 
	virtual void				DrawText(IViewPort* viewPort, SysRgn updateRgn);	  // draws the text
	virtual void				PostDrawText(IViewPort* viewPort, SysRgn updateRgn); // called after text is drawn
};


#endif
