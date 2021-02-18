//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutControlViewHelper.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __ILAYOUTCONTROLVIEWHELPER__
#define __ILAYOUTCONTROLVIEWHELPER__

#include "PMPoint.h"
#include "LayoutUIID.h"
#include "GraphicsID.h"
#include "HitTestDragConstants.h"

//========================================================================================
// Forward declarations
//========================================================================================

class IGeometry;

//========================================================================================
// CLASS ILayoutControlViewHelper
//========================================================================================

/**
	Helper routines for performing page item hit-testing.
	This interface is installed on kLayoutWidgetBoss and kTextEditorBoss.

*/
class ILayoutControlViewHelper : public IPMUnknown
{
// ----- Helper methods
public:
	enum { kDefaultIID = IID_ILAYOUTCONTROLVIEWHELPER };
	

	/**	Traverse the current spread's page items in z-order using the Visitor scheme until a successful hit
		test is found for a page item. Return that item. The Visitor scheme is capable of traversing non-hierarchically 
		related items (such as inlines).  
		@param where [IN] Hit test location in pasteboard coordinates
		@param handlerClass [IN] Handler class ID to use for hittesting. The handler boss establishes a particular 
		type of behavior for what to do at each type of page item encountered. 
		@param interfaceID [IN] Interface ID to check the found item for, defaults to IID_IGEOMETRY.
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 
		@return IPMUnknown* Return an interface from the hit item. Nil if no item hit or the found item does not support interfaceID.
		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
 		@see GenericID for various kXXXHitTestHandlerBoss definitions
		@see HitTestDragConstants.h for kHitTestTolerance
	 */
	virtual IPMUnknown* QueryHitTestPageItemNew(const PBPMPoint& where, const ClassID handlerClass,
											 const PMIID& interfaceID = IID_IGEOMETRY, int16 tolerance = kHitTestTolerance) = 0;


	/**	Traverse the page items (in z-order) of each visible spread using the Visitor scheme until a successful hit
		test is found for a page item. Return that item. The Visitor scheme is capable of traversing non-hierarchically 
		related items (such as inlines).
		@param where [IN] Hit test location in pasteboard coordinates
		@param handlerClass [IN] Handler class ID to use for hittesting. The handler boss establishes a particular 
		type of behavior for what to do at each type of page item encountered. 
		@param interfaceID [IN] Interface ID to check the found item for, defaults to IID_IGEOMETRY.
		@param tolerance [IN] The tolerance for how close 'where' must be to be considered a hit. Defaults to kHitTestTolerance. 
		@return IPMUnknown* Return an interface from the hit item. Nil if no item hit or the found item does not support interfaceID.
 		The reference count is incremented. The caller is responsible for calling Release() or embedding the return value in an 
		appropriate InterfacePtr construct.
		@see GenericID for various kXXXHitTestHandlerBoss definitions
		@see HitTestDragConstants.h for kHitTestTolerance
	 */
	virtual IPMUnknown* QueryHitTestPageItemOnVisibleSpreadsNew(const PBPMPoint& where, const ClassID handlerClass,
											 const PMIID& interfaceID = IID_IGEOMETRY, int16 tolerance = kHitTestTolerance) = 0;
};

#endif
