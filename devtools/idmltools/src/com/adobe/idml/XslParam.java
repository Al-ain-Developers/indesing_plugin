//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/XslParam.java $
//  
//  Owner: Joe Stinson
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 2008 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

package com.adobe.idml;

/**
 * This class stores a single parameter name/value pair
 * These parameters are used to add parameters from the Java application to the XSL StyleSheets at transform time.
 * Note: Maps were not used to store name/value pairs because duplicate names will need to be stored.
 */
public class XslParam
{	
	private String fParamName;
	private String fParamValue;
	
	/**
	 * This constructor loads the parameter name and value.
	 * @param paramName	The name of the XSL parameter.
	 * @param paramValue The value for the XSL parameter.
	 */
	public XslParam(String paramName, String paramValue)
	{
		fParamName = paramName;
		fParamValue = paramValue;
	}
	
	/**
	 * Get the parameter name.
	 * @return The name of the parameter.
	 */
	public String getName()
	{
		return fParamName;
	}
	
	/**
	 * Get the parameter value
	 * @return The value for the parameter. 
	 */
	public String getValue()
	{
		return fParamValue;
	}
}
