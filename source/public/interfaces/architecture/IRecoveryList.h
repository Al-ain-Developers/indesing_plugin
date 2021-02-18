//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IRecoveryList.h $
//  
//  Owner: Roey Horns
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
#ifndef __IRecoveryList__
#define __IRecoveryList__

#include "IPMUnknown.h"
#include "PMString.h"
#include "DocumentID.h"

class IRecoveryList : public IPMUnknown
{
public:
		// Methods for Default Pub Recovery (accessed by CSession)
	virtual bool16 DefaultFileWasOpen() const = 0;
	virtual const IDFile *GetDefaultMiniSaveFile() const = 0;
	virtual void SetDefaultMiniSaveFile(const IDFile *file) = 0;
	virtual void StartDefaultFileRecovery() = 0;
	virtual void EndDefaultFileRecovery() = 0;
	virtual bool16 InDefaultFileRecovery() = 0;
		
		// Recovery Control
	virtual void DoRecovery() = 0;
	virtual bool16 InRecovery() const = 0;
	
		// Recovery List Maintainance
		// The doc interface could be a regular InDesign document or 
		// book file or some other special files we may support later.
	//virtual void AddDocument(IPMUnknown	*doc, ClassID commandID = kRecoverDocumentCmdBoss) = 0;
	virtual void AddDocument(IPMUnknown	*doc, ClassID commandID = kInvalidClass) = 0;
	virtual void UpdateDocument(IPMUnknown	*doc) = 0;
	virtual void RemoveDocument(IPMUnknown	*doc) = 0;
};

#endif // __IRecoveryList__