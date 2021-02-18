//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyWorkFlowUtils.h $
//  
//  Owner: cparrish
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

#pragma once
#ifndef __IInCopyWorkFlowUtils__
#define __IInCopyWorkFlowUtils__

#include "IStyleInfoMapData.h"

#include "GraphicTypes.h"
#include "InCopyWorkflowID.h"
#include "UIDList.h"

class UIDRef;
class WideString;
class IInCopyXMLElementAttr;
class ITextModel;
class IStyleNameTable;
class InCopyTextStyle;
class IInCopyImportOptions;
class ITextTarget;
class IDocument;
class RangeData;

/**
	IInCopyWorkFlowUtils is a utility class which provides common services to read and write
	InCopy files.  Some routines are general file handling routines while others are specific
	to the incd file format.  Most developers shouldn't need to call these routines unless 
	they are attempting to replace parts of InCopy's normal file handling operations.
*/
class IInCopyWorkFlowUtils : public IPMUnknown
{
public:
		enum	{kDefaultIID = IID_IIINCOPYWORKFLOWUTILS};
		
		/**
			SetFileTypeCreator sets the Macintosh type and creator codes on a file.
			@param file - The file to set the type and creator on.
			@param type - A FileTypeInfoID of the kind of file to set.
		*/
		virtual void SetFileTypeCreator(
								const IDFile& file,
								FileTypeInfoID type
								) = 0;	

		/**
			FindSwatchByName looks for a swatch in the specified database.
			@param db - The database to look in.
			@param swatchName - The name of the swatch to find.
			@return - The UID of the swatch (will be kInvalidUID if not found).
		*/
		virtual UID FindSwatchByName(
								IDataBase* db,
								const PMString swatchName
								) = 0;

		/**
			ColorFromAttr converts InCopy XML into a color UID, making it if necessary.
			@param storyRef - The story this color is associated with.
			@param elemName - The XML element name from the file.
			@param iAttrs - The XML attributes from the file.
			@return - The UID of the imported color (which may have been found or created).
		*/
		virtual UID 	ColorFromAttr(
								const UIDRef& storyRef, 
								const WideString& elemName, 
								IInCopyXMLElementAttr* iAttrs
								) = 0;	
		
		/**
			CreateTintSwatch, unsurprisingly, creates a tint swatch.
			@param db - The document database to create or find the swatch in.
			@param tintName - The tint name.
			@param tintPercent - The tint percentage.
			@return - The tint UID.
		*/
		virtual UID		CreateTintSwatch(
								IDataBase* db,
								const PMString tintName,
								const PMReal tintPercent
								) = 0;

		/**
			CreateGradient reconstructs a gradient from it's various elements.
			@param db - The database to make the gradient in.
			@param gradientName - The name of the gradient.
			@param gradientType - The type of the gradient (radial or linear).
			@param stopColor - An array of stop colors.
			@param stopPos - An array of stop positions.
			@param midPoint - An array of midpoint positions.
			@return - The gradient UID.
		*/
		virtual UID		CreateGradient(
								IDataBase* db,
								const PMString& gradientName,
								const GradientType gradientType,
								K2Vector<UID> stopColor,
								K2Vector<PMReal> stopPos,
								K2Vector<PMReal> midPoint
								) = 0;
								
		/**
			MakeQName constructs a fully qualified name from a local name.
			The difference is the aic: namespace (Adobe InCopy) prefix.
			@param localName - A tag name.
			@param qName - The qualified tag name.
		*/
		virtual void 	MakeQName(
								const WideString& localName, 
								WideString& qName
								) = 0;
								
		/**
			GrabQName makes a qname and returns it. Simply a wrapper for MakeQName.
			@param localName - A tag name.
			@return - The qualified tag name.
		*/
		virtual ConstWString 	GrabQName(
									const WideString& localName
									) = 0;

		/**
			GrabQName makes qname and returns it.  Simply a wrapper for GrabQName.
			@param localName - A UTF16 string pointer to a tag name.
			@return - The qualified tag name.
		*/
		ConstWString 			GrabQName(const UTF16TextChar* localName)
									{ return this->GrabQName(WideString(localName)); }
										
		/**
			QueryTextMetaDataBoss returns the metadata interface for a story.
			@param textModel - The story text model pointer.
			@param bForceCreate - Whether to create the metadata interface, default is true.
			@return - A pointer to the story's metadata interface
		*/
		virtual IPMUnknown 	*QueryTextMetaDataBoss(
								ITextModel *textModel,
								bool16 bForceCreate = kTrue
								) = 0;
							
							
		/**
			QueryNthStoryMetaDataBoss returns the metadata for the nth story in a document.
			This will create the metadata interface if it does not exist.
			@param document - The document containing the stories.
			@param index - The index in the story list of the story desired.
			@return - A pointer to the story's metadata interface.
		*/
		virtual IPMUnknown *QueryNthStoryMetaDataBoss(
								IDocument *document, 
								int32 index
								) = 0;
		
		/**
			CopyInlines copies inlines from the old story to the beginning of the new story.
			@param oldStory - The old story UIDRef
			@param newStory - The new story UIDRef
			@return - The number of inlines copied.
		*/
		virtual int32 CopyInlines(
						const UIDRef& oldStory,
						const UIDRef& newStory
						) = 0;

		/**
			FindInlineInStory locates an inline story in a target story.
			@param startPos - The text index to start looking from.
			@param tgtStory - The target story
			@param inLineUIDVal - The UID of the inline story to locate
			@return - The index into the text where the story was found (-1 if not found)
		*/
		virtual TextIndex FindInlineInStory(
						TextIndex startPos,
						const UIDRef& tgtStory,
						const int32 inLineUIDVal
						) = 0;

		/**
			SearchStoriesForInline searches all stories of a document for a specified inline story.
			@param db - The document database to search.
			@param inLineUIDVal - The inline story UID.
			@param tgtStory - The story the inline was found in.
			@param startPos - The position of the inline in tgtStory
			@param omitStories - A list of story UIDs to skip.
		*/
		virtual void SearchStoriesForInline(
						IDataBase *db,
						const int32 inLineUIDVal,
						UIDRef& tgtStory,
						TextIndex& startPos,
						UIDList *omitStories
						) = 0;

		/**
			MapInlineToOriginal maintains a list of inline UIDs while importing
			@param index - The text index of the original inline
			@param newStory - The new inline UID
			@param originalInline - The original inline UID
		*/
		virtual void MapInlineToOriginal(
						TextIndex index,
						const UIDRef& newStory,
						const UIDRef& originalInline
						) = 0;
					
		
		/**
			GetInlineInCopyStories returns a list of inline story UIDs for a document.
			@param doc - The document.
			@param stories - The inline stories in that document.
		*/
		virtual void GetInlineInCopyStories(
						IDocument *doc, 
						UIDList& stories
						) = 0;

	/**
		Collects non-InCopy stories from a document.
		@param fromDoc IN document with or without InCopy stories.
		@param doIncludeMasterItems IN indicates if get graphics on master spreads of not
		@return UIDList with both text and graphic stories.
	*/
	virtual UIDList GetNonInCopyTextAndGraphicStories( const IDocument *fromDoc, bool16 doIncludeMasterItems = kTrue ) const = 0;

	/**
		Collects non-InCopy graphic stories from a document; these are text stories
		collected by interating the storylist that do not have an InCopy format datalink.
		@param fromDoc IN document with or without InCopy stories.
		@param doIncludeMasterItems IN indicates if get graphics on master spreads of not
		@return UIDList with non-InCopy stories.
	*/
	virtual UIDList GetNonInCopyTextStories( const IDocument *fromDoc, bool16 doIncludeMasterItems = kTrue ) const = 0;

	/**
		Collects non-InCopy non-inlined graphic stories from a document; these are graphic
		frames collected by interating the spreads' layers including those that appear in 
		groups that do not have an InCopy format datalink.
		@param fromDoc IN document with or without InCopy stories.
		@param doIncludeMasterItems IN indicates if get graphics on master spreads of not
		@return UIDList with non-InCopy stories.
	*/
	virtual UIDList GetNonInCopyGraphicStories( const IDocument *fromDoc, bool16 doIncludeMasterItems = kTrue ) const = 0;

	/**
		Collects list of non-lined graphics from a document; these are graphic frames
		collected by interating the spreads' layers including those that appear in groups.
		The all param lets callers indicate if they want all graphics or only those that
		do not have InCopy format datalink (same as if calling GetNonInCopyGraphicStories).
		@param fromDoc IN document with or without InCopy stories.
		@param all IN indicates is all graphics or just those without InCopy format datalink
		@param thisLayer IN UID of the layer to collect from, kInvalidUID means all layers
		@param doIncludeMasterItems IN indicates if get graphics on master spreads of not
		@return UIDList with graphic frames.
	*/
	virtual UIDList GetAllGraphics( const IDocument *fromDoc, bool16 all = kTrue, UID thisLayer = kInvalidUID, bool16 doIncludeMasterItems = kTrue ) const = 0;

	/**
		Finds the first incopy graphic story in the document, useful when graphic story 
		opened in standalone mode
		@param fromDoc IN document to search
		@return UIDRef of the first found graphic story, UIDRef::gNull if none found
	*/
	virtual UIDRef	GetFirstGraphicStory( const UIDRef& fromDoc ) const = 0;

	/**
		Finds the first incopy text story or incopy graphic story (there should only be one
		in standalone mode) in the document; verifies document is standalone.
		@param fromDoc IN document to search
		@return UIDRef of the first found incopy story, UIDRef::gNull if none found or doc not standalone
	*/
	virtual UIDRef	GetStandaloneStory( const UIDRef& fromDoc ) const = 0;

	/**
		Flag that tells whether InCopy is currently importing a story, in either InDesign or InCopy.
		@return Boolean for importing or not.
	*/
	virtual bool16 IsImporting() = 0;

	/**
		Set the flag that tells whether InCopy is currently importing a story. 
		This shouldn't be called except by the import provider.
		@param Boolean for importing flag.
	*/
	virtual void SetImporting(bool16 importing) = 0;

	/**
		Retrieves the name of the element specified by the ClassID and returns kTrue if the class was found.
		@param ClassID for the class interested in.
		@param WideString IN name of the element.
		@return bool16 kTrue if the class is found.
	*/
	virtual bool16 GetElementName(ClassID cls, WideString *elementName) = 0;
	
	/**
		Get the containing InCopy story for the specified linked item.
		@param linkedObjRef IN uidref of the linked item to get containing incopy story
		@return UIDRef of the containing incopy story (if any)
	*/
	virtual UIDRef GetContainingInCopyStory( const UIDRef& linkedItemRef ) const = 0;

	/**
		Get the outermost InCopy story for the specified text target
		@param target IN text model of the selected story
		@param range IN RangeData of the selected story
		@return UIDRef of the outermost parent incopy story
	*/
	virtual UIDRef GetOutermostParentStory(const UIDRef& target, const RangeData& range) const = 0;

	/**
		Examines both ancestors and decendents for an IID_IFORMFIELD.
		@param itemRef IN UIDRef of item to examine, if a text model will examine the 0th text frame.
		@return bool16 kTrue if item is decended from or by IID_IFORMFIELD.
	*/
	virtual bool16 IsAFormObject(const UIDRef& itemRef) const = 0;
};

#endif	// __IInCopyWorkFlowUtils__
