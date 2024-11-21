#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View window;
  window.show();
  window.debugValues();
  return a.exec();
}
