//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/TextWalkerObserver.h $
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
#ifndef __TextWalkerObserver__
#define __TextWalkerObserver__

#include "SelectionObserver.h"
#include "ITextWalker.h"
#include "TextPanelID.h"
#include "IWalkerScopeFactoryUtils.h"

class WideString;
class ITextFocus;

#ifdef TEXTPANELLIB_BUILD
#pragma export on
#endif

//----------------------------------------------------------------------------------------
// Class TextWalkerObserver
//----------------------------------------------------------------------------------------

class TEXTPANELLIB_DECL TextWalkerObserver : public ActiveSelectionObserver
{
public:
						TextWalkerObserver(IPMUnknown *boss);
		virtual ~TextWalkerObserver();
		
		// CObserver: override 
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();

		virtual	void		HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);


		virtual	ISubject *		QueryPanelSubject();
		virtual	void			Mute( bool16 bOn );
		virtual	bool16			IsMuted() const;

		// you have to override DoWalkAndResumeCommand()
		virtual void			DoWalkAndResumeCommand() = 0;

protected:
		virtual void	Notify( ClassID nClass, void *pChangeBy = nil );
		virtual void	NotifyDoHalt();
		virtual void	WalkAndCheck();

		virtual void	DoHalt( bool16 bDeselect );
		
		// member
		bool16					fAttached;
		int32					fMute;

		bool16					fWrap;
		bool16					fOverset;
		bool16					fAttachedToTextFocus;
};



//----------------------------------------------------------------------------------------
// Class TextWalkerObserverMuter
//----------------------------------------------------------------------------------------

// use the TextWalkerObserverMuter if you call set-methods on your controldata

class TEXTPANELLIB_DECL TextWalkerObserverMuter
{
public:
	inline	TextWalkerObserverMuter( TextWalkerObserver *pObserver ) : fObserver( pObserver ) { pObserver->Mute( kTrue ); }
	inline	~TextWalkerObserverMuter() { fObserver->Mute( kFalse ); }

private:
	 TextWalkerObserver *fObserver;
};

#ifdef TEXTPANELLIB_BUILD
#pragma export off
#endif

#endif

