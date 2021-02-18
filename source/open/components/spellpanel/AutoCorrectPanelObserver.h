//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectPanelObserver.h $
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
#ifndef _H_AutoCorrectPanelObserver
#define _H_AutoCorrectPanelObserver

#include "CObserver.h"

class ISubject;
class IUserDictService;
class AutoCorrectList;

class AutoCorrectPanelObserverData : public CObserver
{
public:
	AutoCorrectPanelObserverData( IPMUnknown *boss );

    void		SetControlID( const PMIID& nID ) { ASSERT_MSG(nID != IID_IUNKNOWN,"Can't use control ID of IID_IUNKNOWN"); fControlID = nID; }
    PMIID		GetControlID() const { return fControlID; }

    void		SetReset( bool16 bOn ) { fReset = bOn; }
    bool16		IsReset() const { return fReset; }

    void		SetMessageID( const ClassID &rMsg ) { fMessageID = rMsg; }
    ClassID		GetMessageID() const { return fMessageID; }

protected:
    PMIID		fControlID;
    bool16		fReset;
    ClassID		fMessageID;
};

class AutoCorrectPanelObserver : public AutoCorrectPanelObserverData
{
public:
	AutoCorrectPanelObserver(IPMUnknown *boss);
	
	virtual void				AutoAttach();
	virtual void 				AutoDetach();

	virtual	void				Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	virtual	bool16				ApplyToWidget();
	virtual	bool16				ApplyToFocus();

	virtual	bool16				SetupWidget();

	virtual	void				Mute( bool16 bOn );		// if mute is set update will return without any actions.
	virtual	bool16				IsMuted() const;
	
protected:
    bool16        fInUpdate;
    bool16        fAttached;
    bool16        fInApplyToWidget;
    uint32        fMute;

	ILanguage*			QueryLanguage();
	ISubject*			QueryPanelSubject();
	IUserDictService*	QueryUserDictService();

private:
	bool16				DoApplyToFocus();
};

//----------------------------------------------------------------------------------------
// Class AutoCorrectPanelObserverMuter
//----------------------------------------------------------------------------------------

// use the AutoCorrectPanelObserverMuter if you call set-methods on your controldata

class AutoCorrectPanelObserverMuter
{
public:
    inline    AutoCorrectPanelObserverMuter( AutoCorrectPanelObserver *pObserver ) : fObserver( pObserver ) { pObserver->Mute( kTrue ); }
    inline    ~AutoCorrectPanelObserverMuter() { fObserver->Mute( kFalse ); }

private:
     AutoCorrectPanelObserver *fObserver;
};


#endif //_H_AutoCorrectPanelObserver