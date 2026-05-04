class ContaComMonitor {
    private double saldo = 0;

    // COM synchronized - O Monitor está ativo!
    public synchronized void depositar(double valor) {
        try {
            // Passo 1: Lê o saldo com exclusividade
            double saldoLido = this.saldo;

            // Passo 2: Mesmo dormindo, a thread NÃO solta o cadeado
            Thread.sleep(0);

            // Passo 3: Atualiza o valor com segurança
            this.saldo = saldoLido + valor;
            System.out.println(Thread.currentThread().getName() + " depositou. Saldo atual: " + this.saldo);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    // Consulta de saldo também precisa ser sincronizada para evitar leitura de dados parciais
    public synchronized double getSaldo() {
        return saldo;
    }
}