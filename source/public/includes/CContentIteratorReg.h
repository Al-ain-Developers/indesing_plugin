//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CContentIteratorReg.h $
//  
//  Owner: Steve Pellegrin
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
#if !defined(__CContentIteratorReg__)
#define __CContentIteratorReg__


// ----- Interfaces -----

#include "IContentIteratorRegister.h"

// ----- Includes -----

#include "K2Vector.h"

// ----- Utility files -----

#include "SchemaUtils.h"


class FormatID;
class VersionID;


//========================================================================================
//	CLASS CContentIteratorRegister
//========================================================================================

#ifdef PUBLIC_BUILD
#pragma export on
#endif


/** CContentIteratorRegister is a useful base class for implementing IContentIteratorRegister
    in situations where all of the iterators are schema-driven. This class will do most of the
	work for you, generating input iterators that are driven by information found in the schemas.
	Public methods are uncommented here because they are documented in IContentIteratorRegister.
	@see IContentIteratorRegister
*/
class  PUBLIC_DECL CContentIteratorRegister : public IContentIteratorRegister
{
public:
	CContentIteratorRegister();
	
	virtual uint32 GetClassIDCount();
	virtual void GetNthClassID(uint32 n, ClassID &id);
	
	virtual uint32 GetImplementationIDCount();
	virtual void GetNthImplementationID(uint32 n, ImplementationID &id);	
	
	virtual IContentReadIterator *NewNthClassReadIterator(uint32 n, const VersionID &version, IPMStream *s);
	virtual IContentWriteIterator *NewNthClassWriteIterator(uint32 n, const VersionID &version, IPMStream *s);
	
	virtual IContentReadIterator *NewNthImplementationReadIterator(uint32 n, const VersionID &version, IPMStream *s);
	virtual IContentWriteIterator *NewNthImplementationWriteIterator(uint32 n, const VersionID &version, IPMStream *s);
	
protected:
	/** Return a referenced input iterator based on a schema that describe the class data format.
	    @param classID IN The class to be iterated
		@param version IN The class data format
		@param s IN An input stream that contains the data in the specified format
		@return A referenced instance of IContentReadIterator
	*/
	IContentReadIterator *NewSchemaReadIterator(ClassID classID, const VersionID &version, IPMStream *s)
		{return NewClosestSchemaReadIterator(true, classID.Get(), version, s);}

	/** Return a referenced input iterator based on a schema that describes the implementation data format.
	    @param implID IN The implementation to be iterated
		@param version IN The implementation data format
		@param s IN An input stream that contains the data in the specified format
		@return A referenced instance of IContentReadIterator
	*/
	IContentReadIterator *NewSchemaReadIterator(ImplementationID implID, const VersionID &version, IPMStream *s)
		{return NewClosestSchemaReadIterator(false, implID.Get(), version, s);}
	
private:
	IContentReadIterator *NewClosestSchemaReadIterator(bool isClass, uint32 idValue, const VersionID &version, IPMStream *s);
	const Schemas::Schema *FindSchema(bool isClass, uint32 idValue, const VersionID &version);
	const Schemas::Schema *AddSchema(bool isClass, uint32 idValue, const VersionID &version);
	
private:
	PluginID							fMyPlugin;
 	PluginManager						fPluginManager;
 	SchemaManager						fSchemaMgr;
 	PathManager							fPathMgr;
	Schemas::IteratorSchemaInfoVector	fSchemaList;
};

#ifdef PUBLIC_BUILD
#pragma export off
#endif


#endif	// __CContentIteratorReg__
