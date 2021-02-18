//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/Package.java $
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

import java.io.*;
import java.util.zip.*;
import java.util.*;
import java.io.IOException;


/**
 * Contains methods for working with IDML packages.
 */
public class Package 
{

	/** 
	 * Is this an IDML package.
	 * @param filePath A path to an IDML file that may or may not already exist. 
	 * @return true if this appears to be an IDML file.
	 */
	public static boolean isAPackage(String filePath)
	{
		File file = new File(filePath);
		
		// If it's a directory, then we'll consider it a package.
		if( file.isDirectory())
		{
			return true;
		}
		
		// If it ends with an ".idml" extension then consider it an IDML file
		return filePath.toLowerCase().endsWith(".idml");
	}
	
	/**
	 * Throws an exception if the file is not an IDML package.
	 * @param filePath	A path to the file requiring verification.
	 */
	public static void verifyPackage(String filePath)
	{
		if (!Package.isAPackage(filePath))
		{
			String err = String.format("%s is not an IDML Package.", filePath);
			throw new IllegalArgumentException(err);
		}
	}
	
	/** 
	 * The decompress method can be used to extract an IDML archive specified
	 * in the compressedFilePath parameter to the directory specified in the targetDirPath parameter.
	 * @param compressedFilePath the IDML archive to decompress
	 * @param targetDirPath The directory to extract files to.
	 * @throws IOException 
	 */
	public static void decompress(String compressedFilePath, String targetDirPath) throws IOException
	{	
		File compressedFile = FileUtils.getFile(compressedFilePath);
		File targetDir = FileUtils.getFile(targetDirPath);
		decompress(compressedFile, targetDir);
	}
	
	/** 
	 * The decompress method can be used to extract an IDML archive specified
	 * in the idmlSrcFile parameter to the directory specified in the idmlDestinationFile parameter.
	 * @param idmlSrcFile	The source file.
	 * @param idmlDestinationFile The destination file.
	 * @throws IOException 
	 */
	public static void decompress(File idmlSrcFile, File idmlDestinationFile) throws IOException 
	{
		//In case the directory does not exist, this ensures the directory does exist.
		FileUtils.ensureDirectory(idmlDestinationFile);
		
		String targetName = idmlSrcFile.getAbsolutePath();
		targetName = idmlDestinationFile.getPath();
		if( targetName.endsWith(File.separator) == false)
			targetName += File.separator;
		
		ZipFile idmlFile = new ZipFile(idmlSrcFile);
		
		try
		{
			Enumeration<? extends ZipEntry> entries = idmlFile.entries();
			while(entries.hasMoreElements())
			{
				ZipEntry entry = (ZipEntry)entries.nextElement();
				String str = targetName + entry.getName();
				
				int z = str.lastIndexOf('/');
				if (z > 0) 
				{
					String dirName = str.substring(0, z);
					File dirFile = new File(dirName);
					if (dirFile.exists() == false) 
				            dirFile.mkdir();
				}
				
				extractFile(idmlFile.getInputStream(entry),
						new BufferedOutputStream(new FileOutputStream(targetName + entry.getName())));
			}
		}
		catch(IOException e)
		{
			throw e;
		}
		finally
		{
			idmlFile.close();
			idmlFile = null;
		}
	}
	
	/**
	 * Creates a temporary directory and decompresses the IDML file provided into that directory.
	 * @param idmlFilePath The location of the IDML file to be decompressed.
	 * @return	Returns the location of the temporary directory created.
	 * @throws IOException 
	 */
	public static File decompress(String idmlFilePath) throws IOException 
	{
		File idmlFile = FileUtils.getFile(idmlFilePath);
		return decompress(idmlFile);
	}
	
	/** 
	 * Creates a temporary directory and decompresses the IDML file provided into that directory.
	 * @param idmlSrc The location of the IDML file to be decompressed.
	 * @return	Returns File object representing the location of the directory created.
	 * @throws IOException 
	 */
	public static File decompress(File idmlSrc) throws IOException
	{
		File tempDir = FileUtils.CreateTempDir();
		String tempDirPath = tempDir.getPath();

		if( tempDirPath.endsWith(File.separator) == false)
			tempDirPath += File.separator;
		
		ZipFile idmlFile = new ZipFile(idmlSrc);
		
		try
		{
			Enumeration<? extends ZipEntry> entries = idmlFile.entries();
			while(entries.hasMoreElements())
			{
				ZipEntry entry = (ZipEntry)entries.nextElement();
				String str = tempDirPath + entry.getName();
							
				int z = str.lastIndexOf('/');
				if (z > 0) 
				{
					String dirName = str.substring(0, z);
					File dirFile = new File(dirName);
					if (dirFile.exists() == false) 
				            dirFile.mkdir();
				}
				
				extractFile(idmlFile.getInputStream(entry),
				           new BufferedOutputStream(new FileOutputStream(tempDirPath + entry.getName())));
			}
		}
		catch(IOException e)
		{
			throw e;
		}
		finally
		{
			idmlFile.close();
			idmlFile = null;
		}
		
		return tempDir;
	}
	
	/** 
	 * The extractFile is a private method called by decompress().
	 * @param in a non-nil InputStream
	 * @param out a non-nil OutputStream
	 * @throws IOException
	 */
	private static final void extractFile(InputStream in, OutputStream out) throws IOException
	{
		byte[] buffer = new byte[1024];
		int len;
		
		while((len = in.read(buffer)) >= 0)
			out.write(buffer, 0, len);
		
		in.close();
		out.close();
	}
	
	/** 
	 * The compress method builds an IDML compatible archive from
	 * all the files contained in directory provided.  This does not include the
	 * containing folder.
	 * @param dirPath A path to a folder containing the files to be compressed into an IDML archive
	 * @param fileName  The name of the new IDML package file.
	 * @throws IOException 
	 */
	public static void compress(String dirPath, String fileName) throws IOException 
	{		
		File dir = FileUtils.getFile(dirPath);
		compress(dir, fileName);
	}
	
	/** 
	 * The compress method builds an IDML compatible archive from
	 * all the files contained in directory provided.  This does not include the
	 * containing folder.	  
	 * @param locationDir  A file object representing the directory containing files to be compressed into an IDML archive.
	 * @param fileName  The name of the new IDML package file.
	 * @throws IOException 
	 */
	public static void compress(File locationDir, String fileName) throws IOException 
	{
		FileUtils.verifyDirectory(locationDir);
		
		// Setup a stream for the zip file
		ZipOutputStream out = new ZipOutputStream(new FileOutputStream(fileName));
		out.setLevel(Deflater.BEST_SPEED);  
		
		// Before adding the files, do some work to make sure you are working with
		// consistent file separators and a locationName that ends in a separator.
		// We need to know this because we have to trim that string off at some point.
		String locationName = locationDir.getPath();
		if( locationName.endsWith(File.separator) == false)
			locationName += File.separator;
		
		// Add the Files and close the stream
		addFiles(out, locationName, locationName);
		out.close();
	}
	
	/** 
	 * The addFiles method is a private helpter for compress().  It recursively 
	 * walks the directory structure adding files to the archive. It ensures
	 * that if mimetype exists in the top level folder, it is the first file added
	 * to the the archive, and that it's not compressed.  This is required by IDML.
	 * @param out
	 * @param filePath
	 * @param rootFileName
	 * @throws IOException 
	 */
	private static void addFiles(ZipOutputStream out, String filePath, String rootFileName) throws IOException 
	{
		File file = FileUtils.getFile(filePath);
		if (file.isDirectory())
        {
        	String[] children = file.list();
        	if( filePath.equals(rootFileName))
        	{
	        	// The mimetype file has to be added first.
	        	// This will find it and add it first if it exists.
        		// And, this is only done for the initial directory.
	        	for (String child: children) {
	        		if( child.equalsIgnoreCase("mimetype"))
	        		{
	        			addFiles(out, filePath + File.separator + child, rootFileName);
	        			break;
	        		}
	        	}
        	}        	

            for (int i=0; i<children.length; i++) {
            	String child = children[i];
            	if( child.equalsIgnoreCase("mimetype") && filePath.equals(rootFileName))
            		continue;
            	
            	addFiles(out, filePath + File.separator + child, rootFileName);
            }
        } 
        else 
        {
        	// It's a file so we're going to write it to the Zip file out stream
        	
        	// But before we do, we want to drop off the initial starting directory
        	// which through the recursion is represented by rootFileName.
        	//
        	String simplifiedFileName = filePath;
        	
        	// I expect this to be true, but make sure the file name actually starts
        	// with rootFileName.
        	if( simplifiedFileName.startsWith(rootFileName))
        	{
        		// Trim off the rootFileName string from the front of the string
        		simplifiedFileName = simplifiedFileName.substring(rootFileName.length() + 1);
        	}
            ///System.out.println(simplifiedFileName);
        	
        	
        	// We need to use unix file separators instead of windows.
        	simplifiedFileName = simplifiedFileName.replaceAll("\\\\", "/");
        	
            byte[] buf = new byte[1024];
            
            
            // Add ZIP entry to output stream.
            ZipEntry entry = new ZipEntry(simplifiedFileName);
            
            // We save mimetype non-compressed
            if( file.getName().equals("mimetype"))
            {
	            CRC32 crc = new CRC32();
	            BufferedInputStream bis = new BufferedInputStream(
	                    new FileInputStream(file));
	            int bytesRead;
	            while ((bytesRead = bis.read(buf)) != -1) {
	                crc.update(buf, 0, bytesRead);
	            }
	            bis.close();
	            entry.setMethod(ZipEntry.STORED);
	            entry.setCompressedSize(file.length());
	            entry.setSize(file.length());
	            entry.setCrc(crc.getValue());
            }
            
            out.putNextEntry(entry);
    
            // Transfer bytes from the file to the ZIP file
            FileInputStream in = new FileInputStream(file);
            int len;
            while ((len = in.read(buf)) > 0) {
                out.write(buf, 0, len);
            }
    
            out.closeEntry();
            in.close();
        }
    }
	
	private static void usage()
	{
		System.err.println("Usage: Package -hcd source destination");
		System.err.println("-h\tThis help message.");
		System.err.println("-d\tDecompress source file into destination directory");
		System.err.println("-c\tCompress all files in the source directory into destination file");
		System.err.println("-i\tCall PackageInspector to dump info from this package.");
		System.exit(-1);
	}
	
	/** 
	 * Driver method for packaging and unpackaging.   
	 * Run with "-h" option for usage.
	 * @param args
	 */
	public static void main(String[] args) 
	{
		try
		{
			if ((args.length < 2) || (args.length > 3)) 
			{
				if ((args.length == 1 ) && (args[0].equals("-h")))
				{
					usage();					
				}
				else
				{
					System.err.println("Error: Incorrect usage!");
					usage();	
				}				
			}
			else if( args[0].equals("-c"))
			{
				compress(args[1], args[2]);
			}
			else if( args[0].equals("-d"))
			{
				String target = args[1];
				String dest = args.length == 3 ? args[2] : ".";
				decompress(target, dest);
			}
			else if(args[0].equals("-i"))
			{
				String target = args[1];
				PackageInspector.dumpInfo(target);
			}
		}
		catch( Exception e)
		{
			System.err.println(e.toString());
		}

	}
}
