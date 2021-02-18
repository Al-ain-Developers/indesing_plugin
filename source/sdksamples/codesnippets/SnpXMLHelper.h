//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpXMLHelper.h $
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

#ifndef __SnpXMLHelper_H_DEFINED__
#define __SnpXMLHelper_H_DEFINED__




/** Provides XML-related methods, some of which are wrappers 
	around methods on facades (IXMLElementCommands, IXMLTagCommands, IXMLUtils).

  	@ingroup sdk_snippet
	@ingroup sdk_xmedia
	@see 	IXMLElementCommands, IXMLTagCommands, IXMLUtils

 */
class SnpXMLHelper
{
public:

	/** Constructor */
	SnpXMLHelper() {}

	/** Destructor */
	virtual ~SnpXMLHelper() {}


	/**	Obtain a reference to a tag (kXMLTagBoss) by name. If the tag exists in the tag-list
		of the specified document with the given name, a reference to the existing tag is returned.
		If the tag doesn't exist then it is created.

		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef identifies document in which the tag is to be created/acquired
		@param  tagName specifies tag of interest.
		@return UIDRef of kXMLTagBoss, from which IXMLTag can be instantiated
	 */
	UIDRef AcquireTag(const UIDRef& documentUIDRef,
						const PMString& tagName);


	/**	Associate (import) a DTD with the logical structure of a document
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document of interest
		@param dtdFile specifies the DTD file to associate with the document
		@return ErrorCode kSuccess on success, some other ErrorCode otherwise
	 */
	ErrorCode AssociateDTD(const UIDRef& documentUIDRef, const IDFile& dtdFile);


	/**	Return a description of the tag object (kXMLTagBoss) supplied
		@precondition tagUIDRef should allow IXMLTag to be instantiated
		@param tagUIDRef specifies tag object (kXMLTagBoss) of interest
		@return  PMString containing description of the tag
	*/
	PMString AsString(const UIDRef& tagUIDRef);
	
	/**	Return a description of the XML element (IIDXMLElement) supplied.
		@param xmlReference specifies XML element of interest
		@return  PMString containing description of the XML element
	*/
	PMString AsString(const XMLReference& xmlReference);


	/**	Mutator for the name of a tag
		@precondition tagUIDRef should allow IXMLTag to be instantiated
		@param tagUIDRef specifies the tag (kXMLTagBoss) of interest
		@param newTagName 
		@return ErrorCode 
	 */
	ErrorCode ChangeTagName(const UIDRef& tagUIDRef,
								const PMString& newTagName);


	/**	Return the class of an object as a PMString, in debug or release.
		@param classID 
		@return  PMString containing the name of the class 
	*/
	PMString GetClassFrom(const ClassID& classID);

	/**	Return the class of an object as a PMString, in debug or release.
		@param objUIDRef specifies object of interest
		@return  PMString containing the name fo the class
	*/
	PMString GetClassFrom(const UIDRef& objUIDRef);

	/**	Get a reference to the root element (kTextXMLElementBoss) in the logical structure.
		
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef specifies document (kDocBoss) of interest, from which IDocument can be instantiated
		@return XMLReference 
	 */
	XMLReference GetRootXMLReference(const UIDRef& documentUIDRef);



	/**	Inserts a tagged text range into a story.
		
		@precondition textModelUIDRef should allow ITextModel to be instantiated

		@param textModelUIDRef specifies the story (kTextStoryBoss) of interest
		@param pstr contains the text to tag
		@param startIndex where the text is to be inserted into the story
		@param tagName specifies the tag by name
		@return TextIndex indicating new insertion point just after the text inserted
		*/
	TextIndex InsertTaggedText(const UIDRef& textModelUIDRef, const PMString& pstr, 
									TextIndex startIndex, const PMString& tagName);


	/**	Places element (IIDXMLElement) into graphic frame.
		@precondition graphicFrameUIDRef should allow IGraphicFrameData to be instantiated
		@precondition object specified by graphicFrameUIDRef should support IXMLUtils::IsTaggablePageItem
		@param xmlRef specifies element of interest
		@param graphicFrameUIDRef graphic frame into which content should be placed
		@return ErrorCode 
	 */
	ErrorCode PlaceElement(const XMLReference& xmlRef, const UIDRef& graphicFrameUIDRef);

	/**	Set the preference to export from selected element, used by export provider.
		@precondition workspaceUIDRef should allow IWorkspace to be instantiated
		@param workspaceUIDRef 
		@param state 
		@return ErrorCode 
	 */
	ErrorCode SetExportFromSelected(const UIDRef& workspaceUIDRef, bool16 state);

	/**	Set preference for import provider to import into selected node

		@precondition workspaceUIDRef should allow IWorkspace to be instantiated
	
		@param workspaceUIDRef 
		@param state 
		@return ErrorCode 
	 */
	ErrorCode SetImportIntoSelected(const UIDRef& workspaceUIDRef, bool16 state);

	/**	Set name of the root element's tag
		@precondition documentUIDRef should allow IDocument to be instantiated
		@param documentUIDRef 
		@param tagName 
		@return ErrorCode 
		*/
	ErrorCode SetRootTag(const UIDRef& documentUIDRef, const PMString& tagName);


	/**	Control visibility of tagged frame decoration.

		@param setVisible 
		@return ErrorCode 
	 */
	ErrorCode ShowHideTaggedFrames(bool16 setVisible);

	/**	Tag story (kTextStoryBoss)
		@precondition textModelUIDRef should allow instantiating ITextModel
		@param textModelUIDRef 
		@param tagName 
		@return ErrorCode 
		*/
	ErrorCode TagStory(const UIDRef& textModelUIDRef, const PMString& tagName);

	/**	Tag a table (kTableModelBoss).
		@precondition tableModelUIDRef should allow instantiating ITableModel
		@param tableModelUIDRef 
		@param tableTagName 
		@param cellTagName 
		@return ErrorCode 
	*/
	ErrorCode TagTable(const UIDRef& tableModelUIDRef, 
						const PMString & tableTagName, 
						const PMString& cellTagName, 
						XMLReference& outCreatedXMLReference);


	/**	Create a tagged text range.
		@precondition textModelUIDRef should allow instantiating ITextModel
		@precondition startIndex, endIndex should lie in same story thread (ITextStoryThread)
		@param textModelUIDRef 
		@param tagName 
		@param startIndex 
		@param endIndex 
		@return ErrorCode 
	 */
	ErrorCode TagTextRange(const UIDRef& textModelUIDRef, 
							const PMString& tagName, 
							TextIndex startIndex, 
							TextIndex endIndex);
	

	
protected:
	/**	Helper method that is used by InsertTaggedText. 

		@param textModelUIDRef 
		@param data 
		@param position 
		@return ErrorCode 
		*/
	ErrorCode InsertText(const UIDRef& textModelUIDRef, const PMString& data, const TextIndex& position);

};



#endif //  __SnpXMLHelper_H_DEFINED__

//End, SnpXMLHelper.h
