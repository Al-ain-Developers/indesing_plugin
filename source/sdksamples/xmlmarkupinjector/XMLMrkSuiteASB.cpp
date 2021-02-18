//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlmarkupinjector/XMLMrkSuiteASB.cpp $
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


// General includes:
#include "CPMUnknown.h"
#include "CmdUtils.h"	// so that the thing will compile (selectionasbtemplates.tpp)
#include "SelectionASBTemplates.tpp"

#include "XMLMrkID.h"
#include "IXMLMrkSuite.h"

/**
	Integrator IXMLMrkSuite implementation. Uses templates
	provided by the API to delegate calls to IXMLMrkSuite
	implementations on underlying concrete selection boss
	classes.

	See XMLMrkConstants for definition of the top-level elements
	that are created by these operations.
	@ingroup xmlmarkupinjector
	
*/
class XMLMrkSuiteASB : public CPMUnknown<IXMLMrkSuite>
{
public:
	/** Constructor.
		@param boss boss object on which this interface is aggregated.
	 */
	XMLMrkSuiteASB (IPMUnknown *boss);

	/** Destructor.
	 */
	virtual ~XMLMrkSuiteASB (void);

public:
	/**	See IXMLMrkSuite::CanMakeTable
		@param none
		@return bool16 
	 */
	virtual bool16 CanMakeTable() const;


	/**	IXMLMrkSuite::MakeTable
		@param hasHeaderRow 
		@return ErrorCode 
	 */
	virtual ErrorCode MakeTable(bool16 hasHeaderRow);

	/**	See IXMLMrkSuite::CanMakeKeywordSet
		@param none
		@return bool16 
	 */
	virtual bool16 CanMakeKeywordSet() const ;


	/**	See IXMLMrkSuite::MakeKeywordSet
		@param none
		@return ErrorCode 
	 */
	virtual ErrorCode MakeKeywordSet() ;

	/**	See IXMLMrkSuite::CanMakeItemizedList
		@param none
		@return bool16 
	 */
	virtual bool16 CanMakeItemizedList() const ;

	/**	See IXMLMrkSuite::MakeItemizedList
		@param none
		@return ErrorCode 
	 */
	virtual ErrorCode MakeItemizedList() ;

	/**	See IXMLMrkSuite::CanMakeSectionComposite
		@param none
		@return bool16 
	 */
	virtual bool16 CanMakeSectionComposite() const ;


	/**	See IXMLMrkSuite::MakeSectionComposite
		@param none
		@return ErrorCode 
	 */
	virtual ErrorCode MakeSectionComposite() ;

	/**	See IXMLMrkSuite::CanMakeMediaObject
		@param none
		@return bool16 
	 */
	virtual bool16 CanMakeMediaObject() const;


	/**	See IXMLMrkSuite::MakeMediaObject
		@param none
		@return ErrorCode 
	 */
	virtual ErrorCode MakeMediaObject();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(XMLMrkSuiteASB, kXMLMrkSuiteASBImpl)


/* XMLMrkSuiteASB Constructor
*/
XMLMrkSuiteASB::XMLMrkSuiteASB(IPMUnknown* boss) :
	CPMUnknown<IXMLMrkSuite>(boss)
{
}

/* XMLMrkSuiteASB Destructor
*/
XMLMrkSuiteASB::~XMLMrkSuiteASB(void)
{
}

/* CanMakeTable
*/
bool16 XMLMrkSuiteASB::CanMakeTable() const
{
	return (AnyCSBSupports(make_functor(&IXMLMrkSuite::CanMakeTable), this));
}

/* MakeTable
*/
ErrorCode XMLMrkSuiteASB::MakeTable(bool16 hasHeaderRow)
{
	return (Process(make_functor(&IXMLMrkSuite::MakeTable, hasHeaderRow), this));
}

/* CanMakeKeywordSet
*/
bool16 XMLMrkSuiteASB::CanMakeKeywordSet() const
{
	return (AnyCSBSupports(make_functor(&IXMLMrkSuite::CanMakeKeywordSet), this));
}

/* MakeKeywordSet
*/
ErrorCode XMLMrkSuiteASB::MakeKeywordSet()
{
	return (Process(make_functor(&IXMLMrkSuite::MakeKeywordSet), this));
}


/* CanMakeItemizedList
*/
bool16 XMLMrkSuiteASB::CanMakeItemizedList() const
{
	return (AnyCSBSupports(make_functor(&IXMLMrkSuite::CanMakeItemizedList), this));
}

/* MakeItemizedList
*/
ErrorCode XMLMrkSuiteASB::MakeItemizedList()
{
	return (Process(make_functor(&IXMLMrkSuite::MakeItemizedList), this));
}

/* CanMakeSectionComposite
*/
bool16 XMLMrkSuiteASB::CanMakeSectionComposite() const
{
	return (AnyCSBSupports(make_functor(&IXMLMrkSuite::CanMakeSectionComposite), this));
}

/* MakeSectionComposite
*/
ErrorCode XMLMrkSuiteASB::MakeSectionComposite()
{
	return (Process(make_functor(&IXMLMrkSuite::MakeSectionComposite), this));
}

/* CanMakeMediaObject
*/
bool16 XMLMrkSuiteASB::CanMakeMediaObject() const
{
	return (AnyCSBSupports(make_functor(&IXMLMrkSuite::CanMakeMediaObject), this));
}

/* MakeMediaObject
*/
ErrorCode XMLMrkSuiteASB::MakeMediaObject()
{
	return (Process(make_functor(&IXMLMrkSuite::MakeMediaObject), this));
}
// End, XMLMrkSuiteASB.cpp.


