//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformTextAttrKenten.cpp $
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
#include "TextChar.h"
#include "TextID.h"
#include "TextRange.h"
#include "Utils.h"
#include "WideString.h"

// Interface includes:
#include "IAttrReport.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "IDataBase.h"
#include "IEncodingUtils.h"
#include "IFontFamily.h"
#include "IKentenStyle.h"
#include "ISelectUtils.h"
#include "ISwatchList.h"
#include "ISwatchUtils.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrClassID.h"
#include "ITextAttrFont.h"
#include "ITextAttrInt16.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttrUID.h"
#include "ITextAttrUtils.h"
#include "ITextFocus.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "ITextUtils.h"
#include "LocaleSetting.h"

#include "SnpTextAttrHelper.h"


/** Number of kenten kinds
 */	
static const int16 kSnpNumKentenKinds = 12;

/** Kenten kind name table
 */
static const char* kSnpKentenKindTable[kSnpNumKentenKinds] = { 
	"None", 			// 0, or IKentenStyle::Kenten_None
	"BlackSesameDot",  	// 1, or IKentenStyle::Kenten_BlackSesameDot
	"WhiteSesameDot", 	// 2, or IKentenStyle::Kenten_WhiteSesameDot
	"Fisheye", 			// 3, or IKentenStyle::Kenten_Fisheye
	"BlackCircle", 		// 4, or IKentenStyle::Kenten_BlackCircle
	"SmallBlackCircle", // 5, or IKentenStyle::Kenten_SmallBlackCircle
	"Bullseye", 		// 6, or IKentenStyle::Kenten_Bullseye
	"BlackTriangle", 	// 7, or IKentenStyle::Kenten_BlackTriangle
	"WhiteTriangle", 	// 8, or IKentenStyle::Kenten_WhiteTriangle
	"WhiteCircle", 		// 9, or IKentenStyle::Kenten_WhiteCircle
	"SmallWhiteCircle", // 10, or IKentenStyle::Kenten_SmallWhiteCircle
	"Custom"  		// 11, or IKentenStyle::Kenten_Custom
};

/** Bool text lookup
 */
static const char* kSnpBool16Text[2] =  { "False", "True" };

/** Kenten alignment type text lookup
 */
static const char* kSnpKentenAlignmentTypeText[3] = { "Left", "Center", "Right"};

/**	Kenten character set text lookup
 */
static const char* kSnpKentenCharacterSetText[4] = { "ShiftJIS", "JIS", "Unicode", "Kuten"};

// TODO align with coding conventions
/**
 * 	Stores all Kenten related attributes in a single structure.
 * 	Note that this sample only sets a few of the members, however
 * 	all members are inspected.
 * 	All member variables correspond to a kenten attribute.
 */
struct SnpKentenDataSettings
{
	// (Kenten Panel selectable dialog 1) general kenten settings

	/**	Specifies the kenten dot kind. 
	 * 	typecast to int16 for the attribute.
	 * 	@see kTAKentenKindBoss */
	/*IKentenStyle::KentenKind*/ int16 fKind;
	
	/**	Species the size of kenten dot character in points. 
	 * 	-1.0 for automatic.
	 * 	@see kTAKentenSizeBoss */
	PMReal fSize;

	/**	Specifies relative size of kenten dot.
	 * 	@see kTAKentenRelatedSizeBoss */
	PMReal fRelatedSize;
	
	/**	Specifies X-scale of kenten dot. (%/100, i.e. 0.0-1.0 = 0-100%)
	 * 	Note that in a vertical text story, X increases downwards.
	 * 	@see kTAKentenXScaleBoss */
	PMReal fXScale;
	
	/**	Specifies Y-scale of kenten dot. (%/100, i.e. 0.0-1.0 = 0-100%)
	 * 	Note that in a vertical text story, Y increases to the left.
	 * 	@see kTAKentenYScaleBoss */
	PMReal fYScale; 

	/**	Specifies the distance of kenten dot from the base text.
	 * 	In points.
	 * 	@see kTAKentenYOffsetBoss */
	PMReal fYOffset;
	
	/**	Specifies alignment to top/left or center of characters.
	 * 	0-top/left, 
	 * 	1-center, 
	 * 	2-bottom/right (not shown in UI)
	 * 	@see kTAKentenAlignmentBoss 
	 * 	@see IKentenStyle::AlignmentType */
	IKentenStyle::AlignmentType fAlignment;

	/**	Specifies location of kenten dot.
	 * 	above/right (kTrue) or below/left (kFalse)
	 * 	@see kTAKentenPositionBoss */
	bool16 fPosition;
	
	/**	Specifies kenten dot font family (UID). 
	 * 	kInvalidUID if same as base character.
	 * 	@see kTAKentenFontFamilyBoss */
	UID fFontFamily;
	
	/**	Specifies font style string.  
	 * 	Depends on font family.
	 * 	@see kTAKentenFontStyleBoss */
	PMString fFontStyle;
	
	/**	Specifies character set for special kenten character.
	 * 	Used only if kenten kind is IKentenStyle::Kenten_Custom.
	 * 		kShiftJIS = 0,
	 *		kJIS = 1, 
	 *		kUnicode = 2,
	 *		kKuten = 3
	 * 	@see kTAKentenCharacterSetBoss 
	 * 	@see IKentenStyle */
	int16 fCharacterSet;

	/**	Specifies the kenten character.
	 *  Used only kenten if kind is IKentenStyle::Kenten_Custom.
	 * 	NOTE: This is limited to a 16-bit signed integer.
	 * 	@see kTAKentenCharacterBoss */
	int16 fCharacter; 


    // (Kenten Panel selectable dialog 2) kenten color settings

	/**	Specifies the color of kenten dot.
	 * 	@see kTAKentenColorBoss */
	UID fColor;
	
	/**	Specifies the tint (in %) of the kenten dot.
	 * 	@see kTAKentenTintBoss */
	PMReal fTint;
	
	/**	Specifies if overprint on or off.
	 * 	Auto = -1;
	 * 	Off = 0;
	 * 	On = 1
     * 	@see kTAKentenOverprintBoss */
	int16 fOverprint;
	
	/**	Specifies of the color (UID) of the kenten stroke.
	 * 	@see kTAKentenStrokeColorBoss */
	UID fStrokeColor;
	
	/**	Specifies the tint (in %) of the kenten stroke.
	 * 	@see kTAKentenStrokeTintBoss */
	PMReal fStrokeTint;
	
	/**	Specifies if the kenten stroke overprint is on or off.
	 * 	Auto = -1;
	 * 	Off = 0;
	 * 	On = 1
	 * 	@see kTAKentenStrokeOverprintBoss */
	int16 fStrokeOverprint;
	
	/**	Specifies the width (in points) of the kenten stroke.
	 *  Auto = -1.0;
	 * 	Otherwise specify the stroke width in points.
	 * 	@see kTAKentenOutlineBoss */
	PMReal fOutline;
};


/** 
	\li How to apply, remove, and inspect kenten text attributes.
	
	This snippet is an extension of what used to be the KentenCreatorJ sample plug-in. 

	@ingroup sdk_snippet
	@ingroup sdk_text
	@ingroup sdk_cjk
	@see IAttrReport
	@see IComposeScanner
	@see IKentenStyle
	@see ITextAttrBoolean
	@see ITextAttrClassID
	@see ITextAttrFont
	@see ITextAttrInt16
	@see ITextAttrRealNumber
	@see ITextAttrUID
	@see ITextAttrUtils
	@see ITextFocus
	@see ITextModel
	@see ITextTarget
	@see ITextUtils
*/
class SnpPerformTextAttrKenten 
{
public:
	/** Constructor.  
	*/
	SnpPerformTextAttrKenten() {}

	/** Destructor..
	*/
	virtual ~SnpPerformTextAttrKenten() {}

	/**	Applies kenten attributes onto the specified text model range.
	 * 	@param textRange (in) The text range to which you want to apply kenten.
	 * 	@param kentenData (in) The kenten settings.  Use SetKentenData() to fill in the members. 
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ApplyKenten(const InDesign::TextRange& textRange, const SnpKentenDataSettings& kentenData);

	/**	Removes (or simply turns off) kenten attributes from the specified text model range.
	 * 	@param textRange (in) The text range from which you want to remove kenten.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode RemoveKenten(const InDesign::TextRange& textRange);

	/**	Inspects kenten attributes over the specified text model range.
	 * 	The details are printed onto the SNIPLOG.
	 * 	@param textRange (in) The text range from which you want to inspect kenten.
	 * 	@param kentenData (out) The kenten settings. 
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode InspectKenten(const InDesign::TextRange& textRange, SnpKentenDataSettings& kentenData);
	
	/** Sets the SnpKentenDataSettings structure.
	 * 	@param textRange (in) The text range to use as a basis for some kenten 
	 * 		settings, particularly those that depend on the base text.
	 * 	@param kentenData (out) The kenten settings that can be passed on to ApplyKenten().
	 */
	void SetKentenData(const InDesign::TextRange& textRange, SnpKentenDataSettings& kentenData);
	
	/** Reports kenten data to SNIPLOG.
	 * 	@param kentenData (in) The kenten settings.  
	 * 	@param db (in) Database for getting the swatch names.
	 */
	void ReportKentenData(const SnpKentenDataSettings& kentenData, IDataBase* db);



};


/* ApplyKenten
*/
ErrorCode SnpPerformTextAttrKenten::ApplyKenten(const InDesign::TextRange& textRange, 
										  const SnpKentenDataSettings& kentenData)
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
		if (rangeData.Length() <= 0)
		{
			SNIPLOG("You must have a positive number of text characters selected. Please try again.");
			break;
		}
        
		// create an AttributeBossList so we can apply all attributes in one operation.
		boost::shared_ptr<AttributeBossList> attrList (new AttributeBossList);
		if (attrList.get() == nil) 
		{
			ASSERT(attrList);
			break;
		}
        InterfacePtr<IAttrReport> attr01(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenKindBoss, kentenData.fKind));
		attrList->ApplyAttribute(attr01);
		InterfacePtr<IAttrReport> attr02(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenSizeBoss, kentenData.fSize));
		attrList->ApplyAttribute(attr02);
		InterfacePtr<IAttrReport> attr03(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenRelatedSizeBoss, kentenData.fRelatedSize));
		attrList->ApplyAttribute(attr03);
		InterfacePtr<IAttrReport> attr04(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenXScaleBoss, kentenData.fXScale));
		attrList->ApplyAttribute(attr04);
		InterfacePtr<IAttrReport> attr05(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenYScaleBoss, kentenData.fYScale));
		attrList->ApplyAttribute(attr05);
		InterfacePtr<IAttrReport> attr06(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenYOffsetBoss, kentenData.fYOffset));
		attrList->ApplyAttribute(attr06);
		InterfacePtr<IAttrReport> attr07(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenAlignmentBoss, kentenData.fAlignment));
		attrList->ApplyAttribute(attr07);
		InterfacePtr<IAttrReport> attr08(SnpTextAttrHelper::CreateTextBool16Attribute(kTAKentenPositionBoss, kentenData.fPosition));
		attrList->ApplyAttribute(attr08);
		InterfacePtr<IAttrReport> attr09(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, ITextAttrUID::ValueType>(kTAKentenFontFamilyBoss, kentenData.fFontFamily));
		attrList->ApplyAttribute(attr09);
		InterfacePtr<IAttrReport> attr10(SnpTextAttrHelper::CreateTextFontStyleAttribute(kTAKentenFontStyleBoss, kentenData.fFontStyle));
		attrList->ApplyAttribute(attr10);
		InterfacePtr<IAttrReport> attr11(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenCharacterSetBoss, kentenData.fCharacterSet));
		attrList->ApplyAttribute(attr11);
		InterfacePtr<IAttrReport> attr12(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenCharacterBoss, kentenData.fCharacter));
		attrList->ApplyAttribute(attr12);
		InterfacePtr<IAttrReport> attr13(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, ITextAttrUID::ValueType>(kTAKentenColorBoss, kentenData.fColor));
		attrList->ApplyAttribute(attr13);
		InterfacePtr<IAttrReport> attr14(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenTintBoss, kentenData.fTint));
		attrList->ApplyAttribute(attr14);
		InterfacePtr<IAttrReport> attr15(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenOverprintBoss, kentenData.fOverprint));
		attrList->ApplyAttribute(attr15);
		InterfacePtr<IAttrReport> attr16(SnpTextAttrHelper::CreateTextAttribute<ITextAttrUID, ITextAttrUID::ValueType>(kTAKentenStrokeColorBoss, kentenData.fStrokeColor));
		attrList->ApplyAttribute(attr16);
		InterfacePtr<IAttrReport> attr17(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenStrokeTintBoss, kentenData.fStrokeTint));
		attrList->ApplyAttribute(attr17);
		InterfacePtr<IAttrReport> attr18(SnpTextAttrHelper::CreateTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(kTAKentenStrokeOverprintBoss, kentenData.fStrokeOverprint));
		attrList->ApplyAttribute(attr18);
		InterfacePtr<IAttrReport> attr19(SnpTextAttrHelper::CreateTextAttribute<ITextAttrRealNumber, ITextAttrRealNumber::ValueType>(kTAKentenOutlineBoss, kentenData.fOutline));
		attrList->ApplyAttribute(attr19);

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

	} while(false);
	return status;
}

/* RemoveKenten
*/
ErrorCode SnpPerformTextAttrKenten::RemoveKenten(const InDesign::TextRange& textRange)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
	
		// check if kenten is on
		int16 kind = IKentenStyle::Kenten_None;
	
		// Get kenten kind
        status = SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKentenKindBoss, kind);
		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (kind == IKentenStyle::Kenten_None) 
		{
			SNIPLOG("Kenten is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			status = kSuccess;
			break;
		}

		// set kenten to none.
		status = SnpTextAttrHelper::SetTextInt16Attribute(textRange, kTAKentenKindBoss, IKentenStyle::Kenten_None);

	
	} while (false);
	return status;
}


/* InspectKenten
*/
ErrorCode SnpPerformTextAttrKenten::InspectKenten(const InDesign::TextRange& textRange, 
											SnpKentenDataSettings& kentenData)
{
	ErrorCode status = kFailure;
	do {
	
		// Check if the text range is valid.
		if (textRange.IsValid() == kFalse) 
		{
			SNIPLOG("textRange is invalid - you must have some text selected first.");
			break;
		}
	
		// check if kenten is on
		int16 kind = IKentenStyle::Kenten_None;
	
		// Get kenten kind
        status = SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKentenKindBoss, kind);
		if (status != kSuccess)
		{
			// GetTextAttribute reported the error, so just exit.
			break;
		}
		else if (kind == IKentenStyle::Kenten_None) 
		{
			SNIPLOG("Kenten is not turned at the text selection... Skipping.");
			// exit with status == kSuccess
			status = kSuccess;
			break;
		}
	
		// get all kenten attributes
		// (Kenten Panel selectable dialog 1) general kenten settings
		kentenData.fKind = kind;
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenSizeBoss, kentenData.fSize);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenRelatedSizeBoss, kentenData.fRelatedSize);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenXScaleBoss, kentenData.fXScale);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenYScaleBoss, kentenData.fYScale);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenYOffsetBoss, kentenData.fYOffset);
		int16 alignment;
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKentenAlignmentBoss, alignment);
		kentenData.fAlignment = (IKentenStyle::AlignmentType) alignment;
		SnpTextAttrHelper::GetTextBool16Attribute(textRange, kTAKentenPositionBoss, kentenData.fPosition);

		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(textRange, kTAKentenFontFamilyBoss, kentenData.fFontFamily);
		SnpTextAttrHelper::GetTextFontStyleAttribute(textRange, kTAKentenFontStyleBoss, kentenData.fFontStyle);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKentenCharacterSetBoss, kentenData.fCharacterSet);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, ITextAttrInt16::ValueType>(textRange, kTAKentenCharacterBoss, kentenData.fCharacter);


		// (Kenten Panel selectable dialog 2) kenten color settings
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(textRange, kTAKentenColorBoss, kentenData.fColor);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenTintBoss, kentenData.fTint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, int16>(textRange, kTAKentenOverprintBoss, kentenData.fOverprint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID, UID>(textRange, kTAKentenStrokeColorBoss, kentenData.fStrokeColor);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenStrokeTintBoss, kentenData.fStrokeTint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrInt16, int16>(textRange, kTAKentenStrokeOverprintBoss, kentenData.fStrokeOverprint);
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber, PMReal>(textRange, kTAKentenOutlineBoss, kentenData.fOutline);
	
		// get database of text model
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		IDataBase* db = ::GetDataBase(textModel);

		// report this to SnipLog
		this->ReportKentenData(kentenData, db);
	
		status = kSuccess;
	} while (false);
	return status;
}

/* SetKentenData
*/
void SnpPerformTextAttrKenten::SetKentenData(const InDesign::TextRange& textRange, 
									   SnpKentenDataSettings& kentenData)
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

		// (Kenten Panel selectable dialog 1) general kenten settings
		
		// set the kenten kind to none by default
        kentenData.fKind = IKentenStyle::Kenten_None;

		// get current point size
		PMReal pointSize;
		SnpTextAttrHelper::GetTextAttribute<ITextAttrRealNumber>(textRange, kTextAttrPointSizeBoss, pointSize);
		kentenData.fSize = -1; // -1 means automatic,otherwise, based on parent font size (in points) 
		
		kentenData.fRelatedSize = 0.5;
		kentenData.fXScale = 0.75; // %/100
		kentenData.fYScale = 1.25; // %/100
		kentenData.fYOffset = -0.5; // pt (negative means "left" in a vertical frame)
		kentenData.fAlignment = IKentenStyle::kLeft; // top/left
		kentenData.fPosition = kFalse; // right/above
		
		UID fontUID = kInvalidUID;
		// get the current font UID
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID>(textRange, kTextAttrFontUIDBoss, fontUID);
		kentenData.fFontFamily = kInvalidUID; // use the same font (kInvalidUID) as the text itself
		
		PMString fontStyle("");
		SnpTextAttrHelper::GetTextFontStyleAttribute(textRange, kTextAttrFontStyleBoss, fontStyle);
		kentenData.fFontStyle = fontStyle;
		kentenData.fCharacter = kTextChar_Null; // 0
		kentenData.fCharacterSet = IKentenStyle::kShiftJIS;

		// (Kenten Panel selectable dialog 2) kenten color settings
		UID fontColorUID = kInvalidUID;
		SnpTextAttrHelper::GetTextAttribute<ITextAttrUID>(textRange, kTextAttrColorBoss, fontColorUID);

		kentenData.fColor = fontColorUID;  // just use the same color as the base text for the kenten
		kentenData.fTint = 100.0; // full tint
		kentenData.fOverprint = (int16) kTrue; // NOTE: kTrue = 1
		
		UID noneSwatchUID = swatchList->GetNoneSwatchUID();
		ASSERT(noneSwatchUID != kInvalidUID);
		
		kentenData.fStrokeColor = fontColorUID; // or noneSwatchUID; 
		kentenData.fStrokeTint = 50.0; // lighter stroke tint
		kentenData.fStrokeOverprint = (int16) kTrue; // NOTE: kTrue = 1
		kentenData.fOutline = 0.25; // (points) kenten outline stroke width

		status = kSuccess;

	} while (false);
	ASSERT(status == kSuccess);
}


/* ReportKentenData
*/
void SnpPerformTextAttrKenten::ReportKentenData(const SnpKentenDataSettings& kentenData, IDataBase* db)
{
	SNIPLOG("=== SnpKentenDataSettings (begin) ===");
	SNIPLOG("--- GENERAL SETTINGS ---");
	SNIPLOG("*Kind: %s", kSnpKentenKindTable[kentenData.fKind]);
	SNIPLOG("*Size: %f pt", ::ToDouble(kentenData.fSize));
	SNIPLOG("*RelatedSize: %f", ::ToDouble(kentenData.fRelatedSize));
	SNIPLOG("*XScale: %f", ::ToDouble(kentenData.fXScale));
	SNIPLOG("*YScale: %f", ::ToDouble(kentenData.fYScale));
	SNIPLOG("*YOffset: %f pt", ::ToDouble(kentenData.fYOffset));
	SNIPLOG("*Alignment: %s", kSnpKentenAlignmentTypeText[kentenData.fAlignment]);
	SNIPLOG("*Position: %s", kSnpBool16Text[kentenData.fPosition]);
	SNIPLOG("*FontUID: 0x%X", kentenData.fFontFamily.Get());
	SNIPLOG("*FontStyle: %s", kentenData.fFontStyle.GetPlatformString().c_str());
	PMString kentenCharacterString;
	kentenCharacterString.InsertW((textchar)kentenData.fCharacter);
	SNIPLOG("*Character: %s (Unicode 0x%X)", kentenCharacterString.GetPlatformString().c_str(), kentenData.fCharacter);
	SNIPLOG("*CharacterSet: %s", kSnpKentenCharacterSetText[kentenData.fCharacterSet]);

	SNIPLOG("--- COLOR ---");
	PMString colorSwatchName("<unknown>");
	if (db && kentenData.fColor != kInvalidUID)
	{
		colorSwatchName = Utils<ISwatchUtils>()->GetSwatchName(db, kentenData.fColor);
		colorSwatchName.Translate();
	}
    SNIPLOG("*ColorUID: 0x%X (%s)", kentenData.fColor.Get(), colorSwatchName.GetPlatformString().c_str());
	SNIPLOG("*Tint: %f %%", ::ToDouble(kentenData.fTint));
	SNIPLOG("*Overprint: %d", kentenData.fOverprint);
	PMString strokeColorSwatchName("<unknown>");
	if (db && kentenData.fStrokeColor != kInvalidUID)
	{
		strokeColorSwatchName = Utils<ISwatchUtils>()->GetSwatchName(db, kentenData.fStrokeColor);
		strokeColorSwatchName.Translate();
	}
	SNIPLOG("*StrokeColorUID: 0x%X (%s)", kentenData.fStrokeColor.Get(), strokeColorSwatchName.GetPlatformString().c_str());
	SNIPLOG("*StrokeTint: %f %%", ::ToDouble(kentenData.fStrokeTint));
	SNIPLOG("*StrokeOverprint: %d", kentenData.fStrokeOverprint);
	SNIPLOG("*Outline: %f pt", ::ToDouble(kentenData.fOutline));

	SNIPLOG("=== (end) ===");
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerPerformTextAttrKenten : public SnpRunnable
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
	} eSnipKentenOpcode;
	
	/** Get parameters and populates the SnpKentenDataSettings. 
	 * 	@param textRange (in) The text range to use as a basis for some kenten 
	 * 		settings, particularly those that depend on the base text.
	 * 	@param kentenData (out) The filled out SnpKentenDataSettings structure. 
	 * 	@return The operation type indicated by the parameters. 
	 */
	eSnipKentenOpcode GetParameters(const InDesign::TextRange& textRange, 
									SnpKentenDataSettings& kentenData);

public:

	// SnippetRunner framework hooks.

	/** Constructor.  
	*/
	_SnpRunnerPerformTextAttrKenten(void);

	/** Destructor..
	*/
	virtual ~_SnpRunnerPerformTextAttrKenten(void);

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
_SnpRunnerPerformTextAttrKenten::_SnpRunnerPerformTextAttrKenten(void) 
	: SnpRunnable("PerformTextAttrKenten")
{
	this->SetDescription("Shows how to apply, remove, and inspect kenten text attributes.");
	this->SetPreconditions("some text must be selected");
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformTextAttrKenten::~_SnpRunnerPerformTextAttrKenten(void)
{
	// do nothing.
}



/* GetParameters
*/
_SnpRunnerPerformTextAttrKenten::eSnipKentenOpcode 
	_SnpRunnerPerformTextAttrKenten::GetParameters(const InDesign::TextRange& textRange, 
							    			SnpKentenDataSettings& kentenData)
{
	// set return opcode
	_SnpRunnerPerformTextAttrKenten::eSnipKentenOpcode opcode = _SnpRunnerPerformTextAttrKenten::kCancelled;
	
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
		choices.push_back(PMString("inspect kenten (default)"));	// 0 - shows kenten attribute details on sniplog.
		choices.push_back(PMString("apply kenten"));				// 1 - specify the kenten kind. If "Custom, specify the kenten character after a space
		choices.push_back(PMString("remove kenten"));				// 2 - the kenten under the current selected text is removed.

		int32 choice = parameterUtils->GetChoice(PMString("What operation do you want to perform?"), choices, 0);
		if (parameterUtils->WasDialogCancelled()) 
		{
			opcode = _SnpRunnerPerformTextAttrKenten::kCancelled;
			break;
		}
		
		// examine the choice
		switch (choice) 
		{
		
		case 0:
			// (option 0) inspect
			// (inspects kenten attributes, prints message if there is no kenten on current text)
			opcode = _SnpRunnerPerformTextAttrKenten::kInspect;
			SNIPLOG("(Option 0): inspect");
			break;
		
		case 1:
			{
				// (option 1) apply kind [char] 
				SNIPLOG("(Option 1): apply");
				opcode = _SnpRunnerPerformTextAttrKenten::kApply;
	
				// set the default kenten data
				// sets kind as "none" by default
				SnpPerformTextAttrKenten instance;
				instance.SetKentenData(textRange, kentenData);
	
				// set the kenten kind attribute according to the next choice
				choices.clear();
				choices.push_back(PMString("None")); // 0
				choices.push_back(PMString("BlackSesameDot (default)")); // 1
				choices.push_back(PMString("WhiteSesameDot")); // 2
				choices.push_back(PMString("Fisheye")); // 3
				choices.push_back(PMString("BlackCircle")); // 4
				choices.push_back(PMString("SmallBlackCircle")); // 5
				choices.push_back(PMString("Bullseye")); // 6
				choices.push_back(PMString("BlackTriangle")); // 7
				choices.push_back(PMString("WhiteTriangle")); // 8
				choices.push_back(PMString("WhiteCircle")); // 9
				choices.push_back(PMString("SmallWhiteCircle")); // 10 (0xA)
				choices.push_back(PMString("Custom")); // 11 (0xB)
				choice = parameterUtils->GetChoice(PMString("Which kind of kenten do you want to apply?"), choices, 1);
				if (parameterUtils->WasDialogCancelled()) 
				{
					opcode = _SnpRunnerPerformTextAttrKenten::kCancelled;
					break;
				}

				kentenData.fKind = choice; // IKentenStyle::KentenKind
				SNIPLOG("   %s", kSnpKentenKindTable[choice]);
	
				if (kentenData.fKind == IKentenStyle::Kenten_Custom) 
				{
					// Gather the rest of the string as the custom kenten character 
					// Since the text edit box only accomodates platform chararacters, 
					// assume "Platform" character set.(ShiftJIS on Japanese UI locale)
					PMString defaultKentenString;
					defaultKentenString.InsertW(UTF32TextChar((uint32)kTextChar_CJKPostalMarkFace));
					PMString customKentenString = parameterUtils->GetPMString("Enter a custom kenten character (only the first char will be used)", defaultKentenString);
					if (parameterUtils->WasDialogCancelled()) 
					{
						opcode = _SnpRunnerPerformTextAttrKenten::kCancelled;
						break;
					}

					// remove all white spaces
					customKentenString.StripWhiteSpace();
					// set default value for kenten character code (Unicode)
					int16 kentenCharW = kTextChar_Null;
					if (customKentenString.empty() == kFalse) 
					{
						// set the custom kenten character (in Unicode)
						kentenCharW = customKentenString.GetWChar(0).GetValue() & 0x0000FFFF; // get only low 16 bits
					}
					// set the kenten character code
					kentenData.fCharacter = kentenCharW;
					// set the custom kenten character set 
					// (just say it's ShiftJIS, even though we are specifying by Unicode)
					// (this is actually not really used)
					kentenData.fCharacterSet = IKentenStyle::kShiftJIS;
					// display on sniplog
					SNIPLOG("   CustomChar: %s (0x%X)", customKentenString.GetPlatformString().c_str(), kentenCharW);
				}
			}
			break;
	
		case 2:
            // (option 2) remove 
			// (deletes current kenten, prints message if there is no kenten on current text)
			opcode = _SnpRunnerPerformTextAttrKenten::kRemove;
			SNIPLOG("(Option 2): remove");
			break;

		default:
			opcode = _SnpRunnerPerformTextAttrKenten::kInspect;
			SNIPLOG("Invalid option - using \"inspect\"");
			break;
		}
	} while (false);

	return opcode;
}


/* CanRun
*/
bool16 _SnpRunnerPerformTextAttrKenten::CanRun(ISnpRunnableContext* runnableContext)
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

		// check against known text composers that are known to compose kenten attributes correctly
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
ErrorCode _SnpRunnerPerformTextAttrKenten::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpPerformTextAttrKenten instance;
		// we need a text focus in order to run this snippet
		// query the text target from the current context
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			ASSERT(textTarget);
			break;
		}
		// query the text focus (bridge method)
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
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
		// NOTE: Any body of text can carry any set of attributes, however, 
		// this check was added so that when the kenten attributes are applied, 
		// the adornments are properly displayed.
		ClassID composerClass(kInvalidClass);
		status = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);

		// check against known text composers that are known to compose kenten attributes correctly
		if (composerClass != kJParagraphComposerBoss &&
			composerClass != kJSingleComposerBoss) 
		{
			SNIPLOG("The selected text is not using a Japanese text composer, "
					"so kenten attributes will not compose properly.\n"
					"Please use a Japanese paragraph or single-line composer.");
			break;
		}
		
		// create a local SnpKentenDataSettings strcture to pass around.
		SnpKentenDataSettings data;

		// get the parameters
		_SnpRunnerPerformTextAttrKenten::eSnipKentenOpcode opcode = this->GetParameters(textRange, data);
		
		switch (opcode) 
		{
		case _SnpRunnerPerformTextAttrKenten::kApply:
			status = instance.ApplyKenten(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrKenten::kRemove:
			status = instance.RemoveKenten(textRange);
			break;
		
		case _SnpRunnerPerformTextAttrKenten::kInspect:
			status = instance.InspectKenten(textRange, data);
			break;
		
		case _SnpRunnerPerformTextAttrKenten::kCancelled:
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
bool16  _SnpRunnerPerformTextAttrKenten::CanLoad() const
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
static _SnpRunnerPerformTextAttrKenten instance_SnpRunnerPerformTextAttrKenten;
DEFINE_SNIPPET(_SnpRunnerPerformTextAttrKenten) 	

//End, SnpPerformTextAttrKenten.cpp

