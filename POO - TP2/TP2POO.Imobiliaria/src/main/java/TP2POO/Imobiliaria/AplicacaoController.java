package TP2POO.Imobiliaria;

import java.io.File;

public class AplicacaoController {
	LandingPage landing;
	MainPage main;
	
	File arquivoSelecionado;
	
	 public AplicacaoController()
	   {
		 landing = new LandingPage(this);
		 main = new MainPage(this);
		 
		 arquivoSelecionado = new File("database_imoveis.txt"); 
				 
		 showLanding();
	   }
	 
	 public void showLanding()
	   {
		 landing.setVisible(true);
		 main.setVisible(false);
	   }
	 
	 public void showMain()
	   {
		 System.out.println(arquivoSelecionado);
		 landing.setVisible(false);
		 main.setVisible(true);
	   }
}
