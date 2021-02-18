//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ITLAdornmentUtils.h $
//  
//  Owner: Cindy Chen
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __ITLAdornmentUtils__
#define __ITLAdornmentUtils__

#include "InCopySharedID.h"

class IFrameList;
class UIDList;
class UIDRef;

/**
   This utility adding/removing the Lock adornment (represents the InCopy story) to/from the objects.
 */

class ITLAdornmentUtils : public IPMUnknown
{
public:
		enum	{kDefaultIID = IID_ITLADORNUTILS};


		/**	Adding the Lock adornment
			If ICBridgeAdornmentUtils is present, adding the adornment (kICBridgeTextLockAdornmentBoss) to objects (GraphicFrame).
			otherwise adding adornment (kTextLockAdornmentBoss) to the objects (MultiColumnFrame)
			@param list The objects that the adornment is added to
			@param docRef The document contains the objects
		*/
		virtual void AddTextLockAdornment(UIDList* list, UIDRef& docRef) = 0;	

		/**	Adding the Lock adornment
			If ICBridgeAdornmentUtils is present, adding the adornment (kICBridgeTextLockAdornmentBoss) to objects (GraphicFrame).
			otherwise adding adornment (kTextLockAdornmentBoss) to the objects (MultiColumnFrame)
			@param list The objects that the adornment is added to
			@param docRef The document contains the objects
		*/
		virtual void AddFrameListTextLockAdornment(IFrameList *list, UIDRef& docRef) = 0;	

		/**	Remove Lock adornment
			@param list The objects that the adornment is removed
			@param docRef The document contains the objects
		*/
		virtual void RemoveTextLockAdornment(UIDList* list, UIDRef& docRef) = 0;	

		/**	Remove Lock adornment
			@param list The objects that the adornment is removed
			@param docRef The document contains the objects
		*/
		virtual void RemoveFrameListTextLockAdornment(IFrameList *list, UIDRef& docRef) = 0;	

		/**	Check if this IFrameList has Lock adornment
			@param list 
			@return bool16 kTrue means this IFrameList already has Lock adornment
		*/
		virtual bool16 HasTextLockAdornment(IFrameList *list) = 0;	

		/**	Check if this object has Lock adornment
			@param objectRef (Text or Graphic)
			@return bool16 kTrue means this objectRef already has Lock adornment
		*/
		virtual bool16 HasTextLockAdornment(UIDRef objectRef) = 0;	

};
#endif