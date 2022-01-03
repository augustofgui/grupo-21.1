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

	AplicacaoController controller = null;

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final Action alterarArquivo = new alterarArquivo();
	private final Action continuaPrograma = new SwingAction();
	private JLabel selectedFile;

	Font rationaleFont = null;

	/**
	 * Create the panel.
	 */
	public LandingPage(AplicacaoController c) {
		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			System.out.println("Não foi possivel carregar fonte - " + e.getMessage());
		}

		setBounds(new Rectangle(0, 0, 1280, 720));
		controller = c;

		setBackground(Color.WHITE);
		setLayout(null);

		JLabel lblNewLabel = new JLabel("Imobiliária");
		lblNewLabel.setAlignmentX(Component.CENTER_ALIGNMENT);
		lblNewLabel.setFont(rationaleFont.deriveFont(72f));
		lblNewLabel.setBounds(180, 140, 280, 80);
		add(lblNewLabel);

		JPanel panel = new JPanel();
		panel.setBorder(null);
		FlowLayout flowLayout_1 = (FlowLayout) panel.getLayout();
		flowLayout_1.setVgap(1);
		flowLayout_1.setHgap(1);
		panel.setBackground(Color.BLACK);
		panel.setBounds(176, 220, 280, 5);
		add(panel);

		JLabel lblNewLabel_1 = new JLabel("Arquivo");
		lblNewLabel_1.setFont(rationaleFont.deriveFont(36f));
		lblNewLabel_1.setBounds(180, 460, 280, 40);
		add(lblNewLabel_1);

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
		btnAlterarArquivo.setFont(rationaleFont.deriveFont(18f));
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
		selectedFile.setFont(rationaleFont.deriveFont(24f));
		selectedFile.setBorder(null);
		fileArquivoText.add(selectedFile);

		JLabel background = new JLabel("");
		background.setIcon(new ImageIcon(LandingPage.class.getResource("/images/imgLanding.png")));
		background.setBounds(0, -32, 1264, 713);
		add(background);
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

			if (response == JFileChooser.APPROVE_OPTION) {
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
