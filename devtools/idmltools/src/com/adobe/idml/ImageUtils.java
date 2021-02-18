//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/ImageUtils.java $
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

import java.awt.Graphics2D;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.IIOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;


/**
 * This class contains utilities related to viewing images in a Java graphical interface.
 */
public abstract class ImageUtils {

	
	/**
	 * Given an image file and the required dimensions, this method will 
	 * return a scaled ImageIcon object for the image file provided.
	 * @param width The requested width for the image.
	 * @param height The requested height for the image.
	 * @param imgFile	The image file to generated an ImageIcon object from.
	 * @return A scaled ImageIcon object for the image file provided.
	 * @throws IOException
	 * @throws PackageException
	 */
	public static ImageIcon getScaledImageIcon(int width, int height, File imgFile) throws IOException, PackageException
	{
		BufferedImage img;
		if (!isSupportedByImageIO(imgFile.getName()))
		{
			String err = 	"The selected image file cannot be displayed in this utility." +
							"\nThis filetype is not supported for this dislay." +
							"\n\nSelected Image File: %s";
			throw new IllegalArgumentException(String.format(err, imgFile.getName()));
		}
		try 
		{
			img = ImageIO.read(imgFile);
		}
		catch(IIOException e) 
		{
			String err = 	"The selected image file cannot be displayed in this utility. " +
							"\nThis will happen if the color model of the image is CMYK instead of RGB. " +
							"\n\nSelected Image File: %s";
			throw new PackageException(String.format(err, imgFile.getName()));
		}
		BufferedImage scaledImg = scaleImage(img, width, height);
		
		ImageIcon icon = new ImageIcon();
		icon.setImage(scaledImg);
		
		return icon;
	}
	
	/**
	 * Scales a BufferedImage object to the size requested.
	 * @param img	The BufferedImage object to be scaled.
	 * @param width	The width to scale the image to.
	 * @param height The height to scale the image to.
	 * @return	Returns a BufferedImage object scaled to the width and height requested.
	 * @throws IOException
	 */
	public static BufferedImage scaleImage(BufferedImage img, int width, int height) throws IOException 
	{
		//Create a buffered image object.
		BufferedImage scaledImg = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		Graphics2D g = scaledImg.createGraphics();
		
		//Copy the img image to a scaled image.
		AffineTransform at = AffineTransform.getScaleInstance((double)width/img.getWidth(), (double)height/img.getHeight());
		
		//Update graphics object and return it.
		g.drawRenderedImage(img,at);
		return scaledImg;
	}

	/**
	 * Determines if the file type of the image is supported by this utility.
	 * @param imgPath The path the the image file to be tested.
	 * @return Returns true if the file type of the image is supported by this utility and false if not.	
	 */
	public static boolean isSupportedByImageIO(String imgPath)
	{
		String supportedSuffixes[] = ImageIO.getReaderFormatNames();
		String imgSuffix = FileUtils.getFileType(imgPath);
		for (int i = 0; i < supportedSuffixes.length; i++)
		{
			String suffix = supportedSuffixes[i];
			if (suffix.equalsIgnoreCase(imgSuffix))
			{
				return true;
			}
		}
		return false;
	}
}
	
	
