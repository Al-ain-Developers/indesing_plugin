//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/Swap.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __SWAP__
#define __SWAP__


class ByteSwapReverse
{
public:
	static char SwapChar(char c)		
		{ return c; }
	static uint16 SwapInt16(uint16 i)	
		{ return (((i&0xFF)<<8) | (i>>8)); }
	static uint32 SwapInt32(uint32 i)	
		{ return (((i&0xff000000)>>24)
				| ((i&0x00ff0000)>>8)
				| ((i&0x0000ff00)<<8)
				| ((i&0x000000ff)<<24)); }
	
	static void SwapDouble(double &d)
		{
			uchar*  pLeft = (uchar *) &d;
			uchar*  pRight = (uchar *) (pLeft + sizeof(double) - 1);
			
			for ( unsigned int n = 0; n < (sizeof(double) / 2); n++ )
			{
				uchar temp = *pLeft;
				*pLeft = *pRight;
				*pRight = temp;
				++pLeft; --pRight;
			}
		}
};


#endif // __SWAP__
