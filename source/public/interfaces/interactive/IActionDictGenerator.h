//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/IActionDictGenerator.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IActionDictGenerator_h__
#define __IActionDictGenerator_h__

#include "IPMUnknown.h"
#include "InteractivePDFID.h"
#include "BehaviorTypes.h"

class IBehaviorData;

//========================================================================================
// CLASS IActionDictGenerator
//========================================================================================

/** Base data interface for all behavior bosses
	Each behavior has an implementation of this interface
	that has a method to generate PDF for the behavior.
	Called by IFormsPort to generate PDF for actions.
	@see MovieActionDictGenerator, IFormsPort
*/
class IActionDictGenerator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IACTIONDICTGENERATOR };

	/** Generate a CosObj that is an action dictionary
		@param port An IFormsPort, an interface on the IPDFDocPort
		@param exportFile The PDF file being generated
		@param document Document being exported, used to create new dict with PDFLib (cos)
		@param behaviorData Interface on behavior being generated
		@return Action dictionary in CosObj form (should least contain keys: /Type ( == /Action), /S ( == /<actionsubtype>)
		
	*/
	virtual CosObj	Generate(IPMUnknown* port, const IDFile& exportFile, CosDoc document, IBehaviorData* behaviorData, CosObj field, ActionEvent event) const = 0;
};

#endif // __IActionDictGenerator_h__
