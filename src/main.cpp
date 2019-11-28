#include <QtQuick>

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);
    QQuickView view;
    view.source()
    view.show();
    return app.exec();
}
