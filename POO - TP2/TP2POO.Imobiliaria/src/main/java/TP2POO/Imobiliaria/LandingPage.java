package TP2POO.Imobiliaria;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.io.File;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;
import java.awt.Rectangle;

public class LandingPage extends JPanel {
	
	AplicacaoController controller = null;
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final Action alterarArquivo = new alterarArquivo();	
	private final Action continuaPrograma = new SwingAction();
	private JLabel selectedFile;
	
	/**
	 * Create the panel.
	 */
	public LandingPage(AplicacaoController c) {
		setBounds(new Rectangle(0, 0, 1280, 720));
		controller = c;
		
		setBackground(Color.WHITE);
		setLayout(null);
		
		JLabel lblNewLabel = new JLabel("Imobiliária");
		lblNewLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		lblNewLabel.setFont(new Font("Segoe UI Historic", Font.PLAIN, 56));
		lblNewLabel.setBounds(180, 140, 280, 80);
		add(lblNewLabel);
		
		JPanel panel = new JPanel();
		panel.setBorder(null);
		FlowLayout flowLayout_1 = (FlowLayout) panel.getLayout();
		flowLayout_1.setVgap(1);
		flowLayout_1.setHgap(1);
		panel.setBackground(Color.BLACK);
		panel.setBounds(180, 220, 265, 5);
		add(panel);
		
		JLabel lblNewLabel_1 = new JLabel("Arquivo");
		lblNewLabel_1.setFont(new Font("Trebuchet MS", Font.PLAIN, 24));
		lblNewLabel_1.setBounds(180, 460, 100, 40);
		add(lblNewLabel_1);
		
		JButton buttonContinuar = new JButton("Continuar");
		buttonContinuar.setAction(continuaPrograma);
		buttonContinuar.setFocusPainted(false);
		buttonContinuar.setFocusable(false);
		buttonContinuar.setBackground(Color.BLACK);
		buttonContinuar.setBorder(null);
		buttonContinuar.setAutoscrolls(true);
		buttonContinuar.setFont(new Font("Verdana", Font.BOLD, 12));
		buttonContinuar.setForeground(Color.WHITE);
		buttonContinuar.setBounds(180, 550, 130, 40);
		add(buttonContinuar);
		
		JPanel buttonArquivo = new JPanel();
		buttonArquivo.setBorder(new LineBorder(new Color(0, 0, 0), 3));
		buttonArquivo.setBounds(330, 550, 130, 40);
		add(buttonArquivo);
		buttonArquivo.setLayout(new BorderLayout(0, 0));
		
		JButton btnAlterarArquivo = new JButton("Alterar arquivo");
		btnAlterarArquivo.setAction(alterarArquivo);
		btnAlterarArquivo.setFocusPainted(false);
		btnAlterarArquivo.setFocusable(false);
		btnAlterarArquivo.setBorder(null);
		btnAlterarArquivo.setForeground(Color.BLACK);
		btnAlterarArquivo.setFont(new Font("Verdana", Font.BOLD, 12));
		btnAlterarArquivo.setBackground(Color.WHITE);
		btnAlterarArquivo.setAutoscrolls(true);
		buttonArquivo.add(btnAlterarArquivo);
		
		JPanel fileArquivoText = new JPanel();
		fileArquivoText.setBackground(Color.WHITE);
		FlowLayout fl_fileArquivoText = (FlowLayout) fileArquivoText.getLayout();
		fl_fileArquivoText.setHgap(10);
		fl_fileArquivoText.setAlignment(FlowLayout.LEFT);
		fileArquivoText.setBorder(new LineBorder(new Color(0, 0, 0), 3));
		fileArquivoText.setBounds(180, 497, 280, 42);
		add(fileArquivoText);
		
		selectedFile = new JLabel("database_imoveis.txt");
		selectedFile.setHorizontalTextPosition(SwingConstants.LEFT);
		selectedFile.setForeground(Color.GRAY);
		selectedFile.setFont(new Font("Verdana", Font.PLAIN, 20));
		selectedFile.setBorder(null);
		fileArquivoText.add(selectedFile);
		
		JLabel logoImg_1 = new JLabel("");
		logoImg_1.setIcon(new ImageIcon("C:\\Users\\jeron\\Downloads\\imgLanding.png"));
		logoImg_1.setBounds(0, -32, 1264, 713);
		add(logoImg_1);
	}
	

	private class alterarArquivo extends AbstractAction {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		public alterarArquivo() {
			putValue(NAME, "Alterar arquivo");
			
		}
		public void actionPerformed(ActionEvent e) {
			JFileChooser fileChooser = new JFileChooser();
			
			fileChooser.setCurrentDirectory(new File("."));
			fileChooser.setBounds(50, 50, 0, 0);
			int response = fileChooser.showOpenDialog(null);
			
			if(response == JFileChooser.APPROVE_OPTION) {
				File file = new File(fileChooser.getSelectedFile().getAbsolutePath());
				
				selectedFile.setText(file.getName());
			}
		}
	}
	private class SwingAction extends AbstractAction {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		public SwingAction() {
			putValue(NAME, "Continuar");
		}
		public void actionPerformed(ActionEvent e) {
			controller.showMain();
		}
	}

}
