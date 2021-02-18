//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IDFactory_fr.h $
//  
//  Owner: Michael Burbidge
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

#ifndef __IDFactory_fr_h__
#define __IDFactory_fr_h__
#include "IDFactory.h"

#ifdef REGISTER_OM_IDS

#undef DECLARE_PMID
#undef START_IDS
#undef END_IDS

#define RESOURCE_NUMBER	__LINE__

#define DECLARE_PMID(space, name, id)	 space, #name, id, 

#define START_IDS()	resource IDNameList (RESOURCE_NUMBER)	{	{	
	
#define END_IDS()	}	};



#endif // REGISTER_OM_IDS

#endif // __IDFactory_fr_h__
