//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/dialogs/selectabledialogs/CDialogCreator.cpp $
//  
//  Owner: Tom Taylor
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

#include "VCWidgetHeaders.h"

#include "CDialogCreator.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "StreamUtil.h"
#include "widgetid.h"
#include "IDResourceShell.h"

// BP 04/24/01: moved to WidgetBinImpl.cpp .
// CREATE_PMINTERFACE(CDialogCreator, kCDialogCreatorImpl)
DEFINE_HELPER_METHODS(CDialogCreator)

CDialogCreator::CDialogCreator(IPMUnknown *boss) :
	HELPER_METHODS_INIT(boss)
{
}

CDialogCreator::~CDialogCreator()
{
}

IDialog* CDialogCreator::CreateDialog()
{
	return nil;
}

void CDialogCreator::GetOrderedPanelIDs(K2Vector<ClassID>& classIDs)
{
	this->GetOrderedPanelIDs( ::GetPluginID( this ), classIDs );
}

void CDialogCreator::GetOrderedPanelIDs(const PluginID pluginID, K2Vector<ClassID>& classIDs)
{
	classIDs.clear();	// make sure the list is wiped clean at the first

	RsrcID orderPanelsID = GetOrderedPanelsRsrcID();
	
	if (orderPanelsID) 
	{
		InterfacePtr<IPMStream> stream((IPMStream*) StreamUtil::CreateResourceStreamRead(RsrcSpec(pluginID, kIDListRsrcType, orderPanelsID)));
		
		if (stream != nil) 
		{
			int32 panelIDCount = stream->XferInt32(panelIDCount);
			for(int32 i = 0; i < panelIDCount; ++i)
			{
				int32 panelID = stream->XferInt32(panelID);
				classIDs.push_back(panelID);
			}
		}
#ifdef DEBUG
		else
		{
			DebugClassUtilsBuffer aClassIDName;
			
			ASSERT_FAIL( FORMAT_ARGS("CDialogCreator::GetOrderedPanelIDs - can't find IDList resource %d for class %s.",GetOrderedPanelsRsrcID(),DebugClassUtils::GetIDName( &aClassIDName, ::GetClass(this) ) ));
			// if you hit this assert, you can step into the next line to see what goes wrong. Most likely is that the resource fork that's currently open doesn't have an IDList resource with the ID specified.
			InterfacePtr<IPMStream> debugStream((IPMStream*) StreamUtil::CreateResourceStreamRead(RsrcSpec(pluginID, kIDListRsrcType, GetOrderedPanelsRsrcID(),kTrue)));
		}
#endif
		
	}
}

RsrcID CDialogCreator::GetOrderedPanelsRsrcID() const
{
	return kInvalidRsrcID;
}
