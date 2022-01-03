package TP2POO.Imobiliaria;

import java.awt.Font;
import java.io.File;

public class AplicacaoController {
	LandingPage landing = null;
	MainPage main = null;
	SearchPage search = null;
	
	File arquivoSelecionado = null;
	Font rationaleFont = null;
	
	TiposPesquisa pesquisa;
	
	public enum TiposPesquisa {
		Valor(1), Proprietario(2), Tipo(3), Cidade(4), NumQuartos(5);
	
	
	private final int valorPesquisa;
	TiposPesquisa(int valorP) {
		valorPesquisa = valorP;
	}
	
	public int getValor(){
		return valorPesquisa;
	}
	}
	
	 public AplicacaoController()
	   {
		 landing = new LandingPage(this);
		 main = new MainPage(this);
		 search = new SearchPage(this);
		 
		 arquivoSelecionado = new File("database_imoveis.txt");
		 
		 showLanding();
	   }
	 
	 public Font getFont() {
		 return rationaleFont;
	 }
	 
	 public void showLanding()
	   {
		 landing.setVisible(true);
		 main.setVisible(false);
		 search.setVisible(false);
	   }
	 
	 public void showMain()
	   {
		 System.out.println(arquivoSelecionado);
		 landing.setVisible(false);
		 main.setVisible(true);
		 search.setVisible(false);
	   }
	 
	 public void showSearchPageByType(TiposPesquisa tipo)
	   {
		 pesquisa = tipo;
		 landing.setVisible(false);
		 main.setVisible(false);
		 search.setVisible(true);
	   }
}
