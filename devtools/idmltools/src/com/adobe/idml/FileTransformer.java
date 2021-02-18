//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/FileTransformer.java $
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
package com.adobe.idml;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.ListIterator;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.stream.StreamResult;
import javax.xml.transform.stream.StreamSource;

/** The FileTransformer class is used to transform s single XML input file
 *	into one or many files.  Two use cases for file transformation are supported.  
 *	The output file can be specified, or the style sheets can be responsible for 
 *	file output.  See the transformFile() method.
 */
public class FileTransformer
{
	/** Construct a FileTransformer loaded with a style sheet.
	 * @param xslFile The XSL file that will be used for transformation.
	 * @param params The parameters that will be passed to the style sheet.
	 * @throws TransformerConfigurationException
	 * @throws TransformerFactoryConfigurationError
	 */
	public FileTransformer(File xslFile, ArrayList<XslParam> params) throws TransformerConfigurationException, TransformerFactoryConfigurationError
	{
		fTransformer = TransformerFactory.newInstance().newTransformer(new StreamSource(xslFile));
		addParameters(params);
	}
	
	/** Adds parameters that will be passed to the style sheet.
	 * @param params
	 */
	public void addParameters(ArrayList<XslParam> params)
	{
		if(params != null) 
		{
			ListIterator<XslParam> itr = params.listIterator();
			while(itr.hasNext())
			{
				XslParam param = itr.next();
				fTransformer.setParameter(param.getName(), param.getValue());
			}
		}
	}
	
	/** Clears the parameters that are passed to the style sheet.
	 */
	public void clearParameters()
	{
		fTransformer.clearParameters();
	}
	
	/** Reinitializes to a new XSL file and set of parameters.
	 * @param xslFile
	 * @param params Style sheet parameters, or null.
	 * @throws TransformerConfigurationException
	 * @throws TransformerFactoryConfigurationError
	 */
	public void reset(File xslFile, ArrayList<XslParam> params) throws TransformerConfigurationException, TransformerFactoryConfigurationError
	{
		fTransformer = TransformerFactory.newInstance().newTransformer(new StreamSource(xslFile));
		addParameters(params);
	}
	
	/** Transforms an XML file with the current style sheet and parameters.
	 * @param xmlFile The File to transform
	 * @param outFile The output file.  Transformation has a standard output.  This output is 
	 * 					captured in the specified outFile if non-null.  Often style sheets will manage 
	 * 					their own output files.  If this is the case the main output isn't needed.  A
	 * 					null outFile can be passed if the caller doesn't need the standard output. 
	 * @throws TransformerException
	 * @throws IOException
	 */
	public void transformFile(File xmlFile, File outFile) throws TransformerException, IOException 
	{
		File tempFile = FileUtils.CreateTempFile();
		FileOutputStream fileOutStream = new FileOutputStream(tempFile.getAbsolutePath());		
		fTransformer.transform(new StreamSource(xmlFile), new StreamResult(fileOutStream));
		fileOutStream.close();
		
		if(outFile != null)
		{
			outFile.delete();
			tempFile.renameTo(outFile);
		}
	}
	
	private Transformer fTransformer;
}
