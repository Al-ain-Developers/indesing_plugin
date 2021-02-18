/*
 *  IHTMLPageItemAttributes.h
 *  HTMLPGT
 *
 *  Created by Dave Stephens on 9/23/11.
 *  Copyright 2011 Adobe Systems, Inc. All rights reserved.
 *
 */
//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IHTMLPageItemAttributes.h $
//  
//  Created by Dave Stephens on 9/23/11.
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2011 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IHTMLPageItemAttributes__
#define __IHTMLPageItemAttributes__

#include "IPMUnknown.h"

#include "HTMLPGTID.h"

/** IHTMLPageItemAttributes are a collection of attributes or options on the embedded HTML which are
 used for such things as deciding how the iframe that wraps the HTML is transformed in response to
 liquid layout rules. */
class IHTMLPageItemAttributes : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHTMLPAGEITEMATTRIBUTES};
	
	/** Set whether or not the dimensions of this HTML is intrinsically fixed.
	 @param isFixed [IN] true if dimensions are fixed, false if liquid.
	 */
	virtual void SetHasFixedDimensions(bool32 isFixed) = 0;

	/** Is this HTML a fixed size or is it liquid in nature such that if the parent div or iframe is resized,
		it can adapt its contents to fit the new dimensions? If it is fixed size, then we must scale the parent
		element. If it is not fixed size, we can resize the parent element.
	 @return true if it is fixed size and hence must be scaled. false if it is liquid in nature.
	*/
	virtual bool32 GetHasFixedDimensions() const = 0;
		
	/** Placed HTML comes into InDesign as a packaged file where the actual HTML file is embedded somewhere
		within the package. On HTML export, we need to build a relative POSIX path to the HTML file to use as the 'src' of
		an 'iframe'. This field helps us to do that. 
		@param relativePosixPath [IN] subpath within the placed package to the actual HTML file, relative to the uncompressed 
			package folder.
	 @return an ErrorCode (kSuccess if successful).
	 */
	virtual ErrorCode SetRelativeURIToHTMLFile(const WideString* relativePosixPath) = 0;
	
	/** Placed HTML comes into InDesign as a packaged file where the actual HTML file is embedded somewhere
		within the package. On HTML export, we need to build a relative path to the HTML file to use as the 'src' of
		an 'iframe'. This field helps us to do that. 
		@param relativePosixPath [OUT] a Posix subpath within the placed package to the actual HTML file, relative to the uncompressed 
			package folder.
	 */
	virtual void GetRelativeURIToHTMLFile(WideString& relativePosixPath) const = 0;
	
	/** A convenience function for clients so that they do not need to be updated if new data members are added
	 to this interface in the future. This function simply copies the data from the provided srcAttrs into
	 'this.'
	 @param srcAttrs [IN] The attributes to copy from
	 */
	virtual ErrorCode CopyFrom(IHTMLPageItemAttributes* srcAttrs) = 0;
};

#endif
