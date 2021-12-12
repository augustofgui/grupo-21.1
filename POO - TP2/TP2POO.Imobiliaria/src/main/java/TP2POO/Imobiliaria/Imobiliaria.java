package TP2POO.Imobiliaria;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Imobiliaria {
    public static void main (String[] args){
        // - > Leitura do arquivo database_imoveis.txt
        try {
            File database_imoveis = new File("database_imoveis.txt");
            Scanner txt = new Scanner(database_imoveis);
            while (txt.hasNextLine()) {
                String imovel = txt.nextLine();
                String[] data = imovel.split(";");
                if (data[0].equals("casa")){ // - > Criação do objeto e push_back no vetor polimórfico de imóveis
                    
                }
                else if (data[0].equals("apartamento")){

                }
                else if (data[0].equals("chacara")){

                }
            }
            txt.close();
            } catch (FileNotFoundException e) {
            System.out.println("ERRO : Arquivo não encontrado.\n");
            e.printStackTrace();
        }
    }
}