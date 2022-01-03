package TP2POO.Imobiliaria;

import javax.swing.JPanel;
import java.awt.Rectangle;
import java.awt.Color;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;

import javax.swing.JButton;
import java.awt.Component;
import java.awt.Cursor;
import javax.swing.AbstractAction;
import java.awt.event.ActionEvent;
import javax.swing.Action;
import java.io.File;
import java.io.IOException;

import javax.swing.SwingConstants;

import TP2POO.Imobiliaria.AplicacaoController.TiposPesquisa;

import java.awt.BorderLayout;
import javax.swing.Box;
import java.awt.Dimension;
import java.awt.Insets;

public class MainPage extends JPanel {

	private static final long serialVersionUID = 1L;

	private AplicacaoController controller = null;
	private final Action voltarLandingPage = new SwingAction();

	private Font rationaleFont = null;
	private final Action pesquisaValor = new SwingAction_1();
	private final Action pesquisaProprietario = new SwingAction_2();
	private final Action pesquisaTipo = new SwingAction_3();
	private final Action pesquisaCidade = new SwingAction_4();
	private final Action pesquisaNumQuartos = new SwingAction_5();

	public MainPage(AplicacaoController c) {
		controller = c;

		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException | FontFormatException e) {
			rationaleFont = new Font("Microsoft Yi Baiti", Font.PLAIN, 8);
		}

		setBounds(new Rectangle(0, 0, 1280, 720));
		setBackground(Color.WHITE);
		setLayout(null);

		JPanel panelValor = new JPanel();
		panelValor.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
		panelValor.setBackground(Color.WHITE);
		panelValor.setBounds(240, 160, 160, 160);
		add(panelValor);
		panelValor.setLayout(new BorderLayout(0, 0));

		Component verticalStrut = Box.createVerticalStrut(20);
		verticalStrut.setPreferredSize(new Dimension(0, 40));
		panelValor.add(verticalStrut, BorderLayout.NORTH);

		JButton buttonValor = new JButton("Por Valor");
		buttonValor.setFont(rationaleFont.deriveFont(18f));
		buttonValor.setFocusable(false);
		buttonValor.setFocusTraversalKeysEnabled(false);
		buttonValor.setFocusPainted(false);
		buttonValor.setAction(pesquisaValor);
		buttonValor.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonValor.setBackground(Color.WHITE);
		buttonValor.setVerticalTextPosition(SwingConstants.BOTTOM);
		buttonValor.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonValor.setIcon(new ImageIcon(MainPage.class.getResource("/images/moneyIcon.png")));
		buttonValor.setMargin(new Insets(0, 0, 0, 0));
		buttonValor.setBorder(null);
		panelValor.add(buttonValor, BorderLayout.CENTER);

		JPanel panelProprietario = new JPanel();
		panelProprietario.setBackground(Color.WHITE);
		panelProprietario.setBounds(400, 160, 160, 160);
		add(panelProprietario);
		panelProprietario.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1 = Box.createVerticalStrut(20);
		verticalStrut_1.setPreferredSize(new Dimension(0, 40));
		panelProprietario.add(verticalStrut_1, BorderLayout.NORTH);

		JButton buttonProprietario = new JButton("Por proprietário");
		buttonProprietario.setFocusable(false);
		buttonProprietario.setFont(rationaleFont.deriveFont(18f));
		buttonProprietario.setFocusTraversalKeysEnabled(false);
		buttonProprietario.setFocusPainted(false);
		buttonProprietario.setAction(pesquisaProprietario);
		buttonProprietario.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonProprietario.setBackground(Color.WHITE);
		buttonProprietario.setVerticalTextPosition(SwingConstants.BOTTOM);
		buttonProprietario.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonProprietario.setIcon(new ImageIcon(MainPage.class.getResource("/images/personIcon.png")));
		buttonProprietario.setMargin(new Insets(0, 0, 0, 0));
		buttonProprietario.setBorder(null);
		panelProprietario.add(buttonProprietario, BorderLayout.CENTER);

		JPanel panelTipo = new JPanel();
		panelTipo.setBackground(Color.WHITE);
		panelTipo.setBounds(560, 160, 160, 160);
		add(panelTipo);
		panelTipo.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_1 = Box.createVerticalStrut(20);
		verticalStrut_1_1.setPreferredSize(new Dimension(0, 40));
		panelTipo.add(verticalStrut_1_1, BorderLayout.NORTH);

		JButton buttonTipo = new JButton("Por Tipo");
		buttonTipo.setFont(rationaleFont.deriveFont(18f));
		buttonTipo.setFocusable(false);
		buttonTipo.setFocusTraversalKeysEnabled(false);
		buttonTipo.setFocusPainted(false);
		buttonTipo.setAction(pesquisaTipo);
		buttonTipo.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonTipo.setBackground(Color.WHITE);
		buttonTipo.setVerticalTextPosition(SwingConstants.BOTTOM);
		buttonTipo.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonTipo.setIcon(new ImageIcon(MainPage.class.getResource("/images/houseIcon.png")));
		buttonTipo.setMargin(new Insets(0, 0, 0, 0));
		buttonTipo.setBorder(null);
		panelTipo.add(buttonTipo, BorderLayout.CENTER);

		JPanel panelCidade = new JPanel();
		panelCidade.setBackground(Color.WHITE);
		panelCidade.setBounds(720, 160, 160, 160);
		add(panelCidade);
		panelCidade.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_2 = Box.createVerticalStrut(20);
		verticalStrut_1_2.setPreferredSize(new Dimension(0, 40));
		panelCidade.add(verticalStrut_1_2, BorderLayout.NORTH);

		JButton buttonCidade = new JButton("Por Cidade");
		buttonCidade.setFont(rationaleFont.deriveFont(18f));
		buttonCidade.setFocusable(false);
		buttonCidade.setFocusTraversalKeysEnabled(false);
		buttonCidade.setFocusPainted(false);
		buttonCidade.setAction(pesquisaCidade);
		buttonCidade.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonCidade.setBackground(Color.WHITE);
		buttonCidade.setVerticalTextPosition(SwingConstants.BOTTOM);
		buttonCidade.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonCidade.setIcon(new ImageIcon(MainPage.class.getResource("/images/locationIcon.png")));
		buttonCidade.setMargin(new Insets(0, 0, 0, 0));
		buttonCidade.setBorder(null);
		panelCidade.add(buttonCidade, BorderLayout.CENTER);

		JPanel panelNumQuartos = new JPanel();
		panelNumQuartos.setBackground(Color.WHITE);
		panelNumQuartos.setBounds(880, 160, 160, 160);
		add(panelNumQuartos);
		panelNumQuartos.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_3 = Box.createVerticalStrut(20);
		verticalStrut_1_3.setPreferredSize(new Dimension(0, 40));
		panelNumQuartos.add(verticalStrut_1_3, BorderLayout.NORTH);

		JButton buttonNumQuartos = new JButton("Por Número Quarto");
		buttonNumQuartos.setFont(rationaleFont.deriveFont(18f));
		buttonNumQuartos.setFocusable(false);
		buttonNumQuartos.setFocusTraversalKeysEnabled(false);
		buttonNumQuartos.setFocusPainted(false);
		buttonNumQuartos.setAction(pesquisaNumQuartos);
		buttonNumQuartos.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonNumQuartos.setBackground(Color.WHITE);
		buttonNumQuartos.setVerticalTextPosition(SwingConstants.BOTTOM);
		buttonNumQuartos.setHorizontalTextPosition(SwingConstants.CENTER);
		buttonNumQuartos.setIcon(new ImageIcon(MainPage.class.getResource("/images/bedIcon.png")));
		buttonNumQuartos.setMargin(new Insets(0, 0, 0, 0));
		buttonNumQuartos.setBorder(null);
		panelNumQuartos.add(buttonNumQuartos, BorderLayout.CENTER);

		JButton buttonVoltar = new JButton("< Escolher outro arquivo");
		buttonVoltar.setAction(voltarLandingPage);
		buttonVoltar.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		buttonVoltar.setFocusable(false);
		buttonVoltar.setFocusPainted(false);
		buttonVoltar.setFocusTraversalKeysEnabled(false);
		buttonVoltar.setOpaque(false);
		buttonVoltar.setBorder(null);
		buttonVoltar.setFont(rationaleFont.deriveFont(24f));
		buttonVoltar.setForeground(Color.WHITE);
		buttonVoltar.setAlignmentX(Component.CENTER_ALIGNMENT);
		buttonVoltar.setBackground(Color.WHITE);
		buttonVoltar.setBounds(0, 5, 237, 35);
		add(buttonVoltar);

		JLabel titlePesquisa = new JLabel("Pesquisa");
		titlePesquisa.setFont(rationaleFont.deriveFont(72f));
		titlePesquisa.setHorizontalAlignment(SwingConstants.CENTER);
		titlePesquisa.setBounds(0, 15, 1280, 64);
		add(titlePesquisa);

		JLabel background = new JLabel("");
		background.setIcon(new ImageIcon(MainPage.class.getResource("/images/imgMain.png")));
		background.setBounds(0, 0, 1264, 681);
		add(background);
	}

	private class SwingAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public SwingAction() {
			putValue(NAME, "< Escolher outro Arquivo");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showLanding();
		}
	}

	private class SwingAction_1 extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public SwingAction_1() {
			putValue(NAME, "Por Valor");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showSearchPageByType(TiposPesquisa.Valor);
		}
	}

	private class SwingAction_2 extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public SwingAction_2() {
			putValue(NAME, "Por Proprietário");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showSearchPageByType(TiposPesquisa.Proprietario);
		}
	}

	private class SwingAction_3 extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public SwingAction_3() {
			putValue(NAME, "Por Tipo");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showSearchPageByType(TiposPesquisa.Tipo);
		}
	}

	private class SwingAction_4 extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public SwingAction_4() {
			putValue(NAME, "Por Cidade");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showSearchPageByType(TiposPesquisa.Cidade);
		}
	}

	private class SwingAction_5 extends AbstractAction {
		private static final long serialVersionUID = 1L;

		public SwingAction_5() {
			putValue(NAME, "Por Número de Quartos");
		}

		public void actionPerformed(ActionEvent e) {
			controller.showSearchPageByType(TiposPesquisa.NumQuartos);
		}
	}
}
