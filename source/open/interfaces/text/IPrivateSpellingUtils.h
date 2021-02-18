//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IPrivateSpellingUtils.h $
//  
//  Owner: hhorton
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
#ifndef _H_IPrivateSpellingUtils
#define _H_IPrivateSpellingUtils

#include "SpellPanelID.h"
#include "IPMUnknown.h"
#include "Utils.h"
#include "ISpellingService.h"

class UndoInfo;
class ILinguisticMgr;
class IHyphenationExceptions;
class ILanguage;
class IComposeScanner;
class IControlView;
class IUserDictService;
class ILanguage;
class IPMUnknown;
class IUserDict;
class UserDictWordList;
class IDocument;

typedef enum { kAddToDict = 0, kRemoveFromDict, kIgnoreDict } DictAction;

class IPrivateSpellingUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPRIVATESPELLINGUTILS };

	virtual void InvalTextRange(IControlView* view, ITextModel* textModel, TextIndex startIndex, TextIndex endIndex) = 0;

	virtual void DeleteCacheAndInvalDocWindows(IDocument* doc, bool16 recheckAll) = 0;	/* all windows for a single document */
	virtual void DeleteCacheAndInvalAllDocWindows(bool16 recheckAll) = 0;	/* all windows for all documents */

	virtual bool16 ModifyDictionary(const PMString& originalWord, 
									DictAction action,
									bool16 bCaseSensitive,
									IPMUnknown* target,
									ILanguage* pLanguage,
									const UserDictWordList& udStrList) = 0;
	
};

#endif /* _H_IPrivateSpellingUtils */

