//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/ICusDtLnkOptions.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __ICusDtLnkOptions_H_DEFINED__
#define __ICusDtLnkOptions_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "CusDtLnkID.h"

/** From SDK sample; stores options as set of key-value pairs in some kind
	of workspace

	@ingroup customdatalink
	@see kCusDtLnkChangeOptionsCmdBoss
	@see IWorkspace
*/
class ICusDtLnkOptions : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_ICUSDTLNKOPTIONS };

	/** Append an option to the list. 
		@param key the key that should be used to retrieve the value
		@param val the value to store
	*/
	virtual void AddKeyValuePair(const WideString& key, const WideString& val)=0; 

	/**	Return option given its key
		@param key identifies the key to retrieve the stored option
		@return WideString representing the value given the key
	 */
	virtual WideString GetValueFromKey(const WideString& key) const =0; 

	/**	Accessor for the nth key to retrieve a stored option
		@param index zero based index 
		@return WideString representing key at given index
	 */
	virtual WideString GetNthKey(const int32 index) const =0;

	/**	Determine how many options are stored
		@return int32 representing number of options stored
	 */
	virtual int32 GetKeyValuePairCount() const =0;
};


#endif // __ICusDtLnkOptions_H_DEFINED__



