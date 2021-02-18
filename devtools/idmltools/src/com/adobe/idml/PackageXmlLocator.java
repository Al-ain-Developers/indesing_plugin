//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/PackageXmlLocator.java $
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

package com.adobe.idml;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import javax.xml.xpath.XPathExpressionException;

import org.w3c.dom.NodeList;

/**
 * Given the location of an extracted IDML Package file, this class
 * will locate the individual XML files.
 */
public class PackageXmlLocator {
	
	private String _expandedIdmlDirPath;
	
	/**
	 * Returns an ArrayList of Strings containing complete paths to each of the XML files found in a specified folder.
	 * @param dirPath	the folder containing the xml files
	 * @return	an ArrayList of file paths.
	 * @throws IOException 
	 */
	private ArrayList<String> getDirectoryXmlFiles(String dirPath) throws IOException 
	{
		File dir = FileUtils.getFile(dirPath);
		ArrayList<String> xmlFiles = new ArrayList<String>();
		String[] fileList = dir.list();
		for (int i = 0; i < fileList.length; i++) 
		{
			String file = (String) fileList[i];
			if (file.endsWith(".xml")) 
			{
				xmlFiles.add(dirPath + "/" + file);
			}
		}		
		return xmlFiles;
	}
	
	/**
	 * Instantiates a new XMLLocator object for the expanded IDML file provided.
	 * @param expandedIdmlDirPath 	The path to an expanded IDML File
	 */
	public PackageXmlLocator(String expandedIdmlDirPath)
	{
		_expandedIdmlDirPath = expandedIdmlDirPath;
	}
	
	/**
	 *  Instantiates a new XMLLocator object for the expanded IDML file provided.
	 * @param expandedIdmlDir	The file object representing the expanded IDML Directory.
	 */
	public PackageXmlLocator(File expandedIdmlDir)
	{
		_expandedIdmlDirPath = expandedIdmlDir.getAbsolutePath();
	}

	/**
	 * Returns a String with a folder path to the MasterSpreads folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getMasterSpreadsDirPath() 
	{
		return _expandedIdmlDirPath + "/MasterSpreads";
	}
	
	/**
	 * Returns a String with a folder path to the Spreads folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getSpreadsDirPath() 
	{
		return _expandedIdmlDirPath + "/Spreads";
	}
	
	/**
	 * Returns a String with a folder path to the Resources folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getResourcesDirPath() 
	{
		return _expandedIdmlDirPath + "/Resources";
	}
	
	/**
	 * Returns a String with a folder path to the Stories folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getStoriesDirPath() 
	{
		return _expandedIdmlDirPath + "/Stories";
	}
		
	/**
	 * Returns a String with a folder path to the XML folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getXMLDirPath() 
	{
		return _expandedIdmlDirPath + "/XML";
	}

	/**
	 * Returns a String with a folder path to the META-INF folder within an expanded IDML file.
	 * @return a String with a folder path.
	 */
	public String getMETAINFDirPath() 
	{
		return _expandedIdmlDirPath + "/META-INF";
	}	
	
	/**
	 * Returns a String with a file path to the designmap.xml file within an expanded IDML file.
	 * @return a String with a file path.
	 */
	public String getDesignMapFilePath() 
	{
		return _expandedIdmlDirPath + "/designmap.xml";
	}
	
	/**
	 * Returns a String with a file path to the Preferences.xml file within an expanded IDML file.
	 * @return a String with a file path.
	 */
	public String getPreferencesFilePath() 
	{
		return _expandedIdmlDirPath + "/Resources/Preferences.xml";
	}
	
	/**
	 * Returns a String with a file path to the Styles.xml file within an expanded IDML file.
	 * @return a String with a file path.
	 */
	public String getStylesFilePath() 
	{
		return _expandedIdmlDirPath + "/Resources/Styles.xml";
	}
	
	/**
	 * Returns a String with a file path to the Tags.xml file within an expanded IDML file.
	 * @return a String with a file path.
	 */
	public String getTagsFilePath() 
	{
		return _expandedIdmlDirPath + "/XML/Tags.xml";
	}
	
	/**
	 * Returns a String with a file path to the BackingStory.xml file within an expanded IDML file.
	 * @return a String with a file path.
	 */
	public String getBackingStoryFilePath() 
	{
		return _expandedIdmlDirPath + "/XML/BackingStory.xml";
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the METAINF folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getMETAINFXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getMETAINFDirPath());
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the XML folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getXMLXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getXMLDirPath());
	}
	
	/**
	 * Returns a String containing the path to the first XML File in the designated folder that returns a result.
	 * @param dir The path the the directory.
	 * @param xpath An XPath Expression.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public String getXMLFile(String dir, String xpath ) throws IOException, XPathExpressionException, PackageException
	{
		ArrayList<String> files = getDirectoryXmlFiles(dir);
		Iterator<String> iter = files.iterator();
		
		while(iter.hasNext())
		{
			String fileName = iter.next();
			File f = new File(fileName);
			NodeList nodeList = XmlUtils.getXPathValue(f, xpath);
			if( nodeList != null && nodeList.getLength() > 0)
			{
				return fileName;
			}
		}
		return null;
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the Stories folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getStoriesXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getStoriesDirPath());
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the Resources folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getResourcesXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getResourcesDirPath());
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the Spreads folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getSpreadXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getSpreadsDirPath());
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in the MasterSpreads folder of an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getMasterSpreadXmlFiles() throws IOException 
	{
		return getDirectoryXmlFiles(getMasterSpreadsDirPath());
	}
	
	/**
	 * Returns an ArrayList of Strings containing paths to all the XML Files in an expanded IDML file.
	 * @return an ArrayList of file paths.
	 * @throws IOException 
	 */
	public ArrayList<String> getAllXmlFiles() throws IOException 
	{
		ArrayList<String> allXmlFiles = new ArrayList<String>();
		allXmlFiles.addAll(getMasterSpreadXmlFiles());
		allXmlFiles.addAll(getSpreadXmlFiles());
		allXmlFiles.addAll(getResourcesXmlFiles());
		allXmlFiles.addAll(getStoriesXmlFiles());
		allXmlFiles.addAll(getXMLXmlFiles());
		allXmlFiles.addAll(getMETAINFXmlFiles());
		allXmlFiles.add(getDesignMapFilePath());
		return allXmlFiles;
	}
}
