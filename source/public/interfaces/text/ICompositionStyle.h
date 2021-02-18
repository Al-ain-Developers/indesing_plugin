//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ICompositionStyle.h $
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
//  
//  This object holds information for composition.
//  Attributes set this data, and composition reads it.
//  
//========================================================================================

#pragma once
#ifndef __ICompositionStyle__
#define __ICompositionStyle__


#include "IPMUnknown.h"
#include "CTextEnum.h"
#include "TextID.h"

#include "IRunInStylesUtils.h"

#define kCTOT_NoChoiceIndex -1

const double kAutoKernMagicNumber = 1.0e8;

class TabStop;
class TabStopTable;
class RunInStyleList;
class RunInGrepStyleList;
class RunInLineStyleList;


/** One of the interfaces providing text attribute data combined into a single multi-interface structure.
	Mostly concerns paragraph level attributes, but not completely.
	@see IDrawingStyle, IHyphenationStyle, IJustificationStyle.
	@ingroup text_comp_style
*/
class ICompositionStyle : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICOMPOSITIONSTYLE };

		/** Text Alignment. */
		enum TextAlignment {
			kTextAlignLeft = 0,
			kTextAlignCenter,
			kTextAlignRight,
			kTextAlignJustifyFull,
			kTextAlignJustifyLeft,
			kTextAlignJustifyCenter,
			kTextAlignJustifyRight,
			kTextAlignAuto,              // only warichu in 2.0
			kTextAlignToBinding,
			kTextAlignAwayBinding,
			kTextAlignLastValue = kTextAlignAwayBinding
			};

		/** Left to Right / Right to Left paragraph direction */
		enum ParagraphDirection {
			kParagraphDirLTR = 0,
			kParagraphDirRTL
			};

		/** Paragraph Rule Mode. */
		enum ParagraphRuleMode {
			kRule_None = 0,		  // obsolete, but left in for conversion purposes
			kRule_ColumnWidth,
			kRule_TextWidth
			};

		/** Balance Line Preference. */
		enum BalanceLinePreference {
			kBalanceLine_Off,			// no line balancing ( matches kFalse for conversion )
			kBalanceLine_VeeShape,		// last line preferred shorter ( matches kTrue for conversion )
			kBalanceLine_Equal,			// completely balanced
			kBalanceLine_Pyramid		// last line preferred longer
			};

		/** Span Columns Type. */
		enum SpanColumnsTypeOptions {
			kSingleColumn,			// single column paragraph
			kSpanColumn,			// paragraph spans columns
			kSplitColumn			// paragraph splits the column
		};

		/** Paragraph Border and Shading Width. */
		enum ParagraphBorderShadingWidth {			
			kBorderShading_ColumnWidth,	// column width
			kBorderShading_TextWidth	// text width
		};

		/** Paragraph Border and Shading Top Origin. */
		enum ParagraphBorderShadingTopOrigin {
			kBorderShading_AscentTopOrigin,		// ascent top origin
			kBorderShading_BaselineTopOrigin,	// baseline top origin
			kBorderShading_LeadingTopOrigin,	// leading top origin
			kBorderShading_emBoxTopOrigin,		// em box top origin
			kBorderShading_CapHeightTopOrigin,	// cap height top origin
			kBorderShading_xHeightTopOrigin,	// x height top origin
			kBorderShading_EmBoxCenterTopOrigin	// em box center top origin
		};

		/** Paragraph Border and Shading Bottom Origin. */
		enum ParagraphBorderShadingBottomOrigin {
			kBorderShading_DescentBottomOrigin,		// descent bottom origin
			kBorderShading_BaselineBottomOrigin,	// baseline bottom origin
			kBorderShading_EmBoxBottomOrigin,		// em box bottom origin
			kBorderShading_EmBoxCenterBottomOrigin	// em box center bottom origin
		};

		/** Stroke Join Type. */
		enum StrokeJoinType {
			kStroke_MiterJoin,
			kStroke_RoundJoin,
			kStroke_BevelJoin
		};

		/** Stroke Cap Type. */
		enum StrokeCapType {
			kStroke_ButCap,
			kStroke_RoundCap,
			kStroke_ProjectingCap
		};

		/**
			Class containing the  UID and ClassID which identifies the Stroke Type
		*/
		class StrokeType
		{
		public:
			typedef base_type data_type;

			StrokeType() : fClassID(kInvalidClass), fUID(kInvalidUID) {}
			StrokeType(ClassID theClassID, UID theUID) : fClassID(theClassID), fUID(theUID) {}
			bool16 operator== (const StrokeType &other) { return fClassID == other.fClassID && fUID == other.fUID; }
			bool16 operator!= (const StrokeType &other) { return !(*this == other); }
			void operator= (const StrokeType &other) { fClassID = other.fClassID; fUID = other.fUID; }

			ClassID		fClassID;
			UID			fUID;
		};


			/** @return the ClassID of the service that provides the composition
				algorithm for this paragraph */
		virtual ClassID GetComposer() const = 0;
			/** Set ClassID of composer */
		virtual void SetComposer(ClassID algo) = 0;

			/** @return the ClassID of the service that provides the kerning
				algorithm for this character run */
		virtual ClassID GetKerningMethod() const = 0;
			/** set ClassID of kerning method */
		virtual void SetKerningMethod(ClassID algo) = 0;

			/** if value == kAutoKernMagicNumber, then use the algorithm specified by GetKerningMethod()
				@return the kern pair for this run. */
		virtual PMReal GetPairKern() const = 0;
			/** set pair kern value.
				@see GetPairKern */
		virtual void SetPairKern(PMReal amt) = 0;

			/**  Should ligatures be used?
			*/
		virtual bool16 UseLigatures() const = 0;
			/**  Set ligature state
			*/
		virtual void SetLigaturesOn(bool16 on) = 0;

			/** Add the OpenType feature specified.
			@see http://partners.adobe.com/asn/tech/type/opentype/feattags.jsp
			@param feature must be a pointer to a buffer of 4 characters representing an opentype feature. E.g. "smcp", "kern".
			@param choiceIndex may be used to specify an alternate choice for certain opentype features. E.g. "aalt".
			*/
		virtual void AddOpenTypeFeature(const char *feature, int32 choiceIndex = kCTOT_NoChoiceIndex) = 0;

			/** Clear the opentype feature specified by the tag.
			@see http://partners.adobe.com/asn/tech/type/opentype/feattags.jsp
			@param feature must be a pointer to a buffer of 4 characters representing an opentype feature. E.g. "smcp", "kern"
			*/
		virtual void ClearOpenTypeFeature(const char *feature) = 0;

			/** Get how many opentype features are applied to this text.
			*/
		virtual int32 CountOpenTypeFeatures() const = 0;

			/** Get the Nth applied opentype feature.
			@see http://partners.adobe.com/asn/tech/type/opentype/feattags.jsp
			@param choiceIndex if non-nil will be set to the choice index of the Nth feature.
			@return A pointer to a buffer of 4 characters representing the Nth opentype feature. E.g. "smcp", "kern".
			*/
		virtual const char* GetNthOpenTypeFeature(int32 n, int32 *choiceIndex = nil) const = 0;

			/** Is the specified feature applied?
			@see http://partners.adobe.com/asn/tech/type/opentype/feattags.jsp
			@param feature must be a pointer to a buffer of 4 characters representing an opentype feature. E.g. "smcp", "kern"
			*/
		virtual bool16 IsOpenTypeFeatureApplied(const char *feature) const = 0;

			/** Get whether this text should be allowed to break.
			*/
		virtual bool16 GetNoBreak() const = 0;

			/** Set whether this text should be allowed to break.
			*/
		virtual void SetNoBreak(bool16 b) = 0;

			/** Get the left indent.
			*/
		virtual PMReal IndentLeftBody() const = 0;

			/** Get the right indent.
			*/
		virtual PMReal IndentRightBody() const = 0;

			/** Get the last line right indent.
			*/
		virtual PMReal IndentRightLast() const = 0;

			/** Get the first line left indent.
			*/
		virtual PMReal IndentLeftFirst() const = 0;

			/** Set the left indent.
			*/
		virtual void SetIndentLeftBody(PMReal a) = 0;

			/** Set the right indent.
			*/
		virtual void SetIndentRightBody(PMReal a) = 0;

			/** Set the last line right indent.
			*/
		virtual void SetIndentRightLast(PMReal a) = 0;

			/** Set the first line left indent.
			Left indent + first line left indent must be non-negative.
			*/
		virtual void SetIndentLeftFirst(PMReal a) = 0;

			/** Get the paragraph alignment.
			*/
		virtual ParagraphDirection GetParagraphDirection() const = 0;

			/** Set the paragraph alignment.
			*/
		virtual void SetParagraphDirection(ParagraphDirection dir) = 0;

			/** Get the paragraph alignment.
			*/
		virtual TextAlignment GetParagraphAlignment() const = 0;

			/** Set the paragraph alignment.
			*/
		virtual void SetParagraphAlignment(TextAlignment dq) = 0;

			/** Get how a justified line with only one word on it should align.
			*/
		virtual TextAlignment GetSingleWordAlign() const = 0;

			/** Set how a justified line with only one word on it should align.
			*/
		virtual void SetSingleWordAlign(TextAlignment dq) = 0;

			/** Get whether the paragraph should balance its lines.
			Paragraph composer only. Ragged paragraph alignments only.
			*/
		virtual BalanceLinePreference BalanceLineLengths() const = 0;

			/** Set whether the paragraph should balance its lines.
			*/
		virtual void SetBalanceLineLengths(BalanceLinePreference b) = 0;

			/** Get whether to ignore edge alignment
			*/
		virtual bool16 GetIgnoreEdgeAlignment() const = 0;

			/** Set whether to ignore edge alignment
			*/
		virtual void SetIgnoreEdgeAlignment(bool16 ignore) = 0;

			/** Set how many lines the dropcap should knockout.
			*/
		virtual void SetDropCapLines(int16 numLines) = 0;

			/** Set how many characters should drop in the dropcap.
			*/
		virtual void SetDropCapChars(int16 numChars) = 0;

			/** Set details about how the dropcap glyphs are scaled/positioned
			*/
		virtual void SetDropCapDetail(Text::DropCapDetailedSettings settings) = 0;

			/** Get the dropcap lines & characters settings.
			*/
		virtual Text::DropCapDetailedSettings GetDropCapInfo(int16 *elems, int16 *lines) const = 0;

			/** Get amount of space to add before this paragraph.
			*/
		virtual PMReal SpaceBefore() const = 0;

			/** Get amount of space to add after this paragraph.
			*/
		virtual PMReal SpaceAfter() const = 0;
    
            /** Get amount of same para spacing.
             */
        virtual PMReal SameParaSpacing() const = 0;
             
			/** Set amount of space to add before this paragraph.
			*/
		virtual void SetSpaceBefore(PMReal a) = 0;

			/** Set amount of space to add after this paragraph.
			*/
		virtual void SetSpaceAfter(PMReal a) = 0;
    
            /** Set amount of space to add after this paragraph.
             */
        virtual void SetSameParaSpacing(PMReal a) = 0;
    
 			/** Set the break before mode.
			*/
		virtual void SetBreakBeforeMode(Text::StartBreakLocation breakBeforeMode) = 0;

			/** Get the break before mode.
			*/
		virtual Text::StartBreakLocation GetBreakBeforeMode() const = 0;

			/** Get where this paragraph should start.
			*/
		virtual Text::StartBreakLocation GetStartLocation() const = 0;

			/** Set where this paragraph should start.
			*/
		virtual void SetStartLocation(Text::StartBreakLocation startLocation) = 0;

			/** Set whether this paragraph has any keeps enabled.
			Keep all together or keep first/last N lines together, but not keep with next.
			*/
		virtual void SetKeepLines(bool16 keepTogether) = 0;

			/** Get whether this paragraph has any keeps enabled.
			Keep all together or keep first/last N lines together, but not keep with next.
			*/
		virtual bool16 GetKeepLines() const = 0;

			/** Set whether this paragraph has keep whole paragraph together enabled.
			*/
		virtual void SetKeepTogether(bool16 keepTogether) = 0;

			/** Get whether this paragraph has keep whole paragraph together enabled.
			*/
		virtual bool16 GetKeepTogether() const = 0;

			/** Set how many lines after this paragraph should be kept with the last line of this paragraph.
			*/
		virtual void SetKeepWithNextNLines(int16 nLines) = 0;

			/** Get how many lines after this paragraph should be kept with the last line of this paragraph.
			*/
		virtual int16 GetKeepWithNextNLines() const = 0;

			/** Set how many lines at the start of the paragraph to keep together.
			*/
		virtual void SetKeepFirstNLinesTogether(int16 nLines) = 0;

			/** Get how many lines at the start of the paragraph to keep together.
			*/
		virtual int16 GetKeepFirstNLinesTogether() const = 0;

			/** Set how many lines at the end of the paragraph to keep together.
			*/
		virtual void SetKeepLastNLinesTogether(int16 nLines) = 0;

			/** Get how many lines at the end of the paragraph to keep together.
			*/
		virtual int16 GetKeepLastNLinesTogether() const = 0;

			/** Set the entire tab ruler.
			*/
		virtual void SetTabRuler(const TabStopTable &tabs) = 0;

			/** Get the applied tab ruler.
			*/
		virtual const TabStopTable& GetTabRuler() const = 0;

			/** Get the tab stop position after the offset.
			@param offset should be the distance from the frame edge.
			*/
		virtual TabStop GetTabStopAfter(PMReal offset) const = 0;

			/** Get paragraph rule enabled mode.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual bool16 GetParaRuleMode(bool16 above, ICompositionStyle::ParagraphRuleMode *mode) const = 0;

			/** Set paragraph rule mode.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleMode(bool16 above, ICompositionStyle::ParagraphRuleMode mode) = 0;

			/** Set paragraph rule enabled state.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleOn(bool16 above, bool16 onOff) = 0;

			/** Set paragraph rule color.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleColor(bool16 above, UID color) = 0;

			/** Set paragraph rule tint.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleTint(bool16 above, PMReal tint) = 0;

			/** Set paragraph rule overprint state.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleOverprint(bool16 above, bool16 onOff) = 0;

			/** Set paragraph rule stroke weight.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleStroke(bool16 above, PMReal weight) = 0;

			/** Set paragraph rule stroke type.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleStrokeType(bool16 above, ICompositionStyle::StrokeType type) = 0;

			/** Get paragraph rule draw information.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual bool16 GetParaRuleDraw(bool16 above, UID *pColor, PMReal *tint, bool16 *overprint, PMReal *weight,
									   ICompositionStyle::StrokeType *type, UID *gapColor, PMReal *gapTint, bool16 *gapOverprint) const = 0;

			/** Set paragraph rule gap color.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleGapColor(bool16 above, UID color) = 0;

			/** Set paragraph rule gap tint.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleGapTint(bool16 above, PMReal tint) = 0;

			/** Set paragraph rule gap overprint.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleGapOverprint(bool16 above, bool16 onOff) = 0;

			/** Set paragraph rule left indent.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleIndentL(bool16 above, PMReal left) = 0;

			/** Set paragraph rule right indent.
			@param above kTrue if rule above, kFalse for rule below.
			*/
		virtual void SetParaRuleIndentR(bool16 above, PMReal right) = 0;

			/** Set paragraph rule offset.
			@param above kTrue if rule above, kFalse for rule below.
			@param offset positive is down for rule below, up for rule above
			*/
		virtual void SetParaRuleOffset(bool16 above, PMReal offset) = 0;

			/** Get the paragraph rule position data.
			@return kTrue if the rule is "On".
			*/
		virtual bool16 GetParaRulePosition(bool16 above, PMReal *left, PMReal *right, PMReal *offset) const = 0;

			/** set whether the paragraph rule is to stay in the text frame.
			@para keepInFrame kTrue if keep the rule in the frame.
			*/
		virtual void SetKeepParaRuleAboveInFrame(bool16 keepInFrame) = 0;
			/** get whether the paragraph rule is to stay in the text frame.
			@return kTrue if keep the rule in the frame.
			*/
		virtual bool16 GetKeepParaRuleAboveInFrame() const = 0;

			/** are there nested styles, nested line based styles, or grep styles on this text?
			*/
		virtual bool16 HasAutomaticStyling() const = 0;

			/** Set the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual void SetRunInStyleList(const RunInStyleList& list) = 0;

			/** Returns the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual const RunInStyleList& GetRunInStyleList() const = 0;

			/** Set the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual void SetRunInGrepStyleList(const RunInGrepStyleList& list) = 0;

			/** Returns the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual const RunInGrepStyleList& GetRunInGrepStyleList() const = 0;

			/** Set the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual void SetRunInLineStyleList(const RunInLineStyleList& list) = 0;

			/** Returns the run-in style applied to this run of characters (usually paragraph).
			*/
		virtual const RunInLineStyleList& GetRunInLineStyleList() const = 0;

			/** Get the type of paragraph span.
			@return the type of paragraph span
			*/
		virtual SpanColumnsTypeOptions GetSpanColumnType() const = 0;

			/** Set the type of paragraph span.
			@param type the type of paragraph span
			*/
		virtual void SetSpanColumnType(SpanColumnsTypeOptions type) = 0;

			/** Get the number of columns the paragraph spans or splits.
			If type is kSpanColumn and column count is equal to 1 means "all"
			@return the number of columns the paragraph spans or splits
			*/
		virtual int16 GetSpanSplitColumnCount() const = 0;

			/** Set the number of columns the paragraph spans or splits.
			If type is kSpanColumn and column count is equal to 1 means "all"
			@param count the number of columns the paragraph spans or splits
			*/
		virtual void SetSpanSplitColumnCount(int16 count) = 0;

			/** Get the minimum space before span or split columns.
			@return the minimum space before span or split columns
			*/
		virtual PMReal GetSpanSplitMinSpaceBefore() const = 0;

			/** Set the minimum space before span or split columns.
			@param minSpaceBefore the minimum space before span or split columns.
			*/
		virtual void SetSpanSplitMinSpaceBefore(PMReal minSpaceBefore) = 0;

			/** Get the minimum space after span or split columns.
			@return the minimum space after span or split columns
			*/
		virtual PMReal GetSpanSplitMinSpaceAfter() const = 0;

			/** Set the minimum space after span or split columns.
			@param minSpaceAfter the minimum space after span or split columns.
			*/
		virtual void SetSpanSplitMinSpaceAfter(PMReal minSpaceAfter) = 0;

			/** Get the inside gutter for split columns.
			@return the inside gutter for split columns
			*/
		virtual PMReal GetSplitColumnInsideGutter() const = 0;

			/** Set the inside gutter for split columns.
			@param gutter the inside gutter for split columns
			*/
		virtual void SetSplitColumnInsideGutter(PMReal gutter) = 0;

			/** Get the outside gutter for split columns
			@return the outside gutter for split columns
			*/
		virtual PMReal GetSplitColumnOutsideGutter() const = 0;

			/** Set the outside gutter for split columns
			@param gutter the outside gutter for split columns
			*/
		virtual void SetSplitColumnOutsideGutter(PMReal gutter) = 0;

			/** If the first line in the paragraph should be kept with the last line of previous paragraph
			@return if the paragraph should be kept with the last line of previous paragraph
			*/
		virtual bool16 GetKeepWithPrev() const = 0;

			/** Set if the first line in the paragraph should be kept with the last line of previous paragraph
			@param keepLinesWithPrev if the paragraph should be kept with the last line of previous paragraph
			*/
		virtual void SetKeepWithPrev(bool16 keepWithPrev) = 0;

			/** Get paragraph border and shading width.
			@return @see ICompositionStyle::ParagraphBorderShadingWidth.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingWidth GetParaBSWidth() const = 0;
			/** Set paragraph border and shading width.
			@param @see ICompositionStyle::ParagraphBorderShadingWidth.
			*/
		virtual void SetParaBSWidth(ICompositionStyle::ParagraphBorderShadingWidth borderShadingMode) = 0;

			/** Get paragraph border and shading top origin.
			@return @see ICompositionStyle::ParagraphBorderShadingTopOrigin.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingTopOrigin GetParaBSTopOrigin() const = 0;
			/** Set paragraph border and shading top origin.
			@param @see ICompositionStyle::ParagraphBorderShadingTopOrigin.
			*/
		virtual void SetParaBSTopOrigin(ICompositionStyle::ParagraphBorderShadingTopOrigin borderShadingTopOrigin) = 0;

			/** Get paragraph border and shading bottom origin.
			@return @see ICompositionStyle::ParagraphBorderShadingBottomOrigin.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingBottomOrigin GetParaBSBottomOrigin() const = 0;
			/** Set paragraph border and shading bottom origin.
			@param @see ICompositionStyle::ParagraphBorderShadingBottomOrigin.
			*/
		virtual void SetParaBSBottomOrigin(ICompositionStyle::ParagraphBorderShadingBottomOrigin borderShadingBottomOrigin) = 0;

			/** Get whether the paragraph border and shading would clip/crop itself wrt to frame.
			@return kTrue indicated that its kept in frame,  kFalse - otherwise.
			*/		
		virtual bool16 GetParaBSClipToFrame() const = 0;
			/** Set whether the paragraph border and shading should clip/crop itself wrt to frame.
			@param keepInFrame - pass kTrue to keep in frame, kFalse - otherwise.
			*/		
		virtual void SetParaBSClipToFrame(bool16 clipToFrame) = 0;

			/** Get whether the paragraph border and shading would suppress while printing
			@return kTrue indicates it would suppress, kFalse - otherwise.
			*/		
		virtual bool16 GetParaBSSuppressPrinting() const = 0;
			/** Set whether the paragraph border and shading should be suppressed while printing.
			@param keepInFrame - pass kTrue to suppress, kFalse - otherwise.
			*/		
		virtual void SetParaBSSuppressPrinting(bool16 suppressPrinting) = 0;

			/** Get the paragraph border and shading offsets
			@return left - left offset, right - right offset, top - top offset, bottom - bottom offset.
			*/				
		virtual void GetParaBSOffsets(PMReal *left, PMReal *right, PMReal *top, PMReal *bottom) const = 0;
			/** Set the paragraph border and shading left offset
			@param left - left offset.
			*/				
		virtual void SetParaBSOffsetL(PMReal left) = 0;
			/** Set the paragraph border and shading right offset
			@param right - right offset.
			*/				
		virtual void SetParaBSOffsetR(PMReal right) = 0;
			/** Set the paragraph border and shading top offset
			@param top - top offset.
			*/				
		virtual void SetParaBSOffsetT(PMReal top) = 0;
			/** Set the paragraph border and shading bottom offset
			@param bottom - bottom offset.
			*/				
		virtual void SetParaBSOffsetB(PMReal bottom) = 0;

		/** Get the paragraph border offsets
			@return left - left offset, right - right offset, top - top offset, bottom - bottom offset.
			*/				
		virtual void GetParaBorderOffsets(PMReal *left, PMReal *right, PMReal *top, PMReal *bottom) const = 0;
			/** Set the paragraph border left offset
			@param left - left offset.
			*/				
		virtual void SetParaBorderOffsetL(PMReal left) = 0;
			/** Set the paragraph border right offset
			@param right - right offset.
			*/				
		virtual void SetParaBorderOffsetR(PMReal right) = 0;
			/** Set the paragraph border top offset
			@param top - top offset.
			*/				
		virtual void SetParaBorderOffsetT(PMReal top) = 0;
			/** Set the paragraph border bottom offset
			@param bottom - bottom offset.
			*/				
		virtual void SetParaBorderOffsetB(PMReal bottom) = 0;
		
			/** Get whether the paragraph border and shading - fill is on
			@return kTrue - paragraph border and shading fill is on, kFalse otherwise.
			*/
		virtual bool16 GetParaBSFillOn() const = 0;

			/** Set fill mode for the paragraph border and shading
			@param pass kTrue to switch on fill for paragraph border and shading, kFalse otherwise.
			*/
		virtual void SetParaBSFillOn(bool16 fillOn) = 0;

			/** Get fill specific data for paragraph border and shading
			@return colorUID - fill color, tint - fill tint, overprint - whether fill overprint is on.
			*/
		virtual void GetParaBSFillData(UID *colorUID, PMReal *tint, bool16* overprint) const = 0;
			/** Set fill color for paragraph border and shading
			@param fillColorUID - UID of fill color.
			*/				
		virtual void SetParaBSFillColor(UID fillColorUID) = 0;
			/** Set fill tint value for paragraph border and shading
			@param fillTint - tint value.
			*/				
		virtual void SetParaBSFillTint(PMReal fillTint) = 0;
			/** Set fill overprint for paragraph border and shading
			@param fillOverprint - pass kTrue to switch on overprinting for fill.
			*/				
		virtual void SetParaBSFillOverprint(bool16 fillOverprint) = 0;	
		
		/** Get whether the paragraph border and shading stroke is on
		@return kTrue - paragraph border and shading stroke is on, kFalse otherwise.
		*/
		virtual bool16 GetParaBSStrokeOn() const = 0;
		/** Set stroke mode for the paragraph border and shading
		@param pass kTrue to switch on stroke for paragraph border and shading, kFalse otherwise.
		*/
		virtual void SetParaBSStrokeOn(bool16 strokeOn) = 0;

		/** Get stroke specific data for paragraph border and shading
		@return strokeColorUID - stroke color, strokeTint - stroke tint, strokeOverprint - whether stroke overprint is on,
		strokeWeight - weight of stroke, strokeType - type of stroke
		gapColorUID - stroke gap color, gapTint - stroke gap tint, gapOverprint - whether stroke gap overprint is on,
		*/
		virtual void GetParaBSStrokeData(UID *strokeColorUID, PMReal *strokeTint, bool16 *strokeOverprint, 
			PMReal *strokeWeight, ICompositionStyle::StrokeType *strokeType, ICompositionStyle::StrokeJoinType *strokeJoinType, ICompositionStyle::StrokeCapType *strokeCapType,
			UID *gapColorUID, PMReal *gapTint, bool16 *gapOverprint) const = 0;

			/** Set stroke color for paragraph border and shading
			@param strokeColorUID - UID of stroke color.
			*/				
		virtual void SetParaBSStrokeColor(UID strokeColorUID) = 0;
			/** Set stroke tint for paragraph border and shading
			@param strokeTint - stroke tint value.
			*/				
		virtual void SetParaBSStrokeTint(PMReal strokeTint) = 0;
			/** Set stroke overprint for paragraph border and shading
			@param strokeOverprint - pass kTrue to switch on overprinting for stroke.
			*/				
		virtual void SetParaBSStrokeOverprint(bool16 overprint) = 0;
			/** Set stroke weight for paragraph border and shading
			@param strokeWeight - stroke weight value.
			*/				
		virtual void SetParaBSStrokeWeight(PMReal strokeWeight) = 0;
			/** Set stroke type for paragraph border and shading
			@param strokeType - type of stroke.
			@see ICompositionStyle::StrokeType
			*/				
		virtual void SetParaBSStrokeType(ICompositionStyle::StrokeType type) = 0;
			/** Set the paragraph border join type
			@param @see ICompositionStyle::StrokeJoinType.
			*/
		virtual void SetParaBSStrokeJoinType(ICompositionStyle::StrokeJoinType strokeJoinType) = 0;
			/** Set the paragraph border cap type
			@param @see ICompositionStyle::StrokeCapType.
			*/
		virtual void SetParaBSStrokeCapType(ICompositionStyle::StrokeCapType strokeCapType) = 0;
			/** Set stroke gap color for paragraph border and shading
			@param strokeGapColorUID - UID of stroke gap color.
			*/				
		virtual void SetParaBSStrokeGapColor(UID strokeGapColorUID) = 0;
			/** Set stroke gap tint for paragraph border and shading
			@param strokeGapTint - stroke gap tint value.
			*/				
		virtual void SetParaBSStrokeGapTint(PMReal strokeGapTint) = 0;
			/** Set stroke gap overprint for paragraph border and shading
			@param strokeGapOverprint - pass kTrue to switch on overprinting for stroke gap.
			*/				
		virtual void SetParaBSStrokeGapOverprint(bool16 strokeGapOverprint) = 0;

			/** Get the paragraph border corner types
			@return topLeftType - top left corner type, topRightType - top right corner type, bottomLeftType - bottom left corner type, bottomRightType - bottom right corner type.
			*/
		virtual void GetParaBorderCornerType(ClassID *topLeftType, ClassID *topRightType, ClassID *bottomLeftType, ClassID *bottomRightType) const = 0;

			/** Get the paragraph border corner radii
			@return topLeft - top left corner radius, topRight - top right corner radius, bottomLeft - bottom left corner radius, bottomRight - bottom right corner radius.
			*/
		virtual void GetParaBorderCornerRadius(PMReal *topLeft, PMReal *topRight, PMReal *bottomLeft, PMReal *bottomRight) const = 0;

			/** Set paragraph border top left corner type.
			@param @see ClassID.
			*/
		virtual void SetParaBCornerTopLeftType(ClassID cornerType) = 0;
			
			/** Set paragraph border top left radius.
			@param @see PMReal.
			*/
		virtual void SetParaBCornerTopLeftRadius(PMReal radius) = 0;

			/** Set paragraph border top right corner type.
			@param @see ClassID.
			*/
		virtual void SetParaBCornerTopRightType(ClassID cornerType) = 0;
			
			/** Set paragraph border top right radius.
			@param @see PMReal.
			*/
		virtual void SetParaBCornerTopRightRadius(PMReal radius) = 0;

			/** Set paragraph border bottom left corner type.
			@param @see ClassID.
			*/
		virtual void SetParaBCornerBottomLeftType(ClassID cornerType) = 0;
			
			/** Set paragraph border bottom left radius.
			@param @see PMReal.
			*/
		virtual void SetParaBCornerBottomLeftRadius(PMReal radius) = 0;

			/** Set paragraph border bottom right corner type.
			@param @see ClassID.
			*/
		virtual void SetParaBCornerBottomRightType(ClassID cornerType) = 0;
			
			/** Set paragraph border bottom right radius.
			@param @see PMReal.
			*/
		virtual void SetParaBCornerBottomRightRadius(PMReal radius) = 0;

			/** Get the paragraph shading corner types
			@return topLeftType - top left corner type, topRightType - top right corner type, bottomLeftType - bottom left corner type, bottomRightType - bottom right corner type.
			*/
		virtual void GetParaShadeCornerType(ClassID *topLeftType, ClassID *topRightType, ClassID *bottomLeftType, ClassID *bottomRightType) const = 0;

			/** Get the paragraph shading corner radii
			@return topLeft - top left corner radius, topRight - top right corner radius, bottomLeft - bottom left corner radius, bottomRight - bottom right corner radius.
			*/
		virtual void GetParaShadeCornerRadius(PMReal *topLeft, PMReal *topRight, PMReal *bottomLeft, PMReal *bottomRight) const = 0;

			/** Set paragraph shading top left corner type.
			@param @see ClassID.
			*/
		virtual void SetParaSCornerTopLeftType(ClassID cornerType) = 0;
			
			/** Set paragraph shading top left radius.
			@param @see PMReal.
			*/
		virtual void SetParaSCornerTopLeftRadius(PMReal radius) = 0;

			/** Set paragraph shading top right corner type.
			@param @see ClassID.
			*/
		virtual void SetParaSCornerTopRightType(ClassID cornerType) = 0;
			
			/** Set paragraph shading top right radius.
			@param @see PMReal.
			*/
		virtual void SetParaSCornerTopRightRadius(PMReal radius) = 0;

			/** Set paragraph shading bottom left corner type.
			@param @see ClassID.
			*/
		virtual void SetParaSCornerBottomLeftType(ClassID cornerType) = 0;
			
			/** Set paragraph shading bottom left radius.
			@param @see PMReal.
			*/
		virtual void SetParaSCornerBottomLeftRadius(PMReal radius) = 0;
			/** Set paragraph shading bottom right corner type.
			@param @see ClassID.
			*/
		virtual void SetParaSCornerBottomRightType(ClassID cornerType) = 0;
			
			/** Set paragraph shading bottom right radius.
			@param @see PMReal.
			*/
		virtual void SetParaSCornerBottomRightRadius(PMReal radius) = 0;
			/** Get paragraph border width.
			@return @see ICompositionStyle::ParagraphBorderShadingWidth.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingWidth GetParaBSStrokeWidth() const = 0;
			
			/** Set paragraph border width.
			@param @see ICompositionStyle::ParagraphBorderShadingWidth.
			*/
		virtual void SetParaBSStrokeWidth(ICompositionStyle::ParagraphBorderShadingWidth borderShadingMode) = 0;

			/** Get paragraph border top origin.
			@return @see ICompositionStyle::ParagraphBorderShadingTopOrigin.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingTopOrigin GetParaBSStrokeTopOrigin() const = 0;
			
			/** Set paragraph border top origin.
			@param @see ICompositionStyle::ParagraphBorderShadingTopOrigin.
			*/
		virtual void SetParaBSStrokeTopOrigin(ICompositionStyle::ParagraphBorderShadingTopOrigin borderShadingTopOrigin) = 0;

			/** Get paragraph border bottom origin.
			@return @see ICompositionStyle::ParagraphBorderShadingBottomOrigin.
			*/
		virtual ICompositionStyle::ParagraphBorderShadingBottomOrigin GetParaBSStrokeBottomOrigin() const = 0;
			
			/** Set paragraph border bottom origin.
			@param @see ICompositionStyle::ParagraphBorderShadingBottomOrigin.
			*/
		virtual void SetParaBSStrokeBottomOrigin(ICompositionStyle::ParagraphBorderShadingBottomOrigin borderShadingBottomOrigin) = 0;

			/** Set paragraph border top stroke weight value.
			@param @see PMReal.
			*/
		virtual void SetParaBWeightTopValue(PMReal value) = 0;

			/** Set paragraph border bottom stroke weight value.
			@param @see PMReal.
			*/
		virtual void SetParaBWeightBottomValue(PMReal value) = 0;

			/** Set paragraph border left stroke weight value.
			@param @see PMReal.
			*/
		virtual void SetParaBWeightLeftValue(PMReal value) = 0;

			/** Set paragraph border right stroke weight value.
			@param @see PMReal.
			*/
		virtual void SetParaBWeightRightValue(PMReal value) = 0;

			/** Get paragraph border stroke weights.
			@return @see PMReal.
			*/
		virtual void GetParaBorderWeightValues(PMReal *left, PMReal *top, PMReal *right, PMReal *bottom) const = 0;

			/** Get whether to display border if paragraph flows of paragraph border and shading 
			@return kTrue indicates it would suppress, kFalse - otherwise.
			*/
		virtual bool16 GetParaBSParagraphFlow() const = 0;
			/** Sets whether to display border if paragraph flows of paragraph border and shading 
			@param keepInFrame - pass kTrue to suppress, kFalse - otherwise.
			*/
		virtual void SetParaBSParagraphFlow(bool16 displayBorder) = 0;

			/** Get whether to merge consecutive borders with same setting of paragraph border and shading
			@return kTrue indicates it would merge, kFalse - otherwise.
			*/
		virtual bool16 GetParaBSMergeBorder() const = 0;
			/** Sets whether to merge consecutive borders with same setting of paragraph border and shading
			@param mergeBorder - pass kTrue to merge, kFalse - otherwise.
			*/
		virtual void SetParaBSMergeBorder(bool16 mergeBorder) = 0;
};

#endif
	// __ICompositionStyle__

