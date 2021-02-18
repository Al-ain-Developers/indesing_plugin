//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/CAATActionListAddOn.h $
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
#ifndef __CAATActionListAddOn__
	#define __CAATActionListAddOn__

#include "IAATActionListAddOn.h"
#include "IAATActionList.h"
#include "K2Pair.h"

#ifdef __clang__
	//Workaround for missing template members in client code
	template class CPMUnknown<IAATActionListAddOn>;
#endif
class AATLIB_DECL CAATActionListAddOn : public CPMUnknown<IAATActionListAddOn>
{
	public:
		CAATActionListAddOn(IPMUnknown *boss);
		virtual ~CAATActionListAddOn();
		
		virtual ProdBool	IsInited(void) { return fInited; }
		
		virtual void	GetListNamesToAddOn(K2Vector<ProdString>&names);
		virtual ProdBool	AddsToThisList(const ProdString &idStr);
		
		virtual const AATActionHexID& GetNthAATActionID(const ProdString &idStr, ProdInt32 index);
		virtual ProdInt32			GetNumAATActionIDs(const ProdString &idStr);
		
		virtual void AddAATActionID(const ProdString &idStr, const AATActionHexID &id);
		virtual void RemoveAATActionID(AATActionHexID &id);
		
		
	protected:
		ProdBool	fInited;
		K2Vector< K2Pair<ProdString, K2Vector<AATActionHexID*> > >fAddOnPairs;
};


#endif //CAATActionListAddOn