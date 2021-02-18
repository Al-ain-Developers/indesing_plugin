//========================================================================================
//  
//  ADOBE CONFIDENTIAL
//   
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/IArticleUtils.h $
// 
//  Owner: Paresh Goel
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once 
#ifndef __IArticleUtils__ 
#define __IArticleUtils__ 

#include "Utils.h" 
#include "PMString.h"
#include "ArticleID.h" 

#include "IMultiColumnTextFrame.h"

class IArticleUtils : public IPMUnknown 
{ 
    public: 
        enum    {kDefaultIID = IID_IARTICLEUTILS};

		/**	Generates a unique Article name in the format "Article ^1" where
			^1 is the first available number starting from 1
			@param db, whose article list ahould be considered for generation of unique name
		*/
		virtual PMString GenerateUniqueArticleName(IDataBase* db) =0;

		//
		// This method will return the UID of a valid PageItem to add based on the
		// specified PageItem. Typically the same PageItem will be returned but in
		// the case of Images or Spline TextFrames a different PageItem might be
		// returned.
		//
		virtual UID GetActualUIDToAdd(const UIDRef& pageItemRef) =0;	

		virtual UID GetFirstLegalTextFrameUID(const UIDRef& textPageItem) =0;

		// Returns the first legal Spline TextFrame going forward starting at the
		// specified Spline TextFrame. If there are no legal Spline TextFrames then
		// this will return kInvalidUID.
		//
		// Legal in this sense is one that can be pulled into an Article, so not a
		// TextOnPath and not current in a Group.
		virtual UID GetFirstLegalTextFrameUIDFrom(const UIDRef& splineRef) =0;

		// Returns kTrue if the MCF is for a TextOnPath Spline.
		virtual bool16 GetIsTextOnPath(const IMultiColumnTextFrame* iMCF) =0;

		// Returns the UID of the first Spline TextFrame in the same FrameList as the
		//specified Spline TextFrame.
		virtual UID GetFirstTextFrameInFrameList(const UIDRef& splineRef) =0;	
}; 
     
#endif // __IArticleUtils__ 
