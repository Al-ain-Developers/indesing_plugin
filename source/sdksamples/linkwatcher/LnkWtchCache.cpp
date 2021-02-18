//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/linkwatcher/LnkWtchCache.cpp $
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

#include "IDataBase.h"
#include "IDocument.h"
#include "PersistUtils.h"
#include "ISubject.h"
#include "IWorkspace.h"
#include "ILinkManager.h"
#include "LinkQuery.h"

#include "ILnkWtchCache.h"
#include "CPMUnknown.h"
#include "ShuksanID.h"
#include "FileUtils.h"
#include "DebugClassUtils.h"
#include "K2Vector.tpp"

#ifdef SDKAUTOUNDO
// New code:
#include "IPMStream.h"
#endif


/** Implements ILnkWtchCache; see ILnkWtchCache for documentation on the methods.

	@ingroup linkwatcher
*/
class LnkWtchCache : public CPMUnknown<ILnkWtchCache>
{
public:
	/** Constructor.
	*/
	LnkWtchCache(IPMUnknown* boss) : CPMUnknown<ILnkWtchCache>(boss) 
	{}

	/** Destructor.
	*/
	virtual ~LnkWtchCache() {}

	const Entries& Get() const {return fEntries;};
	const PMString GetName(const Entry& entry, bool16 fullName) const;
	void push_back(const Entry& entry);
	int32 Location(const Entry& entry);
	void MarkRemoved(const int32 pos, bool16 removed);
	void Delete(const int32 pos);
	void clear();
	void Dump() const;
	void NotifyCacheChanged();

private:
	void DumpEntry(char* msg, const Entry& entry) const;

private:
	Entries fEntries;

#ifdef SDKAUTOUNDO
// New code:
public:
	/**
	Allows the internal state of the implementation to be marshalled in and out of the snapshot.
	@param s IN the stream the snapshot is being written to
	@param implID IN implementation ID
	*/
	void SnapshotReadWrite(IPMStream* s, ImplementationID implID);
#endif
};

/* In CS2 the state of the cache was maintained using an observer. In CS3
the observer is no longer called on undo and redo. Instead, the state of the
cache is maintained by a new type of interface implementation - a 
"snapshot interface".
*/
#ifdef SDKAUTOUNDO
// New code:
CREATE_SNAPSHOT_PMINTERFACE(LnkWtchCache, kLnkWtchCacheImpl)
#else
// Old code:
CREATE_PMINTERFACE(LnkWtchCache, kLnkWtchCacheImpl)
#endif


/*
*/
void LnkWtchCache::push_back(const Entry& entry)
{
#ifdef SDKAUTOUNDO
	// New code:
	PreDirty();
#endif
	fEntries.push_back(entry);
#ifdef DEBUG
	this->DumpEntry("LnkWtchCache::Add", entry);
#endif
}

/*
*/
int32 LnkWtchCache::Location(const Entry& entry) 
{
	Entries::iterator iter = std::find(fEntries.begin(), fEntries.end(), entry);
	return (iter != fEntries.end() ? iter - fEntries.begin() : -1);
}

/*
*/
void LnkWtchCache::MarkRemoved(const int32 pos, bool16 removed)
{
#ifdef SDKAUTOUNDO
	// New code:
	PreDirty();
#endif
	fEntries[pos].fRemoved = removed;
}

/*
*/
void LnkWtchCache::Delete(const int32 pos)
{
#ifdef SDKAUTOUNDO
	// New code:
	PreDirty();
#endif
	fEntries.erase(fEntries.begin() + pos);
}

/*
*/
void LnkWtchCache::clear()
{
#ifdef SDKAUTOUNDO
	// New code:
	PreDirty();
#endif
	fEntries.clear();
}

/*
*/
const PMString LnkWtchCache::GetName(const Entry& entry, bool16 fullName) const
{
	WideString rsrcName;
	if (entry.fRemoved == kFalse)
	{
		InterfacePtr<IDocument> doc(this, UseDefaultIID());
		IDataBase* db = ::GetDataBase(doc);
		if (db->IsValidUID(entry.fUID))
		{
			InterfacePtr<ILink> theLink(db, entry.fUID, UseDefaultIID());
			if (theLink)
			{
				InterfacePtr<ILinkResource> theLinkResource(db, theLink->GetResource(), UseDefaultIID()); 
				if (theLinkResource) 
				{
					if (fullName)
						rsrcName = theLinkResource->GetLongName(false);
					else
						rsrcName = theLinkResource->GetShortName(false);
				}
			}
		}
		else
		{
			ASSERT_FAIL("Invalid uid in LnkWtchCache");
		}
	}
	PMString name(rsrcName);
	return name;
}

/** Dump and dump entry are debug only. Dump to traceflow
*/
void LnkWtchCache::Dump() const
{
	Entries::const_iterator iter;
	for (iter = fEntries.begin(); iter < fEntries.end(); iter++)
	{
		this->DumpEntry("", *iter);
	}
}

/*
*/
void LnkWtchCache::DumpEntry(char* msg, const Entry& entry) const
{
#ifdef DEBUG
	InterfacePtr<IDocument> doc(this, UseDefaultIID());
	IDataBase* database = ::GetDataBase(doc);
	ClassID itemClassID = database->GetClass(entry.fUID);
	DebugClassUtilsBuffer itemClassName = "";
	DebugClassUtils::GetIDName(&itemClassName, itemClassID);
	PMString name = this->GetName(entry, kTrue);
	TRACEFLOW("LinkWatcher:Cache", "%s(uid=%x/%d) %s %s %s\n",
		itemClassName,
		entry.fUID.Get(),
		entry.fUID.Get(),
		entry.fRemoved ? "removed" : "not removed",
		name.GetUTF8String().c_str(),
		msg);

#endif
}
/*
*/
void LnkWtchCache::NotifyCacheChanged()
{
	InterfacePtr<ISubject> docSubject(this, UseDefaultIID());
#ifdef SDKAUTOUNDO
	// New code:
	docSubject->ModelChange(kLnkWtchCacheChangedMessage, IID_ILNKWTCHCACHE, this);
#else
	// Old code:
	docSubject->Change(kLnkWtchCacheChangedMessage, IID_ILNKWTCHCACHE, this);
#endif
}

#ifdef SDKAUTOUNDO
// New code:
/*
*/
void LnkWtchCache::SnapshotReadWrite(IPMStream* s, ImplementationID implID)
{
	if (s->IsReading())
	{
		TRACEFLOW("LinkWatcher:Cache", ">>read>>>>LnkWtchCache::SnapshotReadWrite\n");
		fEntries.clear();
		int32 size = 0;
		s->XferInt32(size);
		for (int32 i = 0; i < size; i++)
		{
			Entry entry(kInvalidUID, kFalse);
			s->XferReference(entry.fUID);
			s->XferBool(entry.fRemoved);
			fEntries.push_back(entry);
		}
	}
	else
	{
		TRACEFLOW("LinkWatcher:Cache", "<<write<<<<LnkWtchCache::SnapshotReadWrite\n");
		int32 size = fEntries.size();
		s->XferInt32(size);
		Entries::iterator iter;
		for (iter = fEntries.begin(); iter < fEntries.end(); iter++)
		{
			s->XferReference(iter->fUID);
			s->XferBool(iter->fRemoved);
		}
	}
}
#endif