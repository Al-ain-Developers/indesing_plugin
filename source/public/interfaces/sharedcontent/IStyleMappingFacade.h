//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/IStyleMappingFacade.h $ 
//   
//  Owner: Prakash Verma
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//
//  ADOBE CONFIDENTIAL
//   
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//	Description: 
//  A high level API for dealing with shared content links, link resources and link objects.
//   
//======================================================================================== 

#pragma once 
#ifndef __IStyleMappingFacade__ 
#define __IStyleMappingFacade__ 

// ----- Includes ----- 
#include "IPMUnknown.h" 

#include "SharedContentID.h"
#include "Utils.h" 

/** 
Interface used to manage style mappings data on document, app or story.
When possible, interaction with the style mapping data 
should be performed via the methods in this interface. 
@see IStyleMappings 
@see UID 
@see UIDRef 
*/ 
namespace Facade 
{ 

	class IStyleMappingFacade : public IPMUnknown 
	{ 
		public: 
			enum { kDefaultIID = IID_ISTYLEMAPPINGFACADE }; 

			/**
				 Adds a single mapping rule to the mapping data of the object. 
				 @param itemRef object on which style mapping data needs to be changed. The object must have IStyleMappings interface.
				 @param mappingRule [IN] the mapping rule which needs to be added to the mapping data of the objects.
				 @param styleType [IN] the type of style to which the above mapping rule corresponds.
				 @param pos [OUT] the position at which the mapping rule was added, if addition was successful, else -1.				 
				 @return kSuccess if mapping is successfully added. 
			*/
			virtual ErrorCode	AddStyleMappingRule (const UIDRef &itemRef, const IStyleMappings::MappingRule &mappingRule, const IStyleMappings::MappingStyleType &styleType, int32 &pos) const = 0;

			/**
				 Adds a single mapping rule to the mapping data of the objects passed as a list. 
				 @param itemList [IN] the list of objects on which style mapping data needs to be changed. The objects must have IStyleMappings interface.
				 @param mappingRule [IN] the mapping rule which needs to be added to the mapping data of the objects.
				 @param styleType [IN] the type of style to which the above mapping rule corresponds.
				 @return kSuccess if mapping is successfully added. 
			*/
			virtual ErrorCode	AddStyleMappingRule (const UIDList &itemList, const IStyleMappings::MappingRule &mappingRule, const IStyleMappings::MappingStyleType &styleType) const = 0;

			/**
				Changes a single mapping rule present at a specific location in the mapping data of the objects passed as a list. 
				@param itemList [IN] the list of objects on which style mapping data needs to be changed. The objects must have IStyleMappings interface.
				@param index [IN] the index of the mapping rule to modify.
				@param mappingRule [IN] the mapping rule which needs to be added to the mapping data of the objects.
				@param styleType [IN] the type of style to which the above mapping rule corresponds.
				@return kSuccess if mapping rule is successfully changed.
			*/
			virtual ErrorCode	SetStyleMappingRule (const UIDList &itemList, const int32 index, const IStyleMappings::MappingRule &mappingRule, const IStyleMappings::MappingStyleType &styleType) const = 0;


			/** 
				Changes a single mapping rule present at a specific location in the mapping data of the objects passed as a list. 
				@param itemList [IN] the list of objects on which style mapping data needs to be changed. The objects must have IStyleMappings interface.
				@param index [IN] the index of the mapping rule to modify.
				@param styleType [IN] the type of style to which the above mapping rule corresponds.
				@return kSuccess if mapping rule is successfully removed.
			 */ 
			virtual ErrorCode	RemoveStyleMappingRule(const UIDList &itemList, const int32 index, const IStyleMappings::MappingStyleType &styleType) const = 0;


			/** 
				Changes a single mapping rule present at a specific location in the mapping data of the objects passed as a list. 
				@param itemList [IN] the list of objects on which style mapping data needs to be changed. The objects must have IStyleMappings interface.
				@return kSuccess if mapping data is successfully cleared.
			 */ 
			virtual ErrorCode	ClearStyleMappings(const UIDList &itemList) const = 0;

			/** 
				Changes a single mapping rule present at a specific location in the mapping data of the objects passed as a list. 
				@param itemList [IN] the list of objects on which style mapping data needs to be changed. The objects must have IStyleMappings interface.
				@return kSuccess if mapping data is successfully cleared.
			 */ 
			virtual ErrorCode	SetStyleMappings(const UIDList &itemList, const IStyleMappings *inMappingsData) const = 0;

			/**
				 checks if the mapping style name (or style group name) is a valid for style mapping.
				 @param styleName[IN] the style name or the style group name to validate.
				 @return kTrue if the name is valid otherwise kFalse.
			 */
			virtual bool16  ValidateMappingStyleName(const PMString &styleName) const = 0;

	}; 

} // namespace Facade


#endif    // __IStyleMappingFacade__ 
