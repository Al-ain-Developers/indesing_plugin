//========================================================================================
//  
//  File: IWRFontCache.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWRFontCache__
#define __IWRFontCache__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "IWRFont.h"
#include "WRFontContextComponent.h"
#include "WRVector.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif

class WRSERVICES_DECL IWRFontCache : public WRFontContextComponent
{
public:
	virtual ~IWRFontCache() {}
	virtual IWRFont*	GetFont(WRFontDict* dict,WRVector<WRFloat> designVec=WRVector<WRFloat>()) = 0;
	virtual void Open() = 0;
	virtual void Close() = 0;
	virtual void Invalidate() = 0;
};



#endif
