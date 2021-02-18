//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IListOfUIDLists.h $
//  
//  Owner: 
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
#ifndef __IListOfUIDLists__
#define __IListOfUIDLists__

#include "IPMUnknown.h"
#include "ContentDropperID.h"


class IListOfUIDLists : public IPMUnknown
{
public:	
	enum { kDefaultIID = IID_ILISTOFUIDLISTS};

	virtual bool16			IsEmpty() const = 0;	

	virtual const UIDList&	GetNthList(int32 nth) const = 0;

	virtual void			SetNthList(int32 nth, const UIDList& list) = 0;

	virtual void			AddList(const UIDList& list) = 0;

	virtual int32			GetSimilarListIndex(const UIDList* list) const = 0;

	virtual void			RemoveNthList(int32 nth) = 0;

	virtual int32			GetNumberOfLists() const  = 0;

	virtual UIDList			GetFlatList() const = 0;	

	virtual bool16			Contains(UID uid) const = 0;	


};

#endif //__IListOfUIDLists__
