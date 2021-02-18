//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGenStlEdtListMgr.h $
//  
//  Owner: Matt Phillips
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
#ifndef __IGenStlEdtListMgr__
#define __IGenStlEdtListMgr__

#include "K2Vector.h"
#include "UIDList.h"
#include "DBUtils.h"

class IGenStlEdtListMgr : public IPMUnknown

{	
public:

	/** Returns the number of styles in the list.
		@return The number of styles.
	*/
	virtual int32 		GetNumStyles() = 0;

	/** Obtains the name of the Nth style.
		@param index IN The index of the style you're interested in.
		@param pName OUT Receives the name of the style.
		@return An error code or kSuccess if successful.
	*/
	virtual ErrorCode   GetNthStyleName(int32 index, PMString *pName) = 0;

	/** Obtains the description of the Nth style.
		@param index IN The index of the style you're interested in.
		@param pDesc OUT Receives the description of the style.
		@return An error code or kSuccess if successful.
	*/
	virtual ErrorCode   GetNthStyleDescription(int32 index, PMString *pDesc) = 0;

	/** Returns whether a particular style is editable.
		@param index IN The index of the style you're interested in.
		@return True if it's editable; False if locked or uneditable.
	*/
	virtual bool32 	    IsNthStyleEditable(int32 index) = 0;

	/** Returns whether a particular style can be deleted.
		@param index IN The index of the style you're interested in.
		@return True if it can be deleted; False if not.
	*/
	virtual bool32 	    IsNthStyleDeleteable(int32 index) = 0;

	/** Searches the list for a style with the specified name.
		@param name IN The name of the style to look for.
		@return The index of the style, or -1 if it wasn't found.
	*/
	virtual int32 		GetStyleIndexByName(const PMString& pName) = 0;

	/** String IDs for GetUIString. */
	typedef enum
	{
		kDialogTitle,				// Title of the Edit Style dialog, def = "Define Styles"
		kStyleListTitle,			// String appearing above list; def = "Styles:"
		kNewStyleNameTitle,			// Title of new-style name dlg; def = "New Style"
		kRenameStyleTitle,			// Title of rename-style name dlg; def = "Rename Style"
		kNameConflictPrompt,		// Prompt when a name conflicts
		kNameRequiredPrompt,		// Prompt when user enters blank name
		kImportTitle,				// Title of import dialog
		kExportTitle,				// Title of export dialog
		kExportFileClassName,		// Name of export document type, e.g., "Style File"
		kExportDefaultFileName,		// Name of export document, e.g., "Exported Printer Styles"
		kAlertCannotLoadStyles,		// Error to display when file isn't of right type.
		kNameReservedPrompt,		// Prompt when a user enters a reserved name (i.e., "[Custom]")
		kLastGenStlEdtUIStringID
	} GenStlEdtUIStringID;
	
	/** Allows you to override the default strings used in the edit 
		styles interface.  If you want to override the string, set up 'pname' with
		the string and return TRUE.  If you want to use the default, return FALSE.

		@param whichString IN Identifies the string (by ID) that will be shown in the UI.
		@param pName OUT Receives the literal string to show in the UI.
		@return kTrue to override the string; kFalse otherwise.
	*/
	virtual bool32 	GetUIString(GenStlEdtUIStringID whichString, PMString *pName) = 0;
	
	/**	Return the class ID of the boss that you want as the root UID in a new
		export styles document.  Your plug-in provides the class definition and ID.
		Your list mgr interface must live on the boss.

		@return The boss's class ID.
	*/
	virtual ClassID	GetExportFileRootBossClassID() = 0;
			
	/**	Determines the creator and type of the export/import file.
		
		@param pCreator OUT Receives the creator for the export/import file.
		@param pType OUT Receives the type of the export/import file.
	*/
	virtual void GetExportFileCreatorAndType(OSType *pCreator, OSType *pType) = 0;
	
	/**	Get the magic byte of the export/import file.  This is a special unique series of
		characters that you come up with that ensures that the database won't be 
		accidentally imported as a "real" document.

		@param magicBytes OUT Receives the magic bytes to use for the import/export file.
	*/
	virtual void GetImportExportFileMagicByte(DBUtils::MagicBytes magicBytes) = 0;

	/** Determines the extension of the export/import file.

		@param pExt OUT Receives the extension to use for the import/export file.
	*/
	virtual void GetExportFileExtension(PMString *pExt) = 0;
	
	/**	If you have a custom import (i.e., you don't want to use the default implementation 
		provided by GenericStyleEditor) then do your import in here and return kTrue.  Otherwise, 
		return kFalse and the standard implemenation (which calls ImportStyles/ExportStyles
		below) will be used.

		@param theFile IN If null, you should bring up UI to pick the file.  Otherwise,
						should be used as the source or destination import file.
		@return kFalse if you don't implement a custom import; kTrue if you did.
	*/
	virtual bool32 CustomImport(const IDFile* theFile) = 0;

	/**	If you have a custom export (i.e., you don't want to use the default implementation 
		provided by GenericStyleEditor) then do your export in here and return kTrue.  Otherwise, 
		return kFalse and the standard implemenation (which calls ImportStyles/ExportStyles
		below) will be used.

		@param theFile IN If null, you should bring up UI to pick the file.  Otherwise,
						should be used as the source or destination export file.
		@param indexList IN A list of the style indices that should be copied (corresponds to
				the user's selection when they clicked Export).
		@return kFalse if you don't implement a custom export; kTrue if you did.
	*/
	virtual bool32 CustomExport(const IDFile* theFile, K2Vector<int32>& indexList) = 0;

	/**	Imports styles from an open database.
	
		@param uidrefFrom IN Points to the UID in another database from which we can obtain a
					corresponding list manager interface and therefore query for the list of
					styles in that database.  Typically this is the root UID in a style 
					import/export file, but technically any database that can be used to pull 
					styles will do.  The key is that we can query for IGenStlEdtListMgr on the
					boss.
		@return An error code; kSuccess if import was successful.
	*/
	virtual ErrorCode ImportStyles(UIDRef uidrefFrom) = 0;
	
	/**	Exports styles to an open export file.  The selected styles are copied from the defaults
		to the indicated database.

		@param uidrefTo IN The root of a new export document into which the styles will be copied.
		@param indexList IN A list of the style indices that should be copied (corresponds to
				the user's selection when they clicked Export).
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode ExportStyles(UIDRef uidrefTo, K2Vector<int32>& indexList) = 0;

	/** Changes the name of the specified style.  Will fail if the name already
		exists in the style list.  N.B.: Because the list is always maintained
		in alphabetical order, this function will generally cause reordering.

		@param index IN The index of the style that you want to change the name of.
		@param name IN The name of the new style.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode SetNthStyleName(int32 index, PMString& name) = 0;
	
	/**	Generate a unique style name. If the base string is empty, the the new
		will look something like: style 1, style 2. If the base string contains
		an exisiting style name, then the new name will look something like:
		<original name> copy 1, <original name> copy 2.

		@param baseName IN The base name for which you want a unique name.
		@return A unique name (ie, a version of baseName that is not currently in the list).
	*/
	virtual PMString GetUniqueStyleName(PMString& baseName) = 0;
	
	/** Adds a new style with specified initial name.  If the name is already in
		the list, the function fails.

		@param name IN The name of the new style.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode AddStyle(PMString& name) = 0;
	
	/**	Makes a copy of the specified style.  Fails if newName already exists
		in the style list.

		@param srcIndex IN The index of the style to copy.
		@param newName IN The name of the new style.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode CopyNthStyle(int32 srcIndex, PMString& newName) = 0;
	
	/** Deletes a style.

		@param index IN The index of the style to delete.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode DeleteNthStyle(int32 index) = 0;
	
	/**	Invokes UI to edit the styles.  Returns true if the user clicked OK
		(whether or not they actually made changes).

		@param index IN The index of the style to edit.
		@param bNew IN True if the style is a new style (ie, this corresponds to the New button).
		@return True for an OK, false for cancel.
	*/
	virtual bool32 EditNthStyle(int32 index, bool16 bNew) = 0;

	/** Internal use only.  Helper function that inserts a list element when lists are UIDList based.
		This is a direct window into the UIDList and should not be used except by a style list manager
		itself.
		
		@param uid IN The UID to insert.
		@param index IN The index before which to insert the UID, or -1 to append.
	*/
	virtual void ListInsert(UID uid, int32 index = -1) = 0;

	/** Internal use only.  Helper function that removes a list element when lists are UIDList based.
		This is a direct window into the UIDList and should not be used except by a style list manager
		itself.
		
		@param index IN The index of the UID to remove.
	*/
	virtual void ListRemove(int32 index) = 0;

	/** Internal use only.  Helper function that replaces a list element when lists are UIDList based.
		This is a direct window into the UIDList and should not be used except by a style list manager
		itself.
		
		@param uid IN The UID to replace the existing one with.
		@param index IN The index of the element to replace.
	*/
	virtual void ListReplace(UID uid, int32 index) = 0;

	/** Helper function that copies style data from one style to another.
		
		@param srcStyle IN The style from which to copy the data.
		@param dstStyle IN The style to which to copy the data.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode CopyStyleData(UIDRef srcStyle, UIDRef dstStyle) = 0;

	/** Internal use only.  Obtains the UID of the Nth style object.  From this you can get/set the 
		client items.  Note that this only is used by style lists that use UIDList-based storage.

		@param index IN The style to obtain the UIDRef for.
		@return The UIDRef of the style.
	*/
	virtual UIDRef GetNthStyleRef(int32 index) = 0;

	/** Selects the specified style and invokes it; used for print/pdf styles where the user can
		bypass or access the export/print dialog directly from a menu.  
		
		@param index IN The index of the style to invoke.
		@param displayUI IN If true, the print/export dialog is presented first (so the user can 
							change as needed).  Otherwise, it goes right to printing/exporting.
		@return Error code, or kSuccess if successful.
	*/
	virtual ErrorCode InvokeNthStyle(int32 index, bool32 displayUI = kTrue) = 0;

	/** Indicates whether this style list type refers to flattener styles as "child" entities
		(for example, printer styles and pdf export styles).  If true, the flattener styles 
		will be included as part of the export/import process.

		@return True if the style refers to flattener styles; false if it doesn't.
	*/
	virtual bool16 ReferencesFlattenerStyle() = 0;

	/** For flattener-style-referring lists, obtains the flattener style to which a particular
		style refers.

		@param index IN The index of the style.
		@return The UIDRef of the flattener style to which this style refers.
	*/
	virtual UIDRef GetReferencedFlattenerStyle( int32 nIndex ) = 0;

	/** For flattener-style-referring lists, obtains the flattener style to which a particular
		style refers.

		@param index IN The index of the style.
		@return The name of the flattener style to which this style refers.
	*/
	virtual PMString GetFlattenerStyleName( int32 nIndex ) = 0;

	/** For flattener-style-referring lists, associates a flattener style with a list element.

		@param index IN The index of the element.
		@param strName IN The name of the flattener style with which to associate the element.
	*/
	virtual void SetFlattenerStyleName( int32 nIndex, const PMString& strName ) = 0;

	/**	Tells whether items of this list are enabled in no-pub state.  kFalse by default.

		@return True if you should be able to edit the list in a no-pub state; false otherwise.
	*/
	virtual bool16 EnabledInNoPubState()  = 0;

};

#endif // __IGenStlEdtListMgr__

