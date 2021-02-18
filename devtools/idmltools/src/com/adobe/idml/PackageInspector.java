//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/PackageInspector.java $
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

package com.adobe.idml;

import java.io.File;
import java.io.IOException;
import java.util.*;

import javax.xml.xpath.XPathExpressionException;

import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

/**
 * PackageInspector contains a set of methods for inspecting package content.
 * It demonstrates how to use XmlUtils and PackageXmlLocator to extract data 
 * from the package.
 */
public class PackageInspector 
{
	private PackageXmlLocator fLocator;
	
	/**
	 * Instantiates a new PackageInspector object for the directory of XML files provided.
	 * @param expandedIDMLDir A directory containing an expanded IDML package.
	 */
	public PackageInspector(File expandedIDMLDir)
	{
		fLocator = new PackageXmlLocator(expandedIDMLDir.getAbsolutePath());
	}
	
	/**
	 * Instantiates a new PackageInspector object for the directory path to the XML files provided.
	 * @param expandedIDMLPath A path to a directory containing an expanded IDML package.
	 */
	public PackageInspector(String expandedIDMLPath)
	{
		this(new File(expandedIDMLPath));
		
	}
		
	/**
	 * Get the page height in points as a double.
	 * @return The Page Height in points.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public double GetPageHeight() throws PackageException, IOException, XPathExpressionException 
	{
		String result = XmlUtils.getAttribute(fLocator.getPreferencesFilePath(), "/idPkg:Preferences/DocumentPreference/@PageHeight");
		Double d = new Double(result);
		return d.doubleValue();	
	}
	
	/**
	 * Get the page width in points as a double.
	 * @return The page width in points.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public double GetPageWidth() throws PackageException, IOException, XPathExpressionException 
	{
		String result = XmlUtils.getAttribute(fLocator.getPreferencesFilePath(), "/idPkg:Preferences/DocumentPreference/@PageWidth");
		Double d = new Double(result);
		return d.doubleValue();	
	}
	
	/**
	 * Get the number of pages.
	 * @return The number of pages in the document
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public int GetPageCount() throws PackageException, IOException, XPathExpressionException 
	{
		ArrayList<String> pageIDs = XmlUtils.getAttributes(fLocator.getSpreadXmlFiles(), "/idPkg:Spread/Spread/Page/@Self");
		return pageIDs.size();
	}
	
	/**
	 * Gets the number of spreads.
	 * @return The number of spreads in a document
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public int GetSpreadCount() throws PackageException, IOException, XPathExpressionException 
	{
		ArrayList<String> spreadIDs = XmlUtils.getAttributes(fLocator.getSpreadXmlFiles(), "/idPkg:Spread/Spread/@Self");
		return spreadIDs.size();
	}
	
	/**
	 * Get the "Self" attribute for all stories in the package.
	 * @return ArrayList<String> of Self IDs
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public ArrayList<String> GetStoryIDs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributes(fLocator.getStoriesXmlFiles(), "/idPkg:Story/Story/@Self");
	}
	
	/**
	 * Get the Self attributes for all master spreads in the package.
	 * @return ArrayList<String> of all Self IDs
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public ArrayList<String> GetMasterSpreadIDs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributes(fLocator.getMasterSpreadXmlFiles(), "/idPkg:MasterSpread/MasterSpread/@Self");
	}
	
	/**
	 * Get the Self attributes for all layers in the package.
	 * @return ArrayList<String> of all Self IDs
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public ArrayList<String> GetLayerIDs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributes(fLocator.getDesignMapFilePath(), "/Document/Layer/@Self");
	}
	
	/**
	 * Get a Hashtable containing all ParagraphStyle Self ID/Name pairs.
	 * @return A Hashtable containing all ParagraphStyle Self ID/Name pairs.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public Hashtable<String, String> GetParagraphStyleIDNamePairs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getStylesFilePath(), "/idPkg:Styles/RootParagraphStyleGroup//ParagraphStyle", "Self", "Name");
	}
	
	/**
	 * Get a Hashtable containing all CharacterStyle Self ID/Name pairs.
	 * @return A Hashtable containing all CharacterStyle Self ID/Name pairs.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public Hashtable<String, String> GetCharacterStyleIDNamePairs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getStylesFilePath(), "/idPkg:Styles/RootCharacterStyleGroup//CharacterStyle", "Self", "Name");
	}
	
	/**
	 * Get a Hashtable of all object style Self ID/Name pairs.
	 * @return	A Hashtable containing all Self ID/Name pairs.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public Hashtable<String, String> GetObjectStyleIDNamePairs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getStylesFilePath(), "/idPkg:Styles/RootObjectStyleGroup//ObjectStyle", "Self", "Name");
	}
	
	/**
	 * Get Hashtable of all layer Self ID and Name pairs.
	 * @return	A Hashtable containing all layer Self ID/Name pairs.
	 * @throws Exception
	 */
	public Hashtable<String, String> GetLayerIDNamePairs() throws Exception
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getDesignMapFilePath(), "/Document/Layer", "Self", "Name");
	} 
	
	/**
	 * Get a Hashtable of all master spread Self ID/Name pairs.
	 * @return	A Hashtable containing all master spread Self ID/Name pairs.
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public Hashtable<String, String> GetMasterSpreadIDNamePairs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getMasterSpreadXmlFiles(), "/idPkg:MasterSpread/MasterSpread", "Self", "Name");
	} 
	
	/**
	 * Get a Hashtable of all Link ID/LinkResourceURI pairs in the package.
	 * @return Hashtable of all Link Self ID and LinkResourceURI pairs
	 * @throws IOException 
	 * @throws PackageException 
	 * @throws XPathExpressionException 
	 */
	public Hashtable<String, String> GetLinkIDURIPairs() throws PackageException, IOException, XPathExpressionException 
	{
		return XmlUtils.getAttributePairsForElement(fLocator.getSpreadXmlFiles(), "/idPkg:Spread//Link", "Self", "LinkResourceURI");
	} 
	
	/**
	 * Get Story Self ID/ Text Content pairs for each story in the package.
	 * @return A Hashtable mapping story Self IDs to plain text content
	 * @throws Exception
	 */
	public Hashtable<String,String> GetStoryIDsAndContent(  ) throws Exception
	{
		Hashtable<String,String> data = new Hashtable<String,String>();
		
		ArrayList<String> storyFiles = fLocator.getStoriesXmlFiles();
		Iterator<String> iter = storyFiles.iterator();
		while(iter.hasNext())
		{
			String storyPath = iter.next();
			String storyID = XmlUtils.getAttribute(storyPath, "/idPkg:Story/Story/@Self");
			
			String content = "";
			
			// This code actually works with the NodeList directly
			//
			NodeList nodes = XmlUtils.getXPathValue(storyPath, "/idPkg:Story/Story/descendant::Br|/idPkg:Story/Story/descendant::Content");
			int nodeCount = nodes.getLength();
			for (int i = 0; i < nodeCount; i++) 
			{
				Node n = nodes.item(i);
				if(n.getNodeName().equalsIgnoreCase("Content"))
				{
					content += n.getTextContent();
				}
				else if(n.getNodeName().equalsIgnoreCase("Br"))
				{
					content += "\n";
				}
			}			
			data.put(storyID, content);
		}
		
		return data;
	}
	
	private void dumpNameIDPairs(String header, Hashtable<String, String> pairs)
	{
		dumpHashtablePairs(header, pairs, "Self", "Name");
	}
	
	private void dumpHashtablePairs(String header, Hashtable<String, String> pairs, String keyName, String valueName)
	{
		System.out.println(header);
		System.out.println("=================");
		Set<String> keys = pairs.keySet();
		Iterator<String> iter = keys.iterator();
		while(iter.hasNext())
		{
			String name = iter.next();
			System.out.println(keyName + " = \"" + name + "\"" + "\t" + valueName + " = \"" + pairs.get(name) + "\"");
		} 
		System.out.println();
	}
	
	private void dumpStories(Hashtable<String, String> pairs)
	{
		System.out.println("Stories");
		System.out.println("=================");
		Set<String> keys = pairs.keySet();
		Iterator<String> iter = keys.iterator();
		while(iter.hasNext())
		{
			String name = iter.next();
			System.out.println(name);
			System.out.println("------------");
			System.out.println(pairs.get(name) + "\n");
		} 
		System.out.println();
	}
	
	/** Uses PackageInspector to dump various bits of content to STDOUT.
	 * @param idmlFile Path to an IDML file or directory containing expanded IDML file.
	 * @throws Exception
	 */
	public static void dumpInfo(String idmlFile) throws Exception
	{
		File srcFile = new File(idmlFile);
		File tempDir = null;
		boolean deleteTempDir = true;
		
		if(srcFile.exists() && srcFile.isDirectory())
		{
			tempDir = srcFile;
			deleteTempDir = false;
		}
		else
		{
			tempDir = Package.decompress(new File(idmlFile));
		}
		
		try
		{
			PackageInspector inspector = new PackageInspector(tempDir);
			
			// Page Height and Width
			System.out.println("Page Height:\t" + inspector.GetPageHeight());
			System.out.println("Page Width:\t" + inspector.GetPageWidth() + "\n");
			
			// Spread and Page Counts
			System.out.println("Spread Count:\t" + inspector.GetSpreadCount());
			System.out.println("Page Count:\t" + inspector.GetPageCount() + "\n");
			
			// Master Spreads and Layers
			inspector.dumpNameIDPairs("Master Spreads", inspector.GetMasterSpreadIDNamePairs());
			inspector.dumpNameIDPairs("Layers", inspector.GetLayerIDNamePairs());
			
			
			// Various Resources
			inspector.dumpNameIDPairs("Paragraph Styles", inspector.GetParagraphStyleIDNamePairs());
			inspector.dumpNameIDPairs("Character Styles", inspector.GetCharacterStyleIDNamePairs());
			inspector.dumpNameIDPairs("Object Styles", inspector.GetObjectStyleIDNamePairs());
			
			// Links
			inspector.dumpHashtablePairs("Links", inspector.GetLinkIDURIPairs(), "Self", "LinkResourceURI");
			
			// Stories
			inspector.dumpStories(inspector.GetStoryIDsAndContent());
		}
		catch(Exception e)
		{
			throw e;
		}
		finally
		{
			if(deleteTempDir)
				FileUtils.DeleteDirectory(tempDir);
		}
	}
	
	private static void usage()
	{
		System.err.println("usage: PackageInspector idml-file");
		System.err.println("Dumps information from the designaged idml-file or extracted package.");
		System.err.println("-h\tThis help message.");
		System.exit(-1);
	}
	
	/**
	 * Driver method for obtain information from a package.   
	 * Run with "-h" option for usage.
	 * @param args
	 */
	public static void main(String[] args) 
	{
		try
		{
			if(args.length != 1 || args[0].equalsIgnoreCase("-h"))
			{
				usage();
			}
			
			dumpInfo(args[1]);
		}
		catch( Exception e)
		{
			System.err.println(e.toString());
		}

	}
	
	
	
}
