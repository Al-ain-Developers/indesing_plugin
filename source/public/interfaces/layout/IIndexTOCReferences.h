//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexTOCReferences.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IIndexTOCReferences__
#define __IIndexTOCReferences__

#include "LinksID.h"

class UIDList;

class IIndexTOCReferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINDEXTOCREFERENCES };
	
	virtual void AddReferencesToList(UIDList *list) = 0;
	virtual void RemoveReferences(UIDList *list) = 0;
	virtual UIDRef GetNthReferenceUID(int32 index) = 0;
	virtual int32 GetNumReferences() = 0;
	virtual int32 GetReferenceIndex(UID whichUID) = 0;
};

#endif