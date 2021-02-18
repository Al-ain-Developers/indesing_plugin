//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportOptionsService.h $
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
#ifndef __IXMLImportOptionsService__
#define __IXMLImportOptionsService__

#include "IPMUnknown.h"
#include "XMediaUIID.h"

class IControlView;
class IDocument;
//----------------------------------------------------------------------------------------
// IXMLImportOptionsService
//----------------------------------------------------------------------------------------

/** Interface that provides methods needed to automatically build
	the UI elements for the XML import options dialog. Should be 
	used in conjunction with kXMLImportUIService
*/
class IXMLImportOptionsService : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIXMLIMPORTOPTIONSSERVICE };
	
	typedef enum {
		/** Indicates that this element is a checkbox */
		kCheckbox, 
		/** Indicates that this element is a popup */
		kPopup, 
		/** Indicates that this element is a radio group */
		kRadioGroup, 
		/** Indicates that this element is a filename widget */
		kFileName} kUIElementType;

	/**
	Use this to initialze the state of each of the controls
	This simply makes it easier and faster to retrieve info
	about various controls while the dialog is running

	@param doc - The document we are initializing the options
				 for. This is important because different docs
				 can have different default options
	*/
	virtual void Initialize(IDocument *doc) = 0;

	/**
	Warn this service that another control has changed values
	This gives this service a chance to change its state when
	other controls that it may care about change their states

	@param changedService - The service that has been changed
	@param controlView - The control view of the element being changed
	@param which - Which element in the service changed
	@return - A list of elements that cared (empty list if nobody cares)
	*/
	virtual K2Vector<int32> WarnOfChange(IXMLImportOptionsService *changedService, IControlView *controlView, int32 which) = 0;

	/**
	Commit the changes that have been stored while the dialog
	was open.
	*/
	virtual void CommitChanges() = 0;
	/**
	Get the name of the group box for this list of options.
	A group box will not be added if the name is an empty string

	@return - the name of the import options group
	*/
	virtual PMString GetGroupName() const = 0;

	/**
	Get the number of UI elements that this Service Provider supports

	@return - the number of elements supported
	*/
	virtual int32 GetUIElementsCount() const = 0;

	/**
	Get the enabled state of the Nth element

	@param n - The item you want information about
	@return - 'kTrue' element should be enabled
	*/
	virtual bool16 IsNthElementEnabled(int32 n) const = 0;

	/**
	Get the type of the Nth element

	@param n - The item you want information about
	@return - The type of the element
	*/
	virtual IXMLImportOptionsService::kUIElementType GetNthElementType(int32 n) const = 0;

	/**
	Get the name of the Nth element

	@param n - The item you want information about
	@return - The name of the element that should appear in the dialog
	*/
	virtual PMString GetNthElementName(int32 n) const = 0;

	/**
	Get the value of the Nth element

	@param n - The item you want information about
	@return - The default value for this UI element 
			  (kFalse if the element is not a checkbox)
	*/
	virtual bool16 GetNthElementBoolValue(int32 n) const = 0;

	/**
	Get the value of the Nth element

	@param n - The item you want information about
	@param newValue - The new value for this UI element
	*/
	virtual void SetNthElementBoolValue(int32 n, bool16 newValue) = 0;
	
	/**
	Get the list of items in the popup.

	NOTE: This is only used for popup elements

	@param n - The item you want information about
	@param valueList - Filled with all of the items in the popup
	*/
	virtual void GetNthElementPopupValueList(int32 n, K2Vector<PMString> &valueList) const = 0;
	
	/**
	Get the item to select in the popup or radio group.

	NOTE: This is only used for popup or radio group elements

	@param n - The item you want information about
	@return - The item to be selected by default (-1 if this is not a popup)
	*/
	virtual int32 GetNthElementIntValue(int32 n) const = 0;
	
	/**
	Set the item that the user selected in the popup or radio group.

	NOTE: This is only used for popup or radio group elements

	@param n - The item you want information about
	@param selected - The item that is selected
	*/
	virtual void SetNthElementIntValue(int32 n, int32 selected) = 0;
	
	/**
	Get the filename to use by default in the filename widget.

	NOTE: This is only used for filename elements

	@param n - The item you want information about
	@return - The fileName to use by default (Empty file if this is not a file name, or client wants nothing by default)
	*/
	virtual IDFile GetNthElementFileName(int32 n) const = 0;
	
	/**
	Set the filename to use by default in the filename widget.

	NOTE: This is only used for filename elements

	@param n - The item you want information about
	@param selected - The filename that is in the widget
	*/
	virtual void SetNthElementFileName(int32 n, IDFile fileName) = 0;
	
	/**
	Get the default text to use when a text edit box is empty.

	NOTE: This is only used for filename elements right now

	@param n - The item you want information about
	@return - The text to use by default.
	*/
	virtual PMString GetNthElementDefaultText(int32 n) const = 0;

	/**
	Get the file type information for file elements.

	NOTE: This is only used for filename elements right now

	@param n - The item you want information about
	@param typeName - The name to display for this file type
	@param extension - The extension that type file box should expect
	*/
	virtual void GetNthFileTypeInfo(int32 n, PMString &typeName, PMString &extension) const = 0;

	/** 
	Used to determine whether the control should be indented

	@param n - Which item you care about
	@return - kTrue == Indent; kFalse == don't indent
	*/
	virtual bool16 ShouldIndentNthControl(int32 n) const = 0;
};	

#endif // __IXMLImportOptionsService__
