//========================================================================================
//  
//  File: WRUnicodeDatabase.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRUnicodeDatabase__
#define __WRUnicodeDatabase__

#include "WRDefines.h"

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

enum {
    kWRNameCharacterProperty,
    kWRDirectionCharacterProperty,
    kWRDirectionCharacterPropertyWinSoft,
    kWRDecompositionTypeCharacterProperty,
    kWRDecompositionCharacterProperty,
    kWRUppercaseCharacterProperty,
    kWRLowercaseCharacterProperty,
    kWRTitlecaseCharacterProperty,
    kWRMirrorCharacterProperty,
    kWRCursivityCharacterProperty,
	kWRClassCharacterProperty,
	kWRScriptCharacterProperty,
	kWRAllDecompositionsCharacterProperty,
	kWRGraphemeClusterBreakProperty,
	kWRUnicodePropertyCount
};

enum {
	kWRUTF32CharSize = 0,
	kWRUTF16CharSize = 1
};

enum 
{
	WRUCSGraphemeClusterBreak_Other,
	WRUCSGraphemeClusterBreak_CR,
	WRUCSGraphemeClusterBreak_LF,
	WRUCSGraphemeClusterBreak_Control,
	WRUCSGraphemeClusterBreak_Extend,
	WRUCSGraphemeClusterBreak_Prepend,
	WRUCSGraphemeClusterBreak_SpacingMark,
	WRUCSGraphemeClusterBreak_Hangul_L,
	WRUCSGraphemeClusterBreak_Hangul_V,
	WRUCSGraphemeClusterBreak_Hangul_T,
	WRUCSGraphemeClusterBreak_Hangul_LV,
	WRUCSGraphemeClusterBreak_Hangul_LVT,

	WRUCSGraphemeClusterBreak_sot,
	WRUCSGraphemeClusterBreak_eot,
	WRUCSGraphemeClusterBreak_ignore,

	WRUCSGraphemeClusterBreak_Indic_I,
	WRUCSGraphemeClusterBreak_Indic_C,
	WRUCSGraphemeClusterBreak_Indic_N,
	WRUCSGraphemeClusterBreak_Indic_H,
	WRUCSGraphemeClusterBreak_Indic_J,
	WRUCSGraphemeClusterBreak_Indic_NJ,
	WRUCSGraphemeClusterBreak_Indic_M,
	WRUCSGraphemeClusterBreak_Indic_VM,
	WRUCSGraphemeClusterBreak_Indic_SM,
	WRUCSGraphemeClusterBreak_Indic_LM

};

typedef unsigned short WRUCSGraphemeClusterBreak;

typedef unsigned short WRCharacterPropertySelector;

#define WRUDMakeCharacterPropertySelector(charSize, propertyBase) ((((WRCharacterPropertySelector)charSize)<<8) | (((WRCharacterPropertySelector)propertyBase)))

#define WRUDGetCharacterPropertySelectorBase(property) ((WRCharacterPropertySelector)(property & 0xFF))

#define WRUDGetCharacterPropertySelectorCharSize(property) ((WRCharacterPropertySelector)((property >> 8) & 0xFF))

WRError WRUDInitialize();

WRSERVICES_DECL WRError WRUDGetCharacterProperty(
	WRUnichar32                	i_unicode,
	WRCharacterPropertySelector i_propertySelector,
	void*                       o_propertyBuffer,
	WRByteCount*                io_propertyBufferSize,
	WRLanguageID				langID);
/*
Return value:				Result of the function
							Possible return values:
							kWRErr_noError
							kWRErr_bufferTooSmall: Nothing is written to output buffer-increase the size and try again
							kWRErr_unknownCharacter: No entry exists for this. character-returned value is a default

i_unicode:					A Unicode character

i_propertySelector        	Specifies what kind of information is requested

o_propertyBuffer			The rutine output. The size and format of the buffer 
							is determined by the i_propertySelector value
							pass NULL for charcking the needed size to allocate

io_propertyBufferSize:    	On input: 	The size of o_propertyBuffer in bytes
							On output: 	The actual size of the property
										NOTE: For string values io_propertyBufferSize will be the length of the string
										WITHOUT the null terminator, therefore you must allocate an addition 1 or 2 bytes for the null terminator.


            kWRNameCharacterProperty
            	Value: C string
            	Buffer size: Variable. io_propertyBufferSize will return the size of the string without the null terminator
				The NameCharacterProperty is now returned as index into the gUnicodeNamesStringPool[]
				If the client needs to use the real kWRNameCharacterProperty string, he must do this:
					- Link the client application against WRUnicodeNames.h
					- Write a code like the following:
					{
						WRUnichar32 c = myChar;
						char s[256] = "";
						WRInt32 sz = 255;

						WRUDGetCharacterProperty(c, kWRNameCharacterProperty, s, &sz);

						if (sz)
						{
							int nameIndex = -1;

							sscanf(s, "%d", &nameIndex);
							if (nameIndex > 0 && nameIndex < kUnicodeNamesStringPoolSize)
								strcpy(s, gUnicodeNamesStringPool + nameIndex);
						}
					}


            kWRDirectionCharacterProperty
            	Value: WRUCSDirection (Matching exactly Unicode standard)
            	Buffer size sizeof(WRUCSDirection);
				This property must be choosen if WRDSResolveDirections() is called with the i_algorithm parameter set to a value different from kWRDSAlgorithmUnicode24

            kWRDirectionCharacterPropertyWinSoft
            	Value: WRUCSDirection (Matching Unicode standard but with some WinSoft exceptions)
            	Buffer size sizeof(WRUCSDirection);
				This property must be choosen if WRDSResolveDirections() is called with the i_algorithm parameter set to kWRDSAlgorithmUnicode24

            kWRDecompositionTypeCharacterProperty
            	Value: WRCharacterDecompostionMapping
            	Buffer size: sizeof(WRCharacterDecompostionMapping)

            kWRDecompositionCharacterProperty
            	Value: Unicode C String (Null terminated string of WRUnichar32)
            	Buffer size: Variable. io_propertyBufferSize will return the size of the string without the null terminator

            kWRUppercaseCharacterProperty
            	Value: Unicode C String (Null terminated string of WRUnichar32)
            	Buffer size: Variable. io_propertyBufferSize will return the size of the string without the null terminator

            kWRLowercaseCharacterProperty
            	Value: Unicode C String (Null terminated string of WRUnichar32)
            	Buffer size: Variable. io_propertyBufferSize will return the size of the string without the null terminator

            kWRMirrorCharacterProperty
            	Value: WRUnichar32
            	Buffer Size: sizeof(WRUnichar32)

            kWRCursivityCharacterProperty
            	Value: WRUnichar32[4]
            	Buffer Size: sizeof(WRUnichar32) * 5 (1 for trailing)

            kWRClassCharacterProperty
            	Value: WRUnichar32
            	Buffer Size: sizeof(WROTGlyphClassValue)

			kWRScriptCharacterProperty
				Value: WRScriptID
				Buffer Size: sozeof(WRScriptID)

            kWRAllDecompositionsCharacterProperty
            	Value: Unicode C String (Null terminated string of WRUnichar32), ecompositions separated by u0001
            	Buffer size: Variable. io_propertyBufferSize will return the size of the string without the null terminator

			kWRGraphemeClusterBreakProperty
            	Value: WRUCSGraphemeClusterBreak (Matching exactly Unicode standard)
            	Buffer size sizeof(WRUCSGraphemeClusterBreak);


*/

WRSERVICES_DECL WRError WRUDGetCharacterProperty(
		WRUnichar32                	i_unicode,
		WRCharacterPropertySelector i_propertySelector,
		void*                       o_propertyBuffer,
		WRByteCount*                io_propertyBufferSize);
/*Same as above function WRUDGetCharacterProperty. Kept just to avoid API mismatch for older products. */

#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif /* __WRUnicodeDatabase__ */
