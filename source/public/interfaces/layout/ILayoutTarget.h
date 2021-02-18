//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutTarget.h $
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
	#ifndef _ILayoutTarget_
	#define _ILayoutTarget_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "ShuksanID.h"
	#include "UIDList.h"
//================================================================================================
//________________________________________________________________________________________________
//	Constants
//________________________________________________________________________________________________
//	const bool16	kStripStandoffs = kTrue;
//	const bool16	kDontStripStandoffs = kFalse;
//	const bool16	kStripIfParentLocked = kTrue;
//	const bool16	kDontStripIfParentLocked = kFalse;
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
/** The Layout target interface. A wrapper around the a UIDList for selection and target bosses
*/
class ILayoutTarget : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_ILAYOUTTARGET };




	template< typename, int v> struct Int2Type { enum { value = v};};

	struct StandoffChoice
	{
		typedef Int2Type< StandoffChoice, 0> DontStripStandoffs;
		typedef Int2Type< StandoffChoice, 1> StripStandoffs;

		/*--------trickery below--------*/
		template<int v> StandoffChoice( const Int2Type<StandoffChoice, v>& ) : value(v) { }
		StandoffChoice( const StandoffChoice& other) : value( other.value) { }
		friend bool operator==( const StandoffChoice& lhs, const StandoffChoice& rhs) { return lhs.value == rhs.value; }
		friend bool operator!=( const StandoffChoice& lhs, const StandoffChoice& rhs) { return lhs.value != rhs.value; }
		private: int value;
	};

	struct LockedParentChoice
	{
		typedef Int2Type< LockedParentChoice, 0> DontStripIfParentLocked;
		typedef Int2Type< LockedParentChoice, 1> StripIfParentLocked;

		/*--------trickery below--------*/
		template<int v> LockedParentChoice( const Int2Type<LockedParentChoice, v>& ) : value(v) { }
		LockedParentChoice( const LockedParentChoice& other) : value( other.value) { }
		friend bool operator==( const LockedParentChoice& lhs, const LockedParentChoice& rhs) { return lhs.value == rhs.value; }
		friend bool operator!=( const LockedParentChoice& lhs, const LockedParentChoice& rhs) { return lhs.value != rhs.value; }
		private: int value;
	};




	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		//........................................................................................
		//	(Add to / Remove from) the layout target
		//........................................................................................
/**		Add a new item
*/
		virtual void 			Add (const UID newItem) = 0;
/**		Add a new item
*/
		virtual void			Add (const UIDList& newItems) = 0;
/**		Remove a  item
*/
		virtual void 			Remove (const UID itemToRemove) = 0;
		
/**		Clear the target
*/
		virtual void			Clear (void) = 0;
		
/**		Get the target
*/
		virtual UIDList		 	GetUIDList (StandoffChoice stripStandoffs, LockedParentChoice stripIfParentLocked) const = 0;
		inline UIDList		 	GetUIDList( StandoffChoice stripStandoffs) const;



/**		Set the target
*/
		virtual void			SetUIDList (const UIDList&) = 0;		
/**		Set the target
*/
		virtual void			SetUIDList (const UID) = 0;

/**				Return the previous target. Only works on the LayoutCSB.
*/		
//		virtual UIDList		 	GetLastUIDList (StandoffChoice stripStandoffs, bool16 stripIfParentLocked = kDontStripIfParentLocked) const = 0;		

/**				Flattent the target's UIDList. This means:
							(a)	Remove any page item that does not have the GfxSelection interface
							(b)	Expand all containers so their children are in the returned list
					(c) Filter out any page items that do _not_ support "interfaceID" 
							(optional)
							(d)	Any duplicates are removed from the list.
		
			NOTE:		If "interfaceID" is kInvalidInterfaceID don't filter any page items.
		
			@return	Index (>= 0 if in list); Negative number (< 0) if not in list.
*/		
		virtual UIDList			CreateFlattenedUIDList (const PMIID&) const = 0;
		
/**
			Calculate the differences between the last two layout selections.
*/
		virtual void			CalculatePreviousSelectionDifferences (UIDList* addedPageItems, UIDList*removedPageItems) = 0;
		//........................................................................................
		//	Utilities
		//........................................................................................
/**		Initialize
*/
		virtual void			Initialize		(IDataBase*) = 0;
/**		Is the UID part of the target
*/
		virtual bool16			PartOfTarget	(const UID&) const = 0;
		
/**		The target has changed
*/
		virtual void			TargetChanged 	(void) = 0;

/**		Has content, is the UIDList non empty
*/
		virtual bool16			HasContent		(void) const = 0;

/**		Return the key object, kInvalidUIDRef if none
*/
		virtual UIDRef			GetKeyObject	(void) const = 0;

/**		Set the key object, kInvalidUIDRef to clear
*/
		virtual void			SetKeyObject	(const UIDRef& keyObject) = 0;
	};


const ILayoutTarget::StandoffChoice kStripStandoffs = ILayoutTarget::StandoffChoice::StripStandoffs();
const ILayoutTarget::StandoffChoice kDontStripStandoffs = ILayoutTarget::StandoffChoice::DontStripStandoffs();
const ILayoutTarget::LockedParentChoice kStripIfParentLocked = ILayoutTarget::LockedParentChoice::StripIfParentLocked();
const ILayoutTarget::LockedParentChoice kDontStripIfParentLocked = ILayoutTarget::LockedParentChoice::DontStripIfParentLocked();

inline UIDList ILayoutTarget::GetUIDList( StandoffChoice stripStandoffs) const { return GetUIDList( stripStandoffs, kDontStripIfParentLocked);}


#endif // _ILayoutTarget_


