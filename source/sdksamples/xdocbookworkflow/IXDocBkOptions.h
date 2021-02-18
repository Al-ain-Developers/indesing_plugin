//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/IXDocBkOptions.h $
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

#ifndef __IXDocBkOptions_H_DEFINED__
#define __IXDocBkOptions_H_DEFINED__

// Interface includes:
#include "IPMUnknown.h"

// Project includes:
#include "XDocBkID.h"

/** From SDK sample; stores options.

	@ingroup xdocbookworkflow
	@see kXDocBkChangeOptionsCmdBoss
	@see kWorkspaceBoss
*/
class IXDocBkOptions : public IPMUnknown
{

public:
	enum { kDefaultIID = IID_IXDOCBKOPTIONS };

	/** Append an option to the list. If the index you specify is outwith the length, then it'll get appended to the list
		@param newVal IN new value to add to existing list of options.
		@param indexWhere IN where you want it in the list of options, zero based.
	*/
	virtual void AddOption(const WideString& newVal, const int32 indexWhere)=0; 

	/**	Return option at given index in list
		@param index IN zero-based index
		@return PMString 
	 */
	virtual WideString GetNthOption(const int32 index)=0; 

	virtual int32 GetOptionCount()=0;
};


#endif // __IXDocBkOptions_H_DEFINED__



