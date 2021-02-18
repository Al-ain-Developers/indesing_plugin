//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/BehaviorSelectionSuiteData.h $
//  
//  Owner: Michael Brubidge
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
#ifndef __BehaviorSelectionSuiteData_h__
#define __BehaviorSelectionSuiteData_h__

#include "ISelectionMessages.h"

//========================================================================================


/** Defines the interface for the Behavior Selection suite data to be used in the new selection architecture.
	@see IBehaviorSuite
	@see SelectionSuiteData
*/
class BehaviorSelectionSuiteData : public SelectionSuiteData
{
public:
	/** Construct a new BehaviorSelectionSuiteData object
		@param message ID of the message
		@param data Data associated with the message
	*/
	BehaviorSelectionSuiteData(const PMIID& message, const void* data) :
				fMessage(message), fData(data) { }
				
	/** Get the ID of the message
		@return ID of the message
	*/
	PMIID GetMessage() const { return fMessage; }
	
	/** Get the data associated with the message
		@return Data associated with the message
	*/
	const void* GetData() const { return fData; }
	
private:
	PMIID	fMessage;
	const void*	fData;
};

#endif // __BehaviorSelectionSuiteData_h__
