//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IOtherFindChangeOptionData.h $
//  
//  Owner: lance bushore
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
//  Purpose:
//  Data interface for storing Attribute Boss List.
//  
//========================================================================================

#pragma once
#ifndef __IOtherFindChangeOptionData__
#define __IOtherFindChangeOptionData__

#include "IPMUnknown.h"
#include "FontUsageDialogID.h"
#include "ITextWalker.h"
#include "WideString.h"
#include "IWalkerScopeFactoryUtils.h"
#include "IFindChangeOptions.h"

/** 
	@ingroup text_font
	@ingroup text_find
*/
class IOtherFindChangeOptionData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IOTHERFINDCHANGEOPTIONDATA };

	/**	
		Sets other find change option data.

		@param caseSensitive		Used to set case sencitive flag.
		@param word				Used to set entire word flag.
		@param scope			Used to set walk scope type.
		@param find				Used to set find string.
		@param replace			Used to set replace string.
		@param widthSensitive		Used to set width sensitive flag.
		@param kanaSensitive		Used to set Kana sensitive flag.
		@param changeMode		Used to set change mode.
		@param findCharacterType	Used to set find character type.
		@param replaceCharacterType	Used to set replace character type.
	 */
	virtual void SetData(bool16 caseSensitive, bool16 word, IWalkerScopeFactoryUtils::WalkScopeType scope, 
						const WideString& find, const WideString& replace, 
						bool16 widthSensitive,
						bool16 kanaSensitive,
						IFindChangeOptions::ChangeMode	changeMode,
						IFindChangeOptions::CharacterType findCharacterType,
						IFindChangeOptions::CharacterType replaceCharacterType) = 0;

	/**	
		Gets case sensitive flag.

		@return bool16	kTrue if case sensitive, kFalse otherwise.
	 */
	virtual bool16 GetCase() const=0;
	/**	
		Gets entire word flag.

		@return bool16	kTrue if entire word, kFalse otherwise.
	 */
	virtual bool16 GetEntireWord() const=0;
	/**	
		Gets walk scope type.

		@return IWalkerScopeFactoryUtils::WalkScopeType	walk scope type.
	 */
	virtual IWalkerScopeFactoryUtils::WalkScopeType GetScope() const=0;
	/**	
		Gets find string.

		@return WideString		Find string retrieved.
	 */
	virtual WideString GetFindString() const=0;
	/**	
		Gets replace string.

		@return WideString		Replace string retrieved.
	 */
	virtual WideString GetReplaceString() const=0;
	/**	
		Gets width sensitive flag.

		@return bool16	kTrue if width sensitive, kFalse otherwise.
	 */
	virtual	bool16 GetWidthSensitive () const = 0;
	/**	
		Gets Kana sensitive flag.

		@return bool16	kTrue if Kana sensitive, kFalse otherwise.
	 */
	virtual	bool16 GetKanaSensitive () const = 0;
	/**	
		Gets change mode.

		@return IFindChangeOptions::ChangeMode change mode retrieved.
	 */
	virtual	IFindChangeOptions::ChangeMode	GetChangeMode () const = 0;
	/**	
		Gets find character type.

		@return IFindChangeOptions::CharacterType Find character type retrieved.
	 */
	virtual	IFindChangeOptions::CharacterType GetFindCharacterType () const = 0;
	/**	
		Gets replace character type.

		@return IFindChangeOptions::CharacterType Replace character type retrieved.
	 */
	virtual	IFindChangeOptions::CharacterType GetReplaceCharacterType () const = 0;
};


#endif // __IOtherFindChangeOptionData__
