class Banheiro {
    private int cabinesLivres = 3;

    public synchronized void entrar() throws InterruptedException {
        String nome = Thread.currentThread().getName();

        // Enquanto não houver cabine, a pessoa espera na porta (sala de espera)
        while (cabinesLivres == 0) {
            System.out.println(nome + " está esperando na fila...");
            wait();
        }

        cabinesLivres--;
        System.out.println(nome + " ENTROU. Cabines livres: " + cabinesLivres);
    }

    public synchronized void sair() {
        String nome = Thread.currentThread().getName();
        cabinesLivres++;
        System.out.println(nome + " SAIU. Cabines livres: " + cabinesLivres);

        // Avisa quem está na fila que uma cabine liberou
        notifyAll();
    }
}