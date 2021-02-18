//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IAssignmentOptionsDialogData.h $
//  
//  Owner: Cindy Chen
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
//  The data interface for the Assignment Options dialog.	
//  
//========================================================================================

#pragma once
#ifndef __IAssignmentOptionsDialogData__
#define __IAssignmentOptionsDialogData__

#include "IPMUnknown.h"
#include "AssignmentUIID.h"
#include "IAssignment.h"

/** Data interface for the Assignment Options dialog */
class IAssignmentOptionsDialogData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENTOPTIONSDIALOGDATA };

	/**
		Copy data from another object to this one.
		@param data - The data object to copy from.
	*/
	virtual void CopyData(IAssignmentOptionsDialogData * data) = 0;

	/**
		Set the assignment this dialog will be referring to.
		@return - An IAssignment pointer for the assignment.
	*/
	virtual IAssignment* GetAssignment() = 0;

	/**
		Get the assignment this dialog is referring to.
		@param data - An IAssignment pointer.  This object should not be modified 
		until the dialog is dismissed.
	*/
	virtual void SetAssignment(IAssignment* asssignment) = 0;

	/**
		Get the document UIDRef
		@return - The UIDRef of the document.
	*/
	virtual UIDRef GetDocRef() = 0;

	/**
		Set the document.
		@param docRef - A UIDRef of the document.
	*/
	virtual void SetDocRef(UIDRef docRef) = 0;

	/**
		Get the assignment name.
		@return - A PMString reference containing the assignment name.
	*/
	virtual const PMString& GetName() = 0;

	/**
		Set the assignment name.
		@param name - A PMString holding the assignment name.
	*/
	virtual void SetName(const PMString& name)  = 0;

	/**
		Get the original file path for the assignment.
		@return - A platform path for the assignment.
	*/
	virtual const PMString& GetOriginalFile()  = 0;

	/**
		Set the original file path for the assignment.
		@param folder - A platform path for the assignment.
	*/
	virtual void SetOriginalFile(const PMString& file)  = 0;

	/**
		Get the new file path for the assignment.
		@return - A platform path for the assignment.
	*/
	virtual const PMString& GetNewFile()  = 0;

	/**
		Set the new file path for the assignment.
		@param folder - A platform path for the assignment.
	*/
	virtual void SetNewFile(const PMString& file)  = 0;

	/**
		Get the user name of the assignment.
		@return - A reference to a PMString containing the user's name.
	*/
	virtual const PMString& GetUser()  = 0;

	/**
		Set the user name for the assignment.
		@param user - A PMString containing the user name.
	*/
	virtual void SetUser(const PMString& user)  = 0;

	/**
		Get the color UID for the assignment.
		@return - A UID for the color from IInCopyUIColors.
	*/
	virtual UID GetColor()  = 0;

	/**
		Set the color UID for the assignment.
		@param color - A UID for the color from IInCopyUIColors.
	*/
	virtual void SetColor(UID color)  = 0;

	/**
		Get the assignment export preview level options.
		@return - The enumeration for the preview level.
	*/
	virtual IAssignment::AssignmentExportOptions GetExportOption()  = 0;

	/**
		Set the assignment export preview level option.
		@param options - The enumeration for the new export level.
	*/
	virtual void SetExportOption(IAssignment::AssignmentExportOptions options) = 0;

	/**
		The assignment export compatibility for this assignment.
		@return - The compatibility enumeration.
	*/
	virtual IAssignment::AssignmentCompatibility		GetExportCompatibility() const = 0;

	/**
		Set the assignment export compatibility level.
		@param options - The enumeration desired.
	*/
	virtual void						SetExportCompatibility(IAssignment::AssignmentCompatibility compatibility) = 0;

	/**
		The assignment option for including linked files or not when packaging.
		@return bool16 kTrue if should include, otherwise kFalse.
	*/
	virtual bool16	GetIncludeLinkedFilesWhenPackage() const = 0;

	/**
		Set the assignment option for including linked files or not when packaging.
		@param includeFlag pass kTrue to include linked files, otherwise kFalse.
	*/
	virtual void SetIncludeLinkedFilesWhenPackage(bool16 includeFlag) = 0;

	/**
		Indicates whether this is a new assignment dialog (based on whether SetAssignment was called).
		@return - A boolean indicating whether this is a new assignment dialog.
	*/
	virtual bool16 IsNewAssignment() = 0;

	/**
		Indicates whether the new assignment location needs validation by the dialog controller.  The new assignment location may have been validated by the relink observer such that the controller validation is redundant so returns false in that case.
		@return - A boolean indicating whether this new assignment location needs validation by the dialog controller; returns kFalse if this is not a new assignment dialog.
	*/
	virtual bool16 GetNewAssignmentLocationNeedsValidation() = 0;

	/**
		Sets whether the new assignment location needs validation by the dialog controller, this is the case if user sets location by changing the name thus bypassing the relink observer.  Only sets if this is a new assignment dialog.
		@param validated - A boolean indicating that this new assignment location needs validation.
		@return - A boolean indicating whether the flag was set.
	*/
	virtual bool16 SetNewAssignmentLocationNeedsValidation(bool16 validated) = 0;

	/**
		Indicates whether this is an orphaned assignment file.
		@return - A boolean indicating whether this is an orphaned assignment file.
	*/
	virtual bool16 IsOrphaned() = 0;

	/**
		Set whether this is an orphaned assignment file or not.
		@param Orphaned - A boolean indicating whether this is an orphaned assignment file.
	*/
	virtual void SetOrphaned(bool16 Orphaned)  = 0;

};

#endif // __IAssignmentOptionsDialogData__
