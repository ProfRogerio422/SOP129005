public class MainMonitor {
    public static void main(String[] args) throws InterruptedException {
        ContaComMonitor conta = new ContaComMonitor();
        int numeroDeThreads = 10;
        Thread[] threads = new Thread[numeroDeThreads];

        System.out.println("Iniciando 10 depósitos sincronizados (Monitor ativo)...");

        for (int i = 0; i < numeroDeThreads; i++) {
            threads[i] = new Thread(() -> {
                conta.depositar(100);
            }, "Thread-" + (i + 1));
            threads[i].start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("--------------------------------------");
        System.out.println("SALDO FINAL ESPERADO: R$ 1000.0");
        System.out.println("SALDO FINAL OBTIDO:   R$ " + conta.getSaldo());
        System.out.println("--------------------------------------");

        if (conta.getSaldo() == 1000) {
            System.out.println("SUCESSO: O Monitor garantiu a integridade dos dados!");
        }
    }
}