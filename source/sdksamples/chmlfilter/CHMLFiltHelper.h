//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltHelper.h $
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

#ifndef __CHMLFiltHelper_H_DEFINED__
#define __CHMLFiltHelper_H_DEFINED__

#include <map>
#include "PMRect.h"

/** Helper (data) class for exporting aspects of a layout.

	@ingroup chmlfilter
*/
class CHMLGraphicFrameMetaData {
public:
	// (irp Apr 24 03) If this is not object_type, then the destructor won't get
	// called and then you get a leak from the objects that are instance
	// variables
	typedef object_type  data_type;

	/** Types for the layout objects we understand */
	enum LayoutObjectType {
		/** A graphics frame (that may contain an image);
			type from  which we can get an IGraphicFrameData but
			iGraphicFrameData->GetTextContentUID is kInvalidUID, i.e. it can't be a text frame.*/
		eGraphicsFrame,
			eTextFrame,
			/** Some other type */
			eUnknown };

	/** Default constructor */
	CHMLGraphicFrameMetaData():
					fPage(0),
					fLayoutObjectType(eUnknown),
					fDataLinkPath("UNDEFINEDDATALINK") {}

	/** Constructor
		@param type IN what sort of layout object this is (from IPageItemTypeUtils. A graphics frame; IGraphicFrameData or a text frame)
		@param page  IN which page number this object is on (absolute, not just a spread-page index)
		@param bboxRectInPage  IN bounding box in the parent coordinate system
	*/
	CHMLGraphicFrameMetaData(LayoutObjectType type, int32 page, const PMRect& bboxRectInPage) :
					fLayoutObjectType(type),
					fRectInPage(bboxRectInPage),
					fPage(page),
					fDataLinkPath("UNDEFINEDDATALINK") {}

	/** Constructor
		@param type  IN what sort of layout object this is (from IPageItemTypeUtils. A graphics frame; IGraphicFrameData or a text frame)
		@param page  IN which page number this object is on (absolute, not just a spread-page index)
		@param bboxRectInPage  IN bounding box in the parent coordinate system
		@param datalinkpath  IN specifies the path to the linked file
	*/
	CHMLGraphicFrameMetaData(LayoutObjectType type, int32 page, const PMRect& bboxRectInPage, const PMString& datalinkpath) :
		fLayoutObjectType(type), fRectInPage(bboxRectInPage), fPage(page), fDataLinkPath(datalinkpath) {}


	/**	Accessor for the type of this layout object

		@return one of the enumerated LayoutObjectType values
	 */
	LayoutObjectType GetLayoutObjectType() const { return fLayoutObjectType; }

	/**	Accessor for the page (absolute) on which this layout object is located in the publication

		@return page on which layout object is found
	 */
	int32 GetPage() const { return fPage; }

	/**	Accessor for the bounding box of the layout object

		@return PMRect giving the bounding box of the layout object in the parent coordinates
	 */
	PMRect GetRectInPage() const  { return fRectInPage; }

	/** Accessor for path to datalinked asset represented in this
		@return PMString
	 */
	PMString GetDataLinkPath() const { return fDataLinkPath;}

	/**	Specify the path of the datalinked file
		@param path  IN represents path to asset that is datalinked
	 */
	void  SetDataLinkPath(const PMString& path) { this->fDataLinkPath = path;}
private:
	int32 fPage;
	PMRect fRectInPage;
	LayoutObjectType fLayoutObjectType;
	PMString fDataLinkPath;
};

class IDocument;
class IPMStream;
class ISpreadList;

/**  Helper class that is used in exporting a layout.
	@ingroup chmlfilter
*/
class CHMLFiltHelper {

	public:

		/** Default constructor */
		CHMLFiltHelper();

		/** Destructor */
		virtual ~CHMLFiltHelper();


	/**	Export the layout contained in the document to a stream
		@param stream IN where to write the export into
		@param doc IN where to get the content from
		@param targetBoss IN provides encapsulation of the selection and a way to get at the selection target
	 */
	ErrorCode ExportLayout(IPMStream* stream, IDocument* doc, IPMUnknown* targetBoss=nil);

	/** Export the layout contained in the document to a file.
		@param sysFile IN where to write the export into
		@param doc IN where to get the content from
		@param targetBoss IN provides encapsulation of the selection and a way to get at the selection target
	*/
	void ExportLayout(const IDFile& sysFile, IDocument* doc, IPMUnknown* targetBoss=nil);

	/** Given an index in the list of pages in a spread, turn into a global page number in the entire publication.
		@param spreadList IN spread list from the document
		@param inSpreadIndex  IN which spread the page is in
		@param relativePageIndex  IN what the page position is in this spread
	*/
	int32 GlobalFromLocalPageIndex(ISpreadList* spreadList, int32 inSpreadIndex, int32 relativePageIndex);

	/** Method to determine the default spread layer into which to put content.
		Document layer 0 is the pages layer, and document layer n-1 is used for some nefarious purpose too.
		Document layer 1 is the first layer that can contain content + guides. If we have no preference for
		assigning content, then we can put it on the first content spread layer in Document layer 1. This method
		hides making that choice and avoids the client code having to care about document layers, which
		complicate the process if we have to consider them.
		@param docUIDRef IN document of interest
		@param spreadIndex IN which spread we're interested in
		@return the UIDRef of the spread layer that is the default for content, from which an ISpreadLayer can be instantiated.
  */
	UIDRef GetDefaultSpreadLayerRef(const UIDRef& docUIDRef, int32 spreadIndex);

private:
	void collectGraphicFrames(const UIDRef& docRef,	K2Vector<CHMLGraphicFrameMetaData>& collectFrames);
	void addGraphicFrameDescription(const UIDRef& docRef,
													const UIDRef& pageItemRef,
														K2Vector<CHMLGraphicFrameMetaData >& collectFrames,
														int32 absolPage);
	void writeStream(IPMStream* stream, const CHMLGraphicFrameMetaData& metadata);
	void writeStream(IPMStream* stream, const PMString& str);

};







#endif // __CHMLFiltHelper_H_DEFINED__

