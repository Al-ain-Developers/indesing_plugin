//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/AddCatalogPages.java $
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

import com.adobe.idml.FileTransformer;
import com.adobe.idml.Package;
import com.adobe.idml.PackageTransformer;
import com.adobe.idml.FileUtils;
import com.adobe.idml.PackageXmlLocator;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.XslParam;
import com.adobe.idml.XmlUtils;

import java.io.File;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPathExpressionException;


/** 
 * The AddCatalogPages sample extends PackageTransformer taking advantage
 * of a hook it provides that allows a subclass to do additional work
 * before or after the transformation.  The core PackageTransformer code 
 * transforms the designmap.xml file using the the xsl/transforms/designmap.xsl 
 * file.  The added code expands several XSL templates in the xsl/templates 
 * directory template into the new spread and story files.
 * 
 * */
public class AddCatalogPages extends PackageTransformer 
{	
	String fXSLTemplatePath;
	String fXSLTransformPath;
	String fXMLPath;
	String fSpreadID;
	DocumentBuilder fDocBuilder;

	/**
	 * This constructor sets up the XSL paths and the input XML file containing the 
	 * information needed to add new content to the an existing IDML file.
	 * @param xslTransformPath
	 * @param xslTemplatePath
	 * @param xmlPath
	 * @throws ParserConfigurationException
	 */
	public AddCatalogPages(String xslTransformPath, String xslTemplatePath, String xmlPath) throws ParserConfigurationException
	{
		//Setting instance variable values.
		fXSLTemplatePath = xslTemplatePath;
		fXSLTransformPath = xslTransformPath;
		fXMLPath = xmlPath;		
		//TODO: Think about the best way to ensure it is unique.
		fSpreadID = generateRandonString(3);
		fDocBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();
	}

	/**
	 * Overrides beforeTransform of the PackageTransformer class.
	 * This method creates the new stories and spread to be added to the IDML packages
	 * based on the content in the XML file represented by the fXMLPath instance variable.
	 * @throws XPathExpressionException 
	 */
	protected void beforeTransform(String idmlInput, File idmlInputDir) throws Exception 
	{
		PackageXmlLocator xmlLoc = new PackageXmlLocator(idmlInputDir);
		PackageXslLocator xslLoc = new PackageXslLocator(fXSLTemplatePath);
		
		// Generate an XSL file that includes all the other style sheets.
		// This XSL file will take a number of parameters.
		
		// Add the Parrameters.
		ArrayList<String> params = new ArrayList<String>();
		params.add("working-dir");
		params.add("spread-id");
		params.add("page-height");
		params.add("page-width");
		params.add("text-layer-id");
		params.add("masterpage-id");		
		
		String mainXSLPath = xslLoc.makeDynamicMain(params);

		File mainXSLFile = new File(mainXSLPath);
					
		String pageHeight = XmlUtils.getAttribute(xmlLoc.getPreferencesFilePath(), "/idPkg:Preferences/DocumentPreference/@PageHeight");
		String pageWidth = XmlUtils.getAttribute(xmlLoc.getPreferencesFilePath(), "/idPkg:Preferences/DocumentPreference/@PageWidth");
		String textLayerID = XmlUtils.getAttribute(xmlLoc.getDesignMapFilePath(), "/Document/Layer[@Name = 'text']/@Self"	);
		String masterPageID = XmlUtils.getAttribute(xmlLoc.getMasterSpreadXmlFiles(), "/idPkg:MasterSpread/MasterSpread[@Name = 'D-catalog']/@Self");
			
		ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
		xslParamValues.add(new XslParam("working-dir", idmlInputDir.getName()));
		xslParamValues.add(new XslParam("spread-id", fSpreadID)); 
		xslParamValues.add(new XslParam("page-height", pageHeight));  
		xslParamValues.add(new XslParam("page-width", pageWidth));  
		xslParamValues.add(new XslParam("text-layer-id", textLayerID));
		xslParamValues.add(new XslParam("masterpage-id", masterPageID));

				
		FileTransformer fileTransformer = new FileTransformer(mainXSLFile, xslParamValues);
		fileTransformer.transformFile(new File(fXMLPath), null); // style sheets specify output files
	}		
	
	/**
	 * Adds pages to an existing IDML file.
	 * @param idmlInput		The IDML file which will have pages added to it.
	 * @param idmlOutput	The IDML file which will be created after the pages are added.
	 * @throws Exception 
	 */
	public void addPages(String idmlInput, String idmlOutput) throws Exception 
	{
		Package.verifyPackage(idmlInput);
		Package.verifyPackage(idmlOutput);
		
		ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
		xslParamValues.add(new XslParam("inputXmlFilePath", FileUtils.getRelativePath(fXSLTransformPath, fXMLPath)));
		xslParamValues.add(new XslParam("spreadID", fSpreadID));

		transform(fXSLTransformPath, idmlInput, idmlOutput, xslParamValues);
	}	
	
	/**
	 * Returns a random string of numbers and letters.
	 * @param length	The length of the character string.
	 * @return	A random string of letters and numbers.
	 */
	private String generateRandonString(int length) 
	{
	     char[] randomStr = new char[length];
	     
	     for (int i=0; i < length; i++)
	     {
	    	 int randomChr = 0;	
	    	 //Choose between numbers, lower and upper case letters.
	    	 switch((int)Math.random() * 3) 
			 {
				case 0: //Numbers
					randomChr = '0' +  (int)(Math.random() * 10); 
					break;
				case 1: //Lower case
					randomChr = 'a' +  (int)(Math.random() * 26); 
					break;
				case 2: //Upper case
					randomChr = 'A' +  (int)(Math.random() * 26); 
					break;
			 }
	    	 randomStr[i] = (char)randomChr;      
	     }
	     return new String(randomStr);
	}
	
	
			
	private static void usage()
	{
		System.out.println("usage: AddCatalogPages xslTemplatesDir xmlInput source destination");
		System.out.println("\tTransforms the \"source\" package with transformations in the directory specified by \"xslDir\".");
		System.out.println("\tResults are saved to \"destination\" which should specify an .idml file.");
		System.out.println("-h\tThis help message.");
		System.exit(-1);
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		if( args.length != 3)
		{
			usage();
		}
		
		String xslTransformsPath = "xsl/transforms";
		String xslTemplatesPath = "xsl/templates";
		String xmlInput = args[0];
		String source = args[1];
		String destination = args[2];
		
		try
		{
			//The output files have not yet been created.
			//This ensures the parent directory which will 
			//contain the file exists.
			FileUtils.ensureParentDirectory(destination);
			
			AddCatalogPages pME = new AddCatalogPages(xslTransformsPath, xslTemplatesPath, xmlInput);
 			pME.addPages(source, destination);
		}
		catch( Exception e)
		{
			String err = "Failed to add pages.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
	}
}
