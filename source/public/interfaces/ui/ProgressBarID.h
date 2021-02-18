//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ProgressBarID.h $
//  
//  Owner: Neil Levine
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

#ifndef __ProgressBarID__
#define __ProgressBarID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kProgressBarPrefix	 RezLong(0x8500)

// <Start IDC>
// <Class ID>
//******CLASS IDs

// <Interface ID>
//******INTERFACE IDs

// <Service ID>
//******SERVICE IDs

// <Implementation ID>
//******IMPLEMENTATION IDs

// <Ignore>
//******OWNER IDs (for special useage by the Progress Bar Users)

//gap #define 			kProgressBarPrefix + 1
//gap #define 			kProgressBarPrefix + 2
//gap #define 			kProgressBarPrefix + 3
#define kProgressBarUserColorMap			kProgressBarPrefix + 4
#define kProgressBarUserCompareDisplayList	kProgressBarPrefix + 5
#define kProgressBarUserImportImage			kProgressBarPrefix + 6
#define kProgressBarUserAutoFlowCmd			kProgressBarPrefix + 7
#define kProgressBarUserEPSServer			kProgressBarPrefix + 8
#define kProgressBarUserFindChange			kProgressBarPrefix + 9
#define kProgressBarDocumentActions			kProgressBarPrefix + 10
#define kProgressBarUserPDFExportCmd		kProgressBarPrefix + 11
#define kProgressBarPrintCmd				kProgressBarPrefix + 12
#define kProgressBarEPSExportCmd			kProgressBarPrefix + 13
#define kProgressBarLoadStyleCmd			kProgressBarPrefix + 14
#define kProgressBarUserPDFPlaceCmd			kProgressBarPrefix + 15


#endif // __ProgressBarID__	
