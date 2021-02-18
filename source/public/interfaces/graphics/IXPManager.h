//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPManager.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IXPManager__
#define __IXPManager__

#include "IPMUnknown.h"
#include "BravoForwardDecl.h"
#include "XPID.h"

class IDocument;
class ICommand;
class PMRect;
class UIDList;
class IShape;
class IGraphicsPort;

// For blur amounts less than kMinSuperSampleBlurSize, automatically multiply the
// ideal resolution by kSuperSampleMultiplier in order to avoid impression of jaggies.
const float kXPMinSuperSampleBlurSize = 0.5;
const float kXPSuperSampleMultiplier = 3.0;


class IXPManager : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXPMANAGER };

		// This is a helper function which gives you the AGMColorSpace corresponding to the
		// current blending space preference in the document.	Note that iPort is optional
		// but that's primarily for backward compiler compatibility -- in general the port
		// is needed so we can inspect the proofing configuration and make the appropriate
		// profile available.
		virtual AGMColorSpace* GetDocumentBlendingSpace(IGraphicsPort* iPort = nil) const = 0;
		virtual void ReleaseBlendingSpace(AGMColorSpace*) const = 0;

		// Brute-force Transparency Search
		// -------------------------------
			// This is an expensive operation because it actually iterates over the content
			// of the spread, including its masters.  boundsRect is useful if you want to know,
			// for example, whether a given page has transparency.  iterateFlags controls the
			// draw manager iteration used to search the page, so for example setting it to
			// IShape:: kSkipHiddenLayers will cause the method to ignore transparency on
			// hidden layers.
					
			virtual bool32 SpreadContainsTransparency(UID spreadRef, const PMRect& boundsRectInSpreadCoordinates, 
								int32 iterateFlags = 0) = 0;
			
			// Returns 1 or 0.  The two later parameters allow an ITerateDrawOrder to call this, and then
			// internally to continue using the same parameters.
			virtual int32 ItemHasTransparency_(IShape* item, const PMMatrix* transform, int32 nFlags) = 0;
			
			// Check if a particular IShape item has transparency. 
			int32 ItemHasTransparency(IShape* item)
			{
				return ItemHasTransparency_( item, nil, 0);
			}
			
		// Page-Items-With-Transparency List
		// ---------------------------------
			// The XPManager maintains a list of all page items in the document which have
			// transparency.  This is used for a number of purposes, but mainly for determining
			// whether there's XP in the document, and for transparency usage.
			
			virtual int32 GetNumItemsWithXP() const = 0;
			virtual UID GetNthItemWithXP(int32 n) const = 0;
			virtual int32 GetItemIndex(UID uid) const = 0;
		
			// These are called whenever you affect the presence of transparency on an item.  In
			// response, the XPManager will ask the item(s) for their new XP state, and if it changes,
			// will update the list of items in the doc containing XP.  See also XPItemXPChangedCmd.
		
			// XPChangeType is used to tell ItemXPChanged what happened.
			enum XPChangeType
			{
				kXPC_AddedSomeXP, 			// An XP attribute/setting was added/enabled
				kXPC_RemovedSomeXP, 		// An XP attribute/setting was removed/disabled
				kXPC_AddedItemWithXP,		// Added a new item that has transparency.
				kXPC_ItemRemoved,			// The item is being deleted (remove from itemlist).
				kXPC_ItemMoved,				// The item was moved or resized (if on a master, could affect
											//  the XP state of the spreads using that master)
				kXPC_NoChange,				// Only used as a no-op case.
				kXPC_MayHaveAddedSomeXP		// Settings were changed; unclear if result was to add transparency
			};
			virtual void ItemXPChanged(UID itemUID, XPChangeType chg) = 0;
			virtual void ItemXPChanged(const UIDList& itemList, XPChangeType chg) = 0;
			
			// Utility version of above which builds and processes an XPItemXPChangedCmd.
			virtual ErrorCode ProcessItemXPChangedCmd(const UIDList& itemList, XPChangeType chg) = 0;
				
		// Spread-Has-Transparency Cache
		// -----------------------------
			// Maintains a per-spread cache of presence of transparency.  Info is maintained solely on 
			// the presence of transparent items on spread, not based on location; so, if you want to know
			// if a *page* has transparency,  you have to use one of the search-based methods above.
			// Note that the cache is NOT persistent.
		
			// Returns 1 or 0, unless autoValidate is false, in which case can also return -1 if state not known.
			virtual int32 SpreadHasTransparency(UID spreadUID, bool32 autoValidate = kTrue) = 0;
			
			// Cache invalidation
			virtual void InvalidateSpreadHasXPCache() = 0; // entire cache
			virtual void InvalidateSpreadHasXPCache(UID spreadUID) = 0; // just this spread
			virtual void InvalidateSpreadHasXPCache(const UIDList& spreadList) = 0; // just these spreads

		// Adobe internal use only
			virtual void ConvertPhase2(int32 privatePhase2Code) = 0;

			// Check if a particular item itself or any item in its parent hierarchy has transparency.
			virtual int32 ItemHasTransparencyInParentHierarchy(IShape* item) = 0;

};

#endif