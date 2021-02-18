//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/PackageTransformer.java $
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

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.ListIterator;

import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactoryConfigurationError;

/**
 *	Contains overloaded transform methods.  This class is used to perform
 *	all XSL transformations for the IDML Tools samples.
 */
public class PackageTransformer 
{	
	/** 
	 * Performs a set of XSL transformations on an IDML input file or directory.  If
	 * the input is a directory these transformations are done in place.  If it is an
	 * archive file, the transformations are done in a temporary directory.  In either
	 * case you can specify an output IDML file path.
	 * 
	 * @param xslDir	Contains the XSL StyleSheets needed to transform the IDML file.	
	 * @param idmlInput	The IDML file or directory to be transformed.
	 * @param idmlOutput The path to the IDML file to which the transformations changes should be written.  Or null if no changes should be written.
	 * @param params	A list of key/value pairs containing parameter values required by the XSL StyleSheets.
	 * @throws Exception 
	 */
	public void transform(String xslDir, String idmlInput, String idmlOutput, ArrayList<XslParam> params) throws Exception 

	{		
		// Decide if we are dealing with an archive or a directory.
		// If it's a directory we don't need to manage a temporary directory.
		// The variable archiveMode is set to true if it's not a directory.
		//
		boolean archiveMode = true;
		File idmlInputFile = new File(idmlInput);
		if(idmlInputFile.isDirectory())
		{
			archiveMode = false;
		}
		
		// We set the input directory based on which mode we're in.  It's going to be
		// a temporary directory if we are dealing with an IDML file.
		//
		File inputDir = archiveMode ? FileUtils.CreateTempDir() : idmlInputFile;		
		
		try
		{
			// If we're in archive mode we need to uncompress the package
			if( archiveMode )
				Package.decompress(idmlInput, inputDir.getAbsolutePath());
			
			PackageXmlLocator xmlLoc = new PackageXmlLocator(inputDir);		
			PackageXslLocator xslLoc = new PackageXslLocator(xslDir);
			ArrayList<String> list = xmlLoc.getAllXmlFiles();
			ListIterator<String> itr = list.listIterator();
			
			beforeTransform(idmlInput, inputDir);
			while(itr.hasNext())
			{
				String xmlFilePath = itr.next();
				if(isInExcludeList(xmlFilePath))
				{
					continue;
				}
				String xslFilePath = xslLoc.getCorrespondingXslFilePath(xmlFilePath);
				if (null == xslFilePath)
				{
					continue;
				}
				
				File xslFile = new File(xslFilePath);
				File xmlFile = new File(xmlFilePath);
				
				FileTransformer fileTransformer = new FileTransformer(xslFile, params);
				fileTransformer.transformFile(xmlFile, xmlFile); // overwrites xmlFile
			}			
			afterTransform(idmlInput, inputDir);
			
			// If an output file was specified then we write the package
			if(idmlOutput != null)
				Package.compress(inputDir.getAbsolutePath(), idmlOutput);
		}
		finally
		{
			// If we're in archive mode we should have a temporary directory to cleanup
			if(archiveMode)
				FileUtils.DeleteDirectory(inputDir);
		}
	}
	
	/** 
	 * Performs XSL transformations on all XML files in the IDML input file.
	 * @param xslLoc	The PackageXslLocator object used to find the XSL files needed in the transformation.	
	 * @param xmlLoc	The PackageXmlLocator object used to find the XML files needed in the transformation.
	 * @param params	A list of key/value pairs containing parameter values required by the XSL StyleSheets.
	 * @throws IOException 
	 * @throws TransformerException 
	 * @throws TransformerFactoryConfigurationError 
	 */
	public void transform(PackageXslLocator xslLoc, PackageXmlLocator xmlLoc, ArrayList<XslParam> params) throws IOException, TransformerFactoryConfigurationError, TransformerException 
	{			
		ArrayList<String> list = xmlLoc.getAllXmlFiles();
		ListIterator<String> itr = list.listIterator();
		while(itr.hasNext())
		{
			String xmlFilePath = itr.next();
			if(isInExcludeList(xmlFilePath))
			{
				continue;
			}
			String xslFilePath = xslLoc.getCorrespondingXslFilePath(xmlFilePath);
			if (xslFilePath == null)
			{
				continue;
			}
			
			File xslFile = new File(xslFilePath);
			File xmlFile = new File(xmlFilePath);
			
			FileTransformer fileTransformer = new FileTransformer(xslFile, params);
			fileTransformer.transformFile(xmlFile, xmlFile); // overwrites xmlFile
		}						
	}
	
	/**
	 * A hook method into the XSL transformation with the String, String, String, ArrayList signature.
	 * @param xmlFile	The XML file to be tested.	
	 * @return	Returns true if the file is in the list and false if not.
	 */
	protected boolean isInExcludeList(String xmlFile)
	{
		return false;
	}
	
	/**
	 * A hook method into the XSL transformation with the String, String, String, ArrayList signature which is called before the transforms take place.
	 * @param idmlInput	The path to the IDML file being transformed.
	 * @param inputDir	The file representing the expanded IDML directory.
	 */
	protected void beforeTransform(String idmlInput, File inputDir) throws Exception
	{
		//No Operation
	}

	/**
	 * A hook method into the XSL transformation with the String, String, String, ArrayList signature which is called after the transforms take place. @param idmlInput	The path to the IDML file being transformed.
	 * @param inputDir	The file representing the expanded IDML directory.
	 */
	protected void afterTransform(String idmlInput, File inputDir) throws IOException
	{
		//No Operation
	}
}
