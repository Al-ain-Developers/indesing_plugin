//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IINXManager.h $
//  
//  Owner: Steve Pellegrin
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
//  This file simply includes the sources file from the AXE Core Tech XML parser required
//  to be built on the client side for initilaiztion and termination.
//  
//========================================================================================

#pragma once
#ifndef __IINXManager_h__
#define __IINXManager_h__

// Adobe Patent or Adobe Patent Pending Invention Included Within this File
// Adobe patent application tracking B234, entitled Method and apparatus for formatting portion of content, inventors: Craig Rainwater, Steve Pellegrin,  Robin Briggs 

// ----- Interfaces -----

#include "IDOMElement.h"

// ----- Includes -----
#include "PMString.h"

// ----- ID.h files -----

#include "INXCoreID.h"

// ----- Forward -----

class IINXImportPolicy;
class IINXExportPolicy;
class IINXImportValidation;
class INXOptions;
class IPMStream;
class IINXErrorHandler;

/** Provides service for INX import and export. 
	
	This interface is the only access point for core INX functionality (both import and export).
*/
class IINXManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINXMANAGER };

	/**
		Callback function used for INXError Handling. See @SetINXErrorHandler and @GetINXErrorHandler below.
	*/
	typedef IINXErrorHandler * (*CreateINXErrorHandler) ();

public:
	// INX export related function.
	/**
		Writes the INX representation of a set of rooted object trees to a stream.
		Callback allows the client to guide the export operation.
		@param roots IN A list of root objects to be exported
		@param policy IN Pointer to an Export Policy object, or nil.
		@param stream IN The stream to write info
		@param encoding IN Output stream encoding type (UTF8, UTF16, etc.)
		@param uiFlags IN UI Flags. Determines whether dialog boxes are displayed, etc.
		@return kSuccess, kCancel if aborted by policy or user, or an error code kFailure 
		@see INXOptions.h
		@see IINXExportPolicy.h
	*/
	virtual ErrorCode ExportINX(const IDOMElement::ElementList &roots, IINXExportPolicy *policy, 
					IPMStream *stream, UIFlags uiFlags = kFullUI) = 0;

	/**
		Begin multiple INX export session. Using multiple export session can improve performance if you need to export
		multiple snippet based files (snippet, incopy story et al). Code assumes that document is not changed during inx 
		export operation. All export session should use the same INXOptions.
	*/
	virtual void BeginExportSession() = 0;

	/**
		End multiple INX export session. Must be paired with BeginExportSession
	*/
	virtual void EndExportSession() = 0;


	// INX import related function
	/**
		Construct a DOM tree from information found in an INX file.
		@param stream IN The input stream containing INX data.
		@param validation IN A pointer to an import validation object, or nil
		@return kSuccess or an error code.
 		@see IINXImportValidation.h
	*/
	virtual ErrorCode ValidateINX(IPMStream *stream, IINXImportValidation *validation = nil) = 0;

	/**
		Construct a DOM tree from information found in an INX file.
		@param parent IN An object that will serve as the parent of the imported DOM tree.
		@param policy IN A pointer to an import policy object, or nil.
		@param stream IN The input stream containing INX data.
		@param progressBarTitle IN A pointer to a PMString object to be used as the title of the progress bar, or nil.
		@param uiFlags IN How to handle UI events during the import operation.
		@param object IN A pointer to an interface pointer that will contain the root object of the imported DOM tree.
		@return kSuccess or an error code.
		@see IINXImportPolicy.h
	*/
	virtual ErrorCode ImportINX(IDOMElement * root, IINXImportPolicy *policy, IPMStream *stream,
					const PMString *progressBarTitle = nil, UIFlags uiFlags = kFullUI, IDOMElement **object = nil) = 0;

	/**
		Begin multiple INX import session. Using multiple import session can improve performance if you need to import
		multiple snippet files. Code assumes that document is not changed except inx operation. All inx file should have 
		the same scripting context and inx options. Otherwise, you won't get any performance improvement.
	*/
	virtual void BeginImportSession() = 0;

	/**
		End multiple INX import session. Must be paired with BeginImportSession.
	*/
	virtual void EndImportSession() = 0;


	// INX error handling related function
	/**
		Installs a callback handler function that will be called to create the INX Error Handler.
		The callback function will be called for every IDML export/import that happens in a different thread.
		Note that the ownership of releasing the INXErrorHandler object created by the 
		CreateINXErrorHandler lies with the INXManager and not with the client. 
		@param handlerOwner IN The callback handler to be installed. nil to remove existing callback handler.
 		@see IINXErrorHandler.h
	*/
	virtual void SetINXErrorHandler(CreateINXErrorHandler handlerOwner) = 0;

	/**
		Get installed INX error handler.
		@param fnPointer OUT Contains the CreateINXErrorHandler callback reference if one is installed, nil otherwise.
		@return pointer to installed inx error handler. nil if no error handler installed
	*/
	virtual IINXErrorHandler * GetINXErrorHandler(CreateINXErrorHandler * fnPointer = nil) const = 0;

	//NOTE: Adobe internal use only
	virtual void ImportHelperAddCacheEntry(const PMString& inKey, const PMString& inValue) = 0;
	virtual PMString ImportHelperGetCacheEntry(const PMString& inKey) = 0;
};

#endif // __IINXManager_h__
