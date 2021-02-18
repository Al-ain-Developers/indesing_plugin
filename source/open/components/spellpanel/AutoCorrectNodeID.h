//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/spellpanel/AutoCorrectNodeID.h $
//  
//  Owner: Heath Horton
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

#ifndef __AUTOCORRECTNODEID__
#define __AUTOCORRECTNODEID__


#include "NodeID.h"
#include "IPMStream.h"
#include "SpellPanelID.h"
#include "WideString.h"

//========================================================================================
// class AutoCorrectNodeID 
//========================================================================================
class AutoCorrectNodeID : public NodeIDClass
{
public:
	enum { kNodeType = kAutoCorrectNodeIDClass };

	static	NodeID_rv		Create(const WideString& correctedName, const WideString& misspelledName) { return new AutoCorrectNodeID(correctedName, misspelledName); }

	virtual ~AutoCorrectNodeID() { }
	
	virtual NodeType		GetNodeType() const { return kNodeType; }
	virtual int32			Compare(const NodeIDClass* NodeIDClass) const;
	virtual NodeIDClass*	Clone() const;
	virtual void			Read(IPMStream*	stream);
	virtual void			Write(IPMStream* stream) const;
	virtual PMString        GetDescription() const;

	const WideString&		GetMisspelledName() const { return fMisspelledName; }
	const WideString&		GetCorrectedName() const { return fCorrectedName; }
			
private:
	AutoCorrectNodeID(const WideString& correctedName, const WideString& misspelledName);
		
	WideString fMisspelledName;
	WideString fCorrectedName;
};

#endif // __AUTOCORRECTNODEID__
