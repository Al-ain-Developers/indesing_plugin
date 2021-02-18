//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtSuiteASB.cpp $
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
#include "WideString.h"
#include "CmdUtils.h"

// Project includes:
#include "HidTxtID.h"
#include "IHidTxtSuite.h"

/**	Integrator IHidTxtSuite implementation that forwards calls on to
	CSB IHidTxtSuite implementations that have a selection.

	
	@ingroup hiddentext
	@see IHidTxtSuite
*/
class HidTxtSuiteASB : public CPMUnknown<IHidTxtSuite>
{
	public:
		/** Constructor.
			@param boss
		 */
		HidTxtSuiteASB (IPMUnknown *boss);
		/** Destructor.
		 */
		virtual ~HidTxtSuiteASB (void);

	public:
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanCreateHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		CreateHiddenText(const WideString& text);
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanGetHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual void			GetHiddenText(WideString& text) const;
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanModifyHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		ModifyHiddenText(const WideString& text);
		/** @see IHidTxtSuite.
		 */
		virtual bool16			CanDeleteHiddenText() const;
		/** @see IHidTxtSuite.
		 */
		virtual ErrorCode		DeleteHiddenText();

};

/*
*/
CREATE_PMINTERFACE(HidTxtSuiteASB, kHidTxtSuiteASBImpl)


/*
*/
HidTxtSuiteASB::HidTxtSuiteASB(IPMUnknown* boss) :
	CPMUnknown<IHidTxtSuite>(boss)
{
}

/*
*/
HidTxtSuiteASB::~HidTxtSuiteASB(void)
{
}

/*
*/
bool16 HidTxtSuiteASB::CanCreateHiddenText() const
{
	return (AnyCSBSupports(make_functor(&IHidTxtSuite::CanCreateHiddenText), this));
}

/*
*/
ErrorCode HidTxtSuiteASB::CreateHiddenText(const WideString& text)
{
	return (Process(make_functor(&IHidTxtSuite::CreateHiddenText, text), this));
}

/*
*/
bool16 HidTxtSuiteASB::CanGetHiddenText() const
{
	return (AnyCSBSupports(make_functor(&IHidTxtSuite::CanGetHiddenText), this));
}

/*
*/
void HidTxtSuiteASB::GetHiddenText(WideString& text) const
{
	CallEach(make_functor(&IHidTxtSuite::GetHiddenText, text), this);
}

/*
*/
bool16 HidTxtSuiteASB::CanModifyHiddenText() const
{
	return (AnyCSBSupports(make_functor(&IHidTxtSuite::CanModifyHiddenText), this));
}

/*
*/
ErrorCode HidTxtSuiteASB::ModifyHiddenText(const WideString& text)
{
	return (Process(make_functor(&IHidTxtSuite::ModifyHiddenText, text), this));
}

/*
*/
bool16 HidTxtSuiteASB::CanDeleteHiddenText() const
{
	return (AnyCSBSupports(make_functor(&IHidTxtSuite::CanDeleteHiddenText), this));
}

/*
*/
ErrorCode HidTxtSuiteASB::DeleteHiddenText()
{
	return (Process(make_functor(&IHidTxtSuite::DeleteHiddenText), this));
}


// End, HidTxtSuiteASB.cpp.

