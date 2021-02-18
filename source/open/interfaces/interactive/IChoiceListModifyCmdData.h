 //========================================================================================
 //  
 //  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/interactive/IChoiceListModifyCmdData.h $
 //  
 //  Owner: Reena Agrawal
 //  
 //  $Author: pmbuilder $
 //  
 //  $DateTime: 2020/11/06 13:08:29 $
 //  
 //  $Revision: #2 $
 //  
 //  $Change: 1088580 $
 //  
 //  ADOBE CONFIDENTIAL
 //  
 //  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
 //  
 //  NOTICE:  All information contained herein is, and remains
 //  the property of Adobe Systems Incorporated and its suppliers,
 //  if any.  The intellectual and technical concepts contained
 //  herein are proprietary to Adobe Systems Incorporated and its
 //  suppliers and may be covered by U.S. and Foreign Patents,
 //  patents in process, and are protected by trade secret or copyright law.
 //  Dissemination of this information or reproduction of this material
 //  is strictly forbidden unless prior written permission is obtained
 //  from Adobe Systems Incorporated.
 //  
 //========================================================================================
 
 #pragma once
 #ifndef __IChoiceListModifyCmdData_h__
 #define __IChoiceListModifyCmdData_h__

#include "IPMUnknown.h"
#include "FormFieldID.h"

class IChoiceListModifyCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICHOICELISTMODIFYCMDDATA };
	enum ModificationRequired
	{
		kAddChoice,
		kRemoveChoice,
		kMoveChoice,
		kSortChoices,
		kClearChoices
	};

	virtual void SetChoice(const PMString &choice) = 0;
	virtual const PMString& GetChoice() const = 0;
	virtual void SetModificationRequired(ModificationRequired modification) = 0;
	virtual ModificationRequired GetModificationRequired() const = 0;
	virtual void SetPositionToMove(int32 pos) = 0;
	virtual int32 GetPositionToMove() const = 0;
};

 #endif
