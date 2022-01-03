package TP2POO.Imobiliaria;

import javax.swing.JFrame;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.CardLayout;

public class Aplicacao {

	private JFrame frame;
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    Aplicacao window = new Aplicacao();
                    window.getFrame().setResizable(false);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
	
	/**
	 * Create the application.
	 */
	public Aplicacao() {
		initialize();
	}

	private void initialize() {
		frame = new JFrame();
		frame.setBackground(Color.WHITE);
		frame.setResizable(false);
		frame.getContentPane().setBackground(Color.WHITE);

		AplicacaoController controller = new AplicacaoController();

		frame.getContentPane().add(controller.landing);
		frame.getContentPane().add(controller.main);
		frame.getContentPane().add(controller.search);

		frame.getContentPane().setLayout(new CardLayout(0, 0));

		frame.setBounds(100, 100, 1280, 720);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		frame.revalidate();
	}

	public JFrame getFrame() {
		return frame;
	}
}
