//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateDocument.h $
//  
//  Owner: ???
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

#ifndef __SnipCreateDocument_h__
#define __SnipCreateDocument_h__

/** 
	\li	How to create a new document and put it on view in a window,
	\li	uses SDKLayoutHelper to perform the document action,
	\li	the page dimensions, total number of pages and number of pages 
		in each spread can be given.

  	@ingroup sdk_snippet
	@ingroup sdk_layout
	
	@see SDKLayoutHelper
 */
class SnpCreateDocument
{
	public:
		/** Create a document and put it on view in a window.

			@param uiFlags IN
			@param width IN width of page in points
			@param height IN height of page in points
			@param numPages IN number of pages
			@param numPagesPerSpread IN number of pages per spread
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode Create(const UIFlags uiFlags,
			const	PMReal& width, 
			const	PMReal& height, 
			const	int32 numPages, 
			const	int32 numPagesPerSpread);
};


#endif // __SnipCreateDocument_h__

//End, SnipCreateDocument.h


