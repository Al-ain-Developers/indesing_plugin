//========================================================================================
//  
//  File: IWROptyca.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//  
//========================================================================================

#ifndef __IWROptycaPool__
#define __IWROptycaPool__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"
#include "WRFontContextComponent.h"

class IWROptyca;

class WRSERVICES_DECL IWROptycaPool : public WRFontContextComponent
{
public:
	virtual ~IWROptycaPool() {}
	virtual IWROptyca*		Create() = 0;
	virtual void			Delete(IWROptyca* inst) = 0;
	virtual	void			Cleanup() = 0;	// flush all buffers (be sure it has been called BEFORE CTTerminate!
};

#endif
