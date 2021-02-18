//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISnippetImport.h $
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
#ifndef __ISnippetImport_h__
#define __ISnippetImport_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

#include "SnippetID.h"
#include "IDOMElement.h"
#include "IPMUnknown.h"


/**	This is the main access point for reading in (importing) snippets of XML in INX format.
	You can use ISnippetExport to write objects out to INX. 
	
	Access this interface via the Utils<> helper.
	@see ISnippetExport
	@see Utils
*/
class ISnippetImport : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISNIPPETIMPORT };

			/** Import from a snippet in a stream, to make it a child of rootElement.
				@param stream - XML will is read in from this output stream (assumes whole stream is INX)
				@param rootElement - where in the ID document the objects read in should appear. 
				@param policyClass - which import policy to use (depends on type of snippet). kInvalidClass means it will figure it out.
				@param uiFlags - how to handle UI during the import process
				@param progressBarTitle IN A pointer to a PMString object to be used as the title of the progress bar, or nil.
				@return ErrorCode kSuccess if it worked
			*/
		virtual ErrorCode ImportFromStream(IPMStream *stream, IDOMElement *rootElement, ClassID policyClass = kInvalidClass, 
			UIFlags uiFlags = kFullUI, const PMString *progressBarTitle = nil) = 0;	
};

#endif	// __ISnippetImport_h__