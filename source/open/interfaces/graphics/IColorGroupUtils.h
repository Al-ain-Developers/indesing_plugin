//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/graphics/IColorGroupUtils.h $
// 
//  Owner: Ankur Gupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once 
#ifndef __IColorGroupUtils__ 
#define __IColorGroupUtils__ 

class IColorGroupList;
#include "Utils.h"
#include "PMString.h"

/**    Helper class to facilitate processing of unique color group names. 
*/ 
class ColorGroupUtilsUniqueNameTempCache 
{ 
public: 
    ColorGroupUtilsUniqueNameTempCache(): 
        bBaseNameExists(0), 
        bInitializedIndices(0) {} 

public: 
    K2Vector<int32> vecIndices; 
    bool16          bBaseNameExists; 
    bool16          bInitializedIndices; 
}; 



class IColorGroupUtils : public IPMUnknown 
{ 
    public: 
        enum    {kDefaultIID = IID_ICOLORGROUPUTILS};

		/** Get a unique color group name starting with "baseName". If the baseName is already unique, this 
			is returned. 
			@param iColorGroupList the color group list in which the name should be unique. 
			@param baseName the base name to start with. 
			@param suffixString the string to append to baseName if not empty. 
			@param doAppendSuffix if set to kTrue, then suffixString is appended. 
			@param doTruncateNumber if set to kTrue, the existing number appended to baseName will be removed first. 
			@param pCache if you are calling GenerateUniqueColorGroupName many times repeatedly for the same 
			   base name, this will act as a cache and significantly improve performance.  If nil, it is ignored. 
			@return a unique color group name within the specified color group list. 
		*/
		virtual PMString GenerateUniqueColorGroupName
			( 
			IColorGroupList*    iColorGroupList, 
			PMString& baseName, 
			const PMString& suffixString = "", 
			bool16            doAppendSuffix = kTrue, 
			bool16            doTruncateNumber = kTrue,
			ColorGroupUtilsUniqueNameTempCache* pCache = nil 
			) = 0;	

		/** Query for the color group list of the given database. 
			@param iDataBase the database to use 
			@return a IColorGroupList* associated with the iDataBase. 
			@see IColorGroupList 
		*/
		virtual IColorGroupList* QueryColorGroupList(IDataBase* iDataBase) = 0;

		/** Query for the current active color group list in the specified context. If the context is nil, the current active 
			context is used. 
			@param context the active context to use. 
			@return a IColorGroupList* associated with the context. 
			@see IColorGroupList 
		*/ 
		virtual IColorGroupList* QueryActiveColorGroupList(IActiveContext* context = nil) = 0;

		/** Check if input is a color group in color group list of given input element database
			@param uidRef of element to check
			@return kTrue if element is color group otherwise kFalse.  
		*/ 
		virtual bool16 IsColorGroup(const UIDRef& uidRef) =0;
}; 
     
#endif // __IColorGroupUtils__ 

