//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltHelper.cpp $
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
#include "IGeometry.h"
#include "IDocument.h"
#include "IHierarchy.h"
#include "ILayerList.h"
#include "ISpreadList.h"
#include "ISpread.h"
#include "ISpreadLayer.h"
#include "IGraphicFrameData.h"
#include "IGeometry.h"
#include "IMargins.h"
#include "IPageItemTypeUtils.h"
#include "IPMStream.h"
#include "ILayoutUtils.h"
#include "ILinkObject.h"
#include "ILinkManager.h"
#include "ILink.h"
#include "ILinkResource.h"

// non-interf includes

#include "TransformUtils.h"
#include "StreamUtil.h"
#include "SDKLayoutHelper.h"
#include "CHMLFiltHelper.h"
#include "K2Vector.tpp"


/* Default constructor
*/
CHMLFiltHelper::CHMLFiltHelper() 
{

}

/* Destructor
*/
CHMLFiltHelper::~CHMLFiltHelper()
{

}


ErrorCode CHMLFiltHelper::ExportLayout(IPMStream* stream, IDocument* doc, IPMUnknown* targetBoss)
{
	ErrorCode err = kFailure;
	do {
		ASSERT(stream && doc);
		if(!(stream && doc)) {
			break;
		}
		UIDRef docRef = ::GetUIDRef(doc);
		K2Vector<CHMLGraphicFrameMetaData> collectFrames;
		PMString headerStr("<CHML>");
		PMString newLineStr;
		newLineStr.AppendW('\n');
		this->writeStream(stream, headerStr);
		this->writeStream(stream,newLineStr);
		this->collectGraphicFrames(docRef, collectFrames);
		K2Vector<CHMLGraphicFrameMetaData>::const_iterator iter;
		for(iter = collectFrames.begin(); iter != collectFrames.end(); ++iter) {
			this->writeStream(stream, *iter);
			this->writeStream(stream,newLineStr);
		}
		err = kSuccess;
	} while(kFalse);

	return err;
}

void CHMLFiltHelper::ExportLayout(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetBoss)
{
	do 
		{
			InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWriteLazy(sysFile, kOpenOut | kOpenTrunc));
			ASSERT(stream);
			if (!stream) {
				break;
			}
			this->ExportLayout(stream, doc, targetBoss);
		} while (kFalse);
}




void CHMLFiltHelper::collectGraphicFrames(const UIDRef& docRef,	K2Vector<CHMLGraphicFrameMetaData>& collectFrames)
{
	do{
		ASSERT(docRef != UIDRef::gNull);
		InterfacePtr<IDocument> document(docRef, UseDefaultIID());
		ASSERT(document);
		if(!document) {
			break;
		}
		IDataBase* database = ::GetDataBase(document);
		ASSERT(database);
		if(!database) {
			break;
		}
		
		// Get the list of spreads in the document
		InterfacePtr<ISpreadList> spreadList(document, UseDefaultIID());
		ASSERT(spreadList);
		if(!spreadList) {
			break;
		}
		
		// Build a list of all the graphic frames in the document
		UIDList frameList(database);
		// Iterate over all the spreads
		int32 spreadCount = spreadList->GetSpreadCount();
		for (int32 spreadIndex = 0; spreadIndex < spreadCount; spreadIndex++ )
		{
			UIDRef spreadUIDRef(database, spreadList->GetNthSpreadUID(spreadIndex));
			InterfacePtr<ISpread> spread(spreadUIDRef, UseDefaultIID());
			ASSERT(spread);
			if(!spread) {
				break;
			}
	
			// Iterate over all the pages on the spread.
			int32 numberOfPages = spread->GetNumPages();
			for (int32 nPage = 0; nPage < numberOfPages; nPage++ )
			{
				UIDList pageItemList(database);
				spread->GetItemsOnPage
				(
					nPage, 
					&pageItemList, 
					kFalse, // don't include the page object itself
					kFalse // don't include items that lie on the pasteboard because we only want what's on the page?  
				);
				
				// Iterate the page items and save off the UIDs of frames.
				int32 pageItemListLength = pageItemList.Length();
				for (int32 j = 0; j < pageItemListLength; j++ )
				{
						UIDRef pageItemRef = pageItemList.GetRef(j);
						InterfacePtr<IGraphicFrameData> graphicFrameData(pageItemRef, UseDefaultIID());
						if (graphicFrameData != nil) {
							int32 absolPage = this->GlobalFromLocalPageIndex(spreadList, spreadIndex, nPage);
							this->addGraphicFrameDescription(docRef,
																				pageItemRef,
																				collectFrames, 
																				absolPage);
						}
				}
			} // iterate pages in spread		
		} // interate spreads

	} while(kFalse);

}


void CHMLFiltHelper::addGraphicFrameDescription(const UIDRef& docRef,
																		const UIDRef& pageItemRef,
																				K2Vector<CHMLGraphicFrameMetaData>& collectFrames,
																				int32 absolPage)
{
		do {
			// Calculate its co-ordinates in the page coordinates
			//  calculate its type via IPageItemTypeUtils
			SDKLayoutHelper layoutHelper;
			// We want the co-ordinates in page-based coordinate system.			
			InterfacePtr<IHierarchy> pageItemHierarchy(pageItemRef, UseDefaultIID());
			ASSERT(pageItemHierarchy);
			if(!pageItemHierarchy) {
				break;
			}

			UIDRef pageRef (pageItemRef.GetDataBase(), Utils<ILayoutUtils>()->GetOwnerPageUID(pageItemHierarchy));
			InterfacePtr<IGeometry> pageGeometry(pageRef, UseDefaultIID());
			ASSERT(pageGeometry);
			if(!pageGeometry) {
				break;
			}
			// The rationale is this
			// Transform the layout object coordinates (inner) to pasteboard
			// transform from pasteboard to page.
			// 
			// First, we want to know the transform from the pasteboard into the page
			PMMatrix page2pb = ::InnerToPasteboardMatrix(pageGeometry);
			PMMatrix pb2page = page2pb;
			pb2page.Invert ();
			PMRect marginBBox;
			InterfacePtr<IMargins> margins(pageRef, IID_IMARGINS);
			ASSERT(margins);
			if (margins) {
				margins->GetMargins(&marginBBox.Left(), &marginBBox.Top(), &marginBBox.Right(), &marginBBox.Bottom());
				// We're saying, subtract off the margin top,left, 
				// so that the point e.g. 10,10 (crossing of margins in topleft) would be 0,0
				pb2page.Translate(-marginBBox.Left(), -marginBBox.Top());
			}
			// And we consider the page origin to start at the top,left crossing of margins rather than outside the margins
			// See SDKLayoutHelper::PageToSpread
			// Then we want to know the transform that takes the inner to pasteboard so
			// that we're going back from pasteboard to the page
			PMMatrix inner2pb2page = pb2page;
			InterfacePtr<IGeometry> objectGeometry(pageItemRef, UseDefaultIID());
			ASSERT(objectGeometry);
			if(!objectGeometry) {
				break;
			}
			inner2pb2page.PreConcat(::InnerToPasteboardMatrix(objectGeometry));
			// Perhaps I could use inner to arbitrary parent, but this is a simple way to do it as the page object isn't
			// on the hierarchy, it might involve yet more faffing
			Utils<IPageItemTypeUtils> pageItemTypeUtils;
			ASSERT(pageItemTypeUtils);
			if(!pageItemTypeUtils) {
				break;
			}
			CHMLGraphicFrameMetaData::LayoutObjectType objectType = CHMLGraphicFrameMetaData::eUnknown;
			if(pageItemTypeUtils->IsGraphicFrame(pageItemRef)) {
				objectType = CHMLGraphicFrameMetaData::eGraphicsFrame;
				} 
			else if(pageItemTypeUtils->IsTextFrame(pageItemRef)) {
				objectType = CHMLGraphicFrameMetaData::eTextFrame;
			} 
	
			// Only add types we want to represent information about on export
			if(objectType != CHMLGraphicFrameMetaData::eUnknown) {
				PMRect bboxRectInPage = objectGeometry->GetStrokeBoundingBox(inner2pb2page);
				
				if(pageItemTypeUtils->IsTextFrame(pageItemRef)) {
					CHMLGraphicFrameMetaData metadata(objectType, absolPage, bboxRectInPage);
					// TODO do we want to export styled text or just leave it?
					collectFrames.push_back(metadata);
					
				} else if(pageItemTypeUtils->IsGraphicFrame(pageItemRef)) {
					InterfacePtr<IHierarchy> frameHierarchy(pageItemRef, UseDefaultIID());
					ASSERT(frameHierarchy);
					if(!frameHierarchy) {
						break;
					}
					InterfacePtr<IHierarchy> childHierarchy(frameHierarchy->QueryChild(0));
					if(!childHierarchy) {
						break;
					}
					// If we're on a placed image we should have a data link to source item
					InterfacePtr<ILinkObject> iLinkObject(childHierarchy,UseDefaultIID());
					// get the link for this object

					IDataBase* iDataBase = ::GetDataBase(childHierarchy);
					InterfacePtr<ILinkManager> iLinkManager(iDataBase,iDataBase->GetRootUID(),UseDefaultIID());
					ASSERT_MSG(iLinkManager, "CHMLFiltHelper::addGraphicFrameDescription - No link manager?");
					ILinkManager::QueryResult linkQueryResult;

					if (iLinkManager->QueryLinksByObjectUID(::GetUID(childHierarchy), linkQueryResult)){
						ASSERT_MSG(linkQueryResult.size()==1,"CHMLFiltHelper::addGraphicFrameDescription - Only expecting single link with this object");

						ILinkManager::QueryResult::const_iterator iter = linkQueryResult.begin();

						InterfacePtr<ILink> iLink (iDataBase, *iter,UseDefaultIID());
						if (iLink!=nil)
						{
							InterfacePtr<ILinkResource> iLinkResource(iLinkManager->QueryResourceByUID(iLink->GetResource()));
							ASSERT_MSG(iLinkResource,"CHMLFiltHelper::addGraphicFrameDescription - Link with no associated asset?");
							if(iLinkResource!=nil)
							{
								PMString datalinkPath = iLinkResource->GetLongName(false);
								if(datalinkPath.CharCount()>0) {
									CHMLGraphicFrameMetaData metadataWithDataLink(objectType, absolPage, bboxRectInPage);
									// We want the parent bbox
									metadataWithDataLink.SetDataLinkPath(datalinkPath);
									collectFrames.push_back(metadataWithDataLink);
								}
								else {
									datalinkPath = PMString("UNDEFINED");
								}
							}
						}
					}
				}
			}
	} while(kFalse);

}


int32 CHMLFiltHelper::GlobalFromLocalPageIndex(ISpreadList* spreadList, int32 inSpreadIndex, int32 relativePageIndex)
{
	int32 retval = relativePageIndex;
	do {
		
		ASSERT(spreadList);
		if(!spreadList) {
			break;
		}
		bool16 validIndexForCalc = (inSpreadIndex > 0 &&  inSpreadIndex < spreadList->GetSpreadCount());
		if(!validIndexForCalc) {
			break;
		}
		IDataBase* database = ::GetDataBase(spreadList);
		ASSERT(database);
		if(!database) {
			break;
		}
		// We want total up to current spread, ie. inSpreadIndex-1
		for (int32 spreadIndex = 0; spreadIndex < (inSpreadIndex - 1); spreadIndex++ )
		{
			UIDRef spreadUIDRef(database, spreadList->GetNthSpreadUID(spreadIndex));
			InterfacePtr<ISpread> spread(spreadUIDRef, UseDefaultIID());
			ASSERT(spread);
			if(!spread) {
				break;
			}
			// Iterate over all the pages on the spread.
			retval += spread->GetNumPages();
		}

	} while(kFalse);

	return retval;
}

UIDRef CHMLFiltHelper::GetDefaultSpreadLayerRef(const UIDRef& docUIDRef, int32 spreadIndex)
{
	UIDRef retval = UIDRef::gNull;
	do {
		ASSERT(docUIDRef != UIDRef::gNull);
		
		InterfacePtr<ISpreadList> iSpreadList(docUIDRef, IID_ISPREADLIST);
		ASSERT(iSpreadList);
		if(!iSpreadList) {
			break;
		}
		ASSERT(spreadIndex >= 0 && spreadIndex < iSpreadList->GetSpreadCount());
		InterfacePtr<IGeometry> iSpreadGeometry(iSpreadList->QueryNthSpread(spreadIndex));
		ASSERT(iSpreadGeometry);
		if(!iSpreadGeometry) {
			break;
		}
		InterfacePtr<ISpread> iSpread(iSpreadGeometry, UseDefaultIID());
		ASSERT(iSpread);
		if(!iSpread) {
			break;
		}
		SDKLayoutHelper layoutHelper;
		retval = layoutHelper.GetSpreadLayerRef(::GetUIDRef(iSpread));
	} while(kFalse);
	return retval;
}


void CHMLFiltHelper::writeStream(IPMStream* stream, const CHMLGraphicFrameMetaData& metadata)
{
	do {
		ASSERT(stream);
		if(!stream) {
			break;
		}
		PMString str;
		
		switch(metadata.GetLayoutObjectType() ){
			// TODO not sure about this
			case CHMLGraphicFrameMetaData::eGraphicsFrame:
			{
				// We only need the top left
				str.Append("<i ");
				PMRect rect = metadata.GetRectInPage();
				str +="  ";
				str +="\""; //Always add quotes to file path. Or we could change GetDataLinkPath() to add quotes for paths that contain space
				str += metadata.GetDataLinkPath();
				str +="\""; //Always add quotes to file path
				str +="  ";
				str.AppendNumber(rect.Left(),0);
				str += "  ";
				str.AppendNumber(rect.Top(),0);
				str += " >";
				this->writeStream(stream,str);
			}
			break;

			case CHMLGraphicFrameMetaData::eTextFrame:
			{
				// We want a bounding box for the text
				str.Append("<t ");
				PMRect rect = metadata.GetRectInPage();
				str +="  ";
				str.AppendNumber(rect.Left(),0);
				str += "  ";
				str.AppendNumber(rect.Top(),0);
				str += "  ";
				str.AppendNumber(rect.Right(),0);
				str += "  ";
				str.AppendNumber(rect.Bottom(),0);
				str += " >";
				this->writeStream(stream,str);
			}
			break;

			default:
				ASSERT(0);
				break;
		}
		//TODO
		// str.Append(" page=\"");
		//str.AppendNumber(metadata.GetPage());
		//str.Append("\"");
		
		
	} while (kFalse);
	

}


void CHMLFiltHelper::writeStream(IPMStream* stream, const PMString& str)
{
	const uchar kInternalNewLine='\n';
#ifdef MACINTOSH
		const char* kExternalNewLine="\r";
#else
		const char* kExternalNewLine="\r\n";
#endif
	for (int32 i = 0; i < str.CharCount(); i++)
	{
		PlatformChar pc = str[i];
		// if dual-byte char, output as is, highbyte first.
		if (pc.IsTwoByte()) 
		{
			uchar	hb = pc.HighByte(), 
					lb = pc.LowByte();
			stream->XferByte(&hb, 1);
			stream->XferByte(&lb, 1);
		}
		else // non-dualbyte char
		{
			uchar c = pc.GetAsOneByteChar();
			if (c == kInternalNewLine)
			{
#ifdef MACINTOSH
			stream->XferByte((uchar*)kExternalNewLine, 1);
#else
			stream->XferByte((uchar*)kExternalNewLine, 2);
#endif
			}
			else
			{
				stream->XferByte(&c, 1);
			}
		}
	}
}




