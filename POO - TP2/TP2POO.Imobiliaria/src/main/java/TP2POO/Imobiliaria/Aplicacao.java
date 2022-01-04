package TP2POO.Imobiliaria;

// Imports para fazer a GUI
import javax.swing.JFrame;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.CardLayout;

// Classe da Aplicacao
public class Aplicacao {

	// JFrame da aplicação do programa
	private JFrame frame;
	
	// Main
	public static void main(String[] args) {
		// Iniciar Aplicacao
		EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    Aplicacao window = new Aplicacao();
					// Configs da JFrame
                    window.frame.setResizable(false);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
	
	// Construtor da classe
	public Aplicacao() {
		initialize();
	}

	// Inicializa a JFrame e insere os panels principais
	private void initialize() {
		// Configs da JFrame
		frame = new JFrame();
		frame.setBackground(Color.WHITE);
		frame.getContentPane().setBackground(Color.WHITE);

		// Criação do controlador da aplicação
		AplicacaoController controller = new AplicacaoController();

		// Adicionando os panels principais
		frame.getContentPane().add(controller.getLanding());
		frame.getContentPane().add(controller.getMain());
		frame.getContentPane().add(controller.getSearch());

		// Seta o layout para Card
		frame.getContentPane().setLayout(new CardLayout(0, 0));

		// Configs da JFrame
		frame.setBounds(100, 100, 1280, 720);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

		// Reinicializa a aplicação
		frame.revalidate();
	}
}
