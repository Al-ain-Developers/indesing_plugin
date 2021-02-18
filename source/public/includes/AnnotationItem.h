//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AnnotationItem.h $
//
//  Owner: Souvik Sinha Deb
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __AnnotationItem__
#define __AnnotationItem__


#include "PMRect.h"
#include "IDTime.h"
#include "AnnotationConstants.h"
#include "IPathGeometry.h"
#include <map>
/*
typedef unsigned int AnnotationID;
#define kInvalidAnnotationID 0;
*/

namespace AnnotMapOrDrawType
{
	//Indicates how annotation should be mapped to indesign document
	enum eAnnotMappingType { kBBoxMapping, kPointMapping, kTextMapping, kUnknownMapping };
	//Indicates how annotation should be drawn on indesign document
	enum eAnnotDrawingType { kPathDrawing, kIconDrawing, kTextDrawing, kUnknownDrawing };
}
// Store for each annotation whats kind of mapping and drawing it supports. Populated once from AnnoationItem class constructor
typedef std::map<AnnotationType,std::pair<AnnotMapOrDrawType::eAnnotMappingType, AnnotMapOrDrawType::eAnnotDrawingType>> AnnotationMappingAndDrawingTypeMap;

//Structure for storing segregated mapping textual data, valid only for InDesign exported tagged PDFs
class PUBLIC_DECL SegregatedTextualData
{
public:
	std::vector<UTF32TextChar> precedingContextText, succeedingContextText, targetContextText;
	std::vector<PMRect> quadRects;
	SegregatedTextualData(std::vector<UTF32TextChar> _targetContextText, std::vector<UTF32TextChar> _precedingContextText, std::vector<UTF32TextChar> _succeedingContextText, std::vector<PMRect> _rangeRects) :
		targetContextText(_targetContextText), precedingContextText(_precedingContextText), succeedingContextText(_succeedingContextText), quadRects(_rangeRects) {}
};

// Annotation Body Class -- contains mapping and drawing information.
//See the comments in AnnoationItem on how to fill this structure.

class PUBLIC_DECL AnnotationBody
{
public :
	AnnotationBody() : fDrawingPath(NULL), fInsertCommentIsAfterPrecedingContextText(kFalse) {}

	//To get more details about these API see the comments written in AnnotationItem.
	virtual void ApplyTransformAnnotation(const PMMatrix& transformationMatrix);

	virtual void SetMappingBBoxData(const PMRect& bBox);

	virtual void GetMappingBBoxData(PMRect& bBox) const;

	virtual void SetMappingPointData(const PMRect& bBox, const PMPoint& point);

	virtual void GetMappingPointData(PMRect& bBox, PMPoint& point) const;

	virtual void SetMappingTextData(const PMRect& bBox, const std::vector<UTF32TextChar>& targetContextText, const std::vector<UTF32TextChar>& precedingContextText, const std::vector<UTF32TextChar>& succeedingContextText, const bool& insertCommentAfterSucceedingText);

	virtual void GetMappingTextData(PMRect& bBox, std::vector<UTF32TextChar>& targetContextText, std::vector<UTF32TextChar>& precedingContextText, std::vector<UTF32TextChar>& succeedingContextText, bool16& insertCommentAfterSucceedingText) const;

	virtual void SetTextRectsForMappingTextData(const std::vector<PMRect>& mappingTextRects);

	virtual void GetTextRectsForMappingTextData(std::vector<PMRect>& mappingTextRects) const;

	virtual void SetDrawingDataForPathDrawing(IPathGeometry *path);

	virtual void GetDrawingDataForPathDrawing(IPathGeometry *&path) const;

	virtual void SetDrawingDataForIconDrawing(const PMRsrcID &iconId);

	virtual void GetDrawingDataForIconDrawing(PMRsrcID &iconId) const;

	virtual void SetSegregatedTextualContentData(const std::vector<std::shared_ptr<SegregatedTextualData>> &segregatedTextualData);

	virtual void GetSegregatedTextualContentData(std::vector<std::shared_ptr<SegregatedTextualData>> &segregatedTextualData) const;

	virtual PMRect GetBoundingBox() const;

private : 
	/** The Bounding Box of the Annotation which will be used to map it to pageItem
	*/
	PMRect fMappingBBox;
	/** The Target point of all context based annotations which will be used it to map to pageItem
	*/
	PMPoint fMappingPoint;
	/** The Text referred to in all Text based multiline annotations
	*/
	std::vector<UTF32TextChar> fMappingContextText;
	/** The Text preceding to the text referred to in all Text based multiline annotations
	*/
	std::vector<UTF32TextChar> fMappingPrecedingContextText;
	/** The Text succeeding to the text referred to in all Text based multiline annotations
	*/
	std::vector<UTF32TextChar> fMappingSucceedingContextText;

	/** The BBox of all Text present in fMappingContextText.
	    This is an optional parameter which helps in improving the accuracy of text mapping. 
	*/
	std::vector<PMRect> fMappingTextRects;

	/** The Path if any, to draw body of the Annotation.
	*/
	InterfacePtr<IPathGeometry> fDrawingPath;

	/** The icon if any, to draw as body of Annotation. If not passed, default icon will be draw.
	*/
	PMRsrcID fDrawingIcon;

	/** The collection of comments text and their respective quad-points to iterate over different text frames in InDesign, available only if tagged.
	*/
	std::vector<std::shared_ptr<SegregatedTextualData>> fSegregatedMappingData;

	/** This variable denotes that the position of the insert comment is more closer to the precesing string than the succeeding string. This is useful
	for scenarios like paragraph end and table cell partitions and is valid for only text insert type annotation.
	*/
	bool16 fInsertCommentIsAfterPrecedingContextText;
};

// Annotation Reply Class -- implements a reply to an annotation.
class PUBLIC_DECL AnnotationReply
{
    
public:
    /** Sets the information of a particular reply.
     */
    AnnotationReply();
    
    /** Sets the Textual Content of a particular reply.
     @param content IN is the annotation's content.
     */
    virtual void SetReplyContent(const PMString& content);
    
    /** Gets the Textual Content of a particular reply.
     @param content OUT is the annotation's content.
     */
    virtual PMString GetReplyContent() const;
    
    /** Sets the Status of a particular reply.
     @param status IN is the annotation's current status -- whether open or resolved.
     */
    //virtual void SetAnnotationStatus(const AnnotationStatus& status);
    
    /** Gets the Status of a particular reply.
     @param status OUT is the annotation's current status -- whether open or resolved.
     */
    //virtual void GetAnnotationStatus(AnnotationStatus& status) const;
    
    /** Sets the Author/Creator Name of a particular reply.
     @param creator IN is the annotation's creator -- name of the user who created/edited the annotation.
     */
    virtual void SetReplyCreator(const PMString& creator);
    
    /** Gets the Author/Creator Name of a particular reply.
     @param creator OUT is the annotation's creator -- name of the user who created/edited the annotation.
     */
    virtual PMString GetReplyCreator() const;
    
    /** Sets the Last Modified Time of a particular reply.
     @param modified IN is the annotation's last modified time.
     */
    virtual void SetReplyModified(const IDTime& modified);
    
    /** Gets the Last Modified Time of a particular reply.
     @param modified OUT is the annotation's last modified time.
     */
    virtual IDTime GetReplyModified() const;
    
private:
    
    /** The Textual Content of the Reply
     */
    PMString fContent;
    //AnnotationStatus fStatus;
    /** The name of the Author/Creator of the Reply
     */
    PMString fCreator;
    /** The Last Modified Time of the Reply
     */
    IDTime fModified;
};

// Annotation Item Class -- implements an annotation supported by InDesign.
class PUBLIC_DECL AnnotationItem
{
public:
	/** Sets the information of a particular annotation.
	*/
	AnnotationItem();
    
    /** Sets the Textual Content of a particular annotation.
     @param content IN is the annotation's content.
     */
    virtual void SetAnnotationContent(const PMString& content);
    
    /** Gets the Textual Content of a particular annotation.
     @param content OUT is the annotation's content.
     */
    virtual PMString GetAnnotationContent() const;
	
	/** Sets the Type of a particular annotation.
		@param annotType IN is the annotation's type.
	*/
	virtual void SetAnnotationType(const AnnotationType& annotType);
	
	/** Gets the Type of a particular annotation.
		@param annotType OUT is the annotation's type.
	*/
	virtual AnnotationType GetAnnotationType() const;

	/** Sets the Annotation ID of a particular annotation.
		@param annotid IN is the annotation's unique ID.
     */
	//virtual void SetAnnotationID(const AnnotationID& annotid);
	
	/** Gets the Annotation ID of a particular annotation.
		@param annotid OUT is the annotation's unique ID.
     */
	//virtual void GetAnnotationID(AnnotationID& annotid) const;
	
	/** Sets the Status of a particular annotation.
		@param status IN is the annotation's current status -- whether open or resolved.
     */
	virtual void SetAnnotationStatus(const AnnotationStatus& status);
	
	/** Gets the Status of a particular annotation.
		@param status OUT is the annotation's current status -- whether open or resolved.
     */
	virtual AnnotationStatus GetAnnotationStatus() const;

	/** Sets the Author/Creator Name of a particular annotation.
		@param creator IN is the annotation's creator -- name of the user who created/edited the annotation.
	*/
	virtual void SetAnnotationCreator(const PMString& creator);
	
	/** Gets the Author/Creator Name of a particular annotation.
		@param creator OUT is the annotation's creator -- name of the user who created/edited the annotation.
	*/
	virtual PMString GetAnnotationCreator() const;
    
    /** Sets the file path of a particular annotation.
     @param filepath IN is the annotation's filepath -- path of the file from which annotation was created.
     */
    virtual void SetAnnotationSource(const PMString& filepath);
    
    /** Gets the file path of a particular annotation.
     @param filepath OUT is the annotation's filepath -- path of the file from which annotation was created.
     */
    virtual PMString GetAnnotationSource() const;

	/** Sets the Target Page Index of a particular annotation.
		@param targetPageIndex IN is the annotation's target InDesign page index.
     */
	//virtual void SetAnnotationTargetPageIndex(const int& targetPageIndex);

	/** Gets the Target Page Index of a particular annotation.
		@param targetPageIndex OUT is the annotation's target InDesign page index.
     */
	//virtual void GetAnnotationTargetPageIndex(int& targetPageIndex) const;

	/** Sets the List of Replies of a particular annotation.
		@param replies IN is the list of all the annotation's replies. 
	*/
	virtual void SetAnnotationReplies(const std::vector<std::shared_ptr<AnnotationReply>>& replies);

	/** Gets the List of Replies of a particular annotation.
		@param replies OUT is the list of all the annotation's replies. 
	*/
	virtual void GetAnnotationReplies(std::vector<std::shared_ptr<AnnotationReply>>& replies) const;

	/** Appends a List of Replies to a particular annotation.
	@param replies IN is the list of the annotation's replies.
	*/
	virtual void AppendAnnotationReplies(const std::vector<std::shared_ptr<AnnotationReply>>& replies);

	/** Sets the Last Modified Time of a particular annotation.
		@param modified IN is the annotation's last modified time.
	*/
	virtual void SetAnnotationModified(const IDTime& modified);

	/** Gets the Last Modified Time of a particular annotation.
		@param modified OUT is the annotation's last modified time.
	*/
	virtual IDTime GetAnnotationModified() const;

	/** Transforms the Annotation by a Matrix.
	@param transformationMatrix IN is the matrix by which annotation is to be transformed.
	*/
	virtual void ApplyTransformAnnotation(const PMMatrix& transformationMatrix);
	
	/**
	All the co-ordinates for path,rect, point etc.. should be in spread co-ordinate space.
	*/

	/** Information for Mapping Annotation to document
	Annotations can be mapped to Document via three methods : Bounding Box, Point Or Text data.

	1. These type of annotation are mapped using BBox where the target page item is found by intersection with given BBox.
	kStickyNote, kTextTypewriter, kTextBox, kFreeformDrawing, kLineSegment, kOval, kRectangle, kPolygon, kStamp, kConnectedLines, kCloud
	Use SetMappingBBoxData() to set.

	2. These type of annotation are mapped using a single Point where the target page item is found by intersection with given Point.
	kArrow, kTextCallout
	Use SetMappingPointData() to set.


	3. These type of annotation are mapped using text data where the target text is found using given text data and preceding test data and succeding text data.
	Preceding and Succeding text data helps better in finding the text data when there has been some edits in the text.
	kHighlight, kUnderline, kSquiggly, kStrikeThrough, kReplaceText, kInsertText
	Use SetMappingTextData() to set.

	(Optional information) For mapping text annotations we can also provide BBox of all text parts addiotionally. This will help in improving accuracy of mapping.
	Use SetTextRectsForMappingTextData to set.
	*/

	//Set mapping information. See structure AnnotationBody for more details

	/** Sets the BBox of annotation which will be used to map it to pageItem.
	@param targetPoint IN is the annotation's mapping bbox.
	@return true/false depending on whether the annoation supports mapping using BBox or not.
	*/
	virtual bool SetMappingBBoxData(const PMRect& bBox);

	/** Gets the Bounding Box which is being used to map it to pageItem.
	@param bBox will store the annotation's bbox.
	@returns true/false depending on whether the annoation supports mapping using BBox or not.
	*/
	virtual bool GetMappingBBoxData(PMRect& bBox) const;

	/** Sets the point of annotation which will be used to map it to pageItem.
	@param bBox will store the annotation's bbox.
	@param point IN is the annotation's mapping point.
	@return true/false depending on whether the annoation supports mapping using point or not.
	*/
	virtual bool SetMappingPointData(const PMRect& bBox, const PMPoint& point);

	/** Gets the point which is being used to map it to pageItem.
	@param bBox will store the annotation's bounding box.
	@param point will store the annotation's point.
	@return true/false depending on whether the annoation supports mapping using point or not.
	*/
	virtual bool GetMappingPointData(PMRect& bBox, PMPoint& point) const;

	/** Sets the text data of annotation which will be used to map it to text frame.
	@param bBox will store the annotation's bounding box.
	@param targetContextText is the annotation's target context text.
	@param precedingContextText is the annotation's preceding context text.
	@param succeedingContextText IN is the annotation's succeeding context text.
	@param insertCommentAfterSucceedingText IN is the annotation's flag for placing insert comment by side of preceeding context text.
	@return true/false depending on whether the annoation supports mapping using text or not.
	*/
	virtual bool SetMappingTextData(const PMRect& bBox, const std::vector<UTF32TextChar>& targetContextText, const std::vector<UTF32TextChar>& precedingContextText, const std::vector<UTF32TextChar>& succeedingContextText, const bool &insertCommentAfterSucceedingText);

	/** Get the text data of annotation which is used to map it to text frame.
	@param bBox will store the annotation's bounding box.
	@param targetContextText is the annotation's target context text.
	@param precedingContextText is the annotation's preceding context text.
	@param succeedingContextText IN is the annotation's succeeding context text.
	@param insertCommentAfterSucceedingText IN is the annotation's flag for placing insert comment by side of preceeding context text.
	@return true/false depending on whether the annoation supports mapping using text or not.
	*/
	virtual bool GetMappingTextData(PMRect& bBox, std::vector<UTF32TextChar>& targetContextText, std::vector<UTF32TextChar>& precedingContextText, std::vector<UTF32TextChar>& succeedingContextText, bool16& insertCommentAfterSucceedingText) const;

	/** Set the BBox of all Text elements present in mapping text data.
	This is an optional parameter which helps in improving the accuracy of text mapping.
	@param mappingTextRects will store the BBox of all Text elements present in mapping text data.
	@return true/false depending on whether the annoation supports mapping using text or not.
	*/
	virtual bool SetTextRectsForMappingTextData(const std::vector<PMRect>& mappingTextRects);

	/** Set the BBox of all Text elements present in mapping text data.
	@param mappingTextRects will store the BBox of all Text elements present in mapping text data.
	@return true/false depending on whether the annoation supports mapping using text or not.
	*/
	virtual bool GetTextRectsForMappingTextData(std::vector<PMRect>& mappingTextRects) const;

	/** Return which kind of mapping is supported by this annotation based on annotation type. BBox or Point or Text
		Before setting mapping data call this function to confirm what kind of mapping is supported by this annotation
	*/
	virtual AnnotMapOrDrawType::eAnnotMappingType GetMappingTypeForAnnotation();

	/** Return which kind of drawing is supported by this annotation based on annotation type. Icon or path or text
		Before setting path drawing data data call this function to confirm if annotation supports this or not.
	*/
	virtual AnnotMapOrDrawType::eAnnotDrawingType GetDrawingTypeForAnnotation();

	//Set drawing information. See structure AnnotationBody for more details

	
	/** Information for Drawing Annotation to document. This will indicate how to draw the annoation once it has been mapped to documnet.

	1. These type of annotation will be drawn as icon only. For now annotations already have predefined icon. For now icon will be drawn at top-left point of BBox.
	User can also pass the icon. If not passed, default icon will be drawn.
	kTextTypewriter, kTextBox, kTextCallout, kStickyNote.

	2. These type of annotation will be drawn as given path. Any kind of path (e.g. rectangle, circle, free form) can be supported.
	kFreeformDrawing, kArrow, kLineSegment, kOval, kRectangle, kPolygon, kConnectedLines, kCloud.
	Use SetDrawingDataForPathDrawing() to set.

	3. Text type annotations will be drawn at text directly. No need to set anything for drawing.
	kHighlight, kUnderline, kSquiggly, kStrikeThrough, kReplaceText, kInsertText
	*/
	
	/** Sets the path for drawing of annotation.
	@param path is the path for drawing. It can support any type of path.
	@return true/false depending on whether the annoation supports path drawing or not.
	*/
	virtual bool SetDrawingDataForPathDrawing(IPathGeometry *path);

	/** Gets the path for drawing of annotation.
	@param path is the path for drawing. It can support any type of path.
	@return true/false depending on whether the annoation supports path drawing or not.
	*/
	virtual bool GetDrawingDataForPathDrawing(IPathGeometry *&path) const;

	/** Sets the icon for drawing of annotation.
	@param iconId is the icon for drawing.
	@return true/false depending on whether the annoation supports icon drawing or not.
	@This is an optional information. If not provide, default icon will be drawn instead.
	*/
	virtual bool SetDrawingDataForIconDrawing(const PMRsrcID &iconId);

	/** Gets the icon for drawing of annotation.
	@param iconId is the icon for drawing.
	@return true/false depending on whether the annoation supports icon drawing or not.
	*/
	virtual bool GetDrawingDataForIconDrawing(PMRsrcID &iconId) const;

	/** Sets the segregated textual data for breaking the textual content by InDesign text frames.
	@param segregatedTextualData is the vector of structures of terxtual mapping data pertaing to only one yet unknown InDesign Text frame.
	@return true/false depending on whether the annoation supports mapping using text or not.
	@This is an optional information.
	*/
	virtual bool SetSegregatedTextualMappingData(const std::vector<std::shared_ptr<SegregatedTextualData>> &segregatedTextualData);

	/** Sets the segregated textual data for breaking the textual content by InDesign text frames.
	@param segregatedTextualData is the vector of structures of terxtual mapping data pertaing to only one yet unknown InDesign Text frame.
	@return true/false depending on whether the annoation supports mapping using text or not.
	*/
	virtual bool GetSegregatedTextualMappingData(std::vector<std::shared_ptr<SegregatedTextualData>> &segregatedTextualData) const;

	/** Gets the Bounding Box which of annotation.
	@param bBox will store the annotation's bbox.
	*/
	virtual PMRect GetBoundingBox() const;

private:
    
	//AnnotationID fAnnotid;
    /** The Textual Content of the Annotation
     */
    PMString fContent;
	//AnnotationStatus fStatus;
    /** The name of the Author/Creator of the Annotation
     */
	PMString fCreator;
    /** The file path of the Annotation
     */
    PMString fPath;
    /** The Body of the Annotation for its visual representation
     */
	AnnotationBody fBody;
	//int fTargetPageIndex;
    /** The List of Replies of the Annotation
     */
	std::vector<std::shared_ptr<AnnotationReply>> fReplies;
    /** The Type of Annotation
     */
	AnnotationType fAnnotType;
    /** The Last Modified Time of the Annotation
     */
	IDTime fModified;
	/** The status of annotation  
	*/
	AnnotationStatus fStatus;

	/**
	Store mapping and drawing type for every annotation type.
	*/
	static AnnotationMappingAndDrawingTypeMap annotMappingAndDrawingTypeMap;

	/**
	Populates annotMappingAndDrawingTypeMap map; If at any time drawing and mapping type of annotation is changed. It should also be updated in this function.
	*/
	static void PopulateAnnotationMappingAndDrawingTypeMap();
};

#endif //__AnnotationItem__
