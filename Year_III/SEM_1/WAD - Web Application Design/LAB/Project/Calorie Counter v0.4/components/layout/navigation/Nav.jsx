import Link from 'next/link';
import NavLink from "./NavLink";
import SearchBar from "./Search";
import DropdownMenu from "./Menu";
import AccountIcon from "../../common/AccountIcon";

function Navigation() {
  return (
    <nav className="bg-white shadow mb-4 sticky top-0 z-50">
      <div className="container px-6 py-3 mx-auto">
        <div className="flex flex-row justify-between">
          <div className="flex gap-3">
            <Link href="/">
              <button className="px-4 bg-purple-300 rounded-xl text-2xl font-bold">
                Calorie Counter
              </button>
            </Link>

            <SearchBar />
          </div>

          <div className="flex items-center gap-3">
              <NavLink href="/home">
                Home
              </NavLink>
              <NavLink href="/food">
                Food
              </NavLink>
              <NavLink href="/recipes">
                Recipes
              </NavLink>

            <AccountIcon name="Tatu Bogdan"/>
            <DropdownMenu />
          </div>
        </div>
      </div>
    </nav>
  );
}

export default Navigation;
