//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IPMStringMapData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IPMStringMapData__
#define __IPMStringMapData__

#include "IPMUnknown.h"
#include "XMLID.h"

/** This interface describes a tag to style mapping used when importing an XML document
	and applying predefined paragraph styles to the text.  It belongs to the document workspace.
*/
class IPMStringMapData : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IPMSTRINGMAPDATA};


		/**	Add a key value pair to the associative map
			@param first key to use when adding entry to the map
			@param second value to associate
		 */
		virtual void Insert(const PMString& first, const PMString& second) = 0;

		/**	Remove a given key-value mapping by specifying the key
			@param first specifies key for key-value pair to remove
		 */
		virtual void Erase(const PMString& first) = 0;

		/**	Remove all the entries in the map
			
		 */
		virtual void Clear() = 0;
	

		/**	Return the size of the set of key-value pairs
			
			@return int32 count of key-value pairs in the mapping
		 */
		virtual int32 Size() const = 0;

		/**	Given a key, return the associated value if it can be found
			@param first 
			@return PMString specifying the value associated with given key
		 */
		virtual PMString GetSecond(const PMString& first) const = 0;
};

#endif