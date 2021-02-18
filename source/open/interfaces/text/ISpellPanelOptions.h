//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/ISpellPanelOptions.h $
//  
//  Owner: Bernd Paradies 
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
#ifndef __ISpellPanelOptions__
#define __ISpellPanelOptions__

#include "IPMUnknown.h"
#include "ITextWalker.h"
#include "PMString.h"
#include "IWalkerScopeFactoryUtils.h"
#include "SpellPanelID.h"

//---------------------------------------------------------------
// Interface ISpellPanelOptions
//---------------------------------------------------------------

class ISpellPanelOptions : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ISPELLPANELOPTIONS};

	virtual bool16 					GetOverset() const = 0;
	virtual void 					SetOverset(bool16 bOverset) = 0;

	virtual IWalkerScopeFactoryUtils::WalkScopeType 	GetFindChangeScope() const = 0;
	virtual void 					SetFindChangeScope(IWalkerScopeFactoryUtils::WalkScopeType nScope) = 0;

	virtual bool16					IsIgnored( const PMString &rIgnore ) const = 0;
	virtual bool16					AddToIgnoreList( const PMString &rIgnore ) = 0;
	virtual bool16					RemoveFromIgnoreList( const PMString &rIgnore ) = 0;
	virtual bool16					ClearIgnoreList() = 0;
	virtual int32					GetIgnoredCount() const = 0;
	virtual const PMString &		GetNthIgnored( int32 nIndex ) const = 0;

	virtual bool16					CopyFrom( const ISpellPanelOptions *pFrom ) = 0;

	virtual bool16					GetCaseSensitive() const = 0;
	virtual void					SetCaseSensitive(bool16 bCaseSensitive) = 0;
};


#endif
