package TP2POO.Imobiliaria;
public class Chacara extends Imovel {
    private boolean salao_festa, salao_jogos, campo_futebol, churrasqueira, piscina;

    public Chacara(float valor, String proprietario, String rua, String bairro, String cidade, int numero, int quartos, int banheiros, boolean salao_festa, boolean salao_jogos, boolean campo_futebol, boolean churrasqueira, boolean piscina) {
        super(valor, proprietario, rua, bairro, cidade, numero, quartos, banheiros);
        this.salao_festa = salao_festa;
        this.salao_jogos = salao_jogos;
        this.campo_futebol = campo_futebol;
        this.churrasqueira = churrasqueira;
        this.piscina = piscina;
    }

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
    
    @Override
    public String toString() {
        return "    Proprietário: " + this.getProprietario() + "\nValor: "  + this.getValor()
        + "\nNúmero de quartos: " + this.getQuartos() + "\nRua: " + this.getRua() +
        "\nBairro: " + this.getBairro() + "\nCidade: " + this.getCidade() + "\nPiscina: " + this.isPiscina() + "\n";
    }
}
