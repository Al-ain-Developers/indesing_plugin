//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRemoveMultAttributesCmdData.h $
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
	#ifndef _IRemoveMultAttributesCommandData_
	#define _IRemoveMultAttributesCommandData_

//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"

class IGraphicStyleAttributeBossList;
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATION
//___________________________________________________________________________________

/**	A command data interface for the kRemoveMultAttributesCmdBoss.
*/
	class IRemoveMultAttributesCmdData : public IPMUnknown
		{
		public:
			enum { kDefaultIID = IID_IREMOVEMULTATTRIBUTESCMDDATA };
		//___________________________________________________________________________
		//	Accessor memeber functions
		//___________________________________________________________________________
		public:

			/**	Sets the list of attributes to be removed.
				@param attributes specifies the list of attributes to be removed
			*/
			virtual void SetAttributes(IGraphicStyleAttributeBossList *attributes) = 0;

			/**	Returns the list of attributes to be removed.
			*/
			virtual IGraphicStyleAttributeBossList* QueryAttributes(void) = 0;

			/**	Sets the list of attribute classes to be removed.
				This list limits the attribute classes to be removed to those defined in this list.
				The command should take the ownership of pClassIDList and is responsible for
				its disposal.
				@param pClassIDList specifies the list of attribute classes to remove.
				If all attributes should be removed, then pClassIDList can be nil.
			*/
			virtual void SetAttributeList(ClassID* pClassIDList) = 0;

			/** Returns the list of attributes classes to be removed.
				@return a list of attribute classes.
			*/
			virtual ClassID* GetAttributeList (void) const = 0;

			/**	Sets the number of attribute classes in pClassIDList.
				@param attrClassCount specifies the number of attributes classes.
			*/
			virtual void SetAttributeCount(uint16 attrClassCount) = 0;
			/** Returns the number of attributes classes.
			*/
			virtual uint16 GetAttributeCount (void) const = 0;

			/**	Set whether of not this command should be joined with the previous
				attribute command.
				@param yesno is true if command is joined.
			*/
			virtual void SetJoin(bool8 yesno) = 0;
			/**	Return whether or not command should be joined.
				@return true if command should be joined.
			*/
			virtual bool8 GetJoin(void) const = 0;
		};

		

#endif // _IRemoveMultAttributesCommandData_

