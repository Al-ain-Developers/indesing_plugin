//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapIteratorRegister.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// ----- Includes -----

#include "CContentIteratorReg.h"
#include "K2Debugging.h"
#include "HelperInterface.h"
#include "SchemaBasedIterator.h"

// ----- ID.h files -----

#include "SnapID.h"


/* List of the objects that we represent
*/
static const ImplementationID kImplTable[] =
{
	// These are Schema-based iterators
	ImplementationID(kSnapPrefsDataPersistImpl)
};

/** SnapIteratorRegister

	Register the content iterator for persistent implementation of ISnapPrefsData.
	
	@ingroup snapshot
*/
class  SnapIteratorRegister : public CContentIteratorRegister
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		SnapIteratorRegister(IPMUnknown* boss)
			: HELPER_METHODS_INIT(boss)
			{}
		
		/** 
			Get the implementation ID count.
		*/
		virtual uint32 GetImplementationIDCount()
			{return sizeof(kImplTable) / sizeof(kImplTable[0]);}

		/** 
			Look through the implementation ID table to find the nth implementation ID.
		*/
		virtual void GetNthImplementationID(uint32 n, ImplementationID& impl_id)
			{ASSERT_MSG((n < GetImplementationIDCount()), FORMAT_ARGS("SnapIteratorRegister::GetNthImplementationID() - Invalid index: %d", n));
			 impl_id = kImplTable[n];}
		
		/** 
			Create a new schema based read iterator.
			@param version The version number of this persistent implementation on read data
		*/
		virtual IContentReadIterator* NewNthImplementationReadIterator(uint32 n, const VersionID& version, IPMStream* s);

		/**
			Create a new schema based write iterator.
			@param version The version number of this persistent implementation on write data
		*/
		virtual IContentWriteIterator* NewNthImplementationWriteIterator(uint32 n, const VersionID& version, IPMStream* s);

		DECLARE_HELPER_METHODS()
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SnapIteratorRegister, kSnapIteratorRegisterImpl)

DEFINE_HELPER_METHODS(SnapIteratorRegister)

/* NewNthImplementationReadIterator
*/
IContentReadIterator* SnapIteratorRegister::NewNthImplementationReadIterator
(
	uint32				n,
	const VersionID&	version,
	IPMStream*			s
)
{
	ASSERT_MSG((n < GetImplementationIDCount()), FORMAT_ARGS("SnapIteratorRegister::NewNthImplementationReadIterator() - Invalid index: %d", n));

	return NewSchemaReadIterator(kImplTable[n], version, s);
}

/* NewNthImplementationWriteIterator
*/
IContentWriteIterator* SnapIteratorRegister::NewNthImplementationWriteIterator
(
	uint32				n,
	const VersionID&	version,
	IPMStream*			s
)
{
	ASSERT_MSG((n < GetImplementationIDCount()), FORMAT_ARGS("SnapIteratorRegister::NewNthImplementationWriteIterator() - Invalid index: %d", n));

	return new SchemaBasedWriteIterator(s);
}


