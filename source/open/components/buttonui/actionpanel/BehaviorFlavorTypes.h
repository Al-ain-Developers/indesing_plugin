//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actionpanel/BehaviorFlavorTypes.h $
//  
//  Owner: Michael Burbidge
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
//  Generic PageItem Flavor Helper for URL data
//  
//========================================================================================

#pragma once
#ifndef __BehaviorFlavorTypes_h__
#define __BehaviorFlavorTypes_h__

#include "PMFlavorTypes.h"

#ifdef MACINTOSH
const PMFlavor kBehaviorDragDropFlavor = 'pmbe';
const PMFlavor kEventDragDropFlavor = 'pmev';
#endif

#ifdef WINDOWS
const PMFlavor kBehaviorDragDropFlavor = 0x105D;
const PMFlavor kEventDragDropFlavor = 0x105E;
#endif

#endif // __BehaviorFlavorTypes_h__
