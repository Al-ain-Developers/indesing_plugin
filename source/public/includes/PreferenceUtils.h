//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PreferenceUtils.h $
//  
//  Owner: Tommy Donovan
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

#pragma once
#ifndef __PreferenceUtils__
#define __PreferenceUtils__

class IPMUnknown;
class IActiveContext;

#pragma export on

template <class FACE>									
inline FACE* QuerySessionPreferences()				
{	
	IPMUnknown* face = QuerySessionPreferences(FACE::kDefaultIID);
	
	return static_cast<FACE*>(face);
}

// ---- Query for a preferences interface from either the workspace of the document
//		or Session, whichever is active.
PUBLIC_DECL IPMUnknown* QueryPreferences(PMIID prefInterfaceID, IActiveContext* activeContext);

// ---- Query for a preferences interface in the session workspace.
PUBLIC_DECL IPMUnknown* QuerySessionPreferences(PMIID prefInterfaceID);

// ---- Query for a preferences interface in the workspace of the document in which
//		"object" resides.
PUBLIC_DECL IPMUnknown* QueryPreferences(PMIID prefInterfaceID, const IPMUnknown* object);
PUBLIC_DECL IPMUnknown* QueryPreferences(PMIID prefInterfaceID, const UIDRef& ref);

#pragma export off

#endif
