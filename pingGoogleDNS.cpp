// by grey-olli@ya.ru , based on stackoverflow & book samples. GNU GPL v2

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <QApplication>
#include <QLabel>
#include <QtWidgets>
 
 std::string execute(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE,decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

 
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QWidget wdgt;
    QWidget *pwdgt = new QWidget(&wdgt);
     pwdgt->setWindowFlags(Qt::Window|Qt::WindowTitleHint |Qt::WindowStaysOnTopHint);
    
    QVBoxLayout* pbxLayout = new QVBoxLayout();  
    pbxLayout->addWidget(pwdgt);

   std::string returned = execute("ping -c 3 8.8.8.8");
   QLabel *plabel = new QLabel(returned.c_str()); 
    pbxLayout->addWidget(plabel);

    wdgt.setLayout(pbxLayout);
    wdgt.show();
    return app.exec();
}

#include <pingGoogleDNS.cpp.moc>