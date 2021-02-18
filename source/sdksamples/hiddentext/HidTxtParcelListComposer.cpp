//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtParcelListComposer.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "ITextParcelListComposer.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "HidTxtID.h"

/** Stub ITextParcelListComposer implementation, display of composed  
	hidden text is not supported.

	
	@ingroup hiddentext
	@see ITextParcelListComposer
 */
class HidTxtParcelListComposer : public CPMUnknown<ITextParcelListComposer>
{
	public:
		/** Constructor.
			@param boss
		 */
						HidTxtParcelListComposer(IPMUnknown * boss);
		
		/** Destructor.
		 */
		virtual			~HidTxtParcelListComposer();

		// This is a stub, no documentation comments are provided.
		// See ITextParcelListComposer for all further information.
	public:
		virtual void	RecomposeThruLastParcel();
		virtual void	RecomposeThru(ParcelKey key);
		virtual void	RecomposeThruTextIndex(TextIndex composeUpThruThisIndex);
};

/*
*/
CREATE_PMINTERFACE(HidTxtParcelListComposer, kHidTxtParcelListComposerImpl)

/*
*/
HidTxtParcelListComposer::HidTxtParcelListComposer(IPMUnknown* boss) : CPMUnknown<ITextParcelListComposer>(boss)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListComposer::Constructor()-->In/Out\n");
}

/*
*/
HidTxtParcelListComposer::~HidTxtParcelListComposer()
{
	TRACEFLOW("HiddenText", "HidTxtParcelListComposer::Destructor()-->In/Out\n");
}

/*
*/
void HidTxtParcelListComposer::RecomposeThruLastParcel()
{
	TRACEFLOW("HiddenText", "HidTxtParcelListComposer::RecomposeThruLastParcel()-->In/Out\n");
}

/*
*/
void HidTxtParcelListComposer::RecomposeThru(ParcelKey)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListComposer::RecomposeThru()-->In/Out\n");
}

/*
*/
void HidTxtParcelListComposer::RecomposeThruTextIndex(TextIndex composeUpThruThisIndex)
{
	TRACEFLOW("HiddenText", "HidTxtParcelListComposer::RecomposeThruTextIndex()-->In/Out\n");
}

