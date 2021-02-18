//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/incopy/INoteFindChangeSpelling.h $
//  
//  Owner: Duane Krause
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
#ifndef __INoteFindChangeSpelling__
#define __INoteFindChangeSpelling__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

//========================================================================================
class INoteFindChangeSpelling : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INOTEFINDCHANGESPELLING };
	enum {
		kNoSkipTables			= 0,
		kSkipTablesFromFindChanges	= 1,
		kSkipTablesFromSpelling = 2
	};

	enum ScopeWidgetToUpdate {
		kInvalidScopeWidget = -1,
		kFindChangeScopeWidget	= 0,
		kSpellingScopeWidget = 1
	};

	// show skip table warning
	virtual void			SetStartFindChanges(bool val) = 0;
	virtual void			SetStartSpelling(bool val) = 0;
	virtual bool			GetStartFindChanges() = 0;
	virtual bool			GetStartSpelling() = 0;

	virtual void			SetStartFindChangesAll(bool val) = 0;
	virtual void			SetStartSpellingAll(bool val) = 0;
	virtual bool			GetStartFindChangesAll() = 0;
	virtual bool			GetStartSpellingAll() = 0;

	virtual void			SetFindChangesWarningSkipTables(bool val)	= 0;
	virtual void			SetSpellingWarningSkipTables(bool val)	= 0;
	virtual bool			GetFindChangesWarningSkipTables() = 0;
	virtual bool			GetSpellingWarningSkipTables() = 0;
	
	virtual void			SetCancelSkipTables(bool val) = 0;
	virtual bool			GetCancelSkipTables() = 0;

	virtual void				SetScopeWidgetToUpdate(ScopeWidgetToUpdate widget) = 0;
	virtual ScopeWidgetToUpdate	GetScopeWidgetToUpdate() = 0;
};

//========================================================================================
#endif // __INoteFindChangeSpelling__