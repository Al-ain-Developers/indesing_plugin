//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CIDStaticTextView.h $
//  
//  Owner: Vadim Tkachev
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
#ifndef __CIDStaticTextView__
#define __CIDStaticTextView__

/** class CIDStaticTextView

		Concrete implementation of the IControlView interface for static text views.  
		
		This is the default implementation used in InDesign icon static text widgets, kStaticTextViewImpl
		Clients seeking to make minor modifications to static text behaviors should derive from this class.
		
		This class replaces PlatformStaticTextView, which is now obsolete.
*/

#include "DVStaticTextView.h"

class WIDGET_DECL CIDStaticTextView : public DVStaticTextView
{
	typedef DVStaticTextView inherited;

public:
	CIDStaticTextView(IPMUnknown *boss);
	virtual ~CIDStaticTextView();
};


/** class CIDOwnerDrawStaticTextView

		Base implementation of for IControlView for owner-drawn static text views.  
		Clients seeking to make major modifications to static text behaviors (e.g. background fill, custom text drawing, adornments, etc.) should derive from this class.
		
		This class replaces PlatformStaticTextView, which is now obsolete.
*/

class WIDGET_DECL CIDOwnerDrawStaticTextView : public DVOwnerDrawnStaticTextView
{
	typedef DVOwnerDrawnStaticTextView inherited;

public:
	CIDOwnerDrawStaticTextView(IPMUnknown *boss);
	virtual ~CIDOwnerDrawStaticTextView();
};

#endif //__CIDStaticTextView__
