//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPageTransitionFacade.h $
//  
//  Owner: DBerggren
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IPageTransitionFacade__
#define __IPageTransitionFacade__

#include "DynamicDocumentsID.h"

class IPageTransition;
class IDocument;

namespace Facade
{
	/** A high level API for dealing with page transitions. Each spread can have a page transition
		applied to it. The page transition is defined by a ClassID, direction and duration. Use 
		this facade to determine which page transitions are available, and to Get and Set the 
		page transition information on the spreads. Each page transition is its own boss (ClassID). 
		The IPageTransition interface on the boss defines the type and name of the transition, 
		allowable directions, and a default duration. The directions are enum based, defined in the
		IPageTransition header file. Allowable directions are specific for each transition. Duration 
		is based on number of ticks, where there are 60 ticks per second. There are defines in
		IPageTransition.h for the default settings for fast, medium and slow duration times.
		@see IPageTransition
	
		Please use the IPageTransitionFacade directly via the UtilsBoss if possible, see Utils.h:
		i.e. Utils<IPageTransitionFacade>()->GetPageTransitionCount( );
	   */
	class IPageTransitionFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPAGETRANSITIONFACADE };

		// ***********************
		// Spread based page transition helper routines
		// ***********************

		/**
		 Determine if the given spread has a page transition defined

		 @param spreadRef	IN:	The UIDRef of spread to look for the page transition 
		 @return true if there is a page tranition defined for the spread, false otherwise
		 */
		virtual bool SpreadHasPageTransition(UIDRef const &spreadRef) const = 0;

		/**
		 Determine if the given spread list has a page transition defined or not.
		 As long as there is one spread has page transition, we return true

		 @param spreadList	IN:	The given spread list to check the page transition 
		 @return true if there is one spread has page tranition defined; otherwise return false.
		 */
		virtual bool SpreadsHavePageTransition(UIDList const &spreadList) const = 0;

		/**
		 Gets the page transition information for the spread referenced

		 @param spreadRef	IN:	The UIDRef of spread to get the page transition information
		 @param classID		OUT: The class ID of the transition, may be kInvalidClass if no transition applied
		 @param direction	OUT: The direction of the transition, as defined in IPageTransition
		 @param duration	OUT: The duration of the transition (in ticks - 60 ticks per second)
		 @return kSuccess, or ErrorCode
		 @see IPageTransition
		 */
		virtual ErrorCode GetSpreadPageTransitionDetails(UIDRef const &spreadRef, ClassID* classID = nil, uint32* direction = nil, uint32* duration = nil) const = 0;

		/**
		 Sets the page transition information for the spreads included in the given UIDList

		 @param uidList		IN:	The UIDList of spreads to set the page transition
		 @param classID		IN:	The class ID of the transition, may be kInvalidClass if no transition applied
		 @param direction	IN:	The direction of the transition
		 @param duration	IN:	The duration of the transition (in ticks - 60 ticks per second)
		 @return kSuccess, or ErrorCode
		 */
		virtual ErrorCode SetSpreadPageTransitionDetails(UIDList const &uidList, ClassID const &classID, uint32 direction, uint32 duration) const = 0;

		/**
		Check if all the given spreads have the same page transitions applied or not. 
		If there is no spreads passed in, we will collect all the spreads in the document.

		@param spreadList	IN:	The given spread list to be checked.
		@param resultTransitionClass OUT: the transition class that all spreads are applied.
		@return bool - true if all the spreads has the same page transitions, false otherwise
		*/
		virtual bool AllSpreadsHaveSamePageTransition(UIDList const &spreadList, ClassID& resultTransitionClass) const = 0;

		/**
		Apply the given page transition to all the spreads in the UIDList passed in. If the UIDList is 
		empty, it will get the IDocument (based on the database used to create the UIDList), and apply
		the page transition to all the spreads in the document.

		@param spreads			IN:	The given spreads to apply, if there is no spread, we will apply to all spreads in the document.
		@param transitionClass	IN:	The given ClassID of page transition tp apply
		@param direction		IN:	The given direction of the page transition to apply 
		@param speed			IN:	The given speed of page transition to apply
		@return ErrorCode - kSuccess if we apply successfully, an error otherwise
		*/
		virtual ErrorCode ApplyPageTransitionToAllSpreads(UIDList const &spreads, const ClassID &transitionClass, uint32 const &direction, uint32 const &speed) const = 0;

		// ***********************
		// Page Transition List Routines
		// ***********************

		/**
		 Get number of page transitions defined

		 @return The number of page transitions 
		 */
		virtual uint32 GetPageTransitionCount() const = 0;

		/** 
		 Gets the ClassID of the nth page transition. 
		
		 @param index		IN: Index of the page transition to get
		 @return ClassID of the nth page transition, or kInvalidClass if failure
		 */
		virtual ClassID GetNthPageTransitionClassID(int32 index) const = 0;

		/**
		 Returns name for the nth page transition. 

		 @param index			IN: Index of the page transition to get
		 @param translateName	IN: Whether to translate the name returned (default is false)
		 @return PMString containing its name
		 */
		virtual PMString GetNthPageTransitionName(int32 index, bool translateName = false) const = 0;

		/** 
		 Instantiates nth page transition 
		
		 @param index		IN: Index of the page transition to instantiate
		 @return AddRef'd pointer to nth IPageTransition, or nil if failure
		 */
		virtual IPageTransition *QueryNthPageTransition(int32 index) const = 0;

		/** 
		 Instantiates page transition based on class ID
		
		 @param classId		IN: class ID of the page transition to instantiate
		 @return AddRef'd pointer to the requested IPageTransition, or nil if failure
		 */
		virtual IPageTransition *QueryPageTransition(ClassID const &classID) const = 0;

		/**
		 Retrieves index of page transition with given class ID in the list

		 @param classId			IN: Class id of page transition
		 @return index			index of found item if successful, -1 if not found
		 */
		virtual int32 FindPageTransitionIndex(ClassID const &classID) const = 0;

		/** 
		 Finds named page transition in list, returning its index if found

		 @param name				IN: Name of page transition to find
		 @param useTranslatedNames	IN: Whether to translate page transition names before compare (default is false)
		 @return index				index of found item if successful, -1 if not found
		 */
		virtual int32 FindPageTransitionIndex(PMString const &name, bool useTranslatedNames = false) const = 0;

		/** 
		 Finds the named page transition in list, returning its ClassID if found

		 @param name				IN: Name of page transition to find
		 @param useTranslatedNames	IN: Whether to translate page transition names before compare (default is false)
		 @return ClassID of specified page transition was found, if not found, kInvalidClass
		 */
		virtual ClassID GetPageTransitionClassID(PMString const &name, bool useTranslatedNames = false) const = 0;

		/** 
		 Finds the named page transition in list, returning its ClassID if found

		 @param classID				IN: ClassID of page transition to find
		 @param translateNames		IN: Whether to translate the page transition name before returning (default is false)
		 @return PMString of the name of page transition was found, if not found, and empty string
		 */
		virtual PMString GetPageTransitionName(ClassID const &classID, bool translateName = false) const = 0;

		/**
		 Determine if the given direction is valid for the page transition with given class ID in the list

		 @param classId			IN: Class id of page transition
		 @param uint32			IN: Direction of the page transition to check, as defined in IPageTransition
		 @return bool			true if given direction is valid for the given ClassID, false otherwise
		 @see IPageTransition
		 */
		virtual bool ValidPageTransitionDirection(ClassID const &classID, const uint32 direction) const = 0;

	};
}


#endif // __IPageTransitionFacade__
