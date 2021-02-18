//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxSuiteASB.cpp $
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
#include "ITranFxSuite.h"
// General includes:
#include "CPMUnknown.h"
#include "SelectionASBTemplates.tpp"

// Project includes:
#include "TranFxID.h"


/**	Integrator ITranFxSuite implementation on the ASB.

	Forwards calls onto CSB suite implementations on CSB's
	that have a selection.

	
	@ingroup transparencyeffect
*/
class TranFxSuiteASB : public CPMUnknown<ITranFxSuite>
{
	public:
		/** Constructor.
			@param boss
		 */
		TranFxSuiteASB (IPMUnknown* boss);

		/** Destructor.
		 */
		virtual ~TranFxSuiteASB (void);

		/** See ITranFxSuite::HasAdornment
		 */
		virtual	void		HasAdornment(AttrState& attrState) const;

		/** See ITranFxSuite::HasMode
		 */
		//virtual	void		HasMode(AttrState& attrState,int32& value) const;

		/** See ITranFxSuite::HasXOffset
		 */
		virtual	void		HasXOffset(AttrState& attrState, PMReal& value) const;

		/** See ITranFxSuite::HasYOffset
		 */
		virtual	void		HasYOffset(AttrState& attrState, PMReal& value) const;

		/** See ITranFxSuite::HasUseBlackAsOpaque
		 */
		virtual	void		HasUseBlackAsOpaque(AttrState& attrState, bool16& value) const;

		/** See ITranFxSuite::HasUseAlpha
		 */
		virtual	void		HasUseAlpha(AttrState& attrState, bool16& value) const;

		/** See ITranFxSuite::HasUseBlur
		 */
		virtual	void		HasUseBlur(AttrState& attrState, bool16& value) const;


		/** See ITranFxSuite::CanApplyAdornment
		 */
		virtual bool16	CanApplyAdornment() const;

		/** See ITranFxSuite::CanApplyMode
		 */
		//virtual bool16	CanApplyMode() const;

		/** See ITranFxSuite::CanApplyXOffset
		 */
		virtual bool16	CanApplyXOffset() const;

		/** See ITranFxSuite::CanApplyYOffset
		 */
		virtual bool16	CanApplyYOffset() const;		

		/** See ITranFxSuite::CanApplyUseBlackAsOpaque
		 */
		virtual bool16	CanApplyUseBlackAsOpaque() const;		

		/** See ITranFxSuite::CanApplyUseAlpha
		 */
		virtual bool16	CanApplyUseAlpha() const;

		/** See ITranFxSuite::CanApplyUseBlur
		 */
		virtual bool16	CanApplyUseBlur() const;

		/** See ITranFxSuite::ApplyAdornment
		 */
		virtual ErrorCode	ApplyAdornment(const bool16 isAdd);

		/** See ITranFxSuite::ApplyMode
		 */
		//virtual ErrorCode	ApplyMode(const int32 value);

		/** See ITranFxSuite::ApplyXOffset
		 */
		virtual ErrorCode	ApplyXOffset(const PMReal& value);

		/** See ITranFxSuite::ApplyYOffset
		 */
		virtual ErrorCode	ApplyYOffset(const PMReal& value);

		/** See ITranFxSuite::ApplyUseBlackAsOpaque
		 */
		virtual ErrorCode	ApplyUseBlackAsOpaque(const bool16 value);
		
		/** See ITranFxSuite::ApplyAlpha
		 */
		virtual ErrorCode	ApplyUseAlpha(const bool16 value);

		/** See ITranFxSuite::ApplyBlur
		 */
		virtual ErrorCode	ApplyUseBlur(const bool16 value);

};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(TranFxSuiteASB, kTranFxSuiteASBImpl)

/* Constructor
*/
TranFxSuiteASB::TranFxSuiteASB(IPMUnknown* boss) :
	CPMUnknown<ITranFxSuite>(boss)
{
}

/* Destructor
*/
TranFxSuiteASB::~TranFxSuiteASB(void)
{
}

/*
*/
void	TranFxSuiteASB::HasAdornment(AttrState& attrState) const
{
	CallEach(make_functor(&ITranFxSuite::HasAdornment, attrState), this);
}

/*

void	TranFxSuiteASB::HasMode(AttrState& attrState,int32& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasMode, attrState, value), this);
}
*/
/*
*/
void	TranFxSuiteASB::HasXOffset(AttrState& attrState, PMReal& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasXOffset, attrState, value), this);
}

/*
*/
void	TranFxSuiteASB::HasYOffset(AttrState& attrState, PMReal& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasYOffset, attrState, value), this);
}

/*
*/
void	TranFxSuiteASB::HasUseBlackAsOpaque(AttrState& attrState, bool16& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasUseBlackAsOpaque, attrState, value), this);
}

/*
*/
void	TranFxSuiteASB::HasUseAlpha(AttrState& attrState, bool16& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasUseAlpha, attrState, value), this);
}


/*
*/
void	TranFxSuiteASB::HasUseBlur(AttrState& attrState, bool16& value) const
{
	CallEach(make_functor(&ITranFxSuite::HasUseBlur, attrState, value), this);
}


/*
*/
bool16 TranFxSuiteASB::CanApplyAdornment(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyAdornment), this));
}

/*

bool16 TranFxSuiteASB::CanApplyMode(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyMode), this));
}
*/
/*
*/
bool16 TranFxSuiteASB::CanApplyXOffset(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyXOffset), this));
}

/*
*/
bool16 TranFxSuiteASB::CanApplyYOffset(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyYOffset), this));
}

/*
*/
bool16 TranFxSuiteASB::CanApplyUseBlackAsOpaque(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyUseBlackAsOpaque), this));
}
/*
*/
bool16 TranFxSuiteASB::CanApplyUseAlpha(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyUseAlpha), this));
}
/*
*/
bool16 TranFxSuiteASB::CanApplyUseBlur(void) const
{
	return (AnyCSBSupports (make_functor(&ITranFxSuite::CanApplyUseBlur), this));
}
/*
*/
ErrorCode	TranFxSuiteASB::ApplyAdornment(const bool16 isAdd)
{
	return Process(make_functor(&ITranFxSuite::ApplyAdornment, isAdd), this);
}


/*

ErrorCode	TranFxSuiteASB::ApplyMode(const int32 value)
{
	return Process(make_functor(&ITranFxSuite::ApplyMode, value), this);
}
*/
/*
*/
ErrorCode	TranFxSuiteASB::ApplyXOffset(const PMReal& value)
{
	return Process(make_functor(&ITranFxSuite::ApplyXOffset, value), this);
}	

/*
*/
ErrorCode	TranFxSuiteASB::ApplyYOffset(const PMReal& value)
{
	return Process(make_functor(&ITranFxSuite::ApplyYOffset, value), this);
}	

/*
*/
ErrorCode	TranFxSuiteASB::ApplyUseBlackAsOpaque(const bool16 value)
{
	return Process(make_functor(&ITranFxSuite::ApplyUseBlackAsOpaque, value), this);
}

/*
*/
ErrorCode	TranFxSuiteASB::ApplyUseAlpha(const bool16 value)
{
	return Process(make_functor(&ITranFxSuite::ApplyUseAlpha, value), this);
}

/*
*/
ErrorCode	TranFxSuiteASB::ApplyUseBlur(const bool16 value)
{
	return Process(make_functor(&ITranFxSuite::ApplyUseBlur, value), this);
}

// End, TranFxSuiteASB.cpp.

