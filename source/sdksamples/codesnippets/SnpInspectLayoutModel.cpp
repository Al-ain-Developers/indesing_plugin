//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectLayoutModel.cpp $
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

// Interfaces:
#include "ICommand.h"
#include "IDataBase.h"
#include "IDocument.h"
#include "IDocumentLayer.h"
#include "IGeometry.h"
#include "IHierarchy.h"
#include "IInlineData.h"
#include "IItemStrand.h"
#include "ILayerList.h"
#include "IMasterPage.h"
#include "IMasterSpread.h"
#include "IMasterSpreadList.h"
#include "IPageList.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "ISpreadList.h"
#include "IStoryList.h"
#include "ITextModel.h"
#include "ILayoutTarget.h"
#include "IGraphicFrameData.h"


// General:
#include "CmdUtils.h"
#include "DebugClassUtils.h"
#include "DocumentID.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "K2VectorBase.h"
#include "KeyValuePair.h"
#include "ILayoutUIUtils.h"
#include "OwnedItemDataList.h"
#include "IPathUtils.h"
#include "PersistUtils.h"
#include "TextID.h"
#include "TextOnPathID.h"
#include "TransformUtils.h"
#include "UIDList.h"
#include "IGeometryFacade.h"

// SDK Includes:
#include "SDKLayoutHelper.h"

// Framework includes:
#include "SnpRunnable.h"
#include "SnipRunLog.h"
#include "ISnipRunParameterUtils.h"

/**
	\li How to examine the layout content in a document,
	\li reports spreads, layers, frames, frame content and guides,
	\li teaches you the structure of the layout model,
	\li lets you peek under the hood IHierarchy, IGeometry and ITransform.

	Reports the organisation and geometry of layout content in a document or in a selection of items. 
	To inspect the entire document run the snippet with nothing selected. To inspect specific items 
	select them then run the snippet.

	Documents are made up of one or more spreads(ISpreadList). Each spread(ISpread) contains 
	one or more pages. A document has a list(ILayerList) of document layers(IDocumentLayer) 
	that can be shown, hidden, locked, unlocked and arranged in their z-order. 
	
	Each spread has a set of spread layers(ISpreadLayer) that map to 
	their corresponding document layer. The spread has a tree structure (accessed via 
	interface IHierarchy) whose children are spread layers. The children of each of the 
	spread layers are the frames (IGraphicFrameData) that contain pictorial or 
	textual content and guides. The children of the frames vary depending on what the frame
	contains. For example an EPS image would be have a kEPSItem child. A text frame would
	have a kMultiColumnItemBoss which on turn would have one or more kFrameItemBoss objects
	(one per column).
	
	The methods in this snippet navigate the IHierarchy tree and report on the objects
	they discover.

	Document layers are the layers the user sees in the layers panel. In addition there 
	is a special layer, the pages layer, which is not displayed in the layer panel. This 
	layer is where the page objects live that draw the outline of each page and its drop 
	shadow. The page object also maintains a reference to its associated master page.

	For each document layer there are two spread layers, one that owns the layer's frames 
	and another that owns the layer's guides.

	Content and guides are owned by spread layers _not_ by pages (when executing page
	operations the application considers whether a page item lies within the page area 
	by comparing the bounding box of the item and the bounding box of the page).
	
	Stories can contain inline frames (IInlineData) embedded in the text. The child of
	an inline frame is a regular graphic frame (IGraphicFrameData), normally a 
	kSplineItemBoss, that contains a picture or other text. Like other layout objects
	inline frames have an IHierarchy but instead of being rooted on a spread they are
	rooted on a kInlineBoss that is an owned item in a story.

	@ingroup sdk_snippet
	@ingroup sdk_layout

	@see IDocument
	@see ISpreadList
	@see ISpread
	@see ISpreadLayer
	@see ILayerList
	@see IDocumentLayer
	@see IGraphicFrameData
	@see IHierarchy
	@see ITransform
	@see IGeometry
	@see IInlineData
*/
class SnpInspectLayoutModel 
{
	public:
		/** Constructor.
		 */
		SnpInspectLayoutModel() {}

		/** Destructor.
		 */
		virtual			~SnpInspectLayoutModel() {}

		/** Inspect the layout model by traversing the hierarchy(IHierarchy)
			of the given items.
			@param itemList items to report on.
		 */
		void			ReportItems(const UIDList& itemList);

		/** Inspect the layout model of the entire document.
		 */
		void			ReportDocument(const UIDRef& docUIDRef);

		/** Traverses the hierarchy(IHierarchy) for each
			spread and master spread in the document and reports the
			page items.
		 */
		void			ReportDocumentByHierarchy(const UIDRef& docUIDRef);
	    
		/**	Iterates each spread and master spread in the
			document and reports the page items associated with each
			document layer.

			Document layers are the layers the user sees in the layers
			panel. In addition there is a special layer, the pages
			layer, which is not displayed in the layer panel. This
			layer is where kPageBoss objects live. The pages layer
			is always at index 0 in the document's ILayerList.

			For each document layer there are two corresponding
			spread layers. One for content and one for guides.
		 */
		void			ReportDocumentByDocumentLayer(const UIDRef& docUIDRef);

		/**	Iterate over the spreads in the document and traverse each
			spread's hierarchy of page items reporting their geometry
			and transformation matrix.
		 */
		void			ReportDocumentGeometry(const UIDRef& docUIDRef);

		/** Iterate the stories in the document and report each inline 
			(kInlineBoss) anchored in the text.
		*/
		void 			ReportDocumentByHierarchyOfInlines(const UIDRef& docUIDRef);

		/** Iterate the owned items in the given story and report the inline
			frames (IInlineData) by traversing their hierarchy (IHierarchy).
			@param storyUIDRef
			@param Callback that will report on each IHierarchy node.
		 */
		void			InspectStoryInlines(const UIDRef& storyUIDRef, void (*Callback)(IHierarchy*));

		/**	Recursive method that visits each node in the given
			hierarchy and calls the supplied Callback method.
			@param parent hierarchy
			@param Callback that reports each node.
		*/
		void			TraverseIHierarchy(IHierarchy* parent, void (*Callback)(IHierarchy*));
		
		/**	Iterates over each document layer and
			reports the objects found on its associated content and 
			guide spread layers of the given spread.
		*/
		void			InspectSpreadByDocumentLayer(ISpread* spread);

		/**	Reported spread geometry.
			@param objectUIDRef 
		 */
		void			TraceSpreadGeometry(const UIDRef& objectUIDRef);

		/** Callback functions used to generate reports as the
			page item hierarchy is traversed. These methods are
			all declared as static so they can be used as 
			callback functions with TraverseIHierarchy.
		 */
		//@{
			static void			Indent(int32 level);
			static void			TraceNode(IHierarchy* node);
			static void			TraceNodeGeometryAndTransform(IHierarchy* node);
			static int32		TraceBoss(IPMUnknown* unknown);
			static int32		TraceBoss(IDataBase* database, const UID& uid);
			static void			TraceLayerName(const char* msg, IHierarchy* spreadLayer);
			static void			TracePMMatrix(const char* msg, const PMMatrix& m);
			static void			TracePMRect(const char* msg, const PMRect& bBox);
			static void			TraceGeometry(IGeometry* geometry);
			static void			TraceTransform(ITransform* transform);
			static void			TracePageNode(IHierarchy* node);
			static UIDRef		GetDocumentUIDRef(IPMUnknown* unknown);
			static IDocument*	QueryDocument(IPMUnknown* unknown);

		#ifndef DEBUG // release build only.
		private:
			// Provide some ClassID names under the release build.
			static PMString		LookupClassName(const ClassID& classID);
		#endif
		//@}
private:
	// Used for indenting reports.
	enum {eBuffSize=512};

	static char fPadBuf[eBuffSize];

};
char SnpInspectLayoutModel::fPadBuf[SnpInspectLayoutModel::eBuffSize];

/*
*/
void SnpInspectLayoutModel::ReportItems(const UIDList& itemList)
{
	do {
		// Ask what is to be inspected?
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("hierarchy"));
		choices.push_back(PMString("geometry"));
		choices.push_back(PMString("inline frame hierarchy"));
		choices.push_back(PMString("inline frame geometry"));
		int32 choice = parameterUtils->GetChoice(PMString("Report selection by..."), choices);
		enum {kReportHierarchy, kReportGeometry, kReportInlineHierarchy, kReportInlineGeometry};
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Produce requested report on the selected items.
		switch (choice)
		{
		case kReportHierarchy:
			{
				SNIPLOG("ReportItemsByHierarchy() ********Begin");
				for (int32 i = 0; i < itemList.Length(); i++) {
					InterfacePtr<IHierarchy> hierarchy(itemList.GetRef(i), UseDefaultIID());
					if (hierarchy) {
						TraceNode(hierarchy);
						this->TraverseIHierarchy(hierarchy, TraceNode);
					}
				}	
				SNIPLOG("ReportItemsByHierarchy() ********End");
				break;
			}
		case kReportGeometry:
			{
				SNIPLOG("ReportItemsByGeometry() ********Begin");
				for (int32 i = 0; i < itemList.Length(); i++) {
					InterfacePtr<IHierarchy> hierarchy(itemList.GetRef(i), UseDefaultIID());
					if (hierarchy) {
						TraceNodeGeometryAndTransform(hierarchy);
						TraverseIHierarchy(hierarchy, TraceNodeGeometryAndTransform);
					}
				}
				SNIPLOG("ReportItemsByGeometry() ********End");
				break;
			}
		case kReportInlineHierarchy:
			{
				SNIPLOG("ReportItemsByInlineHierarchy() ********Begin");
				for (int32 i = 0; i < itemList.Length(); i++) {
					InterfacePtr<IGraphicFrameData> graphicFrameData(itemList.GetRef(i), UseDefaultIID());
					ASSERT(graphicFrameData);
					if (!graphicFrameData) {
						break;
					}
					SDKLayoutHelper layoutHelper;
					UIDRef storyUIDRef = layoutHelper.GetTextModelRef(graphicFrameData);
					if (storyUIDRef == UIDRef::gNull) {
						break;
					}
					this->InspectStoryInlines(storyUIDRef, TraceNode);		
				}
				SNIPLOG("ReportItemsByInlineHierarchy() ********End");
				break;
			}
		case kReportInlineGeometry:
			{
				SNIPLOG("ReportItemsByInlineGeometry() ********Begin");
				for (int32 i = 0; i < itemList.Length(); i++) {
					InterfacePtr<IGraphicFrameData> graphicFrameData(itemList.GetRef(i), UseDefaultIID());
					ASSERT(graphicFrameData);
					if (!graphicFrameData) {
						break;
					}
					SDKLayoutHelper layoutHelper;
					UIDRef storyUIDRef = layoutHelper.GetTextModelRef(graphicFrameData);
					if (storyUIDRef == UIDRef::gNull) {
						break;
					}
					this->InspectStoryInlines(storyUIDRef, TraceNodeGeometryAndTransform);		
				}
				SNIPLOG("ReportItemsByInlineGeometry() ********End");
				break;
			}

		default:
			{
				break;
			}
		}
	} while(false);
}

/*
*/
void SnpInspectLayoutModel::ReportDocument(const UIDRef& docUIDRef)
{
	do {
		// Ask what is to be inspected?
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back(PMString("hierarchy"));
		choices.push_back(PMString("layers"));
		choices.push_back(PMString("geometry"));
		choices.push_back(PMString("inline frames"));
		int32 choice = parameterUtils->GetChoice(PMString("Report document by..."), choices);
		enum {kReportHierarchy, kReportLayers, kReportGeometry, kReportInlines};
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Produce requested report on the entire document.
		switch (choice)
		{
		case kReportHierarchy:
			{
				this->ReportDocumentByHierarchy(docUIDRef);
				break;
			}
		case kReportLayers:
			{
				this->ReportDocumentByDocumentLayer(docUIDRef);
				break;
			}
		case kReportGeometry:
			{
				this->ReportDocumentGeometry(docUIDRef);
				break;
			}
		case kReportInlines:
			{
				this->ReportDocumentByHierarchyOfInlines(docUIDRef);
				break;
			}
		default:
			{
				break;
			}
		}
	} while(false);
}

/*
*/
void SnpInspectLayoutModel::ReportDocumentByHierarchy(const UIDRef& docUIDRef)
{
	SNIPLOG("ReportDocumentByHierarchy() ********Begin");
	
	// Get the document
	InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
	
	// SNIPLOG the document's name, class and uid
	TraceBoss(document);
	PMString documentName;
	document->GetName(documentName);
	SNIPLOG("%s", documentName.GetPlatformString().c_str());
	
	// Get the document's database
	IDataBase* database = ::GetDataBase(document);
	
	// Get the list of spreads in this document
	InterfacePtr<ISpreadList> spreadList(document, UseDefaultIID());
	
	// Iterate over all the spreads
	int32 spreadCount = spreadList->GetSpreadCount();
	for ( int32 spreadIndex = 0; spreadIndex < spreadCount; spreadIndex++ )
	{
		// Get the spread
		UIDRef spreadUIDRef(database, spreadList->GetNthSpreadUID(spreadIndex));
		InterfacePtr<IHierarchy> spreadHierarchy(spreadUIDRef, UseDefaultIID());
		
		// SNIPLOG the spread
		SNIPLOG("  Spread %d content by hierarchy...",  spreadIndex+1);	
		TraceBoss(spreadHierarchy);
				
		// Report the page item's on the spread by traversing its hierarchy
		TraverseIHierarchy(spreadHierarchy, TraceNode);
				
	} // iterate spreads
	

	// Get the list of master spreads in the document
	InterfacePtr<IMasterSpreadList> masterSpreadList(document, UseDefaultIID());
	
	// Iterate over all the master spreads	
	int32 masterSpreadCount = masterSpreadList->GetMasterSpreadCount();
	for ( int32 masterSpreadIndex = 0; masterSpreadIndex < masterSpreadCount; masterSpreadIndex++ )
	{
		// Get the master spread
		UIDRef masterSpreadUIDRef(database, masterSpreadList->GetNthMasterSpreadUID(masterSpreadIndex) );
		InterfacePtr<IMasterSpread> masterSpread(masterSpreadUIDRef, UseDefaultIID());
		
		// SNIPLOG the master spread
		PMString masterSpreadName;
		masterSpread->GetName(&masterSpreadName);
		SNIPLOG("  %s master spread content by hierarchy...", masterSpreadName.GetPlatformString().c_str());
		TraceBoss(masterSpread);

		// Report the page item's on the master by traversing its hierarchy
		InterfacePtr<IHierarchy> masterSpreadHierarchy(masterSpread, UseDefaultIID());
		TraverseIHierarchy(masterSpreadHierarchy, TraceNode);
				
	} // iterate master spreads
	
	SNIPLOG("ReportDocumentByHierarchy() ********End");
}

/*
*/
void SnpInspectLayoutModel::ReportDocumentByHierarchyOfInlines(const UIDRef& docUIDRef)
{
	SNIPLOG("ReportDocumentByHierarchyOfInlines() ********Begin");
	
	// Get the document
	InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
	
	TraceBoss(document);
	PMString documentName;
	document->GetName(documentName);
	SNIPLOG("%s", documentName.GetPlatformString().c_str());
	
	// Get the list of stories in this document
	InterfacePtr<IStoryList> storyList(document, UseDefaultIID());
	
	// Iterate over all the user accessible stories
	int32 storyCount = storyList->GetUserAccessibleStoryCount();
	for (int32 storyIndex = 0; storyIndex < storyCount; storyIndex++)
	{
		// Get the story boss
		UIDRef storyUIDRef = storyList->GetNthUserAccessibleStoryUID(storyIndex);
		this->InspectStoryInlines(storyUIDRef, TraceNode);
	}

	SNIPLOG("ReportDocumentByHierarchyOfInlines() ********End");
}

/*
*/
void SnpInspectLayoutModel::ReportDocumentByDocumentLayer(const UIDRef& docUIDRef)
{
	SNIPLOG("ReportDocumentByDocumentLayer() ********Begin");
	
	// Get the document
	InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
	
	// SNIPLOG the document's name, class and uid
	TraceBoss(document);
	PMString documentName;
	document->GetName(documentName);
	SNIPLOG("%s", documentName.GetPlatformString().c_str());

	// Get the document's database
	IDataBase* database = ::GetDataBase(document);
	
	// Iterate over all the normal spreads
	InterfacePtr<ISpreadList> spreadList(document, UseDefaultIID());
	int32 spreadCount = spreadList->GetSpreadCount();
	for ( int32 spreadIndex = 0; spreadIndex < spreadCount; spreadIndex++ )
	{
		// Get the spread
		UIDRef spreadUIDRef(database, spreadList->GetNthSpreadUID(spreadIndex) );
		InterfacePtr<ISpread> spread(spreadUIDRef, UseDefaultIID());
		
		// SNIPLOG the spread
		SNIPLOG("  Spread %d content by layer...", spreadIndex+1);
		TraceBoss(spread);
		
		// Report the spread's page items
		InspectSpreadByDocumentLayer(spread);
		
		SNIPLOG("");
		
	} // iterate normal spreads

		
	// Iterate over all the master spreads
	InterfacePtr<IMasterSpreadList> masterSpreadList(document, UseDefaultIID());
	int32 masterSpreadCount = masterSpreadList->GetMasterSpreadCount();
	for ( int32 masterSpreadIndex = 0; masterSpreadIndex < masterSpreadCount; masterSpreadIndex++ )
	{
		// Get the master spread
		UIDRef masterSpreadUIDRef(database, masterSpreadList->GetNthMasterSpreadUID(masterSpreadIndex) );
		InterfacePtr<IMasterSpread> masterSpread(masterSpreadUIDRef, UseDefaultIID());
		
		// SNIPLOG the master spread
		PMString masterSpreadName;
		masterSpread->GetName(&masterSpreadName);
		SNIPLOG("  %s master spread content by layer...", masterSpreadName.GetPlatformString().c_str());
		TraceBoss(masterSpread);

		// Report the spread's page items
		InterfacePtr<ISpread> spread(masterSpreadUIDRef, UseDefaultIID());
		InspectSpreadByDocumentLayer(spread);
		
		SNIPLOG("");
		
	} // iterate master spreads
	
	SNIPLOG("ReportDocumentByDocumentLayer() ********End");
}


/*
*/
void SnpInspectLayoutModel::InspectSpreadByDocumentLayer(ISpread* spread)
{	
	// Get the document that owns this spread
	InterfacePtr<IDocument> document(QueryDocument(spread));
		
	// Get the list of document layers
	InterfacePtr<ILayerList> layerList(document, IID_ILAYERLIST);
	
	// The document layer at index 0 is the pages layer
	InterfacePtr<IDocumentLayer> pagesDocumentLayer(layerList->QueryLayer(0));
	TraceBoss(pagesDocumentLayer);
	
	// Get its corresponding spread layer
	InterfacePtr<IHierarchy> pagesSpreadLayerHierarchy(spread->QueryPagesLayer());
	
	// Report the pages by traversing the pages spread layer
	TraceLayerName("Layer", pagesSpreadLayerHierarchy);
	TraverseIHierarchy(pagesSpreadLayerHierarchy, TracePageNode);
	
	// Iterate the normal document layers
	int32 layerCount = layerList->GetCount();
	for (int32 layerIndex = 1; layerIndex < layerCount; layerIndex++)
	{
		int32 spreadLayerPosition;
		
		// Get the document layer
		InterfacePtr<IDocumentLayer> documentLayer(layerList->QueryLayer(layerIndex));
		TraceBoss(documentLayer);

		// Get the content spread layer associated with the document layer
		InterfacePtr<ISpreadLayer> contentSpreadLayer
			(
				spread->QueryLayer
					(
						documentLayer,
						&spreadLayerPosition,
						kFalse
					)
			);
		
		// Report the content by traversing the content spread layer
		InterfacePtr<IHierarchy> contentSpreadLayerHierarchy(contentSpreadLayer, UseDefaultIID());
		TraceLayerName("Content", contentSpreadLayerHierarchy);
		TraverseIHierarchy(contentSpreadLayerHierarchy, TraceNode);

		// Get the guides spread layer associated with the document layer
		InterfacePtr<ISpreadLayer> guideSpreadLayer
			(
				spread->QueryLayer
					(
						documentLayer,
						&spreadLayerPosition,
						kTrue
					)
			);
			
		// Report the guides by traversing the guides spread layer
		InterfacePtr<IHierarchy> guideSpreadLayerHierarchy(guideSpreadLayer, UseDefaultIID());
		TraceLayerName("Guides", contentSpreadLayerHierarchy);
		TraverseIHierarchy(guideSpreadLayerHierarchy, TraceNode);
		
	} // Iterate document layers
}


/*
*/
void SnpInspectLayoutModel::ReportDocumentGeometry(const UIDRef& docUIDRef)
{
	SNIPLOG("ReportDocumentGeometry() ********Begin");
	
	// Get the document
	InterfacePtr<IDocument> document(docUIDRef, UseDefaultIID());
	ASSERT(document);
	
	// SNIPLOG the document's name, class and uid
	TraceBoss(document);
	PMString documentName;
	document->GetName(documentName);
	SNIPLOG("%s", documentName.GetPlatformString().c_str());
	SNIPLOG("");
	
	// Get the document's database
	IDataBase* database = ::GetDataBase(document);
	
	// Get the list of spreads in this document
	InterfacePtr<ISpreadList> spreadList(document, UseDefaultIID());
	
	// Iterate over all the spreads
	int32 spreadCount = spreadList->GetSpreadCount();
	for ( int32 spreadIndex = 0; spreadIndex < spreadCount; spreadIndex++ )
	{
		// Get the spread
		UIDRef spreadUIDRef(database, spreadList->GetNthSpreadUID(spreadIndex));
		
		// SNIPLOG the spread
		SNIPLOG("  Spread %d geometry by hierarchy...",  spreadIndex+1);	
		TraceSpreadGeometry(spreadUIDRef);
		SNIPLOG("");
				
		// Report the page item's on the spread by traversing its hierarchy
		InterfacePtr<IHierarchy> spreadHierarchy(spreadUIDRef, UseDefaultIID());
		TraverseIHierarchy(spreadHierarchy, TraceNodeGeometryAndTransform);
		
		SNIPLOG("");
		
	} // iterate spreads

	// Get the list of master spreads in the document
	InterfacePtr<IMasterSpreadList> masterSpreadList(document, UseDefaultIID());
	
	// Iterate over all the master spreads	
	int32 masterSpreadCount = masterSpreadList->GetMasterSpreadCount();
	for ( int32 masterSpreadIndex = 0; masterSpreadIndex < masterSpreadCount; masterSpreadIndex++ )
	{
		// Get the master spread
		UIDRef masterSpreadUIDRef(database, masterSpreadList->GetNthMasterSpreadUID(masterSpreadIndex) );
		InterfacePtr<IMasterSpread> masterSpread(masterSpreadUIDRef, UseDefaultIID());
		
		// SNIPLOG the master spread
		PMString masterSpreadName;
		masterSpread->GetName(&masterSpreadName);
		SNIPLOG("  %s master spread geometry by hierarchy...", masterSpreadName.GetPlatformString().c_str());
		TraceSpreadGeometry(masterSpreadUIDRef);
		SNIPLOG("");

		// Report the page item's on the master by traversing its hierarchy
		InterfacePtr<IHierarchy> masterSpreadHierarchy(masterSpread, UseDefaultIID());
		TraverseIHierarchy(masterSpreadHierarchy, TraceNodeGeometryAndTransform);
				
	} // iterate master spreads

	SNIPLOG("ReportDocumentGeometry() ********End");
		
}


/*
*/
void SnpInspectLayoutModel::InspectStoryInlines(const UIDRef& storyUIDRef, void (*Callback)(IHierarchy*))
{
	do {
		// Get the text model.
		InterfacePtr<ITextModel> textModel(storyUIDRef, UseDefaultIID());
		ASSERT(textModel);
		if (textModel == nil) {
			break;
		}
		TraceBoss(textModel);
		SNIPLOG(" Story inlines by hierarchy");
		
		// Query the owned item strand from the text model
		InterfacePtr<IItemStrand> itemStrand
			(((IItemStrand*)textModel->QueryStrand(kOwnedItemStrandBoss, IItemStrand::kDefaultIID)));
		ASSERT(itemStrand);
		if (itemStrand == nil) {
			break; 
		}

		// Get the list of owned items and iterate over them looking 
		// for inline frames.
		IDataBase* database = storyUIDRef.GetDataBase();
		OwnedItemDataList ownedList;
		itemStrand->CollectOwnedItems(0, textModel->TotalLength(), &ownedList);
		int32 ownedItemCount = ownedList.size();
		int32 inlineFrameCount = 0;
		for (int32 ownedItemIndex = 0; ownedItemIndex < ownedItemCount ; ownedItemIndex++) {
			UID inlineUID = ownedList[ownedItemIndex].fUID;
			// Inline frames are rooted on a boss class 
			// with the signature interface IInlineData (normally a kInlineBoss).
			InterfacePtr<IInlineData> inlineData(database, inlineUID, UseDefaultIID());
			if (!inlineData) {
				continue; 			// not an inline item, so skip
			}
			InterfacePtr<IHierarchy> inlineHierarchy(inlineData, UseDefaultIID());
			if (!inlineHierarchy) {
				continue; // can't get IHierarchy, so skip 
			}

			// Report the inline item
			SNIPLOG("  Inline frame %d content by hierarchy at TextIndex %d...",  
						++inlineFrameCount, 
						ownedList[ownedItemIndex].fAt);	
			TraceBoss(inlineHierarchy);

			// Report its content by traversing its hierarchy
			TraverseIHierarchy(inlineHierarchy, Callback);

		} // iterate owned items

	} while(false);

}

/*
*/
void SnpInspectLayoutModel::TraverseIHierarchy(IHierarchy* parent, void (*Callback)(IHierarchy*))
{
	int32 childCount = parent->GetChildCount();
	for (int32 childIndex = 0; childIndex < childCount; childIndex++)
	{
		InterfacePtr<IHierarchy> child(parent->QueryChild(childIndex));
		Callback(child);
		TraverseIHierarchy(child, Callback);
	}
}




/*
*/
void SnpInspectLayoutModel::Indent(int32 level)
{
	int32 bufSize = level*2 + 1;
	if (bufSize > eBuffSize) {
		bufSize = eBuffSize;
	}
	int32 i;
	for (i = 0; i < bufSize-1 ; i++) {
		fPadBuf [i] = ' ';
	}
	fPadBuf [i] = '\0';
}


/*
*/
int32 SnpInspectLayoutModel::TraceBoss(IPMUnknown* unknown)
{
	int32 level = 0;
	if (unknown != nil)
	{
		ClassID unknownClassID = ::GetClass(unknown);
		
		// Indent all document objects to level 1 minimum
		InterfacePtr<IDocument> document(unknown, UseDefaultIID());
		if (document == nil) 
			level++;
		
		// Indent to appropriate level if unknown is a hierarchy
		InterfacePtr<IHierarchy> hierarchy(unknown, UseDefaultIID());
		if (hierarchy != nil)
		{
			// indent with spaces to indicate level in hierarchy
			UIDList ancestors(::GetDataBase(hierarchy));
			hierarchy->GetAncestors(&ancestors, IHierarchy::kDefaultIID);
			level += ancestors.Length();
		}
		
		Indent(level);

		UID uid = ::GetUID(unknown);

		PMString additionalInfo(" ");
		InterfacePtr<IMasterPage> masterPage(unknown, IID_IMASTERPAGE);
		if (masterPage) {
			// Add a string describing the page.
			InterfacePtr<IDocument> document(QueryDocument(unknown));
			if (document) {
				InterfacePtr<IPageList> pageList(document, UseDefaultIID());
				if (pageList) {
					PMString pageStr;
					pageList->GetPageString(::GetUID(unknown), &pageStr);
					additionalInfo = PMString(", page ");
					additionalInfo.Append(pageStr);
				}
			}
		}

	#ifdef DEBUG		
		// SNIPLOG the class name and uid
		DebugClassUtilsBuffer classBuf;
		const char* className = DebugClassUtils::GetIDName(&classBuf, unknownClassID);
		SNIPLOG("%s%s, uid 0x%x%s", 
			fPadBuf, 
			className, 
			uid.Get(),
			additionalInfo.GetPlatformString().c_str());
	#else
		// Limited ClassID name lookup is provided for the release build,
		PMString className = LookupClassName(unknownClassID);
		SNIPLOG("%s%s, uid 0x%x%s", 
			fPadBuf, 
			className.GetPlatformString().c_str(), 
			uid.Get(),
			additionalInfo.GetPlatformString().c_str());
	#endif
	}
	return level;
}


/*
*/
int32 SnpInspectLayoutModel::TraceBoss(IDataBase* database, const UID& uid)
{
	InterfacePtr<IPMUnknown> unknown(database, uid, IID_IUNKNOWN);
	return TraceBoss(unknown);
}


/*
*/
void SnpInspectLayoutModel::TraceNode(IHierarchy* node)
{
	TraceBoss(node);
}


/*
*/
void SnpInspectLayoutModel::TracePageNode(IHierarchy* node)
{
	do
	{
		int32 level = TraceBoss(node);
		
		InterfacePtr<IMasterPage> masterPage(node, IID_IMASTERPAGE);
		if (masterPage == nil) {
			break;
		}
			
		bool16 isValid = masterPage->IsValid();
		if (isValid == kFalse) {
			// no master page
			break;
		}
			
		// SNIPLOG the master spread
		UID masterUID = masterPage->GetMasterSpreadUID();
		uint16 masterPageIndex = masterPage->GetMasterSpreadPageIndex();
		InterfacePtr<IMasterSpread> masterSpread(::GetDataBase(node), masterUID, UseDefaultIID());
		PMString masterSpreadName;
		masterSpread->GetName(&masterSpreadName);
		Indent(level+1);
		SNIPLOG("%sassigned to master %s, uid 0x%x, masterPageIndex %d", fPadBuf, masterSpreadName.GetPlatformString().c_str(), masterUID.Get(), masterPageIndex);
		Indent(level);
	} while (false);
}


/*
*/
void SnpInspectLayoutModel::TraceLayerName(const char* msg, IHierarchy* node)
{
	PMString layerName;
	UID spreadLayerUID = node->GetLayerUID();
	InterfacePtr<ISpreadLayer> spreadLayer(::GetDataBase(node), spreadLayerUID, UseDefaultIID());
	if (spreadLayer != nil)
		spreadLayer->GetName(&layerName);
	else
		layerName.Append("NoLayer");
	SNIPLOG("  %s %s", layerName.GetPlatformString().c_str(), msg);
}


/*
*/
void SnpInspectLayoutModel::TracePMRect(const char* msg, const PMRect& bBox)
{
	SNIPLOG("%s%s Left=%f Top=%f Right=%f Bottom=%f", 
		fPadBuf, 
		msg, 
		::ToDouble(bBox.Left()),
		::ToDouble(bBox.Top()),
		::ToDouble(bBox.Right()),
		::ToDouble(bBox.Bottom()));
}


/*
*/
void SnpInspectLayoutModel::TraceSpreadGeometry( const UIDRef& objectUIDRef)
{
	InterfacePtr<IGeometry> objectGeometry(objectUIDRef, UseDefaultIID());
	
	TraceBoss(objectGeometry);

	PMRect bBoxInner = Utils<Facade::IGeometryFacade>()->GetItemBounds( objectUIDRef, Transform::InnerCoordinates(), Geometry::OuterStrokeBounds()); 
	TracePMRect("Inner", bBoxInner);

	PBPMRect bBoxPasteboard = Utils<Facade::IGeometryFacade>()->GetItemBounds( objectUIDRef, Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
	TracePMRect("Pasteboard", bBoxPasteboard);
}



/*
*/
void SnpInspectLayoutModel::TracePMMatrix(const char* msg, const PMMatrix& m)
{
	SNIPLOG("%s%s a=%f b=%f c=%f, d=%f e=%f f=%f\n", 
		fPadBuf, 
		msg,
		::ToFloat(m[0]),
		::ToFloat(m[1]),
		::ToFloat(m[2]),
		::ToFloat(m[3]),
		::ToFloat(m[4]),
		::ToFloat(m[5]));
}


/*
*/
void SnpInspectLayoutModel::TraceGeometry(IGeometry* objectGeometry)
{	
	TraceBoss(objectGeometry);

	PMRect bBoxInner = Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(objectGeometry), Transform::InnerCoordinates(), Geometry::OuterStrokeBounds());
	TracePMRect("Inner", bBoxInner);

	PMRect bBoxParent = Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(objectGeometry), Transform::ParentCoordinates(), Geometry::OuterStrokeBounds());
	TracePMRect("Parent", bBoxParent);

	PBPMRect bBoxPasteboard = Utils<Facade::IGeometryFacade>()->GetItemBounds( ::GetUIDRef(objectGeometry), Transform::PasteboardCoordinates(), Geometry::OuterStrokeBounds());
	TracePMRect("Pasteboard", bBoxPasteboard);
}

/*
*/
void SnpInspectLayoutModel::TraceTransform(ITransform* objectTransform)
{
	const PMMatrix& objectTransformMatrix = objectTransform->GetInnerToParentMatrix();
	TracePMMatrix("Transformation matrix ", objectTransformMatrix);
}

/*
*/
void SnpInspectLayoutModel::TraceNodeGeometryAndTransform(IHierarchy* node)
{
	InterfacePtr<IGeometry> geometry(node, UseDefaultIID());
	if (geometry != nil)
	{
		TraceGeometry(geometry);
		InterfacePtr<ITransform> transform(node, IID_ITRANSFORM);
		if (transform != nil)
		{
			TraceTransform(transform);
		}
	}	
}

/*	Given an interface on a persistent object this method
	returns the UIDRef of the document that contains it.
*/
UIDRef SnpInspectLayoutModel::GetDocumentUIDRef(IPMUnknown* unknown)
{
	UIDRef documentUIDRef(nil, kInvalidUID);
	do
	{
		IDataBase* database = ::GetDataBase(unknown);
		if (database == nil)
			break;
		UID documentUID = database->GetRootUID();
		if (documentUID == kInvalidUID)
			break;
		documentUIDRef = UIDRef(database, documentUID);
	} while(false);
	return documentUIDRef;
}
		

/*	Given an interface on a persistent object this method
	returns the IDocument interface of the document that 
	contains it.
*/
IDocument* SnpInspectLayoutModel::QueryDocument(IPMUnknown* unknown)
{
	IDocument* document = nil;
	do
	{
		UIDRef documentUIDRef = GetDocumentUIDRef(unknown);
		if (documentUIDRef == UIDRef(nil, kInvalidUID)) {
			break;
		}
		InterfacePtr<IDocument> doc(documentUIDRef, IID_IDOCUMENT);
		if (doc == nil) {
			break;
		}
		document = doc;
		document->AddRef();
	} while (false);
	return document;
}


#ifndef DEBUG // Diagnostics hack for release build
/*
*/
PMString	SnpInspectLayoutModel::LookupClassName(const ClassID& classID)
{
	typedef	KeyValuePair<int32, PMString> ClassName;
	typedef	K2Vector<ClassName> ClassNameDictionary; 
	static	ClassNameDictionary gClassNameDict;
	if (gClassNameDict.size() == 0) {
		gClassNameDict.push_back(ClassName(0xe01,	"kDocBoss"));
		gClassNameDict.push_back(ClassName(0x501,	"kSpreadBoss"));
		gClassNameDict.push_back(ClassName(0x50f,	"kPageBoss"));
		gClassNameDict.push_back(ClassName(0x1401,	"kMasterPagesBoss"));
		gClassNameDict.push_back(ClassName(0x302,	"kDocumentLayerBoss"));
		gClassNameDict.push_back(ClassName(0x301,	"kSpreadLayerBoss"));
		gClassNameDict.push_back(ClassName(0x201,	"kTextStoryBoss"));
		gClassNameDict.push_back(ClassName(0x2c0f,	"kPageItemBoss"));
		gClassNameDict.push_back(ClassName(0x263,	"kMultiColumnItemBoss"));
		gClassNameDict.push_back(ClassName(0x227,	"kFrameItemBoss"));
		gClassNameDict.push_back(ClassName(0x2c10,	"kDrawablePageItemBoss"));
		gClassNameDict.push_back(ClassName(0x6201,	"kSplineItemBoss"));
		gClassNameDict.push_back(ClassName(0x1701,	"kImageBaseItem"));
		gClassNameDict.push_back(ClassName(0x1702,	"kImageItem"));
		gClassNameDict.push_back(ClassName(0x2501,	"kPlacedPDFItemBoss"));
		gClassNameDict.push_back(ClassName(0x660b,	"kEPSTextItemBoss"));
		gClassNameDict.push_back(ClassName(0x6611,	"kDisplayListPageItemBoss"));
		gClassNameDict.push_back(ClassName(0x6601,	"kEPSItem"));
		gClassNameDict.push_back(ClassName(0x6602,	"kPICTItem"));
		gClassNameDict.push_back(ClassName(0x6603,	"kWMFItem"));
		gClassNameDict.push_back(ClassName(0x660f,	"kDCSItemBoss"));
		gClassNameDict.push_back(ClassName(0x401,	"kGroupItemBoss"));
		gClassNameDict.push_back(ClassName(0xb320,	"kTOPSplineItemBoss"));
		gClassNameDict.push_back(ClassName(0x3301,	"kGuideItemBoss"));
		gClassNameDict.push_back(ClassName(0x262,	"kInlineBoss"));
	}
	PMString result;
	int32 key = classID.Get();
	ClassNameDictionary::const_iterator iter = K2find(gClassNameDict.begin(), gClassNameDict.end(), key);
	if (iter == gClassNameDict.end()) {
		// ID's name is not available, represent ID as hex string.
		char buf[16];
		sprintf(buf,"0x%x", classID.Get());
		result = buf;
	}
	else {
		// ID's name is available.
		result = iter->Value();
	}
	return result;
}

#endif // not DEBUG

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------


/** Makes the snippet SnpInspectLayoutModel available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerInspectLayoutModel : public SnpRunnable
{
	

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
						_SnpRunnerInspectLayoutModel();

		/** Destructor.
		 */
		virtual			~_SnpRunnerInspectLayoutModel();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@pre SnipRun::CanRun is kTrue
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};
/* Constructor
*/
_SnpRunnerInspectLayoutModel::_SnpRunnerInspectLayoutModel() : SnpRunnable("InspectLayoutModel")
{
	this->SetDescription("Report layout content hierarchy and geometry");
	this->SetPreconditions("document open or frame selected");
	this->SetCategories("sdk_snippet, sdk_layout");
}

/* Destructor
*/
_SnpRunnerInspectLayoutModel::~_SnpRunnerInspectLayoutModel()
{
}

/*
*/
bool16 _SnpRunnerInspectLayoutModel::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;

	// Require a document to be open.
	IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
	if (document != nil) {
		result = kTrue;
	}

	return result;
}

/*
*/
ErrorCode _SnpRunnerInspectLayoutModel::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;
	do {
		SnpInspectLayoutModel instance;
		// Require a document to be open.
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		ASSERT(document != nil);
		if (document == nil) {
			SNIPLOG("Please open a document and try again");
			break;
		}
		UIDRef docUIDRef = ::GetUIDRef(document);

		// If there's a layout selection then report on it,
		// otherwise report the entire document.
		UIDList itemList;
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget) {
			itemList = layoutTarget->GetUIDList(kStripStandoffs);
		}
		if (itemList.Length() > 0) {
			instance.ReportItems(itemList);
		}
		else {
			instance.ReportDocument(docUIDRef);
		}

		status = kSuccess;

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectLayoutModel instance_SnpRunnerInspectLayoutModel;
DEFINE_SNIPPET(_SnpRunnerInspectLayoutModel) 	

//End, SnpInspectLayoutModel.cpp

