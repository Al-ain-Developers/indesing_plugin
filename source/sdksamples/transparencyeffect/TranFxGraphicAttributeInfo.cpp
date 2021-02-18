//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxGraphicAttributeInfo.cpp $
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
#include "IGraphicAttributeInfo.h"
#include "IGraphicAttrRealNumber.h"
#include "IGraphicAttrInt32.h"
#include "IGraphicAttrRealNumber.h"
#include "IGraphicAttrBoolean.h"

// project includes:
#include "TranFxID.h"

/** Describes this plug-in's custom graphic attributes.

	There is an implementation in the API that is used by all of the application (default) attributes.
	However, the implementation cannot be re-used; third party attributes have to create their own implementations.

	.
	@ingroup transparencyeffect
 */
class TranFxGraphicAttributeInfo : public CPMUnknown<IGraphicAttributeInfo>
{
public:
	/** Constructor.
	*/
	TranFxGraphicAttributeInfo(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~TranFxGraphicAttributeInfo(){}

public:
	virtual PMString*       GetName                         (void) const;

	virtual bool16          IsTextAttribute                 (void) const;
	virtual bool16          IsGraphicAttribute              (void) const;
	virtual bool16          IsTableAttribute                (void) const;
	virtual bool16          IsExportAttribute                (void) const;
	virtual bool16          IsRequiredGraphicAttr           (void) const;
	virtual bool16          AffectsPageItemGeometry         (void) const;

	virtual bool16          ObservedByGraphicState          (void) const;
	virtual bool16          ObservedByTransparencyAttrSuite (void) const;
	virtual IPMUnknown*     CreateTextAttribute             (void) const;
	virtual IPMUnknown*     CreateTableAttribute            (void) const;

	virtual IPMUnknown*     DuplicateAttribute              (const PMIID& iid) const;

	virtual bool16          IsEqual                         (const IPMUnknown* otherAttr) const;

	virtual ClassID         GetClass                        (void) const;

	virtual PMString        GetValue(const ClassID& attrClass, const IWorkspace* ws) const 
			{ return PMString(""); }

private:
	int16                   fAttributeKind;
	ClassID                 fClassID; 
	IPMUnknown*             fDataInterface;
};

/*
*/
CREATE_PMINTERFACE(TranFxGraphicAttributeInfo, kTranFxGraphicAttributeInfoImpl)

/*
*/
TranFxGraphicAttributeInfo::TranFxGraphicAttributeInfo
	(
		IPMUnknown*        boss
	) :
fAttributeKind (0),
	fClassID(kInvalidClass),
	fDataInterface(nil),
	CPMUnknown<IGraphicAttributeInfo> (boss)
{

	fClassID = ::GetClass (this);

	switch (fClassID.Get())
	{
	case kTranFxOffsetXAttrBoss:
	case kTranFxOffsetYAttrBoss:
	case kTranFxUseBlackAsOpaqueAttrBoss:
	case kTranFxUseAlphaAttrBoss:
	case kTranFxUseBlurAttrBoss:            
		fAttributeKind |= kGraphicAttr;
		break;          
	}

	switch (fClassID.Get())
	{
	// All the real number attributes
	case kTranFxOffsetXAttrBoss:
	case kTranFxOffsetYAttrBoss:
		{
			fDataInterface = QueryInterface (IID_IGRAPHICATTR_REALNUMBER);
			ASSERT(fDataInterface);
			if (!fDataInterface)
			{
				break;
			}
			fDataInterface->Release();
		}
		break;

	// All the boolean attributes
	case kTranFxUseBlackAsOpaqueAttrBoss:
	case kTranFxUseAlphaAttrBoss:
	case kTranFxUseBlurAttrBoss:        {
			fDataInterface = QueryInterface (IID_IGRAPHICATTR_BOOLEAN);
			ASSERT(fDataInterface);
			if (!fDataInterface)
			{
				break;
			}
			fDataInterface->Release();
		}
		break;
	}
}

/*
*/
PMString* TranFxGraphicAttributeInfo::GetName
	(
		void
	) const
{
	PMString*       attributeName(nil);

	switch (fClassID.Get())
	{
	case kTranFxOffsetXAttrBoss:
		attributeName = new PMString ("kTranFxOffsetXAttrBoss");
		break;

	case kTranFxOffsetYAttrBoss:
		attributeName = new PMString ("kTranFxOffsetXAttrBoss");
		break;

	case kTranFxUseBlackAsOpaqueAttrBoss:
		attributeName = new PMString ("kTranFxUseBlackAsOpaqueAttrBoss");
		break;

	case kTranFxUseAlphaAttrBoss:
		attributeName = new PMString ("kTranFxUseAlphaAttrBoss");
		break;

	case kTranFxUseBlurAttrBoss:
		attributeName = new PMString ("kTranFxUseBlurAttrBoss");
		break;

	}

	if (attributeName)
		attributeName->SetTranslatable (kFalse);

	return(attributeName);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::IsTextAttribute
	(
		void
	) const
{
	return((fAttributeKind & kTextAttr) == kTextAttr);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::IsGraphicAttribute
	(
		void
	) const
{
	return((fAttributeKind & kGraphicAttr) == kGraphicAttr);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::IsTableAttribute
	(
		void
	) const
{
	return((fAttributeKind & kTableAttr) == kTableAttr);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::IsExportAttribute
	(
		void
	) const
{
	return((fAttributeKind & kExportAttr) == kExportAttr);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::IsRequiredGraphicAttr
	(
		void
	) const
{
	return kFalse;
}

/*
*/
bool16 TranFxGraphicAttributeInfo::AffectsPageItemGeometry
	(
		void
	) const
{
	return(kFalse);
}

/*
*/
bool16 TranFxGraphicAttributeInfo::ObservedByGraphicState
	(
		void
	) const
{
	return kFalse;
}

/*
*/
bool16 TranFxGraphicAttributeInfo::ObservedByTransparencyAttrSuite
	(
		void
	) const
{
	return kFalse;
}

/*
*/
IPMUnknown* TranFxGraphicAttributeInfo::CreateTextAttribute
	(
	) const
{
	return nil;

}

/*
*/
IPMUnknown* TranFxGraphicAttributeInfo::CreateTableAttribute
	(
	) const
{
	return nil;
}


/*
*/
bool16 TranFxGraphicAttributeInfo::IsEqual(const IPMUnknown* otherAttr) const
{

	bool16 retVal = kFalse;

	// non-const because all of the attribute value interfaces are not const 
	TranFxGraphicAttributeInfo* nonConstThis = (TranFxGraphicAttributeInfo*) this;

	InterfacePtr<IGraphicAttributeInfo> iOtherInfo (otherAttr, IID_IGRAPHICATTR_INFO);

	ClassID otherID = iOtherInfo->GetClass();

	if (fClassID != otherID)
		return retVal;

	switch (fClassID.Get())
	{
	// All the real number attributes
	case kTranFxOffsetXAttrBoss:
	case kTranFxOffsetYAttrBoss:
		{
			IGraphicAttrRealNumber* iLeftAttr = (IGraphicAttrRealNumber*) fDataInterface;
			InterfacePtr<IGraphicAttrRealNumber> iRightAttr (iOtherInfo, UseDefaultIID());
			ASSERT(iLeftAttr && iRightAttr);
			if (!(iLeftAttr && iRightAttr))
			{
				break;
			}
			if (iLeftAttr->GetRealNumber() == iRightAttr->GetRealNumber())
				retVal = kTrue;
		}
		break;

	// All the boolean attributes
	case kTranFxUseBlackAsOpaqueAttrBoss:
	case kTranFxUseAlphaAttrBoss:
	case kTranFxUseBlurAttrBoss:
		{
			IGraphicAttrBoolean* iLeftAttr = (IGraphicAttrBoolean*) fDataInterface;
			InterfacePtr<IGraphicAttrBoolean> iRightAttr (iOtherInfo, UseDefaultIID());

			ASSERT(iLeftAttr && iRightAttr);
			if (!(iLeftAttr && iRightAttr))
			{
				break;
			}

			if (iLeftAttr->GetBoolean() == iRightAttr->GetBoolean())
				retVal = kTrue;
		}
		break;

	}

	return retVal;
}


/*
*/
IPMUnknown* TranFxGraphicAttributeInfo::DuplicateAttribute
	(
		const PMIID& iid
	) const
{

	IPMUnknown* iResultInterface = nil;
	IPMUnknown* iRetInterface = nil;

	// non-const because all of the attribute value interfaces are not const 
	TranFxGraphicAttributeInfo* nonConstThis = (TranFxGraphicAttributeInfo*) this;

	switch (fClassID.Get())
	{
	// All the real number attributes
	case kTranFxOffsetXAttrBoss:
	case kTranFxOffsetYAttrBoss:
		{
			IGraphicAttrRealNumber* iThisAttr = (IGraphicAttrRealNumber*) fDataInterface;
			IGraphicAttrRealNumber* iNewAttr = ::CreateObject2<IGraphicAttrRealNumber>(fClassID);

			ASSERT(iThisAttr && iNewAttr);
			if (!(iThisAttr && iNewAttr))
			{
				break;
			}

			iNewAttr->SetRealNumber (iThisAttr->GetRealNumber());

			iResultInterface = iNewAttr;
		}
		break;

		// All the boolean attributes
	case kTranFxUseBlackAsOpaqueAttrBoss:
	case kTranFxUseAlphaAttrBoss:
	case kTranFxUseBlurAttrBoss:
		{
			IGraphicAttrBoolean* iThisAttr = (IGraphicAttrBoolean*) fDataInterface;
			IGraphicAttrBoolean* iNewAttr = ::CreateObject2<IGraphicAttrBoolean> (fClassID);

			ASSERT(iThisAttr && iNewAttr);
			if (!(iThisAttr && iNewAttr))
			{
				break;
			}
			iNewAttr->SetBoolean (iThisAttr->GetBoolean());

			iResultInterface = iNewAttr;
		}
		break;

	}
	ASSERT(iResultInterface);
	if (!iResultInterface)
	{
		return nil;
	}
	iRetInterface = iResultInterface->QueryInterface (iid);
	iResultInterface->Release();

	return iRetInterface;
}

/*
*/
ClassID TranFxGraphicAttributeInfo::GetClass 
	(
		void
	) const
{
	return fClassID;
}

// End, TranFxGraphicAttributeInfo.cpp.
