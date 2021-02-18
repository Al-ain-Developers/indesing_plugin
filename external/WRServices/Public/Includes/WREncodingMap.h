//========================================================================================
//  
//  File: WREncodingMap.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WREncodingMap__
#define __WREncodingMap__

#include "WRConfig.h"

#include "WRDefines.h"
#include "WRClass.h"
#include "WRVector.h"

#include <memory.h>
#ifdef WR_MAC_ENV
#include <string.h>
#endif

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

#ifdef WR_WIN_ENV
#pragma warning (disable:4251)
#endif

/// Helper to deal with variable size encoded text (UTF-8, UTF-16)
/**
	Many client applications use utf-16 with surrogates or utf-8 instead for the fixed-size UTF-32 encoding for storage efficiency, 
	backward compatibility, etc. Besides the problem of ensuring the encoding integrity, the client must convert the text data and 
	positions in the text to a fixed encoding for calling the line shaping, the direction resolution, and the selection management. 
	Some clients create an fixed-size encoding abstract view on the text model and do not need any extra handling, but the other 
	need to take care of this transcoding explicitely. 
	This class is a run-time helper buffer that handles the transcoding: the input data is passed by SetUTFxx(),  
	the fixed-size encoding being available character by character with GetUTF32() or globally for IWROptyca::SetUnicode() 
	with PeekUTF32() and FixedSize().
	Mapping between indexes in the variable-size encoded input and indexes in the fixed-size encoded output can be performed by 
	FixedToVar() and VarToFixed().  Those method are based on fast, direct-access tables. The same information can be grabbed in a 
	more compact format by GetUTFMapping() for storage and use in the SubstitutionLog.
	NB: the UTF-32 input format is provided here for consistency, although the transcoding will be a no-op.
	@see SubstitutionLog
*/

class WRSERVICES_DECL WREncodingMap : public WRClass
{
public:
	/// Empty WREncodingMap constructor
	/**
		Creates a empty WREncodingMap. WREncodingMap can be reused freely.
	*/
	WREncodingMap() {};

	/// WREncodingMap destructor
	/**
		Releases internal buffers and destroys the object
	*/
	virtual ~WREncodingMap() {};

	/// Set up the map with UTF-8 text
	/**
		Prepares an UTF-32 version of the utf-8 text and updates variable to fixed and fixed to variable index translators
		@param utf8 a pointer to a const char array containing utf-8 encoded text (no trailing null required)
		@param utf8len the byte count (not the UTF32 char count)
		@return a WRInt32 containing an error code (transcoding errors meaning the text is not correctly encoded)
		@see SetUTF16(), SetUTF32()
	*/
	WRInt32 SetUTF8(const char* utf8, int utf8len);

	/// Set up the map with UTF-16 text
	/**
		Prepares an UTF-32 version of the utf-16 text and updates variable to fixed and fixed to variable index translators
		@param utf16 a pointer to a const WRUnichar16 array containing utf-16 encoded text (no trailing null required)
		@param utf16len the utf-16 count (neither the byte count nor the UTF32 char count)
		@return a WRInt32 containing an error code (transcoding errors meaning the text is not correctly encoded)
		@see SetUTF8(), SetUTF32()
	*/
	WRInt32 SetUTF16(const WRUnichar16* utf16, int utf16len);

	/// Set up the map with UTF-32 text
	/**
		Initializes the buffer with UTF-32 text (no transcoding occurs)
		@param utf32 a pointer to a const WRUnichar32 array containing utf-32 encoded text (no trailing null required)
		@param utf32len the char count (not the byte count)
		@return a WRInt32 containing an error code (always kWRNoErr)
		@see SetUTF8(), SetUTF16()
	*/
	WRInt32 SetUTF32(const WRUnichar32* utf32, int utf32len);

	/// Variable encoding/fixed encoding mapping
	/**
		Returns a reference a WRVector<int> constaining the (compressed) data required for mapping from varaible encoding indexes to fixed encoding
		indexes and back. The content of this vector is often stored in the SubstitutionLog and used automatically.
		The actual format is a run-length encoding string of character coding length: (run_in_chars << 4) | char_len. This allows for runs up to more than 1 billion characters.
		@return a refernce to a WRVector<int>
		@see SetUTF8(), SetUTF16(), SetUTF32() and SubstitutionLog
	*/
	const WRVector<int>&		GetUTFMapping() const { return fCompressedMapping; }
	/// Text in fixed UTF-32 encoding
	/**
		Returns a pointer to the WRUnichar32 array resulting form the transcoding on the SetUTF8(), SetUTF16() or SetUF32() call
		@return a pointer to the first WRUnichar32 of the internal buffer
		@see SetUTF8(), SetUTF16() and SetUTF32()
	*/
	const WRUnichar32*		PeekUTF32() const { return fUTF32Codes.PeekArray(); }
	/// Text accessor in fixed UTF-32 encoding
	/**
		Returns the ith WRUnichar32 resulting form the transcoding of the SetUTF8(), SetUTF16() or SetUF32() input
		@param i the 0-based index in the fixed encoding text (less than FixedSize())
		@return an WRUnichar32
		@see SetUTF8(), SetUTF16(), SetUTF32() and FixedSize()
	*/
	WRUnichar32			GetUTF32(int i) const { return fUTF32Codes[i]; }

	/// Text size in fixed UTF-32 encoding
	/**
		Return the WRUnichar32 count resulting form the transcoding on the SetUTF8(), SetUTF16() or SetUF32() call
		@return a int containing the number of WRUnichar32
		@see SetUTF8(), SetUTF16() and SetUTF32()
	*/
	int					FixedSize() const { return fUTF32Codes.Size(); }
	/// size of vector fFixedToVar
	/**
	@return a int containing the number of fFixedToVar
	*/
	int					FixedToVarSize() const { return fFixedToVar.Size(); }
	///size of vector fVarToFixed
	/**
	@return a int containing the number of fVarToFixed 
	*/
	int					VarToFixedSize() const { return fVarToFixed.Size(); }

	/// Fixed to variable encoding index mapping
	/**
		Maps from a index in the fixed-encoding text to a index in the variable-encoding text
		@param n a 0-based index in the fixed encoding text (less than FixedSize())
		@return an 0-based int index in the variable encoding text
		@see SetUTF8(), SetUTF16(), SetUTF32() and FixedSize()
	*/
	int					FixedToVar(int n) const { return fFixedToVar[n]; }
	/// Variable to fixed encoding index mapping
	/**
		Maps from a index in the variable-encoding text to a index in the fixed-encoding text
		@param n a 0-based index in the variable encoding text
		@return an 0-based int index in the fixed encoding text (less than FixedSize())
		@see SetUTF8(), SetUTF16(), SetUTF32() and FixedSize()
	*/
	int					VarToFixed(int n) const { return fVarToFixed[n]; }

private:
	/// Compresses the char len table
	/**
		Compresses the content of fUncompressedMapping into fCompressedMapping
		@see GetUTFMapping(), fCompressedMapping and fUncompressedMapping
	*/
	void				CompressUTFMapping();

	WRVector<int>			fCompressedMapping; /**< Compressed char len table (fUTF32Codes.Size() long) */
	WRVector<WRUnichar32>	fUTF32Codes; /**< Fixed-encoding text (UTF32) */
	WRVector<int>			fFixedToVar; /**< Uncompressed direct mapping table (fUTF32Codes.Size() long) */
	WRVector<int>			fVarToFixed; /**< Uncompressed direct mapping table (original size long) */
	WRVector<int>			fUncompressedMapping; /**< Uncompressed char len table (run-length encoded) */
};


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif
