//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLStreamUtils.h $
//  
//  Owner: chris parrish
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
#ifndef __IXMLSTREAMUTILS__
#define __IXMLSTREAMUTILS__

#include "XMLID.h"
#include "Utils.h"
#include "IXMLOutStream.h"

/** Aid in the creations of XML output streams.
	These methods create the stream and attempt to open it.
	The return value is nil if the stream could not open.
	
	For instance:
	<pre>
	InterfacePtr&lt;XMLOutStream&gt; s(CreateXMLOutFileStream(myFile, IXMLOutStream::kUTF16));
	if (s) {
		... 
		// use stream
		// and close when done to flush and clean-up
		s->Close();
	}
	else {
		...
		// handle error...
	}
	</pre>
*/
class IXMLStreamUtils : public IPMUnknown
{
public:
	enum	{kDefaultIID = IID_IXMLSTREAMUTILS};
	

	/**	Method to create an XML output stream on a file. You must call Close() on the stream to ensure complete
		flushing and cleanup when done with the stream

		@param file specifies the file target that the content will be streamed to
		@param encoding specifies encoding type for output file
		@param stripInvalid determines if invalid Unicode chars are stripped from the output
			or converted to processing instructions that contain their hexidecimal equivalent
		@return  xml stream that wraps a file system stream, nil if stream could not be opened
	 */
	virtual IXMLOutStream*	CreateXMLOutFileStream(const IDFile& file, IXMLOutStream::eEncodingType encoding, bool16 stripInvalid = kTrue) = 0;

	/**	Method to create an XML output stream on an existing IPMStream, which could be file or memory based.
		You must call Close() on the stream to ensure complete
		flushing and cleanup when done with the stream

		@param stream existing IPMStream
		@param encoding one of the encoding types in IXMLOutStream
		@param stripInvalid determines if invalid Unicode chars are stripped from the output
			or converted to processing instructions that contain their hexidecimal equivalent
		@return xml stream that wraps a PMStream, nil if stream could not be opened
	 */
	virtual IXMLOutStream*	CreateXMLOutPMStream(IPMStream* stream, IXMLOutStream::eEncodingType encoding, bool16 stripInvalid = kTrue) = 0;
	
};

#endif