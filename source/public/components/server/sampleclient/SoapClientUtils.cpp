//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/components/server/sampleclient/SoapClientUtils.cpp $
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

#include "SoapClientUtils.h"

void ShowAny(const IDSP__Data* dataHolder)
	{
	switch (dataHolder->__type)
		{
		case SOAP_TYPE_bool:
			{
			ShowAsBool(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__boolean:
			{
			ShowAsXsdBoolean(dataHolder);
			break;
			}

		case SOAP_TYPE_string:
			{
			ShowAsString(dataHolder);
			break;
			}
			
		case SOAP_TYPE_std__string:
			{
			ShowAsStdString(dataHolder);
			break;
			}

		case SOAP_TYPE_int:
			{
			ShowAsInt(dataHolder);
			break;
			}

		case SOAP_TYPE_long:
			{
			ShowAsLong(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__int:
			{
			ShowAsXsdInt(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__Enumeration:
			{
			ShowAsIdspEnumeration(dataHolder);
			break;
			}

		case SOAP_TYPE_float:
			{
			ShowAsFloat(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__float:
			{
			ShowAsXsdFloat(dataHolder);
			break;
			}

		case SOAP_TYPE_double:
			{
			ShowAsDouble(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__double:
			{
			ShowAsXsdDouble(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__Unit:
			{
			ShowAsIdspUnit(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__Object:
			{
			ShowAsIdspObject(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__ObjectList:
			{
			ShowAsIdspObjectList(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__List:
			{
			ShowAsIdspList(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__dateTime:
			{
			ShowAsXsdDateTime(dataHolder);
			break;
			}

		case SOAP_TYPE_xsd__anyURI:
			{
			ShowAsXsdAnyUri(dataHolder);
			break;
			}

		case SOAP_TYPE_IDSP__Record:
			{
			ShowAsIdspRecord(dataHolder);
			break;
			}
			
		default:
			{
			cout << ": Script reported no errors." << std::endl;
			break;
			}
		}
	}

void ShowAsBool(const IDSP__Data* dataHolder)
	{
	cout << " (bool): "
			<< (*((bool*) dataHolder->data) ? "true" : "false")
			<< std::endl;
	}

void ShowAsDouble(const IDSP__Data* dataHolder)
	{
	cout << " (double): "
			<< *((double*) dataHolder->data)
			<< std::endl;
	}

void ShowAsFloat(const IDSP__Data* dataHolder)
	{
	cout << " (float): "
			<< *((float*) dataHolder->data)
			<< std::endl;
	}

void ShowAsInt(const IDSP__Data* dataHolder)
	{
	cout << " (int): "
			<< *((int*) dataHolder->data)
			<< std::endl;
	}

void ShowAsLong(const IDSP__Data* dataHolder)
	{
	cout << " (long): "
			<< *((long*) dataHolder->data)
			<< std::endl;
	}

void ShowAsString(const IDSP__Data* dataHolder)
	{
	cout << " (string): "
			<< (char*) dataHolder->data
			<< std::endl;
	}

void ShowAsIdspEnumeration(const IDSP__Data* dataHolder)
	{
	cout << " (enum): "
			<< *((long*) dataHolder->data)
			<< std::endl;
	}

void ShowAsIdspList(const IDSP__Data* dataHolder)
	{
	IDSP__List* pDataList = (IDSP__List*) dataHolder->data;
	int cData(pDataList->__size);
	cout << " (LIST, " << cData << "):" << std::endl;
	IDSP__Data* memberHolder = pDataList->__ptr;
	if (!memberHolder)
		{
		cout << " No members of list." << std::endl;
		return;
		}

	int n(0);
	for (n = 0; n < cData; n++)
		{
		ShowAny(&memberHolder[n]);
		}
	}

void ShowAsIdspObject(const IDSP__Data* dataHolder)
	{
	IDSP__Object* pObject = (IDSP__Object*) dataHolder->data;
	if (pObject)
		{
		ShowAsIdspObject(pObject);
		}
	else
		{
		cout << "No object."  << std::endl;
		}
	}

void ShowAsIdspObject(const IDSP__Object* object)
	{
	string sObjectType(unsigned_long_to_string(object->objectType));
	cout << " (object): "
			<< "\'" << sObjectType << "\'"
			<< std::endl;
	}

void ShowAsIdspObjectList(const IDSP__Data* dataHolder)
	{
	IDSP__ObjectList* pObjectList = (IDSP__ObjectList*) dataHolder->data;
	int cObjects(pObjectList->__size);
	cout << " (OBJECT LIST, " << cObjects << "):" << std::endl;
	IDSP__Object* memberHolder = pObjectList->__ptr;
	if (!memberHolder)
		{
		cout << " No members of list." << std::endl;
		return;
		}

	int n(0);
	for (n = 0; n < cObjects; n++)
		{
		IDSP__Object* member = &memberHolder[n];
		if (member)
			{
			ShowAsIdspObject(member);
			}
		else
			{
			cout << " No object." << std::endl;
			}
		}
	}

void ShowAsIdspRecord(const IDSP__Data* dataHolder)
	{
	IDSP__Record* pRecord = (IDSP__Record*) dataHolder->data;
	int cFields(pRecord->__size);
	cout << " (record, " << cFields << "):" << std::endl;
	IDSP__Field* memberHolder = pRecord->__ptr;
	if (!memberHolder)
		{
		cout << " No members of record." << std::endl;
		return;
		}

	int n(0);
	for (n = 0; n < cFields; n++)
		{
		ShowAny(memberHolder[n].data);
		}
	}

void ShowAsIdspUnit(const IDSP__Data* dataHolder)
	{
	cout << " (unit): "
			<< *((double*) dataHolder->data)
			<< std::endl;
	}

void ShowAsStdString(const IDSP__Data* dataHolder)
	{
	cout << " (std__string): "
			<< *((string*)dataHolder->data)
			<< std::endl;
	}

void ShowAsXsdAnyUri(const IDSP__Data* dataHolder)
	{
	cout << " (anyURI): "
			<< (char*) dataHolder->data
			<< std::endl;
	}

void ShowAsXsdBoolean(const IDSP__Data* dataHolder)
	{
	cout << " (xsd__boolean): "
			<< (*((bool*) dataHolder->data) ? "true" : "false")
			<< std::endl;
	}

void ShowAsXsdDateTime(const IDSP__Data* dataHolder)
	{
	cout << " (dateTime): "
			<< (char*) dataHolder->data
			<< std::endl;
	}

void ShowAsXsdDouble(const IDSP__Data* dataHolder)
	{
	cout << " (xsd__double): "
			<< *((double*) dataHolder->data)
			<< std::endl;
	}

void ShowAsXsdFloat(const IDSP__Data* dataHolder)
	{
	cout << " (xsd__float): "
			<< *((float*) dataHolder->data)
			<< std::endl;
	}

void ShowAsXsdInt(const IDSP__Data* dataHolder)
	{
	cout << " (xsd__int): "
			<< *((long*) dataHolder->data)
			<< std::endl;
	}

string unsigned_long_to_string(unsigned long valueToConvert)
	{
	char converted[] = {'\0', '\0', '\0', '\0', '\0'};
	unsigned long mask(0x000000FF);
	int n(0);
	for (n = 3; n >= 0; n--)
		{
		converted[n] = char(valueToConvert & mask);
		valueToConvert >>= 8;
		}

	return(string(converted));
	}
