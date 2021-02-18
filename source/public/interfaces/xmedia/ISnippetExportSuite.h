//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISnippetExportSuite.h $
//  
//  Owner: Robin_Briggs
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

#ifndef __ISnippetExportSuite__
#define __ISnippetExportSuite__

#include "IPMUnknown.h"
#include "SnippetID.h"

/** Suite to handle snippet export
*/
class ISnippetExportSuite : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ISNIPPETEXPORTSUITE };

		/**	Can we export the target to a snippet?
			@return kTrue if export can be done
		*/
		virtual bool16	CanExport() const = 0;

		/**	Export the file to a snippet.
			@param stream - directs where the snippet is streamed to
			@return ErrorCode - kSuccess if it worked, error code otherwise
		*/
		virtual ErrorCode	DoExport(IPMStream *stream) = 0;
};


#endif // __ISnippetExportSuite__

