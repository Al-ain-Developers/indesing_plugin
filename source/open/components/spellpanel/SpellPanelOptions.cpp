//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/SpellPanelOptions.cpp $
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
//  
//  Purpose:	Provides a definition of a persistent standoff object.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ILinguisticMgr.h"
#include "IPMStream.h"
#include "ISpellPanelOptions.h"
#include "IUserDictService.h"

#include "HelperInterface.h"
#include "k2sortedvector.h"		
#include "SpellPanelID.h"

typedef K2SortedVector<PMString> SortedStringList;


class SpellPanelOptions : public ISpellPanelOptions
{
public:
    SpellPanelOptions(IPMUnknown * boss);
    
	// IPMUnknown
	virtual void			ReadWrite(IPMStream *s, ImplementationID prop);

	virtual bool16 					GetOverset() const;
	virtual void 					SetOverset(bool16 bOverset);

	virtual IWalkerScopeFactoryUtils::WalkScopeType 	GetFindChangeScope() const;
	virtual void 					SetFindChangeScope(IWalkerScopeFactoryUtils::WalkScopeType nScope );

	virtual bool16					IsIgnored( const PMString &rIgnore ) const;
	virtual bool16					AddToIgnoreList( const PMString &rIgnore );
	virtual bool16					RemoveFromIgnoreList( const PMString &rIgnore );
	virtual bool16					ClearIgnoreList();
	virtual int32					GetIgnoredCount() const;
	virtual const PMString &		GetNthIgnored( int32 nIndex ) const;

	virtual bool16					CopyFrom( const ISpellPanelOptions *pFrom );

	virtual bool16					GetCaseSensitive() const {return fCaseSensitive;}
	virtual void					SetCaseSensitive(bool16 bCaseSensitive);

private:	
	IWalkerScopeFactoryUtils::WalkScopeType 	fScope;
	SortedStringList							fIgnoreList;
	bool16										fOverset;
	bool16										fCaseSensitive;

	IUserDict*									fMemoryIgnoredWordsDictionary; //all lang mem user dict
    InterfacePtr<IUserDictService>              fUserDictService;
	
DECLARE_HELPER_METHODS()
};

//---------------------------------------------------------------
// template SortedStringList
//---------------------------------------------------------------

// SortedObjCollection doesn't work because PMString::ReadWrite() does not accept prop
#include "TemplateDefs.h"
#include "k2sortedvector.tpp"		
#include "K2Vector.tpp"	

// [templit] auto-removed, now exported from public: TEMPLATE K2SortedVector<PMString>;
//TEMPLATE K2SortedVector<PMString>;


CREATE_PERSIST_PMINTERFACE(SpellPanelOptions, kSpellPanelOptionsImpl)
DEFINE_HELPER_METHODS(SpellPanelOptions)

//---------------------------------------------------------------
// SpellPanelOptions constructor 
//---------------------------------------------------------------

SpellPanelOptions::SpellPanelOptions( IPMUnknown *pBoss ) : 
	HELPER_METHODS_INIT( pBoss ),
	fScope( IWalkerScopeFactoryUtils::kEmptyScope ),
	fOverset(kFalse),
	fCaseSensitive(kFalse),
	fMemoryIgnoredWordsDictionary(nil),
    fUserDictService()
{
    InterfacePtr<IK2ServiceRegistry>    pServices(GetExecutionContextSession(), UseDefaultIID());
    InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
    InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );
    
    InterfacePtr<const ILanguage>pAllLanguage( pLinguMgr->QueryLanguage("Neutral") );
    ASSERT( pAllLanguage );
    
    InterfacePtr<IUserDictService> pDictService(pLinguMgr->QueryUserDictService( pAllLanguage ));
    
    fUserDictService.reset(pDictService.forget());
}

//---------------------------------------------------------------
// SpellPanelOptions::ReadWrite
//---------------------------------------------------------------

void SpellPanelOptions::ReadWrite(IPMStream *s, ImplementationID prop)
{
	XFER_ENUM16(s, fScope);
	s->XferBool( fOverset );
	
	// PersistSortedObjCollection doesn't work because PMString::ReadWrite() does not accept prop
	// fIgnoreList.ReadWrite( s, prop );
	int32 nMax = fIgnoreList.Length();
	s->XferInt32(nMax);

	const bool16 bReading = s->IsReading();
	if( bReading )
	{
		fIgnoreList.Clear();
		fIgnoreList.Preallocate( nMax );
		for (int32 i = 0; i < nMax; ++i )
		{
			PMString aTemp;
			aTemp.ReadWrite( s );
			fIgnoreList.Insert( aTemp );
		}
	}
	else
	{
		for( int32 i = 0; i < nMax; ++i  )
			fIgnoreList[i].ReadWrite( s );
	}
}

//---------------------------------------------------------------
// SpellPanelOptions::GetOverset
//---------------------------------------------------------------

bool16 SpellPanelOptions::GetOverset() const
{
	return fOverset;
}


//---------------------------------------------------------------
// SpellPanelOptions::SetOverset
//---------------------------------------------------------------

void 	SpellPanelOptions::SetOverset(bool16 bOverset)
{
	if( bOverset != fOverset )
	{
		PreDirty ();
		fOverset = bOverset;
		
	}
}

//---------------------------------------------------------------
// SpellPanelOptions::GetFindChangeScope
//---------------------------------------------------------------

IWalkerScopeFactoryUtils::WalkScopeType SpellPanelOptions::GetFindChangeScope() const
{
	return fScope;
}

//---------------------------------------------------------------
// SpellPanelOptions::SetFindChangeScope
//---------------------------------------------------------------

void SpellPanelOptions::SetFindChangeScope(IWalkerScopeFactoryUtils::WalkScopeType nScope)
{
	if( fScope != nScope )
	{
		PreDirty ();
		fScope = nScope;
		
	}
}

//---------------------------------------------------------------
// SpellPanelOptions::IsIgnored
//---------------------------------------------------------------

bool16 SpellPanelOptions::IsIgnored( const PMString &rIgnore ) const
{
	if( rIgnore.IsEmpty() )
		return kTrue;
		
	int32 nFound = fIgnoreList.Location( rIgnore );	
	if( nFound >= 0 )
		return kTrue;
		
	// BP 102/05/98: #262877 Ignore All is case sensitive.
	
	PMString aTemp( rIgnore );
	aTemp.Remove( 0, 1 );

	if( UnicodeClass::IsLowercase( rIgnore.GetWChar(0) ) )
		aTemp.InsertW( UnicodeClass::ToUpper( rIgnore.GetWChar(0) ).GetValue(), 0 );
	else
		aTemp.InsertW( UnicodeClass::ToLower( rIgnore.GetWChar(0) ).GetValue(), 0 );
		
	nFound = fIgnoreList.Location( aTemp );		
	
#ifdef DEBUG
	if( nFound < 0 )
	{
		PMString aDebugTemp;
		int32 nIdx = -nFound;
		if( nIdx < fIgnoreList.Length() )
		{
			aDebugTemp = fIgnoreList[nIdx];
			++nIdx;
			if( nIdx < fIgnoreList.Length() )
				aDebugTemp = fIgnoreList[nIdx];
		}
	}
	
#endif
	return nFound >= 0;
}

//---------------------------------------------------------------
// SpellPanelOptions::AddToIgnoreList
//---------------------------------------------------------------

bool16 SpellPanelOptions::AddToIgnoreList( const PMString &rIgnore ) 
{
	if( this->IsIgnored( rIgnore ) )
		return kFalse;
	
	PreDirty();
	fIgnoreList.Insert( rIgnore );

    InterfacePtr<ICommand> isCommand( this, UseDefaultIID() );
	if (!isCommand)
	{
		if (!fMemoryIgnoredWordsDictionary)
		{
			PMString dummyFileName;
			fMemoryIgnoredWordsDictionary = fUserDictService->CreateNewUserDict(dummyFileName, IUserDictService::kCreateMemoryOnly);
		}
		WideString wideIgnoreWord(rIgnore);
		fUserDictService->AddToUserDict(fMemoryIgnoredWordsDictionary, wideIgnoreWord, nil, kTrue);
	}

	return kTrue;
}

//---------------------------------------------------------------
// SpellPanelOptions::RemoveFromIgnoreList
//---------------------------------------------------------------

bool16 SpellPanelOptions::RemoveFromIgnoreList( const PMString &rIgnore ) 
{
	const int32 nFound = fIgnoreList.Location( rIgnore );	
	if( nFound < 0 )
		return kFalse;

	PreDirty();
	fIgnoreList.Remove( nFound );
	
    InterfacePtr<ICommand> isCommand( this, UseDefaultIID()  );
	if (!isCommand)
	{
		ASSERT(fMemoryIgnoredWordsDictionary);
		WideString wideIgnoreWord(rIgnore);
		fUserDictService->RemoveFromUserDict(fMemoryIgnoredWordsDictionary, wideIgnoreWord);
	}

	return kTrue;
}

//---------------------------------------------------------------
// SpellPanelOptions::ClearIgnoreList
//---------------------------------------------------------------

bool16 SpellPanelOptions::ClearIgnoreList()
{
	if( fIgnoreList.Length() == 0 )
		return kFalse;
	
	PreDirty();
	fIgnoreList.Clear();

	if (fMemoryIgnoredWordsDictionary)
	{
		fUserDictService->ClearUserDict(fMemoryIgnoredWordsDictionary);
	}

	return kTrue;
}


//---------------------------------------------------------------
// SpellPanelOptions::GetIgnoredCount
//---------------------------------------------------------------

int32 SpellPanelOptions::GetIgnoredCount() const
{
	return fIgnoreList.Length();
}

//---------------------------------------------------------------
// SpellPanelOptions::GetNthIgnored
//---------------------------------------------------------------

const PMString &SpellPanelOptions::GetNthIgnored( int32 nIndex ) const
{
	return  fIgnoreList[ nIndex ];
}

//---------------------------------------------------------------
// SpellPanelOptions::CopyFrom
//---------------------------------------------------------------
bool16 SpellPanelOptions::CopyFrom( const ISpellPanelOptions *pFrom )
{
	if( !pFrom )
		return kFalse;
	
	fCaseSensitive = pFrom->GetCaseSensitive();
	fOverset = pFrom->GetOverset();
	fScope = pFrom->GetFindChangeScope();
	fIgnoreList.Clear();
	
	const int32 nMax = pFrom->GetIgnoredCount();
	for( int32 i = 0; i < nMax; ++i )
		fIgnoreList.Insert( pFrom->GetNthIgnored( i ) );

    InterfacePtr<ICommand> isCommand( this, UseDefaultIID()  );
	if (!isCommand)
	{
		if (!fMemoryIgnoredWordsDictionary && (fIgnoreList.Length() > 0))
		{
			PMString dummyFileName;
			fMemoryIgnoredWordsDictionary = fUserDictService->CreateNewUserDict(dummyFileName, IUserDictService::kCreateMemoryOnly);
		}
		else if (fMemoryIgnoredWordsDictionary)
		{
			fUserDictService->ClearUserDict(fMemoryIgnoredWordsDictionary);
		}

		for( int32 i = 0; i < fIgnoreList.Length(); ++i )
		{
			WideString wideIgnoreWord(fIgnoreList[i]);
			fUserDictService->AddToUserDict(fMemoryIgnoredWordsDictionary, wideIgnoreWord, nil, kTrue);
		}
	}

	return kTrue;
}


void	SpellPanelOptions::SetCaseSensitive(bool16 bCaseSensitive)
{
	if (bCaseSensitive != fCaseSensitive)
	{
		PreDirty ();
		fCaseSensitive = bCaseSensitive;
		
	}
}

//note: we need this second implementation because some bosses
// were using kSpellPanelOptionsImpl twice, which isn't allowed -ldb 11/18/98

class SpellPanelOptions2 : public SpellPanelOptions
{
public:
			SpellPanelOptions2(IPMUnknown * boss):SpellPanelOptions(boss){}
};


CREATE_PERSIST_PMINTERFACE(SpellPanelOptions2, kSpellPanelOptionsImpl2)
