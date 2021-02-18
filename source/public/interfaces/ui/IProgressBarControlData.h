//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IProgressBarControlData.h $
//  
//  Owner: Dave Burnard (was Neil Levine)
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
#ifndef __IProgressBarControlData__
#define __IProgressBarControlData__

#include "IProgressBarManager.h"

/** Control Data interface corresponding to a progress bar.
*/
class IProgressBarControlData : public IPMUnknown
{
public:
	/** Set the range of the progress bar. */
	virtual bool16 		SetRange (int16 min, int16 max) = 0;
	/** Get the minimum of the progress bar's range */
	virtual int16 		GetMin() const = 0;
	/** Get the maximum of the progress bar's range */
	virtual int16 		GetMax() const = 0;

	/** Set the current value of the progress indicator.

		@param newValue IN the new value for the control
		@param invalidate IN invalidate the associated control view
		@param notifyOfChange IN notify the associated subject
	*/
	virtual void 		SetValue( int16 newValue, 
							bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue) = 0;
							
	/** Get the current value of the progress indicator. */
	virtual int16 		GetValue() const = 0;

	/** Set the Title the progress bar.

		@param title IN the title
		@param invalidate IN invalidate the associated control view
		@param notifyOfChange IN notify the associated subject
	*/
	virtual void 		SetTitle( const PMString& title, 
							bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue) = 0;
	/** Get the Title the progress bar. */
	virtual PMString	GetTitle() const = 0;

	/** Set the name of the current major task

		@param majorTask IN the name of the major task
		@param invalidate IN invalidate the associated control view
		@param notifyOfChange IN notify the associated subject
	*/
	virtual void 		SetMajorTaskName( const PMString& majorTask, 
							bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue) = 0;
	/** Get the name of the current major task. */
	virtual PMString	GetMajorTaskName() = 0;

	/** Set the name of the current minor task

		@param minorTask IN the name of the minor task
		@param invalidate IN invalidate the associated control view
		@param notifyOfChange IN notify the associated subject
	*/
	virtual void 		SetMinorTaskName( const PMString& minorTask, 
							bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue) = 0;
	/** Get the name of the current minor task. */
	virtual PMString	GetMinorTaskName() = 0;

	/** Set the Progress Bar style: eFixedRange, eBarberPole, eDocWindow. */
	virtual void 	SetStyle(ProgressBarStyle s) = 0;
	/** Get the Progress Bar style. */
	virtual ProgressBarStyle GetStyle() const = 0;

	/** Set the current task status string

		@param taskStatus IN status string
		@param invalidate IN invalidate the associated control view
		@param notifyOfChange IN notify the associated subject
	*/
	virtual void 		SetTaskStatus( const PMString& taskStatus, 
							bool16 invalidate = kTrue, 
							bool16 notifyOfChange = kTrue) = 0;
	/** Get the current task status string. */
	virtual PMString	GetTaskStatus() = 0;

	/** Set the "inner text" string (used in DrawBarText method of some progress bar implementations). */
	virtual void SetInnerText( const PMString& str ) = 0;
	/** Get the "inner text" string. */
	virtual PMString GetInnerText() = 0;
};

#endif
