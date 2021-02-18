//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IAppPrefsExportDelegate.h $
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
//========================================================================================

#pragma once
#ifndef __IAppPrefsExportDelegate__
#define __IAppPrefsExportDelegate__

#include "WorkspaceID.h"
#include "IDOMElement.h"

/** This is an interface for customizing the Export of Application Preferences
	exported via ISnippetExport::ExportAppPrefs()
	The methods in this interfaces are callbacks from the export process that allows
	the client to have a say in the export
*/
class IAppPrefsExportDelegate : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPPREFSEXPORTDELEGATE };

	/** 
		The export process goes thru all objects that are children of the application DOM element
		and will ask whether each should be exported.  to get default behavior, just return defaultShouldExportValue
		An expected use of this delegate is to include elements provided by 3rd parties in the export.  Typically,
		only objects that are considered preferences or list items that have been specifically included would be
		exported.  If you have an element that is a child of the application DOM but is not a preference, you'd
		want to use the delegate to return kTrue to get this element exported
		@param domElement the DOM element you are being asked to include or exclude in the export
		@param defaultShouldExportValue the default value that would occur if there was no delegate.  
		@return kTrue to include the element in the export, kFalse to exclude the element.  To get default behavior,
		return defaultShouldExportValue
	*/
	virtual bool16					ShouldExportElement(IDOMElement* domElement, bool16 defaultShouldExportValue ) const = 0;

	/** 
		The export process initially gathers children in no particular order.  The import process requires some order
		to function correctly.  Any item that is referenced by another item should come before the referencing item
		in the export list.  For all known types, this sorting is done for you before this method is called.  This method is typically
		used to move a 3rd party element higher up in the export list so it comes before something that depends on it.
		@param oldList this is the list of elements in the order they will be exported
		@param newList if changes are made to the export order, newList should contain a complete list of the exporting objects in their new export order.
		newList will be empty when this method is called and if it is empty on return, oldList will be used.  i.e. to do nothing, just return.
	*/
	virtual void					ModifyExportOrder( const IDOMElement::ElementList &oldList, IDOMElement::ElementList &newList ) const = 0;

	/** 
		When an export occurs, we keep track of the list element types(swatches, pdf presets, etc.) that have been exported.  On import
		we use this list to determine which list element types to delete.  Say we export 3 XML tags, A, B and C.  Later, we have tags D, E and F and
		we import the prefs that contain A, B and C.  After importing, if we have the DeleteNonImportedListItems preference turned on, we will know
		that D, E and F were not part of the import and will will remove them from the list.  If during the export, we chose not to export tags, then
		on import no tags would have been imported.  If we didn't keep a list of which types were exported, we wouldn't know whether to delete non-imported
		tags or not.  The exportedIDs list allows us to keep track of the types of items that were exported.  If you are exporting a 3rd party list item,
		you'll need to add it here to the list of exported items such that that information is available on import.
		
		@param exportedIDs contains the list of exported types as ScriptIDs, which can be added to to acknowledge other exported list types
	*/
	virtual void					ModifyExportedListElements( K2Vector<ScriptID>& exportedIDs );
};

#endif //__IAppPrefsExportDelegate__
