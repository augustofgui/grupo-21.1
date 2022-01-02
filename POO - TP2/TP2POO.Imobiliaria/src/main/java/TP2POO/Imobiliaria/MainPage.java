package TP2POO.Imobiliaria;

import javax.swing.JPanel;
import java.awt.Rectangle;
import java.awt.Color;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.border.LineBorder;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.Component;
import java.awt.Cursor;
import javax.swing.AbstractAction;
import java.awt.event.ActionEvent;
import javax.swing.Action;

public class MainPage extends JPanel {
	
	
	private static final long serialVersionUID = 1L;

	AplicacaoController controller = null;
	private final Action voltarLandingPage = new SwingAction();

	public MainPage(AplicacaoController c) {
		setBounds(new Rectangle(0, 0, 1280, 720));
		controller = c;
				
		setBackground(Color.WHITE);
		setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBorder(new LineBorder(Color.WHITE, 54, true));
		panel.setBackground(Color.WHITE);
		panel.setBounds(new Rectangle(100, 100, 1024, 200));
		panel.setBounds(128, 130, 1024, 200);
		add(panel);
		
		JButton btnNewButton = new JButton("< Escolher outro arquivo");
		btnNewButton.setAction(voltarLandingPage);
		btnNewButton.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
		btnNewButton.setFocusable(false);
		btnNewButton.setFocusPainted(false);
		btnNewButton.setFocusTraversalKeysEnabled(false);
		btnNewButton.setOpaque(false);
		btnNewButton.setBorder(null);
		btnNewButton.setFont(new Font("Tahoma", Font.PLAIN, 20));
		btnNewButton.setForeground(Color.WHITE);
		btnNewButton.setAlignmentX(Component.CENTER_ALIGNMENT);
		btnNewButton.setBounds(10, 11, 263, 35);
		add(btnNewButton);
		
		JLabel lblNewLabel = new JLabel("");
		lblNewLabel.setIcon(new ImageIcon("C:\\Users\\jeron\\Downloads\\imgMain.png"));
		lblNewLabel.setBounds(0, 0, 1264, 681);
		add(lblNewLabel);
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
}
