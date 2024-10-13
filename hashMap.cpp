#include "hashMap.h"

// Time Complexity: O(1)
int hashMap::hash(std::string &key)
{
    return key.length() % capacity;
}

// Time Complexity: O(n) where n is the number of keys in the bucket
bool hashMap::search(std::string key)
{
    int bucketIndex = hash(key);
    for(auto element:map[bucketIndex])
    {
        if(element.first == key)
        {
            return true;
        }
    }
    return false;
}

// Time Complexity: O(1);
void hashMap::insert(std::string key, std::vector<std::string> values)
{
    if(size >= capacity * 0.75)
    {
        resizeAndRehash(capacity * 2);
    }
    int bucketIndex = hash(key);
    if(search(key))
    {
        return;
    }
    std::pair<std::string, std::vector<std::string>> pair(key, values);
    map[bucketIndex].push_back(pair);
    size++;
}

// Time Complexity: O(n * m) where n is the number of elements in the bucket and m is the number of
// keys in each bucket.
void hashMap::resizeAndRehash(int newCapacity)
{
    std::vector<std::vector<std::pair<std::string, std::vector<std::string>>>> newMap(newCapacity);
    for(auto bucket:map)
    {
        for(auto key:bucket)
        {
            int newBucketIndex = hash(key.first);
            std::pair<std::string, std::vector<std::string>> pair(key.first, key.second);
            newMap[newBucketIndex].push_back(pair);
        }
    }
    map = newMap;
    capacity = newCapacity;
}

// Time Complexity: O(n*m) where n is the number of buckets and m the number of keys
// because each bucket's keys are being searched to find possible matches for the criteria.
std::vector<std::pair<std::string, std::vector<std::string>>> hashMap::compare(std::string rating, std::string year, std::string duration)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> results;
    for(auto it:map)
    {
        for(auto bit:it)
        {
            if(bit.second[0] != "" && bit.second[2] != "")
            {
                if(std::stod(bit.second[0]) >= std::stod(rating) && bit.second[1] >= year && bit.second[2] <= duration)
                {
                    results.push_back(bit);
                }
            }

        }
    }
    return results;
}
