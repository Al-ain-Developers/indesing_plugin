//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/PlatformIconClass.h $
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
//  
//  An icon class that draws itself without a widget
//  
//  This is a class that will draw an icon family with the specified resource id. 
//  
//========================================================================================

#pragma once
#ifndef __PlatformIconClass__
#define __PlatformIconClass__

#ifdef WIDGET_BUILD
#pragma export on
#endif

#include "PNGIcon.h"

typedef PNGIcon PlatformIconClass; //No longer supports platform-resources

#pragma export off

#endif // __PlatformIconClass__




