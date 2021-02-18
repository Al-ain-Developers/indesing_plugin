//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectButtonObservers.h $
//  
//  Owner: Heath Horton
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
#ifndef _H_AutoCorrectButtonObserver
#define _H_AutoCorrectButtonObserver

#include "AutoCorrectPanelObserver.h"

#include "K2Vector.h"
#include "PMString.h"

class ISubject;
class AutoCorrectList;

//----------------------------------------------------------------------------------------
// Class AutoCorrectListObserver
//----------------------------------------------------------------------------------------

class CAutoCorrectButtonObserver : public AutoCorrectPanelObserver
{
public:
						CAutoCorrectButtonObserver(IPMUnknown *boss);

	virtual	void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	// AutoCorrectPanelObserver: override 
	virtual	bool16		ApplyToWidget();
	virtual	bool16		ApplyToFocus();

	virtual	bool16		SetupWidget();
	
	//virtual bool16	GetAutoCorrectListWords(K2Vector<KeyValuePair<WideString, WideString>>& autoStringPair, LanguageID languageID);

	virtual void		NotifyObserver( ClassID nMsg );

protected:
			ISubject *	QueryTreeViewSubject();
};

class AutoCorrectAddButtonObserver : public CAutoCorrectButtonObserver
{
public:
					AutoCorrectAddButtonObserver(IPMUnknown *boss);

	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual	bool16		ApplyToWidget();
	virtual	bool16		ApplyToFocus();

	virtual	bool16		SetupWidget();

	virtual bool16		GetAddingWordMode()	{ return kTrue; }

protected:
	bool16	AddOrEditStandardAutoCorrections(WideString& misspelledWide,  WideString& correctedWide, LanguageID languageID);
	bool16	AddOrEditEntry();
};

class AutoCorrectEditButtonObserver : public AutoCorrectAddButtonObserver
{
public:
						AutoCorrectEditButtonObserver(IPMUnknown *boss);

	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual	bool16		SetupWidget();

	virtual void		AutoAttach();
	virtual void		AutoDetach();

	virtual bool16		GetAddingWordMode()	{ return kFalse; }
};

class AutoCorrectRemoveButtonObserver : public CAutoCorrectButtonObserver
{
public:
						AutoCorrectRemoveButtonObserver(IPMUnknown *boss);
	
	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual	bool16		ApplyToWidget();
	virtual	bool16		ApplyToFocus();

	virtual	bool16		SetupWidget();

	virtual void		AutoAttach();
	virtual void		AutoDetach();

protected:
	bool16		RemoveStandardAutoCorrections(const AutoCorrectItem& autoCorrectItem);
	bool16		RemoveEntries();
};

class AutoCorrectCheckBoxObserver : public AutoCorrectPanelObserver
{
public:
					AutoCorrectCheckBoxObserver(IPMUnknown *boss);
	
	virtual	bool16	ApplyToWidget();
	virtual	bool16	ApplyToFocus();

	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
	virtual void		AutoAttach();
	virtual void		AutoDetach();

};

class AutoCorrectCapCheckBoxObserver : public AutoCorrectPanelObserver
{
public:
					AutoCorrectCapCheckBoxObserver(IPMUnknown *boss);

	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual	bool16	ApplyToWidget();
	virtual	bool16	ApplyToFocus();

	virtual	bool16		SetupWidget();

	virtual void		AutoAttach();
	virtual void		AutoDetach();

protected:
};


#endif //_H_AutoCorrectListObserver