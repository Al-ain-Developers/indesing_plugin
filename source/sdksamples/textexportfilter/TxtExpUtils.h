//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpUtils.h $
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

#ifndef __TxtExpUtils_H__
#define __TxtExpUtils_H__


// Interface includes
#include "ITxtExpFileWriter.h"
#include "IIntData.h"



/** static placeholder for the encoding IIntData pointer.
*/
//extern IIntData* fEncoding;


// some useful macros

#ifndef GETHIBYTE
#define GETHIBYTE(w) ((uchar)(((uint16)(w) >> 8) & 0xFF))
#endif

#ifndef GETLOBYTE
#define GETLOBYTE(w) ((uchar)(w) & 0xFF)
#endif

#ifndef MAKEBIGENDIANWORD
#define MAKEBIGENDIANWORD(hb, lb)	((uint16) ( ((uchar)(lb)) +  ( ((uint16)((uchar)(hb))) << 8) ) )
#endif

#ifndef SWAPWORD
#define SWAPWORD(s) MAKEBIGENDIANWORD(GETLOBYTE(s), GETHIBYTE(s))
#endif


/** TxtExpUtils
	Implements various utility functions that help in the process of
	importing text files, as featured in the TextImportFilter. 
	
	@ingroup textexportfilter
	
*/
class TxtExpUtils
{
public:
    /** Obtains the actual ITxtExpFileWriter interface for the corresponding encoding.
	    @param encoding The encoding for which you want the ITxtExpFileWriter implementation.  
			    See ITxtExpFileWriter::Encoding.
    */
    static ITxtExpFileWriter* QueryTxtExpFileWriter(ITxtExpFileWriter::Encoding encoding);

    /** Gets the IntData pointer for the encoding option so that the dialog
        and the filter could both set and get the same IntData interface.
        The code that first calls GetEncodingIntData should release it when
        all done.  (See TxtExpFilter::TxtExpFilter() and TxtExpFilter::~TxtExpFilter().)
        @param bRelease Set to kTrue if you want to release the IIntData pointer. Defaults to kFalse.
        @return Pointer to IIntData interface.
    */
    static IIntData* GetEncodingIntData(bool16 bRelease = kFalse);

	
	/** Specifies a type of katakana modifier.  
		The following sounds contain a dakuten:
			ga, gi, gu, ge, go, 
			za, zi, zu, ze, zo, 
			da, di, zu, de, do, 
			ba, bi, bu, be, bo
			vu (not very common)
		The following sounds contain a han-dakuten:
			pa, pi, pu, pe, po 
	*/
	enum Modifier
	{
		None,
		Dakuten,
		Handakuten
	};
	
	/** Constant for the hankaku column in the lookup table.
	*/
    static const int32 kHankakuColumn;
	
	/** Constant for the zenkaku column in the lookup table.
	*/
	static const int32 kZenkakuColumn;
	
	/** Constant for the number of katakana entries in the lookup table.
	*/
    static const int32 kNumKatakana;

	/** Constant that signifies that the character was not found in the lookup table.
	*/
	static const int32 kKatakanaNotFound;
	
	
	/** Converts a Hankaku (single-byte) katakana char to its 
		Zenkaku (dual-byte) counterpart. 
		@param tc Textchar containing the single-byte code for the Hankaku katakana.
        @param modifier Specifies whether the hankaku character has a modifier or not. 
				See typedef Modifier.
				If modifier is other than None, then tc's HIBYTE is ignored.
		@return Textchar containing the dual-byte code for the Zenkaku katakana.
				The tc is not found in the lookup table, this returns kTextChar_Null.
	*/
    static textchar HankakuToZenkaku(const textchar tc, 
							  const TxtExpUtils::Modifier modifier = TxtExpUtils::None);
	
	/** Converts a Zenkaku (dual-byte) katakana char to its 
		Hankaku (single-byte) counterpart. 
		@param tc Textchar containing the dual-byte code for the Zenkaku katakana.
				If the textchar has a modifier, then the high-order byte contains
				the actual modifier character. (dakuten or handakuten)
		@param modifier (return by reference) Indicates whether the returned
				textchar has a modifier.
		@return Textchar containing the single-byte code for the Hankaku katakana.
				The tc is not found in the lookup table, this returns kTextChar_Null.
	*/
	static textchar ZenkakuToHankaku(const textchar tc, 
									 TxtExpUtils::Modifier& modifier);

private:
	/** static table that stores the hankaku to zenkaku mappings in textchar type.
		Column 0 is the hankaku column, and Column 1 is the zenkaku column.
	*/
	static const textchar k_fKatakanaLookup[][2];

	/** Looks up the katakana in the lookup table.
		@param uc Textchar to find.
		@param lookAtWhichColumn Column to examine in the table. Use 
				either kHankakuColumn or kZenkakuColumn.
		@return Row index into the look up table. If uc is not found, this returns
				TxtImpUtils::kKatakanaNotFound.
	*/
	static int32 FindKatakanaIndex(const textchar uc, const int32 lookAtWhichColumn);
    
};
#endif // #ifndef __TxtExpUtils_H__


