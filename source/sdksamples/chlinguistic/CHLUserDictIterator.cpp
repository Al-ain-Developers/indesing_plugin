//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDictIterator.cpp $
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

#include "VCPlugInHeaders.h"		// must be the first header file to include

#include "IUserDictIterator.h"
#include "ICHLData.h"

#include "K2SmartPtr.h"
#include "HelperInterface.h"
#include "LinguisticID.h"
#include "PMString.h"
#include "CHLID.h"
#include "Trace.h"
#include "UserDictWordList.h"
#include "CHLUserDict.h"

#include "K2Vector.h"

/** Implements a user dictionary iterator, used to walk all the entries in a single user dictionary. 
 *  
 * 	
 *  @ingroup chlinguistic
*/
class CHLUserDictIterator : public CPMUnknown<IUserDictIterator>
{
public:
				CHLUserDictIterator(IPMUnknown * boss);
				~CHLUserDictIterator();

	virtual bool16	First( IUserDictService *pService, IUserDict* userDict, IUserDictService::WordType nType, WideString *pWord );
	virtual bool16	Next( WideString *pWord );

private:
	bool16						fRunning;
	IUserDictService::WordType 	fType;
	ICHLData	*				fCHLData;
	IUserDict	*				fUserDict;
	const WideString			fPrefTilde;
	const WideString			fRegularTilde;
	const WideString			fUnprefTilde;
	const WideString			fBackSlash;
	PMString					fFileName;

	UserDictWordList			fUDWordList;
	//UserDictWordList::iterator	fUDWordListIterator;

	int32						fUDWordListIndex;

};

CREATE_PMINTERFACE(CHLUserDictIterator, kCHLUserDictIteratorImpl)



#define 	kPrefTilde		"~"
#define 	kRegularTilde	"~~"
#define 	kUnprefTilde	"~~~"
#define 	kBackSlash		"\\"


/* CHLUserDictIterator::CHLUserDictIterator
 */
CHLUserDictIterator::CHLUserDictIterator(IPMUnknown *boss) :
	CPMUnknown<IUserDictIterator>(boss),
		fRunning( kFalse ),
		fType( IUserDictService::kIsAWord ),
		fCHLData( nil ),
		fPrefTilde( kPrefTilde ),
		fRegularTilde( kRegularTilde ),
		fUnprefTilde( kUnprefTilde ),
		fBackSlash( kBackSlash ),
		fFileName(),
		fUserDict(nil),
		fUDWordListIndex(-1)
{
}

/* CHLUserDictIterator::~CHLUserDictIterator
 */
CHLUserDictIterator::~CHLUserDictIterator()
{
}

/* CHLUserDictIterator::First
 *
 * reset the user dictionary iterator and return the first word in the user dictionary
 */
bool16 CHLUserDictIterator::First(IUserDictService *pService, IUserDict * pUserDict, IUserDictService::WordType nType, WideString *pWord)
{
	bool16 retval = kFalse;

	ASSERT(pService);
	if (!pService)
		return kFalse;

	pWord->Clear();
	fRunning = kFalse;
	fType = nType;
	
	InterfacePtr<ICHLData> chlData(pService, IID_ICHLINGUISTICDATA);
	if (!chlData)
		return kFalse;

	if (pUserDict)
	{
		fFileName = pUserDict->GetFilePathName();
	}
	else
	{
		fFileName = IUserDictService::kIsAWord ? chlData->GetIsWordUDCFileName() : chlData->GetNotWordUDCFileName();
	}

	//IDFile *dataFile = fType == IUserDictService::kIsAWord ? (IDFile*)pUserDict->GetDataFile() :  chlData->GetNotWordUDC( kFalse );
	//if (!dataFile)
	//	return kFalse;
	
	if( fUserDict )
		fUserDict->Release();
	fUserDict = pUserDict;
	fUserDict->AddRef();
	
	fRunning = kTrue;

	CHLUserDict* chlUserDict = static_cast<CHLUserDict*>(fUserDict);
	if (chlUserDict)
	{
		chlUserDict->GetUserDictWordList(fUDWordList);
	}

	fUDWordListIndex = 0;

	return this->Next( pWord );
}

/* CHLUserDictIterator::Next
 *
 * get the next word in the user dictionary
 */
bool16 CHLUserDictIterator::Next( WideString *pWord )
{
	pWord->Clear();

	if( !fRunning)
		return kFalse;

	if (fUDWordListIndex >= fUDWordList.Length())
	{
		fRunning = kFalse;

		if( fUserDict )
		{
			fUserDict->Release();
			fUserDict = nil;
		}
		return kFalse;
	}

	*pWord = fUDWordList[fUDWordListIndex++];

	return kTrue;
}

