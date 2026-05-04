public class DisputaConta {
    public static void main(String[] args) throws InterruptedException {
        ContaSemMonitor conta = new ContaSemMonitor();
        int numeroDeThreads = 10;
        Thread[] threads = new Thread[numeroDeThreads];

        System.out.println("Iniciando 10 depósitos de R$100 simultâneos...");

        // Criando e iniciando as threads
        for (int i = 0; i < numeroDeThreads; i++) {
            threads[i] = new Thread(() -> {
                conta.depositar(100);
            });
            threads[i].start();
        }

        // Aguarda todas as threads terminarem (join)
        for (int i = 0; i < numeroDeThreads; i++) {
            threads[i].join();
        }

        System.out.println("--------------------------------------");
        System.out.println("SALDO FINAL ESPERADO: R$ 1000.0");
        System.out.println("SALDO FINAL OBTIDO:   R$ " + conta.getSaldo());
        System.out.println("--------------------------------------");

        if (conta.getSaldo() < 1000) {
            System.out.println("CAOS CONFIRMADO: Houve perda de dados por falta de Monitor!");
        }
    }
}