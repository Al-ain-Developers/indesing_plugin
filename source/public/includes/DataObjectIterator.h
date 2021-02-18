//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DataObjectIterator.h $
//  
//  Owner: Dave Burnard
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
//  a abstract iterator class used to access the items in drap/drop and clipboard operations.
//  
//========================================================================================

#pragma once
#ifndef __DataObjectIterator__
#define __DataObjectIterator__

#include "PMFlavorTypes.h"

class IPMDataObject;

#pragma export on
/** an abstract iterator class used to access the items in data exchange (drap/drop and clipboard) operations.
		There is almost always only one item (always true on Win, and for clipboard, but can be multiple in Mac drops)

		@see IPMDataObject
*/
class DataObjectIterator
{
	public:
		/** Destructor */
		virtual ~DataObjectIterator() {}
		
		/** Get the first data object */
		virtual IPMDataObject*			First() = 0;
		/** Get the next data object */
		virtual IPMDataObject*			Next() = 0;
		
		/** Does the flavor exist in all items

			@param flavor IN which flavor
			@return kTrue or kFalse
		*/
		virtual bool16						FlavorExistsInAllObjects(ExternalPMFlavor flavor) = 0;

		/** Does the flavor exist in all items, and is it the first or highest priority flavor

			@param flavor IN which flavor
			@return kTrue or kFalse
		*/
		virtual bool16						FlavorIsPrimaryInAllObjects(ExternalPMFlavor flavor) = 0;

		/** Does the flavor exist in all items, and at what priority

			@param flavor IN which flavor
			@return response containing kTrue or kFalse plus highest priority of flavor in items
		*/
		virtual DataExchangeResponse	FlavorExistsWithPriorityInAllObjects(ExternalPMFlavor flavor) = 0;
};

#pragma export off

#endif // __IDragItemIterator__
