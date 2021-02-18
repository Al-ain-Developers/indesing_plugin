//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IApplyAttributeCmdData.h $
//  
//  Owner: Michael_Martz
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
	#ifndef _IApplyAttributeCmdData_
	#define _IApplyAttributeCmdData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	The graphic attribute command data for applying a single graphic attribute.
*/
class IApplyAttributeCmdData : public IPMUnknown
	{
	public:
		//................................................................................
		//	Data Type
		//................................................................................
		enum { kDefaultIID = IID_IAPPLYATTRIBUTE_CMDDATA};
		
		//................................................................................
		//	Accessor/Mutator for the command's PrePost mechanism
		//................................................................................

		/**	Enable command pre-post action for the attribute.
			@see also IAttributePrePost.h
			@see also IRenderingObjectApplyAction.h
		*/
		virtual void		EnableCommandPrePost			(void) = 0;
		/**	Disable command pre-post action for the attribute.
			@see also IAttributePrePost.h
			@see also IRenderingObjectApplyAction.h
		*/
		virtual void		DisableCommandPrePost			(void) = 0;
		/**	Set command pre-post action for the attribute.
			@see also IAttributePrePost.h
			@see also IRenderingObjectApplyAction.h
			@param doPrePostAction is true if command pre-post action is set.
		*/
		virtual void		SetCommandPrePostFlag			(bool16 doPrePostAction) = 0;
		/**	Returns true if the command pre-post action flag is set.
		*/
		virtual bool16		GetCommandPrePostFlag			(void) = 0;
		
		//................................................................................
		//	Accessor/Mutator for the command's DoNotify()
		//................................................................................

		/**	Enable command notification.
		*/
		virtual void		EnableCommandDoNotify			(void) = 0;
		/**	Disable command notification.
		*/
		virtual void		DisableCommandDoNotify			(void) = 0;
		/**	Set command notification flag.
			@param doNotify is true if command notification is set.
		*/
		virtual void		SetCommandDoNotifyFlag			(bool16 doNotify) = 0;
		/**	Returns true if the command notification flag is set.
		*/
		virtual bool16		GetCommandDoNotifyFlag			(void) = 0;

		//................................................................................
		//	Accessor/Mutator for whether or not the command should flatten the page
		//	item list.
		//................................................................................

		/**	Enable flattening of page items.
		*/
		virtual	void		EnableFlattenPageItem			(void) = 0;
		/**	Disable flattening of page items.
		*/
		virtual	void		DisableFlattenPageItem			(void) = 0;
		/**	Set the page item flattening flag.
			@param doFlattenPageitem is true if page item flattening flag is set.
		*/
		virtual void		SetFlattenPageItemFlag			(bool16 doFlattenPageitem) = 0;
		/**	Returns true if the page item flattening flag is set.
		*/
		virtual bool16		GetFlattenPageItemFlag			(void) = 0;

		//................................................................................
		//	Accessor/Mutator for whether or not the command should invalidate the page
		//	item list.
		//................................................................................

		/**	Enable the invalidation of page items.
		*/
		virtual	void		EnableInvalidatePageItem		(void) = 0;
		/**	Disable the invalidation of page items.
		*/
		virtual	void		DisableInvalidatePageItem		(void) = 0;
		/**	Set the page item invalidation flag.
			@param doInvalidate is true if page item invalidation flag is set.
		*/
		virtual void		SetInvalidatePageItemFlag		(bool16 doInvalidate) = 0;
		/**	Returns true if the page item invalidation flag is set.
		*/
		virtual bool16		GetInvalidatePageItemFlag		(void) = 0;
	};
		
#endif // _IApplyAttributeCmdData_
