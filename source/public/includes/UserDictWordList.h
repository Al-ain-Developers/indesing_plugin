//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/UserDictWordList.h $
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
//  
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef __USERDICTWORDLIST__
#define __USERDICTWORDLIST__

#include "IUserDictService.h"		// for IUserDictService::WordType
#include "TextCharBuffer.h"
#include "K2Vector.h"
#include "ScriptData.h"

class IUserDictIterator;

#ifdef PUBLIC_BUILD
#pragma export on
#endif
PUBLIC_DECL int16 CompareUserDictString(const WideString& a, const WideString& b, bool16 caseSensitive, bool16 stripHyphens);
#ifdef PUBLIC_BUILD
#pragma export off
#endif


/**
	Sorted list of widestrings for use with user dictionaries.

    @ingroup text_dict
*/
class PUBLIC_DECL UserDictWordList
{
	public:
		UserDictWordList() 
			{}
		UserDictWordList(const UserDictWordList& copy)
			{ *this = copy; }
		
		~UserDictWordList();
		
		UserDictWordList& operator=(const UserDictWordList& other);
		bool16 operator==(const UserDictWordList& other) const
			{ return fList == other.fList; }
		bool16 operator!=(const UserDictWordList& other) const
			{ return fList != other.fList; }
		
		const WideString& operator[](int32 i) const
			{ return *(fList[i]); }

		void SetChunkSize(int32 chunk)
			{ fList.reserve(chunk); }
		bool16 Preallocate(int32 newlen)
			{ fList.reserve(newlen); return kTrue; }

		/**
			Clear list.
		*/
		void clear();

		/**
			Clear list.
		*/
		void Clear()
			{ clear(); }

		/**
			Remove string from list.

			@param	at		position to remove
		*/
		void Remove(int32 at)
			{ delete fList[at]; fList.erase(fList.begin() + at); }
	
		/**
			Insert string in list.

			@return  bool16		returns true if a word was inserted into the list
		*/
		bool16 InsertUnique(const WideString& t);
		
		/**
			Insert strings from user dictionary into list.

			@return  int32		returns number of words inserted into the list
		*/
		int32 InsertUserDict(IUserDictService *pService, IUserDict* userDict, IUserDictIterator *dictIter, IUserDictService::WordType type);
		
		/**
			Insert strings from script list data into list.

			@return  int32		returns number of words inserted into the list
		*/
		int32 InsertScriptList( const ScriptListData& scriptWordList );

		int32 ChunkSize() const
			{ return 8; } //AW_TODO: Possibly deprecate this?
		int32 Length() const
			{ return (int32)fList.size(); }
		bool16 IsEmpty() const
			{ return fList.empty(); }
		const WideString& First() const
			{ return *(fList.front()); }
		const WideString& Last() const
			{ return *(fList.back()); }

		/**
			ExactLocation is for searching case-sensitive, and hyphen point matches.

			@param	t		string to find

			@return  int32		returns location of string
		*/
		int32 ExactLocation(const WideString& t) const;

		/**
			ExactLocation is for searching case-sensitive, and hyphen point matches.

			@param	buffer		string to find
			@param	length		length of string to find

			@return  int32		returns location of string
		*/
		int32 ExactLocation(const textchar *buffer, int32 length) const
			{ WideString str(buffer, length); return ExactLocation(str); }

		/**
			ExactLocation is for searching case-sensitive, and hyphen point matches.

			@param	wrapper		string to find

			@return  int32		returns location of string
		*/
		int32 ExactLocation(const TextCharBuffer& wrapper) const
			{ WideString str(wrapper.begin_raw(), wrapper.end_raw()); return ExactLocation(str); }
		
		/**
			Location is for searching case-insensitive, and hyphen points ignored matches.

			@param	t		string to find

			@return  int32		returns location of string
		*/
		int32 Location(const WideString& t) const;

		/**
			Location is for searching case-insensitive, and hyphen points ignored matches.

			@param	buffer		string to find
			@param	length		length of string to find

			@return  int32		returns location of string
		*/
		int32 Location(const textchar *buffer, int32 length) const
			{ WideString str(buffer, length); return Location(str); }

		/**
			Location is for searching case-insensitive, and hyphen points ignored matches.

			@param	wrapper		string to find

			@return  int32		returns location of string
		*/
		int32 Location(const TextCharBuffer& wrapper) const
			{ WideString str(wrapper.begin_raw(), wrapper.end_raw()); return Location(str); }

		void ReadWrite(IPMStream* s);
	
	private:
			// returns position to insert, if not found
		int32 ExactLocationHint(const WideString& t, bool16& found) const;
		int32 BasicLocationHint(const WideString& t, bool16& found) const;

		K2Vector<WideString*>	fList;
};


#endif
