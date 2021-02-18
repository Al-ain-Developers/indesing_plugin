//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/mso/MSOBehaviorPanelTypes.h $
//  
//  Owner: Greg St. Pierre
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

#include "K2Pair.h"
#include "FormFieldTypes.h"

// This baloney is to work around the use of DropDownListControlDataOf<> in our DDLControlData impl.
// We can't use a simple typedef for UIDRef because we use the same type for animations as well
// (meaning we get a linker error on duplicate uses of DropDownListControlDataOf<UIDRef>). By
// wrapping the UIDRef in a simple struct like this we introduce a new type so we no longer conflict.

struct MSOTargetReference
{
	typedef object_type data_type;		// Grrr....
	
	UIDRef fReference;
	
	MSOTargetReference(IDataBase *db, UID const &uid) : fReference(db, uid) { }
};
