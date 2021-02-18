//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunSuiteASB.cpp $
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
#include "ISelectionManager.h" // required by selection templates.
#include "ICommandSequence.h"

// General includes:
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"
#include "K2Vector.h"

// Project includes:
#include "SnipRunID.h"
#include "ISnipRunSuite.h"

/** ISnipRunSuite abstract selection boss(ASB) suite implementation.

	@ingroup snippetrunner
	
	@see ISnipRunSuite
 */
class SnipRunSuiteASB : public CPMUnknown<ISnipRunSuite>
{
	public:
		/** Constructor.
		*/
		SnipRunSuiteASB(IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~SnipRunSuiteASB();	

		/** See ISnipRunSuite::GetSnippetNames.
		*/
		virtual void GetSnippetNames(SnippetNames& snippetNames) const;

		/** See ISnipRunSuite::IsRegistered.
		*/
		virtual bool16 IsRegistered(const SnippetName& snippetName) const;

		/** See ISnipRunSuite::GetCategories.
		*/
		virtual void GetCategories(const SnippetName& snippetName, Categories& categories) const;

		/** See ISnipRunSuite::GetDescription.
		*/
		virtual void GetDescription(const SnippetName& snippetName, PMString& description) const;

		/** See ISnipRunSuite::GetPreconditions.
		*/
		virtual void GetPreconditions(const SnippetName& snippetName, PMString& preconditions) const;

		/** See ISnipRunSuite::CanRun.
		*/
		virtual bool16 CanRun(const SnippetName& snippetName) const;
		
		/** See ISnipRunSuite::Run.
		*/
		ErrorCode Run(const SnippetName& snippetName, PMString& parameters, bool16 enableParameterDialog) const;

		/** 
			See ISnipRunSuite::SetupContext
		*/
		virtual ErrorCode SetupContext(const SnippetName& snippetName);


};

/*
*/
CREATE_PMINTERFACE(SnipRunSuiteASB, kSnipRunSuiteASBImpl)

/*
*/
SnipRunSuiteASB::SnipRunSuiteASB(IPMUnknown* boss) : CPMUnknown<ISnipRunSuite>(boss)
{
}

/*
*/
SnipRunSuiteASB::~SnipRunSuiteASB()
{
}

/* GetSelectionDescription
*/
void SnipRunSuiteASB::GetSnippetNames(SnippetNames& snippetNames) const 
{
	CallEach(make_functor(&ISnipRunSuite::GetSnippetNames, snippetNames), this);
}

/*
*/
bool16 SnipRunSuiteASB::IsRegistered(const SnippetName& snippetName) const
{
	return (AnyCSBSupports (make_functor(&ISnipRunSuite::IsRegistered, snippetName), this));
}

/*
*/
void SnipRunSuiteASB::GetCategories(const SnippetName& snippetName, Categories& categories) const
{
	CallEach(make_functor(&ISnipRunSuite::GetCategories, snippetName, categories), this);
}

/*
*/
void SnipRunSuiteASB::GetDescription(const SnippetName& snippetName, PMString& description) const
{
	CallEach(make_functor(&ISnipRunSuite::GetDescription, snippetName, description), this);
}

/*
*/
void SnipRunSuiteASB::GetPreconditions(const SnippetName& snippetName, PMString& preconditions) const
{
	CallEach(make_functor(&ISnipRunSuite::GetPreconditions, snippetName, preconditions), this);
}

/*
*/
bool16 SnipRunSuiteASB::CanRun(const SnippetName& snippetName) const
{
	return (AnyCSBSupports (make_functor(&ISnipRunSuite::CanRun, snippetName), this));
}


/*
*/
ErrorCode SnipRunSuiteASB::Run(const SnippetName& snippetName, PMString& parameters, bool16 enableParameterDialog) const
{
	return (Process(make_functor(&ISnipRunSuite::Run, snippetName, parameters, enableParameterDialog), this));
}


/** 
*/
ErrorCode SnipRunSuiteASB::SetupContext(const SnippetName& snippetName)
{
	return (Process(make_functor(&ISnipRunSuite::SetupContext, snippetName), this));
}



// End, SnipRunSuiteASB.cpp.





