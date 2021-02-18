//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateDisplayPerformance.cpp $
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

// Interface includes:
#include "IPathGeometry.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "IImageDataAccess.h"
#include "IBoolData.h"
#include "ISelectionUtils.h"
#include "ISetDrawOptionsCmdData.h"
#include "ILayoutControlData.h"
#include "ILayoutUIUtils.h"
#include "IDrawOptionsSetID.h"
#include "IDrawOptions.h"
#include "ISetDrawOptionOverrideCmdData.h"

#include "PreferenceUtils.h"
#include "InstStrokeFillID.h"

// General includes:
#include "UIDList.h"
#include "Utils.h"
#include "LocaleSetting.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpGraphicHelper.h"

/**	
    This code snippet provide samples for setting up display performance of
	application group definitions,display performance settings of layout default 
	and page item overrides.

  	@ingroup sdk_snippet
  	@ingroup sdk_graphic
	

*/
class SnpManipulateDisplayPerformance
{

	public:
	
		/** Constructor.
		*/
		SnpManipulateDisplayPerformance() {}

		/** Destructor
		*/
		virtual ~SnpManipulateDisplayPerformance() {}

		/** Change display performance group for application.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ChangeDisplayPerformanceGroup();

		/** Set layout view display performance
			@param layoutData the ILayoutControlData you wish to modify
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetViewDisplayPerformance(ILayoutControlData *layoutData);

		/** Set display performance of page item overrides
			@param itemList list of page items whose display settings you wish to modify
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetPageItemDisplayPerformance(UIDList itemList);


};

ErrorCode SnpManipulateDisplayPerformance::ChangeDisplayPerformanceGroup()
{
	ErrorCode errorCode = kFailure;

	do {
		// Get group
		K2Vector<PMString> groups;
		groups.push_back(PMString("Fast (high performance) group"));
		groups.push_back(PMString("Typical group"));
		groups.push_back(PMString("High display quality group"));

		enum {kFast, kTypical, kHighQuality};
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 group  = parameterUtils->GetChoice("Choose a group to change:", groups);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get category
		K2Vector<PMString> categories;
		categories.push_back(PMString("Raster Image"));
		categories.push_back(PMString("Vector graphics"));

		enum {kRaster, kVector};
		int32 category  = parameterUtils->GetChoice("Choose a categary:", categories);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get setting
		K2Vector<PMString> settings;
		settings.push_back(PMString("Graybox"));
		settings.push_back(PMString("Proxy image"));
		settings.push_back(PMString("High resolution"));

		enum {kGraybox, kProxy, kHighResolution};
		int32 setting  = parameterUtils->GetChoice("Choose setting:", settings);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Get the option set (group)
		InterfacePtr<IDrawOptions> iDrawOptions((IDrawOptions*)::QuerySessionPreferences(IID_IDRAWOPTIONS));
		DrawOptionsSet optionsSet;
		switch (group)
		{
		case kFast:
			{
			iDrawOptions->GetSetByID(IDrawOptions::kFastGroup, &optionsSet);
			break;
			}
		case kTypical:
			{
			iDrawOptions->GetSetByID(IDrawOptions::kTypicalGroup, &optionsSet);
			break;
			}
		case kHighQuality:
			{
			iDrawOptions->GetSetByID(IDrawOptions::kHighQualityGroup, &optionsSet);
			break;
			}
		default:
			SNIPLOG("Invalid group choice");
			return kFailure;
		}

		// set up the change
		switch (category)
		{
		case kRaster:
			{
				switch (setting)
				{
				case kGraybox:
					optionsSet.raster = IDrawOptions::kRasterGrayOut;
					break;
				case kProxy:
					optionsSet.raster = IDrawOptions::kRasterProxy;
					break;
				case kHighResolution:
					optionsSet.raster = IDrawOptions::kRasterHighRes;
					break;
				}
				
				break;
			}
		case kVector:
			{
				switch (setting)
				{
				case kGraybox:
					optionsSet.vector = IDrawOptions::kVectorGrayOut ;
					break;
				case kProxy:
					optionsSet.vector = IDrawOptions::kVectorProxy;
					break;
				case kHighResolution:
					optionsSet.vector = IDrawOptions::kDisplayList;
					break;
				}
				
				break;
			}						
		}

		// Create command to change the setting
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kSetDrawOptionsCmdBoss));
		if ( cmd ) {
			InterfacePtr<ISetDrawOptionsCmdData> cmdData(cmd, IID_ISETDRAWOPTIONSCMDDATA);
			if ( cmdData ) 
			{  
				cmdData->SetSet(optionsSet, kTrue /* let it be defaults */);
				cmdData->SetIgnore(iDrawOptions->GetIgnoreOverrides()); // don't change
				errorCode = CmdUtils::ProcessCommand (cmd);
			}
		}

	} while (false);


	return errorCode;
}

ErrorCode SnpManipulateDisplayPerformance::SetViewDisplayPerformance(ILayoutControlData* layoutData)
{
	ErrorCode errorCode = kFailure;
	do {

		if ( !layoutData ) 
		{
			SNIPLOG("Changing view display performance settings requires layout view.");
			break;
		}

		// Get group
		K2Vector<PMString> groups;
		groups.push_back(PMString("Fast (high performance) group"));
		groups.push_back(PMString("Typical group"));
		groups.push_back(PMString("High display quality group"));

		enum {kFast, kTypical, kHighQuality};
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 group  = parameterUtils->GetChoice("Set front layout display to :", groups);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		InterfacePtr<IDrawOptionsSetID> iDrawOptionsSetID(layoutData, IID_IDRAWOPTIONSSETID);
		if (! iDrawOptionsSetID )
			break;

		switch (group)
		{
		case kFast:
			iDrawOptionsSetID->SetID(IDrawOptions::kFastGroup);
			break;
		case kTypical:
			{
			iDrawOptionsSetID->SetID(IDrawOptions::kTypicalGroup);
			break;
			}
		case kHighQuality:
			{
			iDrawOptionsSetID->SetID(IDrawOptions::kHighQualityGroup);
			break;
			}
		}
		
		errorCode = kSuccess;

	} while(false);

	return errorCode;
}


ErrorCode SnpManipulateDisplayPerformance::SetPageItemDisplayPerformance(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Changing page item display performance requires the item selected.");
			break;
		}

		// Get group
		K2Vector<PMString> groups;
		groups.push_back(PMString("Fast (high performance) group"));
		groups.push_back(PMString("Typical group"));
		groups.push_back(PMString("High display quality group"));

		enum {kFast, kTypical, kHighQuality};
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 group  = parameterUtils->GetChoice("Set page item display to :", groups);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		
		// Initialise this to a sensible value
		uint32 option = IDrawOptions::kTypicalGroup;
		switch (group)
		{
		case kFast:
			option = IDrawOptions::kFastGroup;
			break;
		case kTypical:
			option = IDrawOptions::kTypicalGroup;
			break;
		case kHighQuality:
			option = IDrawOptions::kHighQualityGroup;
			break;
		}

		UIDList newList(itemList.GetDataBase());
		for (int32 i = 0; i<itemList.Length(); i++)
		{  // Get graphic items
			SnpGraphicHelper graphicHelper(itemList.GetRef(i));
			InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
			if (imageAccess)
				newList.Append( ::GetUID(imageAccess));
		}

		if (newList.Length() <= 0 ) 
		{
			SNIPLOG("No item with graphics is selected.");
			return kCancel;
		}
		else
		{
			InterfacePtr<ICommand> cmd (CmdUtils::CreateCommand(kSetDrawOptionOverrideCmdBoss));
			if (cmd)
			{
				InterfacePtr<ISetDrawOptionOverrideCmdData> iCmdData(cmd, IID_ISETDRAWOPTIONOVERRIDECMDDATA);
				iCmdData->SetDisplayOption(option);
				cmd->SetItemList (newList);
				errorCode = CmdUtils::ProcessCommand(cmd);
			}
		}

	} while(false);

	return errorCode;
}


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpManipulateDisplayPerformance available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerManipulateDisplayPerformance : public SnpRunnable
{
	public:
		// For SnippetRunner framework.

		/** Constructor.
		*/
		_SnpRunnerManipulateDisplayPerformance();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateDisplayPerformance();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if a document is open, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);	

		/** Don't present this snippet in the framework's UI if the
			product we are running under is InCopy. 
			@return kFalse if the host product is InCopy, kTrue otherwise.
		*/
		bool16 CanLoad() const;
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* Constructor
*/
_SnpRunnerManipulateDisplayPerformance::_SnpRunnerManipulateDisplayPerformance() : SnpRunnable("ManipulateDisplayPerformance")
{
	this->SetDescription("Manipulate display performance settings");
	this->SetPreconditions("None");
	this->SetCategories("sdk_snippet, sdk_graphic");
}

/* Destructor
*/
_SnpRunnerManipulateDisplayPerformance::~_SnpRunnerManipulateDisplayPerformance()
{
}

/*
*/
bool16 _SnpRunnerManipulateDisplayPerformance::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* 
*/
ErrorCode _SnpRunnerManipulateDisplayPerformance::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do 
	{

		SnpManipulateDisplayPerformance instance;

		// Get parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Change settings of a display performance group"));
		choices.push_back(PMString("Change layout display performance settings"));
		choices.push_back(PMString("Set display perofrmance for a page item"));

		enum {kChangeGroupDP, kChangeLayoutDP, kChangePageItemDP};
		int32 choice  = parameterUtils->GetChoice("Choose what you want to do:", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
			
		switch (choice)
		{
		case kChangeGroupDP:
			status = instance.ChangeDisplayPerformanceGroup();
			break;
		case kChangeLayoutDP:
			{
			InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
			status = instance.SetViewDisplayPerformance(layoutData);
			}
			break;
		case kChangePageItemDP:
			// Get current selection
			InterfacePtr<ILayoutTarget> iLayoutTarget (runnableContext, UseDefaultIID ());
			if (!iLayoutTarget)
			{
				SNIPLOG("Changing page item display performance requires the item selected.");
				break;
			}
			UIDList  itemList = iLayoutTarget->GetUIDList(kStripStandoffs);
			status = instance.SetPageItemDisplayPerformance(itemList);
			break;
		}
	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerManipulateDisplayPerformance::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateDisplayPerformance instance_SnpRunnerManipulateDisplayPerformance;
DEFINE_SNIPPET(_SnpRunnerManipulateDisplayPerformance) 	
//End, SnpManipulateDisplayPerformance.cpp
