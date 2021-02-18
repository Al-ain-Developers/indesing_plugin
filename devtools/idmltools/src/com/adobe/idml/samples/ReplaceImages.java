//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ReplaceImages.java $
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
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.Set;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.xpath.XPathExpressionException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import com.adobe.idml.FileTransformer;
import com.adobe.idml.FileUtils;
import com.adobe.idml.XslParam;
import com.adobe.idml.Package;
import com.adobe.idml.PackageException;
import com.adobe.idml.PackageXmlLocator;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.XmlUtils;

/**
 * This class contains tools that can be used to replace images 
 * in an IDML Package.  These tools can be used to replace either linked or embedded images.  
 * However, all image replacements will be linked.  This tool cannot replace an image with an embedded image.
 */
public class ReplaceImages
{
	private File fExpandedIdmlDir;
	private PackageXslLocator fXslLocator;
	private PackageXmlLocator fXmlLocator;
	
	/**
	 * This constructor requires an XSL directory to locate the transforms and an IDML Package 
	 * containing the images to be replaced.
	 * @param xslDirPath	The path to the XSL directory containing the XSL files used to transform Package XML files.
	 * @param idmlSourcePath The path to the IDML Package file containing images to be replaced.
	 * @throws IOException
	 */
	public ReplaceImages(String xslDirPath, String idmlSourcePath) throws IOException
	{		
		this(xslDirPath);		
		setSourcePackage(idmlSourcePath);		
	}
	
	private ReplaceImages(String xslDirPath) throws IOException
	{
		if(xslDirPath != null)
		{
			fXslLocator = new PackageXslLocator(xslDirPath);	
		}
	}
	
	/**
	 * Set the IDML Package in which to replace images.
	 * @param idmlSourcePath	The path to the IDML Package.
	 * @throws IOException
	 */
	public void setSourcePackage(String idmlSourcePath) throws IOException
	{
		Package.verifyPackage(idmlSourcePath);
		fExpandedIdmlDir = Package.decompress(idmlSourcePath);			
		fXmlLocator = new PackageXmlLocator(fExpandedIdmlDir);
	}
	
	/**
	 * Writes a the image ID's and paths to an XML File.
	 * @param outputFilePath The XML file where the image ID's and paths will be written to.
	 * @throws IOException
	 * @throws XPathExpressionException
	 * @throws PackageException
	 * @throws ParserConfigurationException
	 */
	public void exportList(String outputFilePath) throws IOException, XPathExpressionException, PackageException, ParserConfigurationException
	{
		try {
			Hashtable<String, String> links = getLinksFromPackage();
			writeOutputXmlFile(links, outputFilePath);
		}
		finally
		{
			cleanup();
		}
	}
	
	/**
	 * Imports an XML file with image ID's mapped to links and applies the changes to a copy
	 * of the source IDML Package.
	 * @param importXmlPath	The path to the XML file to be imported.
	 * @param idmlOutputPath The path to the IDML file which will be created after applying the changes to the source IDML package.
	 * @throws XPathExpressionException
	 * @throws PackageException
	 * @throws IOException
	 * @throws TransformerFactoryConfigurationError
	 * @throws TransformerException
	 */
	public void importList(String importXmlPath, String idmlOutputPath) throws XPathExpressionException, PackageException, IOException, TransformerFactoryConfigurationError, TransformerException
	{
		FileUtils.deleteFile(idmlOutputPath);	
			
		try
		{
			Hashtable<String, String> links = getLinksFromXml(importXmlPath);
			updatePackage(links, idmlOutputPath);			
		}			
		finally
		{
			cleanup();
		}
	}
	
	/**
	 * Removes the temporary directory used for IDML Package extraction.
	 */
	public void cleanup()
	{
		if (fExpandedIdmlDir == null)
		{
			return;
		}
		FileUtils.DeleteDirectory(fExpandedIdmlDir);
	}
	
	/**
	 * Gets a the image ID's and links from the source IDML Package in a Hashtable.
	 * @return A Hashtable containing the image ID's mapped to image links.
	 * @throws IOException
	 * @throws XPathExpressionException
	 * @throws PackageException
	 */
	public Hashtable<String, String> getLinksFromPackage() throws IOException, XPathExpressionException, PackageException
	{
		ArrayList<String> spreadFiles = fXmlLocator.getSpreadXmlFiles();
		String expr = "//Link[ancestor::Image]";		
		return XmlUtils.getAttributePairsForElement(spreadFiles, expr, "Self", "LinkResourceURI");
	}
	
	/**
	 * Makes a copy of the source IDML Package and updates the links with the values 
	 * found in the links Hashtable.
	 * @param links A Hashtable with link ID/Path Key/Value pairs.
	 * @param idmlOutputPath The IDML Package file that will be created by copying the links file paths to the source IDML package.
	 * @throws IOException 
	 * @throws TransformerFactoryConfigurationError 
	 * @throws TransformerException 
	 */
	public void updatePackage(Hashtable<String, String> links, String idmlOutputPath) throws IOException, TransformerFactoryConfigurationError, TransformerException
	{
		ArrayList<String> spreadFiles = fXmlLocator.getSpreadXmlFiles();
				
		Set<String> keys = links.keySet();			
		Iterator<String> itr = keys.iterator();
		Enumeration<String> values = links.elements();
		
		while(itr.hasNext() && values.hasMoreElements())
		{
			String id = itr.next();
			String uri = values.nextElement();			
			
			ArrayList<XslParam> xslParamValues = new ArrayList<XslParam>();
			xslParamValues.add(new XslParam("linkID", id));
			xslParamValues.add(new XslParam("linkURI", uri));					
			
			ListIterator<String> spreadFilesItr = spreadFiles.listIterator();
		
			while (spreadFilesItr.hasNext())
			{
				String spreadFilePath = spreadFilesItr.next();
				File spreadFile = new File(spreadFilePath);
				
				String xslFilePath = fXslLocator.getCorrespondingXslFilePath(spreadFilePath);
				File xslFile = new File(xslFilePath);
				
				FileTransformer fileTransformer = new FileTransformer(xslFile, xslParamValues);
				fileTransformer.transformFile(spreadFile, spreadFile); // Style sheets specify output file
			}
		}		
		//Create new IDML Package file.
		Package.compress(fExpandedIdmlDir, idmlOutputPath);
	}
		
	
	private void writeOutputXmlFile(Hashtable<String, String> linksTable, String outputFilePath) throws IOException, ParserConfigurationException
	{
		//Create a new empty file.
		FileUtils.deleteFile(outputFilePath);
		File outputFile = FileUtils.createFile(outputFilePath);
		Document xmlDoc = XmlUtils.getNewDOMDoc();
		
		//Create the root element and add it to the document
        Element root = xmlDoc.createElement("root");
        xmlDoc.appendChild(root);
        
        Set<String> keys = linksTable.keySet();			
		Iterator<String> itr = keys.iterator();
		Enumeration<String> values = linksTable.elements();
		
		while(itr.hasNext() && values.hasMoreElements())
		{
			String id = itr.next();
			String uri = values.nextElement();			
			
			Element e = xmlDoc.createElement("Link");
			e.setAttribute("ID", id);
			e.setAttribute("URI", uri);
			root.appendChild(e);
		}
		
		XmlUtils.writeXmlFile(xmlDoc, outputFile);       
	}
		
	
	private Hashtable<String, String> getLinksFromXml(String xmlLinksPath) throws XPathExpressionException, PackageException, IOException
	{
		String expr = "//Link";
		return XmlUtils.getAttributePairsForElement(xmlLinksPath, expr, "ID", "URI");
	}
	
	
	private static void usage()
	{
		System.out.println("Usage: ReplaceImages [operation] [Source IDML File] [Output File]");
		System.out.println("\nOperations:");
		System.out.println("\t-h\tThis help message.");
		System.out.println("\t-it\tImports an XML template file with image replacements for an IDML Package.");
		System.out.println("\t-et\tGenerates a template XML file with information about the images in the IDML Package.");
		System.out.println("\tno operation\tDisplays a Java Swing user interface for selecting images to be replaced.");
		System.out.println("\nExamples: ");
		System.out.println("\tReplaceImages -et ReplaceImages.idml export.xml");
		System.out.println("\tReplaceImages -it export.xml ReplaceImages.idml ReplaceImages_modified.idml");
		System.exit(-1);
	}

	/**
	 * The main method used to initialize the ReplaceImages class.
	 * @param args parameters provided by the console application.
	 */
	public static void main(String[] args) 
	{
		String operation = "";
		if (args.length != 0)
		{
			operation = args[0];
		}
								
		try
		{	
			if(operation.equalsIgnoreCase("-h"))
			{
				usage();
			}
			else if ( operation.equalsIgnoreCase("-et"))
			{				
				String idmlSourcePath = args[1];
				String xmlOutputPath = args[2];
				
				//The output files have not yet been created.
				//This ensures the parent directory which will 
				//contain the file exists.
				FileUtils.ensureParentDirectory(xmlOutputPath);
				
				ReplaceImages ri = new ReplaceImages(null, idmlSourcePath);
				ri.exportList(xmlOutputPath);
			}
			else if ( operation.equalsIgnoreCase("-it"))
			{
				String importXmlPath = args[1];
				String idmlSourcePath = args[2];
				String idmlOutputPath = args[3];				
				
				//The output files have not yet been created.
				//This ensures the parent directory which will 
				//contain the file exists.
				FileUtils.ensureParentDirectory(idmlOutputPath);
				
				String xslPath = "xsl";	
				ReplaceImages ri = new ReplaceImages(xslPath, idmlSourcePath);
				ri.importList(importXmlPath, idmlOutputPath);					
			}
			else //operation is an empty string or invalid 
			{
				String xslPath = "xsl";	
				ReplaceImages ri = new ReplaceImages(xslPath);
				ReplaceImagesGUI gui = new ReplaceImagesGUI(ri);
				gui.setTitle("Replace Images");
				gui.setVisible(true);
			}
		}
		catch( Exception e)
		{
			String err = "Replace Images Failure.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
	}
}
