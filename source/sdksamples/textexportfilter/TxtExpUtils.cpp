//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/textexportfilter/TxtExpUtils.cpp $
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

// General includes
#include "OMTypes.h"
#include "K2Assert.h"
#include "HelperInterface.h"
#include "CreateObject.h"

// Project includes
#include "TxtExpUtils.h"
#include "TxtExpID.h"

// static IIntData* fEncoding = nil; // GCC 4.0 complains fEncoding declared twice (extern and then static)


/* QueryTxtExpFileWriter (static)
*/
ITxtExpFileWriter* TxtExpUtils::QueryTxtExpFileWriter(ITxtExpFileWriter::Encoding encoding)
{
	ITxtExpFileWriter* writer = nil;
	PMIID iid(IID_ITXTEXPFILEWRITER);

	switch (encoding) 
	{
		case ITxtExpFileWriter::kTxtExpEncodingASCII:
			writer = static_cast<ITxtExpFileWriter*>(::CreateObject(kASCIIFileWriterBoss, iid));
			break;

		case ITxtExpFileWriter::kTxtExpEncodingUNICODE:
			writer = static_cast<ITxtExpFileWriter*>(::CreateObject(kUNICODEFileWriterBoss, iid));
			break;

		case ITxtExpFileWriter::kTxtExpEncodingShiftJIS:
			writer = static_cast<ITxtExpFileWriter*>(::CreateObject(kShiftJISFileWriterBoss, iid));
			break;

        case ITxtExpFileWriter::kTxtExpEncodingJIS:
			writer = static_cast<ITxtExpFileWriter*>(::CreateObject(kJISFileWriterBoss, iid));
			break;

		default:
			ASSERT_FAIL(FORMAT_ARGS("TxtExpUtils::QueryTxtExpFileWriter: encoding type (%d) not supported.", encoding));
			break;
	}
	
	return writer;
}

/* GetEncodingIntData (static)
*/
static IDThreading::ThreadLocal<IIntData*> tl_IntEncoding(nil);
IIntData* TxtExpUtils::GetEncodingIntData(bool16 bRelease)
{
    if (bRelease)
    {
        if (tl_IntEncoding.Get())
        {
            tl_IntEncoding.Get()->Release();
			tl_IntEncoding.Set(nil);
        }
    }
    else if (!tl_IntEncoding.Get())
    {
		// instantiate (construct) the IIntData object
        tl_IntEncoding.Set(static_cast<IIntData*>(CreateObject(kTxtExpFilterBoss, IID_IINTDATA)));
        ASSERT_MSG(tl_IntEncoding.Get(), "TxtExpUtils::GetEncodingIntData : tl_IntEncoding not created!"); 
    }
    return tl_IntEncoding.Get();
}


// definitions of constants
const int32 TxtExpUtils::kHankakuColumn =  0;
const int32 TxtExpUtils::kZenkakuColumn =  1;
const int32 TxtExpUtils::kNumKatakana   = 94;
const int32 TxtExpUtils::kKatakanaNotFound = -1;

const textchar TxtExpUtils::k_fKatakanaLookup[TxtExpUtils::kNumKatakana][2] = 
{
//	{hanakaku, zenkaku} offset for zenkaku
    { 0x0020, 0x8140 }, // single->dual byte space
	{ 0x00A1, 0x8142 },	// punctuation (maru)
	{ 0x00A2, 0x8175 }, // open kagikakko
	{ 0x00A3, 0x8176 }, // close kagikakko
	{ 0x00A4, 0x8141 }, // japanese comma
	{ 0x00A5, 0x8145 }, // dot
	{ 0x00B0, 0x815B }, // dash
	{ 0x00A7, 0x8340 }, // small 'a'
	{ 0x00B1, 0x8341 }, // 'a'
	{ 0x00A8, 0x8342 }, // small 'i'
	{ 0x00B2, 0x8343 }, // 'i'
	{ 0x00A9, 0x8344 }, // small 'u'
	{ 0x00B3, 0x8345 }, // 'u'
	{ 0x00AA, 0x8346 }, // small 'e'
	{ 0x00B4, 0x8347 }, // 'e'
	{ 0x00AB, 0x8348 }, // small 'o'
	{ 0x00B5, 0x8349 }, // 'o'
	{ 0x00B6, 0x834A }, // 'ka'
	{ 0xDEB6, 0x834B }, // 'ga'
	{ 0x00B7, 0x834C }, // 'ki'
	{ 0xDEB7, 0x834D }, // 'gi'
	{ 0x00B8, 0x834E }, // 'ku'
	{ 0xDEB8, 0x834F }, // 'gu'
	{ 0x00B9, 0x8350 }, // 'ke'
	{ 0xDEB9, 0x8351 }, // 'ge'
	{ 0x00BA, 0x8352 }, // 'ko'
	{ 0xDEBA, 0x8353 }, // 'go'
	{ 0x00BB, 0x8354 }, // 'sa'
	{ 0xDEBB, 0x8355 }, // 'za'
	{ 0x00BC, 0x8356 }, // 'shi'
	{ 0xDEBC, 0x8357 }, // 'ji'
	{ 0x00BD, 0x8358 }, // 'su'
	{ 0xDEBD, 0x8359 }, // 'zu'
	{ 0x00BE, 0x835A }, // 'se'
	{ 0xDEBE, 0x835B }, // 'ze'
	{ 0x00BF, 0x835C }, // 'so'
	{ 0xDEBF, 0x835D }, // 'zo'
	{ 0x00C0, 0x835E }, // 'ta'
	{ 0xDEC0, 0x835F }, // 'da'
	{ 0x00C1, 0x8360 }, // 'chi'
	{ 0xDEC1, 0x8361 }, // 'ji'
	{ 0x00AF, 0x8362 }, // small 'tsu'
	{ 0x00C2, 0x8363 }, // 'tsu'
	{ 0xDEC2, 0x8364 }, // 'zu'
	{ 0x00C3, 0x8365 }, // 'te;
	{ 0xDEC3, 0x8366 }, // 'de'
	{ 0x00C4, 0x8367 }, // 'to'
	{ 0xDEC4, 0x8368 }, // 'do'
	{ 0x00C5, 0x8369 }, // 'na'
	{ 0x00C6, 0x836A }, // 'ni'
	{ 0x00C7, 0x836B }, // 'nu'
	{ 0x00C8, 0x836C }, // 'ne'
	{ 0x00C9, 0x836D }, // 'no'
	{ 0x00CA, 0x836E }, // 'ha'
	{ 0xDECA, 0x836F }, // 'ba'
	{ 0xDFCA, 0x8370 }, // 'pa'
	{ 0x00CB, 0x8371 }, // 'hi'
	{ 0xDECB, 0x8372 }, // 'bi'
	{ 0xDFCB, 0x8373 }, // 'pi'
	{ 0x00CC, 0x8374 }, // 'fu'
	{ 0xDECC, 0x8375 }, // 'bu'
	{ 0xDFCC, 0x8376 }, // 'pu'
	{ 0x00CD, 0x8377 }, // 'he'
	{ 0xDECD, 0x8378 }, // 'be'
	{ 0xDFCD, 0x8379 }, // 'pe'
	{ 0x00CE, 0x837A }, // 'ho'
	{ 0xDECE, 0x837B }, // 'bo'
	{ 0xDFCE, 0x837C }, // 'po'
	{ 0x00CF, 0x837D }, // 'ma'
	{ 0x00D0, 0x837E }, // 'mi'
	{ 0x00D1, 0x8380 }, // 'mu'
	{ 0x00D2, 0x8381 }, // 'me'
	{ 0x00D3, 0x8382 }, // 'mo'
	{ 0x00AC, 0x8383 }, // small 'ya'
	{ 0x00D4, 0x8384 }, // 'ya'
	{ 0x00AD, 0x8385 },	// small 'yu'
	{ 0x00D5, 0x8386 }, // 'yu'
	{ 0x00AE, 0x8387 }, // small 'yo'
	{ 0x00D6, 0x8388 }, // 'yo'
	{ 0x00D7, 0x8389 }, // 'ra'
	{ 0x00D8, 0x838A }, // 'ri'
	{ 0x00D9, 0x838B }, // 'ru'
	{ 0x00DA, 0x838C }, // 're'
	{ 0x00DB, 0x838D }, // 'ro'
	{ 0x00DC, 0x838F },	// 'wa'
	{ 0x00DC, 0x838E }, // small 'wa' doesn't exist in hankaku
	{ 0x00B2, 0x8390 },	// classic 'yi' doesn't exist in hankaku
	{ 0x00B4, 0x8391 },	// classic 'ye' doesn't exist in hankaku
	{ 0x00A6, 0x8392 },	// 'wo'
	{ 0x00DD, 0x8393 }, // 'n'
	{ 0xDEB3, 0x8394 }, // 'vu'
	{ 0x00B6, 0x8395 }, // small 'ka' doesn't exist in hankaku
	{ 0x00B9, 0x8396 }, // small 'ke' doesn't exist in hankaku
	{ 0x0000, 0x0000 }	// end of list
};



/* FindKatakanaIndex
*/
int32 TxtExpUtils::FindKatakanaIndex(const textchar uc, const int32 lookAtWhichColumn)
{
	int32 index = kKatakanaNotFound;
	int32 i = 0;
	textchar tc = 0;

	if ((lookAtWhichColumn == kHankakuColumn) || 
		(lookAtWhichColumn == kZenkakuColumn)) 
	{
		do
		{
			tc = k_fKatakanaLookup[i][lookAtWhichColumn];
            if (uc == tc)
			{
				index = i;
			}
			i++;
		}while ((tc != 0) && (index == kKatakanaNotFound));
	}
	return index;
}


/* HankakuToZenkaku
*/
textchar TxtExpUtils::HankakuToZenkaku(const textchar uc, 
									   const TxtExpUtils::Modifier modifier)
{
	textchar rc = kTextChar_Null;
	textchar uc2 = kTextChar_Null;
	uchar hb = GETHIBYTE(uc);
	
	if (modifier==TxtExpUtils::None)
	{
		// HIBYTE should really be zero, or one of the modifiers - check here
		if ((hb != 0xDE) && (hb != 0xDF) && (hb != 0))
		{
			// check if the hibyte is nonZero, assume it's stuffed with a 
			// dakuten or a handakuten.
			ASSERT_FAIL("TxtExpUtils::HankakuToZenkaku : HIBYTE isn't a dakuten, handakuten or zero... proceeding with just LOBYTE.");
			uc2 = GETLOBYTE(uc);
		}
		else
		{
			// use as is
			uc2 = uc;
		}
	}
	else
	{ 
		uc2 =  (modifier == TxtExpUtils::Dakuten) ? 
				 MAKEBIGENDIANWORD(0xDE, GETLOBYTE(uc)) : 
				 MAKEBIGENDIANWORD(0xDF, GETLOBYTE(uc));
	}

	int32 index = FindKatakanaIndex(uc2, kHankakuColumn); 
	if (index != kKatakanaNotFound) 
	{
		// returning zenkaku
		rc = k_fKatakanaLookup[index][kZenkakuColumn];
	}
	return rc;
}


/* ZenkakuToHankaku
*/
textchar TxtExpUtils::ZenkakuToHankaku(const textchar uc,
									   TxtExpUtils::Modifier& modifier)
{
	textchar rc = kTextChar_Null;

	int32 index = FindKatakanaIndex(uc, kZenkakuColumn); 
	if (index != kKatakanaNotFound) 
	{
		// returning hankaku
		rc = k_fKatakanaLookup[index][kHankakuColumn];
	}
	uchar hb = GETHIBYTE(rc);
	modifier = (hb == 0xDE) ? TxtExpUtils::Dakuten :
				(hb == 0xDF) ? TxtExpUtils::Handakuten : 
								TxtExpUtils::None;
	
	return rc;
}



/// End, TxtExpUtils.cpp.


