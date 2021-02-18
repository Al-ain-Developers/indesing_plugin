//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStoryLabel.h $
//  
//  Owner: Scott Binns
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

#include "IPMUnknown.h"
#include "WideString.h"
#include "InCopySharedID.h"

#pragma once
#ifndef __IStoryLabel__
#define __IStoryLabel__

/** This class is used to get/set a label (name) for a story so that we know which story we are working on */
class IStoryLabel : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISTORYLABEL }; 
	
		//----------------------------------------------------------------------------------------
		//	GetLabel
		//
		//	Try to get the label from the story metadata (XMP data)
		//	else
		//	use the filename from the datalink
		//	else
		//	use "Untitled Story" + story list index (if more than one user accessible story).
		//
		//	Returns a non-empty string.
		//----------------------------------------------------------------------------------------
		/** Returns the name of the story so it can be differenciated from others.
			@return - non-empty string containing the name of the story. The name of the story
			is one of the following (in this order):
			1. The label from the story metadata (XML data)
			2. The filename from the datalink
			3. "Untitled Story" + story list index (if more than one user accessible story)
		*/
		virtual PMString GetLabel() = 0;

		//----------------------------------------------------------------------------------------
		//	SetLabel
		//
		//	Uses commands to set the title field in story metadata (XMP data), creates a new 
		//	metadata structure if story metadata does not exist.
		//----------------------------------------------------------------------------------------
		/** Set the label (name) of this story
			@param &label - New name to use for this story
			@return - kSuccess if everything went OK
		*/
		virtual ErrorCode SetLabel(
			const PMString& label
			) = 0;

		/** General method for reading from or writing to a stream
			@param *s - The stream to use
			@param prop - The implementation ID
		*/
		virtual void ReadWrite(
			IPMStream *s,
			ImplementationID prop
			) = 0;		
};

#endif //__IStoryLabel__
