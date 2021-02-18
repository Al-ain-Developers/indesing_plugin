//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/MuteBackingStoreSubject.h $
//  
//  Owner: Matt Joss
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
//  Purpose:
//  Helper class for muting the ISubject of the backing store.  For many commands,
//  we don't want to broadcast their subcommands.  Clients should just be able to listen for 
//  The higher level commands
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IDataBase.h"
#include "IDocument.h"
#include "IXMLUtils.h"
#include "IIDXMLElement.h"
#include "ISubject.h"

class MuteBackingStoreSubject
{
	public:
		MuteBackingStoreSubject(IDataBase*	db) : fSubject(nil), fWasMuted(kFalse)
		{			
			// -- We have to hang on to the subject here because it is not persistant.  With the instance cache
			// -- turned off the state of mute gets lost as soon as ISubject goes out of scope.  Then the next
			// -- time it is instantiated it gets un-muted.  Hanging on to the subject will ensure that the
			// -- mute state will persist as long as this class is in scope. [LDM]
		/*	fSubject = (ISubject*)Utils<IXMLUtils>()->GetBackingStore(db).Instantiate(IID_ISUBJECT);
			if (fSubject)
			{
				fWasMuted = fSubject->IsMuted();
				fSubject->Mute(kTrue);
			}*/
 		}
 		
		~MuteBackingStoreSubject()
		{
		/*	if (fSubject)
			{
				if (!fWasMuted)
					fSubject->Mute(kFalse);
					
				fSubject->Release();
				fSubject = nil;
			}*/
		}

	
	private:
		MuteBackingStoreSubject() {}
		
		ISubject* fSubject;
		bool16 fWasMuted;
};
