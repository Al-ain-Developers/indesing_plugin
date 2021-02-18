//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chlinguistic/CHLUserDict.h $
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

#ifndef __CHLUserDict_h__
#define __CHLUserDict_h__
#include "LanguageID.h"

#define HY_NORM			0x04
#define HY_PREF			0x05
#define HY_UNPREF		0x06

class ILanguage;
class IDFile;

#include "UserDictWordList.h"
#include "IUserDictService.h"

//----------------------------------------------------------------------------------------
// Class CHLUserDict
//----------------------------------------------------------------------------------------

class CHLUserDict : public CPMUnknown<IUserDict>
{
public:
			CHLUserDict(IPMUnknown * boss);
	virtual	~CHLUserDict();
	
	virtual void			SetFilePathName(const PMString& filePath);
	virtual const PMString&	GetFilePathName(void) const;

	virtual void		SetDataFile(void* dataFile);
	virtual void*		GetDataFile(void) const;

	virtual	void		Flush(void);

	virtual PMString	GetDisplayName();

public:
			void		GetUserDictWordList(UserDictWordList& userDictWordList);
			void		SetUserDictWordList(const UserDictWordList& userDictWordList);
			void		SetLanguageID(LanguageID languageID);
			LanguageID	GetLanguageID(void);

protected:
	PMString	fFilePathName;
	IDFile*		fUDCDataFile;
	LanguageID	fLanguageID;
	
private:
	UserDictWordList fUserDictWordList;
};

#endif // __CHLUserDict_h__
