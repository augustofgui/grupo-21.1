package TP2POO.Imobiliaria;

import java.awt.Font;
import java.io.File;
import java.util.ArrayList;

import javax.swing.JOptionPane;

public class AplicacaoController {
	private LandingPage landing = null;
	private MainPage main = null;
	private SearchPage search = null;
	
	private ArrayList<Imovel> imoveisBase = null;
	private ArrayList<Imovel> imoveisPesquisados = null;
	
	private File arquivoSelecionado = null;
	private Font rationaleFont = null;

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
		
		imoveisBase = new ArrayList<Imovel>();
		imoveisPesquisados = new ArrayList<Imovel>();
		
		arquivoSelecionado = new File("database_imoveis.txt");

		showLanding();
	}
	

	public Font getFont() {
		return rationaleFont;
	}
	
	public LandingPage getLanding() {
		return landing;
	}
	
	public MainPage getMain() {
		return main;
	}
	
	public SearchPage getSearch() {
		return search;
	}
	
	public void setArquivoSelecionado(File newFile) {
		arquivoSelecionado = newFile;
	}

	public void showLanding() {
		landing.setVisible(true);
		main.setVisible(false);
		search.setVisible(false);
	}

	public void showMain() {
		imoveisBase.clear();
		imoveisBase = Imobiliaria.leArquivo(arquivoSelecionado);
		if(imoveisBase.isEmpty()) {
			JOptionPane.showMessageDialog(landing, "Não foi encontrado nenhum imóvel neste arquivo!!", "Erro de arquivo", JOptionPane.ERROR_MESSAGE);
			showLanding();
			return;
		}
		
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);
	}
	
	public void returnToMain() {
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);
		search.resetTextField();
		search.resetTextPane();
		
		if(imoveisPesquisados != null)
			imoveisPesquisados.clear();
	}

	public void showSearchPageByType(TiposPesquisa tipo) {
		landing.setVisible(false);
		main.setVisible(false);
		search.setVisible(true);
		search.setTipoPesquisa(tipo);
	}
	
	public void insereNoTextField(ArrayList<Imovel> imoveis) {
		String pesquisa = "";
		
		if(imoveis.isEmpty())
			pesquisa = "Não foi encontrado nenhum imóvel com este parametro!";
		
		for (Imovel imovel : imoveis) {
			pesquisa = pesquisa.concat(imovel.toString() + System.lineSeparator());
        }
		
		search.changeTextPane(pesquisa);
	}
	
	public void salvaPesquisa() {
		Imobiliaria.salvarColecao(imoveisPesquisados);
	}
	
	public void printPesquisa() {
		Imobiliaria.printColecao(imoveisPesquisados);
	}
	
	public void realizarPesquisa(TiposPesquisa tipo, String strValor) {
		if (tipo == TiposPesquisa.Cidade) {
			imoveisPesquisados = Imobiliaria.buscarCidade(imoveisBase, strValor);
		} else if (tipo == TiposPesquisa.NumQuartos) {
			imoveisPesquisados = Imobiliaria.buscarQuartos(imoveisBase, Integer.parseInt(strValor));
		} else if (tipo == TiposPesquisa.Proprietario) {
			imoveisPesquisados = Imobiliaria.buscarProprietario(imoveisBase, strValor);
		} else if (tipo == TiposPesquisa.Tipo) {
			imoveisPesquisados = Imobiliaria.buscarPorTipo(imoveisBase, strValor);
		} else if (tipo == TiposPesquisa.Valor) {
			imoveisPesquisados = Imobiliaria.buscarPrecoMaximo(imoveisBase, Float.parseFloat(strValor));
		} else {
			System.out.println("Pesquisa inválida!");
		}
		
		insereNoTextField(imoveisPesquisados);
	}
}
