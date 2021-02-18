//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltTextHelper.cpp $
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
// Interface includes
#include "IDocument.h"
#include "IDocFontMgr.h"
#include "IPMFont.h"
#include "ITextAttrUtils.h"
#include "ITextAttrUnderlineMode.h"
#include "ITextAttrFont.h"
#include "ITextAttrUID.h"
#include "ITextModel.h"
#include "ITextAttrRealNumber.h"
#include "ITextModelCmds.h"
#include "ITextAttrAlign.h"
#include "IApplyStyleData.h"
// Other includes
#include "CmdUtils.h"
#include "UIDList.h"

#include "CHMLFiltTextHelper.h"

/* Default constructor
*/
CHMLFiltTextHelper::CHMLFiltTextHelper(const UIDRef& textModelUIDRef) : 
	fTextModelUIDRef(textModelUIDRef),
		fRangeData(RangeData(0,RangeData::kLeanForward))
{

}

CHMLFiltTextHelper::CHMLFiltTextHelper(const UIDRef& textModelUIDRef, const RangeData& range) : 
	fTextModelUIDRef(textModelUIDRef),
	fRangeData(range)
{

}

/* Destructor
*/
CHMLFiltTextHelper::~CHMLFiltTextHelper()
{

}

void CHMLFiltTextHelper::Reset(const RangeData& targetRange)
{
	this->fRangeData = targetRange;
}

void CHMLFiltTextHelper::Reset(const TextIndex& position)
{
	this->fRangeData = RangeData(position, RangeData::kLeanForward);
}

void CHMLFiltTextHelper::checkInvariant()
{
	// Only create new one if it's nil, otherwise we're midway through a sequence of
	// add operations
	if(this->fCharAttributeBossList.get() == nil) {
		fCharAttributeBossList.reset(new AttributeBossList());
	} 
	if(this->fParaAttributeBossList.get() == nil) {
		fParaAttributeBossList.reset(new AttributeBossList());
	}
}

ErrorCode CHMLFiltTextHelper::Apply()
{
	ErrorCode retval = kSuccess;
	do { 
		ErrorCode didChar = this->doApplyAttributes(this->fCharAttributeBossList,kCharAttrStrandBoss);
		ASSERT(didChar == kSuccess);
		ErrorCode didPara = this->doApplyAttributes(this->fParaAttributeBossList,kParaAttrStrandBoss);
		ASSERT(didPara == kSuccess);
		if(didChar != kSuccess || didPara != kSuccess) {
			retval = kFailure;
		}
	} while(kFalse);
	return retval;
}

ErrorCode CHMLFiltTextHelper::doApplyAttributes(boost::shared_ptr<AttributeBossList>& attrList, const ClassID& which)
{
	ErrorCode retval = kFailure;
	do { 

		ASSERT(attrList.get());
		if(!attrList.get()) {
			break;
		}
		if(!(attrList->CountBosses()>0)) {
			// If we have no attrs to apply treat as success
			retval = kSuccess;
			break;
		}

		InterfacePtr<ITextModel> model(this->fTextModelUIDRef,UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		InterfacePtr<ITextModelCmds> modelCmds(model, UseDefaultIID());
		ASSERT(modelCmds);
		if(!modelCmds) {
			break;
		}
		// We've called release() on the encapsulated ptr, meaning we relinquish ownership of it
		// and set our owned ptr to nil
		TextIndex startPosition = this->fRangeData.Start(nil);
		TextIndex runLength = this->fRangeData.Length();
		//Copy attrList before you pass it in.
		boost::shared_ptr<AttributeBossList>attrList_Copy(attrList->Duplicate()); 
		InterfacePtr<ICommand> applyCmd(modelCmds->ApplyCmd (this->fRangeData,attrList_Copy, which));

		ASSERT(applyCmd);
		if(!applyCmd) {
			break;
		}
		// The command owns the newly created attribute list
		retval= CmdUtils::ProcessCommand(applyCmd);
	
		} while(kFalse);
	return retval;
}



ErrorCode CHMLFiltTextHelper::InsertText(const WideString& text)
{
	ErrorCode retval = kFailure;
	do {
		InterfacePtr<ITextModel> iTextModel(this->fTextModelUIDRef, UseDefaultIID());
		ASSERT(iTextModel);
		if(!iTextModel) {
			break;
		}	
		// Add the text to the model
		InterfacePtr<ITextModelCmds> textModelCmds(iTextModel, UseDefaultIID());
		ASSERT(textModelCmds);
		if(!textModelCmds) {
			break;
		}
		TextIndex tpos = this->fRangeData.Start(nil);
		boost::shared_ptr<WideString> string(new WideString(text));
		InterfacePtr<ICommand> insertCmd (textModelCmds->InsertCmd(tpos, string)); // do make a copy
		ASSERT(insertCmd);
		if(!insertCmd) {
			break;
		}
		retval = CmdUtils::ProcessCommand(insertCmd);
		ASSERT(retval == kSuccess);
		
	} while(kFalse);
	return retval;
}



void CHMLFiltTextHelper::AddAlignment(ICompositionStyle::TextAlignment  alignment)
{
	do {
		this->checkInvariant();
		InterfacePtr<ITextAttrAlign> iTextAttrAlignBody(CreateObject2<ITextAttrAlign>(kTextAttrAlignmentBoss));//, IID_ITEXTATTRALIGN));
		ASSERT(iTextAttrAlignBody);
		if(!iTextAttrAlignBody) {
			break;
		}
		iTextAttrAlignBody->SetAlignment(alignment);
		this->fParaAttributeBossList->ApplyAttribute(iTextAttrAlignBody);
		//this->fParaAttributeBossList->ApplyAttribute(iTextAttrAlignLast);

	} while(kFalse);
}

void CHMLFiltTextHelper::AddBold()
{
	do {
		this->checkInvariant();
		InterfacePtr<ITextAttrFont> iTextAttrFont(CreateObject2<ITextAttrFont>(kTextAttrFontStyleBoss));
		ASSERT(iTextAttrFont);
		if(!iTextAttrFont) {
			break;
		}
		iTextAttrFont->SetFontName(PMString("Bold"), kFalse);
		ASSERT(this->fCharAttributeBossList);
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrFont);

	} while(kFalse);
}


void CHMLFiltTextHelper::AddDefaultFont()
{
	do {
		this->checkInvariant();
	// just set the characters to the default as defined by the iTextAttrFont
		InterfacePtr<ITextAttrFont> iTextAttrFont(CreateObject2<ITextAttrFont>(kTextAttrFontStyleBoss));
		ASSERT(iTextAttrFont);
		if(!iTextAttrFont) {
			break;
		}		
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrFont);

	} while(kFalse);
}


void CHMLFiltTextHelper::AddFont(const PMString& name)
{
	do {
		this->checkInvariant();
		UID fontUID = kInvalidUID;
			// get the font manager for this document			
		// let's make sure the font is supported first
		InterfacePtr<IFontMgr> iFontMgr(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(iFontMgr);
		if (iFontMgr == nil) {
			break;
		}
		InterfacePtr<IPMFont> isAppSupFont(iFontMgr->QueryFont(name));
		InterfacePtr<IPMFont> isPlatSupFont(iFontMgr->QueryFontPlatform(name, IFontMgr::kNormal));
	
		if(((!isAppSupFont)||((isAppSupFont->GetFontStatus() & IPMFont::kFontNotAvailable) != 0) &&
			(!isPlatSupFont)||((isPlatSupFont->GetFontStatus() & IPMFont::kFontNotAvailable) != 0)))
		{
			// We can't deal with the font... we can't apply the override,
			// so fail quietly. The missing font adornment will highlight the
			// fact we couldn't find the font.
			TRACEFLOW("CHMLFilter", "Missing font in CHMLFiltTextHelper::AddFont(%s)", name.GetUTF8String().c_str());
			break;
		}
		// we still use the font group - even if it doesn't exist. This way the missing font
		// adornment is turned on...
		IDataBase* db = this->fTextModelUIDRef.GetDataBase();
		InterfacePtr<IDocument> iDocument(db, db->GetRootUID(), IID_IDOCUMENT);
		ASSERT(iDocument);
		if(!iDocument) {
			break;
		}
		InterfacePtr<IDocFontMgr> iDocFontMgr(iDocument->GetDocWorkSpace(), UseDefaultIID());
		ASSERT(iDocFontMgr);
		if(!iDocFontMgr) {
			break;
		}
		// get the uid for the font specified in name (e.g. "Times")

		// if it doesn't exist, don't create it!
		fontUID = iDocFontMgr->GetFontGroupUID(name, kTrue); 
		InterfacePtr<ITextAttrUID> iTextAttrUID(CreateObject2<ITextAttrUID>(kTextAttrFontUIDBoss));
		ASSERT(iTextAttrUID);
		if(!iTextAttrUID) {
			break;
		}
	
		iTextAttrUID->SetUIDData(fontUID);
		ASSERT(this->fCharAttributeBossList);
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrUID);

	} while(kFalse);
}


void CHMLFiltTextHelper::AddNonUnderline()
{
	do {
		this->checkInvariant();
		InterfacePtr<ITextAttrUnderlineMode> iTextAttrUnderlineMode(CreateObject2<ITextAttrUnderlineMode>(kTextAttrUnderlineBoss));
		ASSERT(iTextAttrUnderlineMode);
		if(!iTextAttrUnderlineMode) {
			break;
		}
		iTextAttrUnderlineMode->SetMode(IDrawingStyle::kUnderlineNone);
		ASSERT(this->fCharAttributeBossList);
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrUnderlineMode);

	} while(kFalse);
}


void CHMLFiltTextHelper::AddPointSize(const PMReal& pointSize)
{
	do {
		this->checkInvariant();
		InterfacePtr<ITextAttrRealNumber> iTextAttrRealNumber(CreateObject2<ITextAttrRealNumber>(kTextAttrPointSizeBoss));
		ASSERT(iTextAttrRealNumber);
		if(!iTextAttrRealNumber) {
			break;
		}
		iTextAttrRealNumber->SetRealNumber(pointSize);
		ASSERT(this->fCharAttributeBossList);
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrRealNumber);

	} while(kFalse);
}


void CHMLFiltTextHelper::AddUnderline()
{
	
	do {
		this->checkInvariant();
		InterfacePtr<ITextAttrUnderlineMode> iTextAttrUnderlineMode(CreateObject2<ITextAttrUnderlineMode>(kTextAttrUnderlineBoss));
		ASSERT(iTextAttrUnderlineMode);
		if(!iTextAttrUnderlineMode) {
			break;
		}
		iTextAttrUnderlineMode->SetMode(IDrawingStyle::kUnderlineSingle);
		ASSERT(this->fCharAttributeBossList);
		this->fCharAttributeBossList->ApplyAttribute(iTextAttrUnderlineMode);

	} while(kFalse);
}

//  Code generated by DollyXS code generator

