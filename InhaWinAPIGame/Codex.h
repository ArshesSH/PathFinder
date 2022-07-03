#pragma once

#include <vector>
#include <memory>
#include <string>

template<class T>
class Codex
{
private:
	class Entry
	{
	public:
		Entry( const std::wstring& key, const std::shared_ptr<T>& pResource)
			:
			key(key),
			pResource(pResource)
		{}
		std::wstring key;
		const std::shared_ptr<T> pResource;
	};

public:
	// Retrive a ptr to resource based on string
	static const std::shared_ptr<T> Retrieve( const std::wstring& key )
	{
		return Get()._Retrieve(key);
	}
	// Remove all entries from codex
	static void RemoveAll()
	{
		Get()._RemoveAll();
	}

private:
	// find ptr to resoruce based on string
	const T* _Retrieve( const std::wstring& key )
	{
		// find position of resource or when resource should be ( binary search )
		auto i = std::lower_bound( entries.begin(), entries.end(), key,
			[]( const Entry& e, const std::wstring& key )
			{
				return e.key < key;
			}
		);

		// if resource does not exist, load and store in sorted pos in coex, and set i to point to it
		if ( i == entries.end() || i->key != key )
		{
			// construct entry in i
			i = entries.emplace_back( i, key, std::make_unique<T>(key) );
		}

		// Return ptr to resource in codex
		return i->pResource;
	}

	void _RemoveAll()
	{
		entries.clear();
	}

	// Get Singleton Instance
	static Codex& Get()
	{
		static Codex codex;
		return codex;
	}

private:
	std::vector<Entry> entries;
};