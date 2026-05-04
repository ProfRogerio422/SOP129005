class ContadorComMonitor {
    private int valor = 0;

    // A palavra-chave 'synchronized' ativa o Monitor do objeto.
    // Garante que apenas UMA thread por vez execute este método.
    public synchronized void incrementar() {
        valor++;
    }

    // Consulta de valor também precisa ser sincronizada para evitar leitura de dados parciais
    public synchronized int getValor() {
        return valor;
    }
}


