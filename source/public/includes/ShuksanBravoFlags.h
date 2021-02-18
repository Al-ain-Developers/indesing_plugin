//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ShuksanBravoFlags.h $
//  
//  Owner: Chris Jones
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
//  ADOBE CONFIDENTIAL
//  
//  Global include file for AGM. Any code within InDesign that needs to access
//  CoreTech objects should include this rather than including CoreTech headers
//  directly.
//  
//  Notes:
//  
//  InDesign #defines BIB_NO_THROW to force CoreTech components not to throw
//  exceptions in error situations
//  
//========================================================================================

#pragma once
#ifndef __ShuksanBravoFlags__
#define __ShuksanBravoFlags__


// Disable exception throwing by BIB components
#if !defined(INDESIGN_BIB_THROW) && !defined(BIB_NO_THROW)
#define BIB_NO_THROW
#endif


// Enable multi-threaded components.
#ifndef BIB_MULTI_THREAD
#define BIB_MULTI_THREAD
#endif



// setup the correct namespace name.
#ifdef BIB_MULTI_THREAD
 #ifdef INDESIGN_BIB_THROW
  #define INDESIGN_BIB_NS BIB_T_MT
 #else
  #ifdef SANGAM_TEMPORARY_HACKFEST
   #define INDESIGN_BIB_NS BIB_NT
  #else
   #define INDESIGN_BIB_NS BIB_NT_MT
  #endif
 #endif
#else
 #ifdef INDESIGN_BIB_THROW
  #define INDESIGN_BIB_NS BIB_T_NMT
 #else
  #ifdef SANGAM_TEMPORARY_HACKFEST
   #define INDESIGN_BIB_NS BIB_NT
  #else
   #define INDESIGN_BIB_NS BIB_NT_NMT
  #endif
 #endif
#endif

// if bib namespaces are off, #define everything to nothing,
// otherwise, give it a meaninful definition.
#ifdef INDESIGN_DISABLE_BIB_NAMESPACES
#undef INDESIGN_BIB_NS 
#define INDESIGN_BIB_NS 
#define BEGIN_BIB_NAMESPACE
#define END_BIB_NAMESPACE
#define USING_BIB_NAMESPACE
#error "Using no namespaces"
#else
#define BEGIN_BIB_NAMESPACE namespace INDESIGN_BIB_NS {
#define END_BIB_NAMESPACE }
#define USING_BIB_NAMESPACE using namespace INDESIGN_BIB_NS
#endif


#endif 
