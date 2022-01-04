package TP2POO.Imobiliaria;

// Imports
import javax.swing.JPanel;
import java.awt.Rectangle;
import java.io.File;
import java.io.IOException;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;

import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.SwingConstants;

import TP2POO.Imobiliaria.AplicacaoController.TiposPesquisa;

import javax.swing.AbstractAction;
import java.awt.event.ActionEvent;
import javax.swing.Action;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import java.awt.Cursor;
import javax.swing.border.CompoundBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextPane;

// Classe de página de pesquisa, JPanel
public class SearchPage extends JPanel {
	// Instancia  do controlador, criando encapsulamento
	private AplicacaoController controller = null;
	
	// Variáveis
	
	private static final long serialVersionUID = 1L;
	private JLabel pesquisaTitle;
	private JTextPane resultadoPesquisa;
	private JTextField textPesquisa;
	private TiposPesquisa tipoPesquisa;
	
	// Ações dos botões
	private final Action voltar = new SwingAction();
	private final Action executaPesquisa = new SwingAction_1();
	private final Action action = new SwingAction_2();
	private final Action action_1 = new SwingAction_3();
	
	// Fonte customizada
	private Font rationaleFont = null;

	// Construtor da página/classe
	public SearchPage(AplicacaoController c) {
		// Insere o controlador na classe
		controller = c;

		// Tenta recuperar a fonte customizada, caso não funcione, setta fonte como um padrão
		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			rationaleFont = new Font("Microsoft Yi Baiti", Font.PLAIN, 8);
		}

		// Configs do JPanel
		setBounds(new Rectangle(0, 0, 1280, 720));
		setBackground(Color.WHITE);
		setLayout(null);

		// Cria componentes da página
		JButton buttonVoltar = new JButton("< Voltar");
		buttonVoltar.setFont(rationaleFont.deriveFont(24f));
		buttonVoltar.setAction(voltar);
		buttonVoltar.setHorizontalTextPosition(SwingConstants.LEFT);
		buttonVoltar.setHorizontalAlignment(SwingConstants.LEFT);
		buttonVoltar.setBorderPainted(false);
		buttonVoltar.setBorder(null);
		buttonVoltar.setBackground(Color.WHITE);
		buttonVoltar.setBounds(15, 0, 150, 40);
		add(buttonVoltar);

		pesquisaTitle = new JLabel("Pesquisa");
		pesquisaTitle.setHorizontalAlignment(SwingConstants.LEFT);
		pesquisaTitle.setBounds(15, 70, 500, 50);
		pesquisaTitle.setFont(rationaleFont.deriveFont(45f));
		add(pesquisaTitle);
		
		resultadoPesquisa = new JTextPane();
		resultadoPesquisa.setFont(new Font("Tahoma", Font.PLAIN, 18));
		resultadoPesquisa.setEditable(false);
		resultadoPesquisa.setBorder(new EmptyBorder(15, 15, 15, 15));
		resultadoPesquisa.setBounds(15, 200, 450, 450);
				
		JScrollPane panelScroll = new JScrollPane(resultadoPesquisa);
		panelScroll.setBorder(new LineBorder(new Color(0, 0, 0), 3));
		panelScroll.setBounds(15, 200, 450, 400);
		add(panelScroll);
		
		textPesquisa = new JTextField();
		textPesquisa.setFont(new Font("Tahoma", Font.PLAIN, 18));
		textPesquisa.setBounds(15, 140, 400, 40);
		textPesquisa.setBorder(new CompoundBorder(new LineBorder(new Color(0, 0, 0), 3), new EmptyBorder(0, 15, 0, 0)));
		textPesquisa.setColumns(10);
		add(textPesquisa);
		
		JButton buttonIconPesquisa = new JButton("");
		buttonIconPesquisa.setAction(executaPesquisa);
		buttonIconPesquisa.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonIconPesquisa.setIcon(new ImageIcon(SearchPage.class.getResource("/images/iconSearch.png")));
		buttonIconPesquisa.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonIconPesquisa.setBackground(Color.WHITE);
		buttonIconPesquisa.setBorderPainted(false);
		buttonIconPesquisa.setBorder(null);
		buttonIconPesquisa.setBounds(425, 140, 40, 40);
		add(buttonIconPesquisa);
		
		JButton buttonSalvar = new JButton("Printar no terminal");
		buttonSalvar.setFocusable(false);
		buttonSalvar.setFocusTraversalKeysEnabled(false);
		buttonSalvar.setFocusPainted(false);
		buttonSalvar.setForeground(Color.WHITE);
		buttonSalvar.setBackground(Color.BLACK);
		buttonSalvar.setFont(rationaleFont.deriveFont(18f));
		buttonSalvar.setBorder(null);
		buttonSalvar.setAction(action);
		buttonSalvar.setBounds(265, 611, 200, 30);
		add(buttonSalvar);
		
		JButton buttonPrint = new JButton("Salvar em um arquivo");
		buttonPrint.setFocusable(false);
		buttonPrint.setFocusTraversalKeysEnabled(false);
		buttonPrint.setFocusPainted(false);
		buttonPrint.setForeground(Color.WHITE);
		buttonPrint.setBackground(Color.BLACK);
		buttonPrint.setFont(rationaleFont.deriveFont(18f));
		buttonPrint.setBorder(null);
		buttonPrint.setAction(action_1);
		buttonPrint.setBounds(15, 611, 200, 30);
		add(buttonPrint);

		JLabel background = new JLabel("");
		background.setBounds(-10, -37, 1280, 720);
		background.setIcon(new ImageIcon(SearchPage.class.getResource("/images/imgSearch.png")));
		add(background);

	}
	
	// Getters
	public TiposPesquisa getTipoPesquisa() {
		return tipoPesquisa;
	}
	
	// Setters
	public void setTipoPesquisa(TiposPesquisa tipo) {
		tipoPesquisa = tipo;
		changeTitle(tipoPesquisa);
	}
	
	// Altera o título da página de acordo com o tipo de pesquisa selecionado
	public void changeTitle(TiposPesquisa tipo) {
		if (tipo == TiposPesquisa.Cidade) {
			pesquisaTitle.setText("Por Cidade");
		} else if (tipo == TiposPesquisa.NumQuartos) {
			pesquisaTitle.setText("Por Número Quartos");
		} else if (tipo == TiposPesquisa.Proprietario) {
			pesquisaTitle.setText("Por Proprietário");
		} else if (tipo == TiposPesquisa.Tipo) {
			pesquisaTitle.setText("Por Tipo");
		} else if (tipo == TiposPesquisa.Valor) {
			pesquisaTitle.setText("Por Valor");
		} else {
			pesquisaTitle.setText("Pesquisa");
		}
	}
	
	// Altera o campo de resultado da pesquisa
	public void changeTextPane(String str) {
		resultadoPesquisa.setText(str);
	}
	
	// Limpa o campo de pesquisa
	public void resetTextField() {
		textPesquisa.setText("");
	}
	
	// Limpa o campo de resultado da pesquisa
	public void resetTextPane() {
		resultadoPesquisa.setText("");
	}

	// Retorna a aplicação para a página princiapal
	private class SwingAction extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public SwingAction() {
			putValue(NAME, "< Voltar");
		}

		public void actionPerformed(ActionEvent e) {
			controller.returnToMain();
		}
	}
	
	// Recupera a resposta do usuário no campo de pesquisa
	// e inicia a pesquisa de acordo com o tipo de pesquisa
	private class SwingAction_1 extends AbstractAction {
		
		private static final long serialVersionUID = 1L;
		
		public SwingAction_1() {
			putValue(NAME, "");
		}
		public void actionPerformed(ActionEvent e) {	
			controller.realizarPesquisa(tipoPesquisa, textPesquisa.getText());
		}
	}

	// Salva a string de pesquisa realizada em um arquivo
	private class SwingAction_2 extends AbstractAction {
		
		private static final long serialVersionUID = 1L;
		
		public SwingAction_2() {
			putValue(NAME, "Salvar em um arquivo");
		}
		public void actionPerformed(ActionEvent e) {
			controller.salvaPesquisa();
			
		}
	}

	// Printa a string de pesquisa realizada no terminal
	private class SwingAction_3 extends AbstractAction {
		
		private static final long serialVersionUID = 1L;
		
		public SwingAction_3() {
			putValue(NAME, "Printar no terminal");
		}
		public void actionPerformed(ActionEvent e) {
			controller.printPesquisa();
		}
	}
}
