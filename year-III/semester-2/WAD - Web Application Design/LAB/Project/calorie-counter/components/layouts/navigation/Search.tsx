import { Search } from 'components/common/svg/Heroicons'
import { useState } from 'react'
import Router from 'next/router'

function SearchBar() {
    const [searchResult, setSearchResult] = useState('')

    const handleChange = (searchTerm: string) => {
        setSearchResult(searchTerm)
        Router.push({
            pathname: '/food',
            query: {
                search: searchTerm
            }
        })
    }

    return (
        <div className="flex items-center">
            <div className="absolute pl-3">
                <Search className="text-gray-400" />
            </div>

            <input
                type="text"
                className="w-full h-full border border-gray-400 pl-11 text-gray-700 rounded-xl focus:ring-purple-300 focus:outline-none focus:ring"
                placeholder="Search"
                value={searchResult}
                onChange={(e) => handleChange(e.target.value)}
            />
        </div>
    );
}

export default SearchBar;