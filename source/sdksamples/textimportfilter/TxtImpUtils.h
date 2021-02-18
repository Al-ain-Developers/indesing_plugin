//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/TxtImpUtils.h $
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

#ifndef __TxtImpUtils_H__
#define __TxtImpUtils_H__

// Interface includes
#include "ITxtImpFileReader.h"
#include "IIntData.h"

/** TxtImpUtils
	Implements various utility functions that help in the process of
	importing text files, as featured in the TextImportFilter. 

	@ingroup textimportfilter
	
*/
class TxtImpUtils
{
public:
    /** Obtains the actual ITxtImpFileReader interface for the corresponding encoding.
	    @param encoding The encoding for which you want the ITxtImpFileReader implementation.  
			    See ITxtImpFileReader::Encoding.
    */
    static ITxtImpFileReader* QueryTxtImpFileReader(ITxtImpFileReader::Encoding encoding);

	/** Detects the encoding type from the a uchar buf.
		@param buf A uchar array that contains characters in some Japanese encoding.
		@param bufSize Number of bytes in the uchar array.
		@return ITxtImpFileReader::Encoding. If not recognized, it will return Invalid.
	*/
	static ITxtImpFileReader::Encoding DetectJapaneseEncodingType(uchar* buf, int32 bufSize);
};
#endif // #ifndef __TxtImpUtils_H__

// End, TxtImpUtils.h.


