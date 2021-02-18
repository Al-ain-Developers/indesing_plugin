//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPlugInDialogInfo.h $
//  
//  Owner: Sdu 
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
#ifndef __IPlugInDialogInfo__
#define __IPlugInDialogInfo__


#include "IPMUnknown.h"

//-----------------------------------------------------------------------------
// Class: CPlugInDialogInfo
// Owner: JeffreyS
//-----------------------------------------------------------------------------
class IPlugInDialogInfo : public IPMUnknown
{
   public:
      //-----------------------------------------------------------------------------
      // Owner: JeffreyS
      // 
      // Returns:  kTrue  - The user clicked Cancel
      //           kFalse - The user clicked OK.
      //-----------------------------------------------------------------------------
      virtual bool32  GetCancelled() = 0;

      //-----------------------------------------------------------------------------
      // Owner: JeffreyS
      // 
      // Description:  Sets the flag representing if a user clicked
      //               Cancel or OK.  (kTrue for Cancel).
      //-----------------------------------------------------------------------------
      virtual void    SetCancelled(bool32 in_cancelled) = 0;
};

/******************************************************************************
 * $Log: /shuksan/source/public/Interfaces/UI/IPlugInDialogInfo.h $
 * 
 * 2     7/10/98 5:23p Sdu
 * Updated Paradigm check-in
 * 
 * 1     5/29/98 4:35p Jeffreys
 * Interface to allow passing of data from a plugin UI to its core.
 *****************************************************************************/

#endif // __IPlugInDialogInfo__

