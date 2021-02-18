//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ExceptionHyphenWord.h $
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
#ifndef __ExceptionHyphenWord__
#define __ExceptionHyphenWord__

#include "IHyphenatedWord.h"

#include "TextChar.h"

class WideString;

#define HY_NORM		0x04	
#define HY_PREF		0x05	
#define HY_UNPREF	0x06	


/** 	
	Stores information about the hyphenation points within a particular word.

	@ingroup text_hyphen
*/
class ExceptionHyphenWord : public IHyphenatedWord
{
public:
						/** 	
							Constructor. pWord and pPoints will be copied.
						*/
						ExceptionHyphenWord(	const WideString& 	word,
												const HyphenPoints& points,  
												const int32 		nMinTail, 
												const int32 		nMinHead );
						~ExceptionHyphenWord();
						
	/** 
		How many hyphenation points?
		
		@return the count of hyphenation points that has been found. 
	*/
	virtual	int32		GetPointCount() const;
	/** 
		The index is the position before the hyphen: i.e. ser-vice returns 2 (zero-based).
		
		@param nNthPoint is which point to ask about.
		
		@return the index in the word of the Nth hyphenation point.	
	*/
	virtual	int32		GetIndexOfPoint( int32  nNthPoint ) const;
	/** 
		The quality value of the Nth hyphenation point.
		
		@param nNthPoint is which point to ask about.
		
		@return the quality in the word of the Nth hyphenation point.
	*/
	virtual	int32		GetQualityOfPoint( int32 nNthPoint ) const;
	
	/** 
		Copies the word (might be different because the linguisitc systems do their own character translations).
		
		@return a WideString version of the word being hyphenated. 
	*/
	virtual	WideString	GetWord() const;
	/** 
		Fills the WideStrings without hyphen, i.e.: "service" to "ser" and "vice". Will do spelling changes
		but doesn't add the hyphen (if it wasn't already there).
		
		@param nNthPoint is which break point.
		@param pFirstPart is a pointer (not nil) to a blank WideString, is filled out with the pre-break point part.
		@param pLastPart is a pointer (not nil) to a blank WideString, is filled out with the post-break point part.
	*/
	virtual	void		GetPartsOfPoint( int32 nNthPoint, WideString *pFirstPart, WideString *pLastPart ) const;
	/** 
		Fills the WideString without hyphen, i.e.: "service" to "ser". Will do spelling changes
		but doesn't add the hyphen (if it wasn't already there).
		
		@param nNthPoint is which break point.
		@param pPart is a pointer (not nil) to a blank WideString, is filled out with the pre-break point part.
	*/
	virtual	void		GetFirstPartOfPoint( int32 nNthPoint, WideString *pPart ) const;
	/** 
		Fills the WideString, i.e.: "service" to "vice". Can do spelling changes.
		
		@param nNthPoint is which break point.
		@param pPart is a pointer (not nil) to a blank WideString, is filled out with the post-break point part.
	*/
	virtual	void		GetLastPartOfPoint( int32 nNthPoint, WideString *pPart ) const;
	/** 
		Merge 2 lists of break points. Used to combine dictionary breakpoints with other types of breaking
		Used only for to combine hard dash breaking since Discretionary hyphens always take precidence.
		
		@param pToMergeWith is another hyphenated word to merge into this one.
	*/
	virtual	void		Merge( const IHyphenatedWord *pToMergeWith );
	/** 
		after merging, this routine is called as a post-method clean up 
	*/
	virtual	void		ValidatePointRanges(void);

protected:
		HyphenPoints 	fPoints;
		WideString		fWord;
			
private:
	/** 
		Untility function which removed invalid hyphenation points with specified  minimum head and tail.

		@param nMinTail	minimum tail for hyphenation points.
		@param nMinHead	minimum head for hyphenation points.
	*/
	void		InitTailHead(int32 nMinTail, int32 nMinHead);
	/** 
		Untility function which checks if the specified character is seperator character.

		@param c	Character to check for.

		@return bool16	kTrue if the character is a seperator character.
	*/
	static inline 	bool16 		IsWordSeparatorChar(textchar c)
			{	switch (c)
					{
					case kTextChar_NoBreakHyphen:
						return kFalse;
					case kTextChar_Ellipse:
					case kTextChar_Solidus:
					case kTextChar_ReverseSolidus:
					case kTextChar_Underscore:
						return kTrue;
					default:
						break;
					}
				return UnicodeClass::IsPunctuationDash(c);
			}
 };

#endif
