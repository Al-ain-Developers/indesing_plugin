//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLConvertElementToTableCmdData.h $
//  
//  Owner: Matt Joss
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
#ifndef __IXMLConvertElementToTableCmdData__
#define __IXMLConvertElementToTableCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** Data interface Convert Element to Table Cmd
*/
class IXMLConvertElementToTableCmdData : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IXMLCONVERTELEMENTTOTABLECMDDATA };
	
	/**	Sets the data necessary for the XMLConvertElementToTableCmd command
	@param element the element to convert to a table
	@param tableRowTagName tag used to designate a table row in the elements structure
	@param tableCellTagName tag used to designate a table cell in the elements structure
	*/
	virtual void Set
					(
						const XMLReference& element,
						const WideString& tableRowTagName,
						const WideString& tableCellTagName
					) = 0;

	
	/**	@return the xml reference.
		*/
	virtual XMLReference GetXMLReference() const = 0;
	
	/**	@return the table row tag name.
		*/
	virtual WideString GetTableRowTagName() const = 0;
	
	/**	@return the table cell tag name.
		*/
	virtual WideString GetTableCellTagName() const = 0;
};

#endif //IXMLConvertElementToTableCmdData
