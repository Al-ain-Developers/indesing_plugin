//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TOCEntryInfo.h $
//  
//  Owner: Yeming Liu
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
//  comments: Helper class to do TOC sorting.
//  
//========================================================================================

#pragma once
#ifndef __TOCENTRYINFO__
#define __TOCENTRYINFO__

// ----- Interface files
#include "ITOCCmdData.h"
#include "IPMStream.h"

// ----- Include files
//#include "WideString.h"

/** Helper class to cache general information for each table of content(TOC) entry.
*/
class TOCEntryInfo
{
public:
	typedef object_type data_type;

	/** Copy constructor with given values.
		@param origStyleName IN style name included in TOC
		@param bookContentUID IN book content UID within book database
		@param pageIndex IN page index associated with the document
		@param formatUID IN UID of paragraph style to format TOC entries
		@param origStyleName IN style name included in TOC
	*/
	TOCEntryInfo(
			const PMString& origStyleName,		// style name included in TOC
			const int32& pageIndex,				// index of page
			const UID& bookContentUID,			// if kInvalidUID indicates document scope when create TOC
			const UID& formatUID,				// UID of paragraph style to format TOC entries
			const PMString& textAnchorName):	// text anchor name associated with this TOC entry in source story
		fOrigStyleName(origStyleName),
		fPageIndex(pageIndex),
		fBookContentUID(bookContentUID),
		fFormatUID(formatUID),
		fTextAnchorName(textAnchorName) {}

	PMString   fOrigStyleName;
	int32	   fPageIndex;
	UID        fBookContentUID;
	UID		   fFormatUID;
	PMString   fTextAnchorName;
};

/** Helper class to cache runin information for each table of content(TOC) entry.
*/
class TOCEntryRunInInfo
{
	public:
		typedef object_type data_type;

		/** Default constructor.
		*/
		TOCEntryRunInInfo() {}

		/** Copy constructor with given values.
		    @param entryIndex IN entry index that needs runin
			@param runInSep IN separator for runin
		*/
		TOCEntryRunInInfo(
				const int32 entryIndex,			// entry index that needs runin
				const WideString& runInSep) :	// run in separator
			fEntryIndex(entryIndex),
				fRunInSep(runInSep) {}

		/** Equal operator for comparison.
		    @param other IN the object to compare with.
			@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const TOCEntryRunInInfo& other) const
		{
			return ( (fEntryIndex == other.fEntryIndex) &&
				     (fRunInSep == other.fRunInSep) );
		}

		int32		fEntryIndex;
		WideString  fRunInSep;
};

/** Helper class to cache formating information for each table of content(TOC) entry.
    This class has the sort information.
*/
class TOCFormatEntryInfo
{
	public:
		typedef object_type data_type;

		/** Default constructor.
		*/
		TOCFormatEntryInfo() :
			fSourceDoc(""),
			fParaFormatStyle(kInvalidUID),
			fLevel(1),
			fLevelSort(kFalse),
			fPosition(ITOCCmdData::kAfterEntry),
			fPageNumFormatStyle(kInvalidUID),
			fSeparatorStyle(kInvalidUID),
			fRunIn(kFalse),
			fIncludeSectionName(kTrue)
			{
				WideString defaultSep;
				defaultSep.Append(kTextChar_Tab);
				fSeparator = defaultSep;

				WideString defaultRunInSep;
				defaultRunInSep.Append(kTextChar_Semicolon);
				fRunInSep = defaultRunInSep;
			}

		/** Copy constructor with given values.
		    @param sourceDoc IN document name from the paraFormatStyle from
			@param paraFormatStyle IN the UID of paragraph style to format TOC entries
			@param level IN level of paragraph style included in TOC
			@param bSort IN sort flag for paragraph style included in TOC
			@param position IN position for where page number should be inserted
			@param pageNumFormatStyle IN the UID of character style to format page number of TOC entry
			@param separator IN separator between TOC entry and page number
			@param separatorStyle IN the UID of character style to separator of TOC entry
			@param bRunIn IN run in flag for TOC entry
			@param runInSep IN run in separator
			@param includeSectionName IN flag for including section name of page number
		*/
		TOCFormatEntryInfo(
				const PMString&  sourceDoc,			// document name from the paraFormatStyle from
				const UID        paraFormatStyle,	// UID of paragraph style to format TOC entries
				const int32      level,				// level of paragraph style included in TOC
				const bool16	 bSort,				// sort flag for paragraph style included in TOC
				const ITOCCmdData::PageNumPosition position, // position for where page number should be inserted
				const UID        pageNumFormatStyle,// UID of character style to format page number of TOC entry
				const WideString separator,			// separator between TOC entry and page number
				const UID        separatorStyle,	// UID of character style to separator of TOC entry
				const bool16     bRunIn,			// run in flag for TOC entry
				const WideString runInSep,			// run in separator
				const bool16     includeSectionName) : // flag for including section name of page number
			fSourceDoc(sourceDoc),
			fParaFormatStyle(paraFormatStyle),
			fLevel(level),
			fLevelSort(bSort),
			fPosition(position),
			fPageNumFormatStyle(pageNumFormatStyle),
			fSeparator(separator),
			fSeparatorStyle(separatorStyle),
			fRunIn(bRunIn),
			fRunInSep(runInSep),
			fIncludeSectionName(includeSectionName){}

		/** Equal operator for comparison.
		    @param other IN the object to compare with.
			@return bool16 kTrue means equal, otherwise kFalse.
		*/
		bool16 operator==(const TOCFormatEntryInfo& other) const
		{
			return ( (fSourceDoc == other.fSourceDoc) &&
				     (fParaFormatStyle == other.fParaFormatStyle) &&
				     (fLevel == other.fLevel) &&
				     (fLevelSort == other.fLevelSort) &&
				     (fPosition == other.fPosition) &&
				     (fPageNumFormatStyle == other.fPageNumFormatStyle) &&
				     (fSeparator == other.fSeparator) &&
				     (fSeparatorStyle == other.fSeparatorStyle) &&
				     (fRunIn == other.fRunIn) &&
				     (fRunInSep == other.fRunInSep) &&
				     (fIncludeSectionName == other.fIncludeSectionName) );
		}

		/** Persist the table of content entries(TOCFormatEntryInfo) in the document.
		    @param s IN stream where we read/write object of TOCFormatEntryInfo.
		*/
		void ReadWrite(IPMStream *s)
		{
			/****************************************************************
			If this ReadWrite method ever changes you MUST update the schema
			Converter for kTOCStyleInfoImpl in TOCSchemas.fr.  That schema is
			"unrolling this class because it is written deirectly out in the
			TOCStyleInfo ReadWrite method.  Failure to do this will cause bad
			things to happen.
			****************************************************************/
			fSourceDoc.ReadWrite(s);
			s->XferReference(fParaFormatStyle);
			s->XferInt16(fLevel);

			// --- Due to the lack of UI to set the fLevelSort now,
			//     there is an assert about CStream::XferBool() not a bool.
			s->XferBool(fLevelSort);

			if (s->IsReading())
			{
				int16 position(0);
				s->XferInt16(position);
				fPosition = static_cast<ITOCCmdData::PageNumPosition>(position);
			}
			else
			{
				int16 position = static_cast<int16>(fPosition);
				s->XferInt16(position);
			}

			s->XferReference(fPageNumFormatStyle);
			fSeparator.ReadWrite(s);
			s->XferReference(fSeparatorStyle);
			s->XferBool(fRunIn);
			fRunInSep.ReadWrite(s);
			s->XferBool(fIncludeSectionName);
		}

		PMString    fSourceDoc;
		UID			fParaFormatStyle;
		int16		fLevel;
		bool16		fLevelSort;
		ITOCCmdData::PageNumPosition fPosition;
		UID			fPageNumFormatStyle;
		WideString	fSeparator;
		UID			fSeparatorStyle;
		bool16		fRunIn;
		WideString	fRunInSep;
		bool16		fIncludeSectionName;
};

#endif // __TOCENTRYINFO__
