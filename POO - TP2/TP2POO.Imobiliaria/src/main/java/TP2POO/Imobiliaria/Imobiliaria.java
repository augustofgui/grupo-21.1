package TP2POO.Imobiliaria;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Imobiliaria {
    public static void main(String[] args) {
        ArrayList<Imovel> imoveis = new ArrayList<Imovel>();
        // - > Leitura do arquivo database_imoveis.txt
        try {
            File database_imoveis = new File("POO - TP2/TP2POO.Imobiliaria/database_imoveis.txt");
            Scanner txt = new Scanner(database_imoveis);
            while (txt.hasNextLine()) {
                String imovel = txt.nextLine();
                String[] data = imovel.split(";");
                if (data[0].equals("casa")) // - > Criação do objeto e push_back no vetor polimórfico de imóveis
                    imoveis.add(new Casa(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            Integer.parseInt(data[9]), Boolean.parseBoolean(data[10])));
                else if (data[0].equals("apartamento"))
                    imoveis.add(new Apartamento(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            Integer.parseInt(data[9]), Float.parseFloat(data[10]), Boolean.parseBoolean(data[11]),
                            Boolean.parseBoolean(data[12])));
                else if (data[0].equals("chacara"))
                    imoveis.add(new Chacara(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5],
                            Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]),
                            Boolean.parseBoolean(data[9]), Boolean.parseBoolean(data[10]),
                            Boolean.parseBoolean(data[11]), Boolean.parseBoolean(data[12]),
                            Boolean.parseBoolean(data[13])));
                else
                    System.out.println("ERRO : Imóvel inválido.\n");
            }
            txt.close();
        } catch (FileNotFoundException e) {
            System.out.println("ERRO : Arquivo não encontrado.\n");
            e.printStackTrace();
        }
    }

    public static void ordenarCrescente(ArrayList<Imovel> imoveis){
        Collections.sort(imoveis);
    }

    public static ArrayList<Imovel> buscarPorTipo(ArrayList<Imovel> imoveis){
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        int tipo_imovel = 0; // - > placeholder

        switch(tipo_imovel){
            case 1 :
                for (Imovel imovel : imoveis){
                    if (imovel instanceof Casa)
                        resultado.add(imovel);
                }
                break;
            case 2 :
                for (Imovel imovel : imoveis){
                    if (imovel instanceof Apartamento)
                        resultado.add(imovel);
                }
                break;
            case 3 :
                for (Imovel imovel : imoveis){
                    if (imovel instanceof Chacara)
                        resultado.add(imovel);
                }
                break;
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarProprietario(ArrayList<Imovel> imoveis) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getProprietario().equals("#placeholder#"))
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarPrecoMaximo(ArrayList<Imovel> imoveis) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getValor() < 1000000) // - > placeholder
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarCidade(ArrayList<Imovel> imoveis) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getProprietario().equals("#placeholder#"))
                resultado.add(imovel);
        }

        return resultado;
    }

    public static ArrayList<Imovel> buscarQuartos(ArrayList<Imovel> imoveis) {
        ArrayList<Imovel> resultado = new ArrayList<Imovel>();
        for (Imovel imovel : imoveis) {
            if (imovel.getQuartos() < 1000000) // - > placeholder
                resultado.add(imovel);
        }

        return resultado;
    }

    public static void printColecao(ArrayList<Imovel> imoveis) {
        for (Imovel imovel : imoveis)
            System.out.println(imovel.toString());
    }
}