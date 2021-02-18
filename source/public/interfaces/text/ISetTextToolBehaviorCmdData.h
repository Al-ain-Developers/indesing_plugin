//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISetTextToolBehaviorCmdData.h $
//  
//  Owner: Dave Stephens
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
#ifndef __ISetTextToolBehaviorCmdData__
#define __ISetTextToolBehaviorCmdData__

#include "IPMUnknown.h"
#include "TextEditorModelID.h"

/** Command data interface for setting the behavior of the text tool.  
	This interface is used by the kSetTextToolBehaviorCmdBoss and currently
	allows the client to specify whether or not the text tool will convert
	a non-text frame to a text frame if the user clicks and releases the mouse
	within the contents of the non-text frame.
*/
class ISetTextToolBehaviorCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETTEXTTOOLBEHAVIORCMDDATA };

	typedef bool16		ValueType;

	/** 	Return the value stored by this interface
		@return The stored boolean
	*/
	virtual ValueType GetTextToolConvertsFrames() const = 0;
		
	/** 	Store a new boolean value into this interface.
		@param b The new boolean to store
	*/
	virtual void SetTextToolConvertsFrames(ValueType b) = 0;	
};


#endif // __ISetTextToolBehaviorCmdData__
