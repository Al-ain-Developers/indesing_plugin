//======================================================================================== 
//   
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CCollection.h $ 
//   
//  Owner: vaggarwa 
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
#ifndef __Collection__ 
#define __Collection__ 

// ----- Interfaces -----
#include "ICommand.h"

// ----- Includes -----
#include "ContentDropperTypes.h"
#include "BravoForwardDecl.h"
// ----- ID.h files -----
#include "ContentDropperToolID.h"

//======================================================================================== 
// class Collection 
//======================================================================================== 

class CCollection
{
public:
	explicit CCollection(int32 objType,IDataBase* db): fType(objType),fDb(db),fCaptureID(-1),fLinkPolicy(ContentDropperTypes::kUnknownPolicy) {};
	virtual ~CCollection(){};
	//For general operations on a colection
	
	virtual bool16 Find(UID)const = 0 ;
	virtual bool16 Remove(UID) = 0;	
	virtual bool16 RemoveNth(int32) = 0;	

	virtual CCollection* GetNthElement(int16) const = 0 ;
	virtual int32 GetNumberOfElements(void) const = 0 ;

	//returns UIDList of all the items in this collection. Flattened List with all the children 
	//@param - true if the returned list should be sorted in order of z-order, uses ArrangeUtils Sorting
	virtual const UIDList GetFlattenedUIDList(bool16 sorted = kTrue) const = 0 ;
	
	//Check operations that may be restricted
	virtual bool16 IsExpandable()const = 0 ;
	virtual bool16 CanUnbundle() const= 0 ;
	//virtual bool16 IsCollapsed()const = 0 ;
	

	//Preview handling
	virtual void ReadWrite(IPMStream* s, ImplementationID id) = 0; 

	virtual int32  GetType() const {return fType;}

	virtual bool16 GetPreview(CAGMImage & newImage, const uint32 maxWidth, const uint32 maxHeight) const = 0;

	virtual void SetCaptureID(int32 id) {fCaptureID = id;}
	virtual int32 GetCaptureID() const {return fCaptureID;}

	virtual void		 SetLinkPolicy(ContentDropperTypes::LinkPolicy linkPolicy) { fLinkPolicy = linkPolicy; }
	virtual ContentDropperTypes::LinkPolicy		 GetLinkPolicy() const { return fLinkPolicy; }

protected:
	int32 fType;		//stores identifier for each subclass type. CollectionFactory uses this.
	IDataBase* fDb;
	int32 fCaptureID;
	ContentDropperTypes::LinkPolicy fLinkPolicy;
};

#endif
