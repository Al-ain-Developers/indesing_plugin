//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveData.h $
//  
//  Owner: Sachin Singhal
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 2018 Adobe Systems Incorporated. All rights reserved.
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
#ifndef __IAdaptiveData__
#define __IAdaptiveData__

#include "IPMUnknown.h"
#include "AutoLayoutID.h"
#include "UIDList.h" 
#include "ErrorUtils.h"

/** Interface to control adaptive layout.
*/
class IAdaptiveData : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IADAPTIVEDATA };

	/**	This is the first control given to the page item. This is called when the process of change in layout is about to start. The page item can capture the initial state e.g. initial bounds of the page item and dependent etc.
		This information may be used in later steps.
	*/
	virtual void SetRecommendedBounds(PMRect bounds) = 0;

	/**	This is the second control given to the page item. This will be called after the changes in the layout has happened and thus gives a chance to the individual page items to adjust according to the changes in the layout.
		Changes like resizing of the outer bound may happen here.
	*/
	virtual PMRect GetRecommendedBounds(bool reset = false) = 0;

	/** This is the third control given to the page item. This is called after calling process on every page item. This is mainly supposed to be used when some processing has dependency on the other page items to adjust themselves.
	*/
	virtual bool HasRecommendedBounds() = 0;

	/** This is called at the very end when the page item can perform a cleanup and reset any cached information in the above calls. This may even be called in between if the whole process is to be aborted.
	*/
	virtual PMRect GetInitialBounds() = 0;
    
    virtual void SetInitialBounds(PMRect bounds) = 0;
    
    virtual PMRect GetFinalBounds() = 0;
    virtual void SetFinalBounds(PMRect bounds) = 0;

    virtual UIDRef GetParentUID() = 0;
    virtual void SetParentUID(UIDRef uidRef) = 0;
    
    virtual UID GetSpreadUID() = 0;
    virtual void SetSpreadUID(UID uid) = 0;
    
	virtual bool16 HasNewStartAndEndPointForTOP() = 0;
	virtual void GetStartAndEndPointForTOP(PMPoint &startPoint, PMPoint &endPoint, bool reset = false) = 0;
	virtual void SetStartAndEndPointForTOP(PMPoint startPoint, PMPoint endPoint) = 0;

    virtual void Reset() = 0;
};

#endif	// __IAdaptiveLayout__
