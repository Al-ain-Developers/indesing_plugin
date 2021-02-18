//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SelectionExtTemplates.tpp $
//  
//  Owner: Michael Martz
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
//  Note:		
//  
//========================================================================================

	#ifndef _SelectionExtention_Templates_
	#define _SelectionExtention_Templates_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "ISelectionExtension.h"						// Superclass declaration
	#include "CPMUnknown.h"
	#include "ISelectionManager.h"
//================================================================================================
//________________________________________________________________________________________________
//	TEMPLATE DECLARATION
//________________________________________________________________________________________________
template <class AssociatedSuite>
class SelectionExt : public CPMUnknown<ISelectionExtension>
	{
	public:	
							 		SelectionExt						(IPMUnknown* = nil);

		virtual void				Startup			 					(void);
		virtual void				Shutdown			 				(void);
		virtual void				SelectionChanged 					(SuiteBroadcastData*, const PMIID&, void*);
		virtual void				SelectionAttributeChanged 			(SuiteBroadcastData*, const PMIID&, void*);
		virtual void				HandleIntegratorSuiteMessage		(void*, const ClassID&, ISubject*, const PMIID&, void*, ISelectionManager*);
		virtual ProtocolCollection*	CreateObserverProtocolCollection 	(void);

		typedef CPMUnknown<ISelectionExtension> Inherited;
	};

//________________________________________________________________________________________________
//	TEMPLATE FUNCTIONS
//________________________________________________________________________________________________
//________________________________________________________________________________________________
//	DESCR:		Constructor.
//________________________________________________________________________________________________
template <class AssociatedSuite>
SelectionExt<AssociatedSuite>::SelectionExt (IPMUnknown* iBoss) : Inherited (iBoss)
	{
	}

//________________________________________________________________________________________
//	DESC:		Start up
//________________________________________________________________________________________
template <class AssociatedSuite>
void SelectionExt<AssociatedSuite>::Startup (void)
	{
	InterfacePtr<AssociatedSuite>		iSuite (this, UseDefaultIID ());
	
	ASSERT_MSG (iSuite != nil, "nil suite in selection extention template.");
	if( iSuite )
		iSuite->Startup ();
	}
	
//________________________________________________________________________________________
//	DESC:		Shutdown
//________________________________________________________________________________________
template <class AssociatedSuite>
void SelectionExt<AssociatedSuite>::Shutdown (void)
	{
	InterfacePtr<AssociatedSuite>		iSuite (this, UseDefaultIID ());
	if( iSuite )
		iSuite->Shutdown ();
	}
	
//________________________________________________________________________________________
//	DESC:		Selection changed.
//				CSB's disabled/enabled which means the IGraphicAttributeSuite may
//				become disabled/enabled as well.
//________________________________________________________________________________________
template <class AssociatedSuite>
void SelectionExt<AssociatedSuite>::SelectionChanged (SuiteBroadcastData* suiteBroadcastData, const PMIID& interfaceID, void*	message )
	{
	InterfacePtr<AssociatedSuite>		iSuite (this, UseDefaultIID ());
	
	if (iSuite != nil)
		{
		iSuite->SelectionChanged (suiteBroadcastData, interfaceID, message);
		}
	}
	
//________________________________________________________________________________________
//	DESCR:		This member function is called whenever some attribute of the items that
//				make up selection have changed. For instance if a page item is selected 
//
//	NOTE:		ASB does NOT use this member function.
//________________________________________________________________________________________
template <class AssociatedSuite>
void SelectionExt<AssociatedSuite>::SelectionAttributeChanged (SuiteBroadcastData* broadcastData,  const PMIID& interfaceID, void*	data)
	{
	InterfacePtr<AssociatedSuite>		iSuite (this, UseDefaultIID ());

	if (iSuite != nil)
		{
		iSuite->SelectionAttributeChanged (broadcastData, interfaceID, data);
		}
	}
	
//________________________________________________________________________________________
//	DESCR:		This member function is called whenever a suite on a CSB passes some 
//				information onto an integrator suite.
//
//	NOTE:		The iSelectionManager is used to query the interface in case it is disabled.
//________________________________________________________________________________________
template <class AssociatedSuite>
void SelectionExt<AssociatedSuite>::HandleIntegratorSuiteMessage
	(	
	void*				suiteMessage,
	const ClassID&		classID,
	ISubject*			iSubject,
	const PMIID&		protocol,
	void*				voidStar,
	ISelectionManager*	iSelectionManager
	)
	{
	InterfacePtr<AssociatedSuite>		iSuite (static_cast<AssociatedSuite*>(iSelectionManager->QueryIntegratorSuite (AssociatedSuite::kDefaultIID, ISelectionManager::kAnyInterface)));

	ASSERT_MSG (iSuite != nil, "nil suite in selection extention template.");
	if( iSuite )
		iSuite->HandleIntegratorSuiteMessage (suiteMessage, classID, iSubject, protocol, voidStar);
	}

//________________________________________________________________________________________
//	DESCR:		Returned a list of protocol interested.
//
//	RETURNS:	ProtocolCollection*
//________________________________________________________________________________________
template <class AssociatedSuite>
ProtocolCollection* SelectionExt<AssociatedSuite>::CreateObserverProtocolCollection
	(	
	void
	)
	{
	InterfacePtr<AssociatedSuite>		iSuite (this, UseDefaultIID ());

	ASSERT_MSG (iSuite != nil, "nil suite in selection extention template.");

	return (iSuite->CreateObserverProtocolCollection ());
	}

#endif // _SelectionExtention_Templates_