//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textimportfilter/CTxtImpFileReader.h $
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

#ifndef __CTxtImpFileReader_H__
#define __CTxtImpFileReader_H__


// General includes
#include "K2Assert.h"
#include "CPMUnknown.h"
#include "TextChar.h"

// Interface includes
#include "IPMStream.h"
#include "ITxtImpFileReader.h"


/** CTxtImpFileReader
	Provides a partial implementation for a file reader. 
	The only method that is missing is the GetNextTextChar, in which
	subclasses of CTxtImpFileReader will perform the actual conversions
	of various encodings to UNICODE, and store it in a local UTF16TextChar 
	buffer. 
 
	@ingroup textimportfilter
	
*/
class CTxtImpFileReader: public CPMUnknown<ITxtImpFileReader>
{
	public:
		/** Constructor 
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CTxtImpFileReader(IPMUnknown* boss);
	
		/** Destructor
		*/
		virtual ~CTxtImpFileReader(void);
	
		/** Sets the stream to read.
			@param stream IPMStream to read.
		*/
		virtual void SetStream(IPMStream* stream);

		/** Returns the stream (file) size in bytes.
		*/	
		virtual int32 GetFileSizeInBytes(void);
		
		/**	(pure abstract method) Gets next text char from internal text char buffer.
			If the buffer has been read until the end or is empty, it reads a chunk out
			the stream, converts the text to UNICODE, and stores it in the buffer.
			Subclasses must provide the implementation.
		*/
		virtual UTF16TextChar GetNextTextChar(void) = 0;

	protected:
		
		/** Stores IPMStream of currently opened stream (indicated by fFilename) */
		IPMStream* 	fStream;
		/** Stores a "chunk" of file text in a UNICODE buffer */
		UTF16TextChar*	fTCBuf;
		/** Stores bytes directly read from stream. This is the data before UNICODE conversion */
		uchar*		fCBuf;
		/** Stores length of stream. */
		int32 		fLen;
		/** Stores the current marker position within fTCBuf.  Used in GetNextTextChar.*/
		int32 		fCurrMarker;
		/** Stores the position of the last character within fTCBuf.  Used in GetNextTextChar. */
		int32 		fEndOfReadMarker;
	
};


#endif // ifndef __CTxtImpFileReader_H__

// End, CTxtImpFileReader.h.


