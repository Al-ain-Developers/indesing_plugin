//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ISmartReflowService.h $
//  
//  Owner: David Stephens
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
#ifndef __ISmartReflowService__
#define __ISmartReflowService__

#include "IPMUnknown.h"

class IFrameList;

/** This is an Interface plugins can implement if they'd like to be called during text overset
	and underset handling.	In order to get your implementation of this interface called at 
	during "Smart Text Reflow" processing, you must	create a new boss.  like so:
	
resource ClassDescription (13)
{
	kMySmartReflowServiceBoss,   
	kInvalidClass,
	{
		// kSmartTextReflowServiceProviderImpl is a CServiceProvider that registers the
		//	boss as a kSmartReflowServiceID. You can replace this implementation with your own,
		//	but it must return kSmartReflowServiceID from its GetServiceID() method in order to
		//	get your implementation of IID_ISMARTREFLOWSERVICE to be called.
		//			
		IID_IK2SERVICEPROVIDER, kSmartTextReflowServiceProviderImpl,

		// Replace kMySmartReflowServiceImpl with your own implementation of ISmartReflowService.
		IID_ISMARTREFLOWSERVICE, kMySmartReflowServiceImpl,
	}
};

*/

class ISmartReflowService : public IPMUnknown
{
public:
	/** Default interface ID for the ISmartReflowService allowing for declarations such as the following:
        InterfacePtr<ISmartReflowService> iSmartReflowService(provider, UseDefaultIID()); 
	*/
    enum { kDefaultIID = IID_ISMARTREFLOWSERVICE }; 

	/** Is the smart reflow feature supported. This method will only be called once per session. Its purpose is to
		allow the enabling or disabling of the Smart Text Reflow feature.  For example, InCopy ships with 
		this feature disabled.  However, you could write an ISmartReflowService in an InCopy plug-in that
		returns 'true' to enable this feature.  Keep in mind that InCopy does not save changes to the 
		InDesign binary document (indd).  Therefore, enabling this feature for InCopy would only allow users
		to see what should happen in InDesign when InCopy story changes are updated in the document from within
		InDesign. 
		
		If your plug-in could be used for both InDesign and InCopy and you do not want the feature
		enabled in InCopy, then return 'false' if the result of LocaleSetting::GetLocale().IsProductFS(kInCopyProductFS)
		is false.

		@return true to allow the Smart Text Reflow feature, false otherwise.
	*/
	virtual bool IsSmartReflowFeatureSupported(void) = 0;

	/** Is it okay for InDesign to create new pages and flow the overset text onto those pages? 
		@param inFrameList [IN]: The frame list that is in overset.
		@return. Return true to allow the adding of pages for the given story. Return false to disallow.
	*/
	virtual bool GetAllowOversetStoryToReflow(const IFrameList* inFrameList) = 0;

	/** Is it okay for InDesign to delete pages containing empty text frames from the given
		frameList? 
		@param inFrameList [IN]: The frame list that is in underset.
		@return. Return true to allow the deleting of pages for the given story. Return false to disallow.
	*/
	virtual bool GetAllowPageDeletesForUndersetStory(const IFrameList* inFrameList) = 0;

	/** InDesign is incrementally adding pages to handle the overset text. If the last frame in the
		inFrameList at the time the text went into overset (i.e. when GetAllowOversetStoryToReflow was called)
		is an overridden master text frame, then the master page that was applied to the page containing the
		overset text will be applied to the new pages and the corresponding master text frames will be overridden
		and threaded at the end of the inFrameList. 
		@param inFrameList [IN]: The frame list that is in overset.
		@param inInsertSpread [IN]: The spread that 'inPageInsertLocation' is relative to.
		@param inPageInsertLocation [IN]: zero-based index within the given spread to insert new pages.
		@param inNumPages [IN]: The number of pages that will be inserted.
		@return. Return true to continue smart reflow. Return false to stop processing.  Returning false 
			does not remove any pages added thus far.
	*/
	virtual bool AddingPages(const IFrameList* inFrameList, const UIDRef& inInsertSpread, 
			uint32 inPageInsertLocation, uint32 inNumPages) = 0;

	/** Is if okay for InDesign to delete this particular page item and thus okay to delete the page that contains
		it if all other page deletion conditions are met? 
		
		This method is useful if you have created a custom page item that you wish to allow to be
		deleted under certain conditions. For example, if you have a custome page item that contains
		a text frame, you may want to allow your page item to be deleted if the text frame becomes empty.

		@return true if it is OK for the page item to be deleted as part of smart reflow.
	*/
	virtual bool CanDeletePageItemForReflow(UIDRef& pageItem) = 0;
};

#endif
