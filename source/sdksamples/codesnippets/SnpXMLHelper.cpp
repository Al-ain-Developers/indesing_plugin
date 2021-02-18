//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpXMLHelper.cpp $
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
#include "IBoolData.h"
#include "IColorData.h"
#include "IDocument.h"
#include "IGraphicFrameData.h"
#include "IIDXMLElement.h"
#include "IPersistUIDData.h"
#include "ITableModel.h"
#include "IXMLExportOptions.h"
#include "IXMLImportOptions.h"
#include "IXMLLoadDTDCmdData.h"
#include "IXMLMappingCommands.h"
#include "IXMLPreferences.h"
#include "IXMLReferenceData.h"
#include "IXMLStyleToTagMap.h"
#include "IXMLTag.h"
#include "IXMLTagCommands.h"
#include "IXMLTagList.h"
#include "IXMLTagToStyleMap.h"
#include "IXMLUtils.h"
#include "IXMLValidator.h"
#include "IWorkspace.h"
// General includes:
#include "PreferenceUtils.h" // QuerySessionPreferences
#include "SDKLayoutHelper.h"
#include "SDKFileHelper.h"
// Project includes
#include "SnipRunLog.h"
#include "SnpXMLResolutionHelper.h"
#include "SnpTextModelHelper.h"
#include "SnpRunnable.h"
#include "SnpXMLHelper.h"


// Have static instance rather than create instance when needed, as this is has fairly large footprint in memory
static SnpXMLResolutionHelper sSnpXMLResolutionHelper;

/*
*/
UIDRef SnpXMLHelper::AcquireTag(const UIDRef& documentUIDRef,
									 const PMString& tagName
									 )
{
	UIDRef retval;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		if(!document) {
			break;
		}
		InterfacePtr<IXMLTagList> tagList(Utils<IXMLUtils>()->QueryXMLTagList(documentUIDRef.GetDataBase()));
		ASSERT(tagList);
		if(!tagList) {
			break;
		}

		WideString tagNameWide(tagName);
		UID existingTagUID  = tagList->GetTag(tagNameWide);
		if(existingTagUID == kInvalidUID) {

			UID createdTagUID = kInvalidUID;
			ErrorCode err = Utils<IXMLTagCommands>()->CreateTag (::GetUIDRef(tagList), 
															tagNameWide,
															kInvalidUID, 
															&createdTagUID);

			ASSERT(err == kSuccess);
			ASSERT(createdTagUID != kInvalidUID);
			retval = UIDRef(::GetDataBase(tagList), createdTagUID);

		} else {
			retval = UIDRef(::GetDataBase(tagList), existingTagUID);
		}

	} while(kFalse);

	return retval;
}

/*
*/
ErrorCode SnpXMLHelper::AssociateDTD(const UIDRef& documentUIDRef, const IDFile& sysFile)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		if(!document) {
			break;
		}
		InterfacePtr<ICommand> loadDTDCmd(CmdUtils::CreateCommand(kXMLLoadDTDCmdBoss));
		ASSERT(loadDTDCmd);
		if(!loadDTDCmd) {
			break;
		}
		InterfacePtr<IXMLLoadDTDCmdData> loadDTDData(loadDTDCmd, UseDefaultIID());
		ASSERT(loadDTDData);
		if(!loadDTDData) {
			break;
		}
		loadDTDData->Set(sysFile, document);
		err = CmdUtils::ProcessCommand(loadDTDCmd);

	} while(kFalse);
	return err;
}

/*
*/
PMString SnpXMLHelper::AsString(const UIDRef& tagUIDRef)
{
	PMString retval;
	do {
		// +precondition
		InterfacePtr<IXMLTag> xmlTag(tagUIDRef, UseDefaultIID());
		ASSERT(xmlTag);
		if(!xmlTag) {
			break;
		}
		// -precondition
		IDataBase* db = tagUIDRef.GetDataBase();
		
		PMString colourName;
		InterfacePtr<IPersistUIDData> colourUIDData(tagUIDRef, IID_ICOLORPERSISTUIDDATA);
		ASSERT(colourUIDData);
		if(!colourUIDData) {
			break;
		}
		UIDRef colourUIDRef(db, colourUIDData->GetUID());
		InterfacePtr<IColorData> colorData(colourUIDRef, UseDefaultIID());
		if(colorData) {
			colourName += " (";
			for(int32 i=0; i < colorData->GetNumComponents(); i++) {
				colourName.AppendNumber(colorData->GetNthComponent(i), 2);
				if(i < colorData->GetNumComponents()- 1) {
					colourName += " ";
				}
			}
			colourName += ") ";
		}
			
		
		retval += "Tag Named ";
		retval.Append(xmlTag->GetTagName());
		retval += " has colour ";
		retval.Append(colourName);
		retval += ", tag is represented by ";
		retval.Append(this->GetClassFrom(tagUIDRef));
		retval += ", UID= ";
		retval.AppendNumber(tagUIDRef.GetUID().Get());
		retval += ", and colour is represented by ";
		retval.Append(this->GetClassFrom(colourUIDRef));
		retval += ", UID= ";
		retval.AppendNumber(colourUIDRef.GetUID().Get());
	
		
	} while(kFalse);
	return retval;
}

/*
*/
PMString SnpXMLHelper::AsString(const XMLReference& xmlReference)
{
	PMString retval;
	do {
		InterfacePtr<IIDXMLElement> element(xmlReference.Instantiate());
		// This can legimately be nil sometimes so don't assert
		// 
		if(!element) {
			break;
		}
		ClassID elementClassID = ::GetClass(element);
		PMString elementClassName = sSnpXMLResolutionHelper.ResolveClass(elementClassID.Get());
		UID contentItem = element->GetContentItem(); // content Item UID
		XMLReference xmlRef = element->GetXMLReference(); // XMLReference
		UID xmlRefUID = xmlRef.GetUID(); // UID of XMLReference
		LSID xmlRefLSID = xmlRef.GetLogicalID(); // Logical ID of XMLReference
		PMString tagString = element->GetTagString(); // tag
		IDataBase* dataBase = xmlRef.GetDataBase();
		ClassID backClassID = dataBase->GetClass(xmlRefUID);
		ClassID contentClassID = dataBase->GetClass(contentItem);
		PMString backClassStr = sSnpXMLResolutionHelper.ResolveClass(backClassID.Get());
		PMString contentClassStr = sSnpXMLResolutionHelper.ResolveClass(contentClassID.Get());
		
		retval += "Element: <";
		retval.Append(tagString);
		retval += "> (class ";
		retval.Append(elementClassName);
		retval += "), ";
		retval.Append("\n");
		retval += " BkStore UID=";
		retval.AppendNumber(xmlRefUID.Get());
		retval += " (class ";
		retval.Append(backClassStr);
		retval += "), LSID=";
		retval.AppendNumber(xmlRefLSID);
		retval += ", ";
		retval.Append("\n");
		retval += " ContentItem UID=";
		retval.AppendNumber(contentItem.Get());
		retval += " (";
		retval.Append(contentClassStr);
		retval += ")";
		retval.Append("\n");

		
		for (int32 attrIndex = 0 ; attrIndex < element->GetAttributeCount() ; attrIndex++) 
		{
			WideString attributeName = element->GetAttributeNameAt(attrIndex);
			WideString attributeValue = element->GetAttributeValue(attributeName);
			
			retval +="\t+Attr=";
			retval.Append(attributeName);
			retval += ", val=\"";
			retval.Append(attributeValue);
			retval += "\"";
		}
		
		XMLContentReference contentRef = element->GetContentReference();
		retval.Append("\n");
		retval += "ContentReference UID = ";
		retval.AppendNumber(contentRef.GetUID().Get());
		ClassID cid = dataBase->GetClass(contentRef.GetUID());
		PMString bcstr = sSnpXMLResolutionHelper.ResolveClass(cid.Get());
		retval += "(";
		retval.Append(bcstr);
		retval += ") ";
		if(contentRef.IsTable()) {
			retval += ", Table Content";
			retval.Append("\n");
		} else if(contentRef.IsTableCell()) {
			retval += ", Table Cell";
			retval.Append("\n");
		} 


	} while(kFalse);
	return retval;
}


/*
*/
ErrorCode SnpXMLHelper::ChangeTagName(const UIDRef& tagUIDRef,
									 const PMString& newTagName
									 )
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IXMLTag> tag(tagUIDRef, UseDefaultIID());
		ASSERT(tag);
		if(!tag) {
			break;
		}
		// -precondition
		err = Utils<IXMLTagCommands>()->SetTagName(tagUIDRef.GetDataBase(),
												tagUIDRef.GetUID(),
												WideString(newTagName));
		// if the tagname exists already, this method will return an error
	} while(kFalse);

	return err;
}


/*
*/
PMString SnpXMLHelper::GetClassFrom(const UIDRef& objUIDRef)
{
	PMString retval;
	do {
		ClassID classID;
		InterfacePtr<IControllingUnknown> bossControllingUnknown(objUIDRef,UseDefaultIID());
		ASSERT(bossControllingUnknown);
		if(!bossControllingUnknown) {
			break;
		}
		classID = bossControllingUnknown->GetClass();
		retval  = this->GetClassFrom(classID);
	} while(kFalse);
	return retval;
}

/*
*/
PMString SnpXMLHelper::GetClassFrom(const ClassID& classID)
{
	return sSnpXMLResolutionHelper.ResolveClass(classID.Get());
}

/*
*/
XMLReference SnpXMLHelper::GetRootXMLReference(const UIDRef& documentUIDRef)
{
	XMLReference rootXMLReference;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		if(!document) {
			break;
		}
		IDataBase*db = documentUIDRef.GetDataBase();
		InterfacePtr<IIDXMLElement> rootXMLElement(Utils<IXMLUtils>()->QueryRootElement(db));
		ASSERT(rootXMLElement);
		if(!rootXMLElement) {
			break;
		}
		rootXMLReference = rootXMLElement->GetXMLReference();
	} while(kFalse);
	return rootXMLReference;
}

/*
*/
TextIndex SnpXMLHelper::InsertTaggedText(const UIDRef& textModelUIDRef, const PMString& pstr, TextIndex startIndex, const PMString& tagName)
{
	TextIndex err = startIndex;
	do {
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		this->InsertText(textModelUIDRef,pstr,startIndex);
		TextIndex endIndex = startIndex + pstr.CharCount();
		this->TagTextRange(textModelUIDRef, tagName, startIndex, endIndex);
		PMString cr;
		cr.Append(kTextChar_CR);
		const int32 numZWCharsAdded = 2;
		// We need to insert at endIndex+ num zero-width chars we added
		this->InsertText(textModelUIDRef, cr, endIndex+numZWCharsAdded);
		
		// Return the next index where we can insert text
		err =  (endIndex+numZWCharsAdded) + 1;
	} while(kFalse);
	return err;
}

/*
*/

ErrorCode SnpXMLHelper::InsertText(const UIDRef& textModelUIDRef, const PMString& data, const TextIndex& position)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		// -precondition 
		if(!textModel) {
			break;
		}
		boost::shared_ptr<WideString>  wide(new WideString(data));
		SnpTextModelHelper  textCmdHelper;
		err =  textCmdHelper.InsertText(textModel, position, wide);
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::PlaceElement(const XMLReference& xmlRef, const UIDRef& graphicFrameUIDRef)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<IGraphicFrameData> graphicFrameData(graphicFrameUIDRef, UseDefaultIID());
		ASSERT(graphicFrameData);
		if(!graphicFrameData) {
			break;
		}
		Utils<IXMLElementCommands> elementCommands;
		ASSERT(elementCommands);
		if(!elementCommands) {
			break;
		}
		err = elementCommands->PlaceElement(xmlRef, graphicFrameUIDRef);

		ASSERT(err == kSuccess);
		
	} while(kFalse);

	return err;
}



/*
*/
ErrorCode SnpXMLHelper::SetExportFromSelected(const UIDRef& workspaceUIDRef, bool16 state)
{
	ErrorCode err = kFailure;
	do {
		
		InterfacePtr<IWorkspace> workspace(workspaceUIDRef, UseDefaultIID());
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
		InterfacePtr<ICommand> changeCmd(CmdUtils::CreateCommand(kChangeXMLExportOptionsCmdBoss));
		ASSERT(changeCmd);
		if(!changeCmd) {
			break;
		}
		InterfacePtr<IXMLExportOptions> workspaceExportOptions(workspace, UseDefaultIID());
		ASSERT(workspaceExportOptions);
		if(!workspaceExportOptions) {
			break;
		}
		InterfacePtr<IXMLExportOptions>	cmdExportOptions(changeCmd, UseDefaultIID());
		ASSERT(cmdExportOptions);
		if(!cmdExportOptions) {
			break;
		}
		cmdExportOptions->Copy(workspaceExportOptions);
		cmdExportOptions->SetExportFromSelected(state);
		changeCmd->SetItemList(UIDList(workspace));

		err = CmdUtils::ProcessCommand(changeCmd);
	
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::SetImportIntoSelected(const UIDRef& workspaceUIDRef, bool16 state)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IWorkspace> workspace (workspaceUIDRef, UseDefaultIID());
		ASSERT(workspace);
		if(!workspace) {
			break;
		}
		InterfacePtr<ICommand> changeCmd(CmdUtils::CreateCommand(kChangeXMLImportOptionsCmdBoss));
		ASSERT(changeCmd);
		if(!changeCmd) {
			break;
		}
		InterfacePtr<IXMLImportOptions> workspaceImportOptions(workspace, UseDefaultIID());
		ASSERT(workspaceImportOptions);
		if(!workspaceImportOptions) {
			break;
		}
		InterfacePtr<IXMLImportOptions>	cmdImportOptions(changeCmd, UseDefaultIID());
		ASSERT(cmdImportOptions);
		if(!cmdImportOptions) {
			break;
		}
		cmdImportOptions->Copy(workspaceImportOptions);
		cmdImportOptions->SetImportIntoSelected(state);
		changeCmd->SetItemList(UIDList(workspace));

		err = CmdUtils::ProcessCommand(changeCmd);
		
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::SetRootTag(const UIDRef& documentUIDRef, const PMString& tagName)
{
	
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IDocument> document(documentUIDRef, UseDefaultIID());
		if(!document) {
			break;
		}
		UIDRef tagUIDRef = this->AcquireTag(documentUIDRef, tagName);
		XMLReference rootXMLRef = this->GetRootXMLReference(documentUIDRef);
		err = Utils<IXMLElementCommands>()->SetElement(rootXMLRef, tagUIDRef.GetUID());
		ASSERT(err == kSuccess);
	} while(kFalse);

	return err;
}


/*
*/
ErrorCode SnpXMLHelper::ShowHideTaggedFrames(bool16 setVisible)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<IXMLPreferences> prefs((IXMLPreferences*)
			::QuerySessionPreferences(IXMLPreferences::kDefaultIID));
		ASSERT(prefs);
		if(!prefs) {
			break;
		}
		if (prefs->GetShowTaggedFrames() == setVisible) {
		 err = kSuccess;
		 break;
		}

		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kShowTaggedFramesCmdBoss));
		ASSERT(cmd);
		if(!cmd) {
			break;
		}
		InterfacePtr<IBoolData> boolData(cmd, UseDefaultIID());
		ASSERT(boolData);
		if(!boolData) {
			break;
		}
		boolData->Set(setVisible);
		cmd->SetItemList(::GetUIDRef(prefs));
		err = CmdUtils::ProcessCommand(cmd);
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::TagStory(const UIDRef& textModelUIDRef, 
								 const PMString& tagName)
{
	ErrorCode err = kFailure;
	do {
		// +precondition
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		// -precondition
		IDataBase* database = textModelUIDRef.GetDataBase();

		InterfacePtr<IIDXMLElement> rootXMLElement(Utils<IXMLUtils>()->QueryRootElement(database));
		ASSERT(rootXMLElement);
		if(!rootXMLElement) {
			break;
		}
		XMLReference rootXMLReference = rootXMLElement->GetXMLReference();

		int32 indexInParent =  rootXMLElement->GetChildCount();
		if(indexInParent < 0) {
			indexInParent = 0;
		} 
		UIDRef rootDocumentUIDRef(database,database->GetRootUID());
		UIDRef tagUIDRef = this->AcquireTag(rootDocumentUIDRef, tagName);

		err = Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), 
			textModelUIDRef.GetUID(),
			rootXMLReference,
			indexInParent
			);
		ASSERT(err == kSuccess);
	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::TagTable(const UIDRef& tableModelUIDRef, 
								 const PMString & tableTagName, 
								 const PMString& cellTagName,
								 XMLReference& outCreatedXMLReference)
{
	ErrorCode err = kFailure;
	do {
		// + preconditions
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel != nil);
		// - preconditions
		if(!tableModel) {
			break;
		}
		IDataBase* database = tableModelUIDRef.GetDataBase();
		UIDRef rootDocumentUIDRef(database,database->GetRootUID());
	
		UIDRef tablTagUIDRef = this->AcquireTag(rootDocumentUIDRef, tableTagName);
		UIDRef cellTagUIDRef = this->AcquireTag(rootDocumentUIDRef, cellTagName);

		err = Utils<IXMLElementCommands>()->CreateTableElement (tablTagUIDRef.GetUID(),
											cellTagUIDRef.GetUID(),
											tableModelUIDRef,
											&outCreatedXMLReference);
		ASSERT(err == kSuccess);

	} while(kFalse);
	return err;
}

/*
*/
ErrorCode SnpXMLHelper::TagTextRange(const UIDRef& storyUIDRef,
									const PMString& tagName,
									TextIndex startIndex,
									TextIndex endIndex)
{
	ErrorCode err = kFailure;
	do {
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
		ASSERT(textModel != nil);
		if(!textModel) {
			break;
		}
		IDataBase* database = storyUIDRef.GetDataBase();
		UIDRef rootDocumentUIDRef(database,database->GetRootUID());

		UIDRef tagUIDRef = this->AcquireTag(rootDocumentUIDRef,
											tagName);

		err = Utils<IXMLElementCommands>()->CreateElement(tagUIDRef.GetUID(), storyUIDRef,
			startIndex, endIndex);

		err = kSuccess;
	} while(kFalse);
	return err;
}



// End, SnpXMLHelper.cpp

