//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IClearAttrOverrideCmdData.h $
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
	#ifndef _IClearAttrOverrideCmdData_
	#define _IClearAttrOverrideCmdData_
//========================================================================================
//________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
	#include <vector>
//========================================================================================
//________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________

/**	A graphic attribute command data interface for clearing attribute overrides.
	This data interface will either take one attribute class ID or a list of attribute
	class IDs.
*/
class IClearAttrOverrideCmdData : public IPMUnknown
	{
	public:
		//................................................................................
		//	Data Type
		//................................................................................
		enum { kDefaultIID = IID_CLEARATTROVERRIDE_CMDDATA};
		
		/**	Set the graphics attribute class ID to clear.
			Setting this after setting class list will clear the list and add this attribute ClassID
			to the list.
			@param attriClassID specifies the attribute class ID to clear.
		*/
		virtual void		SetAttributeClassID				(ClassID attrClassID) = 0;
		/**	Returns the graphics attribute class ID set through SetAttributeClassID to clear.
			@see SetAttributeClassID
		*/
		virtual ClassID		GetAttributeClassID				(void) = 0;

		/**	Set the list of graphics attribute class ID to clear.
			If pClassIDList is not nil, then this is used to determine the  list of 
			attribute class to clear. This object will acquire ownership of the array, and will delete it
			@param pClassIDList specifies the list of attribute class ID to clear.
		*/
		virtual void SetAttributeClassIDList(const std::vector<ClassID>& classIDList) = 0;
		/**	Get the list of graphics attribute class ID to clear.
			@reutrn a list of attribute class ID to clear.
		*/
		virtual const std::vector<ClassID>& GetAttributeClassIDList (void) const = 0;

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
		
#endif // _IClearAttrOverrideCmdData_
