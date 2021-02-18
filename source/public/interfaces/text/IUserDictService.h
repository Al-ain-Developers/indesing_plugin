//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IUserDictService.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IUserDictService__
#define __IUserDictService__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "KeyValuePair.h"
#include "LinguisticID.h"
//----------------------------------------------------------------------------------------
// Interface IUserDictService
//----------------------------------------------------------------------------------------
class WideString;
class IHyphenatedWord;
class UserDictWordList;

// key: index in word, value: kNoHyphenPoint to kHardHyphenPoint (see LinguisticID.h).
typedef K2Vector<KeyValuePair<int32, int32> > HyphenPoints;

class IUserDict : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_IUSERDICT};
	
	virtual void			SetFilePathName(const PMString& filePath) = 0;
	virtual const PMString&	GetFilePathName(void) const = 0;

	virtual void			SetDataFile(void* dataFile) = 0;
	virtual void*			GetDataFile(void) const = 0;

	virtual	void			Flush(void) = 0;

	/** 
		Get name of user dictionary to display to user.

		@return PMString	user dictionary name 
	*/
	virtual PMString		GetDisplayName() = 0;
};

/** 
	@ingroup text_dict
*/
class IUserDictService : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_IUSERDICTSERVICE};

	enum 	 WordType{ kIsAWord, kNotAWord };
	enum 	 UserDictType{ kNone, kIsDict, kNotDict };

	/** 
		Adds words to user dictionary.

		If words are in NotUserDict(see QueryNotUserDict) then the add also removes word from NotUserDict.
		If userDict is the same as QueryNotUserDict then words are added to NotUserDict and removed from main user dict.

		@param userDict			user dictionary to add to
		@param constWordList	words to add
		@param caseSensitive	if kFalse words to add are lower case which service providers should interperate
								as "case insensitive"
		@param addToNotList		if kTrue add words to not list. Only works for the Main and memory user dictionaries.

		@return bool16			kTrue if words were added. 
	*/
	virtual bool16			AddToUserDict(IUserDict* userDict, const UserDictWordList &constWordList, bool16 caseSensitive, bool16 addToNotList = kFalse) = 0;

	/** 
		Adds word to user dictionary.

		If word was in NotUserDict(see QueryNotUserDict) then the add also removes word from NotUserDict.
		If userDict is the same as QueryNotUserDict then word is added to NotUserDict and removed from main user dict.

		@param userDict			user dictionary to add to
		@param rWord			word to add
		@param pPoints			hyphen points to give word
		@param caseSensitive	if kFalse word is added as lower case which service providers should interperate
								as "case insensitive"

		@return bool16			kTrue if word was added. 
	*/
	virtual	bool16		AddToUserDict( IUserDict* userDict, const WideString &rWord, const HyphenPoints *pPoints = nil, bool16 caseSensitive = kFalse  ) = 0;

	/** 
		Removes word from user dictionary.

		@param userDict			user dictionary to remvoe from
		@param rWord			word to remove

		@return bool16			kTrue if word was removed. 
	*/
	virtual	bool16		RemoveFromUserDict( IUserDict* userDict, const WideString &rWord ) = 0;

	/** 
		Clears word from user dictionary.

		@param userDict			user dictionary to clear from
		@return bool16			kTrue if words were removed. 
	*/
	virtual	bool16		ClearUserDict(IUserDict* userDict) = 0;

	/** 
		Checks user dictionary for word.

		@param userDict			user dictionary to check. nil checks main user dictionary
		@param rWord			word to look for
		@param pCorrectedWord	[OUT] same as rWord unless word was added with a correction.
								This string is empty when kNotDict is returned.

		@return UserDictType	if and how found. kNone if not in user dictionary. kIsDict if in user dictionary as a word.
								kNotDict if in user dictionary as not a word. 
	*/
	virtual	UserDictType	GetCorrectedWord( IUserDict* userDict, const WideString &rWord, WideString *pCorrectedWord ) = 0;
						
	/**
		UNSUPPORTED
	*/
	virtual	bool16		GetHyphenatedWord( IUserDict* userDict, const WideString &rWord, WideString *pHyphenatedWord ) = 0;

	//--------- SEARCH PATH ROUTINES-----------------

	/** 
		Adds user dictionary to dictionaries list.

		@param userDict			user dictionary to be added. 
		@param index			index in the dictionaries list where user dictionary will be inserted. -1 if add to the end of the list 
		@param addToVendorList	kTrue if the user dictionary should be added to IVendorList. kFalse ONLY FOR USE INSIDE IUserDictService
								implementation. Calling code should always use kTrue.
		@param initializing		kTrue if in initializing code. kTrue ONLY FOR USE INSIDE IUserDictService
								implementation. Calling code should always use kFalse.

		@return bool16	kTrue if the user dictionary was added successfully.
	*/
	virtual bool16		AddUserDictToSearchPath(IUserDict* userDict, int32 index, bool16 addToVendorList = kTrue, bool16 initializing = kFalse) = 0;

	/** 
		Move user dictionary in dictionaries list.

		@param oldIndex			index of user dictionary to be moved. 
		@param newIndex			new location of user dictionary. -1 if move to the end of the list 

		@return bool16	kTrue if the user dictionary was moved successfully.
	*/
	virtual bool16		MoveUserDictInSearchPath(int32 oldIndex, int32 newIndex) = 0;

	/** 
		Removes user dictionary from dictionaries list.

		@param userDict			user dictionary to be removed. 

		@return bool16	kTrue if the user dictionary was removed successfully.
	*/
	virtual bool16		RemoveUserDictFromSearchPath(IUserDict* userDict) = 0;

	/** 
		Replaces the specified user dictionary in dictionaries list with supplied new user dictionary.

		@param originalUserDict	user dictionary to be replaced. 
		@param newUserDict		new user dictionary to be added.
		
		@return bool16	kTrue if the original user dictionary was replaced by new one successfully.
	*/
	virtual bool16		ReplaceUserDictInSearchPath(IUserDict* originalUserDict, IUserDict* newUserDict) = 0;
	
	/** 
		Queries all user dictionaries in dictionaries list.

		This is not really a Query. It should be named Get. It
		does not add ref the IUserDicts in the list so you should
		not call release.

		@param userDictList	[OUT] list of all user dictionaries. 
		@param bOpenFiles	kTrue if need to open data files.
		
		@return int32	count of user dictionaries in the returned list.
	*/
	virtual int32		QueryAllUserDictsInSearchPath(K2Vector<IUserDict*>& userDictList, bool16 bOpenFiles) = 0;

	/** 
		Removes all user dictionaries in dictionaries list.

		@return int32	count of user dictionaries removed.
	*/
	virtual int32		RemoveAllUserDictsFromSearchPath(void) = 0;


	//--------- MISC ROUTINES-----------------

	/** 
		returns the pointer to NotUserDict.

		@return IUserDict* pointer to NotUserDict.
	*/
	virtual IUserDict* 	QueryNotUserDict(void) = 0;

	/** 
		Return main user dictionary.

		@return IUserDict*		main user dictionary 
	*/
	virtual IUserDict* 	QueryMainUserDict(void) = 0;

	/**
		UNSUPPORTED
	*/
	virtual bool16	 	SetMainUserDict(IUserDict* userDict) = 0;

    /** 
        CreateType 

        @see CreateNewUserDict 
    */ 
	enum CreateType {
			/** Do not create a file. 
			*/ 
			kDoNotCreate,

			/** Create file only if no file was found.
			*/ 
			kCreateIfNotFound,

			/** Create file even if file already exists. This replace the existing file. 
			*/ 
			kAlwaysCreate,

			/** Create a memory only dictionary. No file is created.

				Memory dictionaries are used for word lists like Ignored words and
				document dictionaries. They are added to the list of dictionaries that are 
				checked with this call. No other call is needed. To remove and delete the
				dictionary call RemoveUserDictFromSearchPath. If RemoveUserDictFromSearchPath
				is not called the dictionary we be release and memory deleted in this destructor.

			*/ 
			kCreateMemoryOnly
	};

	/** 
		Creates a new user dictionary. Caller is responsible for IUserDict.
		

		@param filePathName	File path of the user dictionary. Parameter is ignored if kCreateMemoryOnly.
		@param createFlags	0 = do not create, 1 = create if not found, 2 = always create
							3 = create memory only dictionary. See CreateType.

		@return	IUserDict* pointer to the new user dictionary.
	*/
	virtual IUserDict*	CreateNewUserDict(const PMString& filePathName, int16 createFlags) = 0;

	/** 
		Migrates a user dictionary in an old format.
		

		@param existingDictFile	File to convert to new format
		@param newDictFile	File to create in new format. Can be an existing file or the same as existingDictFile
			in the case of an existing file _temp is added to the name as a temp file and the temp file is deleted
			after if _temp cannot be created MigrateUserDict fails.

		@return	bool16 true if file was migrated
	*/
	virtual bool16			MigrateUserDict(const IDFile& existingDictFile, const IDFile& newDictFile) = 0;

	/** 
		Creates a user dict object for each path saved in the vendor data.

		@return bool16 kTrue if successfully created user dict object for each path.
	*/
	virtual bool16		InitializePaths(void) = 0;

	/** 
		Checks if the user dictionary is read only.

		@param userDict	user dictionary to check for.
		
		@return bool16 kTrue if the user dictionary is read only, kFalse otherwise.
	*/
	virtual	bool16		IsReadOnly(IUserDict* userDict) = 0;

	/** 
		Flushes data files.
		
		@return bool16 kTrue if succeeded.
	*/
	virtual	bool16		Flush() = 0;

	/** 
		Flushes user dictionary list.
	*/
	virtual	void		FlushUserDicts(void) = 0;

	/** 
		Returns default data file path name.

		@return PMString& default data file path string.
	*/
	virtual	const PMString&	GetDefaultFilePathName(void) const = 0;

	/**
		UNSUPPORTED
	*/
	virtual	const PMString&	GetNotFilePathName(void) const = 0;


	/** 
		Removes word from main dictionary.

		This really adds the word to the NotUserDict (see QueryNotUserDict). It also removes the word from
		the main user dictionary if it was in there.

		@param rWord			word to remove

		@return bool16			kTrue if word was removed. 
	*/
	virtual	bool16		RemoveFromMainDict( const WideString &rWord ) = 0;

	/** 
		Undo remove word from main dictionary.

		This really removes the word from the NotUserDict (see QueryNotUserDict).

		@param rWord			word to undo remove

		@return bool16			kTrue if word was removed. 
	*/
	virtual	bool16		UndoRemoveFromMainDict( const WideString &rWord ) = 0;

	/** 
		Clears removed words from main dictionary.

		This really clear the words in NotUserDict (see QueryNotUserDict).

		@return bool16			kTrue if words were removed. 
	*/
	virtual	bool16		ClearRemovedFromMainDict(IUserDict* userDict) = 0;

	/**
		UNSUPPORTED
	*/
	virtual	bool16		CloseNotClamFile() = 0;
	/**
		UNSUPPORTED
	*/
	virtual	bool16		IsWordInMainDict( const WideString &rWord, const HyphenPoints *pPoints = nil ) = 0;
	
	/**
		UNSUPPORTED
	*/
	virtual	bool16		Bind( IUserDict* userDict, const WideString &rChangeFrom, const WideString &rChangeTo ) = 0;
	/**
		UNSUPPORTED
	*/
	virtual	bool16		Unbind( IUserDict* userDict, const WideString &rChangeFrom, const WideString &rChangeTo ) = 0;
};

#endif
