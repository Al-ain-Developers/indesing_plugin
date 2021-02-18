//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/XmlUtils.java $
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
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.ListIterator;

import javax.xml.XMLConstants;
import javax.xml.namespace.NamespaceContext;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.apache.xml.serialize.OutputFormat;
import org.apache.xml.serialize.XMLSerializer;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

/**
 * This class contains static methods for working with XML related technologies 
 * such as XML, XSL and XPath.
 */
public abstract class XmlUtils {

	/**
	 * Given a file object and an XML DOM Document, this method will write a formatted XML file
	 * to disk.
	 * @param doc	The Document object to be written to file.
	 * @param xmlFile	The file object the Document Object will be written to.
	 * @throws IOException
	 * @throws ParserConfigurationException
	 */
	public static void writeXmlFile(Document doc, File xmlFile) throws IOException, ParserConfigurationException
	{
		OutputFormat format = new OutputFormat(doc); // Serialize DOM
		
		//Used to print formatted XML to file.
        format.setIndenting(true);
        format.setIndent(2);        
        
        FileOutputStream out = new FileOutputStream(xmlFile);
		XMLSerializer serial = new XMLSerializer(out, format);
		serial.asDOMSerializer(); 
		serial.serialize(doc);
		out.close();
	}
	
	/**
	 * Get an empty DOM Document.
	 * @return	An empty DOM Document.
	 * @throws ParserConfigurationException
	 */
	public static Document getNewDOMDoc() throws ParserConfigurationException
	{
		DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = documentBuilderFactory.newDocumentBuilder();
		return builder.newDocument();
	}
	
	
	/**
	 * Get an empty XSL version 1.0 document.
	 * @return	An empty XSL version 1.0 document.
	 * @throws ParserConfigurationException
	 */
	public static Document getNewXslStylesheet() throws ParserConfigurationException
	{
		Document xslDoc = getNewDOMDoc();		
		Element rootElem = (Element) xslDoc.createElement("xsl:stylesheet");
		xslDoc.appendChild(rootElem);
		rootElem.setAttribute("xmlns:xsl", "http://www.w3.org/1999/XSL/Transform");
		rootElem.setAttribute("version", "1.0");
		return xslDoc;
	}
	
	/**
	 * Get a DOM Document object from an existing file.
	 * @param xmlFilePath	A path to the XML file.
	 * @return A DOM Document object derived from the XML file provided.
	 * @throws ParserConfigurationException
	 * @throws IOException
	 * @throws SAXException
	 */
	public static Document getExistingXmlDoc(String xmlFilePath) throws ParserConfigurationException, IOException, SAXException
	{
		InputSource src = new InputSource(xmlFilePath); 
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder parser = factory.newDocumentBuilder();
		return parser.parse(src);
	}
		
	/**
	 * Given an XML file path and an XPath expression, this method will return
	 * a node set containing the results of the query.
	 * @param xmlFilePath	The XML file to searched.
	 * @param expr	The xPath expression which will retrieve the required nodes from the XML file.
	 * @return NodeList containing the results of the xPath query.
	 * @throws PackageException 
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static NodeList getXPathValue(String xmlFilePath, String expr) throws PackageException, IOException, XPathExpressionException
	{
		File xmlFile = FileUtils.getFile(xmlFilePath);
		return getXPathValue(xmlFile, expr);
	}
	
	/**
	 * Given an XML file and an XPath expression, this method will return
	 * a node set containing the results of the query.
	 * @param xmlFile	The file to be queried.
	 * @param expr		The expression to query the file.
	 * @return	A NodeList containing the results of the query.
	 * @throws PackageException
	 * @throws IOException
	 * @throws XPathExpressionException 
	 */
	public static NodeList getXPathValue(File xmlFile, String expr) throws PackageException, IOException, XPathExpressionException
	{
		FileUtils.verifyFile(xmlFile);

		XPathFactory  factory = XPathFactory.newInstance();
		XPath xPath = factory.newXPath();			
		FileInputStream xmlStream = new FileInputStream(xmlFile);
		InputSource inputSource = new InputSource(xmlStream);
		
		//Note: This enables IDML Namespace to be used in xPath expressions.  Example: <idPkg:Masterspread>
		xPath.setNamespaceContext(new IdmlNamespaceContext());
		
		XPathExpression  xPathExpr = xPath.compile(expr);
		return (NodeList) xPathExpr.evaluate(inputSource, XPathConstants.NODESET);
	}	
	
	/**
	 * Returns a String containing the result after searching the element for the attribute name provided.  An 
	 * Exception is thrown if the attribute is not found.
	 * Searches an element for the specific attribute name.
	 * @param nm	The NamedNodeMap object for the node element.
	 * @param attrib	The attribute name to search for.
	 * @return	The value of the attribute name in the NamedNodeMap object provided.
	 * @throws PackageException
	 */
	public static String getAttribute(NamedNodeMap nm, String attrib) throws PackageException
	{
		Node n = nm.getNamedItem(attrib);
		if (n == null)
		{
			throw new PackageException(String.format("The attribute \"%s\" was not found.", attrib));
		}
		return n.getNodeValue();
	}
	
	
	/**
	 * Returns a String containing the result of the xPath expression after it is executed 
	 * against the XML file.    
	 * @param xmlFilePath	The single XML file to searched.
	 * @param expr	The xPath expression which will retrieve the required nodes from the XML file.  The expression should be written to lookup exactly one attribute.  
	 * Otherwise an Exception will be thrown.
	 * @return	String containing the results of the xPath query.
	 * @throws PackageException 
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static String getAttribute(String xmlFilePath, String expr) throws PackageException, IOException, XPathExpressionException
	{		
		NodeList results = getXPathValue(xmlFilePath, expr);
		Node n = results.item(0);  
		if ((results.getLength() != 1) || (n.getNodeType() != Node.ATTRIBUTE_NODE))
		{
			throw new PackageException(String.format("The xPath expression \"%s\" is invalid in this method. It should be written to return a single attribute.", expr));
		}
		return n.getNodeValue();			
	}
	
	/**
	 * Returns a String containing the result of the xPath expression after it is executed 
	 * against the XML file.  
	 * @param files		The XML files to searched.
	 * @param expr		The xPath expression which will retrieve the required nodes from the XML files.	The expression should be written to lookup a specific attribute.  
	 * Otherwise an Exception will be thrown.
	 * @return	ArrayList containing the results of the xPath query.
	 * @throws PackageException
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static String getAttribute(ArrayList<String> files, String expr) throws PackageException, IOException, XPathExpressionException
	{
		ListIterator<String> itr = files.listIterator();
		ArrayList<String> attributes = new ArrayList<String>();
		while (itr.hasNext())
		{			
			String file = itr.next();	
			
			NodeList results = getXPathValue(file, expr);
			Node n = null;
			if( results.getLength() > 0)
			{
				n = results.item(0);
				attributes.add(n.getNodeValue());
			}
			
			if( attributes.size() > 1)
				break;
		}	
		
		if (attributes.size() > 1)
		{
			throw new PackageException("The expression returned more than one value.");
		}
		else if(attributes.size() < 1)
		{
			throw new PackageException("The expression returned only one value.");
		}
		return attributes.get(0);
	}
	
	/**
	 * Get the number of nodes returned by an expression to an XML file.
	 * @param xmlFilePath	The path to the XML file to be queried.
	 * @param expr	The XPath expression to query the file with.
	 * @return	The number of nodes returned.
	 * @throws PackageException
	 * @throws IOException
	 * @throws XPathExpressionException
	 */
	public static int getNodeListCount(String xmlFilePath, String expr) throws PackageException, IOException, XPathExpressionException
	{
		NodeList results = getXPathValue(xmlFilePath, expr);
		return results.getLength();
	}
		
	/**
	 * Returns a ArrayList of Strings containing the result of the xPath expression after it is executed 
	 * against the XML file.  The expression should be written to lookup a specific attribute.  
	 * Otherwise an InterrogatorException will be thrown.
	 * @param xmlFilePath	The single XML file to searched.
	 * @param expr	The xPath expression which will retrieve the required nodes from the XML file.
	 * @return	ArrayList containing the results of the xPath query.
	 * @throws PackageException
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */	
	public static ArrayList<String> getAttributes(String xmlFilePath, String expr) throws PackageException, IOException, XPathExpressionException
	{
		File xmlFile = FileUtils.getFile(xmlFilePath);
		NodeList results = getXPathValue(xmlFile, expr);
		ArrayList<String> attributes = new ArrayList<String>();
		int resultCount = results.getLength();
		for (int i = 0; i < resultCount; i++) 
		{
			Node n = results.item(i);
			if (n.getNodeType() != Node.ATTRIBUTE_NODE)
			{
				throw new PackageException(String.format("The xPath expression \"%s\" is invalid in this method. It should be written to return an attribute.", expr));
			}
			attributes.add(n.getNodeValue());
		}
		return attributes;
	}
		
	/**
	 * Gets an ArrayList of the text content in a group of elements.
	 * @param xmlFilePath The path to the XML file to be queried.
	 * @param expr	The XPath Expression to query the XML file with.
	 * @return	An ArrayList of Strings containing the text content of the elements returned by the query.
	 * @throws PackageException
	 * @throws IOException
	 * @throws XPathExpressionException
	 */
	public static ArrayList<String> getElements(String xmlFilePath, String expr) throws PackageException, IOException, XPathExpressionException
	{
		File xmlFile = FileUtils.getFile(xmlFilePath);
		NodeList results = getXPathValue(xmlFile, expr);
		ArrayList<String> elements = new ArrayList<String>();
		int resultCount = results.getLength();
		for (int i = 0; i < resultCount; i++) 
		{
			Node node = results.item(i);
			if (node.getNodeType() != Node.ELEMENT_NODE)
			{
				throw new PackageException(String.format("The xPath expression \"%s\" is invalid in this method. It should be written to return an element.", expr));
			}
			Element element = (Element) node;
			String content = element.getTextContent();
			elements.add(content);
		}
		return elements;
	}
		

		
	/**
	 * Gets an ArrayList of the text content in a group of elements.
	 * @param xmlFilePaths The paths to the XML files to be queried.
	 * @param expr	The XPath Expression to query the XML file with.
	 * @return	An ArrayList of Strings containing the text content of the elements returned by the query.
	 * @throws PackageException
	 * @throws IOException
	 * @throws XPathExpressionException
	 */
	public static ArrayList<String> getElements(ArrayList<String> xmlFilePaths, String expr) throws PackageException, IOException, XPathExpressionException
	{
		ListIterator<String> itr = xmlFilePaths.listIterator();
		ArrayList<String> elements = new ArrayList<String>();
		while (itr.hasNext())
		{			
			String xmlFilePath = itr.next();			
			elements.addAll(getElements(xmlFilePath, expr));	
		}	
		return elements;
	}
			
	/**
	 * Returns a ArrayList of Strings containing the result of the xPath expression after it is executed 
	 * against the XML file.  The expression should be written to lookup a specific attribute.  
	 * Otherwise an InterrogatorException will be thrown.
	 * @param files		The XML files to searched.
	 * @param expr		The xPath expression which will retrieve the required nodes from the XML files.	
	 * @return	ArrayList containing the results of the xPath query.
	 * @throws PackageException
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static ArrayList<String> getAttributes(ArrayList<String> files, String expr) throws PackageException, IOException, XPathExpressionException
	{
		ListIterator<String> itr = files.listIterator();
		ArrayList<String> attributes = new ArrayList<String>();
		while (itr.hasNext())
		{			
			String xmlFilePath = itr.next();			
			attributes.addAll(getAttributes(xmlFilePath, expr));	
		}	
		return attributes;
	}	
	
	/**
	 * Returns a HashTable of Strings containing the result of the xPath expression after it is executed 
	 * against the XML file.  The expression should be written to lookup elements.  The key and value parameters 
	 * specify attributes in the the elements which will be loaded into the HashTable has key/value pairs.
	 * @param file	The single XML file to searched.
	 * @param expr	The xPath expression which will retrieve the required nodes from the XML files.	
	 * @param keyAttrib	The name of the attribute which will be the key in the HashTable returned.
	 * @param valueAttrib	The name of the attribute which will be the value in the HashTable returned.
	 * @return	HashTable containing the results of the xPath query.
	 * @throws PackageException	
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static Hashtable<String, String> getAttributePairsForElement(String file, String expr, String keyAttrib, String valueAttrib) throws PackageException, IOException, XPathExpressionException
	{
		Hashtable<String, String> ht = new Hashtable<String, String>();
		NodeList results = getXPathValue(file, expr);
		int resultsCount = results.getLength();
		for (int i = 0; i < resultsCount; i++) 
		{
			Node result = results.item(i);
			if (result.hasAttributes())
			{
				NamedNodeMap attrMap = result.getAttributes();
				String key = getAttribute(attrMap, keyAttrib);
				String value = getAttribute(attrMap, valueAttrib);
				ht.put(key, value);
			}
			else {
				throw new PackageException(String.format("The xPath expression \"%s\" is invalid in this method. Either the element returned does not contain attributes specified or the expression returned a single attribute.", expr));
			}
		}
		return ht;
	}	
	
	/**
	 * Returns a HashTable of Strings containing the result of the xPath expression after it is executed 
	 * against the XML files.  The expression should be written to lookup elements.  The key and value parameters 
	 * specify attributes in the the elements which will be loaded into the HashTable has key/value pairs.
	 * @param xmlFilePaths The list of XML files to queried.
	 * @param expr	The xPath expression which will retrieve the required nodes from the XML files.	
	 * @param keyAttrib	The name of the attribute which will be the key in the HashTable returned.
	 * @param valueAttrib	The name of the attribute which will be the value in the HashTable returned.
	 * @return	HashTable containing the results of the xPath query.
	 * @throws PackageException	
	 * @throws IOException 
	 * @throws XPathExpressionException 
	 */
	public static Hashtable<String, String> getAttributePairsForElement(ArrayList<String> xmlFilePaths, String expr, String keyAttrib, String valueAttrib) throws PackageException, IOException, XPathExpressionException
	{
		Hashtable<String, String> ht = new Hashtable<String, String>();
		ListIterator<String> itr = xmlFilePaths.listIterator();
		while (itr.hasNext())
		{			
			String file = itr.next();
			NodeList results = getXPathValue(file, expr);
			int resultsCount = results.getLength();
			for (int i = 0; i < resultsCount; i++) 
			{
				Node result = results.item(i);
				if (result.hasAttributes())
				{
					NamedNodeMap attrMap = result.getAttributes();
					String key = getAttribute(attrMap, keyAttrib);
					String value = getAttribute(attrMap, valueAttrib);
					ht.put(key, value);
				}
				else 
				{
					throw new PackageException(String.format("The xPath expression \"%s\" is invalid in this method. Either the element returned does not contain attributes specified or the expression returned a single attribute.", expr));
				}
			}
		}		
		return ht;
	}
}

//TODO: Comment this.
class IdmlNamespaceContext implements NamespaceContext {

    public String getNamespaceURI(String prefix) {
        if (prefix == null) 
        {
        	throw new NullPointerException("Null prefix");
        }
    
        else if ("idPkg".equals(prefix)) 
    	{
        	return "http://ns.adobe.com/AdobeInDesign/idml/1.0/packaging";
    	}
    
        else if ("xml".equals(prefix)) 
    	{
        	return XMLConstants.XML_NS_URI;
       	}
        
        return XMLConstants.NULL_NS_URI;
    }
    
    public String getPrefix(String uri) {
        throw new UnsupportedOperationException();
    }

	public Iterator<Object> getPrefixes(String arg0) {
		throw new UnsupportedOperationException();
	}
}
