//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IAddMultAttributesCmdData.h $
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
	#ifndef _IAddMultAttributesCommandData_
	#define _IAddMultAttributesCommandData_

//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________

	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"

//===================================================================================
	class IGraphicStyleAttributeBossList;
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

	/**	A command data interface for adding multiple graphic attributes to the graphic state.
	*/
	class IAddMultAttributesCmdData : public IPMUnknown
		{
		public:
			enum {kDefaultIID = IID_IADDMULTATTRIBUTESCMDDATA };

		public:

			/**	Set the list of attributes to be added.
				The data interface has the owenership of the attribute list.
				@param attributes specifies the list of attributes to add.
			*/
			virtual void SetAttributes(IGraphicStyleAttributeBossList *attributes) = 0;

			/**	Returns the list of attributes.
			*/
			virtual IGraphicStyleAttributeBossList* QueryAttributes(void) = 0;

			/**	Set the list of attribute classes to add.
				This list limits the attributes to add to only those attribute classes in this list.
				The command data interface has the owenership of the class list.
				@param pClassList specifies the list of attribute classes. If all attributes
				should be added, then pClassList can be nil.
			*/
			virtual void SetAttributeList(ClassID* pClassList) = 0;
			/**	Returns the list of attribute classes specified by pClassList.
			*/
			virtual ClassID* GetAttributeList (void) const = 0;

			/**	Set the number of attributes in the attribute class list.
				@param attributeCount is number of attributes.
			*/
			virtual void SetAttributeCount(uint16 attributeCount) = 0;
			/**	Returns the number of attributes in the attribute class list.
			*/
			virtual uint16 GetAttributeCount (void) const = 0;

			/**	Set whether or not this command should be joined with the previous
				attribute command.
				@param yesno is true if command is joined.
			*/
			virtual void SetJoin(bool8 yesno) = 0;
			/**	Return whether or not command should be joined.
				@return true if command should be joined.
			*/
			virtual bool8 GetJoin(void) const = 0;
		};

		

#endif // _IAddMultAttributesCommandData_

