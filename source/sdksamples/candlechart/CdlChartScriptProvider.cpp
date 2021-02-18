//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartScriptProvider.cpp $
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
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IPageItemScriptUtils.h"
#include "INewPageItemCmdData.h"

// Implementation includes:
#include "CmdUtils.h"
#include "CScriptProvider.h"
#include "UIDList.h"

// Project includes:
#include "ChartCSVFile.h"
#include "CdlChartID.h"
#include "ICdlChartData.h"

/** From SDK sample; shows how to implement a script provider for a custom page item,
	kCdlChartPageItemBoss.

	See Scripting Resources defined in the plug-in's .fr file.
	
	@see kCdlChartPageItemBoss - the scriptable boss
	@see kCandleChartObjectScriptElement - the script object that exposes kCdlChartPageItemBoss in the Scripting DOM
	@see CdlChart.fr
	@see IPageItemScriptUtils
	@ingroup candlechart
*/
class CdlChartScriptProvider : public RepresentScriptProvider
{
public:
	/** Constructor
		@param boss the boss object this interface is aggregated onto
	*/
	CdlChartScriptProvider(IPMUnknown *boss);

	/** Destructor.
	*/
	virtual ~CdlChartScriptProvider();

	/** Called if a provider can handle a method/event.
		@param methodID identifies the ID of the method/event to handle.
		@param data identifies an interface pointer used to extract data.
		@param script identifies an interface pointer on the script object representing the parent of the application object.
	 */
	virtual ErrorCode		HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script);

	/** This method is called by the script manager if this provider can handle a specific property.
     *     @param propID identifies the ID of the property to handle.
     *     @param data identifies an interface pointer used to extract data.
     *     @param parent identifies an interface pointer on the script object representing the parent of the current object.
     */
    virtual ErrorCode  AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* parent);

protected:
	/**	Get the number of child objects in a collection on the given parent.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@return the number of child objects.
	 */
	virtual int32		GetNumObjects( const IScriptRequestData* data, IScript* parent );

	/**	Append the nth child object from a collection on the given parent.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@param n IN the index (0-based) of the desired child object in the collection.
		@param objectList OUT the nth child gets added to this list
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	virtual ErrorCode	AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList );

	/**	Append all child objects in a collection on the given parent.
		n is a 0-based index.
		@param data IN identifies the type of child object.
		@param parent IN references the owner of the collection.
		@param objectList OUT the objects in the collection.
		@return kSuccess on success, other ErrorCode otherwise.
	 */
	virtual ErrorCode	AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList );

private:
	/** Callback that creates a kCdlChartPageItemBoss, see IPageItemScriptUtils::DoCreatePageItem.
		@param data
		@param script
		@param parent
		@param bounds
		@param pageItem
		@param boundsSpace
	*/
	static ErrorCode CreateCandleChart(IScriptRequestData* data, IScript* script, IPMUnknown* parent, const PMPointList& bounds, UIDRef& pageItem, const Transform::CoordinateSpace& boundsSpace);

	/** Import candle chart data from csv file.
     *     @see HandleMethod
     */
    ErrorCode ImportCandleChartData(IScriptRequestData* data, IScript* script);

	/** AccessProperty calls this method to delegate access to the p_SnpRunnableName property.
     *     @see AccessProperty
     */
    ErrorCode AccessCandleChartName(IScriptRequestData* data, IScript* script);
};

/* Makes the implementation available to the application.
*/
CREATE_PMINTERFACE(CdlChartScriptProvider, kCdlChartScriptProviderImpl)

/*
*/
CdlChartScriptProvider::CdlChartScriptProvider(IPMUnknown *boss):
RepresentScriptProvider(boss)
{
}

/*
*/
CdlChartScriptProvider::~CdlChartScriptProvider()
{
}

/*
*/
int32 CdlChartScriptProvider::GetNumObjects( const IScriptRequestData* data, IScript* parent )
{
	return Utils<IPageItemScriptUtils>()->CountPageItemChildren(parent, data) ;
}

/*
*/
ErrorCode CdlChartScriptProvider::AppendNthObject( const IScriptRequestData* data, IScript* parent, int32 n, ScriptList& objectList )	//0-based index
{
	return Utils<IPageItemScriptUtils>()-> GetNthPageItemChild( n, parent, data, objectList );
}

/*
*/
ErrorCode CdlChartScriptProvider::AppendAllObjects( const IScriptRequestData* data, IScript* parent, ScriptList& objectList )
{
	return Utils<IPageItemScriptUtils>()-> GetEveryPageItemChild( parent, data, objectList );
}

/*
*/
ErrorCode CdlChartScriptProvider::HandleMethod(ScriptID methodID, IScriptRequestData* data, IScript* script)
{
	switch (methodID.Get())
	{
		case e_Create:
			return Utils<IPageItemScriptUtils>()->DoCreatePageItem(data, script, &this->CreateCandleChart);
		case e_ImportData:
			return ImportCandleChartData(data, script);
		default:
			return RepresentScriptProvider::HandleMethod(methodID, data, script);
	}
}

ErrorCode CdlChartScriptProvider::AccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
{
    switch (propID.Get())
    {
        case p_Name:
            return AccessCandleChartName(data, script);
    }

    return RepresentScriptProvider::AccessProperty(propID, data, script);
}


/** Create empty candle chart
*/
ErrorCode CdlChartScriptProvider::CreateCandleChart(IScriptRequestData* data, IScript* , IPMUnknown* parent, const PMPointList& bounds, UIDRef& pageItem, const Transform::CoordinateSpace& boundsSpace)
{
	UIDRef parentRef;
	ErrorCode result = Utils<IPageItemScriptUtils>()->PreparePageItemParent(data, parent, parentRef);
	ASSERT(result == kSuccess);
	if (result != kSuccess) {
		return kCdlChartCreatePageItemErrorCode;
	}
	PMRect bbox = PMRect(bounds[0], bounds[1]);

	// Create empty candle chart box
	InterfacePtr<ICommand> newCdlChartCmd(CmdUtils::CreateCommand(kNewCdlChartCmdBoss));
	InterfacePtr<INewPageItemCmdData> newData(newCdlChartCmd, UseDefaultIID());

	// Set options and fire the command
	newData->Set(parentRef.GetDataBase(), kCdlChartPageItemBoss, parentRef.GetUID(), bounds); 
	result = CmdUtils::ProcessCommand(newCdlChartCmd);

	if (result == kSuccess) 
	{
		pageItem = newCdlChartCmd->GetItemList()->GetRef(0);
		return kSuccess;
	}
	else
	{
		return kCdlChartCreatePageItemErrorCode;
	}
}
/** Import candle chart data
*/
ErrorCode CdlChartScriptProvider::ImportCandleChartData(IScriptRequestData* data, IScript* script)
{
	// Get the file to read data
	IDFile        csvFile;
    ScriptData    scriptData;

    ErrorCode err = data->ExtractRequestData(keyASPrepositionFrom, scriptData);
    if (err != kSuccess) 
		return kCdlChartImportDataErrorCode;
	else
	{
		err = scriptData.GetFile(&csvFile, data->GetRequestContext());
		CdlStockChartData newStockData;
		PMString fileNameStr;

		// Read the file and store the data into newStockData
		if (ChartCSVFile::LoadFile(csvFile, fileNameStr, newStockData))
		{
			// Set actual chart data read from CSV file
			InterfacePtr<ICommand> alterCdlChartCmd(CmdUtils::CreateCommand(kModifyCdlChartCmdBoss));
			InterfacePtr<ICdlChartData> cdlChartData(alterCdlChartCmd, UseDefaultIID());
			alterCdlChartCmd->SetItemList(UIDList(script));
			cdlChartData->Set(newStockData);
			cdlChartData->SetName(WideString(fileNameStr));

			err = CmdUtils::ProcessCommand(alterCdlChartCmd);
		}
		else
			return kCdlChartImportDataErrorCode;

	}

	if (err == kSuccess) 
	{
		return kSuccess;
	}
	else
	{
		return kCdlChartImportDataErrorCode;
	}
}

ErrorCode CdlChartScriptProvider::AccessCandleChartName(IScriptRequestData* data, IScript* script)
{
    int32 err = kSuccess;
    ScriptData scriptData;

	WideString name;
    InterfacePtr<ICdlChartData> chartData(script, IID_ICDLCHARTDATA);
    if (chartData)
        chartData->GetName(name);

    if (data->IsPropertyGet())
    {
        scriptData.SetWideString(name);
        data->AppendReturnData( script, p_Name, scriptData ) ;
    }
    else
    {
        err = data->ExtractRequestData(p_Name, scriptData);
        if (err != kSuccess) return err;

        WideString newName;
        err = scriptData.GetWideString(newName);
        if (err != kSuccess) return err;

		if (newName != name)
		{
			InterfacePtr<ICommand> alterCdlChartCmd(CmdUtils::CreateCommand(kModifyCdlChartCmdBoss));
			InterfacePtr<ICdlChartData> cdlChartData(alterCdlChartCmd, UseDefaultIID());
			alterCdlChartCmd->SetItemList(UIDList(script));
			// Set new chart data
			cdlChartData->Set(chartData->Get());
			cdlChartData->SetName(newName);

			err = CmdUtils::ProcessCommand(alterCdlChartCmd);
		}
    }

    return err;
}


// End, CdlChartScriptProvider.cpp.



