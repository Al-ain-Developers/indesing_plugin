//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulateTextStyle.cpp $
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
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ITextModel.h"
#include "ITextFocus.h"
#include "IStyleUnpacker.h"
#include "IAttributeStrand.h"
#include "IStyleInfo.h"
#include "ITextAttributes.h"
#include "ITextAttributeSuite.h"
#include "ITextTarget.h"
#include "IWorkspace.h"
#include "IDocument.h"
#include "IUIDData.h"
#include "IApplyStyleData.h"
#include "IStyleUtils.h"
#include "IStyleGroupHierarchy.h"

// General includes:
#include "CmdUtils.h"
#include "PreferenceUtils.h"

// Framework includes:
#include "SnipRunID.h"
#include "ISnpRunnableContext.h"
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/**
	Sample code snippet that shows how to create a new paragraph style, 
	based on the text attributes of a text selection.
 
	@ingroup sdk_snippet
	@ingroup sdk_text

 */
class SnpManipulateTextStyle 

{
public:
	/** 
	*/
	SnpManipulateTextStyle() {}

	/**
	*/
	virtual ~SnpManipulateTextStyle() {}

private:
	/** Creates a new paragraph or character style.
	    @param name IN style name, should not clash with an existing name.
		@param iWorkspace IN the workspace to which the new style is added.
		@param attribs IN the attributes to be applied to the new style.
		@param styleType IN IID identifying the name table to which the 
		          style applies (we only support char and para styles here).
		@param basedOn IN style the new style is to be based on.
		@return kSuccess is the style is successfully created, kFailure otherwise.
	*/
	ErrorCode CreateStyle(const PMString& name, const IWorkspace* iWorkspace, const AttributeBossList& attribs, const PMIID styleType, const UID basedOn = kInvalidUID);


	/** Apply a specific  style to the text selection.

		@param styleToApply IN the style to apply
		@param attributeSuite the suite that is used to apply the style
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ApplyStyle(const UID styleToApply, ITextAttributeSuite* attributeSuite);

	/** Delete a specific style.

		@param styleToDelete IN the style to be deleted
		@param iWorkspace IN workspace to be deleted from
		@param replaceStyle IN the style to replace the deleted style
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode DeleteStyle(const UID styleToDelete, IWorkspace* iWorkspace, const UID replaceStyle = kInvalidUID);

	/** Creates a new paragraph or character style, based on the current selection.
	    @param name IN style name, name of the new style should not clash with an existing name.
		@param iTextFocus IN the text focus used to create the new style.
		@param iActiveContext IN our current context.
		@param styleType IN IID identifying the name table to which the 
		          style applies (we only support char and para styles here).
		@return kSuccess is the style is successfully created, kFailure otherwise.
	*/
	ErrorCode CreateStyleFromSelection(PMString& name, const InterfacePtr<ITextFocus> iTextFocus, IActiveContext* activeContext, const PMIID styleType);

public:

	/** Creates a new paragraph or character style, based on the current selection.
		@param iTextFocus IN the text focus used to create the new style.
		@param activeContext IN our current context.
		@return kSuccess is the style is successfully created, kFailure otherwise.
	*/
	ErrorCode CreateStyleFromSelection(const InterfacePtr<ITextFocus> iTextFocus, IActiveContext* activeContext);
	
	/** apply a style to the selection.

		@param activeContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode ApplyStyle(ISnpRunnableContext* iSnpRunnableContext);


	/** update a paragraph style based on the selection.

		@param textFocus describing text on which style is to be based
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode UpdateParaStyle(const InterfacePtr<ITextFocus> textFocus, IActiveContext* activeContext);

	/** Set the paragraph style of the current text selection as default.

		@param textFocus describing text on which style is to be based
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode SetDefaultParaStyle(const InterfacePtr<ITextFocus> textFocus, IActiveContext* activeContext);

	/** Delete a style.

		@param activeContext IN our active context
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode DeleteStyle(ISnpRunnableContext* iSnpRunnableContext);

	/** Drives the UI that allows a user to pick a style
		@param iSnpRunnableContext IN the active context
		@param style OUT the selected style
		@param action IN the verb that applies to this operation
		@param styleType IN if nil, allows user to choose between para or char style. If non-nil either identifies whether the user should
				only be asked to choose between char/para styles, or if set to kInvalidInterfaceID, will return the type of style chosen.
		@return kSuccess if a style is successfully picked
	*/
	ErrorCode ChooseStyle(ISnpRunnableContext* iSnpRunnableContext, UID& style, const char * action, PMIID* styleType = nil);

};

/*
*/
ErrorCode 
SnpManipulateTextStyle::CreateStyle(const PMString& name, const IWorkspace* iWorkspace, const AttributeBossList& attribs, const PMIID styleType, const UID basedOn){
	ErrorCode status = kFailure;
	do {
		ClassID styleCmd = styleType == IID_IPARASTYLEGROUPMANAGER ? kCreateParaStyleCmdBoss : kCreateCharStyleCmdBoss;
		InterfacePtr<ICommand> iCommandNewStyle(CmdUtils::CreateCommand(styleCmd));
		if(iCommandNewStyle == nil) {
			ASSERT(kFalse);
			break;
		}

		InterfacePtr<IStyleInfo> iStyleInfo(iCommandNewStyle, UseDefaultIID());
		if(iStyleInfo == nil) {
			ASSERT(kFalse);
			break;
		}
		iCommandNewStyle->SetItemList(UIDList(iWorkspace));
		
		// Populate the fields for the data-carrying interface
		iStyleInfo->SetBasedOn(basedOn);
		iStyleInfo->SetNextStyle(kInvalidUID);
		iStyleInfo->SetName(name);	// Default not translatable
        iStyleInfo->SetStyleType(styleType == IID_IPARASTYLEGROUPMANAGER ? IStyleInfo::kParagraphStyle : IStyleInfo::kCharacterStyle);
		iStyleInfo->SetIsStyleImported(kFalse);
		
		// Need to set the text attributes that specify this style
		InterfacePtr<ITextAttributes> iTextAttributes(iCommandNewStyle, UseDefaultIID());
		if(iTextAttributes == nil) {
			ASSERT(kFalse);
			break;
		}
		iTextAttributes->ClearAllOverrides();
		iTextAttributes->ApplyAttributes(&attribs);

		// now process the command
		status = CmdUtils::ProcessCommand(iCommandNewStyle);	
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpManipulateTextStyle::CreateStyleFromSelection(const InterfacePtr<ITextFocus> iTextFocus, IActiveContext* activeContext)
{
	ErrorCode status = kFalse;
	do 
	{
		Utils<ISnipRunParameterUtils> iSnipRunParameterUtils;
		if (iSnipRunParameterUtils == nil){
			ASSERT(iSnipRunParameterUtils);
			break;
		}
		K2Vector<PMString> choices;
		choices.push_back(PMString("Create Para Style"));
		choices.push_back(PMString("Create Char Style"));

		enum {kCreateParaStyle, kCreateCharStyle};

		int32 choice  = iSnipRunParameterUtils->GetChoice("Paragraph or character style?", choices);
		if (iSnipRunParameterUtils->WasDialogCancelled()) {
			break;
		}
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		PMString styleName = iSnipRunParameterUtils->GetPMString(PMString("Style name?"));
		if (iSnipRunParameterUtils->WasDialogCancelled()) {
			break;
		}

		status = this->CreateStyleFromSelection(styleName, iTextFocus, activeContext, choice == kCreateParaStyle ? IID_IPARASTYLEGROUPMANAGER: IID_ICHARSTYLEGROUPMANAGER);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpManipulateTextStyle::CreateStyleFromSelection(PMString& name, const InterfacePtr<ITextFocus> iTextFocus, IActiveContext* activeContext, const PMIID styleType){
	ErrorCode status = kFailure;
	do {
		// Find a name for the style.
		InterfacePtr<IStyleGroupManager> styleGroupMgr(static_cast<IStyleGroupManager*>(::QueryPreferences(styleType, activeContext)));
		if (styleGroupMgr == nil) {
			ASSERT(kFalse);
			break;
		}

		Utils<IStyleUtils>()->CreateUniqueName(styleGroupMgr->GetRootHierarchy(), name);		

		SNIPLOG("New style name : %s",name.GetPlatformString().c_str());

		TextIndex focusStart = iTextFocus->GetStart(nil);
		int32 focusRange = iTextFocus->Length();
		InterfacePtr<ITextModel> iTextModel(iTextFocus->QueryModel());
		if(iTextModel == nil) {
			ASSERT(kFalse);
			break;
		}
		// get both attribute strands
		InterfacePtr<IAttributeStrand> iParaAttributeStrand(static_cast<IAttributeStrand* >(
												iTextModel->QueryStrand(kParaAttrStrandBoss, 
												IID_IATTRIBUTESTRAND)));
		if (iParaAttributeStrand == nil) {
			ASSERT(kFalse);
			break;
		}

		InterfacePtr<IAttributeStrand> iCharAttributeStrand(static_cast<IAttributeStrand* >(
											iTextModel->QueryStrand(kCharAttrStrandBoss, 
											IID_IATTRIBUTESTRAND)));
		if(iCharAttributeStrand == nil) {
			ASSERT(kFalse);
			break;
		}

		// the attribute boss list we collect the appropriate attributes onto...
		boost::shared_ptr<AttributeBossList> attrBossList(new AttributeBossList());

		if (styleType == IID_IPARASTYLEGROUPMANAGER) {
			// if we are dealing with a paragraph style, get the local para overrides
			const DataWrapper<AttributeBossList> paraListOverrides =  iParaAttributeStrand->GetLocalOverrides(focusStart,&focusRange);
			if ((paraListOverrides != nil) && (*paraListOverrides).CountBosses() > 0) {
				attrBossList->ApplyAttributes(paraListOverrides);
			}
			
			// pull in any attributes defined on the character attribute strand
			UID charStyleUID = iCharAttributeStrand->GetStyleUID(focusStart, &focusRange);	
			// Collect a complete list of style attributes from the character style, if applicable  
			if (charStyleUID != kInvalidUID)
			{
				IDataBase* iDataBase = ::GetDataBase(styleGroupMgr);
				if(iDataBase == nil) {
					ASSERT(iDataBase);
					break;
				}
				InterfacePtr<IStyleUnpacker> iStyleUnpacker(iDataBase, iDataBase->GetRootUID(),UseDefaultIID());
				if (iStyleUnpacker != nil)
				{
					K2::scoped_ptr<AttributeBossList> charStyleAttrs(iStyleUnpacker->CreateUnpackedStyle(charStyleUID));
					if (charStyleAttrs && charStyleAttrs->CountBosses() > 0) {
						attrBossList->ApplyAttributes(charStyleAttrs.get());
					}
				}
			}
		}

		// at this point, if we are creating a character style, we have nothing in out AttributeBossList
		// if we are creating a paragraph style, we have the local paragraph overrides and the attributes
		// from any existing character style. 
		// In either case, we need to add the local character attribute overrides 
		

		// Get the local overrides from the text selected.
		const DataWrapper<AttributeBossList> charListOverrides =  iCharAttributeStrand->GetLocalOverrides(focusStart,&focusRange);
		if ((charListOverrides != nil) && (*charListOverrides).CountBosses() > 0) {
			attrBossList->ApplyAttributes(charListOverrides);
		}

		UID basedOnStyle = styleType == IID_IPARASTYLEGROUPMANAGER ? iParaAttributeStrand->GetStyleUID(focusStart,&focusRange) :
											iCharAttributeStrand->GetStyleUID(focusStart,&focusRange);
		IWorkspace* iWorkspace = activeContext->GetContextWorkspace();
		status =  this->CreateStyle(name, iWorkspace,*attrBossList.get(),styleType, basedOnStyle);
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode  SnpManipulateTextStyle::ChooseStyle(ISnpRunnableContext* iSnpRunnableContext, UID& style, const char * action, PMIID* styleType)
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
		// general purpose buffer to create the prompts
		char buffer[200];
		PMIID localStyleType = kInvalidInterfaceID;
		// if the caller is interested in all styles...
		if (styleType == nil || *styleType == kInvalidInterfaceID)
		{
			K2Vector<PMString> paraOrChar;
			paraOrChar.push_back(PMString("Paragraph"));
			paraOrChar.push_back(PMString("Character"));
			enum {kParaStyle, kCharStyle};
			sprintf(buffer,"What style type to %s?",action);
			int32 response = iSnipRunParameterUtils->GetChoice(buffer, paraOrChar);

			if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
				break;
			}
			bool16	applyPara = (response == kParaStyle);
			localStyleType = applyPara ? IID_IPARASTYLEGROUPMANAGER: IID_ICHARSTYLEGROUPMANAGER;

			if (styleType != nil)
			{
				*styleType = localStyleType;
			}
		}
		else 
		{
			localStyleType = *styleType;
		}
	
		InterfacePtr<IStyleGroupManager> styleGroupMgr(iWorkspace,localStyleType);
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
//			InterfacePtr<IStyleInfo> iStyleInfo(iDataBase, styleUIDList[loop],UseDefaultIID());
			InterfacePtr<IStyleGroupHierarchy> styleHier(iDataBase, styleUIDList[loop],UseDefaultIID());
			PMString name (styleHier->GetFullPath());
			name.Translate();
			styleList.push_back(name);
//			styleList.push_back(iStyleInfo->GetName());
		}

		sprintf(buffer,"What style to %s?",action);
		int32 response2 = iSnipRunParameterUtils->GetChoice(buffer, styleList);

		if (iSnipRunParameterUtils->WasDialogCancelled() == kTrue) {
			break;
		}

		style = styleUIDList[response2];
		status = kSuccess;
	}while (kFalse);
	return status;
}


/*
*/
ErrorCode SnpManipulateTextStyle::ApplyStyle(const UID styleToApply, ITextAttributeSuite* iTextAttributeSuite)
{
	ErrorCode status = kFailure;
	do {

		if (iTextAttributeSuite == nil)
		{
			ASSERT_FAIL("suite invalid");
			break;
		}

		if (!iTextAttributeSuite->CanApplyAttributes())
		{
			SNIPLOG("Can't apply attributes.");
			break;
		}
		// apply the style. 
		status = iTextAttributeSuite->ApplyStyle(styleToApply);
		ASSERT_MSG(status == kSuccess, "ApplyParaStyle failed!");

	} while(false);
	return status;
} 


/*
*/
ErrorCode SnpManipulateTextStyle::ApplyStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do 
	{

		UID styleToApply = kInvalidUID;

		if (this->ChooseStyle(iSnpRunnableContext,styleToApply, "apply") != kSuccess)
		{
			SNIPLOG("Style choice failed");
			break;
		}

		InterfacePtr<ITextAttributeSuite> iTextAttributeSuite(iSnpRunnableContext, UseDefaultIID());
		if (iTextAttributeSuite == nil)
		{
			SNIPLOG("You do not have a text attribute suite.");
			break;
		}		
		status = this->ApplyStyle(styleToApply,iTextAttributeSuite);
	} while(false);
	return (status);
}


/*
*/
ErrorCode SnpManipulateTextStyle::UpdateParaStyle(const InterfacePtr<ITextFocus> textFocus, IActiveContext* activeContext)
{
	ErrorCode status = kFailure;
	do {
		TextIndex start,end;
		RangeData currentRange = textFocus->GetCurrentRange();
		start = currentRange.Start(nil);
		end = currentRange.End();
		int32 len = end-start;
		// let us get the text model for the text under this text focus.
		InterfacePtr<ITextModel> iTextModel(textFocus->QueryModel());
		if(iTextModel == nil)
			break;		

		// and retrieve the paragraph attribute strand
		InterfacePtr<IAttributeStrand> ipastrand((IAttributeStrand *)(
			iTextModel->QueryStrand(kParaAttrStrandBoss, 
			IID_IATTRIBUTESTRAND)));
		if (ipastrand == nil)
			break;		

		InterfacePtr<IAttributeStrand> icastrand((IAttributeStrand *)(
			iTextModel->QueryStrand(kCharAttrStrandBoss, 
			IID_IATTRIBUTESTRAND)));
		if (icastrand == nil)
			break;		

		int32 count; // number of chars from start that have this style
		// let's see what style applies to this bit of text
		UID parastyle = ipastrand->GetStyleUID(start,&count);
		IWorkspace * theWS = activeContext->GetContextWorkspace();
		if (theWS == nil)
			break;		

		InterfacePtr<IStyleGroupManager> styleNameTable(theWS,IID_IPARASTYLEGROUPMANAGER);
		if (styleNameTable == nil)
			break;		
		if (parastyle == styleNameTable->GetRootStyleUID()) // we do not want to update the root style
			break;

		const DataWrapper<AttributeBossList> paraOverride = ipastrand->GetLocalOverrides(start,nil);
		const AttributeBossList* paraList = paraOverride;
		const DataWrapper<AttributeBossList> charOverride = icastrand->GetLocalOverrides(start,nil);
		const AttributeBossList * charList = charOverride;
		
		// Create an ITextAttributes Interface:
		InterfacePtr<ITextAttributes> origAttrs(::GetDataBase(theWS), parastyle, IID_ITEXTATTRIBUTES);
		if (origAttrs == nil)
			break;
		 
		// apply overrides and original set of attrs:
		// the ordering of this is importand, if an attribute overrides the one set in the style, we should
		// choose the override, so we start with the list of current attributes in the style...	
		const AttributeBossList* originalListofAttrs = origAttrs->GetBossList();
		AddAttributeList addAttrList(new AttributeBossList);
		
		// apply the original attributes that were being applied to the style
		addAttrList->ApplyAttributes(originalListofAttrs);
		// apply the overrides from the paragraph strand
		addAttrList->ApplyAttributes(paraList);
		// apply the overrides from the character attribute strand
		addAttrList->ApplyAttributes(charList);
		
		// Create an IStyleInfo Interface:
		InterfacePtr<IStyleInfo> origStyle(::GetDataBase(theWS), parastyle, IID_ISTYLEINFO);
		if (origStyle == nil)
			break;

		RemoveAttributeList removeAttrList;
		// Create an EditTextStyleCmd:
		InterfacePtr<ICommand> styleCmd(Utils<IStyleUtils>()->CreateEditStyleCmd(origStyle, addAttrList, removeAttrList));
		if (styleCmd == nil)
			break;

		if ((status = CmdUtils::ProcessCommand(styleCmd)) != kSuccess)
			break;

		// now the overrides are part of the style, we can clear them out now..
		TextIndex newstart = start;
		int32 newlen = len;
		// get correct paragraph boundaries
		UID style = ipastrand->GetStyleUID(start, nil, &newstart); // get the start of the paragraph
		int32 endofrange = ::maximum(int32(start + len - 1), int32(0));
		style = ipastrand->GetStyleUID(endofrange, &newlen, nil);
		newlen += (len - 1);
		newlen += (start - newstart);

		//clear attribute boss list from range
		status = iTextModel->ClearOverrides(newstart, newlen, paraList, kParaAttrStrandBoss); 
		if (status != kSuccess)
			break;

		status = iTextModel->ClearOverrides(newstart, newlen, charList, kCharAttrStrandBoss);
  		if (status != kSuccess)
			break;
  		
	} while(false);

	return (status);
} 

ErrorCode SnpManipulateTextStyle::SetDefaultParaStyle(const InterfacePtr<ITextFocus> textFocus, IActiveContext* activeContext)
{
	ErrorCode status = kFailure;
	do {
		TextIndex start,end;
		int32 count; // number of chars from start that have this style
		RangeData currentRange = textFocus->GetCurrentRange();
		start = currentRange.Start(nil);
		end = currentRange.End();
		// get the coressponding text model
		InterfacePtr<ITextModel> iTextModel(textFocus->QueryModel());
		if(iTextModel == nil)
			break;		

		// get the paragraph attribute strand
		InterfacePtr<IAttributeStrand> ipastrand((IAttributeStrand *)(
			iTextModel->QueryStrand(kParaAttrStrandBoss, 
			IID_IATTRIBUTESTRAND)));
		if (ipastrand == nil)
			break;		

		// get the paragraph style that is applied at this 
		UID parastyle = ipastrand->GetStyleUID(start,&count);
		// Get the workspace we are dealing with
		IWorkspace* theWS = activeContext->GetContextWorkspace();
		if (theWS == nil)
			break;		

		// create the command
		InterfacePtr<ICommand> defaultStyleCmd(CmdUtils::CreateCommand(kDefaultTextStyleCmdBoss));
		if (defaultStyleCmd == nil)
			break;		

		// point the command at the current workspace
		defaultStyleCmd->SetItemList(UIDList(::GetUIDRef(theWS)));
		InterfacePtr<IApplyStyleData> data(defaultStyleCmd, IID_IAPPLYSTYLEDATA);
		if (data == nil)
			break;		

		// point the command at the style (and indicate it is a paragraph style)
		data->Set(kParaAttrStrandBoss, parastyle, AttributeBossList::kNil_shared_ptr);
		// if we get this far, the eventual error code depends on the status returned by the command
		status = CmdUtils::ProcessCommand(defaultStyleCmd);
	} while(false);
	return (status);
} 

/*
*/
ErrorCode SnpManipulateTextStyle::DeleteStyle(ISnpRunnableContext* iSnpRunnableContext)
{
	ErrorCode status = kFailure;
	do {
		IWorkspace* iWorkspace = iSnpRunnableContext->GetActiveContext()->GetContextWorkspace();
		if (iWorkspace == nil) { 
			ASSERT(kFalse);
			break;
		}

		UID styleToDelete = kInvalidUID;
		PMIID styleType = kInvalidInterfaceID;
		
		if (this->ChooseStyle(iSnpRunnableContext,styleToDelete,"delete", &styleType) != kSuccess)
		{
			SNIPLOG("Style choice failed");
			break;
		}


		InterfacePtr<IStyleGroupManager> styleGroupMgr(iWorkspace,styleType);
		if (styleGroupMgr == nil) {
			ASSERT(styleGroupMgr);
			break;
		}

		// deleting the root style is illegal. Bad things happen.
        if (styleToDelete == styleGroupMgr->GetRootStyleUID()){
			SNIPLOG("Cannot delete root style");
			break;
		}

		IDataBase* iDataBase = ::GetDataBase(iWorkspace);
		if (iDataBase == nil){
			ASSERT(kFalse);
			break;
		}

		// deleting the basic paragraph style is also a bad thing.
		InterfacePtr<IStyleInfo> iStyleInfo(iDataBase, styleToDelete, UseDefaultIID());
		PMString nameToDelete(iStyleInfo->GetName());
		if (nameToDelete == "NormalParagraphStyle"){
			SNIPLOG("Cannot delete default paragraph style");
			break;
		}
	
		// now get the style to replace the deleted style with
		UID styleToReplace;
		if (this->ChooseStyle(iSnpRunnableContext,styleToReplace,"replace", &styleType) != kSuccess)
		{
			SNIPLOG("Style choice failed");
			break;
		}
		

		if (styleToDelete == styleToReplace){
			SNIPLOG("Replacing a style with itself?");
			break;
		}


		status = this->DeleteStyle(styleToDelete,iWorkspace,styleToReplace);
	} while(false);
	return (status);
}


ErrorCode SnpManipulateTextStyle::DeleteStyle(const UID styleToDelete, IWorkspace* iWorkspace, const UID replaceStyle){
	ErrorCode status = kFailure;
	do {
		IDataBase* iDataBase = ::GetDataBase(iWorkspace);
		if (iDataBase == nil){
			ASSERT(kFalse);
			break;
		}

		InterfacePtr<IStyleInfo> iStyleInfo(iDataBase, styleToDelete,UseDefaultIID());

		// Create a command to delete the style.
		ClassID	styleID;
		// if (iStyleInfo->IsParagraphStyle())
		ASSERT(iStyleInfo->GetStyleType() == IStyleInfo::kParagraphStyle || iStyleInfo->GetStyleType() == IStyleInfo::kCharacterStyle);
	
        if (iStyleInfo->GetStyleType() == IStyleInfo::kParagraphStyle)
			styleID = kDeleteParaStyleCmdBoss;
		else
			styleID = kDeleteCharStyleCmdBoss;
		InterfacePtr<ICommand> iDeleteStyleCmd(CmdUtils::CreateCommand(styleID));
		if (iDeleteStyleCmd == nil) {
			ASSERT(kFalse);
			break;
		}

		// Set the ItemList to point at this workspace
		iDeleteStyleCmd->SetItemList(UIDList(iWorkspace));

		// Get an IUIDData Interface for the command:
		InterfacePtr<IUIDData> uidData(iDeleteStyleCmd, UseDefaultIID());
		if (uidData == nil) {
			ASSERT(kFalse);
			break;
		}

		// Set the IUIDData Interfaceís data to indicate the style we want to delete
		uidData->Set(::GetDataBase(iWorkspace), styleToDelete);

		// Get an IUIDData Interface for the command:
		InterfacePtr<IUIDData> uidReplaceData(iDeleteStyleCmd, IID_IREPLACEUIDDATA);
		if (uidReplaceData == nil) {
			ASSERT(kFalse);
			break;
		}

		// Set the IUIDData Interfaceís data to indicate the style we want to delete
		uidReplaceData->Set(::GetDataBase(iWorkspace), replaceStyle);

		// Process the DeleteParaStyleCmd:
		status = CmdUtils::ProcessCommand(iDeleteStyleCmd);
	} while(kFalse);
	return status;
}


// --------------------------------- For SnippetRunner framework ---------------------------------------------------

class _SnpRunnerManipulateTextStyle : public SnpRunnable

{

public:
		// SnippetRunner framework hooks.

		/** Constructor.
		*/
		_SnpRunnerManipulateTextStyle();

		/** Destructor
		*/
		virtual ~_SnpRunnerManipulateTextStyle();

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
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextSelectionTargetContext;}
};
/* Constructor
*/
_SnpRunnerManipulateTextStyle::_SnpRunnerManipulateTextStyle() : SnpRunnable("ManipulateTextStyle")
{
	this->SetDescription("manipulates text style");
	this->SetPreconditions("some operations require a range of selected text, others have no requirements");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor
*/
_SnpRunnerManipulateTextStyle::~_SnpRunnerManipulateTextStyle()
{
}

/* The implementation defers the decision to the sub-snippet.
*/
bool16 _SnpRunnerManipulateTextStyle::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kTrue;
	return result;
}


ErrorCode _SnpRunnerManipulateTextStyle::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpManipulateTextStyle instance;

		// Find the text frame manipluation to be performed.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("Apply Style"));
		choices.push_back(PMString("Update Para Style"));
		choices.push_back(PMString("Set Default Para Style"));
		choices.push_back(PMString("Delete a Style"));
		choices.push_back(PMString("Create a style from selection"));

		enum {kApplyStyle, kUpdateParaStyle, kSetDefaultParaStyle, kDeleteStyle, kCreateFromSelection};

		int32 choice  = parameterUtils->GetChoice("Which operation?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		SNIPLOG("%s", choices[choice].GetPlatformString().c_str());

		// Apply the manipulation.
		switch (choice) 
		{
			case kApplyStyle:
			{
				status = instance.ApplyStyle(runnableContext);
				break;
			}

			// these sub-snippets have common set up code
			case kUpdateParaStyle:
			case kSetDefaultParaStyle:
			case kCreateFromSelection:
			{
				InterfacePtr<ITextAttributeSuite> textAttributeSuite(runnableContext, UseDefaultIID());
				if (textAttributeSuite == nil)
				{
					SNIPLOG("You do not have a text attribute suite. Exiting...");
					break;
				}		
				
				if (!textAttributeSuite->CanApplyAttributes())
				{
					SNIPLOG("Can't apply attributes.");
					break;
				}


				IActiveContext* activeContext = runnableContext->GetActiveContext();
				// we need a text focus in order to run this snippet
				// query the text target from the current context
				InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
				if (textTarget == nil) 
				{
					SNIPLOG("This snippet requires a text selection");
					break;
				}
				// query the text focus (bridge method)
				InterfacePtr<ITextFocus> textFocus(textTarget->QueryTextFocus());
				ASSERT(textFocus);
				if (textFocus == nil) 
				{
					SNIPLOG("You do not have any text selection - please select some text first.");
					break;
				}
				if (choice == kUpdateParaStyle)
				{
					status = instance.UpdateParaStyle(textFocus, activeContext);				
				}
				else if (choice == kSetDefaultParaStyle) 
				{
					status = instance.SetDefaultParaStyle(textFocus, activeContext);			
				}
				else
				{
					status = instance.CreateStyleFromSelection(textFocus, activeContext);
				}
				break;
			}

			case kDeleteStyle:
			{
				status = instance.DeleteStyle(runnableContext);
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
static _SnpRunnerManipulateTextStyle instance_SnpRunnerManipulateTextStyle;
DEFINE_SNIPPET(_SnpRunnerManipulateTextStyle) 	

