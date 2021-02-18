//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IAATActionListAddOn.h $
//  
//  Owner: Gregor Kaplan
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
#ifndef __IAATActionListAddOn__
	#define __IAATActionListAddOn__

#include "IPMUnknown.h"
#include "ProductTypeDefs.h"

class IAATFactory;
class AATActionHexID;

class IAATActionListAddOn : public IPMUnknown
{
	public:
		virtual ~IAATActionListAddOn() {}
		
		
		
		virtual ProdBool Init(void) = 0;
		virtual ProdBool IsInited(void) = 0;
		
		virtual void	GetListNamesToAddOn(K2Vector<ProdString>&names) = 0;
		virtual ProdBool	AddsToThisList(const ProdString &idStr) = 0;
		
		virtual const AATActionHexID& GetNthAATActionID(const ProdString &idStr, ProdInt32 index) = 0;
		virtual ProdInt32			GetNumAATActionIDs(const ProdString &idStr) = 0;
		
		virtual void AddAATActionID(const ProdString &idStr, const AATActionHexID &id) = 0;
		virtual void RemoveAATActionID(AATActionHexID &id) = 0;
		
		virtual void	RegisterAATActions(IAATFactory *factory, ProdString *filter) = 0;
};


#endif //__IAATFactory__