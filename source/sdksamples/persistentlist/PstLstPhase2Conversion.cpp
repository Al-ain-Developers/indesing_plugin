//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstPhase2Conversion.cpp $
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

// Interface includes:
#include "IPhase2Conversion.h"
#include "isignalmgr.h"
#include "IUIDIterator.h"
#include "IDataBase.h"

// General includes
#include "CResponder.h"
#include "FormatNumber.h"
#include "UIDList.h"
#include "FormatID.h"

// Project includes:
#include "PstLstID.h"
#include "IPstLstUIDList.h"
#include "IPstLstData.h"

/** IResponder implementation for phase 2 conversion (see IPhase2Conversion). Static changes to the 
	format of persistent data in a plug-in can be handled by schema based conversion 
	(see kPstLstConversionProviderBoss). Dynamic changes require the database being converted to be 
	manipulated in some way that can't be handled by a static mapping. 
	
	Format changes at InDesign CS2:

	FormatID(kPstLstAddParentReferenceUIDMajorFormat, kPstLstAddParentReferenceUIDMinorFormat)
	This plug-in added a back reference to PstLstDataPersist that refers by UID to the boss that owns 
	a kPstLstDataBoss object. When a database containing data of an earlier format is opened the
	back reference will be kInvalidUID. The code below (see PstLstPhase2Conversion::AddParentReferenceUID) 
	scans all the kPstLstDataBoss objects in the document and fixes this up so each object has a back
	reference to its parent.

	Note:
	It's likely that most of your plug-in's persistent data format changes can be handled by schema based
	conversion (see kPstLstConversionProviderBoss for sample code). Check it out and see if it can meet
	your needs. Only implement a phase 2 converter like that below if your data reallys needs it.

	@see IPhase2Conversion
	@ingroup persistentlist
*/
class PstLstPhase2Conversion : public CResponder
{
public:
	/** Constructor
		@param boss on which this interface is aggregated.
	*/
	PstLstPhase2Conversion(IPMUnknown * boss)
		: CResponder(boss)
		{}

	/** Respond to phase 2 database conversion signals and convert
		this plug-in's dynamic persistent data.
		@param signalMgr
	*/
	virtual void Respond(ISignalMgr* signalMgr);

private:
	/** Add back reference to the boss that owns each kPstLstDataBoss
		object in the database being converted.
		@param phase2 provides the context for the conversion to be performed.
	*/ 
 	void AddParentReferenceUID(IPhase2Conversion* phase2);
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(PstLstPhase2Conversion, kPstLstPhase2ConversionImpl)

/*
*/
void PstLstPhase2Conversion::Respond(ISignalMgr* signalMgr)
{
	do
	{
		//
		// Get our Phase 2 Conversion interface from the Signal Manager.
		//
		InterfacePtr<IPhase2Conversion>	phase2(signalMgr, UseDefaultIID());
		ASSERT(phase2);
		if (!phase2)
		{
			break;
		}

		//
		// Determine the source and target format numbers to see if we will convert or not.
		//
		FormatID sFormat, tFormat;
		bool16 gotSFormat = phase2->GetSourcePluginFormatNumber(kPstLstPluginID, sFormat);
		if (gotSFormat == kFalse)
		{
			// No persistent data from this plug-in found in the database.
			// There's nothing we need to convert.
			break;
		}
		bool16 gotTFormat = phase2->GetTargetPluginFormatNumber(kPstLstPluginID, tFormat);
		ASSERT_MSG(gotTFormat, "PstLstPhase2Conversion::Respond() - Cannot get target format number.");

		// If the data was earlier than the AddParentReferenceUID format change then convert the data.
		if (sFormat < FormatID(kPstLstAddParentReferenceUIDMajorFormat, kPstLstAddParentReferenceUIDMinorFormat))
		{
			this->AddParentReferenceUID(phase2);
		}
	} while(false);
}

/*	The design approach used below uses IUIDIterator iterator to examine
	all the boss objects in the database. Since this plug-in's data can
	get stored in many different places in a document (in a spread, group,
	an inline graphic in text, in nested frames) it's a valid approach
	but it has an obvious performance penalty.

	If your plug-in's data is stored in a well known set of locations 
	it is better to navigate to the interfaces that store your data 
	using bridge methods on interfaces. For example if your data
	is stored on a spread navigate from the database root (IDocument)
	each spread via ISpreadList, find your data interface and fix it.
*/
void PstLstPhase2Conversion::AddParentReferenceUID(IPhase2Conversion* phase2)
{
	do
	{
		// Iterate over UIDs to discover the objects that have IPstLstUIDList.
		IDataBase* db = phase2->GetRootObject().GetDataBase();
		IUIDIterator* uidIter = db->NewUIDIterator();
		ASSERT(uidIter);
		if (!uidIter)
		{
			break;
		}
		for (UID uid = uidIter->First(); uid != kInvalidUID; uid = uidIter->Next())
		{
			InterfacePtr<IPstLstUIDList> pstLstUIDList(db, uid, UseDefaultIID());
			if (pstLstUIDList) 
			{
				// Check all the boss objects owned by this list have back references to their parent boss.
				const UIDList* list = pstLstUIDList->GetUIDList();
				for (int32 i = 0 ; i < list->Length(); i++)
				{
					InterfacePtr<IPstLstData> pstLstData(list->GetRef(i), UseDefaultIID());
					ASSERT(pstLstData);
					if (!pstLstData)
					{
						break;
					}
					if (pstLstData->GetParent() == kInvalidUID) 
					{
						// No back reference to parent - so add it
						pstLstData->SetParent(uid);
					}
					if (pstLstData->GetParent() != uid) 
					{
						// Bad parent reference shouldn't happen but fix it up if we find it.
						ASSERT_FAIL("PstLstPhase2Conversion::AddParentReferenceUID detected bad parent reference - fixing");
						pstLstData->SetParent(uid);
					}
				}
			}
		}
		db->DeleteUIDIterator(&uidIter);
	} while(false);
}

// End, PstLstPhase2Conversion.cpp.



