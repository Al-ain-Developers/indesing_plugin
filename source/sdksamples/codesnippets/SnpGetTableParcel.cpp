//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpGetTableParcel.cpp $
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
#include "ICellContent.h"
#include "ICellFocus.h"
#include "IParcelList.h"
#include "IParcel.h"
#include "ITableTarget.h"
#include "IMeasurementSystem.h"
#include "IUnitOfMeasureSettings.h"
#include "IUnitOfMeasure.h"
// General includes:
#include "Utils.h"
#include "PreferenceUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li	Iterates the parcels in the cell focus GridArea.

  	@ingroup sdk_snippet
  	@ingroup sdk_table

 */
class SnpGetTableParcel 
{
	public:
		/** Constructor.
		 */
		SnpGetTableParcel();

		/** Destructor.
		 */
		virtual			~SnpGetTableParcel() {}

		/**
			Shows how to iterate through parcels within a table model. 
			@param tableModel The table model which you want to look at
			@param focusGridArea The focus area of the table you want to examine. 
				Examines all of the parcels that correspond to cells in the given area.
			@param ac The current active context.
			@return kSuccess on success, kFailure otherwise.
		*/
		ErrorCode DoIterateParcels(const InterfacePtr<ITableModel>& tableModel,
								   const GridArea& focusGridArea,
								   IActiveContext* ac);
		
		/** Return the bounds of a PMRect as a PMString.
			@param bounds A PMRect to examine.
			@return PMString representation of the PMRect passed in, so it's human-readable.
		*/	
		PMString GetBoundsAsSystemString(const PMRect& bounds);
private:
	IActiveContext*	fActiveContext;
};

SnpGetTableParcel::SnpGetTableParcel()
: fActiveContext(nil)
{}

/*
*/
ErrorCode SnpGetTableParcel::DoIterateParcels(const InterfacePtr<ITableModel>& tableModel,
											   const GridArea& focusGridArea,
											   IActiveContext* ac)	
{
	ErrorCode status = kFailure;
	do
	{	
		fActiveContext = ac;
		// check preconditions: valid table model, non-empty focus grid area
		ASSERT(tableModel);
		if (tableModel == nil)
		{
			break;
		}
		if (focusGridArea.IsEmpty())
		{
			SNIPLOG("Cell focus area is empty!");
			break;
		}

		// Iterate over selected range of cells
		ITableModel::const_iterator iterTable(tableModel->begin(focusGridArea));
		ITableModel::const_iterator end(tableModel->end(focusGridArea));
		while(iterTable != end) 
		{
			// get the grid address of cell
			GridAddress gridAddress = *iterTable;
			SNIPLOG("Cell (row=%d,column=%d)", gridAddress.row, gridAddress.col);

			InterfacePtr<ICellContent> cellContent(tableModel->QueryCellContentBoss(gridAddress));
			ASSERT(cellContent);
			if(cellContent == nil) 
			{
				break;
			}

			InterfacePtr<IParcelList> parcelList(cellContent, UseDefaultIID());
			ASSERT(parcelList);
			if(parcelList == nil) 
			{
				break;
			}	

			// Go through each parcel in the parcelList at this grid address...
			IParcelList::const_iterator end = parcelList->end();
			for (IParcelList::const_iterator iter = parcelList->begin(); iter != end; ++iter)
			{
				InterfacePtr<IParcel> parcel(parcelList->QueryParcel(*iter));
				if (parcel == nil)
				{
					break;
				}
	
				// Get the parcel geometry
		        PMRect parcelBounds = parcel->GetBounds();
				SNIPLOG(this->GetBoundsAsSystemString(parcelBounds).GetPlatformString().c_str());
			}
			// Goto the next grid address
			++iterTable;
		}
		status = kSuccess;
	} while (false);
	return status;
} // SnipGetTableParcel




PMString SnpGetTableParcel::GetBoundsAsSystemString(const PMRect& bounds)
{
    InterfacePtr<IMeasurementSystem> ms(GetExecutionContextSession(), IID_IMEASUREMENTSYSTEM);
    InterfacePtr<IUnitOfMeasureSettings> iMeasurePrefs((IUnitOfMeasureSettings*)::QueryPreferences(IID_IUNITOFMEASURESETTINGS, fActiveContext));
    int16 hUnitIndex = iMeasurePrefs->GetXUnitOfMeasureIndex();
    int16 vUnitIndex = iMeasurePrefs->GetYUnitOfMeasureIndex();
	PMString hUnits, vUnits;
    InterfacePtr<IUnitOfMeasure> hCurrentUnit(ms->QueryUnitOfMeasure(hUnitIndex));
    hCurrentUnit->GetName(&hUnits);
    InterfacePtr<IUnitOfMeasure> vCurrentUnit(ms->QueryUnitOfMeasure(vUnitIndex));
    vCurrentUnit->GetName(&vUnits);

	PMString result;
	
	char buf[12];
	sprintf(buf, "%6.2f ", ::ToDouble(hCurrentUnit->PointsToUnits(bounds.Left())));
	PMString left(buf);
	sprintf(buf, "%6.2f", ::ToDouble(vCurrentUnit->PointsToUnits(bounds.Top())));
	PMString top(buf);
	sprintf(buf, "%6.2f", ::ToDouble(hCurrentUnit->PointsToUnits(bounds.Right())));
	PMString right(buf);
	sprintf(buf, "%6.2f", ::ToDouble(vCurrentUnit->PointsToUnits(bounds.Bottom())));
	PMString bottom(buf);

	result = PMString("[Left: ") + left + PMString (" ") + hUnits 
			+ PMString(", Top: ") + top + PMString (" ") + vUnits 
			+ PMString(", Right: ") + right + PMString (" ") + hUnits 
			+ PMString(", Bottom: ") + bottom + PMString (" ") + vUnits + PMString("]");

	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpGetTableParcel available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerGetTableParcel : public SnpRunnable
{
	

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerGetTableParcel();

		/** Destructor.
		 */
		virtual			~_SnpRunnerGetTableParcel();

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
_SnpRunnerGetTableParcel::_SnpRunnerGetTableParcel() : SnpRunnable("GetTableParcel")
{
	// Describe what your snippet does.
	this->SetDescription("Gets a parcel from selected table cell");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("A table on a document with some cells selected");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerGetTableParcel::~_SnpRunnerGetTableParcel()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerGetTableParcel::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableTarget> 
			tableTarget(runnableContext, UseDefaultIID());
		if (tableTarget != nil)
		{
			InterfacePtr<ICellFocus> cellFocus(tableTarget, UseDefaultIID());
			if (!cellFocus)
				break;

			// Get the range of the selected cells
			// Must have some connection to table model, or will assert.
			GridArea focusGridArea = cellFocus->GetRange();
			if(focusGridArea.IsEmpty()) 
			{
				break;
			}
			// Get the table model
			InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
			ASSERT(tableModel);	// If it asserts, then something is really wrong
			if(tableModel == nil) 
			{
				break;
			}
			// Now enable the button
			result = kTrue;
		}
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerGetTableParcel::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpGetTableParcel instance;
		InterfacePtr<ITableTarget> tableTarget(runnableContext, UseDefaultIID());
		ASSERT(tableTarget);
		if(tableTarget == nil) 
		{
			break;
		}
		InterfacePtr<ICellFocus> cellFocus(tableTarget, UseDefaultIID());
		ASSERT(cellFocus);
		if(cellFocus == nil) 
		{
			break;
		}

		// Get the range of the selected cells
		// Must have some connection to table model, or will assert.
        GridArea focusGridArea = cellFocus->GetRange();
		//ASSERT(!focusGridArea.IsEmpty());
		if(focusGridArea.IsEmpty()) 
		{
			break;
		}
		// Get the table model
		InterfacePtr<ITableModel> tableModel(tableTarget->QueryModel());
		ASSERT(tableModel);	// If it asserts, then something is really wrong
		if(tableModel == nil) 
		{
			break;
		}
		IActiveContext* activeContext = runnableContext->GetActiveContext();
		status = instance.DoIterateParcels(tableModel, focusGridArea, activeContext);
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerGetTableParcel instance_SnpRunnerGetTableParcel;
DEFINE_SNIPPET(_SnpRunnerGetTableParcel) 	

// End, SnpGetTableParcel.cpp

