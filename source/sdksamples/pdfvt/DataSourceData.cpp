//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/DataSourceData.cpp $
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

#include "VCPlugInHeaders.h"

#include "IPMStream.h"

#include <map>

#include "IDataSourceData.h"

using namespace std;

/** Stores persistent data to control the
	behavior of PDF/VT export process.

	@ingroup pdfvt

*/
class DataSourceData : public CPMUnknown<IDataSourceData>
{
public:
	/** Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	DataSourceData(IPMUnknown* boss);	

	/**	Gets the path to the datasource file.
		@return The path to the datasource file.
	*/
	virtual WideString GetPath() const;

	/** Sets the path of the datasource file.
		@param path The path to the datasource file.
	*/
	virtual void SetPath(const WideString& path);

	/** Gets CIP4 metadata mapping.
		@return CIP4 metadata mapping.
	*/
	virtual const map<WideString, WideString>& GetCIP4Mapping() const;

	/** Sets CIP4 metadata mapping.
		@param mapping CIP4 metadata mapping.
	*/
	virtual void SetCIP4Mapping(const map<WideString, WideString>& mapping);

	/** Saves persistently, reads persistent data.
	*/
	void ReadWrite(IPMStream* stream, ImplementationID implementation);

private:	
	/** path of the datasource file
	*/
	WideString fPath;

	/** CIP4 metadata mapping
	*/
	map<WideString, WideString> fCIP4Mapping;	
	
};

CREATE_PERSIST_PMINTERFACE(DataSourceData, kDataSourceDataImpl)

DataSourceData::DataSourceData(IPMUnknown* boss) : CPMUnknown<IDataSourceData>(boss),
	fPath(),
	fCIP4Mapping()
{

}

WideString DataSourceData::GetPath() const
{
	return fPath;
}

void DataSourceData::SetPath(const WideString& path)
{
	PreDirty();
	fPath.SetString(path);
}

const map<WideString, WideString>& DataSourceData::GetCIP4Mapping() const
{
	return fCIP4Mapping;
}

void DataSourceData::SetCIP4Mapping(const map<WideString, WideString>& mapping)
{
	PreDirty();
	fCIP4Mapping = mapping;
}

void DataSourceData::ReadWrite(IPMStream* stream, ImplementationID implementation)
{
	fPath.ReadWrite(stream);
	int32 size = static_cast<int32>(fCIP4Mapping.size());
	
	stream->XferInt32(size);
	if (stream->IsWriting())
	{
		map<WideString, WideString>::const_iterator it = fCIP4Mapping.begin();
		for (; it !=fCIP4Mapping.end(); it++)		
		{
			PMString tmpKey(it->first);
			PMString tmpValue(it->second);
			tmpKey.ReadWrite(stream);
			tmpValue.ReadWrite(stream);			
		}
	}
	else if (stream->IsReading())
	{
		for (int32 i = 0; i < size; i++)
		{
			PMString tmp;
			tmp.ReadWrite(stream);
			WideString key(tmp);
			tmp.ReadWrite(stream);			
			fCIP4Mapping[key] = WideString(tmp);
		}
	}
}
