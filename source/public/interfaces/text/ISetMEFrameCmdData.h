//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISetMEFrameCmdData.h $
//  
//  Owner:
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
//  Usage rights licenced to Adobe Inc. 1993 - 2007.
//  
//========================================================================================

#ifndef __ISetMEFrameCmdData__
#define __ISetMEFrameCmdData__

#include "IPMUnknown.h"

#include "WorldReadyID.h"

/** This data interface is used by a number of commands to describe how the frame
	is supposed to be created: right-to-left or left-to-right reading order?
*/
class ISetMEFrameCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISETMEFRAMECMDDATA };

		enum { kUndefined=0, kCreation, kRight, kLeft };

		/** Set the created frame's writing direction.
		@param type is the desired writing direction.
		*/
		virtual void	SetType( const int32  type ) = 0;
		/** Get the created frame's desired writing direction.
		@return the desired writing direction.
		*/
		virtual int32	GetType() const = 0;
};

#endif
