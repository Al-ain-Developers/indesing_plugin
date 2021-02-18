//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IMessageBoolData.h $
//  
//  Owner: Thanh Nguyen
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
#ifndef __IMessageBoolData__
#define __IMessageBoolData__

class PMPoint;

#include "IBoolData.h"

/**	This is an obsolete data interface and will be removed.
	This interface will not be supported. Please do not use anymore.
*/
class IMessageBoolData : public IBoolData
{
	public:
		virtual void SetFromPanelObs(bool16 b) = 0;
		virtual void SetFromObserver(bool16 b) = 0;
		virtual void SetUpdateType(int16 updateType) = 0;
		virtual void SetHitIndex(int16 hitIndex) = 0;
		virtual void SetHitPoint(PMPoint hitPoint) = 0;
 		virtual void SetDeactivatePanel(bool16 b) = 0;
		virtual void SetMessageOwner(bool16 b) = 0;
		virtual void SetIsInDialog(bool16 b) = 0;
		virtual void SetRealNumber(PMReal value) = 0;

 		virtual	bool16 GetFromPanelObs() = 0;
		virtual bool16 GetFromObserver() = 0;
		virtual int16 GetUpdateType() = 0;
		virtual int16 GetHitIndex() = 0;
		virtual PMPoint GetHitPoint() = 0;
		virtual bool16 GetDeactivatePanel() = 0;
		virtual bool16 GetMessageOwner() = 0;  
		virtual bool16 GetIsInDialog() = 0;
		virtual PMReal GetRealNumber() = 0;
};
#endif 

