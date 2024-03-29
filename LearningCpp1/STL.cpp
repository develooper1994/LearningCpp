#include "STL.h"
#include "Integer.h"


namespace stl_containers {
	/*
	Container Types
	Sequential = array(static array), vector(dynamic array), deque, list(linked list 2 direction), forward_list(linked list 1 direction)
	Associative = set(not repeated, sorted, binary tree), multiset(repeated, sorted, binary tree), map(not repeated, sorted, key-value pairs), multimap(repeated, sorted, key-value pairs)
	Unordered = unordered_set, unordered_multi_set | unordered_map, unordered_multi_map

	Note:
	* Associative requires a comparison operator
	* Unordered requires a hash function

	Note: complexity of operations are different!!!
	*NA   = not provided
	*O(1) = not
	Container								operator[]			push_back			pop_back			insert				erase				find				sort
	array									|O(1)				|					|					|					|					|O(n)				|O(log n)
	vector									|O(1)				|O(1)				|O(1)				|O(n)				|O(n)				|O(n)				|O(log n)
	deque									|O(1)				|O(1)*				|O(1)*				|O(n)				|O(n)				|O(n)				|O(log n)
	list									|NA					|O(1)				|O(1)				|O(1)				|O(1)				|O(n)				|O(log n)
	forward_list							|NA					|NA*				|NA*				|O(1)				|O(1)				|O(n)				|NA
	set/multiset							|NA					|NA					|NA					|O(log n)			|O(log n)			|O(log n)			|NA
	map/multi_map							|NA					|NA					|NA					|O(log n)			|O(log n)			|O(log n)			|NA
	unordered_set/unordered_map				|NA					|NA					|NA					|O(1)				|O(1)				|O(1)				|NA
	unordered_multiset/unordered_multimap	|NA					|NA					|NA					|O(1)				|O(1)				|O(1)				|NA

	* Use vector for random access, but not insertion/deletion
	* deque is preferable when elements need to be inserted and removed from both the ends
	* Use list if frequent insertions/deletions are required
		* Use forward_list for memory constrained systems
	* Use associative containers if loop up/search is important
	* Favour unordered containers if elements need not be ordered, else use set/map

	*/
	namespace Sequential {
		void stdArray() {
			/*
			* coverage of c style arrays
			* provides standard access patterns.
			* It is static
			*/
			std::cout << "\n-*-*-*-*-* stdArray *-*-*-*-*-\n";
			std::array<int, 5> arr;
			//subscript
			for (size_t i = 0; i < arr.size(); ++i) {
				arr[i] = i;
			}
			//iterator
			for (auto x : arr) {
				std::cout << x << " ";
			}
			std::cout << "\n";
			auto data_ptr = arr.data();

			auto itrBegin = arr.begin(); //arr[0]
			auto itrEnd = arr.end(); //arr[arr.size()-1]
			for (; itrBegin < itrEnd; ++itrBegin)
			{
				std::cout << *itrBegin << " ";
			}
		}
		void stdVector() {
			/*
			* Behaves like a dynamic array(You can threat like static array)
			* Grows automatically
			* Efficient for addition/removal at the end
			* Provides random access
			* Not good for insertion/deletion
			*/
			std::cout << "\n-*-*-*-*-* stdVector *-*-*-*-*-\n";
			std::vector<int> coll{ 1,2,3,4 }; // std::vector<int, <allocator>> arr;
			//subscript
			for (size_t i = 0; i < 5; ++i) {
				coll.push_back(i * 10);
				std::cout << coll.size() << '\n';
			}
			//iterator
			auto itr = coll.begin();
			for (auto x : coll) {
				std::cout << x << " ";
			}
			std::cout << "\n";
			auto data_ptr = coll.data();

			for (size_t i = 0; i < coll.size(); i++) {
				coll[i] *= coll[i];
				std::cout << coll[i] << '\n';
			}
			coll.insert(coll.begin(), 700);
			coll.erase(coll.end() - 5);
			coll.pop_back();

			auto itrBegin = coll.begin(); //arr[0]
			auto itrEnd = coll.end(); //arr[arr.size()-1]
			for (; itrBegin < itrEnd; ++itrBegin)
			{
				std::cout << *itrBegin << " ";
			}
		}
		void stdDeque() {
			/*
			* Grows automatically
			* Efficient for addition/removal at the both ends
			* Provides random access
			* Not good for insertion/deletion
			*/
			std::cout << "\n-*-*-*-*-* stdDeque *-*-*-*-*-\n";
			std::deque<int> coll{ 1,2,3,4 }; // std::vector<int, <allocator>> arr;
			//subscript
			for (size_t i = 0; i < 5; ++i) {
				coll.push_back(i * 10);
				std::cout << coll.size() << '\n';
			}
			for (size_t i = 0; i < 5; ++i) {
				coll.push_front(i * 10);
				std::cout << coll.size() << '\n';
			}
			//iterator
			auto itr = coll.begin();
			for (auto x : coll) {
				std::cout << x << " ";
			}
			std::cout << "\n";
			//auto data_ptr = coll.data();

			for (size_t i = 0; i < coll.size(); i++) {
				coll[i] *= coll[i];
				std::cout << coll[i] << '\n';
			}
			coll.insert(coll.begin(), 700);
			coll.erase(coll.end() - 5);
			coll.pop_back();

			auto itrBegin = coll.begin(); //arr[0]
			auto itrEnd = coll.end(); //arr[arr.size()-1]
			for (; itrBegin < itrEnd; ++itrBegin)
			{
				std::cout << *itrBegin << " ";
			}
		}
		void stdList() {
			/*
			* Implemented as a two-way linked list
			* Efficient for insertion/deletion at the both ends
			* Does not provide random access(use iterators)
			*/
			std::cout << "\n-*-*-*-*-* stdList *-*-*-*-*-\n";
			std::list<int> coll{ 1,2,3,4 }; // std::vector<int, <allocator>> arr;
			//subscript
			for (size_t i = 0; i < 5; ++i) {
				coll.push_back(i * 10);
				coll.push_front(i * 10);
				std::cout << coll.size() << '\n';
			}
			//iterator
			auto itr = coll.begin();
			for (auto x : coll) {
				std::cout << x << " ";
			}
			std::cout << "\n";
			//auto data_ptr = coll.data();

			//for (size_t i = 0; i < coll.size(); i++) {
			//	coll[i] *= coll[i];
			//	std::cout << coll[i] << '\n';
			//}
			coll.insert(coll.begin(), 700);
			coll.erase(coll.begin());
			coll.pop_back();
			coll.pop_front();

			auto itrBegin = coll.begin(); //arr[0]
			auto itrEnd = coll.end(); //arr[arr.size()-1]
			for (; itrBegin != itrEnd; ++itrBegin) {
				std::cout << *itrBegin << " ";
			}
		}
		void stdForwardList() {
			/*
			* Implemented as a one-way linked list
			* Elements are added at the front
			* Small memory-footprint
			* Efficient for insertion/deletion
			* Does not provide support for size
			* Does not provide random access(use iterators)
			*/
			std::cout << "\n-*-*-*-*-* stdForwardList *-*-*-*-*-\n";
			std::forward_list<int> coll{ 1,2,3,4 }; // std::vector<int, <allocator>> arr;
			//subscript
			for (size_t i = 0; i < 5; ++i) {
				//coll.push_back(i * 10);
				coll.push_front(i * 10);
				//std::cout << coll.size() << '\n';
			}
			//iterator
			auto itr = coll.begin();
			for (auto x : coll) {
				std::cout << x << " ";
			}
			std::cout << "\n";
			//auto data_ptr = coll.data();

			//for (size_t i = 0; i < coll.size(); i++) {
			//	coll[i] *= coll[i];
			//	std::cout << coll[i] << '\n';
			//}
			coll.insert_after(coll.begin(), 700); // inserted at the second position("coll.begin()+1")
			coll.erase_after(coll.begin()); // erased at the second position("coll.begin()+1")
			//coll.pop_back();
			coll.pop_front();

			auto itrBegin = coll.begin(); //arr[0]
			auto itrEnd = coll.end(); //arr[arr.size()-1]
			for (; itrBegin != itrEnd; ++itrBegin) {
				std::cout << *itrBegin << " ";
			}
		}
		void Sequential_main() {
			std::cout << "\n-*-*-*-*-* Sequential_main *-*-*-*-*-\n";
			stdArray();
			stdVector();
			stdDeque();
			stdList();
			stdForwardList();
		}
	}

	namespace Associative {
		// Ordered Associative
		void stlSet() {
			/*
			* Implemented as a binary tree
			* Elements are stored in sorted order(< & >)
			* Value acts as key
			* Efficient for fast search and lookup
			* No random access
			* Elements cannot be modified directly
			* Default sorting order is descending. (operator<)
			Not: set doesn't allow duplicates |but multiset does.
			*/
			std::cout << "\n-*-*-*-*-* stlSet *-*-*-*-*-\n";
			{
				//std::set<int> s{ 8,2,0,9,5 };   // std::set<int, <comparision operator that the set will use for sorting(default=std::less<int>)>, allocator>
				std::set<int, std::greater<int>> s{ 8,2,0,9,5 };   // std::set<int, <comparision operator that the set will use for sorting>, allocator>
				s.insert(1);
				s.insert(3);
				s.insert(3);
				s.insert(3);

				auto itrBegin = s.begin();
				// *itrBegin = 1; // !!! ERROR !!!
				auto itrEnd = s.end();
				while (itrBegin != itrEnd) {
					std::cout << *itrBegin++ << '\n';
				}
				s.erase(0);
				s.erase(s.begin());
				//s.erase(s.begin() + 1);
				auto itr = s.begin();
				std::advance(itr, 1);
				s.erase(itr);
				// associative containers provides find
				itr = s.find(5);
				auto result = itr != s.end() ? "Found" : "Not found";
				std::cout << result << '\n';
			}




			std::cout << "\n-*-*-*-*-* stlMultiSet *-*-*-*-*-\n";
			{
				//std::multiset<int> s{ 8,2,0,9,5 };   // std::set<int, <comparision operator that the set will use for sorting(default=std::less<int>)>, allocator>
				std::multiset<int, std::greater<int>> s2{ 8,2,0,9,5 };   // std::set<int, <comparision operator that the set will use for sorting>, allocator>
				s2.insert(1);
				s2.insert(3);
				s2.insert(3);
				s2.insert(3);

				auto itrBegin2 = s2.begin();
				// *itrBegin = 1; // !!! ERROR !!!
				auto itrEnd2 = s2.end();
				while (itrBegin2 != itrEnd2) {
					std::cout << *itrBegin2++ << '\n';
				}
				s2.erase(0);
				s2.erase(s2.begin());
				//s.erase(s2.begin() + 1);
				auto itr2 = s2.begin();
				std::advance(itr2, 1);
				s2.erase(itr2);
				// associative containers provides find
				auto itr = s2.find(5);
				auto result1 = itr != s2.end() ? "Found" : "Not found";
				std::cout << result1 << '\n';

				auto found = s2.equal_range(3);
				while (found.first != found.second) {
					std::cout << *found.first++ << '\n';
				}
			}
		}
		void stlMap() {
			/*
			* Efficient for fast search and lookup
			* Implemented as a binary tree with (value-key) pairs
			* Elements are stored in sorted order(< & >)
			* Fast search
			* No random access(there is a subscript operator)
			* Elements cannot be modified directly
			* Default sorting order is descending. (operator<)
			Not: map doesn't allow duplicates |but multimap does.
			Not: avoid using subscript operator for searching  inside the map.
			*/
			std::cout << "\n-*-*-*-*-* stlMap *-*-*-*-*-\n";
			{
				std::map<int, std::string> m{
				{1, "c"},
				{2, "c++"},
				{3, "c#"}
				};

				m.insert(std::pair<int, std::string>(7, "Java"));
				m.insert(std::make_pair(8, "Javascript"));
				m.insert(std::make_pair(8, "Javascript"));
				m[8] = "Javascript";

				m[0] = "Cuda";
				m[8] = "Opencl";
				auto itr = m.begin();
				std::cout << "Iterator: " << itr->first << " : " << itr->second << '\n';
				std::cout << "10: " << " : " << m[10] << '\n'; // If not find 10.element then inserts an empty value with key 10.
				for (const auto& x : m)
					std::cout << x.first << " : " << x.second << '\n';
				auto foundIter = m.find(1);
				if (foundIter != m.end())
					std::cout << "Found: " << foundIter->second << '\n';
				else
					std::cout << "Not Found\n";
			}

			std::cout << "\n-*-*-*-*-* stlMultiMap *-*-*-*-*-\n";
			{
				std::multimap<int, std::string> m2{
				{1, "c"},
				{2, "c++"},
				{3, "c#"}
				};
				m2.insert(std::pair<int, std::string>(7, "Java"));
				m2.insert(std::make_pair(8, "Javascript"));
				m2.insert(std::make_pair(8, "Javascript"));
				m2.insert(std::make_pair(8, "Javascript"));

				//m2[0] = "Cuda";
				//m2[8] = "Opencl";
				auto itr2 = m2.begin();
				std::cout << "Iterator: " << itr2->first << " : " << itr2->second << '\n';
				//std::cout << "10: " << " : " << m2[10] << '\n'; // If not find 10.element then inserts an empty value with key 10.
				for (const auto& x : m2)
					std::cout << x.first << " : " << x.second << '\n';
				//auto foundIter2 = m2.find(1);
				//if (foundIter != m2.end())
				//	std::cout << "Found: " << foundIter->second << '\n';
				//else
				//	std::cout << "Not Found\n";

				auto found = m2.equal_range(6);
				while (found.first != found.second) {
					std::cout << found.first->first << " : " << found.first->second << '\n';
					++found.first;
				}
			}


		}
		void Associative_main() {
			std::cout << "\n-*-*-*-*-* Associative_main *-*-*-*-*-\n";
			stlSet();
			stlMap();
		}
	}

	namespace Unordered {
		// Unordered Associative
		/*
		* Associative containers implemented as hash tables(hash acts like a key ;))
		* Values are hashed and stored in undefined order
		* Fast search, insertion/deletion, but may degrade over a period of time
		* std::unordered_set stores values that act as keys for hashing
		* std::unordered_map stores pairs (first is used to compute hash)
		* Iterators are constant
		Note: If there are too many entries in the buckets, then that will degrade the performance of the hash table.
		Note: hash function and hash table is a big topic in computer science. SEARCH IT!
		*/
		void stlUnordered_set() {
			/*
			*
			*/
			std::cout << "\n-*-*-*-*-* stlUnordered_set *-*-*-*-*-\n";
			{
				std::unordered_set<std::string> coll;
				coll.insert("a");
				coll.insert("a");
				coll.insert("a");
				coll.insert("b");
				coll.insert("c");
				coll.insert("d");
				coll.insert("e");
				coll.insert("f");
				coll.insert("g");
				coll.insert("g");
				coll.insert("g");
				coll.insert("srtgfhkmjnro�klh");

				std::cout << '\n';
				for (const auto x : coll) {
					std::cout << "# Bucket: " << coll.bucket(x) << " contains : " << x << '\n';
				}
				std::cout << '\n';
				// hash table stores a buckets
				std::cout << "Bucket count: " << coll.bucket_count() << '\n';
				std::cout << "Number of elements" << coll.size() << '\n';
				std::cout << "Load factor: " << coll.load_factor() << '\n'; // coll.load_factor() approaches to 1, the performance of the hash table degrades.
			}

			std::cout << "\n-*-*-*-*-* stlUnordered_multiset *-*-*-*-*-\n";
			{
				std::unordered_multiset<std::string> coll;
				coll.insert("a");
				coll.insert("a");
				coll.insert("a");
				coll.insert("b");
				coll.insert("c");
				coll.insert("d");
				coll.insert("e");
				coll.insert("f");
				coll.insert("g");
				coll.insert("g");
				coll.insert("g");
				coll.insert("srtgfhkmjnro�klh");

				std::cout << '\n';
				for (const auto x : coll) {
					std::cout << "# Bucket: " << coll.bucket(x) << " contains : " << x << '\n';
				}
				std::cout << '\n';
				// hash table stores a buckets
				std::cout << "Bucket count: " << coll.bucket_count() << '\n';
				std::cout << "Number of elements" << coll.size() << '\n';
				std::cout << "Load factor: " << coll.load_factor() << '\n'; // coll.load_factor() approaches to 1, the performance of the hash table degrades.
			}

		}
		void stlUnordered_map() {
			/*
			*
			*/
			std::cout << "\n-*-*-*-*-* stlUnordered_map *-*-*-*-*-\n";
			{
				std::unordered_map<int, std::string> coll;
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::make_pair(2, "b"));
				coll.insert(std::make_pair(3, "c"));
				coll.insert(std::make_pair(4, "d"));
				coll.insert(std::make_pair(5, "e"));
				coll.insert(std::make_pair(6, "f"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll[8] = "asedhfmsrdfgh";

				std::cout << '\n';
				for (const auto x : coll) {
					std::cout << "# Bucket: " << coll.bucket(x.first) << "->" << x.first << " : " << x.second << '\n';
				}
				std::cout << '\n';
				// hash table stores a buckets
				std::cout << "Bucket count: " << coll.bucket_count() << '\n';
				std::cout << "Number of elements" << coll.size() << '\n';
				std::cout << "Load factor: " << coll.load_factor() << '\n'; // coll.load_factor() approaches to 1, the performance of the hash table degrades.
			}

			std::cout << "\n-*-*-*-*-* stlUnordered_multimap *-*-*-*-*-\n";
			{
				std::unordered_multimap<int, std::string> coll;
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::pair<int, std::string>(1, "a"));
				coll.insert(std::make_pair(2, "b"));
				coll.insert(std::make_pair(3, "c"));
				coll.insert(std::make_pair(4, "d"));
				coll.insert(std::make_pair(5, "e"));
				coll.insert(std::make_pair(6, "f"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll.insert(std::pair<int, std::string>(7, "g"));
				coll.insert(std::make_pair(8, "asedhfmsrdfgh"));

				std::cout << '\n';
				for (const auto x : coll) {
					std::cout << x.first << " : " << x.second << '\n';
				}
				std::cout << '\n';

				std::cout << '\n';
				for (const auto x : coll) {
					std::cout << "# Bucket: " << coll.bucket(x.first) << "->" << x.first << " : " << x.second << '\n';
				}
				std::cout << '\n';
				// hash table stores a buckets
				std::cout << "Bucket count: " << coll.bucket_count() << '\n';
				std::cout << "Number of elements" << coll.size() << '\n';
				std::cout << "Load factor: " << coll.load_factor() << '\n'; // coll.load_factor() approaches to 1, the performance of the hash table degrades.
			}
		}
		void Unordered_main() {
			std::cout << "\n-*-*-*-*-* Unordered_main *-*-*-*-*-\n";
			stlUnordered_set();
			stlUnordered_map();
		}
	}

	namespace HASHES {
		class Employee {
			std::string m_Name;
			int m_Id;
		public:
			Employee(const std::string& n, int id) :m_Name(n), m_Id(id) {}
			const std::string& GetName()const {
				return m_Name;
			}
			int GetId()const {
				return m_Id;
			}
		};

		//Custom hash function
		struct EmployeeHash {
			size_t operator()(const Employee& emp)const {
				auto s1 = std::hash<std::string>{}(emp.GetName());
				auto s2 = std::hash<int>{}(emp.GetId());
				return s1 ^ s2; // use hash combinator of the boost is recommended
			}
		};
		//Custom function object for equality
		struct EmpEquality {
			bool operator()(const Employee& e1, const Employee e2)const {
				return e1.GetId() == e2.GetId();
			}
		};
		void Hashes() {
			std::cout << "\n-*-*-*-*-* Hashes *-*-*-*-*-\n";
			std::hash<std::string> h;
			//Hash is computed by the function object
			std::cout << "Hash:" << h("Hello") << std::endl;


			std::unordered_set<Employee, EmployeeHash, EmpEquality> coll;
			coll.insert(Employee("Umar", 123));
			coll.insert(Employee("Bob", 678));
			coll.insert(Employee("Joey", 612));

			for (const auto& x : coll) {
				std::cout << x.GetId() << ":" << x.GetName() << std::endl;
			}
		}
	}

	void stl_containers_main() {
		std::cout << "\n-*-*-*-*-* stl_containers_main *-*-*-*-*-\n";
		stl_containers::Sequential::Sequential_main();
		stl_containers::Associative::Associative_main();
		stl_containers::Unordered::Unordered_main();
		stl_containers::HASHES::Hashes();
	}
}

namespace stl_algorithms {
	/*
	*
	*/
	class Employee {
		std::string m_Name;
		int m_Id;
		std::string m_ProgLang;
	public:
		Employee(const std::string& n, int id, std::string pl) :m_Name(n), m_Id(id), m_ProgLang(pl) {}
		const std::string& GetName()const {
			return m_Name;
		}
		int GetId()const {
			return m_Id;
		}
		const std::string& GetProgrammingLanguage()const {
			return m_ProgLang;
		}
		bool operator<(const Employee& e)const {
			// default comparison operator
			return m_Id < e.m_Id;
		}
		bool operator>(const Employee& e)const {
			return m_Id > e.m_Id;
		}
		bool operator==(const Employee& e)const {
			return m_Id == e.m_Id;
		}
	};
	// !!! Creating a function object is more flexible because that way you can decide, which attribute to use for comparison !!!
	struct EmpCompare {
		bool operator ()(const Employee& e1, const Employee& e2)const {
			return e1.GetId() < e2.GetId();
		}
	};
	void stlSort() {
		/*
		*/
		std::cout << "\n-*-*-*-*-* stlSort *-*-*-*-*-\n";
		std::cout << "-*-*-*-*-* std::vector<Employee> *-*-*-*-*-\n";
		{
			std::vector<Employee> v{
			Employee{"Mustafa", 101, "Html"},
			Employee{"Selcuk", 102, "C++"},
			Employee{"Caglar", 103, "Python"},
			};
			// provied default comparison("operator<") and "operator>"
			// also I can define custom predicate callback function to sort them.
			std::sort(v.begin(), v.end(), [](const auto& e1, const auto& e2) {
				return e1.GetName() < e2.GetName();
				});
			for (const auto& e : v) {
				std::cout
					<< "Id: " << e.GetId() << "  | "
					<< "Name: " << e.GetName() << " | "
					<< "Language: " << e.GetProgrammingLanguage()
					<< '\n';
			}
		}

		std::cout << "-*-*-*-*-* std::set<Employee, EmpComp> *-*-*-*-*-\n";
		{
			std::set<Employee, EmpCompare> v{
			Employee{"Mustafa", 101, "Html"},
			Employee{"Selcuk", 102, "C++"},
			Employee{"Caglar", 103, "Python"},
			};
			for (const auto& e : v) {
				std::cout
					<< "Id:" << e.GetId()
					<< " | Name:" << e.GetName()
					<< " | Language:" << e.GetProgrammingLanguage() << std::endl;
			}
		}
	}

	struct EmpIds {
		std::vector<int> m_Ids;
		void operator()(const Employee& emp) {
			if (emp.GetProgrammingLanguage() == "C++") {
				m_Ids.push_back(emp.GetId());
			}
		}
	};
	void count_find_foreach() {
		/*
		*/
		std::cout << "\n-*-*-*-*-* count_find_foreach *-*-*-*-*-\n";
		std::vector<Employee> v{
			Employee{"Mustafa", 101, "Html"},
			Employee{"Selcuk", 102, "C++"},
			Employee{"Caglar", 103, "Python"},
		};

		//count
		auto cppCount = std::count(v.begin(), v.end(), Employee{ "", 0, "C++" });
		std::cout << "count: " << cppCount << '\n';
		auto cppCount_if = std::count_if(v.begin(), v.end(), [](const auto& e) {
			return e.GetProgrammingLanguage() == "C++";
			});
		std::cout << "count_if: " << cppCount_if << '\n';
		//find
		auto iter = std::find_if(v.begin(), v.end(), [](const auto& e) {
			return e.GetProgrammingLanguage() == "Java";
			});
		if (iter != v.end())
			std::cout << "Found: " << iter->GetName() << " is a Java programmer\n";
		//print all to the console
		std::for_each(v.begin(), v.end(), [](const auto& e) {
			std::cout << e.GetName() << '\n';
			});
		//push all of them
		// only algorithm that copy and return.
		auto foundIds = std::for_each(v.begin(), v.end(), EmpIds()); // This functionality only possible with function objects.
		for (auto id : foundIds.m_Ids) {
			std::cout << "Id : " << id << '\n';
		}
	}

	void stl_algorithms_main() {
		std::cout << "\n-*-*-*-*-* stl_algorithms_main *-*-*-*-*-\n";
		stlSort();
		count_find_foreach();
	}
}

namespace STL_changes {
	template<typename Container>
	void Print(const Container& container, const char* msg = "") {
		std::cout << msg << '\n';
		for (auto a : container) {
			std::cout << a << '\n';
		}
	}
	void changes1() {
		/*
		If you created an object and you want to store inside of container without creating a copy -> use emplace, emplace_back, emplace_front
		*/
		std::cout << "\n-*-*-*-*-* changes1 *-*-*-*-*-\n";
		std::vector<Integer> ints;
		ints.push_back(5);

		// They are the same without "noexcept move contructor and move operator"
		Integer val{ 5 };
		ints.push_back(val);
		ints.emplace_back(val);

		// 
		std::vector<std::pair<int, std::string>> data;
		data.push_back(std::make_pair(2, "asdf"));
		data.emplace_back(2, "asdf");

	}
	void changes2() {
		/*
		* emplace_back requires "noexcept move operations" ("noexcept move assignment and move constructor")
		*/
		std::cout << "\n-*-*-*-*-* changes2 *-*-*-*-*-\n";
		std::vector<Integer> ints;
		ints.emplace_back(1);
		ints.emplace_back(2);
		ints.emplace_back(3);
	}
	void changes3() {
		/*
		* vector size == capacity => vector allocates more memory, increases capacity
		* Even remove the element capacity will not shrink. Allocation will be remained
		*/
		std::cout << "\n-*-*-*-*-* changes3 *-*-*-*-*-\n";
		std::vector<int> ints;
		for (size_t i = 0; i < 10; i++) {
			ints.emplace_back(i);
		}
		std::cout << "Size: " << ints.size() << '\n';
		std::cout << "Capacity: " << ints.capacity() << '\n';
		ints.erase(ints.begin(), ints.end() - 10); // capacity will not shrink. Allocation will be remained
		ints.shrink_to_fit(); // to reduces capacity. frees memory, extra unused memory is trimmed.
		std::cout << "After erase\n";
		std::cout << "Size: " << ints.size() << '\n';
		std::cout << "Capacity: " << ints.capacity() << '\n';
	}
	void changes4() {
		std::cout << "\n-*-*-*-*-* changes4 *-*-*-*-*-\n";
		std::vector<int> vInts{ 1,2,3,4 };
		std::list<int> listInts{ 1,2,3,4 };
		std::deque<int> dequeInts{ 1,2,3,4 };

		std::erase(vInts, 2);
		std::erase(listInts, 2);
		std::erase(dequeInts, 2);

		Print(vInts, "vector");
		Print(listInts, "list");
		Print(dequeInts, "deque");


	}
	void changes5() {
		/*
		If you have an iterator close to the position where the new element can be inserted, then you can use emplacement insert that element.
		*/
		std::cout << "\n-*-*-*-*-* changes5 *-*-*-*-*-\n";
		std::set<int> data{ 1,5,8,9 };
		data.emplace_hint(data.begin(), 0);

		//before c++20
		auto it = data.find(6);
		if (it != data.end()) {
			std::cout << "Found it!";
		}
		//after c++20
		auto isContains = data.contains(6);

		std::set<std::string> names{ "Erlang", "Nim", "Mesele", "Harry" };
		auto it2 = names.find("Mesele");
		//auto& name2 = *it2; // constant iterator
		//name2[0] = 'U'; // constant iterator
		auto name = *it2;
		name[0] = 'U'; // doesn't change underlying data
		names.erase(it2);
		names.insert(name);

		// I can access to underlying data of set and map
		auto node = names.extract(it2); // copy forgotten object
		node.value()[0] = 'U';
		names.insert(std::move(node));

	}
	void STL_changes_main() {
		std::cout << "\n-*-*-*-*-* STL_changes_main *-*-*-*-*-\n";

		changes1();
		changes2();
		changes3();
		changes4();
		changes5();
	}
}

namespace AssignmentSTL {
	/*
	STL Project
	Create a contacts application that allows users to store contact information:

	First Name
	Last Name
	Primary phone number
	Secondary phone number
	Email id
	Address
	Company
	Group (Friends, Family, Coworker, Acquaintance)
	Provide the following features:

	Display all contacts sorted by first or last name (provide an option that users can choose)
	Display only first name with primary number
	Display contacts from the same company only
	Display contacts based on group type
	Allow contact search by first or last name
	Display count of contacts by company and group.
	Decide carefully about the usage of containers and algorithms.
	*/
	void AssignmentSTL_main()
	{

	}
}

void STL_main() {
	//stl_containers::stl_containers_main();
	//stl_algorithms::stl_algorithms_main();
	//STL_changes::STL_changes_main();
	AssignmentSTL::AssignmentSTL_main();
}