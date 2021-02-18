//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ICreateFormFieldCmdData.h $
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
//========================================================================================

#pragma once
#ifndef __ICreateFormFieldCmdData_h__
#define __ICreateFormFieldCmdData_h__

#include "IPMUnknown.h"
#include "PMString.h"
#include "FormFieldID.h"

/** Command parameters for the CreateFormField command
*/
class ICreateFormFieldCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICREATEFORMFIELDCMDDATA };
	
	/** Set the form field type to create
		@param inFormType Boss of form field to create e.g. kPushButtonItemBoss
	*/
	virtual void SetFormPageItemType(ClassID inFormType) = 0;

	/** Set dimensions of form field */
	virtual void SetFormRect(const PMRect& inRect) = 0;

	/** A list of page items to be moved inside of the newly created form.
	    Used to "Create Button" from non-form field page items */
	virtual void SetIconList( const UIDList& inIconList) = 0;

	/** Set page item desination for new form field
		@param inParent The form field will be created as a child of this page item.
	*/
	virtual void SetParent( const UIDRef& inParent) = 0;
	
	/** Get the form field type to create
		@return inFormType Boss of form field to create e.g. kPushButtonItemBoss
	*/
	virtual ClassID GetFormPageItemType() const = 0;

	/** Get the dimensions form field type to create
		@return inFormType Boss of form field to create e.g. kPushButtonItemBoss
	*/
	virtual PMRect GetFormRect() const = 0;

	/** @return A list of page items to be moved inside of the newly created form.
	 */
	virtual void GetIconList( UIDList* outIconList) = 0;

	/** Get page item destination for new form field
		@return UIDRef of the form fields parent
	*/
	virtual UIDRef GetParent() const = 0;
	/** Get destination database for new form field
		@return the form fields database
	*/
	virtual IDataBase* GetDataBase () const = 0;

	/** @return kTrue if the form field has icons (i.e. page items to be placed in the new form field)
	*/
	virtual bool16 GetUseIcons() const = 0;
};

//=============================================================================

#endif // __ICreateFormFieldCmdData_h__

//  ICreateFormFieldCmdData.h.
