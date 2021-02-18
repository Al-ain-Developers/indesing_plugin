//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/PMTimer.h $
//  
//  Owner: Frits Habermann
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
#ifndef __PMTimer__
#define __PMTimer__

#ifdef DEBUG

#pragma export on

class PUBLIC_DECL Timer
{
public:
	Timer(char *startString = nil, char *endString = nil);
		//Start timing an operation
	~Timer();
		//Stop timing an operation. Reports elapsed tick count to the debug window using Trace
private:
	int32	fElapsedTime;
	std::string	*fStartString, *fEndString;
};

#pragma export off

#endif		// DEBUG

#endif
