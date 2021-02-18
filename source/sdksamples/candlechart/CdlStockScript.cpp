//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlStockScript.cpp $
//  
//  Owner: Shengliu Dai
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
#include "CProxyScript.h"

#include "ICdlChartData.h"
#include "IIntData.h"

#include "CScript.h"
#include "CdlChartID.h"

/** From SDK sample; shows how to implement a proxy script object,
	kCdlStockScriptObjectBoss.

	See Scripting Resources defined in the plug-in's .fr file.
	
	@see kCdlStockScriptObjectBoss - the proxy object boss
	@see kCandleStockObjectScriptElement - the script object defintion
	@see CdlChart.fr
	@ingroup candlechart
*/
class CdlStockScript : public CProxyScript
{
public:
	CdlStockScript( IPMUnknown* boss ) : CProxyScript( boss ) {}

	virtual bool16 HasBeenDeleted(const RequestContext& context) ;
} ;

CREATE_PMINTERFACE( CdlStockScript, kCdlStockScriptImpl )

bool16 CdlStockScript::HasBeenDeleted(const RequestContext& context)
{
	InterfacePtr<ICdlChartData>	stockdata( (ICdlChartData*) QueryParent( IID_ICDLCHARTDATA, context ) ) ;
	InterfacePtr<IIntData> indexData( this, IID_IINTDATA ) ;

	if ( stockdata != nil && indexData != nil )
	{
		int32 numCdlStocks = stockdata->Get().size() ;
		int32 cdlStockIndex = indexData->GetInt() ;	//0-based index
		if ( cdlStockIndex >= 0 && numCdlStocks > cdlStockIndex )
			return kFalse ;
	}

	return kTrue ;
}
