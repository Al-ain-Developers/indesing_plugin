//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DialogUtils.tpp $
//  
//  Owner: rkamicar
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

#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"

#include "IStringListControlData.h"
#include "IDropDownListController.h"
#include "IPanelControlData.h"

#include "InstStrokeFillID.h"


template <class I>
int32 IDialogUtils::ServiceDropDownFiller(IPanelControlData*, IStringListControlData* offsetData, ServiceID sid, ClassID cid)
{
	offsetData->Clear(kDontInvalidate, kDontNotify);

	InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());

	int32 which = IStringListControlData::kInvalidStringIndex;
	bool16 findClassID = (cid != kInvalidClass);
	bool16 shouldSort = sid == kTextVariableServiceID ? kTrue : kFalse;	// should be on the interface eventually

	PMString thisName;

	int32 nServices = serviceRegistry->GetServiceProviderCount(sid);
	for (int32 iService=0 ; iService < nServices ; iService++)
	{
		// Add the string to the drop-down
		InterfacePtr<IK2ServiceProvider> serviceProvider(serviceRegistry->QueryNthServiceProvider(sid, iService));
		InterfacePtr<I> service(serviceProvider, UseDefaultIID());

		if (service->IncludeStyleChoiceInUI())
		{
			thisName.Clear();
			service->GetStyleName(thisName);
			ClassID thisID = serviceRegistry->GetNthServiceProviderID(sid, iService);

			int32 offsetLength = offsetData->Length();
			int32 offset = offsetLength + 1;			
			bool16 shouldAdd = kTrue;
			if (shouldSort)
			{
				for (int32 i=0 ; i < offsetLength ; i++)
				{
					PMString thatName = offsetData->GetString(i);
					if (thisName.Compare(kFalse, thatName) < 0)
					{
						shouldAdd = kFalse;
						offsetData->AddString(thatName, IStringListControlData::kEnd, kDontInvalidate, kDontNotify);// just making room - actual string doesn't matter
						offsetLength = offsetData->Length();			
						for (int32 j=offsetLength-1 ; j > i ; j--)	// N2 but N is small
						{
							PMString otherName = offsetData->GetString(j-1);
							offsetData->SetString(j, otherName);
						}
						offsetData->SetString(i, thisName, kDontInvalidate, kDontNotify);
						offset = i;
						break;
					}
				}
			}
			if (shouldAdd)
				offsetData->AddString(thisName, IStringListControlData::kEnd, kDontInvalidate, kDontNotify);
		}
	}

	if (findClassID)
	{
		for (int32 i=0 ; i < nServices ; i++)
		{
			InterfacePtr<IK2ServiceProvider> serviceProvider(serviceRegistry->QueryNthServiceProvider(sid, i));
			InterfacePtr<I> service(serviceProvider, UseDefaultIID());

			if (service->IncludeStyleChoiceInUI())
			{
				thisName.Clear();
				ClassID thisID = serviceRegistry->GetNthServiceProviderID(sid, i);
				if (thisID == cid)
				{
					service->GetStyleName(thisName);
					for (int32 j=0 ; j < offsetData->Length() ; j++)
					{
						if (offsetData->GetString(j) == thisName)
						{
							which = j;
							break;
						}
					}
				}
			}
			if (which != IStringListControlData::kInvalidStringIndex)
				break;
		}
	}

	// Couldn't or didn't find the cid - check for default..
	if (!findClassID || which == IStringListControlData::kInvalidStringIndex)
	{
		ClassID defaultCid = serviceRegistry->GetDefaultServiceProviderID(sid);
		if (defaultCid != kInvalidClass)
		{
			int32 defaultWhich = serviceRegistry->GetServiceProviderIndex(sid, cid);
			if (defaultWhich != -1)
				which = defaultWhich;
		}
	}

	return which;
}

template<class I>
ClassID IDialogUtils::Index2ServiceStyle(const IStringListControlData* offsetData, int32 which, ServiceID sid)
{
	PMString selected = offsetData->GetString(which);

	TRACEFLOW("Variables", "IDialogUtils::Index2ServiceStyle<I>: Looking for '%s'..\n", selected.GetUTF8String().c_str());

	InterfacePtr<IK2ServiceRegistry> serviceRegistry(GetExecutionContextSession(), UseDefaultIID());

	PMString thisName;
	int32 nServices = serviceRegistry->GetServiceProviderCount(sid);
	ASSERT(nServices > 0);

	for (int32 i = nServices - 1; i >= 0; --i)
	{
		InterfacePtr<IK2ServiceProvider> serviceProvider(serviceRegistry->QueryNthServiceProvider(sid, i));
		InterfacePtr<I> service(serviceProvider, UseDefaultIID());

		thisName.Clear();
		service->GetStyleName(thisName);

		TRACEFLOW("Variables", "\t\t vs. '%s'\n", thisName.GetUTF8String().c_str());
		if (thisName == selected)
		{
			ClassID thisID = serviceRegistry->GetNthServiceProviderID(sid, i);
			return thisID;
		}
	}

	return kInvalidClass;
}

