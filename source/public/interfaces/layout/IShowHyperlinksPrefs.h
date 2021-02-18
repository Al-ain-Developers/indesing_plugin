//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IShowHyperlinksPrefs.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IShowHyperlinksPREFS__
#define __IShowHyperlinksPREFS__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

/** Used to store/get whether hyperlinks should be shown in the layout */
class IShowHyperlinksPrefs : public IPMUnknown
{
public:	
 	enum { kDefaultIID = IID_ISHOWHYPERLINKSPREFERENCES };
 
	/** Allows the user to determine whether hyperlinks should be shown
		@param bShown - kTrue will show hyperlinks, kFalse will not
	*/
	virtual void SetShowHyperlinks(const bool16 bShown) = 0;

	/** Indicates to the client whether hyperlinks should be shown
		@return kTrue means show hyperlinks, kFalse means do not
	*/
	virtual const bool16 GetShowHyperlinks() = 0;
};

#endif
