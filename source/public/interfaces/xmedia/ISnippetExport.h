//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/ISnippetExport.h $
//  
//  Owner: robin briggs
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

#ifndef __ISnippetExport__
#define __ISnippetExport__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

#include "SnippetID.h"
#include "IPMUnknown.h"
#include "IDOMElement.h"
#include "INXOptions.h"

class XMLReference;
class IScript;
class IXMLOutStream;
class IDocument;
class IAppPrefsExportDelegate;

/**	This is the API for using the Snippets plug-in to generate (export) XML in
	INX format. You can use this to write objects out to INX, and you can use 
	ISnippetImport to read them in from INX. These functions will write out the
	specified objects, as well as whatever dependent objects they rely on. So,
	for instance, if it writes out a page item, it will also write out any swatches
	used in the page item.
	
	Access this interface via the Utils<> helper.
	@see ISnippetImport
	@see Utils
*/
class ISnippetExport : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISNIPPETEXPORT };

	/**	Export XML elements to snippet
		@param stream - XML will be written to this output stream
		@param elementRefList - which elements in the structure view to export (clients required to removed child elements if the list also contains the parent element)
		@return ErrorCode kSuccess if it worked
	*/
	virtual ErrorCode ExportXMLElements(IPMStream *stream, const K2Vector<XMLReference>& elementRefList) = 0;

	/**	Export a list of either page items to snippet
		@param stream - XML will be written to this output stream
		@param pgItem - list of page items, all items in list must provide IDOMElement interfaces
		@return ErrorCode kSuccess if it worked
	*/
	virtual ErrorCode ExportPageitems(IPMStream *s, const UIDList& uidList) = 0;
	
	/**	Export a single page item or story to a stream as we can export only one incx in one go.
		Does not support exporting the XML backing store, if the backing store is the only item
		in the uidList, returns kFailure
		@param stream - XML will be written to this output stream
		@param uidList - Only supports single item in list, item in list must provide IDOMElement and IXMLFragment interfaces
		@return ErrorCode kSuccess if it worked
	*/
	virtual ErrorCode ExportInCopyInterchange(IPMStream *s, const UIDList& uidList) = 0;

	/**	Export the application preferences to a stream.  You can specify which elements you want exported by passing the appropriate ScriptIDs in the
		preferenceIDs parameter.

		Script IDs can be found in ScriptingDefs.h.  In ScriptingDefs.h, most list style elements will have a singular identifier and a plural identifier, such as c_DocumentStyle 
		and c_DocumentStyles.  In all cases, you should pass in the singular version, i.e. c_DocumentStyle.
		
		Many preferences can have dependencies on other preferences.  i.e. Character and Paragraph styles have references to colors in them.  
		If you are exporting Character and Paragraph styles, you should also export colors, swatches, gradients, etc. or use extreme caution.

		@param stream - XML will be written to this output stream
		@param operation - indicates whether the ScriptIDs in 'preferenceIDs' should be the only ScriptIDs included in the export, by specifying PreferenceOperation::kInclude,
			or whether the ScriptIDs in 'preferenceIDs' should be excluded, by specifying PreferenceOperation::kExclude, from the standard list of preferences that get exported
			i.e. if we wanted to export only the list of document presets and the 
			Margin preferences, we would add c_MarginPref and c_DocumentStyle to our preferenceIDs and set operation to kInclude.  
			If we wanted to write out all the prefs except Object Styles, we would add c_ObjectStyle to our preferenceIDs and set operation to kExclude.	
		@param preferenceIDs - 
		@return ErrorCode kSuccess if it worked
	*/
	typedef enum { kInclude, kExclude } PreferenceOperation;
	virtual ErrorCode	ExportAppPrefs( IPMStream *stream, PreferenceOperation operation = kExclude, const K2Vector<ScriptID>& preferenceIDs = K2Vector<ScriptID>(), IAppPrefsExportDelegate* delegate = nil ) = 0;

	/**	Return the list of selected page items
	@param pageItems - [OUT] - UIDs of selected page items will be returned in this.
	@return bool16 kTrue if the list of selected page items could be obtained.
	*/
	virtual bool16 GetSelectedPageItemsToExport(UIDList& pageItems) = 0;

	/**	Export the currently selected page items to snippet
	@param s - XML will be written to this output stream
	@return ErrorCode kSuccess if it worked
	*/
	virtual ErrorCode ExportSelectedPageItems(IPMStream *s) = 0;
};

#endif // __ISnippetExport__


