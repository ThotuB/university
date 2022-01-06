import Link from 'next/link';
import NavLink from "./NavLink";
import SearchBar from "./Search";
import DropdownMenu from "./Menu";
import AccountIcon from "components/common/AccountIcon";

export default function Nav() {
    return (
        <nav className="bg-white shadow sticky top-0 z-50">
            <div className="container px-6 py-3 mx-auto">
                <div className="flex flex-row justify-between">
                    <div className="flex gap-3">
                        <Link href="/">
                            <button className="px-4 bg-purple-300 rounded-xl text-2xl font-bold">
                                Calorie Counter
                            </button>
                        </Link>

                        <SearchBar/>
                    </div>

                    <div className="flex items-center gap-3">
                            <NavLink href="/home" label='Home'/>
                            <NavLink href="/food" label='Food'/>
                            <NavLink href="/recipes" label='Recipes'/>

                        <AccountIcon name="Tatu Bogdan"/>
                        <DropdownMenu />
                    </div>
                </div>
            </div>
        </nav>
    );
}
