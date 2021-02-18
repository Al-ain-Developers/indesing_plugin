//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IImportImageCmdData.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IImportImageCmdData__
#define __IImportImageCmdData__

#include "IPMUnknown.h"
#include "ImageID.h"

/** Command data interface for the kPlaceImageCmdBoss
*/
class IImportImageCmdData : public IPMUnknown
{
public:
	/** default interface IID for this interface */
	enum { kDefaultIID = IID_IIMPORTIMAGECMDDATA };

	/** The ImportImageCmd requires the client to pass in a valid IDataBase, UID, and stream.
		@param db - IN: The IDataBase that the image is being placed into.
		@param uid - IN: The UID should be created using NewPageItemCmd and is the UID of the actual 
			image boss.
		@param stream - IN: The stream can be a file stream or a DB stream depending on the source.  
			For example, if	the data is coming from the scrap/clipboard it will be a DB stream and 
			if the data is coming from a file selected in the Place dialog then a file stream will be 
			used.  
		@param showProgressBar - IN: Pass kFalse for the showProgressBar argument to suppress any 
			progress bars from displaying (in case you want to display your own).
		@param forceCreateProxy - IN: kFalse allows the command to share the proxy with
			another image if that image has the same link. kFalse helps prevent pub bloat.
		@param transparencyAlphaIndex - IN: If >= 0, it is the index of the alpha to use as
			a transparency mask.
	*/
	virtual void Set(IDataBase* db, UID uid, IPMStream *stream,
		bool8 showProgressBar = kTrue,
		bool8 forceCreateProxy = kFalse,	// kFalse allows the command to share the proxy with
											// another image if that image has the same link. kFalse
											// helps prevent pub bloat.
		int16 transparencyAlphaIndex = -1	// If >= 0, it is the index of the alpha to use as
											// a transparency mask.
		) = 0;

	/** Stream accessor for the Set method above.
		@return pointer to the source stream.
	*/
	virtual IPMStream *GetStream() const = 0;

	/** IDataBase accessor for the Set method above.
		@return pointer to the destination IDataBase.
	*/
	virtual IDataBase* GetImageDB() const = 0;

	/** UID accessor for the Set method above.
		@return UID of the kImageItem boss.
	*/
	virtual UID GetImageUID() const = 0;

	/** ShowProgressBar accessor for the Set method above.
		@return kTrue if we are showing the progress bar.
	*/
	virtual bool8 GetShowProgress() const = 0;

	/** @return kTrue if we are forcing a new image proxy to be created.
	*/
	virtual bool8 GetForceCreateProxy() const = 0;

	/** @return Zero-based index of the index of the alpha channel to use as a transparency mask.
	*/
	virtual int16 GetTransparencyIndex() const = 0;
};

#endif
