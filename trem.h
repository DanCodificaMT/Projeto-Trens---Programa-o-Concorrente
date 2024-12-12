#ifndef TREM_H
#define TREM_H

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QSemaphore>
#include <QWaitCondition>

/*
 * Classe Trem herda QThread
 * Classe Trem passa a ser uma thread.
 * A função START inicializa a thread. Após inicializada, a thread irá executar a função RUN.
 * Para parar a execução da função RUN da thread, basta executar a função TERMINATE.
 *
*/
class Trem: public QThread{
 Q_OBJECT
public:
    Trem(int,int,int);  //construtor
    void run();         //função a ser executada pela thread
    void atualizarVelocidade(int); //função que atualiza a velocidade do trem
    void startTrem(); //função que bota o trem para andar de novo depois de parado
    void desbloquearMutexes();


//Cria um sinal
signals:
    void updateGUI(int,int,int);

private:
   int x;           //posição X do trem na tela
   int y;           //posição Y do trem na tela
   int ID;          //ID do trem
   int velocidade;  //Velocidade. É o tempo de dormir em milisegundos entre a mudança de posição do trem
   QMutex mutexParada;
   QWaitCondition condParada;
};

#endif // TREM_H
