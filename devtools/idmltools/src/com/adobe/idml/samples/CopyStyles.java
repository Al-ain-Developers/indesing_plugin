//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/CopyStyles.java $
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
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactoryConfigurationError;

import com.adobe.idml.FileTransformer;
import com.adobe.idml.XslParam;
import com.adobe.idml.Package;
import com.adobe.idml.PackageXmlLocator;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.FileUtils;

/**
 * This class can be used to copy styles of 
 * any type (Object, Paragraph, Character and so on)
 * from one IDML Package or another.
 */
public class CopyStyles
{
	PackageXslLocator fXSLLocator;
	
	/**
	 * This constructor sets up an XSL Locator object.
	 * @param xslPath	The path to the XSL files needed for transforms.
	 * @throws IOException 
	 */
	public CopyStyles(String xslPath) throws IOException
	{
		fXSLLocator = new PackageXslLocator(xslPath);		
	}
	
	/**
	 * Creates a new IDML file by copying styles from a source IDML file to a destination IDML.  
	 * The final IDML file contains the styles of the source file and everything else from the destination file.
	 * @param idmlFrom	The IDML source file containing the styles to be copied.
	 * @param idmlTo	The IDML destination file which will be copied to have the styles applied to it.
	 * @param idmlOut	The new IDML file containing the a copy of the idmlTo file with the idmlFrom styles applied to it.
	 * @throws TransformerFactoryConfigurationError
	 * @throws TransformerException
	 * @throws IOException
	 */
	public void copy(String idmlFrom, String idmlTo, String idmlOut) throws TransformerFactoryConfigurationError, TransformerException, IOException
	{
		Package.verifyPackage(idmlFrom);
		Package.verifyPackage(idmlTo);
		Package.verifyPackage(idmlOut);
		
		//Create temporary directories for the IDML file to be extracted into.
		File extractedFromDir = FileUtils.CreateTempDir();
		File extractedToDir = FileUtils.CreateTempDir();
		try
		{	
			//Extract the IDML files in to be extracted into.
			Package.decompress(idmlFrom, extractedFromDir.getAbsolutePath());
			PackageXmlLocator fromXmlLoc = new PackageXmlLocator(extractedFromDir);

			Package.decompress(idmlTo, extractedToDir.getAbsolutePath());
			PackageXmlLocator toXmlLoc = new PackageXmlLocator(extractedToDir);
						
			String fromXmlFilePath = fromXmlLoc.getStylesFilePath();
			String fromXslDirPath = fXSLLocator.getCorrespondingXslDirPath(fromXmlFilePath);
			String relPath = FileUtils.getRelativePath(fromXslDirPath, fromXmlFilePath);
			
			ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
			xslParamValues.add(new XslParam("srcXmlFilePath", relPath));

			String toXmlFilePath = toXmlLoc.getStylesFilePath();
			File toXmlFile = FileUtils.getFile(toXmlFilePath);
			String toXslFilePath = fXSLLocator.getCorrespondingXslFilePath(toXmlFilePath);
			File toXslFile = FileUtils.getFile(toXslFilePath);
			
			FileTransformer fileTransformer = new FileTransformer(toXslFile, xslParamValues);
			fileTransformer.transformFile(toXmlFile, toXmlFile); // style sheets specify output files
			
			Package.compress(extractedToDir, idmlOut);
		}
		finally 
		{
			//Cleanup
			FileUtils.DeleteDirectory(extractedFromDir);
			FileUtils.DeleteDirectory(extractedToDir);
		}
	}	
		
	/** 
	 * CopyStyles usage message. 
	 */
	private static void usage()
	{
		System.out.println("usage: CopyStyles [operation] [style type] [source file] [destination file] [output file]");
		System.out.println("\n\tCopyStyles copies a style from a source IDML Package to a destination IDML Package.");
		System.out.println("\nOperations:");
		System.out.println("\t-h\tThis help message.");
		System.out.println("\t-a\tAll styles are copied from the source to the destination.");
		System.out.println("\t-e\tExisting styles or styles that share a common name are copied from the source to the destination.");
		System.out.println("\t-n\tNew styles or styles not found in the destination are copied from the source to the destination.");
		System.out.println("\nStyle Type:");
		System.out.println("\t-p\tParagraph Styles.");
		System.out.println("\t-o\tObject Styles.");		
		System.out.println("\nExamples: ");
		System.out.println("\tCopyStyles -e -o FromObjectStyles.idml ToObjectStyles.idml CopyExistingObjectStylesResult.idml");
		System.out.println("\tCopyStyles -a -p FromParagraphStyles.idml ToParagraphStyles.idml CopyAllParagraphStylesResult.idml");
		System.exit(-1);
	}
	
	/**
 	 * The main method used to initialize the CopyStyles class.
	 * @param args parameters provided by the console application.
	 */
	public static void main(String[] args) 
	{	
		String operation = "";
		if (args.length != 0)
		{
			operation = args[0];
		}
		
		if(operation.equalsIgnoreCase("-h") || args.length != 5)
		{
			usage();
		}
				
		String xslPath = "";
		String style = args[1];
		if(operation.equalsIgnoreCase("-a") || 
				operation.equalsIgnoreCase("-e") ||
				operation.equalsIgnoreCase("-n")
				&&
				style.equalsIgnoreCase("-o") ||
				style.equalsIgnoreCase("-p")
		)
		{
			xslPath = "xsl/" + operation.substring(1).toLowerCase() + style.substring(1).toLowerCase();
		}
		else 
		{
			usage();
		}
				
		String idmlFromPath = args[2];
		String idmlToPath = args[3];
		String idmlOutPath = args[4];
		
		try
		{
			//The output files have not yet been created.
			//This ensures the parent directory which will 
			//contain the file exists.
			FileUtils.ensureParentDirectory(idmlOutPath);
			
			CopyStyles cn = new CopyStyles(xslPath);
			cn.copy(idmlFromPath, idmlToPath, idmlOutPath);
		}
		catch( Exception e)
		{
			String err = "Failed to copy styles.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
	}
}
