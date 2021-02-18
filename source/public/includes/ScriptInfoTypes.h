//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptInfoTypes.h $
//  
//  Owner: Jonathan W. Brown
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
#ifndef __SCRIPTINFOTYPES_H__
#define __SCRIPTINFOTYPES_H__

#include "AnsiBasedTypes.h"


#if !defined(__ODFRC__)
namespace ScriptInfo
{
#endif

//for resource directives
const int16 kReadOnly						= kFalse ;
const int16 kReadWrite						= kTrue ;
const int16 kReadOnlyButReadWriteForINX		= 0x10 ;

//for internal identification of resource elements
const int16 kSIBase							= 0x0001 ;
const int16 kSISuite						= kSIBase + 0 ;
const int16 kSIObject						= kSIBase + 1 ;
const int16 kSIMethod						= kSIBase + 2 ;
const int16 kSIProperty						= kSIBase + 3 ;
const int16 kSIEnum							= kSIBase + 4 ;
const int16 kSIParent						= kSIBase + 5 ;
const int16 kSIProvider						= kSIBase + 6 ;
const int16 kSIMetadata						= kSIBase + 7 ;
const int16 kSIEnumerator					= kSIBase + 8 ;
const int16 kSITranslation					= kSIBase + 9 ;
const int16 kSITypeDef						= kSIBase + 10 ;
const int16 kSIEvent						= kSIBase + 11 ;

//Use these instead of kDragontailM??orVersionNumber 
// for elements defined in Dragontail
const int32 kInitialScriptInfoMajorVersionNumber	= 0x0 ;
const int32 kInitialScriptInfoMinorVersionNumber	= 0x0 ;

#if !defined(__ODFRC__)
}	// End namespace ScriptInfo
#endif

#endif	// __SCRIPTINFOTYPES_H__
