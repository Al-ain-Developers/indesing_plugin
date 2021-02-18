//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyWorkgroupHelper.h $
//  
//  Owner: Michele Goodwin
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
#ifndef __IInCopyWorkgroupHelper__
#define __IInCopyWorkgroupHelper__

#include "IPMUnknown.h"
#include "ISession.h"
#include "InCopyCoreID.h"
#include "IDocFileHandler.h"


/**	FOR INTERNAL USE.
	This interface is provided to give source code delivered via the sdk (i.e InCopyFileActions,InCopyDocUtils)
	access to private workgroup methods.
*/
class IInCopyWorkgroupHelper : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYWORKGROUPHELPER };

	/**	Downloads the specified file for open if it does not already exist locally.
		@param fileToOpen file to download.
		@return bool16 true if file was successfully downloaded.
	*/
	virtual bool16			WorkgroupSyncPreLoad( const IDFile& fileToOpen ) const = 0;

	/**	Downloads the specified file for place if it does not already exist locally.
		@param fileToOpen file to download.
		@return bool16 true if file was successfully downloaded.
	*/
	virtual bool16			WorkgroupSyncPrePlace( const IDFile& fileToOpen ) const = 0;

	/**	Downloads the specified story for open if it does not already exist locally.
		@param story to download.
		@return bool16 true if file was successfully downloaded.
	*/
	virtual bool16			WorkgroupSyncPreLoad( const UIDRef& story ) const = 0;

	/**	Downloads the specified story for place if it does not already exist locally.
		@param story to download.
		@return bool16 true if file was successfully downloaded.
	*/
	virtual bool16			WorkgroupSyncPrePlace( const UIDRef& story ) const = 0;

	/**	Test whether the specified story is managed by version cue and can be downloaded for open.
		@param story to test for a replica path.
		@return bool16 whether or not story is managed by version cue.
	*/
	virtual bool16			ShouldSyncPreLoad(UIDRef story) = 0;

	/**	Test whether the specified story is managed by version cue and can be downloaded for place.
		@param story to test for a replica path.
		@return bool16 whether or not story is managed by version cue.
	*/
	virtual bool16			ShouldSyncPrePlace(UIDRef story) = 0;

	/**	Version cue post save upload of the specified file.
		@param theFile the file to upload.
	*/
	virtual void			WorkgroupSyncPostSave (const IDFile& theFile) const = 0;

	/**	Test whether there is a new version of the specified document, used to
		to determine Update Design enablement.
		@param doc the document to test.
		@return bool16 true if there is a newer version.
	*/
	virtual bool16			HasNewerVersion(const UIDRef& doc) = 0;

	/**	Called from IInCopyDocUtils::DoSaveAs() to get original sys file for temp 
		version. Method will check for IsStandAloneDoc and IsTemporaryVersion.
		@param doc IN document for which to get the original sysfile.
		@param originalSysFile OUT the original sysfile.
		@return bool16 true if the specified doc was stand-alone, temp version and able to get the original version's sysfile.
	*/
	virtual bool16			GetOriginalSysFile(const UIDRef& doc, IDFile& originalSysFile) = 0;

	/**	Called from IInCopyDocUtils::ShouldDoSaveAs() to determine if the specified
		document is a temporary version such that Save should behave as SaveAs. Method
		will check for IsStandAloneDoc.
		@param doc the document to test.
		@return bool16 true if specified doc is temporary version.
	*/
	virtual bool16			IsTemporaryVersion(const UIDRef& doc) = 0;

	/**	Called from IInCopyDocUtils::DoSaveAs() to see if the current version is open
		such that it can be silently closed in order to save the temporary version to the
		same location. Method will check for IsStandAloneDoc and IsTemporaryVersion.
		@param doc the document to test for the temporary version.
		@param destFile the destination file path.
		@return UIDRef for the current version corresponding to this temp version if open.
	*/
	virtual UIDRef			GetCurrentVersionDoc(const UIDRef& doc, const IDFile& destFile) = 0;

	/**	Sets the workgroup ui data replica monitor so that is can be used in the
		AWS_CUI_CreateSaveDialog.
		@param doc the document to save as.
	*/
	virtual void			SetWorkgroupSaveAsData(const UIDRef& doc) = 0;

	/**	Test whether this document needs workgroup version close ui.
		@param doc the document to test.
		@return bool16 true if IsStandAloneDoc, is managed by version cue and is not a temporary version.
	*/
//	virtual bool16			UseVersionedCloseUI(const UIDRef& doc) = 0;

	/**	Display workgroup ui to save - this is the 4-button save alert - for the specified document.
		@param doc the document to save.
		@return IDocFileHandler::CloseOptions the user's selection in the save alert.
	*/
//	virtual IDocFileHandler::CloseOptions	DoSaveAlert(const UIDRef& doc) = 0;

	/** Test whether this document is versioned by version cue.
		@param doc the document to test.
		@return bool16 true if is standalone and is versioned.
	*/
	virtual bool16			IsVersioned(const UIDRef& doc) const = 0;

	/** Test whether this file location is in a version cue project.
		@param theFile the file location to test.
		@return bool16 true if file location versioned.
	*/
	virtual bool16			IsVersionedLocation(const IDFile& theFile) const = 0;

	/**	Called from IInCopyDocUtils::DoSaveAs() to test whether the specified document
		should be saved as alternate - the user checked the Save As Alternate check box	in the
		Save As dialog. Method will verify specified document is standaloneand is versioned.
		@param doc IN document to test.
		@param originalPath OUT the path of the original replica (that this doc will become an alternate of).
		@return bool16 true if Save As Alternate was checked.
	*/
	virtual bool16			ShouldSaveAsAlternate(const UIDRef& doc, IDFile& originalPath) const = 0;

	/**	Called from IInCopyDocUtils::DoSaveAs() to make the new version an alternate of the
		specified original version.
		@param versionSysFile the new version file path.
		@param originalReplicaSysFile the original version file path.
		@return int32 kSuccess or workgroup error code.
	*/
	virtual int32			MakeAlternate(const IDFile* versionSysFile, const IDFile *originalReplicaSysFile) const = 0;

};

#endif // __IInCopyWorkgroupHelper__
