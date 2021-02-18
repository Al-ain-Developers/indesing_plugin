//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookPrintData.h $
//  
//  Owner: Yeming Liu
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
#ifndef __IBookPrintData__
#define __IBookPrintData__

#include "BookID.h"

class IPrintData;

/** Command data interface relating to printing book.
	@ingroup layout_book
	@see kBookSavePrintDataCmdBoss 
*/
class IBookPrintData : public IPMUnknown
{
	public:
		/** Default enum.
		*/
		enum { kDefaultIID = IID_IBOOKPRINTDATA };
	
		/**	All inclusive set method to initialize data members.
			@param sysFile IN the book file
			@param iPrintData IN the IPrintData being used
		 */
		virtual void Set(IDFile& sysFile, IPrintData* iPrintData) = 0;

		/**	Get the book file.
			@return IDFile containing the book file
		*/
		virtual IDFile GetBookFile() = 0;

		/**	Set method to set the book file.
			@param BookFile IN the book file
		 */
		virtual void SetBookFile(const IDFile& BookFile) = 0;

		/**	Get the IPrintData interface being used.
			@return IPrintData* the print data being used
		 */
		virtual IPrintData* GetPrintData() = 0;

		/**	Set the IPrintData that is being used.
			@param iPrintData pointer to the print data being used
		 */
		virtual void SetPrintData(IPrintData* iPrintData) = 0;
		
};

#endif //__IBookPrintData__