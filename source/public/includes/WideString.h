//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WideString.h $
//  
//  Owner: Nat McCully
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
//  An UTF16-encoded string (16-bit code values).
//  
//  SEE USAGE EXAMPLES AT THE BOTTOM OF THIS FILE!
//  
//========================================================================================

#pragma once
#ifndef __WIDESTRING__
#define __WIDESTRING__

#include "PMUtils.h"
#include "K2Iterator.h"
#include "K2TypeTraits.h"
#include "Invariant.h"
#include "UnicodeClass.h"
#include "K2SmartPtr.h"

#include "Trace.h"	// /public/includes/

#include "UnicodeSavvyString.h"

class PMString;
class IPMStream;
class TextIterator;

#pragma export on

// SEE USAGE EXAMPLES AT THE BOTTOM OF THIS FILE!

// Alias for an unicode code point as defined by the Unicode standard.
// Long story made short: UTF32TextChar was introduced because we wanted to provide
// some type safety. To anybody's indignation, the compilers will happily accept the following code:
//
// typedef uint32 UniCodePoint;
// UniCodePoint u(0xFFFFFFFF);
// char c = u;
//
// Not even a warning is generated. This intention of providing some basic type safety
// is honorable and we respect that. However, we run accros a big problem when trying
// to use the UTF32TextChar in conjuction with boost::tokenizer. The <xstring> header shipped
// with .NET 2003 compiler has a small stirng optimization defined like this:
//
//	union _Bxty{
//		_Elem _Buf[_BUF_SIZE];
//		_Elem *_Ptr;
//		} _Bx;
//
// Unfortunately, when instantiating the above template code _Elem template type to UTF32TextChar
// we get a compiler error because you can't put types that have constructors in the unions.
//
// Until we find a solution that will satisfy these two conflicting requirements, we will
// use this typedef for our Unicode code point type.
//
// BEWARE: DON'T MAKE ANY ASSUMPTIONS in your code about the size of a UniCodePoint.
// DO NOT assume that will always be 32-bit and don't cast it around. Just use it as it is.
//
typedef uint32 UniCodePoint;

class WideString;

/**
		WideStringConstUTF32Iter, also known as WideString::const_iterator, is an iterator class
		on a WideString object. The buffer in a WideString is encoded in UTF-16, which means that
		Unicode surrogates are used when representing codepoints > U+FFFF. It is important to
		limit direct access to the buffer in a WideString because of the possible presence of surrogates.
		The iterator internally handles surrogates, so clients can operate in true UTF-32 character units.
*/
class  WideStringConstUTF32Iter
{
public:

	// Iterator traits: not entirely correct, but work for now :)
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef UniCodePoint value_type;
	typedef std::ptrdiff_t difference_type;
	typedef UTF16TextChar* pointer;
	typedef UTF16TextChar& reference;

	WideStringConstUTF32Iter(const WideString *string, int32 charIndex = 0);

	WideStringConstUTF32Iter(const UTF16TextChar *buffer, bool16 hasSurrogates, int32 numChars) : fCurrent(buffer), fHasSurrogates(hasSurrogates)
		{
#ifdef DEBUG
			fNumChars = numChars;
			fPosition = 0;
#else
			numChars++; //make release happy
#endif
		}

	/** Returns a const ptr to the WideString buffer at the location of the iterator.
		Should be used with care, since buffers can contain surrogate pairs of UTF-16 codepoints.
		@return const UTF16TextChar*
	*/
	const UTF16TextChar* PtrAt() const
		{ return fCurrent; }

	/** Dereference operator.
		@return UTF32TextChar
	*/
	value_type operator*() const
		{
#ifdef DEBUG 
			ASSERT(fPosition >= 0 && fPosition <= fNumChars);
#endif
            return fHasSurrogates ? surro_operStar() : *fCurrent; 
	}

	/** Pre-Increment operator. Less expensive than post-incrementing.
	*/
	WideStringConstUTF32Iter& operator++()
		{ if (fHasSurrogates) surro_operPP();
			else ++fCurrent;
#ifdef DEBUG
		  ++fPosition;
		  ASSERT(fPosition <= fNumChars);	// can be one off end
#endif
		  return *this; }

	/** Post-Increment operator. Makes a copy, so more expensive than pre-incrementing.
	*/
	WideStringConstUTF32Iter operator++(int)
		{ WideStringConstUTF32Iter tmp(*this); ++(*this); return tmp; }

	/** Pre-Decrement operator. Less expensive than post-decrementing.
	*/
	WideStringConstUTF32Iter& operator--()
		{ if (fHasSurrogates) surro_operMM();
			else --fCurrent;
#ifdef DEBUG
		  --fPosition;
		  ASSERT(fPosition >= 0);
#endif
		  return *this; }

	/** Post-Decrement operator. Makes a copy, so more expensive than pre-decrementing.
	*/
	WideStringConstUTF32Iter operator--(int)
		{ WideStringConstUTF32Iter tmp(*this); --(*this); return tmp; }

	WideStringConstUTF32Iter& operator+=(int32 n)
		{ if (fHasSurrogates) surro_operPE(n);
			else {
				fCurrent += n;
#ifdef DEBUG
		  		fPosition += n;
			}
		  ASSERT(fPosition <= fNumChars);	// can be one off end
#else
			}
#endif
		  return *this; }

	WideStringConstUTF32Iter operator+(int32 n) const
		{ return WideStringConstUTF32Iter(*this) += n; }

	WideStringConstUTF32Iter& operator-=(int32 n)
		{ if (fHasSurrogates) surro_operME(n);
		  else {
		  	fCurrent -= n;
#ifdef DEBUG
		  	fPosition -= n;
		  	}
		  	ASSERT(fPosition >= 0);
#else
			}
#endif
		  return *this; }

	WideStringConstUTF32Iter operator-(int32 n) const
		{ return WideStringConstUTF32Iter(*this) -= n; }

	int32 operator-(const WideStringConstUTF32Iter& other) const
		{ return fHasSurrogates ? surro_operDiff(other) : fCurrent - other.fCurrent; }

	UTF32TextChar operator[](int32 i) const
		{ WideStringConstUTF32Iter tmp(*this); tmp += i; return *tmp; }

	friend WideStringConstUTF32Iter operator+(int32 n, const WideStringConstUTF32Iter& rhs)
		{ return WideStringConstUTF32Iter(rhs) += n; }

	friend bool operator==(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent == y.fCurrent; }

	friend bool operator!=(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent != y.fCurrent; }

	friend bool operator<(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent < y.fCurrent; }

	friend bool operator<=(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent <= y.fCurrent; }

	friend bool operator>(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent > y.fCurrent; }

	friend bool operator>=(const WideStringConstUTF32Iter& x, const WideStringConstUTF32Iter& y)
		{ return x.fCurrent >= y.fCurrent; }

#ifdef DEBUG
	/** DEBUG ONLY -- keeps track of current position in WideString buffer
	*/
	int32 Position() const
		{ return fPosition; }

	/** DEBUG ONLY -- keeps track of number of characters (UTF-32) in WideString buffer
	*/
	int32 NumChars() const
		{ return fNumChars; }

	/** DEBUG ONLY -- keeps track of number of characters (UTF-32) in WideString buffer
	*/
	int32& NumChars()
		{ return fNumChars; }
#endif

private:
	WideStringConstUTF32Iter() {}
	const UTF16TextChar * operator->() const { return fCurrent; }
	PUBLIC_DECL UniCodePoint surro_operStar() const;
	PUBLIC_DECL void surro_operPP();
	PUBLIC_DECL void surro_operPE(int32 n);
	PUBLIC_DECL void surro_operMM();
	PUBLIC_DECL void surro_operME(int32 n);
	PUBLIC_DECL int32 surro_operDiff(const WideStringConstUTF32Iter& other) const;

private:
	const UTF16TextChar *fCurrent;
	bool16				fHasSurrogates;
#ifdef DEBUG
	int32				fNumChars;
	int32				fPosition;
#endif
};



/** return the number of characters stripped from the string
*/
template <typename T>
int32 Strip_If(WideString& string, T f);

/**
		WideString is the main Unicode string storage class.
*/
class WideString : public UnicodeSavvyString
{
	public:
   		typedef object_type 				data_type;
		typedef UTF16TextChar&			reference_raw;
		typedef const UTF16TextChar&		const_reference_raw;
		typedef UTF16TextChar			value_type_raw;
		typedef std::ptrdiff_t				difference_type;
		typedef UTF16TextChar*			pointer_raw;
		typedef const UTF16TextChar*		const_pointer_raw;

		typedef UTF16TextChar*			iterator_raw;
		typedef const UTF16TextChar*		const_iterator_raw;
		typedef K2Reverse_iterator<iterator_raw, value_type_raw, difference_type, pointer_raw, reference_raw>					reverse_iterator_raw;
		typedef K2Reverse_iterator<const_iterator_raw, value_type_raw, difference_type, const_pointer_raw, const_reference_raw>	const_reverse_iterator_raw;

		typedef UTF32TextChar&			reference;
		typedef const UTF32TextChar&		const_reference;
		typedef UTF32TextChar			value_type;
		typedef UTF32TextChar*			pointer;
		typedef const UTF32TextChar*		const_pointer;

//		typedef WideStringUTF32Iter			iterator;
		typedef WideStringConstUTF32Iter	const_iterator;
		typedef K2Reverse_iterator<const_iterator, value_type, difference_type, const_pointer, const_iterator::value_type> const_reverse_iterator;

		//////////////// Constructors //////////////

		PUBLIC_DECL WideString();

		explicit PUBLIC_DECL WideString(WideString::const_pointer_raw s, int32 len = kMaxInt32, int32 numChars = -1);

		PUBLIC_DECL WideString(const WideString::const_iterator& iter, int32 numChars);

		PUBLIC_DECL WideString(const WideString& w);

		WideString(WideString &&other) noexcept = default;

		explicit PUBLIC_DECL WideString(ConstCString string, int32 numChars = -1);

		explicit PUBLIC_DECL WideString(const PMString& s);

		PUBLIC_DECL explicit WideString(const wchar_t* s, int32 len = kMaxInt32); 	// wchar_t is a distinct type on CW

		/** Constructs the string using a range of code values [b, e).
			The code values in the range need to be UTF16 or UTF32 encoded.
			@param b [IN] - beginning  of the range.
			@param e [IN] - end of the range (one past last one).
			@param nCodePoints [IN, OPTIONAL] - number of code points in the range.
				This parameter can be used for optimization purposes, if the caller
				knows the number of code points represented in the range.
		*/
		template <class IteratorType>
		WideString(IteratorType b, IteratorType e, size_type nCodePoints = 0)
			: UnicodeSavvyString()
		{
			assign(b, e, nCodePoints);
		}

		/** Movable constructor - assumes ownership of the remote part.
		 */
		WideString(adobe::move_from<WideString> other)
			: UnicodeSavvyString(adobe::move_from<UnicodeSavvyString>(other.source))
		{}

		/** Destructor.
		*/
		PUBLIC_DECL ~WideString();

				/**
					COPY the data passed in into a new implementation
				*/
		PUBLIC_DECL void SetString(const WideString& s);
		PUBLIC_DECL void SetString(const WideString::const_iterator& iter, int32 numChars);

				/**
					these routines automatically convert to 16 bits.
					optionally they will also convert embedded unicode sequences, e.g. <2022> (unicode bullet)
				*/
		PUBLIC_DECL void SetCString(ConstCString C, bool16 convertEmbeddedUnicode = kFalse, int32 numChars = -1);

		PUBLIC_DECL void SetX16String(WideString::const_pointer_raw x, int32 len = kMaxInt32, int32 numChars = -1);		// already 16 bit string
		PUBLIC_DECL void SetX16String(const wchar_t* s, int32 len = kMaxInt32, int32 numChars = -1);

				/**
					the next set return a pointer to the buffer still owned by the object
					fast and dangerous...you'd better not be modifying format or content
					of the object while the pointer is in use. The point of these is to
					lightly wrap system strings while avoiding a round trip copy.
					This CAN do slow things if you HAVE a cstring and ask for a pstring,
					the object will turn itself into something that can return a pstring.
					These work best when you ask for a format that is easy to convert to.

					You cannot change the number of characters in the buffer using iterators.
					If you use the raw non-const iterators on a string that has
					surrogates, you cannot change a surrogate value to a non-surrogate, and vice-versa.
				*/
		PUBLIC_DECL iterator_raw begin_raw();
		PUBLIC_DECL const_iterator_raw begin_raw() const;


		PUBLIC_DECL iterator_raw end_raw();

		PUBLIC_DECL const_iterator_raw end_raw() const;


		reverse_iterator_raw rbegin_raw()
			{ TRACE_IF(HasMultiWordUnicode(), "About to hand back non-const iterator on WideString's buffer! Be careful with surrogates!"); return reverse_iterator_raw(end_raw()); }
		const_reverse_iterator_raw rbegin_raw() const
			{ return const_reverse_iterator_raw(end_raw()); }

		reverse_iterator_raw rend_raw()
			{ TRACE_IF(HasMultiWordUnicode(), "About to hand back non-const iterator on WideString's buffer! Be careful with surrogates!"); return reverse_iterator_raw(begin_raw()); }
		const_reverse_iterator_raw rend_raw() const
			{ return const_reverse_iterator_raw(begin_raw()); }


			/** These are the methods on the smart UTF32 and surrogate-savvy iterator.
				Since the UTF32TextChar handed back cannot be changed (it is calculated),
				there is no non-const version of the iterator.
			*/
		const_iterator begin() const
			{ return const_iterator(this, 0); }

		const_iterator end() const
			{ return const_iterator(this, CharCount()); }

		const_reverse_iterator rbegin() const
			{ return const_reverse_iterator(end()); }

		const_reverse_iterator rend() const
			{ return const_reverse_iterator(begin()); }

			//---------------------------


		PUBLIC_DECL int32 UTF16IndexToCodePointIndex(int32 index) const;

			//---------------------------

		bool16 empty() const
			{ return fUTF16BufferLength == 0; }

		void Clear()
			{ clear(); }

		/** DEPRECATED: Use CharCount() instead
		*/
		int32 Length() const
			{ return CharCount(); }

		bool16 IsNull() const
			{ return empty(); }

		//---------CHAR LEVEL ROUTINES
		UTF32TextChar GetChar(int32 pos) const
			{ return GetUTF32TextChar(pos); }
		PUBLIC_DECL UTF32TextChar LastChar() const;
		PUBLIC_DECL UTF32TextChar FirstChar() const;

		void push_back(WideString::value_type c)
			{ Append(c); }

				// these routines append only, no positioning provided (use insert)

		PUBLIC_DECL void Append(const WideString &s);

 		void Append(const WideString::const_iterator& iter, int32 numChars)
			{ Append(iter.PtrAt(), (iter + numChars).PtrAt() - iter.PtrAt(), numChars); }

		PUBLIC_DECL void Append(WideString::const_pointer_raw buf, int32 n, int32 numChars = -1);

		/** Appends the code values from the C-array s at the end of the current string.
			@param s [IN] - C-array of code values that will be added to this string.
			@param nCodeValues [IN] - number of code values to be added.
			@param nCodePoints [IN, OPTIONAL] - number of code points that nCodeValues represent.
			This can be used for optimization purposes if the caller knows how many code points are added.
			@return reference to this string.
		*/
		WideString& append(WideString::const_pointer_raw s, size_type nCodeValues, size_type nCodePoints = 0)
		{
			UnicodeSavvyString::append(s, nCodeValues, nCodePoints);
			return *this;
		}

		/** Replaces the code points in range [b, e) with the string s.
			The function grows the string if necessary to accomodate for the replacement string.
			Note: to remove the specified range, use an empty string.
			To insert or append characters without removing anything, use the same iterator for b and e.
			@param b [IN] - begining of the range where replacement starts.
			@param e [IN] - end of the range to be replaced.
			@param s [IN] - replacement string whose content will replace the [b, e) range.
			@return reference to this string.
		*/
		WideString& replace(const WideString::const_iterator& b, const WideString::const_iterator& e, const WideString& s)
		{
			return replace(b, e, s.begin(), s.end());
		}

		/** Replaces the code points in range [b, e) with the code points in the range [br, er).
			The function grows the string if necessary to accomodate for the replacement string.
			Note: to remove the specified range, use an empty range for replacement (i.e. br == er).
			To insert or append characters without removing anything, use the same iterator for b and e.
			@param b [IN] - begining of the range where replacement starts.
			@param e [IN] - end of the range to be replaced.
			@param br [IN] - begin of replacement range.
			@param er [IN] - begin of replacement range.
			@return reference to this string.
		*/
		PUBLIC_DECL WideString& replace(const WideString::const_iterator& b, const WideString::const_iterator& e,
													const WideString::const_iterator& br, const WideString::const_iterator& er);

		/** Removes the code points in range [b, e).
			@param b [IN] - begining of the range where erase starts.
			@param e [IN] - end of the range to be erased.
			@return reference to this string.
		*/
		WideString& erase(const WideString::const_iterator& b, const WideString::const_iterator& e)
		{
			return replace(b, e, b, b);
		}

		void Append(WideString::value_type c32)
			{ UnicodeSavvyString::AppendUTF32TextChar(c32); }

				// these routines insert count character of string s at position.
		PUBLIC_DECL void Insert(const WideString &s, int32 position = 0, int32 count = kMaxInt32);
		void Insert(WideString::const_pointer_raw buf, int32 len, int32 pos = 0)
			{ if (len > 0) UnicodeSavvyString::InsertUTF16String(buf, len, pos); }
		void Insert(WideString::value_type c, int32 pos = 0)
			{ UnicodeSavvyString::InsertUTF32TextChar(c, pos); }

		PUBLIC_DECL WideString* Substring(int32 position, int32 count = kMaxInt32) const;		// return string from position on, zero = rest

		/**	Returns the specified token/item of a string, given a single delimiter
			@param delimiter IN The string to use as a delimiter
		 	@param nItem IN The one based item number for the the desired item
		 	@return A pointer to a string you need to deallocate, typically via k2::scoped_ptr.
		 	If the item does not exist (i.e. nItem is too low or high) then nil will be returned
		 	instead of a valid object.
		 */
		PUBLIC_DECL WideString* GetItem(const WideString& delimiter, const int32 nItem) const;				// return the item-th delimited token, one based

		PUBLIC_DECL void remove_raw(int32 utf16Pos, int32 utf16Count);
		PUBLIC_DECL void RemoveCodePoints(int32 startCodePointIndex, int32 numCodePoints);		// assumes legal arguments, doesn't call CountChars()

		PUBLIC_DECL int32 IndexOf(const WideString& keyString, int32 position = 0) const; 	// position of non-overlappin occurence of key string
		PUBLIC_DECL int32 IndexOf(WideString::value_type c, int32 position = 0) const;

		bool16 Contains(const WideString& key, int32 pos = 0) const
			{ return IndexOf(key, pos) >= 0; }

		/**	remove extra chunks if false, all extra space if true
		*/
		void Shrink(bool16 maxshrink = kFalse);

		//----------OPERATORS---------------

		/** Copy assignment operator. */
		WideString& operator = (const WideString &other)
		{
			UnicodeSavvyString::CopyFrom(other);
			return *this;
		}

		/** Move assignment operator. */
		WideString& operator = (WideString &&other) noexcept
		{
			UnicodeSavvyString::move_from(other);
			return *this;
		}

		WideString& operator = (WideString::const_pointer_raw copy)
		{
			return assign(copy, copy + UTF16TextCharLength(copy));
		}

			/** CANNOT set using this routine! use SetChar()
			*/
		const UTF32TextChar operator[](int32 index) const
			{ return GetChar(index); }

		PUBLIC_DECL void SetChar(int32 index, WideString::value_type c32);

		PUBLIC_DECL int32 compare(const WideString& s) const;

		/** Assigns to the string the code values in the specified range [b, e).
			The code values in the range need to be UTF16 or UTF32 encoded.
			@param b [IN] - beginning  of the range.
			@param e [IN] - end of the range (one past last one).
			@param nCodePoints [IN, OPTIONAL] - number of code points in the range.
				This parameter can be used for optimization purposes, if the caller
				knows the number of code points represented in the range.
		*/
		template <class IteratorType>
		WideString& assign(IteratorType b, IteratorType e, size_type nCodePoints = 0)
		{
			typedef typename std::iterator_traits<IteratorType>::value_type iterator_value_type;

			// We accept iterators to UTF16 or UTF32 ranges only!
			BOOST_STATIC_ASSERT(sizeof(iterator_value_type)*CHAR_BIT == 16 ||
								sizeof(iterator_value_type)*CHAR_BIT == 32);

			// The code values should be unsigned values
			BOOST_STATIC_ASSERT(!std::numeric_limits<iterator_value_type>::is_signed);

			// Dispatch to the correct impl (UTF16 or UTF32 source)
			EncodingSelector<sizeof(iterator_value_type)*CHAR_BIT> encodingSel;

			WideString::assign_impl(b, e, nCodePoints, encodingSel);
			return *this;
		}

		/** Assigns to the string nCodeValues from the array indicated by src.
			The code values in the range need to be UTF16 encoded.
			@param src [IN] - array of UTF16 code values. It must contain at least nCodeValues elements.
			@param nCodeValues [IN, OPTIONAL] - number of code values to be copied from src.
			@param nCodePoints [IN, OPTIONAL] - number of code points represented in the specified range.
		*/
		inline WideString& assign(WideString::const_pointer_raw src, size_type nCodeValues, size_type nCodePoints = 0)
		{
			// Check for negative values
			ASSERT_MSG(nCodeValues != static_cast<size_type>(-1), "-1 is not a valid value for nCodeValues");
			ASSERT_MSG(nCodePoints != static_cast<size_type>(-1), "-1 is not a valid value for nCodePoints");

			return assign(src, src + nCodeValues, nCodePoints);
		}


		bool16 operator >= (const WideString &s) const
			{ return compare(s) >= 0; }
		bool16 operator > (const WideString &s) const
			{ return compare(s) > 0; }
		bool16 operator <= (const WideString &s) const
			{ return compare(s) <= 0; }
		bool16 operator < (const WideString &s) const
			{ return compare(s) < 0; }

		PUBLIC_DECL bool16 operator == (const WideString &s) const;
		bool16 operator != (const WideString &s) const
			{ return !(*this == s); }

		PUBLIC_DECL bool16 operator == (WideString::const_pointer_raw b) const;
		bool16 operator != (const UTF16TextChar *b) const
			{ return !(*this == b); }

		WideString& operator +=(WideString::value_type c)
		{	UnicodeSavvyString::AppendUTF32TextChar(c);
			return *this;	}

		WideString& operator +=(const WideString& s)
		{	Append(s);
			return *this;	}

		//---------------MISC ROUTINES------------------------
		/** provide a binary hash value based on numeric codes
		*/
		PUBLIC_DECL uint32 Hash(void) const;
		PUBLIC_DECL void ToLower();
		PUBLIC_DECL void ToUpper();

		/** remove all instance of char in the string and return the number of chars stripped
		*/
		int32 Strip(WideString::value_type c)
			{ return Strip_If(*this, std::bind1st(std::equal_to<WideString::value_type>(), c));}

			//----------------------------------------------------
			// conversion routines.
		// *** GetAsSystemString() is now obsolete. In order to convert a WideString
		// *** into a PMString you can either:
		// *** 1. Construct the PMString using a WideString argument.
		// *** 2. Assign the WideString to the PMString using operator=.
		// *** 3. Call GetSystemString().
//		PMString* 		GetAsSystemString(void) const;
		PUBLIC_DECL void BuildFromSystemString(const PMString& ss);
		PUBLIC_DECL void GetSystemString( PMString *ss ) const;

			//------streaming functions---------
		PUBLIC_DECL void ReadWrite(IPMStream* s);

	private:

		// Helper selector for assign() dispatch
	    template <unsigned int i> class EncodingSelector {};

		/** Specialization for UTF16 iterators.
		*/
		template <class IteratorType>
		inline void assign_impl(IteratorType b, IteratorType e, size_type nCodePoints, EncodingSelector<16>)
		{
			// UnicodeSavvyString handles UTF16s
			UnicodeSavvyString::assign(b, e, nCodePoints);
		}

		/** Specialization for UTF32 iterators.
		*/
		template <class IteratorType>
		void assign_impl(IteratorType b, IteratorType e, size_type nCodePoints, EncodingSelector<32>)
		{
			clear();

			// Try to optimize allocations in case the client told us the number of code points.
			if (nCodePoints)
			{
				reserve(nCodePoints);
			}

			// TODO: optimize this - it goes thru an unnecessary UTF32TextChar constructor
			std::copy(b, e, std::back_inserter(*this));
		}


#ifdef DEBUG
	// ---- Data
	mutable InvariantCount 	fInvariant;
public:
	PUBLIC_DECL void Invariant() const;
	// atomic updates and reads
	PUBLIC_DECL static bool16 ts_ForceRoundtrip;
private:
	PUBLIC_DECL bool16 ParseForMultiWordUnicode() const;
#endif
public:
	PUBLIC_DECL static const boost::shared_ptr<WideString> kNil_shared_ptr;
};

inline WideStringConstUTF32Iter::WideStringConstUTF32Iter(const WideString *string, int32 charIndex)
{
	if (string)
	{
		fCurrent = string->GrabUTF16Buffer(nil) + string->CodePointIndexToUTF16Index(charIndex);
		fHasSurrogates = string->HasMultiWordUnicode();
#ifdef DEBUG
		fPosition = charIndex;
		fNumChars = string->CharCount();
#endif
	}
	else
	{
		fCurrent = nil;
		fHasSurrogates = kFalse;
#ifdef DEBUG
		fPosition = 0;
		fNumChars = 0;
#endif
	}
}

inline void swap(WideString& left, WideString& right) noexcept
{
	// Base class swap
	swap(static_cast<UnicodeSavvyString&>(left), static_cast<UnicodeSavvyString&>(right));
}

/** return the number of characters stripped from the string
*/
template <typename T>
int32 Strip_If(WideString& string, T f)
{
	const int32	originalNumChars = string.CharCount();
	int32		num2Strip = 0;

	for (int32 strIndex = originalNumChars - 1; strIndex >= 0; --strIndex)
	{
		if (f(string.GetChar(strIndex)))
			++num2Strip;
		else if (num2Strip)
		{
			string.RemoveCodePoints(strIndex+1, num2Strip);	// start from the next one becaues we just found one NOT to strip
			num2Strip = 0;

		}
	}
		// stripping from the beginning
	if (num2Strip)
		string.RemoveCodePoints(0, num2Strip);	// start from the next one becaues we just found one NOT to strip

	return originalNumChars - string.CharCount();
}


inline WideString::const_iterator_raw ToRawIterator(const WideStringConstUTF32Iter& iter)
{ return iter.PtrAt(); }
inline WideString::const_pointer_raw IterToPtr(const WideString::const_iterator_raw& i)
{ return &(*i); }
inline int NumUTF16CodesFromCharacter(const WideString::value_type val)
{ return (val > 0xFFFF ? 2 : 1); }



/** Specialization for WideString's const iterator.
	This is necessary because WideStringConstUTF32Iter's value_type is a 32 bit value.
*/
template <>
inline WideString& WideString::assign<WideString::const_iterator>(WideString::const_iterator b, WideString::const_iterator e, size_type nCodePoints)
{
	UnicodeSavvyString::assign(b.PtrAt(), e.PtrAt(), nCodePoints);
	return *this;
}

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("widestring:indesign:adobe",WideString);

#pragma export off

/** Usage examples:

-- Constructing a WideString from a const ASCII string:

	WideString str(L"my string");

-- Converting to/from UTF8
	You have two options:
		1 - use the ASL proviced Unicode utilities (see unicode.hpp).
			These utilities always throw an exception if they encounter a malformed UTF sequence.
		2 - use the iterator adapters (see unicode/utf8_iterators.h)
			You can specify the error policy (or create you own) allowing you to specify
			the behavior you need when malformed sequences are encountered.

	** From UTF8 **
	1)	std::vector<utf8_t> src;
		WideString str(utf8::make_input_iter_adapter(src.begin()), utf8::make_input_iter_adapter(src.end()));

	2)	WideString str2;
		adobe::to_utf32(src.begin(), src.end(), std::back_inserter(str2));

	** To UTF8 **
	1)	std::vector<utf8_t> dest;
		WideString str(L"test");
		std::copy(str.begin(), str.end(), utf8::make_output_iter_adapter(std::back_inserter(dest)));

	2)	adobe::to_utf8(str.begin(), str.end(), std::back_inserter(dest));

-- To use WideString with boost::tokenizer:

	WideString sentence(L"The quick brown fox jumps over the lazy dog");

	// Convenience typedefs
	typedef	boost::char_separator<UniCodePoint> UTF32TextCharSeparator;
	typedef boost::tokenizer<UTF32TextCharSeparator, WideString::const_iterator, WideString > WideTokenizer;

	// Define the separators
	UniCodePoint	wordSeparator[2] = { kTextChar_Space, kTextChar_Null };

	// Construct a char_separator object
	UTF32TextCharSeparator	separator(wordSeparator);

	// Construct the tokenizer
	WideTokenizer theTokens(sentence, separator);

	// Iterate thru the tokens
	WideTokenizer::iterator it = theTokens.begin();
	for (; it != theTokens.end(); ++it)
	{
		// *it will return a WideString object
		DoSomething(*it);
	}

	// or even more hip:
	for_each(theToken.begin(), theTokens.end(), DoSomething);

*/

#endif
