//========================================================================================
//  
//  File: WRFontContextComponent.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __WRFontContextComponent__
#define __WRFontContextComponent__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"

#ifdef WR_WIN_ENV
#pragma warning(disable:4250)
#endif


class IWRFontAccess;
class IWRFontInfo;
class IWRFontCache;
class IWRFontContext;
class IWRMultiProcessing;
class IWROptycaPool;
class IWRClientSettings;
class IWRExtensions;

// bridge class
class WRSERVICES_DECL WRFontContextComponent : public WRClass
{
public:
	virtual ~WRFontContextComponent();
	virtual IWRFontContext*	GetFontContext();
	virtual void			SetFontContext(IWRFontContext* cntxt);
	virtual IWRMultiProcessing*	MultiProcessing();
	virtual IWRFontAccess*	Access();
	virtual IWRFontInfo*	Info();
	virtual IWRFontCache*	Cache();
	virtual IWROptycaPool*	OptycaPool();
	virtual IWRClientSettings*	ClientSettings();
	virtual IWRExtensions*	Extensions();

protected:
	IWRFontContext*	fContext;
};


#endif
