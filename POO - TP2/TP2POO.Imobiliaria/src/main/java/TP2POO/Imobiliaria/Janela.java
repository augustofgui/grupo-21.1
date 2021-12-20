package TP2POO.Imobiliaria;

import javax.swing.*;
import java.awt.*;

public class Janela extends JFrame {

    Janela(){
        this.setTitle("Imobiliária");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setSize(1280,720);
        
        ImageIcon logo = new ImageIcon("POO - TP2/TP2POO.Imobiliaria/logo.png");
        this.setIconImage(logo.getImage());

        this.setLayout(new BorderLayout());

        JPanel navBar = new JPanel();
        navBar.setPreferredSize(new Dimension(120, 120));
        navBar.setBackground(Color.blue);
        JLabel navBarLabel = new JLabel("Imobiliária");
        navBarLabel.setBounds(120, 120, 0, 0);
        navBarLabel.setFont(new Font("Verdana", Font.PLAIN, 48));

        navBar.add(navBarLabel);
        
        this.add(navBar, BorderLayout.NORTH);
        this.setVisible(true);
    }
    
}
