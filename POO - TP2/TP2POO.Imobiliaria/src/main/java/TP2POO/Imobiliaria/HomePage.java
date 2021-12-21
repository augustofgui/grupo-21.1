package TP2POO.Imobiliaria;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.BorderFactory;
import javax.swing.text.AttributeSet.ColorAttribute;

import java.awt.*;
import java.awt.event.*;
import java.io.File;

public class HomePage extends JPanel {
    
    HomePage() {
        this.setLayout(new GridLayout(1,2));

        JPanel left = new JPanel(new GridLayout(2,1));
        left.setBackground(Color.white);

        JPanel right = new JPanel(new GridLayout(1,0));
        right.setBackground(Color.white);
        
        JPanel top = new JPanel(new BorderLayout());
        top.setBackground(Color.white);

        JPanel logoMargin = new JPanel();
        logoMargin.setBackground(Color.white);
        logoMargin.setPreferredSize(new Dimension(185, 185));

        JPanel logo = new JPanel(new GridLayout(2,1,0,-10));
        logo.setBackground(Color.white);
        
        JLabel logoText = new JLabel("Imobiliária");
        logoText.setFont(new Font("SansSerif", Font.BOLD, 54));
        logoText.setVerticalAlignment(JLabel.BOTTOM);
        logoText.setHorizontalAlignment(JLabel.LEFT);

        JLabel logoAccent = new JLabel();
        logoAccent.setIcon(new ImageIcon(System.getProperty("user.dir") + "/POO - TP2/TP2POO.Imobiliaria/img/logoAccent.png"));
        logoAccent.setVerticalAlignment(JLabel.TOP);
        logoAccent.setHorizontalAlignment(JLabel.LEFT);

        logo.add(logoText);
        logo.add(logoAccent);

        top.add(logoMargin, BorderLayout.WEST);
        top.add(logo, BorderLayout.CENTER);

        JPanel bottom = new JPanel(new BorderLayout());
        bottom.setBackground(Color.white);

        JPanel panelMargin = new JPanel();
        panelMargin.setBackground(Color.white);
        panelMargin.setPreferredSize(new Dimension(185, 185));

        JPanel filePanel = new JPanel();
        filePanel.setLayout(new BoxLayout(filePanel, BoxLayout.Y_AXIS));
        filePanel.setPreferredSize(new Dimension(185, 185));
        filePanel.setBackground(Color.white);

        JLabel fileLabel = new JLabel("Arquivo");
        fileLabel.setFont(new Font("SansSerif", Font.BOLD, 24));
        fileLabel.setPreferredSize(new Dimension(270, 42));
        fileLabel.setHorizontalAlignment(JLabel.LEFT);
        fileLabel.setAlignmentX(Component.LEFT_ALIGNMENT);

        Border fileLabelBoxBorder = BorderFactory.createLineBorder(Color.black, 2);

        String spaces = "    ";

        JLabel fileLabelBox = new JLabel("  database_imoveis.txt" + spaces + spaces);
        fileLabelBox.setFont(new Font("SansSerif", Font.PLAIN, 20));
        fileLabelBox.setPreferredSize(new Dimension(276, 42));
        fileLabelBox.setBorder(fileLabelBoxBorder);
        fileLabelBox.setAlignmentX(Component.LEFT_ALIGNMENT);
        
        
        JPanel fileButtons = new JPanel();
        fileButtons.setLayout(new FlowLayout(FlowLayout.LEFT));
        fileButtons.setAlignmentX(Component.LEFT_ALIGNMENT);
        fileButtons.setBackground(Color.white);
        
        JButton submit = new JButton("Confirmar");
        submit.setPreferredSize(new Dimension(120, 42));
        submit.setAlignmentX(Component.LEFT_ALIGNMENT);
        submit.setBackground(Color.black);
        submit.setBorder(null);
        submit.setFocusPainted(false);
        submit.setBorderPainted(true);
        submit.setMargin(new Insets(0,0,0,0));
        

        JButton alterar = new JButton("Alterar arquivo");
        alterar.setPreferredSize(new Dimension(120, 42));
        alterar.setAlignmentX(Component.LEFT_ALIGNMENT);
        alterar.setBackground(Color.white);
        alterar.setBorder(null);
        alterar.setFocusPainted(false);
        alterar.setBorderPainted(true);
        alterar.setMargin(new Insets(0,0,0,0));
        

        fileButtons.add(submit);
        fileButtons.add(alterar);

        filePanel.add(fileLabel);
        filePanel.add(fileLabelBox);
        filePanel.add(fileButtons);

        bottom.add(panelMargin, BorderLayout.WEST);
        bottom.add(filePanel, BorderLayout.CENTER);

        left.add(top);
        left.add(bottom);

        this.add(left);
        this.add(right);
    }
}
