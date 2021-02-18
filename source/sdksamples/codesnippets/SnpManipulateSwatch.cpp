//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateSwatch.cpp $
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
#include "IWorkspace.h"
#include "ISwatchUtils.h"
#include "ISwatchList.h"
#include "IRenderingObject.h"
#include "IGraphicStateUtils.h"
#include "IGraphicStateRenderObjects.h"
#include "IColorOverrides.h"
#include "IColorSystemUtils.h"
#include "IPersistUIDData.h"
#include "IPMInkBossData.h"
#include "IInkList.h"
#include "IGraphicAttrRealNumber.h"
// General includes:
#include "SwatchLibPanelID.h"
#include "K2Vector.tpp"
#include "ErrorUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Create the gradient swatch,
	\li Create the RGB color swatch,
	\li Create the CMYK color swatch,
	\li Delete a swatch,
	\li Create color swatch by external name and setting,
	\li Iterate swatch list,
	\li Iterate ink list.
	
	This snippet creates a new gradient swatch based on swatches called "Step 1" and "Step 2" and "Step 3" (created as needed).
	When you run the snippet, specify the name of your new swatch, and choose the type of gradient.
	The new swatch will be created, and will appear in the Swatches panel.
	If a swatch by the name you specify already exists, a new one will not be created. 
	The snippet also demonstrates how to create a color swatch that matchs
	a defined setting of external swatch and iterate swatch list and ink list as well.	
	
  	@ingroup sdk_snippet
  	@ingroup sdk_graphic

	@see IWorkspace
	@see ISwatchUtils
	@see ISwatchList
	@see IRenderingObject
	@see IGraphicStateUtils
 */
class SnpManipulateSwatch 
{
	public:
		/** Data on the color step for the gradient swatch.
			It uses as a vector.
		*/
		struct SnpGradientStep
		{
			/** This allows the structure to be put into a K2Vector.
			*/
			typedef object_type data_type;

			/** The color UID for the step of gradient.
			*/
			UID		gradientColorUID;
			
			/** The position of stop for the step of gradient.
			*/
			PMReal	stopPosition;
			
			/** The middle point of the step of gradient.
			*/
			PMReal	gradientMidPoint;
		};

	public:
		/** Constructor.
		 */
		SnpManipulateSwatch();

		/** Destructor.
		 */
		virtual			~SnpManipulateSwatch() {}

	
		/** This method creates a gradient swatch and returns its UID.
			If a swatch by the given name already exists, the UID of the existing swatch will be returned.
			@param warkspace The workspace that swatch is made.
			@return gradient swatch UID.
		 */
		UID CreateGradientSwatch(IWorkspace* warkspace);

		/** Delete the specified swatch.
			@param ref2Delete Specifies UIDRef of swatch to be deleted.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode DeleteSwatch(UIDRef ref2Delete);
			
		/** swatch is looked up with a name from the swatch list.
			If it is not here, swatch of the RGB color is made.
			@param warkspace The workspace that swatch is made.
			@param colorName Color swatch name.
			@param r A red rate.
			@param g A green rate.
			@param b A blue rate
			@return color swatch UID.
		 */
		UID GetRGBColourUIDByName(IWorkspace* warkspace,
									const PMString& colorName, 
									const PMReal& r, const PMReal& g, const PMReal& b);
									
		/** swatch is looked up with a name from the swatch list.
			If it is not here, swatch of the CMYK color is made.
			@param warkspace The workspace that swatch is made.
			@param colorName Color swatch name.
			@param c A cyan rate.
			@param m A magenta rate.
			@param y A yellow rate
			@param k A black rate
			@return color swatch UID.
		 */
		UID GetCMYKColourUIDByName(IWorkspace* warkspace,
							   		const PMString& colorName, 
									const PMReal& c, const PMReal& m, const PMReal& y, const PMReal& k );									
		
	
		void SetGradientType(const GradientType& p) { this->fGradType = p; }

		void SetSwatchName(const PMString& s) { this->fSwatchName = s; }

		/** This method creates a new color swatch with the same definition
		    of PANTONE 368 C
			If a swatch is successfully created, the UID of the swatch will be returned.
			@return color swatch UID.
		 */
		UID CreateColorSwatch();
		
		/** This method iterates active swatch list, show the swatch information
		    on the snip log.
		*/
		void IterateSwatchList(IWorkspace* workspace);

		/** This method iterates ink list of active workspace, show the ink information
		    on the snip log.
		*/
		void IterateInkList(IWorkspace* workspace);

	private:
		/** The name of gradient swatch to create.
		*/
		PMString	fSwatchName;
				
		/** The type of the gradient.
			(kAxial or kRadial)
		*/
		GradientType fGradType;
	
};

SnpManipulateSwatch::SnpManipulateSwatch()
: fGradType(kAxial)
{}

/* GetRGBColourUIDByName
*/
UID SnpManipulateSwatch::GetRGBColourUIDByName(IWorkspace* workspace,
											   		const PMString& colorName, 
													const PMReal& r, const PMReal& g, const PMReal& b )
{
	UID retval = kInvalidUID;
	do{
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
		InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
		ASSERT(swatchList);
		if(!swatchList) {
			break;
		}
		UIDRef  uidRef = swatchList->FindSwatch(colorName);  
		if(uidRef.GetUID()== kInvalidUID)
		{
			retval = Utils<ISwatchUtils>()->CreateSpotRGBSwatch(workspace, colorName, r, g, b);
		}
		else
		{
			retval = uidRef.GetUID();
		}
	}while(false);
	return retval;
}

/* GetCMYKColourUIDByName
*/
UID SnpManipulateSwatch::GetCMYKColourUIDByName(IWorkspace* workspace,
											   		const PMString& colorName, 
													const PMReal& c, const PMReal& m, const PMReal& y, const PMReal& k )
{
	UID retval = kInvalidUID;
	do{
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
	
		InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
		ASSERT(swatchList);
		if(!swatchList) {
			break;
		}
	
		UIDRef  uidRef = swatchList->FindSwatch(colorName);  
		if(uidRef.GetUID()== kInvalidUID)
		{
			retval = Utils<ISwatchUtils>()->CreateSpotCMYKSwatch(workspace, colorName, c, m, y, k);
		}
		else
		{
			retval = uidRef.GetUID();
		}
	}while(false);
	return retval;
}

/* CreateGradientSwatch
*/
UID SnpManipulateSwatch::CreateGradientSwatch(IWorkspace* workspace)
{ 
	ErrorCode status = kFailure;
	UID newGradientUID = kInvalidUID;
	do
	{
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
				
		InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
		ASSERT(swatchList);
		if(!swatchList) {
			break;
		}
		// Get or create "Step 1" swatch to use as a basis.			
		UID step1UID = this->GetCMYKColourUIDByName(workspace, PMString("Step 1"), 0.2, 1.0, 0.5, 0);
		ASSERT(step1UID != kInvalidUID);
		if(step1UID == kInvalidUID) {
			break;
		}
		// Get or create "Step 2" swatch to use as a basis.			
		UID step2UID = this->GetRGBColourUIDByName(workspace, PMString("Step 2"), 0.0, 1.0, 0.5);
		ASSERT(step2UID != kInvalidUID);
		if(step2UID == kInvalidUID) {
			break;
		}
		// Get or create "Step 3" swatch to use as a basis.			
		UID step3UID = this->GetCMYKColourUIDByName(workspace, PMString("Step 3"), 0.0, 0.3, 0.9, 0.0);
		ASSERT(step3UID != kInvalidUID);
		if(step3UID == kInvalidUID) {
			break;
		}
		SNIPLOG("*Step 1 color swatch UID: 0x%X", step1UID.Get());
		SNIPLOG("*Step 2 color swatch UID: 0x%X", step2UID.Get());
		SNIPLOG("*Step 3 color swatch UID: 0x%X", step3UID.Get());

		// Set up gradients for the gradient swatch.
		K2Vector<SnpGradientStep> gradientSteps;
		
		SnpGradientStep step;
		step.gradientColorUID = step1UID;
		step.stopPosition = 0;
		step.gradientMidPoint = 0.25;
		gradientSteps.push_back(step);
		
		step.gradientColorUID = step2UID;
		step.stopPosition = 0.5;
		step.gradientMidPoint = 0.75;
		gradientSteps.push_back(step);
		
		step.gradientColorUID = step3UID;
		step.stopPosition = 1;
		step.gradientMidPoint = 0.85;
		gradientSteps.push_back(step);

		UIDRef  uidRef = swatchList->FindSwatch(fSwatchName);  
		if(uidRef.GetUID()== kInvalidUID)
		{
			// Create a temporary gradient object. We will set the gradient data below.
			InterfacePtr<IRenderingObject> gradientRenderingObject(
								Utils<IGraphicStateUtils>()->CreateTemporaryRenderObject(kGradientRenderingObjectBoss));
			ASSERT(gradientRenderingObject);
	 		if(!gradientRenderingObject) {
				break;
			}

	 		InterfacePtr<IGradientFill> gradientData(gradientRenderingObject, UseDefaultIID());
			ASSERT(gradientData);
	 		if(!gradientData) {
				break;
			}
		
			gradientRenderingObject->SetSwatchName(fSwatchName);
			gradientRenderingObject->SetVisibility(kTrue); 

			int32 num = gradientSteps.size();
			
			gradientData->SetNumberOfStop(num);		
			gradientData->SetGradientFillType(fGradType);
			
			K2Vector<SnpGradientStep>::const_iterator beginIter = gradientSteps.begin();
			K2Vector<SnpGradientStep>::const_iterator endIter = gradientSteps.end();
			K2Vector<SnpGradientStep>::const_iterator iter;
			
			int32 i = 0;
			for(iter = beginIter; iter != endIter; ++iter)
			{
				gradientData->SetNthGradientColorUID(i, iter->gradientColorUID);
				gradientData->SetNthStopPosition(i, iter->stopPosition);
				gradientData->SetNthGradientMidPoint(i, iter->gradientMidPoint);
				i++;
			}
			
			newGradientUID = Utils<ISwatchUtils>()->CreateNewSwatch(kGradientRenderingObjectBoss, gradientData, workspace, kFalse);	
		}
		else
		{
			newGradientUID = uidRef.GetUID();
		}
		
		status = kSuccess;
	
	}while(kFalse);

	return newGradientUID;
}

/* DeleteSwatch.
*/
ErrorCode SnpManipulateSwatch::DeleteSwatch(UIDRef ref2Delete)
{
	ErrorCode result = kFailure;

	// Substitute for deleted swatch.
	UID altColorUID = Utils<ISwatchUtils>()->GetNamedSwatch("Black");

	// List of swatches to delete (list of 1 here).
	UIDList list2Delete(ref2Delete);

	// Delete all swatches in list2Delete after replacing all references 
	// to these swatches with the replacement swatch (altColorUID).
	// We could use kDeleteSwatchesCmd here, but this wrapper function 
	// takes care of:
	// - dependent swatches
	// - conflicts with tint swatches
	// - reseting the graphic state of objects that use deleted swatch to
	//   the rendering object represented by replacement swatch color UID.
	result = Utils<ISwatchUtils>()->ReplaceAndDeleteSwatches(
		&list2Delete, altColorUID);

	return result;
}

UID SnpManipulateSwatch::CreateColorSwatch()
{
	UID newSwatchUID = kInvalidUID;
	do
	{
		// Get active swatch list. If there is no open document, we will get one from application workspace.
		InterfacePtr<ISwatchList> iSwatchList(Utils<ISwatchUtils> ()->QueryActiveSwatchList());
		// %%+ 0.57 0 1 0 (PANTONE 368 C)
		PMString	swatchName("PANTONE 368 C");
		swatchName.SetTranslatable (kFalse);

		//If the swatch already exists, just bail out
		//We don't want return the UID of FindSwatch result because that
		//may confuse caller method if they really created new swatch. 
		//In the production code, the created swatch is often used to apply to
		//pageitem, so you may want return UID of the found swatch.
		if(iSwatchList->FindSwatch(swatchName)) 
		{
	 		SNIPLOG("Swatch name already exists");
			break;
		}

		ColorArray colorArray;
		colorArray.push_back(0.57);
		colorArray.push_back(0);
		colorArray.push_back(1);
		colorArray.push_back(0);

		int16	colorSpace = kPMCsCalCMYK;
		IInkData::InkType	inkType = IInkData::kSpotInk;
		int32	creatorID=kPantoneCoatedNewLibCreatorID;

		InterfacePtr<IRenderingObject>	iNewRenderObject (Utils<IGraphicStateUtils> ()->CreateTemporaryRenderObject (kPMColorBoss));
		InterfacePtr<IColorData> 	iNewColorData( iNewRenderObject, UseDefaultIID () );
		InterfacePtr<IInkData> 		iNewInkData( iNewRenderObject, UseDefaultIID () );
		if (iNewColorData)
			iNewColorData->SetColorData (colorSpace, colorArray);
		if (iNewRenderObject)
		{
			iNewRenderObject->SetVisibility (kTrue);
			iNewRenderObject->SetSwatchName (swatchName);
			iNewRenderObject->SetCanDelete (kTrue);
			iNewRenderObject->SetCreatorID (creatorID);
		}
		if (iNewInkData)
			iNewInkData->SetInkType (inkType);

		Utils<ISwatchUtils>			iSwatchUtils;
		InterfacePtr<IWorkspace>	workspacePtr (iSwatchList, IID_IWORKSPACE );
		if (iSwatchUtils)
			newSwatchUID = iSwatchUtils->CreateNewSwatch (kPMColorBoss, iNewRenderObject, workspacePtr, kFalse); 
                        //  Simply adding the selected swatches to the swatches panel should not affect
                        //  the graphic state. Unless explicitly selected in the swatches panel, 
		                //  user don't need to set the last para to kTrue to update the graphics state

 	}while(kFalse);

	return newSwatchUID;
}

void SnpManipulateSwatch::IterateSwatchList(IWorkspace* workspace)
{
	InterfacePtr<ISwatchList> iSwatchList(workspace, UseDefaultIID());
    UID    noneSwatchUID = iSwatchList->GetNoneSwatchUID ();
    UID    paperSwatchUID = iSwatchList->GetPaperSwatchUID ();
    UID    blackSwatchUID = iSwatchList->GetBlackSwatchUID ();
    UID    regSwatchUID = iSwatchList->GetRegistrationSwatchUID ();

	IDataBase*	iDataBase = ::GetDataBase (iSwatchList);
	int32 		index;
	int32	numSwatches = iSwatchList->GetNumSwatches ();
	SNIPLOG("start of swatch list");
	SNIPLOG("Reserved swatches: None = %ld, paper = %ld; black = %ld, register = %ld\n", 
		noneSwatchUID.Get(),paperSwatchUID.Get(),blackSwatchUID.Get(),regSwatchUID.Get());

	for (index = 0; index < numSwatches; index++)
	{
		UIDRef	swatchRef = iSwatchList->GetNthSwatch (index);
		InterfacePtr<IRenderingObject>	iRenderObj (swatchRef, UseDefaultIID ());
		PMString swatchName = iRenderObj->GetSwatchName();
		SNIPLOG(" %dth Swatch: name = %s; UID = %ld", index, swatchName.GetPlatformString().c_str(), swatchRef.GetUID().Get());

		bool16 visible = iRenderObj->GetVisibility();
		if (visible)
			SNIPLOG("visible; ");
		else
			SNIPLOG("Invisilbe; ");
		
		ClassID swatchClass = iDataBase->GetClass (swatchRef.GetUID());
		if (swatchClass == kPMColorBoss)
		{
			SNIPLOG("swatch class =  kPMColorBoss;");
			InterfacePtr<IPersistUIDData>	iRefData (iRenderObj, IID_IPERSISTUIDDATA);
			UID baseUID = iRefData->GetUID();
			SNIPLOG(" baseUID= %ld", baseUID.Get());
 
			InterfacePtr<IColorOverrides>	iOverrides (iRenderObj, UseDefaultIID ());
			PMReal tint = iOverrides->GetTint();
			int32 colorRemark = iOverrides->GetColorRemark();
			SNIPLOG(" tint = %f, color remark= %d", ::ToDouble(tint), colorRemark);

			PMString colorType;
			InterfacePtr<IInkData>			iInkData (iRenderObj, UseDefaultIID ());
			if (iInkData->GetInkType () == IInkData::kDeviceNInk)
				colorType = "Mixed ink";
			else if (iInkData->GetInkType () == IInkData::kSpotInk)
				colorType = "Spot";
			else if (iInkData->GetInkType () == IInkData::kProcessInk)
				colorType = "Process";
			SNIPLOG(" colorType = %s ", colorType.GetPlatformString().c_str());

			InterfacePtr<IColorData> 	iColorData( iRenderObj, UseDefaultIID () );
			int32 colorSpace = iColorData->GetColorSpace();
			if (colorSpace == kPMCsCalRGB)
				SNIPLOG("kPMCsCalRGB; ");
			else if (colorSpace == kPMCsCalCMYK)
				SNIPLOG("kPMCsCalCMYK; ");
			else if (colorSpace == kPMCsLab)
 				SNIPLOG("kPMCsLab; ");
            else if (colorSpace ==kPMCsDeviceN)
				SNIPLOG("kPMCsDeviceN; ");

            ColorArray colorArray = iColorData->GetColorData();
			SNIPLOG("Color components:(");
			for (int32 i = 0; i< iColorData->GetNumComponents(); i++)
				SNIPLOG(" %f, ",::ToDouble(colorArray[i]));
			SNIPLOG(")");

			SNIPLOG("\n");

		}
		else if (swatchClass == kGradientRenderingObjectBoss)
		{
			InterfacePtr<IGradientFill>		iGradientData (iRenderObj, UseDefaultIID ());
			int32							stopCount = iGradientData->GetNumberOfStop ();
			SNIPLOG("swatch class =  kGradientRenderingObjectBoss; numStops = %d ", stopCount);
			for (int32 m = 0; m < stopCount; m++)
			{
				PMReal stopPostion = iGradientData->GetNthStopPosition (m); 
				UID stopUID = iGradientData->GetNthGradientColorUID (m);		
				SNIPLOG("%dth Stop;  stop pos = %f, stop color UID = %ld", m, ::ToDouble(stopPostion), stopUID.Get());
			}
			SNIPLOG("\n");
		}
		else if (swatchClass == kGraphicStateNoneRenderingObjectBoss)
		{
			SNIPLOG("kGraphicStateNoneRenderingObjectBoss \n");
		}
		else if (swatchClass == kAGMBlackBoxRenderingObjectBoss)
		{
			SNIPLOG("kAGMBlackBoxRenderingObjectBoss \n");
		}
		else
		{
			SNIPLOG("Unknown swatch class, id = %ld \n ",swatchClass.Get());
		} 
	}
	// end of swatch list
	SNIPLOG("end of swatch list");
}


void SnpManipulateSwatch::IterateInkList(IWorkspace* workspace)
{
	InterfacePtr<IInkList>   iInkList (workspace, UseDefaultIID ());
    int32   inkCount = iInkList->GetNumInks ();
    int32      index;
	SNIPLOG("start of ink list");
    for (index = 0; index < inkCount; index++)
    {
        UIDRef   inkUIDRef = iInkList->GetNthInk (index);
        InterfacePtr<IPMInkBossData>iInkBossData (inkUIDRef, UseDefaultIID ());
		PMString inkName = iInkBossData->GetInkName();
		SNIPLOG(" %dth Ink: name = %s; UID = %ld", index, inkName.GetPlatformString().c_str(), inkUIDRef.GetUID().Get());

        if (iInkBossData->GetInkIsProcess ())
			SNIPLOG("ink type = process");
		else
			SNIPLOG("ink type = Spot");
		SNIPLOG("\n");
	}
	SNIPLOG("End of ink list");

}
// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------


/** Makes the snippet SnpManipulateSwatch available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulateSwatch : public SnpRunnable
{
										
		
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerManipulateSwatch();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulateSwatch();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunWorkspaceContext;}
};

/* Constructor.
*/
_SnpRunnerManipulateSwatch::_SnpRunnerManipulateSwatch(): SnpRunnable("ManipulateSwatch")
{
	this->SetDescription("Manipulating the color and gradient swatch. Iterate swatch and ink list");
	this->SetPreconditions("Active workspace");
	this->SetCategories("sdk_snippet, sdk_graphic");
}

/* Destructor.
*/
_SnpRunnerManipulateSwatch::~_SnpRunnerManipulateSwatch()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerManipulateSwatch::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;

	IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();
	InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
	// Condition #1: Swatch List is available.
	if(swatchList != nil)
	{
		int32 numVisible = swatchList->GetNumVisibleSwatches();
		//Condition #2: There is at least 1 visible swatch.
		if(numVisible > 0)
		{
			result = kTrue;
		}
	}

	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerManipulateSwatch::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpManipulateSwatch  instance;

		// Use runnableContext to discover the selection target or IActiveContext.
		IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();

		InterfacePtr<ISwatchList> swatchList(workspace, UseDefaultIID());
		if (swatchList == nil)
		{
			SNIPLOG("The swatch list is nil.");
			status = kFailure;
			break;
		}
		
		// Use IParameterUtils to prompt for parameters to set up your call(if any).
		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> choices;
		choices.push_back(PMString("Create Color Swatch"));
		choices.push_back(PMString("Create Gradient Swatch"));
		choices.push_back(PMString("Delete a swatch"));
		choices.push_back(PMString("Iterate swatch list"));
		choices.push_back(PMString("Iterate ink list"));
		enum {kCreateColorSwatch, kCreateGradientSwatch, kDeleteSwatch, kIterateSwatchList, kIterateInkList};
		int32 choice  = parameterUtils->GetChoice("Choose process option?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		switch (choice) 
		{
		case kCreateColorSwatch:
			{
				//If a swatch I want to create exist, it returns cancel status. 
				UID colorUID = instance.CreateColorSwatch();
				if (colorUID != kInvalidUID)
					status = kSuccess;
				break;
			}
		case kCreateGradientSwatch:
			{
				// The input of the name of the gradient swatch.
				PMString nameString = parameterUtils->GetPMString("Specify the name of the gradient swatch to create.", "Tie-dye");
				if(parameterUtils->WasDialogCancelled())
				{
					break;
				}
				
				if (swatchList->FindSwatch(nameString) != UIDRef::gNull)
				{
	 				SNIPLOG("Swatch name already exists");
					status = kFailure;
					break;
				}
				
				instance.SetSwatchName(nameString);
						
				//The input of the type of gradient.
				K2Vector<PMString> gradType;
				gradType.push_back(PMString("Linear"));
				gradType.push_back(PMString("Radial"));
				
				enum {kChooseAxial, kChooseRadial};
				
				int32 choiceGradType = parameterUtils->GetChoice("Which type of gradient do you want?", gradType);
				if(parameterUtils->WasDialogCancelled())
				{
					break;
				}
				
				switch(choiceGradType)
				{
					case kChooseAxial:
					{
						instance.SetGradientType(kAxial);
						break;
					}
					case kChooseRadial:
					{
						instance.SetGradientType(kRadial);
						break;
					}
				}
				
				
	 			SNIPLOG("=== Swatch UID Info(begin)===");
				UID gradientUID = instance.CreateGradientSwatch(workspace);
				ASSERT(gradientUID != kInvalidUID);
				if(gradientUID == kInvalidUID) {
					break;
				}
				SNIPLOG("*Gradient color swatch UID: 0x%X", gradientUID.Get());
				SNIPLOG("===(end)===");

				status = kSuccess;
			}
			break;

		case kDeleteSwatch:
			{
				int32 numVisible = swatchList->GetNumVisibleSwatches();
				K2Vector<PMString> swatchChoices;

				// Iterate the visible swatches to populate the
				// choices K2Vector.
				for (int32 i = 0; i < numVisible; i++)
				{
					UIDRef colorRef = swatchList->GetNthVisibleSwatch(i);
					IDataBase* db = colorRef.GetDataBase();
					UID uid = colorRef.GetUID();

					swatchChoices.push_back(PMString(Utils<ISwatchUtils>()->GetSwatchName(db, uid)));
				}

				Utils<ISnipRunParameterUtils> parameterUtils;

				int32 choice = parameterUtils->GetChoice(
					PMString("Which swatch would you like to delete?"), swatchChoices);

				if (parameterUtils->WasDialogCancelled() == kFalse)
				{
					// Get the UIDRef that corresponds to the selected swatch.
					// Note: here the indexes used as arguments to GetNthVisibleSwatch()
					// align nicely. Double check this in other cases.
					UIDRef colorRef2Delete = 
						swatchList->GetNthVisibleSwatch(choice);

					// Delete the specified swatch.
					status = instance.DeleteSwatch(colorRef2Delete);
				}

			}
			break;
		case kIterateSwatchList:
			{
				instance.IterateSwatchList(workspace);
				status = kSuccess;
			}
			break; 
		case kIterateInkList:
			{
				instance.IterateInkList(workspace);
				status = kSuccess;
			}
			break;
		default:
			{
				SNIPLOG("Invalid option. Skipping.");
				status = kFailure;
			}
			break;
		}
	
	} while(false);

	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateSwatch instance_SnpRunnerManipulateSwatch;
DEFINE_SNIPPET(_SnpRunnerManipulateSwatch) 	
// End, SnpManipulateSwatch.cpp

