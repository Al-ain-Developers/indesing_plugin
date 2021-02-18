//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/layout/SelectionUtils.h $
//  
//  Owner: Michael Martz
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
//  Note: This file is intended to replace SelectUtils.h. 
//  It is used with the new selection architecture.
//  
//========================================================================================

#pragma once
#ifndef _SelectionUtils_
#define _SelectionUtils_

#include "ISelectionUtils.h"
//________________________________________________________________________________________________
//	Class Declaration
//________________________________________________________________________________________________
namespace SelectionUtils
	{
		//________________________________________________________________________________________
		// This works like the original QuerySuite(const PMIID&, ISelectionManager* = nil), but you can omit
		// the interface ID if the suite interface defines kDefaultIID, and the correct suite pointer is
		// returned. Usage is like this: mySuite = SelectionUtils::QuerySuite<ITableSelectionSuite>().
		//________________________________________________________________________________________
		template <class SUITE>									
		inline SUITE* QuerySuite(ISelectionManager* selectionManager = nil)	// do not forward declare these: CW Pro 5 won't inline them if they're forward declared...
		{	
			IPMUnknown* face = Utils<ISelectionUtils>()->QuerySuite(SUITE::kDefaultIID, selectionManager);
			return static_cast<SUITE*>(face);
		}
}
	
#endif // _SelectionUtils_
