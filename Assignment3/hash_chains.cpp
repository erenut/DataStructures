#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>

using std::string;
using std::vector;
using std::deque;
using std::cin;
using std::find;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // create the data structure as vector of deques
    vector< deque<string> > data_;
    // create the hash function
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }
    

	public:

    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count), data_(bucket_count) {}

	// Read the queries from input
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }


	// Add to hash table
	void add_Data(const string &s){
		auto &chain = data_[hash_func(s)]; // get deque corresponding to the hashvalue
		if (find(chain.begin(), chain.end(), s) == chain.end())
			chain.push_front(s);

	}


	// Delete from the hash table
	void delete_Data(const string &s){
		auto &chain = data_[hash_func(s)]; // get deque corresponding to the hashvalue
		auto it = find(chain.begin(), chain.end(), s); // find the element if it is in the chain
		if (it != chain.end())
			chain.erase(it);
	}


	// find the string in the hash table
	bool find_Data(const string &s){
		auto &chain = data_[hash_func(s)]; // get deque corresponding to the hashvalue
		// check if the string is in the chain
		if(find(chain.begin(), chain.end(), s) != chain.end())
			return true;
		return false;
	}


	// Check if the element is in the hashtable
	void check_Data(int key){
		const auto &chain = data_[key];
		if (chain.empty())
			std::cout << " " << std::endl;
		else{
			for(auto element : chain)
				std::cout << element << " "; 
			std::cout << std::endl;
		}

	}


    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {

		if (query.type == "check"){
			check_Data(query.ind);
		}
		else {
            if (query.type == "find")
                writeSearchResult(find_Data(query.s));
            else if (query.type == "add") 
            	add_Data(query.s);
            else if (query.type == "del") 	
            	delete_Data(query.s);
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
