//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/incopy/IContainerClassification.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IContainerClassification__
#define __IContainerClassification__

#include "WritingModeID2.h"
#include "IPMUnknown.h"

/** A class to provide further identification of types of text containers. Currently,
	the containers are text frames but this may be attached to parcels in the future
	so the name is kept somewhat generic. This class is only used in InCopy.
	@author Kevin Van Wiel
*/
class IContainerClassification : public IPMUnknown
{
public:
	/** Standard enum to for use with GetDefaultIID() method.
	*/
	enum { kDefaultIID = IID_ICONTAINERCLASSIFICATION };

	/** This enum provides options for different types of text containers
	*/
	typedef enum { kOversetContainer, kRegularTextContainer } Classification;
	
	/** 	Get the type of composition container. May be of two types regular or overset.
			This is of no relavance to the actual composer it is simply used by the galley
			view code to determine how to draw the text. As overset or regular. It is also
			used to modify some behaviors like fillwithplaceholder text so that instead of
			filling to the last text container it only fills to the last regular text.
			container. No longer const to fix issue with purging where data would
			be lost so if purged the value is dynamically recalculated at get time.
			Currently only used in the InCopy Code base 11/8/2002
			@return container classification of type enum Classification
	*/
	virtual	Classification				GetClassification() = 0;
	
	/** 	Set the type of composition container. May be of two types regular or overset.
			This is of no relavance to the actual composer it is simply used by the galley
			view code to determine how to draw the text. See comments for GetClassification
			method.
			@param enum of one of two types kOversetContainer or kRegularTextContainer
			@return none
	*/	
	virtual	void						SetClassification(Classification category) = 0;
};


#endif // __IContainerClassification__
