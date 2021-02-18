//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IIMEPrefsCmdData.h $
//  
//  Owner: hhorton
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
//  Proj:	
//  
//========================================================================================

#pragma once
#ifndef _H_IIMEPrefsCmdData
#define _H_IIMEPrefsCmdData

#include "IPMUnknown.h"

/** 
	Interface for command to set preferences of Japanese 
	Inline input and IME (Input Method Editor) support
*/
class IIMEPrefsCmdData : public IPMUnknown
{
public:
	/** Set the flag to use the floating input window
		@param useFloatingInputWindow		true = useWindow, false = useInline
		@param useFakeInputWindow		obsolete
	*/
	virtual void Set(const bool16& useFloatingInputWindow, const bool16& useFakeInputWindow) = 0; 

	/** Get the flag to use the floating input window
		@return		useFloatInput		true = useWindow, false = useInline
	*/
	virtual bool16 GetUseFloatingInputWindow() = 0;

	/** obsolete
	*/
	virtual bool16 GetUseFakeInputWindow() = 0;
};


#endif	/* _H_IIMEPrefsCmdData */
