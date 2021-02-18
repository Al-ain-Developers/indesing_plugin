//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/contentdropper/IContentDropperFacade.h $ 
//   
//  Owner: Ashish Duggal(aduggal)
//   
//  $Author: pmbuilder $ 
//   
//  $DateTime: 2020/11/06 13:08:29 $ 
//   
//  $Revision: #2 $ 
//   
//  $Change: 1088580 $ 
//
//  ADOBE CONFIDENTIAL
//   
//  Copyright 2011 Adobe Systems Incorporated
//  All Rights Reserved.
//   
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received 
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//	Description: 
//  A high level API for dealing with content dropper.
//   
//======================================================================================== 

#pragma once 
#ifndef __IContentDropperFacade__ 
#define __IContentDropperFacade__ 

// ----- Includes ----- 
#include "IPMUnknown.h" 
#include "ContentDropperID.h"
#include "ContentDropperTypes.h"

// -----Forward Declarations------



namespace Facade 
{ 

	class IContentDropperFacade : public IPMUnknown 
	{ 
		public: 
			enum { kDefaultIID = IID_ICONTENTDROPPERFACADE }; 

		//Load into Conveyor APIs
			
			/**	Loads Conveyor with items in the list, as one set.
				@param[in] items UIDList of items to be loaded in the conveyor
				@param[in] linkPolicy LinkPolicy (if any) for the items.
				@return ErrorCode returned from the last Grab Command executed in the API
			*/
			virtual ErrorCode	LoadContentDropper(const UIDList& items,
				ContentDropperTypes::LinkPolicy linkPolicy = ContentDropperTypes::kUnknownPolicy) = 0;	
			

			/**	Loads Conveyor with items and items referred by them
				@param[in] items UIDList of items to be loaded in the conveyor
				@param[in] linkPolicy LinkPolicy(if any) for the items.
				@return ErrorCode returned from the last Grab Command executed in the API
			*/
			virtual ErrorCode	LoadContentDropperWithNeedfulSet(const UIDList* items,
				ContentDropperTypes::LinkPolicy linkPolicy = ContentDropperTypes::kUnknownPolicy) = 0;
			
			/**	Loads Conveyor with items from Pages of the document
				@param[in] db DataBase ptr to the document from which items are to be grabbed.
				@param[in] pageUIDList UIDList of pages from which items are to be grabbed.
				@param[in] makeOneCollection when grabbing from more than one page,
					kTrue - to make one collection from all pages,
					kFalse - grab diff collectons pagewise.
			 	@return ErrorCode returned from the last Grab Command executed in the API.
			 		If any command fails, it does not execute further commands.
			*/
			virtual ErrorCode LoadItemsFromPage(IDataBase* db, const UIDList& pageUIDList, bool16 makeOneCollection = kFalse) = 0;

			/**	Loads Conveyor with items from Spreads of the document
				@param[in] db DataBase ptr to the document from which items are to be grabbed.
				@param[in] spreadUIDList UIDList of spreads from which items are to be grabbed.
				@param[in] makeOneCollection when grabbing from more than one spread,
					kTrue - to make one collection from all spreads,
					kFalse - grab diff collectons spreadwise.
				@return ErrorCode returned from the last Grab Command executed in the API.
					If any command fails, it does not execute further commands.
			*/
			virtual ErrorCode LoadItemsFromSpreads(IDataBase* db, const UIDList& spreadUIDList , bool16 makeOneCollection ) = 0;

		//Place APIs
			/**	Places items onto a specific spread, and applies link policy
				@param[in] itemsToPlace UIDListof items to be placed
				@param[in] targetRef UIDRef of spread under whose heirarchy the items are to be added.
				@param[in] linkPolicy LinkPolicy (if any) for the items.
				@param[in] mapStyles map styles.
				@return ErrorCode returned from the Drop Command executed in the API.
			*/
			virtual ErrorCode	PlaceContent(const UIDList& itemsToPlace, const UIDRef& targetRef,
				ContentDropperTypes::LinkPolicy linkPolicy = ContentDropperTypes::kUnknownPolicy, bool16 mapStyles = kFalse) = 0;

			/**	Place items from Conveyor PlayHead onto a specific spread, and applies link policy
				@param[in] targetRef UIDRef of spread under whose heirarchy the items are to be added.
				@param[in] linkPolicy LinkPolicy(if any) for the items.
				@param[in] mapStyles map styles.
				@return ErrorCode returned from the Drop Command executed in the API.
			*/
			virtual ErrorCode	PlaceContentFromConveyor(const UIDRef& targetRef,
				ContentDropperTypes::LinkPolicy linkPolicy = ContentDropperTypes::kUnknownPolicy, bool16 mapStyles = kFalse) = 0;
			
		//Manage Conveyor

			/**	Clears items from the Conveyor. pass kTrue to clear all items,
					only the item at PlayHead gets cleared otherwise.
				@param[in] allItems kFalse to remove the item at PlayHead,
					kTrue to remove all items from Conveyor
				@return ErrorCode returned from the Remove Command(s) executed in the API.
			*/
			virtual ErrorCode	ClearItemsFromConveyor(bool16 allItems = kFalse) = 0;
			
			/** Moves PlaceHead(the left most position in Conveyor) in Conveyor, by 'byNoOfItems'
				@param[in] byNoOfItems count of positions by which items are to be moved
				@param[in] isForwardDirection kTrue to move item on right of PlaceHead to PlaceHead
				@return kTrue if items got rotated.
			*/
			virtual bool16 RotateItemsBy(const int32 byNoOfItems, const bool16 isForwardDirection = kTrue) = 0;

			/** If item on PlaceHead is a collection, API can be used to show the items in the Set. 
					If they are already shown, use this to go back to up level
				@param[in] expand kTrue to expand the set, kFalse to collapse(go up one level).
				@return kTrue if operation could be performed
			*/
			virtual bool16 ExpandCollapseItemAtHead(bool16 expand = kTrue) = 0;

			/** Items in Conveyor are sorted in their pck order.
					API gets the first/last item that was picked on PlaceHead.
				@param[in] moveToFirst kTrue to get the first item on PlaceHead,
					kFalse get the last item on PlaceHead.
				@return kTrue if operation could be performed
			*/
			virtual bool16 MoveHeadToFirstLastItem(bool16 moveToFirst = kTrue) = 0;

			/**
				@return kTrue if there items loaded in Conveyor
			*/
			virtual bool16		IsConveyorLoaded() = 0;
			
			/** Get the list of items that are part of Nth collection in Conveyor
				@param[in] n The index of the collection
				@return UIDList of the items in the collection
			*/
			virtual UIDList		GetNthItems(uint32 n) = 0;	

			/**	Get the list of items that are part of collection at PlaceHead in Conveyor
				@return UIDList of the items in the collection at the PlaceHead
			*/
			virtual UIDList		GetPlaceHeadItems() = 0;
			
			/** Items in a document may refer to other items like threaded text frames or buttons referring to MSO.
					These items shall be dropped together to maintain the references.
					This API returns the set created by such references of the given item.
				@param[in] root item for which the NeedfulSet is to be created
				@param[out] needfulSet UIDList containing UIDs of all the items in set.
				@return number of items in the set.
			*/
			virtual int32 GetNeedfulSetForItem(UID root, UIDList& needfulSet) = 0;

			/**	Checks if a same set of items from the document already exists in Conveyor.
				@param[in] uidListToAdd set of items to check for.
				@return kTrue if no other set with same item exists.
			*/
			virtual bool16 IsUniqueCollectionInDoc(const UIDList& uidListToAdd) const = 0;

			/**	Get the after place option from Conveyor. 
				@return Option for item placed to be:
					-# Removed
					-# Retained on PlaceHead
					-# Retained in Conveyor but moved to last place
			*/
			virtual ContentDropperTypes::eAfterDrop GetCDUIPrefsAfterPlaceOption() const = 0;

			/** Set the after place option from Conveyor.
				@param[in] option The after drop option
				@return kSuccess if successful, or other error code
			*/
			virtual ErrorCode SetCDUIPrefsAfterPlaceOption(ContentDropperTypes::eAfterDrop option) = 0;

			/**	Get the state of Link option from Conveyor.
				@return kTrue if link creation is enabled, kFalse otherwise.
			*/
			virtual bool16 GetCDUIPrefsLinkOption() = 0;

			/**	Set the state of Link option for Conveyor.
				@param[in] link kTrue to enable link creation, kFalse otherwise.
			*/
			virtual void SetCDUIPrefsLinkOption(bool16 link = kTrue) = 0;

			/**	Get the state of Map Styles option from Conveyor.
				@return kTrue if mapping of styles is enabled, kFalse otherwise
			*/
			virtual bool16 GetCDUIPrefsMapStyles() = 0;

			/** Set the state of Map Styles option for Conveyor.
				@param[in] mapStyle kTrue to enable map styles, kFalse otherwise
			*/
			virtual void SetCDUIPrefsMapStyles(bool16 mapStyle = kTrue) = 0;

			/**	Get the state of Collect All Threaded Frames option from Conveyor.
				@return kTrue if the conveyor is set to collect all threaded frames
			*/
			virtual bool16 GetCDUIPrefsCollectAllThreadedFrames() = 0;

			/**	Set the state of Collect All Threaded Frames option from Conveyor.
				@param[in] collectAllFrames kTrue to collect all threaded frames, kFalse otherwise
			*/
			virtual void SetCDUIPrefsCollectAllThreadedFrames(bool16 collectAllFrames = kTrue) = 0;
	}; 

} // namespace Facade

#endif    // __IContentDropperFacade__ 
