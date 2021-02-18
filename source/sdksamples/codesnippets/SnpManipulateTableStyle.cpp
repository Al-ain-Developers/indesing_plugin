//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTableStyle.cpp $
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
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ITableStylesFacade.h"
#include "ICellStylesFacade.h"
#include "ITableTarget.h"
#include "IStyleInfo.h"
#include "IStyleUtils.h"
#include "IWorkspace.h"
#include "ICellStyleSuite.h"
#include "ITableStyleSuite.h"
#include "ISelectionManager.h"
#include "ITableAttrAccessor.h"
#include "ITableAttributes.h"
#include "ITableAttrInt32.h"
#include "ITableLineType.h"
#include "ITableAttrRealNumber.h"
#include "ITableAttrUID.h"
#include "ITableAttrBool16.h"
#include "ISwatchList.h"

// General includes:
#include "TablesID.h"
#include "TabStyID.h"
#include "CelStyID.h"
#include "UIDRef.h"
#include "ILayoutUtils.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/**
	Sample code snippet that shows how to 
	<li> Create, delete, apply, and modify a cell and table styles 
	<li> Get/Set Regional cell styles in Tables Style 

	@ingroup sdk_snippet
	@ingroup sdk_table

 */
class SnpManipulateTableAndCellStyle 

{
public:
	/** 
	*/
	SnpManipulateTableAndCellStyle() {}

	/**
	*/
	virtual ~SnpManipulateTableAndCellStyle() {}

public:

	/** Creates a new table style based on the current selection.
		@param runnableContext IN our active context
		@param tableStyleSuite IN table style selection suite.
		@return kSuccess is the style is successfully created, kFailure otherwise.
	*/
	ErrorCode CreateTableStyleFromSelection(ISnpRunnableContext* runnableContext, const InterfacePtr<ITableStyleSuite>tableStyleSuite);

	/** Modify table style based on the selection.
		@param runnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ModifyTableStyle(ISnpRunnableContext* runnableContext);

	/** Apply selected table style to current selection.
		@param runnableContext IN our active context
		@param tableStyleSuite IN table style selection suite.
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ApplyTableStyleToSelection(ISnpRunnableContext* runnableContext, ITableStyleSuite *tableStyleSuite);

	/** Delete a style.
		@param iSnpRunnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode DeleteTableStyle(ISnpRunnableContext* iSnpRunnableContext);
	
	/** Creates a new cell style based on the current selection.
		@param runnableContext IN our active context
		@param cellStyleSuite IN cell style selection suite.
		@return kSuccess is the style is successfully created, kFailure otherwise.
	*/
	ErrorCode CreateCellStyleFromSelection(ISnpRunnableContext* runnableContext, const InterfacePtr<ICellStyleSuite>cellStyleSuite);

	/** Modify cell style based on the selection.
		@param runnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ModifyCellStyle(ISnpRunnableContext* runnableContext);

	/** Apply selected cell style to current selection.
		@param runnableContext IN our active context
		@param cellStyleSuite IN cell style selection suite.
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ApplyCellStyleToSelection(ISnpRunnableContext* runnableContext, ICellStyleSuite *cellStyleSuite);

	/** Delete a style.
		@param iSnpRunnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode DeleteCellStyle(ISnpRunnableContext* iSnpRunnableContext);

	/** Set regional cell style.
		@param iSnpRunnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode SetRegionalStyle(ISnpRunnableContext* iSnpRunnableContext);

	/** Get regional cell style.
		@param iSnpRunnableContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode GetRegionalStyle(ISnpRunnableContext* iSnpRunnableContext);



private:

	/** Create and Apply row stroke attributes.
		@param attrs IN/OUT AttributeBossList to add
		@return kSuccess on success, other ErrorCode on failure.
	*/
	void ApplyTableRowStrokeAttributes(AttributeBossList& attrs);

		
	/** Drives the UI that allows a user to pick a style.
		@param iSnpRunnableContext IN the active context.
		@param style OUT the selected style.
		@param action IN the verb that applies to this operation.
		@param IID_ITABLESTYLEGROUPMANAGER or IID_ICELLSTYLEGROUPMANAGER.
		@return kSuccess if a style is successfully picked.
	*/
	ErrorCode ChooseStyle(ISnpRunnableContext* iSnpRunnableContext, UIDRef& style, const char * action, PMIID styleType, UID excludedStyle = kInvalidUID);

	/** Drives the UI that allows a user to pick a region.
		@param iSnpRunnableContext IN the active context.
		@param region OUT the table attribute ClassID representing the region.
		@param regionName OUT the name of a region.
		@return kSuccess if a style is successfully picked.
	*/
	ErrorCode ChooseRegion(ISnpRunnableContext* iSnpRunnableContext, ClassID &region, ClassID &useBody, PMString& regionName);
};

/*
*/
ErrorCode SnpManipulateTableAndCellStyle::CreateTableStyleFromSelection(ISnpRunnableContext* runnableContext, const InterfacePtr<ITableStyleSuite>tableStyleSuite)
{
	ErrorCode status = kFailure;
	do 
	{
		//Get table of the selection
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		if (!tableTarget)
			break;
		UIDRef tableModel(tableTarget->GetModel());	

		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		PMString styleName = iSnipRunParameterUtils->GetPMString(PMString("Style name?"), "SnpTableStyle");
		if (iSnipRunParameterUtils->WasDialogCancelled()) {
			break;
		}

		IActiveContext* ac = runnableContext->GetActiveContext();
		IWorkspace* workspace = ac->GetContextWorkspace();

		InterfacePtr<IStyleGroupManager> styleGroupMgr(workspace, IID_ITABLESTYLEGROUPMANAGER);
		if (styleGroupMgr == nil) {
			ASSERT(kFalse);
			break;
		}

		// Find a unique name for the style.
		const IStyleGroupHierarchy* hierarchy = styleGroupMgr->GetRootHierarchy();
		if (hierarchy->FindByName(styleName) != kInvalidUID)
			Utils<IStyleUtils>()->CreateUniqueName(hierarchy, styleName);		
		SNIPLOG("New style name : %s",styleName.GetPlatformString().c_str());


		//You may use simpler method such as
		//ITableStyleSuite::CreateTableStyle() or
		//ITableStylesFacade::CreateNewTableStyle()
		//to create table style with generated unqiue style name,
		//but for demonstration purpose, we use a little bit more code.

		//Set parent to root
		InterfacePtr<IStyleGroupHierarchy> parentHier(styleGroupMgr->GetRootHierarchy(), UseDefaultIID());
 
		InterfacePtr<ITableAttrAccessor> attrAccessor(tableModel, UseDefaultIID());
		if (!attrAccessor)
			break;


		//prepare based on UID
		UID basedOnUID = attrAccessor->GetTableStyle();
		const UID basicTableStyle = styleGroupMgr->FindByName("[Basic Table]");
		if(basedOnUID == basicTableStyle)
		{
			basedOnUID = styleGroupMgr->GetRootStyleUID();
		}
		
		//Prepare table attributes list
		InterfacePtr<const ITableAttributes> tableOverrides(attrAccessor->QueryTableOverrides());
		const AttributeBossList* newAttrs = tableOverrides->GetBossList();

		//create the table style 
		UIDRef out_StyleRef;
		status = Utils<Facade::ITableStylesFacade>()->CreateTableStyle(workspace, parentHier, -1, styleName, 
						out_StyleRef, basedOnUID, newAttrs);

	} while (kFalse);

	return status;
}


/*
*/
ErrorCode SnpManipulateTableAndCellStyle::ModifyTableStyle(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {

		//Choose a table style to change
		UIDRef styleRef = kInvalidUIDRef;
		if (this->ChooseStyle(runnableContext,styleRef, "modify", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style failed");
			break;
		}

		//Get current style info
		InterfacePtr<IStyleInfo> styleInfo(styleRef, UseDefaultIID());
		if (!styleInfo)
		{
			ASSERT_MSG(styleInfo, "table style info is invalid!");
			break;
		}

		int16 modifiers = 0;
		VirtualKey shortcutKey = styleInfo->GetKeyboardShortcut(&modifiers);
		GlobalTime shortcutTime(styleInfo->GetKeyboardShortcutTimeStamp());

		//Change based on
		UIDRef basedOnRef = kInvalidUIDRef;
		if (this->ChooseStyle(runnableContext,basedOnRef, "base on", IID_ITABLESTYLEGROUPMANAGER, styleRef.GetUID()) != kSuccess)
		{
			SNIPLOG("Choose a based on table style failed");
			break;
		}

		IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();

		//Hard code to set up table row stroke
        InterfacePtr<ITableAttributes>    iStyleAttributes (styleRef, IID_ITABLEATTRIBUTES);
        const AttributeBossList*   styleAttrBossList = iStyleAttributes->GetBossList();
		AttributeBossList attrs(*styleAttrBossList);
		this->ApplyTableRowStrokeAttributes(attrs);

		//Change the style
		status = Utils<Facade::ITableStylesFacade>()->EditTableStyle(styleInfo->GetName(), &attrs, workspace, styleRef.GetUID(),
		basedOnRef.GetUID(), shortcutKey, modifiers, &shortcutTime, kFalse);
  		
	} while(false);

	return (status);
} 


/*
*/
ErrorCode SnpManipulateTableAndCellStyle::ApplyTableStyleToSelection(ISnpRunnableContext* runnableContext, ITableStyleSuite *tableStyleSuite)
{
	ErrorCode status = kFailure;
	do 
	{

		UIDRef styleToApply = kInvalidUIDRef;

		if (this->ChooseStyle(runnableContext,styleToApply, "apply", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style failed");
			break;
		}

		status = tableStyleSuite->ApplyTableStyle(styleToApply);
	} while(false);
	return (status);
}

/*
*/
ErrorCode SnpManipulateTableAndCellStyle::DeleteTableStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {

		UIDRef styleToDelete = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleToDelete, "delete", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style to delete failed");
			break;
		}

 		// now get the style to replace the deleted style with
		UIDRef styleToReplace = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleToReplace,"replace", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style to replace failed");
			break;
		}
		

		if (styleToDelete == styleToReplace){
			SNIPLOG("Replacing a style with itself?");
			break;
		}


		status =  Utils<Facade::ITableStylesFacade>()->DeleteTableStyle(styleToDelete, styleToReplace.GetUID());


	} while(false);
	return (status);
}


/*
*/
ErrorCode SnpManipulateTableAndCellStyle::CreateCellStyleFromSelection(ISnpRunnableContext* runnableContext, const InterfacePtr<ICellStyleSuite>cellStyleSuite)
{
	ErrorCode status = kFailure;
	do 
	{

		//Get table of the selection
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		if (!tableTarget)
			break;
		UIDRef tableModel(tableTarget->GetModel());	

		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		PMString styleName = iSnipRunParameterUtils->GetPMString(PMString("Cell style name?"), "SnpCellStyle");
		if (iSnipRunParameterUtils->WasDialogCancelled()) {
			break;
		}

		IActiveContext* ac = runnableContext->GetActiveContext();
		IWorkspace* workspace = ac->GetContextWorkspace();
		
		InterfacePtr<IStyleGroupManager> styleGroupMgr(workspace,IID_ICELLSTYLEGROUPMANAGER);
		if (styleGroupMgr == nil) {
			ASSERT(kFalse);
			break;
		}

		//Find a unique name for the style.
		const IStyleGroupHierarchy* hierarchy = styleGroupMgr->GetRootHierarchy();
		if (hierarchy->FindByName(styleName) != kInvalidUID)
			Utils<IStyleUtils>()->CreateUniqueName(hierarchy, styleName);		
		SNIPLOG("New style name : %s",styleName.GetPlatformString().c_str());


		//Simpler method such as ICellStyleSuite::CreateCellStyle() 
		//or ICellStylesFacade::CreateCellStyle() are available
		//to create cell style with generated unqiue style name,
		//but for demonstration purpose, we use a little bit more code.

		//Set parent to root
		InterfacePtr<IStyleGroupHierarchy> parentHier(styleGroupMgr->GetRootHierarchy(), UseDefaultIID());
 		
		//Prepare cell attributes list
		AttributeBossList cellAttributes;
        cellStyleSuite->GetLocalOverrides(cellAttributes);

		//prepare based on UID
		UID basedOnUID = kInvalidUID;
		UIDList selectedStyles(tableModel.GetDataBase());
		if(cellStyleSuite->GetSelectedCellStyles(selectedStyles) == kSuccess)
		{
           if(selectedStyles.Length() != 0)
           {
               basedOnUID = selectedStyles[0];
		   }
		}

		if(basedOnUID == kInvalidUID)
		{
			basedOnUID = styleGroupMgr->GetRootStyleUID();
		}

		//create the cell style 
		UIDRef out_StyleRef;
		status = Utils<Facade::ICellStylesFacade>()->CreateCellStyle(workspace, parentHier, -1, styleName, 
						out_StyleRef, basedOnUID, &cellAttributes);

	} while (kFalse);

	return status;
}


/*
*/
ErrorCode SnpManipulateTableAndCellStyle::ModifyCellStyle(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {

		//Choose a cell style to change
		UIDRef styleRef = kInvalidUIDRef;
		if (this->ChooseStyle(runnableContext,styleRef, "modify", IID_ICELLSTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a cell style failed");
			break;
		}

		//Get current style info
		InterfacePtr<IStyleInfo> styleInfo(styleRef, UseDefaultIID());
		if (!styleInfo)
		{
			ASSERT_MSG(styleInfo, "cell style info is invalid!");
			break;
		}

		int16 modifiers = 0;
		VirtualKey shortcutKey = styleInfo->GetKeyboardShortcut(&modifiers);
		GlobalTime shortcutTime(styleInfo->GetKeyboardShortcutTimeStamp());

		//Change based on
		UIDRef basedOnRef = kInvalidUIDRef;
		if (this->ChooseStyle(runnableContext,basedOnRef, "base on", IID_ICELLSTYLEGROUPMANAGER, styleRef.GetUID()) != kSuccess)
		{
			SNIPLOG("Choose a based on cell style failed");
			break;
		}

		IWorkspace* workspace = runnableContext->GetActiveContext()->GetContextWorkspace();
		InterfacePtr<ISwatchList> iSwatchList(workspace, IID_ISWATCHLIST);
		//Hard code to set up cell row stroke
        InterfacePtr<ITableAttributes>    iStyleAttributes (styleRef, IID_ITABLEATTRIBUTES);
        const AttributeBossList*   styleAttrBossList = iStyleAttributes->GetBossList();
		AttributeBossList attrs(*styleAttrBossList);
		ITableAttrUID* newAttr = ::CreateObject2<ITableAttrUID>(kCellAttrFillColorBoss);
		UID swatchUID = iSwatchList->GetNthSwatch(5).GetUID(); //choose a watch
		newAttr->Set(swatchUID);
		attrs.ApplyAttribute(newAttr);

		//Change the style
		status = Utils<Facade::ICellStylesFacade>()->EditCellStyle(styleInfo->GetName(), &attrs, workspace, styleRef.GetUID(),
		basedOnRef.GetUID(), shortcutKey, modifiers, &shortcutTime);
  		
	} while(false);

	return (status);
} 


/*
*/
ErrorCode SnpManipulateTableAndCellStyle::ApplyCellStyleToSelection(ISnpRunnableContext* runnableContext, ICellStyleSuite *cellStyleSuite)
{
	ErrorCode status = kFailure;
	do 
	{

		UIDRef styleToApply = kInvalidUIDRef;

		if (this->ChooseStyle(runnableContext,styleToApply, "apply", IID_ICELLSTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a cell style failed");
			break;
		}

		status = cellStyleSuite->ApplyCellStyle(styleToApply);
	} while(false);
	return (status);
}

/*
*/
ErrorCode SnpManipulateTableAndCellStyle::DeleteCellStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {

		UIDRef styleToDelete = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleToDelete, "delete", IID_ICELLSTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a cell style to delete failed");
			break;
		}

 		// now get the style to replace the deleted style with
		UIDRef styleToReplace = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleToReplace,"replace", IID_ICELLSTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a cell style to replace failed");
			break;
		}
		

		if (styleToDelete == styleToReplace){
			SNIPLOG("Replacing a style with itself?");
			break;
		}


		status =  Utils<Facade::ICellStylesFacade>()->DeleteCellStyle(styleToDelete, styleToReplace.GetUID());


	} while(false);
	return (status);
}

/*
*/
ErrorCode SnpManipulateTableAndCellStyle::GetRegionalStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {

		//Choose a table style to get regional style
		UIDRef styleRef = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleRef, "get from", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style failed");
			break;
		}


		//Get the region
		ClassID regionClass = kInvalidClass;
		ClassID useBodyClass = kInvalidClass;
		PMString name;
		if (this->ChooseRegion(iSnpRunnableContext, regionClass, useBodyClass, name) != kSuccess)
		{
			SNIPLOG("Choose a region failed");
			break;
		}
		
		//We want to check the value, local overrides is not sufficient. Get all attributes from their parent
		//InterfacePtr<ITableAttributes>    iStyleAttributes (styleRef, IID_ITABLEATTRIBUTES);
        // const AttributeBossList*   styleAttrBossList = iStyleAttributes->GetBossList();
		AttributeBossList allAttribs;
		Utils<Facade::ITableStylesFacade>()->GetTableStyleAttrsResolved(styleRef, allAttribs);
		InterfacePtr<const ITableAttrUID> regionalStyleData(static_cast<const ITableAttrUID*>( allAttribs.QueryByClassID( regionClass, IID_ITABLEATTRUID )));
		InterfacePtr<const ITableAttrBool16> useBody(static_cast<const ITableAttrBool16*>(allAttribs.QueryByClassID( useBodyClass, IID_ITABLEATTRBOOL16)));
		if(regionClass != kTableAttrBodyCellStyleBoss && useBody && useBody->Get()) //select [Same as Body Rows]
		{
			SNIPLOG("The %s regional cell style is %s", name.GetPlatformString().c_str(), "Same as Body Rows");	
		}
		else if (regionalStyleData)
		{
			UID cellStyle = regionalStyleData->Get();
			//Get cell style info
			InterfacePtr<IStyleInfo> styleInfo(styleRef.GetDataBase(),cellStyle, UseDefaultIID());
			if (!styleInfo)
			{
				ASSERT_MSG(styleInfo, "cell style info is invalid!");
				break;
			}
			//Report the cell style name
			SNIPLOG("The %s regional cell style is %s", name.GetPlatformString().c_str(), styleInfo->GetName().GetPlatformString().c_str());
		}
		status =  kSuccess;


	} while(false);
	return (status);
}

ErrorCode SnpManipulateTableAndCellStyle::SetRegionalStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {

		//Choose a table style to change
		UIDRef styleRef = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,styleRef, "change", IID_ITABLESTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a table style failed");
			break;
		}

		//Get current style infor
		InterfacePtr<IStyleInfo> styleInfo(styleRef, UseDefaultIID());
		if (!styleInfo)
		{
			ASSERT_MSG(styleInfo, "table style info is invalid!");
			break;
		}
		int16 modifiers = 0;
		VirtualKey shortcutKey = styleInfo->GetKeyboardShortcut(&modifiers);
		GlobalTime shortcutTime(styleInfo->GetKeyboardShortcutTimeStamp());
		UID basedOn= styleInfo->GetBasedOn();

		//get region
		ClassID regionClass = kInvalidClass;
		ClassID useBodyClass = kInvalidClass;
		PMString name;
		if (this->ChooseRegion(iSnpRunnableContext,regionClass, useBodyClass, name) != kSuccess)
		{
			SNIPLOG("Choose a region failed");
			break;
		}

		//Choose a cell style to change to 
		UIDRef cellStyle = kInvalidUIDRef;
		if (this->ChooseStyle(iSnpRunnableContext,cellStyle, "change to", IID_ICELLSTYLEGROUPMANAGER) != kSuccess)
		{
			SNIPLOG("Choose a cell style to change to failed");
			break;
		}

		IWorkspace* workspace = iSnpRunnableContext->GetActiveContext()->GetContextWorkspace();

        InterfacePtr<ITableAttributes>    iStyleAttributes (styleRef, IID_ITABLEATTRIBUTES);
        const AttributeBossList*   styleAttrBossList = iStyleAttributes->GetBossList();
		AttributeBossList attrs(*styleAttrBossList);
		InterfacePtr<ITableAttrUID>	attr(::CreateObject2<ITableAttrUID>(regionClass));
		attr->Set(cellStyle.GetUID());
		attrs.ApplyAttribute(attr);
        if(regionClass != kTableAttrBodyCellStyleBoss)
        {
            InterfacePtr<ITableAttrBool16> useBody(::CreateObject2<ITableAttrBool16>(useBodyClass));
            useBody->Set(kFalse);
            attrs.ApplyAttribute(useBody);
		}

		//Change the style
		status = Utils<Facade::ITableStylesFacade>()->EditTableStyle(styleInfo->GetName(), &attrs, workspace, styleRef.GetUID(),
		basedOn, shortcutKey, modifiers, &shortcutTime, kFalse);

	} while(false);
	return (status);
}

/** Manually apply row stroke attributes
*/
void SnpManipulateTableAndCellStyle::ApplyTableRowStrokeAttributes(AttributeBossList& attrs)
{
    const int32 kFirstCount= 2;
    const int32 kSecondCount = 1;

    const ITableLineType::SType kFirstType     = ITableLineType::SType(kThickThinPathStrokerBoss, kInvalidUID);
    const ITableLineType::SType kSecondType = ITableLineType::SType(kThickThinThickPathStrokerBoss, kInvalidUID);

    const PMReal kFirstWeight = 2;
    const PMReal kSecondWeight = 4;

    // First
    InterfacePtr<ITableAttrInt32> firstCount(CreateObject2<ITableAttrInt32>(kTableAttrRowStrokePatternFirstCountBoss));
    InterfacePtr<ITableLineType> firstType(CreateObject2<ITableLineType>(kTableAttrRowStrokePatternFirstTypeBoss));
    InterfacePtr<ITableAttrRealNumber> firstWeight(CreateObject2<ITableAttrRealNumber>(kTableAttrRowStrokePatternFirstWeightBoss));

    firstCount->Set(kFirstCount);
    firstType->Set(kFirstType);
    firstWeight->Set(kFirstWeight);

    attrs.ApplyAttribute(firstCount);
    attrs.ApplyAttribute(firstType);
    attrs.ApplyAttribute(firstWeight);

    // Second
    InterfacePtr<ITableAttrInt32> secondCount(CreateObject2<ITableAttrInt32>(kTableAttrRowStrokePatternSecondCountBoss));
    InterfacePtr<ITableLineType> secondType(CreateObject2<ITableLineType>(kTableAttrRowStrokePatternSecondTypeBoss));
    InterfacePtr<ITableAttrRealNumber> secondWeight(CreateObject2<ITableAttrRealNumber>(kTableAttrRowStrokePatternFirstWeightBoss));

    secondCount->Set(kSecondCount);
    secondType->Set(kSecondType);
    secondWeight->Set(kSecondWeight);

    attrs.ApplyAttribute(secondCount);
    attrs.ApplyAttribute(secondType);
    attrs.ApplyAttribute(secondWeight);
}

/*
*/
ErrorCode  SnpManipulateTableAndCellStyle::ChooseStyle(ISnpRunnableContext* iSnpRunnableContext, UIDRef& style, const char * action, PMIID styleType, UID excludedStyle)
{
	ErrorCode status = kFailure;
	do {
		IWorkspace* iWorkspace = iSnpRunnableContext->GetActiveContext()->GetContextWorkspace();
		if (iWorkspace == nil) { 
			ASSERT(kFalse);
			break;
		}

		IDataBase* iDataBase = ::GetDataBase(iWorkspace);
		if (iDataBase == nil){
			ASSERT(kFalse);
			break;
		}

		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}
		InterfacePtr<IStyleGroupManager> styleGroupMgr(iWorkspace,styleType);
		if (styleGroupMgr == nil) {
			ASSERT(styleGroupMgr);
			break;
		}
	
		// Determine the number of styles registered with the name table
		UIDList styleUIDList(::GetDataBase(styleGroupMgr));
		styleGroupMgr->GetRootHierarchy()->GetDescendents(&styleUIDList,IID_ISTYLEINFO);

		int32 numOfStyles = styleUIDList.Length();

		K2Vector<PMString> styleList;
		for (int32 loop=0; loop<numOfStyles; loop++){
			UID currentStyle = styleUIDList[loop];
			if(currentStyle != excludedStyle)
			{
				InterfacePtr<IStyleGroupHierarchy> styleHier(iDataBase, styleUIDList[loop],UseDefaultIID());
				styleList.push_back(styleHier->GetFullPath());
			}
		}

		PMString typeString;
		if (styleType == IID_ITABLESTYLEGROUPMANAGER)
			typeString = "table";
		else if (styleType == IID_ICELLSTYLEGROUPMANAGER)
			typeString = "cell";

		// general purpose buffer to create the prompts
		char buffer[200];
		sprintf(buffer,"Please choose which %s style to %s?",typeString.GetPlatformString().c_str(), action);
		int32 response = iSnipRunParameterUtils->GetChoice(buffer, styleList);

		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		style = styleUIDList.GetRef(response);
		status = kSuccess;
	}while (kFalse);
	return status;
}

/*
*/
ErrorCode  SnpManipulateTableAndCellStyle::ChooseRegion(ISnpRunnableContext* iSnpRunnableContext, ClassID &region, ClassID &useBody, PMString& regionName)
{
	ErrorCode status = kFailure;
	do {

		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}

		K2Vector<PMString> regionList;
		regionList.push_back(PMString("Header rows"));
		regionList.push_back(PMString("Footer rows"));
		regionList.push_back(PMString("Left column"));
		regionList.push_back(PMString("Right column"));
		regionList.push_back(PMString("Body rows"));

		enum {kHeader, kFooter, kLeft, kRight, kBody};
		int32 response = iSnipRunParameterUtils->GetChoice("Please choose a region?", regionList);

		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		switch(response)
		{
		case kHeader:
			region = kTableAttrHeaderCellStyleBoss;
			useBody = kTableAttrHeaderUseBodyCellStyleBoss;
			regionName = "header rows";
			break;
		case kFooter:
			region = kTableAttrFooterCellStyleBoss;
			useBody = kTableAttrFooterUseBodyCellStyleBoss;
			regionName = "footer rows";
			break;
		case kLeft:
			region = kTableAttrLeftColCellStyleBoss;
			useBody = kTableAttrLeftColUseBodyCellStyleBoss;
			regionName = "left column";
			break;
		case kRight:
			region = kTableAttrRightColCellStyleBoss;
			useBody = kTableAttrRightColUseBodyCellStyleBoss;
			regionName = "right column";
			break;
		case kBody:
			region = kTableAttrBodyCellStyleBoss;
			useBody = kInvalidClass;
			regionName = "body rows";
			break;
		}

		status = kSuccess;
	}while (kFalse);

	return status;
}
// --------------------------------- For SnippetRunner framework ---------------------------------------------------

class _SnpRunnerManipulateTableAndCellStyle : public SnpRunnable
{

public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		_SnpRunnerManipulateTableAndCellStyle();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateTableAndCellStyle();

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
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}

};
/* Constructor
*/
_SnpRunnerManipulateTableAndCellStyle::_SnpRunnerManipulateTableAndCellStyle() : SnpRunnable("ManipulateTableAndCellStyle")
{
	this->SetDescription("manipulates table and cell styles");
	this->SetPreconditions("some operations require table (or cell) selection, others have no requirements");
	this->SetCategories("sdk_snippet, sdk_table");
}

/* Destructor
*/
_SnpRunnerManipulateTableAndCellStyle::~_SnpRunnerManipulateTableAndCellStyle()
{
}

/* Always enabled.
*/
bool16 _SnpRunnerManipulateTableAndCellStyle::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kTrue;
	return result;
}


ErrorCode _SnpRunnerManipulateTableAndCellStyle::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTableAndCellStyle instance;

		IActiveContext* ac = runnableContext->GetActiveContext();
		ISelectionManager* selMgr = ac->GetContextSelection();
		InterfacePtr<ICellStyleSuite> cellStyleSuite(static_cast<ICellStyleSuite*>(selMgr->QueryIntegratorSuite(IID_ICELLSTYLESUITE, ISelectionManager::kEnabledInterface)));
		InterfacePtr<ITableStyleSuite> tableStyleSuite(static_cast<ITableStyleSuite*>(selMgr->QueryIntegratorSuite(IID_ITABLESTYLESUITE, ISelectionManager::kEnabledInterface)));

		// Get the operation to be performed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Create new table style from selection"));
		choices.push_back(PMString("Modify a table style"));
		choices.push_back(PMString("Apply table style to current selection"));
		choices.push_back(PMString("Delete a table Style"));
		choices.push_back(PMString("Create new cell style from selection"));
		choices.push_back(PMString("Modify a cell Style"));
		choices.push_back(PMString("Apply cell style to selection"));
		choices.push_back(PMString("Delete a cell style"));
		choices.push_back(PMString("Get regional style"));
		choices.push_back(PMString("Set regional style"));

		enum {kNewTableStyle, kModifyTableStyle, kApplyTableStyle, kDeleteTableStyle, 
			  kNewCellStyle, kModifyCellStyle, kApplyCellStyle, kDeleteCellStyle, 
		      kGetRegionalStyle, kSetRegionalStyle};

		int32 choice  = parameterUtils->GetChoice("Which operation?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		switch (choice) 
		{
			case kNewTableStyle:
			{
				if (tableStyleSuite && tableStyleSuite->CanCreateTableStyle())
				{
					status = instance.CreateTableStyleFromSelection(runnableContext, tableStyleSuite);
				}
				else
				{
					SNIPLOG("You do not have any table selection - please select a table first.");
				}
				break;
			}

			case kNewCellStyle:
			{
				if (cellStyleSuite && cellStyleSuite->CanCreateCellStyle())
				{
					status = instance.CreateCellStyleFromSelection(runnableContext, cellStyleSuite);
				}
				else
				{
					SNIPLOG("You do not have any cell selection - please select a cell first.");
				}
				break;
			}

			case kModifyTableStyle:
			{  // This operation do not need selection
				status = instance.ModifyTableStyle(runnableContext);
				break;
			}

			case kModifyCellStyle:
			{  // This operation do not need selection
				status = instance.ModifyCellStyle(runnableContext);
				break;
			}

			case kApplyTableStyle:
			{
				if (tableStyleSuite && tableStyleSuite->CanApplyTableStyle())
				{
					status = instance.ApplyTableStyleToSelection(runnableContext, tableStyleSuite);
				}
				else
				{
					SNIPLOG("You do not have any table selection - please select a table first.");
				}
				break;
			}

			case kApplyCellStyle:
			{
				if (cellStyleSuite && cellStyleSuite->CanApplyCellStyle())
				{
					status = instance.ApplyCellStyleToSelection(runnableContext, cellStyleSuite);
				}
				else
				{
					SNIPLOG("You do not have any cell selection - please select a cell first.");
				}
				break;
			}

			case kDeleteTableStyle:
			{  // This operation do not need selection
				status = instance.DeleteTableStyle(runnableContext);
				break;
			}

			case kDeleteCellStyle:
			{  // This operation do not need selection
				status = instance.DeleteCellStyle(runnableContext);
				break;
			}
			case kGetRegionalStyle:
			{
				status = instance.GetRegionalStyle(runnableContext);
				break;
			}
			case kSetRegionalStyle:
			{
				status = instance.SetRegionalStyle(runnableContext);
				break;
			}
			
			default:
			{
				SNIPLOG("Invalid option. Skipping.");
				break;
			}
		}

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerManipulateTableAndCellStyle instance_SnpRunnerManipulateTableAndCellStyle;
DEFINE_SNIPPET(_SnpRunnerManipulateTableAndCellStyle) 	

