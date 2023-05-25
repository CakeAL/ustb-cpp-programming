#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>

namespace Ui {
class GameUI;
}

class GameUI : public QWidget
{
    Q_OBJECT

public:
    explicit GameUI(QWidget *parent = nullptr);
    ~GameUI();
    QWidget *par_widget;

private:
    Ui::GameUI *ui;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void recvGameUI();
    void mainloop();;
};

#endif // GAMEUI_H
