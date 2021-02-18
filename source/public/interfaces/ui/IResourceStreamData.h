//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IResourceStreamData.h $
//  
//  Owner: robin briggs
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
#ifndef __IResourceStreamData__
#define __IResourceStreamData__

#include "ShuksanID.h"

class IDataBase;
class RsrcSpec;

/** Interface used on resource stream objects to denote the resource to be read, and the database for the result.

		@see StreamUtil, IObjectTextFileStreamData
*/
class IResourceStreamData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRESOURCESTREAMDATA };
		/** Set the resource type and id to be read by the stream object. 
				Database is set if the stream implementation needs to create objects in a database as a result
				of reading data from the stream. 
				
				@see ResourceStreamRead, ObjectResourceStreamRead
		*/
		virtual void Set(const RsrcSpec& spec, IDataBase* db = 0, bool16 useLocaleIndex = kTrue) = 0;
		
		/** get the resource spec (type and id) */
		virtual const RsrcSpec& GetRsrcSpec() const = 0;
		/** get the database */
		virtual IDataBase* GetDataBase() const = 0;
		/** Get the "use locale index" flag */
		virtual bool16 GetUseLocaleIndex() const = 0;
};


#endif // __IResourceStreamData__
