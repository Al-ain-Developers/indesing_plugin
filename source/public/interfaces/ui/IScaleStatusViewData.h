//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IScaleStatusViewData.h $
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
//========================================================================================

#pragma once
#ifndef __ISCALESTATUSVIEWDATA__
#define __ISCALESTATUSVIEWDATA__

//========================================================================================
// Forward declaration
//========================================================================================

//========================================================================================
// CLASS IScaleStatusViewData
//========================================================================================

class IScaleStatusViewData : public IPMUnknown
{
// ----- Accessors
public:
	virtual void			SetScaleFactor(const PMReal& xScaleFactor,
										   const PMReal& yScaleFactor) = 0;
	virtual void			GetScaleFactor(PMReal& xScaleFactor,
										   PMReal& yScaleFactor) const = 0;
};

#endif
