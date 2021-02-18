//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PersistRealNumberData.h $
//  
//  Owner: Paul Sorrick
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
//  Interface for storing int32s persistently.
//  
//========================================================================================

#pragma once
#ifndef __PERSISTREALNUMBERDATA__
#define __PERSISTREALNUMBERDATA__

#include "IRealNumberData.h"
#include "HelperInterface.h"

/**  Data interface for storing a floating-point value (PMReal).
	@ingroup arch_coredata 
*/
class PersistRealNumberData : public IRealNumberData
{
public:
	/**	Constructor
		@return  
	 */
	PersistRealNumberData(IPMUnknown *boss);
	/**	Destructor
		@return  
	 */
	virtual ~PersistRealNumberData();

	/**	Set the real number
		@param r the number
		@return  
	 */
	virtual void Set(const PMReal& r); 
	/**	Get the real number
		@return  PMReal
	 */
	virtual const PMReal GetRealNumber() const;
	/**	ReadWrite
		@param s the stream
		@param prop the property
	 */
	virtual void ReadWrite(IPMStream *s, ImplementationID prop);
	
private:
	PMReal fRealNumber;

DECLARE_HELPER_METHODS()
};


#endif // __PERSISTREALNUMBERDATA__
