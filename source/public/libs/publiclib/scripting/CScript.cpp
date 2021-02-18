//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/scripting/CScript.cpp $
//  
//  Owner: Jonathan W. Brown
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

#include "VCPublicHeaders.h"
#include "CScript.h"

#include "IM2MMessageManager.h"
#include "IScriptInfoManager.h"
#include "IScriptUtils.h"

#include "ScriptClientObject.h"
#include "StreamUtil.h"

#include <boost/bind.hpp>

#define	MAGIC_BYTES	0x7B7B	/* symmetric across byte swaps; unlikely to occur in the first two bytes of a PMString */
IScriptLabel::ScriptLabelKey IScriptLabel::kDefaultScriptLabelKey( "Label" ) ;

static void SendSpecialM2M(const IPMUnknown* boss, const IScriptLabel::ScriptLabelKey& key);

CScript::CScript( IPMUnknown* boss ) :
	CPMUnknown<IScript>(boss)
#ifdef DEBUG
	,fBDidConversion(kFalse)
#endif
{
}

CScript::~CScript()
{
	if ( !fClientObjects.empty() )
	{
		std::for_each( fClientObjects.begin(), fClientObjects.end(), std::mem_fun( &ScriptClientObject::ReleaseRefFromObjectModel ) ) ;
		fClientObjects.clear() ;
	}
}

bool16 CScript::IsObjectType( const ScriptID& type, const ScriptInfo::RequestContext& context ) const
{
	const ObjectScriptElement* pObjSI = this->GetObjectInfo( context ) ;
	if ( pObjSI )
		return pObjSI->IsObjectType( type );

	return kFalse ;
}

bool16 CScript::IsObjectType( const ScriptElementID& type, const ScriptInfo::RequestContext& context ) const
{
	const ObjectScriptElement* pObjSI = this->GetObjectInfo( context ) ;
	if ( pObjSI )
		return pObjSI->IsObjectType( type );

	return kFalse ;
}

const ObjectScriptElement* CScript::GetObjectInfo( const RequestContext& context ) const
{
	const ObjectScriptElement* pObjSI = nil ;
	InterfacePtr<IScriptInfoManager> scriptInfoMgr( Utils<IScriptUtils>()->QueryScriptInfoManager( context ) ) ;
	ASSERT( scriptInfoMgr ) ;
	if ( scriptInfoMgr )
	{
		pObjSI = scriptInfoMgr->FindObject( this->GetObjectType( context ) ) ;
#ifdef DEBUG
        ASSERT_MSG( pObjSI, FORMAT_ARGS( "CScript::GetObjectInfo - Object type '%s' not found in DOM %s",
			Utils<IScriptUtils>()->GetScriptID(this->GetObjectType(context)).GetUTF8String().c_str(), context.WhoAmI()));
#endif
	}
	return pObjSI ;
}

void CScript::SetObjectType( const ScriptID& type, const RequestContext& context )
{
	ASSERT_UNIMPLEMENTED() ;	//implement in subclass
}

void CScript::ReadWrite(IPMStream *s, ImplementationID prop)
{
	/*
		This is a bit of a hack - CScript is the base class for many objects, with many different 
		implementations, possibly including ones not under our control (i.e. 3rd party plugins). This
		makes it impossible to write a converter in the normal way. 
		Since any implementation that hits this ReadWrite method must be derived from this implementation, 
		we fix it up here. 
		
		The old (pre 12/2002) implementation of CScript persisted one PMString (the 'script label'). After this
		change, CScript persists a K2Vector of PMString pairs (keys & values). The old script label is added as
		the first element of this vector. In order for this to work, we also persist a 2 byte magic cookie before
		any label (if the cookie is there, then the vector follows; otherwise a PMString follows)
	 */

	int16	magic = MAGIC_BYTES;
	int32	startLocation = 0;

	if (s->IsReading())	
		startLocation = s->Seek(0, kSeekFromCurrent);

	s->XferInt16(magic);

	if (s->IsReading())
	{
		if (magic == MAGIC_BYTES)
		{
			K2Read(s, fLabels);
		}
		else
		{
			s->Seek(startLocation, kSeekFromStart);	// back up the stream & read the PMString

			PMString	originalValue;
			originalValue.ReadWrite(s);

			/* Quietly (i.e. without a 'Dirty') add the default label to our K2Vector of labels */
			InsertOrReplaceKeyValue(fLabels, kDefaultScriptLabelKey, originalValue);

#ifdef DEBUG
			fBDidConversion = kTrue;
#endif			
		}
	}
	else
	{
		// Give our caller a clue that we may change the data without Dirty() being called - i.e.
		//	if we read in an old style tag (PMString), and are now writing out a vector of key/values.
		//
		// (Note: This call is a No-op in the Release build.)
		//
		// TODO: Is it worth it to remember if this is the case?
		//
#ifdef DEBUG
		if (fBDidConversion)	// only mute the debug-only assert if we really did do a conversion
#endif
		StreamUtil::SetStreamContentsChanged(s);

		K2Write(s, fLabels);
	}
}

IScriptLabel::ScriptLabelValue CScript::GetTag() const
{
	return GetTag(kDefaultScriptLabelKey);
}

void CScript::SetTag( const ScriptLabelValue& string )
{
	SetTag(kDefaultScriptLabelKey, string);
}

IScriptLabel::ScriptLabelValue CScript::GetTag( const ScriptLabelKey& key ) const
{
	int32 location = FindLocation(fLabels, key);
	if (location >= 0) 
		return(fLabels[location].Value());
	return kNullString;
}

void CScript::SetTag( const ScriptLabelKey& key, const ScriptLabelValue& value )
{
	//Don't bother storing pair if the value is the empty string
	if ( value == kNullString )
	{
		int32 location = FindLocation(fLabels, key);
		if ( location >= 0 )
		{
			SendSpecialM2M(this, key);
			PreDirty ();
			fLabels.erase(fLabels.begin() + location);
		}
	}
	else
	{
		SendSpecialM2M(this, key);
		PreDirty ();
		InsertOrReplaceKeyValue(fLabels, key, value);
		
	}
}

void CScript::SetTags( const ScriptLabelKeyValueList& labels )
{
	for ( ScriptLabelKeyValueList::const_iterator iter = labels.begin() ; iter != labels.end() ; ++iter )
	{
		SetTag( iter->Key(), iter->Value() ) ;
	}
}

IScriptLabel::ScriptLabelKeyValueList CScript::GetTags() const
{
	return fLabels ;
}

void CScript::ClearTags()
{
	if ( fLabels.size() > 0 )
	{
		PreDirty ();
		fLabels.clear();
		
	}
}

// A safe way to determine the appropriate database for this object. Most implementations 
// can simply inherit and use the default implementation { return ::GetDataBase( this ) ; }
// but some script bosses are non-persistent, and should therefore override this method.
IDataBase* CScript::GetDataBase( const RequestContext& context ) const
{
	return ::GetDataBase( this ) ;
}

ScriptObject CScript::GetScriptObject( const RequestContext& context ) const
{
	//Default for persistent objects is to return by uniqueID
	UID uid = ::GetUID( this ) ;
	if ( uid != kInvalidUID )
	{
		return ScriptObject( ScriptData( (int32)uid.Get() ), GetObjectType( context ), kFormUniqueID ) ;
	}
	else
	{
		//implement in subclass for non-persistent objects
		ASSERT_FAIL( "Non-persistent object: derive from CProxyScript class or override GetScriptObject method" ) ;
		return ScriptObject() ;
	}
}

bool16 CScript::HasBeenDeleted( const RequestContext& context )
{
	UIDRef ref = ::GetUIDRef(this) ;
	return !ref.ExistsInDB() ;
}

bool16 CScript::IsEqual( const IScript* script, const RequestContext& context ) const
{
	return this == script ;
}

void CScript::RegisterClientObject( ScriptClientObject* clientObject )
{
#ifdef DEBUG
	//Make sure that this is a persistent boss OR, if not, then it implements IID_ISCRIPTOBJECTPARENT
	InterfacePtr<IScriptObjectParent> hasScriptObjectParent( this, UseDefaultIID() ) ;
	if ( hasScriptObjectParent )
	{
		InterfacePtr<IPMUnknown> parent( hasScriptObjectParent->QueryParent( IID_IUNKNOWN ) ) ;
		ASSERT_MSG( parent != nil, "IScriptObjectParent is nil; it must be set during creation of the proxy object" ) ;
		//Typically proxy script objects are created using IScriptUtils::CreateProxyScriptObject. Otherwise,
		//you must call IScriptObjectParent::SetParent() directly.
	}
	else
	{
		InterfacePtr<IPMPersist> isPersistent( this, UseDefaultIID() ) ;
		ASSERT_MSG( isPersistent, "Non-persistent (proxy) scripting boss must implement IID_ISCRIPTOBJECTPARENT and its IID_ISCRIPT implementation should inherit from CProxyScript" ) ;
		//Generally proxy scripting bosses implement IID_ISCRIPTOBJECTPARENT via boss inheritance from kBaseProxyScriptObjectBoss
		//Alternatively, they can add it directly to their boss class resource like this: 
		//		IID_ISCRIPTOBJECTPARENT,	kScriptObjectParentImpl,	//provides access to this object's parent object
	}
#endif
	if ( clientObject )
	{
		clientObject->AddRefFromObjectModel() ;
		fClientObjects.push_back( clientObject ) ;
	}
}

void CScript::UnregisterClientObject( ScriptClientObject* clientObject )
{
	ScriptClientObject** iter = std::find( fClientObjects.begin(), fClientObjects.end(), clientObject ) ;
	if ( iter != fClientObjects.end() )
	{
		(*iter)->ReleaseRefFromObjectModel() ;
		fClientObjects.erase( iter ) ;
	}
}

void CScript::NotifyClientObjectsToReleaseMe()
{
	if ( !fClientObjects.empty() )
	{
		const K2Vector<ScriptClientObject*> temp = fClientObjects ;
		std::for_each( temp.begin(), temp.end(), std::mem_fun( &ScriptClientObject::AddRefFromObjectModel ) ) ;
		std::for_each( temp.begin(), temp.end(), boost::bind( &ScriptClientObject::ReleaseReferencesToObjectModel, _1, this ) ) ;
		std::for_each( temp.begin(), temp.end(), std::mem_fun( &ScriptClientObject::ReleaseRefFromObjectModel ) ) ;
	}
}

// IID_ISCRIPT_LABEL and IID_ISCRIPT_KEY_DPS are faux messages generated to let the client listeners know what kind of script key change occurred.
// If a DPS label changes or gets deleted, then IID_ISCRIPT_KEY_DPS is sent to clients, else IID_ISCRIPT_LABEL is sent.
// These faux messages are defined in ScriptingID.h
// In CS6, the only known listener for these faux messages is the sharedContent plug-in which uses this to distinguish between DPS and non-DPS keys.

void SendSpecialM2M(const IPMUnknown* boss, const IScriptLabel::ScriptLabelKey& key)
{
	IDataBase* db = ::GetDataBase(boss);
	const IScriptLabel::ScriptLabelKey kDPSPrefix("kAdobeDPSInteractivity_");

	if(db == nil)
		return;

	PMIID id = IID_ISCRIPT_LABEL;

	if(key.IndexOfString(kDPSPrefix) == 0)
		id = IID_ISCRIPT_KEY_DPS;

	// Send out a notification to interested clients.
	InterfacePtr<IM2MMessageManager> m2mmm(db, db->GetRootUID(), UseDefaultIID()); 
	if (m2mmm) 
		m2mmm->PreChangeMessage(boss, id); 
}
