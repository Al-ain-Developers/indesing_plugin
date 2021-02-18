//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/Validator.java $
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

import java.io.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;


import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.w3c.dom.ProcessingInstruction;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import com.thaiopensource.validate.SchemaReader;
import com.thaiopensource.validate.rng.CompactSchemaReader;
import com.thaiopensource.util.PropertyMapBuilder;
import com.thaiopensource.validate.ValidateProperty;
import com.thaiopensource.validate.ValidationDriver;
import com.thaiopensource.validate.rng.RngProperty;
import com.thaiopensource.xml.sax.ErrorHandlerImpl;

/**
 * <p>
 * The Validator class can be used to validate IDML packages, 
 * extracted IDML packages, and non-package IDML files such as
 * IDMS (snippets) and ICML (InCopy stories).  Because non-package 
 * IDML files exist in a single file the class and documentation
 * will referred to them as unified IDML file).
 * </p>
 * <p>
 * This class can be used programaticlly by contructing an Validator
 * instance and calling one of three validate() methods on a given path.
 * </p>
 * <p>
 * You can construct an Validator with both types of schemas as follows:
 * </p>
 * <code>
 * Validator validator =  
 * 			new Validator("/MyFiles/PackageIDMLSchema", "/MyFiles/UnifiedIDMLSchema);
 * </code>
 * <p>
 * You also can us the more intelligent constructor that determines which type
 * of schema you are loading and initializes the Validator with the
 * appropriate schema type.
 * </p>
 * <code>
 * Validator validator =  
 * 			new Validator("/MyFiles/someIDMLSchema");
 * </code>
 * <p>
 * You could also use the setPackageSchema() and setUnifiedSchema() methods after
 * construction.
 * </p>
 * <p> 
 * Once an Validator is constructed you can validate using one of three
 * methods.  The validate method examines the file name and uses the appropriate
 * schema type for validation.  It's up to you to make sure that schema type
 * is loaded.  For example the following
 * </p>
 * <code> 
 * validator.validate("/MyFiles/Hello.idml");
 * validator.validate("/MyFiles/Story.icml");
 * </code>
 * <p>
 * You can manually specify which type of schema to use via the following calls.
 * </p>
 * <code>
 * validator.validatePackage("/MyFiles/Hello.idml");
 * validator.validateUnifiedFile("/MyFiles/Hello/icml");
 * </code>
 * <p>
 * This class also provides a main method that uses the intelligent
 * constructor and validate method.  For example, it could be run as follows:
 * </p>
 * <code>
 *  com.adobe.idml.validation.Validator 
 *  		/MyFiles/PackageIDMLSchema /MyFiles/UnifiedIDMLSchema/MyFiles/Hello.idml
 * </code>
 * <p>
 *  IDML tools comes with several shell script wrappers that show how to set the classpath.
 *  See Readme.txt in the IDMLTools directory for more information on these scripts.
 * </p>
 */
public class Validator
{
	/** Contructor used to create an instance of an Validator loaded with 
	 * paths to schemas.
	 * @param packageSchemaPath A path to the folder containing the package schema.  
	 * 		This can be nil if the caller doesn't expect to use a package schema.
	 * @param unifiedSchemaPath A path to the folder containing the unified schema.
	 * 		This can be nil if the caller doesn't expect to use a unified schema.
	 */
	public Validator( String packageSchemaPath, String unifiedSchemaPath )
	{
		init(packageSchemaPath, unifiedSchemaPath);
	}
	
	/**This constructor takes a path to one schema folder and 
	 * examines it to decide which type of schema it is, and calls
	 * init(String, String) appropriately. If it can
	 * find a designmap.rnc file in the schema folder it considers
	 * it a package schema.  Otherwise, it will be considered
	 * a  non-package schema.
	 * 
	 * @param schemaPath The path to the schema folder.  
	 */
	public Validator(String schemaPath)
	{
		// If it looks like a package schema, initialize
		// it like a package schema.
		File f = new File(schemaPath + "/designmap.rnc");
		if(f.exists() && f.isFile())
		{
			init(schemaPath, null);
				return;
		}
		
		// If it doesn't look like a package schema, initialize 
		// it lik a non-package schema
		init(null, schemaPath);
	}
	
	/** Simple contructor for instantiated an unoaded Validator.
	 * This is equivalent to calling Validator(null, null)."
	 * 
	 */
	public Validator()
	{
		init(null, null);
	}
	
	/**Initialize the class with both types of schemas.
	 * @param packageSchemaPath A path to the folder containing the package schema.
	 * @param unifiedSchemaPath A path to the folder containing the non-package schema.
	 */
	public void init(String packageSchemaPath, String unifiedSchemaPath)
	{
		setPackageSchema(packageSchemaPath);
		setUnifiedSchema(unifiedSchemaPath);
		
		// THis is probably some of the more important code in the class.
		// This is how you create and configure the Jing RelaxNG parser.
		ErrorHandlerImpl eh = new ErrorHandlerImpl() 
		{
			public void print(String message) 
			 {
				 String str = message.replaceFirst(".*_idmltools_temp_dir_\\d*_\\\\", "");
				 super.print(str);
			 }
		};
		PropertyMapBuilder properties = new PropertyMapBuilder();
		ValidateProperty.ERROR_HANDLER.put(properties, eh);
		RngProperty.CHECK_ID_IDREF.add(properties);
		SchemaReader sr = CompactSchemaReader.getInstance();  // Compact
		fValidationDriver = new ValidationDriver(properties.toPropertyMap(), sr);
	}
	
	/**Set the path to the package schema.
	 * @param packageSchemaPath
	 */
	public void setPackageSchema( String packageSchemaPath )
	{
		fPackageSchemaPath = packageSchemaPath;
	}
	
	/**
	 * @return the path to the folder containing the package schema
	 */
	public String getPackateSchema()
	{
		return fPackageSchemaPath;
	}
	
	/**Sets the unified schema path
	 * @param unifiedSchemaPath
	 */
	public void setUnifiedSchema( String unifiedSchemaPath )
	{
		fUnifiedSchemaPath = unifiedSchemaPath;
	}
	
	
	/**
	 * @return the path to the folder containing the unified schema
	 */
	public String getUnifiedSchema()
	{
		return fUnifiedSchemaPath;
	}
	
	
	/* Private method that validates an XML file, using the specified schema, if
	 * the file exists.  If the file does not exit it does nothing.
	 */
	private void validateOptionalFile(File xmlFile, File schemaFile) throws SAXException, IOException
	{
		if(!xmlFile.exists())
			return;
		
		validateFile(xmlFile, schemaFile);
	}
	
	/* Private method that validates an XML file, using the specified schema, if
	 * the file does not exists an IOExeception will be thrown.
	 */
	private void validateFile(File xmlFile, File schemaFile) throws SAXException, IOException
	{
		InputSource in = ValidationDriver.uriOrFileInputSource(schemaFile.getAbsolutePath());
		if (fValidationDriver.loadSchema(in))
		{
			fValidationDriver.validate(ValidationDriver.uriOrFileInputSource(xmlFile.getAbsolutePath()));
		}
		else
		{
			throw new IOException("Failed to load schema file!");
		}
	}
	
	/*
	 * Non-schema based checks on the package.
	 * 
	 * Is the ?aid PI present?
	 * Are all referenced package files present?
	 * 
	 */
	private boolean preVerifyPackage(String packageLocation)
	{
		boolean result = true;
		
		try
		{
			File designmapFile = new File(packageLocation + "/designmap.xml");
			if(designmapFile.exists() == false)
			{
				System.err.println("Error: This package does not contain a designmap.xml file!");
				return false;
			}
			
			DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
			Document document;
			document = docBuilder.parse(designmapFile);
			
			// Check for ?aid PI at the top of the file
			Node n = document.getFirstChild();
			if (n.getNodeType() == Node.PROCESSING_INSTRUCTION_NODE)
			{
				String target = "", data="";
				ProcessingInstruction pi = (ProcessingInstruction) n; 
				
				target = pi.getTarget();
				data = pi.getData();
				
				if(! (target.equals("aid") && 
						data.matches("^style=\"50\" type=\"document\" readerVersion=\"\\d\\.\\d\".*")) )
				{
					System.err.println("Error: Missing or incorrect ?aid Processing Instruction.");
					result = false;
				}
			}
			
			// Check all the idPkg elements to make sure the src file really exists.
			// I would have used document.getElementsByTagNameNS, but it didn't appear to 
			// work as documents.  So, isntead the following gets a list of all child
			// elements of the root element, and checks if they start with "idPkg".
			//
			Element rootElem = document.getDocumentElement();
			NodeList elements = rootElem.getElementsByTagName("*");
			for(int i=0; i<elements.getLength(); i++)
			{
				Element packageElem = (Element) elements.item(i);
				
				if( packageElem.getNodeName().startsWith("idPkg"))
				{
					String src = packageElem.getAttribute("src");
					File f = new File(packageLocation + "/" + src);
					if( f.exists() == false)
					{
						System.err.println("Error: Referenced file\"" + src + "\" does not exist in the package!");
						result = false;
					}
					
				}
			}
			
		}
		catch( Exception e)
		{
			System.err.println("Failed to parse designmap.xml file.");
			return false;
		}
		
		
		return result;
	}
	
	/* Private method that validates an uncompressed IDML package.  This is where
	 * the package generation really happens because even when the caller specifies
	 * a package, it is uncompressed into a temporary folder.
	 */
	private void validateUncompressPackage(String packageLocation) throws SAXException, IOException
	{
		// Non RelaxNG based validations
		if(preVerifyPackage(packageLocation) == false)
		{
			return;
		}
		
		// Start RelaxNG Validation
		//
		
		// There should always be a designmap.xml file to validate.  If it's missing then
		// that is a fatal error that should have been caught in preVerifyPackage().  
		File designmapFile = new File(packageLocation + "/designmap.xml");
		validateFile(designmapFile, new File(fPackageSchemaPath + "/designmap.rnc"));
		
		// Everything else is more or less optional.  If the package references 
		// a file that doesn't exist then it should have been detected in 
		// preVerifyPackage().  
		
		
		// validate Resources
		validateOptionalFile(new File(packageLocation + "/Resources/Fonts.xml"), new File(fPackageSchemaPath + "/Resources/Fonts.rnc"));
		validateOptionalFile(new File(packageLocation + "/Resources/Graphic.xml"), new File(fPackageSchemaPath + "/Resources/Graphic.rnc"));
		validateOptionalFile(new File(packageLocation + "/Resources/Preferences.xml"), new File(fPackageSchemaPath + "/Resources/Preferences.rnc"));
		validateOptionalFile(new File(packageLocation + "/Resources/Styles.xml"), new File(fPackageSchemaPath + "/Resources/Styles.rnc"));
		
		// Validate XML
		validateOptionalFile(new File(packageLocation + "/XML/BackingStory.xml"), new File(fPackageSchemaPath + "/XML/BackingStory.rnc"));
		validateOptionalFile(new File(packageLocation + "/XML/Mapping.xml"), new File(fPackageSchemaPath + "/XML/Mapping.rnc"));
		validateOptionalFile(new File(packageLocation + "/XML/Tags.xml"), new File(fPackageSchemaPath + "/XML/Tags.rnc"));
		
		
		// Validate each file in Stories
		File storiesDir = new File(packageLocation + "/Stories");
		File [] stories = storiesDir.listFiles();
		if( stories != null ) // null when there is no stores directory present
		{
			for(int i=0; i<stories.length; i++)
				validateFile(stories[i], new File(fPackageSchemaPath + "/Stories/Story.rnc"));
		}
		
		// Validate each file in Spreads
		File spreadsDir = new File(packageLocation + "/Spreads");
		File [] spreads = spreadsDir.listFiles();
		if( spreads != null )
		{
			for(int i=0; i<spreads.length; i++)
				validateFile(spreads[i], new File(fPackageSchemaPath + "/Spreads/Spread.rnc"));
		}
		
		// Validate each file in Master Spreads
		File masterSpreadsDir = new File(packageLocation + "/MasterSpreads");
		File [] masterSpreads = masterSpreadsDir.listFiles();
		if( masterSpreads != null )
		{
			for( int i=0; i< masterSpreads.length; i++)
				validateFile(masterSpreads[i], new File(fPackageSchemaPath + "/MasterSpreads/MasterSpread.rnc"));
		}
		
		
		
		
	}
	
	/**Valildates an IDML package.  This can be either a path to a compressed IDML
	 * file, or a directory containing uncompressed IDML files.
	 * 
	 * @param idmlFile A path to a folder or a compressed IDML file.
	 */
	public void validatePackage(String idmlFile)
	{
		//TODO At some point we might want to check the following...
		//	1. Check to make sure designmap.rnc and datatype.rnc exist in schema folder.
		//	
		
		// First check that we have a healthy package schema
		File designMapFile = new File(fPackageSchemaPath + "/designmap.rnc");
		if( designMapFile.exists() == false)
		{
			System.err.println("Package schema was not found or is incomplete!");
			System.err.println("The package schema is currently set to " + fPackageSchemaPath);
			return;
		}
		
		File packageFile = new File(idmlFile);
		File tempDir = null;
		
		try 
		{
			// If we're working with an archive file we need to uncompress
			// the archive to a temp folder.
			//
			if (packageFile.isFile())
			{
				// uncompress the file into a temp dir
				tempDir = FileUtils.CreateTempDir();
				
				if(tempDir != null)
				{
					Package.decompress(idmlFile, tempDir.getAbsolutePath());
				}
				
				idmlFile = tempDir.getAbsolutePath();
		
			}
			
			// Validate the uncompressed directory
			validateUncompressPackage(idmlFile);
			
		}
		catch (Exception e) 
		{
			System.err.println("Method validatePackage failed!");
			System.err.println(e.getMessage());
		}
		finally
		{
			if(tempDir != null)
				FileUtils.DeleteDirectory(tempDir);
		}
	}
	
	/**Validates a non-package file (such as an ICML, IDMS).
	 * @param idmlFilePath The path to the IDML xml file.
	 */
	public void validateUnifiedFile(String idmlFilePath)
	{
		// validate a non-package IDML file
		
		try
		{
			File xmlFile = new File(idmlFilePath);
			if( xmlFile.exists() == false)
			{
				System.err.println("XML file not found!");
				return;
			}
			
			File schemaFile = new File(fUnifiedSchemaPath + "/IDMarkupLanguage.rnc");
			if( schemaFile.exists() == false)
			{
				System.err.println("Non-package schema not found!");
				System.err.println("The non-package schema is currently set to " + fUnifiedSchemaPath);
				return;
			}
			
			validateFile(xmlFile, schemaFile );
		}
		catch( Exception e)
		{
			System.err.println("Method validateUnifiedFile failed!");
			System.err.println(e.getMessage());
		}
		
	}
	
	/**This method validates IDML packages (compressed or decompressed) as well as 
	 * non-package files (ICML and IDMS).  If the file name has the ".idml" 
	 * extension (case insensitive) or is a folder, it's considered a package and
	 * the package schema is used.  Otherwise it's considered to be a single IDML
	 * file.
	 * 
	 * @param file The abosolute or relative path to the IDML file of folder.
	 */
	public void validate(String file)
	{
		if(Package.isAPackage(file))
			validatePackage(file);
		else
			validateUnifiedFile(file);
	}

	private String fPackageSchemaPath;
	private String fUnifiedSchemaPath;
	private ValidationDriver fValidationDriver;
	
	/** Allows you to execute validation from the commnd line.
	 * This constructs an Validator with one schema loaded.
	 * @param args
	 */
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		// Validator schemaFile idmlFile
		
		if( args.length < 2 || (args.length >0 && args[0] == "-h"))
		{
			System.err.println("Usage:");
			System.err.println("Validator SchemaPath PackagePath [PackagePath...]");
			System.exit(-1);
		}
		
		// Create the validator with the passed in schema path
		Validator validator =  new Validator(args[0]);
		
		// Call validate on each remaining argument
		for( int i=1; i<args.length; i++)
		{
			validator.validate(args[i]);
		}
	}
}
