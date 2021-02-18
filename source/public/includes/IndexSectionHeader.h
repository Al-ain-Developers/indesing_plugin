//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IndexSectionHeader.h $
//  
//  Owner: Michel Hutinel
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
//  comments: Data class to store one Topic Section Header ('A' or 'B' or ...).
//  
//========================================================================================

#pragma once
#ifndef __INDEXSECTIONHEADER__
#define __INDEXSECTIONHEADER__

#include "IPMStream.h"

#include "LanguageID.h"
#include "WideString.h"

/** Data class that stores a section header.
	The sections in an index depend on the language.
	For Roman languages (western) sections are "A", "B", ...
*/
class IndexSectionHeader
{
	public:
		typedef object_type data_type;

		/** Constructs an empty section header.
		*/
		IndexSectionHeader():
			fSortingHeader(""),
			fTextHeader(""),
			fUIHeader(""),
			fLanguage(kLanguageUserDefault)
			{}

		/** Equality test operator.
		*/
		bool16 operator==(const IndexSectionHeader& other) const
		{
			return ( (fSortingHeader == other.fSortingHeader) && 
				     (fTextHeader == other.fTextHeader) && 
				     (fUIHeader == other.fUIHeader) &&
					 (fLanguage == other.fLanguage)); 
		}

		/** Inequality test operator.
		*/
		bool16 operator!=(const IndexSectionHeader& other) const
		{
			return ( !(*this == other) ); 
		}

		/** Persistence support for the section header.
			@param s [IN] - the stream to read/write the section header from/to.
		*/
		void ReadWrite(IPMStream *s)
		{
			fSortingHeader.ReadWrite(s);

			fTextHeader.ReadWrite(s);

			fUIHeader.ReadWrite(s);

			s->XferInt16(fLanguage);
		}

		/** String used to attribute a topic to a section.

			Multiple characters mean other possible first letters. Example "VW" is
			used by Swedish to indicate that a word starting with either v or w may
			sort using this header. If you instead want a digraph or trigraph like
			Czech "Ch" leave this empty and use fTextHeader.
			Use capital version of letters.
		*/
		WideString		fSortingHeader;

		/** Used for sorting digraphs and trigraphs. Example Czech "Ch" or Hungarian "Dzs"
		
			Before CS3 fTextHeader was only used in the CE versions for digraphs and trigraphs (Czech, Hungarian)
			Now in CS3 this is used by all versions for digraphs and trigraphs.
			Letters may be either capital or small. Will upper case both fTextHeader and sort string on compare.
		*/
		WideString		fTextHeader;

		/** String used to display the header in the UI
		*/
		PMString		fUIHeader;

		/** Language of the section header
		*/
		LanguageID		fLanguage;
};

#endif // __INDEXSECTIONHEADER__