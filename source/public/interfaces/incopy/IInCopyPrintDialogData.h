//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyPrintDialogData.h $
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
//  Purpose:
//  The data interface for print dialog in InCopy.	
//  
//========================================================================================

#pragma once
#ifndef __IInCopyPrintDialogData__
#define __IInCopyPrintDialogData__

#include "IPMUnknown.h"
#include "IInCopyLayoutPrintData.h"
#include "IInCopyGalleyPrintData.h"
#include "IInCopyGalleySettingData.h"
#include "IPrintData.h"
#include "UIDRef.h"

/** Data interface for kInCopyPrintDialogBoss
*/
class IInCopyPrintDialogData : public IPMUnknown
{
public:
	/** The type of panel displaying in the Print dialog */
	enum {
		kLayoutPanel		= 0,
		kGalleyPanel		= 1
	};

/**	Set method for IInCopyLayoutPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetLayoutPrintData(IInCopyLayoutPrintData* iPrintData) = 0;

/**	Set method for IPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetPrintData(IPrintData* iPrintData) = 0;

/**	Set method for IInCopyGalleyPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetGalleyPrintData(IInCopyGalleyPrintData* iPrintData) = 0;

/**	set method for IInCopyGalleySettingData object pointer for dialog use
	@param iSettingData 
 */
	virtual void SetGalleySettingData(IInCopyGalleySettingData* iSettingData) = 0;

/**	Set method for document UIDRef object to print
	@param docUIDRef 
 */
	virtual void SetDocUIDRef(const UIDRef& docUIDRef) = 0;

/**	Set method for which panel displaying in the print dialog
	@param panel kLayoutPanel, kGalleyPanel
 */
	virtual void SetCurrentPanel(const int32 panel) = 0;

/**	Get method for IInCopyLayoutPrintData object pointer
	@return IInCopyLayoutPrintData* 
 */
	virtual IInCopyLayoutPrintData* GetLayoutPrintData() const = 0;

/**	Get method for IInCopyGalleyPrintData object pointer 
	@return IInCopyGalleyPrintData* 
 */
	virtual IInCopyGalleyPrintData* GetGalleyPrintData() const = 0;

/**	Get method for IInCopyGalleySettingData object pointer
	@return IInCopyGalleySettingData* 
 */
	virtual IInCopyGalleySettingData* GetGalleySettingData() const = 0;

/**	Get method for IPrintData object pointer 
	@return IPrintData* 
 */
	virtual IPrintData* GetPrintData() const = 0;

/**	Get method for document UIDRef object 
	@return const 
 */
	virtual const UIDRef& GetDocUIDRef() const = 0;

/**	Get method for which panel is currently displaying in the print dialog
	@return int32 kLayoutPanel or kGalleyPanel
 */
	virtual int32 GetCurrentPanel() const = 0;
};

#endif // __IInCopyPrintDialogData__
