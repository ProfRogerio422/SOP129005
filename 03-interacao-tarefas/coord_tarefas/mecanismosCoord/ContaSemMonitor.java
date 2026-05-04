class ContaSemMonitor {
    private double saldo = 0;

    // SEM synchronized - Aberto para disputa
    public void depositar(double valor) {
        try {
            // Passo 1: Lê o saldo (Janela de perigo)
            double saldoLido = this.saldo;

            // Passo 2: Força uma troca de contexto (usleep do C)
            Thread.sleep(0);

            // Passo 3: Modifica e grava
            this.saldo = saldoLido + valor;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public double getSaldo() {
        return saldo;
    }
}