//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IApplyRendObjAttrCmdData.h $
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
	#ifndef _IApplyRenderingObjectAttributeCmdData_
	#define _IApplyRenderingObjectAttributeCmdData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "IPMUnknown.h"
	#include "GraphicStylesID.h"
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	A command data interface for applying a rendering attribute. There are currently three
	rendering attributes: kGraphicStyleFillRenderingAttrBoss, kGraphicStyleStrokeRenderingAttrBoss, and
	kGraphicStyleGapRenderingAttrBoss.
*/
class IApplyRendObjAttrCmdData : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IAPPLYRENDOBJATTR_CMDDATA };
		
		/**	Set the renering attribute class ID for the command.
			@param renderingAttrClassID specfies the rendering attribute class ID.
		*/
		virtual void		SetAttributeClassID				(ClassID renderingAttrClassID) = 0;

		/**	Returns the rendering attribute class ID.
		*/
		virtual ClassID		GetAttributeClassID				(void) = 0;

		/**	Set the corresponding renering object class ID for the command. 
			This should be kPMColorBoss, kGradientRenderingObjectBoss, or 
			kGraphicStateNoneRenderingObjectBoss.
			@param renderingClassID specfies the rendering object class ID.
		*/
		virtual void		SetRenderingClassID				(ClassID renderingClassID) = 0;
		/**	Returns the rendering object class ID.
		*/
		virtual ClassID		GetRenderingClassID				(void) = 0;

		/**	Set the database for the command target.
		*/
		virtual void		SetDataBase						(IDataBase* iDataBase) = 0;
		/**	Returns the command target database.
		*/
		virtual IDataBase*	GetDataBase						(void) = 0;

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
	};
		
#endif // _IApplyRenderingObjectAttributeCmdData_
