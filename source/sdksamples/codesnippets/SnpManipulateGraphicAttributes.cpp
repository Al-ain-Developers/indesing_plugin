//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateGraphicAttributes.cpp $
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
#include "IDashedAttributeValues.h"
#include "IGraphicAttributeUtils.h"
#include "IGraphicAttrRealNumber.h"
#include "IGraphicStyleDescriptor.h"
#include "ILayoutTarget.h"
#include "ISelectionManager.h"
#include "ISwatchUtils.h"

// General includes:
#include "UIDList.h"
#include "Utils.h"
#include "InstStrokeFillID.h" // for ClassIDs of path strokers, corner effects etc.
#include "LocaleSetting.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"
#include "SnpGraphicHelper.h"

/**	
	\li How to apply graphic attributes that control how a path is drawn using the low level API,
	\li How to inspect the graphic attributes applied to a page item,
	\li the attributes that control stroke weight, stroke colour, fill colour, mitre, 
		line cap, dashed lines, rounded corners, line end and other effects are shown,
	\li for documentation on low level manipulation of graphic attributes read 
		SnpGraphicHelper and check out IGraphicAttributeUtils,
	\li check out IGraphicAttributeSuite for a ready made suite if you don't
		need low level access.

  	@ingroup sdk_snippet
  	@ingroup sdk_graphic
	
	@see SnpGraphicHelper
	@see IGraphicAttributeSuite
	@see IGraphicAttributeUtils
	@see IGraphicStyleDescriptor
*/
class SnpManipulateGraphicAttributes
{

	public:
	
		/** Constructor.
		*/
		SnpManipulateGraphicAttributes() {}

		/** Destructor
		*/
		virtual ~SnpManipulateGraphicAttributes() {}

		/** Changes the value of a single graphic attribute in
			all the given items. 
		
			The attributes this method can change represent some of the
			most frequently used. Once the attribute and its value
			have been obtained SnpGraphicHelper is used to make the
			change. If you want to change more than one attribute value 
			at a time you can, check out SnpGraphicHelper for how.

			@param itemList references the page items to be changed.
			@return kSuccess on success, other ErrorCode otherwise.
		 */
		ErrorCode Apply(const UIDList& itemList);
		
		/**	Inspect some of the graphic attributes that apply to the given page item.
			@param pageItemUIDRef to be inspected.
		 */
		void		Inspect(const UIDRef& pageItemUIDRef);
};

/* 
*/
ErrorCode SnpManipulateGraphicAttributes::Apply(const UIDList& itemList)
{
	ErrorCode status = kFailure;
	do {
		// Ask for the type of attribute to be applied.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("StrokeWeight"));
		choices.push_back(PMString("StrokeRendering"));
		choices.push_back(PMString("FillRendering"));
		choices.push_back(PMString("CornerImplementation"));
		choices.push_back(PMString("CornerRadius"));
		choices.push_back(PMString("LineImplementation"));
		choices.push_back(PMString("LineEndEndImplementation"));
		choices.push_back(PMString("JoinType"));
		choices.push_back(PMString("LineCap"));
		choices.push_back(PMString("DashedValues"));
		enum {kStrokeWeight, kStrokeRendering, kFillRendering, kCornerImplementation, kCornerRadius, kLineImplementation,
			kLineEndEndImplementation, kJoinType, kLineCap, kDashedValues};
		int32 choice  = parameterUtils->GetChoice("Choose graphic attribute.", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Use a helper class to apply the chosen attribute
		// to all selected items.
		SnpGraphicHelper graphicHelper(itemList);

		// Ask for the attribute's value.
		switch (choice) 
		{
		default:
		case kStrokeWeight:
			{
				PMReal strokeWeight = parameterUtils->GetPMReal("Stroke weight", 1.0, 0.0, 100.0);
				graphicHelper.AddStrokeWeight(strokeWeight);
				break;
			}
		case kStrokeRendering:
			{
				PMString swatchName = parameterUtils->GetPMString("Swatch name", PMString("Black"));
				UID swatchUID = graphicHelper.GetNamedSwatch(swatchName, itemList.GetDataBase());
				graphicHelper.AddStrokeRendering(swatchUID);
				break;
			}
		case kFillRendering:
			{
				PMString swatchName = parameterUtils->GetPMString("Swatch name", PMString("Black"));
				UID swatchUID = graphicHelper.GetNamedSwatch(swatchName, itemList.GetDataBase());
				graphicHelper.AddFillRendering(swatchUID);
				break;
			}
		case kCornerImplementation:
			{
				K2Vector<PMString> names;
				K2Vector<ClassID> classIDs;
				names.push_back("kFancyCornerBoss");
				classIDs.push_back(kFancyCornerBoss);
				names.push_back("kBevelCornerBoss");
				classIDs.push_back(kBevelCornerBoss);	
				names.push_back("kInsetCornerBoss");
				classIDs.push_back(kInsetCornerBoss);
				names.push_back("kInverseRoundedCornerBoss");
				classIDs.push_back(kInverseRoundedCornerBoss);
				names.push_back("kRoundedCornerBoss");
				classIDs.push_back(kRoundedCornerBoss);
				int32 index  = parameterUtils->GetChoice("Choose corner effect.", names);
				graphicHelper.AddCornerImplementation(classIDs[index]);
				break;
			}
		case kCornerRadius:
			{
				PMReal cornerRadius = parameterUtils->GetPMReal("Corner radius", 12.0, 0.0, 800.0);
				graphicHelper.AddCornerRadius(cornerRadius);
				break;
			}
		case kLineImplementation:
			{
				K2Vector<PMString> names;
				K2Vector<ClassID> classIDs;
				names.push_back("kSolidPathStrokerBoss");
				classIDs.push_back(kSolidPathStrokerBoss);
				names.push_back("kCannedDotPathStrokerBoss");
				classIDs.push_back(kCannedDotPathStrokerBoss);
				names.push_back("kCannedDash3x2PathStrokerBoss");
				classIDs.push_back(kCannedDash3x2PathStrokerBoss);	
				names.push_back("kCannedDash4x4PathStrokerBoss");
				classIDs.push_back(kCannedDash4x4PathStrokerBoss);
				names.push_back("kDashedPathStrokerBoss");
				classIDs.push_back(kDashedPathStrokerBoss);
				names.push_back("none");
				classIDs.push_back(kInvalidClass);
				int32 index  = parameterUtils->GetChoice("Choose line implementation.", names);
				graphicHelper.AddLineImplementation(classIDs[index]);
				break;
			}
		case kLineEndEndImplementation:
			{
				K2Vector<PMString> names;
				K2Vector<ClassID> classIDs;
				names.push_back("kBarbedArrowHeadBoss");
				classIDs.push_back(kBarbedArrowHeadBoss);
				names.push_back("kCircleSolidArrowHeadBoss");
				classIDs.push_back(kCircleSolidArrowHeadBoss);
				names.push_back("kTriangleArrowHeadBoss");
				classIDs.push_back(kTriangleArrowHeadBoss);	
				names.push_back("none");
				classIDs.push_back(kInvalidClass);
				int32 index  = parameterUtils->GetChoice("Choose line end end implementation.", names);
				graphicHelper.AddLineEndEndImplementation(classIDs[index]);
				break;
			}
		case kJoinType:
			{
				K2Vector<PMString> names;
				names.push_back("miter");
				names.push_back("round");
				names.push_back("bevel");
				SnpGraphicHelper::JoinType joinType = (SnpGraphicHelper::JoinType)parameterUtils->GetChoice("Choose join type.", names);
				graphicHelper.AddJoinType(joinType);
				break;
			}
		case kLineCap:
			{
				K2Vector<PMString> names;
				names.push_back("butt");
				names.push_back("round");
				names.push_back("square");
				SnpGraphicHelper::LineCap lineCap = (SnpGraphicHelper::LineCap)parameterUtils->GetChoice("Choose join type.", names);
				graphicHelper.AddLineCap(lineCap);
				break;
			}
		case kDashedValues:
			{
				PMReal dash = parameterUtils->GetPMReal("Dash length in points", 8.0, 0.25, 100.0);
				if (parameterUtils->WasDialogCancelled()) {
					break;
				}
				PMReal gap = parameterUtils->GetPMReal("Gap length in points", 2.0, 0.25, 100.0);
				K2Vector<PMReal> dashAndGapValues;
				dashAndGapValues.push_back(dash);
				dashAndGapValues.push_back(gap);
				graphicHelper.AddDashedValues(dashAndGapValues);
				break;
			}
		}
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Apply the attribute.
		status = graphicHelper.ApplyAttributes();

	} while(false);
	
	return status;
}

/*
*/
void SnpManipulateGraphicAttributes::Inspect(const UIDRef& pageItemUIDRef)
{
	do {
		InterfacePtr<IGraphicStyleDescriptor> descriptor(pageItemUIDRef, UseDefaultIID());
		ASSERT(descriptor);
		if (!descriptor) {
			break;
		}
		IDataBase* db = pageItemUIDRef.GetDataBase();
		ASSERT(db);
		if (!db) {
			break;
		}

		// Report the page item's UID.
		SNIPLOG("pageItemUID=0x%x", pageItemUIDRef.GetUID().Get());
		
		// You can use IGraphicAttributeUtils helper methods to find the most common 
		// graphic attribute values. Here we inspect the stroke weight.
		PMReal strokeWeight(0.0);
		if (Utils<IGraphicAttributeUtils>()->GetStrokeWeight(strokeWeight, descriptor) == kSuccess) {
			SNIPLOG(" strokeWeight=%f", ::ToDouble(strokeWeight));
		}

		// Or if you know the ClassID of the attribute you are interested in you can 
		// examine its value without using IGraphicAttributeUtils. Below we access the
		// value of kGraphicStyleStrokeWeightAttrBoss which is the attribute the
		// IGraphicAttributeUtils code above will have looked at to find the stroke weight.
		// You have to use this technique if there is no IGraphicAttributeUtils method that
		// helps examine the attribute you are interested in.
		InterfacePtr<IGraphicAttrRealNumber> strokeWeightGraphicAttrRealNumber(static_cast<IGraphicAttrRealNumber*>
			(descriptor->QueryAttribute(kGraphicStyleStrokeWeightAttrBoss, IGraphicAttrRealNumber::kDefaultIID)));
		if (strokeWeightGraphicAttrRealNumber != nil) {
			SNIPLOG(" kGraphicStyleStrokeWeightAttrBoss value=%f",::ToDouble(strokeWeightGraphicAttrRealNumber->GetRealNumber()));
		}

		// Inspect stroke colour.
		UID strokeRenderingUID = kInvalidUID;
		if (Utils<IGraphicAttributeUtils>()->GetStrokeRenderingUID(strokeRenderingUID, descriptor) == kSuccess) {
			PMString swatchName = Utils<ISwatchUtils>()->GetSwatchName(db, strokeRenderingUID);
			SNIPLOG(" strokeRenderingUID=0x%x swatchName=%s", strokeRenderingUID.Get(), swatchName.GetPlatformString().c_str());
		}

		// Inspect fill colour.
		UID fillRenderingUID = kInvalidUID;
		if (Utils<IGraphicAttributeUtils>()->GetFillRenderingUID(fillRenderingUID, descriptor) == kSuccess) {
			PMString swatchName = Utils<ISwatchUtils>()->GetSwatchName (db, fillRenderingUID);
			SNIPLOG(" fillRenderingUID=0x%x swatchName=%s", fillRenderingUID.Get(), swatchName.GetPlatformString().c_str());
		}

		// Inspect corner effect.
		ClassID pathCornerClassID = kInvalidClass;
		if (Utils<IGraphicAttributeUtils>()->GetCornerImplementation(pathCornerClassID, descriptor) == kSuccess) {
			SNIPLOG(" pathCornerClassID=0x%x", pathCornerClassID.Get());
		}

		// Inspect corner effect radius.
		PMReal cornerRadius;
		if (Utils<IGraphicAttributeUtils>()->GetCornerRadius(cornerRadius, descriptor) == kSuccess) {
			SNIPLOG(" cornerRadius=%f", ::ToDouble(cornerRadius));
		}

		// Inspect path stroker.
		ClassID pathStrokerClassID;
		UID pathStrokerUID = kInvalidUID; // New for InDesign 3.0
		if (Utils<IGraphicAttributeUtils>()->GetLineImplementation(pathStrokerClassID, pathStrokerUID/*new*/, descriptor) == kSuccess) {
			SNIPLOG(" pathStrokerClassID=0x%x", pathStrokerClassID.Get());
		}

		// Inspect path end stroker.
		ClassID pathEndStrokerClassID = kInvalidClass;
		if (Utils<IGraphicAttributeUtils>()->GetLineEndEndImplementation(pathEndStrokerClassID, descriptor) == kSuccess) {
			SNIPLOG(" pathEndStrokerClassID=0x%x", pathEndStrokerClassID.Get());
		}

		// Inspect join type.
		int32 joinType;
		if (Utils<IGraphicAttributeUtils>()->GetJoinType(joinType, descriptor) == kSuccess) {
			SNIPLOG(" joinType=%d", joinType);
		}

		// Inspect line cap.
		int32 lineCap;
		if (Utils<IGraphicAttributeUtils>()->GetLineCap(lineCap, descriptor) == kSuccess) {
			SNIPLOG(" lineCap=%d", lineCap);
		}

		// Inspect dash.
		InterfacePtr<IDashedAttributeValues> dashedAttributeValues(static_cast<IDashedAttributeValues*>(descriptor->QueryAttribute(kDashedAttributeValuesBoss, IDashedAttributeValues::kDefaultIID)));
		if (dashedAttributeValues != nil) {
			SNIPLOG(" dashedAttributeValues");
			for (int32 i = 0; i < dashedAttributeValues->NumValues(); i++) {
				SNIPLOG("  [%d] %f", i, ::ToDouble(dashedAttributeValues->GetValue(i)));
			}
		}

	} while(false);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpManipulateGraphicAttributes available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerManipulateGraphicAttributes : public SnpRunnable
{
	public:
		// For SnippetRunner framework.

		/** Constructor.
		*/
		_SnpRunnerManipulateGraphicAttributes();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateGraphicAttributes();

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
_SnpRunnerManipulateGraphicAttributes::_SnpRunnerManipulateGraphicAttributes() : SnpRunnable("ManipulateGraphicAttributes")
{
	this->SetDescription("Applies and inspects graphic attributes of various types (stroke weight, stroke colour, fill colour etc.)");
	this->SetPreconditions("page item selected");
	this->SetCategories("sdk_snippet, sdk_graphic");
}

/* Destructor
*/
_SnpRunnerManipulateGraphicAttributes::~_SnpRunnerManipulateGraphicAttributes()
{
}

/*
*/
bool16 _SnpRunnerManipulateGraphicAttributes::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;

	// Require a layout selection to be able to run.
	InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
	if (layoutTarget != nil) {
		UIDList itemList = layoutTarget->GetUIDList(kStripStandoffs);
		if (itemList.Length() > 0) {
			result = kTrue;
		}
	}

	return result;
}

/* 
*/
ErrorCode _SnpRunnerManipulateGraphicAttributes::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do 
	{
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
		SnpManipulateGraphicAttributes instance;

		// ask for a choice of tasks
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Inspect graphic attributes", PMString::kEncodingASCII));
		choices.push_back(PMString("Apply graphic attributes", PMString::kEncodingASCII));
		enum {kInspect, kApply};
		int32 defaultChoice = kInspect;
		int32 choice  = parameterUtils->GetChoice("What do you want to do?", choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue) 
		{
			status = kCancel;
			break;
		}
		switch (choice) 
		{
		case kInspect:
			// Inspect the items.
			for (int32 i = 0; i < itemList.Length(); i++) 
			{
				instance.Inspect(itemList.GetRef(i));
			}
			status = kSuccess;
			break;
		case kApply:
			// apply attributes
			status = instance.Apply(itemList);
			break;
		}
	} while(false);
	return status;
}

/* 
*/
bool16  _SnpRunnerManipulateGraphicAttributes::CanLoad() const
{
	bool16 result = kTrue;
	if (LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)) {
		// Graphic attributes can be applied to page items under InCopy
		// but we don't load this snippet because there's no pointer tool 
		// to select a page item with. If we loaded the snippet the Go 
		// button for the snippet would mostly be disabled.
		result = kFalse;
	}
	return result;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulateGraphicAttributes instance_SnpRunnerManipulateGraphicAttributes;
DEFINE_SNIPPET(_SnpRunnerManipulateGraphicAttributes) 	
//End, SnpManipulateGraphicAttributes.cpp
