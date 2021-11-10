import Link from 'next/link';

function NavLink(props) {
    const { href, children } = props;
    return (
        <Link href={href}>
            <button className="px-3 py-2 rounded-md text-gray-700 transition-colors duration-200 transform hover:bg-purple-400 font-bold">
                {children}
            </button>
        </Link>
    );
}

export default NavLink;