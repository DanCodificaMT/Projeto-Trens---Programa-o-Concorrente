#include "trem.h"
#include <QtCore>

QMutex mutex0, mutex1, mutex2, mutex3, mutex4, mutex5, mutex6;
QSemaphore sem(2);

// Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 220;
}

// Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        // Se a velocidade estiver no máximo, espere até ter uma nova atualização na velocidade
        if (this->velocidade == 230) {
            condParada.wait(&mutexParada);
        }
        switch(ID){
        case 1: // Trem 1
            if (y == 30 && x < 460){
                x += 10;
                // Entrando no mutex0
                if (x == 440){
                    sem.acquire(1);
                    mutex0.lock();
                }
            }
            else if (x == 460 && y < 150){
                y += 10;
                // Entrando no mutex2
                if (y == 130){
                    mutex2.lock();
                }
            }
            else if (x > 190 && y == 150){
                x -= 10;
                // Saindo do mutex0
                if (x == 440){
                    mutex0.unlock();
                    sem.release(1);
                }
                // Entrando no mutex1
                if (x == 350){
                    mutex1.lock();
                }
                // Saindo do mutex2
                if (x == 310){
                    mutex2.unlock();
                }
            } else {
                y -= 10;
                // Saindo do mutex1
                if (y == 130){
                    mutex1.unlock();
                }
            }
            emit updateGUI(ID, x, y); // Emite um sinal
            break;

        case 2: // Trem 2
            if (y == 30 && x < 730){
                x += 10;
                // Saindo do mutex0
                if (x == 480){
                    mutex0.unlock();
                }
            } else if (x == 730 && y < 150){
                y += 10;
                // Entrando no mutex4
                if (y == 130){
                    mutex4.lock();
                }
            } else if (x > 460 && y == 150) {
                x -= 10;
                // Entrando no mutex3
                if (x == 620){
                    sem.acquire(1);
                    mutex3.lock();
                }
                // Saindo do mutex4
                if (x == 580){
                    mutex4.unlock();
                }
                // Entrando no mutex0
                if (x == 480){
                    mutex0.lock();
                }
            } else {
                y -= 10;
                // Saindo do mutex3
                if (y == 130){
                    mutex3.unlock();
                    sem.release(1);
                }
            }

            emit updateGUI(ID, x, y); // Emite um sinal
            break;

        case 3: // Trem 3
            if (y == 150 && x < 330){
                x += 10;
                // Entrando no mutex1
                if (x == 170){
                    mutex5.lock();
                    mutex1.lock();
                }
            } else if (x == 330 && y < 270){
                y += 10;
                // Saindo do mutex1
                if (y == 170){
                    mutex1.unlock();
                }
            } else if (x > 60 && y == 270){
                x -= 10;
                // Saindo do mutex5
                if (x == 310){
                    mutex5.unlock();
                }
            } else {
                y -= 10;
            }
            emit updateGUI(ID, x, y); // Emite um sinal
            break;

        case 4: // Trem 4
            if (y == 150 && x < 600){
                x += 10;
                // Saindo do mutex5
                if (x == 350){
                    mutex5.unlock();
                }
                // Entrando no mutex3
                if (x == 440){
                    mutex3.lock();
                }
                // Saindo do mutex2
                if (x == 480){
                    mutex2.unlock();
                    sem.release(1);
                }
                // Entrando no mutex6
                if (x == 580){
                    mutex6.lock();
                }
            } else if (x == 600 && y < 270){
                y += 10;
                // Saindo do mutex3
                if (x == 600 && y == 170){
                    mutex3.unlock();
                }
            } else if (x > 330 && y == 270){
                x -= 10;
                // Saindo do mutex6
                if (x == 580){
                    mutex6.unlock();
                }
                // Entrando no mutex5
                if (x == 350){
                    mutex5.lock();
                }
            } else {
                y -= 10;
                // Entrando no mutex2
                if (y == 170){
                    sem.acquire(1);
                    mutex2.lock();
                }
            }
            emit updateGUI(ID, x, y); // Emite um sinal
            break;

        case 5: // Trem 5
            if (y == 150 && x < 830){
                x += 10;
                // Saindo do mutex6
                if (x == 620){
                    mutex6.unlock();
                }
                // Saindo do mutex4
                if (x == 750){
                    mutex4.unlock();
                }
            } else if (x == 830 && y < 270){
                y += 10;
            } else if (x > 600 && y == 270){
                x -= 10;
                // Entrando no mutex6
                if (x == 620){
                    mutex4.lock();
                    mutex6.lock();
                }
            } else {
                y -= 10;
            }
            emit updateGUI(ID, x, y); // Emite um sinal
            break;

        default:
            break;
        }
        msleep(this->velocidade);
    }
}

// Função para atualizar a velocidade do trem
void Trem::atualizarVelocidade(int velocidade){
    this->velocidade = 230 - velocidade;
}

// Função que manda um sinal pro trem sair do wait()
void Trem::startTrem() {
    condParada.wakeAll();
}

// Função que libera todos os mutex
void Trem::desbloquearMutexes() {
    // Usando QMutexLocker para garantir que os mutexes sejam desbloqueados quando a aplicação for fechada
    QMutexLocker locker0(&mutex0);
    QMutexLocker locker1(&mutex1);
    QMutexLocker locker2(&mutex2);
    QMutexLocker locker3(&mutex3);
    QMutexLocker locker4(&mutex4);
    QMutexLocker locker5(&mutex5);
    QMutexLocker locker6(&mutex6);
}

