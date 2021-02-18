//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IAdaptiveTransform.h $
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
#ifndef __IAdaptiveTransform__
#define __IAdaptiveTransform__

#include "IPMUnknown.h"
#include "AutoLayoutID.h"
#include "UIDList.h" 
#include "ErrorUtils.h"

#include <set>

/** Interface to control adaptive layout.
*/
class IAdaptiveTransform : public IPMUnknown
{
public:
	/* Default IID to be used by UseDefaultIID() */
	enum { kDefaultIID = IID_IADAPTIVETRANSFORM };

	/**	This is the first control given to the page item. This is called when the process of change in layout is about to start. The page item can capture the initial state
		e.g. initial bounds of the page item and dependent etc.
		This information may be used in later steps.
	*/
	virtual ErrorCode PreProcess() = 0;

	/**	This is the second control given to the page item. This will be called after the changes in the layout has happened and thus gives a chance to the individual page items
		to adjust according to the changes in the layout. Changes like resizing of the outer bound may happen here.
	*/
	virtual ErrorCode Process() = 0;

	/** This is the third control given to the page item. This is called after calling process on every page item. 
		This is mainly supposed to be used when some processing has dependency on the other page items to adjust themselves.
	*/
	virtual ErrorCode PostProcess() = 0;

	/** This is called at the very end when the page item can perform a cleanup and reset any cached information in the above calls. 
		This may even be called in between if the whole process is to be aborted.
	*/
	virtual void Finish() = 0;

	//anichopr: Please remove this.
	virtual std::set<PMReal> GetAllFontsSizes() = 0;
};

#endif	// __IAdaptiveTransform__
