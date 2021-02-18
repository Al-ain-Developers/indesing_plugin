//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttributeSuite.h $
//  
//  Owner:
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
//  Notes:
//  
//========================================================================================

#pragma once
#ifndef __ITextAttributeSuite__
#define __ITextAttributeSuite__

#include "IPMUnknown.h"
#include "TextID.h"
#include "AttributeBossList.h"
#include "ICommand.h"
#include "IDrawingStyle.h"
#include "ICompositionStyle.h"
#include "IHyphenationStyle.h"
#include "ITextAttrFigureStyle.h"
#include "IMojikumiStyle.h"

class ITextSelectionSuite;

/** This interface is implemented by the abstract selection boss and by the concrete selection
	bosses for text and tables. It will be called from a replacement for TextFocusTarget.
	@ingroup text_attr
	@ingroup text_suite
*/
class ITextAttributeSuite : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRIBUTE_ISUITE };

	public:

		//________________________________________________________________________________________
		//	DESCR:		Return the number of unique attributes bosses for the specified class.
		//
		//	RETURNS:	Count of attributes or 0
		//________________________________________________________________________________________
		virtual int32 CountAttributes(ClassID attr) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Query the N-th ("which" - a zero based index) attribute of the specified
		//				class for the specified interface.
		//________________________________________________________________________________________
		virtual const IPMUnknown* QueryAttributeN(int32 which, ClassID attr, PMIID interfaceID) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Apply the new attributes in the "appliedAttrBossList" and remove the
		//				attributes in "removedAttrBossList".
		//
		//	RETURNS:	Error Code.
		//________________________________________________________________________________________
		virtual ErrorCode ApplyAttributes(const AttributeBossList* applied,  ClassID strandID) = 0;
			// !!! To do: It's really unfortunate to perpetuate this exposure of the strandID

		//________________________________________________________________________________________
		//	DESCR:		Copy attribute classes with a single attribute boss into "attrList".
		//				Copy attribute classes with 2 or more unique attributes into "mixedList".
		//________________________________________________________________________________________
		virtual void CopyToAttributeLists(AttributeBossList* attrList, AttributeBossList* mixedList = nil ) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the number of paragraph styles in the selection
		//________________________________________________________________________________________
		virtual int32 CountParagraphStyles() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the N-th (0-based) paragraph style in the selection
		//________________________________________________________________________________________
		virtual UID GetNthParagraphStyle(int32 n) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the number of character styles in the selection
		//________________________________________________________________________________________
		virtual int32 CountCharacterStyles() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the N-th (0-based) paragraph style in the selection
		//________________________________________________________________________________________
		virtual UID GetNthCharacterStyle(int32 n) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the number of paragraph styles in the selection
		//________________________________________________________________________________________
		virtual int32 CountRunInCharacterStyles() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the N-th (0-based) paragraph style in the selection
		//________________________________________________________________________________________
		virtual UID GetNthRunInCharacterStyle(int32 n) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns kTrue if the specified style is overridden in the selection
		//________________________________________________________________________________________
		virtual bool16 IsStyleOverridden(UID style) = 0;

		//________________________________________________________________________________________
		//	DESCR:		How many different runs of attributes are selected?
		//________________________________________________________________________________________
		virtual int32 CountSelectedRuns() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the number of fonts in the selection
		//________________________________________________________________________________________
		virtual int32 CountFonts(ClassID fontUIDBoss = kTextAttrFontUIDBoss) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Returns the N-th (0-based) font in the selection
		//________________________________________________________________________________________
		virtual PMString GetNthFont(int32 n, bool16* incorrectFace = nil, ClassID fontUIDBoss = kTextAttrFontUIDBoss, ClassID fontStyleBoss = kTextAttrFontStyleBoss) = 0;
		virtual UID GetNthFamilyUIDAndFace(int32 n, PMString * faceName, ClassID fontUIDBoss = kTextAttrFontUIDBoss, ClassID fontStyleBoss = kTextAttrFontStyleBoss) = 0;

		//________________________________________________________________________________________
		//	DESCR:		???
		//________________________________________________________________________________________
		virtual const Fixed* GetNthMMAxes(int32 n, int32 *numaxes) = 0;

		virtual bool16 CanApplyAttributes() const = 0;

		// Currently, CanQueryAttributes() is only used when we determine if a para/char style can be created or not.
		// We allow to create a para/char style if the selection contains logic text ranges.
		// For text/table selection, CanQueryAttributes() will always return kTrue.
		// For layout selection, CanQueryAttributes() will return kFalse if the selection
		// does not have text frame included, otherwise, it will always return kTrue.
		// See bug #619781 for more info. --- Yeming Liu(07/30/2003).
		virtual bool16 CanQueryAttributes() const = 0;

		typedef enum { kOff, kOn, kMixed, kUnavailable, kUninitialized } FeatureState;

		// General Setters/Accessors
		virtual ErrorCode ApplyAttribute(const IPMUnknown * attribute) = 0;

		virtual ErrorCode ToggleBooleanAttribute(ClassID attributeClass) = 0;
		virtual ErrorCode SetBooleanAttribute(ClassID attributeClass, bool16 theValue) = 0;
		virtual FeatureState GetBooleanAttributeState(ClassID attributeClass) = 0;

		virtual ErrorCode ToggleInt16Attribute(ClassID attributeClass, int16 onValue, int16 offValue) = 0;
		virtual ErrorCode SetInt16Attribute(ClassID attributeClass, int16 theValue) = 0;
		virtual FeatureState GetInt16AttributeState(ClassID attributeClass, int16 theValue) = 0;

		virtual ErrorCode SetRealNumberAttribute(ClassID attributeClass, PMReal theValue) = 0;
		virtual bool16 GetRealNumberAttributeValue(ClassID attributeClass, PMReal * pValue) = 0;
			// Returns kTrue if the selection contained only one value for this attribute
			// and returns the attribute value in pValue;
			// Returns kFalse if the attribute contained multiple values for the current
			// selection or there were no attribute for the ClassID (and the value returned
			// in pValue is undefined).


		// Specific Setters/Accessors
		virtual ErrorCode ClearTypeStyleAttributes() = 0;
		virtual ErrorCode ToggleBold() = 0;
		virtual ErrorCode ToggleItalic() = 0;

		virtual ErrorCode ToggleBaselineGrid() = 0;
		virtual FeatureState GetBaselineGridState() = 0;

		virtual ErrorCode ToggleUnderline() = 0;
		virtual FeatureState GetUnderlineState() = 0;

		virtual ErrorCode ToggleCapsMode(IDrawingStyle::CapitalizeMode theMode) = 0;
		virtual FeatureState GetCapsModeState(IDrawingStyle::CapitalizeMode theMode) = 0;

		virtual ErrorCode TogglePositionMode(IDrawingStyle::PositionMode positionMode) = 0;
		virtual FeatureState GetPositionModeState(IDrawingStyle::PositionMode positionMode) = 0;

		virtual ErrorCode ToggleHyphenationMethod(IHyphenationStyle::HyphenationMethod hyphenationMethod) = 0;
		virtual ITextAttributeSuite::FeatureState GetHyphenationMethodState(IHyphenationStyle::HyphenationMethod hyphenationMethod) = 0;

		virtual ErrorCode SetFigureStyle(ITextAttrFigureStyle::FigureStyle figureStyle) = 0;
		virtual FeatureState GetFigureStyleState(ITextAttrFigureStyle::FigureStyle figureStyle) = 0;

		virtual ErrorCode ToggleStylisticSet(int32 whichSet) = 0;
		virtual FeatureState GetOTStylisticSetState(int32 whichSet) = 0;

		virtual ErrorCode SetAlignment(ICompositionStyle::TextAlignment align) = 0;

		virtual ErrorCode IncrementRealNumberAttribute(ClassID attributeClass, PMReal incrementAmt,
				const PMString& undoIncreaseString, const PMString& undoDecreaseString) = 0;

		virtual ErrorCode IncrementPointSize(PMReal amount) = 0;
		virtual ErrorCode IncrementLeading(PMReal amount) = 0;
		virtual ErrorCode IncrementTracking(PMReal amount) = 0;
		virtual ErrorCode IncrementBaselineShift(PMReal amount) = 0;
		virtual ErrorCode IncrementWordSpace(PMReal amount) = 0;

		typedef enum { kIgnoreCharacterStyles, kRemoveCharacterStyles } CharStyleParam;
		typedef enum { kApplySingleStyle, kAutoApplyNextStyle } NextStyleParam;
		typedef enum { kRemoveOldStyle, kMaintainOldStyleAttrs } StyleToAttrParam;

		/**
			@param oldStyleAttrs IN whether to apply the old style as overrides before setting new style.
						This variable is only used if styleUID is the root style.
		*/
		virtual ErrorCode ApplyStyle(UID styleUID, bool16 clearOverrides = kFalse, CharStyleParam removeCharacterStyles = kIgnoreCharacterStyles,
									NextStyleParam autoNextStyle = kApplySingleStyle, StyleToAttrParam oldStyleAttrs = kMaintainOldStyleAttrs) = 0;

		virtual ErrorCode ClearCharacterOverrides() = 0;
		virtual ErrorCode ClearParagraphOverrides() = 0;
		virtual ErrorCode ClearIndentOverrides() = 0;
		virtual bool16 CanClearIndentOverrides() = 0;
		virtual ErrorCode ClearAllOverrides() = 0;

		virtual ErrorCode SetCharAlignment(IDrawingStyle::CharacterHang theMode) = 0;
		virtual FeatureState GetCharAlignmentState(IDrawingStyle::CharacterHang theMode) = 0;

		virtual ErrorCode SetKinsokuType(IMojikumiStyle::KinsokuType theMode) = 0;
		virtual FeatureState GetKinsokuTypeState(IMojikumiStyle::KinsokuType theMode) = 0;

		virtual ErrorCode ToggleKinsokuHangType(IMojikumiStyle::KinsokuHangType theMode) = 0;
		virtual FeatureState GetKinsokuHangTypeState(IMojikumiStyle::KinsokuHangType theMode) = 0;

		virtual ErrorCode ToggleGridAlignmentMetric(Text::GridAlignmentMetric theMode) = 0;
		virtual FeatureState GetGridAlignmentMetricState(Text::GridAlignmentMetric theMode) = 0;

		virtual ErrorCode SetLeadingModel(Text::LeadingModel theMode) = 0;
		virtual FeatureState GetLeadingModelState(Text::LeadingModel theMode) = 0;

		virtual bool16 CanRemoveFormatting() const = 0;
		virtual ErrorCode RemoveFormatting() = 0;

		virtual bool16 AdjacentParagraphsSelected() const = 0;
		virtual bool16 ContainsParagraphStyleOverrides() const = 0;
			// Are there paragraph style overrides within the selected range of characters?

		virtual bool16 SelectedParagraphsIncludeOverrides() const = 0;
			// Are there paraagraph style overrides within the paragraphs intersected by the selection?

		virtual bool16 SelectedParagraphsIncludeCharStyles() const = 0;
			// Are there character styles used (other than "[None]") within the paragraphs intersected by the selection?

		virtual bool16 CheckSelectionForRuby() = 0;
		virtual ErrorCode SetRubyNone() = 0;

		virtual ErrorCode AdjustSelectionForBoolAttribute(ITextSelectionSuite * textSelectionSuite, ClassID attrClass) = 0;

			// This takes all ruby runs in the selection and makes sure that the ruby attr and ruby string attr matches
		virtual ErrorCode SynchRubyAttrToRubyStrand() = 0;

		//________________________________________________________________________________________
		//	DESCR:		Fills the vector of strings passed in with the names of the current overrides
		//				(to be used to display the overrides in the tool tip)
		//	@param	K2Vector<PMString>& overrideStrings
		//	@param	useParaStyle	kTrue -- paragraph style, kFalse -- characterStyle
		//	@return	bool16 true if the overrides are mixed
		//________________________________________________________________________________________
		virtual bool16 FillStringListWithOverrides(K2Vector<PMString>& overrideStrings, bool16 useParaStyle) const = 0;

		virtual ErrorCode SetPositionalForm(IDrawingStyle::OTPositioningForm form) = 0;
		virtual FeatureState CheckPositionalForm(IDrawingStyle::OTPositioningForm check) const = 0;
		virtual ErrorCode ChangeParagraphDirection(ICompositionStyle::ParagraphDirection paraDir) = 0;

		//________________________________________________________________________________________
		//	DESCR:		Apply the new attributes in the "appliedAttrBossList" with the specified undo ability type
		//
		//	RETURNS:	Error Code.
		//________________________________________________________________________________________
		virtual ErrorCode ApplyAttributes(const AttributeBossList* applied, ClassID strandID, ICommand::Undoability undoabilityFlag) = 0;

};

#endif

