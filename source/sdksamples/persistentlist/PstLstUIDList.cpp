//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/PstLstUIDList.cpp $
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
#include "ISession.h"
#include "IWorkspace.h"
#include "IDataBase.h"
#include "IPMStream.h"
#include "CPMUnknown.h"

// General includes:
// None.

// PstLst includes:
#include "IPstLstUIDList.h"
#include "PstLstID.h"

/**	A persistent IPstLstUIDList implementation, which is aggregated in kDrawablePageItemBoss.
 * 	When this plug-in is loaded, a page item will carry this UID list which contains UIDs of 
 * 	all associated persistent list items. UIDs of persistent list items are added to the list
 * 	by processing kPstLstNewDataCmdBoss.  PstLstUIDList allows adding/removing of a UID to/from 
 * 	the list.  In the UI plug-in (persistentlistui), a user can see this list of UIDs as children 
 * 	of drawable page item node on the plug-in's panel.
 * 	@ingroup persistentlist
*/
class PstLstUIDList : public CPMUnknown<IPstLstUIDList>
{
	public:
		/**	Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		PstLstUIDList(IPMUnknown* boss);
		
		/**	Destructor. The UIDList is deleted.
		*/
		virtual ~PstLstUIDList();
				
		/**	Appends a UID of an object to the UID list of persistent list items.
		 * 
		 * 	NOTE: This method must be called from within a command, as it 
		 * 	internally dirties the database. Client code must process the 
		 * 	kPstLstNewDataCmdBoss instead of calling this method directly.
		 * 
		 * 	@param uid IN The UID of the object to be appened to the UID list.
		 * 	@see kPstLstNewDataCmdBoss 
		*/
		virtual void Append(const UID& uid);
		
		/**	Removes a UID of an object from the UID list of persistent list items.
		 * 
		 * 	NOTE: This method must be called from within a command, as it 
		 * 	internally dirties the database. Client code must process the 
		 * 	kPstLstDeleteDataCmdBoss instead of calling this method directly.
		 * 
		 * 	@param uid IN The UID of the object to be removed from the UID list.
		 * 	@see kPstLstDeleteDataCmdBoss
		*/
		virtual void Remove(const UID& uid);
	
		/** Gets the list of persistent list items maintained.
			@return UIDList maintained by this class.
		*/
		virtual const UIDList* GetUIDList();
	
	
		/**	Given an index, this routine will return the corresponding object's UIDRef.
		 * 	@param index IN The index of the object in the persistent item list.
		 * 	@return The UIDRef of the desired object.
		*/
		virtual UIDRef GetRef(int32 index);
		
		/** Gets the database associated with the persistent list.
			@return the database that stores the UID list 
		*/
		virtual IDataBase* GetDataBase();
		
		/**	Because this is a persistent interface, it must support the ReadWrite method. 
		 * 	This method is used for both writing data out to the database and 
		 * 	reading data from the database.
		 * 	The infomation it reads/writes include the current 
		 * 	selected UID and the whole UID list of persistent list items associated.
		 * 
		 * 	@param s IN Contains the stream to read or write.
		 * 	@param prop IN The implementation ID to read or write
		*/
		virtual void ReadWrite(IPMStream* s, ImplementationID prop);
	
	private:
		UIDList* fUIDList;
		void ReadWriteUIDList(IPMStream* s, ImplementationID prop);
};

CREATE_PERSIST_PMINTERFACE(PstLstUIDList, kPstLstUIDListImpl)

/*	PstLstUIDList::PstLstUIDList
*/
PstLstUIDList::PstLstUIDList(IPMUnknown* boss) : 	
		CPMUnknown<IPstLstUIDList>(boss),
		fUIDList(nil)
{
	TRACEFLOW(kPstLstPluginName, "PstLstUIDList::Constructor(), iDataBase = %x\n", ::GetDataBase(this));
	fUIDList = new UIDList(::GetDataBase(this));
}

/*	PstLstUIDList::~PstLstUIDList
*/
PstLstUIDList::~PstLstUIDList()
{
	TRACEFLOW(kPstLstPluginName, "PstLstUIDList::Destructor()\n");
	if (fUIDList != nil)
		delete fUIDList;
}


/*	PstLstUIDList::GetDataBase
*/
IDataBase* PstLstUIDList::GetDataBase()
{
	return fUIDList->GetDataBase();
}

/*	PstLstUIDList::GetRef
*/
UIDRef PstLstUIDList::GetRef(int32 index)
{
  	UIDRef uidRef;
  	if (index >= 0 && index < fUIDList->Length())
  		uidRef = fUIDList->GetRef(index);
  	return uidRef;
}
  

/*	PstLstUIDList::GetUIDList
*/
const  UIDList* PstLstUIDList::GetUIDList()
{
	return fUIDList;
}

/*	PstLstUIDList::Append
*/
void PstLstUIDList::Append(const UID& uid)  
{
	PreDirty (kPstLstUIDListImpl);
	fUIDList->Append(uid);	
}

/*	PstLstUIDList::Remove
*/
void PstLstUIDList::Remove(const UID& uid)  
{
	int32 index = fUIDList->Location(uid);
	if (index >= 0)
	{
		PreDirty (kPstLstUIDListImpl);
		fUIDList->Remove(index);
	}
}

/*	PstLstUIDList::ReadWrite
*/
void PstLstUIDList::ReadWrite(IPMStream* s, ImplementationID prop)
{
	/* 	
	//	REMINDER: 
	//	If you change the arrangement of persistent data in this method, 
	//	remember to update the format number in the PluginVersion resource. 
	//	(See the PstLstID.h file for the plug-in specific format numbers.) 
	*/
	TRACEFLOW(kPstLstPluginName, "PstLstUIDList::ReadWrite()\n");
	ReadWriteUIDList(s,prop);
}

/*	PstLstUIDList::ReadWriteUIDList
*/
void PstLstUIDList::ReadWriteUIDList(IPMStream* s, ImplementationID prop)
{
	int32 length = fUIDList->Length();
	s->XferInt32(length);

	if (s->IsReading())
	{
		fUIDList->Clear();
		fUIDList->Preallocate(length);

		for (int32 i = 0; i < length; i++)	
		{
			UID		u;
			fUIDList->Append(s->XferObject(u));
		}
	}
	else
	{
		for (int32 i = 0; i < length; i++)
			s->XferObject(fUIDList->At(i));
	}	
}

// End, PstLstUIDList.cpp.

