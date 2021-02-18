//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/PackageXslLocator.java $
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
import java.util.Hashtable;
import java.util.ListIterator;
import javax.xml.parsers.ParserConfigurationException;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Contains tools for locating the XSL file need for the transformation. 
 */
public class PackageXslLocator 
{
	private String fXSLPath;
	private Hashtable<String, String> fXSLHash;
	
	/**
	 * Instantiates a new XSLLocator object for the directory of XSL files provided.
	 * @param xslPath 	The path to the root directory containing XSL files.
	 * @throws IOException 
	 */
	public PackageXslLocator(String xslPath) throws IOException
	{
		FileUtils.verifyDirectory(xslPath);
		fXSLPath = xslPath;
		loadXslFileHash();
	}
	
	/**
	 * Given an XML file name this method will return the path to the matching XSL file needed for the transform.
	 * @param xmlFileName	The name of the XML file to be transformed.
	 * @return	The path to the XSL file needed for the transform.
	 */
	public String getCorrespondingXslFilePath(String xmlFileName)
	{
		xmlFileName = xmlFileName.substring((xmlFileName.lastIndexOf("/") + 1), xmlFileName.length());
		xmlFileName = xmlFileName.substring(0, xmlFileName.indexOf(".xml"));
		xmlFileName = xmlFileName.substring(0, (xmlFileName.indexOf("_") > 0)? xmlFileName.indexOf("_"): xmlFileName.length());
		xmlFileName = xmlFileName.toLowerCase();
		String xslFile = fXSLHash.get(xmlFileName);
		return xslFile;
	}
	
	/**
	 * Given an XML file name this method will return the path to directory containing the matching XSL file needed for the transform.
	 * @param xmlFileName	The name of the XML file to be transformed.
	 * @return	The path to the directory containing the XSL file needed for the transform.
	 * @throws IOException 
	 */
	public String getCorrespondingXslDirPath(String xmlFileName) throws IOException
	{
		String xslFile = getCorrespondingXslFilePath(xmlFileName);
		if (xslFile.equals(null))  //A corresponding XSL file was not found.
		{
			return null;
		}
		File xslDir = FileUtils.getParentDirectory(xslFile);
		return xslDir.getAbsolutePath();
	}
	
	/**
	 * Returns the path to the XSL root directory.
	 * @return	The path to the XSL root directory
	 */
	public String getXslRoot() 
	{
		return fXSLPath;
	}
	
	
	/**
	 * Builds a file named dynamic_main.xsl which will contain XSL:Inlude references to all XSL files
	 * in the provided directory and sub-directories.
	 * @param params	An ArrayList containing values to be added as XSL:Params to the main.xsl StyleSheet.
	 * @return The file path to the main.xsl file created by this method.
	 * @throws IOException
	 * @throws ParserConfigurationException
	 */
	public String makeDynamicMain(ArrayList<String> params) throws IOException, ParserConfigurationException
	{
		FileUtils.verifyDirectory(fXSLPath);
		
		//This value is hard-coded intentionally.
		String xslMainPath = fXSLPath + "/dynamic_main.xsl";
		File xslMainFile = new File(xslMainPath);
		
		if (xslMainFile.exists())
		{
			xslMainFile.delete();
		}		

		//A blank StyleSheet is created.
		Document document = XmlUtils.getNewXslStylesheet();
		Element rootElem = document.getDocumentElement();

		//Setup xsl:preserve-space options
		Element preserveElem = (Element) document.createElement("xsl:preserve-space");
		preserveElem.setAttribute("elements", "text");
		rootElem.appendChild(preserveElem);

		//Setup xsl:output options
		Element outputElem = (Element) document.createElement("xsl:output");
		outputElem.setAttribute("method", "text");
		outputElem.setAttribute("indent", "no");
		rootElem.appendChild(outputElem);
		
		//Setup xsl:param options
		if (null != params)
		{
			ListIterator<String> itr = params.listIterator();
			while(itr.hasNext())
			{
				Element paramElement = (Element) document.createElement("xsl:param");
				paramElement.setAttribute("name", itr.next());
				rootElem.appendChild(paramElement);
			}
		}
		
		//Setup xsl:template options
		Element templateElem = (Element) document.createElement("xsl:template");
		templateElem.setAttribute("match", "/");
		Element applyElem = (Element) document.createElement("xsl:apply-templates");
		rootElem.appendChild(templateElem);
		templateElem.appendChild(applyElem);

		//Recursively add an xsl:include option to for each XSL file found.
		ArrayList<File> xslFiles = getAllXslFiles(new ArrayList<File>(), FileUtils.getDirectory(fXSLPath));
		ListIterator<File> itr = xslFiles.listIterator();
		while(itr.hasNext())
		{
			File xslFile = itr.next();
			Element includeElem = (Element) document.createElement("xsl:include");
			includeElem.setAttribute("href", FileUtils.getRelativePath(new File(fXSLPath), xslFile));
			rootElem.appendChild(includeElem);

		}
		
		XmlUtils.writeXmlFile(document, xslMainFile);
		return xslMainPath;
	}
	
	/**
	 * Loads a HashTable with file names as the key and XSL Paths as the the value.  
	 * @throws IOException
	 */
	private void loadXslFileHash() throws IOException 
	{
		fXSLHash = new Hashtable<String, String>();
		File xslDir = new File(fXSLPath);
		ArrayList<File> xslFiles = getAllXslFiles(new ArrayList<File>(), xslDir);
		ListIterator<File> itr = xslFiles.listIterator();
		while(itr.hasNext())
		{
			File file = itr.next();
			String filename = file.getName();
			String key = filename.substring(0, filename.indexOf(".")).toLowerCase();
			String value = file.getAbsolutePath();
			fXSLHash.put(key, value);
		}
	}
	
	/**
	 * Loads all XSL file paths within a directory into and ArrayList.  
	 * This method is called recursively to ensure that all sub-directories are 
	 * included.
	 * @param xslFiles	The ArrayList containing the XSL file paths.
	 * @param currentDir	The current directory being scanned for XSL files.
	 * @return	They ArrayList of XSL file paths.
	 * @throws IOException
	 */
	private ArrayList<File> getAllXslFiles(ArrayList<File> xslFiles, File currentDir) throws IOException
	{
		FileUtils.verifyDirectory(currentDir);		
		File[] dirItems = currentDir.listFiles();
		for (int i = 0; i < dirItems.length; i++)
		{
			File item = dirItems[i];			
			if (item.isDirectory())
			{
				xslFiles = getAllXslFiles(xslFiles, item);
			}
			else if (isInvalidXslFile(item.getName()))
			{
				continue;
			}
			else {
				xslFiles.add(item);
			}
		}		
		return xslFiles;
	}
	
	
	/**
	 * Excludes files from the XSL file path list.
	 * @param str
	 * @return
	 */
	private boolean isInvalidXslFile(String xslFileName)
	{
		return 	!xslFileName.endsWith(".xsl");
	}	
}
