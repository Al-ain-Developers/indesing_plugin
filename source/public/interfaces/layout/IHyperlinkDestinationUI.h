//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkDestinationUI.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IHyperlinkDestinationUI_h__
#define __IHyperlinkDestinationUI_h__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

class IHyperlinkDestination;

/** Class responsible for going to hyperlink destinations.

	@ingroup layout_hyper
*/
class IHyperlinkDestinationUI : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKDESTINATIONUI };

	/**	Show the destination in the Layout Window
		@param none
	 */
	virtual void	GoToHyperlinkDestination(const IHyperlinkDestination* destination) const = 0;
};

#endif	// __IHyperlinkDestinationUI_h__
