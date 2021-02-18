//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IFontGroupId.h $
//  
//  Owner: mvogel
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

#pragma once
#ifndef __IFontGroupId__
#define __IFontGroupId__

#include "GRRefCountedObj.h"
#include "InterfacePtr.h"
#include "IFontGroup.h"
#include "BravoForwardDecl.h"

#include "IPMFont.h"

class PMString;

#define ALLOWDUPFONTS 1

/** Contains an IFontGroup and a Group name. The group name is used if the IFontGroup is nil.
	A font group name is not enough to identify a group. 2 groups can have the same name.
	@ingroup text_font
*/
class IFontGroupId : public grRefCountedObj
{
public:
	IFontGroupId (IFontGroup *group, PMString const &fontGroupName, PMString const &fontGroupNameNative) :
		fGroup (group),
		fFontGroupName (fontGroupName),
		fFontGroupNameNative (fontGroupNameNative),
		fFontType (IPMFont::kUnknownFontType)
	{
		if (fGroup)
			fGroup->AddRef();
	}

	IFontGroupId (IFontGroup *group, PMString const &fontGroupName, PMString const &fontGroupNameNative, IPMFont::FontType fontType) :
		fGroup(group),
		fFontGroupName (fontGroupName),
		fFontGroupNameNative (fontGroupNameNative),
		fFontType (fontType)
	{
		if (fGroup)
			fGroup->AddRef();
	}

	~IFontGroupId()
	{
		if (fGroup)
		{
			fGroup->Release();
			fGroup = nil;
		}
	}

	const PMString &GetName() const
	{
		return fFontGroupName;
	}
	IFontGroup *GetGroup() const
	{
		return fGroup;
	}
	IPMFont::FontType GetFontType() const
	{
		return fFontType;
	}
	bool16 operator == (const IFontGroupId &value) const
	{	// There are ill-formed fonts whose native family names differ within the group but whose non-native family names
		// are identical across the group. In the English locale, for example, these would be considered a single group
		// if we relied only on the non-native name. But we must treat them separately in order to avoid problems
		// elsewhere. Hence we compare against both native and non-native.
		// On the other hand, if native is empty, it signals "unknown", effectively, and we'll allow a match there
		// because in any normal circumstance that should be true.
		if (value.fFontGroupName == fFontGroupName && (
				fFontGroupNameNative.empty() || value.fFontGroupNameNative.empty() ||
				value.fFontGroupNameNative == fFontGroupNameNative))
			return	fFontType == value.GetFontType() ||
					fFontType == IPMFont::kUnknownFontType || value.GetFontType() == IPMFont::kUnknownFontType;

		return kFalse;
	}
 

private:
	IFontGroupId() :
		fGroup(nil),
		fFontGroupName(),
		fFontGroupNameNative(),
		fFontType(IPMFont::kUnknownFontType)
	{}
	// Copy constructor
    IFontGroupId( const IFontGroupId& orig ) :
		fGroup(orig.fGroup),
		fFontGroupName(orig.fFontGroupName),
		fFontGroupNameNative (orig.fFontGroupNameNative),
		fFontType(orig.fFontType)
		{
			ASSERT_FAIL("DOES THIS HAPPEN??");
			//if (fGroup) fGroup->AddRef();
		}

	IFontGroupId& operator=(const IFontGroupId& fontGroupIdentifierPtr);

	IFontGroup *fGroup;
	PMString fFontGroupName;
	PMString fFontGroupNameNative;
	IPMFont::FontType fFontType;
};

DECLARE_OBJECT_TYPE(IFontGroupId);

template <>
class InterfacePtr<IFontGroupId>
{
public:
        InterfacePtr(IFontGroupId * pFace)
            // Note: Constructing an InterfacePtr from an existing,
            // "real" interface pointer implies the InterfacePtr
            // now owns the reference that was held by the real pointer.
            : fFace(pFace) {}

        ~InterfacePtr()
            {
                if (fFace != nil){
                    //const_cast<IFontGroupId *>(unknown)->Release();
                    fFace->Release();
                }
            }

        operator IFontGroupId*() const
        { return fFace; }
            // We allow the cast operator to return a nil pointer
            // since it is valid to test against nil and may be valid
            // to pass a nil pointer to some methods.


        IFontGroupId * operator ->() const
            {
            #ifdef DEBUG
                ASSERT_MSG(fFace != nil,"About to use nil interface ptr!");
            #endif
            return fFace;
            }

private:
    IFontGroupId * fFace;

        // If you feel you need one of these, let me know.  Thx. - Zak
        // For the sake of clarity and simplicity, they're currently not supported.

        InterfacePtr(void);
        InterfacePtr(const InterfacePtr<IFontGroupId>& fontGroupIdentifierPtr);
        InterfacePtr<IFontGroupId>& operator=(const InterfacePtr<IFontGroupId>& fontGroupIdentifierPtr);
        InterfacePtr<IFontGroupId>& operator=(IFontGroupId * pFace);

};

#endif
		//__IFontGroupId__
		
