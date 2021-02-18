//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstReferenceConverter.cpp $
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

//===========================
//  Plug-in includes
//===========================

#include "VCPlugInHeaders.h"

#include "CReferenceConverter.h"

// Interface includes:
#include "IPMUnknown.h"
#include "IScrapUtils.h"
#include "IDataBase.h"

// API includes:
#include "Utils.h"

// Project includes:
#include "PstLstID.h"

/** Implements a reference converter, IReferenceConverter,
	that controls how objects of ClassID kPstLstDataBoss get copied.

	For example, say a page item has two associated kPstLstDataBoss objects with
	UID's UID1, UID2 and the selected object is UID2 (see interface IPstLstUIDList). 
	When this page item is copied a new page item is created and distinct copies
	of the kPstLstDataBoss objects are made. The new page item's associated
	kPstLstDataBoss objects are UID1', UID2' and the selected object is UID2'. 
	UID1' contains a copy of the data held by the object UID1. UID2' contains a copy 
	of the data held by the object UID2. 
	
	When the copy happens, a persistent implementation's ReadWrite function gets
	called to write itself out into the copy stream. When the ReadWrite function
	calls IPMStream::XferReference on the UID, the copy stream tries to copy the UID.
	First it checks to see if the UID has already been copied previously in the 
	copy session(see IXReferenceUID). If it hasn't, then it looks for a reference converter 
	which can copy the UID for it. If it finds a reference converter, it calls it to make a 
	copy of the UID. The reference converter returns the UID of the copy. If there
	is no reference converter, then the copy stream just returns kInvalidUID. When
	the ReadWrite function calls IPMStream::XferObject the same process is run through
	with the additional final step of simply streaming the data for the object via
	ReadWrite if no reference converter is available.

	If a reference converter is not provided for a persistent boss class then
	calls to IPMStream::XferReference for UID's of that ClassID return kInvalidUID 
	(as was the case before this reference converter was added to this plug-in).
	When PstLstUIDList::ReadWrite was called during copy operations its data member 
	(fSelectedUID) was copied with a value of kInvalidUID. PstLstUIDList::ReadWrite was 
	updating fSelectedUID when this happened and calling Dirty to mask this problem.
	The ReadWrite method of a persistent implementation should never call Dirty.
	Adding the reference converter maintains fSelectedUID across the copy to be the 
	UID of the selected kPstLstDataBoss object, see PstLstUIDList::ReadWrite. This
	removed the need to dirty the object during ReadWrite.

	@ingroup persistentlist
	
*/
class PstLstReferenceConverter : public CReferenceConverter
{
public:
	typedef CReferenceConverter inherited;

	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	PstLstReferenceConverter(IPMUnknown* boss);

	/**	Destructor.
	*/
	virtual ~PstLstReferenceConverter();

	/** Return kTrue if clsID is kPstLstDataBoss, kFalse otherwise.
		@param clsID objects boss class
		@return kTrue if clsID is kPstLstDataBoss, kFalse otherwise.
	 */
	virtual bool16 CanConvert(ClassID clsID);	

	/** Return UID of converted object in target database, IScrapUtils::CopyObject
		is used to make the conversion.
		@param sourceDB database containing the source object.
		@param convertThis refers to the object to be converted.
		@param targetDB database containing the converted object.
		@param pmobject
		@return UID of converted object in target database.
	 */
	virtual UID ConvertReference(IDataBase* sourceDB, UID convertThis, IDataBase* targetDB, IPMUnknown* pmobject);

	/** Return kFalse to indicate that if another reference to an object that has already
		been converted is encountered the application can simply reuse the result of the
		previous conversion.
		@return kFalse.
	 */
	virtual bool16 ConvertAlways(void) const;

	/** Return kInvalidUID. If the method could find an existing object in the 
		target database that convertThis should be converted to, it could return
		it. Since kPstLstDataBoss objects have no special rules that allow such
		matching, this method returns kInvalidUID.
		@param sourceDB database containing the source object.
		@param convertThis refers to the object to be converted.
		@param targetDB database containing the converted object
			(this method should never create new objects in the target database).
		@return kInvalidUID.
	 */
	virtual UID GetReference(IDataBase* sourceDB, UID convertThis, IDataBase* targetDB ) const;

};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(PstLstReferenceConverter, kPstLstReferenceConverterImpl)

/*
*/
PstLstReferenceConverter::PstLstReferenceConverter(IPMUnknown* boss) :
	inherited(boss)
{
}

/*
*/
PstLstReferenceConverter::~PstLstReferenceConverter()
{
}

/*
*/
bool16 PstLstReferenceConverter::CanConvert(ClassID clsID)
{
	bool16 result = kFalse;
	if (clsID == kPstLstDataBoss)
	{
		result = kTrue;
	}
	return result;
}

/*
*/
UID PstLstReferenceConverter::ConvertReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB, IPMUnknown* pmobject)
{
	UID result = kInvalidUID;
	Utils<IScrapUtils> scrapUtils;
	ASSERT(scrapUtils);
	if (scrapUtils)
	{
		result = scrapUtils->CopyObject(UIDRef(sourceDB, convertThis), targetDB, pmobject);
	}
	return result;
}

/*
*/
bool16 PstLstReferenceConverter::ConvertAlways(void) const
{
	return kFalse;
}

/*
*/
UID PstLstReferenceConverter::GetReference(IDataBase *sourceDB, UID convertThis, IDataBase *targetDB ) const
{
	return kInvalidUID;
}


// End, PstLstReferenceConverter.cpp.

