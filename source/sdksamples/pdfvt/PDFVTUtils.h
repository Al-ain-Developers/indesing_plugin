//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/PDFVTUtils.h $
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

#ifndef __PDFVTUTILS_H
#define __PDFVTUTILS_H

#include "IPMUnknown.h"
#include "WideString.h"

#include <string>
#include <sstream>
#include <queue>
#include <vector>

/** 
	From SDK sample; Utility class for PDFVT.

	@ingroup pdfvt
*/
class PDFVTUtils
{
public:

	typedef enum {
		kUTF16LE,
		kUTF16BE,
		kUTF8BOM,
		kUTF8NOBOM,
		kUnsupportedEncoding
	} Encoding;

	/** Converts an object of type T into a string.
		@param t IN Object of type T.
		@return String representation of object t.
	*/
	template<class T>
	static std::string ToString(const T& t)
	{
		return ToTString<T, char>(t);
	}

	/** Reads the datasource file and retrieves the key list.
		@param keyList OUT The key list in the datasource file.
		@param filePath IN Path to the datasource file.
	*/	
	static void GetDataSourceKeyList(std::vector<std::string>& keyList, const WideString& filePath);

	/** Reads and parses data from extenal datasource file.
		@param filePath IN Path to the datasource file.
		@param keyList OUT The key list in the datasource file.
		@param recordList OUT The record list in the data source file.
		@return kTrue if the datasource file is opened successfully, kFalse otherwise.
	*/
	static bool16 ReadDataSource(const WideString& filePath, std::vector<std::string>& keyList, std::queue<std::vector<std::string> >& recordList);		

	/** Detects the encoding of the given stream for the file.
		@param stream IN IPMStream for the file.
		@return File encoding.
	*/	
	static Encoding DetectEncoding(IPMStream* stream);

private:
	/** Reads a line of text.
		@param stream IN IPMStream for the file.
		@param line OUT The line of text read, in UTF-8 encoding.
		@param encoding IN The encoding of the file.
	*/
	static void GetLine(IPMStream* stream, std::string& line, Encoding encoding);
	
	/** Reads a line of UTF-16 encoded text.
		@param stream IN IPMStream for the file.
		@param line OUT The line of text read, in UTF-8 encoding.
	*/
	static void GetLineUTF16(IPMStream* stream, std::string& line);

	/** Reads a line of UTF-8 encoded text.
		@param stream IN IPMStream for the file.
		@param line OUT The line of text read, in UTF-8 encoding.
	*/
	static void GetLineUTF8(IPMStream* stream, std::string& line);

	/** Removes consecutive combinations of \r and \n.
		@param stream IN The file stream.
	*/
	static void StripCRsW(IPMStream* stream);

	/** Removes consecutive combinations of \r and \n.
		@param stream IN The file stream.
	*/
	static void StripCRs(IPMStream* stream);

	template<class T, class CharType>
	static std::basic_string<CharType> ToTString(const T& t)
	{
		std::basic_ostringstream<CharType> o;
		o << t;
		return o.str();
	}
};

#endif