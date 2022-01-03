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
import javax.swing.AbstractAction;
import java.awt.event.ActionEvent;
import javax.swing.Action;
import java.awt.Dimension;
import javax.swing.JScrollPane;
import java.awt.Component;
import javax.swing.Box;
import javax.swing.BoxLayout;

public class SearchPage extends JPanel {
	private static final long serialVersionUID = 1L;
	
	AplicacaoController controller = null;
	Font rationaleFont = null;
	private final Action action = new SwingAction();
	
	public SearchPage(AplicacaoController c) {
		setPreferredSize(new Dimension(1280, 720));
		controller = c;
		
		try {
			rationaleFont = Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")).deriveFont(24f);
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
		    ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("Rationale.ttf")));
		} catch (IOException|FontFormatException e) {
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
		
		JPanel panel = new JPanel();
		panel.setBounds(15, 68, 500, 500);
		add(panel);
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		
		JScrollPane scrollPane_1 = new JScrollPane();
		panel.add(scrollPane_1);
		
		JPanel panel_1 = new JPanel();
		panel.add(panel_1);
		
		JPanel panel_2 = new JPanel();
		panel.add(panel_2);
		
		JLabel lblNewLabel = new JLabel("");
		lblNewLabel.setBounds(-10, -37, 1280, 720);
		lblNewLabel.setIcon(new ImageIcon(SearchPage.class.getResource("/images/imgSearch.png")));
		add(lblNewLabel);
		
		}	
	private class SwingAction extends AbstractAction {
		/**
		 * 
		 */
		private static final long serialVersionUID = 1L;
		public SwingAction() {
			putValue(NAME, "< Voltar");
		}
		public void actionPerformed(ActionEvent e) {
			controller.showMain();
		}
	}
}
