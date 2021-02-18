//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/CTargetServer.h $
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
#ifndef __CTargetServer__
#define __CTargetServer__

#include "SelectionObserver.h"

class ITextTargetAttributes;
class ITextAttributeSuite;



//----------------------------------------------------------------------------------------
// Class CTargetServer
//----------------------------------------------------------------------------------------
#ifdef TEXTPANELLIB_BUILD
#pragma export on
#endif

	#define TARGETSERVERBASE ActiveSelectionObserver

class TEXTPANELLIB_DECL CTargetServer : public TARGETSERVERBASE
{
public:
		enum SelectionAttributeStatus {
										kUnInitialized		= -1,
										kHasAttributes,
										kDoesntHaveAttributes
									 };
									 
					CTargetServer(IPMUnknown *boss, PMIID targetServerIID );
		virtual		~CTargetServer();

		// IObserver
		virtual void	AutoAttach();
		virtual void 	AutoDetach();
		virtual void	Update(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy);
		
		// CTargetServer: override 
		virtual	bool16	SetupWidget();
				// called at the first time for setting up the Widget

		virtual	void	Mute( bool16 bOn );
				// if mute is set update will return without any actions.
		virtual	bool16	IsMuted() const;


		// pure virtual methods:
		
		virtual	ITextTargetAttributes *		CreateTarget( IPMUnknown *pModelTarget ) const = 0;
		virtual	IPMUnknown *		QueryModelTarget() = 0;
		virtual	PMIID			GetTargetServerIID() const = 0;		// i.e. IID_ITEXTTARGETSERVER
		virtual	PMIID			GetWorkspaceIID() const = 0;			// i.e. IID_ITEXTATTRIBUTES
		virtual	PMIID			GetObserverIID() const = 0;			// i.e. IID_ITEXTTARGETOBSERVER
		
		// Selection Observer
		virtual void HandleActiveSelectionChanged (void);
		virtual void HandleSelectionAttributeChanged(const ISelectionMessage*);
		virtual void HandleSelectionChanged (const ISelectionMessage*);
		
		virtual void TextAttributesChanged( ITextAttributeSuite* attributes );

protected:
		bool16		fAttached;

		// The CTargetServer can have different targets:
		// (1) TextSelection => read/write from/to TextFocus
		// (2) selected pageitem => disable the widget
		// (3) open doc, nothing is selected =>  read/write from/to the document workspace
		// (4) no doc =>  read/write from/to the application workspace
		virtual	bool16 EnableWidget();
				// enables and reactivates the widget. Called by ChangeToNoSelection().
		virtual	bool16 DisableWidget();
				// disables and deactivates the widget. Called by ChangeToMultipleSelection() and ChangeToOneSelection().
		virtual	void			OnDocumentChange();
				// callback

		void				Notify( ClassID nClass, void *pTarget = nil );
		virtual ITextTargetAttributes *CreateTheTarget( CTargetServer *pServer );

		bool16	IsPreviewOn();

private:
		bool16						fEnabled;
		uint32						fMute;
		SelectionAttributeStatus	fAttributeStatus;
};

#ifdef TEXTPANELLIB_BUILD
#pragma export off
#endif

//----------------------------------------------------------------------------------------
// Class TargetServerMuter
//----------------------------------------------------------------------------------------

// use the TargetServerMuter if you call set-methods on your controldata

class TEXTPANELLIB_DECL TargetServerMuter
{
public:
	inline	TargetServerMuter( CTargetServer *pObserver ) : fObserver( pObserver ) { pObserver->Mute( kTrue ); }
	inline	~TargetServerMuter() { fObserver->Mute( kFalse ); }

private:
	 CTargetServer *fObserver;
};

#endif
