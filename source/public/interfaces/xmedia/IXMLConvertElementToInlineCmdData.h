//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLConvertElementToInlineCmdData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IConvertElementToInlineCmdData__
#define __IConvertElementToInlineCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "PMPoint.h"
#include "XMLReference.h"

/** Data interface Convert Element to Inline Cmd
*/
class IXMLConvertElementToInlineCmdData : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IXMLCONVERTELEMENTTOINLINECMDDATA };

	/**	Use this to create a rectangular inline with the specified dimensions
		@param xmlRef the element to convert to an inline.
		@param thePoint dimensions of the new inline
	*/
	virtual void Set(const XMLReference& xmlRef, const PMPoint& dimensions) = 0;

	/**	Use this to create a copy of the specified item as your inline.
		Dimensions will be the same as the copied element
		@param xmlRef the element to convert to an inline.
		@param frameToCopy UID of the frame you'd like to copy
		@param frameToCopy UID of the frame you'd like to copy
		@param retainExistingFrame if true and the element is already an inline, the existing frame will be used.  if false, existing frame will be deleted and copied frame used
	*/
	virtual void Set(const XMLReference& xmlRef, UID frameToCopy, bool16 retainExistingFrame) = 0;

	/**	@return the xml reference.
	*/
	virtual XMLReference GetXMLReference() const = 0;

	/**	@return the dimensions.
	*/
	virtual const PMPoint& GetDimensions() const = 0;

	/**	@return the frame to copy.
	*/
	virtual UID GetFrameToCopy() const = 0;

	/**	@return the Retain Existing Frame setting.
	*/
	virtual bool16 GetRetainExistingFrame() const = 0;

};

#endif //IConvertElementToInlineCmdData
