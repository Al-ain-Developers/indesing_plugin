//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/sharedcontent/IStyleMappings.h $
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
// NOTICE:  All information contained herein is, and remains
// the property of Adobe Systems Incorporated and its suppliers,
// if any.  The intellectual and technical concepts contained
// herein are proprietary to Adobe Systems Incorporated and its
// suppliers and are protected by trade secret or copyright law.
// Dissemination of this information or reproduction of this material
// is strictly forbidden unless prior written permission is obtained
// from Adobe Systems Incorporated. 
//   
//======================================================================================== 

#ifndef __IStyleMappings_h__ 
#define __IStyleMappings_h__ 

//interface includes
#include "IStyleInfo.h"

//project includes
#include "SharedContentID.h"

class IStyleMappings : public IPMUnknown
{
public:
	/**
		Standard enum to for use with GetDefaultIID() method.
	 */
	enum  { kDefaultIID = IID_ISTYLEMAPPINGS };

	/**
		Enum for specifying style type.
	 */
	enum MappingStyleType {

		/** Paragraph Style Mapping */
		kParaStyleMapping = 0,

		/** Character Style Mapping */
		kCharStyleMapping,

		/** Table Style Mapping */
		kTableStyleMapping,

		/** Cell Style Mapping */
		kCellStyleMapping,

		/** Object Style Mapping */
		kObjectStyleMapping,
	};

	/**
		Enum for specifying mapping rule type.
	 */
	enum MappingRuleType {

		/** Style To Style Mapping */
		kStyleMappingRule = 0,

		/** Group To Group Mapping */
		kGroupMappingRule,

		/** Style To Group Mapping */
		kStyleToGroupMappingRule,

		/** Group To Style Mapping */
		kGroupToStyleMappingRule,
	};

	/**
		Defines a single mapping rule of a particular style type. A mapping rule could define a "style to style", "group to group"
		"group to style", or "style to group" mapping.
	 */
	struct MappingRule {

		/** The source mapping name, it can be full path name of a style or a style group. */
		PMString fSrcString;

		/** The destination mapping name, it can be full path name of a style or a style group. */
		PMString fDestString;

		/** The source mapping name, it can be full path name of a style or a style group. */
		MappingRuleType fRuleType;

		/** Constructor to construct mapping rule from mapping data. */
		MappingRule(PMString srcString, PMString destString, MappingRuleType ruleType): fSrcString(srcString), fDestString(destString), fRuleType(ruleType) {}

		/** Constructor to construct mapping rule clone from another mapping rule. */
		MappingRule(const MappingRule &mapRule): fSrcString(mapRule.fSrcString), fDestString(mapRule.fDestString), fRuleType(mapRule.fRuleType) {}
		
		/** Default constructor */
		MappingRule(): fSrcString(PMString()), fDestString(PMString()), fRuleType(kStyleMappingRule) {}

		/** Comparison operator to compare two mapping rules corresponding to the same style type. */
		bool operator==(const MappingRule &other) const
		{
			return ((this->fSrcString == other.fSrcString) && (this->fDestString == other.fDestString) && (this->fRuleType == other.fRuleType));
		}
	};

	/** typedef for mapping rule vector corresponding to a particular style type. */
	typedef std::vector<MappingRule> MappingRuleVector;

	/**
		Replace the mapping rule vector for a particular style type, with the passed mapping rule vector.
		@param inStyleMap[IN] the style name or the style group name to validate.
		@return kTrue if the name is valid otherwise kFalse.
	 */
	virtual void				SetStyleMappings(const MappingRuleVector& inStyleMap, MappingStyleType eInMappingType) = 0;

	/**
		Returns the mapping rule vector corresponding to the given style type
		@param eInMappingType[IN] the style type for which mapping rule vector will be returned
		@param outStyleMap[IN] mapping rule vector corresponding to the style type passed.
	 */
	virtual void				GetStyleMappings(MappingStyleType eInMappingType, MappingRuleVector& outStyleMap) const = 0;

	/**
		Search the passed mapping parameters in the mapping data, if not already present at them as a mapping rule.
		@param inStrStyleName[IN] new source mapping name to set.
		@param inStrMappedTo[IN] new target mapping name to set.
		@param eInMappingRuleType[IN] new type for the mapping rule to set.
		@param eInMappingStyleType[IN] style type.
	 */
	virtual void				SetMapping(const PMString& inStrStyleName,const PMString& inStrMappedTo, MappingRuleType eInMappingRuleType, MappingStyleType eInMappingStyleType) = 0;

	/**
		Add a mapping corresponding to the passed parameters to the mapping data.
		@param inStrStyleName[IN] new source mapping name.
		@param inStrMappedTo[IN] new target mapping name.
		@param eInMappingRuleType[IN] new type for the mapping rule.
		@param eInMappingStyleType[IN] style type.
		@return previous size of the mapping rule vector before this addition occured.
	 */
	virtual int32				AddMapping(const PMString& inStrStyleName,const PMString& inStrMappedTo, MappingRuleType eInMappingRuleType, MappingStyleType eInMappingStyleType) = 0;

	/**
		Add the passed mapping rule to the mapping data.
		@param inMappingRule[IN] mapping rule to add.
		@param eInMappingStyleType[IN] style type.
	 */
	virtual void				AddMapping(MappingRule &inMappingRule, MappingStyleType eInMappingStyleType) = 0;

	/**
		Try to find a mapping rule which is applicable in mapping an input source style name. If found return the 
		target style or group name to which the input style should be mapped.
		@param inStrStyleName[IN] name of the source style to be mapped.
		@param eInMappingType[IN] style type.
		@param outStrMappedTo[IN] name of the target style or group if an applicable mapping rule was found.
		@return rule type of the applicable mapping rule found.
	 */
	virtual MappingRuleType		FindMapping(const PMString& inStrStyleName, MappingStyleType eInMappingType, PMString& outStrMappedTo) const = 0;

	/**
		Get the nth mapping rule present in the mapping rule vector corresponding to a particular style type.
		@param n[IN] position (in the mapping rule vector) of the mapping rule (mapping) we want to return.
		@param eInMappingStyleType[IN] style type to which the mapping rule, corresponds.
		@param outStrStyleName[IN] source mapping name corresponding to the nth mapping rule found.
		@param outStrMappedTo[IN] target mapping name corresponding to the nth mapping rule found.
		@return rule type of the nth mapping rule in the mapping rule vector.
	 */
	virtual MappingRuleType		GetNthMapping(int32 n, MappingStyleType eInMappingStyleType, PMString& outStrStyleName, PMString& outStrMappedTo) const = 0;

	/**
		Get the nth mapping rule present in the mapping rule vector corresponding to a particular style type.
		@param n[IN] position (in the mapping rule vector) of the mapping rule (mapping) we want to return.
		@param eInMappingStyleType[IN] style type to which the mapping rule, corresponds.
		@param outMappingRule[IN] the nth mapping rule which is being returned by this function.
		@return kTrue if nth mapping rule was found, else return kFalse.
	 */
	virtual bool16				GetNthMapping(int32 n, MappingStyleType eInMappingStyleType, MappingRule &outMappingRule) const = 0;

	/**
		Change the nth mapping rule present in the mapping rule vector corresponding to a particular style type.
		@param n[IN] position (in the mapping rule vector) of the mapping rule (mapping) we want to change.
		@param inStrStyleName[IN] new source mapping name with which we replace the old source mapping name.
		@param inStrMappedTo[IN] new target mapping name with which we replace the old target mapping name.
		@param eInMappingRuleType[IN] new type for the mapping rule.
		@param eInMappingStyleType[IN] style type to which the mapping rule being modified, corresponds.
	 */
	virtual void				SetNthMapping(int32 n, const PMString& inStrStyleName,const PMString& inStrMappedTo, MappingRuleType eInMappingRuleType, MappingStyleType eInMappingStyleType) = 0;

	/**
		Get the index or position of a mapping rule (defined by the passed on mapping data) in the mapping rule vector corresponding to a particular style type.
		@param eInMappingStyleType[IN] style type of the mapping rule.
		@param inStrStyleName[IN] the source mapping name for the mapping rule we want to find.
		@param eInMappingRuleType[IN] the type of the mapping we want to find.
		@param inStrMappedTo[IN] the target mapping name for the mapping rule we want to find.
		@return position of the mapping rule with the same mapping data as the passed parameters.
	 */
	virtual int32				GetMappingIndex(MappingStyleType eInMappingStyleType, PMString& inStrStyleName, MappingRuleType eInMappingRuleType, PMString& inStrMappedTo) const = 0;

	/**
		Get the number of style mapping rules present for a particular mapping style type.
		@param mappingStyleType[IN] style type for which we want to get number of style mapping rules.
		@return number of style mapping rules present for the given style type.
	 */
	virtual int32				GetMappingRuleVectorSize(MappingStyleType eInMappingStyleType) const = 0;

	/**
		copies-in all the style mapping data (for all style types) from the input (parameter) style mapping data.
		@param inStyleMap[IN] input style mapping data from which the data is copied to this interface.
	 */
	virtual void				CopyFrom(const IStyleMappings *inStyleMap) = 0;

	/**
		Removes (or clears) all the style mapping data for all style types.
	 */
	virtual void				ClearMappings() = 0;

	/**
		For an input style, this returns the mapping style type to which this style will correspond.
		@param styleInfo[IN] IStyleInfo interface of the style.
		@return mapping style type corresponding to the style.
	 */
	virtual MappingStyleType	GetMappingStyleType(const IStyleInfo* styleInfo) const = 0;

	/**
		Remove nth mapping rule from the style mapping data.
		@param n[IN] the index of the style mapping rule to be removed.
		@param mappingStyleType[IN] style type of the mapping rule.
		@return kTrue if there is an nth mapping rule of the given type otherwise kFalse.
	 */
	virtual bool16				RemoveMapping(int32 n, MappingStyleType mappingStyleType) = 0;
};

#endif	//__IStyleMappings_h__ 
