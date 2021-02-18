//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/ClickableStaticTextView.h $
//  
//  Owner: lance bushore
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
#ifndef __ClickableStaticTextView__
#define __ClickableStaticTextView__

#include "CIDStaticTextView.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL ClickableStaticTextView : public CIDStaticTextView
{
	typedef CIDStaticTextView inherited;
	public:
		ClickableStaticTextView (IPMUnknown *boss) : inherited (boss) {}
		virtual ~ClickableStaticTextView() {}
		
		virtual void Init(const WidgetID& widgetId, const PMRect& bbox, RsrcID rsrcID);
		virtual void ReadWrite(IPMStream *s, ImplementationID prop);

	protected:
		virtual void	GetTextColors(RealAGMColor& enabledTextColor, RealAGMColor& disabledTextColor) const;

	private:
		void		CommonInit();

};

#pragma export off

#endif
