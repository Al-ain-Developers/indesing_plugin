//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IBlackBoxCommands.h $
//  
//  Owner: Robin_Briggs
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

#pragma once
#ifndef __IBlackBoxCommands__
#define __IBlackBoxCommands__


#include "IPMUnknown.h"
#include "DocFrameworkID.h"
#include "IBlackBoxData.h"		// for BlackBoxKey

class XMLReference;

/** This is an interface to a container for generic data. Use this interface if you want
	to attach data to an InDesign document, but you want complete control and responsibility
	over how the data is managed.
*/
class IBlackBoxCommands : public IPMUnknown {
public:
	enum { kDefaultIID = IID_IBLACKBOXCOMMANDS };

	/** Processes a command to add data to a UID-based object's black box.
		@param obj		specify which object gets the data
		@param key		what key the data will be stored under for later refetch
		@param buffer	buffer containing the data to write
		@param length	number of bytes to write
		@return ErrorCode	kSuccess or failure code if operation is unsuccessful
	*/
	virtual ErrorCode AddData(const UIDRef& obj, BlackBoxKey key, void *buffer, int32 length) = 0;
	
	/** Processes a command to add data to an XML element's black box. 
		@param obj		specify which object gets the data
		@param key		what key the data will be stored under for later refetch
		@param buffer	buffer containing the data to write
		@param length	number of bytes to write
		@return ErrorCode	kSuccess or failure code if operation is unsuccessful
	*/
	virtual ErrorCode AddData(const XMLReference& obj, BlackBoxKey key, void *buffer, int32 length) = 0;
	
	/** Processes a command to remove data from the UID-based object's black box.
		@param obj		specify which object to remove from 
		@param key		what key the data was be stored under originally
		@return ErrorCode	kSuccess or failure code if operation is unsuccessful
	*/
	virtual ErrorCode RemoveData(const UIDRef& obj, BlackBoxKey key) = 0;
	
	/** Processes a command to remove data from an XML element's black box.
		@param obj		specify which object to remove from 
		@param key		what key the data was be stored under originally
		@return ErrorCode	kSuccess or failure code if operation is unsuccessful
	*/
	virtual ErrorCode RemoveData(const XMLReference& obj, BlackBoxKey key) = 0;
	
	/** Processes a command to retrieve data from the UID-based object's black box.
	@param obj		specify which object to get 
	@param key		what key the data was be stored under originally
	@param buffer	OUT buffer where the data will be put
	@param amountToRead	maximum amount to read
	@return int32	number of bytes in output buffer
	*/
	virtual int32 GetData(const UIDRef& obj, BlackBoxKey key, void *buffer, int32 amountToRead) = 0;
	
	/** Processes a command to retrieve data from the XML element's black box.
	@param obj		specify which object to get 
	@param key		what key the data was be stored under originally
	@param buffer	OUT buffer where the data will be put
	@param amountToRead	maximum amount to read
	@return int32	number of bytes in output buffer
	*/
	virtual int32 GetData(const XMLReference& obj, BlackBoxKey key, void *buffer, int32 amountToRead) = 0;
	

};



#endif // __IBlackBoxCommands__
