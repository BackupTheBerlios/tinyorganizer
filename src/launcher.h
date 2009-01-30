#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QList>
#include <QString>
#include <QTranslator>

extern const QString TRANSLATORS_PATH;

class MainWindow;

class Launcher
{
public:
    Launcher();
    virtual ~Launcher();

    void start();

private:
    void setupTranslators();
    bool installTranslatorForLocaleSymbol(const QString & localeSymbol);

private:
    MainWindow * mMainWindow;
    QList<QTranslator*> mTranslators;
};

#endif // LAUNCHER_H
