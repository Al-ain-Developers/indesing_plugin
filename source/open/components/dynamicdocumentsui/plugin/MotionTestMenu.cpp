//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/plugin/MotionTestMenu.cpp $
//
//  Owner: SusanCL
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
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Test Menu
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#ifdef DEBUG

#include "TestMenuComponent.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ISession.h"
#include "IApplication.h"
#include "IBoolData.h"
#include "IDocument.h"
#include "IWorkspace.h"
#include "IOpenFileDialog.h"
#include "IActionStateList.h"
#include "IActiveContext.h"
#include "ISelectionManager.h"
#include "IConcreteSelection.h"
#include "ILayoutTarget.h"
#include "ISaveFileDialog.h"
#include "IMotionPresetMgr.h"
#include "IMotionPresetUtils.h"
#include "ILayoutUIUtils.h"
#include "ISpreadList.h"
#include "IControlView.h"
#include "ISpreadDynamicContentMgr.h"
#include "IDynamicEventTimingMgr.h"
#include "IDynamicEventTimingFacade.h"
#include "IBehaviorData.h"
#include "ISoundActionData.h"
#include "IMovieActionData.h"
#include "IBehaviorList.h"
#include "IAppearanceList.h"
#include "IGraphicStyleDescriptor.h"

#include "SysFileList.h"
#include "FileTypeRegistry.h"
#include "FileUtility.h"
#include "StreamUtil.h"
#include "FileUtils.h"
#include "DynamicDocumentsUIID.h"
#include "GenericID.h"

#include "Trace.h"
#include "CAlert.h"
#include "IMotionTestUtils.h"
#include "IMotionPresetData.h"
#include "ErrorUtils.h"
#include "AnimationTypes.h"
#include "AttributesUtils.h"

#include "LocaleSetting.h"
#include "RsrcSpec.h"
#include "CoreResTypes.h"
#include "DynamicDocumentsUIDefs.h"
#include "StringUtils.h"
#include "CAlert.h"
#include <boost/bind.hpp> 

class MotionTestMenu : public TestMenuComponent
{
	public:
		 MotionTestMenu(IPMUnknown *boss);
		 ~MotionTestMenu();

		static PMString	fCurrentPresetName;
		
		static bool PickPresetFile(IDFile& presetFile);

		static bool GetSaveAsFile (IDFile& saveAsPresetFile, PMString& defaultFileName);
		static void GetSelectedItems (UIDList& newSelectionList);

		static void ApplyMotion(const PMString& presetName);
		static void SaveAsXML();
		static void DumpIDMotionXMLToFile();
		static void DumpSpreadDynamicContent();
		static void CheckButtonBehaviorAndTiming ();
		static void DumpSpreadDynamicTiming ();
		static void DumpSpreadUnassigned ();

		static int16 UpdateCurrentPreset (const PMString& presetName, int16 actionState);
		static UIDRef GetMotionPreset(const PMString& presetName);
		
		static MotionTestMenu *gThisInstance;		// Reference for the static methods

		class MotionTestItem : public TestItem
		{
		private:
			PMString fCaseName;
		public:
			MotionTestItem (const PMString& suiteName, const PMString& fullCaseName, const PMString& caseName, TestFuncPtr testFuncPtr, UpdateFuncPtr updateFuncPtr, int16 enable) : 
				TestItem (suiteName, fullCaseName, testFuncPtr, updateFuncPtr, enable ), fCaseName (caseName)
			{
			}

			virtual void RunTestFunction ( IActiveContext* ac ) 
			{
				MotionTestMenu::ApplyMotion (fCaseName);
			}

			virtual int16 GetUpdatedActionState( int16 actionState, IActiveContext* ac ) 
			{
				return MotionTestMenu::UpdateCurrentPreset (fCaseName, actionState);
			} 
		};

};

MotionTestMenu *MotionTestMenu::gThisInstance = nil;
PMString MotionTestMenu::fCurrentPresetName = PMString (); 


CREATE_PERSIST_PMINTERFACE( MotionTestMenu, kMotionTestMenuImpl)


MotionTestMenu::MotionTestMenu(IPMUnknown *boss) :
	TestMenuComponent(boss)
{
	bool16	kNotObsolete = kFalse;

	//AddTestMenu("Motion","Apply a motion to selected page item...", MotionTestMenu::ApplyMotion, kAlwaysEnabled, kNotObsolete);
	PMString presetSubmenu ("Apply Preset:");

	InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
	int32 nPresets = iPresetMgr->GetNumPresets ();
	if (nPresets == 0)
	{
		ASSERT_FAIL ("App motion preset manager not initialized yet.");
        InterfacePtr<ICommand>	iLoadCmd (CmdUtils::CreateCommand(kLoadMotionPresetFilesCmdBoss)); 
        CmdUtils::ProcessCommand (iLoadCmd);
		ASSERT (ErrorUtils::PMGetGlobalErrorCode () == kSuccess);
		nPresets = iPresetMgr->GetNumPresets ();
	}

	for (int32 n = 0; n < nPresets; n++)
	{
		PMString presetName;
		iPresetMgr->GetNthPresetName (n, presetName);
		
		PMString subMenuItem = presetSubmenu;
		subMenuItem.Append (presetName);
		subMenuItem.SetTranslatable (kFalse);

		MotionTestItem*	pTestItem = new MotionTestItem ("Motion", subMenuItem, presetName, nil, nil, kTrue);
		AddTestMenu (pTestItem);
	}

	AddTestMenu("Motion","Save motion preset as preset xml...", MotionTestMenu::SaveAsXML, kAlwaysEnabled, kNotObsolete);
	AddTestMenu("Motion","Dump ID Motion XML...", MotionTestMenu::DumpIDMotionXMLToFile, kAlwaysEnabled, kNotObsolete);
	AddTestMenu("Motion","Dump Spread Dynamic Content Info...", MotionTestMenu::DumpSpreadDynamicContent, kAlwaysEnabled, kNotObsolete);
	AddTestMenu("Motion","Check button behavior and Timing...", MotionTestMenu::CheckButtonBehaviorAndTiming, kAlwaysEnabled, kNotObsolete);
	AddTestMenu("Motion","Dump Spread Dynamic Timing...", MotionTestMenu::DumpSpreadDynamicTiming, kAlwaysEnabled, kNotObsolete);
	AddTestMenu("Motion","Dump Spread Unassiged...", MotionTestMenu::DumpSpreadUnassigned, kAlwaysEnabled, kNotObsolete);
	
	MotionTestMenu::gThisInstance = this;
}

MotionTestMenu::~MotionTestMenu()
{
	MotionTestMenu::gThisInstance = nil;
}

void MotionTestMenu::SaveAsXML()
{
	UIDList newSelectionList;
	GetSelectedItems (newSelectionList);
	if (newSelectionList.Length () == 1)
	{
		bool	success = false;
		PMString result;
		Utils<IMotionTestUtils>	iTestUtils;
		if (iTestUtils)
		{
			success = iTestUtils->PeekPresetAsXML (newSelectionList.GetRef (0), result);
		}

		//	Bring up a dialog to show the resulting strings?
		if (success && result.CharCount () > 0)
		{
			PMString defaultFileName("MotionTest.xml"); 
			IDFile saveAsPresetFile;
			if (GetSaveAsFile (saveAsPresetFile, defaultFileName))
			{
				InterfacePtr<IPMStream>	outStream (StreamUtil::CreateFileStreamWrite (saveAsPresetFile));
				if (outStream)
				{
					std::string	resultString = result.GetPlatformString ();
					outStream->XferByte((uchar*)resultString.c_str (), static_cast<int32> (resultString.size ()));
				}
			}
		}
	}
}


int16 MotionTestMenu::UpdateCurrentPreset (const PMString& presetName, int16 actionState)
{
	if (presetName == fCurrentPresetName)
	{
		return kEnabledAction | kSelectedAction;
	}
	else
	{
		return kEnabledAction;
	}
}

void MotionTestMenu::ApplyMotion(const PMString& presetName)
{
	InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
	UIDRef presetRef = GetMotionPreset (presetName);
	if (presetRef != UIDRef::gNull)
	{
		Utils<IMotionTestUtils>	iTestUtils;
		if (presetRef != UIDRef::gNull && iTestUtils)
		{
			UIDList newSelectionList;
			GetSelectedItems (newSelectionList);

			PMString result;
			bool success = iTestUtils->ApplyMotionPreset (newSelectionList, presetRef, result);
		}
	}
}


void MotionTestMenu::DumpIDMotionXMLToFile()
{
	IDFile	presetFile;
	bool		success = false;
	UIDList		newSelectionList;
	GetSelectedItems (newSelectionList);

	if (newSelectionList.Length () < 1) return;

	size_t	bufSize;
	boost::shared_ptr<uint8> buffer = Utils<IMotionTestUtils> ()->PeekPresetAsIDMotionXML (newSelectionList.GetRef (0), bufSize);
	if (buffer.get () != nil && bufSize > 0)
	{
		//	Dump to file
		PMString defaultFileName ("DumpMotionTest.xml");
		IDFile dumpFile;
		if (GetSaveAsFile (dumpFile, defaultFileName))
		{
			uint8 const *pMotionDataBuffer = buffer.get () ;

			InterfacePtr<IPMStream>	outStream (StreamUtil::CreateFileStreamWrite (dumpFile));
			if (outStream)
			{
				outStream->XferByte(const_cast<uint8 *>(pMotionDataBuffer), static_cast<int32> (bufSize));
			}
		}
	}
}

static void GetBehaviorTargetList (const UIDRef& ownerRef, const EventTriggerType& trigger, std::vector<UID>& targetList)
{
	ActionEvent actEvt = kNoEvt;
	if (trigger == kOnClick) actEvt = kMouseDownEvt;
	else if (trigger == kOnRelease) actEvt = kMouseUpEvt;
	else if (trigger == kOnRollover) actEvt = kMouseEnterEvt;
	else if (trigger == kOnRolloff) actEvt = kMouseExitEvt;

	InterfacePtr<IBehaviorList> iBehaviorList (ownerRef, UseDefaultIID ());
	std::vector<UID> actsList = iBehaviorList->Get (actEvt);

	IDataBase* iDB = ownerRef.GetDataBase ();

	targetList.clear ();
	std::vector<UID>::iterator behaviorIter = actsList.begin ();
	while (behaviorIter != actsList.end ())
	{
		UID itemUID = kInvalidUID;
		InterfacePtr<IBehaviorData const> iBehavior (iDB, *behaviorIter, UseDefaultIID());
		if (iBehavior != nil)
		{
			//	TODO: Add a case for animation & mso when it is available.
			switch (iBehavior->GetAction())
			{
				case kSoundBehavior: 
				{ 
					InterfacePtr<ISoundActionData const> data (iBehavior, UseDefaultIID()); 
					if (data) 
					{
						itemUID = data->GetSound();
					}
					break;
				}
				case kMovieBehavior: 
				{ 
					InterfacePtr<IMovieActionData const> data (iBehavior, UseDefaultIID()); 
					if (data) 
					{ 
						itemUID = data->GetMovie();
					}
				}
			}
			if (itemUID != kInvalidUID)
			{
				targetList.push_back (itemUID);
			}
		}
		++behaviorIter;
	}
}

PMString static GetTargetDescriptFromTargetUID (const ISpreadDynamicContentMgr* iDynMgr, UID targetUID)
{
	UID itemUID = targetUID;
	InterfacePtr<IBehaviorData> iBehavior (::GetDataBase (iDynMgr), targetUID, UseDefaultIID ());
	if (iBehavior)
	{
		switch (iBehavior->GetAction())
		{
			case kSoundBehavior: 
            { 
				InterfacePtr<ISoundActionData const> data (iBehavior, UseDefaultIID()); 
				if (data) 
				{
					itemUID = data->GetSound();
				}
				break;
			}
			case kMovieBehavior: 
			{ 
				InterfacePtr<IMovieActionData const> data (iBehavior, UseDefaultIID()); 
				if (data) 
				{ 
					itemUID = data->GetMovie();
				}
			}
		}
	}

	PMString statusString;
	statusString.SetTranslatable (kFalse);
	int32 index = iDynMgr->FindTarget (itemUID);
	if (index >= 0)
	{
		ISpreadDynamicContentMgr::DynamicContentType targetType = iDynMgr->GetNthTargetType (index);
		
		switch (targetType)
		{
			case ISpreadDynamicContentMgr::kSoundItemType:
				statusString.Append ("Sound");
				break;
			case ISpreadDynamicContentMgr::kMovieItemType:
				statusString.Append ("Movie");
				break;
			case ISpreadDynamicContentMgr::kButtonItemType:
				statusString.Append ("Button");
				break;
			case ISpreadDynamicContentMgr::kAnimationItemType:
				statusString.Append ("Animation");
				break;
			default:
				statusString.Append ("Unexpected");
				break;
		}

		PMString targetName;
		iDynMgr->GetNthTargetName (index, targetName);
		statusString.Append ("(");
		statusString.Append (targetName);
		statusString.Append (")");
	}
	else
	{
		statusString.Append ("Unknown");
	}
	return statusString;
}

static void GetButtonTimingSyncStatus (const ISpreadDynamicContentMgr* iDynMgr, const UIDRef& buttonRef, const EventTriggerType& trigger, PMString& statusString)
{
	statusString.SetTranslatable (kFalse);

	std::vector<UID> targetList;
	GetBehaviorTargetList (buttonRef, trigger, targetList);
	uint32 numGroups = Utils<Facade::IDynamicEventTimingFacade> ()->GetNumGroupsInEvent (buttonRef, trigger);
	if (numGroups > 0)	// for now assume we just have one group of sequence.
	{
		PMString behaviorStatus;
		PMString timingStatus;
		PMString numTargets;
		numTargets.SetTranslatable (kFalse);
		numTargets.AsNumber (numGroups);
		behaviorStatus.SetTranslatable (kFalse);
		behaviorStatus.Append ("      Behavior List: Num targets = ");
		behaviorStatus.Append (numTargets);
		behaviorStatus.Append (": ");

		timingStatus.SetTranslatable (kFalse);
		timingStatus.Append ("      Timing List: Num targets = ");
		timingStatus.Append (numTargets);
		timingStatus.Append (": ");

		uint32 flatPosition = 0;
		InterfacePtr<IDynamicEventTimingMgr> iTimingMgr (buttonRef, UseDefaultIID ());
		for (int32 m = 0; m < numGroups; m++)
		{
			IDynamicEventTimingMgr::DynamicTargetList timingItemList;
			Utils<Facade::IDynamicEventTimingFacade> ()->GetNthGroupItemsInEvent (buttonRef, trigger, m, timingItemList);
			if (m != 0)
			{
				behaviorStatus.Append (" ");
				timingStatus.Append (" ");
			}
			//PMString behaviorItemStatus = GetTargetDescriptFromTargetUID (iDynMgr, targetList [m]);
			//behaviorStatus.Append (behaviorItemStatus);

			PMString timingItemStatus;
			timingItemStatus.SetTranslatable (kFalse);
			if (timingItemList.size () == 1)
			{
				//	Single item group
				//uint32 flatPosition = animation_utils::CalculateFlatPositionFromTimingList (iTimingMgr, trigger, timingItemList [0], numGroups);
				
				ASSERT (targetList [flatPosition] == timingItemList [0]->GetTargetUID ());

				PMString behaviorItemStatus = GetTargetDescriptFromTargetUID (iDynMgr, targetList [flatPosition]);
				behaviorStatus.Append (behaviorItemStatus);

				timingItemStatus = GetTargetDescriptFromTargetUID (iDynMgr, timingItemList [0]->GetTargetUID ());
				timingStatus.Append (timingItemStatus);
				++flatPosition;
			}
			else if (timingItemList.size () == 0)
			{
				timingItemStatus.Append ("kUnknown(0)");
				timingStatus.Append (timingItemStatus);
			}
			else
			{
				timingItemStatus.Append ("Linked[");
				for (IDynamicEventTimingMgr::DynamicTargetList::iterator p = timingItemList.begin (); p != timingItemList.end (); p++)
				{
					if (p != timingItemList.begin ())
					{
						behaviorStatus.Append (" ");
						timingItemStatus.Append (" ");
					}
					//	action target position should be the flatten position of the same item in group.
					ASSERT (targetList [flatPosition] == timingItemList [0]->GetTargetUID ());

					PMString behaviorItemStatus = GetTargetDescriptFromTargetUID (iDynMgr, targetList [flatPosition]);
					behaviorStatus.Append (behaviorItemStatus);

					PMString itemStatus = GetTargetDescriptFromTargetUID (iDynMgr, (*p)->GetTargetUID ());
					timingItemStatus.Append (itemStatus);

					++flatPosition;
				}
				timingItemStatus.Append ("]");
				timingStatus.Append (timingItemStatus);
			}
		}
		timingStatus.Append ("\n");
		behaviorStatus.Append ("\n");
		statusString.Append ("\n");
		statusString.Append (behaviorStatus);
		statusString.Append (timingStatus);

	}
	else if (targetList.size () == numGroups)
	{
		statusString.Append ("empty.\n");
	}
	else
	{
		statusString.Append ("mis-matched.\n");
	}
}

void MotionTestMenu::CheckButtonBehaviorAndTiming ()
{
	Utils<ILayoutUIUtils> iLayoutUIUtils;
	IDocument* iFrontDoc = iLayoutUIUtils->GetFrontDocument ();
	if (iFrontDoc == nil) return;

	InterfacePtr<ISpreadList> iSpreadList(iFrontDoc, UseDefaultIID()); 
	InterfacePtr<IControlView> iLayoutView (iLayoutUIUtils->QueryFrontView ());
	UID spreadUID = iLayoutUIUtils->GetVisibleSpreadUID (iLayoutView, iSpreadList);
	
	IDataBase* iDB = ::GetDataBase ((IPMUnknown*)iSpreadList);
	InterfacePtr<const ISpreadDynamicContentMgr> iDynContentMgr (iDB, spreadUID, UseDefaultIID ());
	if (iDynContentMgr)
	{
		uint32 numButtons = iDynContentMgr->GetNumButtons ();
		for (uint32 n = 0; n < numButtons; ++n)
		{
			UIDRef buttonRef (iDB, iDynContentMgr->GetNthButton (n));

			InterfacePtr<IBehaviorList> iBehaviorList (buttonRef, UseDefaultIID ());
			InterfacePtr<IAppearanceList> iAppearances(iBehaviorList, IID_IAPPEARANCELIST);
			InterfacePtr<IGraphicStyleDescriptor> styleDescriptor (iBehaviorList, UseDefaultIID());
			PMString buttonName = AttributesUtils::GetStringValue(styleDescriptor, kFormNameAttrBoss);
			buttonName.SetTranslatable (kFalse);
			
			PMString buttonStatus;
			buttonStatus.SetTranslatable (kFalse);
			buttonStatus.Append (buttonName);
			buttonStatus.Append (":\n");

			InterfacePtr<IDynamicEventTimingMgr> iTimingMgr (buttonRef, UseDefaultIID ());
			if (iBehaviorList)
			{
				PMString onClickStatus;
				onClickStatus.SetTranslatable (kFalse);
				onClickStatus.Append ("   On Click: ");
				GetButtonTimingSyncStatus (iDynContentMgr, buttonRef, kOnClick, onClickStatus);
				
				PMString onReleaseStatus;
				onReleaseStatus.SetTranslatable (kFalse);
				onReleaseStatus.Append ("   On Release: ");
				GetButtonTimingSyncStatus (iDynContentMgr, buttonRef, kOnRelease, onReleaseStatus);
				
				PMString onRolloverStatus;
				onRolloverStatus.SetTranslatable (kFalse);
				onRolloverStatus.Append ("   On Rollover: ");
				GetButtonTimingSyncStatus (iDynContentMgr, buttonRef, kOnRollover, onRolloverStatus);

				PMString onRolloffStatus;
				onRolloffStatus.SetTranslatable (kFalse);
				onRolloffStatus.Append ("   On Rolloff: ");
				GetButtonTimingSyncStatus (iDynContentMgr, buttonRef, kOnRolloff, onRolloffStatus);

				buttonStatus.Append (onClickStatus);
				buttonStatus.Append (onReleaseStatus);
				buttonStatus.Append (onRolloverStatus);
				buttonStatus.Append (onRolloffStatus);
			}
			CAlert::InformationAlert (buttonStatus); 
		}
	}
}

static void GetEventStatusString (EventTriggerType& trigger, PMString& statusString)
{
	statusString.SetTranslatable (kFalse);
	if (trigger == kOnPageLoad)
	{
		statusString.Append ("On Page Load:\n");
	}
	else if (trigger == kOnPageClick)
	{
		statusString.Append ("On Page Click:\n");
	}
	else
	{
		PMString illegalEvent;
		illegalEvent.SetTranslatable (kFalse);
		if (trigger == kOnClick)
		{
			illegalEvent.Append ("On Click\n");
		}
		else if (trigger == kOnRelease)
		{
			illegalEvent.Append ("On Release\n");
		}
		else if (trigger == kOnRollover)
		{
			illegalEvent.Append ("On Rollover\n");
		}
		else if (trigger == kOnRolloff)
		{
			illegalEvent.Append ("On Rolloff\n");
		}
		statusString.Append ("Unexpected event: ");
		statusString.Append (illegalEvent);
	}
}


void MotionTestMenu::DumpSpreadUnassigned ()
{
	Utils<ILayoutUIUtils> iLayoutUIUtils;
	IDocument* iFrontDoc = iLayoutUIUtils->GetFrontDocument ();
	if (iFrontDoc == nil) return;

	InterfacePtr<ISpreadList> iSpreadList(iFrontDoc, UseDefaultIID()); 
	InterfacePtr<IControlView> iLayoutView (iLayoutUIUtils->QueryFrontView ());
	UID spreadUID = iLayoutUIUtils->GetVisibleSpreadUID (iLayoutView, iSpreadList);

	PMString spreadUnassigned;
	spreadUnassigned.SetTranslatable (kFalse);
	spreadUnassigned.Append ("Spread unassigned targets: \n");

	IDataBase* iDB = ::GetDataBase ((IPMUnknown*)iSpreadList);
	InterfacePtr<const ISpreadDynamicContentMgr> iDynContentMgr (iDB, spreadUID, UseDefaultIID ());
	
	std::vector<UID> unassignedList;
	iDynContentMgr->GetUnassignedTargets (unassignedList);
	if (unassignedList.size () == 0)
	{
		spreadUnassigned.Append ("   None.");
	}
	else
	{
		std::vector<UID>::const_iterator item = unassignedList.begin ();
		while (item != unassignedList.end ())
		{
			int32 index = iDynContentMgr->FindTarget (*item);
			ASSERT (index >= 0);
			PMString nthUnassignedString;
			nthUnassignedString.SetTranslatable (kFalse);
			nthUnassignedString.Append ("   ");

			PMString name;
			iDynContentMgr->GetNthTargetName (index, name);
			nthUnassignedString.Append (name);
			nthUnassignedString.Append ("\n");
			spreadUnassigned.Append (nthUnassignedString);
			++item;
		}
	}

	CAlert::InformationAlert (spreadUnassigned);
}

void MotionTestMenu::DumpSpreadDynamicTiming ()
{
	Utils<ILayoutUIUtils> iLayoutUIUtils;
	IDocument* iFrontDoc = iLayoutUIUtils->GetFrontDocument ();
	if (iFrontDoc == nil) return;

	InterfacePtr<ISpreadList> iSpreadList(iFrontDoc, UseDefaultIID()); 
	InterfacePtr<IControlView> iLayoutView (iLayoutUIUtils->QueryFrontView ());
	UID spreadUID = iLayoutUIUtils->GetVisibleSpreadUID (iLayoutView, iSpreadList);
	
	PMString spreadTimingStatus;
	spreadTimingStatus.SetTranslatable (kFalse);

	IDataBase* iDB = ::GetDataBase ((IPMUnknown*)iSpreadList);
	InterfacePtr<IDynamicEventTimingMgr> iTimingMgr (iDB, spreadUID, UseDefaultIID ());
	InterfacePtr<const ISpreadDynamicContentMgr> iDynContentMgr (iDB, spreadUID, UseDefaultIID ());
	int32 numEvents = iTimingMgr->GetNumDynamicEvents ();
	for (uint32 n = 0; n < numEvents; n++)
	{
		PMString eventStatusString;
		eventStatusString.SetTranslatable (kFalse);

		EventTriggerType trigger = iTimingMgr->GetNthDynamicEvent (n);
		GetEventStatusString (trigger, eventStatusString);
		spreadTimingStatus.Append (eventStatusString);

		int32 numGroups = iTimingMgr->GetNumGroups (trigger);
		for (uint32 m = 0; m < numGroups; m++)
		{
			PMString groupString;
			groupString.SetTranslatable (kFalse);
			if (m==0)
			{
				groupString.Append ("   ");
			}

			PMReal groupDelay = 0.0;
			//std::vector<UID> targetList;
			IDynamicEventTimingMgr::DynamicTargetList targetList;
			iTimingMgr->GetNthGroupItems (trigger, m, targetList);
			//iTimingMgr->GetNthGroupDelay(trigger, m, groupDelay);

			//PMString groupDelayString;
			//groupDelayString.SetTranslatable (kFalse);
			//groupDelayString.AppendNumber (groupDelay, 2);
			groupString.Append ("[");
			//groupString.Append (groupDelayString);
			//groupString.Append (", ");

			PMReal targetDelay = 0.0;
			PMString targetStatus;
			targetStatus.SetTranslatable (kFalse);
			if (targetList.size () == 1)
			{
				targetStatus = GetTargetDescriptFromTargetUID (iDynContentMgr, targetList [0]->GetTargetUID ());
				groupString.Append (targetStatus);
				groupString.Append ("(");
				iTimingMgr->GetTargetDelayInNthGroup(trigger, targetList [0], m, targetDelay);
				groupString.AppendNumber (targetDelay, 2);
				groupString.Append (")");
			}
			else if (targetList.size () == 0)
			{
				targetStatus.Append ("kUnknown(0)");
				groupString.Append (targetStatus);
			}
			else
			{
				targetStatus.Append ("Linked[");
				for (IDynamicEventTimingMgr::DynamicTargetList::iterator p = targetList.begin (); p != targetList.end (); p++)
				{
					if (p != targetList.begin ())
					{
						targetStatus.Append (" ");
					}

					PMString itemStatus = GetTargetDescriptFromTargetUID (iDynContentMgr, (*p)->GetTargetUID ());
					targetStatus.Append (itemStatus);
					targetStatus.Append ("(");
					iTimingMgr->GetTargetDelayInNthGroup(trigger, *p, m, targetDelay);
					targetStatus.AppendNumber (targetDelay, 2);
					targetStatus.Append (")");
				}
				targetStatus.Append ("]");
				groupString.Append (targetStatus);
			}
			groupString.Append ("]  ");
			spreadTimingStatus.Append (groupString);
		}
		spreadTimingStatus.Append ("\n");
	}
	if (spreadTimingStatus.empty ())
	{
		spreadTimingStatus.Append ("Not event-based timing list on the spread.");
	}
	CAlert::InformationAlert (spreadTimingStatus); 
}

void MotionTestMenu::DumpSpreadDynamicContent ()
{
	Utils<ILayoutUIUtils> iLayoutUIUtils;
	IDocument* iFrontDoc = iLayoutUIUtils->GetFrontDocument ();
	if (iFrontDoc == nil) return;

	InterfacePtr<ISpreadList> iSpreadList(iFrontDoc, UseDefaultIID()); 
	InterfacePtr<IControlView> iLayoutView (iLayoutUIUtils->QueryFrontView ());
	UID spreadUID = iLayoutUIUtils->GetVisibleSpreadUID (iLayoutView, iSpreadList);
	
	IDataBase* iDB = ::GetDataBase ((IPMUnknown*)iSpreadList);
	InterfacePtr<const ISpreadDynamicContentMgr> iDynContentMgr (iDB, spreadUID, UseDefaultIID ());
	if (iDynContentMgr)
	{
		uint32 numTargets = iDynContentMgr->GetNumTargets ();
		
		std::vector<UID> animationList;
		std::vector<UID> soundList;
		std::vector<UID> movieList;
		std::vector<UID> msoList;
		iDynContentMgr->GetItemsByTargetType (ISpreadDynamicContentMgr::kAnimationItemType, animationList);
		iDynContentMgr->GetItemsByTargetType (ISpreadDynamicContentMgr::kSoundItemType, soundList);
		iDynContentMgr->GetItemsByTargetType (ISpreadDynamicContentMgr::kMovieItemType, movieList);
		iDynContentMgr->GetItemsByTargetType (ISpreadDynamicContentMgr::kMultiStateItemType, msoList);

		uint32 numCalTargets = static_cast<uint32> (animationList.size () + soundList.size () + movieList.size () + msoList.size ());
		
		PMString result1;
		result1.SetTranslatable (kFalse);
		result1.Append ("Total number of targets = ^1.\n");
		
		PMString result2;
		result2.SetTranslatable (kFalse);
		result2.Append ("    Number of animations = ^1, number of sounds = ^2, number of movies = ^3, number of mso = ^4.\n");
		
		PMString number, num1, num2, num3, num4;
		number.AsNumber (numTargets);
		ReplaceStringParameters( &result1, number); 
		
		num1.AsNumber (static_cast<int32>(animationList.size ()));
		num2.AsNumber (static_cast<int32>(soundList.size ()));
		num3.AsNumber (static_cast<int32>(movieList.size ()));
		num4.AsNumber (static_cast<int32>(msoList.size ()));
		ReplaceStringParameters( &result2, num1, num2, num3, num4 ); 

		uint32 numButtons = iDynContentMgr->GetNumButtons ();
		PMString result3;
		result3.SetTranslatable (kFalse);
		result3.Append ("    Number of buttons = ^1. \n");
		number.AsNumber (numButtons);
		result3.SetTranslatable (kFalse);
		ReplaceStringParameters( &result3, number); 

		result1.Append (result2);
		result1.Append (result3);
		result1.SetTranslatable (kFalse);
		CAlert::InformationAlert (result1);
	}
}


void MotionTestMenu::GetSelectedItems (UIDList& newSelectionList)
{
	IActiveContext*			iActiveContext = GetExecutionContextSession()->GetActiveContext (); 
	ISelectionManager*		iSelectionManager = iActiveContext->GetContextSelection(); 

	newSelectionList.Clear ();
	if (iSelectionManager != nil) 
	{ 
		InterfacePtr<IPMUnknown>	iLayoutSelectionBoss (iSelectionManager->QueryConcreteSelectionBoss (kNewLayoutSelectionBoss));
		if (iLayoutSelectionBoss != nil)
		{
			InterfacePtr<ILayoutTarget>	iNewSelectionTarget (iLayoutSelectionBoss, UseDefaultIID ()); 
			newSelectionList = iNewSelectionTarget->GetUIDList (kStripStandoffs); 
		}
	}
}
UIDRef MotionTestMenu::GetMotionPreset(const PMString& presetName)
{
	UIDRef presetRef;
	InterfacePtr<IMotionPresetMgr>	iPresetMgr (Utils<IMotionPresetUtils> ()->QueryMotionPresetManager ());
	int32 presetIndex = iPresetMgr->FindPreset (presetName);
	if (presetIndex >= 0)
	{
		PMString	testName;
		iPresetMgr->GetNthPresetName (presetIndex, testName);
		ASSERT (testName == presetName);

		fCurrentPresetName = presetName;
		presetRef = UIDRef (::GetDataBase (iPresetMgr), iPresetMgr->GetNthPresetUID (presetIndex));
	}
	return presetRef;
}


bool MotionTestMenu::PickPresetFile (IDFile& presetFile)
{
	InterfacePtr<IOpenFileDialog> openDlg((IOpenFileDialog*)::CreateObject(kOpenDocDialogBoss, IID_IOPENFILEDIALOG));
	// Add PC file extensions
	PMString allFiles("All Readable Files");
	allFiles.Translate();

	FileTypeRegistry::FileExtensionList extList;
	FileTypeRegistry::GetAllFileExtension(kXMLFileTypeInfoID, extList, kTrue);

	FileTypeRegistry::FileExtensionList::iterator eItr = extList.begin();
	while (eItr != extList.end())
	{
		openDlg->AddExtension(&allFiles, eItr);
		++eItr;
	}
			
	SysFileList k2Files;
	bool16	okToImport = openDlg->DoDialog (nil, k2Files, kFalse);
	if (okToImport)
	{
		// check if document is opened, otherwise open the document with no window
		FileUtility FileUtil(*(k2Files.GetNthFile(0)));
		presetFile = FileUtil.GetSysFile();		
	}

	return okToImport;
}

bool MotionTestMenu::GetSaveAsFile (IDFile& saveAsPresetFile, PMString& defaultFileName)
{
    InterfacePtr<ISaveFileDialog>	iSaveDlg (::CreateObject2<ISaveFileDialog>(kSaveFileDialogBoss, IID_ISAVEFILEDIALOG)); 

    PMString exten("xml"); 
    iSaveDlg->AddFileTypeInfo(exten, exten); 
     
#ifdef WINDOWS 
    iSaveDlg->SetAdditionalFOSFlags(FOS_OVERWRITEPROMPT | FOS_NOREADONLYRETURN); 
#endif 

    // Set the default name to use. 
    IDFile defaultFile; 
    defaultFileName.SetTranslatable (kFalse); 
    defaultFile.SetFileName(defaultFileName); 
     
    PMString dialogTitle = "kMotionTestSaveDlgTitle"; 
    dialogTitle.Translate(); 

    int32* pSelectedIndex = nil; 
    bool16 useSystemDefaultDir = kFalse; 
    bool16 showTypeMenu = kTrue; 

    // Show the dialog. 
    return iSaveDlg->DoDialog (&defaultFile, &saveAsPresetFile, pSelectedIndex, useSystemDefaultDir, showTypeMenu, &dialogTitle); 
}

#endif
