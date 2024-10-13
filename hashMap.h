#pragma once
#include <vector>
#include <iostream>

class hashMap
{
public:
    std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> map{10};
    int capacity = map.capacity();
    int size = 0;

    int hash(std::string& key);
    bool search(std::string key);
    void insert(std::string key, std::vector<std::string> values);
    void resizeAndRehash(int newCapacity);
    std::vector<std::pair<std::string, std::vector<std::string>>> compare(std::string rating, std::string year, std::string duration);
};