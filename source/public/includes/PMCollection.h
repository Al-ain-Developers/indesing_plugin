//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMCollection.h $
//  
//  Owner: 
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
//  collections for Interfaces & IIDs
//  
//========================================================================================

#pragma once
#ifndef __PMCOLLECTION__
#define __PMCOLLECTION__

#include "K2Vector.h"


typedef IPMUnknown					*PMUnknownPtr;
typedef K2Vector<PMUnknownPtr>	PMUnknownArray;

#pragma export on

/** Used for storing lists of pointers to interfaces, where all the pointers are
	referenced, and this list will keep track of the AddRef & Release for you.
	Please consider using K2Vector<InterfacePtr<IFoo> > instead! This is really 
	only still here for backwards compatibility.
	@see IPMUnknownRefListData
*/
class PMUnknownRefList: public PMUnknownArray
{
	public:
		/** Construct an empty list */
		PMUnknownRefList() {}

		/** Construct an empty list, but set aside storage space.
			@param chunksize	number of entries to allocate in storage space
		*/
		PMUnknownRefList(int32 chunksize) :PMUnknownArray()
        {
            reserve(chunksize);
        }

		/** Construct a new list, which will be a copy of the supplied list.
			@param copy	the list to copy
		*/
		PMUnknownRefList(const PMUnknownRefList& copy) :PMUnknownArray(copy) {}

		/** Desctruct the list. Releases all the objects on the list.
		*/
		PUBLIC_DECL ~PMUnknownRefList();
};

#pragma export off

#endif
