#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push, 1)
struct rar_header {
    unsigned short head_crc;
    unsigned char  head_type;
    unsigned short head_flags;
    unsigned short head_size;
};
#pragma pack(pop)

int main() {
    ifstream in("Example.rar", ios::binary);
    if (!in) return 1;
    in.seekg(7, ios::beg);
    while (true) {
        rar_header h;
        in.read((char*)&h, sizeof(h));
        if (!in) break;
        cout << (int)h.head_type << " " << h.head_size << endl;
        in.seekg((int)h.head_size - (int)sizeof(rar_header), ios::cur);
        if (!in) break;
    }
    return 0;
}
