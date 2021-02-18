//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IAATActionList.h $
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
#ifndef __IAATActionList__
	#define __IAATActionList__

#include "CSequenceItem.h"

const ProdInt32 kMaxIDLen(8);

#define ADD_AAT_ACTION_TO_LIST_REG(b, a) \
if(b) \
{ \
	b->AddAATAction(AAT_FACTORY_ENTRY(a)); \
}\


class AATActionHexID
{
	public:
		typedef object_type data_type;
		
		AATActionHexID(void) {}
		AATActionHexID(const char *str) { SetChars(str); }
		virtual ~AATActionHexID() {}
		
		
		virtual void SetChars(const char *str)
		{
			ProdInt32 len(0);
			ASSERT(strlen(str) == kMaxIDLen);
			
			while(len < kMaxIDLen)
			{
				fChars[len] = str[len];
				++len;
			}	
			
			fChars[kMaxIDLen] = '\0';
		}
		virtual const char* GetChars(void) const { return fChars; }
		
		virtual void operator=(const char *str) { SetChars(str); }
		virtual ProdBool operator<(const AATActionHexID &compID) const
		{
			return std::strcmp(fChars, compID.GetChars()) < 0;
		}
		
		virtual ProdBool operator!=(const AATActionHexID &compID) { return !(*this == compID); }
		virtual ProdBool operator==(const AATActionHexID &compID) const
		{
			ProdBool match(kTrue);
			ProdInt32 len(0);
			while(len < kMaxIDLen)
			{
				if(fChars[len] != compID.fChars[len])
				{
					match = kFalse;
					break;
				}
				++len;
			}
			return match;
		}
		
	protected:
		char fChars[kMaxIDLen + 1];
};

const AATActionHexID kInvalidTestID("00000000");

class IAATFactory;
class VAATAction;

class IAATActionList : public CSequenceItem
{
	public:
		IAATActionList(IPMUnknown *boss) : CSequenceItem(boss) {}
		virtual ~IAATActionList() {}
		
		virtual ErrorCode Execute(IAATSessionProperties* properties) = 0;
		
		virtual ProdBool Init(void) = 0;
		virtual ProdBool IsInited(void) = 0;
		
		virtual ProdString GetListName(void) = 0;
		
		virtual void RegisterWithFactory(IAATFactory *factory) = 0;
		
		virtual void 	AddAATActionID(AATActionHexID id) = 0;
		virtual void 	RemoveAATActionID(AATActionHexID &id) = 0;
		virtual ProdBool	HasThisID(AATActionHexID &id) = 0;
		
		virtual ProdInt32 GetNumAATActionIDs(void) = 0;
		virtual AATActionHexID* GetNthAATActionID(ProdInt32 index) = 0;
		
		virtual ProdBool SetActiveAATAction(AATActionHexID &id) = 0;
		virtual VAATAction* GetActiveAATAction(void)  = 0;
		virtual AATActionHexID GetActiveAATActionID(void)  = 0;
		
		virtual bool16		IsGenericActionList(void) = 0;
		
		virtual void		SetActiveAATActionVersion(ProdInt32 version) = 0;
		virtual ProdInt32	GetActiveAATActionVersion(void) = 0;
		
		virtual ProdBool	ConvertParam(VAATData *oldParam, ProdInt32 version) = 0;
		virtual ProdBool	ConvertParam(const ProdString &readStr, const ProdString &tag, ProdInt32 version, VAATData **dataHndl = nil) = 0;
		virtual void	GetConvertedTags(K2Vector<ProdString> &tags) = 0;
		
	protected:
		//Override this to add in your action IDs.  This is called by the base
		//class when Init is called.  fInited is set by the return value.
		virtual	ProdBool Initialize(void) = 0;
		
		//override this method to register your actions
		virtual void RegisterAATActions(IAATFactory *factory) = 0;
};


#endif //__IAATFactory__