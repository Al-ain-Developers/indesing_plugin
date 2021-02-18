//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/MeasurementSystemID.h $
//  
//  Owner: Robin_Briggs
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
//  Contains IDs used by the group item plug-in
//  
//========================================================================================

#ifndef __MeasurementSystemID__
#define __MeasurementSystemID__

#include "CrossPlatformTypes.h"
#include "IDFactory.h"

#define kMeasurementSystemPrefix	 RezLong(0x1200)


// <Start IDC>
// <Class ID>
// ClassIDs
DECLARE_PMID(kClassIDSpace, kPointsBoss, kMeasurementSystemPrefix + 1)
DECLARE_PMID(kClassIDSpace, kPicasBoss, kMeasurementSystemPrefix + 2)
DECLARE_PMID(kClassIDSpace, kInchesBoss, kMeasurementSystemPrefix + 3)
DECLARE_PMID(kClassIDSpace, kInchesDecimalBoss, kMeasurementSystemPrefix + 4)
DECLARE_PMID(kClassIDSpace, kMillimetersBoss, kMeasurementSystemPrefix + 5)
DECLARE_PMID(kClassIDSpace, kCentimetersBoss, kMeasurementSystemPrefix + 6)
DECLARE_PMID(kClassIDSpace, kCicerosBoss, kMeasurementSystemPrefix + 7)
DECLARE_PMID(kClassIDSpace, kSetMeasureUnitsCmdBoss, kMeasurementSystemPrefix + 8)
DECLARE_PMID(kClassIDSpace, kMeasurementSysConvBoss, kMeasurementSystemPrefix + 9)
DECLARE_PMID(kClassIDSpace, kAgatesBoss, kMeasurementSystemPrefix + 10)
DECLARE_PMID(kClassIDSpace, kPixelsBoss, kMeasurementSystemPrefix + 11)
DECLARE_PMID(kClassIDSpace, kRulerCustomMSBoss, kMeasurementSystemPrefix + 12)

// <Interface ID>
// IIDs
DECLARE_PMID(kInterfaceIDSpace, IID_IUNITOFMEASURE, kMeasurementSystemPrefix + 1)
DECLARE_PMID(kInterfaceIDSpace, IID_IUNITOFMEASURESETTINGS, kMeasurementSystemPrefix + 2)
DECLARE_PMID(kInterfaceIDSpace, IID_IMEASUREMENTSYSTEM, kMeasurementSystemPrefix + 3)
DECLARE_PMID(kInterfaceIDSpace, IID_IIMEASUREUNITSCMDDATA, kMeasurementSystemPrefix + 4)

// <Implementation ID>
// ImplementationIIDs
DECLARE_PMID(kImplementationIDSpace, kMeasurementSystemImpl, kMeasurementSystemPrefix + 1)
DECLARE_PMID(kImplementationIDSpace, kUnitOfMeasureSettingsImpl, kMeasurementSystemPrefix + 2)
DECLARE_PMID(kImplementationIDSpace, kPointsImpl, kMeasurementSystemPrefix + 3)
DECLARE_PMID(kImplementationIDSpace, kPicasImpl, kMeasurementSystemPrefix + 4)
DECLARE_PMID(kImplementationIDSpace, kInchesImpl, kMeasurementSystemPrefix + 5)
DECLARE_PMID(kImplementationIDSpace, kInchesDecimalImpl, kMeasurementSystemPrefix + 6)
DECLARE_PMID(kImplementationIDSpace, kMillimetersImpl, kMeasurementSystemPrefix + 7)
DECLARE_PMID(kImplementationIDSpace, kCentimetersImpl, kMeasurementSystemPrefix + 8)
DECLARE_PMID(kImplementationIDSpace, kCicerosImpl, kMeasurementSystemPrefix + 9)
DECLARE_PMID(kImplementationIDSpace, kSetMeasureUnitsCmdImpl, kMeasurementSystemPrefix + 10)
DECLARE_PMID(kImplementationIDSpace, kMeasureUnitsCmdDataImpl, kMeasurementSystemPrefix + 11)
DECLARE_PMID(kImplementationIDSpace, kDfltUnitOfMeasureServiceImpl, kMeasurementSystemPrefix + 12)
DECLARE_PMID(kImplementationIDSpace, kUnitOfMeasureService, kMeasurementSystemPrefix + 13)
DECLARE_PMID(kImplementationIDSpace, kMeasurementSystemConvProviderImpl, kMeasurementSystemPrefix + 14)
DECLARE_PMID(kImplementationIDSpace, kAgatesImpl, kMeasurementSystemPrefix + 15)
DECLARE_PMID(kImplementationIDSpace, kPixelsImpl, kMeasurementSystemPrefix + 16)
DECLARE_PMID(kImplementationIDSpace, kCustomMSImpl, kMeasurementSystemPrefix + 17)

// <Service ID>
// Service Provider IDs
DECLARE_PMID(kServiceIDSpace, kService_UnitOfMeasure, kMeasurementSystemPrefix + 1)

#endif // __MeasurementSystemID__




