//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ICopyStreamData.h $
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
#ifndef __ICopyStreamData__
#define __ICopyStreamData__

#include "ShuksanID.h"

class IXferBytes;
class IDataBase;

/** Data interface for controlling a copy stream. Copy streams are sometimes used
	to copy the data out of an object, into a stream, or to instantiate an object
	that was copied out. This is very low level functionality; look in ScrapUtils
	to see if that can meet your needs before using copy streams. Even if you do
	need a copy stream, normally you can get the stream from StreamUtil instead of
	setting it up yourself. This interface is only useful if you get passed a stream
	and need to know what its target is.
@see ScrapUtil
@see StreamUtil
@ingroup arch_db
*/
class ICopyStreamData : public IPMUnknown
{
	public:
		/** Set the information required for the copy.
			@param srcDB	source database
			@param destDB	destination database
			@param xferBytes	underlying stream data
		*/
		virtual void Set(IDataBase *srcDB, IDataBase *destDB, IXferBytes *xferBytes) = 0;

		/** Get the source database for the copy
			@return source database
		*/
		virtual IDataBase *GetSourceDataBase() const = 0;

		/** Get the destination database for the copy
			@return destination database
		*/
		virtual IDataBase *GetDestinationDataBase() const = 0;

		/** Get the stream bytes for the copy
			@return stream bytes
		*/
		virtual IXferBytes *GetXferBytes() const = 0;
};


#endif // __ICopyStreamData__
