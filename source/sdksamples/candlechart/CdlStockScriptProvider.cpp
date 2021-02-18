//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlStockScriptProvider.cpp $
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
#include "CScriptProvider.h"

#include "IIntData.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "ICdlChartData.h"
#include "IIntData.h"

#include "CScript.h"
#include "CdlChartID.h"
#include "CmdUtils.h"
#include "UIDList.h"


/** From SDK sample; shows how to implement a script provider for proxy script object,
	kCdlStockScriptObjectBoss.

	See Scripting Resources defined in the plug-in's .fr file.
	
	@see kCdlStockScriptObjectBoss - the proxy object boss
	@see kCandleStockObjectScriptElement - the script object defintion
	@see CdlChart.fr
	@ingroup candlechart
*/

class CdlStockScriptProvider : public RepresentScriptProvider
{
	typedef RepresentScriptProvider Inherited ;

public:
	CdlStockScriptProvider( IPMUnknown* boss ) ;
	~CdlStockScriptProvider() ;

	virtual ErrorCode		HandleMethod( ScriptID methodID, IScriptRequestData* data, IScript* script ) ;
	virtual ErrorCode		AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script ) ;

protected:
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent ) ;
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList ) ;	//0-based index

private:
	ErrorCode DeleteCdlStock( IScriptRequestData* data, IScript* script ) ;
	ErrorCode CreateCdlStock( IScriptRequestData* data, IScript* parent ) ;

	ErrorCode AccessOneCdlStockProperty( ScriptID propID, IScriptRequestData* data, IScript* script );

	static int32 GetCdlStockIndex( IPMUnknown* cdlStock ) ;						//0-based index
	IScript* QueryCdlStock( const IScriptRequestData* data, IScript* parent, int32 n ) ;						//0-based index

} ;

CREATE_PMINTERFACE( CdlStockScriptProvider, kCdlStockScriptProviderImpl )

CdlStockScriptProvider::CdlStockScriptProvider( IPMUnknown* boss ) :
	Inherited( boss )
{
}

CdlStockScriptProvider::~CdlStockScriptProvider()
{
}


ErrorCode CdlStockScriptProvider::HandleMethod( ScriptID methodID, IScriptRequestData* data, IScript* script )
{
	switch ( methodID.Get() )
	{
		case e_Delete :
			return DeleteCdlStock( data, script ) ;
		case e_Create :
			return CreateCdlStock( data, script ) ;
		default:
			return Inherited::HandleMethod( methodID, data, script ) ;
	}
}

ErrorCode CdlStockScriptProvider::AccessProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	switch ( propID.Get() )
	{
		case p_CdlStackOpen :
		case p_CdlStackHigh :
		case p_CdlStackLow :
		case p_CdlStackClose:
		case p_CdlStackVolume:
			return AccessOneCdlStockProperty(propID, data, script ) ;
	}

	return Inherited::AccessProperty( propID, data, script ) ;
}


int32 CdlStockScriptProvider::DeleteCdlStock( IScriptRequestData* data, IScript* script )
{
	ErrorCode err = kSuccess ;

 	int32 cdlStockIndex = GetCdlStockIndex( script ) ;
	InterfacePtr<ICdlChartData>	stockdata( (ICdlChartData*)script->QueryParent( IID_ICDLCHARTDATA, data->GetRequestContext() ) ) ;

	if (stockdata)
	{
		WideString name;
        stockdata->GetName(name);	
		CdlStockChartData stocks = stockdata->Get();

		stocks.erase(stocks.begin() + cdlStockIndex);

		InterfacePtr<ICommand> alterCdlChartCmd(CmdUtils::CreateCommand(kModifyCdlChartCmdBoss));
		InterfacePtr<ICdlChartData> cdlChartData(alterCdlChartCmd, UseDefaultIID());
		alterCdlChartCmd->SetItemList(UIDList(stockdata));

		// Set new chart data
		cdlChartData->Set(stocks);
		cdlChartData->SetName(name);

		err = CmdUtils::ProcessCommand(alterCdlChartCmd);

	}

	return err ;
}

int32 CdlStockScriptProvider::CreateCdlStock( IScriptRequestData* data, IScript* parent )
{
	ScriptData	scriptData;
	ErrorCode err = kFailure ;

	InterfacePtr<ICdlChartData>	stockdata( parent, IID_ICDLCHARTDATA  ) ;

	if (stockdata)
	{
		WideString name;
        stockdata->GetName(name);	
		CdlStockChartData stocks = stockdata->Get();

		CdlStockData stockData;  // constrcut a default stock data
		// Add code here to get 5 doubles from script (if available)
		stocks.push_back(stockData);

		InterfacePtr<ICommand> alterCdlChartCmd(CmdUtils::CreateCommand(kModifyCdlChartCmdBoss));
		InterfacePtr<ICdlChartData> cdlChartData(alterCdlChartCmd, UseDefaultIID());
		alterCdlChartCmd->SetItemList(UIDList(stockdata));

		// Set new chart data
		cdlChartData->Set(stocks);
		cdlChartData->SetName(name);

		err = CmdUtils::ProcessCommand(alterCdlChartCmd);

		int32 newCdlStockIndex = GetNumObjects(data, parent) - 1 ;
		ScriptList scriptList ;
		err = AppendNthObject( data, parent, newCdlStockIndex, scriptList ) ;

		if ( scriptList.size() > 0 )
		{
			IScript* newScript = scriptList[0] ;
			data->AppendReturnData( parent, e_Create, ScriptData( newScript ) ) ;

			err = kSuccess ;
		}
	}

	return err ;
}

ErrorCode CdlStockScriptProvider::AccessOneCdlStockProperty( ScriptID propID, IScriptRequestData* data, IScript* script )
{
	ErrorCode err = kSuccess ;
	ScriptData scriptData;

 	int32 cdlStockIndex = GetCdlStockIndex( script ) ;
	InterfacePtr<ICdlChartData>	stockdata( (ICdlChartData*)script->QueryParent( IID_ICDLCHARTDATA, data->GetRequestContext() ) ) ;

	if (stockdata)
	{
		WideString name;
        stockdata->GetName(name);	
		CdlStockChartData stocks = stockdata->Get();
		PMReal value;

		if ( data->IsPropertyGet() )
		{
			switch ( propID.Get() )
			{
				case p_CdlStackOpen :
					value = stocks[cdlStockIndex].open;
					break;
				case p_CdlStackHigh :
					value = stocks[cdlStockIndex].high;
					break;
				case p_CdlStackLow :
					value = stocks[cdlStockIndex].low;
					break;
				case p_CdlStackClose:
					value = stocks[cdlStockIndex].close;
					break;
				case p_CdlStackVolume:			
					value = stocks[cdlStockIndex].volume;
					break;
			}
			scriptData.SetPMReal(value);
			data->AppendReturnData( script, propID, scriptData ) ;
			return kSuccess;
		}
		else if (data->IsPropertyPut())
		{
			err = data->ExtractRequestData( propID.Get(), scriptData ) ;

			err = scriptData.GetPMReal(&value);
			
			if (err != kSuccess) return ( err);	

			// set data
			switch ( propID.Get() )
			{
				case p_CdlStackOpen :
					stocks[cdlStockIndex].open = ToDouble(value) ;
					break;
				case p_CdlStackHigh :
					stocks[cdlStockIndex].high = ToDouble(value) ;
					break;
				case p_CdlStackLow :
					stocks[cdlStockIndex].low = ToDouble(value) ;
					break;
				case p_CdlStackClose:
					stocks[cdlStockIndex].close = ToDouble(value) ;
					break;
				case p_CdlStackVolume:			
					stocks[cdlStockIndex].volume = ToDouble(value) ;
					break;
			}			

			InterfacePtr<ICommand> alterCdlChartCmd(CmdUtils::CreateCommand(kModifyCdlChartCmdBoss));
			InterfacePtr<ICdlChartData> cdlChartData(alterCdlChartCmd, UseDefaultIID());
			alterCdlChartCmd->SetItemList(UIDList(stockdata));

			// Set new chart data
			cdlChartData->Set(stocks);
			cdlChartData->SetName(name);

			err = CmdUtils::ProcessCommand(alterCdlChartCmd);
		}
	}

	return err ;
}


///////////////////////////////////////////////////////////////////////////////////////////
//	HELPERS
///////////////////////////////////////////////////////////////////////////////////////////

int32 CdlStockScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	ASSERT( data->GetDesiredType() == c_CandleStock ) ;
	int32 count = 0 ;

	InterfacePtr<ICdlChartData>	stockdata( parent, IID_ICDLCHARTDATA  ) ;
	if (stockdata)
	{
		count = (int32) stockdata->Get().size();
	}
	return count ;
}

ErrorCode CdlStockScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	ASSERT( data->GetDesiredType() == c_CandleStock ) ;
	ASSERT_MSG( n >= 0 && n < GetNumObjects( data, parent ), "Index out of bounds" ) ;
	InterfacePtr<IScript> cdlStockScript(QueryCdlStock( data, parent, n )) ;
	if ( cdlStockScript != nil )
		objectList.push_back( cdlStockScript ) ;
	return kSuccess ;
}

int32 CdlStockScriptProvider::GetCdlStockIndex( IPMUnknown* cdlStock )				//0-based index
{
	int32 index = -1 ;

	InterfacePtr<IIntData> indexData( cdlStock, IID_IINTDATA ) ;
	if ( indexData != nil )
		index = indexData->GetInt() ;

	return index ;
}

IScript* CdlStockScriptProvider::QueryCdlStock( const IScriptRequestData* data, IScript* parent, int32 n )					//0-based index
{
	IScript* cdlStock = Utils<IScriptUtils>()->CreateProxyScriptObject( data->GetRequestContext(), kCdlStockScriptObjectBoss, c_CandleStock, parent, n ) ;
	ASSERT_MSG( cdlStock != nil, "cdlStock is nil" ) ;
	return cdlStock ;
}
