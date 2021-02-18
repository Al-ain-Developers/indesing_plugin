//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/HyphenExceptions.h $
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __HyphenExceptions__
#define __HyphenExceptions__

#include "K2Vector.h"
#include "UserDictWordList.h"

class ILanguage;

class PUBLIC_DECL HyphenExceptions 
{
public:
	typedef object_type data_type;
	HyphenExceptions();
	HyphenExceptions(const HyphenExceptions& other);
	HyphenExceptions(const ILanguage *language);
	~HyphenExceptions();

	void 	operator=	(const HyphenExceptions& copy);
	/**	
		Hyphenation exception is considered to be equal if all members are euqal.

		@param other		Hyphenation exception to compare to.

		@return bool16	kTrue if the hyphenation exception is the same as the other one.
	 */
	bool16 	operator==	(const HyphenExceptions& other) const
		{ return (fLanguageName == other.fLanguageName && 
				  fStrings == other.fStrings && 
				  fNotStrings == other.fNotStrings); }
	/**	
		Hyphenation exception is considered to be greater than the other one
		if language name string is greater.

		@param other		Hyphenation exception to compare to.

		@return bool16	kTrue if the hyphenation exception is greater than the other one.
	 */
	bool16 	operator>	(const HyphenExceptions& other) const
		{ return fLanguageName > other.fLanguageName; }
	/**	
		Hyphenation exception is considered to be smaller than the other one
		if language name string is smaller.

		@param other		Hyphenation exception to compare to.

		@return bool16	kTrue if the hyphenation exception is smaller than the other one.
	 */
	bool16 	operator<	(const HyphenExceptions& other) const
		{ return fLanguageName < other.fLanguageName; }

    	/**	
    		Hyphen exceptions is empty.
    	
		@return bool16    kTrue if no exceptions in either added or excluded lists
	*/
	bool16 empty() const;

	/** 
		HyphenExcetions share same language

		@param other		Other hyphenation excpetion to check against	
		
		@return bool16    	kTrue if same language
	*/
	bool16 SameLanguage(const HyphenExceptions& other) const;

	/** 
		HyphenExcetions share same language

		@param language	Language to check against
		
		@return bool16    	kTrue if same language
	*/
	bool16 SameLanguage(const ILanguage *language) const;

	/** 
		Set language
		
		@param language		language of HyphenException
	*/
	void SetLanguage(const ILanguage *language);

	/** 
		Query language
		
		@return ILanguage    language of HyphenException
	*/
	ILanguage *QueryLanguage() const;

	/** 
		Set language name
		
		@param languageName    name of language of HyphenException
	*/
	void SetLanguageName(const PMString &languageName);

	/** 
		Read and write for the hyphenation exception
		
		@param s    stream to read from or write to
	*/
	void ReadWrite(IPMStream* s);

private:
	PMString			fLanguageName;
public:
	UserDictWordList	fStrings;
	UserDictWordList	fNotStrings;
};


class PUBLIC_DECL HyphenExceptionsList		//sorted
{
	public:
		HyphenExceptionsList()
			{}
		HyphenExceptionsList(const HyphenExceptionsList& copy)
			{ *this = copy; }
		~HyphenExceptionsList();
	
		/** 
			Clears hyphenation exceptions list.
		*/
		void clear();
		/** 
			Clears hyphenation exceptions list.
		*/
		void Clear()
			{ clear(); }
		
		/** 
			Returns size of hyphenation exceptions list.

			@return int32	Size of hyphenation excpetions list.
		*/
		int32 size() const
			{ return (int32)fList.size(); }
		/** 
			Returns size of hyphenation exceptions list.

			@return int32	Size of hyphenation excpetions list.
		*/
		int32 Length() const
			{ return size(); }
			
		/** 
			Inserts the specified hyphenation exception into the list in sorted order.

			@param xx	Hyphenation exception to be inserted.
		*/
		void Insert(const HyphenExceptions& xx);
		
		/** 
			Returns the hyphenation exception in the list at specified index.

			@param i		Index in the hyphenation exeptions list.

			@return HyphenExceptions&		Hyphenation exception at specified index
		*/
		const HyphenExceptions& operator[](int32 i) const
			{ ASSERT(fList[i] != nil); return *(fList[i]); }
		/** 
			Returns the hyphenation exception in the list at specified index.

			@param i		Index in the hyphenation exeptions list.

			@return HyphenExceptions&		Hyphenation exception at specified index
		*/
		HyphenExceptions& operator[](int32 i)
			{ ASSERT(fList[i] != nil); return *(fList[i]); }

		HyphenExceptionsList& operator=(const HyphenExceptionsList& copy); 

		/** 
			Checks if the hyphenation exceptions list is the same as the other one. 
			Two lists are considered euqal if every item in the lists are equal.

			@param other		Other hyphenation exceptions list to compare with

			@return bool16		kTrue if two are considered equal
		*/
		bool16 operator==(const HyphenExceptionsList& other) const;
		/** 
			Checks if the hyphenation exceptions list is different than the other one. 
			Two lists are considered not euqal if any item in the lists are not equal.

			@param other		Other hyphenation exceptions list to compare with

			@return bool16		kTrue if two are considered not equal
		*/
		bool16 operator!=(const HyphenExceptionsList& other) const
			{ return !(*this == other); }

		/** 
			Read and write for the hyphenation exceptions list
			
			@param s    stream to read from or write to
		*/
		void ReadWrite(IPMStream* s);

	private:
		K2Vector<HyphenExceptions*>		fList;	/** List of hyphenation exceptions */
};


#endif
