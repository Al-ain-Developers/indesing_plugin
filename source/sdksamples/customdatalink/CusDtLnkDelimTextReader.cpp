//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkDelimTextReader.cpp $
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

// Interface includes:
#include "ICusDtLnkDelimTextReader.h"
#include "IPMStream.h"

// Implementation includes:
#include "CPMUnknown.h"
#include <string>
#include <vector>

#ifndef BOOST_SPIRIT_THREADSAFE
#define BOOST_SPIRIT_THREADSAFE
#endif

#include <boost/spirit/include/classic_core.hpp>
#include <boost/spirit/include/classic_confix.hpp>

using namespace std;
using namespace boost::spirit::classic;

/** Spirit parser framework semantic action class. 
	This functor filters out escaped '"', 
	which are represented as double double-quotes.
	@ingroup customdatalink
*/
class CusDtLnkFilteredAppend
{
public:
	CusDtLnkFilteredAppend(vector<string>& fields) : fFields(fields) { }
	void operator()(string const& str) const { fFields.insert(fFields.end(), strip_escaped_chars(str)); }
	void operator()(const char* first, const char* last) const { fFields.insert(fFields.end(), strip_escaped_chars(string(first, last))); }

private:
	string strip_escaped_chars(const string& input) const;
	vector<string>& fFields;
};

/*
*/
string CusDtLnkFilteredAppend::strip_escaped_chars(const string& input) const
{
	string output;
	
	bool escape_started = false;
	for (string::const_iterator i = input.begin(); i != input.end(); i++)
	{
		if (escape_started)
		{
			if (*i != '"')
				output.push_back(*i);				
			escape_started = false;
		}
		else
		{
			if (*i == '"')
				escape_started = true;
			output.push_back(*i);				
		}
	}
	
	return output;
}

/** Implementation of ICusDtLnkDelimTextReader to read
	comma-separated values, including enquoted values
	@ingroup customdatalink
*/
class CusDtLnkDelimTextReader : public CPMUnknown<ICusDtLnkDelimTextReader>
{
public:
	/** Constructor 
		@param boss
	*/
	CusDtLnkDelimTextReader(IPMUnknown *boss);
	
	/**
	*/
	virtual ~CusDtLnkDelimTextReader();


	/** Determine if we can read a row of our database from the given
		stream
		@param stream where to read from
		@return kTrue if we can read at least one record, kFalse otherwise
	*/
	virtual bool16 CanRead(IPMStream* stream);

	/**	Read a record from our notional database, i.e.
		read a complete row from the stream

		@param stream where to read from
		@param outputFields list of values we read
		@return bool kTrue if OK, kFalse otherwise
	 */
	virtual bool16 ReadRecord(IPMStream* stream, K2Vector<PMString>& outputFields) const;

private:	
	/** Read a line from the stream into buffer */
	bool16 readLine(char* buffer, int32 buffer_len, IPMStream* stream) const;
	/** Parse a buffer of data into distinct fields */
	bool16 parseLine(char* buffer, vector<string>& fields) const;
};


CREATE_PMINTERFACE(CusDtLnkDelimTextReader, kCusDtLnkDelimTextReaderImpl)

/*
*/
CusDtLnkDelimTextReader::CusDtLnkDelimTextReader(IPMUnknown *boss) :
	CPMUnknown<ICusDtLnkDelimTextReader>(boss)
{
}

/*
*/
CusDtLnkDelimTextReader::~CusDtLnkDelimTextReader()
{
}

/*
*/
bool16 CusDtLnkDelimTextReader::CanRead(IPMStream* stream)
{
	ASSERT(stream);
	if(!stream) {
		return kFalse;
	}
	bool16 canRead = kFalse;
	// make sure we are looking at start of stream
	stream->Seek(0, kSeekFromStart);
	K2Vector<PMString>	record;
	// Can we read a vector of some kind from the stream
	if (this->ReadRecord(stream, record)) {
		canRead = kTrue;
	}
	// reset stream to start
	stream->Seek(0, kSeekFromStart);
	
	return canRead;

}

/*
*/
bool16 CusDtLnkDelimTextReader::ReadRecord(IPMStream* stream, K2Vector<PMString>& outputFields) const
{
	ASSERT(stream);
	if(!stream) {
		return kFalse;
	}
	char buffer[4096];
	bool16 retval = kFalse;
	vector<string> fields;
	if (readLine(buffer, 4096, stream)) {
		retval =  parseLine(buffer, fields);
		// Convert back out to ID type system
		outputFields.clear();
		vector<string>::const_iterator iter = fields.begin();
		for(; iter != fields.end(); iter++) {
			PMString pmStr(iter->c_str());
			pmStr.SetTranslatable(kFalse);  // the data we read from the data file is non-translatable.
			outputFields.push_back(pmStr);
		}
	}
	return retval;
}

/*
*/
bool16 CusDtLnkDelimTextReader::readLine(char* buffer, int32 buffer_len, IPMStream* stream) const
{
	ASSERT(stream);
	if(!stream) {
		return kFalse;
	}
	ASSERT(stream->IsReading());
	ASSERT(stream->GetStreamState() == kStreamStateGood);
	
	unsigned char ch = 0;
	
	int32 bytes_read = 0;
	buffer[bytes_read++] = stream->XferByte(ch);
	while(stream->GetStreamState() == kStreamStateGood && bytes_read < buffer_len)
	{
		// Unix end-of-line.
		if (ch == 0xA)
			break;
		
		// Dos and Mac end-of-line.
		if (ch == 0xD)
		{
			ch = stream->XferByte(ch);
			if (ch != 0xA) {
				stream->Seek(-1, kSeekFromCurrent);
			}
			break;
		}
		
		buffer[bytes_read++] = stream->XferByte(ch);
	}
	
	if (buffer[bytes_read-1] == 0xD || buffer[bytes_read-1] == 0xA) {
		bytes_read--;
	}
	buffer[bytes_read] = 0;
	
	ASSERT(bytes_read <= buffer_len);
	
	return stream->GetStreamState() == kStreamStateGood;
}

/*
*/
bool16 CusDtLnkDelimTextReader::parseLine(char* buffer, vector<string>& fields) const
{
	// See http://www.boost.org/libs/spirit/doc/faq.html
	rule<phrase_scanner_t> field, quoted_data, data, record;
	
	record
		= 	field >> +(ch_p(',') >> field)
		;
		
	field
		=	quoted_data
		| 	data
		;
		
	quoted_data
		=	confix_p(ch_p('\"'), (*(anychar_p - '"' | str_p("\"\"")))[CusDtLnkFilteredAppend(fields)], ch_p('\"'))
		;
		
	data
		= 	(*(anychar_p - ch_p(',')))[CusDtLnkFilteredAppend(fields)]
		;
	
	
	return parse(buffer, record, space_p).full;
}
