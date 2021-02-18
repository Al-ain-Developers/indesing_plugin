//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDistributeCmdData.h $
//  
//  Owner: psorrick
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
//  Values for IID_IINTDATA in DistributeCmd
//  
//========================================================================================

#pragma once
#ifndef __DISTRIBUTECMDDATA__
#define __DISTRIBUTECMDDATA__

typedef enum
{
	kFirstDistributeStandard = 0,
	kHDistributeLeft	= kFirstDistributeStandard,
	kHDistributeCenter	= 1,
	kHDistributeRight	= 2,
	kVDistributeTop		= 3,
	kVDistributeCenter	= 4,
	kVDistributeBottom	= 5,
	kLastDistributeStandard = kVDistributeBottom,
	kFirstDistributeSpace = 6,
	kVDistributeSpace	= kFirstDistributeSpace,
	kHDistributeSpace	= 7,
	kLastDistributeSpace = kHDistributeSpace,
	
	kFirstDistributeKeyObject = 8,
	kHDistributeKeyObjectLeft	= kFirstDistributeKeyObject,
	kHDistributeKeyObjectCenter	= 9,
	kHDistributeKeyObjectRight	= 10,
	kVDistributeKeyObjectTop		= 11,
	kVDistributeKeyObjectCenter	= 12,
	kVDistributeKeyObjectBottom	= 13,
	kLastDistributeKeyObject = kVDistributeKeyObjectBottom,
	kFirstDistributeKeyObjectSpace = 14,
	kVDistributeKeyObjectSpace	= kFirstDistributeKeyObjectSpace,
	kHDistributeKeyObjectSpace	= 15,
	kLastDistributeKeyObjectSpace = kHDistributeKeyObjectSpace,

	kFirstDistributeRect	= 16,
	kHPageDistributeLeft 		= kFirstDistributeRect,
	kHPageDistributeCenter		= 17,
	kHPageDistributeRight		= 18,
	kVPageDistributeTop			= 19,
	kVPageDistributeCenter		= 20,
	kVPageDistributeBottom		= 21,
	kVPageDistributeSpace		= 22,
	kHPageDistributeSpace		= 23,
	
	kHSpreadDistributeLeft 		= 24,
	kHSpreadDistributeCenter	= 25,
	kHSpreadDistributeRight		= 26,
	kVSpreadDistributeTop		= 27,
	kVSpreadDistributeCenter	= 28,
	kVSpreadDistributeBottom	= 29,
	kVSpreadDistributeSpace		= 30,
	kHSpreadDistributeSpace		= 31,
	
	kHMarginDistributeLeft 		= 32,
	kHMarginDistributeCenter	= 33,
	kHMarginDistributeRight		= 34,
	kVMarginDistributeTop		= 35,
	kVMarginDistributeCenter	= 36,
	kVMarginDistributeBottom	= 37,
	kVMarginDistributeSpace		= 38,
	kHMarginDistributeSpace		= 39,
	kLastDistributeRect	= kHMarginDistributeSpace

} DistributeType; 

// The DistributeType values can be used with another PMReal parameter (IID_IDISTRIBUTEREALNUMBERDATA) 
// to let user distribute objects numerically.

// Values for IID_USEDISTRIBUTEVALUEDATA
typedef enum
{
	kUseDistributeValue	= 0,
	kSkipDistributeValue = 1
} UseDistributeValue; 

#endif //__DISTRIBUTECMDDATA__

