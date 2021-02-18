//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDrawingStyle.h $
//  
//  Owner: EricM
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
#ifndef __IDrawingStyle__
#define __IDrawingStyle__


#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"

class IDataBase;
class IPMFont;
class IFontInstance;
class IWaxRenderData;
class ITextAdornmentData;
class IWaxRun;

class PMString;
class PMMatrix;
class PMPoint;

/**
	IDrawingStyle is the primary interface of character attribute summary data.
	Text attributes can be summarized into a kComposeStyleBoss object, which is a non-persistent
	summary of every text attribute applied to some text. IDrawingStyle lists most, but not all
	character attributes: font, pointsize, color, etc.
	IDrawingStyle should be considered a "read-only" interface because the set operations have no
	impact beyond this data interface. It does not apply through to the text that this interface derived from.
	The text attributes themselves are the primary setters of the data.
	@see IComposeScanner
	@see kComposeStyleBoss
	@see ICompositionStyle
	@see IHyphenationStyle
	@see IJustificationStyle
	@ingroup text_comp_style
*/
class IDrawingStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IDRAWINGSTYLE };

		/**	CapitalizeMode.
			Normal,
			lowercase->small uppercase mapping,
			lowercase->uppercase mapping,
			lowercase & uppercase -> small uppercase mapping.
		*/
		enum CapitalizeMode { kCapNormal = 0, kCapSmallLowercase, kCapAll, kCapSmallEverything };

		/**	PositionMode.
			Mutually exclusive positioning of glyphs.
			kPosSuperior = opentype superscript feature.
			kPosInferior = opentype subscript feature.
			kPosNumerator, kPosDenominator are opentype features only.
		*/
		enum PositionMode { kPosNormal = 0, kPosSuperscript, kPosSubscript,
						kPosSuperior, kPosInferior, kPosNumerator, kPosDenominator };

		/**	UnderlineMode.
			May be extended in the future.
		*/
		enum UnderlineMode { kUnderlineNone = 0, kUnderlineSingle };

		/**	CharacterHang.
			Used in Japanese to place different sized characters relative to each other.
		*/
		enum CharacterHang { kHangBaseline = 0, kHangEmCenter, kHangEmBottom, kHangEmTop, kHangICFBottom, kHangICFTop };

		/**	PositionIndicator.
			Used by some calculated text (page numbers, variables, bullets & numbering).
		*/
		enum PositionIndicator { kDataPosition_ThisPage = 0, kDataPosition_PreviousPage, kDataPosition_NextPage, kDataPosition_TextVariable,
#ifdef ID_DEPRECATED
						kDataPosition_This = kDataPosition_ThisPage, kDataPosition_Previous = kDataPosition_PreviousPage, kDataPosition_Next = kDataPosition_NextPage
#endif
		};

		/** OpenType Positioning Form.
			Ties to the opentype features that control position-dependent glyphs (especially for cursive scripts like Arabic).
			kOTPosForm_Off = no features.
			kOTPosForm_Auto = automatically generates the 4 positional features listed below based on the underlying text.
			kOTPosForm_Initial = beginning of word form.
			kOTPosForm_Medial = middle of word form.
			kOTPosForm_Final = end of word form.
			kOTPosForm_Isolated = by itself (one character word) form.
		*/
		enum OTPositioningForm { kOTPosForm_Off, kOTPosForm_Auto, kOTPosForm_Initial, kOTPosForm_Medial, kOTPosForm_Final, kOTPosForm_Isolated };

		/**
		Query for the IFontInstance.
		@param vertical specifies whether you wish the horizontal or vertical instance.
		*/
		virtual IFontInstance* QueryFontInstance(bool16 vertical) const = 0;

		/**
		Query for the IPMFont.  IPMFont does not specify a writing direction or pointsize, just the font object.
		*/
		virtual IPMFont* QueryFont() const = 0;

		/** 	Is the referred-to font considered missing?
		*/
		virtual bool16 IsFontMissing() const = 0;

		/**
		Does the referred-to font have the multiple master optical size axis? This is only special because the optical size
		can be set to match the pointsize, giving the optimal font appearance.
		*/
		virtual bool16 HasMMOpticalSize() const = 0;

		/**
		Set the glyph-specific data for the non-representable character.
		Only used in special cases where the font has glyphs wanted without associated unicode character values.
		*/
		virtual void SetSpecialGlyph(const char* name, Text::GlyphID glyph = kInvalidGlyphID) = 0;

		/**
		If the underlying character didn't have a unicode representation, this will return the expected glyph.
		*/
		virtual Text::GlyphID GetSpecialGlyph() const = 0;		// figures out glyphid for this font

		/** Set the point size.
		*/
		virtual void SetPointSize(PMReal p) = 0;

		/**	Get the point size.
		*/
		virtual PMReal GetPointSize() const = 0;

		/**	Set the skew angle.
		*/
		virtual void SetSkewAngle(PMReal p) = 0;
		/**	Get the skew angle.
		*/
		virtual PMReal GetSkewAngle() const = 0;

		/**
		Returns calculated font matrix (includes super/subscript, h/v scale only).
		@param fontMatrix is set the the calculated font matrix.
		*/
		virtual void GetScaledFontMatrix(PMMatrix * fontMatrix) const = 0;

		/**
		Returns matrix you can concat with scaled font matrix to get final font matrix.
		@param fontMatrix is set the the font matrix.
		@param vertical specifies the primary writing direction.
		*/
		virtual void GetUnScaledFinalFontMatrix(PMMatrix * fontMatrix, bool16 vertical) const = 0;

		/**
		Returns final font matrix used to draw glyphs.
		NOTE: origin of matrix = glyph origin (left edge/Roman baseline), which means center-based calculations
		like free rotation and shatai must calculate the glyph center before and after these transformations
		to find out where to move the glyph location.
		@param fontMatrix is set the the final font matrix.
		*/
		virtual void GetFinalFontMatrix(PMMatrix * fontMatrix, bool16 vertical) const = 0;

		/**
		Fonts are divided into families, and each family has a separate record in an InDesign document.
		@param u is a font UID refering to one of these IFontFamily objects.
		*/
		virtual void SetFontUID(UID u) = 0;

		/**	Get the font family UID.
		*/
		virtual UID GetFontUID() const = 0;

		/**
		In addition to the font family, fonts have style names.
		It would appear as "Bold" or "Roman" or "" or "Semibold Condensed" for example.
		@param name is the font style name.
		*/
		virtual void SetFontStyleName(const PMString& name) = 0;

		/**	Get the font style name.
		*/
		virtual const PMString& GetFontStyleName() const = 0;

		/**
		The font family UID and font style name are combined to refer to a specific font by postscript name.
		@return The actually used postscript font name is returned.
		*/
		virtual const PMString& GetPostscriptFontName() const = 0;

		/**
		Multiple master fonts have a vector of 16/16 fixed point numbers that specify the
		values of each multiple master axis.
		@param num is number of values in the buffer.
		@buffer is the array of fixed point axis values.
		*/
		virtual void SetMMAxes(int32 num, const Fixed *buffer) = 0;

		/**
		Get the vector of axis values. May be nil. The number of elements in the vector
		is from font->GetNumDesignAxes()
		*/
		virtual const Fixed* GetMMAxes() const = 0;

		/**
		Sets the scale factor in the x direction
		*/
		virtual void SetGlyphScaleX(PMReal scale) = 0;
		/**
		Sets the scale factor in the y direction. This is different from setting the pointsize larger because larger pointsizes
		affect a number of different calculations (leading, optical sizes, etc) but the y scale does not.
		*/
		virtual void SetGlyphScaleY(PMReal scale) = 0;

		/**
		This is the desired glyph scale set in the justification dialog.
		The user may specify scaling in the x & y direction, but the user may also specify a desired glyph scale in the
		justification dialog.
		*/
		virtual void SetDesiredGlyphScale(PMReal xscale) = 0;

		/**
		Returns the product of both the user's x-scale and the desired glyph scale.
		*/
		virtual PMReal GetXScale() const = 0;

		/** Returns the specified y-scale.
		*/
		virtual PMReal GetYScale() const = 0;

		/**
		Returns only the user's x-scale and NOT the desired glyph scale.
		*/
		virtual PMReal GetXScaleOnly() const = 0;

		/**
		Sets the leading value. Values less than zero are considered "auto".
		*/
		virtual void SetLeading(PMReal abs) = 0;

		/**
		Sets the auto-leading factor. Leading = factor * pointsize.
		*/
		virtual void SetAutoLead(PMReal factor) = 0;

		/**
		Gets the specified leading value: either auto or fixed.
		*/
		virtual PMReal GetLeading() const = 0;

		/** Returns the auto leading scale factor.
		*/
		virtual PMReal GetAutoLead() const = 0;

		/** Is auto-leading specified?
		*/
		virtual bool16 UseAutoLeading() const = 0;

		/** Get the baseline shift.
		*/
		virtual PMReal GetBaseLineShift() const = 0;

		/** Set the baseline shift.
		*/
		virtual void SetBaseLineShift(PMReal r) = 0;

		/** Character hang for Japanese composition.
		kHangBaseline, kHangEmCenter, kHangEmBottom, kHangEmTop, kHangICFBottom, kHangICFTop.
		*/
		virtual CharacterHang GetCharacterHang() const = 0;

		/** Character hang for Japanese composition.
		*/
		virtual void SetCharacterHang(CharacterHang b) = 0;

		/** OpenType positioning form.
		kOTPosForm_Off, kOTPosForm_Auto, kOTPosForm_Initial, kOTPosForm_Medial, kOTPosForm_Final, kOTPosForm_Isolated.
		corresponds to: 'init', 'medi', 'fina', 'isol'
		*/
		virtual OTPositioningForm GetOTPositioningForm() const = 0;

		/** enType positioning form.
		*/
		virtual void SetOTPositioningForm(OTPositioningForm form) = 0;

		/**	Get page number position.
		kDataPosition_ThisPage = use the current page. kDataPosition_PreviousPage = previous page.
		kDataPosition_NextPage	 = next page.
		*/
		virtual PositionIndicator GetPageNumberPosition() const = 0;

		/** Set page number position.
		@param pi can be kDataPosition_ThisPage, kDataPosition_PreviousPage, or kDataPosition_NextPage	 = next page.
		*/
		virtual void SetPageNumberPosition(PositionIndicator pi) = 0;

		/**
		Returns the calculated offset for the baseline (includes baseline shift, ILG shift, super/subscript, etc.)
		*/
		virtual PMReal GetEffectiveBaseline() const = 0;

		/** Get color rendering object for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual UID GetColorUID(bool16 stroke) const = 0;

		/** Set color rendering object for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetColorUID(bool16 stroke, UID newColor) = 0;

		/** Set tint percent for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetTint(bool16 stroke, PMReal tint) = 0;

		/** Get tint percent for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMReal GetTint(bool16 stroke) const = 0;

		/** Set overprint for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetOverprint(bool16 stroke, bool16 over) = 0;

		/** Get overprint for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual bool16 GetOverprint(bool16 stroke) const = 0;

		/** Gradient hilite angle for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetHiliteAngle(bool16 stroke, PMReal v) = 0;

		/** Gradient hilite angle for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMReal GetHiliteAngle(bool16 stroke) const = 0;

		/** Gradient hilite length for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetHiliteLength(bool16 stroke, PMReal v) = 0;

		/** Gradient hilite length for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMReal GetHiliteLength(bool16 stroke) const = 0;

		/** Gradient angle for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetGradientAngle(bool16 stroke, PMReal angle) = 0;

		/** Gradient angle for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMReal GetGradientAngle(bool16 stroke) const = 0;

		/** Gradient length for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetGradientLength(bool16 stroke, PMReal length) = 0;

		/** Gradient length for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMReal GetGradientLength(bool16 stroke) const = 0;

		/** Gradient center for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual void SetGradientCenter(bool16 stroke, const PMPoint& center) = 0;

		/** Gradient center for stroke or fill.
		@param stroke is kTrue from stroke, kFalse for fill.
		*/
		virtual PMPoint GetGradientCenter(bool16 stroke) const = 0;

		/** The system sets the database when creating the kComposeStyleBoss.
		Don't call this method.
		*/
		virtual void SetDataBase(IDataBase *db) = 0;

		/** Get the database that these attributes came from.
		*/
		virtual IDataBase* GetDataBase() const = 0;

		/** Is the text outlined?
		*/
		virtual bool16 IsOutlined() const = 0;

		/** What is the text outline width?
		@param width is the line weight of the text's outline.
		*/
		virtual void SetOutlineWidth(PMReal width) = 0;

		/** What is the text outline width?
		*/
		virtual PMReal GetOutlineWidth() const = 0;

		/** What is the text outline miter limit?
		@param miterLimit - the miter limit of the text's outline.
		*/
		virtual void SetMiterLimit(PMReal miterLimit) = 0;

		/** What is the text outline miter limit?
		*/
		virtual PMReal GetMiterLimit() const = 0;

		/** What is the text stroke aglignment?
		@param align - the text's stroke alignment.
		*/
		virtual void SetStrokeAlignment(int32 align) = 0;

		/** What is the text stroke alignment?
		*/
		virtual int32 GetStrokeAlignment() const = 0;

		/** What is the text outline join?
		@param join - the text's outline join.
		*/
		virtual void SetOutlineJoin(int32 join) = 0;

		/** What is the text outline join?
		*/
		virtual int32 GetOutlineJoin() const = 0;

		/** Set underline mode. This is only On/Off actually. the enum names is a historical misnomer.
		Actually, the stroke style is specified in the kTextAttrCharUnderlineTypeBoss text attribute.
		Perhaps we will have the idea of skipping descenders specified here some day.
		*/
		virtual void SetUnderlineMode(UnderlineMode underlineMode) = 0;

		/** Get Underline mode.
		*/
		virtual UnderlineMode GetUnderlineMode() const = 0;

		/** Set the position mode of the glyphs.
		kPosNormal has no affect.
		kPosSuperscript scales and shifts the glyphs up. 	kPosSubscript scales and shifts the glyphs down.
		kPosSuperior applies the opentype 'sups' feature. kPosInferior applies the opentype 'sinf' AND 'subs'.
		kPosNumerator applies opentype 'numr'. kPosDenominator applies opentype 'deno'
		*/
		virtual void SetPositionMode(PositionMode position) = 0;

		/** Get the position mode of the glyphs.
		*/
		virtual PositionMode GetPositionMode() const = 0;

		/** Is strike through enabled?
		*/
		virtual void SetStrikethruFlag(bool16 strikethru) = 0;

		/** Is strike through enabled?
		*/
		virtual bool16 GetStrikethruFlag() const = 0;

		/** Set the capitalization mode.
		@param cm can be:
		kCapNormal has no affect. kCapSmallLowercase draws lowercase letters as small capitals.
		kCapAll draws all letters as capitals. kCapSmallEverything will draw both uppercase and lowercase letters
		as small capitals, but is only supported by opentype fonts that have the 'c2sc' feature currently.
		*/
		virtual void SetCapitalsMode(CapitalizeMode cm) = 0;

		/** Get the capitalization mode.
		*/
		virtual CapitalizeMode GetCapitalsMode() const = 0;

		/** Cached space glyph.
		*/
		virtual Text::GlyphID GetSpaceGlyph() const = 0;

		/** Cached width of the space glyph.
		*/
		virtual PMReal GetSpaceWidth() const = 0;

		/** Cached Em space width.
		*/
		virtual PMReal GetEmSpaceWidth(bool16 vertical) const = 0;

		/** Cached En space width.
		*/
		virtual PMReal GetEnSpaceWidth(bool16 vertical) const = 0;

		/** Cached width of the hyphen glyph.
		*/
		virtual PMReal GetHyphenWidth() const = 0;

		/** Do both of these IDrawingStyles share the drawing-specific data such that they can be kerned?
		For example, kerning cannot cross pointsize and font changes. But we do allow kerning to cross color changes.
		@param other is an adjacent IDrawingStyle that we are kerning against.
		*/
		virtual bool16 CanSimpleKernWith(const IDrawingStyle* other, bool16 vertical) const = 0;

		/** Do both of these IDrawingStyles share the drawing-specific data such that they can share the same opentype features?
		For example, opentype features cannot cross pointsize and font changes. But we do allow changes to cross color and underline
		changes.
		@param other is an adjacent IDrawingStyle that we are composing next to.
		*/
		virtual bool16 CanDoOpenTypeFeaturesAcross(const IDrawingStyle* other, bool16 vertical) const = 0;

		/** Do both of these IDrawingStyles share the drawing-specific data such that they can share the same wax run?
		For example, pointsize, color, and font will create new wax runs. Page number position will not.
		@param other is an adjacent IDrawingStyle that we are building wax next to.
		*/
		virtual bool16 CanShareWaxRunWith(const IDrawingStyle* other) const = 0;

		/** Are the glyphs forced vertical?
		*/
		virtual bool16 GetForceVerticalGlyphs() const = 0;

		/** Force the glyphs to be vertical.
		*/
		virtual void SetForceVerticalGlyphs(bool16 b) = 0;

		/**
		Add the adornment specified by the text attribute  to this interface.
		*/
		virtual void AddTextAdornment(ClassID attrID, ClassID adornmentID, ITextAdornmentData *data) = 0;

		/**
		Get one text adornment's data for writing. This method assumes you will modify the data, which is much
		slower because it makes a copy.
		*/
		virtual void GetTextAdornment(ClassID attrID, ClassID *adornmentID, ITextAdornmentData **data) = 0;

		/**
		Read one text adornment's data. This method assumes you won't modify the data, which is much more
		efficient because it won't make copies.
		*/
		virtual void GetTextAdornment(ClassID attrID, ClassID *adornmentID, const ITextAdornmentData **data) const = 0;

		/**
		Copy text attribute information into IWaxRun interfaces. Wax is the term for composed text data.
		*/
		virtual void FillOutRenderData(IWaxRenderData* data, bool16 vertical) const = 0;

		/**
		Add the adornments specified by the text attributes  to the IWaxRun interface.
		*/
		virtual void AddAdornments(IWaxRun *waxRun) const = 0;

		/**
		The EmBox and ICFBox are font metrics specific to japanese fonts.
		*/
		virtual PMReal GetStyleEmBoxTop(bool16 verticalGlyphs, bool16 usePointSizeNotScale = kFalse) const = 0;
		/**
		The EmBox and ICFBox are font metrics specific to japanese fonts.
		*/
		virtual PMReal GetStyleEmBoxBottom(bool16 verticalGlyphs, bool16 usePointSizeNotScale = kFalse) const = 0;
		/**
		The EmBox and ICFBox are font metrics specific to japanese fonts. (ICF=Ideographic Character Face)
		@see http://partners.adobe.com/asn/tech/type/opentype/appendices/baselinetags.jsp#icfbox
		*/
		virtual PMReal GetStyleICFBoxTop(bool16 verticalGlyphs, bool16 usePointSizeNotScale = kFalse) const = 0;
		/**
		The EmBox and ICFBox are font metrics specific to japanese fonts. (ICF=Ideographic Character Face)
		@see http://partners.adobe.com/asn/tech/type/opentype/appendices/baselinetags.jsp#icfbox
		*/
		virtual PMReal GetStyleICFBoxBottom(bool16 verticalGlyphs, bool16 usePointSizeNotScale = kFalse) const = 0;

		/** Get the WritingScript()
		*/
		virtual int32 GetWritingScript() const = 0;

		/**
		The Macintosh has always supported a dozen or so mathematical symbols in every font by
		substituting the "Symbol" font behind the scenes. This reproduces that behavior.
		We do it on both platforms (starting in CS3) for consistency.
		*/
		virtual void SetForSymbolHack() = 0;
};

#endif
	// __IDrawingStyle__

