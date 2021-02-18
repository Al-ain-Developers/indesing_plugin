//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/objectmodel/IDFactory.cpp $
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

#include "IDFactory.h"
#include "IObjectModel.h"
#include "ISession.h"

#ifdef REGISTER_OM_IDS

IDFactory* IDFactory::fgFirstID = nil;

IDFactory::IDFactory(const int32& space, const char* name, const int32& id) :
	fNextID(fgFirstID),
	fSpace(space),
	fName(name),
	fId(id)
{
	fgFirstID = this;
}

void IDFactory::InstallIDs(PluginID ownerComponent)
{
	InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);
	for (IDFactory *idFactory = fgFirstID; idFactory != nil; idFactory = idFactory->fNextID)
		om->RegisterID(ownerComponent, idFactory->fSpace, idFactory->fName, idFactory->fId);			

	// Transmit an invalid ID at the end, so that the object model will know that all
	// IDs for this plug-in have been registered.
	om->RegisterID(kInvalidPlugin, kPlugInIDSpace, nullptr, kInvalidPlugin.Get()) ;
}

#endif // REGISTER_OM_IDS

