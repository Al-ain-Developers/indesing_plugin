//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeFormatData.h $
//  
//  Owner: Wai Cheuk
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

#pragma once
#ifndef __IFindChangeFormatData__
#define __IFindChangeFormatData__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

#include "TextWalkerServiceProviderID.h"
#include "IFindChangeOptions.h"

class AttributeBossList;
class PMString;

/** 
	@ingroup text_find
*/
class IFindChangeFormatData : public IPMUnknown
{
public:
	/**
	Standard enum to for use with GetDefaultIID() method.
	 */
	enum { kDefaultIID = IID_IFINDCHANGEFORMATDATA };

	/** 
	Enum specifying whether the format data is for find dialog or for change dialog 
	 */
	enum	FindChangeFormatDataType		
	{ 
		/** Find Dialog */
		kFindDialogType = 0,
		/** Change Dialog */
		kChangeDialogType 
	};

	/**
	Gets the dialog type for which this format data is being supplied
	@return is of type IFindChangeFormatData::FindChangeFormatDataType
	@see IFindChangeFormatData::FindChangeFormatDataType
	@see IFindChangeFormatData::SetDialogType
	 */
	virtual FindChangeFormatDataType GetDialogType() = 0;

	/**
	Sets the dialog type for which this format data is being supplied
	@param type is of type IFindChangeFormatData::FindChangeFormatDataType
	@see IFindChangeFormatData::FindChangeFormatDataType
	@see IFindChangeFormatData::GetDialogType
	 */
	virtual void SetDialogType(FindChangeFormatDataType type) = 0;

	/**
	Gets the data base of find/change attributes that are being specified
	@return is a pointer to IDataBase interface
	@see IFindChangeFormatData::SetTargetDB
	 */
	virtual IDataBase* GetTargetDB() = 0;

	/**
	Gets the attributes that will be searched for
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is a pointer to AttributeBossList
	@see IFindChangeFormatData::SetFindAttrsToApply
	 */
	virtual const AttributeBossList* GetFindAttrsToApply(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the character style that will be searched for
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is character style's UID
	@see IFindChangeFormatData::SetFindCharStyle
	 */
	virtual const UID& GetFindCharStyle(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the paragraph style that will be searched for
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is paragraph style's UID
	@see IFindChangeFormatData::SetFindParaStyle
	 */
	virtual const UID& GetFindParaStyle(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the object style that will be searched for
	@return is object style's UID
	@see IFindChangeFormatData::SetFindParaStyle
	 */
	virtual const UID& GetObjectFindStyle() = 0;

	/**
	Sets the database of find/change attributes
	@param db is a pointer to IDataBase interface
	 */
	virtual void SetTargetDB(IDataBase *db) = 0;

	/**
	Sets the attributes for which we will search for
	@param findList is a pointer to AttributeBossList
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetFindAttrsToApply
	 */
	virtual void SetFindAttrsToApply(const AttributeBossList* findList,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the UID of character style to be searched for
	@param styleName is of type UID
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetFindCharStyle
	 */
	virtual void SetFindCharStyle(const UID& styleName,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the UID of paragraph style to be searched for
	@param styleName is of type UID
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetFindParaStyle
	 */
	virtual void SetFindParaStyle(const UID& styleName,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the UID of object style to be searched for
	@param styleName is of type UID
	@see IFindChangeFormatData::GetObjectFindStyle
	 */
	virtual void SetObjectFindStyle(const UID& styleName) = 0;

	/**
	Clears the attributes for which we will search for
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearFindAttrsToApply(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the attributes which will be applied on found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is a pointer to AttributeBossList
	@see IFindChangeFormatData::SetChangeAttrsToApply
	 */
	virtual const AttributeBossList* GetChangeAttrsToApply(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the character style to be applied on found text
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is of type UID specifying character style's UID
	@see IFindChangeFormatData::SetChangeCharStyle
	 */
	virtual const UID& GetChangeCharStyle(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the paragraph style to be applied on found text
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is of type UID specifying paragraph style's UID
	@see IFindChangeFormatData::SetChangeParaStyle
	 */
	virtual const UID& GetChangeParaStyle(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the object style to be applied on found object
	@return is of type UID specifying object style's UID
	@see IFindChangeFormatData::SetObjectStyle
	 */
	virtual const UID& GetObjectChangeStyle() = 0;

	/**
	Sets attributes that will be applied on found text/object
	@param changeList is a pointer to AttributeBossList
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetChangeAttrsToApply
	 */
	virtual void SetChangeAttrsToApply(const AttributeBossList* changeList,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the character style that will be applied on found text
	@param styleName is UID of the character style
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetChangeCharStyle
	 */
	virtual void SetChangeCharStyle(const UID& styleName,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the paragraph style that will be applied on found text
	@param styleName is UID of the paragraph style
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetChangeParaStyle
	 */
	virtual void SetChangeParaStyle(const UID& styleName,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Sets the object style that will be applied on found object
	@param styleName is UID of the object style
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetObjectChangeStyle
	 */
	virtual void SetObjectChangeStyle(const UID& styleName) = 0;

	/**
	Clears the attributes which will be applied on found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	 */
	virtual void ClearChangeAttrsToApply(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the XML tag that will be applied on found text/object
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return is of type PMString
	@see IFindChangeFormatData::SetChangeXMLTag
	 */
    virtual const PMString& GetChangeXMLTag(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) =0;

	/**
	Sets the XML tag that will be applied on found text/object
	@param tagName is of type PMString specifying XML Tag
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::GetChangeXMLTag
	 */
	virtual void SetChangeXMLTag(const PMString& tagName,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;

	/**
	Gets the change conditions mode that will be applied to found text
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::SearchMode
	@return IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeFormatData::SetChangeConditionsMode
	 */
    virtual IFindChangeOptions::ChangeConditionsMode GetChangeConditionsMode(IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) =0;

	/**
	Sets the change conditions mode that will be applied to found text
	@param chgConditionsMode is of type IFindChangeOptions::ChangeConditionsMode  specifying the mode for change conditions
	@param mode is of type IFindChangeOptions::SearchMode specifying the mode of Find/Change
	@see IFindChangeOptions::ChangeConditionsMode
	@see IFindChangeOptions::SearchMode
	@see IFindChangeFormatData::SetChangeConditionsMode
	 */
	virtual void SetChangeConditionsMode(IFindChangeOptions::ChangeConditionsMode chgConditionsMode,IFindChangeOptions::SearchMode mode = IFindChangeOptions::kTextSearch) = 0;
};

#endif
