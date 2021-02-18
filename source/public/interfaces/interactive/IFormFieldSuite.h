//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IFormFieldSuite.h $
//  
//  Owner: Tim Wright
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
//  Comments:	Selection suite for Form items
//  
//========================================================================================

#pragma once
#ifndef _IFormFieldSuite_
#define _IFormFieldSuite_

#include "FormFieldID.h"
#include "FormFieldTypes.h"

//================================================================================================
class IGraphicStyleAttributeBossList;
class ITextAttributes;
class AttributeBossList;
class IFormFieldFactory;

/** Selection suite for manipulating form field page items  and attributes.
	
@see IAppearanceList
*/

class IFormFieldSuite : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFORMFIELDSUITE };

	/** @return kTrue if selection is all form fields (or default selection) */
	virtual bool16 IsFieldSelection() const = 0;

	/** @return kTrue if selection is all form fields (or default selection)
		@param inFormFieldType Type of form field to create (e.g. kPushButtonItemBoss) */
	virtual bool16 IsFieldSelectionOfType(ClassID inFormFieldType) const = 0;
	
	/** @return kTrue if Form Field selection is mixed (not a single type of field) */
	virtual bool16 IsMixedSelection() const = 0; 
	
	/** @return kTrue if Form Field selection is a default pseudo form field item */
	virtual bool16 IsDefaultSelection() const = 0;

	/** Get a factory compatible with the selection.
		returns 0 for default selection, or a mixed selection.
		You can query based on currently selected tool with FormFieldUIUtils...
	*/
	virtual IFormFieldFactory* QueryFormFieldFactory() const = 0;

	/** @return kTrue if selection is a Form Field selection that can be changed */
	virtual bool16 CanEditFieldSelection() const = 0;

	/** @return kTrue if the required form field type can be created from the selection.
		@param inFormFieldType Type of form field to create (e.g. kPushButtonItemBoss) */
	virtual bool16 CanCreateFieldFromSelection(ClassID inFormFieldType) const = 0;

	/** Place selection inside a new form field
		@param inFormFieldType Type of form field to create (e.g. kPushButtonItemBoss) */
	virtual ErrorCode CreateFieldFromSelection(ClassID inFormFieldType) = 0;

	/** @return kTrue if selection is a form field(s) that can be destroyed, i.e. converted to object.
		@param outWarnNonEmptyStates set true if there are states that are not empty that would be lost by destroying the field  */
	virtual bool16 CanDestroyFieldFromSelection(bool16 &outWarnNonEmptyStates) const = 0;

	/** Destroy the selected form fields, i.e. convert the fields back to objects.
		@return kTrue if the fields in selection converted to object successfully 
		@param formFieldToConvert, if this is invoked in the course of converting some form fields to another type,
		then this parameter would be the destination form field type	*/
	virtual ErrorCode DestroyFieldFromSelection(ClassID formFieldToConvert = kInvalidClass) = 0;

	/** @return kTrue if the selection has any form fields	*/
	virtual bool16 SelectionHasAnyFormFields() const = 0;

	/** @return kTrue if the selection has any fields of the type indicated by field type.	*/
	virtual bool16 SelectionHasAnyFieldsOfType(ClassID inFieldType) const = 0;

	/** @return kTrue if all the fields in the selection have their hidden until triggered flag set	
		@Param isMixed indicates whether for the selection, hidden until triggered flag has a mixed value*/
	virtual bool16 GetIsInitiallyHidden(bool16 &isMixed) const = 0;

	/** @return kTrue if all the fields in the selection have their printable flag set	
		@Param isMixed indicates whether for the selection, printable flag has a mixed value*/
	virtual bool16 GetIsPrintable(bool16 &isMixed) const = 0;

	/** @return kTrue if all the fields in the selection have their readonly flag set	
		@Param isMixed indicates whether for the selection, readonly flag has a mixed value*/
	virtual bool16 GetIsReadOnly(bool16 &isMixed) const = 0;

	/** @return kTrue if all the fields in the selection have their required flag set	
		@Param isMixed indicates whether for the selection, required flag has a mixed value*/
	virtual bool16 GetIsRequired(bool16 &isMixed) const = 0;

	/** @return kTrue if all the check boxes and radio buttons in the selection have their selected by default flag set	
		@Param isMixed indicates whether for the selection, selected by default flag has a mixed value*/
	virtual bool16 GetIsSelectedByDefault(bool16 &isMixed) const = 0;

	/** @return kTrue if all the text fields in the selection have their multiline flag set	
		@Param isMixed indicates whether for the selection, multiline flag has a mixed value*/
	virtual bool16 GetIsMultiLineTextField(bool16 &isMixed) const = 0;

	/** @return kTrue if all the text fields in the selection have their password flag set	
		@Param isMixed indicates whether for the selection, password flag has a mixed value*/
	virtual bool16 GetIsPasswordTextField(bool16 &isMixed) const = 0;

	/** @return kTrue if all the text fields in the selection have their scrollable flag set	
		@Param isMixed indicates whether for the selection, scrollable flag has a mixed value*/
	virtual bool16 GetIsScrollableTextField(bool16 &isMixed) const = 0;

	/** Get the description for all the selected form fields. 
	@return kSuccess if no error occurred while getting description for the form fields	*/
	virtual ErrorCode GetFormFieldDescription(PMString &description) const = 0;

	/** Set the hidden until triggered flag for all the selected form fields.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsInitiallyHidden(bool16 inHidden) const = 0;

	/** Set the printable flag for all the selected form fields.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsPrintable(bool16 isPrintable) const = 0;

	/** Set the readonly flag for all the selected form fields.
	@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsReadOnly(bool16 isReadOnly) const = 0;

	/** Set the required flag for all the selected form fields.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsRequired(bool16 isRequired) const = 0;

	/** Set the selected by default flag for the selected radio buttons or check boxes.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsSelectedByDefault(bool16 isSelectedByDefault) const = 0;

	/** Set the multiline flag for all the selected text fields.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsTextFieldMultiline(bool16 isMultiLine) const = 0;

	/** Set the password flag for all the selected text fields.
		@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsTextFieldPasswordField(bool16 isPasswordField) const = 0;

	/** Set the scrollable flag for all the selected text fields.
	@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsTextFieldScrollable(bool16 isScrollable) const = 0;

	/** Set the description for all the selected form fields.
	@return kSuccess if the description is set successfully for all the fields.	*/
	virtual ErrorCode SetFormFieldDescription(const PMString &description) const = 0;

	/** Get the list of choices for the selected combo/list box.	
	@return kSuccess if no error occurs while getting the list of choices for 
	the selected list/combo box.	*/
	virtual ErrorCode GetChoiceList(Form::ChoiceList &choices) const = 0;

	/** Add a choice to the list of choices for the selected combo/list box.	
	@return kSuccess if no error occurs while adding the choice for the selected list/combo box.	*/
	virtual ErrorCode AddChoice(const PMString &choice) const = 0;

	/** Remove a choice from the list of choices for the selected combo/list box.	
	@return kSuccess if no error occurs while removing the choice from the list of 
	choices for the selected list/combo box.	*/
	virtual ErrorCode RemoveChoice(const PMString &choice) const = 0;

	/** Set the multiple selection flag for all the selected Combo boxes/list fields.
	@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsMultipleSelectionEnabled(bool16 isMultipleSelectionEnabled) const = 0;

	/** @return kTrue if all the list/combo fields in the selection have their multiple selection flag set	
		@Param isMixed indicates whether for the selection, the sort flag has a mixed value*/
	virtual bool16 GetIsMultipleSelectionEnabled(bool16 &isMixed) const = 0;

	/** Move the currently selected option to position specified by pos in the combo/list box options.*/
	virtual ErrorCode MoveChoice(const PMString &choice, int32 pos) const = 0;

	/** Set the font size for the text in text field, list box, combo box.*/
	virtual ErrorCode SetTextSizeAttribute(const PMReal &FontSize) const = 0;

	/** Get the Font Size attribute for all the selected fields. 
	@return kTrue if the font size is same for all fields.	*/
	virtual bool16 GetTextSizeAttribute(PMReal &FontSize) const = 0;

	/** @return kTrue if all the list/combo fields in the selection have their multiple selection flag set	
		@Param isMixed indicates whether for the selection, the sort flag has a mixed value*/
	virtual bool16 GetShouldSortListItems(bool16 &isMixed) const = 0;

	/** Set the sorted flag for all the selected text fields.
	@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetShouldSortListItems(bool16 isSorted) const = 0;

	/** @return kTrue if all the list/combo/text fields in the selection have ME right to left flag set	
		@Param isMixed indicates whether for the selection, the ME right to left flag has a mixed value*/
	virtual bool16 GetIsMERTLEnabled(bool16 &isMixed) const = 0;

	/** Set the ME right to left flag for all the selected list/combo/text fields.
	@return kSuccess if the flag is set successfully for all the fields.	*/
	virtual ErrorCode SetIsMERTLEnabled(bool16 isMERTLEnabled) const = 0;

	/** Get the default option for the list box/combo box.
		@return kTrue if a default choice had been specified for the list/combo box.
		@Param choice is the string which has the default choice if any default choice had been set. 
		@Param index is the index of the default choice. If no default choice had been set, this will
		be set to -1. */
	virtual bool16 GetDefaultChoice(PMString &choice, int32 &index) const = 0;

	/** Set the default option for the list box/combo box. 
		@return kSuccess if the flag is set successfully for all the fields.
		@Param choice is the default choice to be set.	*/
	virtual ErrorCode SetDefaultChoice(const PMString &choice) const = 0;

	/** Get the export value for all the selected radios and checks. 
	@return kSuccess if no error occurred while getting export value for the the selected radios and checks.	*/
	virtual ErrorCode GetExportValue(PMString &exportValue) const = 0;

	/** Set the export value for all the selected radios and checks. 
	@return kSuccess if no error occurred while setting export value for the the selected radios and checks.	*/
	virtual ErrorCode SetExportValue(const PMString &exportValue) const = 0;

	virtual ErrorCode SetFontFamilyAttr(const PMString& fontFamilyName) const = 0;
	virtual bool16	GetFontFamilyAttribute(PMString& fontFamilyName) const = 0;
	virtual ErrorCode SetFontFamilyUIDAttr(const PMString& fontFamilyName, const PMString& fontStyleName) const = 0;
	virtual bool16	GetFontFamilyUIDAttr(UID& FontUID) const = 0;
	virtual ErrorCode SetFontStyleAttribute(const PMString& fontStyleName) const = 0;
	virtual bool16 GetFontStyleAttribute(PMString& fontStyleName) const = 0;

#ifdef DEBUG
	virtual ErrorCode TraceSelectionGeometry() = 0;
#endif
};


#endif // _IFormFieldSuite_
