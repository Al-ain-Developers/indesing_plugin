//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IAssignmentPackageUIFacade.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __IASSIGNMENTPACKAGEUIFACADE__
#define __IASSIGNMENTPACKAGEUIFACADE__

#include "AssignmentUIID.h"
#include "Utils.h"

class IAssignedDocument;

/**
	IAssignmentPackageUIFacade is an utility functions to help to enable and process the package menu items on assignment panel
*/

class IAssignmentPackageUIFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IASSIGNMENTPACKAGEUIFACADE };

	/** Can package selected assignment
		@return kTrue if the panel items can be packaged
	*/
	virtual bool16 CanPackage() const = 0;

	/**	Package all selected items
		@param email a boolean to indicate whether package and email
		@return An error code indicating whether the package operation succeeded or not.
	*/
	virtual ErrorCode Package(bool16 email = kFalse) = 0;

	/** Whether or not update package is enabled.  This is true when there is a single packaged assignment selected that is out of date
		or has been updated since packaged.
		@return kTrue if the can update
	*/
	virtual bool16 EnableUpdatePackage() const = 0;

	/**	Updates the package; convenience method that performs a cancel package then a package.
		@return An error code indicating whether the update package operation succeeded or not.
	*/
	virtual ErrorCode UpdatePackage(bool16 email = kFalse) = 0;

	/** Can forward packaged assignment to InCopy user
		@return kTrue if the panel items can be packaged
	*/
	virtual bool16 CanForwardPackage() const = 0;

	/**	Forward package assignment to InCopy user
		@param email a boolean to indicate whether package and email
		@return An error code indicating whether the package operation succeeded or not.
	*/
	virtual ErrorCode ForwardPackage(bool16 email = kFalse) = 0;

	/** Can return packaged assignment to InDesign user
		@return kTrue if the panel items can be packaged
	*/
	virtual bool16 CanReturnPackage() const = 0;

	/**	Return package assignment to InDesign user
		@param email a boolean to indicate whether package and email
		@return An error code indicating whether the package operation succeeded or not.
	*/
	virtual ErrorCode ReturnPackage(bool16 email = kFalse) = 0;

	/** Can open package
		@return kTrue if the can open
	*/
	virtual bool16 CanOpenPackage() const = 0;

	/**	Opens package: prompts user for assignment package file to open and opens the selected file.
		@param openedDocRef OUT the open document, if one opened
		@return An error code indicating whether the package open operation succeeded or not, could be kCancel if user cancelled.
	*/
	virtual ErrorCode OpenPackage(UIDRef& openDocRef) = 0;

	/** Can cancel package
		@return kTrue if the can cancel
	*/
	virtual bool16 CanCancelPackage() const = 0;

	/**	Cancels package
		@return An error code indicating whether the package cancel operation succeeded or not.
	*/
	virtual ErrorCode CancelPackage() = 0;
};

#endif // __IASSIGNMENTPACKAGEUIFACADE__