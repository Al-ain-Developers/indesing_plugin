//========================================================================================
//  
//  File: IWRCharBuffer.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __ICharBuffer__
#define __ICharBuffer__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRChar.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif


class WRSERVICES_DECL IWRCharBuffer
{
public:
#ifndef WR_WIN_ENV
	virtual				~IWRCharBuffer() {} // gcc needs it even in abstract classes
#endif
	virtual IWRChar&	GetChar(WRInt32 i) = 0;
	virtual WRInt32		Size(void) const = 0;
	virtual void		Remove(WRInt32 start, WRInt32 count = 1) = 0;
	virtual WRError		Insert(IWRChar* item, WRInt32 start, WRInt32 count = 1) = 0;
};

#endif
