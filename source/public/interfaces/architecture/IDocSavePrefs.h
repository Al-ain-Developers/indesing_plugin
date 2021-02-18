//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocSavePrefs.h $
//  
//  Owner: Dave Stephens
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
#ifndef __IDocSavePrefs__
#define __IDocSavePrefs__

#include "IPMUnknown.h"
#include "DocumentID.h"


/**	IDocSavePrefs are document preferences which dictates whether or not a JPEG thumbnail
of the first one or more Pages will be created and added to the InDesign document at Save time.  
Creating a thumbnail or preview can be very expensive if the document is complex.  Sometimes, 
a preview is not necessary because the document is being stored in a database 
(as is the case for some system integrators) and the preview will never be used.  For these cases, 
a client may wish to disable the preview creation. Use the kSetDocSavePrefsCmdBoss to change 
the thumbnail an preview settings.
 */
class IDocSavePrefs : public IPMUnknown
{
public:
	/** Default IID enum */
	enum { kDefaultIID = IID_IDOCSAVEPREFS};

	/** The thumbnail creation options
	*/
	typedef enum 
	{
		kFirstPageJPEGThumbnail = 0,	// create a JPEG thumbnail of the first Page
		kFirst2PagesJPEGThumbnail ,	// create a JPEG thumbnail of the first 2 Pages
		kFirst5PagesJPEGThumbnail ,	// create a JPEG thumbnail of the first 5 Pages
		kFirst10PagesJPEGThumbnail ,	// create a JPEG thumbnail of the first 10 Pages
        kAllPagesJPEGThumbnail	// create a JPEG thumbnail of all Pages
	} ThumbnailOptions;

	/**	Set the thumbnail preference
		@param thumbnail IN - the new setting
	 */
	virtual void SetThumbnailOptions(ThumbnailOptions thumbnail) = 0;

	/**	Get the current thumbnail preference
		@param void 
		@return ThumbnailOptions 
	 */
	virtual ThumbnailOptions GetThumbnailOptions() const = 0;

	/**	Set the preference of whether or not to save previews with documents
		@param saveThumbnail IN - the new setting
	 */
	virtual void SetSaveThumbnailWithDocument(bool16 saveThumbnail) = 0;

	/**	Get the preference of whether or not to save previews with documents
		@param void 
		@return true if we're saving thumbnails 
	 */
	virtual bool16 GetSaveThumbnailWithDocument() const = 0;

	/** The Preview size options
	*/
	typedef enum 
	{
		kSmall = 0,		// Small		128x128
		kMedium,		// Medium		256x256
		kLarge,			// Large		512x512
		kExtraLarge		// ExtraLarge	1024x1024
	} PreviewSizeOptions;

	/**	Set the Preview size preference
		@param previewsize IN - the new setting
	 */
	virtual void SetPreviewSizeOptions(PreviewSizeOptions previewsize) = 0;

	/**	Get the current Preview size preference
		@param void 
		@return PreviewSizeOptions 
	 */
	virtual PreviewSizeOptions GetPreviewSizeOptions() const = 0;

};

#endif
