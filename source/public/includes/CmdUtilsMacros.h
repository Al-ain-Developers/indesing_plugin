//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CmdUtilsMacros.h $
//  
//  Owner: Manish Jangir
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2019 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//
//	This header is for private use only. 
//
//
//========================================================================================

#ifndef __CMDUTILSMACROS__
#define __CMDUTILSMACROS__

#define EXPANDER_IN(x) #x

#define EXPANDER(x) EXPANDER_IN(x)

#define LOCATION(S,L) EXPANDER(S) ":" EXPANDER(L)

/**
To be used when Command Sequence is to be created with Tracking data. 
@Usage: ICommandSequence* seq = CMDUTILS_BEGINCOMMANDSEQ(__FILE__,__LINE__)

*/
#define CMDUTILS_BEGINCOMMANDSEQ(S1,S2) CmdUtils::BeginCommandSequence(LOCATION(S1,S2))

/**
To be used when Abortable Command Sequence is to be created with Tracking data. 
@Usage: IAbortableCmdSeq* seq = CMDUTILS_BEGINABORTABLECMDSEQ(__FILE__,__LINE__)

*/

#define CMDUTILS_BEGINABORTABLECMDSEQ(S1,S2) CmdUtils::BeginAbortableCmdSeq(LOCATION(S1,S2))

/**
	FOR INTERNAL USE ONLY
*/
#define QACMDUTILS_BEGINCOMMANDSEQ(S1,S2) QACmdUtils::BeginCommandSequence(LOCATION(S1,S2))

/**
	FOR INTERNAL USE ONLY
*/
#define QACMDUTILS_BEGINABORTABLECMDSEQ(S1,S2) QACmdUtils::BeginAbortableCmdSeq(LOCATION(S1,S2))

/**
	FOR INTERNAL USE ONLY
*/
#define CONCAT_NAMES(S1,S2) LOCATION(S1,S2)

#endif