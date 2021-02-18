//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicmenu/IBscMnuSuite.h $
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

#ifndef _IBscMnuSuite_
#define _IBscMnuSuite_

//	INCLUDES
#include "ShuksanID.h"
#include "BscMnuID.h"

class IPMUnknown;

//	CLASS DECLARATION

/** From SDK sample; provides an dummy interface to get to the current selection.

	@ingroup basicmenu
	
*/
class IBscMnuSuite : public IPMUnknown
{
//	Data Types
public:
	enum { kDefaultIID = IID_IBSCMNU_ISUITE };

//	Member functions
public:
	/**
		@return kTrue if the user can apply BscMnu (in this sample, doing nothing but pops a dialog) 
		with the current selection, kFalse otherwise
	*/
	virtual bool16			CanApplyBscMnu(void) = 0;
};

#endif // _IBscMnuSuite_


