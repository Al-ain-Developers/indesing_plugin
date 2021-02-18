//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterConst.h $
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

#ifndef __DataUpdaterConst_h__
#define __DataUpdaterConst_h__

// General:
#include "WideString.h"

const WideString kDataUpdaterTagNamePrefix ("_DataUpdater_");
const WideString kDataUpdaterTableTag("_DataUpdater_TABLE_");
const WideString kDataUpdaterKeyTag ("_DataUpdater_RECORD_");
const WideString kDataUpdaterFieldTag ("_DataUpdater_FIELD_");
const WideString kDataUpdaterValueTag ("_DataUpdater_VALUE_");

const WideString kDataUpdaterTableNameAttribute("table");
const WideString kDataUpdaterRecordKeyAttribute ("key");
const WideString kDataUpdaterFieldNameAttribute ("field");

const WideString kWideString_DataUpdaterSeparatorSpace("_");
const WideString kWideString_DataUpdaterCarriageReturn ("\r");
const WideString kWideString_DataUpdaterNull ("");
const WideString kWideString_DataUpdaterValueNotFound("####");

// Number of zero width character added when tag text with XML 
const int32 numZWCharsAdded = 2;

// File control characters
const uchar kuchar_Separator = ',';
const uchar kuchar_CR = 0x0d;
const uchar kuchar_LF = 0x0a;

const WideString k_DataUpdatekeyString ("SKU");
const WideString k_DataUpdatepriceString ("Price");
const WideString k_DataUpdatedescriptionString ("Description");

#endif

// End, DataUpdaterConst.h


