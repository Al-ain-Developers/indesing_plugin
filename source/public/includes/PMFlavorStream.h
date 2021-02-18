//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PMFlavorStream.h $
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
//  Provides an accessor class for obtaining and automatically releasing
//  Read or Write streams from data exchange data objects.
//  
//========================================================================================

#pragma once
#ifndef __PMFlavorStream__
#define __PMFlavorStream__

#include "IPMDataObject.h"
#include "PMFlavorTypes.h"

class IPMStream;

// -------------------------------------------------------------
// Class PMFlavorStream
// -------------------------------------------------------------
enum eFlavorStreamType {kReadFlavorStream = 0, kWriteFlavorStream = 1};

/** An accessor class for obtaining and automatically releasing
		Read or Write streams for data exchange data objects.
		
		@see IPMDataObject
*/
class PMFlavorStream
{
	public:			
			/** Constructor used to create the stream
				@param dataObject IN data object associated with the data stream
				@param flavor IN what external flavor will this stream contain
				@param type IN specify kReadFlavorStream or kWriteFlavorStream
			*/
			PMFlavorStream(IPMDataObject* dataObject, ExternalPMFlavor flavor, 
				eFlavorStreamType type = kReadFlavorStream)
				: fDataObject(dataObject), fStream(nil)
			{
				if (type == kReadFlavorStream)
					fStream = fDataObject->GetStreamForReading(flavor);
				else if (type == kWriteFlavorStream)
					fStream = fDataObject->GetStreamForWriting(flavor);
			}
			
			/** Destructor used to release the stream */
			~PMFlavorStream()
			{
				if (fStream != nil)
					fDataObject->FinishedWithStream(fStream);
				fDataObject = nil;
				fStream = nil;
			}
			
			/** convert to a stream */
			operator IPMStream*() { return fStream; }
				// We allow the cast operator to return a nil pointer
				// since it is valid to test against nil and may be valid
				// to pass a nil pointer to some methods.
			
			/** access as a stream */
			IPMStream* operator ->()
			{
			#ifdef DEBUG
				ASSERT_MSG(fStream != nil,"About to use nil PMFlavorStream!");
			#endif
				return fStream;
			}

	private:
		IPMDataObject* fDataObject;
		IPMStream * fStream;
};

#endif
