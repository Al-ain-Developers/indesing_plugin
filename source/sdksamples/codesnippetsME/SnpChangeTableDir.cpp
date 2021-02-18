//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippetsME/SnpChangeTableDir.cpp $
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
//  
//  Usage rights licenced to Adobe Inc. 1997 - 2010.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ITableSuite.h"

// General includes:
#include "Utils.h"
#include "TableTypes.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	\li How to modify various properties of a story's table model (ITableSuite)

	This snippet highlights those ITableSuite functions that
	perform actions on the selection or on the table containing
	the selection. This snippet does not cover creating a table 
	and filling its cells with text; the TableBasics SDK sample
	plug-in covers this.

	For additional information regarding table attributes, look in the 
	browseable API documentation for kTableAttrXXXBoss entries.

	@ingroup sdk_snippet
  	@ingroup sdk_table
	@author Rodney Cook
	@see ITableSuite
	@see ITableModel
*/

class SnpChangeTableDir : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	SnpChangeTableDir();

	/** Destructor.
	 */
	virtual ~SnpChangeTableDir();

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);

	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunTableTargetContext;}
};


// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/* Constructor.
*/
SnpChangeTableDir::SnpChangeTableDir() : SnpRunnable("ChangeTableDir")
{
	// Describe what your snippet does.
	this->SetDescription("Change table direction.");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("Selection in a table");

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_table");
}

/* Destructor.
*/
SnpChangeTableDir::~SnpChangeTableDir()
{
}

/* Check if your preconditions are met.
*/
bool16	SnpChangeTableDir::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do
	{
		InterfacePtr<ITableSuite> tableSuite(runnableContext, UseDefaultIID());
		if (tableSuite != nil)
		{
			result = tableSuite->CanChangeTableDirection();
		}
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode SnpChangeTableDir::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		InterfacePtr<ITableSuite> 
			tableSuite(runnableContext, UseDefaultIID());
		if (tableSuite == nil)
		{
			status = kFailure;
			break;
		}

		Tables::EDirection tableDir = tableSuite->GetTableDirection();
		if (tableDir == Tables::eLTR)
			tableDir = Tables::eRTL;
		else
			tableDir = Tables::eLTR;

		tableSuite->ChangeTableDirection(tableDir);
		SNIPLOG("Change table direction");
		status = kSuccess;		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
SnpChangeTableDir instanceSnpChangeTableDir;

// End, SnpChangeTableDir.cpp

