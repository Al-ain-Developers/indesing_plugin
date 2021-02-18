//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpSetTableFill.cpp $
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
#include "ITableModel.h"
#include "IWorkspace.h"
#include "ILayoutUtils.h"
#include "ISwatchUtils.h"
#include "ITableCommands.h"
#include "ITableTarget.h"
#include "ITableAttrUID.h"
#include "AttributeBossList.h"

// General includes:
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Sets fill on a table.

  	@ingroup sdk_snippet
  	@ingroup sdk_table
 */
class SnpSetTableFill 
{
	public:

		/** Constructor.
		 */
		SnpSetTableFill() : fApplyToRow(0) {}

		/** Destructor.
		 */
		virtual			~SnpSetTableFill() {}

		/**	Shows how to apply the table-wide attribute for color.
			
			@param tableModel The table model of interest.
			@param gridAreaTarget The target grid area.
			@param colorUID The UID of the color to fill.
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode SetFillColour(InterfacePtr<ITableModel>& tableModel, 
								const GridArea& gridAreaTarget, 
								const UID& colorUID);
		
		/** Gets a grid area to work on. 
			This particular method just returns the entire table area, but does it
			iteratively.
			@param tableModel The table model of interest. 
			@return GridArea of the "interesting" area.
		*/
		GridArea getGridAreaTarget(const InterfacePtr<ITableModel>& tableModel);

	
private:
	const int32 fApplyToRow;
};



/*
*/
ErrorCode SnpSetTableFill::SetFillColour(InterfacePtr<ITableModel>& tableModel, 
										  const GridArea& gridAreaTarget, 
										  const UID& colorUID)
{
	ErrorCode status = kFailure;
	
	do {

		ASSERT(tableModel);	// If it asserts have you a table in selection?
		if(tableModel == nil) 
		{
			break;
		}
		ASSERT(colorUID != kInvalidUID);
		if(colorUID == kInvalidUID) 
		{
			break;
		}
		
		// Get the table commands, since we want to be able to 
		// specify the table area to apply the attributes to.
		// If we just wanted to apply attributes to the selected area, 
		// then ITableSuite::CanApplyCellOverrides()/ApplyCellOverrides() would suffice. 
		InterfacePtr<ITableCommands> iTableCommands(tableModel, UseDefaultIID());
		ASSERT(iTableCommands);
		if(iTableCommands == nil) 
		{
			break;
		}
		
		// Create a list of attr boss classes to apply
		AttributeBossList attributeBossList;

		// Create a Cell-fill colour boss class
		InterfacePtr<ITableAttrUID> iTableAttrUID(::CreateObject2<ITableAttrUID>(kCellAttrFillColorBoss));
		ASSERT(iTableAttrUID);
		if(iTableAttrUID == nil) 
		{
			break;
		}
		// Set the color attribute by color UID
		iTableAttrUID->Set(colorUID);
		
		// apply the attribute on to the list of attribute bosses
		attributeBossList.ApplyAttribute(iTableAttrUID);


		// This is the KEY point: Apply the attribute to an area in the table
		status = iTableCommands->ApplyCellOverrides(gridAreaTarget, &attributeBossList);

	} while(kFalse);

	return status;

}

/*
*/
GridArea SnpSetTableFill::getGridAreaTarget(const InterfacePtr<ITableModel>& tableModel)
{
	GridArea unionGridArea;
	do 
	{
		ASSERT(tableModel);
		if(tableModel == nil) 
		{
			break;
		}
		ITableModel::const_iterator iterTable(tableModel->begin());
		ITableModel::const_iterator endTable(tableModel->end());
		
		while(iterTable != endTable) 
		{
				
			GridAddress gridAddress = (*iterTable);
			if(gridAddress.row == fApplyToRow) 
			{
				// GridAddress, GridSpan
				GridSpan gridSpan = tableModel->GetCellSpan(gridAddress);
				GridArea gridArea = GridArea(gridAddress, gridSpan);
				if(unionGridArea.IsEmpty()) 
				{
					unionGridArea = gridArea;
				} 
				else 
				{
					// Take the union of current area and the latest area
					unionGridArea = unionGridArea | gridArea;
				}
			}
			++iterTable;
		}
	} while(kFalse);
	return unionGridArea;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerSetTableFill : public SnpRunnable
{
	
	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerSetTableFill();

		/** Destructor.
		 */
		virtual			~_SnpRunnerSetTableFill();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}
};

/* Constructor.
*/
_SnpRunnerSetTableFill::_SnpRunnerSetTableFill() : SnpRunnable("SetTableFill")
{
	// Describe what your snippet does.
	this->SetDescription("Provides a SetTableFill");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("A table must be selected");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerSetTableFill::~_SnpRunnerSetTableFill()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerSetTableFill::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableTarget> 
			tableTarget(runnableContext, UseDefaultIID());
		if (tableTarget != nil)
		{
			InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
			if (tableModel)
				result = kTrue;
		}
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerSetTableFill::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpSetTableFill instance;
		// First, get the currently selected table. 
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		ASSERT(tableTarget);
		if(tableTarget == nil) 
		{
			break;
		}
		InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
		ASSERT(tableModel);	// If it asserts have you a table in selection?
		if(tableModel == nil) 
		{
			break;
		}

		IWorkspace* iActiveWorkspace = runnableContext->GetActiveContext()->GetContextWorkspace();
		
		ASSERT(iActiveWorkspace);
		if(iActiveWorkspace == nil) 
		{
			break;
		}
		// create some dummy swatch
		UID dummySwatchUID = Utils<ISwatchUtils>()->CreateProcessCMYKSwatch(iActiveWorkspace,
																			 PMString(), 0, 0, 1, 0);

		// Apply the color on an area of the table (in this case, the 1st row)
		GridArea gridAreaTarget = instance.getGridAreaTarget(tableModel);
		status = instance.SetFillColour(tableModel, gridAreaTarget, dummySwatchUID);
		// xxx Use this next line instead of above two if you want the entire table for instance 
		// status = instance.SetFillColour(tableModel, tableModel->GetTableArea(), dummySwatchUID);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerSetTableFill instance_SnpRunnerSetTableFill;
DEFINE_SNIPPET(_SnpRunnerSetTableFill) 	

// End, SnpSetTableFill.cpp

