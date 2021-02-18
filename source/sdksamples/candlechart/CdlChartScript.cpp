//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartScript.cpp $
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
#include "IPageItemScriptUtils.h"
#include "Utils.h"

// Implementation includes:
#include "CScript.h"
#include "CdlChartID.h"

/** From SDK sample; shows how to implement CScript for this plug-in's scriptable custom page item,
	kCdlChartPageItemBoss.

	@see kCdlChartPageItemBoss
	@see CdlChartScriptProvider
	@ingroup candlechart
*/
class CdlChartScript : public CScript
{
public:
	/**	Constructor 
		@param boss interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartScript(IPMUnknown* boss);

	/** Destructor.  
	*/
	virtual ~CdlChartScript(void);

	/** Return the object's type.
		@return The object's ScriptID.
	 */
	virtual ScriptID GetObjectType(const RequestContext& context) const;

	/** Set the object's type.
	*/
	virtual void			SetObjectType( const ScriptID& type, const RequestContext& context );

	/**	Return the parent of this object in the script DOM hierarchy.
		IDOMElement::QueryParent delegates to this method. 
		@param iid IN IID of interest on the parent DOM object.
		@return An interface pointer to the IID of interest on the parent DOM object. 
	 */
	virtual IPMUnknown* QueryParent(const PMIID& iid, const RequestContext& context) const ;
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CdlChartScript, kCdlChartScriptImpl)


/* 
*/
CdlChartScript::CdlChartScript(IPMUnknown* boss)
: 	CScript(boss)
{
	// do nothing
}

/* 
*/
CdlChartScript::~CdlChartScript(void)	
{
	// do nothing
}

/*
*/
void CdlChartScript::SetObjectType( const ScriptID& type, const RequestContext& context )
{
	ASSERT(type == c_CandleChart);
}

/* 
*/
ScriptID CdlChartScript::GetObjectType(const RequestContext& context) const
{
	return c_CandleChart;
}

/*  
*/
IPMUnknown* CdlChartScript::QueryParent(const PMIID& iid, const RequestContext& context) const
{
	IPMUnknown* parent = nil;

	InterfacePtr<IScript> parentScript ( Utils<IPageItemScriptUtils>()->QueryPageItemParent( (IScript*) this, context ) );
	if ( parentScript != nil )
		parent = parentScript->QueryInterface( iid ) ;

	return parent ;
}

// End, CdlChartScript.cpp.



