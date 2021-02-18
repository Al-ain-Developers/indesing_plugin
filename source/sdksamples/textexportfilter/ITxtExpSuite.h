//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/ITxtExpSuite.h $
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

#ifndef _ITxtExpSuite_
#define _ITxtExpSuite_

class IPMUnknown;
#include "ITxtExpFileWriter.h"
/**
	From SDK sample; interface added by this plug-in that allows
	client code to export the selected text into its own format.

	@ingroup textexportfilter
	
	@see TxtExpSuiteASB
	@see TxtExpSuiteTextCSB
*/
class ITxtExpSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITXTEXPSUITE };

public:
	/**
		@param formatName IN the export format name, must be the one we support to return kTrue.
		@return kTrue if there is text focus, in that case, we will export the selected text or the whole
		text story.
	*/
	virtual bool16 CanExportText(const PMString& formatName) = 0;

	/**
		Export the text. 
		@param fileStreamWrites IN the the writes stream used to output text.
		@precondition CanExportText == kTrue
		@return kSuccess if the export operation is successful
	*/
	virtual ErrorCode DoExportText(IPMStream *fileStreamWrites, ITxtExpFileWriter::Encoding encoding) = 0;

};

#endif // _ITxtExpSuite_


// End, ITxtExpSuite.h


