import Link from 'next/link';
import SearchBar from './search';
import style from './styles/navigation.module.css'

function Navigation() {
    return (
        <div className={style.nav}>
            <div className={style.nav_bar}>
                <div className="">
                    <Link href="/home">CALORIE COUNTER</Link>
                </div>
                <div className="">
                    <SearchBar />
                </div>
                <div className={style.links}>
                    <div>
                        <Link href="/home">Home</Link>
                    </div>
                    <div>
                        <Link href="/recipes">Recipes</Link>
                    </div>
                    <div>
                        <Link href="/account">Account</Link>
                    </div>
                    <div>
                        <Link href="/settings">Settings</Link>
                    </div>
                </div>
            </div>
        </div>
    )
}

export default Navigation;