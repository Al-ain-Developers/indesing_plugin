//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInCopyPDFExptDialogData.h $
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
//  The data interface for the pdf export dialog in InCopy.	
//  
//========================================================================================

#pragma once
#ifndef __IInCopyPDFExptDialogData__
#define __IInCopyPDFExptDialogData__

#include "IPMUnknown.h"
#include "IInCopyPDFExptLayoutData.h"
#include "IInCopyPDFExptGalleyData.h"
#include "IInCopyGalleySettingData.h"
#include "IPDFExportPrefs.h"

#include "UIDRef.h"

/** Dialog data interface for kInCopyPDFExptDialogBoss. Pass in other interface point for dialog to use and set the settings.
*/
class IInCopyPDFExptDialogData : public IPMUnknown
{
public:
	//galley or layout dialog panel flags
	enum {
		kLayoutPanel		= 0,
		kGalleyPanel		= 1
	};

/**	Set method to pass IInCopyPDFExptLayoutData interface pointer for dialog use and set the layout export settings
	@param iData 
 */
	virtual void SetLayoutData(IInCopyPDFExptLayoutData* iData) = 0;
	
/**	Set method to pass IInCopyPDFExptGalleyData interface pointer for dialog use and set the galley export settings
	@param iData 
 */
	virtual void SetGalleyData(IInCopyPDFExptGalleyData* iData) = 0;

/**	Set method to pass IInCopyGalleySettingData interface pointer for dialog use
	@param iSettingData 
 */
	virtual void SetGalleySettingData(IInCopyGalleySettingData* iSettingData) = 0;

/**	Set method for the current displayed panel in the dialog
	@param panel, 0 = layout panel, 1 = galley panel
 */
	virtual void SetCurrentPanel(const int32 panel) = 0;

/**	Set method to pass IPDFExportPrefs interface pointer for dialog use and set data
	@param iData 
 */
	virtual void SetExportPrefs(IPDFExportPrefs* iData) = 0;

/**	Get method for IInCopyPDFExptLayoutData interface pointer
	@param none
	@return IInCopyPDFExptLayoutData* 
 */
	virtual IInCopyPDFExptLayoutData* GetLayoutData() const = 0;

/**	Get method for IInCopyPDFExptGalleyData interface pointer
	@param none
	@return IInCopyPDFExptGalleyData* 
 */
	virtual IInCopyPDFExptGalleyData* GetGalleyData() const = 0;
	
/**	Get method for IInCopyGalleySettingData interface pointer 
	@param none
	@return IInCopyGalleySettingData* 
 */
	virtual IInCopyGalleySettingData* GetGalleySettingData() const = 0;
	
/**	Get method for IPDFExportPrefs object pointer
	@param none
	@return IPDFExportPrefs* 
 */
	virtual IPDFExportPrefs* GetExportPrefs() const = 0;

/**	Get the current displayed panel in the dialog, this would be the view to export
	@param none
	@return int32 0 = layout panel, 1  galley panel
 */
	virtual int32 GetCurrentPanel() const = 0;
};

#endif // __IInCopyPDFExptDialogData__
