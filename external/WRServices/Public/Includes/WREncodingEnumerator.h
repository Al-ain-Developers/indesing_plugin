//========================================================================================
//
//	File:	WREncodingEnumerator.h
//
//	Author: Pascal Rubini
//
//	Date:	9/11/00
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WREncodingEnumerator_h__
#define __WREncodingEnumerator_h__

#include "WRDefines.h"
#include "WRServices.h"
#include "WRPlatformUtils.h"

enum { 
	kWRUnicodeBasedEncoding = 1,// true for utf-7,8,16 and 32
	kWRVariableLengthEncoding = 2,// true of utf-7/8 and cjk
	kWRWesternArea = 4,
	kWRCJKArea = 8,
	kWRCentralEuropeArea = 16,
	kWRMiddleEasternArea = 32,
	kWRFakeScript = 64,
	kWRVisualOrdering = 128
};
	
typedef struct
{
	char		fEnglishName[32];
	char		fInternetName[32];
	WRCodePage	fCodePage;
	int			fEncodingLength;	// size of the base element 1,2 or 4 bytes
	WRScriptID	fScript;			// main script kWRDontKnowScript if multiscript
	WRPlatform	fPlatform;			// kWRUnknownPlatform if cross platform
	WRInt32		fProperties;
} WREncodingInfoRecord;

enum {
	kWRSortEncodingNone,
	kWRSortEncodingByArea,
	kWRSortEncodingByPlatform,
	kWRSortEncodingByScript
};

class WRSERVICES_DECL WREncodingEnumerator : public WRClass
{
public:
	WREncodingEnumerator(int key1 = kWRSortEncodingNone,int key2 = kWRSortEncodingNone, int key3 = kWRSortEncodingNone);
	~WREncodingEnumerator();

	int	 GetCount() const;
	int GetCurrent() const { return fCurrent; }
	const WREncodingInfoRecord*	GetNext();
	const WREncodingInfoRecord* GetIthRecord(int recIdx);
	void	Rewind() { fCurrent = 0; }

protected:
	void Sort(void);
	static int EncodingSortCompare(int key, const WREncodingInfoRecord* a, const WREncodingInfoRecord* b);
	int fCurrent;
	int* fIndexes;
	int fKey[3];
};

#endif //__WREncodingEnumerator_h__
