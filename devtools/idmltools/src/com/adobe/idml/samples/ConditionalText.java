//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ConditionalText.java $
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
package com.adobe.idml.samples;

import java.io.File;
import java.util.ArrayList;

import com.adobe.idml.*;
import com.adobe.idml.Package;

/** The ConditionalText sample shows how to work with Conditional Text within an
 * IDML package.
 */
public class ConditionalText 
{

	/** 
	 * ConditionalText usage message. 
	 */
	private static void usage()
	{
		System.out.println("usage: ConditionalText operation condition source destination");
		System.out.println("\n\tConditionalText can control the text conditions in an IDML file.");
		System.out.println("\n\tThe condition is specified by Self ID (the Conditions Self Attriute).");
		System.out.println("\n\tThe specified operations are carried out on the source file and written");
		System.out.println("\tto the specified destination file.");
		System.out.println("\nOperations:");
		System.out.println("\n\t-on\tTurn the provided condition on.");
		System.out.println("\t-off\tTurn the provided condition off.");
		System.out.println("\t-rm\tRemove the provided condition.");
		System.out.println("\t-xon\tTurn the provided condition on and all others off.");
		System.out.println("\t-xoff\tTurn the provided condition off and all others on.");
		System.out.println("\t-rmx\tRemove all except the provided condition.");
		System.out.println("\t-h\tThis help message.");
		System.out.println("\nExamples:");
		System.out.println("\tConditionalText -on \"Print Only\" ConditionalText.idml ConditionalText1.idml");
		System.out.println("\tTurns on the condition with the name \"Print Only\" and saves it to ConditionalText1.idml\n");
		System.out.println("\tConditionalText -off \"Print Only\" ConditionalText.idml ConditionalText2.idml");
		System.out.println("\tTurns off the condition with the name \"Print Only\" and saves it to ConditionalText2.idml\n");
		System.exit(-1);
	}
	
	/**
	 * Driver program for ConditionalText sample.
	 * @param args Arguments passed from the console.
	 */
	public static void main(String[] args) 
	{
		if(args.length < 4 || args[0].equalsIgnoreCase("-h"))
		{
			usage();
		}
		
		File tempDir = null;
		
		try
		{
			String operation = args[0];
			String conditionName = args[1];
			String source = args[2];
			String destination = args[3];
			
			// Figure out which style sheets to use based on the operation
			// To do this we look to see if we recognize the operation.  If
			// it's in the list we know about we remove the "-" at the front 
			// of the String and append it to the end of xslPath.
			//
			String xslPath = "xsl/";
			
			if(operation.equalsIgnoreCase("-on") || 
					operation.equalsIgnoreCase("-off") ||
					operation.equalsIgnoreCase("-rm") ||
					operation.equalsIgnoreCase("-xon") ||
					operation.equalsIgnoreCase("-xoff") ||
					operation.equalsIgnoreCase("-rmx")
				)
			{
				// Removing the "-" character gives us the path to the XSL files
				xslPath += operation.substring(1).toLowerCase();
			}
			else
			{
				usage();
			}
			
			// Check to see what type of file was specified.
			//
			if(Package.isAPackage(source))
			{
				tempDir = Package.decompress(source);
				
				PackageXmlLocator xmlLocator = new PackageXmlLocator(tempDir);
				
				// Get the Self ID matching 
				String conditionID = XmlUtils.getAttribute(xmlLocator.getDesignMapFilePath(), "/Document/Condition[@Name = '" + conditionName + "']/@Self");
				
				
				// Text conditions are listed in a number of attributes.
				// Whitespace is used as a delimiter.  In these cases the
				// spaces within the condition name are changes to "%20".
				// So we need to have a version of the condition that makes
				// that same substitution
				//
				String conditionIDEscaped = conditionID.replaceAll(" ", "%20");
				
				// Use the PackageTransformer to apply the correct transform.
				//
				PackageTransformer pTransformer = new PackageTransformer();
				
				// Pass along the condition (and the condition with spaces escaped)
				ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
				xslParamValues.add(new XslParam("condition", conditionID));
				xslParamValues.add(new XslParam("conditionEscaped", conditionIDEscaped));

				// Transform the files and write out the new IDML file.
				pTransformer.transform(xslPath, tempDir.getAbsolutePath(), destination, xslParamValues);

			}
			else
			{
				//TODO We have not yet implemented the ICML version of this.
				System.err.println("ICML and Snippet file version is not yet implemented!");
			}
		}
		catch( Exception e)
		{
			String err = "ConditionalText Failure.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
		finally
		{
			if(tempDir != null)
				FileUtils.DeleteDirectory(tempDir);
		}
		
	}

}
