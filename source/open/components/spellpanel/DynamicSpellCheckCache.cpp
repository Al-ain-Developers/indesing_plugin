//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/DynamicSpellCheckCache.cpp $
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
//========================================================================================

#include "VCPlugInHeaders.h"

#include "CDynamicSpellCheckCache.h"

#include "HelperInterface.h"
#include "SpellPanelID.h"

#include "K2Vector.h"
	
/* template */
#include "TemplateDefs.h"
#include "k2sortedvector.tpp"		
#include "K2Vector.tpp"	

#ifdef WINDOWS
#pragma warning (disable:4660)
#endif

TEMPLATE K2Vector<DSCCache>;

//----------------------------------------------------------------------------------------
// CLASS DynamicSpellCheckCache 
//----------------------------------------------------------------------------------------
class DynamicSpellCheckCache : public CDynamicSpellCheckCache
{
public:
	DynamicSpellCheckCache(IPMUnknown *boss);

};

CREATE_PMINTERFACE(DynamicSpellCheckCache, kDynamicSpellCheckCacheImpl);

//----------------------------------------------------------------------------------------
// DynamicSpellCheckCache constructor 
//----------------------------------------------------------------------------------------
DynamicSpellCheckCache::DynamicSpellCheckCache(IPMUnknown *boss) :
	CDynamicSpellCheckCache(boss)
{
	//TRACEFLOW_OBSOLETE("DSC", "DynamicSpellCheckCache::DynamicSpellCheckCache\n");
}
