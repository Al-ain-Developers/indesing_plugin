//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelObserver.h $
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
#ifndef __SpellPanelObserver__
#define __SpellPanelObserver__

#include "CObserver.h"

class IWorkspace;
class PMString;
class ITextWalker;
class IStringData;
class ILinguisticMgr;
class ISpellPanelOptions;
class ILanguage;
class IDocument;
class IDocumentLayer;
class ISpread;
class IUserDictService;

//----------------------------------------------------------------------------------------
// Class SpellPanelObserverData
//----------------------------------------------------------------------------------------

class SpellPanelObserverData : public CObserver
{
public:
						SpellPanelObserverData( IPMUnknown *boss );

		inline	void		SetControlID( const PMIID& nID ) { fControlID = nID; }
		inline	PMIID	GetControlID() const { return fControlID; }

		inline	void		SetReset( bool16 bOn ) { fReset = bOn; }
		inline	bool16	IsReset() const { return fReset; }

protected:
		PMIID				fControlID;
		bool16				fReset;
};

//----------------------------------------------------------------------------------------
// Class SpellPanelObserver
//----------------------------------------------------------------------------------------

class SpellPanelObserver : public SpellPanelObserverData
{
public:
				SpellPanelObserver(IPMUnknown *boss);
	virtual		~SpellPanelObserver();

	// IObserver
	virtual void	AutoAttach();
	virtual void 	AutoDetach();
	virtual void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);

	// SpellPanelObserver: override 
	virtual	bool16	SetupWidget();// called at the first time for setting up the Widget

	virtual	bool16	ApplyToWidget();
			// called when the widget has to be updated. If you override it take care
			// of different attributes in the selection and call ApplyAttrToWidget().
			
	virtual	bool16	ApplyToFocus();	// called when the attribute has to be applied to the selection

	virtual	ISubject*	QueryPanelSubject() const;	// returns the ISubject interface of the panel
	
	virtual IUserDictService* QueryUserDictService(void);

	virtual	bool16	ApplyToPreferences();	// called when the user has entered a new value without TextFocus

	virtual	void	Mute( bool16 bOn );	// if mute is set update will return without any actions.

	virtual	bool16	IsMuted() const;
			
			// only supported for Bool/TriState controls
			bool16	IsControlSelected() const;
			void		DeselectControl();

	


protected:
	bool16		fInUpdate;
	bool16		fAttached;
	bool16		fInApplyToWidget;
	uint32		fMute;
	
	void			AutoAttachToTextWalker();
	void			AutoDetachFromTextWalker();
	ITextWalker* QuerySessionWalker();
	ITextWalker *		QueryTextWalker();
	IStringData *		QueryWordToSpell();
	ILinguisticMgr *	QueryLinguisticMgr();
	ILanguage *		QueryCurrentLanguage();
	ISpellPanelOptions*	QuerySpellPanelOptions();

	IPMUnknown	*		GetTarget();
	void				SetTarget(IPMUnknown* target);

	const PMString &	GetUserCorrectedWord() const;
		
private:
	bool16		DoApplyToFocus();
	bool16		DoApplyToWidget();
	
	ITextWalker *	QueryPanelTextWalker();
	ITextWalker *	QuerySessionTextWalker();		
};

//----------------------------------------------------------------------------------------
// Class SpellPanelObserverMuter
//----------------------------------------------------------------------------------------

// use the SpellPanelObserverMuter if you call set-methods on your controldata

class SpellPanelObserverMuter
{
public:
	inline	SpellPanelObserverMuter( SpellPanelObserver *pObserver ) : fObserver( pObserver ) { pObserver->Mute( kTrue ); }
	inline	~SpellPanelObserverMuter() { fObserver->Mute( kFalse ); }

private:
	 SpellPanelObserver *fObserver;
};

#endif
