//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpCreateCustomAnimation.cpp $
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
//  Copyright 1997-2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IBehaviorEventData.h"
#include "ICmdCollection.h"
#include "ICommandFactory.h"
#include "IComposeScanner.h"
#include "ICreateFormFieldCmdData.h"
#include "IDocument.h"
#include "IDynamicDocumentsExportCommandData.h"
#include "IDataBase.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IPageList.h"
#include "ISpreadList.h"
#include "ISwatchList.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "IAppearanceItemFacade.h"
#include "ILayerUtils.h"
#include "IControlView.h"
#include "IMultiStateObjectBehaviorData.h"
#include "IMotionPresetMgr.h"
#include "IMotionPresetUtils.h"
#include "ILayoutControlData.h"
#include "IAnimationUtils.h"
#include "IMotionFacade.h"
#include "IMotionPresetData.h"
#include "IStringListBoxControlData.h"

// General includes:
#include "DynamicDocumentsID.h"
#include "FileTypeRegistry.h"
#include "FileUtils.h"
#include "PMRect.h"
#include "SDKFileHelper.h"
#include "SDKLayoutHelper.h"
#include "SnipRunLog.h"
#include "StreamUtil.h"
#include "TextRange.h"
#include "UIDList.h"
#include "Utils.h"
#include "BehaviorTypes.h"
#include "DynamicDocumentsUIID.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnpGraphicHelper.h"
#include "SnpTextAttrHelper.h"
#include "SnpTextModelHelper.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Shows how to Create a Multi-State object and how to transition between states.

  	@ingroup sdk_snippet

 */
class SnpCreateCustomAnimation
{
	public:
		/** Builds a Multi-State object on a new document and adds buttons to transition between states.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode CreateCustomAnimation(ISnpRunnableContext* runnableContext);

	private:
		ErrorCode ExportMotionPreset();
		ErrorCode ImportMotionPreset();
		ErrorCode ChooseExportLocation(IDFile& chosenFile, PMString & fileName);
		ErrorCode ChooseFileToImport(IDFile& chosenFile);

		
		SDKLayoutHelper fLayoutHelper;
		SnpTextModelHelper	fTextCmdHelper;
		IBehaviorData* QuerySelectedBehaviorData(int32 actionType) const; 
};


ErrorCode SnpCreateCustomAnimation::ChooseFileToImport(IDFile& chosenFile)
{
	PMString title = "Choose Motion Preset XML file";
	title.SetTranslatable(kFalse); 	
		
	//Set the file chooser to select xml files.
	SDKFileOpenChooser fileChooser;
	fileChooser.AddFilter(kXMLFileTypeInfoID, "TEXT XML files(xml)"); 
    fileChooser.AddAllFiles();
	fileChooser.SetTitle(title);

	//Select file to import 
	fileChooser.ShowDialog();
	if (!fileChooser.IsChosen()) 
		return kCancel;

	// Return the chosen file to the caller.
	chosenFile = fileChooser.GetIDFile();

	return kSuccess;
}


ErrorCode SnpCreateCustomAnimation::ChooseExportLocation(IDFile& chosenFile, PMString & fileName)
{
	//Prepare fileName PMString
	fileName.Append(".xml");
	fileName.SetTranslatable(kFalse);

	//Prepare file chooser
	SDKFileSaveChooser fileChooser;
	fileChooser.AddFilter(kXMLFileTypeInfoID, "TEXT XML files(xml)");
	fileChooser.SetFilename(fileName);

	//Prompt to export to file
	fileChooser.ShowDialog();
	if (!fileChooser.IsChosen()) 
		return kCancel;

	// Return the chosen file to the caller.
	chosenFile = fileChooser.GetIDFile();

	return kSuccess;
}


ErrorCode SnpCreateCustomAnimation::ExportMotionPreset()
{
	ErrorCode result;

	//Get installed motion preset names
	K2Vector<PMString> motionPresetNames;
	InterfacePtr<IMotionPresetMgr> iPresetMgr (Utils<IMotionPresetUtils>()->QueryMotionPresetManager (nil)); 
	int32 presetCount = iPresetMgr->GetNumPresets();
	for (int32 i = 0; i < presetCount; i++)
	{
		PMString presetName;
		iPresetMgr->GetNthPresetName(i, presetName);
		motionPresetNames.push_back(presetName);
	}

	//Prompt for motion preset choice
	Utils<ISnipRunParameterUtils> parameterUtils;
	int32 choice = parameterUtils->GetChoice(PMString("Export Motion Preset to XML File"), motionPresetNames);
	if (parameterUtils->WasDialogCancelled()) {
		return kCancel;
	}
	SNIPLOG("Chosen motion preset: %s", motionPresetNames.at(choice).GetPlatformString().c_str());
	
	//Create output file for preset
	IDFile file;
	result = ChooseExportLocation(file, motionPresetNames.at(choice));
	if( result != kSuccess )
		return result;

	//Get a UIDRef for the Preset
    UID presetUID = iPresetMgr->GetNthPresetUID (choice); 
    UIDRef presetRef = UIDRef (::GetDataBase (iPresetMgr), presetUID);
	
	//Save Preset to File
	Utils<Facade::IMotionFacade > iMotionFacade;
	result = iMotionFacade->SavePresetToFile(presetRef, file);
	if( result != kSuccess )
		return result;

	return kSuccess;	
}


ErrorCode SnpCreateCustomAnimation::ImportMotionPreset()
{
	ErrorCode result;

	//Select preset xml file.
	IDFile file;
	result = ChooseFileToImport(file);
	if( result != kSuccess )
		return result;

	//Import preset xml File
	//Note: When viewed in InDesign, this will not have a animation associated with it in the Animation Panel.
	//		To associate an animation, a SWF file with the name of the imported XML file must be placed in the
	//		InDesign presets folder.  
	//		The name of the preset in the Animations Panel will be the name of the XML file imported.
	std::vector<IDFile> files; 
    files.push_back(file); 
	UID newPresetUID = kInvalidUID;	
	result = Utils<Facade::IMotionFacade>()->LoadPresetFromFile(files, newPresetUID, false); 
	if (result != kSuccess) 
		return result;

	return kSuccess;	
}


/*
*/
ErrorCode SnpCreateCustomAnimation::CreateCustomAnimation(ISnpRunnableContext* runnableContext)
{
	//Prompt for import or export
	Utils<ISnipRunParameterUtils> parameterUtils;
	K2Vector<PMString> choices;
	choices.push_back(PMString("Import Motion Preset"));
	choices.push_back(PMString("Export Motion Preset"));
	enum {kImport, kExport};
	int32 choice = parameterUtils->GetChoice(PMString("Custom Motion Preset Options"), choices);
	if (parameterUtils->WasDialogCancelled()) 
		return kCancel;

	SNIPLOG("Chosen Motion Preset Option: %s", choices.at(choice).GetPlatformString().c_str());
	
	switch (choice) 
	{
	default:
	case kImport:
		{
			return ImportMotionPreset();
		}
	case kExport:
		{
			return ExportMotionPreset();
		}
	}

	return kFailure;	
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpExportDynamicDocument available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerCreateCustomAnimation : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerCreateCustomAnimation();

		/** Destructor.
		 */
		virtual			~_SnpRunnerCreateCustomAnimation();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);

		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}

};

/* Describe your snippet to the framework here.
*/
_SnpRunnerCreateCustomAnimation::_SnpRunnerCreateCustomAnimation() : SnpRunnable("CreateCustomAnimation")
{
	this->SetDescription("Create Custom Animation");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerCreateCustomAnimation::~_SnpRunnerCreateCustomAnimation()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerCreateCustomAnimation::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		// TODO: query runnableContext for the selection target 
		// e.g. ILayoutTarget or ITextTarget. Or call
		// runnableContext to get the IActiveContext.
		// See ISnpRunnableContext for documentation.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerCreateCustomAnimation::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		// TODO:
		// Use runnableContext to discover the selection target or IActiveContext if you need a context.

		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		// Utils<ISnipRunParameterUtils> parameterUtils;

		// Perform your operation.
		SnpCreateCustomAnimation instance;
		status = instance.CreateCustomAnimation(runnableContext);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerCreateCustomAnimation instance_SnpCreateCustomAnimation;
DEFINE_SNIPPET(_SnpRunnerCreateCustomAnimation) 	

// End, SnpExportDynamicDocument.cpp
