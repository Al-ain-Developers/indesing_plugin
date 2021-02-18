//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvIdleTask.cpp $
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

// interface includes
#include "IApplication.h"
#include "IMenuManager.h"
#include "IActionManager.h"
#include "IIdleTaskMgr.h"
#include "ITreeViewMgr.h"
#include "IControlView.h"
#include "IPnlTrvDataModel.h"

// General includes:
#include "PnlTrvUtils.h"
#include "CIdleTask.h"

// Project includes
#include "PnlTrvID.h"

const static int kPnlTrvExecInterval = 30*1000; // 30 seconds, as we specify milliseconds between checks	
// Refresh  in case we add new images


/** Implements IIdleTask, to refresh the view onto the file system.
	Just lets us keep up to date when people add new assets.
	This implementation isn't too respectful; it just clears the tree and calls ChangeRoot.

	
	@ingroup paneltreeview
*/

class PnlTrvIdleTask : public CIdleTask
{
public:

	/**	Constructor
		@param boss boss object on which this interface is aggregated
	*/
	PnlTrvIdleTask(IPMUnknown* boss);

	/**	Destructor
	*/
	virtual ~PnlTrvIdleTask() {}


	/**	Called by the idle task manager in the app core when the task is running
		@param appFlags [IN] specifies set of flags which task can check to see if it should do something
			this time round
		@param timeCheck [IN] specifies how many milliseconds before the next active task becomes overdue.
		@return uint32 giving the interval (msec) that should elapse before calling this back
	 */
	virtual uint32 RunTask(uint32 appFlags, IdleTimer* timeCheck);

	/**	Get name of task
		@return const char* name of task
	 */
	virtual const char* TaskName();
protected:

	/**	Update the treeview.
	 */
	void refresh();
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvIdleTask, kPnlTrvIdleTaskImpl)


/* Constructor
*/
PnlTrvIdleTask::PnlTrvIdleTask(IPMUnknown *boss)
	:CIdleTask(boss)
{
}


/* RunTask
*/
uint32 PnlTrvIdleTask::RunTask(
	uint32 appFlags, IdleTimer* timeCheck)
{
	if( appFlags & 
		( IIdleTaskMgr::kMouseTracking 
		| IIdleTaskMgr::kUserActive 
		| IIdleTaskMgr::kInBackground 
		| IIdleTaskMgr::kMenuUp))
	{
		return kOnFlagChange;
	}
	
	this->refresh();

	// Has FS changed?
	return kPnlTrvExecInterval;
}


/* TaskName
*/
const char* PnlTrvIdleTask::TaskName()
{
	return kPnlTrvIdleTaskKey;
}


/* refresh
*/
void PnlTrvIdleTask::refresh()
{
	do
	{
		IControlView* treeWidget = 
			PnlTrvUtils::GetWidgetOnPanel(kPnlTrvPanelWidgetID, kPnlTrvTreeViewWidgetID);
		// Don't assert, fail silently, the tree view panel may be closed.
		if(!treeWidget)
		{
			break;
		}
		InterfacePtr<IPnlTrvDataModel> model(treeWidget, UseDefaultIID());
		ASSERT(model);
		if(!model) {
			break;
		}
		PMString folderRootPath = PnlTrvUtils::GetFolderSelectedPath();
		if(folderRootPath.empty()) {
			break;
		}
		model->Rebuild(folderRootPath);
		InterfacePtr<ITreeViewMgr> 
			iTreeViewMgr(treeWidget, UseDefaultIID());
		ASSERT(iTreeViewMgr);
		if(!iTreeViewMgr) {
			break;
		}
		
			
		iTreeViewMgr->ClearTree();
		iTreeViewMgr->ChangeRoot(kTrue);
		
		
	} while(kFalse);
}

//	end, File:	PnlTrvIdleTask.cpp
