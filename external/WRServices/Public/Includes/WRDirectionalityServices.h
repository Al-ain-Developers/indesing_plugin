//========================================================================================
//  
//  File: WRDirectionalityServices.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRDirectionalityServices__
#define __WRDirectionalityServices__

#include "WRConfig.h"
#include "WRDefines.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

typedef enum {
	kWRDSParagraphDirectionMask=1,
	kWRDSContextualMainDirMask=2,
	kWRDSContextualHindiDigitsMask=4,
	kWRDSProcessingLineMask=8
} WRDSOptionsMask;

typedef enum {
	kWRDSAlgorithmWinSoftHead,
	kWRDSAlgorithmUnicodeHead,
	kWRDSAlgorithmWinSoftID2,
	kWRDSAlgorithmWinSoftCS1,
	kWRDSAlgorithmWinSoftCS2,
	kWRDSAlgorithmUnicode24,
	kWRDSAlgorithmFirst = kWRDSAlgorithmWinSoftHead,
	kWRDSAlgorithmLast = kWRDSAlgorithmUnicode24
}WRDSAlgorithm;


typedef WRUInt32 WRDSOptions;

/* 
WRDSResolveDirections 
*/
WRSERVICES_DECL void	WRDSResolveDirections(	const WRDSOptions 		i_options,
												const WRUCSDirection* 	i_input,
												WREmbeddingLevelPtr		o_levels,
												WRUCSDirection*			o_directions,
												const WRCount			i_count,
												const WRLanguageID*		i_languages = NULL,
												const WRDSAlgorithm		i_algorithm = kWRDSAlgorithmUnicode24);
/*
	i_options:				Set kWRDSParagraphDirectionMask to 1 if paragraph direction is right to left
							0 if left to right
							
	i_input:				Pointer to an array of WRUCSDirection
							The client must supply the the direction categories.
							
							
	o_levels:				Pass an array of size i_count
							On output, the resolved levels of the input
							// You can pass this array directly to WRDSReorder.
	
	o_directions:			Pass an array of size i_count
							On Output, the resolved directions of the input
							Possible values are: kWRdirL, kWRdirR, kWRdirAN, kWRdirEN
							Note that input direction kWRdirEN can be converted into kWRdirAN
							According to the unicode rules... You may or may not respect that.
							
							
	i_count:				Number of input and output elements

	i_languages:			optional array of language IDs, for resolving some neutral directions in the
							way expected in the locale
							i_languages is ignored if i_algorithm parameter value is kWRDSAlgorithmWinSoftID2 or kWRDSAlgorithmUnicode24

	i_algorithm:			optional algorithm to use (see kWRDSAlgorithmXXX)
							if no parameter specified, kWRDSAlgorithmUnicode24 is used
							CAUTION: this parameter value must be choosen in conjonction with the direction property selector when calling
							WRUDGetCharacterProperty():
								i_algorithm = kWRDSAlgorithmUnicode24
										WRUDGetCharacterProperty(kWRDirectionCharacterProperty)
								i_algorithm = kWRDSAlgorithmWinSoftID2
								i_algorithm = kWRDSAlgorithmWinSoftCS1,
								i_algorithm = kWRDSAlgorithmWinSoftCS2,
										WRUDGetCharacterProperty(kWRDirectionCharacterPropertyWinSoft)
*/



WRSERVICES_DECL void	WRDSReorder (	const WREmbeddingLevelPtr	i_levels,
										WROffsetPtr					o_indexs,
										const WRCount				i_count);
						
/*
	i_levels:				Resolved embedding levels
	o_indexs:				On output, will contain the indexes of the elements in i_levels
							as they should appear in visual order (left to right)
	i_count:				Number of i_levels and o_indexs
	
*/

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif /* WRDirectionalityServices */
