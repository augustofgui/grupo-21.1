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

	AplicacaoController controller = null;
	private final Action voltarLandingPage = new SwingAction();

	Font rationaleFont = null;
	private final Action action = new SwingAction_1();
	private final Action action_1 = new SwingAction_2();
	private final Action action_2 = new SwingAction_3();
	private final Action action_3 = new SwingAction_4();
	private final Action action_4 = new SwingAction_5();

	public MainPage(AplicacaoController c) {
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

		JPanel panel = new JPanel();
		panel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
		panel.setBackground(Color.WHITE);
		panel.setBounds(240, 160, 160, 160);
		add(panel);
		panel.setLayout(new BorderLayout(0, 0));

		Component verticalStrut = Box.createVerticalStrut(20);
		verticalStrut.setPreferredSize(new Dimension(0, 40));
		panel.add(verticalStrut, BorderLayout.NORTH);

		JButton btnNewButton_1 = new JButton("Por Valor");
		btnNewButton_1.setFont(rationaleFont.deriveFont(18f));
		btnNewButton_1.setFocusable(false);
		btnNewButton_1.setFocusTraversalKeysEnabled(false);
		btnNewButton_1.setFocusPainted(false);
		btnNewButton_1.setAction(action);
		btnNewButton_1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1.setBackground(Color.WHITE);
		btnNewButton_1.setVerticalTextPosition(SwingConstants.BOTTOM);
		btnNewButton_1.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1.setIcon(new ImageIcon(MainPage.class.getResource("/images/moneyIcon.png")));
		btnNewButton_1.setMargin(new Insets(0, 0, 0, 0));
		btnNewButton_1.setBorder(null);
		panel.add(btnNewButton_1, BorderLayout.CENTER);

		JPanel panel_1 = new JPanel();
		panel_1.setBackground(Color.WHITE);
		panel_1.setBounds(400, 160, 160, 160);
		add(panel_1);
		panel_1.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1 = Box.createVerticalStrut(20);
		verticalStrut_1.setPreferredSize(new Dimension(0, 40));
		panel_1.add(verticalStrut_1, BorderLayout.NORTH);

		JButton btnNewButton_1_1 = new JButton("Por proprietário");
		btnNewButton_1_1.setFocusable(false);
		btnNewButton_1_1.setFont(rationaleFont.deriveFont(18f));
		btnNewButton_1_1.setFocusTraversalKeysEnabled(false);
		btnNewButton_1_1.setFocusPainted(false);
		btnNewButton_1_1.setAction(action_1);
		btnNewButton_1_1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1_1.setBackground(Color.WHITE);
		btnNewButton_1_1.setVerticalTextPosition(SwingConstants.BOTTOM);
		btnNewButton_1_1.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1_1.setIcon(new ImageIcon(MainPage.class.getResource("/images/personIcon.png")));
		btnNewButton_1_1.setMargin(new Insets(0, 0, 0, 0));
		btnNewButton_1_1.setBorder(null);
		panel_1.add(btnNewButton_1_1, BorderLayout.CENTER);

		JPanel panel_1_1 = new JPanel();
		panel_1_1.setBackground(Color.WHITE);
		panel_1_1.setBounds(560, 160, 160, 160);
		add(panel_1_1);
		panel_1_1.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_1 = Box.createVerticalStrut(20);
		verticalStrut_1_1.setPreferredSize(new Dimension(0, 40));
		panel_1_1.add(verticalStrut_1_1, BorderLayout.NORTH);

		JButton btnNewButton_1_1_1 = new JButton("Por Tipo");
		btnNewButton_1_1_1.setFont(rationaleFont.deriveFont(18f));
		btnNewButton_1_1_1.setFocusable(false);
		btnNewButton_1_1_1.setFocusTraversalKeysEnabled(false);
		btnNewButton_1_1_1.setFocusPainted(false);
		btnNewButton_1_1_1.setAction(action_2);
		btnNewButton_1_1_1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1_1_1.setBackground(Color.WHITE);
		btnNewButton_1_1_1.setVerticalTextPosition(SwingConstants.BOTTOM);
		btnNewButton_1_1_1.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1_1_1.setIcon(new ImageIcon(MainPage.class.getResource("/images/houseIcon.png")));
		btnNewButton_1_1_1.setMargin(new Insets(0, 0, 0, 0));
		btnNewButton_1_1_1.setBorder(null);
		panel_1_1.add(btnNewButton_1_1_1, BorderLayout.CENTER);

		JPanel panel_1_2 = new JPanel();
		panel_1_2.setBackground(Color.WHITE);
		panel_1_2.setBounds(720, 160, 160, 160);
		add(panel_1_2);
		panel_1_2.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_2 = Box.createVerticalStrut(20);
		verticalStrut_1_2.setPreferredSize(new Dimension(0, 40));
		panel_1_2.add(verticalStrut_1_2, BorderLayout.NORTH);

		JButton btnNewButton_1_1_2 = new JButton("Por Cidade");
		btnNewButton_1_1_2.setFont(rationaleFont.deriveFont(18f));
		btnNewButton_1_1_2.setFocusable(false);
		btnNewButton_1_1_2.setFocusTraversalKeysEnabled(false);
		btnNewButton_1_1_2.setFocusPainted(false);
		btnNewButton_1_1_2.setAction(action_3);
		btnNewButton_1_1_2.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1_1_2.setBackground(Color.WHITE);
		btnNewButton_1_1_2.setVerticalTextPosition(SwingConstants.BOTTOM);
		btnNewButton_1_1_2.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1_1_2.setIcon(new ImageIcon(MainPage.class.getResource("/images/locationIcon.png")));
		btnNewButton_1_1_2.setMargin(new Insets(0, 0, 0, 0));
		btnNewButton_1_1_2.setBorder(null);
		panel_1_2.add(btnNewButton_1_1_2, BorderLayout.CENTER);

		JPanel panel_1_2_1 = new JPanel();
		panel_1_2_1.setBackground(Color.WHITE);
		panel_1_2_1.setBounds(880, 160, 160, 160);
		add(panel_1_2_1);
		panel_1_2_1.setLayout(new BorderLayout(0, 0));

		Component verticalStrut_1_3 = Box.createVerticalStrut(20);
		verticalStrut_1_3.setPreferredSize(new Dimension(0, 40));
		panel_1_2_1.add(verticalStrut_1_3, BorderLayout.NORTH);

		JButton btnNewButton_1_1_3 = new JButton("Por Número Quarto");
		btnNewButton_1_1_3.setFont(rationaleFont.deriveFont(18f));
		btnNewButton_1_1_3.setFocusable(false);
		btnNewButton_1_1_3.setFocusTraversalKeysEnabled(false);
		btnNewButton_1_1_3.setFocusPainted(false);
		btnNewButton_1_1_3.setAction(action_4);
		btnNewButton_1_1_3.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton_1_1_3.setBackground(Color.WHITE);
		btnNewButton_1_1_3.setVerticalTextPosition(SwingConstants.BOTTOM);
		btnNewButton_1_1_3.setHorizontalTextPosition(SwingConstants.CENTER);
		btnNewButton_1_1_3.setIcon(new ImageIcon(MainPage.class.getResource("/images/bedIcon.png")));
		btnNewButton_1_1_3.setMargin(new Insets(0, 0, 0, 0));
		btnNewButton_1_1_3.setBorder(null);
		panel_1_2_1.add(btnNewButton_1_1_3, BorderLayout.CENTER);

		JButton btnNewButton = new JButton("< Escolher outro arquivo");
		btnNewButton.setAction(voltarLandingPage);
		btnNewButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton.setFocusable(false);
		btnNewButton.setFocusPainted(false);
		btnNewButton.setFocusTraversalKeysEnabled(false);
		btnNewButton.setOpaque(false);
		btnNewButton.setBorder(null);
		btnNewButton.setFont(rationaleFont.deriveFont(24f));
		btnNewButton.setForeground(Color.WHITE);
		btnNewButton.setAlignmentX(Component.CENTER_ALIGNMENT);
		btnNewButton.setBackground(Color.WHITE);
		btnNewButton.setBounds(0, 5, 237, 35);
		add(btnNewButton);

		JLabel lblNewLabel = new JLabel("Pesquisa");
		lblNewLabel.setFont(rationaleFont.deriveFont(72f));
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setBounds(0, 15, 1280, 64);
		add(lblNewLabel);

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
