//========================================================================================
//  
//  File: WRClusterBreakIterator.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2009 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2009.
//  
//========================================================================================

#ifndef __WRClusterBreakIterator__
#define __WRClusterBreakIterator__

#include "WRDefines.h"
#include "WRUnicodeDatabase.h"
#include "WRClass.h"

/// Base Class for creating cluster iterators
/**
This class is a base abstract class the client can derive to implement cluster iterators.
Clusters are the character sequences those constitute the unit for arrow key move et forward
delete. They're also the unit for drop caps.
The abstract class implements only the algorithm. The text and character unicode properties are 
provided by the client via the implementation of the GetChar method.
Note: Although the GetCluster() method isn't a typical iterator "GetNext" accessor, it has been optimized
for adjacent queries (next and prev).
*/

class WRSERVICES_DECL ClusterBreakIterator
{
public:
	/// Char structure
	/**
		This structure is a record for passing information about the character at a given position
		@see WRUCSGraphemeClusterBreak
	*/
	typedef struct 
	{
		WRInt32						fPos;		/// Position inthe text (utf32 count)
		WRUnichar32					fUnicode;	/// UTF-32 codepoint
		WRScriptID					fScript;	/// Character script ot kWRDontKnowScript
		WRUCSGraphemeClusterBreak	fCategory;	/// The type of the character
	} Char;
	/// options for the ClusterBreakIterator
	/**
		This is for fine tuning the behavior of the iterator and in particular for disabling
		the clustering in Middle Eastern script, where people are not used to it.
	*/
	enum ClusterBreakIteratorOptions
	{  
			kNoArabicClusters = 1, /// disabled the clustering in Arabic so that vowels can be individually selected 
			kNoHebrewClusters = 2,  /// disabled the clustering in Hebrew so that nikuds can be individually selected
			kNoSyriacClusters = 4,  /// disabled the clustering in Syriac so that vowel can be individually selected
			kNoMiddleEasternClusters =  kNoArabicClusters | kNoHebrewClusters|kNoSyriacClusters /// alias for all Middle Estearn scripts
	};
	/// ClusterBreakIterator constructor
	/**
		Creates a ClusterBreakIterator; mainly initialize the internal cache. 
		@param flags a bitfield specifying the options (kNoArabicClusters | kNoHebrewClusters to get the traditional ME behavior)
	*/
	ClusterBreakIterator(WRInt32 flags);

	/// ClusterBreakIterator destructor
	/**
		Currently does nothing. The implementention must not be in the header if we want to delayLoad WRServices.dll
	*/
	virtual ~ClusterBreakIterator();

	/// Get the surrounding cluster
	/**
		@param pos a WRInt32 the position in the model (utf32 count)
		@param start a WRInt32& the cluster start (utf32 count)
		@param end a WRInt32& the cluster end (utf32 count)
		@return a bool true if the cluster is not empty.
	*/
	virtual bool GetCluster(WRInt32 pos, WRInt32& start, WRInt32& end); // returns the span of the cluster containing the char at pos

protected:
	/// Get the character code at a given index
	/**
		This is an abstract method the client must implement to feed the algorithm with text codes.
		On input, only the fPos member of c is set, and the implementation of this method is expected to fill
		some of the other members. Indexes are utf32 indexes, so a mapping might be necessary if the
		textmodel uses utf-16 or utf-8 positions. 
		If the position is out-of-bounds the fCategory memeber must be set to either WRUCSGraphemeClusterBreak_sot (start of text)
		or WRUCSGraphemeClusterBreak_eot (end of text), otherwise it must be set to WRUCSGraphemeClusterBreak_Other (will be filled
		later by GetCharProperties())
		@param c a reference to a Char record, to be filled by GetChar() 
		@see UTF32ToClientEncoding(), ClientEncodingToUTF32(), WRUCSGraphemeClusterBreak, GetCharProperties

	*/
	virtual void GetCharCode(Char& c) = 0; 

	/// Get the character propterties at a given index
	/**
		This is an abstract method the client must implement to feed the algorithm with text properties.
		On input, only the fPos and fUnicode members of c are set, and the implementation of this method is expected to fill
		the other members (fCategory and fScript).  
		@param c a reference to a Char record, to be filled by GetChar() 
		@see UTF32ToClientEncoding(), ClientEncodingToUTF32(), WRUCSGraphemeClusterBreak

	*/
	virtual void GetCharProperties(Char& c) = 0; 

	/// Get the character code and  properties at a given index
	/**
		This method  to feed the algorithm with text data. It calls GetCharCode and GetCharProperties and there is usually no need to override it.
		@param c a reference to a Char record, to be filled by GetChar() 
		@see WRUCSGraphemeClusterBreak, GetCharCode(), GetCharProperties()

	*/
	virtual void GetChar(Char& c); 

	/// Determines if there is a cluster break between two characters
	/**
		This method  to feed the algorithm with text data. It calls GetCharCode and GetCharProperties and there is usually no need to override it.
		@param c1 a reference to a Char (the first in logical order)
		@param c2 a reference to a Char (the last in logical order)
		@return a bool true if there's a cluster break.
	*/
	virtual bool BreakBetween(Char& c1,Char& c2);


	Char fCharA; /// internal cache: character before the cluster start position
	Char fCharB; /// internal cache: first character of the cluster
	Char fCharC; /// internal cache: last character of the cluster
	Char fCharD; /// internal cache: character after the cluster end position
	WRInt32 fFlags; /// options
};

/// Base Class for creating cluster iterators
/**
This class is a base abstract class derived from ClusterBreakIterator, 
that can in turn be derived by the client to implement cluster iterators.
The class implements the algorithm and the character property fetching. The text is 
provided by the client via the mandatory implementation of the GetCharCode method.
*/

class WRSERVICES_DECL UCDBClusterBreakIterator : public ClusterBreakIterator
{
public:
	/// UCDBClusterBreakIterator constructor
	/**
		Creates a UCDBClusterBreakIterator
		@param flags a bitfield specifying the options (kNoArabicClusters | kNoHebrewClusters to get the traditional ME behavior)
	*/
	UCDBClusterBreakIterator(WRInt32 flags) : ClusterBreakIterator(flags) {}
protected:
	/// Get the character propterties at a given index
	/**
		This implementation calls the WRS Unicode database
		@param c a reference to a Char record, to be filled by GetChar() 
	*/
	virtual void GetCharProperties(Char& c); 
};

#endif
