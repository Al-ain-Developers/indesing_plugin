//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ImportXmlTemplate.java $
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
package com.adobe.idml.samples;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import com.adobe.idml.XslParam;
import com.adobe.idml.Package;
import com.adobe.idml.PackageXmlLocator;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.PackageTransformer;
import com.adobe.idml.FileUtils;

/**
 * Merges an IDML file tagged using XML tags feature with an
 * XML file containing changes for that file.
 */
public class ImportXmlTemplate
{	
	PackageXslLocator fXslLocator;

	/**
	 * Instantiates a new ImportXmlTemplate object and creates an XSLLocator for the directory of XSL files provided.
	 * @param xslDirPath	The path to the XSL files needed for transforms.
	 * @throws IOException 
	 */
	public ImportXmlTemplate(String xslDirPath) throws IOException
	{	
		fXslLocator = new PackageXslLocator(xslDirPath);
	}
	
	/**
	 * Imports an XML file to the root as if the file were imported through Indesign's 
	 * Import XML feature.  This sample is designed to work with image and text changes.
	 * Table changes are not supported in this sample.
	 * @param inIdmlFilePath	An IDML file with tagged content to be replaced.
	 * @param importXmlFilePath	An XML file with new content designed to update the input file from root.
	 * @param outIdmlFilePath	The file to be created when the input IDML file is merged with the import XML file.
	 * @throws Exception 
	 */
	public void importXmlFile(String inIdmlFilePath, String outIdmlFilePath, String importXmlFilePath) throws Exception
	{
		//Verifies the IDML files required are IDML files.
		Package.verifyPackage(inIdmlFilePath);
		Package.verifyPackage(outIdmlFilePath);
		
		//The directory containing the expanded IDML package.
		File expandedIdmlDir = Package.decompress(inIdmlFilePath);			
		
		try
		{
			PackageXmlLocator xmlLoc = new PackageXmlLocator(expandedIdmlDir);	
			String xslPath = fXslLocator.getXslRoot();
			
			//Obtains relative paths from XSL root directory to the needed package XML files.
			String importRelPath = FileUtils.getRelativePath(xslPath, importXmlFilePath);	
			String tagsRelPath = FileUtils.getRelativePath(xslPath, xmlLoc.getTagsFilePath());			
			String backingStoryRelPath = FileUtils.getRelativePath(xslPath, xmlLoc.getBackingStoryFilePath());
			
			// XSL:Param values to be passed to the transformer.		
			ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
			xslParamValues.add(new XslParam("importPath", importRelPath));
			xslParamValues.add(new XslParam("tagsPath", tagsRelPath));
			xslParamValues.add(new XslParam("backingStoryPath", backingStoryRelPath));
			
			PackageTransformer packageTransformer = new PackageTransformer();
			packageTransformer.transform(fXslLocator, xmlLoc, xslParamValues);
			
			//Output to a new IDML file.
			Package.compress(expandedIdmlDir, outIdmlFilePath);					
		}
		finally 
		{
			//Cleanup
			FileUtils.DeleteDirectory(expandedIdmlDir);
		}
	}
	
	private static void usage()
	{
		System.out.println("usage: ImportXmlTemplate [Input IDML File] [Output IDML File] [Import XML File]");
		System.out.println("\nParameters");
		System.out.println("\tInput IDML File\tAn IDML file with tagged content to be replaced.");
		System.out.println("\tOutput IDML File\tThe file to be created when the input IDML file is merged with the import XML file.");
		System.out.println("\tImport XML File\tAn XML file with new content designed to update the input file from root.");
		System.out.println("\nExamples: ");
		System.out.println("\tImportXmlTemplate MensShirts.idml WomensShirts.idml Import.xml");
		System.exit(-1);
	}
	

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		if( args.length != 3)
		{
			usage();
		}
		
		String xslDirPath = "xsl";
		String inIdmlPath = args[0];
		String outIdmlPath = args[1];		
		String inputXmlPath = args[2];
		
		try
		{
			//The output files have not yet been created.
			//This ensures the parent directory which will 
			//contain the file exists.
			FileUtils.ensureParentDirectory(outIdmlPath);
			ImportXmlTemplate imt = new ImportXmlTemplate(xslDirPath);
			imt.importXmlFile(inIdmlPath, outIdmlPath, inputXmlPath);
		}
		catch( Exception e)
		{
			String err = "Failed to import file.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, inputXmlPath, e.getMessage(), e.getStackTrace());
		}
	}
}
