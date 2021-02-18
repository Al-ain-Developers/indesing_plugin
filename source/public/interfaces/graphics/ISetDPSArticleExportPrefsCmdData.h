//========================================================================================
//  Owner: Adobe Systems Inc.
//  
//  Copyright 2010-2015 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once

#include "DigitalPublishingID.h"
#include "IDPSArticleExportPrefs.h"

/**
 A non-persistent companion interface to IDPSArticleExportPrefs. For description of
 various methods, see IDPSArticleExportPrefs.
 */

class ISetDPSArticleExportPrefsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETDPSARTICLEEXPORTPREFSCMDDATA };

//----------------------------------------------------------------------------------------

	/**
	 Gets the target document

	 @return IDocument*
	 */
	virtual const IDocument* GetIDoc() const = 0;

	/**
	 Sets the target document

	 @param iDoc	IN IDocument*
	 */
	virtual void SetIDoc(IDocument* const iDoc) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Gets Target Dimension Width

	 @return Dimension Width
	 */
	virtual uint32 const &GetDimensionWidth() const = 0;

	/**
	 Sets Target Dimension Width

	 @param dimensionWidth	IN Target Dimension Width
	 */
	virtual void SetDimensionWidth(uint32 const &dimensionWidth) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Gets Dimension Height

	 @return Dimension Height
	 */
	virtual uint32 const &GetDimensionHeight() const = 0;

	/**
	 Sets Dimension Height

	 @param dimensionHeight	IN Dimension Height
	 */
	virtual void SetDimensionHeight(uint32 const &dimensionHeight) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Gets Article Format

	 @return Article Format
	 */
	virtual IDPSArticleExportPrefs::ArticleBuilderArticleFormat GetArticleFormat() const = 0;

	/**
	 Sets Article Format

	 @param articleFormat		IN New Article Format
	 */
	virtual void SetArticleFormat(IDPSArticleExportPrefs::ArticleBuilderArticleFormat articleFormat) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Gets JPEG compression quality

	 @return JPEG compression quality
	 */
	virtual IDPSArticleExportPrefs::ArticleBuilderJPEGQuality GetJPEGQuality() const = 0;

	/**
	 Sets JPEG compression quality

	 @param quality		IN New compression quality
	 */
	virtual void SetJPEGQuality(IDPSArticleExportPrefs::ArticleBuilderJPEGQuality quality) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Is Smooth Scrolling Selection

	 @return True if Smooth Scrolling Selection
	 */
	virtual bool16 IsSmoothScrolling() const = 0;

	/**
	 Sets Is Smooth Scrolling Selection

	 @param smoothScrolling		IN New bool if Smooth Scrolling selection
	 */
	virtual void SetSmoothScrolling(bool16 smoothScrolling) = 0;

//----------------------------------------------------------------------------------------

	/**
	 Is Horizontal Swipe Selection

	 @return True if Horizontal Swipe Selection
	 */
	virtual bool16 IsHorizontalSwipe() const = 0;

	/**
	 Sets Is Horizontal Swipe Selection

	 @param horizontalSwipe		IN New bool if Horizontal Swipe selection
	 */
	virtual void SetHorizontalSwipe(bool16 horizontalSwipe) = 0;


//----------------------------------------------------------------------------------------
	/**
	 Gets Layout

	 @return Layout
	 */
	virtual PMString const &GetLayout() const = 0;

	/**
	 Sets Layout

	 @param layout	IN New Layout
	 */
	virtual void SetLayout(PMString const &layout) = 0;

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

};

