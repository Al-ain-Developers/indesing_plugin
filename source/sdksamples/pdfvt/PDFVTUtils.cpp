//========================================================================================
//
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/pdfvt/PDFVTUtils.cpp $
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

#include "unicode/ucsdet.h"
#include "FileUtils.h"
#include "StreamUtil.h"
#include "StringUtils.h"

#include <string>
#include <vector>
#include "boost/algorithm/string.hpp"

#include "PDFVTUtils.h"

using namespace std;

void PDFVTUtils::GetDataSourceKeyList(vector<string>& keyList, const WideString& filePath)
{
    keyList.clear();
    IDFile dataSourceFile = FileUtils::PMStringToSysFile(filePath);
    
    InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(dataSourceFile));
    if (stream)
    {
		PDFVTUtils::Encoding fileEncoding = DetectEncoding(stream);

		stream->Seek(0, kSeekFromStart);
       
#if IS_LITTLE_ENDIAN_ARCH
		stream->SetSwapping(fileEncoding == kUTF16BE);
#else
        stream->SetSwapping(fileEncoding == kUTF16BE);
#endif
		
		switch (fileEncoding)
		{
		case kUTF16BE:
		case kUTF16LE:
			stream->Seek(2, kSeekFromCurrent);

			break;
		case kUTF8BOM:
			stream->Seek(3, kSeekFromCurrent);		
			break;

		default:
			break;
		}

		string s;
		GetLine(stream, s, fileEncoding);
				
		boost::split(keyList, s, boost::is_any_of(","));
		stream->Close();
    }	
}

bool16 PDFVTUtils::ReadDataSource(const WideString& filePath, vector<string>& keyList, queue<vector<string> >& recordList)
{
	bool16 result = kFalse;

	IDFile dataSourceFile = FileUtils::PMStringToSysFile(filePath);
    
    InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamRead(dataSourceFile));
    if (stream)
    {
		PDFVTUtils::Encoding fileEncoding = DetectEncoding(stream);

		stream->Seek(0, kSeekFromStart);
       
#if IS_LITTLE_ENDIAN_ARCH
		stream->SetSwapping(fileEncoding == kUTF16BE);
#else
        stream->SetSwapping(fileEncoding == kUTF16BE);
#endif

		switch (fileEncoding)
		{
		case kUTF16BE:
		case kUTF16LE:
			stream->Seek(2, kSeekFromCurrent);
			break;

		case kUTF8BOM:
			stream->Seek(3, kSeekFromCurrent);
			break;

		default:
			break;
		}

		string s;
		GetLine(stream, s, fileEncoding);

		boost::split(keyList, s, boost::is_any_of(","));

		while (stream->GetStreamState() != kStreamStateEOF)
		{
			GetLine(stream, s, fileEncoding);
			
			vector<string> record;
			boost::split(record, s, boost::is_any_of(","));
			recordList.push(record);
		}

		stream->Close();
		result = kTrue;
    }

	return result;	
}

PDFVTUtils::Encoding PDFVTUtils::DetectEncoding(IPMStream* stream)
{
	Encoding encoding = kUnsupportedEncoding;
	if (stream)
	{
		const int32 kBufferSize = 4096;
		const int32 streamSize = stream->Seek(0, kSeekFromEnd);
		const int32 bufferSize = streamSize < kBufferSize ? streamSize : kBufferSize;

		stream->Seek(0, kSeekFromStart);

		std::vector<uchar> buffer(bufferSize, 0);
		stream->XferByte(&buffer[0], bufferSize);

		UErrorCode status = U_ZERO_ERROR;
		UCharsetDetector* detector = ucsdet_open(&status);
		ucsdet_setText(detector, reinterpret_cast<const char*>(&buffer[0]), static_cast<int32_t>(buffer.size()), &status);

		const UCharsetMatch* match = ucsdet_detect(detector, &status);
		const char* detectedEncoding = ucsdet_getName(match, &status);
		if (!U_FAILURE(status))
		{
			string detectedEnc(detectedEncoding);
			boost::to_upper(detectedEnc);
			
			if (detectedEnc == "UTF-8")
			{
				encoding = kUTF8NOBOM;
				if (buffer[0] == 0xEF && buffer[1] == 0xBB && buffer[2] == 0xBF)
				{
					encoding = kUTF8BOM;
				}
			}
			else if (detectedEnc == "UTF-16BE")
			{
				encoding = kUTF16BE;
			}
			else if (detectedEnc == "UTF-16LE")
			{
				encoding = kUTF16LE;
			}
			else if (detectedEnc == "ISO-8859-1")
			{
				encoding = kUTF8NOBOM;
			}
		}

		ucsdet_close(detector);
	}
	return encoding;
}

void PDFVTUtils::GetLine(IPMStream* stream, std::string& line, Encoding encoding)
{
	switch (encoding)
	{
	case kUTF16BE:
	case kUTF16LE:
		GetLineUTF16(stream, line);
		break;

	case kUTF8BOM:
	case kUTF8NOBOM:
		GetLineUTF8(stream, line);
		break;

	default:
		break;
	}
}

void PDFVTUtils::GetLineUTF16(IPMStream* stream, std::string& utf8Line)
{
	utf8Line.clear();

    PMString line;
    
    int16 oneChar(0);
    textchar surrogateBuffer = 0;
    stream->XferInt16(oneChar);
    
    while (stream->GetStreamState() != kStreamStateEOF)
    {        
        const textchar ch = static_cast<textchar>(oneChar);
        if (ch == kTextChar_CR || ch == kTextChar_LF)
        {
            StripCRsW(stream);
            break;
        }
        if (UnicodeClass::IsHighSurrogate(ch))
        {
            surrogateBuffer = ch;
        }
        else if (surrogateBuffer && UnicodeClass::IsLowSurrogate(ch))
        {
            UTF16TextChar surrogate[2];
            surrogate[0] = surrogateBuffer;
            surrogate[1] = ch;
            line.AppendW(surrogate, 1);
            surrogateBuffer = 0;
        }
        else
        {
            surrogateBuffer = 0;
            line.AppendW(ch);
        }
        stream->XferInt16(oneChar);
    }	

    WideString ws(line);    
    StringUtils::ConvertWideStringToUTF8(ws, utf8Line);
}

void PDFVTUtils::GetLineUTF8(IPMStream* stream, std::string& utf8Line)
{
	utf8Line.clear();		

	uchar oneByte(0);

	stream->XferByte(oneByte);

	while (stream->GetStreamState() != kStreamStateEOF)
	{
		if (oneByte == 0x0D || oneByte == 0x0A)
		{
			StripCRs(stream);
			break;
		}
		utf8Line.append(1, static_cast<char>(oneByte));
		stream->XferByte(oneByte);
	}
}

void PDFVTUtils::StripCRsW(IPMStream* stream)
{
	int16 oneChar(0);
	stream->XferInt16(oneChar);
	while (stream->GetStreamState() != kStreamStateEOF)
	{
		if (static_cast<uint16>(oneChar) != kTextChar_CR && static_cast<uint16>(oneChar) != kTextChar_LF)
        {
		    stream->Seek(-2, kSeekFromCurrent);
			break;
        }
        stream->XferInt16(oneChar);
	}
}

void PDFVTUtils::StripCRs(IPMStream* stream)
{
	uchar oneByte(0);
	stream->XferByte(oneByte);	
	while (stream->GetStreamState() != kStreamStateEOF)
	{
		if (oneByte != 0x0D && oneByte != 0x0A)
		{
			stream->Seek(-1, kSeekFromCurrent);
			break;
		}
		stream->XferByte(oneByte);
	}
}
