//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLRuleActionFacade.h $
//  
//  Owner: Lonnie Millett
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
//  
//  Purpose:
//  Processes commands for creating, deleting, and manipulating XML element attributes.
//  
//========================================================================================

#pragma once
#ifndef __IXMLRuleActionFacade__
#define __IXMLRuleActionFacade__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"
#include "ISpread.h"

class ICommand;
	
/** Exposes methods to do actions on XMLElements that are typically done with the XML Rules functionality
*/
namespace Facade
{
	class IXMLRuleActionFacade : public IPMUnknown 
	{
		public:
			enum	{kDefaultIID = IID_IXMLRULEACTIONFACADE};

		
			/**
			   Method for applying a paragraph style to an XML element.  This should act the same as if the elements
				text was selected by double-clicking on the element, and then the style applied.
			   @param element the style will be applied to
			   @param styleString the style to apply.  If style is in a style folder, use a path like "MyStyles:Headline"
			   @param clearOverrides specifies whether style overrides should be cleared when applying the style
			   @return ErrorCode kSuccess if the operation could be completed
			 */
			virtual ErrorCode ApplyParagraphStyle(const IIDXMLElement *element, const PMString& styleString, bool16 clearOverrides) = 0;


			/**
			   Method for applying a paragraph style to an XML element.  This should act the same as if the elements
				text was selected by double-clicking on the element, and then the style applied.
			   @param element the style will be applied to
			   @param styleRef the UIDRef of the style to apply.  
			   @param clearOverrides specifies whether style overrides should be cleared when applying the style
			   @return ErrorCode kSuccess if the operation could be completed
			 */
			virtual ErrorCode ApplyParagraphStyle(const IIDXMLElement *element, const UIDRef& styleRef, bool16 clearOverrides) = 0;

			/**	Method for applying a character style to an XML element.  This should act the same as if the elements
				text was selected by double-clicking on the element, and then the style applied.
			   @param element the style will be applied to
			   @param styleString the style to apply.  If style is in a style folder, use a path like "MyStyles:Headline"
			   @return ErrorCode kSuccess if the operation could be completed
			 */
			virtual ErrorCode ApplyCharacterStyle(const IIDXMLElement *element, const PMString& styleString) = 0;
			
			/**	Method for applying a character style to an XML element.  This should act the same as if the elements
				text was selected by double-clicking on the element, and then the style applied.
			   @param element the style will be applied to
			   @param styleRef the UIDRef of the style to apply.  
			   @return ErrorCode kSuccess if the operation could be completed

			 */
			virtual ErrorCode ApplyCharacterStyle(const IIDXMLElement *element, const UIDRef& styleRef) = 0;

			/**	Method for applying an object style to an XML element.  This will apply the style to th element's frame only
				if the element is directly associated with the frame.  If the specified element is a child of a story element
				this will have no effect.  For story elements, object style will be applied to all frames containing the story.
			   @param element element the style will be applied to
			   @param styleString the style to apply.  
			   @return ErrorCode kSuccess if the operation could be completed

			 */
			virtual ErrorCode ApplyObjectStyle(const IIDXMLElement *element, const PMString& styleName, bool16 clearOverrides, bool16 clearOverridesThruRoot) = 0;

			/**	Method for applying an object style to an XML element.  This will apply the style to th element's frame only
				if the element is directly associated with the frame.  If the specified element is a child of a story element
				this will have no effect.  For story elements, object style will be applied to all frames containing the story.
			   @param element the style will be applied to
			   @param styleRef the UIDRef of the style to apply.  
			   @return ErrorCode kSuccess if the operation could be completed

			 */
			virtual ErrorCode ApplyObjectStyle(const IIDXMLElement *element, const UIDRef& styleRef,  bool16 clearOverrides, bool16 clearOverridesThruRoot) = 0;

			enum ElementLocation { kAtStart, kAtEnd };
			/**	DEPRECATED -- Use ConvertAttributeToChildElement with WideString instead.
				Method for converting an attribute with value into a child element with content.The content of the new child element becomes part of its parent element's content.
			   Attribute is removed from the element.
			   @param element the element containing the attribute
			   @param location location of the new element( kAtStart, kAtEnd)
			   @param alternateTagName tag name for the new element(default is to use attribute name)
			   @param outNewChildElement out param which will be filled in with the new child element created
			   @return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode ConvertAttributeToChildElement(IIDXMLElement *element, const PMString& attributeName, ElementLocation location, const PMString& alternateTagName = "", XMLReference* outNewChildElement = nil) = 0;

			/**	Method for converting an attribute with value into a child element with content.The content of the new child element becomes part of its parent element's content.
			   Attribute is removed from the element.
			   @param element the element containing the attribute
			   @param location location of the new element( kAtStart, kAtEnd)
			   @param alternateTagName tag name for the new element(default is to use attribute name)
			   @param outNewChildElement out param which will be filled in with the new child element created
			   @return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode ConvertAttributeToChildElement(IIDXMLElement *element, const WideString& attributeName, ElementLocation location, const WideString& alternateTagName = (WideString)"", XMLReference* outNewChildElement = nil) = 0;

			/**	-- Use ConvertElementToAttributeOnParent with WideString instead.
				Method for converting an element into an attribute on the element's parent.  The content of the element becomes the value for the attribute
			   Element and its content are removed from its parent. We commented this out, since its presence along with the widestring version will result 
			   in an ambiguous error when used with a single parameter.
			   @param element the element to convert to an attribute
			   @param alternateAttributeName attribute name for the new attribute(default is to use tag name)
			   @param outNewAttrName out param which will be filled in with the name of the new attribute
			   @return ErrorCode kSuccess if the operation could be completed		 */
			//virtual ErrorCode ConvertElementToAttributeOnParent(IIDXMLElement *element, const PMString& alternateAttributeName = "", PMString* outNewAttrName = nil) = 0;

			/**	Method for converting an element into an attribute on the element's parent.  The content of the element becomes the value for the attribute
			   Element and its content are removed from its parent
			   @param element the element to convert to an attribute
			   @param alternateAttributeName attribute name for the new attribute(default is to use tag name)
			   @param outNewAttrName out param which will be filled in with the name of the new attribute
			   @return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode ConvertElementToAttributeOnParent(IIDXMLElement *element, const WideString& alternateAttributeName = (WideString)"", WideString* outNewAttrName = nil) = 0;

			/**	DEPRECATED -- Use ConvertElementToTable with WideString instead.
				Method for converting an element into a table in the element's parent.
				Element's child structure is used to delineate rows and cells that contruct the new table 
				Table is tagged with elements tag. Children of element are applied to cell content as appropriate
				@param element the element to convert to a table
				@param tableRowTagName name of the tag used to designate table rows in the element
				@param tableCellTagName name of the tag used to dsignate table cells in the element
			*/	
			virtual ErrorCode ConvertElementToTable(IIDXMLElement* element, const PMString& tableRowTagName, const PMString& tableCellTagName, UIDRef& newTable ) = 0;
			
			/** Method for converting an element into a table in the element's parent.
				Element's child structure is used to delineate rows and cells that contruct the new table 
				Table is tagged with elements tag. Children of element are applied to cell content as appropriate
				@param element the element to convert to a table
				@param tableRowTagName name of the tag used to designate table rows in the element
				@param tableCellTagName name of the tag used to dsignate table cells in the element
			*/	
			virtual ErrorCode ConvertElementToTable(IIDXMLElement* element, const WideString& tableRowTagName, const WideString& tableCellTagName, UIDRef& newTable ) = 0;
			
			/**	Place element into a new frame at the specified location.  If the element is in an existing frame, the existing frame will be deleted.
			   @param element the element to place
			   @param spread attribute name for the new attribute(default is to use tag name)
			   @param pasteboardBounds bounds in pasteboard coordinates to create the frame
			   @param newFrame on return, contains the new frame created
				@return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode PlaceIntoFrame(const IIDXMLElement *element, ISpread* spread, const PMRect& pasteboardBounds, UIDRef& newFrame) = 0;

			/**	Place element into a frame at the specified location.  The frame created will be a copy of the frame passed in pageItemToCopy.
				If the element is in an existing frame, the existing frame will be deleted.
			   @param element the element to place
			   @param spread attribute name for the new attribute(default is to use tag name)
			   @param pasteboardLocation point in pasteboard coordinates to for the top left of the copied frame
			   @param frameToCopy the frame you would like to copy(must have IGraphicFrame)
			   @param retainExistingFrame if true and the element is already placed, the existing frame will be moved to the specified location.  if false, existing frame will be deleted and copied frame used
			   @param newFrame on return, contains the new frame created
				@return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode PlaceIntoCopy(const IIDXMLElement *element, ISpread* spread, const PMPoint& pasteboardLocation, UID frameToCopy, bool16 retainExistingFrame, UIDRef& newFrame) = 0;

			/**	Place element into a inline frame at the existing location of the element in its parent story.  The frame will be rectangular and have default attributes.
				If the element is in an existing frame, the existing frame will be deleted.
			   @param element the element to place
			   @param dimensions width and height of the inline
			   @param newFrame on return, contains the new frame created
				@return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode PlaceIntoInlineFrame(const IIDXMLElement *element, const PMPoint& dimensions, UIDRef& newFrame) = 0;

			/**	Place element into a inline frame at the existing location of the element in its parent story.  The frame will be a copy of the frame passed in pageItemToCopy.
				If the element is in an existing frame, the existing frame will be deleted.
			   @param pageItemToCopy the element to place
			   @param frameToCopy the frame you would like to copy(must have IGraphicFrame)
			   @param retainExistingFrame if true and the element is already an inline, the existing frame will be used.  if false, existing frame will be deleted and copied frame used
			   @param newFrame on return, contains the new frame created
				@return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode PlaceIntoInlineCopy(const IIDXMLElement *element, UID frameToCopy, bool16 retainExistingFrame, UIDRef& newFrame) = 0;

			/**	Replace the existing content of the element with the contents of the file specified by the attribute value of the attribute passed in.
				If the attribute name is a relative path, you can pass a base path as well to allow it to resolve to full path
			   @param pageItemToCopy the element whose content you would like to replace
			   @param filePath an absolute or relative file path
			   @param baseRelativePath for a file reference with relative paths, use this as the base path
				@return ErrorCode kSuccess if the operation could be completed		 */
			virtual ErrorCode SetContent(const IIDXMLElement *element, const PMString& filePath, const PMString& baseReleativePath = "") = 0;

			virtual UID	PlaceOntoPage(const IIDXMLElement *element, const UIDRef& pageOrSpread, const PMPoint& placePoint, bool16 autoflow) = 0;

			/**	Given an element, return a list of graphic frames that contain the element.  Does not follow links to other stories.		
			   @param element the element whose frame chain you would like to get
				@return UIDList of graphic frames		 */
			virtual UIDList GetElementFrames(const IIDXMLElement *element) = 0;
	};
}	
#endif // __IXMLRuleActionFacade__
