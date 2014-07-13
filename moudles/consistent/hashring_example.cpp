#include <map>
#include <string>
#include <iostream>

#include "consistent.h"

struct SdbmHash
{
	size_t operator()(const char * str) const
	{
		size_t hash = 0;
		int c;

		while ((c = *str++)) {
			hash = c + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}
};

class CacheServer
{
public:
	typedef std::map<std::string, std::string> StringMap;

	void Put(const std::string& key, const std::string& value)
	{
		cache_[key] = value;
	}

	std::string Get(const std::string& key) const
	{
		std::string value;
		StringMap::const_iterator it = cache_.find(key);
		if (it != cache_.end()) {
			value = it->second;
		}
		return value;
	}

	void Remove(const std::string& key)
	{
		StringMap::iterator it = cache_.find(key);
		if (it != cache_.end()) {
			cache_.erase(it);
		}
	}

private:
	StringMap cache_;
};

int main()
{
	typedef std::map<std::string, CacheServer> ServerMap;
	ServerMap servers;
	Consistent::HashRing<std::string, std::string, SdbmHash> ring(4, SdbmHash());

	// Create some cache servers
	servers["cache1.example.com"] = CacheServer();
	servers["cache2.example.com"] = CacheServer();
	servers["cache3.example.com"] = CacheServer();

	// Add their host names to the hash ring
	for (ServerMap::const_iterator it = servers.begin(); it != servers.end(); ++it) {
		std::cout << "Adding " << it->first << " with hash " << ring.AddNode(it->first) << std::endl;
	}

	// Store some data
	const char* fruits[] = {"apple", "pear", "banana", "orange", "cherry", "apricot"};
	const char* colours[] = {"red", "green", "yellow", "orange", "black", "pink"};
	const unsigned int numfruits = sizeof(fruits) / sizeof(numfruits);
	for (unsigned int f = 0; f < numfruits; f++) {
		std::string host = ring.GetNode(fruits[f]);
		std::cout << "Storing " << fruits[f] << " on server " << host << std::endl;
		servers[host].Put(fruits[f], colours[f]);
	}

	// Read it back
	for (unsigned int f = 0; f < numfruits; f++) {
		std::string host = ring.GetNode(fruits[f]);
		std::string colour = servers[host].Get(fruits[f]);
		std::cout << "Found " << fruits[f] << " on server " << host << " (" << colour << ")" << std::endl;
	}

	return 0;
}
