//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IndexHeaderGroup.h $
//  
//  Owner: Bertrand Lechevalier
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
//  comments: Data class to store one Header Group (Symbol, Numeric, Alphabet, Kana...).
//  
//========================================================================================

#pragma once
#ifndef __INDEXHEADERGROUP__
#define __INDEXHEADERGROUP__

#include "IPMStream.h"

#include "LanguageID.h"
#include "WideString.h"
#include "IndexSectionHeader.h"
#include "K2Vector.h"

/** Groups multiple section headers into one convenient unit.
	The usual groups are Symbol, Numeric, Alphabet, Kana.
*/
class IndexHeaderGroup
{
	public:
		typedef object_type data_type;

		/** Constructs an empty header group.
		*/
		IndexHeaderGroup():
			fName(""),
			fUIHeader(""),
			fTextHeader(""),
			fVisible(kFalse)
			{}

		/** Equality test operator.
		*/
		bool16 operator==(const IndexHeaderGroup& other) const
		{
			return ( (fUIHeader == other.fUIHeader) &&
				     (fName == other.fName) && 
				     (fTextHeader == other.fTextHeader) && 
				     (fVisible == other.fVisible) &&
					 (fSectionHeadersList == other.fSectionHeadersList)); 
		}

		/** Inequality test operator.
		*/
		bool16 operator!=(const IndexHeaderGroup& other) const
		{
			return ( !(*this == other) ); 
		}

		/** Appends a section header to the group.
			@param sectionHeader [IN] - the section header to add to the group.
		*/
		void AppendSectionHeader(const IndexSectionHeader& sectionHeader)
		{
			fSectionHeadersList.push_back(sectionHeader);
		}

		/** Retrieves the section header at the specified index.
			@param i [IN] - index of the desired section header within the group.
			@return the section header at the index i.
		*/
		const IndexSectionHeader& GetNthSectionHeader(int32 i) const
		{
			ASSERT_MSG(i >= 0 && i < fSectionHeadersList.size(), "GetNthSectionHeader::IndexSectionHeadersSet: bad index");
			return fSectionHeadersList[i];
		}

		/** Persistence support for the header group.
			@param s [IN] - the stream to read/write the header group from/to.
		*/
		void ReadWrite(IPMStream *s)
		{
			fName.ReadWrite(s);

			fUIHeader.ReadWrite(s);

			fTextHeader.ReadWrite(s);

			s->XferBool(fVisible);

			if (s->IsReading())
			{
				int32	numHeaders = fSectionHeadersList.size();

				s->XferInt32(numHeaders);

				fSectionHeadersList.clear();
				fSectionHeadersList.reserve(numHeaders);

				int32 i;
				for (i = 0; i < numHeaders; i++)
				{
					IndexSectionHeader	sectionHeader;

					sectionHeader.ReadWrite(s);

					fSectionHeadersList.push_back(sectionHeader);
				}
			}
			else
			{
				int32	numHeaders = fSectionHeadersList.size();

				s->XferInt32(numHeaders);
				int32 i;
				for (i = 0; i < numHeaders; i++)
					fSectionHeadersList[i].ReadWrite(s);
			}
		}

		PMString		fName;				// Internal name
		PMString		fUIHeader;			// String used to display the Group in the UI
		WideString		fTextHeader;		// String used to display the Group in the Pub text
		bool16			fVisible;
		K2Vector<IndexSectionHeader>	fSectionHeadersList;	// List of the section headers
};

#endif // __INDEXHEADERGROUP__