//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basictextadornment/BscTAAttrReport.cpp $
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

// Interfaces:
#include "IDrawingStyle.h"
#include "IAttrReport.h"
#include "ITextAttrBoolean.h"

// General:
#include "CPMUnknown.h"
#include "BuildNumber.h"

// Project:
#include "BscTAID.h"



/** Provides a custom character attribute.  The visible adornment
	is provided by BscTAAdornment. 
	See kBscTAAttrBoss and kBscTAAdornmentBoss.
	
	Most of the behavior specified in BscTAAttrReport is based on a 
	fundamental character attribute (specified privately), except that 
	CanBeInStyle() is set to kFalse due to the lack of the UI to set this 
	particular attribute when creating styles.

	Implements IAttrReport using the CPMUnknown helper class.

	@ingroup basictextadornment
	, John Hake
*/
class BscTAAttrReport : public CPMUnknown<IAttrReport>
{
	public:
		/** Constructor 
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		BscTAAttrReport(IPMUnknown* boss) :
			CPMUnknown<IAttrReport>(boss)
			{}

		/**	We implement a character attribute so we return kFalse. 
		*/
		virtual bool16 IsParagraphAttribute(void) const;
		
		/** We don't want style changes to blow away our attribute so we return kTrue. 
		*/
		virtual bool16 LastsThroughStyleChange(void) const;
		
		/** Specifies if the attribute continues if the user types text at the 
			end of the run of characters to which the attribute applies. 
			
			@return ContinuationType specifies how you the attribute will continue.
			NOTE: The API has changed since InDesign 2.0 Beta. <BR>
			(Beta) bool16 BscTAAttrReport::AutomaticContinuation(void) const<BR>
			(RC) IAttrReport::ContinuationType BscTAAttrReport::AutomaticContinuation(void) const<BR>
		*/
		virtual IAttrReport::ContinuationType AutomaticContinuation(void) const;
		
        /** Specifies whether the attribute can be part of a style.
			NOTE: This method has been added since InDesign 2.0 beta. 
		*/
		virtual bool16 CanBeInStyle(void) const;

		/** Specifies whether the attribute can stay after a search/replace operation.
			NOTE: This method has been added since InDesign 2.0 beta. 
		*/
		virtual bool16 SurvivesReplace(void) const;

		/**	Specifies whether the attribute should be omitted from the focus cache.
			NOTE: This method has been added since InDesign 2.0 beta. 
		*/
		virtual bool16 OmitFromFocusCache(void) const;

		/** Specifies if/when the attribute requires recomposition.
			
			@return RecompositionLevel specifies when the attribute requires recomposition.
			
			NOTE: The API has changed since InDesign 2.0 Beta. <BR>
			(Beta) bool16 BscTAAttrReport::RequiresRecomposition(void) const<BR>
			(RC) IAttrReport::RecompositionLevel BscTAAttrReport::RequiresRecomposition(void) const<BR>
		*/
		virtual IAttrReport::RecompositionLevel RequiresRecomposition(void) const;
		
		/** This is the hook we use to add/remove our adornment to the text so that 
			when the frame is drawn our adornment will be drawn on screen. 
			Called by the composer as it composes the text in a frame.
			See BscTAAdornmentBoss::Draw() to see how the adornment is drawn.
			
			@param compositionStyle The composition style interface that describes the settings of the 
						currently used composer. 
			@param drawingStyle The drawing style interface	that describes visually oriented settings.
						We use the IDrawingStyle::AddTextAdornment() method to add our 
						custom text adornment. 
		*/
		virtual void TellComposition(ICompositionStyle* compositionStyle, IDrawingStyle* drawingStyle) const;

		/** Appends our attribute description. 
		
			@param into The PMString that holds the description.  
			@param theDB The current database. (Not used)
			@param attrBossList The attribute boss list that contains other attributes applied. (Not used). 
		*/
		virtual void AppendDescription(PMString* into, IDataBase* theDB, const AttributeBossList* attrBossList) const;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(BscTAAttrReport, kBscTAAttrReportImpl);


/*	IsParagraphAttribute
*/
bool16 BscTAAttrReport::IsParagraphAttribute(void) const
{
	TRACEFLOW("BasicTextAdornment", "BscTAAttrReport::IsParagraphAttribute()\n");
	return kFalse;
}


/*	LastsThroughStyleChange
*/
bool16 BscTAAttrReport::LastsThroughStyleChange(void) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::LastsThroughStyleChange()\n");
	return kFalse;
}


/*	AutomaticContinuation
*/
IAttrReport::ContinuationType BscTAAttrReport::AutomaticContinuation(void) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::AutomaticContinuation()\n");
	return IAttrReport::kAlwaysContinue;
}


/* CanBeInStyle
*/
bool16 BscTAAttrReport::CanBeInStyle(void) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::CanBeInStyle()\n");
	return kFalse;
}

/* SurvivesReplace
*/
bool16 BscTAAttrReport::SurvivesReplace(void) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::SurvivesReplace()\n");
	return kTrue;
}

/* OmitFromFocusCache
*/
bool16 BscTAAttrReport::OmitFromFocusCache(void) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::OmitFromFocusCache()\n");
	return kFalse;
}

/*	RequiresRecomposition
*/
IAttrReport::RecompositionLevel BscTAAttrReport::RequiresRecomposition(void) const
{
	TRACEFLOW("BasicTextAdornment", "BscTAAttrReport::RequiresRecomposition()\n");
	return IAttrReport::kRequiresRecomposition;
}

/*	TellComposition
*/
void BscTAAttrReport::TellComposition(ICompositionStyle* compositionStyle, IDrawingStyle* drawingStyle) const
{
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::TellComposition()\n");
	do 
	{
		ASSERT(drawingStyle);
		if (drawingStyle == nil) 
		{
			break;
		}

		// Get the current state of the attribute (boolean)		
		InterfacePtr<ITextAttrBoolean> attrFlag(this, UseDefaultIID());
		if (attrFlag == nil) 
		{
			break;
		}

		// Add the adornment ONLY if the attribute is enabled.
		bool16 attrState = attrFlag->Get();

		// Activate or Deactivate our adornment
		// See BscTAAdornment.cpp for details on how it's drawn
		drawingStyle->AddTextAdornment(kBscTAAttrBoss,		// Class ID of attribute.
									   (attrState == kTrue) ? kBscTAAdornmentBoss : kInvalidClass,	// Class ID of adornment.
									   nil);				// No ITextAdornmentData*.
	} while (false);
}

/*	AppendDescription
*/
void BscTAAttrReport::AppendDescription(PMString* into, IDataBase* theDB, const AttributeBossList* attrBossList) const
{
	ASSERT(into);
	TRACEFLOW("BasicTextAdornment","BscTAAttrReport::AppendDescription()\n");

	// Append the description of this character attribute.
	InterfacePtr<const ITextAttrBoolean> state(this, UseDefaultIID());
	if (state && state->Get())
	{
		// Adornment is on.
		PMString conjunction(" + ", PMString::kTranslateDuringCall);
		into->Append(conjunction);
	}
	else
	{
		// Adornment is off.
		PMString conjunction(" - ", PMString::kTranslateDuringCall);
		into->Append(conjunction);
	}
	PMString attrDescr(kBscTACharAttrDescrStringKey, PMString::kTranslateDuringCall);
	into->Append(attrDescr);
}

// End, BscTAAttrReport.cpp.


