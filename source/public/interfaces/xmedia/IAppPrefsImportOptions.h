//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IAppPrefsImportOptions.h $
//  
//  Owner: Matt Joss
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
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once

#ifndef __IAppPrefsImportOptions__
#define __IAppPrefsImportOptions__

#include "ISnippetExport.h"
#include "SnippetID.h"

//========================================================================================
// IAppPrefsImportOptions Class
//========================================================================================
/**	Importing Application Prefs that were exported via Utils<ISnippetExport>->ExportAppPrefs() is done via ISnippetImport::ImportFromStream()
	Importing this way does not allow options for importing, so instead, the options for importing AppPrefs are stored in this interface on the Workspace

	This interface allows you to set import options that will be used during ISnippetImport::ImportFromStream()
	
	@see ISnippetImport
	@see ISnippetExport
*/
class IAppPrefsImportOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPPREFSIMPORTOPTIONS };
	

	typedef enum { kReplaceListItems, kUseExistingListItems } ListImportMatchAction;

	/** 
		When named list items in the app prefs, like Swatches, Text Styles, etc. are imported, there is the potential
		to run into name conflicts.  If we are importing an item named "Headline" and we already have a list item named
		"Headline", there are 2 choices.  We can either use the already existing version of "Headline" in the list or we can
		replace the existing version with the version of "Headline" that is being imported.  
		This method processes a command to set the values, so it can be called from outside a transaction
		@param action specifies whether list elements with matching names should use the existing element or replace it
	*/
	virtual void					SetHandleListItemsWithMatchingNames( ListImportMatchAction action ) = 0;
	/** 
		Returns whether we should replace existing list elements or use the existing elements.  See SetHandleListItemsWithMatchingNames()
		@return kReplaceListItems to replace list items, kUseExistingListItems to use existing list items
	*/
	virtual ListImportMatchAction	HandleListItemsWithMatchingNames(  ) const = 0;

	/** 
		When app prefs are imported, the standard behavior is to replace an entire list with the new set of imported items.
		The standard behavior is to delete non-imported items.  That means if we have items A, B and C before import
		 and the imported items are A, B and D, we should end up with A, B and D.  C was non-imported, so it was deleted
		 If, however, DeleteNonImportedListItems was false, we'd end up with A, B, C and D.  A merge of both lists.
		
		@param deleteNonImported specifies whether pre-existing list elements that were not part of the import should be deleted
	*/
	virtual void					SetDeleteNonImportedListItems( bool16 deleteNonImported ) = 0;
	/** 
		Should non-imported list items be deleted.  See SetDeleteNonImportedListItems() for more info
		@return kTrue to delete on-imported list items, kFalse to keep them
	*/
	virtual bool16					DeleteNonImportedListItems( ) const = 0;


	/** 
		This method is called by the command to set the actual values.  This should not be called by clients, instead call SetHandleListItemsWithMatchingNames()
	*/
	virtual void					ModelSetHandleListItemsWithMatchingNames( ListImportMatchAction action ) = 0;
	/** 
		This method is called by the command to set the actual values.  This should not be called by clients, instead call SetDeleteNonImportedListItems()
	*/
	virtual void					ModelSetDeleteNonImportedListItems( bool16 deleteNonImported ) = 0;
	
};

#endif //__IAppPrefsImportOptions__
