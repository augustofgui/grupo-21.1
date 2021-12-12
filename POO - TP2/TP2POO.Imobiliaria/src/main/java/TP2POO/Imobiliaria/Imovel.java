package TP2POO.Imobiliaria;
public class Imovel {
    private final float valor;
    private String proprietario, rua, bairro, cidade;
    private int numero, quartos, banheiros;

    public Imovel(float valor, String proprietario, String rua, String bairro, String cidade, int numero, int quartos, int banheiros) {
        this.valor = valor;
        this.proprietario = proprietario;
        this.rua = rua;
        this.bairro = bairro;
        this.cidade = cidade;
        this.numero = numero;
        this.quartos = quartos;
        this.banheiros = banheiros;
    }

    public void setProprietario(String proprietario) {
        this.proprietario = proprietario;
    }
    public void setRua(String rua) {
        this.rua = rua;
    }
    public void setBairro(String bairro) {
        this.bairro = bairro;
    }
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }
    public void setNumero(int numero) {
        this.numero = numero;
    }
    public void setQuartos(int quartos) {
        this.quartos = quartos;
    }
    public void setBanheiros(int banheiros) {
        this.banheiros = banheiros;
    }
    
    public float getValor() {
        return valor;
    }
    public String getProprietario() {
        return proprietario;
    }
    public String getRua() {
        return rua;
    }
    public String getBairro() {
        return bairro;
    }
    public String getCidade() {
        return cidade;
    }
    public int getNumero() {
        return numero;
    }
    public int getQuartos() {
        return quartos;
    }
    public int getBanheiros() {
        return banheiros;
    }

    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: "  + this.getValor()
        + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
        "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\n";
    }
}