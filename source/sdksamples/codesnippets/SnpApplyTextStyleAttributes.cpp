//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpApplyTextStyleAttributes.cpp $
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

// Interface includes:
#include "ICompositionStyle.h"
#include "IDrawingStyle.h"
#include "IDocument.h"
#include "IInkData.h"
#include "IStyleInfo.h"
#include "IStylePositionInfo.h"
#include "IStyleGroupInfo.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ISwatchList.h"
#include "ITextAttrInt16.h"
#include "ITextAttrRealNumber.h"
#include "ITextAttributes.h"
#include "ITextAttrUID.h"
#include "ITextAttrFont.h"
#include "ITextAttrAlign.h"
#include "ITextAttrBoolean.h"
#include "ITextAttrUtils.h"
#include "ITextAttrCapitalMode.h"
#include "IUIDData.h"
#include "IRenderingObject.h"
#include "IAttrReport.h" // for SnpTextAttrHelper.h


#include "IMojikumiStyle.h"
#include "TCID.h"
#include "ITextAttrClassID.h"
#include "ITextModel.h" // use SnpTextAttrHelper
#include "IComposeScanner.h" // use SnpTextAttrHelper
#include "ITextTarget.h"
#include "ITextFocus.h"

#include "ISelectionUtils.h"
#include "ITextAttributeSuite.h"
// General includes:
#include "TextAttrID.h"
#include "TextRange.h"
#include "Utils.h"
#include "LocaleSetting.h"


// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// Depends on turn to read.
#include "SnpTextAttrHelper.h" // namespace SnpTextAttrHelper

/** 
	\li How to apply text attributes that control by high level ITextAttributeSuite API,
	\li How to create and apply of paragraph style and character style,
	\li The attributes that control Underline, SmallAllCaps, Font Variant, Alignment,
		and Japanese Features Character rotete, Tsume, Mojikumi spacing, Jidori, Shatai,
	\li This code snippet is the same as the sample code TextStyler of InDesign 2.0 SDK.

  	@ingroup sdk_snippet
  	@ingroup sdk_text
  	@ingroup sdk_cjk

	@see ITextAttributeSuite
 */
class SnpApplyTextStyleAttributes
{
	public:
		/** Constructor.
		 */
		SnpApplyTextStyleAttributes() {}

		/** Destructor.
		 */
		virtual			~SnpApplyTextStyleAttributes() {}

					
		/** Toggles the underline state. 
			@param suite The active ITextAttributeSuite for the current text selection.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ToggleUnderline(ITextAttributeSuite* suite);
		
		/**	Queries the TextAttributeSuite for the CapsMode attribute.  
			Finding one instance of the normal/small/all caps attribute in the
			selected text range means that it may or may not be applied, and the mode must be
			queried to determine this.  Finding multiple instances means that there is
			a mix of modes (part of the text is small/all caps, part is not).

			@param suite The active ITextAttributeSuite for the current text selection.	
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CycleSmallAllCaps(ITextAttributeSuite* suite);
		
		/** Applies the specified font face, by taking the name of the font variant (e.g.,
			"Bold"), and then querying the text attribute suite to determine how many instances
			of the font variant exist. 
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param typeStyle PMString for the type face name. 
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ApplyFontVariant(ITextAttributeSuite* suite, const PMString& typeStyle);
	
		/** Toggles the Bold font style state. 
			@param suite The active ITextAttributeSuite for the current text selection.		
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ToggleBold(ITextAttributeSuite* suite);
		
		/** Toggles the Italic font style state. 
			@param suite The active ITextAttributeSuite for the current text selection.		
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode ToggleItalic(ITextAttributeSuite* suite);

		/** 
			Alignment is applied by creating a "alignment" attribute applied to text.
			kTextAttrAlignBodyBoss and kTextAttrAlignLastBoss are obsolete,
			and have been replaced with kTextAttrAlignmentBoss.
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param alignment The text alignment.
			@return kSuccess on success, other ErrorCode otherwise.
		*/		
		ErrorCode ApplyAlignment(ITextAttributeSuite* suite,
								const ICompositionStyle::TextAlignment alignment);

		/**
			Create a SDK group to organize the styles created in this snippets, also to demo the new feature available in CS3
			@param document We are creating the style as part of doc workspace, this is the doc associated with the style
			@param styleGroupMgr the doc's style group manager, could be either for char or para style, depends on how you query it.
		*/
		const UID CreateSDKStyleGroup(IDocument* document, IStyleGroupManager* styleGroupMgr);
		
		/**	Creates a paragraph style with all the defaults, but 18 point font size.
			The paragraph style table is first queried so that we can be
			sure the style is not already in the document -- if it is,
			a log message will inform the user that the style
			has already been created and choose a different name.  If the style 
			does not exist, it is created.			
			@param suite The active ITextAttributeSuite for the current text selection.	
			@param 	styleName PMSString for the paragraph style name.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode CreateParaStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document);
		
		/**	Looks up the paragraph style in the corresponding style table. 
			The name of the style is hardcoded. 
			If the UID is found to be valid, the style is applied using the TextAttributeSuite. 
			@param suite The active ITextAttributeSuite for the current text selection.	
			@param styleName PMSString for the paragraph style name.
			@param document Active document.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		 ErrorCode ApplyParaStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document);
		 
		/** Creates a character style with defaults, but blue.
			The character style table is first queried so that we can be
			sure the style is not already in the document -- if it is,
			a log message will inform the user that the style
			has already been created and choose a different name.  If the
			style does not exist, it is created.			
			@param suite The active ITextAttributeSuite for the current text selection.	
			@param styleName PMSString for the character style name.
			@param document Active document.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode CreateCharStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document);
		
		/**	Looks up the character style in the corresponding style table.  
			The name of the style is hardcoded. 
			If the UID is found to be valid, the style is applied using the TextAttributeSuite. 
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param styleName PMSString for the character style name.
			@param document Active document.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode ApplyCharStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document);


		// InDesign Japanese Features.

		/**	InDesign Japanese Feature.
			Incremental rotation to characters individually in the specified angle.
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param angle Angle of character rotation.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode IncrementalCharRotation(ITextAttributeSuite* suite, const PMReal angle);

		/** InDesign Japanese Feature.
			Set the tsume value on the selected text.
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param tsume The Moji-Tsume of the characters by the percent.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode ApplyTsume(ITextAttributeSuite* suite, const PMReal tsume);
		
		/** InDesign Japanese Feature.
			Inserts mojikumi space before or after the characters in the selected text.
			Default is "insert before".
			@param space The percent of the mojikumi spacing.
			@param isBefore Flag indicating if we want to set the mojikumi spacing before or after.  
					Default is "before"(kTrue).
		*/
		ErrorCode ApplyMojikumiSpacing(ITextAttributeSuite* suite, const PMReal space, const bool16 isBefore = kTrue);
				
		/** InDesign Japanese Feature.
			Applies Jidori (effective EmBoxes to occupy) in the selected text.
			Jidori composes the selected characters in the specified number of character-widths.
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param jidori Number of characters for jidori.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode ApplyJidori(ITextAttributeSuite* suite, const int16 jidori);
		
		/**	InDesign Japanese Feature.
			Apply shatai in the selected text.
			Shatai is not Italic,  It is an optical effect applied by a lens.
			Shatai uses a lens magnification (Reduction rate) and an angle parameter.
			@param suite The active ITextAttributeSuite for the current text selection.		
			@param lens Lens magnification (Reduction rate).
			@param angle Shatai angle.
			@return kSuccess if value is successfully set, kFailure otherwise.
		*/
		ErrorCode ApplyShatai(ITextAttributeSuite* suite, const PMReal lens, const PMReal angle);

	
		/**	For paragraphy layout, set single column.  
			@param textModel The text model for the current text selection.
			@param range The text range.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetSingleColumn(ITextModel* textModel, const RangeData& range);
	
		/**	For paragraphy layout, set span columns.  
			@param textModel The text model for the current text selection.
			@param range The text range.
			@param spanNumber The number of the columns which need be spanned.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetSpanColumns(ITextModel* textModel, const RangeData& range, int16 spanNumber);
		
		/**	For paragraphy layout, set split columns.  
			@param textModel The text model for the current text selection.
			@param range The text range.
			@param splitNumber The number of the sub-columns.
			@param insideGutter  The inside gutter of split columns.
			@param outsideGutter The outside gutter of split columns.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetSplitColumns(ITextModel* textModel, const RangeData& range, int16 splitNumber, PMReal insideGutter, PMReal outsideGutter);
		
		// Utils.

		/**	Finds or creates a color in the swatch list,
			returning a UID to the color.
			We use a color swatch for the character style. 
			
			@param	swatchName Swatch Name
			@param	rRed Red (0.0...1.0)
			@param	rGreen Green (0.0...1.0)
			@param	rBlue Blue (0.0...1.0)
			@param document Active document.
			@return returning a UID to the color.
		*/
		const UID ResolveRGBColorSwatch(const PMString& swatchName,
										const PMReal rRed,
										const PMReal rGreen,
										const PMReal rBlue,
										IDocument* document);

		ErrorCode ToggleParaBorder(ITextAttributeSuite* suite);

		ErrorCode ToggleParaShading(ITextAttributeSuite* suite);

		
	private:
		ClassID composerClass;
};


/*	ToggleUnderline
*/
ErrorCode SnpApplyTextStyleAttributes::ToggleUnderline(ITextAttributeSuite* suite)
{
	if (suite == nil)
	{
		return kFailure;
	}

	return suite->ToggleUnderline();
}

/*	CycleSmallAllCaps
*/
ErrorCode SnpApplyTextStyleAttributes::CycleSmallAllCaps(ITextAttributeSuite* suite)
{
	ErrorCode result = kFailure;
	do{
		if (suite == nil)
		{
			break;
		}
		// Find out what the current mode is... assume "kCapNormal"
		IDrawingStyle::CapitalizeMode currentCapMode = IDrawingStyle::kCapNormal;

		int32 count = suite->CountAttributes(kTextAttrCapitalModeBoss);
		if(count != 1){
			SNIPLOG("Mixed capital mode attributes.");
		}
		
		// Query first capital mode attribute.
		InterfacePtr<const ITextAttrCapitalMode> pAttr(static_cast< const ITextAttrCapitalMode*>(suite->QueryAttributeN(0, kTextAttrCapitalModeBoss, IID_ITEXTATTRCAPITALMODE)));
		if(!pAttr){
			break;
		}
				
		currentCapMode = pAttr->Get();

		// Switch to the next mode in the list:
		switch (currentCapMode)
		{
			case IDrawingStyle::kCapNormal:
			{
				result = suite->ToggleCapsMode(IDrawingStyle::kCapSmallLowercase);
				SNIPLOG(" Apply IDrawingStyle::kCapSmallLowercase.");
				break;
			}
			case IDrawingStyle::kCapSmallLowercase:
			{
				result = suite->ToggleCapsMode(IDrawingStyle::kCapAll);
				SNIPLOG(" Apply IDrawingStyle::kCapAll.");
				break;
			}
			case IDrawingStyle::kCapAll:
			{
				result = suite->ToggleCapsMode(IDrawingStyle::kCapSmallEverything);
				SNIPLOG(" Apply IDrawingStyle::kCapSmallEverything.");
				break;
			}
			case IDrawingStyle::kCapSmallEverything:
			{
				result = suite->ToggleCapsMode(IDrawingStyle::kCapNormal);
				SNIPLOG(" Apply IDrawingStyle::kCapNormal.");
				break;
			}
			default:
			{
				break;
			}
		}
	}while(false);
	
	return result;
}

/* 	ApplyFontVariant
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyFontVariant(ITextAttributeSuite* suite, const PMString& typeStyle)
{
	ErrorCode result = kFailure;
	do 
	{
		if (suite == nil)
		{
			ASSERT_FAIL("ITextAttributeSuite is nil");
			break;
		}
		
		// make a local copy of the type style, but don't translate
		PMString localTypeStyle(typeStyle);
		localTypeStyle.SetTranslatable(kFalse);
		
		int32 nFonts = suite->CountFonts();
        for (int32 i = 0; i < nFonts ; i++)
        {
			if (suite->GetNthFont(i) == localTypeStyle)
			{
				// Here's the tricky part: if there is one instance of the variant in the 
				// current text selection, and it's not the font style we're trying to apply, then we don't
				// want to remove it.  If the font style does match, we want to toggle the style
				// be setting it to "normal" type style, which is done with an empty string
				localTypeStyle = "Regular";
				localTypeStyle.SetTranslatable(kFalse);

				break; // out of for-loop
			}
		}

		// create the text attr font style attribute
		InterfacePtr<ITextAttrFont>	attrFont(::CreateObject2<ITextAttrFont>(kTextAttrFontStyleBoss));
		if (attrFont == nil){
			break;
		}
		// set the font style.
		attrFont->SetFontName(localTypeStyle, kFalse);

		// apply the attribute
		result = suite->ApplyAttribute(attrFont);		
	} while (false);
	
	return result;
}

/*	ToggleBold
*/
ErrorCode SnpApplyTextStyleAttributes::ToggleBold(ITextAttributeSuite* suite)
{
	if (suite == nil)
	{
		return kFailure;
	}

	return suite->ToggleBold();
}

/*	ToggleItalic
*/
ErrorCode SnpApplyTextStyleAttributes::ToggleItalic(ITextAttributeSuite* suite)
{
	if (suite == nil)
	{
		return kFailure;
	}

	return suite->ToggleItalic();
}


/*	ApplyAlignment
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyAlignment(ITextAttributeSuite* suite, const ICompositionStyle::TextAlignment alignment)
{
	ErrorCode result = kFailure;
	do
	{
		if (suite == nil)
		{
			ASSERT_FAIL("ITextAttributeSuite is nil");
			break;
		}
		
		result = suite->SetAlignment(alignment);
	}while(false);
	
	return result;
}

/* CreateSDKStyleGroup
*/
const UID	SnpApplyTextStyleAttributes::CreateSDKStyleGroup(IDocument* document, IStyleGroupManager* styleGroupMgr)
{
	UID sdkGroupUID = kInvalidUID;
	do
	{
		if (!document || !styleGroupMgr)
		{
			ASSERT_FAIL("kCreateStyleGroupCmdBoss failed");
			break;
		}
		PMString sdkGroupName("SDK Style Group");
		sdkGroupUID = styleGroupMgr->FindByName(sdkGroupName);
		if (sdkGroupUID == kInvalidUID)	// group already exist, find its path
		{
			InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kCreateStyleGroupCmdBoss));
			if (!cmd)
			{
				ASSERT_FAIL("kCreateStyleGroupCmdBoss invalid");
				break;
			}
			// Set the UIDList with the document:
			cmd->SetItemList(UIDList(document->GetDocWorkSpace()));
			InterfacePtr<IStyleGroupInfo> styleSetInfo(cmd,UseDefaultIID());
			ASSERT(styleSetInfo);
			styleSetInfo->SetName(sdkGroupName);
			
			InterfacePtr<IStylePositionInfo> sdkGroupPosInfo(cmd,UseDefaultIID());
			ASSERT(sdkGroupPosInfo);
			sdkGroupPosInfo->SetParent(styleGroupMgr->GetRootHierarchy());
			ErrorCode result = kFailure;
			result = CmdUtils::ProcessCommand(cmd);
			if (result != kSuccess)
			{
				ASSERT_FAIL("kCreateStyleGroupCmdBoss failed");
				break;
			}
			sdkGroupUID = styleGroupMgr->FindByName(sdkGroupName);
		}
	} while (false);
	return sdkGroupUID;
}

/*	CreateParaStyle
*/
ErrorCode SnpApplyTextStyleAttributes::CreateParaStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document)
{
	ErrorCode result = kFailure;
	do
	{
		if (document == nil)
		{
			// How did we POSSIBLY get here when our menu item should have been disabled if we
			// have no document and have no selection?
			ASSERT_FAIL("document invalid");
			break;
		}	

		InterfacePtr<IStyleGroupManager> paraGroupMgr(document->GetDocWorkSpace(), IID_IPARASTYLEGROUPMANAGER);
		if (paraGroupMgr == nil)
		{
			ASSERT_FAIL("paraGroupMgr invalid");
			break;
		}

		// Create a command sequence so we may create and apply this style in one command:
		PMString	createAndApplyParaStyle("Create & Apply Paragraph Style");
		CmdUtils::SequenceContext sequence(&createAndApplyParaStyle);

		// Check if there is a SDK style group already exist, if not, create one and return the group IOD
		UID sdkGroupUID = CreateSDKStyleGroup(document, paraGroupMgr);

		// Make a PMString out of the styleName...
		PMString theStyleName(styleName);
		theStyleName.Translate();

		// Look up the style in the paragraph style table:
		UID styleUID = paraGroupMgr->FindByName(theStyleName);

		if (styleUID != kInvalidUID)
		{
			ASSERT_FAIL("Paragraph style name exists. Please choose a different one for the new style.");
			SNIPLOG("Paragraph style name already exists. Please choose another.");
			break;
		}

		// If the style name isn't found in the table, the UID
		// will be kInvalidUID, and we'll need to create the style:

		// Create the newStyleCmd:
		InterfacePtr<ICommand> newStyleCmd(CmdUtils::CreateCommand(kCreateParaStyleCmdBoss));
		
		// Set the UIDList with the document:
		newStyleCmd->SetItemList(UIDList(document->GetDocWorkSpace()));
		
		// Aquire the IStyleInfo interface:
		InterfacePtr<IStyleInfo> styleInfo(newStyleCmd, UseDefaultIID());
		
		if (styleInfo == nil)
		{
			ASSERT_FAIL("styleInfo invalid");
			break;
		}		

		// Set the style info:
		styleInfo->SetName(theStyleName);
		styleInfo->SetBasedOn(kInvalidUID);
		styleInfo->SetCharStyle(kInvalidUID);
        styleInfo->SetStyleType(IStyleInfo::kParagraphStyle);
		// styleInfo->SetIsParagraphStyle(kTrue);
		styleInfo->SetIsStyleImported(kFalse);
		
		// position the style under SDK Style Group
		InterfacePtr<IStyleGroupHierarchy> parentHier(::GetDataBase(paraGroupMgr), sdkGroupUID, UseDefaultIID());
		InterfacePtr<IStylePositionInfo> newStylePosInfo(newStyleCmd, UseDefaultIID());
		ASSERT(newStylePosInfo);
		newStylePosInfo->SetParent(parentHier);
		
		// Our paragraph style is different by
		// changing the font size for the paragraph
		// to 18.
		
		// First, we create a text attribute real number to hold the font size:
		InterfacePtr<ITextAttrRealNumber> textAttrRealNumber(::CreateObject2<ITextAttrRealNumber>(kTextAttrPointSizeBoss));

		if (textAttrRealNumber == nil)
		{
			ASSERT_FAIL("textAttrRealNumber invalid");
			break;
		}

		// Now we'll set the attribute's value:
		const PMReal font_size(18); // The size we want to change to.			
		textAttrRealNumber->SetRealNumber(font_size);
		
		// Then, we get the standard text attributes interface, hanging off the new style command:
		InterfacePtr<ITextAttributes> textAttributes(newStyleCmd, UseDefaultIID());
		textAttributes->ApplyAttribute(textAttrRealNumber);
		
		// Finally, fire the new style command and report any errors:
		result = CmdUtils::ProcessCommand(newStyleCmd);
		if (result != kSuccess)
		{
			ASSERT_FAIL("newStyleCmd failed");
			break;
		}
 
		UID newStyleUID = paraGroupMgr->FindByName(sdkGroupUID, styleName);
		InterfacePtr<IStyleGroupHierarchy> styleHier(::GetDataBase(paraGroupMgr), newStyleUID, UseDefaultIID());
		PMString styleFullPath = styleHier->GetFullPath();
		SNIPLOG("new style full path: %s", styleFullPath.GetUTF8String().c_str());
		styleFullPath.SetTranslatable(kFalse);
		// We were successful, so apply this style so it shows up:
		result = ApplyParaStyle(suite, styleFullPath, document);
		if (result != kSuccess)
		{
			break;
		}

	} while (false);
		
	return result;
}

/*	ApplyParaStyle
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyParaStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document)
{
	ErrorCode result = kFailure;
	do
	{
		if (suite == nil) 
		{
			ASSERT_FAIL("suite invalid");
			break;
		}

		if (document == nil)
		{
			ASSERT_FAIL("document invalid");
			break;
		}

		InterfacePtr<IStyleGroupManager> styleNameTable_para(document->GetDocWorkSpace(), IID_IPARASTYLEGROUPMANAGER);
		if (styleNameTable_para == nil)
		{
			ASSERT_FAIL("styleNameTable_para invalid");
			break;
		}
		
		UID styleUID = kInvalidUID;
		
		// first, assume styleName is a full path to a style
		styleUID = styleNameTable_para->FindByName(styleName);
		if (styleUID == kInvalidUID)
		{
			// if can't find the style in full path, look for the style in the "SDK Style Group" only"
			PMString sdkGroupName("SDK Style Group");
			UID sdkGroupUID = styleNameTable_para->FindByName(sdkGroupName);
			if (sdkGroupUID != kInvalidUID)
				styleUID = styleNameTable_para->FindByName(sdkGroupUID, styleName);
		}
		
		if (styleUID == kInvalidUID)
		{
			ASSERT_FAIL("Can't find the paragraph style. Please specify a full path of the style or a style in the \"SDK Style Group\"to apply. ");
			SNIPLOG("The paragraph style does not exist. Please create it first.");
			break;
		}

		// apply the style. 
		result = suite->ApplyStyle(styleUID);
		ASSERT_MSG(result == kSuccess, "Could not apply paragraph style.");
		
	} while (false);
	
	return result;
}

/*	CreateCharStyle
*/
ErrorCode SnpApplyTextStyleAttributes::CreateCharStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document)
{
	ErrorCode result = kFailure;

	do{
		if (document == nil)
		{
			ASSERT_FAIL("document invalid");
			break;
		}	

		InterfacePtr<IStyleGroupManager> styleGroupMgr(document->GetDocWorkSpace(), IID_ICHARSTYLEGROUPMANAGER);
		if (styleGroupMgr == nil)
		{
			ASSERT_FAIL("styleGroupMgr invalid");
			break;
		}
		
		// Create a command sequence so we may create and apply this style in one command:		
		PMString	createAndApplyCharStyle("Create & Apply Character Style");
		CmdUtils::SequenceContext sequence(&createAndApplyCharStyle);

		// Check if there is a SDK style group already exist, if not, create one and return the group IOD
		UID sdkGroupUID = CreateSDKStyleGroup(document, styleGroupMgr);
		
		// Make a PMString out of the styleName...
		PMString theStyleName(styleName);
		theStyleName.Translate();

		// Look up the style in the character style table:
		UID styleUID = styleGroupMgr->FindByName(theStyleName);
		
		if (styleUID != kInvalidUID)
		{
			ASSERT_FAIL("Character style name exists. Please choose a different name for the new style.");
			SNIPLOG("Character style name already exists. Please choose a different one.");
			break;
		}

		// If the style name isn't found in the table, the UID
		// will be kInvalidUID, and we'll need to create the style:

		// Create the newStyleCmd:
		InterfacePtr<ICommand> newStyleCmd(CmdUtils::CreateCommand(kCreateCharStyleCmdBoss));
		
		// Set the UIDList with the document:
		newStyleCmd->SetItemList(UIDList(document->GetDocWorkSpace()));
		
		// Aquire the IStyleInfo interface:
		InterfacePtr<IStyleInfo> styleInfo(newStyleCmd, IID_ISTYLEINFO);			
		if (styleInfo == nil)
		{
			ASSERT_FAIL("styleInfo invalid");
			break;
		}
		
		// Set the style info:
		styleInfo->SetName(theStyleName);
		styleInfo->SetBasedOn(kInvalidUID);
		styleInfo->SetCharStyle(kInvalidUID);
		styleInfo->SetStyleType(IStyleInfo::kCharacterStyle);
        // styleInfo->SetIsParagraphStyle(kFalse);
		styleInfo->SetIsStyleImported(kFalse);
		
		// position the style under SDK Style Group
		InterfacePtr<IStyleGroupHierarchy> parentHier(::GetDataBase(styleGroupMgr), sdkGroupUID, UseDefaultIID());
		InterfacePtr<IStylePositionInfo> newStylePosInfo(newStyleCmd, UseDefaultIID());
		ASSERT(newStylePosInfo);
		newStylePosInfo->SetParent(parentHier);
		
		// Our text style will be normal, except
		// the text will be colored blue.  Since
		// blue is not a normal swatch color, we
		// will search for it, and if we don't
		// find it, we'll create it.
		InterfacePtr<ITextAttrUID> textAttrUID_Color(::CreateObject2<ITextAttrUID>(kTextAttrColorBoss));
		if (textAttrUID_Color == nil)
		{
			ASSERT_FAIL("textAttrUID_Color invalid");
			break;
		}

		// Our routine to find or create an RGB color:
		const UID colorBlue = ResolveRGBColorSwatch
		(
			kSDKDefBlueApplicationKey,		// PMString color name
			0,				// Red (0.0...1.0)
			0,				// Green (0.0...1.0)
			1.0,			// Blue (0.0...1.0)
			document
		);
		
		if (colorBlue == kInvalidUID)
		{
			ASSERT_FAIL("colorBlue invalid");
			break;
		}
		
		// Set our color attribute and store it:
		textAttrUID_Color->SetUIDData(colorBlue);
		
		InterfacePtr<ITextAttributes> textAttributes(newStyleCmd, IID_ITEXTATTRIBUTES);
		if (textAttributes == nil)
		{
			ASSERT_FAIL("textAttributes invalid");
			break;
		}
		
		textAttributes->ApplyAttribute(textAttrUID_Color);
		
		// Execute the command and report any errors:
		result = CmdUtils::ProcessCommand(newStyleCmd);
		if (result != kSuccess)
		{
			ASSERT_FAIL("ProcessCommand(newStyleCmd) invalid");
			break;
		}
 
		UID newStyleUID = styleGroupMgr->FindByName(sdkGroupUID, styleName);
		InterfacePtr<IStyleGroupHierarchy> styleHier(::GetDataBase(styleGroupMgr), newStyleUID, UseDefaultIID());
		PMString styleFullPath = styleHier->GetFullPath();
		SNIPLOG("new style full path: %s", styleFullPath.GetUTF8String().c_str());
		styleFullPath.SetTranslatable(kFalse);

		// We were successful, so apply this style so it shows up:
		result = ApplyCharStyle(suite, styleFullPath, document);	// Once we create the style, we'll apply it.
		if (result != kSuccess)
		{
			break;
		}
 			
		result = kSuccess;

	} while (false);
	
	return result;
}
	
/*	ApplyCharStyle
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyCharStyle(ITextAttributeSuite* suite, const PMString& styleName, IDocument* document)
{
	ErrorCode result = kFailure;
	do
	{
		if (document == nil)
		{
			ASSERT_FAIL("document invalid");
			break;
		}

		InterfacePtr<IStyleGroupManager> styleNameTable_char(document->GetDocWorkSpace(), IID_ICHARSTYLEGROUPMANAGER);
		if (styleNameTable_char == nil)
		{
			ASSERT_FAIL("styleNameTable invalid");
			break;
		}
		
		UID styleUID = kInvalidUID;
		
		// first, assume styleName is a full path to a style
		styleUID = styleNameTable_char->FindByName(styleName);
		if (styleUID == kInvalidUID)
		{
			// if can't find the style in full path, look for the style in the "SDK Style Group" only"
			PMString sdkGroupName("SDK Style Group");
			UID sdkGroupUID = styleNameTable_char->FindByName(sdkGroupName);
			if (sdkGroupUID != kInvalidUID)
				styleUID = styleNameTable_char->FindByName(sdkGroupUID, styleName);
		}

		if (styleUID == kInvalidUID)
		{
			ASSERT_FAIL("The style does not exist in the document.");
			SNIPLOG("Style not found in document. Please create it first.");
			break;
		}

		// apply the style.
		result = suite->ApplyStyle(styleUID);

	} while (false);
	
	if(result != kSuccess){
		SNIPLOG("Could not apply character style.");
	}

	return result;
}

// InDesign Japanese Features.

/*  CharRotate
*/
ErrorCode SnpApplyTextStyleAttributes::IncrementalCharRotation(ITextAttributeSuite* suite, const PMReal angle)
{
	ErrorCode result = kFailure;
	PMReal currentAngle = 0.0;

	do {	
		if (suite == nil) {
			break;
		}
		// make a local copy.
		PMReal localAngle(angle);

		// set the attribute boss class ID of interest. 
		ClassID rotateAttrID = kTACharRotateAngleReportBoss;
		
		// get the current value
		bool16 onlyOneValue = suite->GetRealNumberAttributeValue(rotateAttrID, &currentAngle);

		if (onlyOneValue == kTrue) {
			// if there is only one rotation angle on the current selection,
			// increment it.
			localAngle += currentAngle;
			// make sure the angle is between -360 and 360.
			if (localAngle > 360) {
				localAngle -= 360;
			}
			if (localAngle < -360) {
				localAngle += 360;
			}
		}

		// set the angle.
		result = suite->SetRealNumberAttribute(rotateAttrID, localAngle);
		
	} while (false); 
	
	return result;
}

/*	ApplyTsume
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyTsume(ITextAttributeSuite* suite, const PMReal tsume)
{
	ErrorCode result = kFailure;
	
	do{	
		if (suite == nil){
			break;
		}
		
		// Apply the value. 
		result = suite->SetRealNumberAttribute(kTATsumeBoss, tsume);
		
	} while (false); // Only do once.
	
	return result;
}

/*	ApplyMojikumiSpacing
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyMojikumiSpacing(ITextAttributeSuite* suite, const PMReal space, bool16 isBefore)
{
	ErrorCode result = kFailure;
	
	do{
		if (suite == nil){
			break;
		}
	
		// choose the attribute boss class.
		ClassID ourClass;
		if (isBefore) 
			ourClass = kTAMojikumiForceBeforeSpacingBoss;
		else
			ourClass = kTAMojikumiForceAfterSpacingBoss;
				
		// Apply the value. 
		result = suite->SetRealNumberAttribute(ourClass, space);
		
	} while (false);
	
	return result;
}

/*	ApplyJidori
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyJidori(ITextAttributeSuite* suite, const int16 jidori)
{
	ErrorCode result = kFailure;
	
	do{
		// HARDCODE ALERT: limit to 20 characters... 
		if(0 <= jidori && jidori <= 20)
		{
			// Create new Jidori attribute and set the value.
			InterfacePtr<ITextAttrInt16> jidoriValue(::CreateObject2<ITextAttrInt16>(kTAGridJidoriReportBoss));
			if (jidoriValue == nil)
			{
				ASSERT_FAIL("jidoriValue invalid");
				break;
			}
			jidoriValue->SetInt16(jidori);

			// apply the attribute
			result = suite->ApplyAttribute(jidoriValue);
		}
		else
		{
			// Error limit length of Jidori string.
			SNIPLOG("The value must be between 0 and 20.");
		}
	} while (false);
	
	return result;
}

/* 	ApplyShatai
*/
ErrorCode SnpApplyTextStyleAttributes::ApplyShatai(ITextAttributeSuite* suite, const PMReal lens, const PMReal angle)
{
	ErrorCode result = kFailure;
	
	do{
		if (suite == nil){
			break;
		}
		
		result = suite->SetRealNumberAttribute(kTAShataiMagnificationBoss, lens);
		
		if(result != kSuccess){
			break;
		}
		
		result = suite->SetRealNumberAttribute(kTAShataiAngleBoss, angle);
		
		if(result != kSuccess){
			break;
		}

	} while (false);
	
	return result;
}

//-------------------------

template <typename I, typename V>
ErrorCode ChangeTextAttribute(ITextModel* textModel, ClassID strandBoss, ClassID attrBoss, const RangeData& range, V attrVal)
{
	InterfacePtr<I> iAttr(static_cast<I*>(::CreateObject(attrBoss, I::kDefaultIID)) );
	if (iAttr)
	{
		iAttr->Set(attrVal);
		InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, range, iAttr, strandBoss));
		return CmdUtils::ProcessCommand(cmd);
	}
	return kFailure;
}


ErrorCode SnpApplyTextStyleAttributes::SetSingleColumn(ITextModel* textModel, const RangeData& range)
{
	ITextAttrInt16::ValueType value = ICompositionStyle::kSingleColumn;
		
	return ChangeTextAttribute<ITextAttrInt16>(textModel, kParaAttrStrandBoss, kTextAttrSpanColumnTypeBoss , range, value);
}

ErrorCode SnpApplyTextStyleAttributes::SetSpanColumns(ITextModel*  textModel, const RangeData& range, int16 spanNumber)
{
	ErrorCode status = kFailure;
	
	do
	{
		ITextAttrInt16::ValueType value = ICompositionStyle::kSpanColumn;
		status = ChangeTextAttribute<ITextAttrInt16>(textModel, kParaAttrStrandBoss, kTextAttrSpanColumnTypeBoss , range, value);
		
		if ( status != kSuccess )
			break;
		value = spanNumber;
		status = ChangeTextAttribute<ITextAttrInt16>(textModel, kParaAttrStrandBoss, kTextAttrSpanColumnCountBoss , range, value);
	}
	while (false);
	
	return status;
}

ErrorCode SnpApplyTextStyleAttributes::SetSplitColumns(ITextModel*  textModel, const RangeData& range, int16 splitNumber, PMReal insideGutter, PMReal outsideGutter)
{
	ErrorCode status = kFailure;
	
	do
	{
		ITextAttrInt16::ValueType value = ICompositionStyle::kSplitColumn;
		status = ChangeTextAttribute<ITextAttrInt16>(textModel, kParaAttrStrandBoss, kTextAttrSpanColumnTypeBoss , range, value);
		
		if ( status != kSuccess )
			break;
		value = splitNumber;
		status = ChangeTextAttribute<ITextAttrInt16>(textModel, kParaAttrStrandBoss, kTextAttrSpanColumnCountBoss , range, value);
		
		if ( status != kSuccess )
			break;
		
		ITextAttrRealNumber::ValueType realValue = insideGutter;
		status = ChangeTextAttribute<ITextAttrRealNumber>(textModel, kParaAttrStrandBoss, kTextAttrSplitColumnInsideGutterBoss , range, realValue);
		
		if ( status != kSuccess )
			break;
		
		realValue = outsideGutter;
		status = ChangeTextAttribute<ITextAttrRealNumber>(textModel, kParaAttrStrandBoss, kTextAttrSplitColumnOutsideGutterBoss , range, realValue);
	}
	while (false);
	
	return status;
}




/*	ResolveRGBColorSwatch
*/
const UID SnpApplyTextStyleAttributes::ResolveRGBColorSwatch(const PMString& swatchName, 
								  const PMReal rRed, 
								  const PMReal rGreen, 
								  const PMReal rBlue,
								  IDocument* document)
{
	UID colorUID = kInvalidUID;
	do
	{
		if (document == nil)
		{
			ASSERT_FAIL("document invalid");
			break;
		}	

		InterfacePtr<ISwatchList> swatchList(document->GetDocWorkSpace(), UseDefaultIID());
		if (swatchList == nil)
		{
			ASSERT_FAIL("swatchList invalid");
			break;
		}
		

		UIDRef colorUIDRef = swatchList->FindSwatch(swatchName);
		
		if (colorUIDRef != nil)
		{
			colorUID = colorUIDRef.GetUID();
		}
		else
		{
			// Must create the color.  Didn't find it in swatch list.
			
			// First create our command and get at the data:
		    InterfacePtr<ICommand> newColorCmd(CmdUtils::CreateCommand(kNewColorCmdBoss));

			// We'll be adding to the swatch list:
			InterfacePtr<IUIDData> swatchListData(newColorCmd, IID_IUIDDATA);
			if (swatchListData == nil)
			{
				ASSERT_FAIL("swatchListData invalid");
				break;
			}		
			swatchListData->Set(swatchList);

			// Create the rendering object:
		    InterfacePtr<IRenderingObject> renderingObject(newColorCmd, UseDefaultIID());
		    if (renderingObject == nil)
			{
				ASSERT_FAIL("renderingObject invalid");
				break;
			}		
			
		    // Fill out the name:
			renderingObject->SetSwatchName(swatchName);

		    // Supply the actual color via the colorData interface:
		    InterfacePtr<IColorData> colorData(newColorCmd, UseDefaultIID());
		    
		    const int32 colorSpace = (kPMCsCalRGB);	// RGB color space.

		    // Create the color array:
			ColorArray rgbColor;
			
			rgbColor.push_back(rRed); // Red (0.0...1.0)
			rgbColor.push_back(rGreen); // Green (0.0...1.0)
			rgbColor.push_back(rBlue); // Blue (0.0...1.0)
			
		    colorData->SetColorData(colorSpace, rgbColor);
            
			// Set the ink type (swatch validation has been tightened under InDesign CS
			// and if the ink type of a swatch is undefined you will get an assert
			// when the document is closed).
			InterfacePtr<IInkData> inkData(newColorCmd, UseDefaultIID());
			if (inkData == nil)
			{
				ASSERT_FAIL("indData invalid");
				break;
			}
			inkData->SetInkType(IInkData::kProcessInk);

			ErrorCode error = CmdUtils::ProcessCommand(newColorCmd);
			if (error != kSuccess)
			{
				ASSERT_FAIL("newColorCmd failed");
				break;
			}

			// Now get our UID out of the list and add it to the swatch:
		    const UIDList* colorUIDList = newColorCmd->GetItemList();
		    if (colorUIDList == nil)
		    {
				ASSERT_FAIL("UIDList invalid");
				break;
			}
		    
		    // We're only going to add the very first color here, not the whole list:
		    colorUID = colorUIDList->First();

			// As of build 325 we have to manually add to the Swatch list,
			// it's no longer part of the NewColorCmd:
			InterfacePtr<ICommand> addSwatchesCmd(CmdUtils::CreateCommand(kAddSwatchesCmdBoss));
			InterfacePtr<IUIDData> addSwatchesCmdListData(addSwatchesCmd, UseDefaultIID());
			
			if (addSwatchesCmdListData == nil || addSwatchesCmd == nil)
			{
				ASSERT_FAIL("addSwatches invalid");
				break;
			}
			
			addSwatchesCmd->SetName("Add Swatch");				
			
			addSwatchesCmdListData->Set(swatchList);
			addSwatchesCmd->SetItemList(UIDList(colorUIDList->GetDataBase(), colorUID));

			// Finally, add the color to the swatch list via this command:
			error = CmdUtils::ProcessCommand(addSwatchesCmd);
			if (error != kSuccess)
			{
				ASSERT_FAIL("addSwatchesCmd failed");
				break;
			}

			// Now let's try to find the color from the swatch list:
			colorUIDRef = swatchList->FindSwatch(swatchName);

			if (colorUIDRef == nil)
			{
				ASSERT_FAIL("even after new color, cannot find swatch");
				break;
			}
			
			colorUID = colorUIDRef.GetUID();
		}
	} while (false);

	return colorUID;
}

ErrorCode SnpApplyTextStyleAttributes::ToggleParaBorder(ITextAttributeSuite* suite)
{
	ErrorCode result = kFailure;
	do {
		if (suite == nil)
		{
			break;
		}
		// Find out what the current attr value is... assume "kFalse"
		bool16 currentAttrValue = kFalse;

		int32 count = suite->CountAttributes(kTextAttrPBSStrokeOnBoss);
		if (count != 1) {
			SNIPLOG("Mixed para border setting - will turn on.");
		}
		else
		{
			// Query first capital mode attribute.
			InterfacePtr<const ITextAttrBoolean> pAttr(static_cast< const ITextAttrBoolean*>(suite->QueryAttributeN(0, kTextAttrPBSStrokeOnBoss, IID_ITEXTATTRBOOLEAN)));
			if (!pAttr) {
				break;
			}

			currentAttrValue = pAttr->Get();
		}

		// Toggle the value and apply it
		currentAttrValue = !currentAttrValue;
		InterfacePtr<ITextAttrBoolean> newAttr(static_cast<ITextAttrBoolean*>(CreateObject(kTextAttrPBSStrokeOnBoss, IID_ITEXTATTRBOOLEAN)));
		if (!newAttr) {
			break;
		}
		newAttr->Set(currentAttrValue);
		AttributeBossList attrList;
		attrList.ApplyAttribute(newAttr);

		result = suite->ApplyAttributes(&attrList, kParaAttrStrandBoss);
	} while (false);

	return result;
}

ErrorCode SnpApplyTextStyleAttributes::ToggleParaShading(ITextAttributeSuite* suite)
{
	ErrorCode result = kFailure;
	do {
		if (suite == nil)
		{
			break;
		}
		// Find out what the current attr value is... assume "kFalse"
		bool16 currentAttrValue = kFalse;

		int32 count = suite->CountAttributes(kTextAttrPBSFillOnBoss);
		if (count != 1) {
			SNIPLOG("Mixed para shading setting - will turn on.");
		}
		else
		{
			// Query first capital mode attribute.
			InterfacePtr<const ITextAttrBoolean> pAttr(static_cast< const ITextAttrBoolean*>(suite->QueryAttributeN(0, kTextAttrPBSFillOnBoss, IID_ITEXTATTRBOOLEAN)));
			if (!pAttr) {
				break;
			}

			currentAttrValue = pAttr->Get();
		}

		// Toggle the value and apply it
		currentAttrValue = !currentAttrValue;
		InterfacePtr<ITextAttrBoolean> newAttr(static_cast<ITextAttrBoolean*>(CreateObject(kTextAttrPBSFillOnBoss, IID_ITEXTATTRBOOLEAN)));
		if (!newAttr) {
			break;
		}
		newAttr->Set(currentAttrValue);
		AttributeBossList attrList;
		attrList.ApplyAttribute(newAttr);

		result = suite->ApplyAttributes(&attrList, kParaAttrStrandBoss);
	} while (false);

	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpApplyTextStyleAttributes available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerApplyTextStyleAttributes : public SnpRunnable
{
	

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerApplyTextStyleAttributes();

		/** Destructor.
		 */
		virtual			~_SnpRunnerApplyTextStyleAttributes();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			Change the value of text attributes in all the given items.
			Other methods are called to carry out the item chosen by the menu.
			All methods called by this method take in an ITextAttributeSuite.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
		
	private:
		ClassID composerClass;
};


/* Constructor.
*/
_SnpRunnerApplyTextStyleAttributes::_SnpRunnerApplyTextStyleAttributes() : SnpRunnable("ApplyTextStyleAttributes") 
{
	// Describe what your snippet does.
	this->SetDescription("Apply text attributes, Create style");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("some text must be selected");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_cjk, sdk_text");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerApplyTextStyleAttributes::~_SnpRunnerApplyTextStyleAttributes()
{
}


/* Check if your preconditions are met.
*/
bool16	_SnpRunnerApplyTextStyleAttributes::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) {
			break;
		}
		InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
		ASSERT(textFocus);
		if (textFocus == nil) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerApplyTextStyleAttributes::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode result = kCancel;

	do {		
		// Require a text selection to be able to run.
		SnpApplyTextStyleAttributes instance;

		InterfacePtr<ITextAttributeSuite> textAttributeSuite(runnableContext, UseDefaultIID());
		if (textAttributeSuite == nil)
		{
			SNIPLOG("You do not have a text attribute suite. Exiting...");
			break;
		}		
		
		if (!textAttributeSuite->CanApplyAttributes())
		{
			SNIPLOG("Can't apply attributes.");
			break;
		}
		
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

		// query data range and text model
		RangeData range = textFocus->GetCurrentRange();
		RangeData::Lean leanData;
		TextIndex startIndex = range.Start(&leanData);
		
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		if (textModel == nil) {
			break;
		}
		

		// make sure the composer is a Japanese composer
		result = SnpTextAttrHelper::GetTextAttribute<ITextAttrClassID, ClassID>(textRange, kTextAttrComposerBoss, composerClass);
		if(result != kSuccess)
		{
			break;
		}
		
		// Ask for the type of attribute to be applied.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Toggle underline"));
		choices.push_back(PMString("Cycle capital mode"));
		choices.push_back(PMString("Set font style"));
		choices.push_back(PMString("Toggle bold font style"));
		choices.push_back(PMString("Toggle italic font style"));
		choices.push_back(PMString("Set paragraph alignment"));
		choices.push_back(PMString("Create paragraph style"));
		choices.push_back(PMString("Apply paragraph style"));
		choices.push_back(PMString("Create character style"));
		choices.push_back(PMString("Apply character style"));
		choices.push_back(PMString("Set incremental character rotation angle"));
		choices.push_back(PMString("Set paragraph layout"));
		choices.push_back(PMString("Toggle paragraph border"));
		choices.push_back(PMString("Toggle paragraph shading"));

		// check against known text composers that are known to compose TateChuYoko attributes correctly
		if (composerClass == kJParagraphComposerBoss ||
			composerClass == kJSingleComposerBoss) 
		{
			// added only if the composer is a Japanese text composer.
			choices.push_back(PMString("Set moji tsume"));
			choices.push_back(PMString("Set mojikumi before spacing"));
			choices.push_back(PMString("Set mojikumi after spacing"));
			choices.push_back(PMString("Set jidori"));
			choices.push_back(PMString("Set shatai"));
		}
		enum {
				kUnderline, kCycleCaps, kNormalStyle, kBoldStyle, kItalicStyle,kSetAlignment,
				kCreateParagraphStyle, kApplyParaStyle, kCreateCharStyle, kApplyCharacterStyle, kCharacterRotate, kSetParagraphLayout, kToggleParaBorder, kToggleParaShading,
				// InDesign Japanese Features
				kMojiTsume, kMojikumiBeforeSpacing, kMojikumiAfterSpacing, kJidori, kShatai
			};
		int32 choice  = parameterUtils->GetChoice("Choose which text attribute you want to apply.", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		
		// Get front document.
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		
		
		// Ask for the attribute's value.
		switch (choice) 
		{
			default:
			case kUnderline:
				{
					result = instance.ToggleUnderline(textAttributeSuite);
					if(result != kSuccess){
						SNIPLOG("ToggleUnderline failed!");
					}
					break;
				}		
			case kCycleCaps:
				{

					result = instance.CycleSmallAllCaps(textAttributeSuite);

					if(result != kSuccess){
						SNIPLOG("CycleSmallAllCaps failed!");
					}
					break;
				}		
			case kNormalStyle:
				{
					PMString fontStyle = parameterUtils->GetPMString("Enter font style name to apply.", PMString("Regular"));
					result = instance.ApplyFontVariant(textAttributeSuite, fontStyle);
					if(result != kSuccess){
						SNIPLOG("ApplyFontVariant failed!");
					}
					break;
				}		
			case kBoldStyle:
				{
					result = instance.ToggleBold(textAttributeSuite);
					if(result != kSuccess){
						SNIPLOG("ToggleBold failed!");
					}
					break;
				}		
			case kItalicStyle:
				{
					result = instance.ToggleItalic(textAttributeSuite);
					if(result != kSuccess){
						SNIPLOG("ToggleItalic failed!");
					}
					break;
				}
			case kSetAlignment:
				{
					K2Vector<PMString> names;
					names.push_back("flush left");
					names.push_back("centered");
					names.push_back("flush right");
					names.push_back("force justified");
					names.push_back("justified, last left");
					names.push_back("justified, last center");
					names.push_back("justified, last right");
					
					ICompositionStyle::TextAlignment align = (ICompositionStyle::TextAlignment)parameterUtils->GetChoice("Choose text alignment type.", names);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}
					// TODO this shouldn't be done in a Run method in new factoring
				
					result = textAttributeSuite->SetAlignment(align);
					if(result != kSuccess){
						SNIPLOG("SetAlignment failed!");
					}
					break;
				}
				
			case kCreateParagraphStyle:
				{
					PMString styleName = parameterUtils->GetPMString("Enter Paragraph style name to create and apply.", PMString("ExampleParaStyle"));
					result = instance.CreateParaStyle(textAttributeSuite, styleName, document);
					if(result != kSuccess){
						SNIPLOG("CreateParaStyle failed!");
					}
					break;
				}		
			case kApplyParaStyle:
				{
					PMString styleName = parameterUtils->GetPMString("Enter Paragraph style name to apply.", PMString("ExampleParaStyle"));
					result = instance.ApplyParaStyle(textAttributeSuite, styleName, document);
					if(result != kSuccess){
						SNIPLOG("ApplyParaStyle failed!");
					}
					break;
				}		
			case kCreateCharStyle:
				{
					PMString styleName = parameterUtils->GetPMString("Enter Character style name to create and apply.", PMString("ExampleCharStyle"));
					result = instance.CreateCharStyle(textAttributeSuite, styleName, document);
					if(result != kSuccess){
						SNIPLOG("CreateCharStyle failed!");
					}
					break;
				}		
			case kApplyCharacterStyle:
				{
					PMString styleName = parameterUtils->GetPMString("Enter Character style name to apply.", PMString("ExampleCharStyle"));
					result = instance.ApplyCharStyle(textAttributeSuite, styleName, document);
					if(result != kSuccess){
						SNIPLOG("ApplyCharacterStyle failed!");
					}
					break;
				}
			case kCharacterRotate:
				{
					PMReal angle = parameterUtils->GetPMReal("Enter incremental rotation angle.", 28, -360.0, 360.0);
					result = instance.IncrementalCharRotation(textAttributeSuite, angle);
					if(result != kSuccess){
						SNIPLOG("CharRotate failed!");
					}
					break;
				}
			case kSetParagraphLayout:
				{
					K2Vector<PMString> spanNames;
					spanNames.push_back("Single Column");
					spanNames.push_back("Span Columns");
					spanNames.push_back("Split Column");
					
					int32 choiceItem = parameterUtils->GetChoice("Choose paragraph layout type.", spanNames);
					
					enum {
						kSingleColumn = 0,
						kSpanColumn,
						kSplitColumn
					};
					
					if ( parameterUtils->WasDialogCancelled() ) 
					{
						break;
					}
					
					switch ( choiceItem )
					{
						default:
						case kSingleColumn:
						{
							result = instance.SetSingleColumn(textModel,range);
							if( result != kSuccess )
							{
								SNIPLOG("Set single column failed!");
							}
							break;
						}
						case kSpanColumn:
						{
							int32 spanColumnNumber = parameterUtils->GetInt32(PMString("Number of columns to span"), 1, 1, 40);
							if (parameterUtils->WasDialogCancelled())
							{
								break;
							}
							
							result = instance.SetSpanColumns(textModel, range, spanColumnNumber);
							if( result != kSuccess )
							{
								SNIPLOG("Set span columns failed!");
							}
							break;
						}
						case kSplitColumn:
						{
							int32 subColumnNumber = parameterUtils->GetInt32(PMString("Number of columns to split"), 2, 2, 40);
							if (parameterUtils->WasDialogCancelled())
							{
								break;
							}
							
							PMReal insideGutterNumber = parameterUtils->GetPMReal(PMString("Inside Gutter"), 0, 0, 8640.0);
							if (parameterUtils->WasDialogCancelled())
							{
								break;
							}
							
							PMReal outsideGutterNumber = parameterUtils->GetPMReal(PMString("Outside Gutter"), 0, 0, 8640.0);
							if (parameterUtils->WasDialogCancelled())
							{
								break;
							}
							
							result = instance.SetSplitColumns(textModel,range, subColumnNumber, insideGutterNumber, outsideGutterNumber);
							if( result != kSuccess )
							{
								SNIPLOG("Set split column failed!");
							}
							break;
						}
					}
					
					break;
				}
			case kToggleParaBorder:
			{
				result = instance.ToggleParaBorder(textAttributeSuite);
				if (result != kSuccess) {
					SNIPLOG("ToggleParaBorder failed!");
				}
				break;
			}
			case kToggleParaShading:
			{
				result = instance.ToggleParaShading(textAttributeSuite);
				if (result != kSuccess) {
					SNIPLOG("ToggleParaShading failed!");
				}
				break;
			}

			// InDesign Japanese Features
			case kMojiTsume:
				{
					PMReal tsume = parameterUtils->GetPMReal("Enter tsume ratio.", 0.5, 0, 1.0);
					result = instance.ApplyTsume(textAttributeSuite, tsume);
					if(result != kSuccess){
						SNIPLOG("MojiTsume failed!");
					}
					break;
				}
			case kMojikumiBeforeSpacing:
			case kMojikumiAfterSpacing:
				{
					K2Vector<PMString> mojikumiSpace;
					mojikumiSpace.push_back("Auto");
					mojikumiSpace.push_back("None");
					mojikumiSpace.push_back("8bu");
					mojikumiSpace.push_back("4bu");
					mojikumiSpace.push_back("3bu");
					mojikumiSpace.push_back("2bu");
					mojikumiSpace.push_back("2bu4bu");
					mojikumiSpace.push_back("FullWidth");
					enum {
						kItem_Auto = 0, 
						kItem_None,			// 0%
						kItem_8bu,			// 12.5%
						kItem_4bu,			// 25%
						kItem_3bu,			// 33.333..%
						kItem_2bu,			// 50%
						kItem_2bu4bu,		// 75%
						kItem_FullWidth		// 100%
					};
					int32 chosenItem  = parameterUtils->GetChoice("Choose mojikumi spacing.", mojikumiSpace);
					if (parameterUtils->WasDialogCancelled()) {
						break;
					}
					
					PMReal space;
					switch(chosenItem)
					{			
						default:
						case kItem_Auto:
						{
							space = kSpacing_Auto;
							break;
						}
						case kItem_None:
						{
							space = kSpacing_None;
							break;
						}
						case kItem_8bu:
						{
							space = kSpacing_8bu;
							break;
						}
						case kItem_4bu:
						{
							space = kSpacing_4bu;
							break;
						}
						case kItem_3bu:
						{
							space =  PMReal(1.0 / 3.0);
							break;
						}
						case kItem_2bu:
						{
							space = kSpacing_2bu;
							break;
						}
						case kItem_2bu4bu:
						{
							space = kSpacing_2bu4bu;
							break;
						}
						case kItem_FullWidth:
						{
							space = kSpacing_FullWidth;
							break;
						}
					}
					
					result = instance.ApplyMojikumiSpacing(textAttributeSuite, space, (choice == kMojikumiBeforeSpacing));
					if(result != kSuccess){
						SNIPLOG("MojikumiAfterSpacing failed!");
					}
					break;
				}
			case kJidori:
				{
					int16 jidori = static_cast<int16>(parameterUtils->GetInt32("Enter jidori amount in number of characters.", 10, 0, 20));
					result = instance.ApplyJidori(textAttributeSuite, jidori);
					if(result != kSuccess){
						SNIPLOG("Jidori failed!");
					}
					break;
				}		
			case kShatai:
				{
					PMReal lens = parameterUtils->GetPMReal("Enter shatai magnification percentage.", 30, 0, 50);
					PMReal angle = parameterUtils->GetPMReal("Enter shatai rotation angle.", 45, -360.0, 360.0);
					result = instance.ApplyShatai(textAttributeSuite, lens, angle);
					if(result != kSuccess){
						SNIPLOG("Shatai failed!");
					}
					break;
				}		
		}		
			
	} while(false);
	return (result);
}



/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerApplyTextStyleAttributes instance_SnpRunnerApplyTextStyleAttributes;
DEFINE_SNIPPET(_SnpRunnerApplyTextStyleAttributes) 
// End, SnpApplyTextStyleAttributes.cpp

