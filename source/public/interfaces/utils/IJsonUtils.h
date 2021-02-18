//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/utils/IJsonUtils.h $
//  
//  Owner: swagarg
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
#ifndef __IJsonUtils__
#define __IJsonUtils__

#include <vector>
#include <map>
#include <string>

#include "boost/property_tree/json_parser.hpp"

class PUBLIC_DECL JSON;

typedef boost::property_tree::ptree Tree;
typedef std::vector<JSON> JSONArray;

class PUBLIC_DECL JSON
{
	Tree value;
public:
	/*
	Enumeration for different types part of json tree
	*/
	enum Type
	{
		type_List,
		type_Map,
		type_String,
		type_Number,
		type_Bool,
		type_Null
	};

	JSON(){}
	JSON(Tree inputValue) : value(inputValue){}
	Tree GetTree() { return value; }
	
	/*
	Gets string value for the key
	@param       [IN] key in json
	@return string value for the key
	*/
	std::string GetString(std::string key);
	std::string GetString();

	/*
	Gets numeric value for the key
	@param       [IN] key in json
	@return numeric value for the key
	*/
	uint64 GetNumber(std::string key);

	/*
	Gets JSON array list value for the key
	@param       [IN]  key in json
	@param		 [OUT] output json array list value for the key
	*/
	void GetListAt(std::string key, JSONArray &outputArray);

	/*
	Gets json value for the key
	@param       [IN]  key in json
	@param		 [OUT] output json value for the key
	*/
	void GetJSONAt(std::string key, JSON &output);
	
	/*
	Gets type of json key
	@param       [IN]  key in json
	@return	key type
	*/
	Type GetType(std::string key);

	/*
	Checks if valid value for key exists in json tree
	@param       [IN]  key in json
	@return	true if valid value for the key exists in json tree else false
	*/
	bool checkKey(std::string key);

	/*
	Checks if value for key is of type map in json tree
	@param       [IN]  key in json
	@return	true value for key is of type map in json tree else false
	*/
	bool isMap(std::string key);

	/*
	Checks if value for key is of type list in jsontree
	@param       [IN]  key in json
	@return	true value for key is of type list in jsontree else false
	*/
	bool isList(std::string key);

	/*
	Checks if value for key is of type number
	@param       [IN]  key in json
	@return	true value for key is of type number else false
	*/
	bool isNumber(std::string key);

	/*
	Checks if value for key is of type string
	@param       [IN]  key in json
	@return	true value for key is of type string else false
	*/
	bool isString(std::string key);

	/*
	Checks if value for key is of type bool in jsontree
	@param       [IN]  key in json
	@return	true value for key is of type bool in jsontree else false
	*/
	bool isBool(std::string key);

	/*
	Adds key and value to json tree
	@param       [IN]  key in json
	@param       [IN]  value in json
	*/
	void addValue(std::string key, std::string val);

	/*
	Reads the json tree from string stream
	@param sstream    [IN]  input stringstream which fills json tree
	*/
	void read_json(std::stringstream &sstream);

	/*
	Writes the json tree into string stream
	@param sstream    [OUT]  output stringstream filled with JSON tree
	@param isPretty   [IN]  if output is to be dumped in PrettyFormat.
	*/
	void write_json(std::stringstream &stream, bool ispretty = false);

	/*
	Writes the json tree into string
	@param sstream    [OUT]  output string filled with JSON tree
	@param isPretty   [IN]  if output is to be dumped in PrettyFormat.
	*/
	void write_json(std::string &str, bool ispretty = false);

};

#endif // __IJsonUtils__
