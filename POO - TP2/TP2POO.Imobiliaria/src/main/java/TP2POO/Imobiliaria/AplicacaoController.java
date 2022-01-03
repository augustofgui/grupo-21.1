package TP2POO.Imobiliaria;

import java.awt.Font;
import java.io.File;
import java.util.ArrayList;

public class AplicacaoController {
	LandingPage landing = null;
	MainPage main = null;
	SearchPage search = null;
	
	Imobiliaria imobiliaria;
	
	ArrayList<Imovel> imoveis = null;
	
	File arquivoSelecionado = null;
	Font rationaleFont = null;

	TiposPesquisa pesquisa;

	public enum TiposPesquisa {
		Valor(1), Proprietario(2), Tipo(3), Cidade(4), NumQuartos(5);

		private final int valorPesquisa;

		TiposPesquisa(int valorP) {
			valorPesquisa = valorP;
		}

		public int getValor() {
			return valorPesquisa;
		}
	}

	public AplicacaoController() {
		landing = new LandingPage(this);
		main = new MainPage(this);
		search = new SearchPage(this);
		
		imobiliaria = new Imobiliaria();
		imobiliaria.imoveis = new ArrayList<Imovel>();
		
		arquivoSelecionado = new File("database_imoveis.txt");

		showLanding();
	}

	public Font getFont() {
		return rationaleFont;
	}

	public void showLanding() {
		landing.setVisible(true);
		main.setVisible(false);
		search.setVisible(false);
	}

	public void showMain() {
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);
		imobiliaria.imoveis = Imobiliaria.leArquivo(arquivoSelecionado);
	}
	
	public void returnToMain() {
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);
	}

	public void showSearchPageByType(TiposPesquisa tipo) {
		pesquisa = tipo;
		landing.setVisible(false);
		main.setVisible(false);
		search.setVisible(true);
		search.setTipoPesquisa(tipo);
	}
	
	public void realizarPesquisa(TiposPesquisa tipo, String strValor) {
		System.out.println("Tipos pesquisa: " + tipo);
		if (tipo == TiposPesquisa.Cidade) {
			Imobiliaria.printColecao(Imobiliaria.buscarCidade(imobiliaria.imoveis, strValor));
		} else if (tipo == TiposPesquisa.NumQuartos) {
			Imobiliaria.printColecao(Imobiliaria.buscarQuartos(imobiliaria.imoveis, Integer.parseInt(strValor)));
		} else if (tipo == TiposPesquisa.Proprietario) {
			Imobiliaria.printColecao(Imobiliaria.buscarProprietario(imobiliaria.imoveis, strValor));
		} else if (tipo == TiposPesquisa.Tipo) {
			Imobiliaria.printColecao(Imobiliaria.buscarPorTipo(imobiliaria.imoveis, strValor));
		} else if (tipo == TiposPesquisa.Valor) {
			Imobiliaria.printColecao(Imobiliaria.buscarPrecoMaximo(imobiliaria.imoveis, Float.parseFloat(strValor)));
		} else {
			System.out.println("Pesquisa inválida!");
		}
		System.out.println("===================================================");
	}
}
