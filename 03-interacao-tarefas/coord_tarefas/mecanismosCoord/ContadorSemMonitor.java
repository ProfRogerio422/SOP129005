class ContadorSemMonitor {
    private int valor = 0;

    // Sem sincronização: várias threads incrementam ao mesmo tempo
    public void incrementar() {
        valor++;
    }

    public int getValor() {
        return valor;
    }
}