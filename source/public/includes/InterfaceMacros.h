//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfaceMacros.h $
//  
//  Owner: Mat Marcus
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
//  This file contains alternative implementations for the CreatePMInterface macros in InterfaceFactory.h.
//  These new macros support template based implementations classes via a ReferenceByID
//  macro. Eventually we may replace the old macros with a variant of these.
//  
//========================================================================================

#pragma once
#ifndef __InterfaceMacros__
#define __InterfaceMacros__

#include "InterfaceFactory.h"
#define CREATE_PMINTERFACE_BYID(_TYPE, _ID) CREATE_PMINTERFACE(_TYPE, _ID)
#define CPMI(_TYPE, _ID) CREATE_PMINTERFACE(_TYPE, _ID)
#define CREATE_PERSIST_PMINTERFACE_BYID(_TYPE, _ID)  CREATE_PERSIST_PMINTERFACE(_TYPE, _ID)
#define CPMPI(_TYPE, _ID) CREATE_PERSIST_PMINTERFACE(_TYPE, _ID)
#define REFERENCE_PMINTERFACE_BYID(_ID) REGISTER_PMINTERFACE(_ID, _ID)
#define RPMIID(_ID) REGISTER_PMINTERFACE(_ID, _ID)


#endif //__InterfaceMacros__