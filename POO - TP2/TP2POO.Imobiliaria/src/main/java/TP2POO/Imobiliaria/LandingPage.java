package TP2POO.Imobiliaria;

// Imports
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

// Classe de página incial, JPanel
public class LandingPage extends JPanel {

	// Instancia  do controlador, criando encapsulamento
	private AplicacaoController controller = null;

	// Variáveis
	private JLabel selectedFile;
	private static final long serialVersionUID = 1L;
	
	// Ações dos botões
	private final Action alterarArquivo = new alterarArquivo();
	private final Action continuaPrograma = new SwingAction();
	
	// Fonte customizada
	private Font rationaleFont = null;

	// Construtor da página/classe
	public LandingPage(AplicacaoController c) {
		
		// Tenta recuperar a fonte customizada, caso não funcione, setta fonte como um padrão
		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			rationaleFont = new Font("Microsoft Yi Baiti", Font.PLAIN, 8);
		}

		// Define tamanho do panel
		setBounds(new Rectangle(0, 0, 1280, 720));

		// Insere o controlador na classe
		controller = c;

		// Configs do JPanel
		setBackground(Color.WHITE);
		setLayout(null);

		// Cria componentes da página
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

	// Recupera e altera o arquivo selecionado peo usuário
	private class alterarArquivo extends AbstractAction {
		
		private static final long serialVersionUID = 1L;

		public alterarArquivo() {
			putValue(NAME, "Alterar arquivo");

		}

		public void actionPerformed(ActionEvent e) {
			// Exibe a tela de escolha de arquivo
			JFileChooser fileChooser = new JFileChooser();

			fileChooser.setCurrentDirectory(new File("."));
			fileChooser.setBounds(50, 50, 0, 0);
			int response = fileChooser.showOpenDialog(null);

			// Caso o arquivo seja alterado
			if (response == JFileChooser.APPROVE_OPTION) {
				File file = new File(fileChooser.getSelectedFile().getAbsolutePath());

				// altera a variável de File do controlador
				// e o nome do arquivo escrito na tela
				selectedFile.setText(file.getName());
				controller.setArquivoSelecionado(file);
			}
		}
	}

	// Continua a aplicação e passa para a próxima tela
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
