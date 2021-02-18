//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/CWalkerScopeObserver.h $
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
#ifndef __CWalkerScopeObserver__
#define __CWalkerScopeObserver__

#include "SelectionObserver.h"
#include "ITextWalker.h"
#include "IWalkerScopeFactoryUtils.h"

#ifdef TEXTPANELLIB_BUILD
#pragma export on
#endif
//----------------------------------------------------------------------------------------
// Class CWalkerScopeObserver
//----------------------------------------------------------------------------------------

class TEXTPANELLIB_DECL CWalkerScopeObserver : public ActiveSelectionObserver
{
public:
		enum		WalkScopeIndex	{	kNoneScopeIndex, 
										kDocumentScopeIndex, 
										kAllDocumentScopeIndex,  
										kStoryScopeIndex, 
										kStoryListScopeIndex, 
										kToEndOfStoryScopeIndex, 
										kSelectionScopeIndex };
							
							CWalkerScopeObserver(IPMUnknown *boss);
		virtual				~CWalkerScopeObserver();
		
		// CTextSelectionObserver
		virtual	void		AutoAttach();
		virtual	void		AutoDetach();



protected:
		virtual	void		HandleSelectionUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);
		virtual	void		HandleSelectionChanged(const ISelectionMessage*);	

protected:
		// Other
		virtual	bool16		ApplyToFocus();

		IWalkerScopeFactoryUtils::WalkScopeType	fCurrentScope;
		

		bool16				fAttached;
		bool16				fAttachedToTextFocus;
		bool16				fAttachedToTextWalker;
		bool16				fWatchSelection;

		virtual void			NotifyObserver();
		virtual ISubject*		QuerySubject();
		virtual void			AttachToTextWalker();
		virtual void			DetachFromTextWalker();
		virtual ITextWalker *	QueryTextWalker();
		virtual bool16			UpdateWidget();
		virtual bool16			ChangeWidget();

		virtual int32			DisableItemsForScope( IWalkerScopeFactoryUtils::WalkScopeType nScope, ITextWalker *pWalker );		

		int32					ScopeToIndex( const PMString &rScopeName  ) const;
		int32					ScopeToIndex( IWalkerScopeFactoryUtils::WalkScopeType nScope ) const;
		IWalkerScopeFactoryUtils::WalkScopeType 	IndexToScope( int32 nIndex ) const;
		inline	bool16			IsMuted() const { return fMute > 0; }

		// returns listindex

private:

		friend class CWalkerScopeObserverMuter;
		void		Mute( bool16 bOn );
		int32		fMute;

	typedef		ActiveSelectionObserver	Inherited;
};
#ifdef TEXTPANELLIB_BUILD
#pragma export off
#endif

//----------------------------------------------------------------------------------------
// Class CWalkerScopeObserverMuter
//----------------------------------------------------------------------------------------

// use the CWalkerScopeObserverMuter if you call set-methods on your controldata

class TEXTPANELLIB_DECL CWalkerScopeObserverMuter
{
public:
	inline	CWalkerScopeObserverMuter( CWalkerScopeObserver *pObserver ) : fObserver( pObserver ) { pObserver->Mute( kTrue ); }
	inline	~CWalkerScopeObserverMuter() { fObserver->Mute( kFalse ); }

private:
	 CWalkerScopeObserver *fObserver;
};

#endif
