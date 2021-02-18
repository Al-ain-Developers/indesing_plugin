//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/IFrmLblDataFacade.h $
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

#ifndef __IFrmLblDataFacade_h__
#define __IFrmLblDataFacade_h__

// Interface includes:
#include "IPMUnknown.h"

// General includes:

// Project includes:
#include "FrmLblID.h"

// Forward declarations
class PMString;
class PMReal;
class UIDRef;
struct FrmLblInfo;

/** A facade that provides useful manipulations of IFrmLblData and IID_IFRMLBLPRINTBOOLDATA.

	@ingroup framelabel
*/
class IFrmLblDataFacade : public IPMUnknown
{
public:

	enum	{kDefaultIID = IID_FRMLBLDATAFACADE};

	/**	Get properties of the frame label on the selected items.
	 *	@param items IN The page items to get frame label properties from.
	 * 	@param frmLblInfo OUT The properties of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelProperties(const UIDList& items, FrmLblInfo& frmLblInfo) = 0;

	/**	Get properties of the frame label on the selected items.
	 *	@param item IN The page item to get frame label properties from.
	 * 	@param frmLblInfo OUT The properties of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelProperties(const UIDRef& item, FrmLblInfo& frmLblInfo) = 0;

	/**	Set the frame label properties on the selected item.
	 *	@param item IN The page item to set frame label properties.
	 * 	@param frmLblInfo IN The frame label properties.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode UpdateFrameLabelProperties(const UIDRef& item, const FrmLblInfo& frmLblInfo) = 0;

	/**	Set the frame label properties on the selected items.
	 *	@param items IN The page item to set frame label properties.
	 * 	@param frmLblInfo IN The frame label properties.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode UpdateFrameLabelProperties(const UIDList& items, const FrmLblInfo& frmLblInfo) = 0;
	
	/**	Get default setting of the frame label from workspace.
	 *	@param item IN The workspae that contains the default setting.
	 * 	@param frmLblInfo OUT The default setting of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelPreference(const UIDRef& workspace, FrmLblInfo& frmLblInfo) = 0;

	/**	Set default setting of the frame label to workspace.
	 *	@param item IN The workspae that contains the default setting.
	 * 	@param frmLblInfo IN The default setting of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode SetFrameLabelPreference(const UIDRef& workspace, const FrmLblInfo& frmLblInfo) = 0;

	/**	Get preference of printing frame label or not.
	 *	@param workspace IN The workspace that contains the printing preference.
	 * 	@param value OUT kTrue the frame label will be printed, kFalse not..
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelPrintPreference(IWorkspace* workspace, bool16& value) = 0;

	/**	Set preference of printing frame label or not.
	 *	@param workspace IN The workspace that contains the printing preference.
	 * 	@param value IN kTrue the frame label will be printed, kFalse not..
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode SetFrameLabelPrintPreference(IWorkspace* workspace, bool16 value) = 0;
};

#endif // __IFrmLblDataFacade_h__

