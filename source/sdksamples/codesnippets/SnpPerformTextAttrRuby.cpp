//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformTextAttrRuby.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

// General includes:
#include "AttributeBossList.h"
#include "CJKID.h"
#include "CmdUtils.h"
#include "PersistUtils.h"
#include "RangeData.h"
#include "TCID.h" // for composer boss class IDs
#include "TextAttrID.h"
#include "TextID.h"
#include "TextRange.h"
#include "Utils.h"
#include "WideString.h"

// Interface includes:
#include "IAttrReport.h"
#include "IClassIDData.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "IDataBase.h"
#include "IFontFamily.h"
#include "IRubyStrand.h" // for IRubyAttrStrand
#include "IRubyStyle.h"
#include "ISelectUtils.h"
#include "ISwatchList.h"
#include "ISwatchUtils.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrClassID.h"
#include "ITextAttrFont.h"
#include "ITextAttrInt16.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttrRubyAdjustParent.h"
#include "ITextAttrRubyAlign.h"
#include "ITextAttrRubyOverhang.h"
#include "ITextAttrUID.h"
#include "ITextAttrUtils.h"
#include "ITextAttrWideString.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "ITextUtils.h"
#include "IUIDData.h"
#include "LocaleSetting.h"

#include "SnpTextAttrHelper.h"


/** Max length of ruby base text
 */
static const int32 kSnipRubyParentStringMaxLength = 32;

/** Bool text lookup
 */
static const char* kSnpBool16Text[2] = 
{
	"False",
	"True"
};

/** Ruby alignment text lookup
 * 	@see IRubyStyle::RubyAlign 
 */
static const char* kSnpRubyAlignText[7] = 
{
	"kRubyAlign_Left",			// Left alignment = 0
	"kRubyAlign_Center",		// Center alignment
	"kRubyAlign_Right",			// Right alignment
	"kRubyAlign_Justify",		// Full Justify
	"kRubyAlign_JISRule",		// 1:2:1
	"kRubyAlign_EqualSpace",	// 1:1:1
	"kRubyAlign_EdgeOneRuby"	// add one width of ruby character. (both sides)
};

/** Ruby overhang text lookup
 * 	@see IRubyStyle::RubyOverHang
 */
static const char* kSnpRubyOverhangText[6] =
{
	"kRubyOverHang_None",		// None  = 0
	"kRubyOverHang_OneRuby",	// One width of Ruby character
	"kRubyOverHang_HalfRuby",	// Half width of Ruby character
	"kRubyOverHang_OneChar",	// One width of Parent character
	"kRubyOverHang_HalfChar",	// Half width of Parent character
	"kRubyOverHang_NoLimit"     
};

/** Ruby adjust parent text lookup
 * 	@see IRubyStyle::RubyAdjustParent
 */
static const char* kSnpRubyAdjustParentText[5] = 
{
	"kRubyAdjustParent_None",		// None = 0
	"kRubyAdjustParent_BothSide",	// Add space both side of parent characters.
	"kRubyAdjustParent_Mojikumi",	// Add space 1:2:1 in parent characters.
	"kRubyAdjustParent_EqualAki",	// Add space 1:1:1 in parent characters.
	"kRubyAdjustParent_Justify"		// Full Justify.
};

// TODO align with coding conventions

/** Stores all Ruby related attributes in a single structure.
 * 	Note that this sample only sets a few of the members, however
 * 	all members are inspected.
 * 	All member variables correspond to a ruby attribute.
 */
struct SnpRubyDataSettings
{
	/** Specifies whether ruby is on or off.
	 * 	kTrue = on;
	 * 	kFalse = off
	 * 	@see kTARubyAttrBoss */
	bool16 fAttrOn;	 	

	/** The ruby string.
	 * 	@see kTARubyStringBoss */
	WideString fString;
	
	// (Ruby Panel selectable dialog 1) Position and spacing related attributes
	
	/** Specifies whether to use Moji (mono) ruby or group ruby.
	 * 	kTrue = mono (moji) ruby;
	 *  kFalse = group ruby
	 * 	@see kTAMojiRubyBoss */
	bool16 fMojiRuby;
	
	/** Ruby alignment.
	 * 	@see kTARubyAlignmentBoss 
	 * 	@see IRubyStyle */
	IRubyStyle::RubyAlign fAlignment;
	
	/**	Specifies the position of the Ruby.
	 * 	0 = right/top
	 * 	1 = left/bottom
	 * @see kTARubyPositionBoss */
	bool16 fPosition;		

	/**	Specifies the X-direction distance from the base text in points.
	 * @see kTARubyXOffsetBoss */
	PMReal fXOffset;
	
	/** Specifies the Y-direction distance from the base text in points.
	 * @see kTARubyYOffsetBoss */
	PMReal fYOffset;
	

	// (Ruby Panel Selectable Dialog 2) Font and size related attributes -----
	
	/** Specifies the ruby font.
	 * 	@see kTARubyFontUIDBoss */
	UID	fFont;				
	
	/**	Specifies the ruby font style (face) 
	 * 	@see kTARubyFontStyleBoss */
	PMString fFontStyle;	

	/** Specifies the relative size of the ruby (between 0.0-1.0 of base text size), 
	 * 	if autoscale is turned on. 
	 * 	@see kTARubyRelativeSizeBoss */
	PMReal fRelativeSize;
	
	/** Specifies the point size of the ruby text, if autoscale is off. 
	 * 	@see kTARubyPointSizeBoss */
	PMReal fPointSize;
	
	/** Specifies X-direction scaling (between 0.0-1.0).
	 * 	Note that in a vertical text story, X increases downwards.
	 * 	@see kTARubyXScaleBoss */
	PMReal fXScale;	
	/** Specifies vertical scaling (between 0.0-1.0).
	 * 	Note that in a vertical text story, Y increases to the left.
	 * 	@see kTARubyYScaleBoss */
	PMReal fYScale;

	/** Specifies if you want to use OpenType Pro ruby glyphs.
	 * 	kTrue = Yes;
	 * 	kFalse = No
	 * 	@see kTARubyOTProBoss */
	bool16 fOTPro;


	// (Ruby Panel: Selectable Dialog 3) attributes on relationship to base text (parent text) -----

	/** Specifies of ruby overhang (if ruby text is longer than base text) is on.
	 * 	kTrue = On;
	 * 	kFalse = Off
	 * 	@see kTARubyOverhangFlagBoss */
	bool16 fOverhangFlag;

	/** Specifies the ruby overhang type.
	 * 	@see kTARubyOverhangBoss 
	 * 	@see IRubyStyle */
	IRubyStyle::RubyOverHang fOverhang;
	
	/** Specifies how the extra ruby text will cause the base (parent)
	 * 	text to expand.
	 * 	@see kTARubyAdjustParentBoss 
	 * 	@see IRubyStyle */
	IRubyStyle::RubyAdjustParent fAdjustParent;
	
	/** Specifies if the ruby text should be 
	 * 	automatically compressed if it's longer than basetext.
	 * 	kTrue = Yes;
	 * 	kFalse = No
	 * 	@see kTARubyAutoScalingBoss */
	bool16 fAutoScaling;
	
	/** Specifies the minimum compression factor (in %/100) if kTARubyAutoScaling is enabled.
	 * 	@see kTARubyAutoScaleMinBoss */
	PMReal fAutoScaleMin;
	
	/** Specifies whether to make the ruby fit in the text frame/frame grid
	 * 	if it is longer than base text that comes at the edge of a frame.
	 * 	kTrue = On;
	 * 	kFalse = Off
	 * 	@see kTARubyEdgeSpaceBoss */
	bool16 fEdgeSpace;		
	

	// (Ruby Panel: Selectable Dialog 4) color related attributes -----
	
	/** Specifies the color (UID) of the ruby text.
	 * 	@see kTARubyColorBoss */
	UID	fColor;				
	
	/** Specifies the tint (in %) of the ruby text. 
	 * 	@see kTARubyTintBoss */
	PMReal	fTint;
	/** Specifies if overprint is on or off.
	 * 	Auto = -1;
	 * 	Off = 0;
	 * 	On = 1
	 * 	@see kTARubyOverprintBoss */
	int16 fOverprint;

	/** Specifies of the color (UID) of the ruby text stroke.
	 * 	@see kTARubyStrokeColorBoss */
	UID	fStrokeColor;
	
	/** Specifies the tint (in %) of the ruby text stroke.
	 *  Auto = -1.0;
	 * 	Otherwise specify (tint percent/100).
	 * 	@see kTARubyStrokeTintBoss */
	PMReal fStrokeTint;

	/** Specifies if the ruby text stroke overprint is on or off.
	 * 	Auto = -1;
	 * 	Off = 0;
	 * 	On = 1
	 * 	@see kTARubyStrokeOverprintBoss */
	int16 fStrokeOverprint;	
	
	/** Specifies the width (in points) of the ruby text stroke.
	 *  Auto = -1.0;
	 * 	Otherwise specify the stroke width in points.
	 * 	@see kTARubyOutlineBoss */
	PMReal fOutline;

	/** Specifies if the ruby text should be Auto TCY in vertical, and how many digits.
	 * 	@see kTARubyAutoTCYNumDigitsBoss */
	int16 fAutoTCYNumDigits;	
	
	/** Specifies if the AutoTCY ruby text should include Roman characters or just numbers.
	 * 	@see kTARubyAutoTCYIncludeRomanBoss */
	bool16 fAutoTCYIncludeRoman;	

	/** Specifies if the AutoTCY ruby text should be scaled to fit in 1 em width.
	 * 	@see kTARubyAutoTCYAutoScaleBoss */
	bool16 fAutoTCYAutoScale;	

};


/** 
	\li How to apply, remove, and inspect ruby text attributes.
 
	This snippet is an extension of what used to be the RubyModifyJ sample plug-in. 

	@ingroup sdk_snippet
	@ingroup sdk_text
	@ingroup sdk_cjk
	@see IAttrReport
	@see IComposeScanner
	@see IRubyAttrStrand
	@see IRubyStyle
	@see ITextAttrBoolean
	@see ITextAttrClassID
	@see ITextAttrFont
	@see ITextAttrInt16
	@see ITextAttrRealNumber
	@see ITextAttrRubyAdjustParent
	@see ITextAttrRubyAlign
	@see ITextAttrRubyOverhang
	@see ITextAttrUID
	@see ITextAttrUtils
	@see ITextAttrWideString
	@see ITextFocus
	@see ITextModel
	@see ITextTarget
	@see ITextUtils
*/
class SnpPerformTextAttrRuby 
{
public:
	
	/** Constructor.
	*/
	SnpPerformTextAttrRuby() {}

	/** Destructor..
	*/
	virtual ~SnpPerformTextAttrRuby() {}

	/**	Applies ruby attributes onto the specified text model range.
	 * 	@param textRange (in) The text range to which you want to apply ruby.
	 * 	@param rubyData (in) The ruby settings.  Use SetRubyData() to fill in the members.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ApplyRuby(const InDesign::TextRange& textRange, const SnpRubyDataSettings& rubyData);

	/**	Removes (or simply turns off) ruby attributes from the specified text model range.
	 * 	@param textRange (in) The text range from which you want to remove ruby.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode RemoveRuby(const InDesign::TextRange& textRange);

	/**	Inspects ruby attributes over the specified text model range.
	 * 	The details are printed onto the SNIPLOG.
	 * 	@param textRange (in) The text range from which you want to inspect ruby.
	 * 	@param rubyData (out) The ruby settings. 
 	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode InspectRuby(const InDesign::TextRange& textRange, SnpRubyDataSettings& rubyData);
	
	/** Sets the SnpRubyDataSettings structure.
	 * 	@param textRange (in) The text range to use as a basis for some ruby 
	 * 		settings, particularly those that depend on the base text.
	 * 	@param rubyData (out) The ruby settings that can be passed on to ApplyRuby().
	 */
	void SetRubyData(const InDesign::TextRange& textRange, SnpRubyDataSettings& rubyData);
	
	/** Reports ruby data to SNIPLOG.
	 * 	@param rubyData (in) The ruby settings. 
	 * 	@param db (in) Database for getting the swatch names.
	 */
	void ReportRubyData(const SnpRubyDataSettings& rubyData, IDataBase* db);

	/** The ruby attribute strand isn't there by default when a new 
	 * 	text model is created, so we need to check if someone has created it... 
	 * 	(Change of behavior in InDesign 2.0)
	 * 	@param textModel  (in) The text model on which the ruby attribute 
	 * 		strand is to be created. 
	 * 	@return ErrorCode  kSuccess if successful. 
	*/
	ErrorCode CreateRubyStrandIfNeeded(ITextModel* textModel);

	/** Gets info about the first ruby strand found in the selected text range.
	 * 	Use this method to accurately check on the existence of any ruby in the
	 * 	specified text range. 
	 * 	@param textRangeToExamine (in) Specifies the text range to look at for ruby.
	 * 	@param firstRubyStrandRange (out) If ruby exists in the textRangeToExamine, 
	 * 		this returns the actual text range for the first ruby strand. 
	 * 		If ruby does not exist in the textRangeToExamine, this will return 
	 * 		a nil TextModel. 
	 * 	@param firstRubyString (out) If ruby exists in the textRangeToExamine,
	 * 		this returns the first ruby string in the range identified by
	 * 		firstRubyStrandRange. Otherwise, returns an empty string.
	 * 	@param firstRubyAttr (out) If ruby exists in the textRangeToExamine,
	 * 		this returns the state of the kTARubyAttrBoss attribute. 
	 */
	ErrorCode GetRubyStrandInfo(const InDesign::TextRange& textRangeToExamine, 
								InDesign::TextRange& firstRubyStrandRange, 
								WideString& firstRubyString,
								bool16& firstRubyAttr);


};



/* ApplyRuby
*/
ErrorCode SnpPerformTextAttrRuby::ApplyRuby(const InDesign::TextRange& textRange, const SnpRubyDataSettings& rubyData)
{
	ErrorCode status = kFailure;
	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// Query the text model and get the range data, 
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		RangeData rangeData = textRange.GetRange();
		
		// Check for valid length. 
		// (it is very unusual for the ruby base text to be longer than 32 characters
		if (rangeData.Length() <= 0 || 
			rangeData.Length() > kSnipRubyParentStringMaxLength)
		{
			SNIPLOG("You must have between 1 and %d base text characters selected. Please try again.", kSnipRubyParentStringMaxLength);
			break;
		}

		// Create ruby strand on-demand (New in InDesign 2.0)
		status = this->CreateRubyStrandIfNeeded(textModel);
		if (status != kSuccess)
		{
			ASSERT_FAIL("CreateRubyStrandIfNeeded failed. Resulting ruby composition will be unstable!");
			break;
		}

        // create an AttributeBossList so we can apply all attributes in one operation.
		boost::shared_ptr<AttributeBossList> attrList (new AttributeBossList);
		if (attrList.get() == nil) 
		{
			ASSERT(attrList);
			break;
		}
		InterfacePtr<IAttrReport> attr01(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyAttrBoss, rubyData.fAttrOn));
		attrList->ApplyAttribute(attr01);
		InterfacePtr<IAttrReport> attr02(SnpTextAttrHelper::CreateTextAttribute<ITextAttrWideString, WideString>(kTARubyStringBoss, rubyData.fString));
		attrList->ApplyAttribute(attr02);
		InterfacePtr<IAttrReport> attr03(SnpTextAttrHelper::CreateTextBool16Attribute(kTAMojiRubyBoss, rubyData.fMojiRuby));
		attrList->ApplyAttribute(attr03);
		InterfacePtr<IAttrReport> attr04(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRubyAlign, IRubyStyle::RubyAlign>(kTARubyAlignmentBoss, rubyData.fAlignment));
		attrList->ApplyAttribute(attr04);
		InterfacePtr<IAttrReport> attr05(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyPositionBoss, rubyData.fPosition));
		attrList->ApplyAttribute(attr05);
		InterfacePtr<IAttrReport> attr06(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyXOffsetBoss, rubyData.fXOffset));
        attrList->ApplyAttribute(attr06);
		InterfacePtr<IAttrReport> attr07(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyYOffsetBoss, rubyData.fYOffset));
		attrList->ApplyAttribute(attr07);

		InterfacePtr<IAttrReport> attr08(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, UID>(kTARubyFontUIDBoss, rubyData.fFont));
		attrList->ApplyAttribute(attr08);
		InterfacePtr<IAttrReport> attr09(SnpTextAttrHelper::CreateTextFontStyleAttribute(kTARubyFontStyleBoss, rubyData.fFontStyle));
		attrList->ApplyAttribute(attr09);
		InterfacePtr<IAttrReport> attr10(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyRelativeSizeBoss, rubyData.fRelativeSize));
		attrList->ApplyAttribute(attr10);
		InterfacePtr<IAttrReport> attr11(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyPointSizeBoss, rubyData.fPointSize));
		attrList->ApplyAttribute(attr11);
        InterfacePtr<IAttrReport> attr12(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyXScaleBoss, rubyData.fXScale));
		attrList->ApplyAttribute(attr12);
		InterfacePtr<IAttrReport> attr13(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyYScaleBoss, rubyData.fYScale));
		attrList->ApplyAttribute(attr13);
		InterfacePtr<IAttrReport> attr14(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyOTProBoss, rubyData.fOTPro));
		attrList->ApplyAttribute(attr14);
        
		InterfacePtr<IAttrReport> attr15(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyOverhangFlagBoss, rubyData.fAutoScaling));
		attrList->ApplyAttribute(attr15);
		InterfacePtr<IAttrReport> attr16(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRubyOverhang, IRubyStyle::RubyOverHang>(kTARubyOverhangBoss, rubyData.fOverhang));
		attrList->ApplyAttribute(attr16);
		InterfacePtr<IAttrReport> attr17(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRubyAdjustParent, IRubyStyle::RubyAdjustParent>(kTARubyAdjustParentBoss, rubyData.fAdjustParent));
		attrList->ApplyAttribute(attr17);
		InterfacePtr<IAttrReport> attr18(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyAutoScalingBoss, rubyData.fAutoScaling));
		attrList->ApplyAttribute(attr18);
		InterfacePtr<IAttrReport> attr19(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyAutoScaleMinBoss, rubyData.fAutoScaleMin));
		attrList->ApplyAttribute(attr19);
		InterfacePtr<IAttrReport> attr20(SnpTextAttrHelper::CreateTextBool16Attribute(kTARubyEdgeSpaceBoss, rubyData.fEdgeSpace));
		attrList->ApplyAttribute(attr20);
		
		InterfacePtr<IAttrReport> attr21(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, UID>(kTARubyColorBoss, rubyData.fColor));
		attrList->ApplyAttribute(attr21);
		InterfacePtr<IAttrReport> attr22(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyTintBoss, rubyData.fTint));
		attrList->ApplyAttribute(attr22);
		InterfacePtr<IAttrReport> attr23(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, int16>(kTARubyOverprintBoss, rubyData.fOverprint));
		attrList->ApplyAttribute(attr23);
		InterfacePtr<IAttrReport> attr24(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, UID>(kTARubyStrokeColorBoss, rubyData.fStrokeColor));
		attrList->ApplyAttribute(attr24);
		InterfacePtr<IAttrReport> attr25(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyStrokeTintBoss, rubyData.fStrokeTint));
		attrList->ApplyAttribute(attr25);
		InterfacePtr<IAttrReport> attr26(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, int16>(kTARubyStrokeOverprintBoss, rubyData.fStrokeOverprint));
		attrList->ApplyAttribute(attr26);
        InterfacePtr<IAttrReport> attr27(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, PMReal>(kTARubyOutlineBoss, rubyData.fOutline));
		attrList->ApplyAttribute(attr27);
		InterfacePtr<IAttrReport> attr28(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, int16>(kTARubyAutoTCYNumDigitsBoss, rubyData.fAutoTCYNumDigits));
		attrList->ApplyAttribute(attr28);
		InterfacePtr<IAttrReport> attr29(SnpTextAttrHelper::CreateTextAttribute<ITextAttrBoolean, bool16>(kTARubyAutoTCYIncludeRomanBoss, rubyData.fAutoTCYIncludeRoman));
		attrList->ApplyAttribute(attr29);
		InterfacePtr<IAttrReport> attr30(SnpTextAttrHelper::CreateTextAttribute<ITextAttrBoolean, bool16>(kTARubyAutoTCYAutoScaleBoss, rubyData.fAutoTCYAutoScale));
		attrList->ApplyAttribute(attr30);

		// generate the command
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		InterfacePtr<ICommand> applyCmd(textModelCmds->ApplyCmd(rangeData, attrList, kCharAttrStrandBoss));
		if (applyCmd == nil) 
		{
			ASSERT(applyCmd); break;
		}

		// process the command
		status = CmdUtils::ProcessCommand(applyCmd);

	} while (false);
	return status;
}

/* RemoveRuby
*/
ErrorCode SnpPerformTextAttrRuby::RemoveRuby(const InDesign::TextRange& textRange)
{
	ErrorCode status = kFailure;
	do {
		
		ITextAttrBoolean::ValueType attrOn = kFalse;
		InDesign::TextRange firstRubyStrandRange;
		WideString firstRubyString;

		// Determine if ruby strand is available - if yes, get some fundamental info.
		status = GetRubyStrandInfo(textRange, firstRubyStrandRange, firstRubyString, attrOn);
		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		if (attrOn == kTrue) 
		{
			// just turn off the ruby attribute from the selected text range
			status = SnpTextAttrHelper::SetTextBool16Attribute(textRange, kTARubyAttrBoss, kFalse);
		}
		else
		{
			SNIPLOG("(Ruby was off already, skipping)");
		}
	} while (false);
	return status;
}


/* InspectRuby
*/
ErrorCode SnpPerformTextAttrRuby::InspectRuby(const InDesign::TextRange& textRange, SnpRubyDataSettings& rubyData)
{
	ErrorCode status = kFailure;
	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

		// check if Ruby is on
		ITextAttrBoolean::ValueType attrOn = kFalse;
		InDesign::TextRange firstRubyStrandRange;
		WideString firstRubyString;

		// Determine if ruby strand is available - if yes, get some fundamental info.
		status = this->GetRubyStrandInfo(textRange, firstRubyStrandRange, firstRubyString, attrOn);
		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (attrOn != kTrue) 
		{
			SNIPLOG("Ruby is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			break;
		}
		
		RangeData examineRange = firstRubyStrandRange.GetRange();
		SNIPLOG("Examining text range (%d, %d)", examineRange.Start(nil), examineRange.End());
		
		// get all ruby attributes
		SnpTextAttrHelper::GetTextAttribute<ITextAttrWideString, WideString>(firstRubyStrandRange, kTARubyStringBoss, rubyData.fString);
		
		// (Ruby Panel selectable dialog 1) Position and spacing related attributes
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTAMojiRubyBoss, rubyData.fMojiRuby);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRubyAlign, IRubyStyle::RubyAlign>(firstRubyStrandRange, kTARubyAlignmentBoss, rubyData.fAlignment);
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTARubyPositionBoss, rubyData.fPosition);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyXOffsetBoss, rubyData.fXOffset);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyYOffsetBoss, rubyData.fYOffset);
		
		// (Ruby Panel Selectable Dialog 2) Font and size related attributes -----
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(firstRubyStrandRange, kTARubyFontUIDBoss, rubyData.fFont);
		SnpTextAttrHelper::GetTextFontStyleAttribute(firstRubyStrandRange, kTARubyFontStyleBoss, rubyData.fFontStyle);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyRelativeSizeBoss, rubyData.fRelativeSize);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyPointSizeBoss, rubyData.fPointSize);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyXScaleBoss, rubyData.fXScale);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyYScaleBoss, rubyData.fYScale);
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTARubyOTProBoss, rubyData.fOTPro);
		
		// (Ruby Panel: Selectable Dialog 3) attributes on relationship to base text (parent text) -----
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTARubyOverhangFlagBoss, rubyData.fAutoScaling);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRubyOverhang, IRubyStyle::RubyOverHang>(firstRubyStrandRange, kTARubyOverhangBoss, rubyData.fOverhang);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRubyAdjustParent, IRubyStyle::RubyAdjustParent>(firstRubyStrandRange, kTARubyAdjustParentBoss, rubyData.fAdjustParent);
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTARubyAutoScalingBoss, rubyData.fAutoScaling);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyAutoScaleMinBoss, rubyData.fAutoScaleMin);
		SnpTextAttrHelper::GetTextBool16Attribute(firstRubyStrandRange, kTARubyEdgeSpaceBoss, rubyData.fEdgeSpace);
		
		// (Ruby Panel: Selectable Dialog 4) color related attributes -----
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(firstRubyStrandRange, kTARubyColorBoss, rubyData.fColor);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyTintBoss, rubyData.fTint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, int16>(firstRubyStrandRange, kTARubyOverprintBoss, rubyData.fOverprint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(firstRubyStrandRange, kTARubyStrokeColorBoss, rubyData.fStrokeColor);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyStrokeTintBoss, rubyData.fStrokeTint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, int16>(firstRubyStrandRange, kTARubyStrokeOverprintBoss, rubyData.fStrokeOverprint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(firstRubyStrandRange, kTARubyOutlineBoss, rubyData.fOutline);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, int16>(firstRubyStrandRange, kTARubyAutoTCYNumDigitsBoss, rubyData.fAutoTCYNumDigits);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrBoolean, bool16>(firstRubyStrandRange, kTARubyAutoTCYIncludeRomanBoss, rubyData.fAutoTCYIncludeRoman);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrBoolean, bool16>(firstRubyStrandRange, kTARubyAutoTCYAutoScaleBoss, rubyData.fAutoTCYAutoScale);
		
		// get database of text model
		InterfacePtr<ITextModel> textModel(firstRubyStrandRange.QueryModel());
		IDataBase* db = ::GetDataBase(textModel);

		// report this to SnipLog
		this->ReportRubyData(rubyData, db);

		status = kSuccess;
	} while (false);
	return status;
}

/* SetRubyData
*/
void SnpPerformTextAttrRuby::SetRubyData(const InDesign::TextRange& textRange, SnpRubyDataSettings& rubyData)
{
	ErrorCode status = kFailure;
	do
	{
		// Get some useful interfaces
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		ASSERT(textModel);
		IDataBase* db = ::GetDataBase(textModel);
		ASSERT(db);
		InterfacePtr<ISwatchList> swatchList(Utils<ISwatchUtils>()->QuerySwatchList(db));
		ASSERT(swatchList);

		// enable the ruby attribute
        rubyData.fAttrOn = kTrue;

		// the ruby string - will be set elsewhere.
		// data.fString

		// (Ruby Panel Selectable Dialog 1) Position and spacing related attributes -----
		rubyData.fMojiRuby = kFalse;
		rubyData.fAlignment = IRubyStyle::kRubyAlign_JISRule;
		rubyData.fPosition = IRubyStyle::kRubyPosition_TopRight;
		rubyData.fXOffset = 0.3; // pt
		rubyData.fYOffset = 0.4; // pt
		
		// (Ruby Panel Selectable Dialog 2) Font and size related attributes -----
		UID fontUID = kInvalidUID;
		// get the current font UID
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID>(textRange, kTextAttrFontUIDBoss, fontUID);
		rubyData.fFont = kInvalidUID; // use the same font (kInvalidUID) as the text itself
		
		PMString fontStyle("");
		SnpTextAttrHelper::GetTextFontStyleAttribute(textRange, kTextAttrFontStyleBoss, fontStyle);
		rubyData.fFontStyle = fontStyle;
		
		rubyData.fRelativeSize = 0.25;
		PMReal pointSize = 8.0;	// arbitrary default
		// get current point size
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber>(textRange, kTextAttrPointSizeBoss, pointSize);
		rubyData.fPointSize = -1; // -1 means automatic,otherwise, based on parent font size (in points) 
		rubyData.fXScale = 1.15; // slightly wider
		rubyData.fYScale = 0.85; // slightly shorter

		bool16 useOpenTypeProRubyGlyphs = kFalse;
		if (fontUID != kInvalidUID)
        {
			InterfacePtr<IFontFamily> fontFamily(db, fontUID, UseDefaultIID());
			if (fontFamily) 
			{
				// Try using the OpenType Pro font ruby glyphs is the font is an OpenType font.
				useOpenTypeProRubyGlyphs = Utils<ITextUtils>()->IsOpenTypeFamily(fontFamily);
			}
		}
		rubyData.fOTPro = useOpenTypeProRubyGlyphs;
		

		// (Ruby Panel: Selectable Dialog 3) attributes on relationship to base text (parent text) -----
		rubyData.fOverhangFlag = kTrue;
		rubyData.fOverhang = IRubyStyle::kRubyOverHang_OneRuby; // one ruby character width
		rubyData.fAdjustParent = IRubyStyle::kRubyAdjustParent_Mojikumi; // 1:2:1 aki
		rubyData.fAutoScaling = kTrue; // auto width compression enabled
		rubyData.fAutoScaleMin = 0.40; // auto width compression minimum (jidouteki ni tsumeru)
		rubyData.fEdgeSpace = kTrue; // jidou gyoutou/gyoumatsu zoroe


		// (Ruby Panel: Selectable Dialog 4) color related attributes -----
		UID fontColorUID = kInvalidUID;
		
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID>(textRange, kTextAttrColorBoss, fontColorUID);

		rubyData.fColor = fontColorUID;  // just use the same color as the base text for the ruby
		rubyData.fTint = 100.0; // full tint
		rubyData.fOverprint = (int16) kTrue; // NOTE: kTrue = 1
		
		UID noneSwatchUID = swatchList->GetNoneSwatchUID();
		ASSERT(noneSwatchUID != kInvalidUID);
		
		rubyData.fStrokeColor = fontColorUID; // or noneSwatchUID; 
		rubyData.fStrokeTint = 50.0; // lighter stroke tint
		rubyData.fStrokeOverprint = (int16) kTrue; // NOTE: kTrue = 1
		rubyData.fOutline = 0.25; // (points) ruby outline stroke width

		rubyData.fAutoTCYNumDigits = 0;
		rubyData.fAutoTCYIncludeRoman = kFalse;
		rubyData.fAutoTCYAutoScale = kTrue;

		status = kSuccess;

	} while (false);
	ASSERT(status == kSuccess);
} 


/* ReportRubyData
*/
void SnpPerformTextAttrRuby::ReportRubyData(const SnpRubyDataSettings& rubyData, IDataBase* db)
{
	SNIPLOG("=== SnpRubyDataSettings (begin) ===");
	PMString rubyString;
	rubyData.fString.GetSystemString(&rubyString);
	SNIPLOG("*RubyString: %s", rubyString.GetPlatformString().c_str());
	
	SNIPLOG("--- POSITION/SPACING ---");
	SNIPLOG("*MojiRuby: %s", kSnpBool16Text[rubyData.fMojiRuby]);
	SNIPLOG("*Alignment: %s", kSnpRubyAlignText[rubyData.fAlignment]);
	SNIPLOG("*Position: %s", kSnpBool16Text[rubyData.fPosition]);
	SNIPLOG("*XOffset: %f pt", ::ToDouble(rubyData.fXOffset));
	SNIPLOG("*YOffset: %f pt", ::ToDouble(rubyData.fYOffset));
	
	SNIPLOG("--- FONT/SIZE ---");
	SNIPLOG("*FontUID: 0x%X", rubyData.fFont.Get());
	SNIPLOG("*FontStyle: %s", rubyData.fFontStyle.GetPlatformString().c_str());
	SNIPLOG("*RelativeSize: %f", ::ToDouble(rubyData.fRelativeSize));
	SNIPLOG("*PointSize: %f pt", ::ToDouble(rubyData.fPointSize));
	SNIPLOG("*XScale: %f", ::ToDouble(rubyData.fXScale));
	SNIPLOG("*YScale: %f", ::ToDouble(rubyData.fYScale));
	SNIPLOG("*OTPro: %s", kSnpBool16Text[rubyData.fOTPro]);
	
	SNIPLOG("--- RELATION TO BASE TEXT ---");
	SNIPLOG("*Overhang: %s", kSnpRubyOverhangText[rubyData.fOverhang]);
	SNIPLOG("*AdjustParentText: %s", kSnpRubyAdjustParentText[rubyData.fAdjustParent]);
	SNIPLOG("*AutoScaling: %s", kSnpBool16Text[rubyData.fAutoScaling]);
	SNIPLOG("*AutoScaleMin: %f", ::ToDouble(rubyData.fAutoScaleMin));
	SNIPLOG("*EdgeSpace: %s", kSnpBool16Text[rubyData.fEdgeSpace]);

	SNIPLOG("--- COLOR ---");
    PMString colorSwatchName("<unknown>");
	if (db && rubyData.fColor != kInvalidUID)
	{
		colorSwatchName = Utils<ISwatchUtils>()->GetSwatchName(db, rubyData.fColor);
		colorSwatchName.Translate();
	}
	SNIPLOG("*ColorUID: 0x%X (%s)", rubyData.fColor.Get(), colorSwatchName.GetPlatformString().c_str());
	SNIPLOG("*Tint: %f %%", ::ToDouble(rubyData.fTint));
	SNIPLOG("*Overprint: %d", rubyData.fOverprint);
	PMString strokeColorSwatchName("<unknown>");
	if (db && rubyData.fStrokeColor != kInvalidUID)
	{
		strokeColorSwatchName = Utils<ISwatchUtils>()->GetSwatchName(db, rubyData.fStrokeColor);
		strokeColorSwatchName.Translate();
	}
	SNIPLOG("*StrokeColorUID: 0x%X (%s)", rubyData.fStrokeColor.Get(), strokeColorSwatchName.GetPlatformString().c_str());
	SNIPLOG("*StrokeTint: %f %%", ::ToDouble(rubyData.fStrokeTint));
	SNIPLOG("*StrokeOverprint: %d", rubyData.fStrokeOverprint);
	SNIPLOG("*Outline: %f pt", ::ToDouble(rubyData.fOutline));
	
	SNIPLOG("--- AUTOTCY ---");
	SNIPLOG("*AutoTCYNumDigits: %d", rubyData.fAutoTCYNumDigits);
	SNIPLOG("*AutoTCYIncludeRoman: %s", kSnpBool16Text[rubyData.fAutoTCYIncludeRoman]);
	SNIPLOG("*AutoTCYAutoScale: %s", kSnpBool16Text[rubyData.fAutoTCYAutoScale]);

	SNIPLOG("=== (end) ===");
}


/* CreateRubyStrandIfNeeded
*/
ErrorCode SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded(ITextModel* textModel)
{
	// assume success - in case we encounter an error
	ErrorCode status = kFailure;

	do {
		if (textModel == nil) 
		{
			ASSERT_FAIL("SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded -- textModel is nil");
			break;
		}

		InterfacePtr<IRubyAttrStrand> rubyAttrStrand(
			(IRubyAttrStrand*)textModel->QueryStrand(kRubyAttrStrandBoss, IID_IRUBYATTRSTRAND));

		if (rubyAttrStrand != nil)
		{
			// nothing to do since the ruby strand is there already, 
			// so just exit with success.
			status = kSuccess;
			break; 
		}
		
		// if the Ruby attribute strand isn't there, make one using PrivateCreateStrandCmd
		InterfacePtr<ICommand> createStrandCmd(CmdUtils::CreateCommand(kPrivateCreateStrandCmdBoss));
		if (createStrandCmd == nil) 
		{
			ASSERT_FAIL("SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded -- createStrandCmd is nil");
			break;
		}

		// store the text model UID
		InterfacePtr<IUIDData> textModelUIDRef(createStrandCmd, UseDefaultIID());
		if (textModelUIDRef == nil) 
		{
			ASSERT_FAIL("SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded -- textModelUIDRef is nil");
			break;
		}
		textModelUIDRef->Set(textModel);

		// store the attribute strand of our choice: kRubyAttrStrandBoss 
		InterfacePtr<IClassIDData> strandClassData(createStrandCmd, UseDefaultIID());
		if (strandClassData == nil) 
		{
			ASSERT_FAIL("SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded -- strandClassData is nil");
			break;
		}
		strandClassData->Set(kRubyAttrStrandBoss);

		// create the strand
		status = CmdUtils::ProcessCommand(createStrandCmd);
		if (status != kSuccess) 
		{
			ASSERT_FAIL("SnpPerformTextAttrRuby::CreateRubyStrandIfNeeded -- PrivateCreateStrandCmd failed");
			break;
		}
	} while (false);

	return status;
}

/* GetRubyStrandInfo
*/
ErrorCode SnpPerformTextAttrRuby::GetRubyStrandInfo(const InDesign::TextRange& textRangeToExamine, 
											  InDesign::TextRange& firstRubyStrandRange, 
											  WideString& firstRubyString,
											  bool16& firstRubyAttr)
{
	ErrorCode status = kSuccess; // assume success
	ITextModel* textModel = nil;
	
	bool16 tempRubyAttr = kFalse; 	// indicates if there is ruby
	TextIndex rubyStart = kInvalidTextIndex,	// start index of first ruby strand
			  rubyEnd = kInvalidTextIndex;		// end index of first ruby strand

	// if ruby is false, still return kFailure, unless there is really an error.

	do {
		// Check if the text range is valid.
		if (textRangeToExamine.IsValid() == kFalse) 
		{
			ASSERT_FAIL("textRangeToExamine is invalid");
			status = kFailure;
			break;
		}

		TextIndex start = textRangeToExamine.Start();
		TextIndex end = textRangeToExamine.End();
		textModel = textRangeToExamine.QueryModel();

		// Ruby strand data and Ruby attribute validate check.
		InterfacePtr<IRubyAttrStrand> rubyStrand((IRubyAttrStrand*)textModel->QueryStrand(kRubyAttrStrandBoss, IRubyAttrStrand::kDefaultIID));
		if (rubyStrand == nil)
		{
			// there is no ruby strand, which means there can't be any ruby here.
			// return success, but return tempFirstRubyAttr = kFalse
	        break;
		}
		
		// examine the ruby strand
		int32  numRuby = 0;		// ruby strand counter
		for (int32 index = start; index < end; )
		{
			int32    tempRubyLen, tempRubyStart;
			// check if the ruby attribute is on, and get the run indices
			tempRubyAttr = rubyStrand->GetRubyRun(index, &tempRubyLen, &tempRubyStart);

			if (tempRubyAttr &&    // ruby flag is ON
				((tempRubyStart < index) || // ruby begins before the start index
				(tempRubyStart + tempRubyLen > end) || // ruby continues on beyond selected range
				(tempRubyStart >= start && tempRubyStart < end))) // ruby is within selected range
			{
				// there is ruby
				numRuby++; // increment ruby count
				if (numRuby == 1)
				{    // Get start and end indices corresponding to first found ruby strand
					rubyStart = tempRubyStart;
					rubyEnd = index + tempRubyLen;
				}
				else
				{
					SNIPLOG("NOTE! More than 1 ruby strand found in text range:\n(strand #%d at TextIndex %d Length %d)", 
							numRuby, tempRubyStart, tempRubyLen);
				}
			}
			if (tempRubyLen <= 0)
			{
				// there is no more ruby, exit for-loop
				break;
			}
			// advance index - to see if there is any more ruby
			index += tempRubyLen;
		} // for (...)

		// Get current ruby string at TextIndex(rubyStart ... rubyEnd) to make sure
		if (numRuby >= 1)
		{
			// Query the compose scanner
			InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
			// it would be bad if the composeScanner isn't here
			ASSERT(composeScanner);

            // Query the ruby string attribute
			InterfacePtr<const IAttrReport> rubyStrAttr(composeScanner->QueryAttributeAt(rubyStart, rubyEnd, kTARubyStringBoss));
			// it would be bad if the ruby string attribute isn't here
			ASSERT(rubyStrAttr);

			// Get the ruby string value
            InterfacePtr<ITextAttrWideString> rubyWStr(rubyStrAttr, UseDefaultIID());
            if (rubyWStr)
            {
				firstRubyString = rubyWStr->Get();
			}
			
			// if the ruby string is empty in the ruby strand, consider ruby to be off.
			if (firstRubyString.Length() <= 0)
			{
				tempRubyAttr = kFalse;
				
				// NOTE: this is a situation where the kTARubyAttr is on, but kTARubyString is empty
				// This situation should be avoided!
				ASSERT(firstRubyString.Length() > 0);
			}
		}

	} while (false);

	// set return parameters
	if (status != kSuccess) 
	{
		// return "default" values.
		firstRubyStrandRange = InDesign::TextRange(nil);
		firstRubyAttr = kFalse;
		firstRubyString.SetCString("");
	}
	else
	{
		// return meaningful values obtained in this method.
		firstRubyStrandRange = InDesign::TextRange(textModel, rubyStart, rubyEnd - rubyStart);
		firstRubyAttr = tempRubyAttr;
		// firstRubyString should already be filled out
	}

	// release text model
	if (textModel != nil) 
	{
		textModel->Release();
	}

	return status;
}

	
// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerPerformTextAttrRuby : public SnpRunnable
{

	/** Indicates the type of operation, as specified by the SnippetRunner parameters. */
	typedef enum 
	{ 
		/** "inspect" operation */
		kInspect,
		/** "apply" operation */
		kApply,
		/** "remove" operation */
		kRemove, 
		/** Cancelled */
		kCancelled
	} eSnipRubyOpcode;

	/** Get parameters and populates the SnpRubyDataSettings. 
	 * 	@param textRange (in) The text range to use as a basis for some ruby 
	 * 		settings, particularly those that depend on the base text.
	 * 	@param rubyData (out) The filled out SnpRubyDataSettings structure. 
	 * 	@return The operation type indicated by the parameters. 
	 */
	eSnipRubyOpcode GetParameters(const InDesign::TextRange& textRange, 
								  SnpRubyDataSettings& rubyData);


public:

	// SnippetRunner framework hooks.

	/** Constructor.
	*/
	_SnpRunnerPerformTextAttrRuby(void);

	/** Destructor..
	*/
	virtual ~_SnpRunnerPerformTextAttrRuby(void);
	
	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@pre SnipRun::CanRun is kTrue
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);

	/** Only present this snippet in the framework's UI if the
		language feature set is Japanese and the product is not
		InCopy.
		@return kTrue if the snippet can be loaded, kFalse otherwise.
	*/
	bool16 CanLoad() const;
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
};

/* Constructor.
*/
_SnpRunnerPerformTextAttrRuby::_SnpRunnerPerformTextAttrRuby(void) 
	: SnpRunnable("PerformTextAttrRuby")
{
	this->SetDescription("Shows how to apply, remove, and inspect ruby text attributes.");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformTextAttrRuby::~_SnpRunnerPerformTextAttrRuby(void)
{
	// do nothing.
}



/* GetParameters
*/
_SnpRunnerPerformTextAttrRuby::eSnipRubyOpcode 
	_SnpRunnerPerformTextAttrRuby::GetParameters(const InDesign::TextRange& textRange, 
                                          SnpRubyDataSettings& rubyData)
{
	// set return opcode
	_SnpRunnerPerformTextAttrRuby::eSnipRubyOpcode opcode = _SnpRunnerPerformTextAttrRuby::kCancelled;
	
	// create a parameter utils to use in this method
	Utils<ISnipRunParameterUtils> parameterUtils;
	K2Vector<PMString> choices;

	do {
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}

        // first, get a choice of operations
		choices.clear();
		choices.push_back(PMString("inspect ruby (default)"));	// 0 - shows ruby attribute details on sniplog.
		choices.push_back(PMString("apply ruby"));				// 1 - specify the ruby type (mono or group) and ruby text,
		choices.push_back(PMString("remove ruby"));				// 2 - the ruby under the current selected text is removed.
	
		int32 choice = parameterUtils->GetChoice(PMString("What operation do you want to perform?"), choices, 0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			opcode = _SnpRunnerPerformTextAttrRuby::kCancelled;
			break;
		}
		
		switch (choice) 
		{
		case 0:
			// (option 0) inspect
			// (inspects ruby attributes, prints error if there is no ruby on current text)
			opcode = _SnpRunnerPerformTextAttrRuby::kInspect;
			SNIPLOG("(Option 0): inspect");
			break;

		case 1:
			{
				// (option 1) apply mono|group rubyString 
				// (allow spaces in 'rubyString')
				SNIPLOG("(Option 1): apply");
				opcode = _SnpRunnerPerformTextAttrRuby::kApply;
			
				// set the default ruby data
				SnpPerformTextAttrRuby instance;
				instance.SetRubyData(textRange, rubyData);
				
				// get the user selected type (mono or group)
				choices.clear();
				choices.push_back(PMString("mono ruby (default)")); // 0
				choices.push_back(PMString("group ruby")); // 1
				choice = parameterUtils->GetChoice(PMString("Select the type of ruby to apply."), choices, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					opcode = _SnpRunnerPerformTextAttrRuby::kCancelled;
					break;
				}
                // set the moji ruby attribute according to the parameters
				rubyData.fMojiRuby = (choice == 0) ? kTrue : kFalse;
		
                // gather the ruby string
				PMString rubyString = parameterUtils->GetPMString("Specify the ruby text. Delimit mono ruby text by [space] (e.g. \"ni hon go\").");
				if (parameterUtils->WasDialogCancelled()) 
				{
					opcode = _SnpRunnerPerformTextAttrRuby::kCancelled;
					break;
				}
				if (rubyString.empty() == kFalse) 
				{
					// strip the leading and trailing white space
					rubyString.StripWhiteSpace(PMString::kLeadingAndTrailingWhiteSpace);
					SNIPLOG("   %s", rubyString.GetPlatformString().c_str());
		
					// set the ruby string field. (convert if it has embedded UNICODE)
					rubyData.fString.SetCString(rubyString.GetPlatformString().c_str(), kTrue);
				}
			}
			break;
		
		case 2:
			// (option 2) remove 
			// (deletes current ruby, prints error if there is no ruby on current text)
			opcode = _SnpRunnerPerformTextAttrRuby::kRemove;
			SNIPLOG("(Option 2): remove");
			break;

		default:
			opcode = _SnpRunnerPerformTextAttrRuby::kInspect;
			SNIPLOG("Invalid option - using \"inspect\"");
			break;
		}
	} while (false);

	return opcode;
}


/* CanRun
*/
bool16 _SnpRunnerPerformTextAttrRuby::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	// we need a text focus in order to run this snippet
	do {
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) 
		{
			break;
		}
		
		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			break;
		}

		// make sure the composer is a Japanese composer
		ClassID composerClass(kInvalidClass);
		ErrorCode status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose ruby attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			break;
		}

		// if we got to this point, we can run this snippet.
		result = kTrue;
	} while(false);
	return result;
}


/* Run
*/
ErrorCode _SnpRunnerPerformTextAttrRuby::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do
	{
		SnpPerformTextAttrRuby instance;
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		if (textFocus == nil) 
		{
			SNIPLOG("You do not have any text selection - please select some text first.");
			break;
		}

		// Get the text range
		InDesign::TextRange textRange(textFocus);
		if (textRange.IsValid() == kFalse)
		{
			SNIPLOG("The textRange is invalid!");
			break;
		}

		// make sure the composer is a Japanese composer
		ClassID composerClass(kInvalidClass);
		status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose ruby attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			SNIPLOG("The selected text is not using a Japanese text composer, "
					"so ruby attributes will not compose properly.\n"
					"Please use a Japanese paragraph or single-line composer.");
			break;
		}

		// create a local SnpRubyDataSettings strcture to pass around.
		SnpRubyDataSettings data;

		// get the parameters
		_SnpRunnerPerformTextAttrRuby::eSnipRubyOpcode opcode = this->GetParameters(textRange, data);
		
		switch (opcode) 
		{
		case _SnpRunnerPerformTextAttrRuby::kApply:
			status = instance.ApplyRuby(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrRuby::kRemove:
			status = instance.RemoveRuby(textRange);
			break;
		
		case _SnpRunnerPerformTextAttrRuby::kInspect:
			status = instance.InspectRuby(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrRuby::kCancelled:
			status = kCancel;
			break;

		default:
			SNIPLOG("Invalid option. Skipping.");
			break;
		}
		
	} while (false);
	return status;
}

/* 
*/
bool16  _SnpRunnerPerformTextAttrRuby::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsLanguageFS(kJapaneseLanguageFS) == kFalse) {
		// Only load under the Japanese language feature set.
		result = kFalse;
	}
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS) == kTrue) {
		// Don't load under InCopy product.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformTextAttrRuby instance_SnpRunnerPerformTextAttrRuby;
DEFINE_SNIPPET(_SnpRunnerPerformTextAttrRuby) 	

//End, SnpPerformTextAttrRuby.cpp

