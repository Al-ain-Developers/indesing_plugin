//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IDocSavePrefsCmdData.h $
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
#ifndef __IDocSavePrefsCmdData__
#define __IDocSavePrefsCmdData__

#include "IPMUnknown.h"
#include "IDocSavePrefs.h"

class IDocument;

/**	IDocSavePrefsCmdData is a data interface for the kSetDocSavePrefsCmdBoss.  It is used
by the client of the command to specify the preview and thumbnail options for InDesign
documents.
@see IDocSavePrefs.h
 */
class IDocSavePrefsCmdData : public IPMUnknown
{
public:
	/** Default IID enum
	*/
	enum { kDefaultIID = IID_IDOCSAVEPREFSCMDDATA};


	/**	Set the target document
		@param *theDocument IN - Called by the client to specify the target document.
	 */
	virtual void SetDocument(IDocument *theDocument) = 0;

	/**	Called by the command to obtain the target document.
		@param none
		@return IDocument - returns the document set by a call to SetDocument(). 
	 */
	virtual IDocument *GetDocument() const = 0;
	
	/**	SetThumbnailOptions is called by the client to specify the new thumbnail options.
		@param thumbnail IN - the new setting
	 */
	virtual void SetThumbnailOptions(IDocSavePrefs::ThumbnailOptions thumbnail) = 0;

	/**	GetThumbnailOptions() is called by the command to obtain the desired thumbnail options.
		@param none
		@return IDocSavePrefs::ThumbnailOptions - returns the thumbnail options set by SetThumbnailOptions().
	 */
	virtual IDocSavePrefs::ThumbnailOptions GetThumbnailOptions() const = 0;

	/**	SetPreviewSizeOptions is called by the client to specify the new Preview size options.
		@param preview size IN - the new setting
	 */
	virtual void SetPreviewSizeOptions(IDocSavePrefs::PreviewSizeOptions Previewsize) = 0;

	/**	GetPreviewSizeOptions() is called by the command to obtain the desired Preview size options.
		@param none
		@return IDocSavePrefs::PreviewSizeOptions - returns the Preview size options set by SetPreviewSizeOptions().
	 */
	virtual IDocSavePrefs::PreviewSizeOptions GetPreviewSizeOptions() const = 0;

	/**	Set the preference of whether or not to save previews with documents
		@param saveThumbnail IN - the new setting
	 */
	virtual void SetSaveThumbnailWithDocument(bool16 saveThumbnail) = 0;

	/**	Get the preference of whether or not to save previews with documents
		@param void 
		@return true if we're saving thumbnails 
	 */
	virtual bool16 GetSaveThumbnailWithDocument() const = 0;

};


#endif // __IDocSavePrefsCmdData__
