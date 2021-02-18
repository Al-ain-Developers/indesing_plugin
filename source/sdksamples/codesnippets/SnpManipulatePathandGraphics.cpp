//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulatePathandGraphics.cpp $
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
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "IImageDataAccess.h"
#include "ISplineUtils.h"
#include "IBoolData.h"
#include "IConvertShapeSuite.h"
#include "IClippingPathSuite.h"
#include "ITextWrapFacade.h"
#include "ISelectionUtils.h"
#include "IClipSettings.h"
#include "IFrameContentFacade.h"
#include "InstStrokeFillID.h"

// General includes:
#include "RangeData.h"
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
    This code snippet provide samples for manipulating path and graphic page item
	settings, specifically, the following area are covered:
	\li How to perform path operations,
	\li How to fit graphic items with frame,
	\li How to set up clipping path,
	\li How to set up text wrap options,

	Note:
	(1) Selection suites takes care of selection of a frame or a graphic item, so when setting clipping path, 
	    we do not need to find graphic item of the frame.
	(2) Since we don't provide method to get number of alpah channel and photoshop path directly, so if alpha or photoshop path index is invalid, you may see assert, but it is ignorable.
	(3) This snippet does not include set text wrap mode. Please see SnpManipulateTextFrame for sample.
	    Since text wrap contour options only available when there is a graphic selected and the text wrap
		mode is "Wrap around object shape", you will have to manually set it on text wrap palette to make this snippet functions as expected.
    

  	@ingroup sdk_snippet
  	@ingroup sdk_graphic
	

*/
class SnpManipulatePathandGraphics
{

	public:
	
		/** Constructor.
		*/
		SnpManipulatePathandGraphics() {}

		/** Destructor
		*/
		virtual ~SnpManipulatePathandGraphics() {}
		
		/** Perform path operations
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode MakeCompoundPath(UIDList itemList);

		/** Perform path operations
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ConvertShape(UIDList itemList);

		/** Fit graphic content with frame
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode PerformContentFitting(UIDList itemList);

		/** Set up clipping path of a graphic item
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetClippingPath();

		/** Set up text wrap contour options
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SetTextWrapContourOptions(UIDList itemList);



private:

	/** Read user choice of corner effect. (used in convert shape)
			@param IN/OUT cornerClass the ClassID of the corner effect. Out as kInvalidClass for regular rectangle (no corner effect)
			@return kCancel is the dialog is cancelled out, otherwise kSuccess.
	*/
	ErrorCode GetCornerEffect(ClassID &cornerClass);


};

/**
Making compound path 
*/
ErrorCode SnpManipulatePathandGraphics::MakeCompoundPath(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() < 2 ) 
		{
			SNIPLOG("Make compound path requires two or more selected items.");
			break;
		}						
		
		Utils<ISplineUtils>()->FilterMakeCompoundPathList(itemList ) ;    //removes text on path, non-path items, locked items

		// Make a compound path
		InterfacePtr<ICommand> makeCmd ( CmdUtils::CreateCommand( kMakeCompoundPathCmdBoss ) );
		InterfacePtr<IBoolData> iBoolData (makeCmd, IID_IBOOLDATA);
		iBoolData->Set (kTrue); // Tell the command to reverse every other path
		makeCmd->SetItemList( itemList ) ;
		errorCode = CmdUtils::ProcessCommand( makeCmd ) ;

		// Report the resulting page item
		const UIDList* cmdList = makeCmd->GetItemList();
		InterfacePtr<IPathGeometry> pathGeo( cmdList->GetDataBase(), cmdList->First(), UseDefaultIID() );
		int32 numPaths = pathGeo->GetNumPaths();
		SNIPLOG("The resulting compound pathhas %d paths:", numPaths);

	} while(false);

	return errorCode;
}

/**
Convert shape. Other path operations such as path finder (compound shape) is similar, but use IPathOperationSuite.
*/
ErrorCode SnpManipulatePathandGraphics::ConvertShape(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Converting shape requires layout selection");
			break;
		}						
		
		Utils<ISplineUtils>()->FilterMakeCompoundPathList(itemList ) ;    //removes text on path, non-path items, locked items


		InterfacePtr<IConvertShapeSuite>   iConvertShapeSuite ((IConvertShapeSuite *)Utils<ISelectionUtils>()->QuerySuite(IID_ICONVERTSHAPESUITE));
		if (!iConvertShapeSuite)
			break;

		// Default parameters
		ClassID cornerClass = kInvalidClass;
		IConvertShapeSuite::ShapeType convertTo = IConvertShapeSuite::kRectangle;
		PMReal cornerRadius = 0;
		int32 numSides = 0;
		int32 starInset = 0;

		// Get parameters
		K2Vector<PMString> choices;
		choices.push_back(PMString("Rectangle"));
		choices.push_back(PMString("Oval"));
		choices.push_back(PMString("Triangle"));
		choices.push_back(PMString("Polygon"));

		enum {kRectangle, kOval, kTriangle, kPolygon};
		Utils<ISnipRunParameterUtils> parameterUtils;
		int32 choice  = parameterUtils->GetChoice("Choose an shape you want to convert to:", choices);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		switch (choice)
		{
		case kRectangle:
			{
				convertTo = IConvertShapeSuite::kRectangle;
				//Ask for corner effects and corner radius
				// corner effects are only for rectangles.
				if (kSuccess != GetCornerEffect(cornerClass))
				{
					errorCode = kCancel;
					break;
				}
				
				if (cornerClass != kInvalidClass)
				{ // Not a regular rectangle, don't need the corner radius
					cornerRadius  = parameterUtils->GetPMReal("Corner radius:");
					if (parameterUtils->WasDialogCancelled()) {
						errorCode = kCancel;
						break;
					}
				}
				errorCode = iConvertShapeSuite->ConvertPageItemShape(convertTo, cornerClass, cornerRadius);

				break;
			}
		case kOval:
			{
				errorCode = iConvertShapeSuite->ConvertPageItemShape(IConvertShapeSuite::kEllipse);
				break;               
			}
		case kTriangle:
			{
				errorCode = iConvertShapeSuite->ConvertPageItemShape(IConvertShapeSuite::kTriangle, kInvalidClass, 3);
				break;
			}
		case kPolygon:
			{
				numSides  = parameterUtils->GetInt32("Number of sides");			
				if (parameterUtils->WasDialogCancelled()) {
					errorCode = kCancel;
					break;
				}
				starInset  = parameterUtils->GetInt32("Star inset");				
				if (parameterUtils->WasDialogCancelled()) {
					errorCode = kCancel;
					break;
				}
				errorCode = iConvertShapeSuite->ConvertPageItemShape(IConvertShapeSuite::kPolygonX, kInvalidClass, cornerRadius, numSides, starInset);
				break;
			}
		}

	} while(false);

	return errorCode;
}

/**
 Content fitting. The sample only lists for graphic frame content fitting, 
 you may also fit frame to content for text frame too.
*/
ErrorCode SnpManipulatePathandGraphics::PerformContentFitting(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("No item is selected.");
			break;
		}						
		
		// Ask for the type of operation to be performed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Fit content to frame"));
		choices.push_back(PMString("Fit frame to content"));
		choices.push_back(PMString("Center content in frame"));
		choices.push_back(PMString("Fit content proportionally"));
		choices.push_back(PMString("Fill frame proportionally"));

		enum {kFitContentToFrame, kFitFrameToContent, kCenterContentInFrame, kFitContentProportionally,kFillFrameProportionally};
		int32 choice  = parameterUtils->GetChoice("Choose an operation.", choices);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		Utils<Facade::IFrameContentFacade> frameContentFacade;
		switch (choice) 
		{
		case kFitContentToFrame:
			{
				UIDList newList(itemList.GetDataBase());
				for (int32 i = 0; i<itemList.Length(); i++)
				{
					SnpGraphicHelper graphicHelper(itemList.GetRef(i));
					InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
					if (imageAccess)
						newList.Append( ::GetUID(imageAccess));
				}

				if (newList.Length() <= 0 ) 
				{
					SNIPLOG("No item with graphics is selected.");
					return kFailure;
				}
				else
				{
					return (frameContentFacade->FitContentToFrame(newList));
				}
			}
		case kFitFrameToContent:
			{
				// Only this command requires the frame of the content.
				UIDList newList(itemList.GetDataBase());
				for (int32 i = 0; i < itemList.Length(); i++)
				{
					SnpGraphicHelper graphicHelper(itemList.GetRef(i));
					newList.Append(graphicHelper.GetGraphicFrame());
				}
				return (frameContentFacade->FitFrameToContent(newList));
			}
		case kCenterContentInFrame:
			{
				UIDList newList(itemList.GetDataBase());
				for (int32 i = 0; i<itemList.Length(); i++)
				{
					SnpGraphicHelper graphicHelper(itemList.GetRef(i));
					InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
					if (imageAccess)
						newList.Append( ::GetUID(imageAccess));
				}

				if (newList.Length() <= 0 ) 
				{
					SNIPLOG("No item with graphics is selected.");
					return kFailure;
				}
				else
				{
					return (frameContentFacade->CenterContentInFrame(newList));
				}
			}
		case kFitContentProportionally:
			{
				UIDList newList(itemList.GetDataBase());
				for (int32 i = 0; i<itemList.Length(); i++)
				{
					SnpGraphicHelper graphicHelper(itemList.GetRef(i));
					InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
					if (imageAccess)
						newList.Append( ::GetUID(imageAccess));
				}

				if (newList.Length() <= 0 ) 
				{
					SNIPLOG("No item with graphics is selected.");
					return kFailure;
				}
				else
				{
					return (frameContentFacade->FitContentProp(newList));
				}	
			}
		case kFillFrameProportionally:
			{
				UIDList newList(itemList.GetDataBase());
				for (int32 i = 0; i<itemList.Length(); i++)
				{
					SnpGraphicHelper graphicHelper(itemList.GetRef(i));
					InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
					if (imageAccess)
						newList.Append( ::GetUID(imageAccess));
				}

				if (newList.Length() <= 0 ) 
				{
					SNIPLOG("No item with graphics is selected.");
					return kFailure;
				}
				else
				{
					return (frameContentFacade->FillFrameProp(newList));
				}

			}
			break;
		}


	} while(false);

	return errorCode;
}
/**
Setting up clipping path use clipping suite.
*/
ErrorCode SnpManipulatePathandGraphics::SetClippingPath()
{
	ErrorCode errorCode = kFailure;
	do {

		InterfacePtr<IClippingPathSuite> iClipPathSuite ((IClippingPathSuite *)Utils<ISelectionUtils>()->QuerySuite(IID_ICLIPPINGPATHSUITE));
		if (!iClipPathSuite)
			break;

		if (!(iClipPathSuite->CanHaveClippingPath()) )
		{
			SNIPLOG("Can not set clipping path for selection. Clipping path requires an graphic to be selected");
			break;
		}

		// Reserve current settings
		InterfacePtr<const IClipSettings> clipSettings(iClipPathSuite->QueryActiveClipSettings());
		IClipSettings::ClipType clipType = clipSettings->GetClipType();

		// set clipping type defaults
		int32 defaultIndex = 0;
		switch (clipType)
		{
		default:
		case IClipSettings::kClipNone:
			defaultIndex = 0;	break;
		case IClipSettings::kClipEdgeDetection:
			defaultIndex = 1;	break;
		case IClipSettings::kClipAlpha:
			defaultIndex = 2;	break;
		case IClipSettings::kClipEmbeddedPath:
			defaultIndex = 3;	break;
		}

		// Get clipping type
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Remove Clipping"));
		choices.push_back(PMString("Detect Edges"));
		choices.push_back(PMString("Using Alpha Channel"));
		choices.push_back(PMString("Using Photoshop Path"));

		enum {kClipNone, kClipEdgeDetection, kClipAlpha, kClipEmbeddedPath};
		int32 choice  = parameterUtils->GetChoice("Set clipping path to:", choices, defaultIndex);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		if (choice == kClipNone)
		{
			return iClipPathSuite->RemoveClipping();
		}

		// These option is only necessory for detect edges.
		PMReal tolerance  = clipSettings->GetTolerance();
		int32 threshold = clipSettings->GetThreshold();
		if (choice == kClipEdgeDetection)
		{
			tolerance = parameterUtils->GetPMReal("Tolerance = ", tolerance);
			if (parameterUtils->WasDialogCancelled()) {
				errorCode = kCancel;
				break;
			}
			threshold = parameterUtils->GetInt32("Threshold = ", threshold);
			if (parameterUtils->WasDialogCancelled()) {
				errorCode = kCancel;
				break;
			}
		}

 		PMReal minPathSize  =  2 * tolerance;

		PMReal inset  = parameterUtils->GetPMReal("Inset = ", clipSettings->GetInset());
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		// Update flags
		bool16 invert = clipSettings->GetInvert();
		bool16 allowHoles = clipSettings->GetAllowHoles();
		bool16 restrictToFrame = clipSettings->GetRestrictToFrame();
		bool16 useHighRes = clipSettings->GetUseHighRes();
		K2Vector<PMString> yesNo;
		yesNo.push_back(PMString("Yes"));
		yesNo.push_back(PMString("No"));
		enum {kYes, kNo};

		int32 allow  = parameterUtils->GetChoice("Invert? ", yesNo, invert? 0 : 1);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}
		invert = (allow == kYes);

		// These option is only necessory for detect edges.
		if (choice == kClipEdgeDetection)
		{
			int32 allow2  = parameterUtils->GetChoice("Allow hole? ", yesNo, allowHoles? 0 : 1);
			if (parameterUtils->WasDialogCancelled()) {
				errorCode = kCancel;
				break;
			}
			allowHoles =(allow2 == kYes);

			allow2  = parameterUtils->GetChoice("Restrict to frame? ", yesNo, restrictToFrame? 0 : 1);
			if (parameterUtils->WasDialogCancelled()) {
				errorCode = kCancel;
				break;
			}
			restrictToFrame =(allow2 == kYes);

			allow2  = parameterUtils->GetChoice("Use high resolution image? ", yesNo, useHighRes? 0 : 1);
			if (parameterUtils->WasDialogCancelled()) {
				errorCode = kCancel;
				break;
			}
			useHighRes =(allow2 == kYes);

		}

		uint32 flags = 0;
		if ( useHighRes )
			flags |= IClippingPathSuite::kUseHighResFlag;
		if ( allowHoles )
			flags |= IClippingPathSuite::kAllowHolesFlag;
		if (  invert )
			flags |= IClippingPathSuite::kInvertFlag;
		if (  restrictToFrame )
			flags |= IClippingPathSuite::kRestrictToFrameFlag;

		int32 subPathIndex;
		switch (choice) 
		{
		case IClipSettings::kClipEdgeDetection:
			{
			errorCode = iClipPathSuite->DoDetectEdges(tolerance, minPathSize, inset,
											flags, threshold);
			break;
			}
		case IClipSettings::kClipAlpha:
			if (iClipPathSuite->HasAlphaChannels())
			{
				subPathIndex  = parameterUtils->GetInt32("Index of alpha channel = ");
				if (parameterUtils->WasDialogCancelled()) {
					errorCode = kCancel;
					break;
				}
				errorCode = iClipPathSuite->ApplyAlphaChannel(subPathIndex, tolerance, minPathSize, inset,
												flags, threshold);
			}
			else
			{
				SNIPLOG("The image does not have alpha channel");
				errorCode = kFailure;
			}
			break;
		case IClipSettings::kClipEmbeddedPath:
			if (iClipPathSuite->HasPhotoshopPaths())
			{
				subPathIndex  = parameterUtils->GetInt32("Index of photoshop path = ");
				if (parameterUtils->WasDialogCancelled()) {
					errorCode = kCancel;
					break;
				}
				errorCode = iClipPathSuite->ApplyEmbeddedPath(subPathIndex, nil, tolerance, minPathSize,
												inset,flags);
			}
			else
			{
				SNIPLOG("The image does not have photoshop path");
				errorCode = kFailure;
			}
			break;
		}

	} while(false);

	return errorCode;
}

/**
 Setting up text wrap contour options using text wrap facade.
 See also manipluate text frame snippet for setting text wrap mode.
*/
ErrorCode SnpManipulatePathandGraphics::SetTextWrapContourOptions(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		Utils<Facade::ITextWrapFacade> textWrapFacade;
		if (!textWrapFacade)
			break;
	
		if (itemList.Length() > 1 ) 
		{
			SNIPLOG("More than one item is selected, this snippet only support setting text wrap first item at a time for demonstatration purpose \n");
		}

		// The facade will take care of frame/item conversion
		UIDRef image = itemList.GetRef(0);
		SnpGraphicHelper graphicHelper(image);
		InterfacePtr<IImageDataAccess> imageAccess(graphicHelper.QueryImageDataAccess());
		if (imageAccess)
			image = ::GetUIDRef(imageAccess);

		IStandOffContourWrapSettings::ContourWrapType oldContourType = IStandOffContourWrapSettings::kInvalid;
		int16 oldPathIndex = 0;
		int16 oldAlphaIndex = 0;
		bool8 oldAllowHoles = kFalse;
		PMReal tolerance = 0;
		uint8 threshold = 0;
		errorCode = textWrapFacade->GetContourWrapSettings(image, &oldContourType, &oldPathIndex, &oldAlphaIndex, &tolerance, &threshold, &oldAllowHoles);

		IStandOffContourWrapSettings::ContourWrapType contourType = IStandOffContourWrapSettings::kInvalid;
		int16 pathOrAlphaIndex = 0;
		bool8 allowHoles = kFalse;

		// Get parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Graphic Bounds"));
		choices.push_back(PMString("Detect Edges"));
		choices.push_back(PMString("Using Alpha Channel"));
		choices.push_back(PMString("Using Photoshop Path"));
		choices.push_back(PMString("Graphic Frame"));
		choices.push_back(PMString("SameAsClip"));
		choices.push_back(PMString("Select Subject"));

		enum {kGraphicBounds, kEdgeDetection, kAlpha, kEmbeddedPath, kGraphicFrame, kSameAsClip, kSelectSubject};
		int32 choice  = parameterUtils->GetChoice("Set contour type to:", choices);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}
		
		switch (choice)
		{
		case kGraphicBounds:
			contourType = IStandOffContourWrapSettings::kGraphicBounds;
			break;
		case kEdgeDetection:
			contourType = IStandOffContourWrapSettings::kEdgeDetection;
			break;
		case kAlpha:
			contourType = IStandOffContourWrapSettings::kAlpha;
			pathOrAlphaIndex  = parameterUtils->GetInt32("Index of alpha channel = ", oldAlphaIndex);
			break;
		case kEmbeddedPath:
			contourType = IStandOffContourWrapSettings::kEmbeddedPath;
			pathOrAlphaIndex  = parameterUtils->GetInt32("Index of photoshop path = ", oldPathIndex);
			break;
		case kGraphicFrame:
			contourType = IStandOffContourWrapSettings::kGraphicFrame;
			break;
		case kSameAsClip:
			contourType = IStandOffContourWrapSettings::kSameAsClip;
			break;
		case kSelectSubject:
			contourType = IStandOffContourWrapSettings::kSelectSubject;
			break;
		}

		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		int32 defaultAllowHolesIndex =  oldAllowHoles? 0 : 1;
		K2Vector<PMString> yesNo;
		yesNo.push_back(PMString("Yes"));
		yesNo.push_back(PMString("No"));
		enum {kYes, kNo};
		int32 allow  = parameterUtils->GetChoice("Allow hole? ", yesNo, defaultAllowHolesIndex);
		if (parameterUtils->WasDialogCancelled()) {
			errorCode = kCancel;
			break;
		}

		allowHoles =(allow == kYes);

		bool16 bSettingsChanged = oldContourType != contourType ||
			((contourType == IStandOffContourWrapSettings::kAlpha) && (oldAlphaIndex != pathOrAlphaIndex)) ||
			((contourType == IStandOffContourWrapSettings::kEmbeddedPath) && (oldPathIndex != pathOrAlphaIndex)) ||
			oldAllowHoles != allowHoles;

		if (!bSettingsChanged)
		{
			SNIPLOG("New setting is the same as old setting, nothing chnaged");
			errorCode = kSuccess;
			break;
		}
		
		// Tolerance and threshold is not changed.
		errorCode  = textWrapFacade->SetContourWrapSettings(image, contourType, pathOrAlphaIndex, pathOrAlphaIndex, tolerance, threshold, allowHoles);

	} while(false);

	return errorCode;
}


/**
Get corner effect
*/
ErrorCode SnpManipulatePathandGraphics::GetCornerEffect(ClassID &cornerClass)
{
	ErrorCode error = kSuccess;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> cornereffects;
		cornereffects.push_back(PMString("Normal rectangle"));
		cornereffects.push_back(PMString("Rounded corner"));
		cornereffects.push_back(PMString("Bever corner"));
		cornereffects.push_back(PMString("Inverse rounded corner"));
		cornereffects.push_back(PMString("Fancy corner"));

		enum {kNormal, kRounded, kBever, kInverseRounded, kFancy};
		int32 effect  = parameterUtils->GetChoice("Choose an corner effects:", cornereffects);
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}

		switch (effect)
		{
		case kNormal:
			cornerClass = kInvalidClass;
			break;
		case kRounded:
			cornerClass = kRoundedCornerBoss;
			break;
		case kBever:
			cornerClass = kBevelCornerBoss;
			break;
		case kInverseRounded:
			cornerClass = kInverseRoundedCornerBoss;
			break;
		case kFancy:
			cornerClass = kFancyCornerBoss;
			break;
		}
		
	}while (false);

	return error;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpManipulatePathandGraphics available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerManipulatePathandGraphics : public SnpRunnable
{
	public:
		// For SnippetRunner framework.

		/** Constructor.
		*/
		_SnpRunnerManipulatePathandGraphics();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulatePathandGraphics();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunLayoutTargetContext;}
};

/* Constructor
*/
_SnpRunnerManipulatePathandGraphics::_SnpRunnerManipulatePathandGraphics() : SnpRunnable("ManipulatePathandGraphics")
{
	this->SetDescription("Manipulate paths and change clipping path, text wrap contour option settings.");
	this->SetPreconditions("Page item selected.");
	this->SetCategories("sdk_snippet, sdk_graphic");
}

/* Destructor
*/
_SnpRunnerManipulatePathandGraphics::~_SnpRunnerManipulatePathandGraphics()
{
}

/*
*/
bool16 _SnpRunnerManipulatePathandGraphics::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 canRun = kFalse;

	do {
		// Require a layout selection to be able to run.
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget == nil) 
		{
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() <= 0 ) 
		{
			break;
		}						
		
		canRun = kTrue;

	} while (false);

	return canRun;
}

/* 
*/
ErrorCode _SnpRunnerManipulatePathandGraphics::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do 
	{

		SnpManipulatePathandGraphics instance;

		// ask for a choice of tasks
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Make compound path"));
		choices.push_back(PMString("Convert shape"));

		choices.push_back(PMString("Fit graphic item with frame", PMString::kEncodingASCII));
		choices.push_back(PMString("Set clipping path", PMString::kEncodingASCII));
		choices.push_back(PMString("Set text wrap contour options", PMString::kEncodingASCII));
		enum {kCompoundPath, kConvertShape, kContentFitting, kClippingPath, kTextWrap};
		int32 choice  = parameterUtils->GetChoice("What do you want to do?", choices);
		if (parameterUtils->WasDialogCancelled() == kTrue) 
		{
			status = kCancel;
			break;
		}

		// Get the selected item
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget == nil) 
		{
			break;
		}
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() <= 0 ) 
		{
			break;
		}						

		switch (choice) 
		{
		case kCompoundPath:
			status = instance.MakeCompoundPath(itemList);
			break;
		case kConvertShape:
			status = instance.ConvertShape(itemList);
			break;
		case kContentFitting:
			status = instance.PerformContentFitting(itemList);
			break;
		case kClippingPath:
			status = instance.SetClippingPath();
			break;
		case kTextWrap:
			status = instance.SetTextWrapContourOptions(itemList);
			break;
		}
	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerManipulatePathandGraphics::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulatePathandGraphics instance_SnpRunnerManipulatePathandGraphics;
DEFINE_SNIPPET(_SnpRunnerManipulatePathandGraphics) 	
//End, SnpManipulatePathandGraphics.cpp
