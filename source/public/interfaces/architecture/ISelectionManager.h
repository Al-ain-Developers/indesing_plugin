//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionManager.h $
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

#pragma once
	#ifndef _ISelectionManager_
	#define _ISelectionManager_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "IPMUnknown.h"
	#include "ISelectionMessages.h"
	
	//.......ID headers...........................................................................
	#include "ShuksanID.h"

//________________________________________________________________________________________________
//	DEFINES
//________________________________________________________________________________________________
//	#define	USE_ILDETASK_FOR_SELATTR_CHANGED	1
//	#define	USE_ILDETASK_FOR_SEL_CHANGED		1
//================================================================================================
//________________________________________________________________________________________________
//	CLASS FORWARDS
//________________________________________________________________________________________________
	class SelectionMessage;
	class IConcreteSelection;
	class IDefaultCSB;
	class IDataBase;
	class PrivateSelectionAccess;
	class IActiveContext;
	class InternalSelectionMessage;
	class IdleTimer;
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/**
	An interface on the Abstract Selection boss to manage the selection
*/
class ISelectionManager : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Do Not copy this idiom
	//
	//	DO NOT ADD FRIENDS TO THIS CLASS WITHOUT DISCUSSING IT WITH MICAHEL MARTZ
	//
	//____________________________________________________________________________________________
	friend class PrivateSelectionAccess;
	
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ISELECTIONMANAGER };

		enum ConcreteBossListType { kEnabledCSBs, kDisabledCSBs, kDefaultCSB, kSelectionCSBs, kAllCSBs };
		enum ExistsType { kUniqueSelection, kMixedSelection,  kAnySelection };
		enum InterfaceType { kEnabledInterface, kAnyInterface};

		typedef K2Vector<InterfacePtr<IPMUnknown> >	ConcreteSelectionBossCollection;	
	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//........................................................................................
		//	Utility
		//........................................................................................
/**
			Is the interface enbaled, i.e. does it exist on one of the enabled CSBs.
		
		@return	True / False.
*/
		virtual bool16 		IsInterfaceEnabled (const PMIID& interfaceID) const = 0;
	
/**
			Query an interface on the Abstract Selection boss.
		
			NOTE:		Should only be used from within a CSB
		@return	IPMUnknown* or nil
*/
		virtual IPMUnknown*		QueryIntegratorSuite (const PMIID& interfaceID, InterfaceType) const = 0;

		//........................................................................................
		//	View Selection
		//........................................................................................
/**
				Initialize the selection manager on the abstract selection boss.
		
		NOTE:		"db" - the persistent store
					"owner" - the view or workspace whom owns this instantiation.
						"concreteSelectionBosses" - the selection manager now owns the object
*/
		virtual void 		Startup (IDataBase* db, const UIDRef& owner) = 0;
/**
		Shutdown
*/
		virtual void		Shutdown (void) = 0;
		
/**
				Return the database which is the persistent store for items in this 
						selection.
		
		@return	IDataBase* or nil
*/
		virtual IDataBase*		GetDataBase (void) const = 0;

/**
				Return the view/workspace that owns the concrete selection bosses 
						currently used by the selection manager.
		
		@return	UIDRef of view window/workspace or UIDRef::gNull.
*/
		virtual UIDRef GetSelectionsOwner (void) const = 0;		

/**
				Does a selection exist in the specified concrete selection boss?
						"existsType" allows the caller to specify the type of selection that exists:
							kUniqueSelection - 	The specified CSB is the only one with a selection
							kMixedSelection  - 	The specified CSB and at least one other CSB have a 
												selection.
							kAnySelection	 - 	At least, the specified CSB has a selection. The 
											other CSBs may or may not have a selection.
						If the ClassID is kInvalidClass AND ExistsType is kAnySelection, then all
						of the concrete selection bosses will be iterated looking for the requested ExistsType.
		
		@return	kTrue / kFalse.
*/
		virtual bool16 SelectionExists (ClassID, ExistsType = kAnySelection) const = 0;

#ifdef ID_DEPRECATED
/**
				Return the specified concrete selection boss.
		
		@return	IConcreteSelection* or nil
*/
		virtual IConcreteSelection* QueryConcreteSelectionBoss (ClassID) const = 0;
#endif // ID_DEPRECATED

/**
				Broadcast a content changed message to observers. Intended for use by 
						suites when they need to broadcast a message.
*/
		virtual void BroadcastMessage (SuiteBroadcastData*) const = 0;

/**
				Send a "SelectAll" to the active CSBs that are listed in "csbList", the
						context indicates where to select (e.g. the current page)
		
			NOTE:		A nil "csbList" means selectall on every active CSB.
		
						If no CSBs are active the SelectAll call is always sent to the ASB's
					primary CSB (csbList is not used).
*/
		virtual void SelectAll (IActiveContext*	iContext, K2Vector<ClassID>* csbList) const = 0;

/**
				Send a "DeselectAll" to the active CSBs that are listed in "csbList"
		
		NOTE:		A nil "csbList" means deselect every active CSB.
*/
		virtual void DeselectAll (K2Vector<ClassID>* csbList) const = 0;


/**
		Deselect All without broadcasting
*/
		inline void DeselectAllNoBroadcast(K2Vector<ClassID>* csbList) const
			{ //implement this to not notify selection observers so that the UI doesn't flash
				DeselectAll (csbList);
			}
		
/**
			Send a "DeselectAll" to the active CSBs that are not listed in the 
						"csbKeepList"
*/
		virtual void DeselectAllExcept (K2Vector<ClassID>* csbKeepList) const = 0;

		//........................................................................................
		//	Internal Selection Utilities
		//........................................................................................
/**
				Broadcast any queued messages on active CSBs.
*/
		virtual bool16 	BroadcastQueuedMessages (IdleTimer*) = 0;

/**
				Internal notification that a CSB has changed selection.
*/
		virtual void 	CSBSelectionChanged (ISelectionMessage*, SuiteBroadcastData*) = 0;

/**
				Internal notification that a CSB has changed selection.
*/
		virtual void 	CSBHasQueuedMessages (ClassID, ISelectionMessage::SelectionMessageType) = 0;

	private:
/**
		Do not use
*/
		virtual IConcreteSelection* QueryConcreteSelectionBoss_Private (ClassID) const = 0;
/**
		Do not use
*/
		virtual IDefaultCSB* QueryDefaultSelectionBoss_Private (void) const = 0;
/**
		Do not use
*/
		virtual ConcreteSelectionBossCollection* QueryConcreteSelectionBosses_Private (ConcreteBossListType, const PMIID&) const = 0;
	};

#endif // _ISelectionManager_