//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/server/sampleclient/SoapClientUtils.h $
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
//========================================================================================

#ifndef SoapClientUtils_H
#define SoapClientUtils_H

#include "soapH.h"
using namespace std;

void ShowAny(const IDSP__Data* dataHolder);

void ShowAsBool(const IDSP__Data* dataHolder);
void ShowAsDouble(const IDSP__Data* dataHolder);
void ShowAsFloat(const IDSP__Data* dataHolder);
void ShowAsInt(const IDSP__Data* dataHolder);
void ShowAsLong(const IDSP__Data* dataHolder);
void ShowAsString(const IDSP__Data* dataHolder);

void ShowAsIdspEnumeration(const IDSP__Data* dataHolder);
void ShowAsIdspList(const IDSP__Data* dataHolder);
void ShowAsIdspObject(const IDSP__Data* dataHolder);
void ShowAsIdspObject(const IDSP__Object* dataHolder);
void ShowAsIdspObjectList(const IDSP__Data* dataHolder);
void ShowAsIdspRecord(const IDSP__Data* dataHolder);
void ShowAsIdspUnit(const IDSP__Data* dataHolder);

void ShowAsStdString(const IDSP__Data* dataHolder);

void ShowAsXsdBoolean(const IDSP__Data* dataHolder);
void ShowAsXsdDateTime(const IDSP__Data* dataHolder);
void ShowAsXsdDouble(const IDSP__Data* dataHolder);
void ShowAsXsdFloat(const IDSP__Data* dataHolder);
void ShowAsXsdInt(const IDSP__Data* dataHolder);
void ShowAsXsdAnyUri(const IDSP__Data* dataHolder);

std::string unsigned_long_to_string(unsigned long valueToConvert);

#endif //SoapClientUtils_H
