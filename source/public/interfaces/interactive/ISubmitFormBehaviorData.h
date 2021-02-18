//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISubmitFormBehaviorData.h $
//  
//  Owner: Michael Brubidge
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2001 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#ifndef __ISubmitFormBehaviorData_h__
#define __ISubmitFormBehaviorData_h__

#include "BehaviorID.h"
#include "IBehaviorData.h"
#include "K2Vector.h"
#include "K2Pair.h"

//========================================================================================
// CLASS ISubmitFormBehaviorData
//========================================================================================

/** Data interface for Submit Form Behavior
	@see INamedPageItemList (for a way of getting candidates for SetFields()
*/
class ISubmitFormBehaviorData : public IBehaviorData
{
public:
	enum FormatConstants 
	{ 
		kPDFFormat, 
		kFDFFormat,		// Not implemented currently.
		kHTMLFormat,	// Not implemented currently.
		kXMLFormat		// Not implemented currently.
	};

	typedef int32 Format;
	
	/** Set format for submission (kFDFFormat, kHTMLFormat, kXMLFormat, or kPDFFormat ) */
	virtual void							SetFormat(const Format& format) = 0;

	/** Get format for submission (kFDFFormat, kHTMLFormat, kXMLFormat, or kPDFFormat ) */
	virtual Format							GetFormat() const = 0;
	
	/** Set URL for submission (/F in submit-form action dict) */
	virtual void							SetURL(const PMString& url) = 0;

	/** Get URL for submission (/F in submit-form action dict) */
	virtual PMString						GetURL() const = 0;
};

#endif // __ISubmitFormBehaviorData_h__

