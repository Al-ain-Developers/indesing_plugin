//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IWritingStoryList.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IWritingStoryList__
#define __IWritingStoryList__

#include "WritingModeUIID2.h"
class IDocument;

/**
	IWritingStoryList (on kWritingModeWidgetBoss) a simple interface that will give a list of the stories displayed in a story or galley view panel. 
	Note this is not used in the current internal code and there are other ways of getting this information. The most common and recommended method
	would be to get an ITextLines interface and ask it for the list of stories via the GetStoryRefList() method. The IWritingStoryList interface
	should be equivalent but it goes through a different mechanism to get the information.
*/
class IWritingStoryList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IWRITINGSTORYLIST};

		/** 
			Get a list of stories displayed in the story/galley window
			@param doc - document this panel belongs to. Can get from IDocRef
			@param stories - list of stories displayed in the window is returned in this paramater
			@return none
		*/
		virtual void GetStoryList(IDocument *doc, UIDList& stories) const = 0;
};

#endif 		// __IStoryRefData__