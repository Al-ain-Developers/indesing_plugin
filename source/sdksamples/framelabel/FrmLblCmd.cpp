//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblCmd.cpp $
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
// None.

// General includes:
#include "Command.h"
#include "ErrorUtils.h"
#include "IPageItemUtils.h"	 

// Project includes:
#include "IFrmLblData.h"
#include "FrmLblID.h"
#include "FrmLblType.h"

/** Stores persistent data to control the display of
	the frame label adornment; implements ICommand.

	@ingroup framelabel
*/
class FrmLblCmd : public Command
{
	public:
		/** Constructor.
		 * 	We initialize all the private members and pass the 
		 * 	boss pointer to the parent class (Command).
		 * 	@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		FrmLblCmd(IPMUnknown* boss);
		
		/** Destructor 
		 */
		virtual ~FrmLblCmd(void);

		/**	See Command::LowMemIsOk
		 * 	@return bool16 
		 */
		bool16 LowMemIsOK(void) const 
		{ return kFalse; }


	protected:

		/**	Execute the main behaviour of the command.
		 * 	The Do method is where all the action happens. In this case we just
		 * 	need to copy the information from the commands data interface to the 
		 * 	frames data interface.
		 * 	@see Command::Do
		 */
		virtual void Do(void);

		/**	Notify interested observers.
		 * 	In our case, we broadcast a change at the document level.
		 * 	@see Command::DoNotify 
		 */
		virtual void DoNotify(void);

		/** Report the name of the command
		 * 	@see Command::CreateName 
		*/
		virtual PMString* CreateName(void);

	private:
		
		/** The size of the property arrays */
		int32		fItemCount;	
};

CREATE_PMINTERFACE(FrmLblCmd, kFrmLblCmdImpl)

/*	Constructor
*/
FrmLblCmd::FrmLblCmd(IPMUnknown* boss) :
	Command(boss), 
	fItemCount(0)
{
}

/* Destructor
*/
FrmLblCmd::~FrmLblCmd(void)
{
}

/* Do
*/
void FrmLblCmd::Do(void)
{
	// Verify the length of the item list
	fItemCount = fItemList.Length();
	
	if (fItemCount == 0)
	{
		ASSERT_FAIL("FrmLblCmd::Do: empty item list");
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
		return;
	}
	
	InterfacePtr<IFrmLblData> commandData(this, UseDefaultIID());
	if (commandData == nil)
	{
		ASSERT_FAIL("LabelFrame::Do cannot get IFrmLblData for the command");
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
	}
	else
	{	
		const FrmLblInfo& frmLblInfo = commandData->Get();
		// Traverses all of the items in the list and change the IFrmLblData information
		// for each one:
		for(int32 frameCount = 0; frameCount < fItemCount; frameCount++)
		{
			InterfacePtr<IFrmLblData> frameData(fItemList.GetRef(frameCount), UseDefaultIID());
			if(frameData != nil)
			{
				//support mix-mode
				FrmLblInfo currFrmLblInfo = frameData->Get();
				if(fItemCount == 1)
				{
					currFrmLblInfo = frmLblInfo;
				}
				else
				{
					//Set the value in IFrmLblData only if the value is "valid". (mix-mode)

					if(frmLblInfo.label.empty() == kFalse)
					{
						currFrmLblInfo.label = frmLblInfo.label;
					}

					if(frmLblInfo.fontColor != kInvalidUID)
					{
						currFrmLblInfo.fontColor = frmLblInfo.fontColor;
					}

					if(frmLblInfo.position != kFrmLblPosNone)
					{
						currFrmLblInfo.position = frmLblInfo.position;
					}

					currFrmLblInfo.visibility = frmLblInfo.visibility;
				}

				// Change the settings for the current page item:
				frameData->Set(currFrmLblInfo);
			}	
		}
	}
}

/*	DoNotify
*/
void FrmLblCmd::DoNotify(void)
{
	if (fItemCount == 0)
	{
		ASSERT_FAIL("FrmLblCmd::DoNotify: empty item list");
		ErrorUtils::PMSetGlobalErrorCode(kFailure);
	}
	else
	{
		// For notfication we'll let PageItemUtils do the work.
		// We have to choose some type of change message, so use 
		// a location change to cause a redraw.
		Utils<IPageItemUtils>()->NotifyDocumentObservers
		(
			fItemList.GetDataBase(), 
			kLocationChangedMessage, 
			IID_ITRANSFORM_DOCUMENT, 
			this,
			nil /* nil cookie */
		);
	}
}

/*	CreateName
*/
PMString* FrmLblCmd::CreateName(void)
{
	// Core resource for string:
	PMString* string = new PMString(kFrmLblCmdStringKey);
	return string;
}

// End, FrmLblCmd.cpp.






