//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/IXCatHndParsingContext.h $
//  
//  Owner: Ian Paterson
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
#ifndef __IXCatHndParsingContext_h__
#define __IXCatHndParsingContext_h__

#include "IPMUnknown.h"
#include "XCatHndID.h"

/** Stores state that we need during parsing.
	@see kXMLParserLocatorBoss.

	@ingroup xmlcataloghandler
*/
class IXCatHndParsingContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXCATHNDPARSINGCONTEXT }; 

		/**	Change the xml:base stored in this
			@param base 
		 */
		virtual void SetCurrentXmlBase(const WideString& base)=0;

		/**	Get xml:base stored
			@param none
			@return WideString 
		 */
		virtual WideString GetCurrentXmlBase()  const =0;

	
};

#endif // __IXCatHndParsingContext_h__


