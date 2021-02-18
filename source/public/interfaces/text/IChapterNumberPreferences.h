//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IChapterNumberPreferences.h $
//  
//  Owner: Pushp Agarwal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __IChapterNumberPreferences__
#define __IChapterNumberPreferences__

#include "PMTypes.h"
#include "BNCoreID.h"
#include "IPMUnknown.h"
#include "IDocument.h"

#define kMinChapterNumber	1
#define kMaxChapterNumber	9999

/**
	namespace Chapter Number Type 
	Type : Type of Chapter Number 
	kUserDefined : Chapter Number is User Defined (Start Chapter Numbering At)
	kSameAsPrevDoc: Chapter Number is same as previous document's chapter number in Book (Same as Previous Document in Book)
	kContFromPrevDoc: Chapter Number is one more than previous document's chapter number (Automatic Chapter Numbering)
*/
namespace ChapterNumType
{
	enum Type
	{
		kUserDefined = 1,
		kSameAsPrevDoc = 2,
		kContFromPrevDoc = 3
	};
}

/**
	Interface to chapter number preferences of Document
	@see kDocWorkSpaceBoss, kModifyChapterNumberPrefsCmdBoss

*/

class IChapterNumberPreferences: public IPMUnknown
{
public:
	enum
   {
       kDefaultIID = IID_ICHAPTERNUMBERPREFERENCES
   };

	/**	Get ClassID of number Formatting service. This class id is of 
		a service of kService_ParagraphNumberingStyles
		@param none
		@return ClassID of number Formatting service
	*/
 	virtual ClassID GetNumberFormatter() const = 0;
	/** Get Chapter Number of document 
		@param none
		@return int32 Chapter Number of Document
	*/
	virtual int32 GetChapterNumber() const = 0;
	/** Get Chapter Number Type or method for computing
		chapter number
		@param none
		@return ChapterNumType::Type Chapter Number Type
	*/
	virtual ChapterNumType::Type GetChapterNumberType() const = 0;
	/**	Set ClassID of number Formatting service to be used for 
		chapter number. This class id is of a service of 
		kService_ParagraphNumberingStyles
		@param class id of number formatting service
	*/
	virtual void SetNumberFormatter(ClassID) = 0;
	/**
		Set Chapter Number when Chapter Numbers are User defined.
		If Chapter Number are not user defined it throws ASSERT
		@param chapterNumber IN user defined chapter number to set
	*/
	virtual void SetUserDefinedChapterNumber(int32) = 0;
	/** Set Chapter Number Type or method for computing
		chapter number
		@param  ChapterNumType::Type Chapter Number Type
	*/
	virtual void SetChapterNumberType(ChapterNumType::Type) = 0; 
	/**
		To set calculated Chapter Numbers
		Note: Use only when chapter Numbers are calculated from Book.
		@param chapterNumber IN calculated chapter number to set
	*/
	virtual void SetCalculatedChapterNumber(int32) = 0;

	/**
		Is document has Chapter Numbering enabled?
		@param none
		@return bool16 kTrue for enabled, kFalse for disabled.
		Note: We introduced this API according to UI spec V2
		but now we dont have option to disable chapter numbering
		(UI spec V4) and this API now returns useless/wrong data.
		We left this API as it is for keeping future changes in mind.
	*/
	virtual bool16 IsChapterNumberingEnabled() const = 0;

	/**
		Enable chapter numbering.
		@param bool16 kTrue to enable, kFalse to disable.
		Note: We introduced this API according to UI spec V2
		but now we dont have option to disable chapter numbering
		(UI spec V4) and this API now does not work.
	*/
	virtual void EnableChapterNumbering(bool16) = 0;

	/** Copy preferences from a document 
		Intended to be used with kModifyChapterNumPrefsCmdBoss
		@param document IN source document
		@see kModifyChapterNumPrefsCmdBoss
	*/
	virtual void CopyPreferencesFromDocument(IDocument *) = 0;
	
};

#endif // __IChapterNumberPreferences__
