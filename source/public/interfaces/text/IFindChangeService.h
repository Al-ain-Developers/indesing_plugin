//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFindChangeService.h $
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
#ifndef __IFindChangeService__
#define __IFindChangeService__

#ifndef __IPMUnknown__
#include "IPMUnknown.h"
#endif

#include "ITextWalker.h"
#include "WideString.h"

class IUIDRefListData;

/** 
	@ingroup text_find
*/
class IFindChangeService : public IPMUnknown
{
public:
	enum FindChangeResult { kFailure, kSuccess, kNotFound, kFoundCompleted, kReplaceAllCompleted };

	/**
		if a text item is found it returns kSuccess and the corresponding text position in start and end
		if a text item is not found it returns kNotFound.  Start and end equal kInvalidTextIndex
		if the search is completed and at least one item was found, it returns kFoundCompleted.  Start and end equal kInvalidTextIndex.
		if the search fails due to error condition, it returns kFailure.  Start and end equal kInvalidTextIndex.
	
		@param	start	OUT found start position.
		@param	end		OUT found end position.
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult SearchText(TextIndex& start, TextIndex& end) = 0;

	/**
		if a text item is replaced successfully, it returns kSuccess and the corresponding text position in start and end
		if the replacement fails due to error conditions, it returns kFailure.  Start and end equal kInvalidTextIndex.
	
		@param	start
		@param	end
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult ReplaceText(TextIndex& start, TextIndex& end) = 0;

	/**
		if both replace and search are successful, it returns kSuccess and the corresponding text position in start and end
		if replace is successful but no more text item is found, it returns kFoundCompleted.  Start and end equal kInvalidTextIndex
		if replace and search fail due to error conditions, it returns kFailure.  Start and end equal kInvalidTextIndex.
	
		@param	start
		@param	end
		@return	FindChangeResult
	*/
	virtual FindChangeResult ReplaceAndSearchText(TextIndex& start, TextIndex& end) = 0;

	/**
		ReplaceAllText
	
		@param	replaceCount	OUT if replace all is successful, it returns kReplaceAllCompleted and the total replacement count in replaceCount field
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult ReplaceAllText(int32* replaceCount) = 0;

	/**
		if a font is found it returns kSuccess and the corresponding text position in start and end. if a text item is not found it returns kNotFound.  Start and end equal kInvalidTextIndex
		if the search is completed and at least one item was found, it returns kFoundCompleted.	Start and end equal kInvalidTextIndex.
		if the search fails due to error condition, it returns kFailure.  Start and end equal kInvalidTextIndex.
	
		@param	doc
		@param	start
		@param	end
		@param	fontUID
		@param	fontStyleName
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult SearchForFont(const UIDRef& doc, TextIndex& start, TextIndex &end, UID fontUID, const PMString& fontStyleName) = 0;

	/**
		if a text item is replaced successfully, it returns kSuccess and the corresponding text position in start and end
		if the replacement fails due to error conditions, it returns kFailure.  Start and end equal kInvalidTextIndex.
	
		@param	start	OUT start position.
		@param	end		OUT end position.
		@param	newFontUID		new font UID to replace with
		@param	newFontStyleName	new font style to replace with
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult ReplaceFont(TextIndex& start, TextIndex &end, UID newFontUID, const PMString& newFontStyleName) = 0;
	
	/**
		replace all fonts with new font
	
		@param	replaceCount	OUT total replacement count
		@param	findFontUID		font family UID to find
		@param	findFontStyleName	font style to find
		@param	newFontUID		new font UID to replace found UID with
		@param	newFontStyleName	new font style to replace found style with
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult ReplaceAllFont(int32* replaceCount, UID findFontUID, const PMString& findFontStyleName, UID newFontUID, const PMString& newFontStyleName) = 0;
	
	/**
		Halt walker if walking 
	
	*/
	virtual void Halt() = 0;

	/**
		search for an object

		@param	foundObject		OUT found object.
		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return	FindChangeResult	returns kFailure if error
	 */
	virtual FindChangeResult SearchObject(UIDRef& foundObject,bool16 initializeWalker = kFalse) = 0 ;
	
	/**
		Replaces the found object's attributes with the target attributes

		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult	returns kFailure if error
	 */
	virtual FindChangeResult ReplaceObject(bool16 initializeWalker = kFalse) = 0;

	/**
		Replaces the found object's attributes with the target attributes and searches next object

		@param nextMatch		OUT next matched object.
		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult
	 */
	virtual FindChangeResult ReplaceAndSearchObject(UIDRef& nextMatch,bool16 initializeWalker = kFalse) = 0;

	/**
		Replaces all found object's attributes with target attributes

		@param foundCount		OUT gives number of objects found
		@param fullyChangedCount OUT gives number of objects fully changed as per change criteria
		@param partiallyChangedCount OUT gives number of objects partially changed as per change criteria

		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult
	 */
	virtual FindChangeResult ReplaceAllObject(int32* foundCount,int32* fullyChangedCount,int32* partiallyChangedCount,bool16 initializeWalker = kFalse) = 0;

	/**
		replace all fonts with new font
	
		@param	doc					document to to replace
		@param	replaceCount		OUT total replacement count
		@param	findFontUID			font family UID to find
		@param	findFontStyleName	font style to find
		@param	newFontUID			new font UID to replace found UID with
		@param	newFontStyleName	new font style to replace found style with
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual FindChangeResult ReplaceAllFont(const UIDRef& doc, int32* replaceCount, UID findFontUID, const PMString& findFontStyleName, UID newFontUID, const PMString& newFontStyleName) = 0;
	

	/**
		Search for a color attribute

		@param	selectedPropertyName		OUT found attribute name.
		@param  numberOfPropertiesFound		OUT no of properties found.
		@param  initializeWalker IN kFalse if you want to re-initialize the walker and kFalse if you want to use as is
		@return	FindChangeResult	returns kFailure if error
	*/
	virtual IFindChangeService::FindChangeResult SearchColor(PMString& selectedPropertyName, int32& numberOfPropertiesFound, bool16 initializeWalker = kFalse) = 0;

	/**
		Replaces the found object's color attributes with the target attributes

		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult	returns kFailure if error
	 */
	virtual IFindChangeService::FindChangeResult ReplaceColor(bool16 initializeWalker = kFalse) = 0;

	/**
		Replaces all found object's color attributes with target attributes

		@param foundCount		OUT gives number of objects found
		@param fullyChangedCount OUT gives number of objects fully changed as per change criteria
		@param partiallyChangedCount OUT gives number of objects partially changed as per change criteria
		@param uidRefListData	OUT gives uidRef of linked assets which can't be changed
		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult
	*/
	virtual IFindChangeService::FindChangeResult ReplaceAllColor(int32* foundCount, int32* fullyChangedCount, int32* partiallyChangedCount, IUIDRefListData* uidRefListData, bool16 initializeWalker = kFalse) = 0;

	/**
		Replaces the found object's color attributes with the target attributes and searches next color attribute

		@param	selectedPropertyName		OUT found attribute name.
		@param  numberOfPropertiesFound		OUT no of properties found.
		@param  initializeWalker IN kTrue if you want to re-initialize the walker and kFalse if you want to use as is
		@return FindChangeResult
	*/
	virtual IFindChangeService::FindChangeResult ReplaceAndSearchColor(PMString& selectedPropertyName, int32& numberOfPropertiesFound, bool16 initializeWalker = kFalse) = 0;

};

#endif
