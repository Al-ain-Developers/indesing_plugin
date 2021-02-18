//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeOptions.h $
//  
//  Owner: Wai Cheuk
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
#ifndef __IFindChangeOptions__
#define __IFindChangeOptions__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

#include "ITextWalker.h"
#include "WideString.h"
#include "TextWalkerServiceProviderID.h"
#include "IWalkerScopeFactoryUtils.h"
#include "CTextEnum.h"

class AttributeBossList;
class ITextAttrFont;
class ITextAttrUID;

// Note: Overset Text control user interface is removed from Find/Change panel.
// Its functionality always includes overset text.
// Wai 5/5/98

/**
	@ingroup text_find
*/
class IFindChangeOptions : public IPMUnknown
{
public:
	/**
	Standard enum to for use with GetDefaultIID() method.
	 */
	enum { kDefaultIID = IID_IFINDCHANGEOPTIONS };

	/**
	Enum for specifying Find/Change mode.
	 */
	enum 	SearchMode
	{
		/** Text Find/Change Mode */
		kTextSearch,
		/** Grep Find/Change Mode */
		kGrepSearch,
		/** Glyph Find/Change Mode */
		kGlyphSearch,
		/** Object Find/Change Mode */
		kObjectSearch,
		/** Transliterate Find/Change Mode */
		kTransliterateSearch,
		/** Color Find/Change Mode */
		kColorSearch
	};

	/**
	Enum for distinguishing between substituting text and changing
	 */
	enum 	ChangeMode
	{
		/** For Changing text */
		kChange,
		/** For Substituing text */
		kTransliterate
	};

	/**
	Enum for distinguishing character type in CJK
	 */
	enum 	CharacterType
	{
		/** Kanji */
		kKanji,
		/** Half width Katakana */
		kHalfWidthKatakana,
		/** Half width Roman */
		kHalfWidthRoman,
		/** Full width Hiragana */
		kFullWidthHiragana,
		/** Full width Katakana */
		kFullWidthKatakana,
		/** Full width Roman */
		kFullWidthRoman,
		/** None */
		kNone,
		kWesternArabicDigits,
		kArabicIndicDigits,
		kFarsiDigits
	} ;

	/**
	Enum for specifying the types of objects to search
	 */
	enum	ObjectType
	{
		/** All Frames */
		kAllFrames,
		/** Text Frames */
		kTextFrames,
		/** Graphic Frames */
		kGraphicFrames,
		/** Unassigned Frames */
		kUnassignedFrames
	};

	/**
	Enum for distinguishing between change conditions replacing applied conditions or adding to applied conditions.
	*/
	enum ChangeConditionsMode
	{
		/** For replacing applied conditions. */
		kChangeReplacesConditions,
		/** For adding to applied conditions. */
		kChangeAddsConditions
	};
	
	/**
	Enum for distinguishing between forward and backward search.
	*/
	enum SearchDirection
	{
		kForward,
		kBackward
	};

	/**
	Gets "Case Sensitive" find option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if case sensitive option is on and "kFalse" if it
	is off.
	@see IFindChangeOptions::SetCaseSensitive
	*/
	virtual bool16 GetCaseSensitive(SearchMode mode) const = 0;

	/**
	Sets "Case Sensitive" find option
	@param caseSensitive is Boolean Value specifying the value to be set
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetCaseSensitive
	 */
	virtual void SetCaseSensitive(bool16 caseSensitive,SearchMode mode) = 0;

	/**
	Gets the option that specifies whether the search is sensitive to katakana vs. hiragana character sets (Japanese)
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if kana sensitive option is on and "kFalse" if it
	is off.
	@see IFindChangeOptions::SetKanaSensitive
	 */
	virtual bool16 GetKanaSensitive(SearchMode mode) const = 0;

	/**
	Sets the option that specifies whether the search is sensitive to katakana vs. hiragana character sets (Japanese)
	@param kanaSensitive is Boolean value specifying the option to be set
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetKanaSensitive
	 */
	virtual void SetKanaSensitive(bool16 kanaSensitive,SearchMode mode) = 0;

	/**
	Japanese character sets have full and half-width options for hiragana, katakana, and Roman character sets
	This method lets us know whether find/change is width sensitive or not in the given mode
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if width sensitive option is on and "kFalse" if it
	is off.
	@see IFindChangeOptions::SetWidthSensitive
	 */
	virtual bool16 GetWidthSensitive(SearchMode mode) const = 0;

	/**
	Japanese character sets have full and half-width options for hiragana, katakana, and Roman character sets
	This method sets whether find/change should be width sensitive or not in the given mode
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetWidthSensitive
	 */
	virtual void SetWidthSensitive(bool16 widthSensitive,SearchMode mode) = 0;

	/**
	Gets the Find/Change mode
	@return IFindChangeOptions::SearchMode
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::SetSearchMode
	 */
	virtual IFindChangeOptions::SearchMode GetSearchMode() const = 0;

	/**
	Sets the Find/Change mode
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetSearchMode
	 */
	virtual void SetSearchMode(IFindChangeOptions::SearchMode mode) = 0;

	/**
	Gets the option that distinguishes Find/Change from Transliterate
	@return IFindChangeOptions::ChangeMode
	@see IFindChangeOptions::ChangeMode
	@see IFindChangeOptions::SetChangeMode
	 */
	virtual IFindChangeOptions::ChangeMode GetChangeMode() const = 0;

	/**
	Sets the option that distinguishes Find/Change from Transliterate
	@param changeMode is of type IFindChangeOptions::ChangeMode
	@see IFindChangeOptions::ChangeMode
	@see IFindChangeOptions::GetChangeMode
	 */
	virtual void SetChangeMode(IFindChangeOptions::ChangeMode changeMode) = 0;

	/**
	When transliterating, sets the options for the type being searched for and the
	character type to replace with
	@param charType is of type IFindChangeOptions::CharacterType
	@see IFindChangeOptions::CharacterType
	@see IFindChangeOptions::GetFindCharacterType
	 */
	virtual void SetFindCharacterType(IFindChangeOptions::CharacterType charType) = 0;

	/**
	When transliterating, gets the options for the type being searched for and the
	character type to replace with
	@return IFindChangeOptions::CharacterType
	@see IFindChangeOptions::CharacterType
	@see IFindChangeOptions::SetFindCharacterType
	 */
	virtual IFindChangeOptions::CharacterType GetFindCharacterType() const = 0;

	/**
	Gets "Include Locked Stories" find option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if include locked stories option is on and "kFalse" if it
	is off. This option is only for find i.e. we do not have option to change in locked stories
	@see IFindChangeOptions::SetIncludeLockedStoriesForFind
	*/
	virtual bool16 GetIncludeLockedStoriesForFind(SearchMode mode) const = 0;

	/**
	Sets "Include Locked Stories" find option
	@param includeLockedStories Boolean value for setting "Include Locked
	Stories" option. This option is only for find i.e. we do not have option to change in locked stories
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetIncludeLockedStoriesForFind
	*/
	virtual void SetIncludeLockedStoriesForFind(bool16 includeLockedStories,SearchMode mode) = 0;

	/**
	Gets "Include Locked Layers" find option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if include locked layers option is on and "kFalse" if it is
	off. This option is only for find i.e. we do not have option to change on locked layers.
	@see IFindChangeOptions::SetIncludeLockedLayersForFind
	*/
	virtual bool16 GetIncludeLockedLayersForFind(SearchMode mode) const = 0;

	/**
	Sets "Include Locked Layers" find option
	@param includeLockedLayers Boolean value for setting "Include Locked
	Layers" option. This option is only for find i.e. we do not have option to change on locked layers.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetIncludeLockedLayersForFind
	*/
	virtual void SetIncludeLockedLayersForFind(bool16 includeLockedLayers,SearchMode mode) = 0;

	/**
	Gets "Include Hidden Layers" option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if include hidden layers option is on and "kFalse" if it is
	off
	@see IFindChangeOptions::SetIncludeHiddenLayers
	*/
	virtual bool16 GetIncludeHiddenLayers(SearchMode mode) const = 0;

	/**
	Sets "Include Hidden Layers" option
	@param includeHiddenLayers Boolean value for setting "Include Hidden
	Layers" option.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetIncludeHiddenLayers
	*/
	virtual void SetIncludeHiddenLayers(bool16 includeHiddenLayers,SearchMode mode) = 0;

	/**
	Gets "Include Master Pages" option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if include master pages option is on and "kFalse" if it is
	off
	@see IFindChangeOptions::SetIncludeMasterPages
	*/
	virtual bool16 GetIncludeMasterPages(SearchMode mode) const = 0;

	/**
	Sets "Include Master Pages" option
	@param includeMasterPages Boolean value for setting "Include Master Pages"
	option.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetIncludeMasterPages
	*/
	virtual void SetIncludeMasterPages(bool16 includeMasterPages, SearchMode mode) = 0;

	/**
	Gets "Include Footnotes" option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if include footnotes option is on and "kFalse" if it is off
	@see IFindChangeOptions::SetIncludeFootnotes
	*/
	virtual bool16 GetIncludeFootnotes(SearchMode mode) const = 0;

	/**
	Sets "Include Footnotes" option
	@param includeFootnotes Boolean value for setting "Include Footnotes"
	option.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetIncludeFootnotes
	*/
	virtual void SetIncludeFootnotes(bool16 includeFootnotes,SearchMode mode) = 0;

	/**
	Gets "Search backwards" option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if search backwards option is on and "kFalse" if it is off
	@see IFindChangeOptions::SetSearchBackwards
	*/
	virtual bool16 GetSearchBackwards(SearchMode mode) const = 0;

	/**
	Sets "Search backwards" option
	@param searchBackwards Boolean value for setting "Search backwards"
	option.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetSearchBackwards
	*/
	virtual void SetSearchBackwards(bool16 searchBackwards,SearchMode mode) = 0;

	/**
	When transliterating, sets the options for the character type to replace with
	@param charType is of type IFindChangeOptions::CharacterType
	@see IFindChangeOptions::CharacterType
	@see IFindChangeOptions::GetReplaceCharacterType
	 */
	virtual void SetReplaceCharacterType(IFindChangeOptions::CharacterType charType) = 0;

	/**
	When transliterating, gets the options for the character type to replace with
	@return IFindChangeOptions::CharacterType
	@see IFindChangeOptions::CharacterType
	@see IFindChangeOptions::SetReplaceCharacterType
	 */
	virtual IFindChangeOptions::CharacterType GetReplaceCharacterType() const = 0;

	/**
	Gets "Entire Word" option
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return "kTrue" if entire word option is on and "kFalse" if it is off
	@see IFindChangeOptions::SetEntireWord
	 */
	virtual bool16 GetEntireWord(SearchMode mode) const = 0;

	/**
	Sets "Entire Word" option
	@param entireWord is a Boolean value specifying whether entire word option should be turned on or off
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetEntireWord
	 */
	virtual void SetEntireWord(bool16 entireWord,SearchMode mode) = 0;

	/**
	Gets the scope in which find/change option will be operating
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return IWalkerScopeFactoryUtils::WalkScopeType
	@see IWalkerScopeFactoryUtils::WalkScopeType
	@see IFindChangeOptions::SetFindChangeScope
	 */
	virtual IWalkerScopeFactoryUtils::WalkScopeType GetFindChangeScope(SearchMode mode) const = 0;

	/**
	Sets the scope in which find/change option will be operating
	@param findChangeScope is of type IWalkerScopeFactoryUtils::WalkScopeType
	@see IWalkerScopeFactoryUtils::WalkScopeType
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetFindChangeScope
	 */
	virtual void SetFindChangeScope(IWalkerScopeFactoryUtils::WalkScopeType findChangeScope,SearchMode mode) = 0;

	/**
	Gets the string being searched for
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return the string being searched for
	@see IFindChangeOptions::SetFindString
	 */
	virtual const WideString& GetFindString(SearchMode mode) const = 0;

	/**
	Sets the string to search for
	@param findString is of type WideString
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetFindString
	 */
	virtual void SetFindString(const WideString& findString,SearchMode mode) = 0;

	/**
	Gets the string that will replace the found string
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return the string that will replace the found string
	@see IFindChangeOptions::SetReplaceString
	 */
	virtual const WideString& GetReplaceString(SearchMode mode) const = 0;

	/**
	Sets the string that will replace the found string
	@param replaeString is of type WideString
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetReplaceString
	 */
	virtual void SetReplaceString(const WideString& replaceString,SearchMode mode) = 0;

	/**
	Gets the attributes being searched for
	@param targetDB is a pointer to IDataBase specifying the database of the attributes
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is a pointer to AttributeBossList
	@see IFindChangeOptions::ApplyToFindAttributeBossList
	 */
	virtual const AttributeBossList* GetFindAttributeBossList( IDataBase *targetDB ,SearchMode mode) const = 0;

	/**
	Sets the attributes to search for
	@param findList is a pointer to AttributeBossList
	@param targetDB is a pointer to IDataBase
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetFindAttributeBossList
	 */
	virtual void ApplyToFindAttributeBossList(const AttributeBossList* findList, IDataBase *targetDB,SearchMode mode) = 0;

	/**
	For Removing a specific attribute from the find attribute list
	@param removeAttribute is of type ClassID specifying the classid of the attribute that needs to be removed from the attribute list
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void RemoveFindAttribute(ClassID removeAttribute,SearchMode mode) = 0;

	/**
	For resetting the find attributes
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearFindAttributeBossList(SearchMode mode) = 0;

	/**
	Gets the attributes that will be applied to found text/object
	@param targetDB is a pointer to attributes database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@param allowCreation is a boolean value indicating whether the attributes need to be created or not if the attributes do not exist
	@return value is a pointer to AttributeBossList
	@see IFindChangeOptions::ApplyToChangeAttributeBossList
	 */
	virtual const AttributeBossList* GetChangeAttributeBossList(IDataBase *targetDB, SearchMode mode, bool16 allowCreation = kTrue) const = 0;

	/**
	Sets the attributes that will be applied to found text/object
	@param findList is a poiner to AttributeBossList
	@param targetDB is a pointer to IDataBase
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetChangeAttributeBossList
	 */
	virtual void ApplyToChangeAttributeBossList(const AttributeBossList* findList, IDataBase *targetDB, SearchMode mode) = 0;

	/**
	Removes the specified attribute from the list of attributes that will be applied to found text/object
	@param removeAttribute is of type ClassID specifying the class id of the attribute to be removed
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void RemoveChangeAttribute(ClassID removeAttribute,SearchMode mode) = 0;

	/**
	Clears the attributes that will be applied to found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeAttributeBossList(SearchMode mode) = 0;

	/**
	Clears the character style that will be found
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearFindCharStyle(SearchMode mode) = 0;

	/**
	Clears the paragraph style that will be found
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearFindParaStyle(SearchMode mode) = 0;

	/**
	Clears the object style that will be found
	 */
	virtual void ClearObjectFindStyle() = 0;

	/**
	Clears the character style that will be applied to found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeCharStyle(SearchMode mode) = 0;

	/**
	Clears the paragraph style that will be applied to found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeParaStyle(SearchMode mode) = 0;

	/**
	Clears the object style that will be applied to found object
	*/
	virtual void ClearObjectChangeStyle() = 0;

	/**
	Sets the character style to be found
	@param s is the UID of the character style
	@param targetDB is the pointer to style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetFindCharStyle
	 */
	virtual void SetFindCharStyle(const UID& s, IDataBase *targetDB, SearchMode mode) = 0;

	/**
	Sets the paragraph style to be found
	@param s is the UID of the paragraph style
	@param targetDB is the pointer to style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetFindParaStyle
	 */
	virtual void SetFindParaStyle(const UID& s, IDataBase *targetDB, SearchMode mode) = 0;

	/**
	Sets the object style to be found
	@param s is the UID of the object style
	@param targetDB is the pointer to style's database
	@see IFindChangeOptions::GetObjectFindStyle
	 */
	virtual void SetObjectFindStyle(const UID& s, IDataBase *targetDB) = 0;

	/**
	Sets the character style that will be applied to found text
	@param s is the UID of the character style
	@param targetDB is the pointer to style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetChangeCharStyle
	 */
	virtual void SetChangeCharStyle(const UID& s, IDataBase *targetDB, SearchMode mode) = 0;

	/**
	Sets the paragraph style that will be applied to found text
	@param s is the UID of the paragraph style
	@param targetDB is the pointer to style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetChangeParaStyle
	 */
	virtual void SetChangeParaStyle(const UID& s, IDataBase *targetDB, SearchMode mode) = 0;

	/**
	Sets the obect style that will be applied to found obect
	@param s is the UID of the object style
	@param targetDB is the pointer to style's database
	@see IFindChangeOptions::GetObjectChangeStyle
	 */
	virtual void SetObjectChangeStyle(const UID& s, IDataBase *targetDB) = 0;

	/**
	Gets the character style that will be found
	@param targetDB is a pointer to character style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is character style's UID
	@see IFindChangeOptions::SetFindCharStyle
	 */
	virtual const UID& GetFindCharStyle( IDataBase *targetDB, SearchMode mode) const = 0;

	/**
	Get the paragraph style that will be found
	@param targetDB is a pointer to paragraph style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is paragraph style's UID
	@see IFindChangeOptions::SetFindParaStyle
	 */
	virtual const UID& GetFindParaStyle( IDataBase *targetDB, SearchMode mode) const = 0;

	/**
	Get the object style that will be found
	@param targetDB is a pointer to object style's database
	@return value is find style's UID
	@see IFindChangeOptions::SetObjectFindStyle
	 */
	virtual const UID& GetObjectFindStyle( IDataBase *targetDB) const = 0;

	/**
	Get the character style that will be applied to found text
	@param targetDB is a pointer to character style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is character style's UID
	@see IFindChangeOptions::SetChangeCharStyle
	 */
	virtual const UID& GetChangeCharStyle( IDataBase *targetDB, SearchMode mode, bool16 allowCreation = kTrue) const = 0;

	/**
	Get the paragraph style that will be applied to found text
	@param targetDB is a pointer to paragraph style's database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is paragraph style's UID
	@see IFindChangeOptions::SetChangeParaStyle
	 */
	virtual const UID& GetChangeParaStyle( IDataBase *targetDB, SearchMode mode, bool16 allowCreation = kTrue) const = 0;

	/**
	Get the object style that will be applied to found object
	@param targetDB is a pointer to object style's database
	@param allowCreation pass kTrue if you want to create the style if it doesn't exist in targetDB
	@return value is object style's UID
	@see IFindChangeOptions::SetObjectChangeStyle
	 */
	virtual const UID& GetObjectChangeStyle( IDataBase *targetDB, bool16 allowCreation = kFalse) const = 0;

	/** The FindChangeOptions interface is in a unique position to know whether there is
	* adequate information defined on it to allow searching for "something".  Without
	* this method, calls throughout the code were asking the interface whether the length
	* of the search string was greater than zero OR there was a special character or paragraph
	* format to search for in various ways such as
	* if (::SearchFormatExist() || !FindEditBoxEmpty())
	* This is worse with the addition of transliterate, where if in transliterate mode, the
	* search string is irrelevant.
	* Although this interface isn't responsible for performing a find, it's now a smart
	* secretary, able to pack the boss's briefcase with all the necessary papers before the
	* big meeting.
	@param targetDB is a pointer to find/change options database
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	*/
	virtual bool16 IsThereSomethingToFind(IDataBase *targetDB, SearchMode mode) const = 0 ;

	/**
	Gets the database of attributes
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is a pointer to database interface
	 */
	virtual IDataBase *					GetUIDAttrDB() const = 0;

	/**
	Initializes various options for a search mode
	 */
	virtual void Init(						bool16	caseSensitive,
											bool16	entireWord,
											bool16	kanaSensitive,
											bool16	widthSensitive,
											SearchMode	searchMode,
											ChangeMode	changeMode,
											CharacterType findCharacterType,
											CharacterType replaceCharacterType,
											IWalkerScopeFactoryUtils::WalkScopeType	findChangeScope,
											const WideString 				&findString,
											const WideString 				&replaceString,
											const AttributeBossList *findAttributeBossList,
											const AttributeBossList	*changeAttributeBossList,
											IDataBase	*targetDB,
											const UID	&findCharStyle,
											const UID	&findParaStyle,
											const UID	&changeCharStyle,
											const UID	&changeParaStyle,
											bool16 grepFlag,
											bool16 includeMasterPages,
											bool16 includeLockedLayersForFind,
											bool16 includeLockedStoriesForFind,
											bool16 includeHiddenLayers,
											bool16 includeFootnotes,
											bool16 searchBackwards,
											Text::GlyphID findGlyphID,
											Text::GlyphID replaceGlyphID) = 0;

	/**
	Resets the find/change options
	 */
	virtual void Clear() = 0;

	/** Grep flag */
	/**
	Gets whether grep search is being carried out or not.
	@return value is kTrue if Grep is active otherwise it is kFalse
	@see IFindChangeOptions::GetGrepFlag
	 */
	virtual bool16 GetGrepFlag() const = 0;

	/**
	Sets the search mode to grep
	@param grepFlag is a boolean specifying the value
	@see IFindChangeOptions::SetGrepFlag
	 */
	virtual void SetGrepFlag(bool16 grepFlag) = 0;

	/**
	Sets the XML tag that will be applied to found text
	@param tagName is of type PMString specifying the tag
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetChangeXMLTag
	 */
	virtual void SetChangeXMLTag(const PMString& tagName,SearchMode mode) = 0;

	/**
	Gets the XML Tag that will be applied to found text
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return value is a PMString
	@see IFindChangeOptions::SetChangeXMLTag
	 */
	virtual const PMString& GetChangeXMLTag(SearchMode mode) const = 0;

	/**
	Resets the XML tag that will be applied to found text to ""
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeXMLTag(SearchMode mode) = 0;

	/** Glyph ID, type, font, style (find and replace) */
	/** Find */
	/**
	Gets the glyph id to be found
	@return value is of type Text::GlyphID
	@see IFindChangeOptions::SetFindGlyphID
	 */
	virtual const Text::GlyphID GetFindGlyphID() const = 0;

	/**
	Sets the glyph id to be found
	@param findGlyphID is of type Text::GlyphID
	@see IFindChangeOptions::GetFindGlyphID
	 */
	virtual void SetFindGlyphID(const Text::GlyphID findGlyphID) = 0;

	/**
	Sets the ROS(Registry Ordered Supplement) font group of the glyph to be searched.
	@param registry is of type PMString
	@param ordering is of type PMString
	 */
	virtual void SetFindROSFontGroup(const PMString& registry,const PMString& ordering) = 0;

	/**
	Gets the ROS(Registry Ordered Supplement) font group of the glyph to be searched.
	@return registry is of type PMString
	@return ordering is of type PMString
	*/
	virtual void GetFindROSFontGroup(PMString& registry,PMString& ordering) const = 0;

	/**
	Set whether the glyph search is for a specific font or a ROS group.
	@param bUseROSFontGroup is of type bool16
	*/
	virtual void SetUseFindROSFontGroup(const bool16 bUseROSFontGroup) = 0;

	/**
	Get whether the glyph search is for a specific font or a ROS group.
	@return value if of type bool16
	*/
	virtual const bool16 GetUseFindROSFontGroup() const = 0;

	/** Replace */
	/**
	Gets the glyph id that will be placed in place of found glyph
	@return is of type Text::GlyphID
	@see IFindChangeOptions::SetReplaceGlyphID
	 */
	virtual const Text::GlyphID GetReplaceGlyphID() const = 0;

	/**
	Sets the glyph id that will be placed in place of found glyph
	@param replaceGlyphID is of type Text::GlyphID
	@see IFindChangeOptions::GetReplaceGlyphID
	 */
	virtual void SetReplaceGlyphID(const Text::GlyphID replaceGlyphID) = 0;

	/**
	Sets the ROS(Registry Ordered Supplement) font group of the glyph to be searched.
	@param registry is of type PMString
	@param ordering is of type PMString
	 */
	virtual void SetReplaceROSFontGroup(const PMString& registry,const PMString& ordering) = 0;

	/**
	Gets the ROS(Registry Ordered Supplement) font group of the glyph to be searched.
	@return registry is of type PMString
	@return ordering is of type PMString
	*/
	virtual void GetReplaceROSFontGroup(PMString& registry,PMString& ordering) const = 0;

	/**
	Set whether the glyph search is for a specific font or a ROS group.
	@param bUseROSFontGroup is of type bool16
	*/
	virtual void SetUseReplaceROSFontGroup(const bool16 bUseROSFontGroup) = 0;

	/**
	Get whether the glyph search is for a specific font or a ROS group.
	@return value if of type bool16
	*/
	virtual const bool16 GetUseReplaceROSFontGroup() const = 0;

	/**
	Sets whether object search should find all frames/text frames/graphic frames/unassigned frames.
	@param objType is of type IFindChangeOptions::ObjectType
	@see IFindChangeOptions::ObjectType
	@see IFindChangeOptions::GetObjectSearchType
	 */
	virtual void SetObjectSearchType(const ObjectType objType)	= 0;

	/**
	Gets whether object search should find all frames/text frames/graphic frames/unassigned frames.
	@return is of type IFindChangeOptions::ObjectType
	@see IFindChangeOptions::ObjectType
	@see IFindChangeOptions::SetObjectSearchType
	 */
	virtual const ObjectType GetObjectSearchType() const = 0;

	/**
	Sets the change conditions mode that will be applied to found text
	@param chgConditionsMode is of type IFindChangeOptions::ChangeConditionsMode  specifying the mode for change conditions
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeOptions::SearchMode
	@see IFindChangeOptions::GetChangeConditionsMode
	 */
	virtual void SetChangeConditionsMode(ChangeConditionsMode chgConditionsMode, SearchMode mode) = 0;

	/**
	Gets the change conditions mode that will be applied to found text
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeOptions::SetChangeConditionsMode
	 */
	virtual IFindChangeOptions::ChangeConditionsMode GetChangeConditionsMode(SearchMode mode) const = 0;

	/**
	Resets the change conditions mode that will be applied to found text to IFindChangeOptions::kChangeReplacesConditions.
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeConditionsMode(SearchMode mode) = 0;
	
	/*
	Internal use. Do not call.
	This is called by the Find-Change startup service to initialize database of attributes.
	*/
	virtual void InitializeDB() = 0;

};

#endif
