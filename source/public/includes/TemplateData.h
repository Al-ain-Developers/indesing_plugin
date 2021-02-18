//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TemplateData.h $
//  
//  Owner: rich gartland
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
//  Class to implement template field data for Knowledge
//  base Interface.
//  
//========================================================================================

#pragma once
#ifndef __TEMPLATEDATA
#define __TEMPLATEDATA


#include "PMTypes.h"
#include "PMString.h"
#include "K2Vector.h"
#include "K2Vector.h"

#ifdef PUBLIC_BUILD
#pragma export on
#endif

typedef enum { fldInt, fldDouble, fldString } fldType;

/**	FOR INTERNAL USE ONLY.
	A glue class used by implementations of IRuleable for conveying field data from the KnowledgeBase 
	plug-in to the Eclipse knowledge base subsystem.
*/
class PUBLIC_DECL FieldData {
	public:
		FieldData();
		FieldData(int32 intvalue);
		FieldData(double doublevalue);
		FieldData(const PMString& stringvalue);
		~FieldData();
		void SetName(ConstCString fname);
		std::string fieldName;
		fldType	fieldType;
		int32	anInt;
		double	aDouble;
		PMString *aString;	
};

/**	FOR INTERNAL USE ONLY.
	A glue class used by implementations of IRuleable for conveying template data from the KnowledgeBase 
	plug-in to the Eclipse knowledge base subsystem.
*/
class PUBLIC_DECL TemplateData {
	public:
		TemplateData();
		~TemplateData();
		TemplateData(ConstCString tname);

		void SetName(ConstCString tname);
		const char* GetName() { return fTemplateName.c_str(); };

		int32 GetNumFields() { return static_cast<int32>(fFieldList.size()); };
		void SetIDIndex(int16 idindex) { fIDIndex = idindex; };
		int16 GetIDIndex() { return fIDIndex; };
		FieldData* MakeField(int16 index);
		
		void SetField(int16 index, ConstCString fname, int32 value, bool16 isID = kFalse);
		void SetField(int16 index, ConstCString fname, double value, bool16 isID = kFalse);
		void SetField(int16 index, ConstCString fname, PMString& value, bool16 isID = kFalse);

		void GetField(int16 index, int32 *value) { *value = fFieldList[index]->anInt; };
		void GetField(int16 index, double *value) { *value = fFieldList[index]->aDouble; };
		void GetField(int16 index, PMString& value) { value = *(fFieldList[index]->aString); };
		fldType GetFieldType(int16 index) { return fFieldList[index]->fieldType; };
		const std::string GetFieldName(int16 index) { return fFieldList[index]->fieldName; };

	private:
		std::string fTemplateName;
		int16		 fIDIndex;
		K2Vector<FieldData*> fFieldList;
};

#pragma export off


#endif	// __TEMPLATEDATA
