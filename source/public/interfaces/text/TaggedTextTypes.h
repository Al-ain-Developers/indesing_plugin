//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/TaggedTextTypes.h $
//  
//  Owner:
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
#ifndef __TaggedTextTypes__
#define __TaggedTextTypes__

//Excluded by Manoj Gupta
//#include "TaggedTextBuildNumber.h"
#include "BaseType.h"

//Encoding to be used while exporting/importing the tagged text file
//Used by the following
//TaggedTextExportFilter prefernces UI, in TaggedTextExportFilter plugin
//TaggedTextExportFilter, in TaggedTextExportFilter plugin
//TaggedText Parser, in TaggedTextImportFilter plugin

typedef enum {
	kEncodingUnknown  = 0x00,
	kEncodingAscii    = 0x01,
	kEncodingShiftJis = 0x02,
	kEncodingBig5     = 0x03,
	kEncodingUnicode  = 0x04,
	kEncodingAnsi	  = 0x05,
	kEncodingCGB18030 = 0x06, // manojg CGB18030 - enum for CGB18030 Encoding
	kEncodingKSC5601  = 0x07 // manojg KSC5601 - enum for KSC5601 Encoding
	,kEncodingCE = 0x08
	,kEncodingCyrillic= 0x09
	,kEncodingGreek= 0x0A
	,kEncodingArabic = 0x0B
	,kEncodingHebrew = 0x0C
} EncodingType;

const int kMaxNumEncoding = 13;

//Platform type on which the Tagged text file was created
typedef enum {
	kPlatformInvalid = 0x00,
	kPlatformMac = 0x01,
	kPlatformWin = 0x02,
	kPlatformAll = 0x03
} PlatformType;

//TagName form to be used while exporting the tagged file
//Used by the following
//TaggedTextExportFilter Preferences UI, in TaggedTextExportFilter plugin
//TaggedTextExportFilter, in TaggedTextExportFilter plugin
typedef enum {
	kVerbose = 0,
	kAbbr
} TagNameForm;

//Whether or not to display the warnings or errors while importing the TXT file
//Used by the following
//TaggedTextImportFilter Preferences UI, in TaggedTextImportFilter plugin
//TaggedTextImporter, in TaggedTextImportFilter plugin
typedef enum {
	kNoSuppressWarnings = 0,
	kSuppressAllWarnings
}SuppressWarning;

//Action to be taken when the style def in tagged text file conflicts with the publication style
//Used by the following
//TaggedTextImportFilter Preferences UI, in TaggedTextImportFilter plugin
//TaggedTextImporter, in TaggedTextImportFilter plugin
typedef enum {
	kApplyPubStyle = 0x00,
	kApplyTaggedTextStyle = 0x01
} StyleConflictAction;

#define kParaRootStyleName	"[No paragraph style]"
#define kCharRootStyleName	"[No character style]"
#define kTableRootStyleName "[No table style]"
#define kCellRootStyleName  "[None]"

const textchar kEndOfParagraphChar = 0x0d;
const textchar kLineBreakChar = 0x0a;

const char kTaggedTextDupStyleNameSuffix[] = "-";

#endif
