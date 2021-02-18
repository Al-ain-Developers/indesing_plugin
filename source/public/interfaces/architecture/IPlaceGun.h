//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPlaceGun.h $
//  
//  Owner: zwilliam
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
#ifndef __IPlaceGun__
#define __IPlaceGun__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"

class ITracker;

/** This class deals with placing images/text onto the 
	page once they have been imported into the document 
*/
class IPlaceGun : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPLACEGUN };
	
	/** Is the place gun loaded 
		@return - kTrue means the place gun currently has data that could be placed on the page.
	*/
	virtual bool16 IsLoaded() const = 0;
	
	/** Count how many UIDs are loaded in the place gun
		@return -count of UIDs
	*/
	virtual uint32 CountPlaceGunUIDs() const= 0;

	/**
		Where to add the item into the place gun
	*/
	typedef enum {
					/** add to front of place gun list - unusual */
					kAddToFront,
					/** add to end of place gun list - typical */
					kAddToBack
			} PlaceGunLocation;
	
	/** Load the place gun with this uid.
		@param uid - The UID of the item to be placed. The uid must be of a page item.
		@param where - Whether to add the item to the front or back of the list
		Note:  The LoadPlaceGunCmd will accept a story uid and call this
		method with the uid of a newly created frame on the story.
	*/
	virtual void LoadPlaceGun(UID uid, PlaceGunLocation where = kAddToBack) = 0;
		
	/**	Clears the uid stored in this interface, but does not
		delete the uid from the database.
	*/
	virtual void EmptyFirstPlaceGunItem() = 0;
		
	/** Returns UID of the current contents of the place gun.
		@return - The UID of the contents of the gun
	*/
	virtual UID GetFirstPlaceGunItemUID() const = 0;

	/** Returns UID of the current contents of the place gun.
		@return - The UID of the contents of the gun
	*/
	virtual UID GetNthPlaceGunItemUID( uint32 n ) const = 0;

	/** During abort place gun, this is the UID of the item being aborted, 
		previously in GetFirstPlaceGunItemUID()
		@return - The item that was (but is no longer) being placed
		@see GetFirstPlaceGunItemUID
	*/
	virtual UID GetAbortingItemUID() const = 0;

	/** Set the UID of the item being aborted
		@param uid - The UID to abort the placing of
	*/
	virtual void SetAbortingItemUID(UID uid) = 0;

	/** Returns whether a given UID is currently in the place gun.
		@param uid - The UID to search for
		@return - kTrue if the UID is found, else kFalse
	*/
	virtual bool16 ContainsUID(UID uid) = 0;

	/** Returns whether any pageitems in the placegun are on a documentLayer.
		@param uid - The document layer UID
		@return - kTrue if an owned pageitem assigned to the layer is found, else kFalse
	*/
	virtual bool16 OwnsAnyPageItemsOnLayer(UID spreadLayerUID) const = 0;

	/** Returns whether any pageitems in the placegun are on a spread.
		@param uid - The spread UID
		@return - kTrue if an owned pageitem on the spread is found, else kFalse
	*/
	virtual bool16 OwnsAnyPageItemsOnSpread(UID spreadUID) const = 0;

	/** Rotates the list of UIDs.
		@param forward - Rotate the list forward(i.e. move the front UID to end) or backwards(move backmost UID to front)
	*/
	virtual void RotateList(bool16 forward) = 0;

};

#endif
