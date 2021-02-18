//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInsertGlyph.cpp $
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
#include "IAttrReport.h"
#include "ICommand.h"
#include "IComposeScanner.h"
#include "IDrawingStyle.h"
#include "IFontFamily.h"
#include "IFontInstance.h"
#include "IGlyphUtils.h"
#include "IPMFont.h"
#include "IRangeData.h"
#include "ITextAttrSpecialGlyph.h"
#include "ITextAttrUID.h"
#include "ITextAttrFont.h"
#include "ITextAttrOTFeatureList.h"
#include "ITextAttrUID.h"
#include "ITextAttrUtils.h"
#include "ITextModel.h"
#include "ITextModelCmds.h"
#include "ITextTarget.h"
#include "ITextUtils.h"

// General includes:
#include "AttributeBossList.h"
#include "CJKID.h"
#include "CmdUtils.h"
#include "cooltypedata.h" // for kCharStringNames
#include "CreateObject.h"
#include "CTUnicodeTranslator.h"
#include "CreateObject.h"
#include "CTextEnum.h" // for kInvalidGlyphID
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "OTFeature.h" // for OpenTypeFeatureList
#include "PersistUtils.h" 
#include "TextChar.h"
#include "TextID.h"
#include "TextAttrID.h"
#include "TextRange.h"
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	How to insert a glyph by its glyph ID (or character ID in a font).
 * 
 * 	This snippet allows you to insert a glyph by its glyph ID.
 * 	What is special about this snippet is that it will adapt to 
 * 	glyphs with various special OpenType features, or even if
 * 	the glyph is just a regular Unicode(TM) character. This snippet 
 * 	will try to find the Unicode character value for the specified glyph, 
 * 	and if it finds the Unicode value, then it will insert that 
 * 	character into the text model, along with necessary text attributes
 * 	such as OpenType attributes. 
 * 	However, if the character does not have a Unicode character value, 
 * 	a placeholder character is inserted into the text model with an 
 * 	appropriate text attribute. 
 * 
 *  This snippet code contains code that is useful for situations where
 * 	you have Unicode characters with alternate forms. This is common in 
 * 	OpenType fonts.
 * 
 *  For example, the OpenType font Kozuma Mincho Pro - Regular contains 22
 * 	different glyph forms of the the NABE character (commonly used in the 
 * 	Japanese surname "Watanabe"). From the top row, left to right:  
 *  <br>
 * 	<img src="SnpInsertGlyph-WatanabeList.gif">
 *  <ul>
 *   <li>U+8FBA, ShiftJIS = 0x95D3, CID = 3621</li>
 *   <li>U+908A, ShiftJIS = 0xE7B2, CID = 6929</li>
 *   <li>U+9089, ShiftJIS = 0xE7B3, CID = 6930</li>	
 *   <li>U+9089, ShiftJIS = 0xE7B3, OpenType Tag = 'jp78', CID = 13407</li>	
 *   <li>U+9089, ShiftJIS = 0xE7B3, OpenType Tag = 'aalt', CID = 14235</li>	
 *   <li>U+9089, ShiftJIS = 0xE7B3, OpenType Tag = 'aalt', CID = 14236</li>	
 *   <li>...</li>
 *   <li>U+9089, ShiftJIS = 0xE7B3, OpenType Tag = 'aalt', CID = 14252</li>	
 *  </ul>
 *  Note that many of these glyphs have the same Unicode character value. 
 * 	Therefore, if you simply inserted these characters by their Unicode character
 * 	values, you may not get the glyph you want. 
 *  One key difference between these glyphs is their CID (Character ID), or GlyphID.  
 * 	This snippet shows how to insert these different characters by their GlyphID.
 * 
 *  NOTE: Due to a shortcoming in the IGlyphUtils interface, some glyphs that have multiple
 * 	forms but with the same values (e.g. U+9089 with 'aalt' in the list above has 19 
 * 	different forms), this sample will end up placing a placeholder character (either 
 *  kTextChar_SpecialGlyph or kTextChar_NonRomanSpecialGlyph) into the 
 * 	text model with a kTextAttrSpecialGlyphBoss attribute. 
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_text
 * 	@ingroup sdk_cjk
 *	@see Insert Glyph Panel in the application
 */
class SnpInsertGlyph 
{
public:

	/** Constructor.
	 */
	SnpInsertGlyph() {}

	/** Destructor.
	 */
	virtual ~SnpInsertGlyph() {}

	/** Insert a specific glyph by its glyph ID. Note that the Unicode
	 * 	character that corresponds to a specific glyph ID will vary with 
	 * 	fonts.
	 * 
	 * 	This method will handle any of these cases:
	 * 	\li (1) The glyph corresponds to a regular Unicode character 
	 * 			that isn't an alternate form of any other Unicode character.
	 * 			In this case, the Unicode character is inserted directly.
	 * 	\li (2) The glyph corresponds to a Unicode character, but is
	 * 			also an alternate form of another Unicode character.
	 * 			In this case, the AltGlyphAttrBoss is applied as an attribute.
	 * 	\li (3) The glyph corresponds to a Unicode character in the 
	 * 			Unicode private use area (PUA). (No alternates)
	 * 			In this case, the Unicode character is inserted directly.
	 * 	\li (4) The glyph corresponds to a Unicode character in the 
	 * 			Unicode private use area (PUA), and is also an alternate 
	 * 			form of another Unicode character.
	 * 			In this case, the AltGlyphAttrBoss is applied as an attribute.
	 * 	\li (5) The glyph doesn't have a corresponding Unicode codepoint.
	 * 			In this case, the TextAttrSpecialGlyphBoss is applied as 
	 * 			an attribute.
	 * 
	 * 	@param textRange IN The text model and text range at which you 
	 * 		want to insert the glyph.
	 * 	@param font IN The font associated with the glyph. Together with the
	 * 		glyph ID, you can identify a character. 
	 * 	@param glyph IN The glyph ID to insert. Note that glyph IDs 
	 * 		are specific to fonts, so you must make sure the desired 
	 * 		glyphID does exist in the font. Note that the glyph may
	 * 		not have an associated Unicode character code with it, 
	 * 		and that a single Unicode characters may have multiple
	 * 		glyphs that correspond to it (e.g. alternate glyphs in 
	 * 		OpenType fonts).
	 * 		
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InsertGlyph(InDesign::TextRange& textRange, 
						  IPMFont* font, 
						  const Text::GlyphID glyph);

	/** Gets the IPMFont and the font names (family and style) at the 
	 * 	given TextRange.
	 * 	@param textRange IN The text range to examine.
	 * 	@param fontFamilyName OUT The family name of the font.
	 * 	@param fontStyleName OUT The style name of the font.
	 * 	@return IPMFont that corresponds to the font. Nil if error.
	 */
	IPMFont* QueryFont(const InDesign::TextRange& textRange, 
					   PMString& fontFamilyName,
					   PMString& fontStyleName);

	/** Convert a glyph to a Unicode character.
	 * 	Also try to find if the glyph is in the Unicode private use area (PUA).
	 * 	@param font IN The font associated with the glyph.
	 * 	@param glyph IN The glyph to examine.
	 * 	@param userAreaChar IN/OUT Pass in a non-nil UTF32TextChar in case the glyph
	 * 		is in the PUA.  If it is in the PUA, the value will be something other
	 * 		than kTextChar_Null.
	 * 	@return The Unicode character associated with the glyph. If there is
	 * 		no Unicode codepoint for the glyph, this will return kTextChar_Null.
	 */
	const UTF32TextChar GlyphToCharacter(IPMFont* font, 
										 const Text::GlyphID glyph, 
										 UTF32TextChar* userAreaChar = nil);

	/** Get the open type feature list applied to the glyph.
	 * 	@param font IN The font associated with the glyph.
	 * 	@param glyph IN The glyph to examine.
	 * 	@return OpenTypeFeatureList for the glyph under question.
	 */
	const OpenTypeFeatureList GetOpenTypeFeatureList(IPMFont* font, 
													 const Text::GlyphID glyph);

	/** Insert an alternate form of a glyph.
	 * 	This is used when the glyph has a corresponding Unicode codepoint.
	 * 	@param textRange IN The text range where the special glyph is 
	 * 			to be inserted.
	 * 	@param font IN The font associated with the glyph.
	 * 	@param featureList IN The OpenType feature tags list to apply to the character
	 * 	@return The command for inserting the special glyph. Nil if error.
	 */
	ICommand* CreateInsertAltGlyphCmd(const InDesign::TextRange& textRange, 
									  IPMFont* font, 
									  const OpenTypeFeatureList& featureList);
	
	/** Create a command to insert a special form of a glyph.
	 * 	This is used when the glyph has no corresponding Unicode codepoint.
	 * 	@param textRange IN The text range where the special glyph is 
	 * 			to be inserted.
	 * 	@param font IN The font associated with the glyph.
	 * 	@param glyph IN The glyph to insert. 
	 * 		The font attribute kCharStringNames is automatically determined.
	 * 	@return The command for inserting the special glyph. Nil if error.
	 */
	ICommand* CreateInsertSpecialGlyphCmd(const InDesign::TextRange& textRange, 
										  IPMFont* font, 
										  const Text::GlyphID glyph);


};


/* InsertGlyph
*/
ErrorCode SnpInsertGlyph::InsertGlyph(InDesign::TextRange& textRange, 
									  IPMFont* font, 
									  const Text::GlyphID glyph)
{
	ErrorCode status = kFailure;
	ICommandSequence* seq = nil;

	Text::GlyphID matchGlyph = -1,
		matchUserAreaGlyph = -1;

	bool16 textcharMatchesOurGlyphID = kTrue, // assume it does
		usercharMatchesOurGlyphID = kFalse; // assume it doesn't

	// make a placeholder for the characters to insert
	boost::shared_ptr<WideString> insert(new WideString);

	do {
		if (!insert || 
			textRange.IsValid() == kFalse || 
			font == nil)
		{
			ASSERT_FAIL("One or more preconditions are not met. Exiting...");
			break;
		}
		if (font->IsValidGlyphID(glyph) == kFalse) 
		{
			ASSERT_FAIL("The glyphID passed in is invalid for the font! Exiting...");
			break;
		}

		// get info from text range
		TextIndex start = textRange.GetRange().Start(nil);
		int32 length = textRange.GetRange().Length();
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		if (textModel == nil) 
		{
			ASSERT(textModel);
			break;
		}

        // get the font manager
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) 
		{
			ASSERT(fontMgr);
			break;
		}

		// make ICommand ptrs for the attribute commands
		InterfacePtr<ICommand> attrCmd(nil);
		InterfacePtr<ICommand> clearTextAttrCmd(nil);

		// 1. try to get the Unicode textchar for the glyphID
		UTF32TextChar userAreaChar(kTextChar_Null);
		/* BUG? 
				If the glyph is an alternate form of a UNICODE character, 
				GlyphToCharacter() doesn't seem to return a valid UTF32TextChar. 
				In such a case, this method returns kTextChar_Null, so we end up
				inserting a specialChar with the kTextAttrSpecialGlyphBoss attribute.
				If that happens, the text model contains the specialChar, so
				when you export it to a format other than InDesign tagged text, you
				end up not being able to roundtrip even to the UNICODE base
				character!
		*/ 
		UTF32TextChar tc(Utils<IGlyphUtils>()->GlyphToCharacter(font, glyph, &userAreaChar));
		
		// 2. try to map it back to glyphID to see if we have a match 
		PMMatrix matrix(12, 0.0, 0.0, 12, 0.0, 0.0);
		InterfacePtr<IFontInstance> fontInstance(fontMgr->QueryFontInstance(font, matrix));
		if (fontInstance == nil) 
		{
			ASSERT(fontInstance);
			break;
		}
		matchGlyph = fontInstance->GetGlyphID(tc);
		if (matchGlyph != glyph)
		{
			// no, it doesn't match
			textcharMatchesOurGlyphID = kFalse;
		}

		// ----------------------------------------------------------------
		// Now, follow a decision tree on how we want to insert the glyph
		// ----------------------------------------------------------------

		// the textchar is NOT a user area character.
		if (tc.GetValue() != kTextChar_Null)
		{ 
			SNIPLOG("Matching Unicode char: %d <0x%X>", tc.GetValue(), tc.GetValue());

			// we were able to match up the text char back to the glyphID, so 
			// it's a "base character" (...when there are "alternate" glyphs)
			if (textcharMatchesOurGlyphID) 
			{
				// OPTION 1: insert by Unicode.
				SNIPLOG("InsertGlyph(glyph #%d) - OPTION 1 - insert directly by Unicode", glyph);
				insert->Append(tc); 
			}
			else
			{   
				// OPTION 2: try to find an OpenType feature for the glyph
				// the OpenType features map to text attributes (kAltGlyphAttrBoss),
				SNIPLOG("InsertGlyph(glyph #%d) - OPTION 2 - alternate glyph for a normal Unicode character", glyph);

				// insert the Unicode character
				insert->Append(tc); 
				
				// Find the open type features applied to this glyph
				OpenTypeFeatureList featureList = this->GetOpenTypeFeatureList(font, glyph);

				// create the command to apply the alt glyph attribute
				attrCmd.reset(this->CreateInsertAltGlyphCmd(textRange, font, featureList));
				if (attrCmd == nil)
				{
					ASSERT(attrCmd);
					break;
				}
			}
		}
		else if (userAreaChar.GetValue() != kTextChar_Null) 
		{
			SNIPLOG("Matching Unicode PUA char: %d <0x%X>", userAreaChar.GetValue(), userAreaChar.GetValue());
			// now try to match this back to the glyph ID
			matchUserAreaGlyph = fontInstance->GetGlyphID(userAreaChar);
			if (matchUserAreaGlyph == glyph) 
			{
				// OPTION 3: if the glyph ID can be mapped back to Unicode, insert it
				SNIPLOG("InsertGlyph(glyph #%d) - OPTION 3 - insert directly by Unicode PUA", glyph);
				usercharMatchesOurGlyphID = kTrue;
				insert->Append(userAreaChar);
			}
			else
			{   
				// OPTION 4:  See notes on option 2
				SNIPLOG("InsertGlyph(glyph #%d) - OPTION 4 - alternate glyph for a Unicode PUA character", glyph);
				
				// insert the Unicode character
				insert->Append(userAreaChar); 
				
				// Find the open type features applied to this glyph
				OpenTypeFeatureList featureList = this->GetOpenTypeFeatureList(font, glyph);
                
				// create the command to apply the alt glyph attribute
				attrCmd.reset(this->CreateInsertAltGlyphCmd(textRange, font, featureList));
				if (attrCmd == nil)
				{
					ASSERT(attrCmd);
					break;
				}
			}
		}

		// check if anything has been inserted yet... 
		if (insert->empty()) 
		{
			// OPTION 5 - (last resort) insert special char and text attribute
			// NOTE: This doesn't work well when searching and during import/export
			// 		since we are using a special placeholder textchar
			SNIPLOG("InsertGlyph(glyph #%d) - OPTION 5 SpecialGlyphAttr on a placeholder", glyph);

			UTF32TextChar specialChar((font->GetWritingScript() == 0 /*Roman*/) ? 
									  kTextChar_SpecialGlyph : kTextChar_NonRomanSpecialGlyph);
			
			// insert placeholder character.
			insert->Append(specialChar);

			// create the command to apply the special glyph attribute
			attrCmd.reset(this->CreateInsertSpecialGlyphCmd(textRange, font, glyph));
			if (attrCmd == nil)
			{
				ASSERT(attrCmd);
				break;
			}

			// in this case, we want to clear the AltGlyphAttr so that the
			// composer doesn't get confused.
			clearTextAttrCmd.reset(Utils<ITextAttrUtils>()->BuildClearTextAttrCmd(textModel, 
																				  start, 
																				  1, 
																				  kTextAttrOTFeatureListBoss, 
																				  kCharAttrStrandBoss));
			if (clearTextAttrCmd == nil)
			{
				ASSERT(clearTextAttrCmd);
				break;
			}
		}

		// see if there is anything to insert.
		if (insert->empty()) 
		{
			// display trace message: We've hit the 2 special cases. 
			SNIPLOG("InsertGlyph() - There are no characters to insert! We didn't hit any of the 5 cases - so we are skipping out.");
			break;
		}


		// ----------------------------------------------------------------
		// Decision tree is done, now process the commands in a sequence
		// ----------------------------------------------------------------
		seq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__);
		if (seq == nil) 
		{
			ASSERT(seq);
			break;
		}
	
		// Command 1: insert the character
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		if (textModelCmds == nil) 
		{
			ASSERT(textModelCmds);
			break;
		}
		InterfacePtr<ICommand> insertCmd(textModelCmds->InsertCmd(start, insert));
		status = CmdUtils::ProcessCommand(insertCmd);
		if (status != kSuccess) 
		{
			SNIPLOG("InsertGlyph() - InsertCmd failed.");
			break;
		}

		// Command 2: clear the attributes (if needed)
		if (clearTextAttrCmd)
		{
			status = CmdUtils::ProcessCommand(clearTextAttrCmd);
			if (status != kSuccess) 
			{
				SNIPLOG("InsertGlyph() - ClearTextAttrCmd failed.");
				break;
			}
		}

		// Command 3: Set the alt or special glyph attribute (if needed)
		if (attrCmd)
		{
			status = CmdUtils::ProcessCommand(attrCmd);
			if (status != kSuccess) 
			{
				SNIPLOG("InsertGlyph() - the attribute apply cmd failed.");
				break;
			}
		}

	} while (false);
 
	if (seq)
	{
		if (status == kSuccess) 
		{
			status = CmdUtils::EndCommandSequence(seq);
		}
		else
		{
			ASSERT_FAIL("InsertGlyph() failed! Aborting cmd sequence");
			ErrorUtils::PMSetGlobalErrorCode(status);
			CmdUtils::EndCommandSequence(seq);
		}
	}

	return status;
}

/* QueryFont
*/
IPMFont* SnpInsertGlyph::QueryFont(const InDesign::TextRange& textRange, 
								   PMString& fontFamilyName,
								   PMString& fontStyleName)
{
	InterfacePtr<IPMFont> font(nil);
	do {

		// get info from text range
		RangeData range = textRange.GetRange();
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		if (textModel == nil) 
		{
			ASSERT(textModel); break;
		}
		

		// query the compose scanner so we can query attributes
		InterfacePtr<IComposeScanner> composeScanner(textModel, UseDefaultIID());
		if (composeScanner == nil) 
		{
			ASSERT(composeScanner); break;
		}
		
		// get the font family UID
		InterfacePtr<const IAttrReport> fontUIDAttrReport(composeScanner->QueryAttributeAt(range, kTextAttrFontUIDBoss));
		if (fontUIDAttrReport == nil)
		{
			ASSERT(fontUIDAttrReport); break;
		}
		InterfacePtr<ITextAttrUID> fontUIDAttr(fontUIDAttrReport, UseDefaultIID());
		if (fontUIDAttr == nil)
		{
			ASSERT_MSG(fontUIDAttr, "Missing ITextAttrUID in QueryFont()");
			break;
		}
		UID fontUID = fontUIDAttr->Get();
		ASSERT_MSG(fontUID != kInvalidUID, "fontUID is invalid");

		// get the font style name
		InterfacePtr<const IAttrReport> fontStyleAttrReport(composeScanner->QueryAttributeAt(range, kTextAttrFontStyleBoss));
		if (fontStyleAttrReport == nil)
		{
			ASSERT(fontStyleAttrReport); break;
		}
		InterfacePtr<ITextAttrFont> fontStyleAttr(fontStyleAttrReport, UseDefaultIID());
		if (fontStyleAttr == nil)
		{
			ASSERT_MSG(fontStyleAttr, "Missing ITextAttrFont in QueryFont()");
			break;
		}

		// get the font family
        InterfacePtr<IFontFamily> fontFamily(::GetDataBase(textModel), fontUID, UseDefaultIID());
		if (fontFamily == nil)
		{
			ASSERT(fontFamily); break;
		}

		fontStyleName = fontStyleAttr->GetFontName();
		if (fontStyleName.empty()) 
		{
			// Font style name is empty.
			// You fall into this case if you haven't set the font face on the selected text.
			// Suggestion - set the font face on the selected text.
			IDrawingStyle* drawingStyle = nil;
			TextIterator textIter = composeScanner->QueryDataAt(range.Start(nil), &drawingStyle, nil);
			if (textIter.IsNull() == kFalse && 
				drawingStyle) 
			{
				// get the font
				font.reset(drawingStyle->QueryFont());
				// release drawingStyle - it was addref'ed in QueryDataAt()
				drawingStyle->Release();

				// get the font family name 
				fontFamilyName.Clear();
				font->AppendFamilyName(fontFamilyName);
				
				// get the font style name 
				fontStyleName.Clear();
				font->AppendStyleName(fontStyleName);
			}
		}
		else
		{
			// get the font
			font.reset(fontFamily->QueryFace(fontStyleName));

			// got the font family name
			fontFamilyName = fontFamily->GetFamilyName();
			ASSERT_MSG(fontFamilyName.empty() == kFalse, "Font family name is empty");
		}
		ASSERT_MSG(font, "Could not query the font");


	} while (false);
	return font.forget();
}


/* GlyphToCharacter
*/
const UTF32TextChar SnpInsertGlyph::GlyphToCharacter(IPMFont* font, 
													 const Text::GlyphID glyph, 
													 UTF32TextChar* userAreaChar /*= nil*/)
{
	UTF32TextChar retval(kTextChar_Null);
#if defined(__IGlyphUtils__)
	ASSERT_FAIL("SnpInsertGlyph::GlyphToCharacter() obsoleted - Call Utils<IGlyphUtils>()->GlyphToCharacter() directly");
#else
	const int32 kCTUseAppleDeprecatedMappings = 256;
    bool16 result = CTUnicodeTranslator::Instance()->GlyphIDToTextChar(font, 
																	   glyph, 
																	   &retval, 
																	   kCTUseAppleDeprecatedMappings);

	// if there is no Unicode mapping for the character, return an invalid textchar
	if (!result) 
	{ 
		retval = UTF32TextChar(kTextChar_Null); 
	} 

	// if the caller wants a Unicode user area text char
	if (userAreaChar != nil)
	{
		*userAreaChar = UTF32TextChar(kTextChar_Null);

		if(result == kTrue && 
		   retval.GetValue() >= kTextChar_PrivateZoneStart && 
		   retval.GetValue() <= kTextChar_PrivateZoneEnd)
		{
			*userAreaChar = retval;
			retval = UTF32TextChar(kTextChar_Null);
		}
	}
#endif
	return retval;
}

/* GetOpenTypeFeatureList
*/
const OpenTypeFeatureList SnpInsertGlyph::GetOpenTypeFeatureList(IPMFont* font, 
																 const Text::GlyphID glyph)
{
	OpenTypeFeatureList featureList;
	featureList.clear();
	do {
		if (font == nil) 
		{
			ASSERT(font);
			break;
		}

		int32 featureToSearchCount = -1; // search all!
		const char* featuresToSearch = nil; // get all features
		GlyphAccessData glyphAccessData;
		glyphAccessData.fDesiredTag = 0; // no preferred tag - get them all
		glyphAccessData.fDesiredTextChars = WideString("");
		
		// get the open type features on this glyph
		bool16 error = font->GetOTGlyphAccess(glyph, 
											  &glyphAccessData, 
											  featureToSearchCount, 
											  featuresToSearch);

		if (error) 
		{
			ASSERT_FAIL("GetOTGlyphAccess() reported an error - bad glyph?");
			break;
		}
		
		// extract the feature list.
        featureList = glyphAccessData.fFeatureList;

	} while (false);
	return featureList;
}

/* CreateInsertAltGlyphCmd
*/
ICommand* SnpInsertGlyph::CreateInsertAltGlyphCmd(const InDesign::TextRange& textRange, 
												  IPMFont* font, 
												  const OpenTypeFeatureList& featureList)
{
	InterfacePtr<ICommand> attrCmd(nil);
	do {
		if (textRange.IsValid() == kFalse || 
			font == nil) 
		{
			ASSERT_FAIL("CreateInsertSpecialGlyphCmd() - One or more preconditions not met. Exiting...");
			break;
		}

		// get info from text range
		TextIndex start = textRange.GetRange().Start(nil);
		int32 length = textRange.GetRange().Length();
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		if (textModel == nil) 
		{
			ASSERT(textModel);
			break;
		}

		// apply the kTextAttrOTFeatureListBoss
		InterfacePtr<ITextAttrOTFeatureList> openTypeFeatureListAttr
			(::CreateObject2<ITextAttrOTFeatureList>(kTextAttrOTFeatureListBoss));
		if (openTypeFeatureListAttr == nil) 
		{
			ASSERT(openTypeFeatureListAttr);
			break;
		}
		// set the glyph name (as nil)
		openTypeFeatureListAttr->SetFeatureList(featureList);
		
		// and we want to apply the special glyph attribute.
		// NOTE: This does an AddRef
		attrCmd.reset(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, start, 1, openTypeFeatureListAttr, kCharAttrStrandBoss));

	} while (false);

	ASSERT(attrCmd);
	return attrCmd.forget();
}
	
/* CreateInsertSpecialGlyphCmd
*/
ICommand* SnpInsertGlyph::CreateInsertSpecialGlyphCmd(const InDesign::TextRange& textRange, 
													  IPMFont* font, 
													  const Text::GlyphID glyph)
{
	InterfacePtr<ICommand> attrCmd(nil);
	do {
		if (textRange.IsValid() == kFalse || 
			font == nil ||
			glyph == kInvalidGlyphID) 
		{
			ASSERT_FAIL("CreateInsertSpecialGlyphCmd() - One or more preconditions not met. Exiting...");
			break;
		}
		
		// get info from text range
		TextIndex start = textRange.GetRange().Start(nil);
		int32 length = textRange.GetRange().Length();
		InterfacePtr<ITextModel> textModel(textRange.QueryModel());
		if (textModel == nil) 
		{
			ASSERT(textModel);
			break;
		}

		// apply the kTextAttrSpecialGlyphBoss
		InterfacePtr<ITextAttrSpecialGlyph> specialGlyphAttr
			(::CreateObject2<ITextAttrSpecialGlyph>(kTextAttrSpecialGlyphBoss));
		if (specialGlyphAttr == nil) 
		{
			ASSERT(specialGlyphAttr);
			break;
		}
		// set the glyph name (as nil)
		specialGlyphAttr->Set(nil);
		// set the glyph ID
		specialGlyphAttr->SetGlyphID(glyph);
		// get the glyphname from the font - only if available
		if (font->GetNumGlyphNames() > 0)
		{
			std::string glyphName = font->GetGlyphName(glyph);
			if (glyphName.size() > 0)
			{
				specialGlyphAttr->Set(glyphName.c_str());
			}
		}
		/* OBSOLETE CODE - GetValDataLength and GetVal will cause an assertion failure.
		int32 size = font->GetValDataLength(kCharStringNames);
		if (size)
		{
			ASSERT_MSG(glyph < size / 4, "There aren't enough glyph names in this font!");
			char** glyphNames = new char*[size / sizeof(char*)];
			if (font->GetVal(kCharStringNames, glyphNames, size))
			{
				// if it's name is blank leave it nil in the attr
				if (strlen(glyphNames[glyph]) > 0) 
				{
					// found the glyph name - set it
					specialGlyphAttr->Set(glyphNames[glyph]);
				}
			}
			if (glyphNames) 
			{
				delete [] glyphNames;
				glyphNames = nil;
			}
		}
		*/

		const char* gn = specialGlyphAttr->Get();
		SNIPLOG("   CreateInsertSpecialGlyphCmd() - glyphID = 0x%X, glyphName=\"%s\"", 
				specialGlyphAttr->GetGlyphID(), 
				(gn != nil) ? gn : "<none>");


		// and we want to apply the special glyph attribute.
		// NOTE: This does an AddRef
		attrCmd.reset(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, 
																	 start, 
																	 1, 
																	 specialGlyphAttr, 
																	 kCharAttrStrandBoss));

	} while (false);

	ASSERT(attrCmd);
	return attrCmd.forget();
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpInsertGlyph available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerInsertGlyph : public SnpRunnable
{

public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerInsertGlyph(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerInsertGlyph(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextTargetContext;}
};

/* Constructor.
*/
_SnpRunnerInsertGlyph::_SnpRunnerInsertGlyph(void) : SnpRunnable("InsertGlyph")
{
	this->SetDescription("Inserts a glyph in various ways");
    this->SetPreconditions("Should be able to insert test");
	this->SetCategories("sdk_snippet, sdk_text, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerInsertGlyph::~_SnpRunnerInsertGlyph(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerInsertGlyph::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			break;
		}
		if (textTarget->GetRange().Start(nil) < 0 ||
			textTarget->GetTextModel().ExistsInDB() == kFalse)
		{
			break;
		}

		// if we got here, we can run.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInsertGlyph::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpInsertGlyph instance;
		// get the text target, model, and selected range
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
		if (textTarget == nil) 
		{
			SNIPLOG("You do not have a text selection.  Exiting...");
			break;
		}
		InterfacePtr<ITextModel> textModel(textTarget->QueryTextModel());
		RangeData range = textTarget->GetRange();
        InDesign::TextRange textRange(textModel, range);
		if (textRange.IsValid() == kFalse)
		{
			ASSERT_FAIL("TextRange is invalid!");
			break;
		}

		// get the current font 
		PMString fontFamilyName, fontStyleName;
		InterfacePtr<IPMFont> font(instance.QueryFont(textRange, fontFamilyName, fontStyleName));
		if (font == nil) 
		{
			SNIPLOG("Couldn't get current font at text insertion point. Exiting...");
			break;
		}
		// get the number of glyphs
		int32 numGlyphs = font->GetNumGlyphs();

		// get user choices
		Utils<ISnipRunParameterUtils> parameterUtils;
		PMString prompt;
		prompt.SetCString("Enter a glyph ID to insert\n(using font = ", PMString::kUnknownEncoding);
		prompt += fontFamilyName;
		if (fontStyleName.empty() == kFalse) 
		{
			prompt += "-";
			prompt += fontStyleName;
		}
		prompt += ")";
		/* Try these on Kozuka Mincho Std or Kozuka Gothic Std!
		// Don't use 0 since that's usually the notdefglyph (IPMFont::GetNotDefinedGlyph())
		int32 defaultGlyph = 8166; // has no Unicode codepoint
		int32 defaultGlyph = 8167; // has no Unicode codepoint
		int32 defaultGlyph = 8168; // has no Unicode codepoint
		int32 defaultGlyph = 8057; // has no ShiftJIS codepoint but has Unicode codepoint
		int32 defaultGlyph = 8058; // has Unicode codepoint
		int32 defaultGlyph = 3621; // wataNABE, Unicode 0x8FBA
		int32 defaultGlyph = 6929; // wataNABE, Unicode 0x908A
		int32 defaultGlyph = 6930; // wataNABE, Unicode 0x9089 (Use OpenType Pro font)
		int32 defaultGlyph = 13407; // wataNABE, Unicode 0x9089 + 'jp78' (Use OpenType Pro font)
		int32 defaultGlyph = 14235; // wataNABE, Unicode 0x9089 + 'aalt' (Use OpenType Pro font)
		... Upto 20 more variations of NABE exist in OpenType Pro fonts.
		*/
		int32 defaultGlyph = (font->GetWritingScript() == 1) ? 
							8166 :  /* Japanese script */
							36 ;    /* Other scripts */
		if (defaultGlyph > numGlyphs) 
		{
			// some fonts don't even have this many glyphs. 
			// in that case, coerce to the upper limit.
			defaultGlyph = numGlyphs - 1;
		}
		Text::GlyphID glyph = (Text::GlyphID)parameterUtils->GetInt32(prompt, defaultGlyph, 1, numGlyphs - 1); 
		if (parameterUtils->WasDialogCancelled()) 
		{
			// cancelled!
			break;
		}

		// insert the glyph
		status = instance.InsertGlyph(textRange, font, glyph);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInsertGlyph instance_SnpRunnerInsertGlyph;
DEFINE_SNIPPET(_SnpRunnerInsertGlyph) 	

// End, SnpInsertGlyph.cpp

