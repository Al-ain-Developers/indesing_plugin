//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLLoadDTDCmdData.h $
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
//  
//  Purpose: Data interface for the XMLLoadDTDCmd.  The XMLLoadDTDCmd allows you to specify
//  and import an external DTD for use in InDesign.
//  
//========================================================================================

#pragma once
#ifndef __IXMLLoadDTDCmdData__
#define __IXMLLoadDTDCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"

class IDocument;

/** Data interface for loading an external DTD.
*/
class IXMLLoadDTDCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLLOADDTDCMDDATA };

	/**	Specify the parameters necessary for loading a DTD.
		@param theDTD identifies the DTD file to load
		@param characterSize identifies the character size used by the DTD file.  Supported types are UTF-8, and UTF-16.
		@param theDocument identifies the document to import the DTD to.
	 */
	virtual void Set(const IDFile& theDTD, IDocument* theDocument) = 0;
	
	/**	Accessor for the DTD file to load.
		
		@return a reference to the DTD file.
	 */
	virtual const IDFile& GetDTDFile() const = 0;

	/**	Accessor for the target document.
		
		@return the target document.
	 */
	virtual IDocument* GetDocument() const = 0;
};

#endif
