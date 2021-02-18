//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxSuiteLayoutCSB.cpp $
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
#include "ILayoutTarget.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "TranFxID.h"
#include "ITranFxSuite.h"
#include "TranFxUtils.h"

/** Concrete ITranFxSuite implementation on the layout CSB.

	
	@ingroup transparencyeffect
	@see TranFxUtils facade used to apply changes and access data in the model.
*/
class TranFxSuiteLayoutCSB : public CPMUnknown<ITranFxSuite>
{
	public:
		/** Constructor.
			@param boss
		*/
		TranFxSuiteLayoutCSB (IPMUnknown* boss);

		/** Destructor.
		*/
		virtual ~TranFxSuiteLayoutCSB (void);


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

	protected:
		/** Get's the items to be targeted from the ILayoutTarget.
			@param itemList list of items to be targeted.
			@return kTrue if itemList contains data, kFalse if empty.
			*/
		bool16 getItemList(UIDList& itemList) const;
};

/* Make implementation available to the application.
*/
CREATE_PMINTERFACE(TranFxSuiteLayoutCSB, kTranFxSuiteLayoutCSBImpl)


/* Constructor
*/
TranFxSuiteLayoutCSB::TranFxSuiteLayoutCSB(IPMUnknown* boss) :
	CPMUnknown<ITranFxSuite>(boss)
{
}

/* Destructor
*/
TranFxSuiteLayoutCSB::~TranFxSuiteLayoutCSB(void)
{
}

/*
*/
bool16	TranFxSuiteLayoutCSB::getItemList(UIDList& itemList) const
{
	bool16 result = kFalse;
	do {
		InterfacePtr<ILayoutTarget> layoutTarget(this, UseDefaultIID());
		ASSERT(layoutTarget);
		if (!layoutTarget) {
			break;
		}
		itemList = layoutTarget->GetUIDList(kStripStandoffs);
		ASSERT(itemList.Length() > 0);
		if (itemList.Length() <= 0) {
			break;
		}
		result = kTrue;
	} while(false);
	return result;
}

/*
*/
void	TranFxSuiteLayoutCSB::HasAdornment(AttrState& attrState) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasAdornment(itemList));
	}
}

/*
*/
void	TranFxSuiteLayoutCSB::HasXOffset(AttrState& attrState, PMReal& value) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasXOffset(itemList, value));
	}
}

/*
*/
void	TranFxSuiteLayoutCSB::HasYOffset(AttrState& attrState, PMReal& value) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasYOffset(itemList, value));
	}
}

/*
*/
void	TranFxSuiteLayoutCSB::HasUseBlackAsOpaque(AttrState& attrState, bool16& value) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasUseBlackAsOpaque(itemList, value));
	}
}

/*
*/
void	TranFxSuiteLayoutCSB::HasUseAlpha(AttrState& attrState, bool16& value) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasUseAlpha(itemList, value));
	}
}

/*
*/
void	TranFxSuiteLayoutCSB::HasUseBlur(AttrState& attrState, bool16& value) const
{
	attrState = eNoValue;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		attrState = (ITranFxSuite::AttrState) (tranFxUtils.HasUseBlur(itemList, value));
	}
}

/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyAdornment(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyAdornment(itemList);
	}
	return result;
}

/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyXOffset(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyXOffset(itemList);
	}
	return result;
}

/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyYOffset(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyYOffset(itemList);
	}
	return result;
}


/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyUseBlackAsOpaque(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyUseBlackAsOpaque(itemList);
	}
	return result;
}

/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyUseAlpha(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyUseAlpha(itemList);
	}
	return result;
}

/*
*/
bool16 TranFxSuiteLayoutCSB::CanApplyUseBlur(void) const
{
	bool16 result = kFalse;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.CanApplyUseBlur(itemList);
	}
	return result;
}

/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyAdornment(const bool16 isAdd)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyAdornment(itemList, isAdd);
	}
	return result;
}

/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyXOffset(const PMReal& value)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyXOffset(itemList, 
			value,
			kTrue, //doPrePost
			kTrue); // doNotify			
	}
	return result;
}	

/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyYOffset(const PMReal& value)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyYOffset(itemList, 
			value,
			kTrue, //doPrePost
			kTrue); // doNotify			
	}
	return result;
}		


/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyUseBlackAsOpaque(const bool16 value)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyUseBlackAsOpaque(itemList, 
			value,
			kTrue, //doPrePost
			kTrue); // doNotify			
	}
	return result;
}		

/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyUseAlpha(const bool16 value)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyUseAlpha(itemList, 
			value,
			kTrue, //doPrePost
			kTrue); // doNotify			
	}
	return result;
}		


/*
*/
ErrorCode	TranFxSuiteLayoutCSB::ApplyUseBlur(const bool16 value)
{
	ErrorCode result = kFailure;
	UIDList itemList;
	if (this->getItemList(itemList)) {
		TranFxUtils tranFxUtils;
		result = tranFxUtils.ApplyUseBlur(itemList, 
			value,
			kTrue, //doPrePost
			kTrue); // doNotify			
	}
	return result;
}		

// End, TranFxSuiteLayoutCSB.cpp.


