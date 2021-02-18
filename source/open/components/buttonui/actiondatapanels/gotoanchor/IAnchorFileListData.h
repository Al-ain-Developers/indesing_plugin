//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/IAnchorFileListData.h $
//  
//  Owner: Steve Dowd
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
#ifndef __IAnchorFileListData_h__
#define __IAnchorFileListData_h__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "FileUtils.h"
#include "BehaviorUIID.h"

//========================================================================================
// CLASS IAnchorFileListData
//========================================================================================

class IAnchorFileListData : public IPMUnknown
{
public:
	class AnchorFileData
	{
	public:
		typedef object_type data_type;

		AnchorFileData(const PMString& sysFile, 
					 const PMString& displayName = ""
					 ) : 
			fSysFile(sysFile),
			fDisplayName(displayName)
		{ 
		}

		AnchorFileData(const AnchorFileData& other) : 
			fSysFile(other.fSysFile),
			fDisplayName(other.fDisplayName)
		{ 
		}

		AnchorFileData& operator=(const AnchorFileData& other)
		{
			if (this != &other)
			{
				fSysFile = other.fSysFile;
				fDisplayName = other.fDisplayName; 
			}
			
			return *this;
		};
		
		bool operator==(const AnchorFileData& other) const
		{
			if ( fSysFile == other.fSysFile &&
				 fDisplayName == other.fDisplayName 
				)
			{
				return kTrue;
			}
			else
			{
				return kFalse;
			}
		}
		
		void SetSysFile(const PMString& sysFile) { fSysFile = sysFile; }
		PMString GetSysFile() const { return fSysFile; }

		void SetDisplayName(const PMString& name) { fDisplayName = name; }
		PMString GetDisplayName() const { return fDisplayName; }

	private:
		PMString fSysFile;
		PMString fDisplayName;
	};
	
public:
	enum { kDefaultIID = IID_IANCHORFILEDATA };

	virtual void						SetAnchorFileData(const K2Vector<AnchorFileData>& GoToAnchorFileData) = 0;
	virtual K2Vector<AnchorFileData>	GetAnchorFileData() const = 0;
};


#endif // __IAnchorFileListData_h__
