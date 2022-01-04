package TP2POO.Imobiliaria;

// Classe derivada do Imovel
public class Casa extends Imovel {
    
    // Variáveis
    private int andares;
    private boolean sala_jantar;

    // Construtor da classe
    public Casa(float valor, String proprietario, String rua, String bairro, String cidade, int numero, int quartos,
            int banheiros, int andares, boolean sala_jantar) {
        super(valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros);
        this.andares = andares;
        this.sala_jantar = sala_jantar;
    }

    // Setter
    public void setAndares(int andares) {
        this.andares = andares;
    }

    public void setSala_jantar(boolean sala_jantar) {
        this.sala_jantar = sala_jantar;
    }

    // Getter
    public int getAndares() {
        return andares;
    }

    // Retorna true caso exista sala de jantar
    public boolean isSala_jantar() {
        return sala_jantar;
    }

    // Sobrecarga do operador toString
    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: " + this.getValor()
                + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
                "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\nAndares: " + this.getAndares()
                + "\n";
    }

    // Sobrecarga do operador toWrite
    @Override
    public String toWrite() {
        return "casa;" + this.getValor() + ";" + this.getProprietario() + ";" + this.getRua() + ";"
                + this.getBairro() + ";" + this.getCidade() + ";" + this.getNumero() + ";" + this.getQuartos()
                + ";" + this.getBanheiros() + ";" + this.getAndares() + ";"
                + booleanToInt(this.isSala_jantar()) + ";\n";
    }
}
