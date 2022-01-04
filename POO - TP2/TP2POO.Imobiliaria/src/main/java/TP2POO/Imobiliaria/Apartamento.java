package TP2POO.Imobiliaria;

// Classe derivada do Imovel
public class Apartamento extends Imovel {

    // Variáveis
    private int andar;
    private float taxa_condominio;
    private boolean elevador, sacada;

    // Construtor da classe
    public Apartamento(float valor, String proprietario, String rua, String bairro, String cidade, int numero,
            int quartos, int banheiros, int andar, float taxa_condominio, boolean elevador, boolean sacada) {
        super(valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros);
        this.andar = andar;
        this.taxa_condominio = taxa_condominio;
        this.elevador = elevador;
        this.sacada = sacada;
    }

    // Setter
    public void setAndar(int andar) {
        this.andar = andar;
    }

    public void setTaxa_condominio(float taxa_condominio) {
        this.taxa_condominio = taxa_condominio;
    }

    public void setElevador(boolean elevador) {
        this.elevador = elevador;
    }

    public void setSacada(boolean sacada) {
        this.sacada = sacada;
    }

    // Getters
    public int getAndar() {
        return andar;
    }

    public float getTaxa_condominio() {
        return taxa_condominio;
    }

    // Retorna true caso exista elevador
    public boolean isElevador() {
        return elevador;
    }

    // Retorna true caso exista sacada
    public boolean isSacada() {
        return sacada;
    }

    // Sobrecarga do operador toString
    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: " + this.getValor()
                + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
                "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\nElevador: " + this.isElevador()
                + "\n";
    }

    // Sobrecarga do operador toWrite
    @Override
    public String toWrite() {
        return "apartamento;" + this.getValor() + ";" + this.getProprietario() + ";" + this.getRua() + ";"
                + this.getBairro() + ";" + this.getCidade() + ";" + this.getNumero() + ";" + this.getQuartos()
                + ";" + this.getBanheiros() + ";" + this.getAndar() + ";"
                + this.getTaxa_condominio() + ";" + booleanToInt(this.isElevador())
                + ";" + booleanToInt(this.isSacada()) + ";\n";
    }
}
