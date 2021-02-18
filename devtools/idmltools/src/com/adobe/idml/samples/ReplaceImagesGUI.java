//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/devtools/idmltools/src/com/adobe/idml/samples/ReplaceImagesGUI.java $
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

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import java.io.File;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Set;

import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.adobe.idml.FileUtils;
import com.adobe.idml.ImageUtils;
import com.adobe.idml.PackageException;
import com.adobe.idml.samples.ReplaceImages;

/**
 * This is a Swing graphical wrapper for the ReplaceImages class.
 */
public class ReplaceImagesGUI extends JFrame implements WindowListener
{
	private JPanel dialogPane;
	private JTabbedPane tabbedPane;
	private JPanel pnlFolderOptions;
	private JTextField txtSourceIdmlPath;
	private JButton btnSourceIdmlPath;
	private JTextField txtDestIdmlDirPath;
	private JTextField txtDestIdmlFilePath;
	private JButton btnDestIdmlPath;
	private JLabel lblSourceIdmlPath;
	private JLabel lblDestIdmlDirPath;
	private JLabel lblDestIdmlFilePath;
	private JButton btnSetPathOptions;
	private JPanel pnlReplaceImages;
	private JSplitPane spReplaceImages;
	private JScrollPane scpImages;
	private JList lstImages;
	private DefaultListModel lstImagesModel;
	private JPanel pnlImageDesc;
	private JLabel lblImgSize;
	private JLabel lblImgSizeValue;
	private JLabel lblImgLocation;
	private JLabel lblImgLocationValue;
	private JButton btnReplaceImages;
	private JLabel lblImgDisplay;
	private JButton btnWriteIdmlFile;	
	private ReplaceImages fReplaceImages;
	private Hashtable<String, String> fLinks;
	
	/**
	 * Constructor requiring a ReplaceImages object.
	 * @param ri The ReplacesImage object used to interact with IDML files.
	 */
	public ReplaceImagesGUI(ReplaceImages ri) {
		fReplaceImages = ri;
		init();
	}

	private void btnSourceIdmlPathActionPerformed(ActionEvent e) 
	{
		JFileChooser fc = new JFileChooser();
		fc.setCurrentDirectory(new File("."));

		int returnVal = fc.showOpenDialog(null);
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
          txtSourceIdmlPath.setText(fc.getSelectedFile().getAbsolutePath());
        }
	}

	private void btnDestIdmlPathActionPerformed(ActionEvent e) 
	{
		JFileChooser fc = new JFileChooser();
		fc.setCurrentDirectory(new File("."));
		fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		
		int returnVal = fc.showOpenDialog(null);
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
          txtDestIdmlDirPath.setText(fc.getSelectedFile().getAbsolutePath());
        }
	}

	private void btnSetPathOptionsActionPerformed(ActionEvent e) {
		try 
		{
			//Incase a file was already extracted, this will ensure no temp directories are left behind.
			fReplaceImages.cleanup();
			
			//Open the IDML Source Path.
			String idmlSourcePath = txtSourceIdmlPath.getText();
			fReplaceImages.setSourcePackage(idmlSourcePath);
			fLinks = fReplaceImages.getLinksFromPackage();
			
			//Update the UI with images found.
			loadLinks();
			
			//Go to the replace images tab.
			tabbedPane.setSelectedIndex(1);
		} 
		catch (ArrayIndexOutOfBoundsException  exc)
		{
			//This error should not occur but it will not hurt this application if it does.
		}
		catch (Exception exc) 
		{
			String err = exc.getMessage();
			JOptionPane.showMessageDialog(this, err, "Replace Images Error", JOptionPane.ERROR_MESSAGE);
		}
	}

	private void btnReplaceImagesActionPerformed(ActionEvent e)
	{		
		//Get selected image file.
		int selectedIndex = lstImages.getSelectedIndex();
		
		//The Replace Images button was clicked but an image was not selected.
		if (selectedIndex < 0)
		{
			JOptionPane.showMessageDialog(this, "Please select an image to replace", "Replace Images", JOptionPane.INFORMATION_MESSAGE);
			return;
		}
		
		//Get the imageID of the selected image.
		String imgID = (String) lstImagesModel.get(selectedIndex); 
			
		JFileChooser fc = new JFileChooser();
		fc.setCurrentDirectory(new File("."));

		int returnVal = fc.showOpenDialog(null);
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
        	String imgPath = String.format("file:%s", fc.getSelectedFile().getAbsolutePath());
        	fLinks.put(imgID, imgPath);
        	loadLinks();
        	lstImages.setSelectionInterval(selectedIndex, selectedIndex);
        }
	}
	
	/**
	 * Updates the UI to reflect changes to the links Hashtable.
	 */
	private void loadLinks() {
		Set<String> keys = fLinks.keySet();			
		Iterator<String> itr = keys.iterator();
		
		lstImagesModel.clear();				
		while(itr.hasNext())
		{
			String id = itr.next();
			lstImagesModel.addElement(id);
		}
	}

	private void btnWriteIdmlFileActionPerformed(ActionEvent e) 
	{
		String destDirPath = txtDestIdmlDirPath.getText();
		String destFilePath = txtDestIdmlFilePath.getText();
		
		//The destination path is optional if a value was provided.
		if ((destDirPath != null) && (!destDirPath.equals("")))
		{
			//If the file path does not have a file separator, add one.
			String lastCharacter = "" + destDirPath.charAt(destDirPath.length() -1);
			destDirPath = (lastCharacter.equals(File.separator))? destDirPath : destDirPath + File.separator;
		}
		
		try {	
			//The destination file is not optional.
			if ((destFilePath == null) || (destFilePath.equals("")))
			{
				throw new IllegalArgumentException("The Destination IDML file path has not been set.");
			}
			
			String destIdmlPath = destDirPath + destFilePath;
			fReplaceImages.updatePackage(fLinks, destIdmlPath);
			
			String msg = String.format("Created IDML Package %s successfully!\n", destFilePath);
			JOptionPane.showMessageDialog(this, msg, "Replace Images", JOptionPane.INFORMATION_MESSAGE);				
		} 
		catch (Exception exc) 
		{
			String err = "Error Writing IDML Package to file:\n" + exc.getMessage();
			JOptionPane.showMessageDialog(this, err, "Replace Images Error", JOptionPane.ERROR_MESSAGE);	
		}
	}

	private void lstImagesValueChanged(ListSelectionEvent e) 
	{
		//Until this is false, there is no need to do anything.
		//It may get triggered multiple times for one click event.
		if (e.getValueIsAdjusting())
		{
			return;
		}
		
		//Setting label values to nothing.
		//If an Exception is thrown, no values will be displayed.
		lblImgSizeValue.setText("");
		lblImgSizeValue.setToolTipText("");
		lblImgLocationValue.setText("");
		lblImgLocationValue.setToolTipText("");
		
		try
		{	
			//Get selected image file.
			int selectedIndex = lstImages.getSelectedIndex();
			
			//If the select index is less than 0 set it to 0.
			selectedIndex = (selectedIndex < 0)? 0: selectedIndex;
			
			//Get the selected image file.
			String imgID = (String) lstImagesModel.get(selectedIndex); 
			String imgPath = fLinks.get(imgID);			
			File imgFile = FileUtils.getIdmlReferencedFile(imgPath);			
			
			//Update image size
			String imgSize = FileUtils.getFileSize(imgFile);
			lblImgSizeValue.setText(imgSize);
			lblImgSizeValue.setToolTipText(imgSize);
			
			//Update image location
			lblImgLocationValue.setText(imgPath);
			lblImgLocationValue.setToolTipText(imgPath);
			
			//Update image display
			ImageIcon icon = ImageUtils.getScaledImageIcon(lblImgDisplay.getWidth(), lblImgDisplay.getHeight(), imgFile);
			lblImgDisplay.setIcon(icon);				
		}
		catch (ArrayIndexOutOfBoundsException  exc)
		{
			//This error should not occur but it will not hurt this application if it is.
		}
		catch (PackageException exc) 
		{
			lblImgDisplay.setIcon(null);
			String err = exc.getMessage();
			JOptionPane.showMessageDialog(this, err, "Image Preview Not Available", JOptionPane.INFORMATION_MESSAGE);
		}
		catch (Exception exc)
		{
			lblImgDisplay.setIcon(null);
			String err = exc.getMessage();
			JOptionPane.showMessageDialog(this, err, "Replace Images Error", JOptionPane.ERROR_MESSAGE);
		}
	}

	private void init() 
	{
		btnSetPathOptions = new JButton();
		btnSourceIdmlPath = new JButton();
		btnReplaceImages = new JButton();
		btnDestIdmlPath = new JButton();
		btnWriteIdmlFile = new JButton();
		dialogPane = new JPanel();
		lblImgDisplay = new JLabel();		
		lblDestIdmlDirPath = new JLabel();
		lblDestIdmlFilePath = new JLabel();
		lblImgSize = new JLabel();
		lblImgSizeValue = new JLabel();
		lblImgLocation = new JLabel();
		lblImgLocationValue = new JLabel();
		lblSourceIdmlPath = new JLabel();
		lstImagesModel = new DefaultListModel();
		lstImages = new JList(lstImagesModel);		
		pnlReplaceImages = new JPanel();
		pnlFolderOptions = new JPanel();
		pnlImageDesc = new JPanel();
		spReplaceImages = new JSplitPane();
		scpImages = new JScrollPane();
		tabbedPane = new JTabbedPane();
		txtSourceIdmlPath = new JTextField();	
		txtDestIdmlDirPath = new JTextField();	
		txtDestIdmlFilePath = new JTextField();
		
		//Allows window events to be overridden.
		addWindowListener(this);
		
		//Dimension for the panels
		Dimension size = new Dimension(600, 450);
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		//dialogPane 
		dialogPane.setBorder(new EmptyBorder(10, 10, 10, 10));
		dialogPane.setLayout(new BorderLayout());		

		//pnlFolderOptions 
		pnlFolderOptions.setLayout(null);
		pnlFolderOptions.setPreferredSize(size);
		pnlFolderOptions.add(txtSourceIdmlPath);
		txtSourceIdmlPath.setBounds(25, 60, 455, txtSourceIdmlPath.getPreferredSize().height);

		//btnSourceIdmlPath 
		btnSourceIdmlPath.setText("...");
		btnSourceIdmlPath.addActionListener
		(
			new ActionListener() 
			{
				public void actionPerformed(ActionEvent e) 
				{
					btnSourceIdmlPathActionPerformed(e);
				}
			}
		);
		pnlFolderOptions.add(btnSourceIdmlPath);
		btnSourceIdmlPath.setBounds(490, 60, btnSourceIdmlPath.getPreferredSize().width, 20);
		
		//txtDestIdmlDirPath
		pnlFolderOptions.add(txtDestIdmlDirPath);
		txtDestIdmlDirPath.setBounds(25, 120, 455, txtDestIdmlDirPath.getPreferredSize().height);
		
		//txtDestIdmlFilePath
		pnlFolderOptions.add(txtDestIdmlFilePath);
		txtDestIdmlFilePath.setBounds(25, 180, 455, txtDestIdmlFilePath.getPreferredSize().height);

		//btnDestIdmlPath 
		btnDestIdmlPath.setText("...");
		btnDestIdmlPath.addActionListener
		(
			new ActionListener() 
			{
				public void actionPerformed(ActionEvent e) 
				{
					btnDestIdmlPathActionPerformed(e);
				}
			}
		);
		pnlFolderOptions.add(btnDestIdmlPath);
		btnDestIdmlPath.setBounds(490, 120, btnDestIdmlPath.getPreferredSize().width, 20);

		//lblSourceIdmlPath 
		lblSourceIdmlPath.setText("Source IDML Package ");
		pnlFolderOptions.add(lblSourceIdmlPath);
		lblSourceIdmlPath.setBounds(25, 35, 205, 25);

		//lblDestIdmlDirPath 
		lblDestIdmlDirPath.setText("Destination IDML Package Directory (Optional)");
		pnlFolderOptions.add(lblDestIdmlDirPath);
		lblDestIdmlDirPath.setBounds(25, 90, 350, 25);
		
		//lblDestIdmlFilePath 
		lblDestIdmlFilePath.setText("Destination IDML Package File ");
		pnlFolderOptions.add(lblDestIdmlFilePath);
		lblDestIdmlFilePath.setBounds(25, 155, 250, 25);

		//btnSetPathOptions 
		btnSetPathOptions.setText("Set Options");
		btnSetPathOptions.addActionListener
		(
			new ActionListener() 
			{
				public void actionPerformed(ActionEvent e) 
				{
					btnSetPathOptionsActionPerformed(e);
				}
			}
		);
		
		pnlFolderOptions.add(btnSetPathOptions);
		btnSetPathOptions.setBounds(425, 230, 115, btnSetPathOptions.getPreferredSize().height);					
		tabbedPane.addTab("Folder Options", pnlFolderOptions);

		//pnlReplaceImages 	
		pnlReplaceImages.setLayout(null);
		pnlReplaceImages.setPreferredSize(size);

		//spReplaceImages 
		spReplaceImages.setContinuousLayout(true);
		spReplaceImages.setEnabled(false);
		spReplaceImages.setDividerLocation(280);

		//lstImages 
		lstImages.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		lstImages.addListSelectionListener
		(
			new ListSelectionListener() 
			{
				public void valueChanged(ListSelectionEvent e) 
				{
					lstImagesValueChanged(e);
				}
			}
		);
		scpImages.setViewportView(lstImages);
		spReplaceImages.setLeftComponent(scpImages);

		//pnlImageDesc 
		pnlImageDesc.setLayout(null);

		//lblImgSize 
		lblImgSize.setText("Image Size:");
		pnlImageDesc.add(lblImgSize);
		lblImgSize.setBounds(10, 250, 145, 20);

		//lblImgSizeValue 
		lblImgSizeValue.setText("");
		lblImgSizeValue.setToolTipText(lblImgSizeValue.getText());
		pnlImageDesc.add(lblImgSizeValue);
		lblImgSizeValue.setBounds(120, 250, 145, 20);

		//lblImgLocation 
		lblImgLocation.setText("Image Location:");
		pnlImageDesc.add(lblImgLocation);
		lblImgLocation.setBounds(10, 280, 145, 20);

		//lblImgLocationValue 
		lblImgLocationValue.setText("");
		lblImgLocationValue.setToolTipText(lblImgLocationValue.getText());
		pnlImageDesc.add(lblImgLocationValue);
		lblImgLocationValue.setBounds(120, 280, 165, 20);

		//btnReplaceImages 
		btnReplaceImages.setText("Replace Image");
		btnReplaceImages.addActionListener
		(
			new ActionListener() 
			{
				public void actionPerformed(ActionEvent e) 
				{
					btnReplaceImagesActionPerformed(e);
				}
			}
		);
		pnlImageDesc.add(btnReplaceImages);
		btnReplaceImages.setBounds(10, 315, 135, btnReplaceImages.getPreferredSize().height);

		//lblImgDisplay 
		lblImgDisplay.setBackground(Color.white);
		pnlImageDesc.add(lblImgDisplay);
		lblImgDisplay.setBounds(10, 5, 245, 240);
		
		//spReplaceImages
		spReplaceImages.setRightComponent(pnlImageDesc);
		pnlReplaceImages.add(spReplaceImages);
		spReplaceImages.setBounds(5, 5, 560, 360);

		//btnWriteIdmlFile
		btnWriteIdmlFile.setText("Write To IDML Package");
		btnWriteIdmlFile.addActionListener
		(
			new ActionListener() 
			{
				public void actionPerformed(ActionEvent e) 
				{
					btnWriteIdmlFileActionPerformed(e);
				}
			}
		);
		pnlReplaceImages.add(btnWriteIdmlFile);
		btnWriteIdmlFile.setBounds(400, 375, btnWriteIdmlFile.getPreferredSize().width, btnWriteIdmlFile.getPreferredSize().height);
		tabbedPane.addTab("Replace Images", pnlReplaceImages);		
		dialogPane.add(tabbedPane, BorderLayout.CENTER);
		contentPane.add(dialogPane, BorderLayout.CENTER);
		pack();
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowActivated(java.awt.event.WindowEvent)
	 */
	public void windowActivated(WindowEvent e) {
		//No operation.			
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowClosed(java.awt.event.WindowEvent)
	 */
	public void windowClosed(WindowEvent e) {
		//No operation.		
	}

	/**
	 * Cleans the temporary directory on the closing event.
	 * @see java.awt.event.WindowListener#windowClosing(java.awt.event.WindowEvent)
	 */
	public void windowClosing(WindowEvent e) {
		fReplaceImages.cleanup();
		System.exit(0);			
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowDeactivated(java.awt.event.WindowEvent)
	 */
	public void windowDeactivated(WindowEvent e) {
		//No operation.				
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowDeiconified(java.awt.event.WindowEvent)
	 */
	public void windowDeiconified(WindowEvent e) {
		//No operation.				
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowIconified(java.awt.event.WindowEvent)
	 */
	public void windowIconified(WindowEvent e) {
		//No operation.			
	}

	/**
	 * (non-Javadoc)
	 * @see java.awt.event.WindowListener#windowOpened(java.awt.event.WindowEvent)
	 */
	public void windowOpened(WindowEvent e) {
		//No operation.				
	}	
}