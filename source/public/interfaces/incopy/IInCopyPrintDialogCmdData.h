//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyPrintDialogCmdData.h $
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
//  The command data interface for the book printing command in K2.	
//  
//  Purpose:
//  The data interface for print dialog command in InCopy.	
//  
//========================================================================================

#pragma once
#ifndef __IInCopyPrintDialogCmdData__
#define __IInCopyPrintDialogCmdData__

#include "IPMUnknown.h"
#include "IInCopyLayoutPrintData.h"
#include "IInCopyGalleyPrintData.h"
#include "IInCopyGalleySettingData.h"
#include "IPrintData.h"
#include "UIDRef.h"

/** Data interface for kInCopyPrintDialogCmdBoss
*/
class IInCopyPrintDialogCmdData : public IPMUnknown
{
public:
	/** The type of panel displaying in the Print dialog */
	enum {
		kLayoutPanel		= 1,
		kGalleyPanel		= 0
	};

/**	Set method for IPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetPrintData(IPrintData *iPrintData) = 0;
	
/**	Set method for IInCopyLayoutPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetLayoutPrintData(IInCopyLayoutPrintData *iPrintData) = 0;

/**	Set method for IInCopyGalleyPrintData object pointer for dialog use
	@param iPrintData 
 */
	virtual void SetGalleyPrintData(IInCopyGalleyPrintData *iPrintData) = 0;
	
/**	Set method for IInCopyGalleySettingData object pointer for dialog use
	@param iData 
 */
	virtual void SetGalleySettingData(IInCopyGalleySettingData *iData) = 0;

/**	Set method for document UIDRef object to print
	@param docUIDRef 
 */
	virtual void SetDocUIDRef(const UIDRef& docUIDRef) = 0;

	
/**	Set method for which panel displaying in the print dialog
	@param panel kLayoutPanel, kGalleyPanel
 */
	virtual void SetCurrentPanel(const int32 panel) = 0;

/**	Set method for print dialog return code
	@param returnCode kSuccess or kCancel
 */
 	virtual void SetReturnCode(const ErrorCode returnCode) = 0;
	
/**	Set method if document has multi-story
	@param multi kTrue means the document has multi-story
 */
	virtual void SetMultiStories(const bool16 multi) = 0;

/**	Get method for IInCopyLayoutPrintData object pointer
	@param none
	@return IInCopyLayoutPrintData* 
 */
	virtual IInCopyLayoutPrintData* GetLayoutPrintData() const = 0;

/**	Get method for IPrintData object pointer
	@param none
	@return IPrintData* 
 */
	virtual IPrintData* GetPrintData() const = 0;
	
/**	Get method for IInCopyGalleyPrintData object pointer
	@param none
	@return IInCopyGalleyPrintData* 
 */
	virtual IInCopyGalleyPrintData* GetGalleyPrintData() const = 0;
	
/**	Get method for IInCopyGalleySettingData object pointer
	@param none
	@return IInCopyGalleySettingData* 
 */
	virtual IInCopyGalleySettingData* GetGalleySettingData() const = 0;

/**	Get method for document UIDRef object 
	@param none
	@return const the UIDRef of the document
 */
	virtual const UIDRef& GetDocUIDRef() const = 0;

	
/**	Get method for which panel currently displaying in the print dialog
	@param none
	@return int32 kLayoutPanel or kGalleyPanel
 */
	virtual int32 GetCurrentPanel() const = 0;

/**	Get method if document has multi-story
	@param none
	@return bool16 kTrue means the document has multi-story
 */
	virtual bool16 GetMultiStories() const = 0;

/**	Get method for print dialog return code
	@param none
	@return ErrorCode kSuccess or kCancel
 */
	virtual ErrorCode GetReturnCode() const = 0;
};

#endif // __IPrintBookCmdData__
