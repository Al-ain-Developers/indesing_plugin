//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyWorkflow.h $
//  
//  Owner: 
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
#ifndef __IInCopyWorkflow__
#define __IInCopyWorkflow__

#include "IPMUnknown.h"

#include "UIDRef.h"

#include "InCopyWorkflowID.h"

class IInCopyImportOptions;
class IPMStream;

/**
	IInCopyWorkflow is the main developer access to import a story from an
	InCopy INCD file/stream.
	
	Exporting to InCopy INCD is no longer supported.

	An InCopy INCD file is an XML based format that uses namespaced element names
	and attributes. See InCopyImportExportDefs.h and InCopyCharAttrElemNames.h
*/

class IInCopyWorkflow : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYWORKFLOW };

	/**
		Import the story from the given stream.  
		@param storyRef The target story to import into. If this story is brand new story 
		intended to replace another story, the other story can be specified in the 
		storyBeingReplaced parameter (see below).
		@param iInStream The input stream to parse the XML from.
		@param options Options the caller can provide to control the import. The
		classID kInCopyImportOptionsBoss can be used by the caller as the 
		container class for the interface.  In other words, the caller does not 
		need to have their own implementation of this interface.
		@param storyBeingReplaced The story the target story is replacing. Can be set
		if the method wants to preserve any data such as inline graphics from the original story. 
		Import providers should set this parameter in their ImportThis
		methods, since the place behavior sometimes causes stories to be replaced entirely. 
		In that case, ImportStory can copy data from storyBeingReplaced
		into the new target story before storyBeingReplaced is deleted.
		@return An ErrorCode if there is some error importing, kSuccess otherwise.
	*/
	virtual ErrorCode ImportStory
							(
								const UIDRef&			storyRef,
								IPMStream*				iInStream,
								IInCopyImportOptions* 	options,
								const UIDRef&			storyBeingReplaced = UIDRef::gNull
							) = 0;

};


#endif // __IInCopyWorkflow__

