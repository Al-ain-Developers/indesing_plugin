//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CPageItemAdaptiveTransform.h $
//  
//  Owner: Sachin Singhal
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2018 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __CPAGEITEMADAPTIVETRANSFORM__
#define __CPAGEITEMADAPTIVETRANSFORM__

#include "IAdaptiveTransform.h"
#include "IAdaptiveTransientData.h"
#include "IGeometryFacade.h"

class PUBLIC_DECL CPageItemAdaptiveTransform : public CPMUnknown<IAdaptiveTransform>
{
	enum STAGE
	{
		PREPROCESS,
		PROCESS,
		POSTPROCESS,
		FINISH
	};
public:
	CPageItemAdaptiveTransform(IPMUnknown *boss);
	virtual ~CPageItemAdaptiveTransform();

	/**	This is the first control given to the page item. This is called when the process of change in layout is about to start. The page item can capture the initial state
		e.g. initial bounds of the page item and dependent etc.
		This information may be used in later steps.
		@return ErroCode.
	*/
	virtual ErrorCode PreProcess();

	/**	This is the second control given to the page item. This will be called after the changes in the layout has happened and thus gives a chance to the individual page items
		to adjust according to the changes in the layout. Changes like resizing of the outer bound may happen here.
		@return ErroCode.
	*/
	virtual ErrorCode Process();

	/** This is the third control given to the page item. This is called after calling process on every page item.
		This is mainly supposed to be used when some processing has dependency on the other page items to adjust themselves.
		@return ErroCode.
	*/
	virtual ErrorCode PostProcess();

	/** This is called at the very end when the page item can perform a cleanup and reset any cached information in the above calls.
		This may even be called in between if the whole process is to be aborted.
	*/
	virtual void Finish();
    
protected:
	/**	The page items are given controls to work on the adjustment at various stages of the process which have been defined above. These controls are not just about the 
		processing of current page item but also about the dependent page items. e.g. A group should also work on the page items that constitute that group. Hence, to 
		ease out the processing at various stages, the broad level calls are further broken into two calls. One (XXThis()) for the processing of the current page item and
		the second (ProcessDependents()) for the processing of the dependent page items. 
		This information may be used in later steps.
	*/
	
	/**	This is called from PreProcess() for the processing of the current page item.
		@return ErroCode.
	*/
	virtual ErrorCode PreProcessThis();

	/**	This is called from Process() for the processing of the current page item.
		@return ErroCode.
	*/
	virtual ErrorCode ProcessThis();

	/**	This is called from PostProcess() for the processing of the current page item.
		@return ErroCode.
	*/
	virtual ErrorCode PostProcessThis();

	/**	This is called from Finish() for the processing of the current page item.
	*/
	virtual void FinishThis();

	/**	This is called from PreProcess(), Process(), PostProcess() and Finish() for the processing of the page items which are dependent on the current page item.
		@return ErroCode.
	*/
	virtual ErrorCode ProcessDependents(CPageItemAdaptiveTransform::STAGE stage);

	/**	This is used to collect all the page items which the current page items deems to be its dependent.
		@return list of dependent page items.
	*/
	virtual UIDList CollectDependents();

	/**	This is called after the final bounds have been computed and set in fFinalBounds. This is done to resize the page items as per the final bounds.
		A page item may choose to do a no-op here.
		@return ErroCode.
	*/
    virtual ErrorCode Resize();

	/**	This may be called when the repositioning of the page item is essential as well. e.g. this may be needed for a parent page item but not for the page items under its hierarchy.
		This is also being called after the final bounds have been computed and set in fFinalBounds.
		@return ErroCode.
	*/
    virtual ErrorCode Reposition();

	/**	This is called after the final bounds have been computed and set in fFinalBounds. This looks for the option of maintaining aspect ratio and if needed sets the final bounds as per that.
	*/
	virtual void MaintainAspectRatioIfNeeded();

	/**	Returns whether the current page item, if hidden, needs to be adjusted or not.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldHandleHidden();

	/**	Returns whether the current page item, if locked, needs to be adjusted or not.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldHandleLocked();

	/**	Returns if the text should be adjusted for the current page item.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldHandleText();

	/**	Returns whether the current page item, if non rectangular, needs to be adjusted while maintaining aspect ratio.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldMaintainAspectRatioForNonRectangularPI();

	/**	Returns if for the current page item, adjustment needs to be done while maintaining aspect ratio.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldMaintainAspectRatioForThis();

	/**	Returns if the current page item, should be processed or not. The decision is made while taking care of various options e.g. whether handling of hidden items is enabled or not.
		These option in conjunction with the current state of page item defines the return value.
		@return	kTrue if yes.
	*/
	virtual bool16 ShouldProcessThis();
   
	virtual std::set<PMReal> GetAllFontsSizes() { return std::set<PMReal>(); }
	virtual ErrorCode ResizeXPEffects();
	virtual void AdaptTextOnPath();

	AdapativePageItemData * fData;
private:
	/**	Unlocks the current page item for processing if such option is set.
		@return	ErrorCode.
	*/
	ErrorCode UnlockIfNeeded();

	/**	Locks the current page item if it was locked earlier.
		@return	ErrorCode.
	*/
	ErrorCode LockIfNeeded();

	/** Returns true if the item is hidden, false otherwise.
		@return True if the item is hidden.
	*/
	bool16 IsCurrentItemHidden();

	/** Returns true if the item is locked, false otherwise.
	@return True if the item is locked.
	*/
	bool16 IsCurrentItemLocked();
};

#endif
