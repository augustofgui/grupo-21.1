package TP2POO.Imobiliaria;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;

public class Janela extends JFrame implements ActionListener {

    JButton changeFileButton;

    Janela(){
        this.setTitle("Imobiliária");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setResizable(false);
        this.setSize(1280, 720);
        this.setBackground(Color.white);
        
        ImageIcon logo = new ImageIcon(System.getProperty("user.dir") + "/POO - TP2/TP2POO.Imobiliaria/img/logo.png");
        this.setIconImage(logo.getImage());

        this.setLayout(new BorderLayout());

        HomePage homePage = new HomePage();

        this.add(homePage, BorderLayout.CENTER);
        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == changeFileButton) {
            JFileChooser fileChooser = new JFileChooser();

            int response = fileChooser.showOpenDialog(null);

            if(response == JFileChooser.APPROVE_OPTION) {
                File file = new File(fileChooser.getSelectedFile().getAbsolutePath());
                System.out.println(file);
            }
        }
        
    }
    
}
