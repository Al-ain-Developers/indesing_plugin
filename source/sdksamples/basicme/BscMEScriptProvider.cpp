//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicme/BscMEScriptProvider.cpp $
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
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IWorkspace.h"
#include "INewDocCmdData.h"
#include "IDocumentCommands.h"
#include "ILayoutUtils.h"
#include "IHierarchy.h"
#include "IPageItemScriptUtils.h"
#include "ITransform.h"
#include "ITextColumnSizer.h"
#include "IGraphicFrameData.h"
#include "IMultiColumnTextFrame.h"
#include "ITextFrameFacade.h"
#include "ITextScriptUtils.h"
#include "ITextAttrClassID.h"
#include "IRangeData.h"
#include "IApplyStyleData.h"
#include "ICompositionStyle.h"
#include "IParagraphDirAttr.h"
#include "ITextAttrUtils.h"
#include "IDirOverrideAttr.h"
#include "IJustificationStyle.h"
#include "IJustifMethodAttr.h"
#include "ITextAttrAlign.h"
#include "IDocFontMgr.h"
#include "IActiveContext.h"
#include "ITextAttrFont.h"
#include "ITextAttrUID.h"

// General includes:
#include "CAlert.h"
#include "CScriptProvider.h"
#include "MessageLog.h"
#include "SDKLayoutHelper.h"
#include "TransformUtils.h"
#include "TCID.h"
#include "K2SmartPtr.h"

// Project includes:
#include "BscMEScriptingDefs.h"
#include "BscMEID.h"
#include "IBscMEInvertFacade.h"


/** There is already well implemented scripting DOM in InDesign server for Middle Eastern (ME) text. 
    BscMEScriptProvider provides the scripting method to access the ME features. It illustrates 
    how to handle script elements such as page and paragraph, apply text attributes for ME text, 
    apply world-ready composer on text.   
 
    @ingroup basicme
*/
class BscMEScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor.
	@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	BscMEScriptProvider(IPMUnknown* boss) : RepresentScriptProvider(boss) {};

	/** Destructor. Does nothing.
	*/
	~BscMEScriptProvider() {}

	/** This method is called if a provider can handle an method.
	@param methodID identifies the ID of the method to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object representing the parent of the application object.
	*/
	virtual ErrorCode HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent);

	/** This method is called if a provider can handle a property.
	@param propID identifies the ID of the property to handle.
	@param data identifies an interface pointer used to extract data.
	@param parent identifies an interface pointer on the script object 		representing the parent of the application object.
	*/
	virtual ErrorCode AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);
	
protected:
	/**	See RepresentScriptProvider::GetNumObjects
	 */
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent );
	
	/** See RepresentScriptProvider::AppendNthObject
	 */
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );
	
private:

	ErrorCode ChangeParagraphAttr(IScriptRequestData* data, IScript* parent);

	ErrorCode CreateDocument(IScriptRequestData* data, IScript* parent);

	ErrorCode CreateTextFrame(IScriptRequestData* data, IScript* parent);

	UIDRef CreateTextFrame(const UIDRef& parentUIDRef,
							const PMRect& boundsInParentCoords,
							int32 numberOfColumns,
							bool16 verticalFrame,
							UIDRef* storyUIDRef,
							bool16 isLeftToRight);
	
	ErrorCode InvertDocument(IScriptRequestData* data, IScript* parent);
	
	ErrorCode GetEnum(IScriptRequestData* data, IScript* parent, ScriptID scriptID, ScriptID& enumData, bool16 required = kTrue);

	ErrorCode GetInt32(IScriptRequestData* data, IScript* parent, ScriptID scriptID, int32& intData, bool16 required = kTrue);
	
	ErrorCode GetBoolean(IScriptRequestData* data, IScript* parent, ScriptID scriptID, bool16& boolData, bool16 required = kTrue);
	
	IScript* QueryScript(IScriptRequestData* data, IScript* parent, ScriptID scriptID);
	
	ClassID GetComposerClassID(const WideString& composerName);
	
	template <typename I, typename V>
	ErrorCode ChangeTextAttribute(ITextModel* textModel, ClassID strandBoss, ClassID attrBoss, const RangeData& range, V attrVal);
};


/* CREATE_PMINTERFACE
Binds the C++ implementation class onto its ImplementationID 
making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(BscMEScriptProvider, kBscMEScriptProviderImpl)


/* HandleMethod */
ErrorCode BscMEScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (methodID.Get())
	{
		case e_BscMECreateDoc:
			status = CreateDocument(data, parent);
			break;

		case e_BscMECreateTextFrame:
			status = CreateTextFrame(data, parent);
			break;

		case e_BscMEChangeParagraphAttr:
			status = ChangeParagraphAttr(data, parent);
			break;
			
		case e_BscMEInvertDocument:
			status = InvertDocument(data, parent);
			break;
				
		default:
			status = CScriptProvider::HandleMethod(methodID, data, parent);
			break;
	}

    return status;
}

/* AccessProperty
*/
ErrorCode BscMEScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;

	switch (propID.Get())
	{
	case p_BscME:
	{
		// Get the basic me script object.
		if (data->IsPropertyGet())
		{
			InterfacePtr<IScript> appScript(Utils<IScriptUtils>()->QueryApplicationScript());
			InterfacePtr<IScript> bscMEScript(Utils<IScriptUtils>()->CreateProxyScriptObject(data->GetRequestContext(), kBscMEScriptObjectBoss, c_BscME, appScript));
			data->AppendReturnData( parent, propID, ScriptData( bscMEScript ) ) ;
			status = kSuccess;
		}
		break;
	}
			
	default:
		status = CScriptProvider::AccessProperty(propID, data, parent);
		break;
    }

    return status;
}

ErrorCode BscMEScriptProvider::InvertDocument(IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	do {
		ScriptData scriptData;
		if (data->ExtractRequestData(p_DocItem, scriptData) != kSuccess)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_DocItem);
			break;
		}
		
		InterfacePtr<IScript> docScript(scriptData.QueryObject());
		if(!docScript)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_DocItem);
			break;
		}
		
		InterfacePtr<IDocument> document(docScript, UseDefaultIID());
		if(!document)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_DocItem);
			break;
		}
		
		InvertOptions inverOptions;
		ScriptID enumData;
		status = GetEnum(data, parent, p_BscMEDirection, enumData, kFalse);
		if(status == kSuccess)
		{
			if(enumData.Get() == en_BscMERightToLeft)
				inverOptions.pageBinding = kRightToLeftBinding;
			else if(enumData.Get() == en_BscMELeftToRight)
				inverOptions.pageBinding = kLeftToRightBinding;
		}
		
		GetBoolean(data, parent, p_BscMEInvertStories, inverOptions.invertStories, kFalse);
		GetBoolean(data, parent, p_BscMEChangeTableDir, inverOptions.changeTableDir, kFalse);
		GetBoolean(data, parent, p_BscMEMovePageItem, inverOptions.movePageItem, kFalse);		
		GetBoolean(data, parent, p_BscMEFlipObjectAngle, inverOptions.flipObjectAngle, kFalse);
		
		Utils<IBscMEInvertFacade>()->InvertDocument(document, inverOptions);
		
		status = kSuccess;
	} while(false);
	
	return status;
}

ErrorCode BscMEScriptProvider::CreateTextFrame(IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	do {
		ScriptData scriptData;
		if (data->ExtractRequestData(p_BscMEPage, scriptData) != kSuccess)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_BscMEPage);
			break;
		}
		
		InterfacePtr<IScript> pageScript(scriptData.QueryObject());
		if(!pageScript)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_BscMEPage);
			break;
		}
		
		InterfacePtr<IHierarchy> pageHier(pageScript, UseDefaultIID());
		if(!pageHier)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_BscMEPage);
			break;
		}

		if(data->ExtractRequestData(p_GeometricBounds, scriptData) != kSuccess)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_GeometricBounds);
			break;
		}
		
		ScriptListData boundsList ;
		status = scriptData.GetList( boundsList ) ;
		if ( status != kSuccess || boundsList.size() != 4 )
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_GeometricBounds);
			break;
		}

		PMReal t, l, b, r;
		scriptData = boundsList[0] ;
		scriptData.GetUnit(&t, ScriptData::kYCoordinate, parent, data->GetRequestContext());
		
		scriptData = boundsList[1] ;
		scriptData.GetUnit(&l, ScriptData::kXCoordinate, parent, data->GetRequestContext());
		
		scriptData = boundsList[2] ;
		scriptData.GetUnit(&b, ScriptData::kYCoordinate, parent, data->GetRequestContext());

		scriptData = boundsList[3] ;
		scriptData.GetUnit(&r, ScriptData::kXCoordinate, parent, data->GetRequestContext());
		PMRect boundsInPage(l, t, r, b);
		
		// Get spread layer the page on.
		InterfacePtr<IHierarchy> pageLayerHier(pageHier->QueryParent());
		ASSERT(pageLayerHier != nil);
		if (pageLayerHier == nil) {
			break;
		}
		UIDRef spreadUIDRef(::GetUIDRef(pageLayerHier).GetDataBase(), pageLayerHier->GetParentUID());
		
		SDKLayoutHelper layoutHelper;
		UIDRef activeLayerRef = layoutHelper.GetActiveSpreadLayerRef(spreadUIDRef);
		
		// Transform the bounds of the frame from page co-ordinates
		// into the parent co-ordinates, i.e. the spread.
		PMRect boundsInSpread = layoutHelper.PageToSpread(::GetUIDRef(pageHier), boundsInPage);

		ScriptID enumData;
		status = GetEnum(data, parent, p_BscMEDirection, enumData);
		if(status != kSuccess)
			break;
		
		int32 colnum;
		status = GetInt32(data, parent, p_TextColumnCount, colnum);
		if(status != kSuccess)
			break;
		
		// Create the frame.
		UIDRef textFrameRef = CreateTextFrame(activeLayerRef, 
											  boundsInSpread, 
											  colnum, 
											  kFalse, 
											  nil, 
											  enumData.Get() == en_BscMELeftToRight);
		
		InterfacePtr<IScript> textFrameScript(textFrameRef, UseDefaultIID());
		data->AppendReturnData( parent, e_BscMECreateTextFrame, ScriptData( textFrameScript ) ) ;

		status = kSuccess;
	} while(false);
	
	return status;
}

UIDRef BscMEScriptProvider::CreateTextFrame(const UIDRef& parentUIDRef,
											const PMRect& boundsInParentCoords,
											int32 numberOfColumns,
											bool16 verticalFrame,
											UIDRef* storyUIDRef,
											bool16 isLeftToRight)
{
	UIDRef result = UIDRef::gNull;
	do
	{
		// Set up the co-ordinates for the frame. The caller passes in the
		// co-ordinates in the co-ordinate space of the parent. kCreateMultiColumnItemCmdBoss
		// expects pasteboard co-ordinates so we have to transform the points before passing
		// them to the command.
		PMPoint topLeft = boundsInParentCoords.LeftTop();
		PMPoint rightBottom = boundsInParentCoords.RightBottom();
		InterfacePtr<ITransform> transform(parentUIDRef, UseDefaultIID());
		ASSERT(transform);
		if (transform == nil) {
			break;
		}
		::TransformParentPointToPasteboard(transform, &topLeft);
		::TransformParentPointToPasteboard(transform, &rightBottom);
		
		// Process command to create multi-column frame.
		if (Utils<Facade::ITextFrameFacade>()->CreateTextFrame(parentUIDRef, result, PMRect(topLeft, rightBottom), kTrue/*noGraphicAttr*/, !verticalFrame, kFalse/*isFrameGrid*/, isLeftToRight) != kSuccess)
		{
			ASSERT_FAIL("kCreateMultiColumnItemCmdBoss failed");
			break;
		}
		ASSERT(result != UIDRef::gNull);
		
		InterfacePtr<IGraphicFrameData> frame(result, IID_IGRAPHICFRAMEDATA);
		InterfacePtr<IMultiColumnTextFrame> mcFrame(result.GetDataBase(), frame->GetTextContentUID(), UseDefaultIID());
		
		// Set up ITextColumnSizer to override defaults.
		if (numberOfColumns > 0)
		{
			InterfacePtr<ITextColumnSizer> columnSizer(mcFrame, UseDefaultIID());
			columnSizer->SetNumberOfColumns(numberOfColumns);
		}
		
		// If the caller requested it by passing in a pointer return a reference
		// to the story associated with the text frame.
		if (storyUIDRef) {
			*storyUIDRef = UIDRef(parentUIDRef.GetDataBase(), mcFrame->GetTextModelUID());
		}
		
	} while(false);
	
	return result;
}

ErrorCode BscMEScriptProvider::CreateDocument(IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	
	do {
		ScriptID enumData;
		status = GetEnum(data, parent, p_BscMEDirection, enumData);
		if(status != kSuccess)
			break;
		
		int32 pageBinding = kDefaultBinding;
		if(enumData.Get() == en_BscMERightToLeft)
			pageBinding = kRightToLeftBinding;
		else if(enumData.Get() == en_BscMELeftToRight)
			pageBinding = kLeftToRightBinding;
		
		const PMReal width = 612;
		const PMReal height = 792;
		
		// Create the command.
		InterfacePtr<ICommand> newDocCmd(Utils<IDocumentCommands>()->CreateNewCommand(K2::kSuppressUI));
		ASSERT(newDocCmd);
		if (newDocCmd == nil) {
			break;
		}
		
		// Set the command's parameterised data.
		InterfacePtr<INewDocCmdData> newDocCmdData(newDocCmd, UseDefaultIID());
		ASSERT(newDocCmdData);
		if (newDocCmdData == nil) {
			break;
		}
		newDocCmdData->SetCreateBasicDocument(kFalse); // Override the following defaults.
		PMPageSize pageSize( width, height);
		newDocCmdData->SetNewDocumentPageSize(pageSize);
		bool16 bWide = kTrue; // landscape orientation.
		if (width < height)
		{
			// portrait orientation.
			bWide = kFalse;
		}
		newDocCmdData->SetWideOrientation(bWide);
		// Size margin proportional to document width and height.
		PMReal horMargin = width / 20;
		PMReal verMargin = height / 20;
		newDocCmdData->SetMargins(horMargin, verMargin, horMargin, verMargin);
		newDocCmdData->SetNumPages(1);
		newDocCmdData->SetPagesPerSpread(2);
		newDocCmdData->SetPageBinding(pageBinding);
		
		// Create the new document.
		if (CmdUtils::ProcessCommand(newDocCmd) != kSuccess) {
			ASSERT_FAIL("IDocumentCommands::CreateNewCommand failed");
			break;
		}
		
		// Pass the UIDRef of the new document back to the caller.
		const UIDList& newDocCmdUIDList = newDocCmd->GetItemListReference();
		
		InterfacePtr<IDocument> newDoc(newDocCmdUIDList.GetRef(0), UseDefaultIID());
		if (newDoc)
		{
			InterfacePtr<IScript> docScript(newDoc, UseDefaultIID());
			data->AppendReturnData( parent, e_BscMECreateDoc, ScriptData( docScript ) ) ;
			status = kSuccess;
		}
		else
		{
			status = kNoDocumentOpenError;
		}
		
		status = kSuccess;
	} while (false);
	
	return status;
}

ErrorCode BscMEScriptProvider::ChangeParagraphAttr(IScriptRequestData* data, IScript* parent)
{
	ErrorCode status = kFailure;
	
	do {
		//Query IScript interface of text story
		InterfacePtr<IScript> textScript(QueryScript(data, parent, p_BscMEPara));
		if(!textScript)
		{
			break;
		}
		
		InterfacePtr<ITextModel> textModel(Utils<ITextScriptUtils>()->QueryTextModel(textScript));		
		//Paragraph range
		RangeData range = Utils<ITextScriptUtils>()->GetScriptTextRange(textScript);
		
		ScriptData scriptData;
		status = data->ExtractRequestData(p_TextCompEngine, scriptData);
		if (status != kSuccess)
		{
			Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, p_TextCompEngine);
			break; 
		}
		
		CmdUtils::SequencePtr cmdSeq;
		
		WideString newComposer;
		scriptData.GetWideString(newComposer);				
		ClassID composerToApply = GetComposerClassID(newComposer);	
		if(composerToApply == kInvalidClass)
		{
			status = Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, p_TextCompEngine);
			break;
		}
		
		//Set composer
		status = ChangeTextAttribute<ITextAttrClassID>(textModel, kParaAttrStrandBoss, kTextAttrComposerBoss, range, composerToApply);
		if(status != kSuccess)
			break;
		
		ScriptID enumData;
		status = GetEnum(data, parent, p_BscMELang, enumData);
		if(status != kSuccess)
			break;
		
		ICompositionStyle::ParagraphDirection dirPara;
		IDirOverrideAttr::DirOverride dirOverride = IDirOverrideAttr::kDirOverrideDefault;
		IJustificationStyle::JustificationMethod justify;
		ICompositionStyle::TextAlignment alignment;
		switch(enumData.Get())
		{
			case en_BscMeArabic:
				dirPara = ICompositionStyle::kParagraphDirRTL;
				justify = IJustificationStyle::kJustifMethodArabic;
				alignment = ICompositionStyle::kTextAlignRight;
				break;
				
			case en_BscMEHebrew:
				dirPara = ICompositionStyle::kParagraphDirRTL;
				justify = IJustificationStyle::kJustifMethodArabic;
				alignment = ICompositionStyle::kTextAlignRight;
				break;
				
			case en_BscMERoman:
			default:
				dirPara = ICompositionStyle::kParagraphDirLTR;
				justify = IJustificationStyle::kJustifMethodDefault;
				alignment = ICompositionStyle::kTextAlignLeft;
				break;
		}

		status = ChangeTextAttribute<IParagraphDirAttr>(textModel, kParaAttrStrandBoss, kParagraphDirAttrBoss, range, dirPara);
		if(status != kSuccess)
			break;
		
		status = ChangeTextAttribute<IDirOverrideAttr>(textModel, kCharAttrStrandBoss, kDirOverrideAttrBoss, range, dirOverride);
		if(status != kSuccess)
			break;

		status = ChangeTextAttribute<IJustifMethodAttr>(textModel, kParaAttrStrandBoss, kJustifMethodAttrBoss, range, justify);
		if(status != kSuccess)
			break;
		
		status = ChangeTextAttribute<ITextAttrAlign>(textModel, kParaAttrStrandBoss, kTextAttrAlignmentBoss, range, alignment);
		
		//digits attribute, kDigitsAttrBoss
		//diacritics position attribute, kDiacVPosAttrBoss		
		//kashida attribute ON/OFF, kKashidaAttrBoss
		
		PMString displayFamilyName, fontStyle;
		displayFamilyName.SetTranslatable(kFalse);
		fontStyle.SetTranslatable(kFalse);
		
		status = data->ExtractRequestData(p_BscMEFont, scriptData);
		if (status != kSuccess)
		{
			Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, p_BscMEFont);
			break; 
		}
		scriptData.GetPMString(displayFamilyName);
		
		//The parent of kBscMEObjectScriptElement is application, so get document through text model instead of active context
		IDataBase* targetDB = ::GetDataBase(textModel);
		InterfacePtr <IDocument> document (targetDB, targetDB->GetRootUID(), UseDefaultIID());
		ASSERT(document);
		if(!document)
			break;
		
		InterfacePtr<IDocFontMgr> iDocFontMgr(document->GetDocWorkSpace(), UseDefaultIID());
		if (iDocFontMgr == nil)
		{
			ASSERT(iDocFontMgr);
			break;
		} 

		UID fontUID = iDocFontMgr->GetFontFamilyUID(displayFamilyName, fontStyle);
		if(fontUID == kInvalidUID)
			break;
		
		status = ChangeTextAttribute<ITextAttrUID>(textModel, kCharAttrStrandBoss, kTextAttrFontUIDBoss, range, fontUID);

	} while(false);
	 
	return status;
}

ClassID BscMEScriptProvider::GetComposerClassID(const WideString& composerName)
{
	if(composerName == WideString("Adobe Paragraph Composer"))
	{
		return kParagraphComposerBoss;
	}
	else if(composerName == WideString("Adobe Single-line Composer"))
	{
		return kSingleLineComposerBoss;
	}
	else if(composerName == WideString("Adobe World-Ready Paragraph Composer"))
	{
		//ME paragraph composer
		return kOptycaParagraphComposerBoss;
	}
	else if(composerName == WideString("Adobe World-Ready Single-line Composer"))
	{
		//ME single-line composer
		return kOptycaSingleComposerBoss;
	}
	return kInvalidClass;		
}

template <typename I, typename V>
ErrorCode BscMEScriptProvider::ChangeTextAttribute(ITextModel* textModel, ClassID strandBoss, ClassID attrBoss, const RangeData& range, V attrVal)
{
	InterfacePtr<I> iAttr(static_cast<I*>(::CreateObject(attrBoss, I::kDefaultIID)) );
	if (iAttr)
	{
		iAttr->Set(attrVal);
		InterfacePtr<ICommand> cmd(Utils<ITextAttrUtils>()->BuildApplyTextAttrCmd(textModel, range, iAttr, strandBoss));
		return CmdUtils::ProcessCommand(cmd);
	}
	return kFailure;
}

int32 BscMEScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	return 1;
}

ErrorCode BscMEScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )
{
	ASSERT(data->GetDesiredType() == c_BscME);
	ASSERT_MSG(n >= 0 && n < this->GetNumObjects(data, parent), "Index out of bounds");
	Utils<IScriptUtils> scriptUtils;
	InterfacePtr<IScript> bscme(scriptUtils->CreateProxyScriptObject(data->GetRequestContext(), kBscMEScriptObjectBoss, c_BscME, parent, n));
	objectList.push_back(bscme);
	return kSuccess;
}

ErrorCode BscMEScriptProvider::GetEnum(IScriptRequestData* data, IScript* parent, ScriptID scriptID, ScriptID& enumData, bool16 required)
{
	ScriptData scriptData;
	if (data->ExtractRequestData(scriptID, scriptData) != kSuccess)
	{
			return required ? Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID) : kFailure;
	}
	
	if(scriptData.GetEnumeration(&enumData) == kSuccess)
	{
		return kSuccess;
	}
	else
	{
		return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, scriptID);
	}
}

ErrorCode BscMEScriptProvider::GetInt32(IScriptRequestData* data, IScript* parent, ScriptID scriptID, int32& intData, bool16 required)
{
	ScriptData scriptData;
	if (data->ExtractRequestData(scriptID, scriptData) != kSuccess)
	{
		return required ? Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID) : kFailure;
	}
	
	if(scriptData.GetInt32(&intData) == kSuccess)
	{
		return kSuccess;
	}
	else
	{
		return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, scriptID);
	}
}

ErrorCode BscMEScriptProvider::GetBoolean(IScriptRequestData* data, IScript* parent, ScriptID scriptID, bool16& boolData, bool16 required)
{
	ScriptData scriptData;
	if (data->ExtractRequestData(scriptID, scriptData) != kSuccess)
	{
		return required ? Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID) : kFailure;
	}
	
	if(scriptData.GetBoolean(&boolData) == kSuccess)
	{
		return kSuccess;
	}
	else
	{
		return Utils<IScriptErrorUtils>()->SetInvalidParameterErrorData(data, scriptID);
	}
}			


IScript* BscMEScriptProvider::QueryScript(IScriptRequestData* data, IScript* parent, ScriptID scriptID)
{
	ScriptData scriptData;
	if (data->ExtractRequestData(scriptID, scriptData) != kSuccess)
	{
		Utils<IScriptErrorUtils>()->SetMissingRequiredParameterErrorData(data, scriptID);
		return nil;
	}
	
	return scriptData.QueryObject();
}

