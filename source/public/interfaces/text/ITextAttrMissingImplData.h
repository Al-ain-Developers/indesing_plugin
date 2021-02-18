//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextAttrMissingImplData.h $
//  
//  Owner: Michael Burbdige
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
#ifndef __ITextAttrMissingImplData_h__
#define __ITextAttrMissingImplData_h__

#include "IPMUnknown.h"
#include "TextAttrID.h"

/** 
	This interface is used for wrapping attributes which may go missing if the plug-in that
	supplies them is missing. It controls the persistence of the attribute, how it is compared
	with other attributes, how it is copied from one AttributeBossList to another.
	@ingroup text_attr
*/
class ITextAttrMissingImplData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTATTRMISSINGIMPLDATA };

#if 0
		/** Initialize is used internally to set up the data of the object.
		*/
		virtual void Initialize() = 0;
#endif
		
		/** Treatment of wrapped attribute.
		*/
		enum MissingAttributeType {
			/** Central data management, not copied when missing.
			*/
			kTreatAsDefault = 0,	// Central data management, not copied when missing, ...
			/** Self-managed (no convert, no ref-index), copied when missing.
			*/
			kTreatAsBlackBox = 1	// Self-managed (no convert, no ref-index), copied when missing
			};
			
		/**	Initialize a blank new attribute. Use this form if you are reading the attribute
			in from disk.
			@param classId	the classID of the embedded attribute
			@param missingType	how to treat the attribute within the system (black box or not)
			@param dataLength length of serialized data in bytes
			@param adoptDataBuffer buffer containing serialized data for embedded attribute. This 
			pointer is adopted by the object, and will be deleted when the wrapper missing attribute
			is deleted.
		*/
		virtual void Set(const ClassID& classId, MissingAttributeType missingType, int16 dataLength, uchar* adoptDataBuffer) = 0;
		
		/**	Initialize a blank new attribute. Use this form if you have an instantiated attribute
			that needs to be wrapped.
			@param classId	the classID of the embedded attribute
			@param treatAsBlackBox	how to treat the attribute within the system (black box or not)
			@param adoptAttr pointer to the attribute to embed. This pointer is adopted by the 
			object, and will be deleted when the wrapper missing attribute is deleted.
		*/
		virtual void Set(const ClassID& classId, MissingAttributeType treatAsBlackBox, IPMUnknown *adoptAttr) = 0;

		/** Return the classID of the wrapped (embedded) attribute.
			@return ClassID 	the classID of the embedded attribute
		*/
		virtual ClassID GetClassID() const = 0;

		/** Return the number of bytes used for persisting the embedded attribute.
			@return int16 	sizeof the embedded attribute
		*/
		virtual int16 GetDataLength() const = 0;
		
		/** Return a buffer containing the last used persisted form of the attribute.
			@return uchar* 	the embedded attribute as a serialized buffer
		*/
		virtual const uchar* GetDataBuffer() const = 0;
		
		/** Return the embedded attribute as an instantiated object.
			This may return nil if the plug-in that supplied the attribute is missing.
			@param faceID			which interface of the attribute to return
			@return IPMUnknown* 	the embedded attribute
		*/
		virtual IPMUnknown *QueryEmbeddedAttribute(PMIID faceID = IID_IUNKNOWN) const = 0;
		
		/** Returns whether the attribute should be treated a "black box" attribute.
			Black box attributes are copied even if the plug-in is missing, are
			always ignored on open (no warning to the user on opening the doc with the
			plug-in missing), and the data for these objects will not be converted.
			@return 	kTrue if the attribute is a black box attribute
		*/
		virtual bool16 TreatAsBlackBox() const = 0;
};

#endif
