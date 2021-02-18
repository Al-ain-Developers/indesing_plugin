//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IGlobalRecompose.h $
//  
//  Owner: Eric Menninga
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
#ifndef __IGLOBALRECOMPOSE__
#define __IGLOBALRECOMPOSE__

#include "IPMUnknown.h"
#include "AttributeChecker.h"
#include "TextID.h"



/**   This class is designed to cause damages to stories in a
  document, hence making the entire document or portion
  of it to recompose when it is needed to.  The damages can
  be set to the entire document, or it can be set according to specified attributes

  The following is a sample code on how to use this interface:
<pre>
  InterfacePtr&lt;IGlobalRecompose&gt; globalRecompose(theFrontDoc, IID_IGLOBALRECOMPOSE);
  MyAttribute attributeAffected;
  globalRecompose->GlobalAttributeDamage(&attributeAffected);
 </pre>
  where MyAttribute is a derived class from AttributeChecker
  containing implementations to check if the front document contains
  a specifed attributes.

	@ingroup text_comp
*/
class IGlobalRecompose : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGLOBALRECOMPOSE };

		/** Causes damages to all stories in this document.
			@param clearModelCaches can be used to automatically clear the ITextReferences cache and the
			IComposeScanner cache. However, this isn't usually necessary, because those interfaces are caches
			of MODEL data, not composition data.
		*/
		virtual void RecomposeAllStories(bool16 clearModelCaches = kFalse) = 0;

		/** Causes damages to stories containing specified attributes.
			@param singleStory specifies the UID of a single text model if only one story should be examined.
			kInvalidUID means all stories.
			@return if any range of text is marked damaged, the method will return kTrue.
			@see AttributeChecker
		*/
		virtual bool16 SelectiveRecompose(const AttributeChecker& whichAttribute, UID singleStory = kInvalidUID) = 0;

		/** Causes damages to lines containing specified attributes.
			@param singleStory specifies the UID of a single text model if only one story should be examined.
			kInvalidUID means all stories.
			@return if any range of text is marked damaged, the method will return kTrue.
			@see WaxLineChecker
		*/
		virtual bool16 SelectiveRecompose(const WaxLineChecker& whichAttribute, UID singleStory = kInvalidUID) = 0;

		/** Causes damages to stories containing specified styles and overrides.
			@param singleStory specifies the UID of a single text model if only one story should be examined.
			kInvalidUID means all stories.
			@return if any range of text is marked damaged, the method will return kTrue.
			@see ModelChecker
		*/
		virtual bool16 SelectiveRecompose(const ModelChecker& whichAttribute, UID singleStory = kInvalidUID) = 0;

		/** Causes damages to stories containing specified story options.
			@param singleStory specifies the UID of a single text model if only one story should be examined.
			kInvalidUID means all stories.
			@return if any range of text is marked damaged, the method will return kTrue.
			@see StoryOptionsChecker
		*/
		virtual bool16 SelectiveRecompose(const StoryOptionsChecker& whichAttribute, UID singleStory = kInvalidUID) = 0;

		/** Force the entire document to be fully composed.
			(The above calls just mark composition damage.)
		*/
		virtual void ForceRecompositionToComplete() = 0;

};


#endif // __IGLOBALRECOMPOSE__

