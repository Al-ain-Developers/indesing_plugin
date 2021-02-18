//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkFacade.h $
//  
//  Owner: Jianlan Song
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
//  Note:
//  
//========================================================================================

#pragma once

#include "Utils.h"

// ----- Interfaces -----
#include "IHyperlinkAppearanceData.h"
#include "IPDFHyperlinks.h"

// ----- ID.h files -----
#include "HyperlinkID.h"

class XRefBuildingBlock;

/** Structure used by IHyperlinkFacade::ChangeHyperlink to specify attributes to be changed for the hyperlink.

	newDestination - new destination for the hyperlink. Default to kInvalidUIDRef.
	newSource - new source for the hyperlink. Default to kInvalidUIDRef.
	newName - new name for the hyperlink. Default to empty string.
	visible - kTrue if the new hyprelink has visible rectangle bordor. kFalse otherwise. Default is kFalse.
	borderLineWidth - hyperlink border line width. Default is 1.
	borderColor - border line color UID. Default to kInvalidUID to use default color.
	hilight - hyperlink hilight setting. Default is no hilight.
	outlineStyle - hyperlink outline style. Default is solid outline.
	hyperlinkAltText - hyperlink alternate text. Default is empty.
*/
struct HyperlinkChanges
{
	HyperlinkChanges() : 
		changeDestination(kFalse), newDestination(kInvalidUIDRef), 
		changeSource(kFalse), newSource(kInvalidUIDRef),
		changeName(kFalse), newName(),
		changeVisibility(kFalse), visible(kFalse),
		changeBorderWidth(kFalse), borderLineWidth(1),
		changeBorderColor(kFalse), borderColor(kInvalidUID),
		changeHilight(kFalse), hilight(IHyperlinkAppearanceData::kNoHyperlinkHilight),
		changeOutline(kFalse), outlineStyle(IHyperlinkAppearanceData::kHyperlinkSolidOutline),
		changeHyperlinkAltText(kFalse), hyperlinkAltText(PMString(""))
	{}

	bool16 changeDestination;
	UIDRef newDestination;

	bool16 changeSource;
	UIDRef newSource;

	bool16 changeName;
	PMString newName;

	bool16 changeVisibility;
	bool16 visible;

	bool16 changeBorderWidth;
	int32 borderLineWidth;

	bool16 changeBorderColor;
	UID borderColor;

	bool16 changeHilight;
	IHyperlinkAppearanceData::HyperlinkHilight hilight;

	bool16 changeOutline;
	IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle;

	bool16 changeHyperlinkAltText;
	PMString hyperlinkAltText;
};

namespace Facade
{
	/** A high level API for dealing with hyprelink objects.  To use this Facade, include
		this header file and use the following example syntax:
		result = Utils<Facade::IHyperlinkFacade>()->CreateHyperlink( ... );

		Following are different hyperlink related objects:
		
		Hyperlink destination - Target of a hyperlink. It is where a hyperlink points to. Hyperlink destination
							can be a page destination, text destination, URL destination or external page 
							destination. 
		Hyperlink text desintation - Text target of a hyperlink. It can be a user created text anchor position or
								a targeted paragraph.
		Hyperlink page destination - Page target of a hyperlink. It is a local page targeted by a hyperlink.
		Hyperlink URL destination - URL target of a hyperlink. It is a URL destination created by user.
		Hyperlink exteranl page destination - External page targeted by a hyperlink. It is a special proxy destination
										in the database to track the external page targeted by a local hyperlink.

		Hyperlink source - Source of a hyperlink. It is where the hyperlink hot spot lives. Hyperlink source
						can be either a text hyperlink source or a page item hyperlink source. A text hyperlink source
						may be a static hyperlink source, which is a regular hyperlink whose content is static text, or 
						a cross reference source, whose content is dynamically calculated from the destination.
		Hyperlink text source - Text source of a hyperlink. If the text source is a cross reference, the source content is calculated
							using the cross reference format referenced by the source object.
		Hyperlink page item source - Page item source of a hyperlink.

		Hyperlink - Hyperlink object links corresponding hyperlink source and destination object. The corresponding hyperlink source 
				object needs to be created prior to the creation of a hyperlink object. But the corresponding destination object may 
				be created prior or after the creation of the hyperlink object.

		Cross reference format - Application pre-defined or customer created formats in the document. It is referenced in cross 
							reference source object for content calculation. 

		Bookmark - User created bookmarks in the document which target a text or page destination. 
		
	     @author Jianlan Song
	*/
	class IHyperlinkFacade : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IHYPERLINKFACADE };

#pragma mark Hyperlink

		/**	Creates a new hyperlink object.
		
			@param hyperlinkSource - Hyperlink source object associated with the new hyperlink.
			@param hyperlinkDestination - Hyperlink destination object associated with the new hyperlink.
			@param newHyperlink - [OUT] Returns newly created hyperlink if pointer is non-nil. 
			@param hyperlinkName - name of the hyperlink. Default to be empty string in which case a unique name will be generated.
			@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.
			@param defaultAppearance - kTrue to use default appearance for the hyperlink. kFalse otherwise. Default is kTrue. 
									In case of kTrue, we ignore the following appearance parameters.  
			@param visibleRectangle - kTrue if the new hyprelink has visible rectangle border. kFalse otherwise. Default is kFalse.
			@param borderLineWidth - hyperlink border line width. Default is 1.
			@param borderColor - border line color UID. Default to kInvalidUID to use default color.
			@param hilight - hyperlink hilight setting. Default is no hilight.
			@param outlineStyle - hyperlink outline style. Default is solid outline.
			@param altText - hyperlink alt text. Default is empty.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlink
							(
								UIDRef hyperlinkSource,
								UIDRef hyperlinkDestination,
								UIDRef* newHyperlink = nil,
								const PMString& hyperlinkName = "",
								bool16 visible = kTrue,
								bool16 defaultAppearance = kTrue,
								bool16 visibleRectangle = kFalse,
								int32 borderLineWidth = 1,
								UID borderColor = kInvalidUID,
								IHyperlinkAppearanceData::HyperlinkHilight hilight = IHyperlinkAppearanceData::kNoHyperlinkHilight,
								IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle = IHyperlinkAppearanceData::kHyperlinkSolidOutline,
								const PMString& altText = ""
							) = 0;
		
		/**	Deletes hyperlinks. This method deletes the specified hyperlink object and 
			disassociate the hyperlink with corresponding hyperlink source. 
			However the hyperlink source object still exists. If you want to delete hyperlink source object, 
			you need to call IHyperlinkFacade::DeleteHyperlinkSource. 
			For associated destination of the deleted hyperlink, if it is a hidden destination, 
			we delete the destination as well because there can only be one hyperlink referencing a hidden destination. 
			If the destination is a visible(sharable) destination, it will not be deleted after the operation.
		
			@param hyperlinks - hyperlinks to be deleted. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode DeleteHyperlinks
							(
								UIDList hyperlinks
							) = 0;
		
		/**	Rename a hyperlink.
		
			@param hyperlink - Hyperlink to be renamed. 
			@param newName - new name for the hyperlink.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameHyperlink
							(
								UIDRef hyperlink,
								const PMString& newName
							) = 0;

		/**	Change the source for a hyperlink.
		
			@param hyperlink - Hyperlink to be changed. 
			@param newSource - new source for the hyperlink.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeSourceForHyperlink
							(
								UIDRef hyperlink,
								UIDRef newSource
							) = 0;

		/**	Change the destination for a hyperlink.
		
			@param hyperlink - Hyperlink to be changed. 
			@param newDestination - new destination for the hyperlink.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeDestinationForHyperlink
							(
								UIDRef hyperlink,
								UIDRef newDestination
							) = 0;

		/**	Change the  hyperlink appearance to default apperance.
		
			@param hyperlink - Hyperlink to be changed. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkToDefaultAppearance
							(
								UIDRef hyperlink
							) = 0;
		
		/**	Change the  hyperlink appearance.
		
			@param hyperlink - Hyperlink to be changed. 
			@param changeVisible - kTrue to change visibility of the hyperlink. kFalse otherwise. 
			@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. 
			@param changeWidth - kTrue to change border line width of the hyperlink. kFalse otherwise. 
			@param borderLineWidth - hyperlink border line width. 
			@param changeBorderColor - kTrue to change border color of the hyperlink. kFalse otherwise. 
			@param borderColor - border line color UID. 
			@param changeHilight - kTrue to change hilight of the hyperlink. kFalse otherwise. 
			@param hilight - hyperlink hilight setting. 
						@See IHyperlinkAppearanceData::HyperlinkHilight.
			@param changeOutlineStyle - kTrue to change outline style of the hyperlink. kFalse otherwise. 
			@param outlineStyle - hyperlink outline style. 
								@See IHyperlinkAppearanceData::HyperlinkOutlineLineStyle.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkAppearance
							(
								UIDRef hyperlink,
								bool16 changeVisible ,
								bool16 visible,
								bool16 changeWidth ,
								int32 borderLineWidth,
								bool16 changeBorderColor,
								UID borderColor,
								bool16 changeHilight,
								IHyperlinkAppearanceData::HyperlinkHilight hilight,
								bool16 changeOutlineStyle,
								IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle
							) = 0;

		/**	Change the  hyperlink visibility.
		
			@param hyperlink - Hyperlink to be changed. 
			@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkVisibility
							(
								UIDRef hyperlink,
								bool16 visible
							) = 0;

		/**	Change the  hyperlink border line width.
		
			@param hyperlink - Hyperlink to be changed. 
			@param borderLineWidth - hyperlink border line width. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkBorderWidth
							(
								UIDRef hyperlink,
								int32 borderLineWidth
							) = 0;
		
		/**	Change the  hyperlink border line color.
		
			@param hyperlink - Hyperlink to be changed. 
			@param borderColor - border line color UID. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkBorderColor
							(
								UIDRef hyperlink,
								UID borderColor 
							) = 0;

		/**	Change the  hyperlink hilight.
		
			@param hyperlink - Hyperlink to be changed. 
			@param hilight - hyperlink hilight setting. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkHilight
							(
								UIDRef hyperlink,
								IHyperlinkAppearanceData::HyperlinkHilight hilight
							) = 0;
		
		/**	Change the  hyperlink outline style.
		
			@param hyperlink - Hyperlink to be changed. 
			@param outlineStyle - hyperlink outline style. 
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkOutlineStyle
							(
								UIDRef hyperlink,
								IHyperlinkAppearanceData::HyperlinkOutlineLineStyle outlineStyle
							) = 0;


		/**	Change the hyperlink.
		
			@param hyperlink - Hyperlink to be changed. 
			@param changes - Contains changes to be made to the hyperlink.
							@See HyperlinkChanges.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlink
							(
								UIDRef hyperlink,
								const HyperlinkChanges &changes
							) = 0;

		/**	Updates hyperlink destination information. This method is used to update all types of destinations.
		
			@param hyperlinks - Hyperlinks to be updated. If the list is empty, all the hyperlinks in the document will be updated.
			@param openClosedDoc - kTrue to open closed documents to get destination info. kFlase otherwise.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode UpdateHyperlinkDestinationInfo
							(
								UIDList hyperlinks,
								bool16 openClosedDoc = kTrue
							) = 0;
		
#pragma mark HyperlinkTextSource
		
		/**	Deletes hyperlink sources. This method is used to delete all types of hyperlink sources.
		
			@param sources - hyperlink sources to be deleted. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode DeleteHyperlinkSource
							(
								UIDList sources
							) = 0;

		/**	Creates a new hyperlink text source.
			To delete the hyperlink text source, use IHyperlinkFacade::DeleteHyperlinkSource method.
		
			@param story - story UIDRef to create the new source in.
			@param startIndex - Text index of the start of the new source.
			@param length - length of the selection to create the text source. if 0 then this is an insertion point.
			@param newSource - [OUT] Returns newly created hyperlink text source if pointer is non-nil. 
			@param hyperlinkName - Name of the new source. Default is empty string in which case a unique name will be generated.  
			@param charStyle - Character style to be applied to the text source. Default is kInvalidUID in which case no character style
							applied.
			@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkTextSource
							(
								UIDRef story,
								TextIndex startIndex,
								int32 length,
								UIDRef* newSource = nil,
								const PMString& hyperlinkName = "",
								UID charStyle = kInvalidUID,
								bool16 visible = kTrue
							) = 0;

		/**	Creates a new cross reference text source.
			To delete the cross reference text source, use IHyperlinkFacade::DeleteHyperlinkSource method.
		
			@param story - story UIDRef to create the new source in.
			@param startIndex - Text index of the start of the new source.
			@param length - length of the selection to create the text source. if 0 then this is an insertion point.
			@param newSource - [OUT] Returns newly created cross reference text source if pointer is non-nil. 
			@param xrefFormat - UID of the format for cross reference source.
			@param hyperlinkName - Name of the new source. Default is empty string in which case a unique name will be generated.  
			@param visible - kTrue if the new cross reference is visible in UI. kFalse otherwise. Default is kTrue.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateXRefTextSource
							(
								UIDRef story,
								TextIndex startIndex,
								int32 length,
								UID xrefFormat,
								UIDRef* newSource = nil,
								const PMString& hyperlinkName = "",
								bool16 visible = kTrue
							) = 0;

		/**	Renames hyperlink or cross reference text source.
		
			@param source - Hyperlink text source to be changed. 
			@param hyperlinkName - Name of the source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameTextSource
							(
								UIDRef source,
								const PMString& hyperlinkName
							) = 0;

		/**	Changes character style of the hyperlink text source.
		
			@param source - Hyperlink text source to be changed. 
			@param charStyle - character style to be applied. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeTextSourceCharacterStyle
							(
								UIDRef source,
								UID charStyle
							) = 0;
		
		/**	Converts the cross reference source to a hyperlink. 
		
			@param source - cross reference source to be converted. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertXRefToHyperlink
							(
								UIDRef source
							) = 0;

		/**	Changes format used in the cross reference source. 
		
			@param source - cross reference source to be changed. 
			@param xrefFormat - UID of the format for new cross reference source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeFormatForXRef
							(
								UIDRef source,
								UID xrefFormat
							) = 0;

		/**	Converts a hyperlink text source to a cross reference source. 
		
			@param source - Hyperlink text source to be converted. 
			@param xrefFormat - UID of the format for new cross reference source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ConvertHyperlinkToXRef
							(
								UIDRef source,
								UID xrefFormat
							) = 0;
		
		/**	Changes a hyperlink or cross reference text source.
		
			@param source - Text source to be changed. 
			@param changeStory - kTrue to change story of the text source. kFalse otherwise. Default is kFalse.
			@param story - story UIDRef to create the new source in.
			@param changeRange - kTrue to change start index or length of the text source range. kFalse otherwise. Default is kFalse.
			@param startIndex - Text index of the start of the new source.
			@param length - length of the selection to create the text source. Default is 0 which is an insertion point.
			@param changeName - kTrue to change the name of the text source. kFalse otherwise. Default is kFalse.
			@param hyperlinkName - Name of the source. Default is empty string in which case a unique name will be generated.  
			@param changeCharStyle - kTrue to change the character style applied on the text source. kFalse otherwise. Default is kFalse.
			@param charStyle - UID of character style. Default is kInvalidUID in which case no character style applied.
			@param changeXRefInfo - kTrue to change isXRef flag or cross reference format of the text source. kFalse otherwise. Default is kFalse.
			@param isXRef - kTrue if the source to change the text source to a cross reference source. kFalse to a hyperlink text source. Default is kFalse.
			@param xrefFormat - UID of the format for cross reference source. If isXRef is kFalse, xrefFormat is ignored.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeTextSource
							(
								UIDRef source,
								bool16 changeStory,
								UIDRef story,
								bool16 changeRange = kFalse,
								TextIndex startIndex = -1,
								int32 length = -1,
								bool16 changeName = kFalse,
								const PMString& hyperlinkName = "",
								bool16 changeCharStyle = kFalse,
								UID charStyle = kInvalidUID,
								bool16 changeXRefInfo = kFalse,
								bool16 isXRef = kFalse,
								UID xrefFormat = kInvalidUID
							) = 0;

		/**	Updates cross reference source text.
		
			@param xrefs - cross references to be updated. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode UpdateXRefSource
							(
								UIDList xrefs
							) = 0;

		/**	Updates cross reference sources in a book.
		
			@param bookFile - file path to the book file. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode UpdateXRefSrcsForBook
							(
								const IDFile& bookFile
							) = 0;

#pragma mark HyperlinkPageItemSource

		/**	Creates a new hyperlink page item source.
			To delete the hyperlink page item source, use IHyperlinkFacade::DeleteHyperlinkSource method.
		
			@param pageItem - page item to create source from.
			@param newSource - [OUT] Returns newly created hyperlink page item source if pointer is non-nil. 
			@param name - Name of the new source. Default is empty string in which case a unique name will be generated.  
			@param visible - kTrue if the new hyprelink is visible in UI. kFalse otherwise. Default is kTrue.

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkPageItemSource
							(
								UIDRef pageItem,
								UIDRef* newSource = nil,
								const PMString& name = "",
								bool16 visible = kTrue
							) = 0;

		/**	Renames hyperlink page item source.
		
			@param source - page item sources to be changed.
			@param name - new name for the page item source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameHyperlinkPageItemSource
							(
								UIDRef source,
								const PMString& name
							) = 0;

		/**	Changes the page item associated with the hyperlink page item source.
		
			@param source - page item sources to be changed.
			@param pageItem - new page item associated with the source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkPageItemSource
							(
								UIDRef source,
								UIDRef pageItem
							) = 0;

		/**	Changes hyperlink page item source.
		
			@param source - page item sources to be changed.
			@param pageItem - new page item associated with the source. 
			@param name - new name for the page item source. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkPageItemSource
							(
								UIDRef source,
								UIDRef pageItem,
								const PMString& name
							) = 0;
		
#pragma mark HyperlinkTextDestination

		/**	Deletes hyperlink destinations. This method is used to delete all types of destinations.
		
			@param destinations - Destinations to be deleted. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode DeleteHyperlinkDestination
							(
								UIDList destinations
							) = 0;
		
		/**	Creates a new hyperlink text destination.
			To delete the hyperlink text destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param story - Story to create destination in.
			@param position - Insertion point of the text destination marker.
			@param newDest - [OUT] Returns newly created hyperlink text destination if pointer is non-nil. 
			@param name - name of the destination. Default to be empty string which will generate a unique name.  
			@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
			@param useExistingAnchor - kTrue to use existing text anchor if one already exists at the insertion point. 
									kFalse to always insert a new one. Default to kFalse.
			@param isParagraph - kTrue if the new destination is a paragraph destination. kFlase otherwise. Default is kFalse.
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkTextDestination
							(
								UIDRef story,
								TextIndex position,
								UIDRef* newDest = nil,
								const PMString& name = "",
								bool16 visible = kTrue,
								bool16 useExistingAnchor = kFalse,
								int32 uniqueKey = 0
							) = 0;
		
		/**	Creates a new paragraph destination for the paragraph containing the specified text index.
			If there is already a paragraph destination for the paragraph, the exsiting paragraph will
			be returned.
			
			To delete the paragraph destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param story - Story to create destination in.
			@param position - Text index inside the paragraph to create destination for.
			@param newDest - [OUT] If not nil, returns newly created paragraph destination when there is not
							one exists already. If a paragraph destination exists already, return the existing one.
			@param newDestCreated -[OUT] if not nil returns kTrue if a new paragraph destination is created, 
								kFalse if an existing one is returned.
			@param name - name of the destination. Default to be empty string which will generate a unique name.  
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateParagraphDestination
							(
								UIDRef story,
								TextIndex position,
								UIDRef* newDest = nil,
								bool16* newDestCreated = nil,
								const PMString& name = "",
								int32 uniqueKey = 0
							) = 0;

		/**	Renames a hyperlink text destination or a paragraph destination.
		
			@param destination - Hyperlink text destination or paragraph destination to be changed. 
			@param name - name of the destination.   
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameHyperlinkTextDestination
							(
								UIDRef destination,
								const PMString& name
							) = 0;
		
		/**	Changes a hyperlink text destination or paragraph destination. For paragraph destination,
			you may not change the story or anchor position to different paragraph, or error will be returned.
		
			@param destination - Destination to be changed. 
			@param changeStory - kTrue to change the story of the destination. kFalse otherwise. 
			@param story - New story to insert destination in. 
			@param changePosition - kTrue to change the text index of the destination. kFalse otherwise. 
			@param position - Insertion point of the text destination marker. 
			@param changeName - kTrue to change the name of the destination. kFalse otherwise. Default is kFalse.
			@param name - name of the destination. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkTextDestination
							(
								UIDRef destination,
								bool16 changeStory,
								UIDRef story,
								bool16 changePosition,
								TextIndex position,
								bool16 changeName = kFalse,
								const PMString& name = ""
							) = 0;

#pragma mark HyperlinkPageDestination

		/**	Creates a new hyperlink page destination.
			To delete the hyperlink page destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param page - Page to create destination for.
			@param newDest - [OUT] Returns newly created hyperlink text destination if pointer is non-nil. 
			@param name - name of the destination.  
			@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
			@param zoomFact - Zoom factor for exporting to PDF. Default to 1.0.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to type DestXYZ which destination specified as upper-left corner point and a zoom factor.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle which has no area.
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkPageDestination
							(
								UIDRef page,
								UIDRef* newDest,
								const PMString& name,
								bool16 visible,
								PMReal zoomFact = 1.0,
								IPDFHyperlinks::DestinationType pdfFitType = IPDFHyperlinks::DestXYZ,
								PMRect zoomRectangle = kEmptyRect,
								int32 uniqueKey = 0
							) = 0;

		/**	Creates a new hyperlink page destination with auto-generated name based on page number.
			To delete the hyperlink page destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param page - Page to create destination for.
			@param newDest - [OUT] Returns newly created hyperlink text destination if pointer is non-nil. 
			@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
			@param zoomFact - Zoom factor for exporting to PDF. Default to 1.0.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to type DestXYZ which destination specified as upper-left corner point and a zoom factor.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle which has no area.
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkPageDestinationWithAutoName
							(
								UIDRef page,
								UIDRef* newDest,
								bool16 visible,
								PMReal zoomFact = 1.0,
								IPDFHyperlinks::DestinationType pdfFitType = IPDFHyperlinks::DestXYZ,
								PMRect zoomRectangle = kEmptyRect,
								int32 uniqueKey = 0
							) = 0;

		/**	Renames a hyperlink page destination to a user specified name.

			@param destination - page destination to be renamed.
			@param name - name of the destination. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameHyperlinkPageDestination
							(
								UIDRef destination,
								const PMString& name
							) = 0;

		/**	Renames a hyperlink page destination to an auto generated name based on page number.

			@param destination - page destination to be renamed.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode RenameHyperlinkPageDestinationWithAutoName
							(
								UIDRef destination
							) = 0;
		
		/**	Changes zoom settings for a hyperlink page destination.

			@param destination - page destination to be changed.
			@param changeZoomFact - kTrue to change zoom factor. kFalse otherwise. 
			@param zoomFact - Zoom factor for exporting to PDF. 
			@param changeFitType - kTrue to change fit type. kFalse otherwise. Default is kFalse.
		 	@param pdfFitType - Fit type for exporting to PDF. 
		 					Otherwise the value will be one of the type in IPDFHyperlinks::DestinationType. 
			@param changeRect - kTrue to change zoom rectangle. kFalse otherwise. Default is kFalse.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeZoomForHyperlinkPageDestination
							(
								UIDRef destination,
								bool16 changeZoomFact,
								PMReal zoomFact,
								bool16 changeFitType = kFalse,
								int32 pdfFitType = -1,
								bool16 changeRect = kFalse,
								PMRect zoomRectangle = kEmptyRect
							) = 0;

		/**	Changes a hyperlink page destination.

			@param destination - page destination to be changed.
			@param changePage - kTrue to change the page associated with the destination.
			@param page - New page to create destination for.
			@param changeName - kTrue to change the name of the destination.
			@param name - name of the destination. Default to be empty string.  
			@param changeZoomFact - kTrue to change zoom factor. kFalse otherwise. Default is kFalse.
			@param zoomFact - Zoom factor for exporting to PDF. 
			@param changeFitType - kTrue to change fit type. kFalse otherwise. Default is kFalse.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to -1. If changeFitType is kTrue, 
		 					the value will be one of the type in IPDFHyperlinks::DestinationType. 
			@param changeRect - kTrue to change zoom rectangle. kFalse otherwise. Default is kFalse.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkPageDestination
							(
								UIDRef destination,
								bool16 changePage,
								UIDRef page,
								bool16 changeName = kFalse,
								const PMString& name = "",
								bool16 changeZoomFact = kFalse,
								PMReal zoomFact = -1,
								bool16 changeFitType = kFalse,
								int32 pdfFitType = -1,
								bool16 changeRect = kFalse,
								PMRect zoomRectangle = kEmptyRect
							) = 0;

		/**	Changes a hyperlink page destination and auto generate the name based on page number.

			@param destination - page destination to be changed.
			@param changePage - kTrue to change the page associated with the destination.
			@param page - New page to create destination for.
			@param changeZoomFact - kTrue to change zoom factor. kFalse otherwise. Default is kFalse.
			@param zoomFact - Zoom factor for exporting to PDF. 
			@param changeFitType - kTrue to change fit type. kFalse otherwise. Default is kFalse.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to -1. If changeFitType is kTrue, 
		 					the value will be one of the type in IPDFHyperlinks::DestinationType. 
			@param changeRect - kTrue to change zoom rectangle. kFalse otherwise. Default is kFalse.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkPageDestinationWithAutoName
							(
								UIDRef destination,
								bool16 changePage,
								UIDRef page,
								bool16 changeZoomFact = kFalse,
								PMReal zoomFact = -1,
								bool16 changeFitType = kFalse,
								int32 pdfFitType = -1,
								bool16 changeRect = kFalse,
								PMRect zoomRectangle = kEmptyRect
							) = 0;

#pragma mark HyperlinkExternPageDestination

		/**	Creates a new hyperlink external page destination.
			To delete the hyperlink external page destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param db - database of the document where the new destination will be added.
			@param filePath - full file name of the document for the external page.
			@param pageIndex - Page index of the external page.
			@param newDest - [OUT] Returns newly created hyperlink external page destination if pointer is non-nil. 
			@param zoomFact - Zoom factor for exporting to PDF. Default to 1.0.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to type DestXYZ which destination specified as upper-left corner point and a zoom factor.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle which has no area.
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkExternPageDestination
							(
								IDataBase* db,
								const PMString& filePath,
								int32 pageIndex,
								UIDRef* newDest = nil,
								PMReal zoomFact = 1.0,
								IPDFHyperlinks::DestinationType pdfFitType = IPDFHyperlinks::DestXYZ,
								PMRect zoomRectangle = kEmptyRect,
								int32 uniqueKey = 0
							) = 0;

		/**	Changes page index of a hyperlink external page destination.

			@param destination - page destination to be changed.
			@param pageIndex - New page index of the external page. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangePageIndexForHyperlinkExternPageDest
							(
								UIDRef destination,
								int32 pageIndex 
							) = 0;
		
		/**	Changes zoom settings for a hyperlink external page destination.

			@param destination - Hyperlink external page destination to be changed.
			@param changeZoomFact - kTrue to change zoom factor. kFalse otherwise. 
			@param zoomFact - Zoom factor for exporting to PDF. 
			@param changeFitType - kTrue to change fit type. kFalse otherwise. Default is kFalse.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to -1. If changeFitType is kTrue,
		 					the value will be one of the type in IPDFHyperlinks::DestinationType. 
			@param changeRect - kTrue to change zoom rectangle. kFalse otherwise. Default is kFalse.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeZoomForHyperlinkExternPageDest
							(
								UIDRef destination,
								bool16 changeZoomFact,
								PMReal zoomFact,
								bool16 changeFitType = kFalse,
								int32 pdfFitType = -1,
								bool16 changeRect = kFalse,
								PMRect zoomRectangle = kEmptyRect
							) = 0;
		
		/**	Changes a hyperlink external page destination.
		
			@param destination - Hyperlink external page destination to be changed. 
			@param changeFile - kTrue to change the file path of the destination. kFalse otherwise. 
			@param filePath - New file name of the document for the destination. 
			@param changePageIndex - kTrue to change the page index of the destination. kFalse othersie. 
			@param pageIndex - New page index of the external page. If changePageIndex is kFalse, pageIndex is ignored.
			@param changeZoomFact - kTrue to change zoom factor. kFalse otherwise. Default is kFalse.
			@param zoomFact - Zoom factor for exporting to PDF. 
			@param changeFitType - kTrue to change fit type. kFalse otherwise. Default is kFalse.
		 	@param pdfFitType - Fit type for exporting to PDF. Default to -1. If changeFitType is kTrue,  
		 					the value will be one of the type in IPDFHyperlinks::DestinationType. 
			@param changeRect - kTrue to change zoom rectangle. kFalse otherwise. Default is kFalse.
			@param zoomRectangle - Zoom rectangle for exporting to PDF. Default to a empty rectangle.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkExternPageDestination
							(
								UIDRef destination,
								bool16 changeFile,
								const PMString& filePath,
								bool16 changePageIndex,
								int32 pageIndex,
								bool16 changeZoomFact = kFalse,
								PMReal zoomFact = -1,
								bool16 changeFitType = kFalse,
								int32 pdfFitType = -1,
								bool16 changeRect = kFalse,
								PMRect zoomRectangle = kEmptyRect
							) = 0;

#pragma mark HyperlinkURLDestination

		/**	Creates a new hyperlink URL destination.
			To delete the hyperlink URL destination, use IHyperlinkFacade::DeleteHyperlinkDestination method.
		
			@param db - database of the document where the new destination will be added.
			@param urlString - URL string for the destination.
			@param newDest - [OUT] Returns newly created hyperlink URL destination if pointer is non-nil. 
			@param name - name of the destination. Default is empty string in which case a unique name will be generated.
			@param visible - kTrue if the new destination is visible in UI. kFalse otherwise. Default is kTrue.
			@param uniqueKey - unique key to assign to the destination. Default is 0 in which case a unique key will
								be generated.
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateHyperlinkURLDestination
							(
								IDataBase* db,
								const PMString& urlString,
								UIDRef* newDest = nil,
								const PMString& name = "",
								bool16 visible = kTrue,
								int32 uniqueKey = 0
							) = 0;

		/**	Changes the name of a hyperlink URL destination.
		
			@param destination - Hyperlink URL destination to be changed. 
			@param name - name of the destination. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkURLDestinationName
							(
								UIDRef destination,
								const PMString& name
							) = 0;

		/**	Changes the URL of a hyperlink URL destination.
		
			@param destination - Hyperlink URL destination to be changed. 
			@param urlString - New URL string for the destination. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkURLDestinationURL
							(
								UIDRef destination,
								const PMString& urlString
							) = 0;

		/**	Changes a hyperlink URL destination.
		
			@param destination - Hyperlink URL destination to be changed. 
			@param urlString - New URL string for the destination. 
			@param name - name of the destination. 
								
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeHyperlinkURLDestination
							(
								UIDRef destination,
								const PMString& urlString,
								const PMString& name
							) = 0;

#pragma mark xRefFormat

		/**	Creates a new cross reference format.
		
			@param db - database of the document where the new format will be added.
			@param newFormat - [OUT] Returns newly created cross reference format if pointer is non-nil. 
			@param buildingBlocks - List of building blocks for the format.
			@param name - name of the format. Default to empty string in which case a unique name will be generated.
			@param charStyle - character style of the format.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode CreateXRefFormat
							(
								IDataBase* db,
								UIDRef* newFormat = nil,
								const K2Vector<XRefBuildingBlock>* buildingBlocks = nil,
								const PMString& name = "",
								UID charStyle = kInvalidUID
							) = 0;
		
		/**	Deletes cross reference formats.
		
			@param formats - cross reference formats to be deleted. 

			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode DeleteXRefFormat
							(
								UIDList formats
							) = 0;

		/**	Changes name of a cross reference format.
		
			@param format - cross reference format to be changed. 
			@param name - new name for the format. name should be a non empty string.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeXRefFormatName
							(
								UIDRef format,
								const PMString& name
							) = 0;

		/**	Changes character style of a cross reference format.
		
			@param format - cross reference format to be changed. 
			@param charStyle - new character style for the format.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeXRefFormatCharacterStyle
							(
								UIDRef format,
								UID charStyle
							) = 0;
		
		/**	Changes building blocks of a cross reference format.
		
			@param format - cross reference format to be changed. 
			@param buildingBlocks - new building blocks for the format. This should be a non-nil pointer.
			@param charStyle - new character style for the format.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeXRefFormatBuildingBlocks
							(
								UIDRef format,
								const K2Vector<XRefBuildingBlock>* buildingBlocks
							) = 0;

		/**	Changes a cross reference format.
		
			@param format - cross reference format to be changed. 
			@param name - new name for the format. name should be a non empty string.
			@param buildingBlocks - new building blocks for the format. This should be a non-nil pointer.
			
			@return ErrorCode - result of the operation.
		 */
		virtual ErrorCode ChangeXRefFormat
							(
								UIDRef format,
								const PMString& name,
								const K2Vector<XRefBuildingBlock>* buildingBlocks,
								UID charStyle
							) = 0;

		/** Loads cross reference formats from another file.

			@param db - Target database to load formats to.
			@param sourceFile - Source file to load formats from.

			@return ErrorCode - result of the operation.
		*/
		virtual ErrorCode LoadXRefFormats
							(
								IDataBase* db, 
								const IDFile& sourceFile
							) = 0;
	};
}

