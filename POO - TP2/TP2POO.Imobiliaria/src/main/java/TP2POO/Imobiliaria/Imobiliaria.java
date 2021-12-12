package TP2POO.Imobiliaria;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class Imobiliaria {
    public static void main (String[] args){
        ArrayList <Imovel> imoveis = new ArrayList <Imovel> ();
        // - > Leitura do arquivo database_imoveis.txt
        try {
            File database_imoveis = new File("database_imoveis.txt");
            Scanner txt = new Scanner(database_imoveis);
            while (txt.hasNextLine()) {
                String imovel = txt.nextLine();
                String[] data = imovel.split(";");
                if (data[0].equals("casa")) // - > Criação do objeto e push_back no vetor polimórfico de imóveis
                    imoveis.add(new Casa(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5], Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]), Integer.parseInt(data[9]), Boolean.parseBoolean(data[10])));
                else if (data[0].equals("apartamento"))
                    imoveis.add(new Apartamento(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5], Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]), Integer.parseInt(data[9]), Float.parseFloat(data[10]), Boolean.parseBoolean(data[11]), Boolean.parseBoolean(data[12])));
                else if (data[0].equals("chacara"))
                    imoveis.add(new Chacara(Float.parseFloat(data[1]), data[2], data[3], data[4], data[5], Integer.parseInt(data[6]), Integer.parseInt(data[7]), Integer.parseInt(data[8]), Boolean.parseBoolean(data[9]), Boolean.parseBoolean(data[10]), Boolean.parseBoolean(data[11]), Boolean.parseBoolean(data[12]), Boolean.parseBoolean(data[13])));
                else System.out.println("ERRO : Imóvel inválido.\n");
            }
            txt.close();
            } catch (FileNotFoundException e) {
            System.out.println("ERRO : Arquivo não encontrado.\n");
            e.printStackTrace();
        }

        for (Imovel imovel : imoveis)
            System.out.println(imovel.toString());
    }
}