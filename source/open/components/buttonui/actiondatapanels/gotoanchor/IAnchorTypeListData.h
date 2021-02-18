//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/IAnchorTypeListData.h $
//  
//  Owner: Mark VerMurlen
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
#ifndef __IAnchorTypeListData_h__
#define __IAnchorTypeListData_h__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "FileUtils.h"
#include "BehaviorUIID.h"

//========================================================================================
// CLASS IAnchorTypeListData
//========================================================================================

class IAnchorTypeListData : public IPMUnknown
{
public:
	class AnchorTypeData
	{
	public:
		typedef object_type data_type;

		AnchorTypeData(const UID anchorUID, 
					 const PMString& displayName = "",
					 const PMString& anchorName = "",
					 const PMString& anchorType = ""
					 ) : 
			fAnchorUID(anchorUID),
			fDisplayName(displayName),
			fAnchorName(anchorName ),
			fAnchorType(anchorType )
		{ 
		}

		AnchorTypeData(const AnchorTypeData& other) : 
			fAnchorUID(other.fAnchorUID),
			fDisplayName(other.fDisplayName),
			fAnchorName(other.fAnchorName ),
			fAnchorType(other.fAnchorType )
		{ 
		}

		AnchorTypeData& operator=(const AnchorTypeData& other)
		{
			if (this != &other)
			{
				fAnchorUID = other.fAnchorUID;
				fDisplayName = other.fDisplayName; 
				fAnchorName = other.fAnchorName; 
				fAnchorType = other.fAnchorType; 
			}
			
			return *this;
		};
		
		bool operator==(const AnchorTypeData& other) const
		{
			if ( fAnchorUID == other.fAnchorUID &&
				 fDisplayName == other.fDisplayName &&
				 fAnchorName == other.fAnchorName &&
				 fAnchorType == other.fAnchorType
				)
			{
				return kTrue;
			}
			else
			{
				return kFalse;
			}
		}
		
		void SetAnchorUID(const UID& anchorUID) { fAnchorUID = anchorUID; }
		UID GetAnchorUID() const { return fAnchorUID; }

		void SetDisplayName(const PMString& name) { fDisplayName = name; }
		PMString GetDisplayName() const { return fDisplayName; }

		void SetAnchorName(const PMString& name) { fAnchorName = name; }
		PMString GetAnchorName() const { return fAnchorName; }

		void SetAnchorType(const PMString& type) { fAnchorType = type; }
		PMString GetAnchorType() const { return fAnchorType; }

	private:
		UID fAnchorUID;
		PMString fDisplayName;
		PMString fAnchorName;
		PMString fAnchorType;
	};
	
public:
	enum { kDefaultIID = IID_IANCHORTYPEDATA };

	virtual void						SetAnchorTypeData(const K2Vector<AnchorTypeData>& GoToAnchorTypeData) = 0;
	virtual K2Vector<AnchorTypeData>	GetAnchorTypeData() const = 0;
};


#endif // __IAnchorFileListData_h__
