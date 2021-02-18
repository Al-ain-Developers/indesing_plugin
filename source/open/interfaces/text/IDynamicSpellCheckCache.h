//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/text/IDynamicSpellCheckCache.h $
//  
//  Owner: Heath Horton
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
//  Proj:	SpellingPanel
//  
//========================================================================================

#pragma once
#ifndef _H_IDynamicSpellCheckCache
#define _H_IDynamicSpellCheckCache

#include "IPMUnknown.h"
#include "SpellPanelID.h"
#include "K2Vector.h"
#include "PMRect.h"
#include "IColorData.h"

struct DSCCache {
	typedef object_type data_type;

	ColorArray	fColor;
	PMRect		fRect;
	PMReal		fWidth;
	int16		fSpellResult;
};

class IDynamicSpellCheckCache : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IDYNAMICSPELLCHECKCACHE};
	
	virtual bool16 		GetCacheFlag() = 0;
	virtual void 		SetCacheFlag(bool16 flag) = 0;	

	virtual K2Vector<DSCCache>*		GetCache() = 0;
	virtual void		SetCache(K2Vector<DSCCache>* cache) = 0;
};

#endif /* _H_IDynamicSpellCheckCache */