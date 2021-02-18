//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/IconEH.h $
//  
//  Owner: Tom Taylor
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
#ifndef __IconEH__
#define __IconEH__

#include "DVControlEventHandler.h"

/**
	Event handler for the basic icon widget type
*/
class WIDGET_DECL IconEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
public:
	IconEH(IPMUnknown *boss);
	virtual ~IconEH();

	/**
		Handle the button down event, clicking on a static text gives keyboard focus to the associated widget, if there is one.
		@param e - click event, standard event information
	*/
	virtual bool16 LButtonDn(IEvent* e);
};

#endif
