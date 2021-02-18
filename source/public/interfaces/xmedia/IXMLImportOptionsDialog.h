//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportOptionsDialog.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IXMLImportOptionsDialog__
#define __IXMLImportOptionsDialog__

#include "IPMUnknown.h"
#include "XMediaUIID.h"

class IDocument;
//----------------------------------------------------------------------------------------
// IXMLImportOptionsDialog
//----------------------------------------------------------------------------------------

/** Interface that provides method to automatically build
	the XML import options dialog. Should be used in conjunction 
	with IXMLImportOptionsService
*/
class IXMLImportOptionsDialog : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLIMPORTOPTIONSDIALOG };

	/** Builds a dialog for the XML Import preferences
		This method will look at all service providers
		for kXMLImportUIService.
		@param doc - The document we are importing into
		@return - kSuccess if the dialog was exited correctly (OK)
				  kFailure if the dialog was wan't built successfully.
	*/
	virtual ErrorCode DoDialog(IDocument *doc) = 0;
};	

#endif // __IXMLImportOptionsDialog__
