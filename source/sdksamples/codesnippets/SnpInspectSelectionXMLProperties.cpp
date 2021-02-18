//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectSelectionXMLProperties.cpp $
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


#include "ICellContent.h"
#include "IFrameType.h"
#include "IGraphicFrameData.h"
#include "IHierarchy.h"
#include "IIDXMLElement.h"
#include "ILayoutTarget.h"
#include "ITableModel.h"
#include "ITableTarget.h"
#include "IMultiColumnTextFrame.h"
#include "ITextFrameColumn.h"
#include "ITextTarget.h"
#include "IXMLNodeTarget.h"
#include "IXMLReferenceData.h"
#include "IXMLUtils.h"



// General includes:
#include "XMLContentIterator.h"
#include "UIDList.h"
// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"
#include "SnpTextModelHelper.h"
#include "SDKFileHelper.h"
#include "SnpXMLHelper.h"
#if __INTEL_COMPILER || MACINTOSH
#include "K2Vector.tpp"
#endif

//-- SNIP

// --------------------------------- 
/** Code that inspects XML-related properties of objects.

  	@ingroup sdk_snippet
	@ingroup sdk_xmedia

 */
class SnpInspectSelectionXMLProperties
{
	public:

		/**	Report on the XML-related properties of a list of XML elements.
			@param elements specifies elements (see IIDXMLElement)
			
		 */
		void Inspect(const K2Vector<XMLReference>& elements);

		/**	Report on the XML-related  properties of a list of UID-based objects in the document
			@param uidList specifies objects of interest
			 
		 */
		void Inspect(const UIDList& uidList);

		/** Report on XML-related properties properties of a single XML element
			@param xmlRef specifies element (IIDXMLElement) of interest
			
		*/
		void Inspect(const XMLReference& xmlRef);

		/**	Report on XML-related properties properties of a single 
				UID-based object; this could be something like a graphic frame
				which contains an image or text.

			@precondition objectUIDRef should allow IFrameType to be instantiated
			@param objectUIDRef object of interest
			 
		 */
		void Inspect(const UIDRef& objectUIDRef);

		/**	Report on XML-related properties of a range of text
			@param textModelUIDRef 
			@param textRange 
			 
		 */
		void InspectText(const UIDRef& textModelUIDRef, const RangeData& textRange);

		/**	Report on XML-related properties of a range of cells in table
			@precondition tableModelUIDRef should allow ITableModel to be instantiated
			@param tableModelUIDRef 
			@param gridArea specifies cells of interest
			
			 
		 */
		void InspectTable(const UIDRef& tableModelUIDRef, const GridArea& gridArea);
		

		/**	Report on properties of a graphic frame
			@param uidRef specifies frame of interest
			@precondition uidRef should allow IGraphicFrameData to be instantiated
		 */
		void InspectLayoutObject(const UIDRef& uidRef);

		/**	Report XML properties of a text frame, including info about the
			XML elements in the span of the frame
			@precondition uidRef should allow IHierarchy to be instantiated
			@param uidRef text frame
		 */
		void InspectTextFrame(const UIDRef& uidRef);

};

/*
*/
void SnpInspectSelectionXMLProperties::Inspect(const K2Vector<XMLReference>& elements)
{
	do {
		
		K2Vector<XMLReference>::const_iterator iter;
		for(iter = elements.begin(); iter != elements.end(); iter++) {
			SNIPLOG("Inspecting element from list of XMLReference: ");
			XMLReference nextXMLRef = *iter;
			this->Inspect(nextXMLRef);

		}
		
	} while(kFalse);

}

/*
*/
void SnpInspectSelectionXMLProperties::Inspect(const XMLReference& xmlRef)
{
	do {
		SnpXMLHelper xmlHelper;
		PMString elemDesc = xmlHelper.AsString(xmlRef);
		SNIPLOG("Element: %s", elemDesc.GetPlatformString().c_str());
		InterfacePtr<IIDXMLElement> element(xmlRef.Instantiate());
		if(!element) {
			break;
		}
		XMLContentIterator iter(element->begin());
		for(; iter != element->end(); iter++) {
			InDesign ::TextRange range = *iter;
			if(range.Length()>0) {
				SnpTextModelHelper textModelHelper;
				WideString wstr = textModelHelper.GetWideStringFromTextRange(range);
				PMString str(wstr);
				SNIPLOG("Text from XMLContentIterator; %s", str.GetPlatformString().c_str());
			}
		}
		
	} while(kFalse);

}

	
/*
*/
void SnpInspectSelectionXMLProperties::Inspect(const UIDList& uidList)
{
	do {

		for(int32 i=0; i < uidList.Length(); i++) {
			UIDRef nextUIDRef = uidList.GetRef(i);
			this->Inspect(nextUIDRef);
			
		}
		
	} while(kFalse);

}

/*
*/
void SnpInspectSelectionXMLProperties::InspectText(const UIDRef& textModelUIDRef,
														  const RangeData& textRange)
{
	do {
		InterfacePtr<ITextModel> textModel(textModelUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if(!textModel) {
			break;
		}
		SNIPLOG("InspectText for range [%d,%d]", textRange.Start(nil), textRange.End());
		SnpXMLHelper xmlHelper;
		PMString textModelClassName =
				xmlHelper.GetClassFrom(::GetClass(textModel));
		SNIPLOG("Text model class = %s", textModelClassName.GetPlatformString().c_str());

		InterfacePtr<IXMLReferenceData> xmlReferenceData( textModel, UseDefaultIID());
		ASSERT(xmlReferenceData);
		if(!xmlReferenceData) {
			break;
		}
		XMLReference xmlRef = xmlReferenceData->GetReference();
		InterfacePtr<IIDXMLElement> element(xmlRef.Instantiate());
		if(element) {
			SNIPLOG("Element: %s", xmlHelper.AsString(xmlRef).GetPlatformString().c_str());
		} else {
			SNIPLOG("NOT CURRENTLY TAGGED");
			break;
		}

		if(textRange.Length()==0) {
			break;
		}
		
		TextIndex startIndexInParent = kInvalidTextIndex;
		TextIndex endIndexInParent = kInvalidTextIndex;
		K2Vector<XMLReference> childRefList;
		XMLReference endParentXMLRef;
		int32 doCalc = Utils<IXMLUtils>()->CalcXMLParent( xmlRef, startIndexInParent, 
												childRefList, endParentXMLRef, 
												endIndexInParent, 
												textRange.Start(nil),
												textRange.End(),
												textModel) ;
		if(doCalc == IXMLUtils::kSuccessCalc) {
			SNIPLOG("Inspecting childRefList:");
			this->Inspect(childRefList);
		} else {
			PMString calcRes("Undefined error");
			switch(doCalc) {
				case IXMLUtils::kStartUnmatched: { calcRes = "kStartUnmatched"; break;}
				case IXMLUtils::kEndUnmatched: { calcRes = "kEndUnmatched"; break;}
				case IXMLUtils::kBothUnmatched: { calcRes = "kBothUnmatched"; break;}
			}
			SNIPLOG("CalcXMLParent failed with errorcode %s", calcRes.GetPlatformString().c_str());
		}
		
	} while(kFalse);

}
/*
*/
void SnpInspectSelectionXMLProperties::Inspect(const UIDRef& objectUIDRef)
{
	
	do {
		InterfacePtr<IFrameType> frameType(objectUIDRef, UseDefaultIID());
		if(!frameType) {
			break; // Some selections won't have a frame type.
		}
		switch(frameType->GetFrameType()) {
			case IFrameType::kGraphicFrame : 
			case IFrameType::kEmptyGraphicFrame:
			case IFrameType::kGraphicFrameWithPlaceHolder:
			{
				this->InspectLayoutObject(objectUIDRef);
			} 
			break;

			case IFrameType::kTextFrame :
			case IFrameType::kEmptyTextFrame :
			{
				this->InspectTextFrame(objectUIDRef);
			} 
			break;


		}
		
	} while(kFalse);
	
}

/*
*/
void SnpInspectSelectionXMLProperties::InspectTable(const UIDRef& tableModelUIDRef, const GridArea& gridArea)
{
	do {
		// precondition; is it really table
		InterfacePtr<ITableModel> tableModel(tableModelUIDRef, UseDefaultIID());
		if(!tableModel) {
			break;
		}
		//
		InterfacePtr<IXMLReferenceData> xmlReferenceData(tableModelUIDRef, UseDefaultIID());
		// Hmmm... we can get a table target but no tagged table,
		// so let's not assert here
		if(!xmlReferenceData) {
			break;
		}

		InterfacePtr<IIDXMLElement> element(xmlReferenceData->GetReference().Instantiate());
		ASSERT(element);
		if(!element) {
			break;
		}
		SNIPLOG("Inspecting GridArea, span [r=%d,c=%d] to [r=%d,c=%d]",
				gridArea.GetTopLeft().row,
				gridArea.GetTopLeft().col,
				gridArea.GetBottomRight().row,
				gridArea.GetBottomRight().col);
		PMString desc;
		XMLContentReference contentRef = element->GetContentReference();
		desc += "ContentRef UID = ";
		desc.AppendNumber(contentRef.GetUID().Get());
		if(contentRef.IsTable()) {
			desc += "Table Content\n";
		} else if(contentRef.IsTableCell()) {
			desc += "Table Cell\n";
		} 
		SNIPLOG("InspectTable: %s", desc.GetPlatformString().c_str());
		ITableModel::const_iterator iterTable(tableModel->begin(gridArea));
		ITableModel::const_iterator endTable(tableModel->end(gridArea));
		while (iterTable != endTable)
		{
			GridAddress gridAddress = (*iterTable);         
			InterfacePtr<ICellContent> cellContent(tableModel->QueryCellContentBoss(gridAddress));
			ASSERT(cellContent);
			if(cellContent == nil) 
			{
				break;
			}
			InterfacePtr<IXMLReferenceData> cellXMLReferenceData(cellContent, UseDefaultIID());
			ASSERT(cellXMLReferenceData);
			if(!cellXMLReferenceData) {
				break;
			}
			XMLReference cellXMLRef = cellXMLReferenceData->GetReference();
			InterfacePtr<IIDXMLElement> cellXMLElement(cellXMLRef.Instantiate());
			if(cellXMLElement) {
				SNIPLOG("CELL XML Element:");
				this->Inspect(cellXMLElement->GetXMLReference());
				
			}
			++iterTable;
		}   

	} while(kFalse);

}

/*
*/
void SnpInspectSelectionXMLProperties::InspectLayoutObject(const UIDRef& uidRef)
{
	do {
		InterfacePtr<IGraphicFrameData> graphicFrame(uidRef, UseDefaultIID());
		ASSERT(graphicFrame);
		if(!graphicFrame) {
			break;
		}
		SnpXMLHelper xmlHelper;
		PMString className = xmlHelper.GetClassFrom(::GetClass(graphicFrame));
		SNIPLOG("--- InspectLayoutObject ---\n Class = %s", className.GetPlatformString().c_str());
		SNIPLOG("Taggable? %d", Utils<IXMLUtils>()->IsTaggablePageItem(graphicFrame));

		InterfacePtr<IHierarchy> graphicFrameHierarchy(graphicFrame, UseDefaultIID());
		ASSERT(graphicFrameHierarchy);
		if(!graphicFrameHierarchy) {
			break;
		}
		InterfacePtr<IHierarchy> childHierarchy(graphicFrameHierarchy->QueryChild(0));
		if(childHierarchy) {
			PMString childClassName =
				xmlHelper.GetClassFrom(::GetClass(childHierarchy));
			SNIPLOG("Child class = %s", childClassName.GetPlatformString().c_str());
			SNIPLOG("Taggable? %d", Utils<IXMLUtils>()->IsTaggablePageItem(childHierarchy));

			InterfacePtr<IXMLReferenceData> xmlReferenceData(childHierarchy, UseDefaultIID());
			ASSERT(xmlReferenceData);
			if(!xmlReferenceData) {
				break;
			}
			XMLReference xmlRef = xmlReferenceData->GetReference();
			InterfacePtr<IIDXMLElement> element(xmlRef.Instantiate());
			if(element) {
				SNIPLOG("Element: %s", xmlHelper.AsString(xmlRef).GetPlatformString().c_str());
			} else {
				SNIPLOG("NOT CURRENTLY TAGGED");
			}
			
			
		}
	
	} while(kFalse);
}

void SnpInspectSelectionXMLProperties::InspectTextFrame(const UIDRef& uidRef)
{
	do {
		InterfacePtr<IHierarchy> hierarchy(uidRef, UseDefaultIID());
		ASSERT(hierarchy);
		if(!hierarchy) {
			break;
		}
		SnpXMLHelper xmlHelper;
		PMString outermostClassName =
				xmlHelper.GetClassFrom(::GetClass(hierarchy));
		SNIPLOG("Outermost class = %s", outermostClassName.GetPlatformString().c_str());

		InterfacePtr<IHierarchy> childHierarchy(hierarchy->QueryChild(0));
		if(childHierarchy) {
			PMString childClassName =
				xmlHelper.GetClassFrom(::GetClass(childHierarchy));
			SNIPLOG("Child class = %s", childClassName.GetPlatformString().c_str());
			InterfacePtr<IMultiColumnTextFrame> mcfTextFrame(childHierarchy, UseDefaultIID());
			ASSERT(mcfTextFrame);
			if(!mcfTextFrame) {
				break;
			}
			InterfacePtr<ITextModel> textModel(mcfTextFrame->QueryTextModel());
			ASSERT(textModel);
			if(!textModel) {
				break;
			}
			
			for(int32 i = 0; i < childHierarchy->GetChildCount(); i++) {
				InterfacePtr<IHierarchy> tfHierarchy(childHierarchy->QueryChild(i));
				ASSERT(tfHierarchy);
				if(!tfHierarchy) {
					break;
				}
				PMString grandChildClassName =
					xmlHelper.GetClassFrom(::GetClass(tfHierarchy));
				SNIPLOG("Grand-child class = %s", grandChildClassName.GetPlatformString().c_str());
		
				InterfacePtr<ITextFrameColumn> childTFC(tfHierarchy, UseDefaultIID());
				ASSERT(childTFC);
				if(!childTFC) {
					break;
				}
				TextIndex startIndex = childTFC->TextStart();
				int32 span = childTFC->TextSpan();
				if(span > 1) {
					RangeData aRange(startIndex, startIndex + span);
					this->InspectText(::GetUIDRef(textModel), aRange);
				}
				
			}

		}
	
	} while(kFalse);
}


// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpInspectSelectionXMLProperties available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerInspectSelectionXMLProperties : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerInspectSelectionXMLProperties();

		/** Destructor.
		 */
		virtual			~_SnpRunnerInspectSelectionXMLProperties();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTextTargetContext;}
};

/* Describe your snippet to the framework here.
*/
_SnpRunnerInspectSelectionXMLProperties::_SnpRunnerInspectSelectionXMLProperties() : SnpRunnable("InspectSelectionXMLProperties")
{
	this->SetDescription("Inspect XML-related properties of a selection");
	this->SetPreconditions("open document with some kind of selection");
	this->SetCategories("sdk_snippet, sdk_xmedia");
}

/* Destructor.
*/
_SnpRunnerInspectSelectionXMLProperties::~_SnpRunnerInspectSelectionXMLProperties()
{
}

/* Check if your snippet's preconditions are met here.
*/
bool16	_SnpRunnerInspectSelectionXMLProperties::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		InterfacePtr<IXMLNodeTarget> xmlNodeTarget(runnableContext, UseDefaultIID()); 
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID()); 
		InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID()); 
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID()); 
	result =  (xmlNodeTarget != nil) || (tableTarget != nil) || (textTarget != nil) || (layoutTarget != nil);
	} while(false);
	return result;
}

/* Set up and call your snippet here.
*/
ErrorCode _SnpRunnerInspectSelectionXMLProperties::Run(ISnpRunnableContext* runnableContext)
{
	SnpInspectSelectionXMLProperties inspector;
	
	InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
	if(layoutTarget) {
		inspector.Inspect(layoutTarget->GetUIDList(kStripStandoffs));
	}

	InterfacePtr<ITextTarget> textTarget(runnableContext, UseDefaultIID());
	if(textTarget) {
		inspector.InspectText(textTarget->GetTextModel(), 
			textTarget->GetRange());
	}

	InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
	if(tableTarget) {
		inspector.InspectTable(tableTarget->GetModel(), tableTarget->GetRange());
	}

	InterfacePtr<IXMLNodeTarget> xmlNodeTarget(runnableContext, UseDefaultIID());
	if(xmlNodeTarget) {
		inspector.Inspect(xmlNodeTarget -> GetAllNodeList ());
	} 
	
	
	return kSuccess;
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerInspectSelectionXMLProperties instance_SnpRunnerInspectSelectionXMLProperties;
DEFINE_SNIPPET(_SnpRunnerInspectSelectionXMLProperties) 	
