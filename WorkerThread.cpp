#include <QPixmap>
#include <QThread>

class WorkerThread : public QThread
{
public:
    std::function<void()> body;
    WorkerThread(std::function<void()> body) {
        this->body = body;
    }
    void run() override {
        body();
    }
};