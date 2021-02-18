//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ICMLBuilder.java $
//  
//  Owner: Heath Lynn
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
package com.adobe.idml.samples;

import java.io.File;
import java.util.ArrayList;


import com.adobe.idml.*;

/** ICMLBuilder uses a FileTransformer to build an ICMLFile.
 */
public class ICMLBuilder 
{
	/* Usage message
	 * 
	 */
	private static void usage()
	{
		System.out.println("usage: ICMLBuilder [-h] xslFile xmlInput icmlOutput");
		System.out.println("-h\t...\tThis usage message.");
		System.out.println("xslFile\t...\tA path to a file containing the the xsl style sheet.");
		System.out.println("xmlInput\t...\tA path to an XML input file used to expand the template.");
		System.out.println("icmlOutput\t...\tA path to the icml file which will be generated.");
		System.exit(-1);
	}	

	/** 
	 * This program constructs the ICMLBuilder instance with the designated XSL File
	 * and a parameter designating the table width.  It then calls transform.
	 * @param args Arguments passed from the console.
	 */
	public static void main(String[] args)
	{
		if(args.length < 3)
		{
			usage();
		}
		
		try
		{
			File xslFile = new File(args[0]);
			File xmlFile = new File(args[1]);
			File icmlOutput = new File(args[2]);			
				
			ArrayList<XslParam> params = new ArrayList<XslParam>();		
			params.add(new XslParam("table-width", "500"));
			
			FileTransformer fileTransformer = new FileTransformer(xslFile, params);
			fileTransformer.transformFile(xmlFile, icmlOutput);
		}
		catch(Exception e)
		{
			String err = "Failed to expand template.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}

	}

}
