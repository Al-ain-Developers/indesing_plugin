//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/StaticMultiLineTextView.h $
//  
//  Owner: Rich Gartland
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
//  
//  Header for Static Multi-Line Text class
//  
//========================================================================================

#pragma once
#ifndef __StaticMultiLineTextView__
#define __StaticMultiLineTextView__

#include "DVStaticMultiLineTextView.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

// StaticMultiLineTextView for pre-CC ompatibility. Adds no additional behavior over DVStaticMultiLineTextView

class WIDGET_DECL StaticMultiLineTextView : public DVStaticMultiLineTextView
{
	typedef DVStaticMultiLineTextView inherited;
public:
						StaticMultiLineTextView(IPMUnknown *boss);
	virtual 			~StaticMultiLineTextView();
};

#pragma export off

#endif //__StaticMultiLineTextView__
