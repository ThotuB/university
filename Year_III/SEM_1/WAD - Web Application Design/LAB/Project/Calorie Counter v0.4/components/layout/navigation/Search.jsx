import { Search } from '../../svg/Heroicons'

function SearchBar() {
  return (
    <div className="flex items-center">
      <div className="absolute pl-3">
        <Search className="text-gray-400"/>
      </div>

      <input type="text" className="w-full h-full border border-gray-400 pl-11 text-gray-700 rounded-xl focus:ring-purple-300 focus:outline-none focus:ring" placeholder="Search"/>
    </div>
  );
}

export default SearchBar;