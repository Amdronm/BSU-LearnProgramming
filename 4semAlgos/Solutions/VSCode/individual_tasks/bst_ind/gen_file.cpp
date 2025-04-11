#include <fstream>
#include <ctime>
#include <cstdlib>

int main(int argc, char* argv[]) {
    std::srand(time(NULL));
    int size = std::atoi(argv[1]);
    std::ofstream fout("tst.in");
    for (size_t i = 0; i < size; i++) {
        fout << rand() * rand() % 2000000 - 1000000 << "\n";
    }
    fout.close();
    return 0;
}