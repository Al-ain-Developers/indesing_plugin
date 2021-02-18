//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/ICHLFileNameTable.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ICHLFileNameTable__
#define __ICHLFileNameTable__

// Interface includes:
#include "IPMUnknown.h"

// General includes:
#include "LanguageID.h"

// Project includes:
#include "CHLID.h"

// Forward declarations:
class PMString;
class ILanguage;

#include "ICUForwardDeclare.h"

#include "unicode/uloc.h"
#include "unicode/ucol.h"
#include "unicode/coll.h"

/** Keeps information about our linguistics files and correlates them to 
 * 	various	language parameters.
*/
struct CHLFileNameData 
{
	/** This allows the structure to be put into a K2Vector.
	 */
	typedef object_type data_type;

	/** The LanguageID. 
	 *	@see LanguageID.h
	 */
	LanguageID	fLanguageID;

	/** The language name. This is what gets displayed. */
	PMString	fLanguageName;

	/** Primary language name. */
	PMString	fPrimaryLanguageName;
	
	/** Sub language name. */
	PMString	fSubLanguageName;

	/** Filename (not full path) of the spelling dictionary file. */
	PMString	fCoreFileName;

	/** Filename (not full path) of the hyphenation dictionary file. */
	PMString	fHyphFileName;

	/** Filename (not full path) of the thesaurus file. */
	PMString	fThesaurusFileName;

	/** Filename (not full path) of the user dictionary file. */
	PMString	fDefaultUserDictFileName;

	/** ICULocale */
	U_ICU_NAMESPACE::Locale		fICULocale;

	/** Compares two CHLFileNameData structures.
	 * 	@param rData IN Another CHLFileNameData to compare.
	 * 	@return kTrue if equal, kFalse otherwise.
	 */
	inline bool16	operator==(const CHLFileNameData& rData) const;
};

/* operator ==
*/
inline bool16 CHLFileNameData::operator==(const CHLFileNameData& rData) const
{
	return	fLanguageID == rData.fLanguageID && 
			fPrimaryLanguageName == rData.fPrimaryLanguageName &&
			fSubLanguageName == rData.fSubLanguageName &&
			fCoreFileName == rData.fCoreFileName &&
			fHyphFileName == rData.fHyphFileName &&
			fThesaurusFileName == rData.fThesaurusFileName &&
			fDefaultUserDictFileName == rData.fDefaultUserDictFileName &&
			fICULocale == rData.fICULocale;
}


/** From SDK sample;  interface that encapsulates a name table that defines 
 *  the data files on which the spelling service depends.
 * 
 *  @ingroup chlinguistic
 *  
*/
class ICHLFileNameTable : public IPMUnknown
{
	public:

		enum { kDefaultIID = IID_ICHLFILENAMETABLE };
		
		/**	Populates an internal copy of the CHLFileNameTable
		 * 	and validates the dictionary paths.
		 * 	This is called from Install method of CHLSpellingMgr.
		 * 	@param rPath It isn't being used by this sample.
		*/
		virtual	void					Install(const PMString& rPath) = 0;
		
		/**	Get the count of CHLFileNameData entries.
		 * 	@return Count of CHLFileNameData entries
		*/
		virtual	int32 					GetEntriesCount() const = 0;
		
		/**	Get the CHLFileNameData entry for the specified index.
		 *  @param nIndex IN the index of the entries.
		 *  @return CHLFileNameData associated with the index entry.
		*/
		virtual	const CHLFileNameData*	GetNthEntry(int32 nIndex) const = 0;
		
		/**	Checks whether the specified index is a spelling service.
		 *  @param nIndex IN the index, it isn't used by this sample.
		 * 	@return returns kTrue if it is.
		*/
		virtual bool16					IsSpellingService(int32 nIndex) const = 0;
		
		/**	Checks whether the specified index is a hyphenation service.
		 *  @param nIndex IN the index, it isn't used by this sample.
		 * 	@return returns kTrue if it is.
		*/
		virtual bool16					IsHyphenationService(int32 nIndex) const = 0;
		
		/**	Checks whether the specified index is a thesaurus service.
		 *  @param nIndex IN the index, it isn't used by this sample.
		 * 	@return returns kTrue if it is.
		*/
		virtual bool16					IsThesaurusService(int32 nIndex) const = 0;
};

#endif // #ifndef __ICHLFileNameTable__


// End, ICHLFileNameTable.h.

