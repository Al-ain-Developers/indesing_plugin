//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyTableContext.h $
//  
//  Owner: Jeff Argast
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
#ifndef __IInCopyTableContext__
#define __IInCopyTableContext__

#include "IPMUnknown.h"

#include "InCopyWorkflowID.h"

class ITableAttrReport;
class ColRange;
class RowRange;

class IInCopyTableContext : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINCOPYTABLECONTEXT };


        //----------------------------------------------------------------------------------------
		virtual void Initialize(
			const UIDRef& storyRef
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void BeginTable(
			const TextIndex insertPosition,
			const int32 rows,
			const int32 columns,
			const int32 headers,
			const int32 footers
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void EndTable() = 0;

        //----------------------------------------------------------------------------------------
		virtual UIDRef GetTable() = 0;

        //----------------------------------------------------------------------------------------
		virtual void BeginTableAttr() = 0;

        //----------------------------------------------------------------------------------------
		virtual void EndTableAttr() = 0;

        //----------------------------------------------------------------------------------------
		virtual void BeginRowAttr(
			RowRange rows
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void EndRowAttr() = 0;

        //----------------------------------------------------------------------------------------
		virtual void BeginColumnAttr(
			ColRange cols
			) = 0;

        //----------------------------------------------------------------------------------------
		virtual void EndColumnAttr() = 0;

        //----------------------------------------------------------------------------------------
		virtual void AddAttribute(
			ITableAttrReport* attr
			) = 0;

		virtual void SetTableDir(int32 tableDir) = 0;

		virtual int32 GetTableDir() const = 0;

};


#endif // __IInCopyTableContext__



