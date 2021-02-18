//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGraphicAttributeInfo.h $
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
	#ifndef _IGraphicAttributeInfo_
	#define _IGraphicAttributeInfo_
//===================================================================================
//___________________________________________________________________________________
//	INCLUDES
//___________________________________________________________________________________
	#include "GraphicStylesID.h"
	#include "IPMUnknown.h"
//===================================================================================
//___________________________________________________________________________________
//	CLASS DECLARATIONS
//___________________________________________________________________________________

/**	This is a required interface for any graphic attributes. This class facilitates in the
	management of graphic attributes.
*/
	class IGraphicAttributeInfo : public IPMUnknown
		{
		//___________________________________________________________________________
		//	Data Types
		//___________________________________________________________________________
		public:
			enum { kDefaultIID = IID_IGRAPHICATTR_INFO };
			
			/**	Indicates type of attributes. An attribute is usually a graphic attribute but
				could be a combination of these three types.
			*/
			enum AttributeKind			// Bit field
				{
				/**	A graphic type attribute.
				*/
				kGraphicAttr			= 0x0001,
				/**	A text type attribute.
				*/
				kTextAttr				= 0x0002,
				/**	A table type attribute.
				*/
				kTableAttr				= 0x0004,

				/** A export type attribute
				*/
				kExportAttr				= 0x0008,
				};
				
		//___________________________________________________________________________
		//	Member Functions
		//___________________________________________________________________________
		public:
			/**	Returns the name of the attribute.
				@return the PMString pointer to the attribute name.
			*/
			virtual PMString*		GetName							(void) const = 0;
			
			/**	Returns kTrue if attribute is a text attribute.
				@return kTrue if attribute is a text attribute; otherwise returns kFalse.
			*/
			virtual bool16			IsTextAttribute					(void) const = 0;
			/**	Returns kTrue if attribute is a graphic attribute.
				@return kTrue if attribute is a graphic attribute; otherwise returns kFalse.
			*/
			virtual bool16			IsGraphicAttribute				(void) const = 0;
			/**	Returns kTrue if attribute is a table attribute.
				@return kTrue if attribute is a table attribute; otherwise returns kFalse.
			*/
			virtual bool16			IsTableAttribute				(void) const = 0;

			/**	Returns kTrue if attribute is a export attribute.
				@return kTrue if attribute is a export attribute; otherwise returns kFalse.
			*/
			virtual bool16			IsExportAttribute				(void) const = 0;
			
			
			/**	Returns kTrue if attribute is a required graphic attribute.
				@return kTrue if attribute is a  required graphic attribute; otherwise returns kFalse.
			*/
			virtual bool16			IsRequiredGraphicAttr			(void) const = 0;

			/**	Returns kTrue if attribute affects page item geometry.
				@return kTrue if attribute affects page item geometry; otherwise returns kFalse.
			*/
			virtual bool16			AffectsPageItemGeometry			(void) const = 0;

			/**	Returns kTrue if attribute is observed by the graphic state.
				Should return kFalse, if plug-in that added the attribute is responsible for managing changes.
				@return kTrue if attribute is observed by the graphic state; otherwise returns kFalse.
			*/
			virtual bool16			ObservedByGraphicState			(void) const = 0;

			/**	Create a text version of this attribute. This method should be implemented if this
				attribute is also a text attribute.
				@return IPMUnknown pointer to the text attribute object or nil.
			*/
			virtual IPMUnknown*		CreateTextAttribute				() const = 0;

			/**	Create a table version of this attribute. This method should be implemented if this
				attribute is also a table attribute.
				@return IPMUnknown pointer to the table attribute object or nil.
			*/
			virtual IPMUnknown*		CreateTableAttribute			() const = 0;
		
			/**	Creates a duplicate attribute and returns the given IID.
				@return IPMUnknown pointer to the attribute copy object or nil.
			*/
			virtual IPMUnknown*		DuplicateAttribute				(const PMIID& iid) const = 0;
			
			/**	Compare the two attributes by first checking that the classIDs are the same and
				then comparing the attribute values.  Returns true if equal else false
				@return kTrue if attributes are equal otherwise kFalse.
			*/
			virtual bool16			IsEqual							(const IPMUnknown* otherAttribute) const = 0;
		
			/**	Returns the class ID the attribute.
				@return attribute Class ID.
			*/
			virtual ClassID			GetClass						(void) const = 0;
			
			/**	Returns kTrue if attribute is observed by the transparency attribute suite.
				Should return kFalse, if plug-in that added the attribute is responsible for managing the changes.
				@return kTrue if attribute is observed by the transparency attribute suite; otherwise returns kFalse.
			*/
			virtual bool16			ObservedByTransparencyAttrSuite	(void) const = 0;

			/**	Returns the string format of the attribute value.
				@param attrClass IN: the ClassID for the attribute.
				@param ws IN: the workspace where we get this attribute value from.
				@return PMString the string format of the attribute value..
			*/
			virtual PMString        GetValue(const ClassID& attrClass, const IWorkspace* ws) const = 0;
		};
			
#endif // _IGraphicAttributeInfo_
