package TP2POO.Imobiliaria;

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

public class SearchPage extends JPanel {
	private static final long serialVersionUID = 1L;

	AplicacaoController controller = null;
	Font rationaleFont = null;
	private final Action action = new SwingAction();

	private JLabel pesquisaTitle;
	private JTextPane textPane;
	private JTextField textField;
	private final Action action_1 = new SwingAction_1();
	
	private TiposPesquisa tipoPesquisa;

	public SearchPage(AplicacaoController c) {
		controller = c;

		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			System.out.println("Não foi possivel carregar fonte - " + e.getMessage());
		}

		setBounds(new Rectangle(0, 0, 1280, 720));
		setBackground(Color.WHITE);
		setLayout(null);

		JButton btnNewButton = new JButton("< Voltar");
		btnNewButton.setFont(rationaleFont.deriveFont(24f));
		btnNewButton.setAction(action);
		btnNewButton.setHorizontalTextPosition(SwingConstants.LEFT);
		btnNewButton.setHorizontalAlignment(SwingConstants.LEFT);
		btnNewButton.setBorderPainted(false);
		btnNewButton.setBorder(null);
		btnNewButton.setBackground(Color.WHITE);
		btnNewButton.setBounds(15, 0, 150, 40);
		add(btnNewButton);

		pesquisaTitle = new JLabel("Pesquisa");
		pesquisaTitle.setHorizontalAlignment(SwingConstants.LEFT);
		pesquisaTitle.setBounds(15, 70, 500, 50);
		pesquisaTitle.setFont(rationaleFont.deriveFont(45f));
		add(pesquisaTitle);
		
		textPane = new JTextPane();
		textPane.setEditable(false);
		textPane.setBorder(new CompoundBorder(new LineBorder(new Color(0, 0, 0), 3), new EmptyBorder(15, 15, 15, 15)));
		textPane.setBounds(15, 200, 450, 450);
				
		JScrollPane scrollPane = new JScrollPane(textPane);
		scrollPane.setBounds(15, 200, 450, 450);
		add(scrollPane);
		
		textField = new JTextField();
		textField.setBorder(new CompoundBorder(new LineBorder(new Color(0, 0, 0), 3), new EmptyBorder(0, 15, 0, 0)));
		textField.setBounds(15, 140, 400, 40);
		textField.setColumns(10);
		add(textField);
		
		JButton btnNewButton_1 = new JButton("");
		btnNewButton_1.setAction(action_1);
		btnNewButton_1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1.setIcon(new ImageIcon(SearchPage.class.getResource("/images/iconSearch.png")));
		btnNewButton_1.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1.setBackground(Color.WHITE);
		btnNewButton_1.setBorderPainted(false);
		btnNewButton_1.setBorder(null);
		btnNewButton_1.setBounds(425, 140, 40, 40);
		add(btnNewButton_1);

		JLabel lblNewLabel = new JLabel("");
		lblNewLabel.setBounds(-10, -37, 1280, 720);
		lblNewLabel.setIcon(new ImageIcon(SearchPage.class.getResource("/images/imgSearch.png")));
		add(lblNewLabel);

	}
	
	public TiposPesquisa getTipoPesquisa() {
		return tipoPesquisa;
	}
	
	public void setTipoPesquisa(TiposPesquisa tipo) {
		tipoPesquisa = tipo;
		changeTitle(tipoPesquisa);
	}
	
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
	
	public void changeTextPane(String str) {
		textPane.setText(str);
	}
	
	public void resetTextField() {
		textField.setText("");
	}
	
	public void resetTextPane() {
		textPane.setText("");
	}

	private class SwingAction extends AbstractAction {
		
		private static final long serialVersionUID = 1L;

		public SwingAction() {
			putValue(NAME, "< Voltar");
		}

		public void actionPerformed(ActionEvent e) {
			controller.returnToMain();
		}
	}
	private class SwingAction_1 extends AbstractAction {
		
		private static final long serialVersionUID = 1L;
		
		public SwingAction_1() {
			putValue(NAME, "");
		}
		public void actionPerformed(ActionEvent e) {	
			controller.realizarPesquisa(tipoPesquisa, textField.getText());
		}
	}
}
