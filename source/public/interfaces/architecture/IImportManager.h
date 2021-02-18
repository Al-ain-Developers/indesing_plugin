//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IImportManager.h $
//  
//  Owner: Zak Williamson
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
#ifndef __IImportManager__
#define __IImportManager__

#include "IPMUnknown.h"
#include "OpenPlaceID.h"
#include "URIList.h"

class IDataBase;
class IDataLink;

/**
 Interface used to select and import files.
 @see IImportProvider
 @see IPrintContentPrefs
 */
class IImportManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IIMPORTMANAGER };

	/**
	 Displays the place file dialog to the user.
	 @param importMe	OUT Files selected to import by the user from the place dialog.
	 @param multipleItemsOK	IN whether user should be able to select multiple items to import.
	 @param dialog IN the dialog to use for the import.
	 @return kFalse if the user cancelled out of the dialog or there was an error, else kTrue.
	 */
	virtual bool16 DoImportDialog(URIList *importMe, bool16 multipleItemsOK, IPMUnknown *dialog) = 0;

	// TODO: LINKREWORK: At what point do I create the link object/asset/link?
	/**
	 Creates a UIDRef from the file referenced by the given URI. 
	 @param intoDBb			IN Database to import into.
	 @param linkAssetUID	IN the link asset to import from.
	 @param flags			IN UI flags denoting how to handle UI events. (see BaseType.h)
	 @param pImportedItem	OUT UIDRef of the newly created imported item.
								This may be a page item or a text story UID.
	 @param uidPreview		IN UID of the pre-existing preview image.
	 */
	virtual void ImportUIDFromLinkAssetUID(IDataBase * intoDB, UID linkAssetUID, UIFlags flags, UIDRef *pImportedItem, UID uidPreview = kInvalidUID) = 0;
};

#endif
