package TP2POO.Imobiliaria;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

import java.util.ArrayList;
import java.util.Collections;

public class Imobiliaria {
	public ArrayList<Imovel> imoveis = null;
	
	
	public Imobiliaria() {
		imoveis = new ArrayList<Imovel>();
	}
	
    public static ArrayList<Imovel> leArquivo(File database_imoveis) {
        ArrayList<Imovel> imoveisArquivo = new ArrayList<Imovel>();

        try {
            Scanner txt = new Scanner(database_imoveis);
            while (txt.hasNextLine()) {
                String imovel = txt.nextLine();
                String[] data = imovel.split(";");
                if (data[0].equals("casa")) // - > Criação do objeto e push_back no vetor polimórfico de imóveis
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
            txt.close();
        } catch (FileNotFoundException e) {
            System.out.println("ERRO : Arquivo não encontrado.\n");
            e.printStackTrace();
        }

        return imoveisArquivo;
    }

    public static ArrayList<Imovel> buscarPorTipo(ArrayList<Imovel> imoveis, String tipo) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        int tipo_imovel = 0; // - > placeholder
        
        tipo.toLowerCase();
        
        if(tipo.equals("casa")) {
        	tipo_imovel = 1;
        } else if(tipo.equals("apartamento")) {
        	tipo_imovel = 2;
        } else if(tipo.equals("chacara")) {
        	tipo_imovel = 3;
        }
        
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

        return resultado;
    }

    public static void salvarColecao(ArrayList<Imovel> imoveis) {
        try {
            FileWriter colecao = new FileWriter("colecao_imoveis.txt");
            for (Imovel imovel : imoveis)
                colecao.write(imovel.toWrite());
            colecao.close();
            System.out.println("Coleção salva em colecao_imoveis.txt!");
        } catch (IOException e) {
            System.out.println("ERRO : I/O.");
            e.printStackTrace();
        }
    }
    
    public static Boolean ehProprietario(Imovel imovel, String proprietario) {
    	
    	if (imovel.getProprietario().equals(proprietario))
    		return true;
       
    	return false;
    }

    public static ArrayList<Imovel> buscarProprietario(ArrayList<Imovel> imoveis, String proprietario) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (ehProprietario(imovel, proprietario))
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarPrecoMaximo(ArrayList<Imovel> imoveis, float valorMax) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getValor() < valorMax) // - > placeholder
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarCidade(ArrayList<Imovel> imoveis, String cidade) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getCidade().equals(cidade))
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarQuartos(ArrayList<Imovel> imoveis, int numQuartos) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getQuartos() <= numQuartos) // - > placeholder
                resultado.add(imovel);
        }

        return resultado;
    }

    public static void ordenarCrescente(ArrayList<Imovel> imoveis) {
        Collections.sort(imoveis);
    }

    public static void ordenarDecrescente(ArrayList<Imovel> imoveis) {
        Collections.sort(imoveis, Collections.reverseOrder());
    }

    public static void printColecao(ArrayList<Imovel> imoveis) {
        for (Imovel imovel : imoveis)
            System.out.println(imovel.toString());
    }

    public static boolean intToBoolean(String x) {
        return (Integer.parseInt(x) == 0) ? false : true;
    }
}
