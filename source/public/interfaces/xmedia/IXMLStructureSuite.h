//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLStructureSuite.h $
//  
//  Owner: Ryan Gano
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
	#ifndef _IXMLStructureSuite_
	#define _IXMLStructureSuite_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IXMLAccess.h"
	#include "IXMLElementCommands.h"
	#include "IXMLHandler.h"
	#include "ISAXServices.h"
	
class IXMLValidationErrorsCtrlData;
class XMLDTDValidationError;
class IDataLink;
class IXMLValidator;
class IAttributeErrorList;

//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATIONS
//________________________________________________________________________________________
/** Interface to manipulate the properties of the structure when there is an active selection. 
	This is appropriate for selections within the structure view.

	Underneath, this makes use of the interfaces such as IXMLAttributeCommands and
	IXMLElementCommands to process the commands relating to the current selection. 

*/
class IXMLStructureSuite : public IPMUnknown
{
	//____________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IXMLSTRUCTURESUITE };

		/**	Determine if we can AddElement based on the current selection.
			You can't add elements to a placed graphic, if any of the selected elements 
			are placed graphics, return kFalse

			
			@return kTrue if elements can be added to selected element, kFalse otherwise
		 */
		virtual	bool16			CanAddElement() const = 0;

		/**	Graphic elements cannot contain children, so are there any graphic 
			elements in the selection that we would convert? For instance, when you
			add a child element to a graphic frame, the AddElement method will convert
			this to a text frame.

			
			@return  kTrue if selection contains graphic elements that would be converted
				to text frames on AddElement
		 */
		virtual bool16			WillAddChangeGraphicElementToText() const = 0;

		/**	Add Element as a child of the selected node; delegates to IXMLElementCommands::CreateElement
			to create a new element and add into the hierarchy.

			If there is more than 1 element selected or if we have no elements selected,
			would add  a child to the root.

			@param tagRef specifies the tag (IXMLTag) to use for the given element
			@return  kSuccess if a new element could be created and added, kFalse otherwise
		 */
		virtual	ErrorCode		AddElement(const UIDRef& tagRef) = 0;

		/** Use this to determine whether the current selection can be wrapped in
			a new XML element.
			@return - kTrue if the selection can be wrapped
		*/
		virtual	bool16			CanWrapWithElement() const = 0;
		
		/**	Add Element as a parent of the selected nodes and a child of their parent; 
			delegates to IXMLElementCommands::WrapWithElement
			to create a new element and add into the hierarchy.

			@param tagRef specifies the tag (IXMLTag) to use for the given element
			@return  kSuccess if a new element could be created and added, kFalse otherwise
		 */
		virtual	ErrorCode		WrapWithElement(const UIDRef& tagRef) = 0;

		/**	Determine if we can DeleteElements based on the current selection.
			Can't delete the doc element or the root element; 
			also, if there are no elements selected, return kFalse.

			@param deleteChildren kTrue if attempting to delete the children of the given element, 
				and kFalse to leave them in the logical structure
			@param deleteContent kTrue to attempt to remove the content within the tag markers, kFalse to leave it
			@return kTrue if selected elements can be deleted, kFalse if selected element(s) can't be deleted, for instance, if empty or the root element
		 */
		virtual	bool16			CanDeleteElements( bool16 deleteChildren = kTrue, bool16 deleteContent = kFalse ) const = 0;

		/**	Delete all selected elements; delegates to appropriate methods on IXMLElementCommands.

			@param deleteChildren kTrue to delete the children of the given element, 
				and kFalse to leave them in the logical structure
			@param deleteContent kTrue to remove the content within the tag markers, kFalse to leave it
			@return  kSuccess if operation completed, kFailure otherwise
		 */
		virtual	ErrorCode		DeleteElements( bool16 deleteChildren = kTrue, bool16 deleteContent = kFalse ) = 0;

		/**	Determine if we can delete the current selection.
			Can't delete the doc element or the root element or the DocType; 
			also, if there are no elements selected, return kFalse.

			@param deleteChildren kTrue if attempting to delete the children of the given element, 
				and kFalse to leave them in the logical structure
			@param deleteContent kTrue to attempt to remove the content within the tag markers, kFalse to leave it
			@return kTrue if selected elements can be deleted, kFalse if selected element(s) can't be deleted, for instance, if empty or the root element
		 */
		virtual	bool16			CanDeleteSelection( bool16 deleteChildren = kTrue, bool16 deleteContent = kFalse ) const = 0;

		/**	Delete all selected elements, comments, PIs, or Attributes; delegates to appropriate methods in this interface.

			@param deleteChildren kTrue to delete the children of the given element, 
				and kFalse to leave them in the logical structure
			@param deleteContent kTrue to remove the content within the tag markers, kFalse to leave it
			@return  kSuccess if operation completed, kFailure otherwise
		 */
		virtual	ErrorCode		DeleteSelection( bool16 deleteChildren = kTrue, bool16 deleteContent = kFalse ) = 0;

		/**	Determine if we can edit the current selection.
			if there is more or less than one object selected, return kFalse.

			@return kTrue if selected object can be edited, kFalse if selected element(s) can't be edited, for instance, if empty or more than one
		 */
		virtual	bool16			CanEditSelection() const = 0;

		/**	Edit selected element, comment, PI, or Attribute; delegates to appropriate methods in this interface.

			@return  kSuccess if operation completed, kFailure otherwise
		 */
		virtual	ErrorCode		EditSelection() = 0;

		/**	Get the value of the selected comment.  If the selection is anything other than a single 
			comment, comment will be an empty string.
			@param value [OUT] contains current value for selected comment  if single comment selected, empty string otherwise
		 */
		virtual	void	 		GetCommentInfo( PMString* comment) = 0;
	
		/**	Get the target and data of the selected processing instruction.  If the selection is anything other than a single 
			pi, both target and data will be empty strings.
			@param target [OUT] contains target for selected pi if single pi selected, empty string otherwise
			@param data [OUT] contains current data for selected pi  if single pi selected, empty string otherwise
		 */
		virtual	void	 		GetProcessingInstructionInfo( PMString* target, PMString* data) = 0;

		/**	Determine if we can add an attribute to the current selection
			
			@return  kTrue if attribute can be added to current selection
		 */
		virtual	bool16			CanAddAttribute() const = 0;

		/**	Determine if we can add the specified attribute to the current selection;
			if the attribute exists on any of the elements, we can't add it.
			@param name specifies the name for the attribute
			@return  kTrue if named attribute can be added, kFalse otherwise
		 */
		virtual	bool16			CanAddSpecificAttribute(const PMString& name) const = 0;

		/**	Determine if we can add an attribute to the current selection
			@param name specifies the name for the attribute
			@param value specifies the value that the attribute should have
			@return ErrorCode kSuccess if operation completed, kFailure otherwise
		 */
		virtual ErrorCode 		AddAttribute(const PMString& name, const PMString& value) = 0;


		/**	Can we replace attribute based on current selection?
			
			@return  kTrue if attribute can be changed/replaced, kFalse otherwise
		 */
		virtual	bool16			CanChangeOrReplaceAttribute() const = 0;

		/**	Can we replace attribute with the specified name
			@param name specifies the name for the attribute
			@return  
		 */
		virtual	bool16			CanReplaceAttribute(const PMString& name) const = 0;

		/**	Change the value of the selected attribute
			@param name specifies the name for the attribute
			@param value specifies the value that the attribute should have
			@return ErrorCode kSuccess if operation completed, kFailure otherwise
		*/
		virtual	ErrorCode 		ChangeAttribute(const PMString& name, const PMString& value) = 0;

		/**	Change the name and value of the selected attribute, 
			essentially removing the selected attribute and adding a new one
			@param name specifies the name for the attribute
			@param value specifies the value that the attribute should have
			@return ErrorCode kSuccess if operation completed, kFailure otherwise
		 */
		virtual	ErrorCode 		ReplaceAttribute(const PMString& name, const PMString& value) = 0;


		/**	Determine if we can delete selected attributes
			
			@return  kTrue if we can delete the attributes in the active selection,
				kFalse otherwise
		 */
		virtual	bool16			CanDeleteAttributes() const = 0;

		/**	Delete attributes of selected node
			
			@return ErrorCode kSucess if the operation completed successfully, kFailure otherwise
		 */
		virtual ErrorCode 		DeleteAttributes() = 0;


		/**	Get the name and value of the selected attribute.  If the selection is anything other than a single 
			attribute, both name and value will be empty strings.
			@param name [OUT] contains name for selected attribute if single attribute selected, empty string otherwise
			@param value [OUT] contains current value for selected attribute  if single attribute selected, empty string otherwise
		 */
		virtual	void	 		GetAttributeInfo( PMString* name, PMString* value) = 0;

		/**	Export the XML based on selection; check IsExportable first
			@param access specifies interface that's part of Visitor pattern for XML export
			@param exportHandler handler that will invoke IXMLGenerator methods to write out the contebt
			@param exportPageItem If kFalse, export from the selected element. If kTrue, export starts
			at the page item element associated with the selected element
			@return ErrorCode kSucess if the operation completed successfully, kFailure otherwise
		 */
		virtual ErrorCode Export( IXMLAccess* access, IXMLHandler* exportHandler, const IDFile& sysFile, bool16 exportPageItem = kFalse,
				const PMString& formatName = "XML", UIFlags uiFlags = kSuppressUI) = 0;

		/**	Can we export from the current selection?
			Return kTrue only if one element is selected.
			
			@return kTrue if can export from active selection, kFalse if we can't, e.g. if more than one element selected 
		 */
		virtual bool16			IsExportable() const = 0;

		/**	Import into selected element from a file; check IsImportable first
			@param db database to be imported into
			@param file pointer to a IDFile to import
			@param flags specifies how much UI to show during import
			@return  kSuccess if operation succeeded, kFailure otherwise
		 */
		virtual ErrorCode		Import( IDataBase *db,  const IDFile *file, UIFlags flags ) = 0;

		/**	Can we import into the current selection? Expects a single selection; will
			return kFailure if more than one element selected.
			Return kTrue only if one element is selected.
			
			@return  kTrue if can be imported into current selection, kFalse if can't, or if more than one element selected at entry
		 */
		virtual bool16			IsImportable() const = 0;

		/**	Is the selected element a known DTD validation problem.  This relies on the
			IID_IBOOLDATA interface on the element (non-persistent) to determine whether
			or not the element/attribute is in an error state
			Return kTrue only if one element is selected. and IBoolData is kFalse
			@param attrErrors List of attributes currently in an error state
			
			@return  kTrue single selected element is in an error state, kFalse if element is OK, or if more than one element selected at entry
		 */

		virtual bool16			IsSelectionInErrorState(IAttributeErrorList *attrErrors) const = 0;

		/**	Select the error that matches this element in the Validation panel
			@param validationErrors Interface that contains the current list of known errors.
			@param attrErrors List of attributes currently in an error state
			
			@return  kFailure if the element isn't in an error state, there is multiple selection, or the error couldn't be found in the list passed in.
					 kSuccess otherwise.
		 */

		virtual ErrorCode			SelectErrorInValidation(IXMLValidationErrorsCtrlData *validationErrors, IAttributeErrorList *attrErrors) = 0;
		
		/**	Can the current selection be validated against the DTD?
			
			@return  whether or not validation can occur.
		 */
		virtual bool16			CanValidateSelection() const = 0;

		/**	Validate this element and its children against the DTD
		 */
		virtual void				ValidateSelection(IXMLValidator *errors) = 0;
		
		/**	Can the current selection change its auto tagging setting?
			
			@return  whether or not it can.
		 */
		virtual bool16 	CanSetTableTagPreference() const = 0;
		
		/**	Change the auto tag setting on the  current selection
			@param newSetting	new setting to apply (row/column/none)
			
			@return  kSuccess or a failure code
		 */
		virtual ErrorCode 	SetTableTagPreference(IXMLElementCommands::TableTagPreference newSetting) = 0;
};



#endif // _IXMLStructureSuite_
