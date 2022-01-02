package TP2POO.Imobiliaria;

import javax.swing.JFrame;
import java.awt.Color;
import java.awt.CardLayout;

public class Aplicacao {

	private JFrame frame;
	
	/**
	 * Create the application.
	 */
	public Aplicacao() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBackground(Color.WHITE);
		frame.setResizable(false);
		frame.getContentPane().setBackground(Color.WHITE);
		
		AplicacaoController controller = new AplicacaoController();
		
		frame.getContentPane().add(controller.landing);
		frame.getContentPane().add(controller.main);
		
		frame.getContentPane().setLayout(new CardLayout(0, 0));
		
		frame.setBounds(100, 100, 1280, 720);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.revalidate();
	}
}
