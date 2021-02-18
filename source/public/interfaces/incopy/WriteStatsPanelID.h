//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/WriteStatsPanelID.h $
//  
//  Owner: kevin van wiel
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

#ifndef __WriteStatsPanelID__
#define __WriteStatsPanelID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kWriteStatsPanelPrefix	 RezLong(0xa100)	// reserved in AdobePrefix.h

//PlugInID
#define kWriteStatsPanelPlugInName					"WriteStats"
DECLARE_PMID(kPlugInIDSpace, kWriteStatsPanelPlugInID, kWriteStatsPanelPrefix + 1)

// ClassIDs
DECLARE_PMID(kClassIDSpace, kWriteStatsPanelRegisterBoss, kWriteStatsPanelPrefix + 2)
DECLARE_PMID(kClassIDSpace, kWriteStatsPanelStringRegisterBoss, kWriteStatsPanelPrefix + 3)
DECLARE_PMID(kClassIDSpace, kWriteStatsPanelBoss, kWriteStatsPanelPrefix + 4)
DECLARE_PMID(kClassIDSpace, kWriteStatsSliderBoss, kWriteStatsPanelPrefix + 5)
// intentional gap

// widgetIDs (ClassIDs)
#define kWriteStatsWidgetPrefix						kWriteStatsPanelPrefix + 10
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelCharDataWidgetID, kWriteStatsWidgetPrefix + 0)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelWordDataWidgetID, kWriteStatsWidgetPrefix + 1)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelLineDataWidgetID, kWriteStatsWidgetPrefix + 2)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelLineRemainDataWidgetID, kWriteStatsWidgetPrefix + 3)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelOverfitDataWidgetID, kWriteStatsWidgetPrefix + 4)
DECLARE_PMID(kWidgetIDSpace, kWriteStatsPanelOverfitGraphWidgetID, kWriteStatsWidgetPrefix + 5)

#define kWriteStatsPanelWidgetCount					6


// Implementation IIDs
DECLARE_PMID(kImplementationIDSpace, kWriteStatsPanelRegisterImpl, kWriteStatsPanelPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kWriteStatsPanelStringRegisterImpl, kWriteStatsPanelPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kWriteStatsPanelObserverImpl, kWriteStatsPanelPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kWriteStatsIdleTaskImpl, kWriteStatsPanelPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kWriteStatsSliderViewImpl, kWriteStatsPanelPrefix + 6)



#endif // __WriteStatsPanelID__




