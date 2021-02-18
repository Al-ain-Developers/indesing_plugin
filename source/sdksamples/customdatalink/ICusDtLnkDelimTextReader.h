//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/ICusDtLnkDelimTextReader.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ICusDtLnkDelimTextReader_H_DEFINED__
#define __ICusDtLnkDelimTextReader_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "CusDtLnkID.h"


/** From SDK sample; for reading delimited text

	@ingroup customdatalink
*/
class ICusDtLnkDelimTextReader : public IPMUnknown
{

public:

	/** Default interface identifier for UseDefaultIID 
		@see UseDefaultIID
	*/
	enum { kDefaultIID = IID_ICUSDTLNKDELIMTEXTREADER };

	/**	Determine if we can read at least one record from the given stream
		@param inStream specifies the stream of interest
		@return bool16 kTrue if we can read a record from stream, kFalse otherwise
	 */
	virtual bool16 CanRead(IPMStream* inStream)=0;

	/**	Read one record from given stream
		@param inStream specifies stream of interest
		@param outputFields contains the values for the fields we read
		@return bool16 kTrue if we did read a record from stream, kFalse otherwise
	 */
	virtual bool16 ReadRecord(IPMStream* inStream, K2Vector<PMString>& outputFields) const = 0;	
};

#endif // __ICusDtLnkDelimTextReader_H_DEFINED__

