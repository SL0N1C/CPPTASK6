#include <cstdint>
#include <fstream>
#include <iostream>
using namespace std;
#pragma pack(push, 1)
struct rar_header {
    uint16_t head_crc;
    uint8_t  head_type;
    uint16_t head_flags;
    uint16_t head_size;
};

struct rar_file_fixed {
    uint32_t pack_size;
    uint32_t unp_size;
    uint8_t  host_os;
    uint32_t file_crc;
    uint32_t file_time;
    uint8_t  unp_ver;
    uint8_t  method;
    uint16_t name_size;
    uint32_t attr;
};
#pragma pack(pop)

int main() {
    std::ifstream in("Example.rar", ios::binary);
    if (!in) return 1;
    in.seekg(7, std::ios::beg);
    while (true) {
        streampos start = in.tellg();
        rar_header h{};
        in.read(reinterpret_cast<char*>(&h), sizeof(h));
        if (!in) break;
        if (h.head_type == 0x74) {
            rar_file_fixed f{};
            in.read(reinterpret_cast<char*>(&f), sizeof(f));
            if (!in) break;
            cout << "FILE_HEAD " << f.pack_size << " " << f.name_size << endl;
        }
        in.seekg(start + (std::streamoff)h.head_size);
        if (!in) break;
    }
    return 0;
}
