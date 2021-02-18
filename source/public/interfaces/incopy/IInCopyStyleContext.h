//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyStyleContext.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IInCopyStyleContext__
#define __IInCopyStyleContext__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

class WideString;
class AttributeBossList;

class IInCopyStyleContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYSTYLECONTEXT };

	// Init the list with the story.  Also, tell the context whether
	// to create paragraph styles or character styles
	virtual void Initialize (const UIDRef& storyRef, bool16 isParagraph) = 0;

	// Add the style.  This takes ownership of the text attributes
	virtual void AddStyle
					(
						const WideString&			styleName,
						const WideString&			basedOnStyleName,
						const WideString&			nextStyleName,
						bool16						isImported,
						AttributeBossList*			textAttributes
					) = 0;
				
	// The style context doesn't do anything until Create is called.  This is because
	// some styles are based on other styles and have follow on styles that might not be
	// defined at the time we are processing the style.  Therefore the style context caches
	// a list of the styles as they are processed and then creates them when Create is called
	virtual void CreateStyles() = 0;
	
};


#endif // __IInCopyWorkflow__




