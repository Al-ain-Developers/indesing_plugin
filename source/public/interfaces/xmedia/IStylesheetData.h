//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IStylesheetData.h $
//  
//  Owner: Michael Burbidge
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
//  Purpose of Interface:
//  A non-persistent data interface that holds a file.
//  
//========================================================================================

#pragma once
#ifndef __IStylesheetData_h__
#define __IStylesheetData_h__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "PMString.h"
#include <vector>

	/**
	An interface that can be aggregated onto the import xml command boss to
	specify a style sheet and a set of style sheet parameters. The xml content
	is transformed using the style sheet and parameters before being handed to
	the xml import code.
	*/
class IStylesheetData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISTYLESHEETDATA };

	/**	Copy the data from other to this interface.
		@param other specifies where the data should be copied from.
	 */
	virtual void Copy(const IStylesheetData* other) = 0;
	
	/**	Specify the file path of the style sheet.
		@param theFile specifies an XSLT style sheet.
	 */
	virtual void SetFile(const IDFile& theFile) = 0;
	/**	Return the file path of the style sheet.
		@return Result is the file path of the style sheet.
	 */
	virtual const IDFile& GetFile() const = 0;
	
	/**	Specify the values for the style sheet parameters.
		@param parameters specifies a list of pairs where the first value in the pair
				in the pair is the name of the parameter and the second is the value.
	 */
	virtual void SetParameters(const std::vector< std::pair<PMString, PMString> >& parameters) = 0;
	/**	Return the list of style sheet parameters and their values.
		@return a list of pairs where the first value in the pair
				in the pair is the name of the parameter and the second is the value.
	 */
	virtual const std::vector< std::pair<PMString, PMString> > GetParameters() const = 0;
};

#endif // __IStyleSheetData_h__
