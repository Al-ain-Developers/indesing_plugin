//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpFindAndReplace.cpp $
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
#include "IBoolData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IFindChangeCmdData.h"
#include "IFindChangeOptions.h"
#include "IIntData.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "IStringData.h"
#include "ITextWalker.h" // also declares ITextWalkerClient
#include "ITextWalkerScope.h"
#include "ITextWalkerSelectionUtils.h"
#include "IWalkerScopeFactoryUtils.h"
#include "IStyleUnpacker.h"
#include "IGraphicAttrClassID.h"
#include "IGraphicAttributeUtils.h"
#include "IFindChangeFormatCmdData.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "IWorkspace.h"
#include "IObjectStylesUtils.h"
#include "IObjectAttributeList.h"
#include "IFindChangeFormatData.h"


// General includes:
#include "CmdUtils.h"
#include "PreferenceUtils.h" // QuerySessionPreferences
#include "Utils.h"
#include "InstStrokeFillID.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

#define ASSERT_BREAK_IF_NIL(p) { ASSERT(p); if (p == nil) { break; } }

/** \li How to set up and perform find change text,
 * 	\li How to set up and perform find change text use grep (Grep search),
 * 	\li How to set up and perform find change glyph,
 * 	\li How to set up and perform find change frame object.

 * 
 * 	This snippet shows you how to do the equivalent of a search/replace in the find/change dialog. 
 *  With this code snippet, you can either:
 * 	\li <B>find text</B>,
 * 	\li <B>replace text</B>.
 * 	\li <B>find text with grep</B>,
 * 	\li <B>replace text with grep</B>.
 * 	\li <B>find glyph</B>,
 * 	\li <B>replace glyph</B>.
 * 	\li <B>find object</B>,
 * 	\li <B>replace object</B>.
 * 
 *  One of the most important interface for find/change is IFindChangeOptions. 
 *  It caches/stores options that are needed to perform search or replace.
 *  
 *  InDesign support find/change text, grep, glyph and object. They are specified
 *  in SearchMode in IFindChangeOptions, as kTextSearch, kGrepSearch, kGlyphSearch
 *  and kObjectSearch respectively.

 * 	Find/change functionalilty can be achive in following two steps:
 *  \li <B>Set up find/change options </B> 
 *  \li <B>Perform find or change </B>
 *  Although these two step are coupled together in our sample code, they
 *  can separated executed. For example, you can set find/change text string
 *  and find/change glyph IDs first, then set search mode to kTextSearch and 
 *  search for text. After that, reset search mode to kGlyphSearch and search
 *  for glyphs.
 *
 * 	While this code snippet processes a multitude of commands to perform each task, 
 * 	there are still some useful find/change related commands that are not used in
 * 	this code snippet.
 *  <BR>
 *  [Commands for find/change based on formats]
 * 	\li kReplaceAllApplyFormatCmdBoss
 * 	\li kClearFindFormatCmdBoss: to clear the find format
 * 	\li kClearChangeFormatCmdBoss: to clear the change format
 *  <BR>
 *  [Commands for find/change based on Japanese character types]
 * 	\li kFindChangeModeCmdBoss: To set the find/replace mode between "Change" (for text) and "Transliterate"
 * 		for Japanese character types. See IFindChangeOptions::ChangeMode.
 * 		(NOTE: This code snippet assumes that "Change" is used, however	if you want to search 
 * 		based on Japanese character types, you must first change the mode with this	command.)
 * 	\li kFindCharacterTypeCmdBoss: To set the find character type (see IFindChangeOptions::CharacterType)
 *  \li kReplaceCharacterTypeCmdBoss: To set the find character type (see IFindChangeOptions::CharacterType)
 *  <BR>
 *  [Commands for setting find/change scope options]
 * 	\li kIncludeLockedStoriesForFindCmdBoss: Find only option, if include locked stories.
 *  \li kIncludeLockedLayersForFindCmdBoss: Find only option, if include locked layers.
 * 	\li	kIncludeHiddenLayersCmdBoss: Find/change include hidden layers?
 *  \li kIncludeMasterPagesCmdBoss: Find/change include master page items?
 *  \li kIncludeFootnotesCmdBoss: Find/change include text in foot notes?
 *
 * 
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_text
 * 	@see IK2ServiceRegistry
 * 	@see IK2ServiceProvider
 * 	@see IFindChangeOptions
 * 	@see IFindChangeCmdData
 * 	@see ITextWalker
 * 	@see ITextWalkerScope
 * 	@see IWalkerScopeFactoryUtils
 * 	@see ITextWalkerSelectionUtils
 * 	@see IStringData
 * 	@see IIntData
 * 	@see IBoolData
 * 	@see kFindStringCmdBoss
 * 	@see kReplaceStringCmdBoss
 * 	@see kScopeCmdBoss
 * 	@see kFindTextCmdBoss
 * 	@see kTWReplaceTextCmdBoss
 * 	@see kReplaceFindTextCmdBoss
 * 	@see kReplaceAllTextCmdBoss
 * 	@see kEntireWordCmdBoss
 * 	@see kCaseSensitiveCmdBoss
 * 	@see kKanaSensitiveCmdBoss
 * 	@see kWidthSensitiveCmdBoss
 */
class SnpFindAndReplace
{
public:
	/** Constructor. */
	SnpFindAndReplace(void) {}

	/** Destructor. */
	~SnpFindAndReplace(void){}

	/** Calls a series of commands to find text or grep.
	 * 	@param searchMode IN The serach mode.  This method support either kTextSearch or kGrepSearch.
	 * 	@param findString IN The text or grep string to find.
	 * 	@param findScope IN The scope of the find. 
	 * 	@param entireWord IN Whether to match the entire word or not. 
	 * 			kTrue = match entire word. Default is kFalse.
	 * 	@param caseSensitive IN Whether to match in a case-sensitive manner or not.  
	 * 			kTrue = case-sensitive. Default is kFalse
	 * 	@param distinguishKanaType IN Whether to match based on the type of kana
	 * 			(hiragana or katakana). kTrue = match based on type of kana.
	 * 			Default is kFalse.
	 * 	@param distinguishKanaWidths IN Whether to match based on kana width
	 * 			(half-width "hankaku", or full-width "zenkaku"). kTrue = match based on 
	 * 			kana width.  Default is kTrue.
	 * 	@return Status code. See IFindChangeService::FindChangeResult
	 * 	@see IFindChangeService::FindChangeResult 
	 */
	IFindChangeService::FindChangeResult Do_FindText(const IFindChangeOptions::SearchMode searchMode,
													 const PMString& findString, 
													 const IWalkerScopeFactoryUtils::WalkScopeType findScope,
													 const bool16 entireWord = kFalse,
													 const bool16 caseSensitive = kFalse, 
													 const bool16 distinguishKanaType = kFalse,
													 const bool16 distinguishKanaWidths = kTrue);

	/** Calls a series of commands to find and replace text or with grep.
	 * 	@param searchMode IN The serach mode. This method support either kTextSearch or kGrepSearch.
	 * 	@param findString IN The text/grep string to find.
	 * 	@param findString IN The text/grep string to replace with.
	 * 	@param findScope IN The scope of the find and replace.
	 * 	@param replaceMode IN A command class ID that specifies which replacement mode to use.
	 * 		Only three are supported by this code snippet: 
	 * 		(1) kTWReplaceTextCmdBoss, 
	 * 		(2) kReplaceFindTextCmdBoss and 
	 * 		(3) kReplaceAllCmdBoss.
	 * 	@param entireWord IN Whether to match the entire word or not. 
	 * 			kTrue = match entire word. Default is kFalse.
	 * 	@param caseSensitive IN Whether to match in a case-sensitive manner or not.  
	 * 			kTrue = case-sensitive. Default is kFalse
	 * 	@param distinguishKanaType IN Whether to match based on the type of kana
	 * 			(hiragana or katakana). kTrue = match based on type of kana.
	 * 			Default is kFalse.
	 * 	@param distinguishKanaWidths IN Whether to match based on kana width
	 * 			(half-width "hankaku", or full-width "zenkaku"). kTrue = match based on 
	 * 			kana width.  Default is kTrue.
	 * 	@return Status code. See IFindChangeService::FindChangeResult
	 * 	@see IFindChangeService::FindChangeResult 
	 */
	IFindChangeService::FindChangeResult Do_ReplaceText(const IFindChangeOptions::SearchMode searchMode,
														const PMString& findString, 
														const PMString& replaceString, 
														const IWalkerScopeFactoryUtils::WalkScopeType findScope, 
														const ClassID& replaceMode, 
														const bool16 entireWord = kFalse,
														const bool16 caseSensitive = kFalse, 
														const bool16 distinguishKanaType = kFalse,
														const bool16 distinguishKanaWidths = kTrue);

	/** Calls a series of commands to find glyph.
	 * 	@param findGlyphID IN The glyph to find.
	 * 	@param findScope IN The scope of the find and replace.
	 */
	IFindChangeService::FindChangeResult Do_FindGlyph(const Text::GlyphID findGlyphID, 
													  const IWalkerScopeFactoryUtils::WalkScopeType findScope);

	/** Calls a series of commands to find and replace glyph.
	 * 	@param findGlyphID IN The glyph to find.
	 * 	@param replaceGlyphID IN The glyph to replace with.
	 * 	@param findScope IN The scope of the find and replace.
	 * 	@param replaceMode IN A command class ID that specifies which replacement mode to use.
	 * 		Only three are supported by this code snippet: 
	 * 		(1) kTWReplaceTextCmdBoss, 
	 * 		(2) kReplaceFindTextCmdBoss and 
	 * 		(3) kReplaceAllCmdBoss.
	 * 	@see IFindChangeService::FindChangeResult 
	 */
	IFindChangeService::FindChangeResult Do_ReplaceGlyph(const Text::GlyphID findGlyphID, 
														 const Text::GlyphID replaceGlyphID, 
														 const IWalkerScopeFactoryUtils::WalkScopeType findScope, 
														 const ClassID& replaceMode);

	/** Reports the status returned from either Do_FindText or Do_ReplaceText.
	 * 	@param status IN  IFindChangeService::FindChangeResult returned from 
	 * 		either Do_FindText or Do_ReplaceText.
	 * 	@return General status code, indicating whether the code snippet succeeded or failed. 
	 * 	@see IFindChangeService::FindChangeResult
	 * 	@see Do_FindText
	 * 	@see Do_ReplaceText
	 */
    ErrorCode ReportError(const IFindChangeService::FindChangeResult status);

private:
	/** The command specified with ClassID is processed by passing in PMString data.
	 * 	The find-change commands that should be processed with this method are the 
	 * 	command bosses with IID_ISTRINGDATA. They are:
	 * 	\li kFindStringCmdBoss
	 * 	\li kReplaceStringCmdBoss
	 * 	@param commandBoss IN ClassID of the command to be processed.
	 * 	@param str IN The string to use by the find command or the replacement command.
	 * 	@param searchMode IN find/change search mode for setting strings.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ProcessFindChangeCommandString(const ClassID& commandBoss, const PMString& str, IFindChangeOptions::SearchMode searchMode);

	/** The command specified with ClassID is processed by passing in 32-bit integer data.
	 * 	The find-change commands that should be processed with this method are the 
	 * 	command bosses with IID_IINTDATA. They are:
	 * 	\li kFindChangeModeCmdBoss (untested in this code snippet)
	 *  \li kFindSearchModeCmdBoss,
	 * 	\li kScopeCmdBoss
	 * 	\li kFindCharacterTypeCmdBoss (untested in this code snippet)
	 *  \li kReplaceCharacterTypeCmdBoss (untested in this code snippet)
	 * 	@param commandBoss IN ClassID of the command to be processed.
	 * 	@param value IN Value for the setup, such as find scope.
	 * 	@param searchMode IN find/change search mode.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ProcessFindChangeCommandInt32(const ClassID& commandBoss, const int32 value, IFindChangeOptions::SearchMode searchMode);

	/** The command specified with ClassID is processed by passing in boolean data.
	 * 	The find-change commands that should be processed with this method are the 
	 * 	command bosses with IID_IBOOLDATA. They are:
	 * 	\li kEntireWordCmdBoss
	 * 	\li kCaseSensitiveCmdBoss
	 * 	\li kKanaSensitiveCmdBoss
	 * 	\li kWidthSensitiveCmdBoss
	 * 	@param commandBoss IN ClassID of the command to be processed.
	 * 	@param value IN Value for the setup, such as whole word searching (on/off).
	 * 	@param searchMode IN find/change search mode.
	 * 	@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ProcessFindChangeCommandBool(const ClassID& commandBoss, const bool16 value, IFindChangeOptions::SearchMode searchMode);

	/**	This method processes a specific Find and/or Replace command.
	 * 	The find-change commands that should be processed with this method are the 
	 * 	command bosses with IID_IFINDCHANGECMDDATA. They are:
	 * 	\li kFindTextCmdBoss
	 * 	\li kTWReplaceTextCmdBoss
	 * 	\li kReplaceFindTextCmdBoss
	 * 	\li kReplaceAllTextCmdBoss
	 * 	@param commandBoss IN ClassID of the command to be processed.
	 * 	@return The result of the search. (kSuccess, kFailure, kNotFound, kFoundCompleted, kReplaceAllCompleted)
	*/
	IFindChangeService::FindChangeResult ProcessFindChangeCommand(const ClassID& commandBoss);

};

/* Do_FindText
*/
IFindChangeService::FindChangeResult SnpFindAndReplace::Do_FindText(const IFindChangeOptions::SearchMode searchMode,
																	const PMString& findString, 
																	const IWalkerScopeFactoryUtils::WalkScopeType findScope,
																	const bool16 entireWord,
																	const bool16 caseSensitive, 
																	const bool16 distinguishKanaType,
																	const bool16 distinguishKanaWidths)
{
	IFindChangeService::FindChangeResult status = IFindChangeService::kFailure;
	ErrorCode internalStatus = kFailure;
	do
	{
		/* check to see if findString is empty */
		if (findString.empty())
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: findString is empty!");
			break;
		}
		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: fomdScope is 'kEmptyScope'!");
			break;
		}

		// set the search mode
		internalStatus = ProcessFindChangeCommandInt32(kFindSearchModeCmdBoss, searchMode, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kFindSearchModeCmdBoss failed with error code %d", status);
			break;
		}

		// set the find string
		internalStatus = ProcessFindChangeCommandString(kFindStringCmdBoss, findString, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kFindStringCmdBoss failed with error code %d", status);
			break;
		}
		// set the find scope
		internalStatus = ProcessFindChangeCommandInt32(kScopeCmdBoss, findScope, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kScopeCmdBoss failed with error code %d", status);
			break;
		}
		// set the entire word flag
		internalStatus = ProcessFindChangeCommandBool(kEntireWordCmdBoss, entireWord, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kEntireWordCmdBoss failed with error code %d", status);
			break;
		}
		// set the case sensitive flag
		internalStatus = ProcessFindChangeCommandBool(kCaseSensitiveCmdBoss, caseSensitive, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kCaseSensitiveCmdBoss failed with error code %d", status);
			break;
		}
		// Japanese: set the distinguish kana type (hiragana vs katakana) flag
		internalStatus = ProcessFindChangeCommandBool(kKanaSensitiveCmdBoss, distinguishKanaType, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kKanaSensitiveCmdBoss failed with error code %d", status);
			break;
		}
		// Japanese: set the distinguish kana widths (half-width vs full-width) flag
		internalStatus = ProcessFindChangeCommandBool(kWidthSensitiveCmdBoss, distinguishKanaWidths, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kWidthSensitiveCmdBoss failed with error code %d", status);
			break;
		}

		// do the find
		status = ProcessFindChangeCommand(kFindTextCmdBoss);
	} while (false);
	return status;
}

/* Do_ReplaceText
*/
IFindChangeService::FindChangeResult SnpFindAndReplace::Do_ReplaceText(const IFindChangeOptions::SearchMode searchMode,
																	   const PMString& findString, 
																	   const PMString& replaceString, 
																	   const IWalkerScopeFactoryUtils::WalkScopeType findScope, 
																	   const ClassID& replaceMode,
																	   const bool16 entireWord,
																	   const bool16 caseSensitive, 
																	   const bool16 distinguishKanaType,
																	   const bool16 distinguishKanaWidths)
{
	IFindChangeService::FindChangeResult status = IFindChangeService::kFailure;
	ErrorCode internalStatus = kFailure;
	do
	{
		/* check to make sure that replaceMode is is an acceptable one. */
		if (replaceMode != kTWReplaceTextCmdBoss && 
			replaceMode != kReplaceFindTextCmdBoss && 
			replaceMode != kReplaceAllTextCmdBoss)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: Invalid replaceMode!");
			break;
		}
		/* check to see if findString is empty */
		if (findString.empty())
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: findString is empty!");
			break;
		}
		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: fomdScope is 'kEmptyScope'!");
			break;
		}

		// set the search mode
		internalStatus = ProcessFindChangeCommandInt32(kFindSearchModeCmdBoss, searchMode, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: kFindSearchModeCmdBoss failed with error code %d", status);
			break;
		}

		// set the find string
		internalStatus = ProcessFindChangeCommandString(kFindStringCmdBoss, findString, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: kFindStringCmdBoss failed with error code %d", status);
			break;
		}
		// set the replace string
		internalStatus = ProcessFindChangeCommandString(kReplaceStringCmdBoss, replaceString, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: kReplaceStringCmdBoss failed with error code %d", status);
			break;
		}
		// set the find scope
		internalStatus = ProcessFindChangeCommandInt32(kScopeCmdBoss, findScope, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceText: kScopeCmdBoss failed with error code %d", status);
			break;
		}
		// set the entire word flag
		internalStatus = ProcessFindChangeCommandBool(kEntireWordCmdBoss, entireWord, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kEntireWordCmdBoss failed with error code %d", status);
			break;
		}
		// set the case sensitive flag
		internalStatus = ProcessFindChangeCommandBool(kCaseSensitiveCmdBoss, caseSensitive, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kCaseSensitiveCmdBoss failed with error code %d", status);
			break;
		}
		// Japanese: set the distinguish kana type (hiragana vs katakana) flag
		internalStatus = ProcessFindChangeCommandBool(kKanaSensitiveCmdBoss, distinguishKanaType, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kKanaSensitiveCmdBoss failed with error code %d", status);
			break;
		}
		// Japanese: set the distinguish kana widths (half-width vs full-width) flag
		internalStatus = ProcessFindChangeCommandBool(kWidthSensitiveCmdBoss, distinguishKanaWidths, searchMode);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindText: kWidthSensitiveCmdBoss failed with error code %d", status);
			break;
		}
		// do the replacement
		status = ProcessFindChangeCommand(replaceMode);
	} while (false);
	return status;
}

/* Do_FindGlyph
*/
IFindChangeService::FindChangeResult SnpFindAndReplace::Do_FindGlyph(const Text::GlyphID findGlyphID, 
																	const IWalkerScopeFactoryUtils::WalkScopeType findScope)
{
	IFindChangeService::FindChangeResult status = IFindChangeService::kFailure;
	ErrorCode internalStatus = kFailure;
	do
	{
		/* check to see if findGlyphID is empty */
		if (findGlyphID == kInvalidGlyphID)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindGlyph: findGlyphID is invalid!");
			break;
		}
		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindGlyph: fomdScope is 'kEmptyScope'!");
			break;
		}

		// set the search mode
		internalStatus = ProcessFindChangeCommandInt32(kFindSearchModeCmdBoss, IFindChangeOptions::kGlyphSearch, IFindChangeOptions::kGlyphSearch);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindGlyph: kFindSearchModeCmdBoss failed with error code %d", status);
			break;
		}

		// set find glyph ID
		InterfacePtr<ICommand> setGlyphCmd(CmdUtils::CreateCommand(kFindChangeGlyphIDCmdBoss));
		InterfacePtr<IIntData> glyphIDData(setGlyphCmd,UseDefaultIID());
		glyphIDData->Set(findGlyphID);
		InterfacePtr<IBoolData> findMode(setGlyphCmd,UseDefaultIID());
		findMode->Set(kTrue);
		CmdUtils::ProcessCommand(setGlyphCmd);

		// set the find scope
		internalStatus = ProcessFindChangeCommandInt32(kScopeCmdBoss, findScope, IFindChangeOptions::kGlyphSearch);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindGlyph: kScopeCmdBoss failed with error code %d", status);
			break;
		}

		// We can do same way as previous text search modes by set IFindChangeOptions::kGlyphSearch
		// and process command directly. But we can also utilize IFindChangeService 
		InterfacePtr<IFindChangeService> findChangeService ( (IFindChangeService*)::CreateObject(kFindChangeServiceBoss, IID_IFINDCHANGSERVICE));
		if (!findChangeService)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindGlyph: failed to create find change service");
			break;
		}

		// the find change options should already been set at this point. 
		// Good for FindNext shortcut(F3)
		TextIndex start, end;
		status = findChangeService->SearchText(start, end);

	} while (false);
	return status;
}

/* Do_ReplaceGlyph
*/
IFindChangeService::FindChangeResult SnpFindAndReplace::Do_ReplaceGlyph(const Text::GlyphID findGlyphID, 
																	   const Text::GlyphID replaceGlyphID, 
																	   const IWalkerScopeFactoryUtils::WalkScopeType findScope, 
																	   const ClassID& replaceMode)
{
	IFindChangeService::FindChangeResult status = IFindChangeService::kFailure;
	ErrorCode internalStatus = kFailure;
	do
	{
		/* check to see if findGlyphID is empty */
		if (findGlyphID == kInvalidGlyphID)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: findGlyphID is invalid!");
			break;
		}

		/* check to see if replaceGlyphID is empty */
		if (replaceGlyphID == kInvalidGlyphID)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: replaceGlyphID is invalid!");
			break;
		}

		// At this point, if you have never used find/change dialog during this session,
		// You may need to use kFindChangeGlyphFontCmdBoss to set find/change Font.
		// (applying kTextAttrFontUIDBoss and kTextAttrFontStyleBoss as ITextAttributes of the command)

		/* check to make sure that replaceMode is is an acceptable one. */
		if (replaceMode != kTWReplaceTextCmdBoss && 
			replaceMode != kReplaceFindTextCmdBoss && 
			replaceMode != kReplaceAllTextCmdBoss)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: Invalid replaceMode!");
			break;
		}

		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: fomdScope is 'kEmptyScope'!");
			break;
		}

		// set the search mode
		internalStatus = ProcessFindChangeCommandInt32(kFindSearchModeCmdBoss, IFindChangeOptions::kGlyphSearch, IFindChangeOptions::kGlyphSearch);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: kFindSearchModeCmdBoss failed with error code %d", status);
			break;
		}


		// set find glyph ID
		InterfacePtr<ICommand> setGlyphCmd(CmdUtils::CreateCommand(kFindChangeGlyphIDCmdBoss));
		InterfacePtr<IIntData> glyphIDData(setGlyphCmd,UseDefaultIID());
		glyphIDData->Set(findGlyphID);
		InterfacePtr<IBoolData> findMode(setGlyphCmd,UseDefaultIID());
		findMode->Set(kTrue);
		CmdUtils::ProcessCommand(setGlyphCmd);

		// set replace glyph ID
		InterfacePtr<ICommand> setGlyphCmd2(CmdUtils::CreateCommand(kFindChangeGlyphIDCmdBoss));
		InterfacePtr<IIntData> glyphIDData2(setGlyphCmd2,UseDefaultIID());
		glyphIDData2->Set(replaceGlyphID);
		InterfacePtr<IBoolData> findMode2(setGlyphCmd2,UseDefaultIID());
		findMode2->Set(kFalse);
		CmdUtils::ProcessCommand(setGlyphCmd2);

		// set the find scope
		internalStatus = ProcessFindChangeCommandInt32(kScopeCmdBoss, findScope, IFindChangeOptions::kGlyphSearch);
		if (internalStatus != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceGlyph: kScopeCmdBoss failed with error code %d", status);
			break;
		}

		// do the replacement
		status = ProcessFindChangeCommand(replaceMode);
	} while (false);
	return status;
}

/* ReportError
*/
ErrorCode SnpFindAndReplace::ReportError(const IFindChangeService::FindChangeResult status)
{
	PMString msg = "<UNKNOWN>";
	ErrorCode generalStatus = kSuccess;
	switch (status)
	{
	case IFindChangeService::kFailure:
		{
			msg = "Failure";
			generalStatus = kFailure;
			break;
		}
	case IFindChangeService::kSuccess:
		{
			msg = "Success";
			break;
		}
	case IFindChangeService::kNotFound:
		{
			msg = "Find text not found";
			break;
		}
	case IFindChangeService::kFoundCompleted:
		{
			msg = "Found and completed";
			break;
		}
	case IFindChangeService::kReplaceAllCompleted:
		{
			msg = "Replace all completed";
			break;
		}
	}
	SNIPLOG("SnpFindAndReplace RESULT: %s", msg.GetPlatformString().c_str());
	return generalStatus;
}

/* ProcessFindChangeCommandString
*/
ErrorCode SnpFindAndReplace::ProcessFindChangeCommandString(const ClassID& commandBoss, const PMString& str, IFindChangeOptions::SearchMode searchMode)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICommand>  pCommand(CmdUtils::CreateCommand(commandBoss));
		ASSERT_BREAK_IF_NIL(pCommand);

		InterfacePtr<IStringData> pStringData(pCommand, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pStringData);

		pStringData->Set(str);
		InterfacePtr<IIntData> modeData(pCommand, IID_IFINDCHANGEMODEDATA);
		modeData->Set(searchMode);

		status = CmdUtils::ProcessCommand(pCommand);

	}while (false);
	return status;
}

/* ProcessFindChangeCommandInt32
*/
ErrorCode SnpFindAndReplace::ProcessFindChangeCommandInt32(const ClassID& commandBoss, const int32 value, IFindChangeOptions::SearchMode searchMode)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICommand>  pCommand(CmdUtils::CreateCommand(commandBoss));
		ASSERT_BREAK_IF_NIL(pCommand);

		InterfacePtr<IIntData>  pIntData(pCommand, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pIntData);

		pIntData->Set(value);
		InterfacePtr<IIntData> modeData(pCommand, IID_IFINDCHANGEMODEDATA);
		modeData->Set(searchMode);

		status = CmdUtils::ProcessCommand(pCommand);

	}while (false);
	return status;
}

/* ProcessFindChangeCommandBool
*/
ErrorCode SnpFindAndReplace::ProcessFindChangeCommandBool(const ClassID& commandBoss, const bool16 value, IFindChangeOptions::SearchMode searchMode)
{
	ErrorCode status = kFailure;
	do
	{
		InterfacePtr<ICommand>  pCommand(CmdUtils::CreateCommand(commandBoss));
		ASSERT_BREAK_IF_NIL(pCommand);

		InterfacePtr<IBoolData> pBoolData(pCommand, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pBoolData);

		pBoolData->Set(value);

		InterfacePtr<IIntData> modeData(pCommand, IID_IFINDCHANGEMODEDATA);
		modeData->Set(searchMode);

		status = CmdUtils::ProcessCommand(pCommand);

	}while (false);
	return status;
}

/* ProcessFindChangeCommand
*/
IFindChangeService::FindChangeResult SnpFindAndReplace::ProcessFindChangeCommand(const ClassID& commandBoss)
{
	IFindChangeService::FindChangeResult result = IFindChangeService::kFailure;
	do
	{
		InterfacePtr<ICommand> pCommand(CmdUtils::CreateCommand(commandBoss));
		ASSERT_BREAK_IF_NIL(pCommand);

		InterfacePtr<IK2ServiceRegistry> pServiceRegistry(GetExecutionContextSession(), UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pServiceRegistry);

		InterfacePtr<IK2ServiceProvider> pServiceProvider(pServiceRegistry->QueryServiceProviderByClassID(kTextWalkerService, kTextWalkerServiceProviderBoss));
		ASSERT_BREAK_IF_NIL(pServiceProvider);

		InterfacePtr<IFindChangeOptions> pFindChangeOptions(::QuerySessionPreferences<IFindChangeOptions>()); 
		ASSERT_BREAK_IF_NIL(pFindChangeOptions);

		InterfacePtr<IFindChangeCmdData> pCmdData(pCommand, UseDefaultIID());    
		ASSERT_BREAK_IF_NIL(pCmdData);

		InterfacePtr<ITextWalker> pWalker(pServiceProvider, UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pWalker);

		pCmdData->SetTextWalker(pWalker);

		if (!pWalker->IsWalking())
		{
			InterfacePtr<ITextWalkerScope> pScope(static_cast<ITextWalkerScope*>(Utils<IWalkerScopeFactoryUtils>()->QueryWalkerScope_UsingSelections(pFindChangeOptions->GetFindChangeScope(pFindChangeOptions->GetSearchMode()))));
            if (!pScope)
                 break;

			InterfacePtr<ITextWalkerClient> pClient(static_cast<ITextWalkerClient*>(::CreateObject2<ITextWalkerClient>(kFindChangeClientBoss)));
			ASSERT_BREAK_IF_NIL(pClient);

			pWalker->Initialize(pClient, pScope, pFindChangeOptions,nil);
		}

		//Critical section for Text Walker Selections
		InterfacePtr<ITextWalkerSelectionUtils> pUtils(pWalker,UseDefaultIID());
		ASSERT_BREAK_IF_NIL(pUtils);

		const TextWalkerSelections_CriticalSection criticalSection(pUtils);

		ErrorCode status = CmdUtils::ProcessCommand(pCommand);
		if (status != kSuccess)
		{
			break;
		}

		result = pCmdData->GetFindChangeResult();

		// Select text after successful find
		if (result == IFindChangeService::kSuccess)
		{
			TextIndex start = kInvalidTextIndex;
			TextIndex end = kInvalidTextIndex;
			UIDRef& textStory = pCmdData->GetRange(start, end);
			InterfacePtr<ITextWalkerSelectionUtils> pTextWalkerSelectUtils(pWalker, UseDefaultIID());
			ASSERT_BREAK_IF_NIL(pTextWalkerSelectUtils);
			pTextWalkerSelectUtils->SelectText(textStory, start, end - start);
		}

	} while (false);

	return result;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpFindAndReplace available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
 */
class _SnpRunnerFindAndReplace : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerFindAndReplace();

	/** Destructor.
	 */
	virtual         ~_SnpRunnerFindAndReplace();

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16          CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode       Run(ISnpRunnableContext* runnableContext);
		
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}

private:
	/** Drives the snippet runner parameter dialogs to get the options for
	 * 	finding text, then calls SnpFindAndReplace::Do_FindText to find text. */
	ErrorCode Run_FindText(IFindChangeOptions::SearchMode searchMode);

	/** Drives the snippet runner parameter dialogs to get the options for
	 * 	replacing text, then calls SnpFindAndReplace::Do_ReplaceText to replace text. */
	ErrorCode Run_ReplaceText(IFindChangeOptions::SearchMode searchMode);

	/** Drives the snippet runner parameter dialogs to get the options for
	 * 	finding text, then calls SnpFindAndReplace::Do_FindGlyph to find glyph. */
	ErrorCode Run_FindGlyph();

	/** Drives the snippet runner parameter dialogs to get the options for
	 * 	replacing text, then calls SnpFindAndReplace::Do_ReplaceGlyph to replace glyph. */
	ErrorCode Run_ReplaceGlyph();

	/** Find object. 
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run_FindObject(ISnpRunnableContext* runnableContext);

	/** Change object. 
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run_ReplaceObject(ISnpRunnableContext* iSnpRunnableContext);

	/** Drives snippet runner parameter dialog to get the find string option.
	 * 	@param findString OUT The user-specified find string.  */
	ErrorCode Do_SpecifyFindString(PMString& findString);

	/** Drives snippet runner parameter dialog to get the replace string option.
	 * 	@param replaceString OUT The user-specified replace string.  */
	ErrorCode Do_SpecifyReplaceString(PMString& replaceString);

	/** Drives snippet runner parameter dialog to get the find scope option.
	 * 	@param findScope OUT The user-specified find scope.  */
	ErrorCode Do_SpecifyFindScope(IWalkerScopeFactoryUtils::WalkScopeType& findScope);

	/** Drives snippet runner parameter dialog to get the find glyph option.
	 * 	@param findString OUT The user-specified find string.  */
	ErrorCode Do_SpecifyFindGlyph(Text::GlyphID& findGlyph);

	/** Drives snippet runner parameter dialog to get the replace glyph option.
	 * 	@param replaceString OUT The user-specified replace string.  */
	ErrorCode Do_SpecifyReplaceGlyph(Text::GlyphID& replaceGlyph);

	/** Drives snippet runner parameter dialog to get the object type.
	 * 	@param objType OUT The user-specified object type.  */
	ErrorCode Do_SpecifyObjectType(IFindChangeOptions::ObjectType& objType);

	/** Drives snippet runner parameter dialog to get the object style.
	 * 	@param objType OUT The user-specified object style.  */
	ErrorCode Do_SpecifyObjectStyle(ISnpRunnableContext* iSnpRunnableContext, UIDRef& objStyleUID, PMString reminder);

	/** cached find string. */
	PMString fFindString;
	/** cached replace string. */
	PMString fReplaceString;
	/** cached find scope */
	int32 fFindScopeEnum;
	/** cached replace mode */
	int32 fReplaceModeEnum;
	/** Flag: has a find text/grep/glyph/object operation been successfully completed? */
	bool16 fIsFoundSelected[5];
	/** Flag: object walker initinalized? */
    bool16  fInitialized;

};

/* Constructor.
*/
_SnpRunnerFindAndReplace::_SnpRunnerFindAndReplace() 
: 	SnpRunnable("FindAndReplace"), 
	fFindString(""), fReplaceString(""), fFindScopeEnum(0), fReplaceModeEnum(0),fInitialized(kFalse)

{
	this->SetDescription("This snippet code shows how to perform a Find/Replace with text, grep, glyph and object.");
	this->SetPreconditions("document open");
	this->SetCategories("sdk_snippet, sdk_text");
	for (int32 ii = 0; ii < 5; ii++)
	{
		fIsFoundSelected[ii] = kFalse;
	}
}

/* Destructor.
*/
_SnpRunnerFindAndReplace::~_SnpRunnerFindAndReplace()	
{
}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerFindAndReplace::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	//If there is a front document, we can run this snippet.
	IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
	if (doc)
	{
		result = kTrue;
	}
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerFindAndReplace::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	do
	{
		// Get current front document		
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
		if (doc == nil)
		{
			SNIPLOG("Please open a document and try again.");
			break;
		}

		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back(PMString("Find text"));
		choices.push_back(PMString("Replace text"));
		choices.push_back(PMString("Find text with grep"));
		choices.push_back(PMString("Replace text with grep"));
		choices.push_back(PMString("Find glyph"));
		choices.push_back(PMString("Replace glyph"));
		choices.push_back(PMString("Find object"));
		choices.push_back(PMString("Replace object"));
		enum { kRun_FindText, kRun_ReplaceText,  kRun_FindGrep, kRun_ReplaceGrep,  kRun_FindGlyph, kRun_ReplaceGlyph,  kRun_FindObject, kRun_ReplaceObject};
		int32 choice  = parameterUtils->GetChoice("Which operation would you like to perform?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// create a new instance of the snippet
		switch (choice)
		{
		case kRun_FindText:
			status = Run_FindText(IFindChangeOptions::kTextSearch);
			break;
		case kRun_ReplaceText:
			status = Run_ReplaceText(IFindChangeOptions::kTextSearch);
			break;
		case kRun_FindGrep:
			status = Run_FindText(IFindChangeOptions::kGrepSearch);
			break;
		case kRun_ReplaceGrep:
			status = Run_ReplaceText(IFindChangeOptions::kGrepSearch);
			break;
		case kRun_FindGlyph:
			status = Run_FindGlyph(); 
			break;
		case kRun_ReplaceGlyph:
			status = Run_ReplaceGlyph();
			break;
		case kRun_FindObject:
			status = Run_FindObject(runnableContext );
			break;
		case kRun_ReplaceObject:
			status =  Run_ReplaceObject(runnableContext); 
			break;
		default:
			SNIPLOG("Invalid choice");
			break;
		}
	} while (false);
	return status;
}

/* Run_FindText
*/
ErrorCode _SnpRunnerFindAndReplace::Run_FindText(IFindChangeOptions::SearchMode searchMode)
{
	ErrorCode status = kCancel;
	do
	{
		// step 1: specify find string
		PMString findString;
		status = Do_SpecifyFindString(findString);
		if (status == kCancel)
			break;

		// step 2: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		// step 3: do the find
		SnpFindAndReplace instance;
		IFindChangeService::FindChangeResult findStatus = instance.Do_FindText(searchMode, findString, findScope);
		if (findStatus == IFindChangeService::kSuccess)
		{
			// we have completed a successful find at least once - requirement for replacing
			fIsFoundSelected[searchMode] = kTrue;
		}
		status = instance.ReportError(findStatus);

	} while (false);
	return status;
}

/* Run_ReplaceText
*/
ErrorCode _SnpRunnerFindAndReplace::Run_ReplaceText(IFindChangeOptions::SearchMode searchMode)
{
	ErrorCode status = kCancel;
	do
	{
		// step 1: specify find string
		PMString findString;
		status = Do_SpecifyFindString(findString);
		if (status == kCancel)
			break;

		// step 2: specify replace string
		PMString replaceString;
		status = Do_SpecifyReplaceString(replaceString);
		if (status == kCancel)
			break;

		// step 3: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		// step 4: specify replace mode
		ClassID replaceMode = kReplaceAllTextCmdBoss;

		// step 5: do the find and replace
		SnpFindAndReplace instance;
		IFindChangeService::FindChangeResult findStatus = instance.Do_ReplaceText(searchMode, findString, replaceString, findScope, replaceMode);
		status = instance.ReportError(findStatus);

	} while (false);
	return status;
}

/* Run_FindGlyph
*/
ErrorCode _SnpRunnerFindAndReplace::Run_FindGlyph()
{
	ErrorCode status = kCancel;
	do
	{
		// step 1: specify find glyph
		Text::GlyphID findGlyph;
		status = Do_SpecifyFindGlyph(findGlyph);
		if (status == kCancel)
			break;

		// step 2: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		// step 3: do the find
		SnpFindAndReplace instance;
		IFindChangeService::FindChangeResult findStatus = instance.Do_FindGlyph(findGlyph, findScope);
		if (findStatus == IFindChangeService::kSuccess)
		{
			// we have completed a successful find at least once - requirement for replacing
			fIsFoundSelected[IFindChangeOptions::kGlyphSearch] = kTrue;
		}
		status = instance.ReportError(findStatus);

	} while (false);
	return status;
}

/* Run_ReplaceGlyph
*/
ErrorCode _SnpRunnerFindAndReplace::Run_ReplaceGlyph()
{
	ErrorCode status = kCancel;
	do
	{
		// step 1 & 2: specify find glyph and replace glyph
		Text::GlyphID findGlyph;
		status = Do_SpecifyFindGlyph(findGlyph);
		if (status == kCancel)
			break;

		Text::GlyphID replaceGlyph;
		status = Do_SpecifyReplaceGlyph(replaceGlyph);
		if (status == kCancel)
			break;

		// step 3: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		// step 4: specify replace mode
		ClassID replaceMode = kReplaceAllTextCmdBoss;

		// step 5: do the find and replace
		SnpFindAndReplace instance;
		IFindChangeService::FindChangeResult findStatus = instance.Do_ReplaceGlyph(findGlyph, replaceGlyph, findScope, replaceMode);
		status = instance.ReportError(findStatus);

	} while (false);
	return status;
}

/* Run_FindObject
*/
ErrorCode _SnpRunnerFindAndReplace::Run_FindObject(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kCancel;
	do
	{
		// step 1: specify find object type
		IFindChangeOptions::ObjectType objType;
		status = Do_SpecifyObjectType(objType);
		if (status == kCancel)
			break;

        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kObjectSearchTypeCmdBoss));
        if (!cmd) return kFailure;
        InterfacePtr<IIntData> intData(cmd, IID_IINTDATA);
        if (!intData) return kFailure;
        intData->Set(objType);
        status =  CmdUtils::ProcessCommand( cmd ) ;
		if (status != kSuccess)
			break;

		// step 2: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindObject: fomdScope is 'kEmptyScope'!");
			break;
		}
		// set the find scope
		InterfacePtr<ICommand>  pCommand(CmdUtils::CreateCommand(kScopeCmdBoss));
		InterfacePtr<IIntData>  pIntData(pCommand, UseDefaultIID());
		pIntData->Set(findScope);
		InterfacePtr<IIntData> searchModeData(pCommand, IID_IFINDCHANGEMODEDATA);
		searchModeData->Set(IFindChangeOptions::kObjectSearch);

		status = CmdUtils::ProcessCommand(pCommand);
		if (status != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_FindObject: kScopeCmdBoss failed with error code %d", status);
			break;
		}

		// step 3: Specify object style
		UIDRef findObjectStyle;
		status = Do_SpecifyObjectStyle(iSnpRunnableContext, findObjectStyle, "Please choose an object style to find:");
		if (status == kCancel)
			break;
		
		// step 4. Specify FindAttrBossList
		const AttributeBossList* attributeBossList;
		InterfacePtr<IPMUnknown> target(::CreateObject(kObjectStylesTargetBoss,IID_IUNKNOWN));
		Utils<IObjectStylesUtils>()->GetTargetFromObjectStyle(findObjectStyle, target);
        InterfacePtr<IObjectAttributeList> objectAttributeList(target, IID_IGFXOBJECTATTRIBUTELIST);
        attributeBossList = objectAttributeList->GetBossList();
        int32 attrCount = attributeBossList->CountBosses();
        AttributeBossList findAttributeBossList = *attributeBossList;
 
		//Now hard code some attribue
		InterfacePtr<IGraphicAttrClassID> cornerEffectAttribute(Utils<IGraphicAttributeUtils>()->CreateCornerImplementationAttribute(kFancyCornerBoss));
		findAttributeBossList.ApplyAttribute(cornerEffectAttribute);

		// Set FindChangeOptions
		IFindChangeOptions::SearchMode searchMode = IFindChangeOptions::kObjectSearch;
		InterfacePtr<ICommand> formatCmd(CmdUtils::CreateCommand(kFindChangeFormatCmdBoss));
		if (formatCmd == nil)
			break;
		InterfacePtr<IIntData> modeData(formatCmd, IID_IFINDCHANGEMODEDATA);
		if (modeData)
			modeData->Set(searchMode);
		InterfacePtr<IFindChangeFormatCmdData> formatCmdData(formatCmd, IID_IFINDCHANGEFORMATCMDDATA);

		if (formatCmdData == nil)
			break;

		formatCmdData->SetTargetDB (findObjectStyle.GetDataBase());
		formatCmdData->ClearFindAttributeBossList(); 
		formatCmdData->ApplyFindAttributeBossList(&findAttributeBossList); 
		formatCmdData->SetObjectFindStyle(findObjectStyle.GetUID());

        status =  CmdUtils::ProcessCommand( formatCmd ) ;
		if (status != kSuccess)
			break;

		// Now perform search
		InterfacePtr<IFindChangeService> findChangeService ( (IFindChangeService*)::CreateObject(kFindChangeServiceBoss, IID_IFINDCHANGSERVICE));
		if (!findChangeService)
		{
			SNIPLOG("SnpFindAndReplace::Run_FindObject: failed to create find change service");
			break;
		}

		// the find change options should already been set at this point. 
        UIDRef foundObject;
        IFindChangeService::FindChangeResult findStatus = findChangeService->SearchObject(foundObject, kTrue /*!fInitialized*/);	//crashes if we do not initialize on 2nd pass
		if (fInitialized == kFalse && findStatus != IFindChangeService::kFailure && findStatus != IFindChangeService::kNotFound)
           fInitialized = kTrue;

		if (findStatus == IFindChangeService::kSuccess)
		{
			// we have completed a successful find at least once - requirement for replacing
			fIsFoundSelected[IFindChangeOptions::kObjectSearch] = kTrue;
		}
		SnpFindAndReplace instance;
		status = instance.ReportError(findStatus);

	} while (false);
	return status;
}

/* Run_FindObject
*/
ErrorCode _SnpRunnerFindAndReplace::Run_ReplaceObject(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kCancel;
	do
	{
		// step 1: specify find object type
		IFindChangeOptions::ObjectType objType;
		status = Do_SpecifyObjectType(objType);
		if (status == kCancel)
			break;

        InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kObjectSearchTypeCmdBoss));
        if (!cmd) return kFailure;
        InterfacePtr<IIntData> intData(cmd, IID_IINTDATA);
        if (!intData) return kFailure;
        intData->Set(objType);
        status =  CmdUtils::ProcessCommand( cmd ) ;
		if (status != kSuccess)
			break;

		// step 2: specify find scope
		IWalkerScopeFactoryUtils::WalkScopeType findScope = IWalkerScopeFactoryUtils::kEmptyScope;
		status = Do_SpecifyFindScope(findScope);
		if (status == kCancel)
			break;

		/* check to see that the find scope is valid */
		if (findScope == IWalkerScopeFactoryUtils::kEmptyScope)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceObject: fomdScope is 'kEmptyScope'!");
			break;
		}
		// set the find scope
		InterfacePtr<ICommand>  pCommand(CmdUtils::CreateCommand(kScopeCmdBoss));
		InterfacePtr<IIntData>  pIntData(pCommand, UseDefaultIID());
		pIntData->Set(findScope);
		InterfacePtr<IIntData> searchModeData(pCommand, IID_IFINDCHANGEMODEDATA);
		searchModeData->Set(IFindChangeOptions::kObjectSearch);

		status = CmdUtils::ProcessCommand(pCommand);
		if (status != kSuccess)
		{
			SNIPLOG("SnpFindAndReplace::Do_ReplaceObject: kScopeCmdBoss failed with error code %d", status);
			break;
		}

		// step 3: Specify object style
		UIDRef findObjectStyle;
		status = Do_SpecifyObjectStyle(iSnpRunnableContext, findObjectStyle, "Please choose an object style to find");
		if (status == kCancel)
			break;
		
		// step 4. Specify FindAttrBossList
		const AttributeBossList* attributeBossList;
		InterfacePtr<IPMUnknown> target(::CreateObject(kObjectStylesTargetBoss,IID_IUNKNOWN));
		Utils<IObjectStylesUtils>()->GetTargetFromObjectStyle(findObjectStyle, target);
        InterfacePtr<IObjectAttributeList> objectAttributeList(target, IID_IGFXOBJECTATTRIBUTELIST);
        attributeBossList = objectAttributeList->GetBossList();
        AttributeBossList findAttributeBossList = *attributeBossList;
 
		//Now hard code some attribue
		InterfacePtr<IGraphicAttrClassID> cornerEffectAttribute(Utils<IGraphicAttributeUtils>()->CreateCornerImplementationAttribute(kFancyCornerBoss));
		findAttributeBossList.ApplyAttribute(cornerEffectAttribute);

		// step 5: Specify change object style
		UIDRef changeObjectStyle;
		status = Do_SpecifyObjectStyle(iSnpRunnableContext, changeObjectStyle, "Please choose an object style for replacing:");
		if (status == kCancel)
			break;

		//Step 6: Specify change attributes
		InterfacePtr<IPMUnknown> changeTarget(::CreateObject(kObjectStylesTargetBoss,IID_IUNKNOWN));
		Utils<IObjectStylesUtils>()->GetTargetFromObjectStyle(changeObjectStyle, changeTarget);
        InterfacePtr<IObjectAttributeList> changeObjectAttributeList(changeTarget, IID_IGFXOBJECTATTRIBUTELIST);
		const AttributeBossList* attributeBossList2 = changeObjectAttributeList->GetBossList();
        AttributeBossList changeAttributeBossList = *attributeBossList2;

		InterfacePtr<IGraphicAttrClassID> changeCornerEffectAttribute(Utils<IGraphicAttributeUtils>()->CreateCornerImplementationAttribute(kBevelCornerBoss));
		changeAttributeBossList.ApplyAttribute(changeCornerEffectAttribute);

		// Set FindChangeOptions
		IFindChangeOptions::SearchMode searchMode = IFindChangeOptions::kObjectSearch;
		InterfacePtr<ICommand> formatCmd(CmdUtils::CreateCommand(kFindChangeFormatCmdBoss));
		if (formatCmd == nil)
			break;
		InterfacePtr<IIntData> modeData(formatCmd, IID_IFINDCHANGEMODEDATA);
		if (modeData)
			modeData->Set(searchMode);
		InterfacePtr<IFindChangeFormatCmdData> formatCmdData(formatCmd, IID_IFINDCHANGEFORMATCMDDATA);

		if (formatCmdData == nil)
			break;

		formatCmdData->SetTargetDB (findObjectStyle.GetDataBase());
		formatCmdData->ClearFindAttributeBossList(); 
		formatCmdData->ApplyFindAttributeBossList(&findAttributeBossList); 
		formatCmdData->SetObjectFindStyle(findObjectStyle.GetUID());
		formatCmdData->SetObjectChangeStyle(changeObjectStyle.GetUID());
		formatCmdData->ClearChangeAttributeBossList(); 
		formatCmdData->ApplyChangeAttributeBossList(&changeAttributeBossList); 

        status =  CmdUtils::ProcessCommand( formatCmd ) ;
		if (status != kSuccess)
			break;

		// Now perform replace
		InterfacePtr<IFindChangeService> findChangeService ( (IFindChangeService*)::CreateObject(kFindChangeServiceBoss, IID_IFINDCHANGSERVICE));
		if (!findChangeService)
		{
			SNIPLOG("SnpFindAndReplace::Run_ReplaceObject: failed to create find change service");
			break;
		}


		// the find change options should already been set at this point. 
		IFindChangeService::FindChangeResult replaceStatus;
        UIDRef itemRef;
        int32 foundCount;
		int32 fullyChangedCount;
		int32 partiallyChangedCount;

		replaceStatus = findChangeService->ReplaceAllObject(&foundCount,&fullyChangedCount,&partiallyChangedCount,kTrue);

		SnpFindAndReplace instance;
		status = instance.ReportError(replaceStatus);

	} while (false);
	return status;
}

/* Do_SpecifyFindString
	This corresponds to the "Find what:" setting on the Find/Replace text dialog in InDesign
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyFindString(PMString& findString)
{
	ErrorCode status = kCancel;
	findString = "";
	do
	{
		Utils<ISnipRunParameterUtils> parameterUtils;
		findString = parameterUtils->GetPMString("Specify text to find.", fFindString);
		if (!parameterUtils->WasDialogCancelled())
		{
			status = kSuccess;
			SNIPLOG("The text to find was set to \"%s\".", findString.GetPlatformString().c_str());
			fFindString = findString;
		}
		else
		{
			SNIPLOG("The text to find was not set.");
		}
	} while (false);
	return status;
}

/* Do_SpecifyReplaceString
	This corresponds to the "Change to:" setting on the Find/Replace text dialog in InDesign.
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyReplaceString(PMString& replaceString)
{
	ErrorCode status = kCancel;
	replaceString = "";
	do
	{
		Utils<ISnipRunParameterUtils> parameterUtils;
		replaceString = parameterUtils->GetPMString("Specify text to replace with.", fReplaceString); 
		if (!parameterUtils->WasDialogCancelled())
		{
			status = kSuccess;
			SNIPLOG("The text to replace with was set to \"%s\".", replaceString.GetPlatformString().c_str());
			fReplaceString = replaceString;
		}
		else
		{
			SNIPLOG("The text to replace was not set.");
		}
	} while (false);
	return status;
}

/* Do_SpecifyFindScope
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyFindScope(IWalkerScopeFactoryUtils::WalkScopeType& findScope)
{
	ErrorCode status = kCancel;
	findScope = IWalkerScopeFactoryUtils::kEmptyScope;
	do
	{
		K2Vector<PMString> scopeMenu;

		/* NOTE: Looking at the currently active scope gives us a 
			range of choices for our find and replace operation scope.
		*/
		IWalkerScopeFactoryUtils::WalkScopeType activeScopeType = 
			Utils<IWalkerScopeFactoryUtils>()->GetActiveSelectionScope();
		int32 defaultScope = 0;
		enum
		{
			kAllDocuments, kDocument, kStory, kToEndOfStory, kSelection
		};

		switch (activeScopeType)
		{
		case IWalkerScopeFactoryUtils::kEmptyScope: 
			{
				scopeMenu.push_back(PMString("[No Text]"));
				if (fFindScopeEnum > kAllDocuments) 
					defaultScope = kAllDocuments;
			}
			break;

		case IWalkerScopeFactoryUtils::kDocumentScope:
		case IWalkerScopeFactoryUtils::kAllDocumentScope:
			{
				scopeMenu.push_back(PMString("All Documents"));
				scopeMenu.push_back(PMString("Document"));
				if (fFindScopeEnum > kDocument) 
					defaultScope = kDocument;
			}
			break;

		case IWalkerScopeFactoryUtils::kStoryListScope:
		case IWalkerScopeFactoryUtils::kStoryScope:     
			{
				scopeMenu.push_back(PMString("All Documents"));
				scopeMenu.push_back(PMString("Document"));
				scopeMenu.push_back(PMString("Stories"));
				if (fFindScopeEnum > kStory) 
					defaultScope = kStory;
			}   
			break;
		case IWalkerScopeFactoryUtils::kToEndOfStoryScope: 
			{
				scopeMenu.push_back(PMString("All Documents"));
				scopeMenu.push_back(PMString("Document"));
				scopeMenu.push_back(PMString("Stories"));
				scopeMenu.push_back(PMString("To End of Story"));
				if (fFindScopeEnum > kToEndOfStory) 
					defaultScope = kToEndOfStory;
			}   
			break;

		case IWalkerScopeFactoryUtils::kSelectionScope: 
			{
				scopeMenu.push_back(PMString("All Documents"));
				scopeMenu.push_back(PMString("Document"));
				scopeMenu.push_back(PMString("Stories"));
				scopeMenu.push_back(PMString("To End of Story"));
				scopeMenu.push_back(PMString("Selection"));
				if (fFindScopeEnum > kSelection) 
					defaultScope = kSelection;
			}
			break;
		default:
			break;
		}

		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 chosenScope = parameterUtils->GetChoice("Where do you want to search?", scopeMenu, defaultScope);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		// cache this value
		fFindScopeEnum = chosenScope;

		PMString scopeName = "";
		switch (chosenScope)
		{
		case kAllDocuments:
			findScope = IWalkerScopeFactoryUtils::kAllDocumentScope;
			scopeName = "all documents";
			break;
		case kDocument:
			findScope = IWalkerScopeFactoryUtils::kDocumentScope;
			scopeName = "entire document";
			break;
		case kStory:
			findScope = IWalkerScopeFactoryUtils::kStoryScope;
			scopeName = "all stories";
			break;
		case kToEndOfStory:
			findScope = IWalkerScopeFactoryUtils::kToEndOfStoryScope;
			scopeName = "to the end of current story";
			break;
		case kSelection:
			findScope = IWalkerScopeFactoryUtils::kSelectionScope;
			scopeName = "current selection";
			break;
		default:
			break;
		}

		// mark this a success;
		if (!scopeName.empty())
		{
			status = kSuccess;
			SNIPLOG("The find scope was set to \"%s\"", scopeName.GetPlatformString().c_str());
		}
		else
		{
			SNIPLOG("The find scope was not set.");
		}

	} while (false);
	return status;
}


/* Do_SpecifyFindGlyph
	This corresponds to the "Find what:" setting on the Find/Replace glyph dialog in InDesign
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyFindGlyph(Text::GlyphID& findGlyph)
{
	ErrorCode status = kCancel;
	findGlyph = kInvalidGlyphID;
	do
	{
		//A more complete solution is to look for available fonts and determine the range of 
		//Glyphs. See SnpInsertGlyph.cpp
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 defaultGlyph = 36;
		findGlyph = (Text::GlyphID)parameterUtils->GetInt32("Specify glyph ID to find.",defaultGlyph);
		if (!parameterUtils->WasDialogCancelled())
		{
			status = kSuccess;
			SNIPLOG("The glyph to find was set to \"%d\".", findGlyph);
		}
		else
		{
			SNIPLOG("The glyph to find was not set.");
		}
	} while (false);
	return status;
}

/* Do_SpecifyReplaceGlyph
	This corresponds to the "Change to:" setting on the Find/Replace glyph dialog in InDesign
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyReplaceGlyph(Text::GlyphID& replaceGlyph)
{
	ErrorCode status = kCancel;
	replaceGlyph = kInvalidGlyphID;
	do
	{
		//A more complete solution is to look for available fonts and determine the range of 
		//Glyphs. See SnpInsertGlyph.cpp
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 defaultGlyph = 36;
		replaceGlyph = (Text::GlyphID)parameterUtils->GetInt32("Specify glyph ID to replace with.",defaultGlyph);
		if (!parameterUtils->WasDialogCancelled())
		{
			status = kSuccess;
			SNIPLOG("The glyph to replace was set to \"%d\".", replaceGlyph);
		}
		else
		{
			SNIPLOG("The glyph to replace was not set.");
		}
	} while (false);
	return status;
}

/* Do_SpecifyObjectType
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyObjectType(IFindChangeOptions::ObjectType& objType)
{
	ErrorCode status = kCancel;
	do
	{
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back(PMString("AllFrames"));
		choices.push_back(PMString("TextFrames"));
		choices.push_back(PMString("GraphicFrames"));
		choices.push_back(PMString("UnassignedFrames"));
	
		enum {en_AllFrames, en_TextFrames, en_GraphicFrames, en_UnassignedFrames };

		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice = parameterUtils->GetChoice("Which frame type?", choices);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

        switch (choice)
        {
            case en_AllFrames:
                objType = IFindChangeOptions::kAllFrames;
                break;
            case en_TextFrames:
                objType = IFindChangeOptions::kTextFrames;
                break;
            case en_GraphicFrames:
                objType = IFindChangeOptions::kGraphicFrames;
                break;
            case en_UnassignedFrames:
                objType = IFindChangeOptions::kUnassignedFrames;
                break;
 
		}
		status = kSuccess;

	} while (false);
	return status;
}

/* Do_SpecifyObjectStyle
*/
ErrorCode _SnpRunnerFindAndReplace::Do_SpecifyObjectStyle(ISnpRunnableContext* iSnpRunnableContext, UIDRef& objStyleUID, PMString reminder)
{
	ErrorCode status = kCancel;
	do
	{
        IWorkspace* ws = iSnpRunnableContext->GetActiveContext()->GetContextWorkspace();
        InterfacePtr<IStyleGroupManager> styleNameTable((IStyleGroupManager*)ws->QueryInterface(IID_IOBJECTSTYLEGROUPMANAGER) ) ;
        UIDList styleUIDList(::GetDataBase(styleNameTable));
        styleNameTable->GetRootHierarchy()->GetDescendents(&styleUIDList,IID_IOBJECTSTYLEINFO);

        int32 numOfStyles = styleUIDList.Length();

        K2Vector<PMString> styleList;
        for (int32 loop=0; loop<numOfStyles; loop++){
            InterfacePtr<IStyleGroupHierarchy> styleHier(styleUIDList.GetRef(loop),UseDefaultIID());
            styleList.push_back(styleHier->GetFullPath());
        }

		Utils<ISnipRunParameterUtils> parameterUtils;
        int32 choice = parameterUtils->GetChoice(reminder, styleList);
		if (parameterUtils->WasDialogCancelled())
		{
			break;
		}

		objStyleUID = styleUIDList.GetRef(choice);

		status = kSuccess;

	} while (false);
	return status;
}
/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerFindAndReplace instance_SnpRunnerFindAndReplace;
DEFINE_SNIPPET(_SnpRunnerFindAndReplace) 	

// End, SnpFindAndReplace.cpp

