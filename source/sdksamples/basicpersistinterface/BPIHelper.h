//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicpersistinterface/BPIHelper.h $
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

#ifndef _BPIHelper_h_
#define _BPIHelper_h_

class ITextFrameColumn;
class UIDList;

/** Facade that helps manipulate IBPIData.
	
	@ingroup basicpersistinterface
	
*/
class BPIHelper
{
public:
	/** Contructor
	*/
	BPIHelper(void);
	
	/** Destructor
	*/
	virtual	~BPIHelper (void);

	/**
		Return kTrue if one of the given objects has IBPIData.
		@param itemList list of objects to examine for IBPIData capability.
		@return kTrue if one of the given objects has IBPIData.
	*/
	virtual bool16 HasBPIData(const UIDList& itemList);

	/**
		Get all unique IBPIData values that apply to the given objects.
		@param itemList IN of objects for which the IBPIData is wanted.
		@param values OUT unique IBPIData values found in the given objects.
		If two items have the same IBPIData value only one attribute with 
		this value will be returned in the vector.
	*/
	virtual void GetBPIData(const UIDList& itemList, K2Vector<WideString>& values);

	/**
		Filter the given objects leaving only objects that have IBPIData.
		@param itemList list of objects to be filtered
	*/
	virtual void FilterForBPIData(UIDList& itemList);
	
	/**
		Process kBPISetDataCmdBoss to set the IBPIData for the given objects.
		@param itemList IN list of objects for which the IBPIData value is to be changed
		@param value IN IBPIData value
		@return kSuccess on success, other ErrorCode otherwise
	*/
	virtual ErrorCode ProcessBPISetDataCmd(const UIDList& itemList, const WideString& value);

	/**
		Find the graphic frame, the spline, that is associated with the given textFrameColumn.
		@param textFrameColumn 
		@return UID of the frame associated with the given textFrameColumn
	*/
	UID FindAssociatedGraphicFrame(const InterfacePtr<ITextFrameColumn>& textFrameColumn);
};

#endif // _BPIHelper_

// End, BPIHelper.h


