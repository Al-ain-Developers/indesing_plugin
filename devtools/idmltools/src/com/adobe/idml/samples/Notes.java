//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/Notes.java $
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

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.ListIterator;

import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.xpath.XPathExpressionException;

import com.adobe.idml.FileTransformer;
import com.adobe.idml.FileUtils;
import com.adobe.idml.Package;
import com.adobe.idml.PackageException;
import com.adobe.idml.PackageXmlLocator;
import com.adobe.idml.PackageXslLocator;
import com.adobe.idml.XmlUtils;

/**
 * This class contains tools for removing and extracting notes from an IDML package.
 */
public class Notes 
{
	
	private PackageXslLocator fXslLocator;
	
	/**
	 * The default constructor.  
	 */
	public Notes() {	}
	
	/**
	 * This constructor sets up an XSL Locator object.
	 * @param xslPath	The path to the XSL files needed for transforms.
	 * @throws IOException
	 */
	public Notes(String xslPath) throws IOException
	{
		fXslLocator = new PackageXslLocator(xslPath);
	}
	
	/**
	 * Copies notes from an IDML file to a separate text file.
	 * @param idmlSource	The IDML file to extract notes from.
	 * @param outputFile	The location to write the output file containing notes to.  
	 * @throws PackageException
	 * @throws IOException
	 * @throws XPathExpressionException 
	 */
	public void extractNotes(String idmlSource, String outputFile) throws PackageException, IOException, XPathExpressionException
	{
		//Ensure the idmlSource is a valid IDML file.
		Package.verifyPackage(idmlSource);
		
		//Create a new output file and get a writer for that file.
		FileUtils.deleteFile(outputFile);
		File txtOutputFile = FileUtils.createFile(outputFile);
		BufferedWriter txtOutputFileWriter = FileUtils.getFileWriter(txtOutputFile);
		
		//Get story files from the idmlSouce package
		File expandedIdmlDir = Package.decompress(idmlSource);			
		PackageXmlLocator xmlLoc = new PackageXmlLocator(expandedIdmlDir);			
		ArrayList<String> storyFiles = xmlLoc.getStoriesXmlFiles();
		ListIterator<String> storyFilesItr = storyFiles.listIterator();	
		
		//Iterate through story files.
		int totalNoteCount = 1;
		while (storyFilesItr.hasNext())	
		{	
			//Iterate through notes in the story file.
			String storyFile = storyFilesItr.next();
			int fileNoteCount =  XmlUtils.getNodeListCount(storyFile, "//Note");			
			for (int i = 1; i <= fileNoteCount; i++)
			{
				//Write Note Heading.
				String noteHeading = String.format("=============== Note %d ===============", totalNoteCount);
				txtOutputFileWriter.write(noteHeading);
				txtOutputFileWriter.newLine();				
				
				//Iterate through each content tag in the Note
				String expr = String.format("//Note[%d]//Content", i);
				ArrayList<String> noteContents = XmlUtils.getElements(storyFile, expr);
				ListIterator<String> noteContentsItr = noteContents.listIterator();	
				while (noteContentsItr.hasNext())
				{	
					String content = noteContentsItr.next();
					txtOutputFileWriter.write(content);
					//When a single note has multiple content elements they are typically separated by a <BR> tag.
					//For that reason a new line is added here to format the notes as they appear in InDesign.
					txtOutputFileWriter.newLine();
				}
				
				//Add space between notes in the output file.
				totalNoteCount++;
				txtOutputFileWriter.newLine();
			}
		}			
		
		//Complete and cleanup
		txtOutputFileWriter.close();
		FileUtils.DeleteDirectory(expandedIdmlDir);
	}
	
	/**
	 * Creates a copy of an IDML file with the notes removed.
	 * @param idmlSource	The IDML file to remove notes from.
	 * @param outputFile	The IDML copy of idmlSource with the notes removed.
	 * @throws IOException
	 * @throws TransformerFactoryConfigurationError
	 * @throws TransformerException
	 */
	public void removeNotes(String idmlSource, String outputFile) throws IOException, TransformerFactoryConfigurationError, TransformerException
	{	
		//Ensure the idmlSource is a valid IDML file.
		Package.verifyPackage(idmlSource);
		
		//Ensure the outputFile has an IDML extension.
		Package.verifyPackage(outputFile);
		
		//Get story files from the idmlSouce package
		File expandedIdmlDir = Package.decompress(idmlSource);	
		PackageXmlLocator xmlLoc = new PackageXmlLocator(expandedIdmlDir);	
		ArrayList<String> storyFiles = xmlLoc.getStoriesXmlFiles();
		ListIterator<String> storyFilesItr = storyFiles.listIterator();

		try 
		{	
			//Iterate through story files.
			while (storyFilesItr.hasNext())
			{		
				String storyFilePath = storyFilesItr.next();
				File storyFile = new File(storyFilePath);
				
				String xslFilePath = fXslLocator.getCorrespondingXslFilePath(storyFilePath);
				File xslFile = new File(xslFilePath);
				
				//Transform each story file with the appropriate XSL file.
				FileTransformer fileTransformer = new FileTransformer(xslFile, null);
				fileTransformer.transformFile(storyFile, storyFile); // overwrites xmlFile
			}
			
			//Create the output IDML Package.
			Package.compress(expandedIdmlDir, outputFile);
		}
		finally 
		{
			//Cleanup
			FileUtils.DeleteDirectory(expandedIdmlDir);
		}
	}
	
	
	private static void usage()
	{
		System.out.println("Usage: Notes [operation] [Source IDML File] [Output File]");
		System.out.println("\nOperations:");
		System.out.println("\t-e\tExtracts or copies the notes from an IDML file to a text file.");
		System.out.println("\t-r\tCreates a copy of an IDML file with the notes removed.");
		System.out.println("\nExamples: ");
		System.out.println("\tNotes -e SampleNote.idml SampleNote_Notes.txt");
		System.out.println("\tNotes -r SampleNote.idml SampleNote_NotesRemoved.idml");
		System.exit(-1);
	}
	
	/**
	 * The main method used to initialize the Notes class.
	 * @param args parameters provided by the console application.
	 */
	public static void main(String[] args) 
	{
		if(args.length < 3)
		{
			usage();
		}
		
		String operation = args[0];
		String idmlSource = args[1];
		String outputFile = args[2];
		
		try
		{		
			//The output files have not yet been created.
			//This ensures the parent directory which will 
			//contain the file exists.
			FileUtils.ensureParentDirectory(outputFile);
			
			if ( operation.equalsIgnoreCase("-e"))
			{
				Notes en = new Notes();
				en.extractNotes(idmlSource, outputFile);
			}
			else if ( operation.equalsIgnoreCase("-r"))
			{
				String xslPath = "xsl/remove";				
				Notes en = new Notes(xslPath);
				en.removeNotes(idmlSource, outputFile);					
			}
			else {
				usage();
			}
		}
		catch( Exception e)
		{
			String err = "Remove Notes Failure.\nError Message:\t%s\nStack Trace:\t%s\n";
			System.err.printf(err, e.getMessage(), e.getStackTrace());
		}
	}
}
