//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISpellingPrefs.h $
//  
//  Owner: hhorton
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
#ifndef _H_ISpellingPrefs
#define _H_ISpellingPrefs

#include "IPMUnknown.h"
#include "SpellingServiceID.h"

/** This interface is gets and sets the preferences used by the dynamic spell checking system.

	@see kWorkspaceBoss
	@see kSpellingPrefsCmdBoss
	@see IUIColorUtils
*/
class ISpellingPrefs : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPELLINGPREFS };

	/**	GetDynamicSpellCheck
		@return kTrue if dynamic spell checking is on; kFalse if it is off
	*/
	virtual bool16 	GetDynamicSpellCheck() const = 0;
	/**	SetDynamicSpellcheck
		@param dynamicSpellcheck: kTrue to turn on dynamic spell checking; kFalse to turn it off
	*/
	virtual void 	SetDynamicSpellCheck(bool16 dynamicSpellCheck) = 0;

	/**
	 GetDynamicSpellMisspelledWordColorIndex
	 Gets the index of the UI color to be used to indicate misspelled words.
	 This color index references the document's UI color list (which resides in the document's workspace).
	 
	 @return The index of the color to be used
	 */
	virtual int32 	GetDynamicSpellMisspelledWordColorIndex() const = 0;
	/**
	 SetDynamicSpellMisspelledWordColorIndex
	 Sets the index of the UI color to be used to indicate misspelled words.
	 
	 @param index: index of color in the document's UI color list
	 */
	virtual void 	SetDynamicSpellMisspelledWordColorIndex(int32 index) = 0;

	/**
	 GetDynamicSpellRepeatedWordColorIndex
	 Gets the index of the UI color to be used to indicate repeated words.
	 This color index references the document's UI color list (which resides in the document's workspace).
	 
	 @return The index of the color to be used
	 */
	virtual int32 	GetDynamicSpellRepeatedWordColorIndex() const = 0;
	/**
	 SetDynamicSpellRepeatedWordColorIndex
	 Sets the index of the UI color to be used to indicate repeated words.
	 
	 @param index: index of color in the document's UI color list
	 */
	virtual void 	SetDynamicSpellRepeatedWordColorIndex(int32 index) = 0;

	/**
	 GetDynamicSpellUncapitalizedWordColorIndex
	 Gets the index of the UI color to be used to indicate uncapitalized words.
	 This color index references the document's UI color list (which resides in the document's workspace).
	 
	 @return The index of the color to be used
	 */
	virtual int32 	GetDynamicSpellUncapitalizedWordColorIndex() const = 0;
	/**
	 SetDynamicSpellUncapitalizedWordColorIndex
	 Sets the index of the UI color to be used to indicate uncapitalized words.
	 
	 @param index: index of color in the document's UI color list
	 */
	virtual void 	SetDynamicSpellUncapitalizedWordColorIndex(int32 index) = 0;

	/**
	 GetDynamicSpellUncapitalizedSentenceColorIndex
	 Gets the index of the UI color to be used to indicate uncapitalized sentences.
	 This color index references the document's UI color list (which resides in the document's workspace).
	 
	 @return The index of the color to be used
	 */
	virtual int32 	GetDynamicSpellUncapitalizedSentenceColorIndex() const = 0;
	/**
	 SetDynamicSpellUncapitalizedSentenceColorIndex
	 Sets the index of the UI color to be used to indicate uncapitalized sentences.
	 
	 @param index: index of color in the document's UI color list
	 */
	virtual void 	SetDynamicSpellUncapitalizedSentenceColorIndex(int32 index) = 0;

	/**	GetCheckMisspelledWords
		@return kTrue if dynamic spell checking is checking for misspelled words; kFalse if it is not
	*/
	virtual bool16 	GetCheckMisspelledWords() const = 0;
	/**	SetCheckMisspelledWords
		@param checkMisspelledWords: kTrue to turn on dynamic checking for misspelled words; kFalse to turn it off
	*/
	virtual void 	SetCheckMisspelledWords(bool16 checkMisspelledWords) = 0;

	/**	GetCheckRepeatedWords
		@return kTrue if dynamic spell checking is checking for repeated words; kFalse if it is not
	*/
	virtual bool16 	GetCheckRepeatedWords() const = 0;
	/**	SetCheckRepeatedWords
		@param checkRepeatedWords: kTrue to turn on dynamic checking for repeated words; kFalse to turn it off
	*/
	virtual void 	SetCheckRepeatedWords(bool16 checkRepeatedWords) = 0;

	/**	GetCheckCapitalizeWords
		@return kTrue if dynamic spell checking is checking for uncapitalized words; kFalse if it is not
	*/
	virtual bool16 	GetCheckCapitalizeWords() const = 0;
	/**	SetCheckCapitalizeWords
		@param checkCapitalizeWords: kTrue to turn on dynamic checking for uncapitalized words; kFalse to turn it off
	*/
	virtual void 	SetCheckCapitalizeWords(bool16 checkCapitalizeWords) = 0;

	/**	GetCheckCapitalizeSentences
		@return kTrue if dynamic spell checking is checking for uncapitalized sentences; kFalse if it is not
	*/
	virtual bool16 	GetCheckCapitalizeSentences() const = 0;
	/**	SetCheckCapitalizeSentences
		@param checkCapitalizeSentences: kTrue to turn on dynamic checking for uncapitalized sentences; kFalse to turn it off
	*/
	virtual void 	SetCheckCapitalizeSentences(bool16 checkCapitalizeSentences) = 0;
	
	/**
		Set: Sets all of the spelling preferences in one call.
	
		@param	IN dsc - kTrue == turn on dynamic spell checking; kFalse == turn off dynamic spell checking
		@param	IN mwColorIndex - color used to mark misspelled words when dynamic spell checking is on
		@param	IN rwColorIndex - color used to mark repeated words when dynamic spell checking is on
		@param	IN uwColorIndex - color used to mark uncapitalized words when dynamic spell checking is on
		@param	IN usColorIndex - color used to mark uncapitalized sentences when dynamic spell checking is on
		@param	IN cmw  - kTrue == check for misspelled words; kFalse == don't
		@param	IN crw - kTrue == check for repeated words; kFalse == don't
		@param	IN ccw - kTrue == check for mis-capitalized words; kFalse == don't
		@param	IN ccs - kTrue == check for mis-capitalized sentences; kFalse == don't
	*/
	virtual void	Set(bool16 dsc, int32 mwColorIndex, int32 rwColorIndex, int32 uwColorIndex, int32 usColorIndex, bool16 cmw, bool16 crw, bool16 ccw, bool16 ccs) = 0;
};

#endif
