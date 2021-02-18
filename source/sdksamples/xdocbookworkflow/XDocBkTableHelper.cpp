//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkTableHelper.cpp $
//  
//  Owner:	Ian Paterson
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
#include "IDocument.h"	
#include "IIDXMLElement.h"	
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "ISwatchList.h"	
#include "ISwatchUtils.h"	
#include "ITableAttrInt32.h"	
#include "ITableAttrRealNumber.h"	
#include "ITableAttrUID.h"	
#include "ITableCommands.h"	
#include "ITableModel.h"	
#include "ITableTextContainer.h"	
#include "ITableUtils.h"	
#include "ITextModelCmds.h"
#include "ITextStoryThread.h"
#include "ITextStoryThreadDict.h"
#include "IWorkspace.h"
#include "IXMLElementCommands.h"
#include "IXMLUtils.h"

// Project includes:
#include "XDocBkConstants.h"
#include "XDocBkTableHelper.h"


/*
*/
XDocBkTableHelper::XDocBkTableHelper(const UIDRef& tableModelUIDRef)
{
	this->fTableModelUIDRef = tableModelUIDRef; 
}
		
/*
*/
XDocBkTableHelper::~XDocBkTableHelper()
{

}

/*
*/
void XDocBkTableHelper::ApplyDefaultStyle()
{
	this->SetTableLevelStyles();
	this->SetLowerLevelStylesWithinTable();
}

/* 
*/
void XDocBkTableHelper::SetTextContent(int32 row,
											   int32 col,
											   const WideString& text)
{
	do 
	{
		InterfacePtr<ITableModel> iTableModel(this->fTableModelUIDRef, UseDefaultIID());
		ASSERT(iTableModel);
		if (iTableModel == nil) {
			break;
		}
		InterfacePtr<ITableCommands> tableCommands(iTableModel, UseDefaultIID());
		ASSERT(tableCommands);
		if (tableCommands==nil) {
			break;
		}

		GridAddress gridAddress(row,col);
		// Set the cell text at the specified grid address
		ErrorCode retval = tableCommands->SetCellText(text, gridAddress);
		ASSERT(retval == kSuccess);
	} while (kFalse);
}

/* 
*/
void XDocBkTableHelper::SetTableLevelStyles()    
{
	do
	{
		InterfacePtr<ITableModel> tableModel(this->fTableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel);
		if (!tableModel) {
			break;
		}

		AttributeBossList attributeBossList;
		this->ApplyTableAttributes(attributeBossList);

		InterfacePtr<ITableCommands> iTableCommands(tableModel, UseDefaultIID());
		ASSERT(iTableCommands);
		if (!iTableCommands) {
			break;
		}
		ErrorCode status = iTableCommands->ApplyTableOverrides(&attributeBossList);
		ASSERT(status == kSuccess);
	} while (kFalse);

}

/* 
*/
void XDocBkTableHelper::ApplyTableAttributes(AttributeBossList& attributeBossList)
{   
	do
	{
		// Create a stripey alternating fill pattern like the "Every Other Row" one in UI
		InterfacePtr<ITableAttrInt32> patternPriority(::CreateObject2<ITableAttrInt32>(kTableAttrFillPatternPriorityBoss));
		ASSERT(patternPriority);
		if (!patternPriority) {
			break;
		}
		patternPriority->Set(0); // row priority
		attributeBossList.ApplyAttribute(patternPriority);

		InterfacePtr<ITableAttrInt32> startValue(::CreateObject2<ITableAttrInt32>(kTableAttrRowFillPatternStartValueBoss));
		ASSERT(startValue);
		if (!startValue) {
			break;
		}
		startValue->Set(0);
		attributeBossList.ApplyAttribute(startValue);

		InterfacePtr<ITableAttrInt32> endValue(::CreateObject2<ITableAttrInt32>(kTableAttrRowFillPatternEndValueBoss));
		ASSERT(endValue);
		if (!endValue) {
			break;
		}
		endValue->Set(0);
		attributeBossList.ApplyAttribute(endValue);

		InterfacePtr<ITableAttrInt32> firstCount(::CreateObject2<ITableAttrInt32>(kTableAttrRowFillPatternFirstCountBoss));
		ASSERT(firstCount);
		if (!firstCount) {
			break;
		}
		firstCount->Set(1);
		attributeBossList.ApplyAttribute(firstCount);

		InterfacePtr<ITableAttrInt32> secondCount(::CreateObject2<ITableAttrInt32>(kTableAttrRowFillPatternSecondCountBoss));
		ASSERT(secondCount);
		if (!secondCount){
			break;
		}
		secondCount->Set(1);
		attributeBossList.ApplyAttribute(secondCount);


		InterfacePtr<ITableAttrRealNumber> iTableAttrRealNumber(::CreateObject2<ITableAttrRealNumber>(kTableAttrRowFillPatternFirstTintBoss));
		ASSERT(iTableAttrRealNumber);
		if (!iTableAttrRealNumber) {
			break;
		}
		PMReal tint(20.0);
		iTableAttrRealNumber->Set(tint);
		attributeBossList.ApplyAttribute(iTableAttrRealNumber);

		InterfacePtr<ITableAttrUID> iTableAttrUID(::CreateObject2<ITableAttrUID>(kTableAttrRowFillPatternFirstColorBoss));
		ASSERT(iTableAttrUID);
		if (!iTableAttrUID) {
			break;
		}
		InterfacePtr<IDocument> iDocument(this->fTableModelUIDRef.GetDataBase(),
			this->fTableModelUIDRef.GetDataBase()->GetRootUID(),UseDefaultIID());
		ASSERT(iDocument);
		if (!iDocument) {
			break;
		}

		UIDRef workspaceUIDRef =  iDocument->GetDocWorkSpace();
		ASSERT(workspaceUIDRef != UIDRef::gNull);
		InterfacePtr<IWorkspace> iDocWorkspace(workspaceUIDRef, UseDefaultIID());
		ASSERT(iDocWorkspace);
		if (!iDocWorkspace) {
			break;
		}
		InterfacePtr<ISwatchList> iSwatchList (iDocWorkspace, UseDefaultIID());

		ASSERT(iSwatchList);
		if (!iSwatchList) {
			break;
		}
		UID blackUID = iSwatchList->GetBlackSwatchUID();
		iTableAttrUID->Set(blackUID);
		attributeBossList.ApplyAttribute(iTableAttrUID);

	} while (kFalse);

}

/* 
*/
void XDocBkTableHelper::SetLowerLevelStylesWithinTable()    
{
	do
	{
		InterfacePtr<ITableModel> tableModel(this->fTableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel);
		if (!tableModel) {
			break;
		}
		InterfacePtr<IDocument> iDocument(this->fTableModelUIDRef.GetDataBase(),
			this->fTableModelUIDRef.GetDataBase()->GetRootUID(),UseDefaultIID());
		ASSERT(iDocument);
		if (!iDocument) {
			break;
		}
		UIDRef uidRef =  iDocument->GetDocWorkSpace();
		ASSERT(uidRef != UIDRef::gNull);
		InterfacePtr<IWorkspace> iDocWorkspace(uidRef, UseDefaultIID());
		ASSERT(iDocWorkspace);
		if (!iDocWorkspace) {
			break;
		}

	
		ITableModel::const_iterator iterTable(tableModel->begin());
		ITableModel::const_iterator end(tableModel->end());

		while (iterTable != end)
		{
			GridAddress gridAddress = *iterTable;           
			this->ApplyCellStyle(gridAddress, uidRef);
			// goto to the next grid address
			++iterTable;
		}

	} while (false);
}

/* 
*/
void XDocBkTableHelper::ApplyCellStyle( const GridAddress& gridAddress,
									const UIDRef& workspaceUIDRef)
{
	do
	{
		InterfacePtr<IStyleGroupManager> iParaStyleNameTable(workspaceUIDRef, IID_IPARASTYLEGROUPMANAGER);
		ASSERT(iParaStyleNameTable);
		if (iParaStyleNameTable == nil) {
			break;
		}


		InterfacePtr<ITableModel> tableModel(this->fTableModelUIDRef, UseDefaultIID());
		ASSERT(tableModel);
		if (tableModel == nil) {
			break;
		}

		// convert the grid address to a grid ID
		const GridID gridID = tableModel->GetGridID(gridAddress);
		// get the table text container so we could get to the text model.
		InterfacePtr<ITableTextContainer> tableTextContainer(tableModel, UseDefaultIID());
		ASSERT(tableTextContainer);
		if (tableTextContainer == nil) {
			break;
		}

		InterfacePtr<ITextModel> textModel(tableTextContainer->QueryTextModel());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}

		InterfacePtr<ITextStoryThreadDict> textStoryThreadDict(tableModel, UseDefaultIID());
		ASSERT(textStoryThreadDict);
		if (textStoryThreadDict == nil) {
			break;
		}
		InterfacePtr<ITextStoryThread> textStoryThread(textStoryThreadDict->QueryThread(gridID));
		ASSERT(textStoryThread);
		if (textStoryThread == nil) {
			break;
		}
		TextIndex threadStart;
		int32 threadLength = -1;
		threadStart = textStoryThread->GetTextStart(&threadLength);

		PMString findParaStyleName(XDocBkConstants::k_ENTRY_TAG);
		// Determine if this is a header row: if so, use a slightly modified style
		RowRange headerRowRange= tableModel->GetHeaderRows();

		if (headerRowRange.Contains(gridAddress.row)) {
			findParaStyleName += "_";
			findParaStyleName +=  XDocBkConstants::k_THEAD_TAG;
		}
		UID styleUID = iParaStyleNameTable->FindByName(findParaStyleName);
		if (styleUID == kInvalidUID) {
			break;
		}
		// apply the style
		InterfacePtr<ITextModelCmds> textModelCmds(textModel, UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			break;
		}
		InterfacePtr<ICommand> applyStyleCmd(textModelCmds->ApplyStyleCmd(threadStart, 
																		  threadLength, 
																		  styleUID, 
																		  kParaAttrStrandBoss, 
																		  kTrue // Replace overrides (shouldn't be manually styling text anyhow)
																		  ));
		CmdUtils::ProcessCommand(applyStyleCmd);

	} while (kFalse);
}