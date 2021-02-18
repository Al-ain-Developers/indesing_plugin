//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocTempFolder.h $
//  
//  Owner: Paul J. Messmer
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
//  Purpose:	Change location of temp folder (recovery) for user documents
//  
//========================================================================================

#pragma once
#ifndef __IDOCTEMPFOLDER__
#define __IDOCTEMPFOLDER__

#include "IPMUnknown.h"
#include "WorkspaceID.h"
#include "DocumentID.h"

class IDocTempFolder : public IPMUnknown
{
public:
 	enum { kDefaultIID = IID_IDOCTEMPFOLDER };
 
	virtual void ActivateFolder () = 0;
	virtual void SetFolder (const IDFile &folder) = 0;
	virtual void GetFolder (IDFile &folder) const = 0;
};

#endif // __IDOCTEMPFOLDER__

