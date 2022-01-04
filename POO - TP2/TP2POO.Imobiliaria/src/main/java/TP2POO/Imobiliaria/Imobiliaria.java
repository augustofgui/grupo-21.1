package TP2POO.Imobiliaria;

// Imports
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import java.util.ArrayList;
import java.util.Collections;

// Classe de controle dos imoveis
public class Imobiliaria {
	
    // Função que tenta abrir o arquivo e recuperara imoveis dele
    public static ArrayList<Imovel> leArquivo(File database_imoveis) {
        ArrayList<Imovel> imoveisArquivo = new ArrayList<Imovel>();

        // Tenta abrir o arquivo
        try {
            Scanner txt = new Scanner(database_imoveis);
            while (txt.hasNextLine()) {
                // Lê linha
                String imovel = txt.nextLine();

                // Separa string lida entre ";"
                String[] data = imovel.split(";");

                // Criação do objeto e push_back no vetor polimórfico de imóveis
                if (data[0].equals("casa")) 
                    imoveisArquivo.add(new Casa(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            Integer.parseInt(data[9]), intToBoolean(data[10])));
                else if (data[0].equals("apartamento"))
                    imoveisArquivo.add(new Apartamento(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            Integer.parseInt(data[9]), Float.parseFloat(data[10]), intToBoolean(data[11]),
                            intToBoolean(data[12])));
                else if (data[0].equals("chacara"))
                    imoveisArquivo.add(new Chacara(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            intToBoolean(data[9]), intToBoolean(data[10]),
                            intToBoolean(data[11]), intToBoolean(data[12]),
                            intToBoolean(data[13])));
                else
                    System.out.println("ERRO : Imóvel inválido.\n");
            }

            // Fecha arquivo
            txt.close();
        } catch (FileNotFoundException e) {
            System.out.println("ERRO : Arquivo não encontrado.\n");
            e.printStackTrace();
        }

        // Retorna coleção de imoveis lidas do arquivo
        return imoveisArquivo;
    }

    // Função que recupera todos os imoveis de um tipo da coleção
    public static ArrayList<Imovel> buscarPorTipo(ArrayList<Imovel> imoveis, String tipo) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        int tipo_imovel = 0; // - > placeholder
        
        // Verifica qual tipo foi buscado
        tipo.toLowerCase();
        if(tipo.equals("casa")) {
        	tipo_imovel = 1;
        } else if(tipo.equals("apartamento")) {
        	tipo_imovel = 2;
        } else if(tipo.equals("chacara")) {
        	tipo_imovel = 3;
        }
        
        // Dependendo do tipo buscado, recupera da coleção
        switch (tipo_imovel) {
            case 1:
                for (Imovel imovel : imoveis) {
                    if (imovel instanceof Casa)
                        resultado.add(imovel);
                }
                break;
            case 2:
                for (Imovel imovel : imoveis) {
                    if (imovel instanceof Apartamento)
                        resultado.add(imovel);
                }
                break;
            case 3:
                for (Imovel imovel : imoveis) {
                    if (imovel instanceof Chacara)
                        resultado.add(imovel);
                }
                break;
        }

        // Retorna o resultado da pesquisa
        return resultado;
    }

    // Salva coleção inserida em um novo arquivo
    public static void salvarColecao(ArrayList<Imovel> imoveis) {
        // Tenta criar e inserir no arquivo
        try {
            FileWriter colecao = new FileWriter("colecao_imoveis.txt");
            // Para cada imovel, tenta escreve-lo no arquivo
            for (Imovel imovel : imoveis)
                colecao.write(imovel.toWrite());

            // Fecha o novo arquivo
            colecao.close();
            System.out.println("Coleção salva em colecao_imoveis.txt!");
        } catch (IOException e) {
            // Aviso de erro
            System.out.println("ERRO : I/O.");
            e.printStackTrace();
        }
    }
    
    // Verifica se é proprietário deste imovel
    public static Boolean ehProprietario(Imovel imovel, String proprietario) {
    	if (imovel.getProprietario().equals(proprietario))
    		return true;
       
    	return false;
    }

    // Recupera da coleção a subcoleção de imoveis que o proprietário possui
    public static ArrayList<Imovel> buscarProprietario(ArrayList<Imovel> imoveis, String proprietario) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {

            // Verifica se é proprietário deste imovel
            if (ehProprietario(imovel, proprietario))
                resultado.add(imovel);
        }

        // Retorna o resultado da pesquisa
        return resultado;
    }

    // Busca na coleção os imoveis com valores abaixo do valor buscado
    public static ArrayList<Imovel> buscarPrecoMaximo(ArrayList<Imovel> imoveis, float valorMax) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            // Caso o valor esteja abaixo, adiciona a coleção de pesquisa
            if (imovel.getValor() < valorMax)
                resultado.add(imovel);
        }

        // Retorna o resultado da pesquisa
        return resultado;
    }

    // Busca na coleção todos os imoveis que tem como cidade a string buscada
    public static ArrayList<Imovel> buscarCidade(ArrayList<Imovel> imoveis, String cidade) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            // Caso a cidade seja igual, é adicionado a coleção de pesquisa
            if (imovel.getCidade().equals(cidade))
                resultado.add(imovel);
        }

        // Retorna o resultado da pesquisa
        return resultado;
    }

    // Busca na coleção todos os imoveis que tem um quantidade de quartos
    // menores ou iguais ao valor inserido
    public static ArrayList<Imovel> buscarQuartos(ArrayList<Imovel> imoveis, int numQuartos) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            // Caso a quantidade de quartos seja menor ou igual, o imovel é inserido na coleção
            if (imovel.getQuartos() <= numQuartos) // - > placeholder
                resultado.add(imovel);
        }

        // Retorna o resultado da pesquisa
        return resultado;
    }

    // Funções de ordenação
    public static void ordenarCrescente(ArrayList<Imovel> imoveis) {
        Collections.sort(imoveis);
    }

    public static void ordenarDecrescente(ArrayList<Imovel> imoveis) {
        Collections.sort(imoveis, Collections.reverseOrder());
    }

    // Função que printa a coleção no terminal
    public static void printColecao(ArrayList<Imovel> imoveis) {
        for (Imovel imovel : imoveis)
            System.out.println(imovel.toString());
    }

    // Funnção que converte int para boolean
    public static boolean intToBoolean(String x) {
        return (Integer.parseInt(x) == 0) ? false : true;
    }
}
