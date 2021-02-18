//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblDataFacade.cpp $
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

// Interface includes:
#include "IClassIDData.h"
#include "ICommand.h"
#include "ILayoutTarget.h"
#include "IPageItemAdornmentList.h"
#include "IDocument.h"
#include "IPageItemBoundsList.h"
#include "IHierarchy.h"
#include "ILayoutUtils.h"
#include "IPageItemUtils.h"
#include "IBoolData.h"
#include "IWorkspace.h"

// General includes:
#include "CmdUtils.h"
#include "UIDList.h"

// Project includes:
#include "FrmLblID.h"
#include "IFrmLblData.h"
#include "IFrmLblDataFacade.h"
#include "FrmLblType.h"

class FrmLblDataFacade : public CPMUnknown<IFrmLblDataFacade>
{
public:
	/**
		Constructor.
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	FrmLblDataFacade(IPMUnknown*  boss) : CPMUnknown<IFrmLblDataFacade>(boss) {}

	/** 
		Destructor.
	*/
	virtual ~FrmLblDataFacade() {}

	/**	Get properties of the frame label on the selected items.
	 *	@param items IN The page items to get frame label properties from.
	 * 	@param frmLblInfo OUT The properties of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelProperties(const UIDList& items, FrmLblInfo& frmLblInfo);

	/**	Get properties of the frame label on the selected items.
	 *	@param item IN The page item to get frame label properties from.
	 * 	@param frmLblInfo OUT The properties of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelProperties(const UIDRef& item, FrmLblInfo& frmLblInfo);

	/**	Set the frame label properties on the selected item.
	 *	@param item IN The page item to set frame label properties.
	 * 	@param frmLblInfo IN The frame label properties.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode UpdateFrameLabelProperties(const UIDRef& item, const FrmLblInfo& frmLblInfo);

	/**	Set the frame label properties on the selected items.
	 *	@param items IN The page item to set frame label properties.
	 * 	@param frmLblInfo IN The frame label properties.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode UpdateFrameLabelProperties(const UIDList& items, const FrmLblInfo& frmLblInfo);
	
	/**	Get default setting of the frame label from workspace.
	 *	@param item IN The workspae that contains the default setting.
	 * 	@param frmLblInfo OUT The default setting of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelPreference(const UIDRef& workspace, FrmLblInfo& frmLblInfo);

	/**	Set default setting of the frame label to workspace.
	 *	@param item IN The workspae that contains the default setting.
	 * 	@param frmLblInfo IN The default setting of frame label.
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode SetFrameLabelPreference(const UIDRef& workspace, const FrmLblInfo& frmLblInfo);

	/**	Get preference of printing frame label or not.
	 *	@param workspace IN The workspace that contains the printing preference.
	 * 	@param value OUT kTrue the frame label will be printed, kFalse not..
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode GetFrameLabelPrintPreference(IWorkspace* workspace, bool16& value);

	/**	Set preference of printing frame label or not.
	 *	@param workspace IN The workspace that contains the printing preference.
	 * 	@param value IN kTrue the frame label will be printed, kFalse not..
	 * 	@return ErrorCode kSuccess if success, specific error code otherwise.
	 */
	virtual ErrorCode SetFrameLabelPrintPreference(IWorkspace* workspace, bool16 value);

private:

	/**	Invalidates the page item bounds cache since the page item's bounds have changed.
	 *	@param item IN The page item that has changed .
	 */
	void InvalidatePageItemCache(const UIDRef& item);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(FrmLblDataFacade, kFrmLblDataFacadeImpl)

/* GetFrameLabelProperties
*/

ErrorCode FrmLblDataFacade::GetFrameLabelProperties(const UIDRef& item, FrmLblInfo& frmLblInfo)
{
	return GetFrameLabelProperties(UIDList(item), frmLblInfo);
}

ErrorCode FrmLblDataFacade::GetFrameLabelProperties(const UIDList& items, FrmLblInfo& frmLblInfo)
{
	ErrorCode error = kFailure;
	do
	{
		if(items.Length() == 0)
		{
			break;
		}

		{
			//Get the frame label data from first selected frame.
			InterfacePtr<IFrmLblData> frameData(items.GetRef(0), UseDefaultIID());
			if (frameData == nil)
			{
				ASSERT_FAIL("The given item does not aggregate IFrmLblData");
				break;
			}
	 
			frmLblInfo = frameData->Get();
		}

		//User selects multiple frames (support mixed mode).
		for(int32 i = 1; i < items.Length(); ++i)
		{
			InterfacePtr<IFrmLblData> frameData(items.GetRef(i), UseDefaultIID());
			if (frameData == nil)
			{
				ASSERT_FAIL("The given item does not aggregate IFrmLblData");
				error = kFailure;
				break;
			}

			FrmLblInfo tmpInfo = frameData->Get();

			//Support mixed mode. 

			//Clear frmLblInfo.label if there is a different frame label string
			if(frmLblInfo.label != tmpInfo.label)
			{
				frmLblInfo.label.clear();
			}

			//Assign frmLblInfo.fontColor to kInvalidUID if there is a different frame label fontColor
			if(frmLblInfo.fontColor != tmpInfo.fontColor)
			{
				frmLblInfo.fontColor = kInvalidUID;
			}

			//Assign frmLblInfo.position to kFrmLblPosNone if there is a different frame label position
			if(frmLblInfo.position != tmpInfo.position)
			{
				frmLblInfo.position = kFrmLblPosNone;
			}

			//Assign frmLblInfo.visibility to kFalse if there is a different frame label visibility
			if(frmLblInfo.visibility != tmpInfo.visibility)
			{
				frmLblInfo.visibility = kFalse;
			}
		}

		error = kSuccess;

	} while (false);

	return error;
}

ErrorCode FrmLblDataFacade::GetFrameLabelPreference(const UIDRef& workspace, FrmLblInfo& frmLblInfo)
{
	ErrorCode error = kFailure;
	do
	{
		InterfacePtr<IFrmLblData> frameData(workspace, UseDefaultIID());
		if (frameData == nil)
		{
			ASSERT_FAIL("Invalid IFrmLblData in document preference");
			break;
		}

		frmLblInfo = frameData->Get();
		error = kSuccess;

	} while(kFalse);

	return error;
}

ErrorCode FrmLblDataFacade::SetFrameLabelPreference(const UIDRef& workspace, const FrmLblInfo& frmLblInfo)
{
	ErrorCode error = kFailure;
	do
	{
		// item list and settings information are ok, create the command.
		InterfacePtr<ICommand> labelCommand(CmdUtils::CreateCommand(kFrmLblCmdBoss));
		if (labelCommand == nil)
		{
			// For some reason we couldn't get our label command pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("FrmLblDataFacade::UpdateFrameLabel: labelCommand invalid");
			error = kFrmLblLabelCommandFailedErrorCode;
			break; // out of do-while
		}

		labelCommand->SetItemList(UIDList(workspace));

		InterfacePtr<IFrmLblData> labelData(labelCommand, UseDefaultIID());     
		if (labelData == nil)
		{
			// For some reason we couldn't get our label data pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("FrmLblDataFacade::UpdateFrameLabel: labelData invalid");
			error = kFrmLblLabelCommandFailedErrorCode;
			break; // out of do-while
		}

		// updating the attributes of the label
		labelData->Set(frmLblInfo);

		// Finally, the command is processed:
		error = CmdUtils::ProcessCommand(labelCommand);

		// Check for errors, issue warning if so:
		if (error != kSuccess)
		{
			error = kFrmLblLabelCommandFailedErrorCode;	
			break; // out of do-while
		}

	} while (false);

	return error;

}

/* UpdateFrameLabelProperties
*/
ErrorCode FrmLblDataFacade::UpdateFrameLabelProperties(const UIDRef& item, const FrmLblInfo& frmLblInfo)
{
	return UpdateFrameLabelProperties(UIDList(item), frmLblInfo);
}

ErrorCode FrmLblDataFacade::UpdateFrameLabelProperties(const UIDList& items, const FrmLblInfo& frmLblInfo)
{
	ErrorCode error = kFailure;
	do
	{
		// item list and settings information are ok, create the command.
		InterfacePtr<ICommand> labelCommand(CmdUtils::CreateCommand(kFrmLblCmdBoss));
		if (labelCommand == nil)
		{
			// For some reason we couldn't get our label command pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("FrmLblDataFacade::UpdateFrameLabel: labelCommand invalid");
			error = kFrmLblLabelCommandFailedErrorCode;
			break; // out of do-while
		}

		labelCommand->SetItemList(items);

		InterfacePtr<IFrmLblData> labelData(labelCommand, UseDefaultIID());     
		if (labelData == nil)
		{
			// For some reason we couldn't get our label data pointer, so assert and
			// issue a user warning and leave:
			ASSERT_FAIL("FrmLblDataFacade::UpdateFrameLabel: labelData invalid");
			error = kFrmLblLabelCommandFailedErrorCode;
			break; // out of do-while
		}

		// updating the attributes of the label
		labelData->Set(frmLblInfo);

		// Finally, the command is processed:
		error = CmdUtils::ProcessCommand(labelCommand);

		// Check for errors, issue warning if so:
		if (error != kSuccess)
		{
			error = kFrmLblLabelCommandFailedErrorCode;	
			break; // out of do-while
		}

		ClassID cmdClassID = kInvalidClass;
		UIDList adornmentCmdItems(items.GetDataBase());

		if (frmLblInfo.visibility == kTrue)
		{
			cmdClassID = kAddPageItemAdornmentCmdBoss;

			for(int32 i = 0; i < items.Length(); ++i)
			{
				bool16 doAddAdornment = kTrue;
				InterfacePtr<IPageItemAdornmentList> iPageItemAdornmentList(items.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
				if (iPageItemAdornmentList)
				{
					InterfacePtr<IAdornmentIterator> pIt(iPageItemAdornmentList->CreateIterator(IAdornmentShape::kAfterShape));	// Should match GetDrawOrderBits in FrmLblAdornment
					IPMUnknown* punkAdorn = nil;
					while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
					{
						InterfacePtr<IAdornmentShape> tShape(punkAdorn, UseDefaultIID());
						if (tShape==nil)
						{
							// nothing left in the list...
							break; // out of while-loop
						}
						// need to check whether the item already has the adornment
						if (::GetClass(tShape) == kFrmLblAdornmentBoss)
						{
							// adornment has already been added - nothing to do
							doAddAdornment = kFalse;
							break; // out of while-loop
						}
					}

					if(doAddAdornment)
					{
						adornmentCmdItems.Append(items.At(i));
					}
					else
					{
						// Invalidates the page item bounds cache since the page item's will changed.
						// IPageItemBoundsList will report assert message if not to do so.
						InvalidatePageItemCache(items.GetRef(i));
					}
				}
			}
		}
		else
		{
			cmdClassID = kRemovePageItemAdornmentCmdBoss;
			// now we don't want to see the adornment, so take it off all the items that already have it

			for(int32 i = 0; i < items.Length(); ++i)
			{
				bool16 doRemoveAdornment = kFalse;

				InterfacePtr<IPageItemAdornmentList> iPageItemAdornmentList(items.GetRef(i), IID_IPAGEITEMADORNMENTLIST);
				if (iPageItemAdornmentList)
				{
					InterfacePtr<IAdornmentIterator> pIt(iPageItemAdornmentList->CreateIterator(IAdornmentShape::kAfterShape));
					IPMUnknown* punkAdorn = nil;
					while (pIt && ((punkAdorn = pIt->GetNextAdornment()) != nil))
					{
						InterfacePtr<IAdornmentShape> tShape(punkAdorn, UseDefaultIID());
						if (tShape==nil)
						{
							// no page items left in the list...
							break; // out of while-loop
						}
						if (::GetClass(tShape) == kFrmLblAdornmentBoss)
						{
							// In this case, we remove the items with the adornment
							doRemoveAdornment = kTrue;
							break; // out of while-loop
						}
					}
				}

				if(doRemoveAdornment)
				{
					adornmentCmdItems.Append(items.At(i));
				}
			}
		}
		
		error = kSuccess;

		// add or remove the page item adornment. 
		//cmdClassID is kAddPageItemAdornmentCmdBoss if frmLblInfo.visibility is true, 
		//otherwise is kRemovePageItemAdornmentCmdBoss
		if(adornmentCmdItems.Length() > 0)
		{
			ASSERT(cmdClassID != kInvalidClass);
			InterfacePtr<ICommand>  cmd((ICommand*)::CreateObject(cmdClassID, IID_ICOMMAND));
			cmd->SetItemList(adornmentCmdItems);
			InterfacePtr<IClassIDData>  classIDData(cmd, UseDefaultIID());
			classIDData->Set(kFrmLblAdornmentBoss);
			error = CmdUtils::ProcessCommand(cmd);
		}

		InterfacePtr<IDocument> doc(items.GetDataBase(), items.GetDataBase()->GetRootUID(), UseDefaultIID());
		if(doc == nil)
		{
			ASSERT_FAIL("Invalid IDocument");
			break;
		}


		Utils<ILayoutUtils>()->InvalidateViews(doc);

	} while (false);

	return error;
}

void FrmLblDataFacade::InvalidatePageItemCache(const UIDRef& item)
{
	do 
	{
		InterfacePtr<IHierarchy> hier(item, UseDefaultIID());
		if(hier == nil)
		{
			ASSERT_FAIL("Invalid IHierarchy");
			break;
		}

		//Get this frame's parent
		InterfacePtr<IHierarchy> parent(hier->QueryParent());
		if(parent == nil)
		{
			break;
		}
		
		InterfacePtr<IPageItemBoundsList> itemBoundsList(parent, IID_IPAGEITEMBOUNDSLIST);
		//The itemBoundsList is nil if the parent is not kGroupItemBoss or kSpreadLayerBoss.
		if(itemBoundsList == nil)
		{
			break;
		}

		itemBoundsList->Invalidate(hier);

	} while(kFalse);
}

ErrorCode FrmLblDataFacade::GetFrameLabelPrintPreference(IWorkspace* workspace, bool16& value)
{
	InterfacePtr<IBoolData> iBoolData(workspace, IID_IFRMLBLPRINTBOOLDATA);
	if (iBoolData == nil)
	{
		ASSERT_FAIL("IID_IFRMLBLPRINTBOOLDATA is invalid");
		return kFailure;
	}

	value = iBoolData->Get();
	return kSuccess;
}

ErrorCode FrmLblDataFacade::SetFrameLabelPrintPreference(IWorkspace* workspace, bool16 value)
{
	ErrorCode result = kFailure;

	do {
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kFrmLblPrintPrefsCmdBoss));
		if(cmd == nil)
		{
			ASSERT_FAIL("IDialog is invalid");
			break;
		}

		cmd->SetItemList(UIDList(::GetUIDRef(workspace)));

		InterfacePtr<IBoolData> iBoolData(cmd, IID_IFRMLBLPRINTBOOLDATA);
		if(iBoolData == nil)
		{
			ASSERT_FAIL("FrmLblPrintPref is invalid");
			break;
		}
		iBoolData->Set(value);
		result = CmdUtils::ProcessCommand(cmd);	

	} while(false);

	return result;
}

