//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicme/IBscMEInvertFacade.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __IBscMEInvertFacade__
#define __IBscMEInvertFacade__


#include "ILayoutUtils.h"
#include "BscMEID.h"

struct InvertOptions
{
	bool16 invertStories;
	bool16 changeTableDir;
	bool16 movePageItem;
	bool16 flipObjectAngle;
	DocPageBinding pageBinding;
	
	InvertOptions() : 
		invertStories(kTrue),
		changeTableDir(kTrue),
		movePageItem(kTrue),
		flipObjectAngle(kTrue),
		pageBinding(kRightToLeftBinding)
	{
	}
};

/** Facade interface provides methods to invert document.
 
 @ingroup basicme
*/
class IBscMEInvertFacade : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IBSCMEINVERTFACADE };
	
	/** Invert page items in document, can be used to convert a Roman document to Hebrew or Arabic
	 @param doc [IN] the document is to be invert
	 @param invertOptions [IN] invert options
	 */
	virtual void InvertDocument(IDocument* doc, const InvertOptions& invertOptions) = 0;

};

#endif