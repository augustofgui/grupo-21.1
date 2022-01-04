package TP2POO.Imobiliaria;

// Classe derivada do Imovel
public class Chacara extends Imovel {

    // Variáveis
    private boolean salao_festa, salao_jogos, campo_futebol, churrasqueira, piscina;

    // Construtor da classe
    public Chacara(float valor, String proprietario, String rua, String bairro, String cidade, int numero, int quartos,
            int banheiros, boolean salao_festa, boolean salao_jogos, boolean campo_futebol, boolean churrasqueira,
            boolean piscina) {
        super(valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros);
        this.salao_festa = salao_festa;
        this.salao_jogos = salao_jogos;
        this.campo_futebol = campo_futebol;
        this.churrasqueira = churrasqueira;
        this.piscina = piscina;
    }

    // Setter
    public void setSalao_festa(boolean salao_festa) {
        this.salao_festa = salao_festa;
    }

    public void setSalao_jogos(boolean salao_jogos) {
        this.salao_jogos = salao_jogos;
    }

    public void setCampo_futebol(boolean campo_futebol) {
        this.campo_futebol = campo_futebol;
    }

    public void setChurrasqueira(boolean churrasqueira) {
        this.churrasqueira = churrasqueira;
    }

    public void setPiscina(boolean piscina) {
        this.piscina = piscina;
    }

    // Funções que retornam true caso exista a respectiva caracteristica
    public boolean isSalao_festa() {
        return salao_festa;
    }

    public boolean isSalao_jogos() {
        return salao_jogos;
    }

    public boolean isCampo_futebol() {
        return campo_futebol;
    }

    public boolean isChurrasqueira() {
        return churrasqueira;
    }

    public boolean isPiscina() {
        return piscina;
    }

    // Sobrecarga do operador toString
    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: " + this.getValor()
                + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
                "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\nPiscina: " + this.isPiscina()
                + "\n";
    }

    // Sobrecarga do operador toWrite
    @Override
    public String toWrite() {
        return "chacara;" + this.getValor() + ";" + this.getProprietario() + ";" + this.getRua() + ";"
                + this.getBairro() + ";" + this.getCidade() + ";" + this.getNumero() + ";" + this.getQuartos()
                + ";" + this.getBanheiros() + ";" + booleanToInt(this.isSalao_festa()) + ";"
                + booleanToInt(this.isSalao_jogos()) + ";"
                + booleanToInt(this.isCampo_futebol()) + ";"
                + booleanToInt(this.isChurrasqueira()) + ";"
                + booleanToInt(this.isPiscina()) + ";\n";
    }
}
