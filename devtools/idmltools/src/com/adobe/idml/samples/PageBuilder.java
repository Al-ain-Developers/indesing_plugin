//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/PageBuilder.java $
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


import com.adobe.idml.XslParam;
import com.adobe.idml.Package;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.FileTransformer;
import com.adobe.idml.FileUtils;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactoryConfigurationError;


/** 
 * PageBuilder builds an IDML package from a set of XSL style
 * sheets and XML input data.  It pulls data from the XML input file, and
 * calls XSLT transformations on an XSL file it generates from the files
 * in the XSL directory.  The XSL files are responsible for producing 
 * package files using the <xsl:document> instruction.
 */
public class PageBuilder
{
	private String fXSLPath;

	/**
	 * Sets the XSL Path.
	 * @param xslPath A Path to the directory containing XSL files.
	 */
	public PageBuilder(String xslPath)
	{
		setXSLPath(xslPath);
	}
	
	/**
	 * Returns the XSL path provided to the class.
	 * @return The path to the directory containing the XSL files.
	 */
	public String getXSLPath()
	{
		return fXSLPath;
	}
	
	/** 
	 * Sets the XSL path.
	 * @param xslPath The new path to the directory containing XSL files.
	 */
	public void setXSLPath(String xslPath)
	{
		fXSLPath = xslPath;
	}
	

	/** 
	 * Creates a package from the input XML file specified.
	 * @param inputXmlPath The XML value containing the values that will be used to create the new IDML package file.
	 * @param outputIdmlFile The IDML package to be created.
	 * @throws TransformerFactoryConfigurationError
	 * @throws IOException 
	 * @throws ParserConfigurationException 
	 * @throws TransformerException 
	 */
	public void expand(String inputXmlPath, String outputIdmlFile) throws TransformerFactoryConfigurationError, IOException, ParserConfigurationException, TransformerException
	{
		File inputXmlFile = new File(inputXmlPath);
		
		String workingDirParam = "workingdir";
		File workingDir = FileUtils.CreateTempDir();
		
		PackageXslLocator xslLoc = new PackageXslLocator(fXSLPath);
		try 
		{
			//Adds a "workingdir" XSL:Param to the the dynamic_main.xsl file to be created.
			ArrayList<String> params = new ArrayList<String>();
			params.add(workingDirParam);
			String mainXSLPath = xslLoc.makeDynamicMain(params);		
			File mainXSLFile = new File(mainXSLPath);
			
			//Sets the value of the "workingdir" param to the temporary directory with the transform.
			ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
			xslParamValues.add(new XslParam(workingDirParam, workingDir.getAbsolutePath()));
			
			FileTransformer fileTransformer = new FileTransformer(mainXSLFile, xslParamValues);
			fileTransformer.transformFile(inputXmlFile, null); // Style sheets specify output file
			
			// compress the package
			Package.compress(workingDir, outputIdmlFile);
		}
		finally
		{
			//Cleanup
			FileUtils.DeleteDirectory(workingDir);
		}		
	}	
	
	private static void usage()
	{
		System.out.println("usage: PageBuilder [-h] or [xmlInput] [idmlOutput]");
		System.out.println("-h\t...\tThis usage message.");
		System.out.println("xmlInput\t...\tA path to an XML input file used to expand the template.");
		System.out.println("idmlOuput\t...\tA path to the idml file which will be generated.  This is an optional argument");
		System.out.println("\nExamples: ");
		System.out.println("\tPageBuilder pagebuilder.xml pagebuilder.idml");
		System.exit(-1);
	}	
	
	/** 
	 * Initializes a PageBuilder instance and sets the default XSL directory used for transforms.
	 * @param args	Parameters passed by the console application.
	 * @throws IOException 
	 */
	public static void main(String[] args) 
	{		
		if((args.length < 1) || (args.length > 2))
		{
			usage(); 
		}
		
		String xslPath = "xsl";
		String xmlInput = args[0];
		String idmlOutput = "";
		
		PageBuilder expander = new PageBuilder(xslPath);
		
		if (args.length == 2)
		{
			idmlOutput = args[1];			
		}
		else if(args.length == 1)
		{
			idmlOutput = xmlInput.substring(0, xmlInput.indexOf(".xml")).concat(".idml");
		}

		try
		{
			FileUtils.ensureParentDirectory(idmlOutput);
			expander.expand(xmlInput, idmlOutput);
		}
		catch(Exception e)
		{
			String err = "Failed to expand template.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
	}
}
