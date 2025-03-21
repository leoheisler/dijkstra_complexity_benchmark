#include <unordered_map>
#include <iostream>
int main(){
    std::unordered_map<int,int> map;

    std::cout << "AAAAAAAAAA";
    map[10] = 20;
    if (map.count(10))
        std::cout << "da bom mano";
    else
        std::cout << "nn da bom mano";
    return 0;
}