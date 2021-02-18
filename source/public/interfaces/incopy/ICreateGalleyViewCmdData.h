//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/ICreateGalleyViewCmdData.h $
//  
//  Owner: Cindy Chen
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
//  Purpose:
//  The data interface for the print dialog in InDesign.	
//  
//========================================================================================

#pragma once
#ifndef __ICreateGalleyViewCmdData__
#define __ICreateGalleyViewCmdData__

#include "IPMUnknown.h"
#include "IInCopyGalleySettingData.h"
#include "UIDRef.h"

/** Command data interface. To set/get the data for command kCreatePrintGalleyViewCmdBoss (creating the view to print/PDF-export)
*/
class ICreateGalleyViewCmdData : public IPMUnknown
{
public:

/**	Set method to set IInCopyGalleySettingData interface pointer to fill the data from the constructed view
	@param iSettingData 
 */
	virtual void SetGalleySettingData(IInCopyGalleySettingData* iSettingData) = 0;

/**	Set method to set the document to print/PDF-export.
	@param docUIDRef 
 */
	virtual void SetDocUIDRef(const UIDRef& docUIDRef) = 0;

/**	Get method to get IInCopyGalleySettingData interface pointer with the data from the constructed view
	@param none
	@return IInCopyGalleySettingData* 
 */
	virtual IInCopyGalleySettingData* GetGalleySettingData() const = 0;

/**	Get method to get the document.
	@param none
	@return const 
 */
	virtual const UIDRef& GetDocUIDRef() const = 0;
};

#endif // __ICreateGalleyViewCmdData__
