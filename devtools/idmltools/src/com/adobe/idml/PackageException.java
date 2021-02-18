//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/PackageException.java $
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
//  ADOBE CONFIDENTIAL
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
 * A simple Exception subclass thrown by several IDMLTools methods.
 */
public class PackageException extends Exception {
	
	/**
	 * @param errMessage The message to be displayed with the Exception.
	 */
	public PackageException(String errMessage)
	{
		super(errMessage);
	}

}
