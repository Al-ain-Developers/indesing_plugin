//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLData.cpp $
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

// ----- Interfaces -----

#include "ICHLData.h"
#include "ICHLFileNameTable.h"
#include "IK2ServiceProvider.h"
#include "IK2ServiceRegistry.h"
#include "ILanguage.h"
#include "ISession.h"
#include "IUserDictService.h"

// ----- Includes -----

#include "CHLID.h"
#include "FileTypeRegistry.h"
#include "K2Vector.h"
#include "LinguisticID.h"
#include "PMString.h"
#include "SDKFileHelper.h"
#include "WideString.h"
#include "TextChar.h"

// ----- Utility files -----

#include "CHLUtils.h"
#include "FileUtils.h"


/** Implements a custom data interface for the linguistic service. 
 *  
 * 	
 *  @ingroup chlinguistic
 */
class CHLData : public CPMUnknown<ICHLData>
{
public:
	CHLData(IPMUnknown * boss);
	~CHLData();

	virtual	int32	GetNumSearchPaths(void) {return fNumSearchPaths;}
	virtual	void	SetNumSearchPaths(int32 numSearchPaths) {fNumSearchPaths = numSearchPaths;}
	virtual void*	AddSearchPath(bool16 flush);
	virtual void*	RemoveSearchPath(bool16 flush);

	virtual	void			SetNotWordUDCFileName(const PMString &rName);
	virtual void			SetIsWordUDCFileName(const PMString &rName);
	virtual	const PMString&	GetNotWordUDCFileName() const {return fNotWordUDCFileName;}
	virtual	const PMString&	GetIsWordUDCFileName() const {return fIsWordUDCFileName;}

	virtual IDFile*		CreateNewUDC(const PMString& fileName);	//used for creating additional UDC files
	virtual IDFile*		GetUDC(const PMString& fileName);	//used for getting UDC files
	virtual	IDFile*		GetNotWordUDC(bool16 bCreateIfNotFound);
	virtual	IDFile*		GetIsWordUDC(bool16 bCreateIfNotFound);

private:
	PMString	fNotWordUDCFileName;	//default NOT data file name
	PMString	fIsWordUDCFileName;		//default UDC data file name

	int32		fNumSearchPaths;

	IDFile* fUDC;
	IDFile* fNotUDC;

	ICHLFileNameTable *	QueryFileNameTable();
};

CREATE_PMINTERFACE(CHLData, kCHLDataImpl)


/* CHLData constructor
 */
CHLData::CHLData( IPMUnknown * boss ) :
	CPMUnknown<ICHLData>(boss),
		fNotWordUDCFileName(),
		fIsWordUDCFileName(),
		fUDC(nil),
		fNotUDC(nil),
		fNumSearchPaths(0)
{
}

/* CHLData destructor 
 */
CHLData::~CHLData()
{
	if (fNotUDC)
	{
		delete fNotUDC;
		fNotUDC = nil;
	}

	if (fUDC)
	{
		delete fUDC;
		fUDC = nil;
	}
}
	
/* CHLData::SetNotWordUDCFileName
 */
void CHLData::SetNotWordUDCFileName( const PMString &rName )
{
	fNotWordUDCFileName = rName;
}

/* CHLData::SetIsWordUDCFileName
 */
void CHLData::SetIsWordUDCFileName( const PMString &rName )
{
	fIsWordUDCFileName = rName;
}
	
/* CHLData::QueryFileNameTable()
 */
ICHLFileNameTable *CHLData::QueryFileNameTable()
{
	InterfacePtr<IK2ServiceRegistry> registry(GetExecutionContextSession(), UseDefaultIID());
	InterfacePtr<IK2ServiceProvider> chlService(registry->QueryServiceProviderByClassID(kLinguisticService, kCHLinguisticBoss));
	ASSERT_MSG(chlService != nil, "CHLData - can't find service provider ");
	return chlService ? (ICHLFileNameTable*)chlService->QueryInterface(IID_ICHLFILENAMETABLE) : nil;
}

/* CHLData::CreateNewUDC
 */
IDFile* CHLData::CreateNewUDC(const PMString& fileName)
{
	IDFile* retval = new IDFile(fileName);

	return retval;
}

/* CHLData::GetUDC
 */
IDFile* CHLData::GetUDC(const PMString& fileName)
{
	IDFile idFile(fileName);

	if (idFile.Exists())
	{
		return new IDFile(fileName);
	}

	return nil;
}

/* CHLData::GetNotWordUDC
 *
 * Get the default NOT data file
 */
IDFile* CHLData::GetNotWordUDC(bool16 bCreateIfNotFound)
{
	if (! fNotUDC)
		fNotUDC = CreateNewUDC(fNotWordUDCFileName);

	return fNotUDC;
}

/* CHLData::GetIsWordUDC
 *
 * Get the default UDC data file
 */
IDFile* CHLData::GetIsWordUDC(bool16 bCreateIfNotFound)
{
	if (! fUDC)
		fUDC = CreateNewUDC(fIsWordUDCFileName);

	return fUDC;
}

/* CHLData::AddSearchPath
 */
void* CHLData::AddSearchPath(bool16 flush)
{
	++fNumSearchPaths;

	//handle any necessary items for adding a search path, and return the path...

	return nil;
}

/* CHLData::RemoveSearchPath
 */
void* CHLData::RemoveSearchPath(bool16 flush)
{
	--fNumSearchPaths;

	//handle any necessary items for removing a search path, and return the path...

	return nil;
}
