//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customconditionaltext/CustomConditionTag.cpp $
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
#include "IPMStream.h"

// General includes:

// Project includes:
#include "CusCondTxtID.h"
#include "ICustomConditionTag.h"

class CustomConditionTag : public CPMUnknown<ICustomConditionTag>
{
	public:
		/** Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		CustomConditionTag(IPMUnknown* boss);
		/** Destructor.
		*/
		virtual ~CustomConditionTag() {}
		
		/** @see ICustomConditionTag.
		 */
		virtual void SetPrintVisible(bool16 visible);
		
		/** @see ICustomConditionTag.
		 */		
		virtual bool16 IsPrintVisible();

		/** @see ICustomConditionTag.
		 */
		virtual void SetIdmlVisible(bool16 visible);
		
		/** @see ICustomConditionTag.
		 */
		virtual bool16 IsIdmlVisible();		
	
		void ReadWrite(IPMStream*  stream, ImplementationID implementation);

	private:
		bool16 fPrintVisible;
		
		bool16 fIdmlVisible;
};

CREATE_PERSIST_PMINTERFACE(CustomConditionTag, kCusCondTxtTagImpl)

CustomConditionTag::CustomConditionTag(IPMUnknown* boss) : 
					CPMUnknown<ICustomConditionTag>(boss),
					fPrintVisible(kTrue),
					fIdmlVisible(kTrue)
{
}

void CustomConditionTag::SetPrintVisible(bool16 visible)
{
	PreDirty ();
	fPrintVisible = visible;
}
		
bool16 CustomConditionTag::IsPrintVisible()
{
	return fPrintVisible;
}

void CustomConditionTag::SetIdmlVisible(bool16 visible)
{
	PreDirty ();
	fIdmlVisible = visible;
}
		
bool16 CustomConditionTag::IsIdmlVisible()
{
	return fIdmlVisible;
}
	
void CustomConditionTag::ReadWrite(IPMStream*  stream, ImplementationID implementation)
{
	stream->XferBool(fPrintVisible);
	stream->XferBool(fIdmlVisible);
}


