//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/links/CLinkInfoProvider.cpp $
//  
//  Owner: lance bushore
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

#include "VCPublicHeaders.h"

// ----- Interface files
#include "CLinkInfoProvider.h"

#ifdef DEBUG
#include "DebugClassUtils.h"
#endif


CLinkInfoProvider::CLinkInfoProvider(IPMUnknown * boss)
	: CPMUnknown<ILinkInfoProvider>(boss)
{
}

CLinkInfoProvider::~CLinkInfoProvider()
{
}

int32 CLinkInfoProvider::Compare(const ILink* link1, const ILinkResource* linkResource1,const ILink* link2, const ILinkResource* linkResource2) const
{
	PMString link1Str = GetUpdatedInfoForLink(link1,linkResource1,true);
	PMString link2Str = GetUpdatedInfoForLink(link2,linkResource2,true);
	return link1Str.Compare(kFalse,link2Str);
	
}

void CLinkInfoProvider::AttachToDocument(IObserver *observer, const IDocument* newDoc)
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides IsLinkInfoDynamic to return true, but fails to override AttachToDocument",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
}

void CLinkInfoProvider::DetachFromDocument(IObserver *observer, const IDocument* oldDoc)
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides IsLinkInfoDynamic to return true, but fails to override DetachFromDocument",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
}

bool16 CLinkInfoProvider::ShouldCauseRefreshOfInfo(const PMIID &protocol) const 
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides IsLinkInfoDynamic to return true, but fails to override ShouldCauseRefreshOfInfo",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
	return false;
}


void CLinkInfoProvider::DoSingleClickAction(const ILink* link, const ILinkResource* linkResource) 
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides CanDoSingleClickAction to return true, but fails to override DoSingleClickAction",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
}

void CLinkInfoProvider::DoDoubleClickAction(const ILink* link, const ILinkResource* linkResource) 
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides CanDoDoubleClickAction to return true, but fails to override DoDoubleClickAction",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
}

PMString CLinkInfoProvider::GetDoubleClickDescription(const ILink* link, const ILinkResource* linkResource) const 
{ 
#ifdef DEBUG
	DebugClassUtilsBuffer idBuf;
	ASSERT_FAIL(FORMAT_ARGS("Info Provider class %s overrides CanDoDoubleClickAction to return true, but fails to override GetDoubleClickDescription",DebugClassUtils::GetIDName(&idBuf,::GetClass(this))));  
#endif
	return "";
}
