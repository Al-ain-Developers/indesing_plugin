//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IConcreteSelection.h $
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
//  Note:		This is the primary interface on the concrete selection boss. Before
//  the boss can be used, it must be initialized. This is done by calling Initialize()
//  on this interface (the implementations are responsible for initializing any other
//  interfaces which may need this service).
//  
//========================================================================================

#pragma once
	#ifndef _IConcreteSelection_
	#define _IConcreteSelection_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "PMCollection.h"
	#include "ISelectionManager.h"
	#include "ShuksanID.h"
	#include "K2Vector.h"
	#include "ISelectionMessages.h"
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class IControlView;
	class IDataBase;
	class ISelectionManager;
//________________________________________________________________________________________________
//	TYPEDEFS
//________________________________________________________________________________________________
	typedef K2Vector<PMIID>	SuiteIIDCollection;	
	enum {kDontNotifySuites = kFalse, kNotifySuites = kTrue};
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/**	
	Represents the primary interface on Concrete Selection Bosses (CSBs). InDesign has the following
	CSBs: Layout, Text, Table & XML. The Selection architecture uses this interface to manage the 
	specific CSB. Some clients of the interface are the CSB's selection suite and it's messaging
	system.
*/
class IConcreteSelection : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ICONCRETESELECTION };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**		Called when the CSB is started up from the ASB.
				@param database The "selectable object" database
				@param owningView The view that "owns" this selection
		*/
 		virtual void Startup (IDataBase* database, const UIDRef& owningView) = 0;

		/**		Called when the CSB is shut down from the ASB.
		*/
		virtual void Shutdown (void) = 0;

		/**
				Return the database which is the persistent store for items in this selection.
				@return	IDataBase* or nil
		*/
		virtual IDataBase* GetDataBase (void) const = 0;

		//........................................................................................
		//	Selection Utilities
		//........................................................................................
		/**
				Broadcast any data from this CSB that has accumulated since the last idle task.
				@param timer The idle task timer to check when to exit
				@return Whether the entire broadcast was completed (kTrue) or if this function needs to be called again (kFalse)
		*/
		virtual bool16 BroadcastQueuedMessages (IdleTimer* timer) const = 0;
		
		/**
				Broadcast an internal message to the Selection Manager that this CSB's selection has changed.
		*/
		virtual void SelectionHasChanged (void) = 0;

		/**
				Broadcast an internal message to the Selection Manager that this CSB has messages to broadcast 
				to clients.
				@param selectionMessageType The type of broadcast that is needed
		*/
		virtual void SelectionHasQueuedMessages (ISelectionMessage::SelectionMessageType selectionMessageType) const = 0;

		/**
				DeselectAll should change the internal state of the concrete selection boss so that 
				DoesSelectionExist returns kFalse. Usually by calling a function on the CSB's selection suite.
				
		*/
		virtual	void				DeselectAll (void) = 0;

		/**		
				Select all. Implement what "Select All" means for this CSB. Usually by calling a function on 
				the CSB's selection suite.
				@param iContext The Active Context of the current selection
		*/
		virtual	void				SelectAll (IActiveContext* iContext) = 0;
		
		/**
				Is there currently anything selected on this CSB?
				@return True or False
		*/
		virtual bool16 				SelectionExists (void) const = 0;

		/**
				Broadcast a message from the CSB to a suite on the ASB.
				@param pmiid The suite IID on the integrator which will receive the message
				@param selectionMessage The message to send
		*/
		virtual void BroadcastToIntegratorSuite (const PMIID& pmiid, void* selectionMessage) = 0;

		/**
				Return the view/workspace that owns the selection sub-system.
				
				NOTE:		This function is temporary until the old architecture is removed. 
							DO NOT USE WITHOUT CONSULTING MICHAEL MARTZ!
				
				@return	UIDRef of view window/workspace or UIDRef::gNull.
		*/
		virtual UIDRef 		GetSelectionsOwner_Temporary_DoNotUse (void) const = 0;
		
		/**
				Query the selection suite that is provided for this CSB.
				Selection Suites are aggregated on the ASB.
				
				@return	IPMUnknown of Selection suite or nil
		*/
		virtual IPMUnknown*		QuerySelectionSuite (const PMIID&) const = 0;

		/**
			Used Internally
		*/
		virtual void				UpdateSelectionChangedBroadcastData (void) = 0;

	};

#endif // _IConcreteSelection_