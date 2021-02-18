//========================================================================================
//
//	File:	WRString.h
//
//	Author: dsvoboda
//
//	Date:	24-01-2005
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRString__
#define __WRString__

#include "WRConfig.h"
#include "WRDefines.h"
#include "WRClass.h"

class WRSERVICES_DECL WRString : public WRClass
{
public:
	
	WRString();
	
	WRString(const char *c_str, WRCodePage cp = kWRUTF8CodePage);
	
	WRString(const char *str, WRByteCount bytelen, WRCodePage cp = kWRUTF8CodePage);

	WRString(const WRUnichar16 *wc_str);
	
	WRString(const WRUnichar16 *wstr, WRCharCount len);

	WRString(const WRUnichar32 *wc_str);
	
	WRString(const WRUnichar32 *wstr, WRCharCount len);
	
	WRString(const WRString& inStr);
	
	void Assign(const char *c_str, WRCodePage cp = kWRUTF8CodePage);
	
	void Assign(const char *str, WRByteCount bytelen, WRCodePage cp);

	void Assign(const WRUnichar16 *wc_str);
		
	void Assign(const WRUnichar16 *wstr, WRCharCount len);

	void Assign(const WRUnichar32 *wc_str);
	
	void Assign(const WRUnichar32 *wstr, WRCharCount len);
	
	void Assign(const WRString& inStr);

	~WRString();
	
	void Append(const WRUnichar32 *wc_str);
	
	void Append(const WRUnichar32 *wstr, WRCharCount len);
	
	void Append(const WRString& wrstr);
	
	bool EndsWith(WRUnichar32 *wc_str) const;
	
	bool EndsWith(WRUnichar32 *wstr, WRCharCount len) const;
	
	bool EndsWith(const WRString& wrstr) const;
	
	WRCharCount GetCharLength(void) const;
	
	bool IsEmpty(void) const;
	
	const WRString& operator=(const WRString& inPath);
	
	void GetStringAsUTF8(char *str, WRByteCount& ioByteSize) const;

	void GetStringAsUTF16(WRUnichar16 *wstr, WRCharCount& ioCharSize) const;
	
	void GetStringAsUTF32(WRUnichar32 *wstr, WRCharCount& ioCharSize) const;

	void GetString8BitEncoded(char *str, WRByteCount& ioByteSize, WRCodePage cp) const;
	
	const char* GetConstUTF8Ptr(WRByteCount* outByteLen = NULL) const;
		
	const WRUnichar16* GetConstUTF16Ptr(WRCharCount* outCharLen = NULL) const; 

	const WRUnichar32* GetConstUTF32Ptr(WRCharCount* outCharLen = NULL) const;

	const char* GetConst8BitEncodedPtr(WRCodePage cp, WRByteCount* outByteLen = NULL) const;

	int operator==(const WRString& inStr) const { return BinaryCompare(inStr) == 0; }
	int operator!=(const WRString& inStr) const { return BinaryCompare(inStr) != 0; }


protected:

	int BinaryCompare(const WRString& inStr) const; // binary compare strictly

	void	DeleteInternalStorage();
	
	mutable WRUnichar32		*fInternalStorage;
	
	mutable char			*fTmpStorage;
	
	mutable WRUnichar16		*fTmpWStorage;
	
	mutable WRCharCount		fLength;
	
	mutable WRByteCount		fISAllocBytes;
	
	mutable WRByteCount		fTmpAllocBytes;
	
	mutable WRByteCount		fTmpWAllocBytes;
};


#endif //WRPath
