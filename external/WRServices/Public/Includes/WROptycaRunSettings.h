//========================================================================================
//  
//  File: WROptycaRunSettings.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2010 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WROPTYCARUNSETTINGS__
#define __WROPTYCARUNSETTINGS__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"

/// opaque type for representing the stylistic attributes set ona character (interpreted thru OptycaStyleClientControl)
typedef void* StyleRef;

/// numbering of an actual font resulting from the optyca internal font substitution
/**
The optyca internal font subtitution reports which font must be used for rendering in this way:
@li 0: nominal font of the style
@li 1: complementary font of the style, as defined by the IWRFontAccess::GetComplementaryFont (which in turn often calls IWRFontInfo)
@li -1: Roman fallback
@li -N-1: fallback for the script N
**/
typedef char WRComplementaryIndex;

/// core run attributes
/**
This structure gathers the most common attributes associated with a strike run
**/
struct OptycaRunSettings
{
	StyleRef				style;			///< style 
	WREmbeddingLevel		level;			///< resolved direction (even for LTR, odd of RTL)
	WRScriptID				script;			///< run script 
	WRLanguageID			language;		///< run language
	WRFloat					scaling;		///< 1.0 = 100%, nominal size
	WRComplementaryIndex	complementary;	///< number of the actual font resulting from the optyca internal font substitution
};


#endif
