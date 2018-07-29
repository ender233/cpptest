#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

struct FileDeleter {
    void operator()(FILE *fp) const {
        std::cout << "FileDeleter\n";
        std::fclose(fp);
    }
};

class MyFile {
public:
    MyFile(std::string file) {
        fp_ = std::fopen(file.c_str(), "r");
    }
    ~MyFile() {
        std::cout << "MyFile close\n";
        std::fclose(fp_);
    }
private:
    FILE *fp_;
};

int main() {
    {
        FILE *fp = std::fopen("test.txt", "r");
        if(!fp) {
            std::cout << "File fopenning failed\n";
        }
        std::cout << "FILE close\n";
        std::fclose(fp);
    }
    {
        std::shared_ptr<FILE> fp(std::fopen("test.txt", "r"), FileDeleter());
    }
    {
        std::shared_ptr<MyFile> fp(new MyFile("test.txt"));
    }
}
