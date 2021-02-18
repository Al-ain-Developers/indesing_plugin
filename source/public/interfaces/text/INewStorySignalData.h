//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/INewStorySignalData.h $
//  
//  Owner: Roey Horns
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
#ifndef __INewStorySignalData__
#define __INewStorySignalData__

#include "IPMUnknown.h"
#include "TextID.h"

class ICommand;

/** Data sent with the newdoc signal
	@ingroup text_story
*/
class INewStorySignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_INEWSTORYSIGNALDATA };
	
	/**
	The signal data is loaded with the new story's UIDRef and possibly the creating command
	by the new story command.
	*/
	virtual void Set(ICommand *newStoryCmd, const UIDRef &textModel) = 0;

	/**
	Get the ICommand that created this new story. May be nil.
	*/
	virtual ICommand *GetNewStoryCmd() = 0;

	/**
	Get the UIDRef of the story that was just created. @see ITextModel.
	*/
	virtual const UIDRef &GetTextModel() const = 0;
};

#endif
		// __INewStorySignalData__

