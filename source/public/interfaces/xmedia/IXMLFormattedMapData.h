//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLFormattedMapData.h $
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
//  
//  Purpose of Interface:
//  Hold information related to formatted images when exporting tagged images.  Formatted
//  images are different from copied and optimized images in that each image is unique because
//  of possible transformations that may have been applied to the image.
//  
//========================================================================================

#pragma once
#ifndef __IXMLFormattedMapData__
#define __IXMLFormattedMapData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** For internal use.
	This interface stores a map between XMLReference objects
	and PMString's which represent a format for images. Used when writing to an IXMLOutStream.
*/
class IXMLFormattedMapData : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_IXMLFORMATTEDMAPDATA};


		/**	Add a key-value pair to the map
			@param first key
			@param second value
		 */
		virtual void Insert(XMLReference first, const PMString& second) = 0;

		/**	Remove an entry corresponding to given key
			@param first 
		 */
		virtual void Erase(XMLReference first) = 0;

		/**	Erase contents of map stored on this interface
			
		 */
		virtual void Clear() = 0;
	

		/**	Accessor for size of map stored on this interface
			
			@return size of the map 
		 */
		virtual int32 Size() const = 0;

		/**	Accessor for value given key
			@param first specifies
			@return PMString  giving value stored given 'key'
		 */
		virtual PMString GetSecond(XMLReference first) const = 0;
};

#endif