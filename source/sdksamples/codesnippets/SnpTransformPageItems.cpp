//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpTransformPageItems.cpp $
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
#include "ILayoutTarget.h"
#include "ITransformFacade.h"
#include "IGeometryFacade.h"
#include "ILayoutControlData.h"
#include "ILayoutUIUtils.h"
#include "IRefPointUIUtils.h"

// General includes:
#include "UIDList.h"
#include "Utils.h"
#include "LocaleSetting.h"
#include "TransformTypes.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/**	
    This code snippet provide samples for transform page items using ITransfromFacade
	and IGeometryFacade.
	\li How to move page item,
	\li How to rotate page item,
	\li How to how to scale page item,
	\li How to skew page item,
	\li How to how to resize page item,
	\li How to use generic transform interface ITransformFacade::TransformItems(...)
	\li How to use generic resize interface IGeometryFacade::ResizeItems(...)


  	@ingroup sdk_snippet
  	@ingroup sdk_layout
	

*/
class SnpTransformPageItems
{

	public:
	
		/** Constructor.
		*/
		SnpTransformPageItems() {}

		/** Destructor
		*/
		virtual ~SnpTransformPageItems() {}
		
		/** Translate pageitems, move page item by a distance
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode TranslateByPageitems(UIDList itemList);

		/** Translate pageitems, move page item to a new location
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode TranslateToPageitems(UIDList itemList);

		/** Rotate pageitems by a degree
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode RotateByPageitems(UIDList itemList);

		/** Rotate pageitems to a new degree.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode RotateToPageitems(UIDList itemList);

		/** Skew pageitems by a slope.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SkewByPageitems(UIDList itemList);

		/** Skew pageitems to a new slope.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode SkewToPageitems(UIDList itemList);

		/** Scale pageitems by a factor.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ScaleByPageitems(UIDList itemList);

		/** Scale pageitems to a certain factor.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ScaleToPageitems(UIDList itemList);

		/** Resize pageitems by a relative amount type in.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ResizeByPageitems(UIDList itemList);

		/** Resize pageitems to new size.
			@param itemList the selected page items.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode ResizeToPageitems(UIDList itemList);

private:
		ErrorCode GetReferencePoint(PBPMPoint &referencePoint );
		ErrorCode GetCoordinateSpace(Transform::CoordinateSpace &coordinateSpace);
		ErrorCode GetBoundsKind(Geometry::BoundsKind &boundsKind);
		ErrorCode GetRealValue(PMReal & value, PMString prompt);

};

/**
Translate By  
*/
ErrorCode SnpTransformPageItems::TranslateByPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get move distance
		PMReal xDistance, yDistance;
		errorCode = GetRealValue(xDistance, "How far do you want to move in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode = GetRealValue(yDistance, "How far do you want to move in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::CurrentOrigin(), Transform::TranslateBy(xDistance, yDistance));

	} while (false);

	return errorCode;
}

/**
Translate To
*/
ErrorCode SnpTransformPageItems::TranslateToPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get move distance
		PMReal xDistance, yDistance;
		errorCode = GetRealValue(xDistance, "Where do you want to move in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode = GetRealValue(yDistance, "Where do you want to move in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::TranslateTo(xDistance, yDistance));

	} while (false);

	return errorCode;
}

/**
Rotate By  
*/
ErrorCode SnpTransformPageItems::RotateByPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Rotate degree
		PMReal degree;
		errorCode = GetRealValue(degree, "How much do you want the page items rotate?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::RotateBy(degree));

	} while (false);

	return errorCode;
}

/**
Rotate to  
*/
ErrorCode SnpTransformPageItems::RotateToPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Rotate degree
		PMReal degree;
		errorCode = GetRealValue(degree, "In what angle do you want the page items rotate to?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::RotateTo(degree));

	} while (false);

	return errorCode;
}

/**
Skew By  
*/
ErrorCode SnpTransformPageItems::SkewByPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get skew slope, 
		PMReal slope;  
		errorCode = GetRealValue(slope, "What is the slope you want the page items skew by?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::SkewBySlope(slope));
							// You may also choose to use degrees by  Transform::SkewBy() 

	} while (false);

	return errorCode;
}

/**
Skew to  
*/
ErrorCode SnpTransformPageItems::SkewToPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Translating pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get skew to slope
		PMReal slope;
		errorCode = GetRealValue(slope, "What is the slope do you want the page items skew to?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::SkewToSlope(slope));

	} while (false);

	return errorCode;
}

/**
Scale By  
*/
ErrorCode SnpTransformPageItems::ScaleByPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get scale factor, 
		PMReal xscale, yscale;
		errorCode = GetRealValue(xscale, "What is the scale factor in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}
		errorCode = GetRealValue(yscale, "What is the scale factor in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::ScaleBy(xscale,yscale));

	} while (false);

	return errorCode;
}

/**
Scale to  
*/
ErrorCode SnpTransformPageItems::ScaleToPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get scale factor, 
		PMReal xscale, yscale;
		errorCode = GetRealValue(xscale, "What is the scale factor you want to be in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}
		errorCode = GetRealValue(yscale, "What is the scale factor you want to be in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::ITransformFacade>()->TransformItems( itemList, coordinateSpace, Transform::PasteboardLocation( referencePoint), Transform::ScaleTo(xscale,yscale));

	} while (false);

	return errorCode;
}

/**
Resize by  
*/
ErrorCode SnpTransformPageItems::ResizeByPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Ask for Bounds kind
		Geometry::BoundsKind boundsKind = Geometry::OuterStrokeBounds();
		errorCode = GetBoundsKind(boundsKind);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get resize amount, 
		PMReal xdelta, ydelta;
		errorCode = GetRealValue(xdelta, "How much do you and change in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}
		errorCode = GetRealValue(ydelta, "How much do you and change in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::IGeometryFacade>()->ResizeItems( itemList, coordinateSpace, boundsKind, Transform::PasteboardLocation( referencePoint), Geometry::AddTo(xdelta,ydelta));

	} while (false);

	return errorCode;
}

/**
Resize to  
*/
ErrorCode SnpTransformPageItems::ResizeToPageitems(UIDList itemList)
{
	ErrorCode errorCode = kFailure;
	do {

		if (itemList.Length() <= 0 ) 
		{
			SNIPLOG("Tranforming pageitems requires layout selection");
			break;
		}						
	
		// Ask for Coordinate space
		Transform::CoordinateSpace coordinateSpace = Transform::PasteboardCoordinates() ;
		errorCode = GetCoordinateSpace(coordinateSpace);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Ask for Bounds kind
		Geometry::BoundsKind boundsKind =Geometry::OuterStrokeBounds();
		errorCode = GetBoundsKind(boundsKind);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get Reference point
		PBPMPoint referencePoint(0, 0); 
		errorCode = GetReferencePoint(referencePoint);
		if (kSuccess != errorCode)
		{
			break;
		}

		// Get new size 
		PMReal xsize, ysize;
		errorCode = GetRealValue(xsize, "What is new size you want to be in X direction?");
		if (kSuccess != errorCode)
		{
			break;
		}
		errorCode = GetRealValue(ysize, "What is new size you want to be in Y direction?");
		if (kSuccess != errorCode)
		{
			break;
		}

		errorCode =  Utils<Facade::IGeometryFacade>()->ResizeItems( itemList, coordinateSpace, boundsKind, Transform::PasteboardLocation( referencePoint), Geometry::ResizeTo(xsize,ysize));

	} while (false);

	return errorCode;
}

/**
GetCoordinateSpace
*/
ErrorCode SnpTransformPageItems::GetReferencePoint(PBPMPoint &referencePoint )
{
	ErrorCode error = kSuccess;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		PMReal xPos, yPos;
		//Set default reference point. It is not necessary, but for convenience
        InterfacePtr<ILayoutControlData> layoutData(Utils<ILayoutUIUtils>()->QueryFrontLayoutData());
		PBPMPoint defaultRefPoint = Utils<IRefPointUIUtils>()->GetPasteboardReferencePoint(layoutData);

		xPos  = parameterUtils->GetPMReal("What is the X value of reference point?", defaultRefPoint.X());
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}		
		yPos  = parameterUtils->GetPMReal("What is the Y value of reference point?", defaultRefPoint.Y());
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}		

		referencePoint.X(xPos);
		referencePoint.Y(yPos);

	} while (false);

	return error;
}
/**
GetCoordinateSpace
*/
ErrorCode SnpTransformPageItems::GetCoordinateSpace(Transform::CoordinateSpace &coordinateSpace)
{
	ErrorCode error = kSuccess;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> coordinateSpaceString;
		coordinateSpaceString.push_back(PMString("Pasteboard Coordinates"));
		coordinateSpaceString.push_back(PMString("Parent Coordinates"));
		coordinateSpaceString.push_back(PMString("Inner Coordinates"));

		enum {kPasteboardCoordinates, kParentCoordinates, kInnerCoordinates};
		int32 space  = parameterUtils->GetChoice("Choose a coordinate system in which you plan to transform :", coordinateSpaceString);
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}

		switch (space)
		{
		case kPasteboardCoordinates:
			coordinateSpace = Transform::PasteboardCoordinates();
			break;
		case kParentCoordinates:
			coordinateSpace = Transform::ParentCoordinates();
			break;
		case kInnerCoordinates:
			coordinateSpace = Transform::InnerCoordinates();
			break;
		}
		
	}while (false);

	return error;
}

/**
GetCoordinateSpace
*/
ErrorCode SnpTransformPageItems::GetBoundsKind(Geometry::BoundsKind &boundsKind)
{
	ErrorCode error = kSuccess;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		K2Vector<PMString> boundsKindString;
		boundsKindString.push_back(PMString("Out stroke bounds"));
		boundsKindString.push_back(PMString("Path bounds"));

		enum {kOutStrokeBounds, kPathBounds};
		int32 kind  = parameterUtils->GetChoice("Choose a bounds type you want to resize :", boundsKindString);
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}

		switch (kind)
		{
		case kOutStrokeBounds:
			boundsKind = Geometry::OuterStrokeBounds();
			break;
		case kPathBounds:
			boundsKind = Geometry::PathBounds();
			break;
		}
		
	}while (false);

	return error;
}

ErrorCode SnpTransformPageItems::GetRealValue(PMReal & value, PMString prompt)
{
	ErrorCode error = kSuccess;
	do {
		Utils<ISnipRunParameterUtils> parameterUtils;

		value  = parameterUtils->GetPMReal(prompt);
		if (parameterUtils->WasDialogCancelled()) 
		{
			error = kCancel;
			break;
		}		
	}while (false);

	return error;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpTransformPageItems available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerTransformPageItems : public SnpRunnable
{
	public:
		// For SnippetRunner framework.

		/** Constructor.
		*/
		_SnpRunnerTransformPageItems();

		/** Destructor
		*/
		virtual ~_SnpRunnerTransformPageItems();

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
_SnpRunnerTransformPageItems::_SnpRunnerTransformPageItems() : SnpRunnable("TransformPageItems")
{
	this->SetDescription("Trasnform page item.");
	this->SetPreconditions("Page item selected in the layout.");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
_SnpRunnerTransformPageItems::~_SnpRunnerTransformPageItems()
{
}

/*
*/
bool16 _SnpRunnerTransformPageItems::CanRun(ISnpRunnableContext* runnableContext)
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
ErrorCode _SnpRunnerTransformPageItems::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do 
	{

		SnpTransformPageItems instance;

		// ask for a choice of tasks
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Translate by", PMString::kEncodingASCII));
		choices.push_back(PMString("Translate to", PMString::kEncodingASCII));
		choices.push_back(PMString("Rotate by", PMString::kEncodingASCII));
		choices.push_back(PMString("Rotate to", PMString::kEncodingASCII));
		choices.push_back(PMString("Skew by", PMString::kEncodingASCII));
		choices.push_back(PMString("Skew to", PMString::kEncodingASCII));
		choices.push_back(PMString("Scale by", PMString::kEncodingASCII));
		choices.push_back(PMString("Scale to", PMString::kEncodingASCII));
		choices.push_back(PMString("Resize by", PMString::kEncodingASCII));
		choices.push_back(PMString("Resize to", PMString::kEncodingASCII));
		enum {kTranslateByPageitems, kTranslateToPageitems, kRotateByPageitems,kRotateToPageitems, kSkewByPageitems,  kSkewToPageitems, kScaleByPageitems,kScaleToPageitems, kResizeByPageitems, kResizeToPageitems};
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
		case kTranslateByPageitems:
			status = instance.TranslateByPageitems(itemList);
			break;
		case kTranslateToPageitems:
			status = instance.TranslateToPageitems(itemList);
			break;
		case kRotateByPageitems:
			status = instance.RotateByPageitems(itemList);
			break;
		case kRotateToPageitems:
			status = instance.RotateToPageitems(itemList);
			break;
		case kSkewByPageitems:
			status = instance.SkewByPageitems(itemList);
			break;
		case kSkewToPageitems:
			status = instance.SkewToPageitems(itemList);
			break;
		case kScaleByPageitems:
			status = instance.ScaleByPageitems(itemList);
			break;
		case kScaleToPageitems:
			status = instance.ScaleToPageitems(itemList);
			break;
		case kResizeByPageitems:
			status = instance.ResizeByPageitems(itemList);
			break;
		case kResizeToPageitems:
			status = instance.ResizeToPageitems(itemList);
			break;
		}
	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerTransformPageItems::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerTransformPageItems instance_SnpRunnerTransformPageItems;
DEFINE_SNIPPET(_SnpRunnerTransformPageItems) 	
//End, SnpTransformPageItems.cpp
