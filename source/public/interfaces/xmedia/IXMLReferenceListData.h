//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLReferenceListData.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLREFERENCELISTDATA__
#define __IXMLREFERENCELISTDATA__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** Data interface for passing a list of XMLReference; from client code, use IXMLElementCommands methods
	rather than process low-level commands directly.
*/
class IXMLReferenceListData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXMLREFERENCELISTDATA };

		/** Enumeration giving positions in list for inserts */
        enum _Placement {
			/** */ 
			kBeginningIndex = 0,
			/** */ 
			kEndIndex = -2,
			/** */ 
			kInvalidIndex = -1
		};

	public:

		/**	Add new XMLReference by default at end of list
			@param xmlRef specifies object to add 
			@param pos location to add at (one of _Placement values) 
		 */
		virtual void Insert(const XMLReference &xmlRef, int32 pos = kEndIndex) = 0;

		/**	Remove supplied XMLReference from list
			@param xmlRef specifies object to remove
		 */
		virtual void Remove(const XMLReference &xmlRef) = 0;

		/**	Empty list contents
		 */
		virtual void Clear(void) = 0;

		/**	Accessor for XMLReference at given index
			@param index specifies index of element of interest
			@return reference to object at given index
		 */
		virtual XMLReference Get(int32 index) const = 0;

		/**	Mutate item at specified index to be supplied XMLReference
			@param index location of the element
			@param newXMLRef element to put in this new location
		 */
		virtual void Set(int32 index, const XMLReference& newXMLRef) = 0;

		/**	Return index given an XMLReference
			@param xmlRef specifies the XMLReference of interest
			@return int32 where in the list of objects it is located; -1 if not found
		 */
		virtual int32 GetIndex(const XMLReference& xmlRef) const = 0;

		/**	Count of XMLReference's stored on this interface
			@return int32 giving count of objects in list stored
		 */
		virtual int32 Size(void) const = 0;
};

#endif		// __IXMLREFERENCELISTDATA__

