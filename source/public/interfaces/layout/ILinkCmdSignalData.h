//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILinkCmdSignalData.h $
//  
//  Owner: Dave Burnard
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
//  
//  Purpose:	Data sent with the new Link Command signals
//  
//========================================================================================

#pragma once
#ifndef __ILINKCMDSIGNALDATA__
#define __ILINKCMDSIGNALDATA__

#include "IPMUnknown.h"
#include "LinksID.h"

class ICommand;

/**	ILinkCmdSignalData is the data sent with with the Link Command signals.
	
	@see ISignalMgr
	@see IResponder
*/
class ILinkCmdSignalData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILINKCMDSIGNALDATA };
	
	/** Set the link command signal data.
	
		@param linkCmd IN the link command for which this signal is being sent
		@param db IN the database this command is targeting
		@param uiflags IN UI control flags (kFullUI, kSuppressUI, kMinimalUI) 
	*/
	virtual void Set(ICommand* linkCmd, IDataBase* db, UIFlags uiflags = kFullUI) = 0;

	/**	Get the link command for which this signal is being sent
		
		@return the command.
	*/
	virtual ICommand*	GetCommand() const = 0;

	/**	Get the database this command is targeting
		
		@return the database.
	*/
	virtual IDataBase* 	GetDataBase() const = 0;

	/**	Get the UI control flags
		
		@return the UI control flags (kFullUI, kSuppressUI, kMinimalUI).
	*/
	virtual const UIFlags GetUIFlags() const = 0;				// the ui behaviour
};

#endif // __ILINKCMDSIGNALDATA__

