package TP2POO.Imobiliaria;
public class Casa extends Imovel {
    private int andares;
    private boolean sala_jantar;

    public Casa(float valor, String proprietario, String rua, String bairro, String cidade, int numero, int quartos, int banheiros, int andares, boolean sala_jantar) {
        super(valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros);
        this.andares = andares;
        this.sala_jantar = sala_jantar;
    }

    public void setAndares(int andares) {
        this.andares = andares;
    }
    public void setSala_jantar(boolean sala_jantar) {
        this.sala_jantar = sala_jantar;
    }

    public int getAndares() {
        return andares;
    }
    public boolean isSala_jantar() {
        return sala_jantar;
    }
    
    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: "  + this.getValor()
        + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
        "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\nAndares: " + this.getAndares() + "\n";
    }
}
