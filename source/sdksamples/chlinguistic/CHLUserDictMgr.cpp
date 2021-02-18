//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDictMgr.cpp $
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

#include "ICHLData.h"
#include "IUserDictMgr.h"
#include "ILinguisticServiceData.h"
#include "ICHLFileNameTable.h"
#include "IUserDictService.h"
#include "ISpellingMgr.h"
#include "ISpellingService.h"
#include "ILanguage.h"
#include "ISession.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILinguisticMgr.h"

#include "CHLID.h"
#include "LanguageID.h"
#include "LinguisticID.h"

#include "CHLUtils.h"
#include "HelperInterface.h"
#include "CrossPlatformTypes.h"
#include "PMString.h"
#include "FileUtils.h"
#include "SDKFileHelper.h"

/** Implements a user dictionary manager. 
 *  
 * 	
 *  @ingroup chlinguistic
*/
class CHLUserDictMgr : public CPMUnknown<IUserDictMgr>
{
public:
	CHLUserDictMgr(IPMUnknown * boss);
	~CHLUserDictMgr() {};

	virtual	void				Install( const PMString &rPath );
	virtual	int32				GetLanguageCount() const;
	virtual	ILanguage*			QueryNthLanguage( int32 nNth );
	virtual	bool16				HasLanguage( const ILanguage * pLanguage ) const;
	virtual	IUserDictService*	QueryServiceOfLanguage( const ILanguage * pLanguage );
};

CREATE_PMINTERFACE(CHLUserDictMgr, kCHLUserDictMgrImpl)

/* CHLUserDictMgr constructor
 */
CHLUserDictMgr::CHLUserDictMgr(IPMUnknown *boss) :
	CPMUnknown<IUserDictMgr>(boss)
{
	InterfacePtr<ILinguisticServiceData>pData( this, IID_ILINGUISTICDATA );
	this->Install( pData->GetPath() );
}

/* CHLUserDictMgr::Install
 */
void	CHLUserDictMgr::Install( const PMString &rPath )
{
	InterfacePtr<ICHLFileNameTable> pTable( this, UseDefaultIID() );
	pTable->Install( rPath );
	const int32 nMax = pTable->GetEntriesCount();

	InterfacePtr<ISpellingMgr> pSpellingMgr( this, UseDefaultIID() );
	if( !pSpellingMgr || pSpellingMgr->GetLanguageCount() != nMax )
	{
		ASSERT_MSG( kFalse, "CHLUserDictMgr - please install ISpellingService before CHLUserDictMgr." );
		return;
	}

	PMString aName, aPrimName, aSubName;
	InterfacePtr<IK2ServiceRegistry>	pServices(GetExecutionContextSession(), IID_IK2SERVICEREGISTRY);
	InterfacePtr<IK2ServiceProvider>pLinguMgrService( pServices->QueryDefaultServiceProvider( kLinguisticManagerService ) );
	InterfacePtr<ILinguisticMgr>pLinguMgr( pLinguMgrService, IID_ILINGUISTICMGR );

	// Get the location to store user created dictionaries.
	// They are stored in the local "Application Data" directory.
	PMString fileName("");
	IDFile idFile;
	bool16 gotUserDictFolder = FileUtils::GetUserDictionariesFolder( &idFile, fileName );

	PMString userDataPath;

	SDKFileHelper sdkFileHelper(idFile);
	userDataPath = sdkFileHelper.GetPath();

	//InDesign defaults to Proximity, strip this off
	CHLUtils::RemoveLastElement(userDataPath);

#if WINDOWS
	userDataPath.Append("\\");
#endif
#if MACINTOSH
	userDataPath.Append(":");
#endif

	//Append our folder name "CodeHawgs"
	PMString dictionaryFolderName(kCHShortName);
	userDataPath.Append(dictionaryFolderName);

	idFile = FileUtils::PMStringToSysFile(userDataPath);

	if (! idFile.Exists())
	{
		bool16 created = idFile.MakeDirectory();
		ASSERT(created);
	}

#if WINDOWS
	userDataPath.Append("\\");
#endif
#if MACINTOSH
	userDataPath.Append(":");
#endif

	for( int32 i = 0; i < nMax; ++i )
	{
		const CHLFileNameData *pData = pTable->GetNthEntry( i );
		PMString aUserDictFileName( pData->fDefaultUserDictFileName );

		if (aUserDictFileName.IsEmpty())
			continue;

		aUserDictFileName.Insert( userDataPath, 0 );

		PMString aNonDictFileName( aUserDictFileName );
		aNonDictFileName.Truncate( 4 );
		aNonDictFileName.Append( ".NOT" );
		
		InterfacePtr<const ILanguage>pLanguage( pLinguMgr->QueryLanguage( pData->fLanguageName ) );
		InterfacePtr<ISpellingService>pSpellingService( pSpellingMgr->QueryServiceOfLanguage( pLanguage ) );

		InterfacePtr<ICHLData> pCHLData( pSpellingService, UseDefaultIID() );
		if( pCHLData )
		{
			pCHLData->SetIsWordUDCFileName( aUserDictFileName );
			pCHLData->SetNotWordUDCFileName( aNonDictFileName );
		}
	}
}

/* CHLUserDictMgr::GetLanguageCount
 */
int32 CHLUserDictMgr::GetLanguageCount() const
{
	InterfacePtr<const ISpellingMgr>pSpellingMgr( this, IID_ISPELLINGMGR );
	return pSpellingMgr ? pSpellingMgr->GetLanguageCount() : 0;
}

/* CHLUserDictMgr::QueryNthLanguage
 */
ILanguage* CHLUserDictMgr::QueryNthLanguage( int32 nNth )
{
	InterfacePtr<ISpellingMgr>pSpellingMgr( this, IID_ISPELLINGMGR );
	return pSpellingMgr ? pSpellingMgr->QueryNthLanguage( nNth ) : nil;
}

/* CHLUserDictMgr::HasLanguage
 */
bool16	CHLUserDictMgr::HasLanguage( const ILanguage *pLanguage ) const
{
	InterfacePtr<const ISpellingMgr>pSpellingMgr( this, IID_ISPELLINGMGR );
	return pSpellingMgr ? pSpellingMgr->HasLanguage( pLanguage ) : kFalse;
}

/* CHLUserDictMgr::QueryServiceOfLanguage
 */
IUserDictService* CHLUserDictMgr::QueryServiceOfLanguage( const ILanguage *pLanguage )
{
	ASSERT_MSG( pLanguage != nil, "CHLUserDictMgr - language is nil" );
	if( !pLanguage )
		return nil;

	InterfacePtr<ISpellingMgr>pSpellingMgr( this, IID_ISPELLINGMGR );
	if( !pSpellingMgr )
		return nil;
	
	InterfacePtr<ISpellingService>pSpellingService( pSpellingMgr->QueryServiceOfLanguage( pLanguage ) );
	if( !pSpellingService )
		return nil;

	return (IUserDictService*)pSpellingService->QueryInterface( IID_IUSERDICTSERVICE );
}

