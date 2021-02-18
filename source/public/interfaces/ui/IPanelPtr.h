//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelPtr.h $
//  
//  Owner: Frits Habermann
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
#ifndef __IPANELPTR__
#define __IPANELPTR__

#include "IPMUnknown.h"

class IControlView;

/**  A simple interface that encapsultes a pointer to a panel. Used several places
	where some code needs to know which panel to do something with.
*/
class IPanelPtr : public IPMUnknown
{
public:
	/**  Set the panel we're interested in.
		@param panel pointer to the panel we want to keep track of.
	*/
	virtual void			SetPanel(IControlView *panel) = 0;

	/**  Get the panel we're interested in.
		@return pointer to the panel we're keeping track of.
	*/
	virtual IControlView*	QueryPanel() const = 0;

	/**  Has a panel been set.
		@return whether a panel has been set. Checks for a panel, but will avoid reinstantiating if possible.
	*/
	virtual bool16			HasPanel() const = 0;
};

#endif