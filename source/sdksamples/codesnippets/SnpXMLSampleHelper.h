//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpXMLSampleHelper.h $
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

#ifndef __SnpXMLSampleHelper_H_DEFINED__
#define __SnpXMLSampleHelper_H_DEFINED__

#include "SnpXMLHelper.h"


/** Creates sample XML/DTD content, and implements non-XML related features 
	used by the snippet samples involving XML.
 	@ingroup sdk_snippet
	@ingroup sdk_xmedia
*/
class SnpXMLSampleHelper : public SnpXMLHelper {

public:

	/** Constructor */
	SnpXMLSampleHelper() {}

	/** Destructor */
	virtual ~SnpXMLSampleHelper() {}

	/**	Obtain reference to a paragraph style by name; create if it doesn't already exist
		
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param name specifies name of style we're looking for
	
		@return UIDRef from which IStyleInfo can be instantiated
	*/
	UIDRef AcquireParaStyle(const UIDRef& documentUIDRef, const PMString& name);

	/**	Obtain reference to a character style by name; create if it doesn't already exist
		
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param name specifies name of style we're looking for
		@return UIDRef from which IStyleInfo can be instantiated
	*/
	UIDRef AcquireCharStyle(const UIDRef& documentUIDRef, const PMString& name);

	/**	Obtain reference to style (kStyleBoss)
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document of interest
		@param name specifies name of style we're looking for
		@param styleIID PMIID for name table with styles in it: for instance IID_IPARASTYLEGROUPMANAGER
		@param createCmdClassID for instance kCreateParaStyleCmdBoss
		@return UIDRef from which IStyleInfo can be instantiated
	*/
	UIDRef AcquireStyle(const UIDRef& documentUIDRef,
												const PMString& name,
												const PMIID& styleIID,
												const ClassID& createCmdClassID);

	/**	Create a rectangle page item (empty graphic frame)
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document of interest
		@param rect The rectangle to create
		@param spreadNum Index of the target spread
		@param pageNum Index of the target page
		@return UIDRef of the created rectangle frame
	*/
	UIDRef CreateRectangleFrame(const UIDRef& documentUIDRef,  const PMRect& rect,
						int32 spreadNum, int32 pageNum);

	/**	Create an instance of a DTD that is used in some of these mini-snippets
		@param file[in] The file to write to. 
		@return ErrorCode 
	*/
	ErrorCode CreateSampleDTD(const IDFile& file);
	
	/**	Create a story with some sample contet and tagged.
		@param textModelUIDRef The story to tag
		@param noOptionalContent If kFalse optional content will be added
		@return ErrorCode 
	*/
	ErrorCode CreateSampleTaggedStory(const UIDRef& textModelUIDRef,
										bool16 noOptionalContent = kFalse);

	/**	Create instance of XML file for import samples.
		@param file The file to write to.
		@param extendedElements If kTrue a copyright line will be added.
		@return ErrorCode 
	 */
	ErrorCode CreateSampleXML(const IDFile& file, bool16 extendedElements = kFalse);

	/**	Create a text frame, and return reference to the new story associated.
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document in which objects should be created
		@param rect bounding box for frame
		@param spreadNum specifies spread index that should be ancestor for content
		@param pageNum which page on given spread
		@return UIDRef for the graphic frame created, from which IGraphicFrameData can be instantiated
	*/
	UIDRef CreateStoryThroughFrame(const UIDRef& documentUIDRef, const PMRect& rect,
									int32 spreadNum, int32 pageNum) ;

	/**	Create a text frame, and in it a table
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef document in which objects should be created
		@param rect bounding box for frame
		@param outTableUIDRef reference to table (kTableModelBoss) created, from which ITableModel can be instantiated
		@param outTextModelUIDRef reference to story (kTextStoryBoss) created, from which ITextModel can be instantiated
		@param nRows number of rows in table to create
		@param nCols number of columns to create
		@return ErrorCode kSuccess on success, or ErrorCode otherwise
	*/
	ErrorCode CreateTableThroughFrame(const UIDRef& documentUIDRef,
											const PMRect& rect,
											UIDRef& outTableUIDRef,
											UIDRef& outTextModelUIDRef,
											int32 nRows=2, int32 nCols=2);
	
	/**	Get a new rect for shape's position on the page; these don't overlap until there
		are more than about 10 page items

		@param[out] outRect The rectangle
	*/
	void GetNextRect(PMRect& outRect);

	/**	Return a filename to be used for these mini-snippets, with variable ending.
		@param extension specifies the last part of the filename to create, could be 
			a short extension or a longer part of the filename
		@return  IDFile that encapsulates constructed path
	*/
	IDFile GetSampleFile(const PMString& extension);

	/**	Insert some text as a CR terminated line and apply a style to it
		@precondition textModelUIDRef should allow ITextModel to be instantiated
		@param textModelUIDRef identifies story (kTextStoryBoss) into which we're inserting text
		@param lineText specifies text to insert
		@param insertionPoint where in the story to insert the text
		@param styleUIDRef specifies run-style to apply to the text inserted 
		@return ErrorCode kSuccess on success, other ErrorCode otherwise
		@see SnpTextModelHelper
	 */
	ErrorCode InsertStyledLine(const UIDRef& textModelUIDRef, 
								const PMString& lineText,
								const TextIndex& insertionPoint,
								const UIDRef& styleUIDRef,
								TextIndex& outNextTextIndex);

	/** Reset the rect counts to zero, to start positioning shapes from the page origin
		again. Rect-counts are just used to avoid overlapping created page items.
	*/
	void ResetRectCounts();
	
	/**	Save string as CR-terminated line to stream.
		@precondition stream should not be nil
		@param str string to save
		@param stream specifies stream into which to save it
	*/
	void SaveLineToStream(const PMString& str, IPMStream* stream);

private:

		static int32 nRectsCreated;
		static int32 nColsCreated;
};



#endif //  __SnpXMLSampleHelper_H_DEFINED__

//End, SnpXMLSampleHelper.h
