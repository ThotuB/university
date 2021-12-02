import classes from './styles/search.module.css'

function SearchBar() {
    return (
        <div className="border-2">
            <input className="w-full" type="text" placeholder="Search" />
        </div>
    );
}

export default SearchBar;