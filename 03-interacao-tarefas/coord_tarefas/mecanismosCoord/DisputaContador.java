public class DisputaContador {

    public static void main(String[] args) throws InterruptedException {
        ContadorComMonitor contador = new ContadorComMonitor();
//        ContadorSemMonitor contador = new ContadorSemMonitor();

        int totalThreads = 100;
        int incrementosPorThread = 100000;

        Thread[] threads = new Thread[totalThreads];

        for (int i = 0; i < totalThreads; i++) {
            threads[i] = new Thread(() -> {
                for (int j = 0; j < incrementosPorThread; j++) {
                    contador.incrementar();
                }
            });
            threads[i].start();
        }

        // Aguarda todas as threads terminarem (join)
        for (Thread t : threads) {
            t.join();
        }



        System.out.println("Esperado: " + (totalThreads * (long)incrementosPorThread));
        System.out.println("Obtido:   " + contador.getValor());
    }
}
