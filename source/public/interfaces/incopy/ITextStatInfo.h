//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITextStatInfo.h $
//  
//  Owner: Matt Ramme
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
#ifndef _ITEXTSTATINFO_H_
#define _ITEXTSTATINFO_H_

#include "IPMUnknown.h"
#include "GalleyInfoID.h"

/** 
	Some methods for calculating statistics on text stories. Related used by the InCopy text statistics ui.
*/
class ITextStatInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITEXTSTATINFO };

	/** Call this to Update the text stats ui
		@param forceUpdate - normally calling this function won't necessarily recalculate the text statistics unless something is changed. Passing true will force a recaclulation
		@param fitExchanging - internal use pass false (default)
	**/
	virtual void		Update(bool16 forceUpdate = kFalse, bool16 fitExchanging = kFalse) = 0;
		
 	/** Get the current number of lines displayed in the ui
	**/
  	virtual uint32		GetLines() = 0;
  	
  	/** Get the current word count displayed in the ui
	**/
  	virtual uint32		GetWords() = 0;
  	
   	/** Get the current character count displayed in the ui
	**/
  	virtual uint32		GetCharacters() = 0;

   	/** Internal use only; Sets whether the numbers are up to date.
		@param isCurrent - kTrue is current false otherwise.
	**/
	virtual void		Current(bool16 isCurrent) = 0; 
	
   	/** Get whether the numbers stats are up to date, appears to be not used anymore may be removed
		@return kTrue if they are up to date
	**/	
	virtual bool16		IsCurrent() = 0;

};

#endif //_ITEXTSTATINFO_H_