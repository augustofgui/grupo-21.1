package TP2POO.Imobiliaria;

import java.io.File;
import java.util.ArrayList;
import javax.swing.JOptionPane;

// Classe do Controlador da aplicação
public class AplicacaoController {

	// Panels principais da aplicação
	private LandingPage landing = null;
	private MainPage main = null;
	private SearchPage search = null;
	
	// Array de coleção de imóveis do arquivo e de pesquisa
	private ArrayList<Imovel> imoveisBase = null;
	private ArrayList<Imovel> imoveisPesquisados = null;
	
	// Arquivo selecionado pelo usuário
	private File arquivoSelecionado = null;

	// Enum para os tipos possíveis de pesquisa da aplicação
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

	// Construtor da classe
	public AplicacaoController() {

		// Cria instâncias dos panels
		landing = new LandingPage(this);
		main = new MainPage(this);
		search = new SearchPage(this);
		
		// Inicializa os Arrays de imóveis
		imoveisBase = new ArrayList<Imovel>();
		imoveisPesquisados = new ArrayList<Imovel>();
		
		// Inicializa o arquivo selecionado com o arquivo padrão
		arquivoSelecionado = new File("database_imoveis.txt");

		showLanding();
	}
	
	// Getters
	public LandingPage getLanding() {
		return landing;
	}
	
	public MainPage getMain() {
		return main;
	}
	
	public SearchPage getSearch() {
		return search;
	}
	
	// Setter
	public void setArquivoSelecionado(File newFile) {
		arquivoSelecionado = newFile;
	}

	// Função que mostra a tela de Landing, primeira tela
	public void showLanding() {
		landing.setVisible(true);
		main.setVisible(false);
		search.setVisible(false);
	}

	// Função de passagem de tela de Landing para Search
	// Lê o arquivo selecionado na tela de Landing e insere
	// no Array de imoveisBase.
	public void showMain() {
		// Reinicia o vetor base de imoveis, depois lê do arquivo selecionado
		imoveisBase.clear();
		imoveisBase = Imobiliaria.leArquivo(arquivoSelecionado);
		
		// Caso o arquivo não contenha um imóvel
		// Retorna para a página de Landing e exibe uma tela de erro
		if(imoveisBase.isEmpty()) {
			JOptionPane.showMessageDialog(landing, "Não foi encontrado nenhum imóvel neste arquivo!!", "Erro de arquivo", JOptionPane.ERROR_MESSAGE);
			showLanding();
			return;
		}

		// Caso não tenha ocorrido erro na leitura
		// o programa passa para a tela principal de funções, MainPage
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);
	}
	
	// Função de retorno para a tela principal, MainPage
	// Mas nesse caso, vindo da tela de pesquisa, SearchPage
	public void returnToMain() {
		// Exibe a tela principal
		landing.setVisible(false);
		main.setVisible(true);
		search.setVisible(false);

		// Limpa os campos de pesquisa da página
		search.resetTextField();
		search.resetTextPane();
		
		// Reinica o Array de itens pesquisados
		if(imoveisPesquisados != null)
			imoveisPesquisados.clear();
	}

	// Mostra a tela de pesquisa de acordo com o tipo de pesquisa escolhido
	public void showSearchPageByType(TiposPesquisa tipo) {
		landing.setVisible(false);
		main.setVisible(false);
		search.setVisible(true);
		search.setTipoPesquisa(tipo);
	}
	
	// Transcreve o resultado da pesquisa para String
	public void insereNoTextField(ArrayList<Imovel> imoveis) {
		String pesquisa = "";
		
		// Caso a pesquisa tenha retornado um Array vazio
		if(imoveis.isEmpty())
			pesquisa = "Não foi encontrado nenhum imóvel com este parametro!";
		
		// Adiciona o imóvel para a string de resultado
		for (Imovel imovel : imoveis) {
			pesquisa = pesquisa.concat(imovel.toString() + System.lineSeparator());
        }
		
		// Altera o campo de texto da página de pesquisa
		search.changeTextPane(pesquisa);
	}
	
	// Função de salvar a pesquisa num arquivo separado
	public void salvaPesquisa() {
		Imobiliaria.salvarColecao(imoveisPesquisados);
		JOptionPane.showMessageDialog(landing, "A coleção foi salva com sucesso no arquivo: colecao_imoveis.txt", "Coleção salva com sucesso!", JOptionPane.INFORMATION_MESSAGE);		
	}
	
	// Função de printar a pesquisa no terminal
	public void printPesquisa() {
		Imobiliaria.printColecao(imoveisPesquisados);
	}
	
	// Realiza a pesquisa pela string inserida dependendo o tipo de pesquisa escolhido
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
		
		// Retorna o resultado da pesquisa para alterar o campo de texto da página
		insereNoTextField(imoveisPesquisados);
	}
}
