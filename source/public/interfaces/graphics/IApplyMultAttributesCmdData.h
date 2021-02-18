//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IApplyMultAttributesCmdData.h $
//  
//  Owner: SusanCL
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
	#ifndef _IApplyMulAttributesCmdData_
	#define _IApplyMulAttributesCmdData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//========================================================================================
class	IGraphicStyleAttributeBossList;
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	A command data interface for applying multiple graphic attributes to page items.
*/
class IApplyMultAttributesCmdData : public IPMUnknown
	{
	public:
		//................................................................................
		//	Data Type
		//................................................................................
		enum { kDefaultIID = IID_IAPPLYMULTATTRIBUTES_CMDDATA};
		

		//____________________________________________________________________________________
		//	Accessor for the command's attribute list
		//	NOTE:	Stroke and fill rendering attributes should also be set here.
		//____________________________________________________________________________________
		/**	Set a list of attributes to apply. If the command already has an attribute list,
			the old one is released and this new list replaces the old list.
			@param iAttrList specifies the graphic attributes to apply.
		*/
		virtual void SetAttributes				(IGraphicStyleAttributeBossList* iAttrList) = 0;
		/**	Add an attribute to the command's attribute list. If the command does not already
			has an attribute list, a new list is created. If the specified attribute already exists,
			the content of the new is copied into the old. Otherwise, the attribute is added to the list.
			@param iAttribute spcifies a graphic attribute to add.
		*/
		virtual void AddAnAttribute				(IPMUnknown*) = 0;
		/**	Returns the command's current attribute list. The caller is required to release the
			the attribute list when done.
		*/
		virtual IGraphicStyleAttributeBossList* QueryAttributes(void) = 0;

		//____________________________________________________________________________________
		//	Accessor/Mutator for the command's PrePost mechanism
		//____________________________________________________________________________________
		/**	Sets the command PrePost flag to true so that the attribute's pre-post action
			will be applied.
		*/
		virtual void		EnableCommandPrePost			(void) = 0;
		/**	Sets the command PrePost flag to false so that the attribute's pre-post action
			will not be applied.
		*/
		virtual void		DisableCommandPrePost			(void) = 0;
		/**	Sets the command PrePost flag to false so that the attribute's pre-post action
			will not be applied.
			@param doPrePost is true if command PrePost flag should be set.
		*/
		virtual void		SetCommandPrePostFlag			(bool16 doPrePost) = 0;
		/**	Returns the command's current PrePost flag.
		*/
		virtual bool16		GetCommandPrePostFlag			(void) = 0;
		
		//____________________________________________________________________________________
		//	Accessor/Mutator for the command's DoNotify()
		//____________________________________________________________________________________
		/**	Sets the command notification flag to true so that the command will notify.
		*/
		virtual void		EnableCommandDoNotify			(void) = 0;
		/**	Sets the command notification flag to false so that the command will not notify.
		*/
		virtual void		DisableCommandDoNotify			(void) = 0;
		/**	Sets the command notification flag.
			@param doNotify is true if command notification flag should be set.
		*/
		virtual void		SetCommandDoNotifyFlag			(bool16 doNotify) = 0;
		/**	Returns the command's current notification flag.
		*/
		virtual bool16		GetCommandDoNotifyFlag			(void) = 0;

		//____________________________________________________________________________________
		//	Accessor/Mutator for whether or not the command should flatten the page
		//	item list.
		//____________________________________________________________________________________
		/**	Sets the command flattening flag to true so that the command's item list will be flatten.
		*/
		virtual	void		EnableFlattenPageItem			(void) = 0;
		/**	Sets the command flattening flag to false so that the command's item list will not be flatten.
		*/
		virtual	void		DisableFlattenPageItem			(void) = 0;
		/**	Sets the command flattening flag.
			@param doFlatten is true if command flattening flag should be set.
		*/
		virtual void		SetFlattenPageItemFlag			(bool16 doFlatten) = 0;
		/**	Returns the command's flattening flag.
		*/
		virtual bool16		GetFlattenPageItemFlag			(void) = 0;

		//____________________________________________________________________________________
		//	Accessor/Mutator for whether or not the command should invalidate the page
		//	item list.
		//____________________________________________________________________________________
		/**	Sets the command invalidate flag to true so that the command will invalidate the page items
			for redraw.
		*/
		virtual	void		EnableInvalidatePageItem		(void) = 0;
		/**	Sets the command invalidate flag to false so that the command will not invalidate the page items
			for redraw.
		*/
		virtual	void		DisableInvalidatePageItem		(void) = 0;
		/**	Sets the command pageitem invalidate flag.
			@param doInvalidate is true if command invalidate flag should be set.
		*/
		virtual void		SetInvalidatePageItemFlag		(bool16 doInvalidate) = 0;
		/**	Returns the command's pageitem invalidate flag.
		*/
		virtual bool16		GetInvalidatePageItemFlag		(void) = 0;
	};
		
#endif // _IApplyMulAttributesCmdData_
