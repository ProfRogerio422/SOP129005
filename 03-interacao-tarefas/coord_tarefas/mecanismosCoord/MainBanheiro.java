public class MainBanheiro {
    public static void main(String[] args) {
        Banheiro banheiro = new Banheiro();

        // Criando 6 pessoas para disputar 3 cabines
        for (int i = 1; i <= 6; i++) {
            String nomePessoa = "Pessoa-" + i;

            new Thread(() -> {
                try {
                    // 1. Tenta entrar (pode ficar na fila)
                    banheiro.entrar();

                    // 2. Simula o uso do banheiro (tempo aleatório)
                    long tempoUso = (long) (Math.random() * 3000 + 1000);
                    Thread.sleep(tempoUso);

                    // 3. Sai e libera a cabine
                    banheiro.sair();

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }, nomePessoa).start();
        }
    }
}