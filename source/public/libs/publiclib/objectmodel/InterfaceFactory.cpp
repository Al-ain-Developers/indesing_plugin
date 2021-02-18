//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/objectmodel/InterfaceFactory.cpp $
//  
//  Owner: Robin_Briggs
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

#include "InterfaceFactory.h"
#include "IObjectModel.h"
#include "ISession.h"
#include "PMString.h"
#include "InterfacePtr.h"

InterfaceFactory *InterfaceFactory::gFirstInterface = nil;

InterfaceFactory :: InterfaceFactory(ImplementationID faceID, 
									 InterfaceConstructor faceFact, 
									 InterfaceDestructor faceDestroy, 
									 InterfaceSizeOf faceSizeOf, 
									 InterfaceReadWrite faceReadWrite, 
									 InterfaceReadWrite faceSnapshotReadWrite,
									 InterfaceResetViewFun resetViewFun) :
	fID(faceID),
	fFactory(faceFact),
	fDestructor(faceDestroy),
	fSizeOf(faceSizeOf),
	fReadWrite(faceReadWrite),
	fSnapshotReadWrite(faceSnapshotReadWrite),
	fInterfaceResetViewFun(resetViewFun),
	fNext(gFirstInterface)
{
	gFirstInterface = this;
}
 

void InterfaceFactory :: InstallInterfaces(PluginID ownerComponent)
{
	InterfacePtr<IObjectModel> om(GetExecutionContextSession(), IID_IOBJECTMODEL);
	for (InterfaceFactory *face = gFirstInterface; face != nil; face = face->fNext)		{
			om->FillOutInterfaceFactory(ownerComponent, face->GetID(), face->GetFactory(), face->GetDestructor(), face->GetSizeOf(), face->GetReadWrite(), face->GetSnapshotReadWrite(), face->GetInterfaceResetViewFun());
		}
}



