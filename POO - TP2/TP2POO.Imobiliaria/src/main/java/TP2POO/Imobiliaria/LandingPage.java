package TP2POO.Imobiliaria;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.IOException;

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

	private AplicacaoController controller = null;

	private static final long serialVersionUID = 1L;
	private final Action alterarArquivo = new alterarArquivo();
	private final Action continuaPrograma = new SwingAction();
	private JLabel selectedFile;

	private Font rationaleFont = null;

	public LandingPage(AplicacaoController c) {
		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			rationaleFont = new Font("Microsoft Yi Baiti", Font.PLAIN, 8);
		}

		setBounds(new Rectangle(0, 0, 1280, 720));
		controller = c;

		setBackground(Color.WHITE);
		setLayout(null);

		JLabel logoText = new JLabel("Imobiliária");
		logoText.setAlignmentX(Component.CENTER_ALIGNMENT);
		logoText.setFont(rationaleFont.deriveFont(72f));
		logoText.setBounds(180, 140, 280, 80);
		add(logoText);

		JPanel rectangleDetail = new JPanel();
		rectangleDetail.setBorder(null);
		FlowLayout fl_rectangleDetail = (FlowLayout) rectangleDetail.getLayout();
		fl_rectangleDetail.setVgap(1);
		fl_rectangleDetail.setHgap(1);
		rectangleDetail.setBackground(Color.BLACK);
		rectangleDetail.setBounds(176, 220, 280, 5);
		add(rectangleDetail);

		JLabel arquivoText = new JLabel("Arquivo");
		arquivoText.setFont(rationaleFont.deriveFont(36f));
		arquivoText.setBounds(180, 460, 280, 40);
		add(arquivoText);

		JButton buttonContinuar = new JButton("Continuar");
		buttonContinuar.setAction(continuaPrograma);
		buttonContinuar.setFocusPainted(false);
		buttonContinuar.setFocusable(false);
		buttonContinuar.setBackground(Color.BLACK);
		buttonContinuar.setBorder(null);
		buttonContinuar.setAutoscrolls(true);
		buttonContinuar.setFont(rationaleFont.deriveFont(18f));
		buttonContinuar.setForeground(Color.WHITE);
		buttonContinuar.setBounds(180, 550, 130, 40);
		add(buttonContinuar);

		JPanel buttonPanel = new JPanel();
		buttonPanel.setBorder(new LineBorder(new Color(0, 0, 0), 3));
		buttonPanel.setBounds(330, 550, 130, 40);
		add(buttonPanel);
		buttonPanel.setLayout(new BorderLayout(0, 0));

		JButton buttonArquivo = new JButton("Alterar arquivo");
		buttonArquivo.setAction(alterarArquivo);
		buttonArquivo.setFocusPainted(false);
		buttonArquivo.setFocusable(false);
		buttonArquivo.setBorder(null);
		buttonArquivo.setForeground(Color.BLACK);
		buttonArquivo.setFont(rationaleFont.deriveFont(18f));
		buttonArquivo.setBackground(Color.WHITE);
		buttonArquivo.setAutoscrolls(true);
		buttonPanel.add(buttonArquivo);

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
		selectedFile.setFont(rationaleFont.deriveFont(24f));
		selectedFile.setBorder(null);
		fileArquivoText.add(selectedFile);

		JLabel background = new JLabel("");
		background.setIcon(new ImageIcon(LandingPage.class.getResource("/images/imgLanding.png")));
		background.setBounds(0, -32, 1264, 713);
		add(background);
	}

	private class alterarArquivo extends AbstractAction {
		
		private static final long serialVersionUID = 1L;

		public alterarArquivo() {
			putValue(NAME, "Alterar arquivo");

		}

		public void actionPerformed(ActionEvent e) {
			JFileChooser fileChooser = new JFileChooser();

			fileChooser.setCurrentDirectory(new File("."));
			fileChooser.setBounds(50, 50, 0, 0);
			int response = fileChooser.showOpenDialog(null);

			if (response == JFileChooser.APPROVE_OPTION) {
				File file = new File(fileChooser.getSelectedFile().getAbsolutePath());

				selectedFile.setText(file.getName());
				controller.setArquivoSelecionado(file);
			}
		}
	}

	private class SwingAction extends AbstractAction {
		
		private static final long serialVersionUID = 1L;

		public SwingAction() {
			putValue(NAME, "Continuar");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showMain();
		}
	}

}
