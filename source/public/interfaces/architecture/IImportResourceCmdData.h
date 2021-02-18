//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportResourceCmdData.h $
//  
//  Owner: Steve Flenniken
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
#ifndef __IImportResourceCmdData__
#define __IImportResourceCmdData__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"

class URI;

/** Interface used to store data for commands that import resources. This is a container class, it can store either a link resource
	(by UID), or a URI identifying some resource. If the link resource is specified, the URI specified with the link resource is the one returned 
	(in the case where there might be a conflict between the URI retained in the interface, and that in ILinkResource).

		@see ImportResourceCmd, ImportAndLoadPlaceGunCmd, ImportAndPlaceCmd, ImportPIFromResourceCmd, InCopyOpenDocCmd
*/
class IImportResourceCmdData : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IIMPORTRESOURCECMDDATA };

	/** Initialize this object from another object of the same type */
	virtual void Set(const IImportResourceCmdData *data) = 0;

	/** Initialize this object manually from a URI

		@param db IN database to be imported into (required)
		@param uri IN identifying the resource to import.
		@param flags IN specifies how much UI to show during import
		@param retainFormat IN retain text format, applies to text import
		@param convertQuotes IN convert quotation mark types, applies to text import
		@param applyCJKGrid IN apply CJK grid if present, applies to text import
		@param uidPreview IN UID of preview object
	*/
	virtual void Set(IDataBase *db, const URI &uri, UIFlags flags, bool16 retainFormat = kFalse, bool16 convertQuotes = kFalse, bool16 applyCJKGrid = kFalse, UID uidPreview = kInvalidUID) = 0;

	/** Initialize this object manually from a link resource

		@param db IN database to be imported into (required)
		@param linkResourceUID IN the link resource to import from  (required)
		@param flags IN specifies how much UI to show during import
		@param oldPageItem IN UID of old page item or kInvalidUID when there is none.  This page item contains
			the preference settings used the last time this item was imported and these preferences are used during this import.
		@param retainFormat IN retain text format, applies to text import
		@param convertQuotes IN convert quotation mark types, applies to text import
		@param applyCJKGrid IN apply CJK grid if present, applies to text import
		@param uidPreview IN UID of preview object
	*/
	virtual void Set(IDataBase *db, UID linkResourceUID, UIFlags flags, UID oldPageItem=kInvalidUID, bool16 retainFormat = kFalse, bool16 convertQuotes = kFalse, bool16 applyCJKGrid = kFalse) = 0;

	/** Update the UIFlags */
	virtual void SetFlags( UIFlags flags ) = 0;

	/** Get the database */
	virtual IDataBase *GetDataBase() const = 0;
	/** Get the URI */
	virtual const URI GetURI() const = 0;
	/** Get the UIFlags */
	virtual UIFlags GetFlags() const = 0;
	/** Get the retain text format flag */
	virtual bool16 GetRetainFormat() const = 0;
	/** Get the convert quotes flag */
	virtual bool16 GetConvertQuotes() const = 0;
	/** Get the apply CJK grid flag */
	virtual bool16 GetApplyCJKGrid() const = 0;
	/** Get the old pageitem */
	virtual UID GetOldPageItem() const = 0;
	/** Get the preview object */
	virtual UID GetPreview() const = 0;
	/** Get the link resource uid */
	virtual UID GetLinkResourceUID() const = 0;
};

#endif
