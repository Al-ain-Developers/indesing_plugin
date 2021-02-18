//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/strokeweightmutator/StrMutDiagnosticHelper.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface include:
#include "ISubject.h"
#include "IGraphicAttributeSuite.h"
#include "ISelectionMessages.h"
#include "IGraphicAttrMessage.h"

// General includes:
#include "K2Assert.h"
#include "Trace.h"
#include "DebugClassUtils.h"

// Project includes:
#include "StrMutID.h"
#include "StrMutDiagnosticHelper.h"

/*
*/
void StrMutDiagnosticHelper::DumpSelectionMessage(const ISelectionMessage* selectionMessage) const
{
#ifdef DEBUG
	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpSelectionMessage()--In\n");
	do
	{
		if (selectionMessage == nil)
		{
			TRACEFLOW(kStrMutPluginName, " selectionMessage is NIL\n");
			break;
		}

		const SuiteBroadcastData* suiteBroadcastData = const_cast<ISelectionMessage*>(selectionMessage)->GetSuiteBroadcastDataList();
		if (suiteBroadcastData == nil)
		{
			TRACEFLOW(kStrMutPluginName, " suiteBroadcastData is NIL\n");
			break;
		}

		SuiteBroadcastData::const_iterator iter;
		for (iter = suiteBroadcastData->begin(); iter < suiteBroadcastData->end(); iter++)
		{
			PMIID messageType = iter->Key();

			DebugClassUtilsBuffer messageTypeName = "";
			DebugClassUtils::GetIDName(&messageTypeName, messageType);
			TRACEFLOW(kStrMutPluginName," messageTypeName=%s\n",
				messageTypeName);

			if (messageType == IGraphicAttributeSuite::kDefaultIID) 
			{
				IGraphicAttrMessage* graphicAttrMessage = static_cast<IGraphicAttrMessage*>
					(selectionMessage->GetSuiteBroadcastData(IGraphicAttributeSuite::kDefaultIID));
				this->DumpGraphicAttrMessage(graphicAttrMessage);
			}
		}
	} while(false);

	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpSelectionMessage()--Out\n");
#endif //DEBUG
}


/*
*/
void	StrMutDiagnosticHelper::DumpGraphicAttrMessage(const IGraphicAttrMessage* graphicAttrMessage) const
{
#ifdef DEBUG
	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpGraphicAttrMessage()--In\n");
	do
	{
		if (graphicAttrMessage == nil)
		{
			TRACEFLOW(kStrMutPluginName, " graphicAttrMessage is NIL\n");
			break;
		}

		IGraphicAttrMessage::MessageType messageType = graphicAttrMessage->GetMessageType();
		int32 classIDCount = graphicAttrMessage->GetClassIDCount();
		TRACEFLOW(kStrMutPluginName," messageType=%d, classIDCount=%d\n",
			messageType,
			classIDCount);
		for (int32 i = 0; i < classIDCount; i++)
		{
			ClassID classID = graphicAttrMessage->GetClassID(i);
			DebugClassUtilsBuffer classIDName = "";
			DebugClassUtils::GetIDName(&classIDName, classID);
			TRACEFLOW(kStrMutPluginName," %d, classIDName=%s\n",
				i,
				classIDName);
		}
	} while(false);
	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpGraphicAttrMessage()--Out\n");
#endif
}

/*
*/
void StrMutDiagnosticHelper::DumpUpdate(const ClassID& theChange, ISubject* theSubject, const PMIID& protocol, void* changedBy )
{
#ifdef DEBUG
	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpUpdate()-->In\n");
	// Dump some diagnostic trace about the update.
	DebugClassUtilsBuffer theChangeName = "";
	DebugClassUtils::GetIDName(&theChangeName, theChange);
	DebugClassUtilsBuffer protocolName = "";
	DebugClassUtils::GetIDName(&protocolName, protocol);
	TRACEFLOW(kStrMutPluginName," theChangeName=%s, protocolName=%s\n",
		theChangeName,
		protocolName);
	TRACEFLOW(kStrMutPluginName, "StrMutDiagnosticHelper::DumpUpdate()-->Out\n");
#endif // DEBUG
}


// End, StrMutDiagnosticHelper.cpp.

