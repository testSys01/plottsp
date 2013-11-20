#include <iostream>
#include <string>

#include <QtGui>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtWidgets>
#endif

#include "view.h"

const std::string helpMessage =
    "Usage: plottsp [ -h | -p ]\n"
    "   -h     Show help message\n"
    "   -p     Expect edges as point pairs (default is sequence)\n"
    "Input is read from standard input";

int main(int argc, char *argv[]) {
    View::EdgeFormat edgeFormat = View::Sequence;

    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg.compare("-p") == 0) {
            edgeFormat = View::Pairs;
        } else if (arg.compare("-h") == 0) {
            std::cout << helpMessage << std::endl;
            return 0;
        } else {
            std::cerr << "Unknown option: " << arg << std::endl;
            std::cerr << helpMessage << std::endl;
            return 1;
        }
    }

    QApplication app(argc, argv);

    QGraphicsScene scene;
    View view(std::cin, edgeFormat, &scene);
    view.show();

    return app.exec();
}
