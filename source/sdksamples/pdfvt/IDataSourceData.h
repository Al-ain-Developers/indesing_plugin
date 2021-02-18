//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/IDataSourceData.h $
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

#ifndef __IDATASOURCEDATA_H
#define __IDATASOURCEDATA_H

#include "IPMUnknown.h"

#include <map>

#include "PDFVTID.h"

/** 
	From SDK sample; Interface to store persistent data to control the
	behavior of PDF/VT export process.

	@ingroup pdfvt

*/
class IDataSourceData : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IDATASOURCEDATA };	

	/**	Gets the path to the datasource file.
			@return path to the datasource file.
	*/
	virtual WideString GetPath() const = 0;	

	/** Sets the path to the datasource file.
			@param path path to the datasource file.
	*/
	virtual void SetPath(const WideString& path) = 0;

	/** Gets CIP4 metadata mapping.
			@return CIP4 metadata mapping.
	*/
	virtual const std::map<WideString, WideString>& GetCIP4Mapping() const = 0;

	/** Sets CIP4 metadata mapping.
			@param mapping CIP4 metadata mapping.
	*/
	virtual void SetCIP4Mapping(const std::map<WideString, WideString>& mapping) = 0;
};
#endif