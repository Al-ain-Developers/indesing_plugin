//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStepAndRepeatDialogPrefData.h $
//  
//  Owner: Ankur Mathur
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change $
//  ___________________
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2014 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IStepAndRepeatDialogPrefData__
#define __IStepAndRepeatDialogPrefData__

#include "IPMUnknown.h"

#include "StepRepeatID.h"

/** Data interface for the "Step and Repeat" command.
*/
class IStepAndRepeatDialogPrefData : public IPMUnknown
{
public:
	/** kDefaultIID */ 
        enum { kDefaultIID = IID_ISTEPANDREPEATDIALOGPREFDATA }; 

	/** Set the command data

		@param repeatCountOrRowCount IN how many times to repeat the command. When columnCount is not -1, this value is a rowCount
		@param columnCount IN how many times to repeat the command. -1 when not creating a grid.		
		@param isGridOn IN kTrue if creating a grid, kFalse otherwise.
	*/
	virtual void Set(const int32	repeatCountOrRowCount,
					 const int32	columnCount,
					 bool16			isGridOn
					 ) = 0;

	/** Get the command data

		@param repeatCountOrRowCount OUT how many times to repeat the command. When columnCount is -1, this is a standard repeatCount. When columnCount is not -1, see below.
		@param columnCount OUT how many times to repeat the command for columns. -1 if not creating a grid.		
		@param isGridOn OUT kTrue if creating a grid, kFalse otherwise.
	*/
	virtual void Get(int32&	 repeatCountOrRowCount,
					 int32&	 columnCount,
					 bool16& isGridOn
					 ) = 0;
};

#endif // __IStepAndRepeatDialogPrefData__
